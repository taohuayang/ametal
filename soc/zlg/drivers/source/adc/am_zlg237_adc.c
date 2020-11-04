/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg237.cn/
*******************************************************************************/

/**
 * \file
 * \brief ADC����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-12  ari, first implementation
 * \endinternal
 */

#include "am_zlg237_adc.h"
#include "ametal.h"
#include "am_int.h"
#include "am_clk.h"
#include "amhw_zlg237_rcc.h"
#include "hw/amhw_zlg237_adc.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

#define __ADC_HW_DECL(p_hw_adc, p_drv)   \
            amhw_zlg237_adc_t *p_hw_adc =   \
            ((am_zlg237_adc_dev_t *)p_drv)->p_devinfo->p_hw_adc

#define __ADC_VREF_GET(p_drv)  (((am_zlg237_adc_dev_t *)p_drv)->p_devinfo->vref)

/*******************************************************************************
* ��������
*******************************************************************************/

/** \brief ����ADCת�� */
static int __fn_adc_start (void                 *p_drv,
                           int                   chan,
                           am_adc_buf_desc_t    *p_desc,
                           uint32_t              desc_num,
                           uint32_t              count,
                           uint32_t              flags,
                           am_adc_seq_cb_t       pfn_callback,
                           void                  *p_arg);

/** \brief ֹͣת�� */
static int __fn_adc_stop (void *p_drv, int chan);

/** \brief ��ȡADC�Ĳ����� */
static int __fn_adc_rate_get (void          *p_drv,
                              int            chan,
                              uint32_t      *p_rate);

/** \brief ����ADC�Ĳ����ʣ�ʵ�ʲ����ʿ��ܴ��ڲ��� */
static int __fn_adc_rate_set (void         *p_drv,
                              int           chan,
                              uint32_t      rate);

/** \brief ��ȡADCת������ */
static uint32_t __fn_bits_get (void *p_drv, int chan);

/** \brief ��ȡADC�ο���ѹ */
static uint32_t __fn_vref_get (void *p_drv, int chan);

/**
 * \brief ADC������
 */
static const struct am_adc_drv_funcs __g_adc_drvfuncs = {
    __fn_adc_start,
    __fn_adc_stop,
    __fn_adc_rate_get,
    __fn_adc_rate_set,
    __fn_bits_get,
    __fn_vref_get
};

/******************************************************************************/

/**
 * \brief ADC����ת������ж�
 */
void __zlg237_adc_irq_handle (void *p_arg)
{
    am_zlg237_adc_dev_t    *p_dev      = (am_zlg237_adc_dev_t *)p_arg;
    amhw_zlg237_adc_t      *p_hw_adc   =  NULL;

    /* ��ǰת�������������� */
    am_adc_buf_desc_t *p_desc  = &(p_dev->p_desc[p_dev->desc_index]);
    uint16_t          *p_buf16 = (uint16_t *)p_desc->p_buf;
    uint16_t           adc_dat = 0;

    if ( p_buf16 == NULL) {
        return ;
    }

    p_hw_adc =  (amhw_zlg237_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    amhw_zlg237_adc_swstart_enable(p_hw_adc);

    /* �ж��Ƿ�ǰ��������Ч�� */
    if (p_dev->conv_cnt < p_desc->length) {

        /* �����ת�������жϱ�־ */
        amhw_zlg237_adc_status_flag_clr(p_hw_adc,AMHW_ZLG237_ADC_END_FLAG);

        /* ��ȡ���� */
        adc_dat = amhw_zlg237_adc_regular_data_get (p_hw_adc);

        /* �������� */
        if (AM_ADC_DATA_ALIGN_LEFT & p_dev->flags) {
            p_buf16[p_dev->conv_cnt] = adc_dat << 4;
        } else {
            p_buf16[p_dev->conv_cnt] = adc_dat >> p_dev->right_bit;
        }

        p_dev->conv_cnt++;

        /* �жϵ�ǰ�����������Ƿ��Ѿ����ת�� */
        if (p_dev->conv_cnt >= p_desc->length) {

            p_dev->conv_cnt = 0;
            if (NULL != p_desc->pfn_complete) {
                p_desc->pfn_complete(p_desc->p_arg, AM_OK);
            }

            p_dev->desc_index++;

            /* �ж����������������Ƿ����һ��ת�� */
            if (p_dev->desc_index == p_dev->desc_num) {

                p_dev->desc_index = 0;
                if (NULL != p_dev->pfn_callback) {
                    p_dev->pfn_callback(p_dev->p_arg, AM_OK);
                }

                p_dev->seq_cnt++; /* ��������ת����� */
                if (p_dev->count != 0 && p_dev->seq_cnt == p_dev->count) {
                    p_dev->seq_cnt = 0;

                    amhw_zlg237_adc_status_flag_clr(p_hw_adc,
                                                    AMHW_ZLG237_ADC_END_FLAG);
                    __fn_adc_stop (p_dev, p_dev->chan);  /* �ر�ģ�� */

                    return ; /* ���� */
                }
            }
        }
    } else {
        if (NULL != p_dev->pfn_callback) {
            p_dev->pfn_callback(p_dev->p_arg, AM_ERROR);
        }
        if (amhw_zlg237_adc_status_flag_check(
            p_hw_adc,AMHW_ZLG237_ADC_END_FLAG) == AM_TRUE) {
            amhw_zlg237_adc_status_flag_clr(p_hw_adc,AMHW_ZLG237_ADC_END_FLAG);
        }
        __fn_adc_stop (p_dev, p_dev->chan);
    }
}

/** \brief ָ��ADC�ж����Ӻ��� */
static int __fn_adc_connect (void *p_drv)
{
    am_zlg237_adc_dev_t *p_dev = NULL;
    amhw_zlg237_adc_t   *p_hw_adc;
    
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg237_adc_dev_t *)p_drv;
    p_hw_adc = (amhw_zlg237_adc_t *)p_dev->p_devinfo->adc_reg_base;

    /* ת�������ж�ʹ��*/
    amhw_zlg237_adc_int_enable(p_hw_adc, AMHW_ZLG237_ADC_INT_END);

    /* ����ת������ж� */
    am_int_connect(p_dev->p_devinfo->inum,
                   __zlg237_adc_irq_handle,
                   (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return AM_OK;
}

/**
 * \brief ADC ʹ���ж�ģʽʱ��������
 */
static void __adc_int_work_startup (am_zlg237_adc_dev_t       *p_dev,
                                    amhw_zlg237_adc_channel_t  chan)
{
    amhw_zlg237_adc_t *p_hw_adc = (amhw_zlg237_adc_t *)
                                  (p_dev->p_devinfo->adc_reg_base);

    /* ADC����*/
    amhw_zlg237_adc_disable(p_hw_adc);

    /* ����ĳһͨ���Ĳ���ʱ��*/
    amhw_zlg237_adc_smpr_set(p_hw_adc,
                             AMHW_ZLG237_ADC_CHAN_ST239_5,
                             chan);

    /* ���ù���ͨ������  1�� */
    amhw_zlg237_adc_regular_channel_length_set(
        p_hw_adc,AMHW_ZLG237_ADC_REGULAR_CHAN_LENGTH_1);

    /* ���ӹ�������ͨ����ADC����ͨ�� */
    amhw_zlg237_adc_regular_channel_order_set(
        p_hw_adc,
        AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_1st,
        chan);

    /* ת�������ж�ʹ��*/
    amhw_zlg237_adc_int_enable(p_hw_adc, AMHW_ZLG237_ADC_INT_END);

    /* ADCʹ��*/
    amhw_zlg237_adc_enable(p_hw_adc);

    /* ���ø�λУ׼*/
    amhw_zlg237_adc_rstcal_enable(p_hw_adc);

    /* �ȴ���λУ׼����*/
    while(amhw_zlg237_adc_rstcal_check(p_hw_adc) == AM_FALSE);

    /* ����ADУ׼*/
    amhw_zlg237_adc_cal_enable(p_hw_adc);

    /* �ȴ�ADУ׼����*/
    while(amhw_zlg237_adc_cal_check(p_hw_adc) == AM_FALSE);

    /* ����ת�� */
    amhw_zlg237_adc_swstart_enable(p_hw_adc);

}

/**
 * \brief ����ADCת��
 */
static int __fn_adc_start (void                *p_drv,
                           int                  chan,
                           am_adc_buf_desc_t   *p_desc,
                           uint32_t             desc_num,
                           uint32_t             count,
                           uint32_t             flags,
                           am_adc_seq_cb_t      pfn_callback,
                           void                *p_arg)
{
    am_zlg237_adc_dev_t *p_dev = NULL;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev = (am_zlg237_adc_dev_t *)p_drv;

    p_dev->p_desc       = p_desc;
    p_dev->chan         = chan;
    p_dev->desc_num     = desc_num;
    p_dev->count        = count;
    p_dev->flags        = flags;
    p_dev->pfn_callback = pfn_callback;
    p_dev->p_arg        = p_arg;
    p_dev->seq_cnt      = 0;
    p_dev->desc_index   = 0;
    p_dev->conv_cnt     = 0;

    am_int_enable(p_dev->p_devinfo->inum); /* �����ж� */
    __adc_int_work_startup(p_dev,(amhw_zlg237_adc_channel_t)chan); /* �жϹ���ģʽ�������� */

    return AM_OK;
}

/**
 * \brief ֹͣת��
 */
static int __fn_adc_stop (void *p_drv, int chan)
{
    am_zlg237_adc_dev_t *p_dev    = (am_zlg237_adc_dev_t *)p_drv;
    amhw_zlg237_adc_t   *p_hw_adc = (amhw_zlg237_adc_t *)
                                    (p_dev->p_devinfo->adc_reg_base);

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    amhw_zlg237_adc_swstart_disable(p_hw_adc);
    amhw_zlg237_adc_int_disable(p_hw_adc, AMHW_ZLG237_ADC_INT_END);
    amhw_zlg237_adc_disable(p_hw_adc);

    am_int_disable(p_dev->p_devinfo->inum);

    return AM_OK;
}

/**
 * \brief ��ȡADC�Ĳ�����
 */
static int __fn_adc_rate_get (void          *p_drv,
                              int            chan,
                              uint32_t      *p_rate)
{
    am_zlg237_adc_dev_t *p_dev;
    amhw_zlg237_adc_t   *p_hw_adc;
    
    uint32_t sample;
    uint32_t adc_clkdiv = 1;
    uint32_t i;

    uint8_t  sample_time[8] = {
      15, 21, 27, 42, 55, 69, 85, 253
    };

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg237_adc_dev_t *)p_drv;
    p_hw_adc = (amhw_zlg237_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    i = amhw_zlg237_adc_smpr_get(p_hw_adc,
                                (amhw_zlg237_adc_channel_t)p_dev->chan);
    sample = sample_time[i];

    /* ADC��Ƶ����λ��RCC������ */
    adc_clkdiv = 2 * (amhw_zlg237_rcc_adc_div_get() + 1);
    *p_rate = am_clk_rate_get(p_dev->p_devinfo->clk_num) /
              (adc_clkdiv * sample);

    return AM_OK;
}

/**
 * \brief ����ADC�Ĳ����ʣ�ʵ�ʲ����ʿ��ܴ��ڲ���
 */
static int __fn_adc_rate_set (void          *p_drv,
                              int            chan,
                              uint32_t       rate)
{
    uint32_t   clk;
    uint32_t   temp_rate = 0;
    uint8_t    i = 0, j  = 0;

    uint8_t  sample_time[8] = {
      15, 21, 27, 42, 55, 69, 85, 253
    };

    uint32_t   rate_high = 0;
    uint32_t   rate_low  = 0;
    uint32_t   rate_err  = 0;

    struct adc_err  {
      uint32_t err;
      uint8_t  sample_time;
      uint8_t  adc_div;
    };

    struct adc_err    adc_rate_err;
    am_zlg237_adc_dev_t *p_dev;
    amhw_zlg237_adc_t   *p_hw_adc;
    
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zlg237_adc_dev_t *)p_drv;
    p_hw_adc = (amhw_zlg237_adc_t *)(p_dev->p_devinfo->adc_reg_base);
    
    adc_rate_err.err         = rate;
    adc_rate_err.sample_time = 0;
    adc_rate_err.adc_div     = 0;

    clk       = am_clk_rate_get(p_dev->p_devinfo->clk_num);
    rate_high = clk / 15;
    rate_low  = clk / (8 * 253);

    if (rate < rate_low || rate > rate_high) {
        return -AM_EINVAL;
    }

    for(i = 1; i < 9; i++) {
        if (rate >= (clk / (i * 253)) &&
            rate <= (clk / (i * 15))) {

            for(j = 0; j < 8; j++) {

                  temp_rate = (clk / (i * sample_time[j]));
                  rate_err = temp_rate >= rate ? temp_rate - rate :
                                                 rate - temp_rate;
                  if (rate_err < adc_rate_err.err) {
                      adc_rate_err.err = rate_err;
                      adc_rate_err.adc_div = i;
                      adc_rate_err.sample_time = j;
                  }

                  if (adc_rate_err.err == 0) {
                      break;
                  }
              }
        }
    }
    amhw_zlg237_rcc_adc_div_set (adc_rate_err.adc_div / 2 - 1);
    amhw_zlg237_adc_smpr_set (p_hw_adc,
          (amhw_zlg237_adc_sample_time_t)adc_rate_err.sample_time,
          (amhw_zlg237_adc_channel_t)chan);

    return AM_OK;
}

/**
 * \brief ��ȡADCת������
 */
static uint32_t __fn_bits_get (void *p_drv, int chan)
{
    /* ��֧��12λ�ֱ��� */
    return AMHW_ZLG237_ADC_DATA_VALID_12BIT;
}

/**
 * \brief ��ȡADC�ο���ѹ
 */
static uint32_t __fn_vref_get (void *p_drv, int chan)
{
    if (NULL == p_drv) {
        return 0;   /* ��Դ�Ѿ��ͷţ��ο���ѹδ֪ */
    }

    return (uint32_t)__ADC_VREF_GET(p_drv);
}

/**
 * \brief ADC��ʼ��
 */
am_adc_handle_t am_zlg237_adc_init (am_zlg237_adc_dev_t           *p_dev,
                                    const am_zlg237_adc_devinfo_t *p_devinfo)
{
    uint16_t bit = 0;

    amhw_zlg237_adc_t   *p_hw_adc = NULL;

    if (NULL == p_devinfo || NULL == p_dev ) {
        return NULL;
    }

    p_dev->p_devinfo         = p_devinfo;
    p_dev->adc_serve.p_funcs = &__g_adc_drvfuncs;
    p_dev->adc_serve.p_drv   = p_dev;

    p_dev->pfn_callback      = NULL;
    p_dev->p_desc            = NULL;
    p_dev->p_arg             = NULL;
    p_dev->desc_num          = 0;
    p_dev->flags             = 0;
    p_dev->count             = 0;
    p_dev->chan              = 0;
    p_dev->seq_cnt           = 0;
    p_dev->desc_index        = 0;
    p_dev->conv_cnt          = 0;

    /* ���ų�ʼ�� */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_hw_adc = (amhw_zlg237_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    /* ADC���� */
    amhw_zlg237_adc_disable(p_hw_adc);

    /* �ر�ɨ��ģʽ��ע��ͨ�����ģʽ������ͨ�����ģʽ*/
    amhw_zlg237_adc_scan_mode_disable(p_hw_adc);
    amhw_zlg237_adc_injected_disc_disable(p_hw_adc);
    amhw_zlg237_adc_regular_disc_disable(p_hw_adc);

    /* ����ת�� */
    amhw_zlg237_adc_cont_set(p_hw_adc, AMHW_ZLG237_ADC_CONVERSION_SINGLE);

    /* ���óɶ���ģʽ*/
    amhw_zlg237_adc_dul_mode_set(p_hw_adc, AMHW_ZLG237_ADC_DUL_MODE_0);

    /* ���ù���ͨ���ⲿ�����������ó����������ʽ */
    amhw_zlg237_adc_extirig_enable(p_hw_adc);
    amhw_zlg237_adc_extsel_set(p_hw_adc, AMHW_ZLG237_ADC12_REGULAR_SWSTART);

    /* ���뷽ʽ--�Ҷ���*/
    amhw_zlg237_adc_data_alignment_set(p_hw_adc,AM_ADC_DATA_ALIGN_RIGHT);

    /* ��Чλ����ȡ */
    bit = __fn_bits_get(p_dev, 0);

    /* ��������λ�� */
    p_dev->right_bit = 12 - bit;

    /* ���ò����� */
    __fn_adc_rate_set(p_dev, 0, 100000);

    if( p_dev->p_devinfo->temp_mode == 0) {
        amhw_zlg237_adc_tsvrefe_disable(p_hw_adc);
    } else {
        amhw_zlg237_adc_tsvrefe_enable(p_hw_adc);
    }

    /* ADCʹ��*/
    amhw_zlg237_adc_enable(p_hw_adc);

    /* ���ø�λУ׼*/
    amhw_zlg237_adc_rstcal_enable(p_hw_adc);

    /* �ȴ���λУ׼����*/
    while(amhw_zlg237_adc_rstcal_check(p_hw_adc) == AM_FALSE);

    /* ����ADУ׼*/
    amhw_zlg237_adc_cal_enable(p_hw_adc);

    /* �ȴ�ADУ׼����*/
    while(amhw_zlg237_adc_cal_check(p_hw_adc) == AM_FALSE);

    /* ע��ADC����ж� */
    __fn_adc_connect(p_dev);

    return (am_adc_handle_t)(&(p_dev->adc_serve));
}

/**
 * \brief ADCȥ��ʼ��
 */
void am_zlg237_adc_deinit (am_adc_handle_t handle)
{
    am_zlg237_adc_dev_t *p_dev    = (am_zlg237_adc_dev_t *)handle;
    amhw_zlg237_adc_t   *p_hw_adc = NULL;

    if (NULL == p_dev) {
        return ;
    }

    p_hw_adc = (amhw_zlg237_adc_t *)(p_dev->p_devinfo->adc_reg_base);
    am_int_disable(p_dev->p_devinfo->inum);

    /* �ر������ж� */
    amhw_zlg237_adc_int_disable(p_hw_adc, AMHW_ZLG237_ADC_INT_ALL);

    /* ADC���� */
    amhw_zlg237_adc_disable(p_hw_adc);

    p_dev->adc_serve.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */

/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ADC����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-17  cds, first implementation
 * \endinternal
 */

#include "am_hc32f460_adc.h"
#include "ametal.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "hw/amhw_hc32f460_rcc.h"
#include "hw/amhw_hc32f460_adc.h"
#include "hc32f460_irq_handle.h"
#include "am_hc32f460.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

#define __ADC_HW_DECL(p_hw_adc, p_drv)   \
            amhw_hc32f460_adc_t *p_hw_adc =   \
            ((am_hc32f460_adc_dev_t *)p_drv)->p_devinfo->p_hw_adc

#define __ADC_VREF_GET(p_drv)  (((am_hc32f460_adc_dev_t *)p_drv)->p_devinfo->vref)
#define __ADC_BITS_GET(p_drv)  (((am_hc32f460_adc_dev_t *)p_drv)->p_devinfo->bits_mode)

#define AMHW_HC32F460_ADC1_INT_VSSEL_BITS_MASK    (0xF)
#define AMHW_HC32F460_ADC2_INT_VSSEL_BITS_MASK    (0xF << 4)

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
void hc32f460_adc_irq_handle (void *p_arg)
{
    am_hc32f460_adc_dev_t    *p_dev      = (am_hc32f460_adc_dev_t *)p_arg;
    amhw_hc32f460_adc_t      *p_hw_adc   =  NULL;

    /* ��ǰת�������������� */
    am_adc_buf_desc_t *p_desc  = &(p_dev->p_desc[p_dev->desc_index]);
    uint16_t          *p_buf16 = (uint16_t *)p_desc->p_buf;
    uint16_t           adc_dat = 0;

    if ( p_buf16 == NULL) {
        return ;
    }

    p_hw_adc =  (amhw_hc32f460_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    /* �ж��Ƿ�ǰ��������Ч�� */
    if (p_dev->conv_cnt < p_desc->length) {

        /* �����ת�������жϱ�־ */
        amhw_hc32f460_adc_int_flag_clr(p_hw_adc,
                                       AMHW_HC32F460_ADC_INT_EOCAF);

        /* ��ȡ���� */
        adc_dat = amhw_hc32f460_adc_ch_data_get (p_hw_adc,
                                                 p_dev->chan,
                                                 p_dev->p_devinfo->bits_mode,
                                                 AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

        /* �������� */
        if (AM_ADC_DATA_ALIGN_LEFT & p_dev->flags) {
            p_buf16[p_dev->conv_cnt] = adc_dat << (16 - p_dev->left_bit);
        } else {
            p_buf16[p_dev->conv_cnt] = adc_dat;
        }

        p_dev->conv_cnt++;

        /* �жϵ�ǰ�����������Ƿ��Ѿ����ת�� */
        if (p_dev->conv_cnt >= p_desc->length) {

            p_dev->conv_cnt = 0;
            if (NULL != p_desc->pfn_complete) {
                p_desc->pfn_complete(p_desc->p_arg, AM_OK);
            }

            p_dev->desc_index++;

            /** \brief �ж����������������Ƿ����һ��ת�� */
            if (p_dev->desc_index == p_dev->desc_num) {

                p_dev->desc_index = 0;
                if (NULL != p_dev->pfn_callback) {
                    p_dev->pfn_callback(p_dev->p_arg, AM_OK);
                }

                p_dev->seq_cnt++; /* ��������ת����� */
                if (p_dev->count != 0 && p_dev->seq_cnt == p_dev->count) {
                    p_dev->seq_cnt = 0;

                    __fn_adc_stop (p_dev, p_dev->chan);  /* �ر�ģ�� */

                    return ;
                }
            }
        } else {

            /* ����ת������ */
            amhw_hc32f460_adc_convert_start(p_hw_adc);

        }

    } else {
        if (NULL != p_dev->pfn_callback) {
            p_dev->pfn_callback(p_dev->p_arg, AM_ERROR);
        }

        __fn_adc_stop (p_dev, p_dev->chan);
    }
}

/** \brief ָ��ADC�ж����Ӻ��� */
static int __fn_adc_connect (void *p_drv)
{
    am_hc32f460_adc_dev_t *p_dev = NULL;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev = (am_hc32f460_adc_dev_t *)p_drv;

    /* �����жϺ��� */
    if (p_dev->p_devinfo->dev_id == 1) {
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_ADC1_INT_VSSEL_BITS_MASK);
    } else if (p_dev->p_devinfo->dev_id == 2){
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_ADC2_INT_VSSEL_BITS_MASK);
    }

    am_int_connect(p_dev->p_devinfo->inum,
                   IRQ142_Handler,
                   (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return AM_OK;
}

/**
 * \brief ADC ʹ���ж�ģʽʱ��������
 */
static void __adc_int_work_startup (am_hc32f460_adc_dev_t       *p_dev,
                                    uint8_t                      chan)
{
    amhw_hc32f460_adc_t *p_hw_adc = (amhw_hc32f460_adc_t *)
                                    (p_dev->p_devinfo->adc_reg_base);

    if (p_dev->p_devinfo->p_ioinfo != NULL) {

        /* ����ADC����ͨ�������� */
        amhw_hc32f460_adc_channel_mux_set(p_hw_adc,
                                          chan,
                                          p_dev->p_devinfo->p_ioinfo[chan].chan_sel);

        /* ����ת��ͨ�� */
        amhw_hc32f460_adc_seq_a_channel_sel0(p_hw_adc, chan);

        /* GPIO����ģʽ���� */
        am_gpio_pin_cfg(p_dev->p_devinfo->p_ioinfo[chan].gpio,
                        p_dev->p_devinfo->p_ioinfo[chan].func);


        /* �������ݶ��뷽ʽΪ�Ҷ��� */
        amhw_hc32f460_adc_data_align_set(p_hw_adc,
                                         AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

        /* �ж�ʹ��*/
        amhw_hc32f460_adc_int_enable (p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);

        /* ���־λ */
        amhw_hc32f460_adc_int_flag_clr(p_hw_adc, AMHW_HC32F460_ADC_INT_EOCAF);

        /* ����ת������ */
        amhw_hc32f460_adc_convert_start(p_hw_adc);
    }
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
    am_hc32f460_adc_dev_t *p_dev = NULL;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev = (am_hc32f460_adc_dev_t *)p_drv;

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

    /* ���ò����� */
    __fn_adc_rate_set(p_dev, chan, 170000);

    __adc_int_work_startup(p_dev, chan);/* �жϹ���ģʽ�������� */

    return AM_OK;
}

/**
 * \brief ֹͣת��
 */
static int __fn_adc_stop (void *p_drv, int chan)
{
    am_hc32f460_adc_dev_t *p_dev    = (am_hc32f460_adc_dev_t *)p_drv;
    amhw_hc32f460_adc_t   *p_hw_adc = (amhw_hc32f460_adc_t *)
                                      (p_dev->p_devinfo->adc_reg_base);

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }
    /* ����ת��ֹͣ */
    amhw_hc32f460_adc_convert_stop(p_hw_adc);

    /* ADC�жϽ��� */
    amhw_hc32f460_adc_all_int_disable(p_hw_adc);

    if(p_dev->p_devinfo->p_ioinfo != NULL) {

        /* �ָ�ADCͨ��Ĭ��ӳ������ */
        amhw_hc32f460_adc_channel_mux_set (p_hw_adc,
                                           chan,
                                           p_dev->p_devinfo->p_ioinfo[chan].d_chan_sel);
    }

    return AM_OK;
}

/**
 * \brief ��ȡADC�Ĳ�����
 */
static int __fn_adc_rate_get (void          *p_drv,
                              int            chan,
                              uint32_t      *p_rate)
{
    am_hc32f460_adc_dev_t *p_dev;
    amhw_hc32f460_adc_t   *p_hw_adc;
    
    uint32_t i;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_hc32f460_adc_dev_t *)p_drv;
    p_hw_adc = (amhw_hc32f460_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    i = amhw_hc32f460_adc_sampling_period_get(p_hw_adc, chan);

    *p_rate = am_clk_rate_get(p_dev->p_devinfo->clk_num) / i;

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
    uint8_t    i = 0;

    uint32_t   rate_high = 0;
    uint32_t   rate_low  = 0;
    uint32_t   rate_err  = 0;

    struct adc_err  {
      uint32_t err;
      uint8_t  sample_time;
    };

    struct adc_err       adc_rate_err;
    am_hc32f460_adc_dev_t *p_dev;
    amhw_hc32f460_adc_t   *p_hw_adc;
    
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_hc32f460_adc_dev_t *)p_drv;
    p_hw_adc = (amhw_hc32f460_adc_t *)(p_dev->p_devinfo->adc_reg_base);
    
    adc_rate_err.err         = rate;
    adc_rate_err.sample_time = 0;

    clk       = am_clk_rate_get(p_dev->p_devinfo->clk_num);

    rate_high = clk / (5);
    rate_low  = clk / (255);

    if (rate < rate_low || rate > rate_high) {
        return -AM_EINVAL;
    }

    for(i = 5; i < 256; i++) {

        temp_rate = (clk / i);
        rate_err = temp_rate >= rate ? temp_rate - rate : rate - temp_rate;
        if (rate_err < adc_rate_err.err) {
              adc_rate_err.err         = rate_err;
              adc_rate_err.sample_time = i;
         }

         if (adc_rate_err.err == 0) {
              break;
         }
    }

    /* ����ת������ */
    amhw_hc32f460_adc_sampling_period_set(p_hw_adc,
                                          p_dev->chan,
                                          adc_rate_err.sample_time);

    return AM_OK;
}

/**
 * \brief ��ȡADCת������
 */
static uint32_t __fn_bits_get (void *p_drv, int chan)
{
    if (NULL == p_drv) {
        return 0;   /* ��Դ�Ѿ��ͷţ�����δ֪ */
    }

    return (uint32_t)__ADC_BITS_GET(p_drv);
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
am_adc_handle_t am_hc32f460_adc_init (am_hc32f460_adc_dev_t           *p_dev,
                                     const am_hc32f460_adc_devinfo_t  *p_devinfo)
{
    uint16_t bit = 0;

    amhw_hc32f460_adc_t   *p_hw_adc = NULL;

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

    /* ʱ��ʹ�� */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_hw_adc = (amhw_hc32f460_adc_t *)(p_dev->p_devinfo->adc_reg_base);


    /* ֹͣADCת�� */
    amhw_hc32f460_adc_convert_stop(p_hw_adc);

    /* ��ֹ���ݼĴ����Զ���� */
    amhw_hc32f460_adc_data_autoclr_disable(p_hw_adc);

    /* ת��ģʽΪ����A����ת�� */
    amhw_hc32f460_adc_mode_set(p_hw_adc, AMHW_HC32F460_ADC_SEQ_A_ONCE);

    /* �������ݶ��뷽ʽΪ�Ҷ��� */
    amhw_hc32f460_adc_data_align_set(p_hw_adc,
                                     AMHW_HC32F460_ADC_DATA_ALIGN_FORMAT_RIGHT);

    /* ��Чλ����ȡ */
    bit = __fn_bits_get(p_hw_adc, 0);

    /* �ֱ������� */
    switch (bit) {

    case 12:
        amhw_hc32f460_adc_resolution_set(p_hw_adc, AMHW_HC32F460_ADC_RESOLUTION_12BIT);
        break;
    case 10:
        amhw_hc32f460_adc_resolution_set(p_hw_adc, AMHW_HC32F460_ADC_RESOLUTION_10BIT);
        break;
    case 8:
        amhw_hc32f460_adc_resolution_set(p_hw_adc, AMHW_HC32F460_ADC_RESOLUTION_8BIT);
        break;
    }

    /* ���������ʱ����λ�� */
    p_dev->left_bit = 12 - bit;

    /* ע��ADC����ж� */
    __fn_adc_connect(p_dev);

    return (am_adc_handle_t)(&(p_dev->adc_serve));
}

/**
 * \brief ADCȥ��ʼ��
 */
void am_hc32f460_adc_deinit (am_adc_handle_t handle)
{
    am_hc32f460_adc_dev_t *p_dev    = (am_hc32f460_adc_dev_t *)handle;
    amhw_hc32f460_adc_t   *p_hw_adc = NULL;

    if (NULL == p_dev) {
        return ;
    }

    p_hw_adc = (amhw_hc32f460_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    /* ɾ�������ж� */
    if (p_dev->p_devinfo->dev_id == 1) {
        amhw_hc32f460_intc_int_vssel_bits_clr(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_ADC1_INT_VSSEL_BITS_MASK);
    } else if (p_dev->p_devinfo->dev_id == 2){
        amhw_hc32f460_intc_int_vssel_bits_clr(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_ADC2_INT_VSSEL_BITS_MASK);
    }

    /* ������жϺŵ����й����ж�λ��û�б�ʹ�ܣ���ɾ���ж����ӣ������ж� */
    if (amhw_hc32f460_intc_int_vssel_get(p_dev->p_devinfo->inum) == 0) {
        am_int_disconnect(p_dev->p_devinfo->inum,
                       IRQ142_Handler,
                       (void *)p_dev);
        am_int_disable(p_dev->p_devinfo->inum);
    }

    /* ADC�жϽ��� */
    amhw_hc32f460_adc_all_int_disable(p_hw_adc);

    p_dev->adc_serve.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */

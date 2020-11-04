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
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */

#include "am_zsn700_adc.h"
#include "ametal.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "zsn700_pin.h"
#include "hw/amhw_zsn700_rcc.h"
#include "hw/amhw_zsn700_adc.h"
#include "zsn700_periph_map.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

#define __ADC_HW_DECL(p_hw_adc, p_drv)   \
            amhw_zsn700_adc_t *p_hw_adc =   \
            ((am_zsn700_adc_dev_t *)p_drv)->p_devinfo->p_hw_adc

#define __ADC_VREF_GET(p_drv)  (((am_zsn700_adc_dev_t *)p_drv)->p_devinfo->vref)

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
void __zsn700_adc_irq_handle (void *p_arg)
{
    am_zsn700_adc_dev_t    *p_dev      = (am_zsn700_adc_dev_t *)p_arg;
    amhw_zsn700_adc_t      *p_hw_adc   =  NULL;

    /* ��ǰת�������������� */
    am_adc_buf_desc_t *p_desc  = &(p_dev->p_desc[p_dev->desc_index]);
    uint16_t          *p_buf16 = (uint16_t *)p_desc->p_buf;
    uint16_t           adc_dat = 0;

    if ( p_buf16 == NULL) {
        return ;
    }

    p_hw_adc =  (amhw_zsn700_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    /* �ж��Ƿ�ǰ��������Ч�� */
    if (p_dev->conv_cnt < p_desc->length) {

        /* �����ת�������жϱ�־ */
        amhw_zsn700_adc_flag_clr(p_hw_adc,
                                 AMHW_ZSN700_ADC_FLAG_CONVERT_SINGLE);

        /* ��ȡ���� */
        adc_dat = amhw_zsn700_adc_data_get (p_hw_adc);

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

                    __fn_adc_stop (p_dev, p_dev->chan);  /* �ر�ģ�� */

                    return ; /* ���� */
                }
            }
        } else {

            /* ����ת������ */
            amhw_zsn700_adc_single_convert_start(p_hw_adc);

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
    am_zsn700_adc_dev_t *p_dev = NULL;
    
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zsn700_adc_dev_t *)p_drv;

    /* �����жϺ��� */
    am_int_connect(p_dev->p_devinfo->inum,
                   __zsn700_adc_irq_handle,
                   (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return AM_OK;
}

/**
 * \brief ADC ʹ���ж�ģʽʱ��������
 */
static void __adc_int_work_startup (am_zsn700_adc_dev_t       *p_dev,
                                    amhw_zsn700_adc_chan_sel_t chan)
{
    amhw_zsn700_adc_t *p_hw_adc = (amhw_zsn700_adc_t *)
                                  (p_dev->p_devinfo->adc_reg_base);

    if(p_dev->p_devinfo->p_ioinfo != NULL) {

        /* ADC����*/
        amhw_zsn700_adc_disable(p_hw_adc);

        /* ����ADC����ͨ�������� */
        amhw_zsn700_adc_sgl_chan_sel(p_hw_adc,
                                     p_dev->p_devinfo->p_ioinfo[chan].chan_sel);

        /* ��ʼ������ */
        if(p_dev->p_devinfo->p_ioinfo[chan].chan_sel <
           AMHW_ZSN700_CHAN_DAC_OUT) {

            /* GPIO����ģʽ���� */
            am_gpio_pin_cfg(p_dev->p_devinfo->p_ioinfo[chan].gpio,
                            p_dev->p_devinfo->p_ioinfo[chan].func);
        } else {

            /* ADC�����źŷŴ���ʹ�� */
            amhw_zsn700_adc_inamplify_enable(p_hw_adc);

            if(p_dev->p_devinfo->p_ioinfo[chan].chan_sel ==
               AMHW_ZSN700_CHAN_INSIDE_TEMP_SENSOR) {

                amhw_zsn700_bgr_temp_sensor_enable(AM_TRUE);
            }
        }

        /* ���뷽ʽ���� */
        amhw_zsn700_adc_align_way_sel(p_hw_adc,
                                      AMHW_ZSN700_ADC_DATA_ALIGN_RIGHT);

        /* �ж�ʹ��*/
        amhw_zsn700_adc_int_enable(p_hw_adc);

        /* ���־λ */
        amhw_zsn700_adc_flag_clr(p_hw_adc, AMHW_ZSN700_ADC_FLAG_ALL);

        /* ADCʹ��*/
        amhw_zsn700_adc_enable(p_hw_adc);

        /* ����ת������ */
        amhw_zsn700_adc_single_convert_start(p_hw_adc);
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
    am_zsn700_adc_dev_t *p_dev = NULL;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev = (am_zsn700_adc_dev_t *)p_drv;

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

    __adc_int_work_startup(p_dev,
                           (amhw_zsn700_adc_chan_sel_t)chan);/* �жϹ���ģʽ�������� */

    return AM_OK;
}

/**
 * \brief ֹͣת��
 */
static int __fn_adc_stop (void *p_drv, int chan)
{
    am_zsn700_adc_dev_t *p_dev    = (am_zsn700_adc_dev_t *)p_drv;
    amhw_zsn700_adc_t   *p_hw_adc = (amhw_zsn700_adc_t *)
                                    (p_dev->p_devinfo->adc_reg_base);

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }
    /* ����ת��ֹͣ */
    amhw_zsn700_adc_single_convert_stop(p_hw_adc);

    /* ADC�жϽ��� */
    amhw_zsn700_adc_int_disable(p_hw_adc);

    /* ADC���� */
    amhw_zsn700_adc_disable(p_hw_adc);

    if(p_dev->p_devinfo->p_ioinfo != NULL) {

        /* ��ʼ������ */
        if(p_dev->p_devinfo->p_ioinfo[chan].chan_sel <
           AMHW_ZSN700_CHAN_DAC_OUT) {

            /* GPIO����ģʽ���� */
            am_gpio_pin_cfg(p_dev->p_devinfo->p_ioinfo[chan].gpio,
                            p_dev->p_devinfo->p_ioinfo[chan].dfunc);
        } else {

            /* ADC�����źŷŴ���ʹ�� */
            amhw_zsn700_adc_inamplify_disable(p_hw_adc);

            if(p_dev->p_devinfo->p_ioinfo[chan].chan_sel ==
               AMHW_ZSN700_CHAN_INSIDE_TEMP_SENSOR) {

                amhw_zsn700_bgr_temp_sensor_enable(AM_FALSE);
            }
        }
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
    am_zsn700_adc_dev_t *p_dev;
    amhw_zsn700_adc_t   *p_hw_adc;
    
    uint32_t sample;
    uint32_t adc_clkdiv = 1;
    uint32_t i;

    uint8_t  sample_time[4] = {4, 6, 8, 12};

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zsn700_adc_dev_t *)p_drv;
    p_hw_adc = (amhw_zsn700_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    i = amhw_zsn700_adc_sample_period_get(p_hw_adc);

    sample = sample_time[i];

    adc_clkdiv = (0x1ul << amhw_zsn700_adc_pclk_div_get(p_hw_adc));

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

    uint8_t  sample_time[4] = {4, 6, 8, 12};

    uint32_t   rate_high = 0;
    uint32_t   rate_low  = 0;
    uint32_t   rate_err  = 0;

    struct adc_err  {
      uint32_t err;
      uint8_t  sample_time;
      uint8_t  adc_div;
    };

    struct adc_err       adc_rate_err;
    am_zsn700_adc_dev_t *p_dev;
    amhw_zsn700_adc_t   *p_hw_adc;
    
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_zsn700_adc_dev_t *)p_drv;
    p_hw_adc = (amhw_zsn700_adc_t *)(p_dev->p_devinfo->adc_reg_base);
    
    adc_rate_err.err         = rate;
    adc_rate_err.sample_time = 0;
    adc_rate_err.adc_div     = 0;

    clk       = am_clk_rate_get(p_dev->p_devinfo->clk_num);

    rate_high = clk / (1 * 4);
    rate_low  = clk / (8 * 12);

    if (rate < rate_low || rate > rate_high) {
        return -AM_EINVAL;
    }

    for(i = 1; i < 5; i++) {
        if (rate >= (clk / ((0x1ul << i) * 12)) &&
            rate <= (clk / ((0x1ul << i) * 4))) {

            for(j = 0; j < 4; j++) {

                  temp_rate = (clk / ((1 << i) * sample_time[j]));
                  rate_err = temp_rate >= rate ? temp_rate - rate :
                                                 rate - temp_rate;
                  if (rate_err < adc_rate_err.err) {
                      adc_rate_err.err         = rate_err;
                      adc_rate_err.adc_div     = i;
                      adc_rate_err.sample_time = j;
                  }

                  if (adc_rate_err.err == 0) {
                      break;
                  }
              }
        }
    }

    /* ����ת������ */
    amhw_zsn700_adc_sample_period_sel(
        p_hw_adc, 
        (amhw_zsn700_adc_sample_period_t)adc_rate_err.sample_time);

    /* ����ADCʱ�ӷ�Ƶ */
    amhw_zsn700_adc_pclk_div_sel(p_hw_adc, 
                                 (amhw_zsn700_adc_pclk_div_t)adc_rate_err.adc_div);

    return AM_OK;
}

/**
 * \brief ��ȡADCת������
 */
static uint32_t __fn_bits_get (void *p_drv, int chan)
{
    /* ��֧��12λ�ֱ��� */
    return 12;
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
am_adc_handle_t am_zsn700_adc_init (am_zsn700_adc_dev_t           *p_dev,
                                    const am_zsn700_adc_devinfo_t *p_devinfo)
{
    uint16_t bit = 0;

    amhw_zsn700_adc_t   *p_hw_adc = NULL;

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

    p_hw_adc = (amhw_zsn700_adc_t *)(p_dev->p_devinfo->adc_reg_base);

    if(p_devinfo->vref_choice == AMHW_ZSN700_ADC_REFVOL_OUTSIDE_PB1) {

        am_gpio_pin_cfg(PIOB_1, PIOB_1_GPIO | PIOB_1_AIN);

        /* �ڲ��ο���ѹ���� */
        amhw_zsn700_adc_inrefvol_disable(p_hw_adc);

        /* ���òο���ѹԴ */
        amhw_zsn700_adc_refvol_sel(p_hw_adc, p_devinfo->vref_choice);

    } else {

        /* �ڲ��ο���ѹʹ�� */
        amhw_zsn700_adc_inrefvol_enable(p_hw_adc);

        /* ���òο���ѹԴ */
        amhw_zsn700_adc_refvol_sel(p_hw_adc, p_devinfo->vref_choice);
    }

    /* BGRģ��ʹ�� */
    amhw_zsn700_bgr_enable(AM_TRUE);

    /* ADCʹ��*/
    amhw_zsn700_adc_enable(p_hw_adc);

    /* ��ʱ 20us���ȴ� ADC�� BGRģ��������� */
    am_udelay(20);

    /* ADC���� */
    amhw_zsn700_adc_disable(p_hw_adc);

    /* ʹ�ܵ���ת��ģʽ */
    amhw_zsn700_adc_mode_sel(p_hw_adc, AMHW_ZSN700_ADC_MODE_SINGLE);

    amhw_zsn700_adc_align_way_sel(p_hw_adc, AMHW_ZSN700_ADC_DATA_ALIGN_RIGHT);

    /* ��Чλ����ȡ */
    bit = __fn_bits_get(p_dev, 0);

    /* ��������λ�� */
    p_dev->right_bit = 12 - bit;

    /* ���ò����� */
    __fn_adc_rate_set(p_dev, 0, 170000);

    if( p_dev->p_devinfo->temp_enable == 0) {
        amhw_zsn700_bgr_temp_sensor_enable(AM_FALSE);
    } else {
        amhw_zsn700_bgr_temp_sensor_enable(AM_TRUE);
    }

    /* ADCʹ��*/
    amhw_zsn700_adc_enable(p_hw_adc);

    /* ע��ADC����ж� */
    __fn_adc_connect(p_dev);

    return (am_adc_handle_t)(&(p_dev->adc_serve));
}

/**
 * \brief ADCȥ��ʼ��
 */
void am_zsn700_adc_deinit (am_adc_handle_t handle)
{
    am_zsn700_adc_dev_t *p_dev    = (am_zsn700_adc_dev_t *)handle;
    amhw_zsn700_adc_t   *p_hw_adc = NULL;

    if (NULL == p_dev) {
        return ;
    }

    p_hw_adc = (amhw_zsn700_adc_t *)(p_dev->p_devinfo->adc_reg_base);
    am_int_disable(p_dev->p_devinfo->inum);

    /* �ر��ж� */
    amhw_zsn700_adc_int_disable(p_hw_adc);

    /* ADC���� */
    amhw_zsn700_adc_disable(p_hw_adc);

    /* BGRģ����� */
    amhw_zsn700_bgr_enable(AM_FALSE);

    p_dev->adc_serve.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */

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
 * \brief DAC����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18
 * \endinternal
 */

#include "am_int.h"
#include "am_zsn700_dac.h"
#include "hw/amhw_zsn700_dac.h"
#include "zsn700_periph_map.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

#define __ZLG_DAC_BITS_GET(p_drv)             \
        (((am_zsn700_dac_dev_t *)p_drv)->p_devinfo->bits)

#define __ZLG_DAC_VREF_GET(p_drv)             \
        (((am_zsn700_dac_dev_t *)p_drv)->p_devinfo->vref)

/*******************************************************************************
* ��������
*******************************************************************************/
static uint32_t __zsn700_dac_get_bits (void *p_drv);

static uint32_t __zsn700_dac_get_vref (void *p_drv);

static int __zsn700_dac_val_set (void *p_drv, int chan, uint32_t value);

static int __zsn700_dac_enable (void *p_drv, int chan );

static int __zsn700_dac_disable (void *p_drv, int chan );

/**
 * \brief DAC������
 */
static const struct am_dac_drv_funcs __g_dac_drvfuncs = {
       __zsn700_dac_get_bits,
       __zsn700_dac_get_vref,
       __zsn700_dac_val_set,
       __zsn700_dac_enable,
       __zsn700_dac_disable
};

/******************************************************************************/

/**
 * \brief ��ȡDACת�����ȡ�
 */
static uint32_t __zsn700_dac_get_bits (void *p_drv)
{
    return (uint32_t)__ZLG_DAC_BITS_GET(p_drv);
}

/**
 * \brief ��ȡDAC�ο���ѹ��
 */
static uint32_t __zsn700_dac_get_vref (void *p_drv)
{
    return (uint32_t)__ZLG_DAC_VREF_GET(p_drv);
}

/**
 * \brief ����ͨ����DACת��ֵ��
 */
static int __zsn700_dac_val_set (void *p_drv, int chan, uint32_t value)
{
    am_zsn700_dac_dev_t *p_dev    = (am_zsn700_dac_dev_t *)p_drv;
    amhw_zsn700_dac_t   *p_hw_dac =
                         (amhw_zsn700_dac_t *)(p_dev->p_devinfo->dac_reg_base);

    if (p_dev == NULL ) {
        return -AM_EINVAL;
    }

    if (chan != 0) {
        return -AM_ENXIO;       /* ��Ч��ͨ��ֵ */
    }

    p_dev->chan = chan;

    if (p_dev->p_devinfo->bits == 8) {

        amhw_zsn700_dac_chan_8bit_right_aligned_data(p_hw_dac, value);
    } else {

        if (p_dev->p_devinfo->align_way == AM_ZSN700_DAC_ALIGN_WAY_12_RIGHT){

            amhw_zsn700_dac_chan_12bit_right_aligned_data(p_hw_dac, value);
        }else{

            amhw_zsn700_dac_chan_12bit_left_aligned_data(p_hw_dac, value);
        }
    }

    return AM_OK;
}

/**
 * \brief ����DACת��
 */
static int __zsn700_dac_enable (void *p_drv, int chan)
{

    am_zsn700_dac_dev_t *p_dev    = (am_zsn700_dac_dev_t *)p_drv;
    amhw_zsn700_dac_t   *p_hw_dac =
                          (amhw_zsn700_dac_t *)(p_dev->p_devinfo->dac_reg_base);

    if (p_dev == NULL ) {
        return -AM_EINVAL;
    }

    if (chan != 0) {
        return -AM_ENXIO;       /* ��Ч��ͨ��ֵ */
    }

    p_dev->chan = chan;

    amhw_zsn700_dac_chan_enable(p_hw_dac);

    return AM_OK;
}

/**
 * \brief ��ֹDACת��
 */
static int __zsn700_dac_disable (void *p_drv, int chan )
{

    am_zsn700_dac_dev_t *p_dev    = (am_zsn700_dac_dev_t *)p_drv;
    amhw_zsn700_dac_t   *p_hw_dac =
                          (amhw_zsn700_dac_t *)(p_dev->p_devinfo->dac_reg_base);

    if (p_dev == NULL ) {
        return -AM_EINVAL;
    }

    if (chan != 0) {
        return -AM_ENXIO;       /* ��Ч��ͨ��ֵ */
    }

    p_dev->chan = chan;

    amhw_zsn700_dac_chan_disable(p_hw_dac);

    return AM_OK;
}

/**
 * \brief DAC��ʼ��
 */
am_dac_handle_t am_zsn700_dac_init (am_zsn700_dac_dev_t           *p_dev,
                                    const am_zsn700_dac_devinfo_t *p_devinfo)
{
    amhw_zsn700_dac_t *p_hw_dac;

    if ((p_devinfo == NULL) || (p_dev == NULL)) {
        return NULL;
    }

    p_dev->p_devinfo         = p_devinfo;
    p_dev->dac_serve.p_funcs = &__g_dac_drvfuncs;
    p_dev->dac_serve.p_drv   = p_dev;

    p_hw_dac = (amhw_zsn700_dac_t *)(p_dev->p_devinfo->dac_reg_base);

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* ʹ��BGR */
    amhw_zsn700_bgr_enable(AM_TRUE);

    /* ʹ��dacͨ�� */
    amhw_zsn700_dac_chan_enable(p_hw_dac);

    /* �ο���ѹѡ�� */
    amhw_zsn700_dac_chan_sref_sel(p_hw_dac, p_dev->p_devinfo->vref_rsc);

    /* ʧ�����������*/
    amhw_zsn700_dac_chan_output_buf_disable(p_hw_dac);

    return (am_dac_handle_t)(&(p_dev->dac_serve));
}

/**
 * \brief DACȥ��ʼ��
 */
void am_zsn700_dac_deinit (am_dac_handle_t handle)
{
    am_zsn700_dac_dev_t *p_dev  = (am_zsn700_dac_dev_t *)handle;
    amhw_zsn700_dac_t *p_hw_dac =
                          (amhw_zsn700_dac_t *)(p_dev->p_devinfo->dac_reg_base);

    p_dev->dac_serve.p_funcs = NULL;
    p_dev->dac_serve.p_drv   = NULL;

    amhw_zsn700_dac_chan_disable(p_hw_dac);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/**
 * \brief DAC ������ʽѡ��
 */
int am_zsn700_dac_tri_way_sel (am_dac_handle_t handle, uint32_t tri_way)
{
    am_zsn700_dac_dev_t *p_dev  = (am_zsn700_dac_dev_t *)handle;
    amhw_zsn700_dac_t *p_hw_dac =
                          (amhw_zsn700_dac_t *)(p_dev->p_devinfo->dac_reg_base);

    if (handle == NULL){

        return AM_ERROR;
    }

    /* ����dacͨ��*/
    amhw_zsn700_dac_chan_disable(p_hw_dac);

    switch (tri_way){

        case AM_ZSN700_DAC_CHAN_TIM0_TRGO :
            amhw_zsn700_dac_chan_trg_sel(p_hw_dac,
                                         AMHW_ZSN700_DAC_CHAN_TIM0_TRGO);
            break;
        case AM_ZSN700_DAC_CHAN_TIM1_TRGO :
            amhw_zsn700_dac_chan_trg_sel(p_hw_dac,
                                         AMHW_ZSN700_DAC_CHAN_TIM1_TRGO);
            break;
        case AM_ZSN700_DAC_CHAN_TIM2_TRGO :
            amhw_zsn700_dac_chan_trg_sel(p_hw_dac,
                                         AMHW_ZSN700_DAC_CHAN_TIM2_TRGO);
            break;
        case AM_ZSN700_DAC_CHAN_TIM3_TRGO :
            amhw_zsn700_dac_chan_trg_sel(p_hw_dac,
                                         AMHW_ZSN700_DAC_CHAN_TIM3_TRGO);
            break;
        case AM_ZSN700_DAC_CHAN_TIM4_TRGO :
            amhw_zsn700_dac_chan_trg_sel(p_hw_dac,
                                         AMHW_ZSN700_DAC_CHAN_TIM4_TRGO);
            break;
        case AM_ZSN700_DAC_CHAN_TIM5_TRGO :
            amhw_zsn700_dac_chan_trg_sel(p_hw_dac,
                                         AMHW_ZSN700_DAC_CHAN_TIM5_TRGO);
            break;
        case AM_ZSN700_DAC_CHAN_SOFTWARE_TRG :
            amhw_zsn700_dac_chan_trg_sel(p_hw_dac,
                                         AMHW_ZSN700_DAC_CHAN_SOFTWARE_TRG);
            break;
        case AM_ZSN700_DAC_CHAN_EXTER :
            amhw_zsn700_dac_chan_trg_sel(p_hw_dac,
                                         AMHW_ZSN700_DAC_CHAN_EXTER);
            break;
        default:
            return AM_ERROR;
    }

    /* ����ʹ�� */
    amhw_zsn700_dac_chan_trg_enable(p_hw_dac);

    return AM_OK;
}


/**
 * \brief DAC �������
 */
void am_zsn700_dac_soft_tri (am_dac_handle_t handle)
{
    am_zsn700_dac_dev_t *p_dev  = (am_zsn700_dac_dev_t *)handle;
    amhw_zsn700_dac_t *p_hw_dac =
                          (amhw_zsn700_dac_t *)(p_dev->p_devinfo->dac_reg_base);

    amhw_zsn700_dac_chan_software_trg_enable(p_hw_dac);
}

/**
 * \brief DAC ת�����ݻ�ȡ
 */
void am_zsn700_dac_convt_data_get (am_dac_handle_t handle, uint16_t *p_out_data)
{
    am_zsn700_dac_dev_t *p_dev  = (am_zsn700_dac_dev_t *)handle;
    amhw_zsn700_dac_t *p_hw_dac =
                          (amhw_zsn700_dac_t *)(p_dev->p_devinfo->dac_reg_base);

    *p_out_data = amhw_zsn700_dac_chan_output_data(p_hw_dac);
}

/* end of file */

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
 * \brief ZLG DAC �û������ļ�
 * \sa am_hwconf_zlg217_dac.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-24
 * \endinternal
 */

#include "am_zlg118.h"
#include "am_zlg118_dac.h"
#include "am_gpio.h"
#include "zlg118_pin.h"
#include "am_clk.h"
#include "hw/amhw_zlg118_dac.h"

/**
 * \addtogroup am_if_src_hwconf_zlg118_dac
 * \copydoc am_hwconf_zlg118_dac.c
 * @{
 */

/**
 * \brief DAC0 ƽ̨��ʼ��
 */
void __zlg118_plfm_dac0_init (void)
{

    /* ����PIOA_4ΪDAC1_OUT���� */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AOUT);

    /* ����DACʱ�� */
    am_clk_enable(CLK_DAC);
}

/**
 * \brief DAC0 ƽ̨ȥ��ʼ��
 */
void __zlg118_plfm_dac0_deinit (void)
{
    /* �ر�DACʱ�� */
    am_clk_disable(CLK_DAC);
}

/** \brief DAC0 �豸��Ϣ */
static const am_zlg118_dac_devinfo_t __g_dac0_devinfo =
{
    ZLG118_DAC_BASE,                      /**< \brief ָ��DAC�Ĵ������ָ�� */

    12,                                   /**< \brief DACת������ */

    AMHW_ZLG118_DAC_CHAN_MASK_EXTER_REF,  /**< \brief DAC�ο���ѹԴ */

    3300,                                 /**< \brief DAC�ο���ѹ,��λ��mv*/

    AM_ZLG118_DAC_ALIGN_WAY_12_RIGHT,     /**< \brief DAC���ݶ��뷽ʽ */

    __zlg118_plfm_dac0_init,              /**< \brief DACƽ̨��ʼ������ */

    __zlg118_plfm_dac0_deinit,            /**< \brief DACƽ̨���ʼ������  */
};

/** \brief DAC0�豸ʵ�� */
static am_zlg118_dac_dev_t __g_dac0_dev;

/** \brief DAC0 ʵ����ʼ�������DAC��׼������ */
am_dac_handle_t am_zlg118_dac_inst_init (void)
{
    return am_zlg118_dac_init(&__g_dac0_dev, &__g_dac0_devinfo);
}

/** \brief DAC0 ʵ�����ʼ�� */
void am_zlg118_dac_inst_deinit (am_dac_handle_t handle)
{
    am_zlg118_dac_deinit(handle);
}

/**
 * @}
 */

/* end of file */

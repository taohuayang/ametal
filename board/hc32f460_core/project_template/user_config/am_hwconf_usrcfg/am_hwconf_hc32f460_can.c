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
 * \brief HC32F460 CAN �û������ļ�
 * \sa am_hwconf_hc32f460_can.c
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

#include "hc32f460_periph_map.h"
#include "am_hc32f460.h"
#include "hc32f460_inum.h"
#include "am_gpio.h"
#include "am_hc32f460_can.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_adc
 * \copydoc am_hwconf_hc32f460_adc.c
 * @{
 */

#define MAX     10

/** \brief CANƽ̨��ʼ�� */
static void __hc32f460_plfm_can_init (void)
{
    am_gpio_pin_cfg(PIOB_6, GPIO_AFIO(AMHW_HC32F460_AFIO_CAN1_RX));
    am_gpio_pin_cfg(PIOB_7, GPIO_AFIO(AMHW_HC32F460_AFIO_CAN1_TX));
    am_gpio_pin_cfg(PIOD_15, AM_GPIO_OUTPUT_INIT_LOW);
    
    am_clk_enable(CLK_CAN);
}

/** \brief ���CANƽ̨��ʼ�� */
static void __hc32f460_plfm_can_deinit (void)
{
    am_clk_disable (CLK_CAN);
}

static am_hc32f460_can_intcb_info_t    __g_can_intcb_info[MAX];

/** \brief �豸��Ϣ */
static const am_hc32f460_can_devinfo_t __g_can_devinfo = {

    HC32F460_CAN_BASE,                 /**< \brief CAN */
    INUM_CAN,                          /**< \brief CAN���жϱ�� */
    AMHW_HC32F460_CAN_PELI_CAN,        /**< \brief CANģʽ���� */
    __g_can_intcb_info,                /**< \brief �ص���Ϣ */
    MAX,                               /**< \brief �ص���Ϣ�ڴ��С*/
    __hc32f460_plfm_can_init,          /**< \brief CAN1��ƽ̨��ʼ�� */
    __hc32f460_plfm_can_deinit,        /**< \brief CAN1��ƽ̨ȥ��ʼ�� */

};

/** \brief �豸ʵ�� */
am_hc32f460_can_dev_t  __g_can_dev;

/** \brief CANʵ����ʼ�������CAN��׼������ */
am_can_handle_t am_hc32f460_can_inst_init (void)
{
    return am_hc32f460_can_init(&__g_can_dev, &__g_can_devinfo);
}

/** \brief CANʵ�����ʼ�� */
void am_hc32f460_can_inst_deinit (am_can_handle_t handle)
{
    am_hc32f460_can_deinit(handle);
}

/**
 * @}
 */

/* end of file */

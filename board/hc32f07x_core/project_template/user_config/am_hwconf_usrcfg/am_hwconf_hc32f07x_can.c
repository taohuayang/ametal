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
 * \brief ZLG237 CAN �û������ļ�
 * \sa am_hwconf_zlg237_can.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-08-12  zc, first implementation
 * \endinternal
 */

#include "hc32f07x_periph_map.h"
#include "am_hc32f07x.h"
#include "hc32f07x_inum.h"
#include "am_gpio.h"
#include "am_hc32f07x_can.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg237_can
 * \copydoc am_hwconf_zlg237_can.c
 * @{
 */

#define MAX     10

/** \brief CANƽ̨��ʼ�� */
static void __hc32f07x_plfm_can_init (void)
{
    am_clk_enable(CLK_CAN);
 
    am_gpio_pin_cfg(PIOD_0, PIOD_0_CAN_RX | PIOD_0_INPUT_FLOAT );
    am_gpio_pin_cfg(PIOD_1, PIOD_1_CAN_TX | PIOD_1_OUT_PP);
    am_gpio_pin_cfg(PIOD_5,  PIOD_5_OUT_PP);
    am_gpio_set(PIOD_5, 0);
}

/** \brief ���CANƽ̨��ʼ�� */
static void __hc32f07x_plfm_can_deinit (void)
{
    am_clk_disable (CLK_CAN);
}

static am_hc32f07x_can_intcb_info_t    __g_can_intcb_info[MAX];

am_hc32f07x_can_init_info_t __g_can_initfo = {

    /** \brief 0 ��ͨģʽ   1 �洢����*/
    AMHW_HC32F07X_CAN_RXBUF_NORMAL,

    /** \brief ʱ�䴥��ͨ��ģʽ  0 �Ǵ���  1 ���� */
	  0,
	
    AMHW_HC32F07X_CAN_RXBUF_NOTSTORED,

    AMHW_HC32F07X_CAN_STB_MODE_FIFO,

    10,

    15,
};

/** \brief �豸��Ϣ */
static const am_hc32f07x_can_devinfo_t __g_can_devinfo = {

    HC32F07X_CAN_BASE,                 /**< \brief CAN */
    INUM_CAN,              /**< \brief CAN���жϱ��  �˴������޸�*/
    AMHW_HC32F07X_CAN_PTB,
    __g_can_intcb_info,              /**< \brief �ص���Ϣ */
    MAX,                             /**< \brief �ص���Ϣ�ڴ��С*/
    __hc32f07x_plfm_can_init,          /**< \brief CAN��ƽ̨��ʼ�� */
    __hc32f07x_plfm_can_deinit,        /**< \brief CAN��ƽ̨ȥ��ʼ�� */
//    &__g_can_filter,
    &__g_can_initfo

};

/**< \brief �豸ʵ�� */
static am_hc32f07x_can_dev_t  __g_can_dev;

/** \brief CANʵ����ʼ�������CAN��׼������ */
am_can_handle_t am_hc32f07x_can_inst_init (void)
{
    return am_hc32f07x_can_init(&__g_can_dev, &__g_can_devinfo);
}

/** \brief CANʵ�����ʼ�� */
void am_hc32f07x_can_inst_deinit (am_can_handle_t handle)
{
    am_hc32f07x_can_deinit(handle);
}

/**
 * @}
 */

/* end of file */

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
 * \brief STM32F103RBT6 CAN �û������ļ�
 * \sa am_hwconf_stm32f103rbt6_can.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-08-12  zc, first implementation
 * \endinternal
 */

#include "stm32f103rbt6_periph_map.h"
#include "am_stm32f103rbt6.h"
#include "stm32f103rbt6_inum.h"
#include "am_gpio.h"
#include "am_stm32f103rbt6_can.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_stm32f103rbt6_can
 * \copydoc am_hwconf_stm32f103rbt6_can.c
 * @{
 */

#define MAX     10

/** \brief CANƽ̨��ʼ�� */
static void __stm32f103rbt6_plfm_can_init (void)
{
    am_clk_enable(CLK_CAN);

    am_gpio_pin_cfg(PIOA_11, PIOA_11_CAN_RX_REMAP0 | PIOA_11_INPUT_PU | PIOA_11_SPEED_50MHz);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_CAN_TX_REMAP0 | PIOA_12_AF_PP |PIOA_12_SPEED_50MHz );


}

/** \brief ���CANƽ̨��ʼ�� */
static void __stm32f103rbt6_plfm_can_deinit (void)
{
    am_clk_disable (CLK_CAN);
}

static am_stm32f103rbt6_can_intcb_info_t    __g_can_intcb_info[MAX];

amhw_stm32f103rbt6_can_filter_t __g_can_filter = {

    /* ����FIFO */
    AMHW_STM32F103RBT6_CAN_FILTER_FIFO0,

    /* �˲���ģʽ */
    AMHW_STM32F103RBT6_CAN_FILTER_MODE_IDMASK,

    /* �˲���λ�� */
    AMHW_STM32F103RBT6_CAN_FILTER_SCALE_32BIT,

    /* �˲�������״̬ */
    1
};

am_stm32f103rbt6_can_init_info_t __g_can_initfo = {

    /** \brief 0 ��ͨģʽ   1 �ػ�ģʽ */
    AMHW_STM32F103RBT6_CAN_MODE_NORMAL,

    /** \brief ʱ�䴥��ͨ��ģʽ  0 �Ǵ���  1 ���� */
    0,

    /** \brief ����Զ����߹���
     *   0 �����MCR��INRQλ�����á�1�� �� �塮0�� һ��Ӳ����⵽128��11λ��������λ���˳�����ģʽ
     *   1 һ��Ӳ����⵽128��11λ��������λ���˳�����ģʽ
     */
    1,

    /** \brief �Զ�����ģʽ
     *   0 ˯��ģʽͨ�����CAN_MCR��SLEEPλ  ���������
     *   1 ˯��ģʽͨ�����CAN���ģ���Ӳ���Զ����ѡ����ѵ�ͬʱ��Ӳ���Զ���CAN_MSR ��SLEEP��SLAK�塮0��
     */
    1,

    /** \brief ��ֹ�����Զ��ش�
     *   0 Ӳ���ڷ��ͱ���ʧ��ʱ��һֱ�ش������ͳɹ�
     *   1 CAN����ֻ����һ��
     */
    0,

    /** \brief ����FIFO����ģʽ
     *   0 �ڽ������ʱFIFOδ��������������FIFO�ı���δ����������һ���յ��ı��ĻḲ��ԭ�еı���
     *   1 �ڽ������ʱFIFO��������������FIFO�ı���δ����������һ���յ��ı��Ļᱻ����
     */
    0,

    /** \brief ����FIFO���ȼ�
     *   0 ���ȼ��ɱ��ĵı�ʶ��������
     *   1 ���ȼ��ɷ��������˳��������
     */
    0
};

/** \brief �豸��Ϣ */
static const am_stm32f103rbt6_can_devinfo_t __g_can_devinfo = {

    STM32F103RBT6_CAN_BASE,                 /**< \brief CAN */
    INUM_USB_HP_CAN_TX,              /**< \brief CAN���жϱ��  �˴������޸�*/
    __g_can_intcb_info,              /**< \brief �ص���Ϣ */
    MAX,                             /**< \brief �ص���Ϣ�ڴ��С*/
    __stm32f103rbt6_plfm_can_init,          /**< \brief CAN1��ƽ̨��ʼ�� */
    __stm32f103rbt6_plfm_can_deinit,        /**< \brief CAN1��ƽ̨ȥ��ʼ�� */
    &__g_can_filter,
    &__g_can_initfo

};

/**< \brief �豸ʵ�� */
static am_stm32f103rbt6_can_dev_t  __g_can_dev;

/** \brief CANʵ����ʼ�������CAN��׼������ */
am_can_handle_t am_stm32f103rbt6_can_inst_init (void)
{
    return am_stm32f103rbt6_can_init(&__g_can_dev, &__g_can_devinfo);
}

/** \brief CANʵ�����ʼ�� */
void am_stm32f103rbt6_can_inst_deinit (am_can_handle_t handle)
{
    am_stm32f103rbt6_can_deinit(handle);
}

/**
 * @}
 */

/* end of file */

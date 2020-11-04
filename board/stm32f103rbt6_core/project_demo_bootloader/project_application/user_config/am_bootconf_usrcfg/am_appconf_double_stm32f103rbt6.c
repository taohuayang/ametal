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
 * \brief STM32F103RBT6 ˫��Ӧ�ó��� �û������ļ�
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */

#include "am_appconf_double_stm32f103rbt6.h"
#include "am_stm32f103rbt6.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "am_stm32f103rbt6_boot_flash.h"
#include "am_arm_boot.h"
#include "am_boot_flash.h"
#include "am_boot_mem_flash.h"
#include "am_stm32f103rbt6_flash.h"
#include "stm32f103rbt6_regbase.h"
#include "am_boot_firmware_flash.h"
#include "am_int.h"
#include "am_stm32f103rbt6_clk.h"
#include "amhw_stm32f103rbt6_rcc.h"
#include "am_arm_nvic.h"
#include "am_boot_msg_flag.h"

static am_boot_flash_handle_t flash_handle;
static am_boot_mem_handle_t   mem_handle;
/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 * < \brief bootloader flash �豸��Ϣ
 */
static am_stm32f103rbt6_boot_flash_devinfo_t __g_flash_devinfo = {

    {
        /** \brief flash����ʼ��ַ */
        0x08000000,
        /** \brief flash���ܵĴ�С */
        128 * 1024,
        /** \brief flash������С */
        1024 * 4,
        /** \brief flashҳ��С */
        1024,
    },

    /** \brief flash�Ĵ����Ļ���ַ */
    STM32F103RBT6_FLASH_BASE,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_stm32f103rbt6_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_stm32f103rbt6_boot_flash_inst_init(void)
{
    return am_stm32f103rbt6_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}

/*******************************************************************************
 * ��flag��ʽ����Ϣ����
 ******************************************************************************/

static am_boot_msg_flag_devinfo_t __g_boot_msg_flag_info = {
    /** \brief ��������ʼ��ַ */
    0x08013C00,
    /** \brief Ӧ������С */
    49 * 1024,
    /** \brief ��־��ŵ�ַ */
    0x08007400,
    /** \brief ��־ռ�õ�ʵ�ʴ�С��һ��Ϊ�ڴ���С��д�뵥Ԫ�����ʹ��flash�ڴ棬��Ϊ��С�Ĳ�����Ԫ*/
    4,
    /** \brief �̼���������Ҫ�ӹ̼��ı�������������Ӧ�ó����ִ����(�����־��Ӧ�ó�����������������ͬһ���ڴ��豸�У����Բ���ʵ�ָú���)*/
    NULL,
};

am_boot_msg_handle_t am_stm32f103rbt6_boot_msg_flag_inst_init()
{
    mem_handle = am_boot_mem_flash_init(flash_handle);
    return am_boot_msg_flag_init(&__g_boot_msg_flag_info,
                                  mem_handle);
}

/*******************************************************************************
 * �̼���flash�ķ�ʽ�洢����
 ******************************************************************************/
static am_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief �̼����ڴ��д�ŵ���ʼ��ַ */
    0x08013C00,
    /**< \brief �̼������ܴ�С */
    49 * 1024,
    /** \brief ������Ź̼���������С ,ֵΪ�ڴ�д����С��С�������� */
    4,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

static am_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_stm32f103rbt6_boot_firmware_flash_inst_init()
{
    flash_handle = am_stm32f103rbt6_boot_flash_inst_init();
    return am_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                        &__g_firmware_flash_devinfo,
                                         flash_handle);
}


/*******************************************************************************
 * ��׼bootloader�û�����
 ******************************************************************************/

/* ������bootloader���õ�����Դ��Ҫ�ӳ�ʼ�����ͷţ��������綨ʱ�������ڵ� */
static void __stm32f103rbt6_boot_plfm_deinit()
{
    volatile uint32_t i = 1000000;
    /* ���ڽ��ʼ�� �����ʼ��ǰ��ҪС�ε���ʱ����֤�Ĵ��������Ѿ����*/
    while(i--){

    }

    amhw_stm32f103rbt6_usart_disable((amhw_stm32f103rbt6_usart_t *)STM32F103RBT6_USART1_BASE);
    am_int_disable(INUM_USART1);

    am_gpio_pin_cfg(PIOA_9, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_10,AM_GPIO_INPUT);

    am_clk_disable(CLK_USART1);

    /* ��ʱ�����ʼ��  */
    amhw_stm32f103rbt6_tim_int_disable(STM32F103RBT6_TIM4, AMHW_STM32F103RBT6_TIM_UIE);
    amhw_stm32f103rbt6_tim_disable(STM32F103RBT6_TIM4);
    am_int_disable(INUM_TIM4);
    am_stm32f103rbt6_clk_reset(CLK_TIM4);
    am_clk_disable(CLK_TIM4);

    STM32F103RBT6_RCC->ahbenr = 0;
    STM32F103RBT6_RCC->apb1enr = 0;
    STM32F103RBT6_RCC->apb2enr = 0;

    amhw_stm32f103rbt6_rcc_sys_clk_set(AMHW_STM32F103RBT6_SYSCLK_HSE);

    am_arm_nvic_deinit();
    __disable_irq();
}

/**
 * < \brief bootloader��׼�豸��Ϣ
 */
static am_arm_boot_devinfo_t __g_stm32f103rbt6_boot_devinfo = {
    /**< \brief Ӧ�ô�������ʼ��ַ*/
    0x08007800,
    /** \brief ram��ʼ��ַ */
    0x20000000,
    /** \brief ram��С */
    20 * 1024,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    __stm32f103rbt6_boot_plfm_deinit,
};

int am_stm32f103rbt6_boot_inst_init()
{
    return am_arm_boot_init(&__g_stm32f103rbt6_boot_devinfo);
}

/** @} */

/* end of file */

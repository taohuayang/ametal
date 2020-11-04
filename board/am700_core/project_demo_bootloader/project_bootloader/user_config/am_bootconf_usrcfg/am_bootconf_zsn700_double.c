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
 * \brief ZSN700 bootloader ˫���û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup am_if_src_bootconf_zsn700_double
 * \copydoc am_bootconf_zsn700_double.c
 * @{
 */
#include <am_bootconf_usrcfg/am_bootconf_zsn700.h>
#include "am_zsn700.h"
#include "am_zsn700_inst_init.h"
#include "am_zsn700_boot_flash.h"
#include "am_arm_boot.h"
#include "am_boot_flash.h"
#include "am_boot_mem_flash.h"
#include "am_zsn700_flash.h"
#include "zsn700_regbase.h"
#include "am_boot_firmware_flash.h"
#include "am_int.h"
#include "am_zsn700_clk.h"
#include "hw/amhw_zsn700_rcc.h"
#include "am_arm_nvic.h"
#include "am_boot_msg_flag.h"
#include "hw/amhw_zsn700_flash.h"
#include "hw/amhw_arm_systick.h"

static am_boot_flash_handle_t flash_handle;
static am_boot_mem_handle_t   mem_handle;
/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 *  \brief bootloader flash �豸��Ϣ
 */
static am_zsn700_boot_flash_devinfo_t __g_flash_devinfo = {

    {
        /** \brief flash����ʼ��ַ */
        0x00000000,
        /** \brief flash���ܵĴ�С */
        256 * 1024,
        /** \brief flash������С */
        512,
        /** \brief flashҳ��С */
        512,
    },
    /** \brief flash�Ĵ����Ļ���ַ */
    ZSN700_FLASH_BASE,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_zsn700_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
static am_boot_flash_handle_t am_zsn700_boot_double_flash_inst_init(void)
{
    return am_zsn700_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}

/*******************************************************************************
 * �̼���flash�ķ�ʽ�洢����
 ******************************************************************************/
static am_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief �̼����ڴ��д�ŵ���ʼ��ַ */
    0x00006800,
    /**< \brief �̼���������ܴ�С */
    115 * 1024,
    /** \brief ������Ź̼���������С , ֵΪ�ڴ�д����С��С�������� */
    4,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

static am_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_zsn700_boot_double_firmware_flash_inst_init()
{
    flash_handle = am_zsn700_boot_double_flash_inst_init();
    return am_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                        &__g_firmware_flash_devinfo,
                                         flash_handle);
}

/*******************************************************************************
 * ��flag��ʽ����Ϣ����
 ******************************************************************************/
static am_boot_msg_flag_devinfo_t __g_boot_msg_flag_info = {
    /** \brief ��������ʼ��ַ */
    0x00023400,
    /** \brief Ӧ������С */
    115 * 1024,
    /** \brief ��־��ŵ�ַ */
    0x00006600,
    /** \brief ��־ռ�õ�ʵ�ʴ�С��һ��Ϊ�ڴ���С��д�뵥Ԫ�����ʹ��flash�ڴ棬��Ϊ��С�Ĳ�����Ԫ*/
    4,
    /** \brief �̼���������Ҫ�ӹ̼��ı�������������Ӧ�ó����ִ����(�����־��Ӧ�ó�����������������ͬһ���ڴ��豸�У����Բ���ʵ�ָú���)*/
    NULL,
};

am_boot_msg_handle_t am_zsn700_boot_msg_flag_inst_init()
{
    mem_handle = am_boot_mem_flash_init(flash_handle);

    return am_boot_msg_flag_init(&__g_boot_msg_flag_info,
                                  mem_handle);
}

/*******************************************************************************
 * ��׼bootloader�û�����
 ******************************************************************************/

/* ������bootloader���õ�����Դ��Ҫ���ʼ�������ܣ��������綨ʱ�������ڵ� */
static void __zsn700_boot_plfm_deinit()
{
    volatile uint32_t i = 2000000;
    /* ���ڽ��ʼ�� �����ʼ��ǰ��ҪС�ε���ʱ����֤�Ĵ��������Ѿ����*/
    while(i--){

    }

    am_zsn700_clk_inst_deinit();

    am_int_disable(INUM_UART0_2);
    am_clk_disable(CLK_UART0);

    am_zsn700_clk_reset(CLK_UART0);
    am_zsn700_clk_reset(CLK_GPIO);

    am_int_disable(INUM_TIM2);
    am_clk_disable(CLK_TIM012);
    am_zsn700_clk_reset(CLK_TIM012);

    ZSN700_RCCCTRL->peri_clken[0] = 0x80800000;
    ZSN700_RCCCTRL->peri_clken[1] = 0;

    am_arm_nvic_deinit();

    __disable_irq();
}

/**
 * < \brief bootloader��׼�豸��Ϣ
 */
static am_arm_boot_devinfo_t __g_zsn700_boot_double_devinfo = {
    /**< \brief Ӧ�ô�������ʼ��ַ*/
    0x00006800,
    /** \brief ram��ʼ��ַ */
    0x20000000,
    /** \brief ram��С */
    32 * 1024,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    __zsn700_boot_plfm_deinit,
};

int am_zsn700_boot_double_inst_init()
{
    return am_arm_boot_init(&__g_zsn700_boot_double_devinfo);
}

/** @} */

/* end of file */

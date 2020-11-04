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
 * \brief HC32 kboot KinetisFlashTool �û������ļ�
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup am_if_src_bootconf_hc32_kft
 * \copydoc am_bootconf_hc32_kft.c
 * @{
 */

#include <am_bootconf_usrcfg/am_bootconf_zlg116.h>
#include "am_zlg116.h"
#include "am_zlg116_inst_init.h"
#include "am_zlg_boot_flash.h"
#include "am_arm_boot.h"
#include "am_boot_flash.h"
#include "am_boot_mem_flash.h"
#include "am_zlg_flash.h"
#include "zlg116_regbase.h"
#include "am_boot_firmware_flash.h"
#include "am_int.h"
#include "am_zlg116_clk.h"
#include "hw/amhw_zlg116_rcc.h"
#include "am_arm_nvic.h"


/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 * < \brief bootloader flash �豸��Ϣ
 */
static am_zlg_boot_flash_devinfo_t __g_flash_devinfo = {

    {
        /** \brief flash����ʼ��ַ */
        0x08000000,
        /** \brief flash���ܵĴ�С */
        64 * 1024,
        /** \brief flash������С */
        1024,
        /** \brief flashҳ��С */
        64,
    },

    /** \brief flash�Ĵ����Ļ���ַ */
    ZLG116_FLASH_BASE,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_zlg_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
static am_boot_flash_handle_t am_zlg116_boot_single_flash_inst_init(void)
{
    return am_zlg_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}

/*******************************************************************************
 * �̼���flash�ķ�ʽ�洢����
 ******************************************************************************/
static am_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief �̼����ڴ��д�ŵ���ʼ��ַ */
    0x08003C00,
    /**< \brief Ӧ�ô��������ܴ�С */
    49 * 1024,
    /** \brief ������Ź̼���������С ,ֵΪ�ڴ�д����С��С�������� */
    4,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

static am_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_zlg116_boot_single_firmware_flash_inst_init(void)
{
    am_boot_flash_handle_t   flash_handle;
    flash_handle = am_zlg116_boot_single_flash_inst_init();
    return am_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                        &__g_firmware_flash_devinfo,
                                         flash_handle);
}

/*******************************************************************************
 * ��׼bootloader�ӿ�����
 ******************************************************************************/

/* ������bootloader���õ�����Դ��Ҫ�ӳ�ʼ�����ͷţ��������綨ʱ�������ڵ� */
static void __zlg116_boot_single_plfm_deinit()
{
    volatile uint32_t i = 1000000;
    /* ���ڽ��ʼ�� �����ʼ��ǰ��ҪС�ε���ʱ����֤�Ĵ��������Ѿ����*/
    while(i--){
    }

    am_zlg116_clk_inst_deinit();

    am_int_disable(INUM_UART1);
    am_clk_disable(CLK_UART1);

    am_arm_nvic_deinit();

    __disable_irq();
}
/**
 * < \brief bootloader��׼�豸��Ϣ
 */
static am_arm_boot_devinfo_t __g_zlg116_boot_single_devinfo = {
    /**< \brief Ӧ�ô�������ʼ��ַ*/
    0x08003C00,
    /** \brief ram��ʼ��ַ */
    0x20000000,
    /** \brief ram��С */
    8 * 1024,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    __zlg116_boot_single_plfm_deinit,
};

int am_zlg116_boot_single_inst_init()
{
    return am_arm_boot_init(&__g_zlg116_boot_single_devinfo);
}


/** @} */

/* end of file */

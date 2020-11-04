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
 * \brief bootloader �̼��洢flash����������̼��洢��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-21  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_ZML165_BOOT_FIRMWARE_H
#define __AM_ZML165_BOOT_FIRMWARE_H

#include "am_boot_flash.h"
#include "am_boot_firmware.h"
typedef struct am_zml165_boot_firmware_flash_devinfo {
    uint32_t firmware_dst_addr;    /**< \brief �̼���flash��ŵ�Ŀ�ĵ�ַ */
    uint32_t buf_size;

    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������ */
}am_zml165_boot_firmware_flash_devinfo_t;

typedef struct am_zml165_boot_firmware_flash_dev {
    /**< \brief �̼���ŵı�׼���� */
    am_boot_firmware_serv_t           firmware_flash_serv;
    /**< \brief flash�Ĳ������*/
    am_boot_flash_handle_t            flash_handle;
    /**< \brief �豸��Ϣ */
    am_zml165_boot_firmware_flash_devinfo_t *p_devinfo;
    /**< \brief ���ݻ����� */
    uint8_t                           buf_data[1024];
    /**< \brief �������Ĵ�С */
    uint32_t                          buf_data_size;
    /**< \brief ��ǰ�������е����ݴ�С */
    uint32_t                          curr_buf_data_size;
    /**< \brief �����������������ʼ��ַ */
    uint32_t                          erase_sector_start_addr;
    /**< \brief ��ǰдflash�ĵ�ַ */
    uint32_t                          curr_program_flash_addr;
    /**< \brief �̼���ŵ�Ŀ�ص�ַ */
    uint32_t                          firmware_dst_addr;
    /**< \brief �̼��ܵĴ�С */
    uint32_t                          firmware_total_size;
    am_bool_t                         firmware_size_is_unknow;
}am_zml165_boot_firmware_flash_dev_t;

/**
 * \brief ��ʼ���̼���ź��������ر�׼����������
 *
 * \param[in] p_dev     : ָ��̼�����豸��ָ��
 * \param[in] p_devinfo : ָ��̼�����豸��Ϣ������ָ��
 *
 * \return �̼���ű�׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_boot_firmware_handle_t am_zml165_boot_firmware_flash_init (
    am_zml165_boot_firmware_flash_dev_t     *p_dev,
    am_zml165_boot_firmware_flash_devinfo_t *p_devinfo,
    am_boot_flash_handle_t                   flash_handle);


/**
 * \brief �̼�flash�洢���ʼ��
 */
void am_zml165_boot_firmware_flash_deint(void);

#endif /* __AM_ZML165_BOOT_FIRMWARE_H */

/* end of file */

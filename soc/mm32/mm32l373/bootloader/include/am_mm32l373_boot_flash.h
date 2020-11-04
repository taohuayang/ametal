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
 * \brief bootloader flash��������������bootloader��flash��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-21  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_MM32L373_BOOT_FLASH_H
#define __AM_MM32L373_BOOT_FLASH_H
#include "am_mm32_flash.h"
#include "am_boot.h"
#include "am_boot_flash.h"

typedef struct am_mm32l373_boot_flash_devinfo {
    uint32_t  flash_start_addr;     /**< \brief flash����ʼ��ַ */
    uint32_t  flash_size;           /**< \brief flash�Ĵ�С */
    uint32_t  flash_sector_size;    /**< \brief flash������С */
    uint32_t  flash_sector_count;   /**< \brief flash������Ŀ */

    uint32_t  flash_reg_rebese;     /**< \brief flash�Ĵ�������ַ */
    void (*pfn_plfm_init)(void);    /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void);  /**< \brief ƽ̨ȥ��ʼ������ */

} am_mm32l373_boot_flash_devinfo_t;

typedef struct am_mm32l373_boot_flash_dev {
    am_boot_flash_serv_t            flash_serv;     /**< \brief flash��׼���� */
    am_boot_flash_info_t            flash_info;     /**< \brief flash��Ϣ�ṹ�� */
    amhw_mm32_flash_t               *amhw_mm32_flash; /**< \brief flash�Ĵ����ṹ�� */
    am_mm32l373_boot_flash_devinfo_t *p_devinfo;      /**< \brief �豸��Ϣ�ṹ�� */
}am_mm32l373_boot_flash_dev_t;

/**
 * \brief ��ʼ��flash������flash��׼����������
 *
 * \param[in] p_dev     : ָ��flash�豸��ָ��
 * \param[in] p_devinfo : ָ��flash�豸��Ϣ������ָ��
 *
 * \return flash��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_boot_flash_handle_t am_mm32l373_boot_flash_init(am_mm32l373_boot_flash_dev_t     *p_dev,
                                                 am_mm32l373_boot_flash_devinfo_t *p_devinfo);


#endif /* __AM_MM32L373_BOOT_FLASH_H */

/* end of file */

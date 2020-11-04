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

#ifndef __AM_ZLG237_BOOT_FLASH_H
#define __AM_ZLG237_BOOT_FLASH_H

#include "am_zlg237_flash.h"
#include "am_boot.h"
#include "am_boot_flash.h"

typedef struct am_zlg237_boot_flash_devinfo {
    /**< \brief flash������Ϣ */
    am_boot_flash_info_t  base_info;
    /**< \brief flash�Ĵ�������ַ */
    uint32_t              flash_reg_rebese;
    /**< \brief ƽ̨��ʼ������ */
    void                (*pfn_plfm_init)(void);
    /**< \brief ƽ̨ȥ��ʼ������ */
    void                (*pfn_plfm_deinit)(void);

} am_zlg237_boot_flash_devinfo_t;

typedef struct am_zlg237_boot_flash_dev {
    /**< \brief flash��׼���� */
    am_boot_flash_serv_t             flash_serv;
    /**< \brief flash�Ĵ����ṹ�� */
    amhw_zlg237_flash_t             *amhw_zlg237_flash;
    /**< \brief �豸��Ϣ�ṹ�� */
    am_zlg237_boot_flash_devinfo_t  *p_devinfo;
}am_zlg237_boot_flash_dev_t;

/**
 * \brief ��ʼ��flash������flash��׼����������
 *
 * \param[in] p_dev     : ָ��flash�豸��ָ��
 * \param[in] p_devinfo : ָ��flash�豸��Ϣ������ָ��
 *
 * \return flash��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_boot_flash_handle_t am_zlg237_boot_flash_init(am_zlg237_boot_flash_dev_t     *p_dev,
                                                 am_zlg237_boot_flash_devinfo_t *p_devinfo);


#endif /* __AM_ZLG237_BOOT_FLASH_H */

/* end of file */

/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg237.cn/
*******************************************************************************/

/**
 * \file
 * \brief Flash������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  ari, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG237_FLASH_H
#define __AM_ZLG237_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "soc_cfg.h"
#include "hw/amhw_zlg237_flash.h"

/**
 * \addtogroup am_zlg237_if_flash
 * \copydoc am_zlg237_flash.h
 * @{
 */

/**
 * \brief Flashģ���ʼ��
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 *
 * \return ��
 */
void am_zlg237_flash_init (amhw_zlg237_flash_t *p_hw_flash);

/**
 * \brief ����ҳ����ҳ��СΪ1024��
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr  ��������ʼ��ַ
 *
 * \return >0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_zlg237_flash_page_erase (amhw_zlg237_flash_t *p_hw_flash,
                                    uint32_t             start_addr);

/**
 * \brief ������ҳ��ҳ��СΪ1024��
 *
 * \param[in] p_hw_gpio  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr ��ҳ����ʼ��ַ
 *
 * \return > 0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_zlg237_flash_half_page_erase (amhw_zlg237_flash_t *p_hw_flash,
                                         uint32_t             start_addr);

/**
 * \brief ����������̻򲿷��������
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 * \param[in] dst_addr   д�뵽flash����ʼ��ַ
 * \param[in] p_src      Ҫд�뵽flash�е����ݵ���ʼ��ַ
 * \param[in] size       д����(32bit)�ĸ���
 *
 * \retval 0 ʵ�ʳɹ�д�������
 */
int32_t am_zlg237_flash_sector_program (amhw_zlg237_flash_t *p_hw_flash,
                                        uint32_t             dst_addr,
                                        uint32_t            *p_src,
                                        uint32_t             size);

/**
 * \brief ������������
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 *
 * \return ִ�н��
 *
 */
uint32_t am_zlg237_flash_all_sector_erase (amhw_zlg237_flash_t *p_hw_flash);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AM_ZLG237_FLASH_H */

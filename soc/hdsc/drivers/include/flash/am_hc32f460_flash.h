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
 * \brief Flash������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-06-17  cds, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_FLASH_H
#define __AM_HC32F460_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "hw/amhw_hc32f460_flash.h"

/**
 * \addtogroup am_hc32f460_if_flash
 * \copydoc am_hc32f460_flash.h
 * @{
 */

/**
 * \brief EFM�Ĵ���д�������
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 *
 * \return ��
 */
void am_hc32f460_flash_unlock(amhw_hc32f460_flash_t            *p_hw_flash);

/**
 * \brief ����FLASH������ĵȴ�����
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 * \param[in] waitcycle   ����
 *
 * \return ��
 */
void am_hc32f460_flash_waitcycle(amhw_hc32f460_flash_t            *p_hw_flash,
                                 amhw_hc32f460_flash_read_waittime waitcycle);

/**
 * \brief EFM�Ĵ���д��������
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 *
 * \return ��
 */
void am_hc32f460_flash_lock(amhw_hc32f460_flash_t *p_hw_flash);


/**
 * \brief FLASH��ʼ��
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 *
 * \return ��
 */
void am_hc32f460_flash_init (amhw_hc32f460_flash_t *p_hw_flash);


/**
 * \brief ��������
 *
 * \param[in] p_hw_gpio  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr ��������ʼ��ַ
 *
 * \return > 0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_hc32f460_flash_sector_erase (amhw_hc32f460_flash_t *p_hw_flash,
                                        uint32_t               start_addr);


/**
 * \brief ȫ����
 *
 * \param[in] p_hw_gpio  ָ��FLASH�Ĵ������ָ��
 *
 * \return ִ�н��
 */
int32_t am_hc32f460_flash_all_sector_erase (amhw_hc32f460_flash_t *p_hw_flash);


/**
 * \brief ��flash���
 *
 * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
 * \param[in] dst_addr  д�뵽flash����ʼ��ַ
 * \param[in] p_src     Ҫд�뵽flash�е����ݵ���ʼ��ַ
 * \param[in] size      д����(32bit)�ĸ���
 *
 * \retval 0 ʵ�ʳɹ�д�������
 */
int32_t am_hc32f460_flash_sector_program (amhw_hc32f460_flash_t *p_hw_flash,
                                          uint32_t               dst_addr,
                                          uint32_t              *p_src,
                                          uint32_t               size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AM_HC32_FLASH_H */

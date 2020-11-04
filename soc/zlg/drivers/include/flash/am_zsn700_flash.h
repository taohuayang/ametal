/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
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
 * - 1.00 20-03-17  YRZ, first implementation
 * \endinternal
 */

#ifndef __AM_ZSN700_FLASH_H
#define __AM_ZSN700_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "soc_cfg.h"
#include "hw/amhw_zsn700_flash.h"

/**
 * \addtogroup am_zsn700_if_flash
 * \copydoc am_zsn700_flash.h
 * @{
 */

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
 * \brief ���ö�FLASH����
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 * \param[in] waitcycle   ����
 *
 * \return ִ�н��
 */
int32_t am_zsn700_flash_waitcycle(amhw_zsn700_flash_t              *p_hw_flash,
                                  amhw_zsn700_flash_read_waittime   waitcycle);

/**
 * \brief ��������
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr  ��������ʼ��ַ
 *
 * \return >0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_zsn700_flash_sector_erase (amhw_zsn700_flash_t  *p_hw_flash,
                                      uint32_t              addr);

/**
 * \brief ��������̻򲿷��������
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 * \param[in] dst_addr   д�뵽flash����ʼ��ַ
 * \param[in] p_src      Ҫд�뵽flash�е����ݵ���ʼ��ַ
 * \param[in] size       д����(32bit)�ĸ���
 *
 * \retval 0 ʵ�ʳɹ�д�������
 */
int32_t am_zsn700_flash_sector_program (amhw_zsn700_flash_t    *p_hw_flash,
                                        uint32_t                dst_addr,
                                        uint32_t               *p_src,
                                        uint32_t                size);

/**
 * \brief ������������(������������SRAM����Ч)
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 *
 * \return ִ�н��
 *
 */
int32_t am_zsn700_flash_all_sector_erase (amhw_zsn700_flash_t *p_hw_flash);

/**
 * \brief Flashģ���ʼ��
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 * \param[in] freqcfg    flashʱ�����
 * \param[in] dpstb_able dpstbʹ�ܿ���
 *
 * \return ��
 */
int32_t am_zsn700_flash_init(amhw_zsn700_flash_t   *p_hw_flash,
                             uint8_t                freqcfg,
                             am_bool_t              dpstb_able);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AM_ZSN700_FLASH_H */

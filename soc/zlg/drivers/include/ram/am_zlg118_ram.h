/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief Flash������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-08
 * \endinternal
 */

#ifndef __AM_ZLG118_RAM_H
#define __AM_ZLG118_RAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hw/amhw_zlg118_ram.h"

/**
 * \addtogroup am_zlg118_if_ram
 * \copydoc am_zlg118_ram.h
 * @{
 */

/* RAM��ַ��Χ */
#define RAM_SIZE            0x7FFF
#define RAM_ADDRESS_BASE    0x20000000
#define RAM_ADDRESS_SIZE   (0x20000000 + RAM_SIZE)

/**
 * \brief RAM��ʼ��
 *
 * \param[in] p_hw_ram ָ��RAM�Ĵ������ָ��
 *
 * \return ��
 */
void am_zlg118_ram_init (amhw_zlg118_ram_t *p_hw_ram);

/**
 * \brief ����RAM����
 *
 * \param[in] p_hw_ram    ָ��RAM�Ĵ������ָ��
 * \param[in] start_addr  ��ʼ��ַ
 * \param[in] size        ��С
 *
 * \return >0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_zlg118_ram_erase (amhw_zlg118_ram_t *p_hw_ram,
                             uint32_t           start_addr,
                             uint16_t           size);

/**
 * \brief ��RAM���
 *
 * \param[in] p_hw_ram   ָ��RAM�Ĵ������ָ��
 * \param[in] dst_addr   д�뵽ram����ʼ��ַ
 * \param[in] p_src      Ҫд�뵽ram�е����ݵ���ʼ��ַ
 * \param[in] size       д���ֽڵĸ���
 *
 * \retval i ʵ�ʳɹ�д�������
 */
int32_t am_zlg118_ram_write (amhw_zlg118_ram_t *p_hw_ram,
                             uint32_t           dst_addr,
                             uint8_t           *p_src,
                             uint16_t           size);

/**
 * \brief ��RAM��ȡ����
 *
 * \param[in] p_hw_ram   ָ��RAM�Ĵ������ָ��
 * \param[in] dst_addr   ��ȡ��ram��ʼ��ַ
 * \param[in] p_src      Ҫ��ȡram�е����ݵ���ʼ��ַ
 * \param[in] size       ��ȡ�ֽڵĸ���
 *
 * \retval i ʵ�ʳɹ���ȡ������
 */
int32_t am_zlg118_ram_read (amhw_zlg118_ram_t *p_hw_ram,
                            uint32_t           dst_addr,
                            uint8_t           *p_src,
                            uint16_t           size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AM_ZLG118_RAM_H */

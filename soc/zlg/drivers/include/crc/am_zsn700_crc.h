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
 * \brief CRC����������CRC��׼�ӿ�
 *
 * ֻ��֧��4�ֽڶ�������м���
 * ���� ���е��ֽ��� % 4 == 0
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-18
 * \endinternal
 */

#ifndef  __AM_ZSN700_CRC_H
#define  __AM_ZSN700_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_crc.h"

#include "hw/amhw_zsn700_crc.h"

/**
 * \addtogroup am_zsn700_if_crc
 * \copydoc am_zsn700_crc.h
 * @{
 */

#define AM_ZSN700_CRC_16  0 /**< \brief CRC-16 У�鷽ʽ*/
#define AM_ZSN700_CRC_32  1 /**< \brief CRC-32 У�鷽ʽ */

/**
 * \brief CRC�豸��Ϣ
 */
typedef struct am_zsn700_crc_devinfo {

    /** \brief CRC�Ĵ�����Ļ���ַ */
    uint32_t   crc_reg_base;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_zsn700_crc_devinfo_t;

/**
 * \brief CRC�豸ʵ��
 */
typedef struct am_zsn700_crc_dev {

    /** \brief CRC��׼���� */
    am_crc_serv_t                  crc_serve;

    /** \brief ָ��CRC�豸��Ϣ��ָ�� */
    const am_zsn700_crc_devinfo_t *p_devinfo;

    /** \brief ָ��CRCģ�͵�ָ�� */
    am_crc_pattern_t              *p_pattern;

} am_zsn700_crc_dev_t;

/**
 * \brief CRC��ʼ��
 *
 * \param[in] p_dev     : ָ��CRC�豸��ָ��
 * \param[in] p_devinfo : ָ��CRC�豸��Ϣ��ָ��
 *
 * \return CRC��׼���������������Ϊ NULL��������ʼ��ʧ��
 */
am_crc_handle_t am_zsn700_crc_init (am_zsn700_crc_dev_t           *p_dev,
                                    const am_zsn700_crc_devinfo_t *p_devinfo);

/**
 * \brief CRCȥ��ʼ��
 *
 * \param[in] handle : am_zsn700_crc_init() ��ʼ��������õ�CRC������
 *
 * \return ��
 */
void am_zsn700_crc_deinit (am_crc_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_CRC_H */

/* end of file */

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
 * \brief CLKTRIM��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-29
 * \endinternal
 */

#ifndef  __AM_ZLG118_CLKTRIM_H
#define  __AM_ZLG118_CLKTRIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "hw/amhw_zlg118_clktrim.h"

/**
 * \addtogroup am_zlg118_if_clktrim
 * \copydoc am_zlg118_clktrim.h
 * @{
 */

/**
 * \brief CLKTRIM���ģʽ����
 *
 * \param[in] rcntval    : �ο���������ֵ
 * \param[in] rcntval    : У׼���������ֵ
 * \param[in] refclk_sel : �ο�ʱ��ѡ��
 * \param[in] calclk_sel : �����ʱ��ѡ��
 *
 * \return <0�������ʱ��ʧЧ
 *        AM_OK����������
 */
uint8_t am_zlg118_clktrim_monitor (uint16_t                     rcntval,
                                   uint16_t                     ccntval,
                                   amhw_clktrim_refclk_sel_t    refclk_sel,
                                   amhw_clktrim_calclk_sel_t    calclk_sel);

/**
 * \brief CLKTRIMУ׼ģʽ����
 *
 * \param[in] rcntval    : �ο���������ֵ
 * \param[in] refclk_sel : �ο�ʱ��ѡ��
 * \param[in] calclk_sel : ��У׼ʱ��ѡ��
 *
 * \return <0�������У׼ʱ��
 *         >0��У׼ʱ�Ӽ�������ֵ / �ο�ʱ�Ӽ�������ֵ * 1000
 */
uint8_t am_zlg118_clktrim_calibrate (uint16_t                     rcntval,
                                     amhw_clktrim_refclk_sel_t    refclk_sel,
                                     amhw_clktrim_calclk_sel_t    calclk_sel);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_CLKTRIM_H */

/* end of file */

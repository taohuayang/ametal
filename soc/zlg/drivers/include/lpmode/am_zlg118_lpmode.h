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
 * \brief LPMODE �����ӿ�����
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-18  nwt, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG118_LPMODE_H
#define __AM_ZLG118_LPMODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "hw/amhw_zlg118_lpmode.h"
#include "hw/amhw_zlg118_rcc.h"

/**
 * \addtogroup am_zlg118_if_lpmode
 * \copydoc am_zlg118_lpmode.h
 * @{
 */

/**
 * \brief LPMODE ģʽ
 */
typedef enum am_zlg118_lpmode_mode {
    AM_ZLG118_LPMODE_MODE_RUN = 0,      /**< \brief ����ģʽ */
    AM_ZLG118_LPMODE_MODE_SLEEP,        /**< \brief ˯��ģʽ */
    AM_ZLG118_LPMODE_MODE_DEEPSLEEP,    /**< \brief ���˯��ģʽ */
} am_zlg118_lpmode_mode_t;

/*
 * \brief LPMODE �豸�ṹ��
 */
typedef struct am_zlg118_lpmode_dev {

    /** \brief LPMODE ģʽ */
    am_zlg118_lpmode_mode_t lpmode_mode;

} am_zlg118_lpmode_dev_t;

/** \brief LPMODE �豸����������Ͷ��� */
typedef am_zlg118_lpmode_dev_t *am_zlg118_lpmode_handle_t;

/**
 * \brief LPMODE ��ʼ��
 *
 * \return ���� am_zlg118_lpmode_handle_t ���͵ľ��
 */
am_zlg118_lpmode_handle_t am_zlg118_lpmode_init (void);

/**
 * \brief ���˯��ģʽ
 *
 * \param[in] stata  AM_TRUE  �� ���˳��쳣������Զ��ٴν������ߣ�
 *                   AM_FALSE �� ���Ѻ����Զ���������
 *
 * \return ��
 */
void am_zlg118_lpmode_deepsleep (am_bool_t stata);

/**
 * \brief ��ͨ˯��ģʽ
 *
 * \param[in] stata  AM_TRUE  �� ���˳��쳣������Զ��ٴν������ߣ�
 *                   AM_FALSE �� ���Ѻ����Զ���������
 *
 * \return ��
 */
void am_zlg118_lpmode_sleep (am_bool_t stata);

/**
 * \brief LPMODEģʽ��ϵͳʱ������
 *
 * \param[in] mode LPMODE ģʽ����
 *
 * \retval  AM_OK      ģʽ�л���Ч
 * \retval  AM_ERROR   ģʽ�л�����
 * \retval -AM_EINVAL  ʽ��������
 */
int am_zlg118_lpmode_clk_change (am_zlg118_lpmode_mode_t mode);

/**
 * \brief ��ȡ LPMODE ģʽ
 *
 * \param[in] ��
 *
 * \return am_zlg118_lpmode_mode_t ��һö�����͵�ֵ
 */
am_zlg118_lpmode_mode_t am_zlg118_lpmode_mode_get (void);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_LPMODE_H */

/* end of file */

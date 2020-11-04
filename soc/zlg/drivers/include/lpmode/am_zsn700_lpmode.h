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
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */

#ifndef __AM_ZSN700_LPMODE_H
#define __AM_ZSN700_LPMODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "hw/amhw_zsn700_lpmode.h"
#include "hw/amhw_zsn700_rcc.h"

/**
 * \addtogroup am_zsn700_if_lpmode
 * \copydoc am_zsn700_lpmode.h
 * @{
 */

/**
 * \brief LPMODE ģʽ
 */
typedef enum am_zsn700_lpmode_mode {
    AM_ZSN700_LPMODE_MODE_RUN = 0,      /**< \brief ����ģʽ */
    AM_ZSN700_LPMODE_MODE_SLEEP,        /**< \brief ˯��ģʽ */
    AM_ZSN700_LPMODE_MODE_DEEPSLEEP,    /**< \brief ���˯��ģʽ */
} am_zsn700_lpmode_mode_t;

/*
 * \brief LPMODE �豸�ṹ��
 */
typedef struct am_zsn700_lpmode_dev {

    /** \brief LPMODE ģʽ */
    am_zsn700_lpmode_mode_t lpmode_mode;

} am_zsn700_lpmode_dev_t;

/** \brief LPMODE �豸����������Ͷ��� */
typedef am_zsn700_lpmode_dev_t *am_zsn700_lpmode_handle_t;

/**
 * \brief LPMODE ��ʼ��
 *
 * \return ���� am_zsn700_lpmode_handle_t ���͵ľ��
 */
am_zsn700_lpmode_handle_t am_zsn700_lpmode_init (void);

/**
 * \brief ���˯��ģʽ
 *
 * \param[in] stata  AM_TRUE  �� ���˳��쳣������Զ��ٴν������ߣ�
 *                   AM_FALSE �� ���Ѻ����Զ���������
 *
 * \return ��
 */
void am_zsn700_lpmode_deepsleep (am_bool_t stata);

/**
 * \brief ��ͨ˯��ģʽ
 *
 * \param[in] stata  AM_TRUE  �� ���˳��쳣������Զ��ٴν������ߣ�
 *                   AM_FALSE �� ���Ѻ����Զ���������
 *
 * \return ��
 */
void am_zsn700_lpmode_sleep (am_bool_t stata);

/**
 * \brief LPMODEģʽ��ϵͳʱ������
 *
 * \param[in] mode LPMODE ģʽ����
 *
 * \retval  AM_OK      ģʽ�л���Ч
 * \retval  AM_ERROR   ģʽ�л�����
 * \retval -AM_EINVAL  ʽ��������
 */
int am_zsn700_lpmode_clk_change (am_zsn700_lpmode_mode_t mode);

/**
 * \brief ��ȡ LPMODE ģʽ
 *
 * \param[in] ��
 *
 * \return am_zsn700_lpmode_mode_t ��һö�����͵�ֵ
 */
am_zsn700_lpmode_mode_t am_zsn700_lpmode_mode_get (void);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_LPMODE_H */

/* end of file */

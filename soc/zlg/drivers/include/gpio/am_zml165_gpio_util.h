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
 * \brief GPIOƽ̨�������ߺ�
 *
 * ���ļ��������� \sa zml165_pin.h. �䶨����GPIOƽ̨���ŵĸ������ܡ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __AM_ZML165_GPIO_UTIL_H
#define __AM_ZML165_GPIO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_zml165_if_gpio_util
 * \copydoc am_zml165_gpio_util.h
 * @{
 */

/**
 * \brief ƽ̨�궨��
 *
 * bit[31:12] ƽ̨����
 *
 */

/**
 * \name ����λ��
 * @{
 */
#define AM_ZML165_GPIO_DIR                   AM_BIT(12) /**< \brief �ܽŷ��� */
#define AM_ZML165_GPIO_OUTRES_RATE           AM_BIT(13) /**< \brief �ܽ���Ӧ���� */
#define AM_ZML165_GPIO_MODE                  AM_BIT(14) /**< \brief �ܽ�ģʽ */
#define AM_ZML165_GPIO_FUNEN                 AM_BIT(15) /**< \brief �ܽŸ��ù���ʹ�� */

/** \brief ����λƫ�� */
#define AM_ZML165_GPIO_DIRBIT_START          16         /**< \brief ��������ʼλ */
#define AM_ZML165_GPIO_DIRBIT_LEN            2          /**< \brief �����볤�� */

/** \brief �÷����� */
#define AM_ZML165_GPIO_DIR_CODE(a)           (AM_SBF((a), AM_ZML165_GPIO_DIRBIT_START) |  \
                                                AM_ZML165_GPIO_DIR)

/** \brief ��ȡ������ */
#define AM_ZML165_GPIO_DIR_GET(data)         AM_BITS_GET((data), AM_ZML165_GPIO_DIRBIT_START, \
                                                            AM_ZML165_GPIO_DIRBIT_LEN)

#define AM_ZML165_GPIO_OUTRESRATEBITS_START  18         /**< \brief �����Ӧ��������ʼλ */
#define AM_ZML165_GPIO_OUTRESRATEBITS_LEN    2          /**< \brief �����Ӧ�����볤�� */

/** \brief ����Ӧ������ */
#define AM_ZML165_GPIO_OUTRES_RATE_CODE(a)   (AM_SBF((a), AM_ZML165_GPIO_OUTRESRATEBITS_START) |  \
                                                AM_ZML165_GPIO_OUTRES_RATE)

/** \brief ��ȡ��Ӧ������ */
#define AM_ZML165_GPIO_OUTRES_RATE_GET(data) AM_BITS_GET((data), AM_ZML165_GPIO_OUTRESRATEBITS_START, \
                                                             AM_ZML165_GPIO_OUTRESRATEBITS_LEN)

#define AM_ZML165_GPIO_MODEBITS_START        20         /**< \brief ģʽ����ʼλ */
#define AM_ZML165_GPIO_MODEBITS_LEN          4          /**< \brief ģʽ�볤�� */

/** \brief ��ģʽ�� */
#define AM_ZML165_GPIO_MODE_CODE(a)          (AM_SBF((a), AM_ZML165_GPIO_MODEBITS_START) |  \
                                                AM_ZML165_GPIO_MODE)

/** \brief ��ȡģʽ�� */
#define AM_ZML165_GPIO_MODE_GET(data)         AM_BITS_GET((data), AM_ZML165_GPIO_MODEBITS_START, \
                                                            AM_ZML165_GPIO_MODEBITS_LEN)

#define AM_ZML165_GPIO_FUNBITS_START          24        /**< \brief ��������ʼλ */
#define AM_ZML165_GPIO_FUNBITS_LEN            4         /**< \brief �����볤�� */

/** \brief �ù����� */
#define AM_ZML165_GPIO_FUNC_CODE(a)           (AM_SBF((a), AM_ZML165_GPIO_FUNBITS_START) |  \
                                                 AM_ZML165_GPIO_FUNEN)

/** \brief ��ȡ������ */
#define AM_ZML165_GPIO_FUNC_GET(data)         AM_BITS_GET((data), AM_ZML165_GPIO_FUNBITS_START, \
                                                            AM_ZML165_GPIO_FUNBITS_LEN)

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZML165_GPIO_UTIL_H */

/* end of file */

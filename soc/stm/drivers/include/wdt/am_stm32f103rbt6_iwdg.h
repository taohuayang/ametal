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
 * \brief IWDG������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-07  sss, first implementation
 * \endinternal
 */

#ifndef __AM_STM32F103RBT6_IWDG_H
#define __AM_STM32F103RBT6_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_wdt.h"

/**
 * \addtogroup am_stm32f103rbt6_if_iwdg
 * \copydoc am_stm32f103rbt6_iwdg.h
 * @{
 */

/**
 * \brief IWDG�豸��Ϣ�ṹ��
 */
typedef struct am_stm32f103rbt6_iwdg_devinfo {

    /** \brief IWDG�Ĵ��������ַ */
    uint32_t iwdg_regbase;

    /** \brief ƽ̨��ʼ������ */
    void   (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void   (*pfn_plfm_deinit)(void);

} am_stm32f103rbt6_iwdg_devinfo_t;

/**
 * \brief IWDG�豸�ṹ��
 */
typedef struct am_stm32f103rbt6_iwdg_dev {

    /** \brief IWDG�ṩ�ı�׼���� */
    am_wdt_serv_t                 wdt_serv;

    /** \brief Ԥ��Ƶ���� */
    uint16_t                      div;

    /** \brief ָ��IWDG�豸����Ϣָ�� */
    const am_stm32f103rbt6_iwdg_devinfo_t  *p_devinfo;
} am_stm32f103rbt6_iwdg_dev_t;

/**
 * \brief IWDG��ʼ��
 *
 * \param[in] p_dev     : ָ��IWDG�豸
 * \param[in] p_devinfo : ָ��IWDG�豸��Ϣ
 *
 * \return IWDG��׼��������ʧ���򷵻�NULL
 */
am_wdt_handle_t am_stm32f103rbt6_iwdg_init (am_stm32f103rbt6_iwdg_dev_t              *p_dev,
                                     const am_stm32f103rbt6_iwdg_devinfo_t *p_devinfo);

/**
 * \brief ���IWDG�豸��ʼ��
 *
 * \param[in] handle : ʹ��IWDG��ʼ������am_stm32f103rbt6_iwdg_init()��ȡ����handle
 *
 * \return ��
 */
void am_stm32f103rbt6_iwdg_deinit (am_wdt_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __AMHW_IWDG_H */

#endif

/* end of file */


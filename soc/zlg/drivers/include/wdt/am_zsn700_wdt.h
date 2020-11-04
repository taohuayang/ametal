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
 * \brief WDT������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-10
 * \endinternal
 */

#ifndef __AM_ZSN700_WDT_H
#define __AM_ZSN700_WDT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_wdt.h"
#include "hw/amhw_zsn700_wdt.h"

/**
 * \addtogroup am_zsn700_if_wdt
 * \copydoc am_zsn700_wdt.h
 * @{
 */

/* WDT���ʱ������ */
typedef enum am_zsn700_wdt_wov {
    ZSN700_WDT_1_6MS = 0x0,
    ZSN700_WDT_3_2MS = 0x1,
    ZSN700_WDT_6_4MS = 0x2,
    ZSN700_WDT_13MS  = 0x3,
    ZSN700_WDT_26MS  = 0x4,
    ZSN700_WDT_51MS  = 0x5,
    ZSN700_WDT_102MS = 0x6,
    ZSN700_WDT_205MS = 0x7,
    ZSN700_WDT_500MS = 0x8,
    ZSN700_WDT_820MS = 0x9,
    ZSN700_WDT_1_64S = 0xa,
    ZSN700_WDT_3_28S = 0xb,
    ZSN700_WDT_6_55S = 0xc,
    ZSN700_WDT_13_1S = 0xd,
    ZSN700_WDT_26_2S = 0xe,
    ZSN700_WDT_52_4S = 0xf
} am_zsn700_wdt_wov_t;

/**
 * \brief WDT�豸��Ϣ�ṹ��
 */
typedef struct am_zsn700_wdt_devinfo {

    /** \brief WDT�Ĵ��������ַ */
    uint32_t  wdt_regbase;

    /** \brief ʱ��ID */
    int       clk_num;

    /** \brief ƽ̨��ʼ������ */
    void    (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void    (*pfn_plfm_deinit)(void);

} am_zsn700_wdt_devinfo_t;

/**
 * \brief WDT�豸�ṹ��
 */
typedef struct am_zsn700_wdt_dev {

    /** \brief WDT�ṩ�ı�׼���� */
    am_wdt_serv_t                   wdt_serv;

    /** \brief Ԥ��Ƶ���� */
    uint16_t                        div;

    /** \brief ָ��WDT�豸����Ϣָ�� */
    const am_zsn700_wdt_devinfo_t  *p_devinfo;
} am_zsn700_wdt_dev_t;


/**
 * \brief WDT��ʼ��
 *
 * \param[in] p_dev     : ָ��WDT�豸
 * \param[in] p_devinfo : ָ��WDT�豸��Ϣ
 *
 * \return WDT��׼��������ʧ���򷵻�NULL
 */
am_wdt_handle_t am_zsn700_wdt_init (am_zsn700_wdt_dev_t            *p_dev,
                                    const am_zsn700_wdt_devinfo_t  *p_devinfo);

/**
 * \brief ���WDT�豸��ʼ��
 *
 * \param[in] handle : ʹ��WDT��ʼ������am_zsn700_wdt_init()��ȡ����handle
 *
 * \return ��
 */
void am_zsn700_wdt_deinit (am_wdt_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __AM_ZSN700_WDT_H */

#endif

/* end of file */


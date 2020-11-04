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
 * \brief WWDG������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-07  sss, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG_WWDG_H
#define __AM_ZLG_WWDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_wdt.h"

/**
 * \addtogroup am_zlg_if_wwdg
 * \copydoc am_zlg_wwdg.h
 * @{
 */

/**
 * \brief WWDG���汾0���豸��Ϣ�ṹ��
 */
typedef struct am_zlg_wwdg_devinfo {

    /** \brief WWDG�Ĵ��������ַ */
    uint32_t  wwdg_regbase;

    /** \brief ʱ��ID */
    int       clk_num;

    /** \brief ƽ̨��ʼ������ */
    void    (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void    (*pfn_plfm_deinit)(void);

} am_zlg_wwdg_devinfo_t;

/**
 * \brief WWDG���汾0���豸�ṹ��
 */
typedef struct am_zlg_wwdg_dev {

    /** \brief WWDG�ṩ�ı�׼���� */
    am_wdt_serv_t                   wdt_serv;

    /** \brief Ԥ��Ƶ���� */
    uint16_t                        div;

    /** \brief ����ֵ */
    uint8_t                         count;

    /** \brief ָ��WWDG���汾0���豸����Ϣָ�� */
    const am_zlg_wwdg_devinfo_t *p_devinfo;
} am_zlg_wwdg_dev_t;

/**
 * \brief WWDG���汾0����ʼ��
 *
 * \param[in] p_dev     : ָ��WWDG���汾0���豸
 * \param[in] p_devinfo : ָ��WWDG���汾0���豸��Ϣ
 *
 * \return WWDG��׼��������ʧ���򷵻�NULL
 */
am_wdt_handle_t am_zlg_wwdg_init (am_zlg_wwdg_dev_t               *p_dev,
                                  const am_zlg_wwdg_devinfo_t  *p_devinfo);

/**
 * \brief ���WWDG���汾0���豸��ʼ��
 *
 * \param[in] handle : ʹ��WWDG���汾0����ʼ������am_zlg_wwdg_init()��ȡ����handle
 *
 * \return ��
 */
void am_zlg_wwdg_deinit (am_wdt_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __AM_ZLG_WWDG_H */

#endif

/* end of file */


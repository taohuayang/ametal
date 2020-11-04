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
 * \brief CAN������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-05  zcb, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_CAN_H
#define __AM_HC32F460_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_can.h"
#include "hw/amhw_hc32f460_can.h"

/**
 * \addtogroup am_hc32f460_if_can
 * \copydoc am_hc32f460_can.h
 * @{
 */

#define AM_HC32F460_FILTER_RTR            (0x1 << 31)
#define AM_HC32F460_FILTER_IDE            (0x1 << 30)
#define AM_HC32F460_FILTER_IDE_0_ID_START (18)

/**
 * \brief �жϻص���Ϣ
 */
typedef struct am_hc32f460_can_intcb_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
} am_hc32f460_can_intcb_info_t;

/**
 * \brief CAN �豸��Ϣ
 */
typedef struct am_hc32f460_can_devinfo {

    /** \brief �Ĵ�������ַ */
    uint32_t                       regbase;

    /** \brief �жϺ� */
    uint32_t                       int_num;

    /** \brief �������� */
    amhw_hc32f460_can_type_t         type;

    /** \brief �ص���Ϣ */
    am_hc32f460_can_intcb_info_t    *p_intcb_info;

    /** \brief �ص���Ϣ�ڴ��С */
    uint8_t                        p_intcb_num;

    /** \brief ƽ̨��ʼ������ */
    void                         (*pfn_plfm_init)(void);

    /** \brief ƽ̨ȥ��ʼ������ */
    void                         (*pfn_plfm_deinit)(void);
} am_hc32f460_can_devinfo_t;

/**
 * \brief �豸
 */
typedef struct am_hc32f460_can_dev {
    am_can_serv_t                   handle;

    amhw_hc32f460_can_mode_t          mode;

    const am_hc32f460_can_devinfo_t  *p_devinfo;
} am_hc32f460_can_dev_t;

/**
 * \brief CAN��ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 * \param[in] p_devinfo : �豸��Ϣ
 *
 * \return handle
 */
am_can_handle_t am_hc32f460_can_init (am_hc32f460_can_dev_t           *p_dev,
                                    const am_hc32f460_can_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 *
 * \return ��
 */
void am_hc32f460_can_deinit (am_can_handle_t handle);

/**
 * @} am_s32k14x_if_can
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_S32K14X_CAN_H */

/* end of file */


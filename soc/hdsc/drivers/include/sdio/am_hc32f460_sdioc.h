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
 * \brief SDIO����������SDIO��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-29  cds, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_SDIOC_H
#define __AM_HC32F460_SDIOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_int.h"
#include "am_sdio.h"
#include "am_list.h"
#include "am_wait.h"
#include "am_softimer.h"

#include "am_vdebug.h"
#include "hw/amhw_hc32f460_sdioc.h"

/**
 * \addtogroup am_hc32f460_if_sdioc
 * \copydoc am_hc32f460_sdioc.h
 * @{
 */

/**
 * \brief SDIOC�豸��Ϣ�����ṹ��
 */
typedef struct am_hc32f460_sdioc_devinfo {

    /** \brief SDIO�Ĵ�������ַ */
    uint32_t                         regbase;

    /** \brief SDIO�豸ID */
    uint8_t                          dev_id;

    /** \brief SDIO�жϺ� */
    uint32_t                         inum;

    /** \brief SDIOʱ��ID */
    int                              clk_num;

    /** \brief SDIO����ģʽ */
    amhw_hc32f460_sdioc_speed_mode_t speed_mode;

    /** \brief ƽ̨��ʼ������ */
    void                           (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                           (*pfn_plfm_deinit)(void);

} am_hc32f460_sdioc_devinfo_t;

/**
 * \brief SDIO�豸�ṹ��
 */
typedef struct am_hc32f460_sdioc_dev {

    /** \brief SDIO��׼����  */
    am_sdio_serv_t                     sdio_serv;

    /** \brief ָ��SDIO�豸��Ϣ  */
    const am_hc32f460_sdioc_devinfo_t *p_devinfo;

    /** \brief wait�ȴ�  */
    am_wait_t                          wait;

    /** \brief ������ͨ�ж�״̬  */
    uint16_t                           int_normal_status;

    /** \brief ��������ж�״̬  */
    uint16_t                           int_err_status;

    /** \brief �Ƿ���Ӧ���е�CRCУ����  */
    am_bool_t                          cmd_crc_enable;

} am_hc32f460_sdioc_dev_t;

/**
 * \brief SDIO��ʼ��
 *
 * \param[in] p_dev     : ָ��SDIO�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SDIO�豸��Ϣ�ṹ���ָ��
 *
 * \return SDIO��׼����������
 */
am_sdio_handle_t am_hc32f460_sdioc_init (am_hc32f460_sdioc_dev_t           *p_dev,
                                         const am_hc32f460_sdioc_devinfo_t *p_devinfo);

/**
 * \brief ���SDIO��ʼ��
 *
 * \param[in] handle : ����豸������SDIO��׼����������
 *
 * \return ��
 */
void am_hc32f460_sdioc_deinit (am_sdio_handle_t handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_SDIOC_H */

/* end of file */

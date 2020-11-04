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
 * \brief ��ʱ��TIM����������CAP��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-08  zp, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG118_ADTIM_CAP_H
#define __AM_ZLG118_ADTIM_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "hw/amhw_zlg118_adtim.h"

/**
 * \addtogroup am_zlg118_if_adtim_cap
 * \copydoc am_zlg118_adtim_cap.h
 * @{
 */

#define  AM_ZLG118_ADTIM_CAP_CHA  0x00   /**< \brief CAPͨ��A��ʶ��*/
#define  AM_ZLG118_ADTIM_CAP_CHB  0x01   /**< \brief CAPͨ��B��ʶ��*/

/**
 * \brief TIM��������ص�GPIO��Ϣ
 */
typedef struct am_zlg118_adtim_cap_ioinfo {
    int8_t   channel;        /**< \brief CAP��ʹ�õ�ͨ����ʶ�� */
    uint32_t gpio;           /**< \brief ��Ӧ��GPIO�ܽ� */
    uint32_t func;           /**< \brief Ϊ������ʱ��GPIO�������� */
    uint32_t dfunc;          /**< \brief ���ܹܽŲ�����ʱ��Ĭ��GPIO�������� */
} am_zlg118_adtim_cap_ioinfo_t;

/**
 * \brief TIM��������ص��豸��Ϣ
 */
typedef struct am_zlg118_adtim_cap_devinfo {
    uint32_t                      tim_regbase;   /**< \brief TIM�Ĵ������ַ */
    uint8_t                       inum;          /**< \brief TIM��Ӧ���жϺ� */
    amhw_zlg118_adtim_pclk_div_t  clk_div;       /**< \brief ʱ�ӷ�Ƶϵ�� */
    uint8_t                       channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ2 */
    am_zlg118_adtim_cap_ioinfo_t *p_ioinfo;      /**< \brief ָ�򲶻�ܽ���Ϣ�ṹ�� */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                          (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                          (*pfn_plfm_deinit)(void);
} am_zlg118_adtim_cap_devinfo_t;

/**
 * \brief TIM�������豸
 */
typedef struct am_zlg118_adtim_cap_dev {
    am_cap_serv_t          cap_serv;      /**< \brief ��׼CAP���� */

    struct {
        am_cap_callback_t  callback_func; /**< \brief �ص����� */
        void              *p_arg;         /**< \brief �ص��������û����� */
    } adtim_callback_info[2];             /**< \brief �洢���2ͨ���Ļص�������Ϣ */

    /** \brief ָ��TIM(������)�豸��Ϣ������ָ�� */
    const am_zlg118_adtim_cap_devinfo_t *p_devinfo;

    uint8_t                chan_max;      /**< \brief ��Ч�����ͨ����  */

} am_zlg118_adtim_cap_dev_t;

/**
 * \brief ��ʼ��TIMΪ������
 *
 * \param[in] p_dev     : ָ��TIM(������)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(������)�豸��Ϣ������ָ��
 *
 * \return CAP��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_cap_handle_t am_zlg118_adtim_cap_init (am_zlg118_adtim_cap_dev_t              *p_dev,
                                        const am_zlg118_adtim_cap_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��TIM������ʱ�����ʼ��TIM�����ܣ��ͷ������Դ
 *
 * \param[in] handle : am_zlg118_adtim_cap_init() ��ʼ��������õ�cap������
 *
 * \return ��
 */
void am_zlg118_adtim_cap_deinit (am_cap_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_ADTIM_CAP_H */

/* end of file */

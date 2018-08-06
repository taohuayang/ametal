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
 * \brief SYSTICK ���������� Timer ��׼�ӿ�
 *
 * \note ʹ�� SYSTICK ����� Timer ��׼�ӿڣ��Ͳ���ʹ�ñ�׼��ʱ�ӿ�
 *       am_mdelay()��am_udelay()
 * \internal
 * \par Modification History
 * - 1.00 15-09-22  win, first implementation.
 * \endinternal
 */

#ifndef __AM_ARM_SYSTICK_H
#define __AM_ARM_SYSTICK_H

#include "ametal.h"
#include "am_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_arm_if_systick
 * \copydoc am_arm_systick.h
 * @{
 */

/**
 * \brief SYSTICK �豸��Ϣ�ṹ��
 */
typedef struct am_arm_systick_devinfo {
    uint32_t     systick_regbase;  /**< \brief SYSTICK �Ĵ������ַ */
    uint32_t     clk_id;           /**< \brief SYSTICK ʱ��ID */
    uint32_t     clk_freq_src;     /**< \brief ʱ��Դ */
    
    /** \brief ƽ̨��ʼ������ */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
} am_arm_systick_devinfo_t;

/**
 * \brief SYSTICK �豸
 */
typedef struct am_arm_systick_dev {

    am_timer_serv_t timer_serv;    /**< \brief ��׼��ʱ(Timer)���� */
    am_pfnvoid_t    pfn_callback;  /**< \brief �ص����� */
    void           *p_arg;         /**< \brief �ص��������û����� */

    /** \brief ָ�� SYSTICK �豸��Ϣ������ָ�� */
    const am_arm_systick_devinfo_t  *p_devinfo;

} am_arm_systick_dev_t;

/**
 * \brief ��ʼ�� SYSTICK Ϊ��ʱ����
 *
 * \param[in] p_dev     : ָ�� SYSTICK �豸��ָ��
 * \param[in] p_devinfo : ָ�� SYSTICK �豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t 
am_arm_systick_init(am_arm_systick_dev_t           *p_dev,
                    const am_arm_systick_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ�� SYSTICK ʱ�����ʼ�� SYSTICK���ͷ������Դ
 *
 * \param[in] handle  : ��ʱ����׼����������
 *
 * \return ��
 */
void am_arm_systick_deinit(am_timer_handle_t handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ARM_SYSTICK_H */

/* end of file */
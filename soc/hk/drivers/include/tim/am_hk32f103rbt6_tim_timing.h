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
 * \brief ��ʱ��TIM����������Timer������ʵ��
 *
 * 1. TIM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���Timer��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. һ��TIMģ�飬ֻ��һ����ʱͨ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation
 * \endinternal
 */

#ifndef __AM_HK32F103RBT6_TIM_TIMING_H
#define __AM_HK32F103RBT6_TIM_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "hw/amhw_hk32f103rbt6_tim.h"

/**
 * \addtogroup am_hk32f103rbt6_if_tim_timing
 * \copydoc am_hk32f103rbt6_tim_timing.h
 * @{
 */

/**
 * \brief TIM��ʱ������ص��豸��Ϣ
 */
typedef struct am_hk32f103rbt6_tim_timing_devinfo {

    uint32_t               tim_regbase; /**< \brief TIM�Ĵ������ַ */

    uint8_t                inum;        /**< \brief TIM�жϺ� */

    int                    clk_num;     /**< \brief ʱ��ID */

    amhw_hk32f103rbt6_tim_type_t    tim_type;    /**< \brief ��ʱ������ */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                 (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                 (*pfn_plfm_deinit)(void);

} am_hk32f103rbt6_tim_timing_devinfo_t;

/**
 * \brief TIM��ʱ�����豸
 */
typedef struct am_hk32f103rbt6_tim_timing_dev {

    am_timer_serv_t timer_serv;         /**< \brief ��׼��ʱ(Timer)���� */

    void (*pfn_callback)(void *);       /**< \brief �ص����� */
    void  *p_arg;                       /**< \brief �ص��������û����� */

    /** \brief ָ��TIM(��ʱ����)�豸��Ϣ������ָ�� */
    const am_hk32f103rbt6_tim_timing_devinfo_t  *p_devinfo;

} am_hk32f103rbt6_tim_timing_dev_t;

/**
 * \brief ��ʼ��TIMΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��TIM(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t
am_hk32f103rbt6_tim_timing_init (am_hk32f103rbt6_tim_timing_dev_t              *p_dev,
                           const am_hk32f103rbt6_tim_timing_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��TIM��ʱ����ʱ�����ʼ��TIM��ʱ���ܣ��ͷ������Դ
 *
 * \param[in] handle : am_hk32f103rbt6_tim_timing_init() ��ʼ��������õ�Timer������
 *
 * \return ��
 */
void am_hk32f103rbt6_tim_timing_deinit (am_timer_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HK32F103RBT6_TIM_TIMING_H */

/* end of file */

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
 * - 1.00 20-03-12  yrz, first implementation
 * \endinternal
 */

#ifndef __AM_ZSN700_TIM_TIMING_H
#define __AM_ZSN700_TIM_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "hw/amhw_zsn700_tim.h"

/**
 * \addtogroup am_zsn700_if_tim_timing
 * \copydoc am_zsn700_tim_timing.h
 * @{
 */

/**
 * \brief TIM��ʱ������ص��豸��Ϣ
 */
typedef struct am_zsn700_tim_timing_devinfo {

    uint32_t                        tim_regbase;    /**< \brief TIM�Ĵ������ַ */

    uint8_t                         inum;           /**< \brief TIM�жϺ� */

    amhw_zsn700_tim_type_t          tim_type;       /**< \brief ��ʱ������ */

    /** \brief 16/32λ����    ע�⣺32λ�����ǲ�����װ�صģ�16λ��������װ��*/
    amhw_zsn700_tim_mode0_counter_t counter_type;

    /** \brief �ſ�ʹ�ܣ���ƽ��Ч�ſ�����������Ҫ���ö�Ӧ��ʱ��GATE���ţ�*/
    amhw_zsn700_tim_gate_t          gate_enable;

    /** \brief �ſص�ƽ��Чѡ��    AM_TRUE���ߵ�ƽ              AM_FALSE���͵�ƽ */
    am_bool_t                       gate_state;

    /** \brief ����ʱ��ѡ���ڲ����ⲿ�����������ⲿ����Ҫ���ö�Ӧ��ʱ��ETR���� */
    amhw_zsn700_tim_clk_src_t       clk_src;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                            (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                            (*pfn_plfm_deinit)(void);

} am_zsn700_tim_timing_devinfo_t;

/**
 * \brief TIM��ʱ�����豸
 */
typedef struct am_zsn700_tim_timing_dev {

    am_timer_serv_t timer_serv;         /**< \brief ��׼��ʱ(Timer)���� */

    void (*pfn_callback)(void *);       /**< \brief �ص����� */
    void  *p_arg;                       /**< \brief �ص��������û����� */

    uint16_t           prescale_to;     /**< \brief ������Ƶֵ  */
    uint16_t           prescale_in;     /**< \brief ʵ�ʷ�Ƶֵ  */

    /** \brief ָ��TIM(��ʱ����)�豸��Ϣ������ָ�� */
    const am_zsn700_tim_timing_devinfo_t  *p_devinfo;

} am_zsn700_tim_timing_dev_t;

/**
 * \brief ��ʼ��TIMΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��TIM(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t
am_zsn700_tim_timing_init (am_zsn700_tim_timing_dev_t              *p_dev,
                           const am_zsn700_tim_timing_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��TIM��ʱ����ʱ�����ʼ��TIM��ʱ���ܣ��ͷ������Դ
 *
 * \param[in] handle : am_zsn700_tim_timing_init() ��ʼ��������õ�Timer������
 *
 * \return ��
 */
void am_zsn700_tim_timing_deinit (am_timer_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_TIM_TIMING_H */

/* end of file */

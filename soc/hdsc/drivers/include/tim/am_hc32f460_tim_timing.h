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

#ifndef __AM_HC32F460_TIM_TIMING_H
#define __AM_HC32F460_TIM_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "hw/amhw_hc32f460_tim.h"

/**
 * \addtogroup am_hc32f460_if_tim_timing
 * \copydoc am_hc32f460_tim_timing.h
 * @{
 */

/**
 * \brief TIM��ʱ������ص��豸��Ϣ
 */
typedef struct am_hc32f460_tim_timing_devinfo {

    uint32_t                     tim_regbase;    /**< \brief TIM�Ĵ������ַ */
    uint8_t                      inum;           /**< \brief TIM�жϺ� */
    tim0_sync_clock_src_t        tim0_sync_clk_src; 
    tim0_async_clock_src_t       tim0_async_clk_src;
    tim0_counter_mode_t          tim0_counter_mode;     
    tim0_channel_t               channel_num;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                       (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                       (*pfn_plfm_deinit)(void);

} am_hc32f460_tim_timing_devinfo_t;

/**
 * \brief TIM��ʱ�����豸
 */
typedef struct am_hc32f460_tim_timing_dev {

    am_timer_serv_t timer_serv;         /**< \brief ��׼��ʱ(Timer)���� */

    void (*pfn_callback)(void *);       /**< \brief �ص����� */
    void  *p_arg;                       /**< \brief �ص��������û����� */

    uint16_t           prescale_to;     /**< \brief ������Ƶֵ  */
    uint16_t           prescale_in;     /**< \brief ʵ�ʷ�Ƶֵ  */

    /** \brief ָ��TIM(��ʱ����)�豸��Ϣ������ָ�� */
    const am_hc32f460_tim_timing_devinfo_t  *p_devinfo;

} am_hc32f460_tim_timing_dev_t;

/**
 * \brief ��ʼ��TIMΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��TIM(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��TIM(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t
am_hc32f460_tim_timing_init (am_hc32f460_tim_timing_dev_t           *p_dev,
                             const am_hc32f460_tim_timing_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��TIM��ʱ����ʱ�����ʼ��TIM��ʱ���ܣ��ͷ������Դ
 *
 * \param[in] handle : am_hc32f460_tim_timing_init() ��ʼ��������õ�Timer������
 *
 * \return ��
 */
void am_hc32f460_tim_timing_deinit (am_timer_handle_t handle);

void Timer01GCMA_IrqHandler(void *p_arg);
void Timer01GCMB_IrqHandler(void *p_arg);
void Timer02GCMA_IrqHandler(void *p_arg);
void Timer02GCMB_IrqHandler(void *p_arg);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_TIM_TIMING_H */

/* end of file */

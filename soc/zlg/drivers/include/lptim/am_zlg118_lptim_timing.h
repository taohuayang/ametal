/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief ��ʱ��LPTIM����������Timer������ʵ��
 *
 * 1. LPTIM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���Timer��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. һ��LPTIMģ�飬ֻ��һ����ʱͨ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27  zp, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG118_LPTIM_LPTIMING_H
#define __AM_ZLG118_LPTIM_LPTIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "hw/amhw_zlg118_lptim.h"

/**
 * \addtogroup am_zlg118_if_lptim_timing
 * \copydoc am_zlg118_lptim_timing.h
 * @{
 */

/**
 * \brief LPTIM��ʱ������ص��豸��Ϣ
 */
typedef struct am_zlg118_lptim_timing_devinfo {

    uint32_t               lptim_regbase;   /**< \brief LPTIM�Ĵ������ַ */

    uint8_t                inum;            /**< \brief LPTIM�жϺ� */

    amhw_zlg118_lptim_clk_src_t   clk_src;  /**< \brief ����/��ʱʱ��Դѡ�� */

    /** \brief ����/��ʱ����ѡ��.ѡ�����ʱ��Ҫ��ʼ�����ETR���ţ����ⲿ������½��ؽ��м��� */
    amhw_zlg118_lptim_function_t  fun_sel;

    amhw_zlg118_lptim_mode_t      mode;     /**< \brief ����/������ģʽѡ��  */

    am_bool_t                     gate_enable; /**< \brief �ſ�ʹ�ܿ���  */

    am_bool_t                     gate_state;  /**< \brief �ſ���Ч�ź�����  */

    /** \brief AM_FALSE:TOG,TOGNͬʱ���0    AM_TRUE: TOG,TOGN�����λ�෴���ź�*/
    am_bool_t                     tog_state;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                 (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                 (*pfn_plfm_deinit)(void);

} am_zlg118_lptim_timing_devinfo_t;

/**
 * \brief LPTIM��ʱ�����豸
 */
typedef struct am_zlg118_lptim_timing_dev {

    am_timer_serv_t timer_serv;         /**< \brief ��׼��ʱ(Timer)���� */

    void (*pfn_callback)(void *);       /**< \brief �ص����� */
    void  *p_arg;                       /**< \brief �ص��������û����� */

    /** \brief ָ��LPTIM(��ʱ����)�豸��Ϣ������ָ�� */
    const am_zlg118_lptim_timing_devinfo_t  *p_devinfo;

    uint32_t  clk_rate;                 /**< \brief ʱ��Ƶ�� */

    am_timer_info_t  timer_info;        /**< \brief ��ʱ������ */
} am_zlg118_lptim_timing_dev_t;

/**
 * \brief ��ʼ��LPTIMΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��LPTIM(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��LPTIM(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t
am_zlg118_lptim_timing_init (am_zlg118_lptim_timing_dev_t           *p_dev,
                               const am_zlg118_lptim_timing_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��LPTIM��ʱ����ʱ�����ʼ��LPTIM��ʱ���ܣ��ͷ������Դ
 *
 * \param[in] handle : am_zlg118_lptim_timing_init() ��ʼ��������õ�Timer������
 *
 * \return ��
 */
void am_zlg118_lptim_timing_deinit (am_timer_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_LPTIM_LPTIMING_H */

/* end of file */

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
 * \brief ��ʱ��ADTIM����������Timer������ʵ��
 *
 * 1. ADTIM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���Timer��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. һ��ADTIMģ�飬ֻ��һ����ʱͨ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-09  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_ADTIM_ADTIMING_H
#define __AM_HC32F460_ADTIM_ADTIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "hw/amhw_hc32f460_adtim.h"

/**
 * \addtogroup am_hc32f460_if_adtim_timing
 * \copydoc am_hc32f460_adtim_timing.h
 * @{
 */

/**
 * \brief ADTIM��ʱ������ص��豸��Ϣ
 */
typedef struct am_hc32f460_adtim_timing_devinfo {

    /**< \brief ADTIM�Ĵ������ַ */
    uint32_t                        adtim_regbase;

    /**< \brief ADTIM�жϺ� */
    uint8_t                         inum;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                            (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                            (*pfn_plfm_deinit)(void);

} am_hc32f460_adtim_timing_devinfo_t;

/**
 * \brief ADTIM��ʱ�����豸
 */
typedef struct am_hc32f460_adtim_timing_dev {

    am_timer_serv_t adtimer_serv;       /**< \brief ��׼��ʱ(Timer)���� */

    void (*pfn_callback)(void *);       /**< \brief �ص����� */
    void  *p_arg;                       /**< \brief �ص��������û����� */

    uint16_t           prescale_to;     /**< \brief ������Ƶֵ  */
    uint16_t           prescale_in;     /**< \brief ʵ�ʷ�Ƶֵ  */

    /** \brief ָ��ADTIM(��ʱ����)�豸��Ϣ������ָ�� */
    const am_hc32f460_adtim_timing_devinfo_t  *p_devinfo;

} am_hc32f460_adtim_timing_dev_t;

/**
 * \brief ��ʼ��ADTIMΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��ADTIM(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��ADTIM(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t
am_hc32f460_adtim_timing_init (am_hc32f460_adtim_timing_dev_t           *p_dev,
                               const am_hc32f460_adtim_timing_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��ADTIM��ʱ����ʱ�����ʼ��ADTIM��ʱ���ܣ��ͷ������Դ
 *
 * \param[in] handle : am_hc32f460_adtim_timing_init() ��ʼ��������õ�Timer������
 *
 * \return ��
 */
void am_hc32f460_adtim_timing_deinit (am_timer_handle_t handle);

void Timer61GCMA_IrqHandler(void *p_arg);
void Timer61GCMB_IrqHandler(void *p_arg);
void Timer61GCMC_IrqHandler(void *p_arg);
void Timer61GCMD_IrqHandler(void *p_arg);
void Timer61GCME_IrqHandler(void *p_arg);
void Timer61GCMF_IrqHandler(void *p_arg);
void Timer61GOV_IrqHandler(void *p_arg);
void Timer61GUD_IrqHandler(void *p_arg);
void Timer61GDT_IrqHandler(void *p_arg);
void Timer61SCMA_IrqHandler(void *p_arg);
void Timer61SCMB_IrqHandler(void *p_arg);

void Timer62GCMA_IrqHandler(void *p_arg);
void Timer62GCMB_IrqHandler(void *p_arg);
void Timer62GCMC_IrqHandler(void *p_arg);
void Timer62GCMD_IrqHandler(void *p_arg);
void Timer62GCME_IrqHandler(void *p_arg);
void Timer62GCMF_IrqHandler(void *p_arg);
void Timer62GOV_IrqHandler(void *p_arg);
void Timer62GUD_IrqHandler(void *p_arg);
void Timer62GDT_IrqHandler(void *p_arg);
void Timer62SCMA_IrqHandler(void *p_arg);
void Timer62SCMB_IrqHandler(void *p_arg);

void Timer63GCMA_IrqHandler(void *p_arg);
void Timer63GCMB_IrqHandler(void *p_arg);
void Timer63GCMC_IrqHandler(void *p_arg);
void Timer63GCMD_IrqHandler(void *p_arg);
void Timer63GCME_IrqHandler(void *p_arg);
void Timer63GCMF_IrqHandler(void *p_arg);
void Timer63GOV_IrqHandler(void *p_arg);
void Timer63GUD_IrqHandler(void *p_arg);
void Timer63GDT_IrqHandler(void *p_arg);
void Timer63SCMA_IrqHandler(void *p_arg);
void Timer63SCMB_IrqHandler(void *p_arg);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_ADTIM_ADTIMING_H */

/* end of file */

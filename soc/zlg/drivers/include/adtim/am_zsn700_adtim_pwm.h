/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsn700.cn/
*******************************************************************************/

/**
 * \file
 * \brief ��ʱ��ADTIM����������PWM��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-17  yrz, first implementation
 * \endinternal
 */

#ifndef __AM_ZSN700_ADTIM_PWM_H
#define __AM_ZSN700_ADTIM_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "hw/amhw_zsn700_adtim.h"

/**
 * \addtogroup am_zsn700_if_adtim_pwm
 * \copydoc am_zsn700_adtim_pwm.h
 * @{
 */

/* PWM������� */
#define  AM_ZSN700_ADTIM_PWM_OCPOLARITY_HIGH 0  /**< \brief �ߵ�ƽ��Ч */
#define  AM_ZSN700_ADTIM_PWM_OCPOLARITY_LOW  1  /**< \brief �͵�ƽ��Ч */

/**
 * \brief ͨ����ʶ��
 *
 * \note CHA �� CHB�����ڵ���PWM�����Ҳ�����ڻ���PWM�����
 */
#define  AM_ZSN700_ADTIM_PWM_CHA  0x00   /**< \brief PWMͨ��A��ʶ��*/
#define  AM_ZSN700_ADTIM_PWM_CHB  0x01   /**< \brief PWMͨ��B��ʶ��*/

/**
 * \brief ADTIMPWM���������ص�GPIO��Ϣ
 */
typedef struct am_zsn700_adtim_pwm_chaninfo {
    int8_t   channel;                  /**< \brief PWM��ʹ�õ�ͨ����ʶ�� */
    int8_t   gpio;                     /**< \brief PWM������õ�GPIO���� */
    uint32_t func;                     /**< \brief PWM���ܵ�GPIO��������ֵ */
    uint32_t dfunc;                    /**< \brief ����PWMģʽ��Ĭ��GPIO��������ֵ */
} am_zsn700_adtim_pwm_chaninfo_t;

/**
 * \brief ADTIMPWM���������ص��豸��Ϣ
 */
typedef struct am_zsn700_adtim_pwm_devinfo {
    uint32_t                     adtim_regbase;    /**< \brief ADTIM�Ĵ������ַ */

    uint8_t                      channels_num;   /**< \brief ʹ�õ�ͨ���������Ϊ2 */

    /** \brief ����PWMѡ��  1������PWM   0������PWM */
    uint8_t                     comp;

    /** \brief PWM�������,AM_ZSN700_LPTIM_PWM_OCPOLARITY_HIGH��AM_ZSN700_LPTIM_PWM_OCPOLARITY_LOW */
    uint8_t                     ocpolarity;

    am_zsn700_adtim_pwm_chaninfo_t  *p_chaninfo;     /**< \brief ָ��PWM���ͨ����Ϣ�ṹ�� */


    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void                      (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void                      (*pfn_plfm_deinit)(void);

} am_zsn700_adtim_pwm_devinfo_t;

/**
 * \brief ADTIMPWM��������豸�ṹ��
 */
typedef struct am_zsn700_adtim_pwm_dev {

    am_pwm_serv_t                      pwm_serv;   /**< \brief ��׼PWM���� */

    /** \brief ָ��ADTIM(PWM�������)�豸��Ϣ������ָ�� */
    const am_zsn700_adtim_pwm_devinfo_t *p_devinfo;

    uint8_t                            chan_max;   /**< \brief ��Ч�����ͨ����  */

} am_zsn700_adtim_pwm_dev_t;

/**
 * \brief ��ʼ��ADTIMΪPWM�������
 *
 * \param[in] p_dev     : ָ��ADTIM(PWM�������)�豸��ָ��
 * \param[in] p_devinfo : ָ��ADTIM(PWM�������)�豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t am_zsn700_adtim_pwm_init(
                    am_zsn700_adtim_pwm_dev_t           *p_dev,
                    const am_zsn700_adtim_pwm_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��ADTIMPWM�������ʱ�����ʼ��ADTIMPWM������ܣ��ͷ������Դ
 *
 * \param[in] handle : am_zsn700_adtim_pwm_init() ��ʼ��������õ�PWM������
 *
 * \return ��
 */
void am_zsn700_adtim_pwm_deinit (am_pwm_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_ADTIM_PWM_H */

/* end of file */

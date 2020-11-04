/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.hc32f460.cn/
*******************************************************************************/

/**
 * \file
 * \brief TIM����PWM��� �û������ļ�
 * \sa am_hwconf_hc32f460_adtim_pwm.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-16  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_hc32f460_adtim_pwm.h"
#include "am_clk.h"
#include "am_hc32f460_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_adtim_pwm
 * \copydoc am_hwconf_hc32f460_adtim_pwm.c
 * @{
 */
 
/*******************************************************************************
  ADTIM61 ����
*******************************************************************************/

/** \brief ADTIM61����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim61_pwm_init (void)
{
    am_clk_enable(CLK_TIMER6_1);
}

/** \brief ���ADTIM61ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim61_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMER6_1);
}

/** \brief ADTIM61����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_adtim_pwm_chaninfo_t __g_adtim61_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {
        AM_HC32F460_ADTIM_PWM_CHA,
        PIOE_9,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        AM_HC32F460_ADTIM_PWM_CHB,
        PIOE_8,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
};

/** \brief ADTIM6����PWM�豸��Ϣ */
const am_hc32f460_adtim_pwm_devinfo_t  __g_adtim61_pwm_devinfo = {
    HC32F460_TMR61_BASE,                           /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_adtim61_pwm_chaninfo_list),   /**< \brief �������ͨ������ */
    1,                                             /**< \brief ����PWMѡ��
                                                    *          1������PWM
                                                    *          0������PWM
                                                    */
    AM_HC32F460_ADTIM_PWM_OCPOLARITY_HIGH,         /**< \brief ������ */
    &__g_adtim61_pwm_chaninfo_list[0],             /**< \brief ͨ��������Ϣ�б� */
    __hc32f460_plfm_adtim61_pwm_init,              /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim61_pwm_deinit             /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM6����PWM�豸���� */
am_hc32f460_adtim_pwm_dev_t __g_adtim61_pwm_dev;

/** \brief adtim6 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_adtim61_pwm_inst_init (void)
{
    return am_hc32f460_adtim_pwm_init(&__g_adtim61_pwm_dev,
                                      &__g_adtim61_pwm_devinfo);
}

/** \brief adtim6 pwm ʵ�����ʼ�� */
void am_hc32f460_adtim61_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_adtim_pwm_deinit(handle);
}

/*******************************************************************************
  ADTIM62 ����
*******************************************************************************/

/** \brief ADTIM62����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim62_pwm_init (void)
{
    am_clk_enable(CLK_TIMER6_2);
}

/** \brief ���ADTIM62ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim62_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMER6_2);
}

/** \brief ADTIM61����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_adtim_pwm_chaninfo_t __g_adtim62_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {
        AM_HC32F460_ADTIM_PWM_CHA,
        PIOE_11,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        AM_HC32F460_ADTIM_PWM_CHB,
        PIOE_10,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
};

/** \brief ADTIM6����PWM�豸��Ϣ */
const am_hc32f460_adtim_pwm_devinfo_t  __g_adtim62_pwm_devinfo = {
    HC32F460_TMR62_BASE,                           /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_adtim62_pwm_chaninfo_list),   /**< \brief �������ͨ������ */
    1,                                             /**< \brief ����PWMѡ��
                                                    *          1������PWM
                                                    *          0������PWM
                                                    */
    AM_HC32F460_ADTIM_PWM_OCPOLARITY_HIGH,         /**< \brief ������ */
    &__g_adtim62_pwm_chaninfo_list[0],             /**< \brief ͨ��������Ϣ�б� */
    __hc32f460_plfm_adtim62_pwm_init,              /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim62_pwm_deinit             /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM6����PWM�豸���� */
am_hc32f460_adtim_pwm_dev_t __g_adtim62_pwm_dev;

/** \brief adtim6 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_adtim62_pwm_inst_init (void)
{
    return am_hc32f460_adtim_pwm_init(&__g_adtim62_pwm_dev,
                                      &__g_adtim62_pwm_devinfo);
}

/** \brief adtim6 pwm ʵ�����ʼ�� */
void am_hc32f460_adtim62_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_adtim_pwm_deinit(handle);
}

/*******************************************************************************
  ADTIM63 ����
*******************************************************************************/

/** \brief ADTIM63����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim63_pwm_init (void)
{
    am_clk_enable(CLK_TIMER6_3);
}

/** \brief ���ADTIM63ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim63_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMER6_3);
}

/** \brief ADTIM63����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_adtim_pwm_chaninfo_t __g_adtim63_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {
        AM_HC32F460_ADTIM_PWM_CHA,
        PIOE_13,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        AM_HC32F460_ADTIM_PWM_CHB,
        PIOE_12,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
};

/** \brief ADTIM6����PWM�豸��Ϣ */
const am_hc32f460_adtim_pwm_devinfo_t  __g_adtim63_pwm_devinfo = {
    HC32F460_TMR63_BASE,                           /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_adtim63_pwm_chaninfo_list),   /**< \brief �������ͨ������ */
    1,                                             /**< \brief ����PWMѡ��
                                                    *          1������PWM
                                                    *          0������PWM
                                                    */
    AM_HC32F460_ADTIM_PWM_OCPOLARITY_HIGH,         /**< \brief ������ */
    &__g_adtim63_pwm_chaninfo_list[0],             /**< \brief ͨ��������Ϣ�б� */
    __hc32f460_plfm_adtim63_pwm_init,              /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim63_pwm_deinit             /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM6����PWM�豸���� */
am_hc32f460_adtim_pwm_dev_t __g_adtim63_pwm_dev;

/** \brief adtim6 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_adtim63_pwm_inst_init (void)
{
    return am_hc32f460_adtim_pwm_init(&__g_adtim63_pwm_dev,
                                      &__g_adtim63_pwm_devinfo);
}

/** \brief adtim6 pwm ʵ�����ʼ�� */
void am_hc32f460_adtim63_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_adtim_pwm_deinit(handle);
}

/**
 * @}
 */

/* end of file */

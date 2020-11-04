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
 * \sa am_hwconf_hc32f460_tim_pwm.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-16  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32f460.h"
#include "am_gpio.h"
#include "am_hc32f460_timea_pwm.h"
#include "am_clk.h"
#include "am_hc32f460_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_tim_pwm
 * \copydoc am_hwconf_hc32f460_tim_pwm.c
 * @{
 */

/*******************************************************************************
  TIMEA1 ����
*******************************************************************************/

/** \brief TIMA1����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_timea1_pwm_init (void)
{
    am_clk_enable(CLK_TIMERA_1);    
    am_clk_enable(CLK_PTDIS);    
}

/** \brief ���TIMA1ƽ̨��ʼ�� */
void __hc32f460_plfm_timea1_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMERA_1);    
    am_clk_disable(CLK_PTDIS);    
}

/** \brief TIMA1����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_timea_pwm_chaninfo_t __g_timea1_pwm_chaninfo_list[] = {

    /** \brief ͨ��1�������� */
    {
        TIMERA_CH1,
        PIOE_9,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        TIMERA_CH2,
        PIOE_11,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��3�������� */
    {
        TIMERA_CH3,
        PIOE_13,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },   
    /** \brief ͨ��4�������� */
    {
        TIMERA_CH4,
        PIOE_14,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��5�������� */
    {
        TIMERA_CH5,
        PIOE_8,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��6�������� */
    {
        TIMERA_CH6,
        PIOE_10,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��7�������� */
    {
        TIMERA_CH7,
        PIOE_12,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��8�������� */
    {
        TIMERA_CH8,
        PIOE_15,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },    
};

/** \brief TIMA1����PWM�豸��Ϣ */
const am_hc32f460_timea_pwm_devinfo_t  __g_timea1_pwm_devinfo = {
    HC32F460_TMRA1_BASE,                           /**< \brief TIMA1�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_timea1_pwm_chaninfo_list),    /**< \brief �������ͨ������ */
    0,                                             /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                                    *          1��ʹ��
                                                    *          0��ʧ��
                                                    */
    &__g_timea1_pwm_chaninfo_list[0],              /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32F460_TIMEA_TYPE_TIM0,                 /**< \brief ��ʱ������ */
    __hc32f460_plfm_timea1_pwm_init,               /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea1_pwm_deinit              /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMA1����PWM�豸���� */
am_hc32f460_timea_pwm_dev_t __g_timea1_pwm_dev;

/** \brief timA1 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_timea1_pwm_inst_init (void)
{
    return am_hc32f460_timea_pwm_init(&__g_timea1_pwm_dev,
                               &__g_timea1_pwm_devinfo);
}

/** \brief timA1 pwm ʵ�����ʼ�� */
void am_hc32f460_timea1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_timea_pwm_deinit(handle);
}

/*******************************************************************************
  TIMEA2 ����
*******************************************************************************/

/** \brief TIMA2����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_timea2_pwm_init (void)
{
    am_clk_enable(CLK_TIMERA_2);    
    am_clk_enable(CLK_PTDIS);    
}

/** \brief ���TIMA2ƽ̨��ʼ�� */
void __hc32f460_plfm_timea2_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMERA_2);    
    am_clk_disable(CLK_PTDIS);    
}

/** \brief TIMA2����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_timea_pwm_chaninfo_t __g_timea2_pwm_chaninfo_list[] = {

    /** \brief ͨ��1�������� */
    {
        TIMERA_CH1,
        PIOA_0,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        TIMERA_CH2,
        PIOA_1,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��3�������� */
    {
        TIMERA_CH3,
        PIOA_2,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },   
    /** \brief ͨ��4�������� */
    {
        TIMERA_CH4,
        PIOA_3,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��5�������� */
    {
        TIMERA_CH5,
        PIOA_13,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��6�������� */
    {
        TIMERA_CH6,
        PIOA_14,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��7�������� */
    {
        TIMERA_CH7,
        PIOC_2,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��8�������� */
    {
        TIMERA_CH8,
        PIOC_3,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },    
};

/** \brief TIMA2����PWM�豸��Ϣ */
const am_hc32f460_timea_pwm_devinfo_t  __g_timea2_pwm_devinfo = {
    HC32F460_TMRA2_BASE,                           /**< \brief TIM3�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_timea2_pwm_chaninfo_list),    /**< \brief �������ͨ������ */
    0,                                             /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                                    *          1��ʹ��
                                                    *          0��ʧ��
                                                    */
    &__g_timea2_pwm_chaninfo_list[0],              /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32F460_TIMEA_TYPE_TIM0,                 /**< \brief ��ʱ������ */
    __hc32f460_plfm_timea2_pwm_init,               /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea2_pwm_deinit              /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMA2����PWM�豸���� */
am_hc32f460_timea_pwm_dev_t __g_timea2_pwm_dev;

/** \brief TIMA2 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_timea2_pwm_inst_init (void)
{
    return am_hc32f460_timea_pwm_init(&__g_timea2_pwm_dev,
                                      &__g_timea2_pwm_devinfo);
}

/** \brief TIMA2 pwm ʵ�����ʼ�� */
void am_hc32f460_timea2_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_timea_pwm_deinit(handle);
}


/*******************************************************************************
  TIMEA3 ����
*******************************************************************************/

/** \brief TIMA3����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_timea3_pwm_init (void)
{
    am_clk_enable(CLK_TIMERA_3);    
    am_clk_enable(CLK_PTDIS);    
}

/** \brief ���TIMA3ƽ̨��ʼ�� */
void __hc32f460_plfm_timea3_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMERA_3);    
    am_clk_disable(CLK_PTDIS);    
}

/** \brief TIMA3����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_timea_pwm_chaninfo_t __g_timea3_pwm_chaninfo_list[] = {

    /** \brief ͨ��1�������� */
    {
        TIMERA_CH1,
        PIOC_6,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        TIMERA_CH2,
        PIOB_5,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��3�������� */
    {
        TIMERA_CH3,
        PIOB_0,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },   
    /** \brief ͨ��4�������� */
    {
        TIMERA_CH4,
        PIOB_1,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��5�������� */
    {
        TIMERA_CH5,
        PIOE_2,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��6�������� */
    {
        TIMERA_CH6,
        PIOE_3,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��7�������� */
    {
        TIMERA_CH7,
        PIOE_4,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��8�������� */
    {
        TIMERA_CH8,
        PIOE_5,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },    
};

/** \brief TIMA3����PWM�豸��Ϣ */
const am_hc32f460_timea_pwm_devinfo_t  __g_timea3_pwm_devinfo = {
    HC32F460_TMRA3_BASE,                           /**< \brief TIM3�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_timea3_pwm_chaninfo_list),    /**< \brief �������ͨ������ */
    0,                                             /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                                    *          1��ʹ��
                                                    *          0��ʧ��
                                                    */
    &__g_timea3_pwm_chaninfo_list[0],               /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32F460_TIMEA_TYPE_TIM0,                 /**< \brief ��ʱ������ */
    __hc32f460_plfm_timea3_pwm_init,               /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea3_pwm_deinit              /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMA3����PWM�豸���� */
am_hc32f460_timea_pwm_dev_t __g_timea3_pwm_dev;

/** \brief TIMA3 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_timea3_pwm_inst_init (void)
{
    return am_hc32f460_timea_pwm_init(&__g_timea3_pwm_dev,
                                      &__g_timea3_pwm_devinfo);
}

/** \brief TIMA3 pwm ʵ�����ʼ�� */
void am_hc32f460_timea3_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_timea_pwm_deinit(handle);
}

/*******************************************************************************
  TIMEA4 ����
*******************************************************************************/

/** \brief TIMA4����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_timea4_pwm_init (void)
{
    am_clk_enable(CLK_TIMERA_4);    
    am_clk_enable(CLK_PTDIS);    
}

/** \brief ���TIMA4ƽ̨��ʼ�� */
void __hc32f460_plfm_timea4_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMERA_4);    
    am_clk_disable(CLK_PTDIS);    
}

/** \brief TIMA4����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_timea_pwm_chaninfo_t __g_timea4_pwm_chaninfo_list[] = {

    /** \brief ͨ��1�������� */
    {
        TIMERA_CH1,
        PIOD_12,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        TIMERA_CH2,
        PIOD_13,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��3�������� */
    {
        TIMERA_CH3,
        PIOD_14,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },   
    /** \brief ͨ��4�������� */
    {
        TIMERA_CH4,
        PIOD_15,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��5�������� */
    {
        TIMERA_CH5,
        PIOC_14,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��6�������� */
    {
        TIMERA_CH6,
        PIOC_15,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��7�������� */
    {
        TIMERA_CH7,
        PIOH_2,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��8�������� */
    {
        TIMERA_CH8,
        PIOC_13,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },    
};

/** \brief TIMA4����PWM�豸��Ϣ */
const am_hc32f460_timea_pwm_devinfo_t  __g_timea4_pwm_devinfo = {
    HC32F460_TMRA4_BASE,                           /**< \brief TIMA4�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_timea4_pwm_chaninfo_list),    /**< \brief �������ͨ������ */
    0,                                             /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                                    *          1��ʹ��
                                                    *          0��ʧ��
                                                    */
    &__g_timea4_pwm_chaninfo_list[0],              /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32F460_TIMEA_TYPE_TIM0,                 /**< \brief ��ʱ������ */
    __hc32f460_plfm_timea4_pwm_init,               /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea4_pwm_deinit              /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMA4����PWM�豸���� */
am_hc32f460_timea_pwm_dev_t __g_timea4_pwm_dev;

/** \brief TIMA4 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_timea4_pwm_inst_init (void)
{
    return am_hc32f460_timea_pwm_init(&__g_timea4_pwm_dev,
                                      &__g_timea4_pwm_devinfo);
}

/** \brief TIMA4 pwm ʵ�����ʼ�� */
void am_hc32f460_timea4_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_timea_pwm_deinit(handle);
}

/*******************************************************************************
  TIMEA5 ����
*******************************************************************************/

/** \brief TIMEA5����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_timea5_pwm_init (void)
{
    am_clk_enable(CLK_TIMERA_5);    
    am_clk_enable(CLK_PTDIS);    
}

/** \brief ���TIMEA5ƽ̨��ʼ�� */
void __hc32f460_plfm_timea5_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMERA_5);    
    am_clk_disable(CLK_PTDIS);    
}

/** \brief TIMEA5����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_timea_pwm_chaninfo_t __g_timea5_pwm_chaninfo_list[] = {

    /** \brief ͨ��1�������� */
    {
        TIMERA_CH1,
        PIOC_10,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        TIMERA_CH2,
        PIOC_11,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��3�������� */
    {
        TIMERA_CH3,
        PIOC_12,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },   
    /** \brief ͨ��4�������� */
    {
        TIMERA_CH4,
        PIOD_0,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��5�������� */
    {
        TIMERA_CH5,
        PIOD_12,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��6�������� */
    {
        TIMERA_CH6,
        PIOD_13,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��7�������� */
    {
        TIMERA_CH7,
        PIOD_14,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��8�������� */
    {
        TIMERA_CH8,
        PIOD_15,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },    
};

/** \brief TIMEA5����PWM�豸��Ϣ */
const am_hc32f460_timea_pwm_devinfo_t  __g_timea5_pwm_devinfo = {
    HC32F460_TMRA5_BASE,                           /**< \brief TIM4�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_timea5_pwm_chaninfo_list),    /**< \brief �������ͨ������ */
    0,                                             /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                                    *          1��ʹ��
                                                    *          0��ʧ��
                                                    */
    &__g_timea5_pwm_chaninfo_list[0],              /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32F460_TIMEA_TYPE_TIM0,                 /**< \brief ��ʱ������ */
    __hc32f460_plfm_timea5_pwm_init,               /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea5_pwm_deinit              /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMEA5����PWM�豸���� */
am_hc32f460_timea_pwm_dev_t __g_timea5_pwm_dev;

/** \brief TIMEA5 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_timea5_pwm_inst_init (void)
{
    return am_hc32f460_timea_pwm_init(&__g_timea5_pwm_dev,
                                      &__g_timea5_pwm_devinfo);
}

/** \brief TIMEA5 pwm ʵ�����ʼ�� */
void am_hc32f460_timea5_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_timea_pwm_deinit(handle);
}

/*******************************************************************************
  TIMEA6 ����
*******************************************************************************/

/** \brief TIMEA6����PWM��� ƽ̨��ʼ�� */
void __hc32f460_plfm_timea6_pwm_init (void)
{
    am_clk_enable(CLK_TIMERA_6);    
    am_clk_enable(CLK_PTDIS);    
}

/** \brief ���TIMEA6ƽ̨��ʼ�� */
void __hc32f460_plfm_timea6_pwm_deinit (void)
{
    am_clk_disable(CLK_TIMERA_6);    
    am_clk_disable(CLK_PTDIS);    
}

/** \brief TIMEA6����PWM���ܵ�����������Ϣ�б� */
am_hc32f460_timea_pwm_chaninfo_t __g_timea6_pwm_chaninfo_list[] = {

    /** \brief ͨ��1�������� */
    {
        TIMERA_CH1,
        PIOD_8,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        TIMERA_CH2,
        PIOD_9,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��3�������� */
    {
        TIMERA_CH3,
        PIOD_10,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },   
    /** \brief ͨ��4�������� */
    {
        TIMERA_CH4,
        PIOD_11,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��5�������� */
    {
        TIMERA_CH5,
        PIOD_1,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��6�������� */
    {
        TIMERA_CH6,
        PIOD_2,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��7�������� */
    {
        TIMERA_CH7,
        PIOD_3,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��8�������� */
    {
        TIMERA_CH8,
        PIOD_4,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA1),
        AM_GPIO_INPUT
    },    
};

/** \brief TIMEA6����PWM�豸��Ϣ */
const am_hc32f460_timea_pwm_devinfo_t  __g_timea6_pwm_devinfo = {
    HC32F460_TMRA6_BASE,                           /**< \brief TIMEA6�Ĵ�����Ļ���ַ */
    AM_NELEMENTS(__g_timea6_pwm_chaninfo_list),    /**< \brief �������ͨ������ */
    0,                                             /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                                    *          1��ʹ��
                                                    *          0��ʧ��
                                                    */
    &__g_timea6_pwm_chaninfo_list[0],              /**< \brief ͨ��������Ϣ�б�        */
    AMHW_HC32F460_TIMEA_TYPE_TIM0,                 /**< \brief ��ʱ������ */
    __hc32f460_plfm_timea6_pwm_init,               /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea6_pwm_deinit              /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMEA6����PWM�豸���� */
am_hc32f460_timea_pwm_dev_t __g_timea6_pwm_dev;

/** \brief TIMEA6 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_hc32f460_timea6_pwm_inst_init (void)
{
    return am_hc32f460_timea_pwm_init(&__g_timea6_pwm_dev,
                                      &__g_timea6_pwm_devinfo);
}

/** \brief TIMEA6 pwm ʵ�����ʼ�� */
void am_hc32f460_timea6_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_hc32f460_timea_pwm_deinit(handle);
}

/**
 * @}
 */

/* end of file */

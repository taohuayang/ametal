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
 * \brief TIM ���ڲ����ܵ��û������ļ�
 * \sa am_hwconf_hc32f460_tim_cap.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-12  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc32f460.h"
#include "am_hc32f460_timea_cap.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_hc32f460_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_tim_cap
 * \copydoc am_hwconf_hc32f460_tim_cap.c
 * @{
 */
/*******************************************************************************
  TIMEA1 ����
*******************************************************************************/

/** \brief TIMEA1���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_timea1_cap_init (void)
{
    am_clk_enable(CLK_TIMERA_1);
    am_clk_enable(CLK_PTDIS);      
}

/** \brief ���TIMEA1ƽ̨��ʼ�� */
void __hc32f460_plfm_timea1_cap_deinit (void)
{
    am_clk_disable(CLK_TIMERA_1);
    am_clk_disable(CLK_PTDIS);        
}

/** \brief TIMEA1���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_timea_cap_ioinfo_t __g_timea1_cap_ioinfo_list[] = {
    /** \brief ͨ��0 */
    {
        TIMERA_CH1,
        PIOE_9,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIMA0),
        AM_GPIO_INPUT
    },

    /** \brief ͨ��1 */
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

/** \brief TIM0���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_timea_cap_devinfo_t  __g_timea1_cap_devinfo = {
    HC32F460_TMRA1_BASE,                    /**< \brief TIMEA1�Ĵ�����Ļ���ַ */
    INUM_TIMERA_1,                          /**< \brief TIMEA1�жϱ�� */
    AMHW_HC32F460_TIMEA_CLK_DIV1024,        /**< \brief ʱ�ӷ�Ƶϵ�� */
    8,                                      /**< \brief 8������ͨ�� */
    0,                                      /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                             *          1��ʹ��
                                             *          0��ʧ��
                                             */

    &__g_timea1_cap_ioinfo_list[0],
    __hc32f460_plfm_timea1_cap_init,         /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea1_cap_deinit        /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMEA1���ڲ����ܵ��豸���� */
am_hc32f460_timea_cap_dev_t  __g_timea1_cap_dev;

/** \brief timea1 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_timea1_cap_inst_init (void)
{
    return am_hc32f460_timea_cap_init(&__g_timea1_cap_dev,
                                      &__g_timea1_cap_devinfo);
}

/** \brief timea1 capʵ�����ʼ�� */
void am_hc32f460_timea1_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_timea_cap_deinit(handle);
}

/*******************************************************************************
  TIMEA2 ����
*******************************************************************************/

/** \brief TIMEA2���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_timea2_cap_init (void)
{
    am_clk_enable(CLK_TIMERA_2);
    am_clk_enable(CLK_PTDIS);      
}

/** \brief ���TIMEA2ƽ̨��ʼ�� */
void __hc32f460_plfm_timea2_cap_deinit (void)
{
    am_clk_disable(CLK_TIMERA_2);
    am_clk_disable(CLK_PTDIS);        
}

/** \brief TIMEA2���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_timea_cap_ioinfo_t __g_timea2_cap_ioinfo_list[] = {
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

/** \brief TIM0���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_timea_cap_devinfo_t  __g_timea2_cap_devinfo = {
    HC32F460_TMRA2_BASE,                    /**< \brief TIMEA1�Ĵ�����Ļ���ַ */
    INUM_TIMERA_2,                          /**< \brief TIMEA1�жϱ�� */
    AMHW_HC32F460_TIMEA_CLK_DIV256,         /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                      /**< \brief 2������ͨ�� */
    0,                                      /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                             *          1��ʹ��
                                             *          0��ʧ��
                                             */

    &__g_timea2_cap_ioinfo_list[0],
    __hc32f460_plfm_timea2_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea2_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMEA1���ڲ����ܵ��豸���� */
am_hc32f460_timea_cap_dev_t  __g_timea2_cap_dev;

/** \brief timea1 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_timea2_cap_inst_init (void)
{
    return am_hc32f460_timea_cap_init(&__g_timea2_cap_dev,
                                      &__g_timea2_cap_devinfo);
}

/** \brief timea1 capʵ�����ʼ�� */
void am_hc32f460_timea2_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_timea_cap_deinit(handle);
}

/*******************************************************************************
  TIMEA3 ����
*******************************************************************************/

/** \brief TIMEA3���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_timea3_cap_init (void)
{
    am_clk_enable(CLK_TIMERA_3);
    am_clk_enable(CLK_PTDIS);      
}

/** \brief ���TIMEA3ƽ̨��ʼ�� */
void __hc32f460_plfm_timea3_cap_deinit (void)
{
    am_clk_disable(CLK_TIMERA_3);
    am_clk_disable(CLK_PTDIS);        
}

/** \brief TIMEA3���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_timea_cap_ioinfo_t __g_timea3_cap_ioinfo_list[] = {
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

/** \brief TIM3���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_timea_cap_devinfo_t  __g_timea3_cap_devinfo = {
    HC32F460_TMRA3_BASE,                    /**< \brief TIMEA1�Ĵ�����Ļ���ַ */
    INUM_TIMERA_3,                          /**< \brief TIMEA1�жϱ�� */
    AMHW_HC32F460_TIMEA_CLK_DIV256,         /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                      /**< \brief 2������ͨ�� */
    0,                                      /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                             *          1��ʹ��
                                             *          0��ʧ��
                                             */

    &__g_timea3_cap_ioinfo_list[0],
    __hc32f460_plfm_timea3_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea3_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMEA1���ڲ����ܵ��豸���� */
am_hc32f460_timea_cap_dev_t  __g_timea3_cap_dev;

/** \brief timea1 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_timea3_cap_inst_init (void)
{
    return am_hc32f460_timea_cap_init(&__g_timea3_cap_dev,
                                      &__g_timea3_cap_devinfo);
}

/** \brief timea1 capʵ�����ʼ�� */
void am_hc32f460_timea3_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_timea_cap_deinit(handle);
}

/*******************************************************************************
  TIMEA4 ����
*******************************************************************************/

/** \brief TIMEA4���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_timea4_cap_init (void)
{
    am_clk_enable(CLK_TIMERA_4);
    am_clk_enable(CLK_PTDIS);      
}

/** \brief ���TIMEA3ƽ̨��ʼ�� */
void __hc32f460_plfm_timea4_cap_deinit (void)
{
    am_clk_disable(CLK_TIMERA_4);
    am_clk_disable(CLK_PTDIS);        
}

/** \brief TIMEA3���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_timea_cap_ioinfo_t __g_timea4_cap_ioinfo_list[] = {
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

/** \brief TIM3���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_timea_cap_devinfo_t  __g_timea4_cap_devinfo = {
    HC32F460_TMRA4_BASE,                    /**< \brief TIMEA1�Ĵ�����Ļ���ַ */
    INUM_TIMERA_4,                          /**< \brief TIMEA1�жϱ�� */
    AMHW_HC32F460_TIMEA_CLK_DIV256,         /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                      /**< \brief 2������ͨ�� */
    0,                                      /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                             *          1��ʹ��
                                             *          0��ʧ��
                                             */

    &__g_timea4_cap_ioinfo_list[0],
    __hc32f460_plfm_timea4_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea4_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMEA1���ڲ����ܵ��豸���� */
am_hc32f460_timea_cap_dev_t  __g_timea4_cap_dev;

/** \brief timea4 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_timea4_cap_inst_init (void)
{
    return am_hc32f460_timea_cap_init(&__g_timea4_cap_dev,
                                      &__g_timea4_cap_devinfo);
}

/** \brief timea4 capʵ�����ʼ�� */
void am_hc32f460_timea4_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_timea_cap_deinit(handle);
}

/*******************************************************************************
  TIMEA5 ����
*******************************************************************************/

/** \brief TIMEA5���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_timea5_cap_init (void)
{
    am_clk_enable(CLK_TIMERA_5);
    am_clk_enable(CLK_PTDIS);      
}

/** \brief ���TIMEA5ƽ̨��ʼ�� */
void __hc32f460_plfm_timea5_cap_deinit (void)
{
    am_clk_disable(CLK_TIMERA_5);
    am_clk_disable(CLK_PTDIS);        
}

/** \brief TIMEA5���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_timea_cap_ioinfo_t __g_timea5_cap_ioinfo_list[] = {
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

/** \brief TIM3���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_timea_cap_devinfo_t  __g_timea5_cap_devinfo = {
    HC32F460_TMRA5_BASE,                    /**< \brief TIMEA1�Ĵ�����Ļ���ַ */
    INUM_TIMERA_5,                          /**< \brief TIMEA1�жϱ�� */
    AMHW_HC32F460_TIMEA_CLK_DIV256,         /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                      /**< \brief 2������ͨ�� */
    0,                                      /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                             *          1��ʹ��
                                             *          0��ʧ��
                                             */

    &__g_timea5_cap_ioinfo_list[0],
    __hc32f460_plfm_timea5_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea5_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMEA1���ڲ����ܵ��豸���� */
am_hc32f460_timea_cap_dev_t  __g_timea5_cap_dev;

/** \brief timea5 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_timea5_cap_inst_init (void)
{
    return am_hc32f460_timea_cap_init(&__g_timea5_cap_dev,
                                      &__g_timea5_cap_devinfo);
}

/** \brief timea5 capʵ�����ʼ�� */
void am_hc32f460_timea5_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_timea_cap_deinit(handle);
}

/*******************************************************************************
  TIMEA6 ����
*******************************************************************************/

/** \brief TIMEA6���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_timea6_cap_init (void)
{
    am_clk_enable(CLK_TIMERA_6);
    am_clk_enable(CLK_PTDIS);      
}

/** \brief ���TIMEA6ƽ̨��ʼ�� */
void __hc32f460_plfm_timea6_cap_deinit (void)
{
    am_clk_disable(CLK_TIMERA_6);
    am_clk_disable(CLK_PTDIS);        
}

/** \brief TIMEA6���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_timea_cap_ioinfo_t __g_timea6_cap_ioinfo_list[] = {
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

/** \brief TIM3���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_timea_cap_devinfo_t  __g_timea6_cap_devinfo = {
    HC32F460_TMRA6_BASE,                    /**< \brief TIMEA1�Ĵ�����Ļ���ַ */
    INUM_TIMERA_6,                          /**< \brief TIMEA1�жϱ�� */
    AMHW_HC32F460_TIMEA_CLK_DIV256,         /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                      /**< \brief 2������ͨ�� */
    0,                                      /**< \brief �Ƿ�ʹ��ͬ��ģʽ
                                             *          1��ʹ��
                                             *          0��ʧ��
                                             */

    &__g_timea6_cap_ioinfo_list[0],
    __hc32f460_plfm_timea6_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_timea6_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIMEA1���ڲ����ܵ��豸���� */
am_hc32f460_timea_cap_dev_t  __g_timea6_cap_dev;

/** \brief timea6 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_timea6_cap_inst_init (void)
{
    return am_hc32f460_timea_cap_init(&__g_timea6_cap_dev,
                                      &__g_timea6_cap_devinfo);
}

/** \brief timea6 capʵ�����ʼ�� */
void am_hc32f460_timea6_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_timea_cap_deinit(handle);
}

/**
 * @}
 */

/* end of file */

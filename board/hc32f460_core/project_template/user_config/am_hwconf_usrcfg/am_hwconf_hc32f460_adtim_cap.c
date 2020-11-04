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
#include "am_hc32f460_adtim_cap.h"
#include "am_hc32f460_adtim_cap.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_hc32f460_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_tim_cap
 * \copydoc am_hwconf_hc32f460_tim_cap.c
 * @{
 */
/*******************************************************************************
  ADTIM61 ����
*******************************************************************************/
/** \brief ADTIM61���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim61_cap_init (void)
{
    am_clk_enable(CLK_TIMER6_1);
}

/** \brief ���ADTIM61ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim61_cap_deinit (void)
{
    am_clk_disable(CLK_TIMER6_1);
}

/** \brief ADTIM6���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_adtim_cap_ioinfo_t __g_adtim61_cap_ioinfo_list[] = {
    /** \brief ͨ��1�������� */
    {
        AM_HC32F460_ADTIM_CAP_CHA,
        PIOE_9,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */    
    {
        AM_HC32F460_ADTIM_CAP_CHB,
        PIOE_8,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),
        AM_GPIO_INPUT
    },
};

/** \brief ADTIM6���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_adtim_cap_devinfo_t  __g_adtim61_cap_devinfo = {
    HC32F460_TMR61_BASE,                   /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    INUM_TIMER6_1,                         /**< \brief ADTIM6�жϱ�� */
    AMHW_HC32F460_ADTIM_PCLK_DIV1024,      /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                     /**< \brief 2������ͨ�� */

    &__g_adtim61_cap_ioinfo_list[0],       /**< \brief ����������Ϣ�б� */
    __hc32f460_plfm_adtim61_cap_init,      /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim61_cap_deinit     /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM6���ڲ����ܵ��豸���� */
am_hc32f460_adtim_cap_dev_t  __g_adtim61_cap_dev;

/** \brief adtim61 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_adtim61_cap_inst_init (void)
{
    return am_hc32f460_adtim_cap_init(&__g_adtim61_cap_dev,
                                      &__g_adtim61_cap_devinfo);
}

/** \brief adtim61 capʵ�����ʼ�� */
void am_hc32f460_adtim61_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_adtim_cap_deinit(handle);
}

/*******************************************************************************
  ADTIM62 ����
*******************************************************************************/
/** \brief ADTIM62���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim62_cap_init (void)
{
    am_clk_enable(CLK_TIMER6_2);
}

/** \brief ���ADTIM62ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim62_cap_deinit (void)
{
    am_clk_disable(CLK_TIMER6_2);
}

/** \brief ADTIM62���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_adtim_cap_ioinfo_t __g_adtim62_cap_ioinfo_list[] = {
    /** \brief ͨ��1�������� */
    {
        AM_HC32F460_ADTIM_CAP_CHA,
        PIOE_11,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        AM_HC32F460_ADTIM_CAP_CHB,
        PIOE_10,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },

};

/** \brief ADTIM6���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_adtim_cap_devinfo_t  __g_adtim62_cap_devinfo = {
    HC32F460_TMR62_BASE,                   /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    INUM_TIMER6_2,                         /**< \brief ADTIM6�жϱ�� */
    AMHW_HC32F460_ADTIM_PCLK_DIV16,        /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                     /**< \brief 2������ͨ�� */

    &__g_adtim62_cap_ioinfo_list[0],       /**< \brief ����������Ϣ�б� */
    __hc32f460_plfm_adtim62_cap_init,      /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim62_cap_deinit     /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM6���ڲ����ܵ��豸���� */
am_hc32f460_adtim_cap_dev_t  __g_adtim62_cap_dev;

/** \brief adtim62 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_adtim62_cap_inst_init (void)
{
    return am_hc32f460_adtim_cap_init(&__g_adtim62_cap_dev,
                                      &__g_adtim62_cap_devinfo);
}

/** \brief adtim61 capʵ�����ʼ�� */
void am_hc32f460_adtim62_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_adtim_cap_deinit(handle);
}

/*******************************************************************************
  ADTIM63 ����
*******************************************************************************/
/** \brief ADTIM63���ڲ����ܵ�ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim63_cap_init (void)
{
    am_clk_enable(CLK_TIMER6_3);
}

/** \brief ���ADTIM63ƽ̨��ʼ�� */
void __hc32f460_plfm_adtim63_cap_deinit (void)
{
    am_clk_disable(CLK_TIMER6_3);
}

/** \brief ADTIM62���ڲ����ܵ�����������Ϣ�б� */
am_hc32f460_adtim_cap_ioinfo_t __g_adtim63_cap_ioinfo_list[] = {
    /** \brief ͨ��1�������� */
    {
        AM_HC32F460_ADTIM_CAP_CHA,
        PIOE_13,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
    /** \brief ͨ��2�������� */
    {
        AM_HC32F460_ADTIM_CAP_CHB,
        PIOE_12,
        GPIO_AFIO(AMHW_HC32F460_AFIO_TIM6),        
        AM_GPIO_INPUT
    },
};

/** \brief ADTIM6���ڲ����ܵ��豸��Ϣ */
const am_hc32f460_adtim_cap_devinfo_t  __g_adtim63_cap_devinfo = {
    HC32F460_TMR63_BASE,                   /**< \brief ADTIM6�Ĵ�����Ļ���ַ */
    INUM_TIMER6_3,                         /**< \brief ADTIM6�жϱ�� */
    AMHW_HC32F460_ADTIM_PCLK_DIV16,        /**< \brief ʱ�ӷ�Ƶϵ�� */
    2,                                     /**< \brief 2������ͨ�� */

    &__g_adtim63_cap_ioinfo_list[0],       /**< \brief ����������Ϣ�б� */
    __hc32f460_plfm_adtim63_cap_init,      /**< \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_adtim63_cap_deinit     /**< \brief ƽ̨���ʼ������ */
};

/** \brief ADTIM63���ڲ����ܵ��豸���� */
am_hc32f460_adtim_cap_dev_t  __g_adtim63_cap_dev;

/** \brief adtim63 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_hc32f460_adtim63_cap_inst_init (void)
{
    return am_hc32f460_adtim_cap_init(&__g_adtim63_cap_dev,
                                      &__g_adtim63_cap_devinfo);
}

/** \brief adtim63 capʵ�����ʼ�� */
void am_hc32f460_adtim63_cap_inst_deinit (am_cap_handle_t handle)
{
    am_hc32f460_adtim_cap_deinit(handle);
}

/**
 * @}
 */

/* end of file */

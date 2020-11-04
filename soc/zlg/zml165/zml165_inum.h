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
 * \brief ZML165 �жϺŶ���
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  sdy, first implementation
 * \endinternal
 */

#ifndef __ZLG_INUM_H
#define __ZLG_INUM_H

#ifdef __cplusplus
extern "C" {

#endif

#include "ametal.h"

/**
 * \addtogroup zml165_if_inum
 * \copydoc zml165_inum.h
 * @{
 */

/**
 * \name ZML165 CPU �жϺ�
 * @{
 */

#define INUM_WWDT                 0    /**< \brief ���ڶ�ʱ���ж� */
#define INUM_PVD                  1    /**< \brief ��Դ��ѹ����ж� */

#define INUM_FLASH                3    /**< \brief ����ȫ���ж� */
#define INUM_RCC_CRS              4    /**< \brief RCC��CRS*ȫ���ж� */
#define INUM_EXTI0_1              5    /**< \brief EXTI��[1��0]�ж� */
#define INUM_EXTI2_3              6    /**< \brief EXTI��[3��2]�ж� */
#define INUM_EXTI4_15             7    /**< \brief EXTI��[15��4]�ж� */

#define INUM_DMA1_1               9    /**< \brief DMA1ͨ��1ȫ���ж� */
#define INUM_DMA1_2_3             10   /**< \brief DMA1ͨ��2��3ȫ���ж� */
#define INUM_DMA1_4_5             11   /**< \brief DMA1ͨ��4��5ȫ���ж� */
#define INUM_ADC_COMP             12   /**< \brief ADC�ͱȽ����ж�(�� EXTI19��20�����һ��) */
#define INUM_TIM1_BRK_UP_TRG_COM  13   /**< \brief TIM1ɲ�������¡�������COM */
#define INUM_TIM1_CC              14   /**< \brief TIM1��׽�Ƚ��ж� */
#define INUM_TIM2                 15   /**< \brief TIM2ȫ���ж� */
#define INUM_TIM3                 16   /**< \brief TIM3ȫ���ж� */

#define INUM_TIM14                19   /**< \brief TIM14ȫ���ж� */

#define INUM_TIM16                21   /**< \brief TIM16ȫ���ж� */
#define INUM_TIM17                22   /**< \brief TIM17ȫ���ж� */
#define INUM_I2C1                 23   /**< \brief I2C1ȫ���ж� */

#define INUM_SPI1                 25   /**< \brief SPI1ȫ���ж� */
#define INUM_SPI2                 26   /**< \brief SPI2ȫ���ж� */
#define INUM_UART1                27   /**< \brief UART1ȫ���ж� */
#define INUM_UART2                28   /**< \brief UART2ȫ���ж� */
#define INUM_AES                  29   /**< \brief AESȫ���ж� */
#define INUM_CAN                  30   /**< \brief CANȫ���ж� */
#define INUM_USB                  31   /**< \brief USBȫ���ж� */

/** @} */

/**
 * \brief ���ж���Ϊ��(INUM_USB - INUM_WWDT + 1),
 *
 */
#define INUM_INTERNAL_COUNT     (INUM_USB - INUM_WWDT + 1)

/**
 * \brief ����жϺ�Ϊ�� INUM_USB
 */
#define INUM_INTERNAL_MAX        INUM_USB

/** \brief ��С�жϺ�: INUM_WWDT */
#define INUM_INTERNAL_MIN        INUM_WWDT

/**
 * \cond
 * �жϺŶ��壬Ϊ core_cm0.h�ļ�����
 */
typedef enum {

    /* ----------------------  Cortex-M0���쳣��  ------------------- */

    /** \brief 2  ���������ж�, ���ܱ�ֹͣ����ռ */
    NonMaskableInt_IRQn      = -14,

    /** \brief 3  Ӳ�������ж� */
    HardFault_IRQn           = -13,

    /** \brief 11  ϵͳ�������ͨ��SVCָ�� */
    SVCall_IRQn              =  -5,

    /** \brief 14  ϵͳ�Ĺ������� */
    PendSV_IRQn              =  -2,

    /** \brief 15  ϵͳ�δ�ʱ�� */
    SysTick_IRQn             =  -1,

    /******  ZML165 Specific Interrupt Numbers *******************************************************/
    WWDT_IRQn                 = 0,        /**< \brief ���ڶ�ʱ���ж� */
    PVD_IRQn                  = 1,        /**< \brief ��Դ��ѹ����ж� */
    Reserved0                 = 2,        /**< \brief RESERVED */
    FLASH_IRQn                = 3,        /**< \brief ����ȫ���ж� */
    RCC_CRS_IRQn              = 4,        /**< \brief RCC��CRS*ȫ���ж� */
    EXTI0_1_IRQn              = 5,        /**< \brief EXTI��[1��0]�ж� */
    EXTI2_3_IRQn              = 6,        /**< \brief EXTI��[3��2]�ж� */
    EXTI4_15_IRQn             = 7,        /**< \brief EXTI��[15��4]�ж� */
    Reserved1                 = 8,        /**< \brief RESERVED */
    DMA1_1_IRQn               = 9,        /**< \brief DMA1ͨ��1ȫ���ж� */
    DMA1_2_3_IRQn             = 10,       /**< \brief DMA1ͨ��2��3ȫ���ж� */
    DMA1_4_5_IRQn             = 11,       /**< \brief DMA1ͨ��4��5ȫ���ж� */
    ADC_COMP_IRQn             = 12,       /**< \brief ADC�ͱȽ����ж� */
    TIM1_BRK_UP_TRG_COM_IRQn  = 13,       /**< \brief TIM1ɲ�������¡�������COM */
    TIM1_CC_IRQn              = 14,       /**< \brief TIM1��׽�Ƚ��ж� */
    TIM2_IRQn                 = 15,       /**< \brief TIM2ȫ���ж� */
    TIM3_IRQn                 = 16,       /**< \brief TIM3ȫ���ж� */
    Reserved2                 = 17,       /**< \brief RESERVED */
    Reserved3                 = 18,       /**< \brief RESERVED */
    TIM14_IRQn                = 19,       /**< \brief TIM14ȫ���ж� */
    Reserved4                 = 20,       /**< \brief RESERVED */
    TIM16_IRQn                = 21,       /**< \brief TIM16ȫ���ж� */
    TIM17_IRQn                = 22,       /**< \brief TIM17ȫ���ж� */
    I2C1_IRQn                 = 23,       /**< \brief I2C1ȫ���ж� */
    Reserved5                 = 24,       /**< \brief RESERVED */
    SPI1_IRQn                 = 25,       /**< \brief SPI1ȫ���ж� */
    SPI2_IRQn                 = 26,       /**< \brief SPI2ȫ���ж� */
    UART1_IRQn                = 27,       /**< \brief UART1ȫ���ж� */
    UART2_IRQn                = 28,       /**< \brief UART2ȫ���ж� */
    AES_IRQn                  = 29,       /**< \brief AESȫ���ж� */
    CAN_IRQn                  = 30,       /**< \brief CANȫ���ж� */
    USB_IRQn                  = 31,       /**< \brief USBȫ���ж� */
} IRQn_Type;

/**
 * \endcond
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZLG_INUM_H */

/* end of file */

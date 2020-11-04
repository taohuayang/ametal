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
 * \brief HC32 �жϺŶ���
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-03  zp, first implementation
 * \endinternal
 */

#ifndef __HC32_INUM_H
#define __HC32_INUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \addtogroup hc32_if_inum
 * \copydoc hc32_inum.h
 * @{
 */

/**
 * \name HC32 CPU �жϺ�
 * @{
 */

/**
 * �жϺ�ʹ��˵��
 *
 * ĳһ������жϺŶ�������һ����INUM_xx��ʽ������ʹ��ʱ���ر�ע������
 *
 * ĳһ������жϺŲ��������������ʹ��ͬһ�жϣ���INUM_xx_xx��ʽ������ʹ��ʱ��Ҫע�⣬��Ϊ�Ƕ�����裬
 * ��ζ����ؿ��ƼĴ����Ļ���ַ��ͬ�����ж����ӡ��Ͽ�ʱ�����ܶ�ε��ã�ʵ���Ͻ�һ����Ч���ص��������жϷ���
 * �����ʹ��������������Ч��ֻ��һ�顣
 *
 * ���磬���жϺŵ��������趼ʹ���жϣ���ֱ�ӵ�����
 *     1.�ڶ��������ó�ʼ��������ֻ�����һ����ʼ���������ж����������С�
 *     2.�ڶ��������ý��ʼ��������ֻҪ����һ�����ʼ�����̣����ж϶Ͽ����ӣ�������������ȫ���⿪�жϡ�
 *
 *  ���ǵ��û�ʹ������Ĳ�ȷ���ԣ�����INUM_LPTIM0_1���м�㺯����ʹ�ö���豸�ṹ��ָ�뻺��+�жϵķ�ʽ�����
 *  ��һ���󣬿��Բο�am_hc32_lptim_timing.c�ý���������Խ�������жϺ�ʹ��ʱ����������
 *
 */
#define INUM_PORTA                 0    /**< \brief PORTA�ж� */
#define INUM_PORTB                 1    /**< \brief PORTB�ж� */
#define INUM_PORTC_E               2    /**< \brief PORTC_E�ж� */
#define INUM_PORTD_F               3    /**< \brief PORTD_F�ж� */
#define INUM_DMA                   4    /**< \brief DMA�ж� */
#define INUM_TIM3                  5    /**< \brief TIM3�ж� */
#define INUM_UART0_2               6    /**< \brief UART0_2�ж� */
#define INUM_UART1_3               7    /**< \brief UART1_3�ж� */
#define INUM_LPUART0               8    /**< \brief LPUART0�ж� */
#define INUM_LPUART1               9    /**< \brief LPUART1�ж� */
#define INUM_SPI0_I2S0            10    /**< \brief SPI0_I2S0�ж� */
#define INUM_SPI1_I2S1            11    /**< \brief SPI1_I2S1�ж� */
#define INUM_I2C0                 12    /**< \brief I2C0�ж� */
#define INUM_I2C1                 13    /**< \brief I2C1�ж� */
#define INUM_TIM0                 14    /**< \brief TIM0�ж� */
#define INUM_TIM1                 15    /**< \brief TIM1�ж� */
#define INUM_TIM2                 16    /**< \brief TIM2�ж� */
#define INUM_LPTIM0_1             17    /**< \brief LPTIM0_1�ж� */
#define INUM_TIM4                 18    /**< \brief TIM4�ж� */
#define INUM_TIM5                 19    /**< \brief TIM5�ж� */
#define INUM_TIM6                 20    /**< \brief TIM6�ж� */
#define INUM_PCA                  21    /**< \brief PCA�ж� */
#define INUM_WDT                  22    /**< \brief WDT�ж� */
#define INUM_RTC                  23    /**< \brief RTC�ж� */
#define INUM_ADC_DAC              24    /**< \brief ADC_DAC�ж� */
#define INUM_PCNT                 25    /**< \brief PCNT�ж� */
#define INUM_VC0_VC1_VC2_LVD      26    /**< \brief INUM_VC0_VC1_VC2_LVD�ж� */
#define INUM_USB                  27    /**< \brief USB�ж� */
#define INUM_CAN                  28    /**< \brief CAN�ж� */
#define INUM_LCD                  29    /**< \brief LCD�ж� */
#define INUM_FLASH_RAM            30    /**< \brief FLASH_RAM�ж� */
#define INUM_CLKTRIM_CTS          31    /**< \brief CLKTRIM_CTS�ж� */

/** @} */

/**
 * \brief ���ж���Ϊ��(INUM_CLKTRIM - INUM_PORTA + 1),
 *
 */
#define INUM_INTERNAL_COUNT     (INUM_CLKTRIM_CTS - INUM_PORTA + 1)

/**
 * \brief ����жϺ�Ϊ�� INUM_CLKTRIM
 */
#define INUM_INTERNAL_MAX        INUM_CLKTRIM_CTS

/** \brief ��С�жϺ�: INUM_PORTA */
#define INUM_INTERNAL_MIN        INUM_PORTA


/**
 * \cond
 * \brief �жϺŶ��壬Ϊcore_cm0plus.h�ļ�����
 */
typedef enum {
    /** \brief  1  ��λ����                                                */
    Reset_IRQn               = -15,

    /** \brief  2  ���������ж�, ���ܱ�ֹͣ����ռ                          */
    NonMaskableInt_IRQn      = -14,

    /** \brief  3  Ӳ�������ж�                                            */
    HardFault_IRQn           = -13,

    /** \brief 11  ϵͳ�������ͨ��SVCָ��                                 */
    SVCall_IRQn              =  -5,

    /** \brief 14  ϵͳ�Ĺ�������                                          */
    PendSV_IRQn              =  -2,

    /** \brief 15  ϵͳ�δ�ʱ��                                          */
    SysTick_IRQn             =  -1,

    /* ---------------  �����ж� ------------------------------------ */
	PORTA_IRQn               = 0,    /**< \brief PORTA     Interrupt  */
	PORTB_IRQn               = 1,    /**< \brief PORTB     Interrupt  */
	PORTC_E_IRQn             = 2,    /**< \brief PORTC_E   Interrupt  */
	PORTD_F_IRQn             = 3,    /**< \brief PORTD_F   Interrupt  */
	DMAC_IRQn                = 4,    /**< \brief DMAC      Interrupt  */
	TIM3_IRQn                = 5,    /**< \brief TIM3      Interrupt  */
	UART0_2_IRQn             = 6,    /**< \brief UART0_2   Interrupt  */
	UART1_3_IRQn             = 7,    /**< \brief UART1_3   Interrupt  */
	LPUART0_IRQn             = 8,    /**< \brief LPUART0   Interrupt  */
	LPUART1_IRQn             = 9,    /**< \brief LPUART1   Interrupt  */
	SPI0_I2S0_IRQn           = 10,   /**< \brief SPI0_I2S0 Interrupt  */
	SPI1_I2S1_IRQn           = 11,   /**< \brief SPI1_I2S1 Interrupt  */
	I2C0_IRQn                = 12,   /**< \brief I2C0      Interrupt  */
	I2C1_IRQn                = 13,   /**< \brief I2C1      Interrupt  */
	TIM0_IRQn                = 14,   /**< \brief TIM0      Interrupt  */
	TIM1_IRQn                = 15,   /**< \brief TIM1      Interrupt  */
	TIM2_IRQn                = 16,   /**< \brief TIM2      Interrupt  */
	LPTIM0_1_IRQn            = 17,   /**< \brief LPTIM0_1  Interrupt  */
	TIM4_IRQn                = 18,   /**< \brief TIM4      Interrupt  */
	TIM5_IRQn                = 19,   /**< \brief TIM5      Interrupt  */
	TIM6_IRQn                = 20,   /**< \brief TIM6      Interrupt  */
	PCA_IRQn                 = 21,   /**< \brief PCA       Interrupt  */
	WDT_IRQn                 = 22,   /**< \brief WDT       Interrupt  */
	RTC_IRQn                 = 23,   /**< \brief RTC       Interrupt  */
	ADC_DAC_IRQn             = 24,   /**< \brief ADC_DAC   Interrupt  */
	PCNT_IRQn                = 25,   /**< \brief PCNT      Interrupt  */
	VC0_1_2_LVD_IRQn         = 26,   /**< \brief VC0_1_2_LVD       Interrupt  */
	USB_IRQn                 = 27,   /**< \brief USB       Interrupt  */
	CAN_IRQn                 = 28,   /**< \brief CAN       Interrupt  */
	LCD_IRQn                 = 29,   /**< \brief LCD       Interrupt  */
	FLASH_RAM_IRQn           = 30,   /**< \brief FLASH_RAM Interrupt  */
	CLKTRIM_CTS_IRQn             = 31,   /**< \brief CLKTRIM   Interrupt  */

}IRQn_Type;

/**
 * \endcond
 */



/**
 * \endcond
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_INUM_H */

/* end of file */

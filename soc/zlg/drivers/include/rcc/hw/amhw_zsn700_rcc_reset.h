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
 * \brief
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-05  zp, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZSN700_RCC_RESET_H
#define __AMHW_ZSN700_RCC_RESET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "zsn700_periph_map.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_zsn700_rcc_if_reset
 * \copydoc amhw_zsn700_rcc_reset.h
 * @{
 */

/**
 * \brief CRC�Ĵ�����ṹ��
 */
typedef struct {
  __IO uint32_t flag;             /**< \brief ��λ��ʶ�Ĵ���     0x4000201C*/
  __IO uint32_t reserve[2];       /**< \brief ����λ  0x40002020��0x40002024*/
  __IO uint32_t reset[2];         /**< \brief �ڲ�����ʱ�ӿ��ƼĴ���  0x40002028��0x4000202C*/
} amhw_zsn700_rcc_reset_t;

#define ZSN700_RCC_RESET  ((amhw_zsn700_rcc_reset_t *)(0x4000201CUL))

/**
 * \brief ���踴λ����λö��
 */
typedef enum {

	/* reset[0]���Ƶ����踴λʹ��λ  */
    AMHW_ZSN700_RCC_RESET_DMA     = 29,
    AMHW_ZSN700_RCC_RESET_GPIO    = 28,
    AMHW_ZSN700_RCC_RESET_AES     = 27,
    AMHW_ZSN700_RCC_RESET_CRC     = 26,
    AMHW_ZSN700_RCC_RESET_SWD     = 25,
    AMHW_ZSN700_RCC_RESET_SYSTICK = 24,
    AMHW_ZSN700_RCC_RESET_LCD     = 22,
    AMHW_ZSN700_RCC_RESET_CLKTRIM = 21,
    AMHW_ZSN700_RCC_RESET_RTC     = 20,
    AMHW_ZSN700_RCC_RESET_PCNT    = 19,
    AMHW_ZSN700_RCC_RESET_RNG     = 18,
	AMHW_ZSN700_RCC_RESET_VC      = 17,
	AMHW_ZSN700_RCC_RESET_ADC     = 16,
	AMHW_ZSN700_RCC_RESET_PCA     = 14,
	AMHW_ZSN700_RCC_RESET_OPA     = 13,
	AMHW_ZSN700_RCC_RESET_TIM3    = 11,
	AMHW_ZSN700_RCC_RESET_ADVTIM  = 10,
    AMHW_ZSN700_RCC_RESET_LPTIM0  = 9,
    AMHW_ZSN700_RCC_RESET_TIM012  = 8,
    AMHW_ZSN700_RCC_RESET_SPI1    = 7,
	AMHW_ZSN700_RCC_RESET_SPI0    = 6,
	AMHW_ZSN700_RCC_RESET_I2C1    = 5,
	AMHW_ZSN700_RCC_RESET_I2C0    = 4,
	AMHW_ZSN700_RCC_RESET_LPUART1 = 3,
    AMHW_ZSN700_RCC_RESET_LPUART0 = 2,
    AMHW_ZSN700_RCC_RESET_UART1   = 1,
    AMHW_ZSN700_RCC_RESET_UART0   = 0,

	/* reset[1]���Ƶ����踴λʹ��λ  */
	AMHW_ZSN700_RCC_RESET_UART3   = 9 + 31,
    AMHW_ZSN700_RCC_RESET_UART2   = 8 + 31,
    AMHW_ZSN700_RCC_RESET_LPTIM1  = 4 + 31,
    AMHW_ZSN700_RCC_RESET_DAC     = 3 + 31,
}amhw_zsn700_rcc_reset_peripheral;

/**
 * \brief ���踴λ��־ö��
 */
typedef enum {
    AMHW_ZSN700_RCC_RESET_FLAG_PORT   = 7,  /**< \brief RSTB�˿ڸ�λ��־ */
	AMHW_ZSN700_RCC_RESET_FLAG_SOFT   = 6,  /**< \brief Cotrex-M0+CPU �����λ��־ */
	AMHW_ZSN700_RCC_RESET_FLAG_LOCKUP = 5,  /**< \brief Cotrex-M0+CPU Lockup��λ��־ */
	AMHW_ZSN700_RCC_RESET_FLAG_PCA    = 4,  /**< \brief PCA��λ��־ */
	AMHW_ZSN700_RCC_RESET_FLAG_WDT    = 3,  /**< \brief WDT��λ��־ */
    AMHW_ZSN700_RCC_RESET_FLAG_LVD    = 2,  /**< \brief LVD��λ��־ */
    AMHW_ZSN700_RCC_RESET_FLAG_POR15V = 1,  /**< \brief Vcore��λ��־ */
    AMHW_ZSN700_RCC_RESET_FLAG_POR5V  = 0,  /**< \brief VCC��Դ��λ��־ */
}amhw_zsn700_rcc_reset_flag_peripheral;

/**
 * \brief ���踴λ��־��Ч�Ի�ȡ
 *
 * \param[in] flag : ��λ��־     amhw_zsn700_rcc_reset_flag_peripheralö�ٳ�Ա
 *
 * return AM_TRUE :  �и�λ��������
 *        AM_FALSE:  �޸�λ��������
 */
am_static_inline
am_bool_t amhw_zsn700_rcc_reset_flag_check(amhw_zsn700_rcc_reset_flag_peripheral flag)
{

    return (ZSN700_RCC_RESET->flag & (0x1ul << flag)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ���踴λ��־��Ч�����
 *
 * \param[in] flag : ��λ��־     amhw_zsn700_rcc_reset_flag_peripheralö�ٳ�Ա
 *
 * return none
 */
am_static_inline
void amhw_zsn700_rcc_reset_flag_clr(amhw_zsn700_rcc_reset_flag_peripheral flag)
{
	ZSN700_RCC_RESET->flag &= ~(0x1ul << flag);
}

/**
 * \brief ʹĳЩ���踴λ
 *
 * \param[in]  peri ����Ҫ��λ������
 *
 * \return ��
 *
 */
void amhw_zsn700_rcc_reset (amhw_zsn700_rcc_reset_peripheral peri);


/**
 * \brief ʹĳЩ������������
 *
 * \param[in]  peri ����Ҫ��������������
 *
 * \return ��
 *
 */
void amhw_zsn700_rcc_reset_stop (amhw_zsn700_rcc_reset_peripheral peri);

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __ZSN700_RCC_RESET_H */

#endif

/* end of file */

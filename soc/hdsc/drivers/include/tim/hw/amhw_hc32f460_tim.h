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
 * \brief ��ʱ��TIM�ӿ�
 *
 * \internal
 * \par History
 * - 1.00 
 * \endinternal
 */

#ifndef __AMHW_HC32F460_TIM_H
#define __AMHW_HC32F460_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */
/**
 *******************************************************************************
 ** \brief Timer0 channel enumeration
 **
 ******************************************************************************/
typedef enum tim0_channel
{
    TIM0_CHANNEL_A = 0x00u,
    TIM0_CHANNEL_B = 0x01u
}tim0_channel_t;

/**
 *******************************************************************************
 ** \brief Timer0 Async Mode clock enumeration
 **
 ******************************************************************************/
typedef enum tim0_async_clock_src
{
    tim0_LRC    = 0x00u,
    tim0_XTAL32 = 0x01u
}tim0_async_clock_src_t;

/**
 *******************************************************************************
 ** \brief Timer0 Sync Mode clock enumeration
 **
 ******************************************************************************/
typedef enum tim0_sync_clock_src
{
    tim0_pclk1          = 0x00u,
    tim0_Inside_hard_trig = 0x01u
}tim0_sync_clock_src_t;

/**
 *******************************************************************************
 ** \brief Timer0 counter mode enumeration
 **
 ******************************************************************************/
typedef enum tim0_counter_mode
{
    tim0_sync  = 0x00u,
    tim0_async = 0x01u
}tim0_counter_mode_t;

/**
 *******************************************************************************
 ** \brief Timer0 trigger event mode enumeration
 **
 ******************************************************************************/
typedef enum tim0_function
{
    tim0_output_capare = 0x00u,
    tim0_input_captrue = 0x01u
}tim0_function_t;

/**
 *******************************************************************************
 ** \brief Timer0 clock division enumeration
 **
 ******************************************************************************/
typedef enum tim0_clock_div
{
    tim0_clk_div0 = 0u,
    tim0_clk_div2,
    tim0_clk_div4,
    tim0_clk_div8,
    tim0_clk_div16,
    tim0_clk_div32,
    tim0_clk_div64,
    tim0_clk_div128,
    tim0_clk_div256,
    tim0_clk_div512,
    tim0_clk_div1024
}tim0_clock_div_t;

/**
 * \brief TMR0 ����ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CNTA                      :16;  /**< \brief ����ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr0_cntar_field_t;

/**
 * \brief TMR0 ����ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CNTB                      :16;  /**< \brief ����ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr0_cntbr_field_t;

/**
 * \brief TMR0 ��׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CMPA                      :16;  /**< \brief ��׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr0_cmpar_field_t;

/**
 * \brief TMR0 ��׼ֵ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CMPB                      :16;  /**< \brief ��׼ֵ*/
    uint32_t RESERVED16                     :16;  /**< \brief ����*/
} stc_tmr0_cmpbr_field_t;

/**
 * \brief TMR0 �������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CSTA                      : 1;  /**< \brief ��ʱ������*/
    __IO uint32_t CAPMDA                    : 1;  /**< \brief ����ģʽѡ��A*/
    __IO uint32_t INTENA                    : 1;  /**< \brief ����ƥ���ж�ʹ��A*/
    uint32_t RESERVED3                      : 1;  /**< \brief ����*/
    __IO uint32_t CKDIVA                    : 4;  /**< \brief ͨ��A����ʱ�ӷ�Ƶѡ��*/
    __IO uint32_t SYNSA                     : 1;  /**< \brief ͨ��A������ʽѡ��*/
    __IO uint32_t SYNCLKA                   : 1;  /**< \brief ͨ��Aͬ������ʱ��Դѡ��*/
    __IO uint32_t ASYNCLKA                  : 1;  /**< \brief ͨ��A�첽����ʱ��Դѡ��*/
    uint32_t RESERVED11                     : 1;  /**< \brief ����*/
    __IO uint32_t HSTAA                     : 1;  /**< \brief Ӳ����������A*/
    __IO uint32_t HSTPA                     : 1;  /**< \brief Ӳ������ֹͣA*/
    __IO uint32_t HCLEA                     : 1;  /**< \brief Ӳ����������A*/
    __IO uint32_t HICPA                     : 1;  /**< \brief Ӳ���������벶��A*/
    __IO uint32_t CSTB                      : 1;  /**< \brief ��ʱ������*/
    __IO uint32_t CAPMDB                    : 1;  /**< \brief ����ģʽѡ��B*/
    __IO uint32_t INTENB                    : 1;  /**< \brief ����ƥ���ж�ʹ��B*/
    uint32_t RESERVED19                     : 1;  /**< \brief ����*/
    __IO uint32_t CKDIVB                    : 4;  /**< \brief ͨ��B����ʱ�ӷ�Ƶѡ��*/
    __IO uint32_t SYNSB                     : 1;  /**< \brief ͨ��B������ʽѡ��*/
    __IO uint32_t SYNCLKB                   : 1;  /**< \brief ͨ��Bͬ������ʱ��Դѡ��*/
    __IO uint32_t ASYNCLKB                  : 1;  /**< \brief ͨ��B�첽����ʱ��Դѡ��*/
    uint32_t RESERVED27                     : 1;  /**< \brief ����*/
    __IO uint32_t HSTAB                     : 1;  /**< \brief Ӳ����������B*/
    __IO uint32_t HSTPB                     : 1;  /**< \brief Ӳ������ֹͣB*/
    __IO uint32_t HCLEB                     : 1;  /**< \brief Ӳ����������B*/
    __IO uint32_t HICPB                     : 1;  /**< \brief Ӳ���������벶��B*/
} stc_tmr0_bconr_field_t;

/**
 * \brief TMR0 ״̬��־�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CMAF                      : 1;  /**< \brief ����ƥ��A*/
    uint32_t RESERVED1                      :15;  /**< \brief ����*/
    __IO uint32_t CMBF                      : 1;  /**< \brief ����ƥ��B*/
    uint32_t RESERVED17                     :15;  /**< \brief ����*/
} stc_tmr0_stflr_field_t;

typedef struct
{
    union
    {
        __IO uint32_t CNTAR;           /**< \brief ����ֵ�Ĵ���*/
        stc_tmr0_cntar_field_t CNTAR_f;
    };
    union
    {
        __IO uint32_t CNTBR;           /**< \brief ����ֵ�Ĵ���*/
        stc_tmr0_cntbr_field_t CNTBR_f;
    };
    union
    {
        __IO uint32_t CMPAR;           /**< \brief ��׼ֵ�Ĵ���*/
        stc_tmr0_cmpar_field_t CMPAR_f;
    };
    union
    {
        __IO uint32_t CMPBR;           /**< \brief ��׼ֵ�Ĵ���*/
        stc_tmr0_cmpbr_field_t CMPBR_f;
    };
    union
    {
        __IO uint32_t BCONR;           /**< \brief �������ƼĴ���*/
        stc_tmr0_bconr_field_t BCONR_f;
    };
    union
    {
        __IO uint32_t STFLR;           /**< \brief ״̬��ʶ�Ĵ���*/
        stc_tmr0_stflr_field_t STFLR_f;
    };
}amhw_hc32f460_tim_t;

/**
 * \brief ARR-16λģʽ���ؼĴ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ARR���ؼĴ�����ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_tim_arr_count_get (amhw_hc32f460_tim_t *p_hw_tim,
                                          uint8_t              chan)
{
    uint16_t arr = 0;

    if (TIM0_CHANNEL_A == chan)
    {
        arr = p_hw_tim->CMPAR;
    }
    else
    {
        arr = p_hw_tim->CMPBR;
    }
    return arr;
}

/**
 * \brief ARR-16λģʽ���ؼĴ���       ���õ�ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    : ���õļ�������ֵ
 *
 *\ return ��
 */
am_static_inline
void amhw_hc32f460_tim_arr_count_set (amhw_hc32f460_tim_t *p_hw_tim,
                                      uint8_t              chan,
                                      uint16_t             value)
{
    if (TIM0_CHANNEL_A == chan)
    {
        p_hw_tim->CMPAR = value;
    }
    else
    {
        p_hw_tim->CMPBR = value;
    }
}

/**
 * \brief CNT-16λģʽ�����Ĵ���         �õ���ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return CNT�����Ĵ�����ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_tim_cnt16_count_get (amhw_hc32f460_tim_t *p_hw_tim,
                                            uint8_t              chan)
{
    uint16_t cnt = 0;
    if (TIM0_CHANNEL_A == chan)
    {
        cnt = p_hw_tim->CNTAR;
    }
    else
    {
        cnt = p_hw_tim->CNTBR;
    }
    return cnt;
}

/**
 * \brief CNT-16λģʽ�����Ĵ���       ���õ�ǰ��������ֵ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] value    : ���õļ�������ֵ
 *
 *\ return ��
 */
am_static_inline
void amhw_hc32f460_tim_cnt16_count_set (amhw_hc32f460_tim_t *p_hw_tim,
                                        uint8_t              chan,
                                        uint16_t             value)
{
    if (TIM0_CHANNEL_A == chan)
    {
        p_hw_tim->CNTAR = value;
    }
    else
    {
        p_hw_tim->CNTBR = value;
    }
}

/**
 * \brief CTEN ��ʱ��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim_disable (amhw_hc32f460_tim_t *p_hw_tim, uint8_t chan)
{
    if (TIM0_CHANNEL_A == chan)
    {
        p_hw_tim->BCONR_f.CSTA = 0;
    }
    else
    {
        p_hw_tim->BCONR_f.CSTB = 0;
    }
}

/**
 * \brief CTEN ��ʱ��ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \note ��ʱ����ͬģʽ��ѡ�����λ�̶����ٸ���������ṹ�����ԣ�ֻ��ĳһ�Ĵ����������ɡ�
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim_enable (amhw_hc32f460_tim_t *p_hw_tim, uint8_t chan)
{
    if (TIM0_CHANNEL_A == chan)
    {
        p_hw_tim->BCONR_f.CSTA = 1;
    }
    else
    {
        p_hw_tim->BCONR_f.CSTB = 1;
    }
}

/**
 * \brief �ڲ�ʱ�ӷ�Ƶѡ��
 */
typedef enum {
    AMHW_HC32F460_TIM_CLK_DIV0 = 0,    /**< \brief 1��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV2,        /**< \brief 2��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV4,        /**< \brief 4��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV8,        /**< \brief 8��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV16,       /**< \brief 16��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV32,       /**< \brief 32��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV64,       /**< \brief 64��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV128,      /**< \brief 128��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV256,      /**< \brief 256��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV512,      /**< \brief 512��Ƶ */
    AMHW_HC32F460_TIM_CLK_DIV1024,     /**< \brief 1024��Ƶ */
}amhw_hc32f460_tim_clkdiv_t;

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ���õķ�Ƶϵ����amhw_hc32_tim_clkdiv_tö������
 */
am_static_inline
amhw_hc32f460_tim_clkdiv_t
    amhw_hc32f460_tim_mode_clkdiv_get (amhw_hc32f460_tim_t *p_hw_tim, uint8_t chan)
{
    amhw_hc32f460_tim_clkdiv_t clkdiv;

    if (TIM0_CHANNEL_A == chan)
    {
        clkdiv = (amhw_hc32f460_tim_clkdiv_t)p_hw_tim->BCONR_f.CKDIVA;
    }
    else
    {
        clkdiv = (amhw_hc32f460_tim_clkdiv_t)p_hw_tim->BCONR_f.CKDIVB;
    }
    return clkdiv;
}

/**
 * \brief PRS �ڲ�ʱ�ӷ�Ƶѡ��   ����
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 * \param[in] clkdiv   : ���õķ�Ƶϵ����amhw_hc32_tim_clkdiv_tö������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim_mode_clkdiv_set (amhw_hc32f460_tim_t       *p_hw_tim,
                                        uint8_t                    chan,
                                        amhw_hc32f460_tim_clkdiv_t clkdiv)
{
    if (TIM0_CHANNEL_A == chan)
    {
        p_hw_tim->BCONR_f.CKDIVA = clkdiv;
    }
    else
    {
        p_hw_tim->BCONR_f.CKDIVB = clkdiv;
    }
}

/**
 * \brief UIE �жϽ���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim_int_disable (amhw_hc32f460_tim_t *p_hw_tim, uint8_t chan)
{
    if (TIM0_CHANNEL_A == chan)
    {
        p_hw_tim->BCONR_f.INTENA = 0;
    }
    else
    {
        p_hw_tim->BCONR_f.INTENB = 0;
    }
}

/**
 * \brief UIE �ж�ʹ��
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim_int_enable (amhw_hc32f460_tim_t *p_hw_tim, uint8_t chan)
{
    if (TIM0_CHANNEL_A == chan)
    {
        p_hw_tim->BCONR_f.INTENA = 1;
    }
    else
    {
        p_hw_tim->BCONR_f.INTENB = 1;
    }
}

/**
 * \brief UIF ����ж� ��־��ȡ
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return AM_TRUE  �� ��־��Ч
 *         AM_FALSE �� ��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f460_tim_int_flag_check(amhw_hc32f460_tim_t *p_hw_tim, uint8_t chan)
{
    uint8_t value = 0;
    if(TIM0_CHANNEL_A == chan)
    {
        value = p_hw_tim->STFLR_f.CMAF;
    }
    else
    {
        value = p_hw_tim->STFLR_f.CMBF;
    }
    return value ? AM_TRUE : AM_FALSE;
}

/**
 * \brief UIF ����ж� ��־���
 *
 * \param[in] p_hw_tim : ָ��TIM��ʱ���Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_tim_int_flag_clr(amhw_hc32f460_tim_t *p_hw_tim, uint8_t chan)
{
    if(TIM0_CHANNEL_A == chan)
    {
        p_hw_tim->STFLR_f.CMAF =0u;
        while(0u != p_hw_tim->STFLR_f.CMAF)
        {
            ;
        }
    }
    else
    {
        p_hw_tim->STFLR_f.CMBF = 0u;
        while(0u != p_hw_tim->STFLR_f.CMBF)
        {
            ;
        }
    }
}

/**
 * \brief ʹ������������ν���
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

  /* ��������������ʹ�� */
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif
/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_TIM_H */

/* end of file */

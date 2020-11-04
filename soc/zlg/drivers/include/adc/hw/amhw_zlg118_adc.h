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
 * \brief ADC Peripheral Access Layer
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-24  zp, first implementation
 *
 * \endinternal
 */

#ifndef __AMHW_ZLG118_ADC_H
#define __AMHW_ZLG118_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zlg118_if_adc
 * \copydoc amhw_zlg118_adc.h
 * @{
 */

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
 * \brief ADC - Register Layout Typedef
 */
typedef struct amhw_zlg118_adc {
    __I  uint32_t reserve0;       /**< \brief ���� */
    __IO uint32_t cr[2];          /**< \brief �������üĴ���0��1 ƫ�Ƶ�ַ0x004��0x008*/
    __I  uint32_t reserve2[13];   /**< \brief ���� */
    __IO uint32_t sqr[3];         /**< \brief ˳��ɨ��ת��ͨ�����üĴ���0��1��2 */
    __IO uint32_t jqr;            /**< \brief ���ɨ��ת��ͨ�����üĴ��� */
    __I  uint32_t sqrresult[16];  /**< \brief ˳��ɨ��ת��ͨ��ת�����(0~15) */
    __I  uint32_t jqrresult[4];   /**< \brief ���ɨ��ת��ͨ��ת�����(0~3) */
    __I  uint32_t result;         /**< \brief ת����� */
    __I  uint32_t resultacc;      /**< \brief ת������ۼ�ֵ */
    __IO uint32_t ht;             /**< \brief �Ƚ�����ֵ */
    __IO uint32_t lt;             /**< \brief �Ƚ�����ֵ */
    __IO uint32_t ifr;            /**< \brief �жϱ�־�Ĵ��� */
    __IO uint32_t icr;            /**< \brief �ж�����Ĵ��� */
    __IO uint32_t exttrigger0;    /**< \brief ����ת����˳��ɨ��ת���ⲿ�жϴ���Դ���üĴ��� */
    __IO uint32_t exttrigger1;    /**< \brief ���ɨ��ת���ⲿ�жϴ���Դ���üĴ��� */
    __IO uint32_t sglstart;       /**< \brief ����ת���������ƼĴ��� */
    __IO uint32_t sqrstart;       /**< \brief ˳��ɨ��ת���������ƼĴ��� */
    __IO uint32_t jqrstart;       /**< \brief ���ɨ��ת���������ƼĴ��� */
    __IO uint32_t allstart;       /**< \brief һֱת������ֹͣ���ƼĴ��� */
} amhw_zlg118_adc_t;

typedef enum {
    AMHW_ZLG118_WORK_MODE_SINGLE = 0,      /**< \brief ����ת��������1��ͨ����*/
    AMHW_ZLG118_WORK_MODE_SQR,             /**< \brief ˳��ɨ�����ת��������16ͨ���� */
    AMHW_ZLG118_WORK_MODE_JQR,             /**< \brief ����ɨ�����ת�� ������4ͨ����*/
}amhw_zlg118_adc_work_mode_t;

typedef enum {
    AMHW_ZLG118_CHAN_AIN0_PA0 = 0,      /**< \brief ת��ͨ��0 */
    AMHW_ZLG118_CHAN_AIN1_PA1,          /**< \brief ת��ͨ��1 */
    AMHW_ZLG118_CHAN_AIN2_PA2,          /**< \brief ת��ͨ��2 */
    AMHW_ZLG118_CHAN_AIN3_PA3,          /**< \brief ת��ͨ��3 */
    AMHW_ZLG118_CHAN_AIN4_PA4,          /**< \brief ת��ͨ��4 */
    AMHW_ZLG118_CHAN_AIN5_PA5,          /**< \brief ת��ͨ��5 */
    AMHW_ZLG118_CHAN_AIN6_PA6,          /**< \brief ת��ͨ��6 */
    AMHW_ZLG118_CHAN_AIN7_PA7,          /**< \brief ת��ͨ��7 */
    AMHW_ZLG118_CHAN_AIN8_PB0,          /**< \brief ת��ͨ��8 */
    AMHW_ZLG118_CHAN_AIN9_PB1,          /**< \brief ת��ͨ��9 */
    AMHW_ZLG118_CHAN_AIN10_PC0,         /**< \brief ת��ͨ��10 */
    AMHW_ZLG118_CHAN_AIN11_PC1,         /**< \brief ת��ͨ��11 */
    AMHW_ZLG118_CHAN_AIN12_PC2,         /**< \brief ת��ͨ��12 */
    AMHW_ZLG118_CHAN_AIN13_PC3,         /**< \brief ת��ͨ��13 */
    AMHW_ZLG118_CHAN_AIN14_PC4,         /**< \brief ת��ͨ��14 */
    AMHW_ZLG118_CHAN_AIN15_PC5,         /**< \brief ת��ͨ��15 */
    AMHW_ZLG118_CHAN_AIN16_PB2,         /**< \brief ת��ͨ��16 */
    AMHW_ZLG118_CHAN_AIN17_PB10,        /**< \brief ת��ͨ��17 */
    AMHW_ZLG118_CHAN_AIN18_PB11,        /**< \brief ת��ͨ��18 */
    AMHW_ZLG118_CHAN_AIN19_PB12,        /**< \brief ת��ͨ��19 */
    AMHW_ZLG118_CHAN_AIN20_PB13,        /**< \brief ת��ͨ��20 */
    AMHW_ZLG118_CHAN_AIN21_PB14,        /**< \brief ת��ͨ��21 */
    AMHW_ZLG118_CHAN_AIN22_PB15,        /**< \brief ת��ͨ��22 */
    AMHW_ZLG118_CHAN_AIN23_PE15,        /**< \brief ת��ͨ��23 */
    AMHW_ZLG118_CHAN_AIN24_PE14,        /**< \brief ת��ͨ��24 */
    AMHW_ZLG118_CHAN_AIN25_PE13,        /**< \brief ת��ͨ��25 */
    AMHW_ZLG118_CHAN_DAC_OUT,           /**< \brief ��DAC������ӣ�ADC_CR0.Buf����Ϊ1 */
    AMHW_ZLG118_CHAN_VCC_DIV3,          /**< \brief ���ڲ�1/3VCC���ӣ�ADC_CR0.Buf����Ϊ1 */
    AMHW_ZLG118_CHAN_INSIDE_TEMP_SENSOR,/**< \brief �������¶ȴ����������ѹ���ӣ�ADC_CR0.Buf����Ϊ1 */
    AMHW_ZLG118_CHAN_INSIDE_REFVCC_12,  /**< \brief ���ڲ���׼1.2V�����ѹ���ӣ�ADC_CR0.Buf����Ϊ1 */
}amhw_zlg118_adc_chan_sel_t;

/**
 * \brief IE �ж�ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_int_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[0] |= (0x1ul << 15);
}

/**
 * \brief IE �жϽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_int_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[0] &= ~(0x1ul << 15);
}

/**
 * \brief En ADCʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[0] |= (0x1ul << 0);
}

/**
 * \brief En ADC����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[0] &= ~(0x1ul << 0);
}

/**
 * \brief InRefEn ADC�ڲ��ο���ѹʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_inrefvol_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[0] |= (0x1ul << 14);
}

/**
 * \brief InRefEn ADC�ڲ��ο���ѹ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_inrefvol_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[0] &= ~(0x1ul << 14);
}

/**
 * \brief ADC ��������
 */
typedef enum {
    AMHW_ZLG118_ADC_SAMPLE_PERIOD_4 = 0,     /**< \brief 4��ת������ */
    AMHW_ZLG118_ADC_SAMPLE_PERIOD_6,         /**< \brief 6��ת������ */
    AMHW_ZLG118_ADC_SAMPLE_PERIOD_8,         /**< \brief 8��ת������ */
    AMHW_ZLG118_ADC_SAMPLE_PERIOD_12,        /**< \brief 12��ת������ */
}amhw_zlg118_adc_sample_period_t;

/**
 * \brief SAM ADC��������ѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] choice   : amhw_zlg118_adc_sample_period_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_sample_period_sel(amhw_zlg118_adc_t              *p_hw_adc,
                                       amhw_zlg118_adc_sample_period_t choice)
{
    p_hw_adc->cr[0] = (p_hw_adc->cr[0] & (~(0x3ul << 12))) |
                      ((choice & 0x3ul) << 12);
}

/**
 * \brief SAM ADC�������ڻ�ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return amhw_zlg118_adc_sample_period_tö����
 */
am_static_inline
amhw_zlg118_adc_sample_period_t amhw_zlg118_adc_sample_period_get(
                                    amhw_zlg118_adc_t *p_hw_adc)
{
    return (amhw_zlg118_adc_sample_period_t)((p_hw_adc->cr[0] >> 12) & 0x3ul);
}

/**
 * \brief Buf ADC�����źŷŴ���ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \note ���¼��������Ҫ��BUF���ܣ�ʹ��BUF����ʱ���������200kbps
 *            1���ⲿ���������ź�
 *            2������1/3AVCC
 *            3������temp sensor
 *            4������VREF1P2
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_inamplify_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[0] |= (0x1ul << 11);
}

/**
 * \brief Buf ADC�����źŷŴ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \note ���¼��������Ҫ��BUF���ܣ�ʹ��BUF����ʱ���������200kbps
 *            1���ⲿ���������ź�
 *            2������1/3AVCC
 *            3������temp sensor
 *            4������VREF1P2
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_inamplify_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[0] &= ~(0x1ul << 11);
}

/**
 * \brief ADC �ο���ѹѡ��
 */
typedef enum {
    AMHW_ZLG118_ADC_REFVOL_INSIDE_1500MV = 0,
    AMHW_ZLG118_ADC_REFVOL_INSIDE_2500MV,
    AMHW_ZLG118_ADC_REFVOL_OUTSIDE_PB1,
    AMHW_ZLG118_ADC_REFVOL_AVCC,
}amhw_zlg118_adc_refvoltage_choice_t;

/**
 * \brief Ref ADC�ο���ѹѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] choice   : amhw_zlg118_adc_refvoltage_choice_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_refvol_sel(amhw_zlg118_adc_t                  *p_hw_adc,
                                amhw_zlg118_adc_refvoltage_choice_t choice)
{
    p_hw_adc->cr[0] = (p_hw_adc->cr[0] & (~(0x3ul << 9))) |
                      ((choice & 0x3ul) << 9);
}

/**
 * \brief Ref ADC�ο���ѹѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] choice   : amhw_zlg118_adc_refvoltage_choice_tö����
 *
 * \return none
 */
am_static_inline
amhw_zlg118_adc_refvoltage_choice_t amhw_zlg118_adc_refvol_get(
                                        amhw_zlg118_adc_t *p_hw_adc)
{
    return (amhw_zlg118_adc_refvoltage_choice_t)((p_hw_adc->cr[0] >> 9) & 0x3ul);
}

/**
 * \brief SGLMux ����ת��ģʽת��ͨ��ѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] choice   : amhw_zlg118_adc_chan_sel_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_sgl_chan_sel(amhw_zlg118_adc_t         *p_hw_adc,
                                  amhw_zlg118_adc_chan_sel_t choice)
{
    p_hw_adc->cr[0] = (p_hw_adc->cr[0] & (~(0x1ful << 4))) |
                      ((choice & 0x1ful) << 4);
}

/**
 * \brief ADCʱ��ѡ��
 */
typedef enum {
    AMHW_ZLG118_ADC_PCLK_DIV1 = 0,
    AMHW_ZLG118_ADC_PCLK_DIV2,
    AMHW_ZLG118_ADC_PCLK_DIV4,
    AMHW_ZLG118_ADC_PCLK_DIV8,
}amhw_zlg118_adc_pclk_div_t;

/**
 * \brief CkDiv ADCʱ�ӷ�Ƶѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] choice   : amhw_zlg118_adc_pclk_div_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_pclk_div_sel(amhw_zlg118_adc_t         *p_hw_adc,
                                  amhw_zlg118_adc_pclk_div_t choice)
{
    p_hw_adc->cr[0] = (p_hw_adc->cr[0] & (~(0x3ul << 2))) |
                      ((choice & 0x3ul) << 2);
}

/**
 * \brief CkDiv ADCʱ�ӷ�Ƶ��ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return amhw_zlg118_adc_pclk_div_tö�����е�һ��
 */
am_static_inline
amhw_zlg118_adc_pclk_div_t amhw_zlg118_adc_pclk_div_get(amhw_zlg118_adc_t
                                                            *p_hw_adc)
{
    return (amhw_zlg118_adc_pclk_div_t)((p_hw_adc->cr[0] >> 2) & 0x3ul);
}

/**
 * \brief RAccClr ADCת������ۼӼĴ�����ADC_ResultAcc������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_acc_clr (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] &= ~(0x1ul << 15);
}

/**
 * \brief RegCmp ADC����Ƚ�ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_interval_cmp_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] |= (0x1ul << 14);
}

/**
 * \brief RegCmp ADC����ȽϽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_interval_cmp_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] &= ~(0x1ul << 14);
}

/**
 * \brief HtCmp ADC����ֵ�Ƚ�ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_ht_cmp_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] |= (0x1ul << 13);
}

/**
 * \brief HtCmp ADC����ֵ�ȽϽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_ht_cmp_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] &= ~(0x1ul << 13);
}

/**
 * \brief LtCmp ADC����ֵ�Ƚ�ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_lt_cmp_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] |= (0x1ul << 12);
}

/**
 * \brief LtCmp ADC����ֵ�ȽϽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_lt_cmp_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] &= ~(0x1ul << 12);
}

/**
 * \brief RAccEn ADCת������Զ��ۼ�ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_acc_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] |= (0x1ul << 11);
}

/**
 * \brief RAccEn ADCת������Զ��ۼӽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_acc_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] &= ~(0x1ul << 11);
}

/**
 * \brief ADCת��ģʽѡ��
 */
typedef enum {
    AMHW_ZLG118_ADC_MODE_SCAN   = 1,
    AMHW_ZLG118_ADC_MODE_SINGLE = 0,
}amhw_zlg118_adc_mode_t;
/**
 * \brief Mode ADCת��ģʽѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] mode     : amhw_zlg118_adc_mode_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_mode_sel (amhw_zlg118_adc_t     *p_hw_adc,
                               amhw_zlg118_adc_mode_t mode)
{
    p_hw_adc->cr[1] =  (p_hw_adc->cr[1] & (~(0x1ul << 10))) |
                       ((mode & 0X1ul) << 10);
}

/**
 * \brief DmaJqr ���ɨ�败��DMA��ȡʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_dma_jqr_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] |= (0x1ul << 9);
}

/**
 * \brief DmaJqr ���ɨ�败��DMA��ȡ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_dma_jqr_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] &= ~(0x1ul << 9);
}

/**
 * \brief DmaSqr ˳��ɨ�败��DMA��ȡʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_dma_sqr_enable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] |= (0x1ul << 8);
}

/**
 * \brief DmaSqr ˳��ɨ�败��DMA��ȡ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_dma_sqr_disable (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->cr[1] &= ~(0x1ul << 8);
}

/**
 * \brief ThCh ��ֵ�Ƚ�ͨ��ѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] choice   : amhw_zlg118_adc_chan_sel_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_threshold_chan_sel(amhw_zlg118_adc_t         *p_hw_adc,
                                        amhw_zlg118_adc_chan_sel_t choice)
{
    p_hw_adc->cr[1] = (p_hw_adc->cr[1] & (~(0x1ful << 3))) |
                      ((choice & 0x1ful) << 3);
}

typedef enum {
    AMHW_ZLG118_ADC_DATA_ALIGN_RIGHT = 0,
    AMHW_ZLG118_ADC_DATA_ALIGN_LEFT  = 1,
}amhw_zlg118_adc_data_align_t;

/**
 * \brief ADC ת������������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] choice   : amhw_zlg118_adc_data_align_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_align_way_sel (amhw_zlg118_adc_t           *p_hw_adc,
                                    amhw_zlg118_adc_data_align_t mode)
{
    p_hw_adc->cr[1] =  (p_hw_adc->cr[1] & (~(0x1ul << 2))) |
                       ((mode & 0x1ul) << 2);
}

/**
 * \brief ˳��ɨ��ת��ͨ������ ��˳��ɨ��ת��ͨ���;����ADC����ͨ���໥���ӣ�
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] sqr_chan : sqrͨ�����
 * \param[in] choice   : amhw_zlg118_adc_chan_sel_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_sqr_chan_sel(amhw_zlg118_adc_t         *p_hw_adc,
                                  uint8_t                    sqr_chan,
                                  amhw_zlg118_adc_chan_sel_t choice)
{
    if(sqr_chan < 16) {
        p_hw_adc->sqr[sqr_chan / 6] =
            (p_hw_adc->sqr[sqr_chan / 6] & (~(0x1ful<<((sqr_chan % 6) * 5)))) |
            ((choice & 0x1ful) << ((sqr_chan % 6) * 5));
    }
}

/**
 * \brief ˳��ɨ��ת����������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] num      : ת������
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_sqr_num_set(amhw_zlg118_adc_t *p_hw_adc,
                                 uint8_t            num)
{
    p_hw_adc->sqr[2] = (p_hw_adc->sqr[2] & (~(0xful << 20))) |
                       ((num & 0xful) << 20);
}

/**
 * \brief ���ɨ��ת��ͨ�����ã� ���ɨ��ת��ͨ���;����ADC����ͨ���໥���ӣ�
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] jqr_chan : jqrͨ�����
 * \param[in] choice   : amhw_zlg118_adc_chan_sel_tö����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_jqr_chan_sel(amhw_zlg118_adc_t         *p_hw_adc,
                                  uint8_t                    jqr_chan,
                                  amhw_zlg118_adc_chan_sel_t choice)
{
    if(jqr_chan < 4) {
        p_hw_adc->jqr = (p_hw_adc->jqr & (~(0x1ful << (jqr_chan * 5)))) |
                         ((choice & 0x1ful) << (jqr_chan * 5));
    }
}

/**
 * \brief ���ɨ��ת����������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] num      : ת������
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_jqr_num_set(amhw_zlg118_adc_t *p_hw_adc,
                                 uint8_t            num)
{
    p_hw_adc->jqr = (p_hw_adc->jqr & (~(0x3ul << 20))) |
                    ((num & 0x3ul) << 20);
}

/**
 * \brief ˳��ɨ��ת��ͨ�� xת������� ���ɨ��AD���ݻ�ȡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] sqr_chan : sqrͨ�����
 *
 * \return 12bitADCת������
 */
am_static_inline
uint16_t amhw_zlg118_adc_sqr_chan_data_get(amhw_zlg118_adc_t *p_hw_adc,
                                           uint8_t            sqr_chan)
{
    if(sqr_chan < 16) {
        return p_hw_adc->sqrresult[sqr_chan];
    } else {
        return 0;
    }
}

/**
 * \brief ���ɨ��ת��ͨ�� xת������� ���ɨ��AD���ݻ�ȡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] jqr_chan : jqrͨ�����
 *
 * \return 12bitADCת������
 */
am_static_inline
uint16_t amhw_zlg118_adc_jqr_chan_data_get(amhw_zlg118_adc_t *p_hw_adc,
                                           uint8_t            jqr_chan)
{
    if(jqr_chan < 4) {
        return p_hw_adc->jqrresult[jqr_chan];
    } else {
        return 0;
    }
}

/**
 * \brief ADCת�������ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return 12bitADCת������
 */
am_static_inline
uint16_t amhw_zlg118_adc_data_get(amhw_zlg118_adc_t *p_hw_adc)
{
    return p_hw_adc->result;
}

/**
 * \brief ADCת������ۼ�ֵ��ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return 16bit����
 */
am_static_inline
uint16_t amhw_zlg118_adc_acc_data_get(amhw_zlg118_adc_t *p_hw_adc)
{
    return p_hw_adc->resultacc;
}

/**
 * \brief ADC�Ƚ�����ֵ��ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return 12bit����
 */
am_static_inline
uint16_t amhw_zlg118_adc_ht_get(amhw_zlg118_adc_t *p_hw_adc)
{
    return p_hw_adc->ht;
}

/**
 * \brief ADC�Ƚ�����ֵ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] data     : ����������ֵ����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_ht_set(amhw_zlg118_adc_t *p_hw_adc,
                            uint16_t           data)
{
    p_hw_adc->ht = (p_hw_adc->ht & (~(0xffful))) |
                   (data & 0xffful);
}

/**
 * \brief ADC�Ƚ�����ֵ��ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return 12bit����
 */
am_static_inline
uint16_t amhw_zlg118_adc_lt_get(amhw_zlg118_adc_t *p_hw_adc)
{
    return p_hw_adc->lt;
}

/**
 * \brief ADC�Ƚ�����ֵ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] data     : ����������ֵ����
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_lt_set(amhw_zlg118_adc_t *p_hw_adc,
                            uint16_t           data)
{
    p_hw_adc->lt = (p_hw_adc->lt & (~(0xffful))) |
                   (data & 0xffful);
}

typedef enum {
    AMHW_ZLG118_ADC_FLAG_ALL         = 6,
    AMHW_ZLG118_ADC_FLAG_CONVERT_JQR = 5,   /* ���ɨ��ת��״̬��־    1�����    0��δ���*/
    AMHW_ZLG118_ADC_FLAG_CONVERT_SQR = 4,   /* ˳��ɨ��ת��״̬��־    1�����    0��δ���*/
    AMHW_ZLG118_ADC_FLAG_COMPARE_REG = 3,   /* ת������Ƿ�λ��[LT �� HT)����    1��λ��    0����λ��*/
    AMHW_ZLG118_ADC_FLAG_COMPARE_HT = 2,    /* ת������Ƿ�λ��[HT �� 4095)����    1��λ��    0����λ��*/
    AMHW_ZLG118_ADC_FLAG_COMPARE_LT = 1,    /* ת������Ƿ�λ��[0 �� LT)����    1��λ��    0����λ��*/
    AMHW_ZLG118_ADC_FLAG_CONVERT_SINGLE = 0,/* ����ת��״̬��־    1�����    0��δ���*/
}amhw_zlg118_adc_flag_type_t;

/**
 * \brief ADC��־״̬��ȡ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_zlg118_adc_flag_type_tö������
 *
 * \return AM_TRUE  : 1
 *         AM_FALSE : 0
 */
am_static_inline
am_bool_t amhw_zlg118_adc_flag_check (amhw_zlg118_adc_t          *p_hw_adc,
                                      amhw_zlg118_adc_flag_type_t type)
{
    return ((p_hw_adc->ifr >> type) & 0x1u) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ADC��־״̬���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_zlg118_adc_flag_type_tö������
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_flag_clr (amhw_zlg118_adc_t          *p_hw_adc,
                               amhw_zlg118_adc_flag_type_t type)
{
    if(type == AMHW_ZLG118_ADC_FLAG_ALL) {
        p_hw_adc->icr &= ~(0x3ful);
    } else {
        p_hw_adc->icr &= ~(0x1ul << type);
    }

}

typedef enum {
    AMHW_ZLG118_ADC_INT_TRIGGER_PC15 = 31,
    AMHW_ZLG118_ADC_INT_TRIGGER_PB15 = 30,
    AMHW_ZLG118_ADC_INT_TRIGGER_PA15 = 29,
    AMHW_ZLG118_ADC_INT_TRIGGER_PC11 = 28,
    AMHW_ZLG118_ADC_INT_TRIGGER_PB11 = 27,
    AMHW_ZLG118_ADC_INT_TRIGGER_PA11 = 26,
    AMHW_ZLG118_ADC_INT_TRIGGER_PD7 = 25,
    AMHW_ZLG118_ADC_INT_TRIGGER_PC7 = 24,
    AMHW_ZLG118_ADC_INT_TRIGGER_PB7 = 23,
    AMHW_ZLG118_ADC_INT_TRIGGER_PA7 = 22,
    AMHW_ZLG118_ADC_INT_TRIGGER_PD3 = 21,
    AMHW_ZLG118_ADC_INT_TRIGGER_PC3 = 20,
    AMHW_ZLG118_ADC_INT_TRIGGER_PB3 = 19,
    AMHW_ZLG118_ADC_INT_TRIGGER_PA3 = 18,
    AMHW_ZLG118_ADC_INT_TRIGGER_DMA = 17,
    AMHW_ZLG118_ADC_INT_TRIGGER_SPI1 = 16,
    AMHW_ZLG118_ADC_INT_TRIGGER_SPI0 = 15,
    AMHW_ZLG118_ADC_INT_TRIGGER_PCA = 14,
    AMHW_ZLG118_ADC_INT_TRIGGER_RTC = 13,
    AMHW_ZLG118_ADC_INT_TRIGGER_VC1 = 12,
    AMHW_ZLG118_ADC_INT_TRIGGER_VC0 = 11,
    AMHW_ZLG118_ADC_INT_TRIGGER_LPUART1 = 10,
    AMHW_ZLG118_ADC_INT_TRIGGER_LPUART0 = 9,
    AMHW_ZLG118_ADC_INT_TRIGGER_UART1 = 8,
    AMHW_ZLG118_ADC_INT_TRIGGER_UART0 = 7,
    AMHW_ZLG118_ADC_INT_TRIGGER_TIM6 = 6,
    AMHW_ZLG118_ADC_INT_TRIGGER_TIM5 = 5,
    AMHW_ZLG118_ADC_INT_TRIGGER_TIM4 = 4,
    AMHW_ZLG118_ADC_INT_TRIGGER_TIM3 = 3,
    AMHW_ZLG118_ADC_INT_TRIGGER_TIM2 = 2,
    AMHW_ZLG118_ADC_INT_TRIGGER_TIM1 = 1,
    AMHW_ZLG118_ADC_INT_TRIGGER_TIM0 = 0,
}amhw_zlg118_adc_int_trigger_src_t;

/**
 * \brief ����ת����˳��ɨ��ת���ⲿ�жϴ���Դ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_zlg118_adc_int_trigger_src_tö������
 *
 * \note TIM4/5/6�жϴ��� ADC�Զ�ת����������Ҫʹ�� TIM4/5/6����Ӧ�ж��⣬����Ҫ����Advanced Timer
 *       ��չƵ���жϴ���ѡ��Ĵ��� TIMX_CRѡ����Դ��� ADC ���ж�Դ
 *
 *       ���� ADCʹ�õ��Ǹ��жϱ�־λ�������ء������Ҫ�ظ���������Ҫ����жϱ�־���������Ҫ�����жϷ������
 *       �벻Ҫʹ�� NVIC���ж�ʹ�ܡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_sgl_sqr_trigger_src_set (
         amhw_zlg118_adc_t                *p_hw_adc,
         amhw_zlg118_adc_int_trigger_src_t type)
{
    p_hw_adc->exttrigger0 |= (0x1ul << type);
}

/**
 * \brief ����ת����˳��ɨ��ת���ⲿ�жϴ���Դ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_zlg118_adc_int_trigger_src_tö������
 *
 * \note TIM4/5/6�жϴ��� ADC�Զ�ת����������Ҫʹ�� TIM4/5/6 ����Ӧ�ж��⣬����Ҫ����Advanced Timer
 *       ��չƵ���жϴ���ѡ��Ĵ��� TIMX_CR ѡ����Դ��� ADC ���ж�Դ
 *
 *       ���� ADC ʹ�õ��Ǹ��жϱ�־λ�������ء������Ҫ�ظ���������Ҫ����жϱ�־���������Ҫ�����жϷ������
 *       �벻Ҫʹ�� NVIC ���ж�ʹ�ܡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_sgl_sqr_trigger_src_clr (
         amhw_zlg118_adc_t                *p_hw_adc,
         amhw_zlg118_adc_int_trigger_src_t type)
{
    p_hw_adc->exttrigger0 &= ~(0x1ul << type);
}

/**
 * \brief ���ɨ��ת���ⲿ�жϴ���Դ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_zlg118_adc_int_trigger_src_tö������
 *
 * \note TIM4/5/6�жϴ��� ADC�Զ�ת����������Ҫʹ�� TIM4/5/6 ����Ӧ�ж��⣬����Ҫ����Advanced Timer
 *       ��չƵ���жϴ���ѡ��Ĵ��� TIMX_CR ѡ����Դ��� ADC ���ж�Դ
 *
 *       ���� ADC ʹ�õ��Ǹ��жϱ�־λ�������ء������Ҫ�ظ���������Ҫ����жϱ�־���������Ҫ�����жϷ������
 *       �벻Ҫʹ�� NVIC ���ж�ʹ�ܡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_jqr_trigger_src_set (
         amhw_zlg118_adc_t                *p_hw_adc,
         amhw_zlg118_adc_int_trigger_src_t type)
{
    p_hw_adc->exttrigger1 |= (0x1ul << type);
}

/**
 * \brief ���ɨ��ת���ⲿ�жϴ���Դ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 * \param[in] type     : ��־���amhw_zlg118_adc_int_trigger_src_tö������
 *
 * \note TIM4/5/6�жϴ��� ADC�Զ�ת����������Ҫʹ�� TIM4/5/6 ����Ӧ�ж��⣬����Ҫ����Advanced Timer
 *       ��չƵ���жϴ���ѡ��Ĵ��� TIMX_CRѡ����Դ��� ADC���ж�Դ
 *
 *       ���� ADCʹ�õ��Ǹ��жϱ�־λ�������ء������Ҫ�ظ���������Ҫ����жϱ�־���������Ҫ�����жϷ������
 *       �벻Ҫʹ�� NVIC���ж�ʹ�ܡ�
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_jqr_trigger_src_clr (
         amhw_zlg118_adc_t                *p_hw_adc,
         amhw_zlg118_adc_int_trigger_src_t type)
{
    p_hw_adc->exttrigger1 &= ~(0x1ul << type);
}

/**
 * \brief ����ת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_single_convert_start (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->sglstart |= (0x1ul << 0);
}

/**
 * \brief ����ת��ֹͣ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_single_convert_stop (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->sglstart &= ~(0x1ul << 0);
}

/**
 * \brief ˳��ɨ��ת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_sqr_convert_start (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->sqrstart |= (0x1ul << 0);
}

/**
 * \brief ˳��ɨ��ת��ֹͣ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_sqr_convert_stop (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->sqrstart &= ~(0x1ul << 0);
}

/**
 * \brief ���ɨ��ת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_jqr_convert_start (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->jqrstart |= (0x1ul << 0);
}

/**
 * \brief ���ɨ��ת��ֹͣ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_jqr_convert_stop (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->jqrstart &= ~(0x1ul << 0);
}


/**
 * \brief һֱת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \note ֹͣADCһֱת��,��Ҫ�ȴ�������ת������
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_always_convert_start (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->jqrstart |= (0x1ul << 0);
}

/**
 * \brief һֱת��ֹͣ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \note ֹͣADCһֱת��,��Ҫ�ȴ�������ת������
 *
 * \return none
 */
am_static_inline
void amhw_zlg118_adc_always_convert_stop (amhw_zlg118_adc_t *p_hw_adc)
{
    p_hw_adc->jqrstart &= ~(0x1ul << 0);
}

/**
 * \brief һֱת��ֹͣ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����ָ��
 *
 * \note ֹͣADCһֱת��,��Ҫ�ȴ�������ת������
 *
 * \return AM_TRUE : ����ת��
 *         AM_FALSE: ��ת��
 */
am_static_inline
am_bool_t amhw_zlg118_adc_always_convert_get (amhw_zlg118_adc_t *p_hw_adc)
{
    return (p_hw_adc->jqrstart & 0x1ul) ? AM_TRUE : AM_FALSE;
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

#endif /* __AMHW_ZLG118_ADC_H */

/* end of file */

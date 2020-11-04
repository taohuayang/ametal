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
 * \brief �߼���ʱ��ADTIM�ӿ�
 *
 * \internal
 * \par History
 * - 1.00 20-03-17  yrz, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZSN700_ADTIM_H
#define __AMHW_ZSN700_ADTIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "zsn700_regbase.h"

/**
 * \addtogroup amhw_zsn700_if_adtim
 * \copydoc amhw_zsn700_adtim.h
 * @{
 */

/**
 * \brief ��ʱ���Ĵ�����ṹ��
 */
typedef struct {
    __IO uint32_t cnter;          /**< \brief 0x000 ͨ�ü�����׼ֵ�Ĵ��� */
    __IO uint32_t perar;          /**< \brief 0x004 ͨ�����ڻ�׼ֵ�Ĵ��� */
    __IO uint32_t perbr;          /**< \brief 0x008 ͨ�����ڻ�׼ֵ����Ĵ���*/
    __IO uint32_t reserve0;       /**< \brief ����*/
    __IO uint32_t gcmxr[4];       /**< \brief 0x010 ͨ�ñȽ�A��B��C��D��׼ֵ�Ĵ��� */
    __IO uint32_t reserve1[2];    /**< \brief ����*/
    __IO uint32_t scmxr[2];       /**< \brief 0x028 ר�ñȽ�A��B��׼ֵ�Ĵ��� */
    __IO uint32_t reserve2[4];    /**< \brief ����*/
    __IO uint32_t dtuar;          /**< \brief 0x040 ����ʱ���׼ֵ�Ĵ��� */
    __IO uint32_t dtdar;          /**< \brief 0x044 ����ʱ���׼ֵ�Ĵ��� */
    __IO uint32_t reserve3[2];    /**< \brief ����*/
    __IO uint32_t gconr;          /**< \brief 0x050 ͨ�ÿ��ƼĴ��� */
    __IO uint32_t iconr;          /**< \brief 0x054 �жϿ��ƼĴ��� */
    __IO uint32_t pconr;          /**< \brief 0x058 �˿ڿ��ƼĴ��� */
    __IO uint32_t bconr;          /**< \brief 0x05C ������ƼĴ��� */
    __IO uint32_t dconr;          /**< \brief 0x060 �������ƼĴ��� */
    __IO uint32_t reserve4;       /**< \brief ����*/
    __IO uint32_t fconr;          /**< \brief 0x068 �˲����ƼĴ��� */
    __IO uint32_t vperr;          /**< \brief 0x06C ��Ч���ڼĴ��� */
    __IO uint32_t stflr;          /**< \brief 0x070 ״̬��־�Ĵ��� */
    __IO uint32_t hstar;          /**< \brief 0x074 Ӳ�������¼�ѡ��Ĵ��� */
    __IO uint32_t hstpr;          /**< \brief 0x078 Ӳ��ֹͣ�¼�ѡ��Ĵ��� */
    __IO uint32_t hcelr;          /**< \brief 0x07C Ӳ�������¼�ѡ��Ĵ��� */
    __IO uint32_t hcpar;          /**< \brief 0x080 Ӳ�������¼�ѡ��Ĵ��� */
    __IO uint32_t hcpbr;          /**< \brief 0x084 Ӳ�������¼�ѡ��Ĵ��� */
    __IO uint32_t hcupr;          /**< \brief 0x088 Ӳ���ݼ��¼�ѡ��Ĵ��� */
    __IO uint32_t hcdor;          /**< \brief 0x08C Ӳ���ݼ��¼�ѡ��Ĵ��� */
    __IO uint32_t reserve5[28];   /**< \brief ����*/
    __IO uint32_t ifr;            /**< \brief 0x100 �жϱ�־�Ĵ��� */
    __IO uint32_t iclr;           /**< \brief 0x104 �ж�����Ĵ��� */
    __IO uint32_t cr;             /**< \brief 0x108 չƵ���жϴ���ѡ��Ĵ��� */
    __IO uint32_t reserve6;       /**< \brief ����*/
    __IO uint32_t aossr;          /**< \brief 0x110 AOSѡ��Ĵ���,����ͨ������ */
    __IO uint32_t aoscl;          /**< \brief 0x114 AOSɲ����־����Ĵ���,����ͨ������ */
    __IO uint32_t ptbks;          /**< \brief 0x118 �˿�ɲ�����ƼĴ���,����ͨ������ */
    __IO uint32_t ttrig;          /**< \brief 0x11C �˿ڴ������ƼĴ���,����ͨ������ */
    __IO uint32_t itrig;          /**< \brief 0x120 AOS �������ƼĴ���,����ͨ������ */
    __IO uint32_t ptbkp;          /**< \brief 0x124 �˿�ɲ�����Կ��ƼĴ���, ����ͨ������ */
    __IO uint32_t reserve7[179];  /**< \brief ����*/
    __IO uint32_t sstar;          /**< \brief 0x3F4 ���ͬ�������Ĵ��� */
    __IO uint32_t sstpr;          /**< \brief 0x3F8 ���ͬ��ֹͣ�Ĵ��� */
    __IO uint32_t sclrr;          /**< \brief 0x3FC ���ͬ������Ĵ��� */
}amhw_zsn700_adtim_t;

/**
 * \brief ADT CHxͨ������
 */
typedef enum {
    AMHW_ZSN700_ADTIM_CHX_A = 0u,            /**< CHx Aͨ�� */
    AMHW_ZSN700_ADTIM_CHX_B = 1u,            /**< CHx Bͨ�� */
}amhw_zsn700_adtim_chx_t;

/**
 * \brief ADT TRIG�˿ڶ���
 */
typedef enum {
    AMHW_ZSN700_ADTIM_TRIG_PORT_A = 0u,   // TIMx ����A�˿�
    AMHW_ZSN700_ADTIM_TRIG_PORT_B = 1u,   // TIMx ����B�˿�
    AMHW_ZSN700_ADTIM_TRIG_PORT_C = 2u,   // TIMx ����C�˿�
    AMHW_ZSN700_ADTIM_TRIG_PORT_D = 3u,   // TIMx ����D�˿�
}amhw_zsn700_adtim_trig_port_t;

/**
 * \brief ADTͨ�ÿ��� - Z����������������
 */
typedef enum {
    AMHW_ZSN700_ADTIM_ZMASK_NO = 0u,  // Z���������ι�����Ч
    AMHW_ZSN700_ADTIM_ZMASK_4  = 1u,  // λ�ü���������������4�����������ڵ�Z�����뱻����
    AMHW_ZSN700_ADTIM_ZMASK_8  = 2u,  // λ�ü���������������8�����������ڵ�Z�����뱻����
    AMHW_ZSN700_ADTIM_ZMASK_16 = 3u,  // λ�ü���������������16�����������ڵ�Z�����뱻����
}amhw_zsn700_adtim_zmask_t;

/**
 * \brief ADTͨ�ÿ��� - ����ʱ��ѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_PCLK_DIV1    = 0ul,  // PCLK0
    AMHW_ZSN700_ADTIM_PCLK_DIV2    = 1ul,  // PCLK0/2
    AMHW_ZSN700_ADTIM_PCLK_DIV4    = 2ul,  // PCLK0/4
    AMHW_ZSN700_ADTIM_PCLK_DIV8    = 3ul,  // PCLK0/8
    AMHW_ZSN700_ADTIM_PCLK_DIV16   = 4ul,  // PCLK0/16
    AMHW_ZSN700_ADTIM_PCLK_DIV64   = 5ul,  // PCLK0/64
    AMHW_ZSN700_ADTIM_PCLK_DIV256  = 6ul,  // PCLK0/256
    AMHW_ZSN700_ADTIM_PCLK_DIV1024 = 7ul,  // PCLK0/1024
}amhw_zsn700_adtim_pclk_div_t;

/**
 * \brief ADT����ģʽ
 */
typedef enum {
    AMHW_ZSN700_ADTIM_CNT_MODE_SAWTOOTH   = 0u,  // ��ݲ�ģʽ
    AMHW_ZSN700_ADTIM_CNT_MODE_TRIANGLE_A = 4u,  // ���ǲ�Aģʽ
    AMHW_ZSN700_ADTIM_CNT_MODE_TRIANGLE_B = 5u,  // ���ǲ�Bģʽ
}amhw_zsn700_adtim_cnt_mode_t;

/**
 * \brief ADT��������
 */
typedef enum {
    AMHW_ZSN700_ADTIM_CNT_DIR_DOWN = 0u,        // �ݼ�����
    AMHW_ZSN700_ADTIM_CNT_DIR_UP   = 1u,        // �ݼӼ���
}amhw_zsn700_adtim_cnt_dir_t;

/**
 * \brief ADTͨ�ñȽϻ�׼
 */
typedef enum {
    AMHW_ZSN700_ADTIM_COMPARE_A = 0u,           // ͨ�ñȽϻ�׼A
    AMHW_ZSN700_ADTIM_COMPARE_B = 1u,           // ͨ�ñȽϻ�׼B
    AMHW_ZSN700_ADTIM_COMPARE_C = 2u,           // ͨ�ñȽϻ�׼C
    AMHW_ZSN700_ADTIM_COMPARE_D = 3u,           // ͨ�ñȽϻ�׼D
}amhw_zsn700_adtim_compare_x_t;

/**
 * \brief ADTר�ñȽϻ�׼
 */
typedef enum {
    AMHW_ZSN700_ADTIM_SPCL_COMP_A = 0u,         // ר�ñȽϻ�׼A
    AMHW_ZSN700_ADTIM_SPCL_COMP_B = 1u,         // ר�ñȽϻ�׼B
}amhw_zsn700_adtim_special_compare_x_t;

/**
 * \brief ADT�˿ڿ��� - TIMx���״̬����
 */
typedef enum {
    AMHW_ZSN700_ADTIM_DISVAL_NORM = 0u,  // ǿ�������Ч����0~3����������ʱ��CHx�˿��������
    AMHW_ZSN700_ADTIM_DISVAL_HIZ  = 1u,  // ǿ�������Ч����0~3����������ʱ��CHx�˿��������̬
    AMHW_ZSN700_ADTIM_DISVAL_LOW  = 2u,  // ǿ�������Ч����0~3����������ʱ��CHx�˿�����͵�ƽ
    AMHW_ZSN700_ADTIM_DISVAL_HIGH = 3u,  // ǿ�������Ч����0~3����������ʱ��CHx�˿�����ߵ�ƽ
}amhw_zsn700_adtim_disval_t;

/**
 * \brief ADT�˿ڿ��� - CHxǿ�������Ч����ѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_DISSEL0 = 0u,      // ѡ��ǿ�������Ч����0
    AMHW_ZSN700_ADTIM_DISSEL1 = 1u,      // ѡ��ǿ�������Ч����1
    AMHW_ZSN700_ADTIM_DISSEL2 = 2u,      // ѡ��ǿ�������Ч����2
    AMHW_ZSN700_ADTIM_DISSEL3 = 3u,      // ѡ��ǿ�������Ч����3
}amhw_zsn700_adtim_dissel_t;

/**
 * \brief ADT�˿ڿ��� - CHx����ֵƥ��ʱ�˿�״̬�趨
 */
typedef enum {
    AMHW_ZSN700_ADTIM_PERIOD_LOW  = 0u,  // ����������ֵ������ֵ���ʱ��CHx�˿��������Ϊ�͵�ƽ
    AMHW_ZSN700_ADTIM_PERIOD_HIGH = 1u,  // ����������ֵ������ֵ���ʱ��CHx�˿�����趨Ϊ�ߵ�ƽ
    AMHW_ZSN700_ADTIM_PERIOD_KEEP = 2u,  // ����������ֵ������ֵ���ʱ��CHx�˿�����趨Ϊ��ǰ״̬
    AMHW_ZSN700_ADTIM_PERIOD_INV  = 3u,  // ����������ֵ������ֵ���ʱ��CHx�˿�����趨Ϊ��ת��ƽ
}amhw_zsn700_adtim_perc_t;

/**
 * \brief ADT�˿ڿ��� - CHx�Ƚ�ֵƥ��ʱ�˿�״̬�趨
 */
typedef enum {
    AMHW_ZSN700_ADTIM_COMPARE_LOW  = 0u, // ������������GCMxR���ʱ��CHx�˿��������Ϊ�͵�ƽ
    AMHW_ZSN700_ADTIM_COMPARE_HIGH = 1u, // ������������GCMxR���ʱ��CHx�˿�����趨Ϊ�ߵ�ƽ
    AMHW_ZSN700_ADTIM_COMPARE_KEEP = 2u, // ������������GCMxR���ʱ��CHx�˿�����趨Ϊ��ǰ״̬
    AMHW_ZSN700_ADTIM_COMPARE_INV  = 3u, // ������������GCMxR���ʱ��CHx�˿�����趨Ϊ��ת��ƽ
}amhw_zsn700_adtim_cmpc_t;

/**
  * \brief ADT�˿ڿ��� - CHx�˿����
  */
typedef enum {
    AMHW_ZSN700_ADTIM_PORT_OUT_LOW  = 0u, // CHx�˿�����趨Ϊ�͵�ƽ
    AMHW_ZSN700_ADTIM_PORT_OUT_HIGH = 1u, // CHx�˿�����趨Ϊ�ߵ�ƽ
}amhw_zsn700_adtim_port_out_t;

/**
 * \brief ADT�˿ڿ��� - CHx�˿ڹ���ģʽѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_PORT_MODE_CMP_OUTPUT = 0u, // CHx�˿��趨Ϊ�Ƚ��������
    AMHW_ZSN700_ADTIM_PORT_MODE_CAP_INPUT  = 1u, // CHx�˿��趨Ϊ�������빦��
}amhw_zsn700_adtim_port_mode_t;

/**
 * \brief ADT�˿ڿ��� - CHx������ʼֹͣ�˿�״̬ѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_STATE_SEL_SS   = 0u, // ������ʼ��ֹͣʱ��CHx�˿������STACB��STPCB����
    AMHW_ZSN700_ADTIM_STATE_SEL_KEEP = 1u, // ������ʼ��ֹͣʱ��CHx�˿�����趨Ϊ��ǰ״̬
}amhw_zsn700_adtim_stastps_t;

/**
 * \brief ADT�������� - CHx���������趨
 */
typedef enum {
    AMHW_ZSN700_ADTIM_DtSeperate = 0u,      // DTUAR��DTDAR�ֱ��趨
    AMHW_ZSN700_ADTIM_DtEqual    = 1u,      // DTDAR��ֵ��DTUAR��ֵ�Զ����
}amhw_zsn700_adtim_sepa_t;

/**
 * \brief ADT�˲����� - TRIx/TIMxIx�˿��˲�������׼ʱ��ѡ��
 */
typedef enum
{
    AMHW_ZSN700_ADTIM_FLTCLK_PCLK_DIV1  = 0u, // PCLK0
    AMHW_ZSN700_ADTIM_FLTCLK_PCLK_DIV4  = 1u, // PCLK0/4
    AMHW_ZSN700_ADTIM_FLTCLK_PCLK_DIV16 = 2u, // PCLK0/16
    AMHW_ZSN700_ADTIM_FLTCLK_PCLK_DIV64 = 3u, // PCLK0/64
}amhw_zsn700_adtim_fltclk_pclkdiv_t;

/**
 * \brief ADT��Ч���� - TIMx��Ч����ѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_PeriodCnts0 = 0u,       // ��Ч����ѡ������Ч
    AMHW_ZSN700_ADTIM_PeriodCnts1 = 1u,       // ÿ��1��������Чһ��
    AMHW_ZSN700_ADTIM_PeriodCnts2 = 2u,       // ÿ��2��������Чһ��
    AMHW_ZSN700_ADTIM_PeriodCnts3 = 3u,       // ÿ��3��������Чһ��
    AMHW_ZSN700_ADTIM_PeriodCnts4 = 4u,       // ÿ��4��������Чһ��
    AMHW_ZSN700_ADTIM_PeriodCnts5 = 5u,       // ÿ��5��������Чһ��
    AMHW_ZSN700_ADTIM_PeriodCnts6 = 6u,       // ÿ��6��������Чһ��
    AMHW_ZSN700_ADTIM_PeriodCnts7 = 7u,       // ÿ��7��������Чһ��
}amhw_zsn700_adtim_pcnts_t;

/**
 * \brief ADT��Ч���� - ��������ѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_PeriodCnteDisable = 0u,  // ��Ч����ѡ������Ч
    AMHW_ZSN700_ADTIM_PeriodCnteMin     = 1u,  // ��ݲ������ϡ����������ǲ�������Ϊ��������
    AMHW_ZSN700_ADTIM_PeriodCnteMax     = 2u,  // ��ݲ������ϡ����������ǲ�������Ϊ��������
    AMHW_ZSN700_ADTIM_PeriodCnteBoth    = 3u,  // ��ݲ������ϡ����������ǲ����壬������Ϊ��������
}amhw_zsn700_adtim_pcnte_t;

/**
 * \brief ADT�˿ڴ������� - ����Դѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_TRIG_PA3  = 0u,    // PA3
    AMHW_ZSN700_ADTIM_TRIG_PB3  = 1u,    // PB3
    AMHW_ZSN700_ADTIM_TRIG_PC3  = 2u,    // PC3
    AMHW_ZSN700_ADTIM_TRIG_PD3  = 3u,    // PD3
    AMHW_ZSN700_ADTIM_TRIG_PA7  = 4u,    // PA7
    AMHW_ZSN700_ADTIM_TRIG_PB7  = 5u,    // PB7
    AMHW_ZSN700_ADTIM_TRIG_PC7  = 6u,    // PC7
    AMHW_ZSN700_ADTIM_TRIG_PD7  = 7u,    // PD7
    AMHW_ZSN700_ADTIM_TRIG_PA11 = 8u,    // PA11
    AMHW_ZSN700_ADTIM_TRIG_PB11 = 9u,    // PB11
    AMHW_ZSN700_ADTIM_TRIG_PC11 = 10u,   // PC11
    AMHW_ZSN700_ADTIM_TRIG_PD1  = 11u,   // PD1
    AMHW_ZSN700_ADTIM_TRIG_PA15 = 12u,   // PA15
    AMHW_ZSN700_ADTIM_TRIG_PB15 = 13u,   // PB15
    AMHW_ZSN700_ADTIM_TRIG_PC5  = 14u,   // PC5
    AMHW_ZSN700_ADTIM_TRIG_PD5  = 15u,   // PD5
}amhw_zsn700_adtim_trigsel_t;

/**
 * \brief ADT AOS�������� - AOSx����Դѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_AosxTrigSelTim0Int   = 0u,    // TIM0_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelTim1Int   = 1u,    // TIM1_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelTim2Int   = 2u,    // TIM2_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelLpTimInt  = 3u,    // LPTIMER_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelTim4Int   = 4u,    // TIM4_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelTim5Int   = 5u,    // TIM5_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelTim6Int   = 6u,    // TIM6_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelUart0Int  = 7u,    // UART0_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelUart1Int  = 8u,    // UART1_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelLpUartInt = 9u,    // LPUART_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelVc0Int    = 10u,   // VC0_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelVc1Int    = 11u,   // VC1_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelRtcInt    = 12u,   // RTC_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelPcaInt    = 13u,   // PCA_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelSpiInt    = 14u,   // SPI_INT
    AMHW_ZSN700_ADTIM_AosxTrigSelAdcInt    = 15u,   // ADC_INT
}amhw_zsn700_adtim_iaosxs_t;

/**
 * \brief ADTӲ��(����/ֹͣ/����/����)�¼�����ѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_HwTrigAos0        = 0u,       // ��AOS�����¼�����0��Ч
    AMHW_ZSN700_ADTIM_HwTrigAos1        = 1u,       // ��AOS�����¼�����1��Ч
    AMHW_ZSN700_ADTIM_HwTrigAos2        = 2u,       // ��AOS�����¼�����2��Ч
    AMHW_ZSN700_ADTIM_HwTrigAos3        = 3u,       // ��AOS�����¼�����3��Ч
    AMHW_ZSN700_ADTIM_HwTrigCHxARise    = 4u,       // CHxA�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwTrigCHxAFall    = 5u,       // CHxA�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwTrigCHxBRise    = 6u,       // CHxB�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwTrigCHxBFall    = 7u,       // CHxB�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwTrigTimTriARise = 8u,       // TIMTRIA�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwTrigTimTriAFall = 9u,       // TIMTRIA�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwTrigTimTriBRise = 10u,      // TIMTRIB�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwTrigTimTriBFall = 11u,      // TIMTRIB�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwTrigTimTriCRise = 12u,      // TIMTRIC�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwTrigTimTriCFall = 13u,      // TIMTRIC�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwTrigTimTriDRise = 14u,      // TIMTRID�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwTrigTimTriDFall = 15u,      // TIMTRID�˿��ϲ������½���
}amhw_zsn700_adtim_hw_trig_t;

/**
 * \brief ADTӲ��(�ݼ�/�ݼ�)�¼�����ѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_HwCntCHxALowCHxBRise   = 0u,  // CHxA�˿�Ϊ�͵�ƽʱ��CHxB�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwCntCHxALowCHxBFall   = 1u,  // CHxA�˿�Ϊ�͵�ƽʱ��CHxB�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwCntCHxAHighCHxBRise  = 2u,  // CHxA�˿�Ϊ�ߵ�ƽʱ��CHxB�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwCntCHxAHighCHxBFall  = 3u,  // CHxA�˿�Ϊ�ߵ�ƽʱ��CHxB�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwCntCHxBLowCHxARise   = 4u,  // CHxB�˿�Ϊ�͵�ƽʱ��CHxA�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwCntCHxBLowCHxAFall   = 5u,  // CHxB�˿�Ϊ�͵�ƽʱ��CHxA�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwCntCHxBHighChxARise  = 6u,  // CHxB�˿�Ϊ�ߵ�ƽʱ��CHxA�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwCntCHxBHighCHxAFall  = 7u,  // CHxB�˿�Ϊ�ߵ�ƽʱ��CHxA�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwCntTimTriARise       = 8u,  // TIMTRIA�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwCntTimTriAFall       = 9u,  // TIMTRIA�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwCntTimTriBRise       = 10u, // TIMTRIB�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwCntTimTriBFall       = 11u, // TIMTRIB�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwCntTimTriCRise       = 12u, // TIMTRIC�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwCntTimTriCFall       = 13u, // TIMTRIC�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwCntTimTriDRise       = 14u, // TIMTRID�˿��ϲ�����������
    AMHW_ZSN700_ADTIM_HwCntTimTriDFall       = 15u, // TIMTRID�˿��ϲ������½���
    AMHW_ZSN700_ADTIM_HwCntAos0              = 16u, // ��AOS�����¼�����0��Ч
    AMHW_ZSN700_ADTIM_HwCntAos1              = 17u, // ��AOS�����¼�����1��Ч
    AMHW_ZSN700_ADTIM_HwCntAos2              = 18u, // ��AOS�����¼�����2��Ч
    AMHW_ZSN700_ADTIM_HwCntAos3              = 19u, // ��AOS�����¼�����3��Ч
}amhw_zsn700_adtim_hw_cnt_t;

/**
 * \brief ADT�˿�ɲ�����Կ���
 */
typedef enum {
    AMHW_ZSN700_ADTIM_PtBrkHigh = 0u,              // �˿�ɲ�����Ըߵ�ƽ��Ч
    AMHW_ZSN700_ADTIM_PtBrkLow  = 1u,              // �˿�ɲ�����Ե͵�ƽ��Ч
}amhw_zsn700_adtim_ptbrk_polarity_t;

/**
 * \brief ADT PWMչƵ����ѡ��
 */
typedef enum {
    AMHW_ZSN700_ADTIM_PwmDitherUnderFlow = 0u,     // PWMչƵ���������
    AMHW_ZSN700_ADTIM_PwmDitherOverFlow  = 1u,     // PWMչƵ���������
}amhw_zsn700_adtim_pwm_dither_type_t;

/**
 * \brief ADT�ж�����
 */
typedef enum {
    AMHW_ZSN700_ADTIM_CMAIrq  = 0u,                // ����ƥ��A���򲶻����룩�ж�
    AMHW_ZSN700_ADTIM_CMBIrq  = 1u,                // ����ƥ��B���򲶻����룩�ж�
    AMHW_ZSN700_ADTIM_CMCIrq  = 2u,                // ����ƥ��C�ж�
    AMHW_ZSN700_ADTIM_CMDIrq  = 3u,                // ����ƥ��D�ж�
    AMHW_ZSN700_ADTIM_OVFIrq  = 6u,                // ����ƥ���ж�
    AMHW_ZSN700_ADTIM_UDFIrq  = 7u,                // ����ƥ���ж�
    AMHW_ZSN700_ADTIM_DTEIrq  = 8u,                // ����ʱ������ж�
    AMHW_ZSN700_ADTIM_SAMLIrq = 14u,               // ͬ���ж�
    AMHW_ZSN700_ADTIM_SAMHIrq = 15u,               // ͬ���ж�
}amhw_zsn700_adtim_irq_type_t;

/**
 * \brief ADT��־����
 */
typedef enum {
    AMHW_ZSN700_ADTIM_CMAF = 0,                    // ����ƥ��A��־
    AMHW_ZSN700_ADTIM_CMBF = 1,                    // ����ƥ��B��־
    AMHW_ZSN700_ADTIM_CMCF = 2,                    // ����ƥ��C��־
    AMHW_ZSN700_ADTIM_CMDF = 3,                    // ����ƥ��D��־
    AMHW_ZSN700_ADTIM_OVFF = 6,                    // ����ƥ���־
    AMHW_ZSN700_ADTIM_UDFF = 7,                    // ����ƥ���־
    AMHW_ZSN700_ADTIM_DTEF = 8,                    // ����ʱ������־
    AMHW_ZSN700_ADTIM_CMSAUF = 9,                  // ���ϼ���ר�ñȽϻ�׼ֵƥ��A��־
    AMHW_ZSN700_ADTIM_CMSADF = 10,                 // ���¼���ר�ñȽϻ�׼ֵƥ��B��־
    AMHW_ZSN700_ADTIM_CMSBUF = 11,                 // ���ϼ���ר�ñȽϻ�׼ֵƥ��A��־
    AMHW_ZSN700_ADTIM_CMSBDF = 12,                 // ���¼���ר�ñȽϻ�׼ֵƥ��B��־
    AMHW_ZSN700_ADTIM_CntDir = 31,                 // ��������
}amhw_zsn700_adtim_state_type_t;

/**
 * \brief ADT���ͬ������
 */
typedef struct {
    am_bool_t adtim4;                              // Timer 4
    am_bool_t adtim5;                              // Timer 5
    am_bool_t adtim6;                              // Timer 6
}amhw_zsn700_adtim_sw_sync_t;

/**
 * \brief ADT AOS��������
 */
typedef struct {
    amhw_zsn700_adtim_iaosxs_t   aos0trig_src;     // AOS0����Դѡ��
    amhw_zsn700_adtim_iaosxs_t   aos1trig_src;     // AOS1����Դѡ��
    amhw_zsn700_adtim_iaosxs_t   aos2trig_src;     // AOS2����Դѡ��
    amhw_zsn700_adtim_iaosxs_t   aos3trig_src;     // AOS3����Դѡ��
}amhw_zsn700_adtim_aos_trig_cfg_t;

/**
 * \brief ADT �жϴ�������
 */
typedef struct {
    am_bool_t   specilmatch_B_trigdma;  // ר�ñȽϻ�׼ֵƥ��Bʹ�ܴ���DMA
    am_bool_t   specilmatch_A_trigdma;  // ר�ñȽϻ�׼ֵƥ��Aʹ�ܴ���DMA
    am_bool_t   underflow_trigdma;      // ����ƥ��ʹ�ܴ���DMA
    am_bool_t   overflow_trigdma;       // ����ƥ��ʹ�ܴ���DMA
    am_bool_t   cntmatch_D_trigdma;     // ����ƥ��Dʹ�ܴ���DMA
    am_bool_t   cntmatch_C_trigdma;     // ����ƥ��Cʹ�ܴ���DMA
    am_bool_t   cntmatch_B_trigdma;     // ����ƥ��Bʹ�ܴ���DMA
    am_bool_t   cntmatch_A_trigdma;     // ����ƥ��Aʹ�ܴ���DMA
    am_bool_t   specilmatch_B_trig;     // ר�ñȽϻ�׼ֵƥ��Bʹ�ܴ���ADC
    am_bool_t   specilmatch_A_trig;     // ר�ñȽϻ�׼ֵƥ��Aʹ�ܴ���ADC
    am_bool_t   underflow_trig;         // ����ƥ��ʹ�ܴ���ADC
    am_bool_t   overflow_trig;          // ����ƥ��ʹ�ܴ���ADC
    am_bool_t   cntmatch_D_trig;        // ����ƥ��Dʹ�ܴ���ADC
    am_bool_t   cntmatch_C_trig;        // ����ƥ��Cʹ�ܴ���ADC
    am_bool_t   cntmatch_B_trig;        // ����ƥ��Bʹ�ܴ���ADC
    am_bool_t   cntmatch_A_trig;        // ����ƥ��Aʹ�ܴ���ADC
}amhw_zsn700_adtim_irq_trig_cfg_t;

/**
 * \brief ADT Trig�˿�����
 */
typedef struct {
    amhw_zsn700_adtim_trigsel_t        trigsrc;      // ����Դѡ��
    am_bool_t                          flt_enable;   // ����Դ���������˲�ʹ��
    amhw_zsn700_adtim_fltclk_pclkdiv_t fltclk;       // �˲�������׼ʱ��
}amhw_zsn700_adtim_port_trig_cfg_t;

/**
 * \brief ADT Z���������ι�������
 */
typedef struct {
    amhw_zsn700_adtim_zmask_t zmask_cycle;   // Z���������μ�������ѡ��
    am_bool_t                 fltposcntmask; // Z������ʱ�����������ڣ�λ�ü����������㹦�ܲ����Σ�FALSE��������(TRUE)
    am_bool_t                 fltrevcntmask; // Z������ʱ�����������ڣ���ת�������ļ������ܲ����Σ�FALSE��������(TRUE)
}amhw_zsn700_adtim_zmask_cfg_t;

/**
 * \brief ADT TIMxX�˿�����
 */
typedef struct {
    amhw_zsn700_adtim_port_mode_t portmode;    // �˿ڹ���ģʽ
    am_bool_t                     outenable;   // ���ʹ��
    amhw_zsn700_adtim_perc_t      perc;        // ����ֵƥ��ʱ�˿�״̬
    amhw_zsn700_adtim_cmpc_t      cmpc;        // �Ƚ�ֵƥ��ʱ�˿�״̬
    amhw_zsn700_adtim_stastps_t   stastps;     // ������ʼֹͣ�˿�״̬ѡ��
    amhw_zsn700_adtim_port_out_t  staout;      // ������ʼ�˿����״̬
    amhw_zsn700_adtim_port_out_t  stpout;      // ����ֹͣ�˿����״̬
    amhw_zsn700_adtim_disval_t    disval;      // ǿ�������Чʱ���״̬����
    amhw_zsn700_adtim_dissel_t    dissel;      // ǿ�������Ч����ѡ��
    am_bool_t                     fltenable;   // �˿ڲ��������˲�ʹ��
    amhw_zsn700_adtim_fltclk_pclkdiv_t fltclk; // �˿��˲�������׼ʱ��
}amhw_zsn700_adtim_timx_chx_port_cfg_t;

/**
 * \brief ADTɲ���˿�����
 */
typedef struct {
    am_bool_t                          portenable;    // �˿�ʹ��
    amhw_zsn700_adtim_ptbrk_polarity_t polaritysel;   // ����ѡ��
}amhw_zsn700_adtim_break_port_cfg_t;

/**
 * \brief ADT��Ч����3����
 */
typedef struct amhw_zsn700_adtim_disable_3_cfg
{
    amhw_zsn700_adtim_break_port_cfg_t stcbrkptcfg[16]; // ɲ���˿�����
    am_bool_t                          fltenable;       // ɲ���˿��˲�ʹ��
    amhw_zsn700_adtim_fltclk_pclkdiv_t fltclk;          // �˲�������׼ʱ��
}amhw_zsn700_adtim_disable_3_cfg_t;

/**
 * \brief ADT��Ч����1����
 */
typedef struct {
    am_bool_t   tim6_outsh;     // TIM6���ͬ��
    am_bool_t   tim5_outsh;     // TIM5���ͬ��
    am_bool_t   tim4_outsh;     // TIM4���ͬ��
    am_bool_t   tim6_outsl;     // TIM6���ͬ��
    am_bool_t   tim5_outsl;     // TIM5���ͬ��
    am_bool_t   tim4_outsl;     // TIM4���ͬ��
}amhw_zsn700_adtim_disable_1_cfg_t;

/**
 * \brief ADT PWMչƵ��������
 */
typedef struct {
    amhw_zsn700_adtim_pwm_dither_type_t enAMHW_ZSN700_ADTIM_PDType;// PWMչƵ����ѡ��
    am_bool_t   bTimxBPDEn;                      // PWMͨ��BչƵʹ��
    am_bool_t   bTimxAPDEn;                      // PWMͨ��AչƵʹ��
}amhw_zsn700_adtim_pwm_dither_cfg_t;

/**
 * \brief ADT������������
 */
typedef struct {
    amhw_zsn700_adtim_cnt_mode_t cntmode;        // ����ģʽ
    amhw_zsn700_adtim_cnt_dir_t  cntdir;         // ��������
    amhw_zsn700_adtim_pclk_div_t cntclkdiv;      // ����ʱ��ѡ��
}amhw_zsn700_adtim_basecnt_cfg_t;

/**
 * \brief ADT����״̬
 */
typedef struct {
    uint16_t  u16counter;                        // ��ǰ�������ļ���ֵ
    am_bool_t cntdir;                            // ��������
    uint8_t   u8validperiod;                     // ��Ч���ڼ���
    am_bool_t cmsbdf;                            // ���¼���ר�ñȽϻ�׼ֵƥ��B��־
    am_bool_t cmsbuf;                            // ���ϼ���ר�ñȽϻ�׼ֵƥ��A��־
    am_bool_t cmsadf;                            // ���¼���ר�ñȽϻ�׼ֵƥ��B��־
    am_bool_t cmsauf;                            // ���ϼ���ר�ñȽϻ�׼ֵƥ��A��־
    am_bool_t dtff;                              // ����ʱ������־
    am_bool_t udff;                              // ����ƥ���־
    am_bool_t ovff;                              // ����ƥ���־
    am_bool_t cmdf;                              // ����ƥ��D��־
    am_bool_t cmcf;                              // ����ƥ��C��־
    am_bool_t cmbf;                              // ����ƥ��B��־
    am_bool_t cmaf;                              // ����ƥ��A��־
}amhw_zsn700_adtim_cntstate_cfg_t;

/**
 * \brief ADT��Ч��������
 */
typedef struct {
    amhw_zsn700_adtim_pcnts_t    validcnt;       // ��Ч����ѡ��
    amhw_zsn700_adtim_pcnte_t    validcdt;       // ��Ч���ڼ�������
    am_bool_t                    period_D;       // ͨ���ź���Ч����ѡ��D
    am_bool_t                    period_C;       // ͨ���ź���Ч����ѡ��C
    am_bool_t                    period_B;       // ͨ���ź���Ч����ѡ��B
    am_bool_t                    period_A;       // ͨ���ź���Ч����ѡ��A
}amhw_zsn700_adtim_validper_cfg_t;

/**
 * \brief ����Ӳ���ݼ��¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_zsn700_adtim_hw_cnt_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfghwcntup(amhw_zsn700_adtim_t       *p_hw_adtim,
                                       amhw_zsn700_adtim_hw_cnt_t choice) {

    if(choice > AMHW_ZSN700_ADTIM_HwCntAos3) {
        return AM_FALSE;
    }

    p_hw_adtim->hcupr |= (1ul << choice);

    return AM_TRUE;
}

/**
 * \brief ���Ӳ���ݼ��¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearhwcntup(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hcupr = 0;

    return AM_TRUE;
}

/**
 * \brief ����Ӳ���ݼ��¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_zsn700_adtim_hw_cnt_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfghwcntdown(amhw_zsn700_adtim_t       *p_hw_adtim,
                                         amhw_zsn700_adtim_hw_cnt_t choice) {
    if(choice > AMHW_ZSN700_ADTIM_HwCntAos3) {
        return AM_FALSE;
    }

    p_hw_adtim->hcdor |= (1ul << choice);

    return AM_TRUE;
}

/**
 * \brief ���Ӳ���ݼ��¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearhwcntdown(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hcdor = 0;

    return AM_TRUE;
}

/**
 * \brief ����Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_zsn700_adtim_hw_trig_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfghwstart(amhw_zsn700_adtim_t        *p_hw_adtim,
                                       amhw_zsn700_adtim_hw_trig_t choice) {
    if(choice > AMHW_ZSN700_ADTIM_HwTrigTimTriDFall) {
        return AM_FALSE;
    }

    p_hw_adtim->hstar |= (1ul << choice);

    return AM_TRUE;
}

/**
 * \brief ���Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearhwstart(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hstar = 0;

    return AM_TRUE;
}

/**
 * \brief ʹ��Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_enablehwstart(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hstar |= (1ul << 31);

    return AM_TRUE;
}

/**
 * \brief ��ֹӲ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_disablehwstart(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hstar &= ~(1ul << 31);

    return AM_TRUE;
}

/**
 * \brief ����Ӳ��ֹͣ�¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_zsn700_adtim_hw_trig_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfghwstop(amhw_zsn700_adtim_t        *p_hw_adtim,
                                      amhw_zsn700_adtim_hw_trig_t choice) {

    if(choice > AMHW_ZSN700_ADTIM_HwTrigTimTriDFall) {
        return AM_FALSE;
    }

    p_hw_adtim->hstpr |= (1ul << choice);

    return AM_TRUE;
}

/**
 * \brief ���Ӳ��ֹͣ�¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearhwstop(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hstpr = 0;

    return AM_TRUE;
}

/**
 * \brief ʹ��Ӳ��ֹͣ�¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_enablehwstop(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hstpr |= (1ul << 31);

    return AM_TRUE;
}

/**
 * \brief ��ֹӲ��ֹͣ�¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_disablehwstop(amhw_zsn700_adtim_t *p_hw_adtim){

    p_hw_adtim->hstpr &= ~(1ul << 31);

    return AM_TRUE;
}

/**
 * \brief ����Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_zsn700_adtim_hw_trig_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfghwclear(amhw_zsn700_adtim_t        *p_hw_adtim,
                                       amhw_zsn700_adtim_hw_trig_t choice) {

    if(choice > AMHW_ZSN700_ADTIM_HwTrigTimTriDFall) {
        return AM_FALSE;
    }

    p_hw_adtim->hcelr |= (1ul << choice);

    return AM_TRUE;
}

/**
 * \brief ���Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearhwclear(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hcelr = 0;

    return AM_TRUE;
}

/**
 * \brief ʹ��Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_enablehwclear(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hcelr |= (1ul << 31);

    return AM_TRUE;
}

/**
 * \brief ��ֹӲ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_disablehwclear(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hcelr &= ~(1ul << 31);

    return AM_TRUE;
}

/**
 * \brief ����Aͨ��Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_zsn700_adtim_hw_trig_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfghwcaptureA(amhw_zsn700_adtim_t        *p_hw_adtim,
                                          amhw_zsn700_adtim_hw_trig_t choice) {

    if(choice > AMHW_ZSN700_ADTIM_HwTrigTimTriDFall) {
        return AM_FALSE;
    }

    p_hw_adtim->hcpar |= (1ul << choice);
    p_hw_adtim->pconr |= (1ul << 0 );

    return AM_TRUE;
}

/**
 * \brief ���Aͨ��Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearhwcaptureA(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hcpar = 0;

    return AM_TRUE;
}

/**
 * \brief ����Bͨ��Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] choice     : amhw_zsn700_adtim_hw_trig_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfghwcaptureB(amhw_zsn700_adtim_t        *p_hw_adtim,
                                          amhw_zsn700_adtim_hw_trig_t choice) {

    if(choice > AMHW_ZSN700_ADTIM_HwTrigTimTriDFall) {
        return AM_FALSE;
    }

    p_hw_adtim->hcpbr |= (1ul << choice);
    p_hw_adtim->pconr |= (1ul << 16 );

    return AM_TRUE;
}

/**
 * \brief ���Bͨ��Ӳ�������¼�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearhwcaptureB(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->hcpbr = 0;

    return AM_TRUE;
}

/**
 * \brief ���ͬ������
 *
 * \param[in] p_cfg : ָ��ADT���ͬ�����ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_swsyncstart(amhw_zsn700_adtim_sw_sync_t *p_cfg) {

    if(p_cfg->adtim4) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sstar = (1ul << 0);
    }

    if(p_cfg->adtim5) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sstar = (1ul << 1);
    }

    if(p_cfg->adtim6) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sstar = (1ul << 2);
    }

    return AM_TRUE;
}

/**
 * \brief ���ͬ��ֹͣ
 *
 * \param[in] p_cfg : ָ��ADT���ͬ�����ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_swsyncstop(amhw_zsn700_adtim_sw_sync_t *p_cfg) {

    if(p_cfg->adtim4) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sstpr = (1ul << 0);
    }
    if(p_cfg->adtim5) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sstpr = (1ul << 1);
    }
    if(p_cfg->adtim6) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sstpr = (1ul << 2);
    }

    return AM_TRUE;
}

/**
 * \brief ���ͬ������
 *
 * \param[in] p_cfg : ָ��ADT���ͬ�����ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_swsyncclear(amhw_zsn700_adtim_sw_sync_t *p_cfg) {

    if(p_cfg->adtim4) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sclrr = (1ul << 0);
    }
    if(p_cfg->adtim5) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sclrr = (1ul << 1);
    }
    if(p_cfg->adtim6) {
        ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->sclrr = (1ul << 2);
    }

    return AM_TRUE;
}

/**
 * \brief ��ȡ���ͬ��״̬
 *
 * \param[in] p_cfg : ָ��ADT���ͬ�����ýṹ���ָ��
 *
 * \return AM_FALSE ����ȡʧ��
 *         AM_TRUE  ����ȡ�ɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setswsyncstate(amhw_zsn700_adtim_sw_sync_t *p_cfg) {

    amhw_zsn700_adtim_t *p_hw_adtim4 = (amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE;

    p_cfg->adtim4 = (p_hw_adtim4->sstar >> 0) & 1ul ? AM_TRUE : AM_FALSE;
    p_cfg->adtim5 = (p_hw_adtim4->sstar >> 1) & 1ul ? AM_TRUE : AM_FALSE;
    p_cfg->adtim6 = (p_hw_adtim4->sstar >> 2) & 1ul ? AM_TRUE : AM_FALSE;

    return AM_TRUE;
}

/**
 * \brief AOS��������
 *
 * \param[in] p_cfg : ָ��AOS�������ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_aostrigcfg(amhw_zsn700_adtim_aos_trig_cfg_t *p_cfg){

    amhw_zsn700_adtim_t *p_hw_adtim4 = (amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE;

    if(p_cfg == NULL) {
        return AM_FALSE;
    }

    p_hw_adtim4->itrig  = 0;
    p_hw_adtim4->itrig |= (p_cfg->aos0trig_src << 0);
    p_hw_adtim4->itrig |= (p_cfg->aos1trig_src << 4);
    p_hw_adtim4->itrig |= (p_cfg->aos2trig_src << 8);
    p_hw_adtim4->itrig |= (p_cfg->aos3trig_src << 12);

    return AM_TRUE;
}

/**
 * \brief �жϴ���ʹ������
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] p_cfg      : ָ���ж�ʹ�����ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_bool_t amhw_zsn700_adtim_irqtrigcfg(
              amhw_zsn700_adtim_t              *p_hw_adtim,
              amhw_zsn700_adtim_irq_trig_cfg_t *p_cfg);

/**
 * \brief �˿ڴ�������
 *
 * \param[in] trigport : amhw_zsn700_adtim_trig_port_t�˿�ö����
 * \param[in] p_cfg    : ָ��˿����ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_bool_t amhw_zsn700_adtim_porttrigcfg(
              amhw_zsn700_adtim_trig_port_t      trigport,
              amhw_zsn700_adtim_port_trig_cfg_t *p_cfg);

/**
 * \brief CHxX�˿�����
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] port       : amhw_zsn700_adtim_chx_tͨ��ö����
 * \param[in] p_cfg      : ָ��TIMxX�˿����ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_bool_t amhw_zsn700_adtim_timxchxportcfg(
              amhw_zsn700_adtim_t                   *p_hw_adtim,
              amhw_zsn700_adtim_chx_t                port,
              amhw_zsn700_adtim_timx_chx_port_cfg_t *p_cfg);

/**
 * \brief ʹ�ܶ˿�ɲ��
 *
 * \param[in] port       : �˿ڱ�ţ�0~15��
 * \param[in] p_cfg      : ָ��TADTɲ���˿����ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_enablebrakeport(
              uint8_t                             port,
              amhw_zsn700_adtim_break_port_cfg_t *p_cfg) {

    amhw_zsn700_adtim_t *p_hw_adtim4 = (amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE;

    if(p_cfg == NULL) {
        return AM_FALSE;
    }

    p_hw_adtim4->ptbkp &= ~(1ul << port);
    p_hw_adtim4->ptbkp |= (p_cfg->polaritysel << port);
    p_hw_adtim4->ptbks |= (1ul << port);

    return AM_TRUE;
}

/**
 * \brief ����˿�ɲ��
 */
am_static_inline
void amhw_zsn700_adtim_clearbrakeport(void) {

    ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->ptbks = 0;
}

/**
 * \brief ��Ч����3����(�˿�ɲ��)
 *
 * \param[in] p_cfg      : ָ��TADT��Ч����3���ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_bool_t amhw_zsn700_adtim_disable3cfg(
              amhw_zsn700_adtim_disable_3_cfg_t *p_cfg);

/**
 * \brief ���ɲ�� Enable/Disable(����������Ч����3ʹ�ܵ������)
 *
 * \param[in] flag      : AM_FALSE(����) ��       AM_TRUE(ʹ��)
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_swbrake(am_bool_t flag) {

    amhw_zsn700_adtim_t *p_hw_adtim4 = (amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE;

    p_hw_adtim4->aossr &= ~(1ul << 7);
    p_hw_adtim4->aossr |= (flag << 7);

    return AM_TRUE;
}

/**
 * \brief ��ȡ�˿�ɲ����־
 *
 * \return AM_FALSE ������״̬
 *         AM_TRUE  ��ʹ��״̬
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_getportbrakeflag(void) {
    return ((((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->aossr >> 0) & 1ul) ?
           AM_TRUE :
           AM_FALSE;
}

/**
 * \brief ����˿�ɲ����־
 *
 */
am_static_inline
void amhw_zsn700_adtim_clearportbrakeflag(void) {

    ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->aoscl &= ~(1ul << 0);
}

/**
 * \brief ��Ч����1����(ͬ��ͬ��ɲ��)
 *
 * \param[in] p_cfg : ָ��TADT��Ч����1���ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_disable1Cfg(
              amhw_zsn700_adtim_disable_1_cfg_t *p_cfg) {

    amhw_zsn700_adtim_t *p_hw_adtim4 = (amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE;

    if(p_cfg == NULL) {
        return AM_FALSE;
    }

    p_hw_adtim4->aossr = (p_hw_adtim4->aossr & (~(1ul << 13))) |
                         (p_cfg->tim6_outsh << 13);
    p_hw_adtim4->aossr = (p_hw_adtim4->aossr & (~(1ul << 12))) |
                         (p_cfg->tim5_outsh << 12);
    p_hw_adtim4->aossr = (p_hw_adtim4->aossr & (~(1ul << 11))) |
                         (p_cfg->tim4_outsh << 11);
    p_hw_adtim4->aossr = (p_hw_adtim4->aossr & (~(1ul << 10))) |
                         (p_cfg->tim6_outsl << 10);
    p_hw_adtim4->aossr = (p_hw_adtim4->aossr & (~(1ul << 9))) |
                         (p_cfg->tim5_outsl << 9);
    p_hw_adtim4->aossr = (p_hw_adtim4->aossr & (~(1ul << 8))) |
                         (p_cfg->tim4_outsl << 8);

    return AM_TRUE;
}

/**
 * \brief ��ȡͬ��ͬ��ɲ����־
 *
 * \return AM_FALSE ��0
 *         AM_TRUE  ��1
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_getsamebrakeflag(void) {
    return ((((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->aossr >> 1) & 1ul) ?
           AM_TRUE :
           AM_FALSE;
}

/**
 * \brief ���ͬ��ͬ��ɲ����־
 *
 */
am_static_inline
void amhw_zsn700_adtim_clearsamebrakeflag(void) {
    ((amhw_zsn700_adtim_t *)ZSN700_TIM4_BASE)->aoscl &= ~(1ul << 1);
}

/**
 * \brief PWMչƵ����
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] p_cfg      : ָ��PWMչƵ�������ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_pwmdithercfg(
              amhw_zsn700_adtim_t                *p_hw_adtim,
              amhw_zsn700_adtim_pwm_dither_cfg_t *p_cfg) {
    if(p_cfg == NULL) {
        return AM_FALSE;
    }

    p_hw_adtim->cr = (p_hw_adtim->cr & (~(1ul << 10))) |
                     (p_cfg->enAMHW_ZSN700_ADTIM_PDType << 10);
    p_hw_adtim->cr = (p_hw_adtim->cr & (~(1ul << 9))) |
                     (p_cfg->bTimxBPDEn << 9);
    p_hw_adtim->cr = (p_hw_adtim->cr & (~(1ul << 8))) |
                     (p_cfg->bTimxAPDEn << 8);

    return AM_TRUE;
}

/**
 * \brief ADTIM��ʼ��
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] p_cfg      : ָ��ADT�����������ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_init(amhw_zsn700_adtim_t             *p_hw_adtim,
                                 amhw_zsn700_adtim_basecnt_cfg_t *p_cfg) {
    if(p_cfg == NULL) {
        return AM_FALSE;
    }

    if((p_cfg->cntmode) > AMHW_ZSN700_ADTIM_CNT_MODE_TRIANGLE_B) {
        return AM_FALSE;
    }

    p_hw_adtim->gconr &= ~(7ul << 1);
    p_hw_adtim->gconr &= ~(7ul << 4);
    p_hw_adtim->gconr &= ~(1ul << 8);

    p_hw_adtim->gconr |= (p_cfg->cntmode << 1);
    p_hw_adtim->gconr |= (p_cfg->cntclkdiv << 4);
    p_hw_adtim->gconr |= (p_cfg->cntdir << 8);

    return AM_TRUE;
}

am_static_inline
amhw_zsn700_adtim_pclk_div_t
amhw_zsn700_adtim_clkdiv_get(amhw_zsn700_adtim_t *p_hw_adtim) {

    return (amhw_zsn700_adtim_pclk_div_t)((p_hw_adtim->gconr >> 4) & 7ul);
}


/**
 * \brief ADTIMȥ��ʼ��
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_bool_t amhw_zsn700_adtim_deinit(amhw_zsn700_adtim_t *p_hw_adtim);

/**
 * \brief ADTIM����
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_startcount(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->gconr |= (1ul << 0);

    return AM_TRUE;
}

/**
 * \brief ADTIMֹͣ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_stopcount(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->gconr &= ~(1ul << 0);

    return AM_TRUE;
}

/**
 * \brief ���ü���ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] cnt        �� ����ֵ�趨
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setcount(amhw_zsn700_adtim_t *p_hw_adtim,
                                     uint16_t             cnt) {

    p_hw_adtim->cnter = cnt;

    return AM_TRUE;
}

/**
 * \brief ��ȡ����ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint16_t amhw_zsn700_adtim_getcount(amhw_zsn700_adtim_t *p_hw_adtim) {
    return p_hw_adtim->cnter;
}

/**
 * \brief �������ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearcount(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->cnter = 0;

    return AM_TRUE;
}

/**
 * \brief ��ȡ��Ч���ڼ���ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return ��Ч���ڼ���ֵ
 */
am_static_inline
uint8_t amhw_zsn700_adtim_getvpernum(amhw_zsn700_adtim_t *p_hw_adtim) {
    return ((p_hw_adtim->stflr >> 21) & 0x7ul);
}

/**
 * \brief ��ȡ״̬��־
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_zsn700_adtim_state_type_t״̬��־ö����
 *
 * \return AM_FALSE ����־��Ч
 *         AM_TRUE  ����־��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_getstate(amhw_zsn700_adtim_t           *p_hw_adtim,
                                     amhw_zsn700_adtim_state_type_t type) {
    return ((p_hw_adtim->stflr >> type) & 1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ���ü�������
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] data       : ���������趨ֵ
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setperiod(amhw_zsn700_adtim_t *p_hw_adtim,
                                      uint16_t             data) {

    p_hw_adtim->perar = data;

    return AM_TRUE;
}

/**
 * \brief ��ȡ��������
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return ��������
 */
am_static_inline
uint16_t amhw_zsn700_adtim_getperiod(amhw_zsn700_adtim_t *p_hw_adtim) {

    return p_hw_adtim->perar;
}

/**
 * \brief ���ü������ڻ���
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] data       : ���ڻ����趨ֵ
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setperiodbuf(amhw_zsn700_adtim_t *p_hw_adtim,
                                         uint16_t             data) {
    p_hw_adtim->perbr  = data;
    p_hw_adtim->bconr |= (1ul << 8);

    return AM_TRUE;
}

/**
 * \brief ����������ڻ���
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearperiodbuf(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->bconr &= ~(1ul << 8);
    p_hw_adtim->perbr  = 0;

    return AM_TRUE;
}

/**
 * \brief ������Ч��������
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] p_cfg      : ָ��ADT��Ч�����������ýṹ���ָ��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setvalidperiod(
              amhw_zsn700_adtim_t              *p_hw_adtim,
              amhw_zsn700_adtim_validper_cfg_t *p_cfg) {
    if(p_cfg == NULL) {
        return AM_FALSE;
    }

    p_hw_adtim->vperr  = 0;
    p_hw_adtim->vperr |= (p_cfg->validcnt << 18);
    p_hw_adtim->vperr |= (p_cfg->validcdt << 16);
    p_hw_adtim->vperr |= (p_cfg->period_D << 3);
    p_hw_adtim->vperr |= (p_cfg->period_C << 2);
    p_hw_adtim->vperr |= (p_cfg->period_B << 1);
    p_hw_adtim->vperr |= (p_cfg->period_A << 0);

    return AM_TRUE;
}

/**
 * \brief ���ñȽ����������׼ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] compare    : amhw_zsn700_adtim_compare_x_tö����
 * \param[in] data       : �趨ֵ
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setcomparevalue(
              amhw_zsn700_adtim_t          *p_hw_adtim,
              amhw_zsn700_adtim_compare_x_t compare,
              uint16_t                      data) {

    switch(compare) {
    case AMHW_ZSN700_ADTIM_COMPARE_A:
        p_hw_adtim->gcmxr[0] = data;
        break;
    case AMHW_ZSN700_ADTIM_COMPARE_B:
        p_hw_adtim->gcmxr[1] = data;
        break;
    case AMHW_ZSN700_ADTIM_COMPARE_C:
        p_hw_adtim->gcmxr[2] = data;
        break;
    case AMHW_ZSN700_ADTIM_COMPARE_D:
        p_hw_adtim->gcmxr[3] = data;
        break;
    default:
        return AM_FALSE;
    }

    return AM_TRUE;
}

/**
 * \brief ����ר�ñȽϼ�����׼ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] compare    : amhw_zsn700_adtim_special_compare_x_tö����
 * \param[in] data       : �趨ֵ
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setspecilcomparevalue(
              amhw_zsn700_adtim_t                  *p_hw_adtim,
              amhw_zsn700_adtim_special_compare_x_t compare,
              uint16_t                              data) {
    switch(compare) {
    case AMHW_ZSN700_ADTIM_SPCL_COMP_A:
        p_hw_adtim->scmxr[0] = data;
        break;
    case AMHW_ZSN700_ADTIM_SPCL_COMP_B:
        p_hw_adtim->scmxr[1] = data;
        break;
    default:
        return AM_FALSE;
    }

    return AM_TRUE;
}

/**
 * \brief ����ͨ�ñȽ�ֵ/����ֵ�Ļ��洫��
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] compare    : amhw_zsn700_adtim_chx_tö����
 * \param[in] enable     : ʹ��״̬��AM_FALSE��AM_TRUE��
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_enablevaluebuf(amhw_zsn700_adtim_t    *p_hw_adtim,
                                           amhw_zsn700_adtim_chx_t port,
                                           am_bool_t               enable) {
    switch(port) {
    case AMHW_ZSN700_ADTIM_CHX_A:
        p_hw_adtim->bconr = (p_hw_adtim->bconr & (~(1ul << 0))) |
                            (enable << 0);
        break;
    case AMHW_ZSN700_ADTIM_CHX_B:
        p_hw_adtim->bconr = (p_hw_adtim->bconr & (~(1ul << 2))) |
                            (enable << 2);
        break;
    default:
        return AM_FALSE;
    }

    return AM_TRUE;
}

/**
 * \brief ����Ƚ��������ֵ/����ֵ����
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] port       : amhw_zsn700_adtim_chx_tö����
 *
 * \return AM_FALSE ������ʧ��
 *         AM_TRUE  �����óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearvaluebuf(amhw_zsn700_adtim_t    *p_hw_adtim,
                                          amhw_zsn700_adtim_chx_t port) {
    switch(port) {
    case AMHW_ZSN700_ADTIM_CHX_A:
        p_hw_adtim->gcmxr[2] = 0;
        break;
    case AMHW_ZSN700_ADTIM_CHX_B:
        p_hw_adtim->gcmxr[3] = 0;
        break;
    default:
        return AM_FALSE;
    }

    return AM_TRUE;
}

/**
 * \brief ��ȡ����ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] port       : amhw_zsn700_adtim_chx_tö����
 *
 * \return ����ֵ
 */
am_static_inline
uint16_t amhw_zsn700_adtim_getcapturevalue(amhw_zsn700_adtim_t    *p_hw_adtim,
                                           amhw_zsn700_adtim_chx_t port) {
    switch(port) {
    case AMHW_ZSN700_ADTIM_CHX_A:
        return p_hw_adtim->gcmxr[0];
    case AMHW_ZSN700_ADTIM_CHX_B:
        return p_hw_adtim->gcmxr[1];
    default:
        return AM_FALSE;
    }
}

/**
 * \brief ��ȡ���񻺴�ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] port       : amhw_zsn700_adtim_chx_tö����
 *
 * \return ���񻺴�ֵ
 */
am_static_inline
uint16_t amhw_zsn700_adtim_getcapturebuf(amhw_zsn700_adtim_t     *p_hw_adtim,
                                          amhw_zsn700_adtim_chx_t port) {
    switch(port) {
    case AMHW_ZSN700_ADTIM_CHX_A:
        return p_hw_adtim->gcmxr[2];
    case AMHW_ZSN700_ADTIM_CHX_B:
        return p_hw_adtim->gcmxr[3];
    default:
        return AM_FALSE;
    }
}

/**
 * \brief ��������ʱ���ϻ�׼ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] data       : �趨ֵ
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setdtua(amhw_zsn700_adtim_t *p_hw_adtim,
                                    uint16_t             data) {
    p_hw_adtim->dtuar = data;

    return AM_TRUE;
}

/**
 * \brief ��������ʱ���»�׼ֵ
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] data       : �趨ֵ
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_setdtda(amhw_zsn700_adtim_t *p_hw_adtim,
                                    uint16_t data) {
    p_hw_adtim->dtdar = data;

    return AM_TRUE;
}

/**
 * \brief ��������ʱ�书��
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] enable     : ��������ʹ�ܣ�AM_FALSE��AM_TRUE��
 * \param[in] equal      : DTDAR��ֵ��DTUAR��ֵ�Զ����ʹ�ܣ�AM_FALSE��AM_TRUE��
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfgdt(amhw_zsn700_adtim_t *p_hw_adtim,
                                  am_bool_t            enable,
                                  am_bool_t            equal) {

    p_hw_adtim->dconr = (p_hw_adtim->dconr &(~(1ul << 0))) |
                        (enable << 0);

    p_hw_adtim->dconr = (p_hw_adtim->dconr &(~(1ul << 8))) |
                        (equal << 8);

    return AM_TRUE;
}

/**
 * \brief �����ж�
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_zsn700_adtim_irq_type_t�ж�����ö����
 * \param[in] equal      : ��Ӧ�ж�ʹ�ܣ�AM_FALSE��AM_TRUE��
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfgirq(amhw_zsn700_adtim_t         *p_hw_adtim,
                                   amhw_zsn700_adtim_irq_type_t type,
                                   am_bool_t                    enable) {
    if(enable == AM_TRUE) {
        p_hw_adtim->iconr |= (1ul << type);
    } else {
        p_hw_adtim->iconr &= ~(1ul << type);
    }

    return AM_TRUE;
}

/**
 * \brief ��ȡ�жϱ�־
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_zsn700_adtim_irq_type_t�ж�����ö����
 *
 * \return AM_FALSE:��־��Ч
 *         AM_TRUE :��־��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_getirqflag(amhw_zsn700_adtim_t         *p_hw_adtim,
                                       amhw_zsn700_adtim_irq_type_t type) {
    return ((p_hw_adtim->ifr >> type) & 1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ����жϱ�־
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] type       : amhw_zsn700_adtim_irq_type_t�ж�����ö����
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearirqflag(amhw_zsn700_adtim_t         *p_hw_adtim,
                                         amhw_zsn700_adtim_irq_type_t type) {
    p_hw_adtim->iclr &= ~(1ul << type);

    return AM_TRUE;
}

/**
 * \brief ��������жϱ�־
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_clearallirqflag(amhw_zsn700_adtim_t *p_hw_adtim) {

    p_hw_adtim->iclr = 0;

    return AM_TRUE;
}

/**
 * \brief Z��������������
 *
 * \param[in] p_hw_adtim : ָ��ADTIM��ʱ���Ĵ������ָ��
 * \param[in] p_cfg      : ָ��Z���������ι������ýṹ���ָ��
 *
 * \return AM_FALSE:����ʧ��
 *         AM_TRUE :���óɹ�
 */
am_static_inline
am_bool_t amhw_zsn700_adtim_cfgzmask(amhw_zsn700_adtim_t           *p_hw_adtim,
                                     amhw_zsn700_adtim_zmask_cfg_t *p_cfg) {
    if(p_cfg == NULL) {
        return AM_FALSE;
    }

    p_hw_adtim->gconr = (p_hw_adtim->gconr & (~(3ul << 18))) |
                        (p_cfg->zmask_cycle << 18);

    p_hw_adtim->gconr = (p_hw_adtim->gconr & (~(1ul << 17))) |
                        (p_cfg->fltposcntmask << 17);

    p_hw_adtim->gconr = (p_hw_adtim->gconr & (~(1ul << 16))) |
                        (p_cfg->fltrevcntmask << 16);

    return AM_TRUE;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZSN700_ADTIM_H */

/* end of file */

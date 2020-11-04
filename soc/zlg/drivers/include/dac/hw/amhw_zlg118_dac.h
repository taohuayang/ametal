/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief DAC�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 19-09-24
 * \endinternal
 */

#ifndef __AMHW_ZLG118_DAC_H
#define __AMHW_ZLG118_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zlg118_if_dac
 * \copydoc amhw_zlg118_dac.h
 * @{
 */

/**
 * \brief DAC - �Ĵ�����
 */
typedef struct amhw_zlg118_dac {
    __IO uint32_t daccr;        /**< \brief DAC ���ƼĴ��� */
    __O  uint32_t dacswt;       /**< \brief DAC ���������ʱ�� */
    __IO uint32_t dacdhr12r0;   /**< \brief DAC 12λ�Ҷ������ݼĴ��� */
    __IO uint32_t dacdhr12l0;   /**< \brief DAC 12λ��������ݼĴ��� */
    __IO uint32_t dacdhr8r0;    /**< \brief DAC 8λ�Ҷ������ݼĴ��� */
         uint32_t res1[6];      /**< \brief ���� */
    __IO uint32_t dacdor0;      /**< \brief DAC ��������Ĵ��� */
         uint32_t res2;         /**< \brief ���� */
    __IO uint32_t dacsr;        /**< \brief DAC ״̬�Ĵ��� */
    __IO uint32_t dacetrs;      /**< \brief DAC ���ԼĴ���/�ⲿ����ѡ��Ĵ��� */
} amhw_zlg118_dac_t;

/*
 * \brief DAC 0ͨ���ο���ѹѡ������
 */
#define AMHW_ZLG118_DAC_CHAN_MASK_INTER_1_5     (0U << 14)
#define AMHW_ZLG118_DAC_CHAN_MASK_INTER_2_5     (1U << 14)
#define AMHW_ZLG118_DAC_CHAN_MASK_EXTER_REF     (2U << 14)
#define AMHW_ZLG118_DAC_CHAN_MASK_AVCC_VOLT     (3U << 14)

/**
 * \brief DAC 0ͨ���ο���ѹѡ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 * \param[in] flag     : �ο��궨�壺DAC 0ͨ���ο���ѹѡ������
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_dac_chan_sref_sel (amhw_zlg118_dac_t *p_hw_dac, uint32_t  flag)
{
    p_hw_dac->daccr = (p_hw_dac->daccr & (~(3U << 14))) | flag;
}

/**
 * \brief DAC 0ͨ��DMAʹ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_dac_chan_dma_enbale (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->daccr |= (1U << 12);
}

/**
 * \brief DAC 0ͨ��DMAʧ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_dac_chan_dma_disbale (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->daccr &= ~(1U << 12);
}

/*
 * \brief DAC 0ͨ������/���ѡ����
 */

#define AMHW_ZLG118_DAC_CHAN_MASK_BIT0_AMPLITUDE1     (0U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT1_AMPLITUDE3     (1U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT2_AMPLITUDE7     (2U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT3_AMPLITUDE15    (3U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT4_AMPLITUDE31    (4U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT5_AMPLITUDE63    (5U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT6_AMPLITUDE127   (6U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT7_AMPLITUDE255   (7U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT8_AMPLITUDE511   (8U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT9_AMPLITUDE1023  (9U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT10_AMPLITUDE2047 (10U << 8)
#define AMHW_ZLG118_DAC_CHAN_MASK_BIT11_AMPLITUDE4095 (11U << 8)

/*
 * \brief DAC 0ͨ������/���ѡ���� ѡ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 * \param[in] flag     : �ο��궨�壺DAC0 ͨ������/���ѡ����
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_mask_ampl_sel (amhw_zlg118_dac_t *p_hw_dac,
                                         uint32_t           flag)
{
    p_hw_dac->daccr = (p_hw_dac->daccr & ~(0xf << 8)) | flag;
}

/*
 * \brief DAC 0ͨ������/���ǲ�����ʹ�� ����
 */

#define AMHW_ZLG118_DAC_CHAN_CLOSE_WAV_GEN (0U << 6)
#define AMHW_ZLG118_DAC_CHAN_NOIS_WAV_GEN  (1U << 6)
#define AMHW_ZLG118_DAC_CHAN_TRIAN_WAV_GEN (2U << 6)

/*
 * \brief DAC 0ͨ������/���ǲ�����ʹ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 * \param[in] flag     : �ο��궨�壺DAC0 ͨ������/���ǲ�����ʹ�� ����
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_wav_gen_enable (amhw_zlg118_dac_t *p_hw_dac,
                                           uint32_t           flag)
{
    p_hw_dac->daccr = (p_hw_dac->daccr & (~(3U << 6))) | flag;
}

/*
 * \brief DAC 0ͨ��������ѡ������
 *
 * \note ֻ����ͨ��ʹ�ܺ��������
 */
#define AMHW_ZLG118_DAC_CHAN_TIM0_TRGO    (0U << 3)
#define AMHW_ZLG118_DAC_CHAN_TIM1_TRGO    (1U << 3)
#define AMHW_ZLG118_DAC_CHAN_TIM2_TRGO    (2U << 3)
#define AMHW_ZLG118_DAC_CHAN_TIM3_TRGO    (3U << 3)
#define AMHW_ZLG118_DAC_CHAN_TIM4_TRGO    (4U << 3)
#define AMHW_ZLG118_DAC_CHAN_TIM5_TRGO    (5U << 3)
#define AMHW_ZLG118_DAC_CHAN_SOFTWARE_TRG (6U << 3)
#define AMHW_ZLG118_DAC_CHAN_EXTER        (7U << 3)

/*
 * \brief DAC 0ͨ��������ѡ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 * \param[in] flag     : �ο��궨�壺DAC0 ͨ��������ѡ������
 *
 * \retval: n��
 */
am_static_inline
void amhw_zlg118_dac_chan_trg_sel (amhw_zlg118_dac_t *p_hw_dac, uint32_t flag)
{
    p_hw_dac->daccr = (p_hw_dac->daccr & (~(0x7u << 3))) | flag;
}

/*
 * \brief DAC 0ͨ������ʹ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_trg_enable (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->daccr |= (1U << 2);
}

/*
 * \brief DAC 0ͨ������ʧ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_trg_disable (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->daccr &= ~(1U << 2);
}

/*
 * \brief DAC 0ͨ�������������ֹ
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: none
 */
am_static_inline
void amhw_zlg118_dac_chan_output_buf_disable (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->daccr |= (1U << 1);
}

/*
 * \brief  DAC 0ͨ�����������ʹ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_output_buf_enable (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->daccr &= ~(1U << 1);
}

/*
 * \brief DAC 0ͨ��ʹ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: none
 */
am_static_inline
void amhw_zlg118_dac_chan_enable (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->daccr |= (1U << 0);
}

/*
 * \brief DAC 0ͨ��ʧ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_disable (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->daccr &= ~(1U << 0);
}

/*
 * \brief DAC0 �������ʹ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_software_trg_enable (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->dacswt |= (1U << 0);
}

/*
 * \brief DAC0 �������ʧ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: none
 */
am_static_inline
void amhw_zlg118_dac_chan_software_trg_disable (amhw_zlg118_dac_t *p_hw_dac)
{
    p_hw_dac->dacswt &= ~(1U << 0);
}

/*
 * \brief DAC ͨ��0 12 λ�Ҷ�������
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 * \param[in] data : ͨ��0����
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_12bit_right_aligned_data (
                                                    amhw_zlg118_dac_t *p_hw_dac,
                                                    uint16_t           data)
{
    p_hw_dac->dacdhr12r0 = (p_hw_dac->dacdhr12r0 & (~(0xfff))) | data;
}

/*
 * \brief DAC ͨ��0 12 λ���������
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 * \param[in] data : ͨ��0����
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_12bit_left_aligned_data (amhw_zlg118_dac_t *p_hw_dac,
                                                   uint16_t           data)
{
    p_hw_dac->dacdhr12l0 = (p_hw_dac->dacdhr12r0 & (~(0xfff << 4))) | (data << 4);

}

/*
 * \brief DAC ͨ��0 8 λ�Ҷ�������
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 * \param[in] data : ͨ��0����
 *
 * \retval: ��
 */
am_static_inline
void amhw_zlg118_dac_chan_8bit_right_aligned_data (amhw_zlg118_dac_t *p_hw_dac,
                                                   uint8_t            data)
{
    p_hw_dac->dacdhr8r0 = (p_hw_dac->dacdhr8r0 & ~(0xff)) | data;
}

/*
 * \brief DAC 0ͨ���������
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: DAC 0ͨ���������
 */
am_static_inline
uint16_t amhw_zlg118_dac_chan_output_data (amhw_zlg118_dac_t *p_hw_dac)
{
    return (p_hw_dac->dacdor0 & 0xfff);
}

/*
 * \brief DAC 0ͨ�� DMA �����־
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 *
 * \retval: DAC 0ͨ��DMA�������״����־
 */
am_static_inline
uint16_t amhw_zlg118_dac_chan_dma_status (amhw_zlg118_dac_t *p_hw_dac)
{
    return (p_hw_dac->dacsr & 0x00002000 >> 13);
}

/*
 * \brief DAC �����˿�ѡ�� ����
 *
 */
#define AMHW_ZLG118_DAC_CHAN_TRI_POT_PA9 (0U << 4)
#define AMHW_ZLG118_DAC_CHAN_TRI_POT_PB9 (1U << 4)
#define AMHW_ZLG118_DAC_CHAN_TRI_POT_PC9 (2U << 4)
#define AMHW_ZLG118_DAC_CHAN_TRI_POT_PD9 (3U << 4)
#define AMHW_ZLG118_DAC_CHAN_TRI_POT_PE9 (4U << 4)
#define AMHW_ZLG118_DAC_CHAN_TRI_POT_PF9 (5U << 4)

/*
 * \brief DAC �˿ڴ���ѡ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ��������ַָ��
 * \param[in] flag : �ο��궨�壺DAC �����˿�ѡ�� ����
 *
 * \retval: ��
 */
am_static_inline
uint16_t amhw_zlg118_dac_chan_tri_port_sel (amhw_zlg118_dac_t *p_hw_dac,
                                            uint32_t           flag)
{
    return (p_hw_dac->dacetrs & ~(0x7 << 4)) | flag;
}

/**
 * @} amhw_if_zlg118_dac
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG118_DAC_H */

/* end of file */

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
 * \brief I2C�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-17  sdy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG_I2C_H
#define __AMHW_ZLG_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

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
 * \addtogroup amhw_zlg_if_i2c
 * \copydoc amhw_zlg_i2c.h
 * @{
 */

/**
 * \brief I2C�Ĵ�����ṹ��
 */
typedef struct amhw_zlg_i2c {
    __IO uint16_t  ic_con;                /**< \brief I2C���ƼĴ��� */
         uint16_t  reserved0;             /**< \brief ����0 */
    __IO uint16_t  ic_tar;                /**< \brief I2CĿ���ַ�Ĵ��� */
         uint16_t  reserved1;             /**< \brief ����1 */
    __IO uint16_t  ic_sar;                /**< \brief I2C�ӻ���ַ�Ĵ��� */
         uint16_t  reserved2;             /**< \brief ����2 */
    __IO uint16_t  ic_hs_maddr;           /**< \brief ���ұ��� */
         uint16_t  reserved3;             /**< \brief ����3 */
    __IO uint16_t  ic_data_cmd;           /**< \brief I2C��������Ĵ��� */
         uint16_t  reserved4;             /**< \brief ����4 */
    __IO uint16_t  ic_ss_scl_hcnt;        /**< \brief ��׼ģʽ I2Cʱ�Ӹߵ�ƽ�����Ĵ��� */
         uint16_t  reserved5;             /**< \brief ����5 */
    __IO uint16_t  ic_ss_scl_lcnt;        /**< \brief ��׼ģʽ I2Cʱ�ӵ͵�ƽ�����Ĵ��� */
         uint16_t  reserved6;             /**< \brief ����6 */
    __IO uint16_t  ic_fs_scl_hcnt;        /**< \brief ����ģʽ I2Cʱ�Ӹߵ�ƽ�����Ĵ��� */
         uint16_t  reserved7;             /**< \brief ����7 */
    __IO uint16_t  ic_fs_scl_lcnt;        /**< \brief ����ģʽ I2Cʱ�ӵ͵�ƽ�����Ĵ��� */
         uint16_t  reserved8;             /**< \brief ����8 */
    __IO uint16_t  ic_hs_scl_hcnt;        /**< \brief ���ұ��� */
         uint16_t  reserved9;             /**< \brief ����9 */
    __IO uint16_t  ic_hs_scl_lcnt;        /**< \brief ���ұ��� */
         uint16_t  reserved10;            /**< \brief ����10 */
    __IO uint16_t  ic_intr_stat;          /**< \brief I2C�ж�״̬�Ĵ��� */
         uint16_t  reserved11;            /**< \brief ����11 */
    __IO uint16_t  ic_intr_mask;          /**< \brief I2C�ж����μĴ��� */
         uint16_t  reserved12;            /**< \brief ����12 */
    __IO uint16_t  ic_raw_intr_stat;      /**< \brief I2C RAW �жϼĴ��� */
         uint16_t  reserved13;            /**< \brief ����13 */
    __IO uint16_t  ic_rx_tl;              /**< \brief I2C������ֵ */
         uint16_t  reserved14;            /**< \brief ����14 */
    __IO uint16_t  ic_tx_tl;              /**< \brief I2C������ֵ */
         uint16_t  reserved15;            /**< \brief ����15 */

    __IO uint16_t  ic_clr_intr;           /**< \brief I2C��ϺͶ����ж�����Ĵ��� */
         uint16_t  reserved16;            /**< \brief ����16 */
    __IO uint16_t  ic_clr_rx_under;       /**< \brief I2C���RX_UNDER�жϼĴ��� */
         uint16_t  reserved17;            /**< \brief ����17 */
    __IO uint16_t  ic_clr_rx_over;        /**< \brief I2C���RX_OVER�жϼĴ��� */
         uint16_t  reserved18;            /**< \brief ����18 */
    __IO uint16_t  ic_clr_tx_over;        /**< \brief I2C���TX_OVER�жϼĴ��� */
         uint16_t  reserved19;            /**< \brief ����19 */
    __IO uint16_t  ic_clr_rd_req;         /**< \brief I2C���RD_REQ�жϼĴ��� */
         uint16_t  reserved20;            /**< \brief ����20 */
    __IO uint16_t  ic_clr_tx_abrt;        /**< \brief I2C���TX_ABRT�жϼĴ��� */
         uint16_t  reserved21;            /**< \brief ����21 */
    __IO uint16_t  ic_clr_rx_done;        /**< \brief I2C���RX_DONE�жϼĴ��� */
         uint16_t  reserved22;            /**< \brief ����22 */
    __IO uint16_t  ic_clr_activity;       /**< \brief I2C��� ACTIVITY�жϼĴ��� */
         uint16_t  reserved23;            /**< \brief ����23 */
    __IO uint16_t  ic_clr_stop_det;       /**< \brief I2C���STOP_DET�жϼĴ��� */
         uint16_t  reserved24;            /**< \brief ����24 */
    __IO uint16_t  ic_clr_start_det;      /**< \brief I2C���START_DET�жϼĴ��� */
         uint16_t  reserved25;            /**< \brief ����25 */
    __IO uint16_t  ic_clr_gen_call;       /**< \brief I2C��� GEN_CALL �жϼĴ��� */
         uint16_t  reserved26;            /**< \brief ����26 */
    __IO uint16_t  ic_enable;             /**< \brief I2Cʹ�ܼĴ��� */
         uint16_t  reserved27;            /**< \brief ����27 */

    __IO uint32_t  ic_status;             /**< \brief I2C״̬�Ĵ��� */
    __IO uint32_t  ic_txflr;              /**< \brief I2C���ͻ���ˮƽ�Ĵ��� */
    __IO uint32_t  ic_rxflr;              /**< \brief I2C���ջ���ˮƽ�Ĵ��� */
    __IO uint32_t  ic_sda_hold;           /**< \brief I2C SDA����ʱ��Ĵ��� */
    __IO uint32_t  ic_tx_abrt_source;     /**< \brief ���ұ��� */
    __IO uint32_t  ic_slv_data_nack_only; /**< \brief ���ұ��� */
    __IO uint32_t  ic_dma_cr;             /**< \brief I2C DMA���ƼĴ��� */
    __IO uint32_t  ic_dma_tdlr;           /**< \brief ���ұ��� */
    __IO uint32_t  ic_dma_rdlr;           /**< \brief ���ұ��� */
    __IO uint32_t  ic_sda_setup;          /**< \brief I2C SDA����ʱ��Ĵ��� */
    __IO uint32_t  ic_ack_general_call;   /**< \brief I2C�㲥���� ACK�Ĵ��� */
    __IO uint32_t  ic_enable_status;      /**< \brief ���ұ��� */

    __IO uint32_t  ic_fs_spklen;          /**< \brief ���ұ��� */
    __IO uint32_t  ic_hs_spklen;          /**< \brief ���ұ��� */

    __IO uint16_t  ic_clr_restart_det;    /**< \brief ���ұ��� */
         uint16_t  reserved28;            /**< \brief ����28 */
    __IO uint32_t  ic_comp_param_1;       /**< \brief ���ұ��� */
    __IO uint32_t  ic_comp_version;       /**< \brief ���ұ��� */
    __IO uint32_t  ic_comp_type;          /**< \brief ���ұ��� */
} amhw_zlg_i2c_t;

/**
 * \brief
 */

/** \brief ����ģʽ */
#define AMHW_ZLG_I2C_MASTER                  (1ul | (1ul << 6))

/** \brief �ӻ�ģʽ */
#define AMHW_ZLG_I2C_SLAVE                   (0ul | (0ul << 6))

/** \brief ��׼ģʽ(0 ~ 100Kbps),����ģʽ����Ч */
#define AMHW_ZLG_I2C_NORMAL_SPEED            (1ul << 1)

/** \brief ����ģʽ(<=400Kbps),����ģʽ����Ч */
#define AMHW_ZLG_I2C_HIGH_SPEED              (2ul << 1)

/** \brief 7 λ��Ѱַ��ַ,�ӻ�ģʽ����Ч */
#define AMHW_ZLG_I2C_7BITADDR_SLAVE          (0ul << 3)

/** \brief 10 λ��Ѱַ��ַ,�ӻ�ģʽ����Ч */
#define AMHW_ZLG_I2C_10BITADDR_SLAVE         (1ul << 3)

/** \brief 7 λ��Ѱַ��ַ,����ģʽ����Ч */
#define AMHW_ZLG_I2C_7BITADDR_MASTER         (0ul << 4)

/** \brief 10 λ��Ѱַ��ַ,����ģʽ����Ч */
#define AMHW_ZLG_I2C_10BITADDR_MASTER        (1ul << 4)

/** \brief ����ģʽ��ʹ�ܷ���RESTART���� */
#define AMHW_ZLG_I2C_RESTART_ENABLE          (1ul << 5)

/** \brief �ӻ�ģʽ��ʹ�ܲ���STOP_DET�ж� */
#define AMHW_ZLG_I2C_STOP_DET_IFADDRESSED    (1ul << 7)

/**
 * \brief I2C�жϱ�־
 */
typedef enum {
   AMHW_ZLG_INT_FLAG_RX_UNDER = (1ul << 0),      /**< \brief ���ջ���Ƿ�� */
   AMHW_ZLG_INT_FLAG_RX_OVER  = (1ul << 1),      /**< \brief ���ܻ������ */
   AMHW_ZLG_INT_FLAG_RX_FULL  = (1ul << 2),      /**< \brief ���ջ���ǿ� */
   AMHW_ZLG_INT_FLAG_TX_OVER  = (1ul << 3),      /**< \brief ���ͻ������ */
   AMHW_ZLG_INT_FLAG_TX_EMPTY = (1ul << 4),      /**< \brief ���ͻ���� */
   AMHW_ZLG_INT_FLAG_RD_REQ   = (1ul << 5),      /**< \brief ������ */
   AMHW_ZLG_INT_FLAG_TX_ABRT  = (1ul << 6),      /**< \brief ������ֹ */
   AMHW_ZLG_INT_FLAG_RX_DONE  = (1ul << 7),      /**< \brief �ӷ��ͽ��� */
   AMHW_ZLG_INT_FLAG_ACTIVITY = (1ul << 8),      /**< \brief I2C�ӿڼ��� */
   AMHW_ZLG_INT_FLAG_STOP_DET = (1ul << 9),      /**< \brief ֹͣ������� */
   AMHW_ZLG_INT_FLAG_START_DET= (1ul << 10),     /**< \brief ��ʼ������� */
   AMHW_ZLG_INT_FLAG_GEN_CALL = (1ul << 11),     /**< \brief �㲥���� */
}amhw_zlg_int_flag_t;

/**
 * \brief I2C״̬��־
 */
typedef enum {
   AMHW_ZLG_STATUS_FLAG_ACTIVITY     = (1ul << 0),   /**< \brief I2Cλ�״̬ */
   AMHW_ZLG_STATUS_FLAG_TFNF         = (1ul << 1),   /**< \brief ���ͻ���δ�� */
   AMHW_ZLG_STATUS_FLAG_TFE          = (1ul << 2),   /**< \brief ���ͻ���� */
   AMHW_ZLG_STATUS_FLAG_RFNE         = (1ul << 3),   /**< \brief ���ջ���ǿ� */
   AMHW_ZLG_STATUS_FLAG_RFF          = (1ul << 4),   /**< \brief ���ջ����� */
   AMHW_ZLG_STATUS_FLAG_MST_ACTIVITY = (1ul << 5),   /**< \brief ����״̬���״̬λ */
   AMHW_ZLG_STATUS_FLAG_SLV_ACTIVITY = (1ul << 6),   /**< \brief �ӻ�״̬���״̬λ */
}amhw_zlg_status_flag_t;

/**
 * \brief ���ÿ��ƼĴ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  flag      : ��־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_con_set (amhw_zlg_i2c_t    *p_hw_i2c,
                           uint16_t           flag)
{
    p_hw_i2c->ic_con |= flag;
}

/**
 * \brief ������ƼĴ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  flag      : ��־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_con_clear (amhw_zlg_i2c_t    *p_hw_i2c,
                             uint16_t           flag)
{
    p_hw_i2c->ic_con &= ~((uint32_t)flag);
}

/**
 * \brief ������������Ŀ���ַ.
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  addr      : Ŀ���ַ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_tar_set (amhw_zlg_i2c_t    *p_hw_i2c,
                           uint16_t           addr)
{
    p_hw_i2c->ic_tar = (p_hw_i2c->ic_tar & ~0x3ff) | (addr & 0x3ff);
}

/**
 * \brief ���ôӻ���ַ.
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  addr      : �ӻ���ַ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_slave_addr_set (amhw_zlg_i2c_t    *p_hw_i2c,
                                  uint16_t           addr)
{
    p_hw_i2c->ic_sar = (p_hw_i2c->ic_sar & ~0x3ff) | (addr & 0x3ff);
}

/**
 * \brief д����.
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  dat       : ����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_dat_write (amhw_zlg_i2c_t    *p_hw_i2c,
                             uint16_t           dat)
{
    p_hw_i2c->ic_data_cmd = dat;
}

/**
 * \brief ������.
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ����
 */
am_static_inline
uint8_t amhw_zlg_i2c_dat_read (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_data_cmd);
}

/**
 * \brief дI2C��׼ģʽ��ʱ�Ӹߵ�ƽ����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  val       : ����(6 ~ 65525)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_ss_scl_high_set (amhw_zlg_i2c_t    *p_hw_i2c,
                                   uint16_t           val)
{
    p_hw_i2c->ic_ss_scl_hcnt = (p_hw_i2c->ic_ss_scl_hcnt & ~0xffff) | val;
}

/**
 * \brief ��I2C��׼ģʽ��ʱ�Ӹߵ�ƽ����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return I2C��׼ģʽ��ʱ�Ӹߵ�ƽ����ֵ(6 ~ 65525)
 */
am_static_inline
uint16_t amhw_zlg_i2c_ss_scl_high_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint16_t)(p_hw_i2c->ic_ss_scl_hcnt & 0xffff);
}

/**
 * \brief дI2C��׼ģʽ��ʱ�ӵ͵�ƽ����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  val       : ����(8 ~ 65535)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_ss_scl_low_set (amhw_zlg_i2c_t    *p_hw_i2c,
                                  uint16_t           val)
{
    p_hw_i2c->ic_ss_scl_lcnt = (p_hw_i2c->ic_ss_scl_lcnt & ~0xffff) | val;
}

/**
 * \brief ��I2C��׼ģʽ��ʱ�ӵ͵�ƽ����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return I2C��׼ģʽ��ʱ�ӵ͵�ƽ����ֵ(8 ~ 65535)
 */
am_static_inline
uint16_t amhw_zlg_i2c_ss_scl_low_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint16_t)(p_hw_i2c->ic_ss_scl_lcnt & 0xffff);
}

/**
 * \brief дI2C����ģʽ��ʱ�Ӹߵ�ƽ����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  val       : ����(6 ~ 65535)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_fs_scl_high_set (amhw_zlg_i2c_t    *p_hw_i2c,
                                   uint16_t           val)
{
    p_hw_i2c->ic_fs_scl_hcnt = (p_hw_i2c->ic_fs_scl_hcnt & ~0xffff) | val;
}

/**
 * \brief ��I2C����ģʽ��ʱ�Ӹߵ�ƽ����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return I2C��ģʽ��ʱ�Ӹߵ�ƽ����ֵ(6 ~ 65525)
 */
am_static_inline
uint16_t amhw_zlg_i2c_fs_scl_high_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint16_t)(p_hw_i2c->ic_fs_scl_hcnt & 0xffff);
}

/**
 * \brief дI2C����ģʽ��ʱ�ӵ͵�ƽ����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  val       : ����(8 ~ 65535)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_fs_scl_low_set (amhw_zlg_i2c_t    *p_hw_i2c,
                                  uint16_t           val)
{
    p_hw_i2c->ic_fs_scl_lcnt = (p_hw_i2c->ic_fs_scl_lcnt & ~0xffff) | val;
}

/**
 * \brief ��I2C����ģʽ��ʱ�ӵ͵�ƽ����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return I2C����ģʽ��ʱ�ӵ͵�ƽ����ֵ(8 ~ 65535)
 */
am_static_inline
uint16_t amhw_zlg_i2c_fs_scl_low_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint16_t)(p_hw_i2c->ic_fs_scl_lcnt & 0xffff);
}

/**
 * \brief ��ȡ�������ж�״̬�Ĵ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return �������ж�״̬�Ĵ���ֵ(���ϵ)
 */
am_static_inline
amhw_zlg_int_flag_t amhw_zlg_i2c_intr_stat_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (amhw_zlg_int_flag_t)(p_hw_i2c->ic_intr_stat & 0xffff);
}

/**
 * \brief �����ж����μĴ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  flag      : �����־�����ϵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_intr_mask_set (amhw_zlg_i2c_t    *p_hw_i2c,
                                 uint16_t           flag)
{
    p_hw_i2c->ic_intr_mask |= flag;
}

/**
 * \brief �����ж����μĴ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  flag      : �����־�����ϵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_intr_mask_clear (amhw_zlg_i2c_t    *p_hw_i2c,
                                   uint16_t           flag)
{
    p_hw_i2c->ic_intr_mask &= ~((uint32_t)flag);
}

/**
 * \brief ��ȡ�ж����μĴ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return �ж����μĴ���ֵ(���ϵ)
 */
am_static_inline
amhw_zlg_int_flag_t amhw_zlg_i2c_intr_mask_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (amhw_zlg_int_flag_t)(p_hw_i2c->ic_intr_mask & 0xffff);
}

/**
 * \brief ��ȡ���������ж�״̬�Ĵ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ���������ж�״̬�Ĵ���ֵ(���ϵ)
 */
am_static_inline
amhw_zlg_int_flag_t amhw_zlg_i2c_raw_intr_stat_get (
                                                    amhw_zlg_i2c_t *p_hw_i2c)
{
    return (amhw_zlg_int_flag_t)(p_hw_i2c->ic_raw_intr_stat & 0xffff);
}

/**
 * \brief ���ý�����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  val       : ��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_rx_tl_set (amhw_zlg_i2c_t *p_hw_i2c, uint8_t val)
{
    p_hw_i2c->ic_rx_tl = val & 0xff;
}

/**
 * \brief ��ȡ������ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ������ֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_rx_tl_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_rx_tl & 0xff);
}

/**
 * \brief ���÷�����ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  val       : ��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_tx_tl_set (amhw_zlg_i2c_t *p_hw_i2c, uint8_t val)
{
    p_hw_i2c->ic_tx_tl = val & 0xff;
}

/**
 * \brief ��ȡ������ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ������ֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_tx_tl_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_tx_tl & 0xff);
}

/**
 * \brief ��ȡI2C��ϺͶ����ж�����Ĵ���ֵ�����I2C��ϺͶ����ж�
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return I2C��ϺͶ����ж�����Ĵ���ֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_intr_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_intr & 0x1);
}

/**
 * \brief I2C���RX_UNDER�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_rx_under_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_rx_under & 0x1);
}

/**
 * \brief I2C���RX_OVER�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_rx_over_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_rx_over & 0x1);
}

/**
 * \brief I2C���TX_OVER�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_tx_over_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_tx_over & 0x1);
}

/**
 * \brief I2C���RD_REQ�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_rd_req_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_rd_req & 0x1);
}

/**
 * \brief I2C���TX_ABRT�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_tx_abrt_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_tx_abrt & 0x1);
}

/**
 * \brief I2C���RX_DONE�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_rx_done_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_rx_done & 0x1);
}

/**
 * \brief I2C��� ACTIVITY�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_activity_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_activity & 0x1);
}

/**
 * \brief I2C���STOP_DET�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_stop_det_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_stop_det & 0x1);
}

/**
 * \brief I2C���START_DET�жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_start_det_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_start_det & 0x1);
}

/**
 * \brief I2C��� GEN_CALL �жϼĴ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��ȡֵ
 */
am_static_inline
uint8_t amhw_zlg_i2c_clr_gen_call_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_clr_gen_call & 0x1);
}

/**
 * \brief ʹ�� I2C ģ��
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_enable (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_enable |= 0x1ul;
}

/**
 * \brief ��ֹ I2C ģ�飨���ͺͽ��ջ��屣�ֲ���״̬��
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_disable (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_enable &= ~0x1ul;
}

/**
 * \brief ��ȡI2C״̬
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ״̬�����ϵ��
 */
am_static_inline
amhw_zlg_status_flag_t amhw_zlg_i2c_status_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (amhw_zlg_status_flag_t)(p_hw_i2c->ic_status);
}

/**
 * \brief ��ȡ���ͻ�����Ч���ݸ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ���ͻ�����Ч���ݸ���
 */
am_static_inline
uint8_t amhw_zlg_i2c_txflr_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_txflr);
}

/**
 * \brief ��ȡ���ջ�����Ч���ݸ���
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ���ջ�����Ч���ݸ���
 */
am_static_inline
uint8_t amhw_zlg_i2c_rxflr_get (amhw_zlg_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->ic_rxflr);
}

/**
 * \brief ʹ�� I2C ����DMA
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_txdma_enable (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_dma_cr |= 0x2ul;
}

/**
 * \brief ����I2C ����DMA
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_txdma_disable (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_dma_cr &= ~0x2ul;
}

/**
 * \brief ʹ�� I2C ��DMA
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_rxdma_enable (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_dma_cr |= 0x1ul;
}

/**
 * \brief ����I2C ����DMA
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_rxdma_disable (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_dma_cr &= ~0x1ul;
}

/**
 * \brief I2C SDA ����ʱ������
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  val       : ����ʱ��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_sda_setup_set (amhw_zlg_i2c_t *p_hw_i2c, uint8_t val)
{
    p_hw_i2c->ic_sda_setup = (p_hw_i2c->ic_sda_setup & ~0xfful) | val;
}

/**
 * \brief I2C ������ֹ
 *        note:  ZML165оƬ�ڶ�����ʱ,��Ҫ���øú������д�����ֹ,����ֹͣλ,ֹͣλ������ᴥ��TX_ABRT�ж�,
 *               ��Ҫ���жϲ�������ic_clr_tx_abrt�Ĵ�����д0�Ա�֤�´�I2C�������䡣
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_trans_abort (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_enable |= 0x02;
}

/**
 * \brief I2C ���tx_abrt�Ĵ���
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_i2c_clr_tx_abort (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_clr_tx_abrt = 0;
}


/**
 * \brief I2C���ܹ㲥���� ��Ӧ ACK
 *
 */
am_static_inline
void amhw_zlg_i2c_gen_call_ack (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_ack_general_call |= 0x1ul;
}

/**
 * \brief I2C���ܹ㲥���� ����Ӧ
 *
 */
am_static_inline
void amhw_zlg_i2c_gen_call_nack (amhw_zlg_i2c_t *p_hw_i2c)
{
    p_hw_i2c->ic_ack_general_call &= ~0x1ul;
}

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
#endif /* __AMHW_ZLG_I2C_H */

#endif

/* end of file */

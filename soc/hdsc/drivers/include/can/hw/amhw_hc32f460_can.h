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
 * \brief CAN hardware operation interface
 *
 * -note:�ڶ�ͬһ�Ĵ������ж�дʱ������Ӧ�Ĺ��ܲ�ͬ
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-05  zcb, first implementation
 * \endinternal
 */

#ifndef __AMHW_HC32F460_CAN_H
#define __AMHW_HC32F460_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_hc32f460_if_can
 * \copydoc amhw_hc32f460_can.h
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
 * \brief CAN���ú�״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t BUSOFF                     : 1;  /** <brief ���߹ر�״̬ */
    __IO uint8_t TACTIVE                    : 1;  /** <brief �����ж�״̬�ź�*/
    __IO uint8_t RACTIVE                    : 1;  /** <brief �����ж�״̬�ź�*/
    __IO uint8_t TSSS                       : 1;  /** <brief TSSS���δ���ģʽ*/
    __IO uint8_t TPSS                       : 1;  /** <brief PTB���δ���ģʽ*/
    __IO uint8_t LBMI                       : 1;  /** <brief �ڲ��ػ�ģʽʹ��λ*/
    __IO uint8_t LBME                       : 1;  /** <brief �ⲿ�ػ�ģʽʹ��λ*/
    __IO uint8_t RESET                      : 1;  /** <brief ��λ����*/
} stc_can_cfg_stat_field_t;

/**
 * \brief CAN����Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t TSA                        : 1;  /** <brief STB����ȡ��λ*/
    __IO uint8_t TSALL                      : 1;  /** <brief �������е�STB�����趨λ*/
    __IO uint8_t TSONE                      : 1;  /** <brief ����һ֡STB�����趨λ*/
    __IO uint8_t TPA                        : 1;  /** <brief PTB����ȡ��λ*/
    __IO uint8_t TPE                        : 1;  /** <brief PTB����ʹ��λ*/
    __IO uint8_t STBY                       : 1;
    __IO uint8_t LOM                        : 1;  /** <brief ��Ĭģʽʹ��λ*/
    __IO uint8_t TBSEL                      : 1;  /** <brief ����BUFѡ��λ*/
} stc_can_tcmd_field_t;

/**
 * \brief CAN���Ϳ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t TSSTAT                     : 2;  /** <brief STB״̬*/
    uint8_t RESERVED2                       : 2;  /** <brief ����*/
    __IO uint8_t TTBM                       : 1;  /** <brief TTCAN BUFģʽ*/
    __IO uint8_t TSMODE                     : 1;  /** <brief STB����ģʽ*/
    __IO uint8_t TSNEXT                     : 1;  /** <brief��һ��STBSLOT*/
    uint8_t RESERVED7                       : 1;  /** <brief ����*/
} stc_can_tctrl_field_t;

/**
 * \brief CAN���տ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t RSSTAT                     : 2;  /** <brief ����BUF״̬*/
    uint8_t RESERVED2                       : 1;  /** <brief ����*/
    __IO uint8_t RBALL                      : 1;  /** <brief ����BUF���ݴ洢���е�����֡*/
    __IO uint8_t RREL                       : 1;  /** <brief �ͷŽ���BUF*/
    __IO uint8_t ROV                        : 1;  /** <brief ����BUF�����־λ*/
    __IO uint8_t ROM                        : 1;  /** <brief ����BUF����ģʽ�趨λ*/
    __IO uint8_t SACK                       : 1;  /** <brief ��Ӧ��*/
} stc_can_rctrl_field_t;

/**
 * \brief CAN���պͷ����ж�ʹ�ܼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t TSFF                       : 1;  /** <brief ����BUF����־*/
    __IO uint8_t EIE                        : 1;  /** <brief �����ж�ʹ��*/
    __IO uint8_t TSIE                       : 1;  /** <brief STB�����ж�ʹ��*/
    __IO uint8_t TPIE                       : 1;  /** <brief PTB�����ж�ʹ��*/
    __IO uint8_t RAFIE                      : 1;  /** <brief ����BUF�����ж�ʹ��*/
    __IO uint8_t RFIE                       : 1;  /** <brief ����BUF���ж�ʹ��*/
    __IO uint8_t ROIE                       : 1;  /** <brief ���������ж�ʹ��*/
    __IO uint8_t RIE                        : 1;  /** <brief �����ж�ʹ��*/
} stc_can_rtie_field_t;

/**
 * \brief CAN���պͷ����ж�ʹ�ܼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t AIF                        : 1;  /** <brief ȡ�������жϱ�־*/
    __IO uint8_t EIF                        : 1;  /** <brief �����жϱ�־*/
    __IO uint8_t TSIF                       : 1;  /** <brief STB�����жϱ�־*/
    __IO uint8_t TPIF                       : 1;  /** <brief PTB�����жϱ�־*/
    __IO uint8_t RAFIF                      : 1;  /** <brief ����BUF�����жϱ�־*/
    __IO uint8_t RFIF                       : 1;  /** <brief ����BUF���жϱ�־*/
    __IO uint8_t ROIF                       : 1;  /** <brief ���������жϱ�־*/
    __IO uint8_t RIF                        : 1;  /** <brief �����жϱ�־*/
} stc_can_rtif_field_t;

/**
 * \brief CAN�����ж�ʹ�ܺͱ�־�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t BEIF                       : 1;  /** <brief ���ߴ����жϱ�־*/
    __IO uint8_t BEIE                       : 1;  /** <brief ���ߴ����ж�ʹ��*/
    __IO uint8_t ALIF                       : 1;  /** <brief �ٲ�ʧ���жϱ�־*/
    __IO uint8_t ALIE                       : 1;  /** <brief �ٲ�ʧ���ж�ʹ��*/
    __IO uint8_t EPIF                       : 1;  /** <brief ���󱻶��жϱ�־*/
    __IO uint8_t EPIE                       : 1;  /** <brief ���󱻶��ж�ʹ��*/
    __IO uint8_t EPASS                      : 1;  /** <brief ���󱻶�*/
    __IO uint8_t EWARN                      : 1;  /** <brief �����趨��ERROR WARNING LIMIT*/
} stc_can_errint_field_t;

typedef struct
{
    __IO uint8_t EWL                        : 4;
    __IO uint8_t AFWL                       : 4;
} stc_can_limit_field_t;

/**
 * \brief CANλʱ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SEG_1                     : 8;  /** <brief λ��1ʱ���趨*/
    __IO uint32_t SEG_2                     : 7;  /** <brief λ��2ʱ���趨*/
    uint32_t RESERVED15                     : 1;  /** <brief ����*/
    __IO uint32_t SJW                       : 7;  /** <brief ��ͬ���������ʱ���趨*/
    uint32_t RESERVED23                     : 1;  /** <brief ����*/
    __IO uint32_t PRESC                     : 8;  /** <brief Ԥ��Ƶ�趨*/
} stc_can_bt_field_t;

/**
 * \brief CAN������ٲ�ʧ�ܲ�׽�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t ALC                        : 5;  /** <brief �ٲ�ʧ��λ�ò�׽*/
    __IO uint8_t KOER                       : 3;  /** <brief �������*/
} stc_can_ealcap_field_t;

/**
 * \brief CANɸѡ������ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t ACFADR                     : 4;  /** <brief ɸѡ����ַ*/
    uint8_t RESERVED4                       : 1;  /** <brief ����*/
    __IO uint8_t SELMASK                    : 1;  /** <brief ѡ��ɸѡ�������μĴ���*/
    uint8_t RESERVED6                       : 2;  /** <brief ����*/
} stc_can_acfctrl_field_t;

/**
 * \brief CANɸѡ����ʹ�ܼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t AE_1                       : 1;  /** <brief ACF1ʹ��*/
    __IO uint8_t AE_2                       : 1;  /** <brief ACF2ʹ��*/
    __IO uint8_t AE_3                       : 1;  /** <brief ACF3ʹ��*/
    __IO uint8_t AE_4                       : 1;  /** <brief ACF4ʹ��*/
    __IO uint8_t AE_5                       : 1;  /** <brief ACF5ʹ��*/
    __IO uint8_t AE_6                       : 1;  /** <brief ACF6ʹ��*/
    __IO uint8_t AE_7                       : 1;  /** <brief ACF7ʹ��*/
    __IO uint8_t AE_8                       : 1;  /** <brief ACF8ʹ��*/
} stc_can_acfen_field_t;

/**
 * \brief CANɸѡ����ʹ�ܼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t ACODEORAMASK              :29;  /** <brief ɸѡ��CODE/ɸѡ��MASK*/
    __IO uint32_t AIDE                      : 1;  /** <brief IDEλMASK*/
    __IO uint32_t AIDEE                     : 1;  /** <brief IDEλ�Ƚ�ʹ��*/
    uint32_t RESERVED31                     : 1;  /** <brief ����*/
} stc_can_acf_field_t;

/**
 * \brief TTCAN TB slotָ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t TBPTR                      : 6;  /** <brief TB SLOTָ��*/
    __IO uint8_t TBF                        : 1;  /** <brief ����TBΪ�����*/
    __IO uint8_t TBE                        : 1;  /** <brief ����TBΪ��*/
} stc_can_tbslot_field_t;

/**
 * \brief TTCAN ʱ�䴥�����üĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint8_t TTEN                       : 1;  /** <brief TTCAN ʹ��*/
    __IO uint8_t T_PRESC                    : 2;  /** <brief TTCAN ������Ԥ��Ƶ*/
    __IO uint8_t TTIF                       : 1;  /** <brief ʱ�䴥���жϱ�־*/
    __IO uint8_t TTIE                       : 1;  /** <brief ʱ�䴥���ж�ʹ��*/
    __IO uint8_t TEIF                       : 1;  /** <brief ���������жϱ�־*/
    __IO uint8_t WTIF                       : 1;  /** <brief ���������жϱ�־*/
    __IO uint8_t WTIE                       : 1;  /** <brief ���������ж�ʹ��*/
} stc_can_ttcfg_field_t;

/**
 * \brief TTCAN �ο���Ϣ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t REF_ID                    :29;  /** <brief �ο���Ϣ��IDEλ*/
    uint32_t RESERVED29                     : 2;  /** <brief ����*/
    __IO uint32_t REF_IDE                   : 1;  /** <brief �ο���Ϣ��IDλ*/
} stc_can_ref_msg_field_t;

/**
 * \brief TTCAN �������üĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint16_t TTPTR                     : 6;  /** <brief ���ʹ�����TBslotָ��*/
    uint16_t RESERVED6                      : 2;  /** <brief ����*/
    __IO uint16_t TTYPE                     : 3;  /** <brief ��������*/
    uint16_t RESERVED11                     : 1;  /** <brief ����*/
    __IO uint16_t TEW                       : 4;  /** <brief ����ʹ�ܴ���*/
} stc_can_trg_cfg_field_t;

/**
 * \brief HC32F460 CAN�Ĵ�����ṹ��
 */
typedef struct amhw_hc32f460_can {
    __IO uint32_t RBUF0;         /**< \brief CAN����BUF0�Ĵ��� */
    __IO uint32_t RBUF1;         /**< \brief CAN����BUF1�Ĵ��� */
    __IO uint32_t RBUF2;         /**< \brief CAN����BUF2�Ĵ��� */
    __IO uint32_t RBUF3;         /**< \brief CAN����BUF3�Ĵ��� */
    uint8_t RESERVED4[64];       /**< \brief ���� */
    __IO uint32_t TBUF0;         /**< \brief CAN����BUF0�Ĵ��� */
    __IO uint32_t TBUF1;         /**< \brief CAN����BUF1�Ĵ��� */
    __IO uint32_t TBUF2;         /**< \brief CAN����BUF2�Ĵ��� */
    __IO uint32_t TBUF3;         /**< \brief CAN����BUF3�Ĵ��� */
    uint8_t RESERVED8[64];       /**< \brief ���� */
    union
    {
        __IO uint8_t CFG_STAT;   /**< \brief CAN���ú�״̬�Ĵ��� */
        stc_can_cfg_stat_field_t CFG_STAT_f;
    };
    union
    {
        __IO uint8_t TCMD;       /**< \brief CAN����Ĵ��� */
        stc_can_tcmd_field_t TCMD_f;
    };
    union
    {
        __IO uint8_t TCTRL;      /**< \brief CAN���Ϳ��ƼĴ��� */
        stc_can_tctrl_field_t TCTRL_f;
    };
    union
    {
        __IO uint8_t RCTRL;      /**< \brief CAN���ܿ��ƼĴ��� */
        stc_can_rctrl_field_t RCTRL_f;
    };
    union
    {
        __IO uint8_t RTIE;       /**< \brief CAN���ܺͷ����ж�ʹ�ܼĴ��� */
        stc_can_rtie_field_t RTIE_f;
    };
    union
    {
        __IO uint8_t RTIF;       /**< \brief CAN���ܺͷ����жϱ�־�Ĵ��� */
        stc_can_rtif_field_t RTIF_f;
    };
    union
    {
        __IO uint8_t ERRINT;     /**< \brief �����ж�ʹ�ܺͱ�־�Ĵ��� */
        stc_can_errint_field_t ERRINT_f;
    };
    union
    {
        __IO uint8_t LIMIT;      /**< \brief CAN�����޶��Ĵ��� */
        stc_can_limit_field_t LIMIT_f;
    };
    union
    {
        __IO uint32_t BT;        /**< \brief CANλʱ��Ĵ��� */
        stc_can_bt_field_t BT_f;
    };
    uint8_t RESERVED17[4];       /**< \brief ���� */
    union
    {
        __IO uint8_t EALCAP;     /**< \brief CAN������ٲ�ʧ�ܲ�׽�Ĵ��� */
        stc_can_ealcap_field_t EALCAP_f;
    };
    uint8_t RESERVED18[1];       /**< \brief ���� */
    __IO uint8_t RECNT;          /**< \brief CAN���մ���������Ĵ��� */
    __IO uint8_t TECNT;          /**< \brief CAN���ʹ���������Ĵ��� */
    union
    {
        __IO uint8_t ACFCTRL;    /**< \brief CANɸѡ������ƼĴ��� */
        stc_can_acfctrl_field_t ACFCTRL_f;
    };
    uint8_t RESERVED21[1];       /**< \brief ���� */
    union
    {
        __IO uint8_t ACFEN;      /**< \brief ɸѡ����ʹ�ܼĴ���*/
        stc_can_acfen_field_t ACFEN_f;
    };
    uint8_t RESERVED22[1];       /**< \brief ���� */
    union
    {
        __IO uint32_t ACF;       /**< \brief ɸѡ����code��mask�Ĵ��� */
        stc_can_acf_field_t ACF_f;
    };
    uint8_t RESERVED23[2];       /**< \brief ���� */
    union
    {
        __IO uint8_t TBSLOT;     /**< \brief TTCAN TB slotָ��Ĵ���*/
        stc_can_tbslot_field_t TBSLOT_f;
    };
    union
    {
        __IO uint8_t TTCFG;      /**< \brief TTCANʱ�䴥�����üĴ���*/
        stc_can_ttcfg_field_t TTCFG_f;
    };
    union
    {
        __IO uint32_t REF_MSG;   /**< \brief �ο���Ϣ�Ĵ���*/
        stc_can_ref_msg_field_t REF_MSG_f;
    };
    union
    {
        __IO uint16_t TRG_CFG;   /**< \brief �������üĴ���*/
        stc_can_trg_cfg_field_t TRG_CFG_f;
    };
    __IO uint16_t TT_TRIG;       /**< \brief ����ʱ��Ĵ���*/
    __IO uint16_t TT_WTRIG;      /**< \brief ��������ʱ��Ĵ���*/
} amhw_hc32f460_can_t;

/**
 * \brief CANģʽ����
 */
typedef enum amhw_hc32f460_can_type {
    AMHW_HC32F460_CAN_BASIC_CAN = 0,        /**< \brief basic can */
    AMHW_HC32F460_CAN_PELI_CAN,             /**< \brief peli can */
}amhw_hc32f460_can_type_t;

/**
 * \brief CAN���ܶ���
 *
 * \note basic canֻ֪�и�λģʽ������ģʽ��˯��ģʽ
 *
 */
typedef enum amhw_hc32f460_can_mode_func {
    AMHW_HC32F460_CAN_MODE_RESET = 0,       /**< \brief ��λģʽ */
    AMHW_HC32F460_CAN_MODE_ONLY_LISTEN,     /**< \brief ֻ��ģʽ */
    AMHW_HC32F460_CAN_MODE_SELF_CHECK,      /**< \brief �Լ�ģʽ */
    AMHW_HC32F460_CAN_MODE_SLEEP = 4,       /**< \brief ˯��ģʽ */
    AMHW_HC32F460_CAN_MODE_RUN,             /**< \brief ����ģʽ */
}amhw_hc32f460_can_mode_t;

/**
 * \brief CAN���ݽ��շ�ʽ
 */
typedef enum amhw_hc32f460_can_recv_mode {
    AMHW_HC32F460_CAN_RECV_POLL = 0,        /**< \brief ��ѯ����ģʽ */
    AMHW_HC32F460_CAN_RECV_INT,             /**< \brief �жϽ���ģʽ */
}amhw_hc32f460_can_recv_mode_t;

/**
 * \brief peli CAN�˲���ʽ
 */
typedef enum amhw_hc32f460_can_peli_filter_mode {
    AMHW_HC32F460_CAN_PELI_SINGLE_FILTER,   /**< \brief peli can ���˲���ģʽ */
    AMHW_HC32F460_CAN_PELI_DOUBLE_FLITER,   /**< \brief peli can ˫�˲���ģʽ */
}amhw_hc32f460_can_peli_filter_mode_t;

/******************************************************************************/

/**
 * \brief CAN�ж�
 *
 * \note 
 *
 * @{
 */

#define AMHW_HC32F460_CAN_INT_RECV             (0x1 << 7ul)  /**< \brief �����ж� */
#define AMHW_HC32F460_CAN_INT_OVER             (0x1 << 6ul)  /**< \brief ��������ж� */
#define AMHW_HC32F460_CAN_INT_PTB_TRAN         (0x1 << 3ul)  /**< \brief PTB�����ж� */
#define AMHW_HC32F460_CAN_INT_STB_TRAN         (0x1 << 2ul)  /**< \brief STB�����ж� */
#define AMHW_HC32F460_CAN_INT_ERR              (0x1 << 1ul)  /**< \brief �����ж� */


typedef enum
{
    CanExternalLoopBackMode  = 0x40,        /**< \brief Loop back mode, external */
    CanInternalLoopBackMode  = 0x20,        /**< \brief Loop back mode, internal */
    CanTxSignalPrimaryMode   = 0x10,        /**< \brief Transmission primary single shot mode for PTB */
    CanTxSignalSecondaryMode = 0x08,        /**< \brief Transmission secondary single shot mode for STB */
    CanListenOnlyMode        = 0xFF,        /**< \brief Listen only mode */
}en_can_mode_t;

typedef enum en_can_functional_state
{
    CanDisable = 0u,
    CanEnable  = 1u,
} en_can_functional_state_t;

typedef enum
{
    CanRxNormal = 0,        /**< \brief Normal operation */
    CanRxAll    = 1,        /**< \brief RB stores correct data frames as well as data frames with error */
}en_can_rx_buf_all_t;

typedef enum
{
    CanRxBufOverwritten = 0,  /**< \brief The oldest message will be overwritten */
    CanRxBufNotStored   = 1,  /**< \brief The new message will not be stored */
}en_can_rx_buf_mode_en_t;

typedef enum
{
    CanSelfAckEnable  = 1,    /**< \brief Self-ACK when LBME=1 */
    CanSelfAckDisable = 0,    /**< \brief no self-ACK */
}en_can_self_ack_en_t;

typedef enum
{
    CanSTBFifoMode    = 0,    /**< \brief FIFO mode */
    CanSTBPrimaryMode = 1,    /**< \brief Priority decision mode */
}en_can_stb_mode_t;

typedef struct stc_can_bt
{
    uint8_t SEG_1;      /**< \brief Bit timing segment 1(Tseg_1 = (SEG_1 + 2)*TQ) */
    uint8_t SEG_2;      /**< \brief Bit timing segment 2(Tseg_2 = (SEG_2 + 1)*TQ) */
    uint8_t SJW;        /**< \brief Synchronization jump width(Tsjw = (SJW + 1)*TQ) */
    uint8_t PRESC;      /**< \brief The Prescaler divides the system clock to get the time quanta clock tq_clk(TQ) */
}stc_can_bt_t;

typedef struct stc_can_warning_limit
{
    uint8_t CanWarningLimitVal;         /**< \brief Receive buffer almost full warning limit */
    uint8_t CanErrorWarningLimitVal;    /**< \brief Programmable error warning limit */
}stc_can_warning_limit_t;

typedef struct stc_can_init_config
{
    en_can_rx_buf_all_t     enCanRxBufAll;      /**< \brief en_can_rx_buf_all_t */
    en_can_rx_buf_mode_en_t enCanRxBufMode;     /**< \brief en_can_rx_buf_mode_en_t */
    en_can_self_ack_en_t    enCanSAck;          /**< \brief en_can_self_ack_en_t */
    en_can_stb_mode_t       enCanSTBMode;       /**< \brief en_can_stb_mode_t */
    stc_can_bt_t            stcCanBt;           /**< \brief stc_can_bt_t */
    stc_can_warning_limit_t stcWarningLimit;    /**< \brief stc_can_warning_limit_t */
}stc_can_init_config_t;

typedef struct
{
    uint32_t DLC                     : 4;        /**< \brief Data length code */
    uint32_t RESERVED0               : 2;        /**< \brief Ignore */
    uint32_t RTR                     : 1;        /**< \brief Remote transmission request */
    uint32_t IDE                     : 1;        /**< \brief IDentifier extension */
    uint32_t RESERVED1               : 24;       /**< \brief Ignore */
}stc_can_txcontrol_t;

typedef enum
{
    CanPTBSel       = 0U,        /**< \brief high-priority buffer */
    CanSTBSel       = 1U,        /**< \brief secondary buffer */
}en_can_buffer_sel_t;

typedef struct stc_can_txframe
{
    union
    {
        uint32_t TBUF32_0;       /**< \brief Ignore */
        uint32_t StdID;          /**< \brief Standard ID */
        uint32_t ExtID;          /**< \brief Extended ID */
    };
    union
    {
        uint32_t TBUF32_1;                  /**< \brief Ignore */
        stc_can_txcontrol_t Control_f;      /**< \brief CAN Tx Control */
    };
    union
    {
        uint32_t TBUF32_2[2];               /**< \brief Ignore */
        uint8_t  Data[8];                   /**< \brief CAN data */
    };
    en_can_buffer_sel_t     enBufferSel;    /**< \brief CAN Tx buffer select */

}stc_can_txframe_t;

typedef enum
{
    CanTxBufEmpty        = 0,       /**< \brief TTEN=0 or  TTTBM=0: STB is empty */
                                    /**< \brief TTEN=1 and TTTBM=1: PTB and STB are empty */
    CanTxBufnotHalfFull  = 1,       /**< \brief TTEN=0 or  TTTBM=0: STB is less than or equal to half full */
                                    /**< \brief TTEN=1 and TTTBM=1: PTB and STB are not empty and not full */
    CanTxBufHalfFull     = 2,       /**< \brief TTEN=0 or  TTTBM=0: STB is more than half full */
                                    /**< \brief TTEN=1 and TTTBM=1: None */
    CanTxBufFull         = 3,       /**< \brief TTEN=0 or  TTTBM=0: STB is full */
                                    /**< \brief TTEN=1 and TTTBM=1: PTB and STB are full */
}en_can_tx_buf_status_t;

typedef enum
{
    CanPTBTxCmd      = 0x10,        /**< \brief Transmit primary for PTB */
    CanPTBTxAbortCmd = 0x08,        /**< \brief Transmit primary abort for PTB */
    CanSTBTxOneCmd   = 0x04,        /**< \brief Transmit secondary one frame for STB */
    CanSTBTxAllCmd   = 0x02,        /**< \brief Transmit secondary all frames for STB */
    CanSTBTxAbortCmd = 0x01,        /**< \brief Transmit secondary abort for STB */
}en_can_tx_cmd_t;

typedef enum
{
    CanRxBufEmpty          = 0,        /**< \brief Empty */
    CanRxBufnotAlmostFull  = 1,        /**< \brief >empty and <almost full */
    CanRxBufAlmostFull     = 2,        /**< \brief >=almost full, but not full and no overflow */
    CanRxBufFull           = 3,        /**< \brief full */
}en_can_rx_buf_status_t;

typedef struct
{
    uint8_t DLC          : 4;       /**< \brief Data length code */
    uint8_t RESERVED0    : 2;       /**< \brief Ignore */
    uint8_t RTR          : 1;       /**< \brief Remote transmission request */
    uint8_t IDE          : 1;       /**< \brief IDentifier extension */
}stc_can_rxcontrol_t;

typedef struct
{
    uint8_t RESERVED0    : 4;       /**< \brief Ignore */
    uint8_t TX           : 1;       /**< \brief TX is set to 1 if the loop back mode is activated */
    uint8_t KOER         : 3;       /**< \brief Kind of error */
}stc_can_status_t;

typedef struct
{
    stc_can_rxcontrol_t Control_f;  /**< \brief stc_can_rxcontrol_t */
    stc_can_status_t    Status_f;   /**< \brief stc_can_status_t */
    uint16_t            CycleTime;  /**< \brief TTCAN cycletime */
}stc_can_cst_t;

typedef struct stc_can_rxframe
{
    union
    {
        uint32_t RBUF32_0;              /**< \brief Ignore */
        uint32_t StdID;                 /**< \brief Standard ID */
        uint32_t ExtID;                 /**< \brief Extended ID */
    };
    union
    {
        uint32_t        RBUF32_1;       /**< \brief Ignore */
        stc_can_cst_t   Cst;            /**< \brief @ref stc_can_cst_t */
    };
    union
    {
        uint32_t RBUF32_2[2];           /**< \brief Ignore */
        uint8_t  Data[8];               /**< \brief CAN data */
    };

}stc_can_rxframe_t;


typedef enum
{
    /** \brief Can Tx or Tx Irq Flg */
    CanTxBufFullIrqFlg          = 0x00000001,
    CanRxIrqFlg                 = 0x00008000,   /**< \brief Receive interrupt flag */
    CanRxOverIrqFlg             = 0x00004000,   /**< \brief RB overrun interrupt flag */
    CanRxBufFullIrqFlg          = 0x00002000,   /**< \brief RB full interrupt flag */
    CanRxBufAlmostFullIrqFlg    = 0x00001000,   /**< \brief RB almost full interrupt flag */
    CanTxPrimaryIrqFlg          = 0x00000800,   /**< \brief Transmission primary interrupt flag */
    CanTxSecondaryIrqFlg        = 0x00000400,   /**< \brief Transmission secondary interrupt flag */
    CanErrorIrqFlg              = 0x00000200,   /**< \brief Error interrupt flag */
    CanAbortIrqFlg              = 0x00000100,   /**< \brief Abort interrupt flag */

    /** \brief Can Error Irq Flg */
    CanErrorWarningIrqFlg       = 0x00800000,   /**< \brief Error warning limit reached flag */
    CanErrorPassivenodeIrqFlg   = 0x00400000,   /**< \brief Error passive mode active flag */
    CanErrorPassiveIrqFlg       = 0x00100000,   /**< \brief Error passive interrupt flag */
    CanArbiLostIrqFlg           = 0x00040000,   /**< \brief Arbitration lost interrupt flag */
    CanBusErrorIrqFlg           = 0x00010000,   /**< \brief Bus error interrupt flag */
}en_can_irq_flag_type_t;

typedef enum
{
    /** \brief Can Rx or Tx Irq En */
    CanRxIrqEn              = 0x00000080,   /**< \brief Receive interrupt enable */
    CanRxOverIrqEn          = 0x00000040,   /**< \brief RB overrun interrupt enable */
    CanRxBufFullIrqEn       = 0x00000020,   /**< \brief RB full interrupt enable */
    CanRxBufAlmostFullIrqEn = 0x00000010,   /**< \brief RB almost full interrupt enable */
    CanTxPrimaryIrqEn       = 0x00000008,   /**< \brief Transmission primary interrupt enable */
    CanTxSecondaryIrqEn     = 0x00000004,   /**< \brief Transmission secondary enable */
    CanErrorIrqEn           = 0x00000002,   /**< \brief Error interrupt enable */

    /** \brief Can Error Irq En */
    CanErrorPassiveIrqEn    = 0x00200000,   /**< \brief Error passive mode active enable */
    CanArbiLostIrqEn        = 0x00080000,   /**< \brief Arbitration lost interrupt enable */
    CanBusErrorIrqEn        = 0x00020000,   /**< \brief Bus error interrupt enable */

}en_can_irq_type_t;

typedef enum en_can_filter_sel
{
    CanFilterSel1        = 0u,   /**< \brief The Acceptance Filter 1 Enable */
    CanFilterSel2        = 1u,   /**< \brief The Acceptance Filter 2 Enable */
    CanFilterSel3        = 2u,   /**< \brief The Acceptance Filter 3 Enable */
    CanFilterSel4        = 3u,   /**< \brief The Acceptance Filter 4 Enable */
    CanFilterSel5        = 4u,   /**< \brief The Acceptance Filter 5 Enable */
    CanFilterSel6        = 5u,   /**< \brief The Acceptance Filter 6 Enable */
    CanFilterSel7        = 6u,   /**< \brief The Acceptance Filter 7 Enable */
    CanFilterSel8        = 7u,   /**< \brief The Acceptance Filter 8 Enable */
}en_can_filter_sel_t;

typedef enum en_can_acf_format_en
{
    CanStdFrames        = 0x02u,   /**< \brief Accepts only Standard frames */
    CanExtFrames        = 0x03u,   /**< \brief Accepts only Extended frames */
    CanAllFrames        = 0x00u,   /**< \brief Accepts both standard or extended frames */
}en_can_acf_format_en_t;

typedef struct stc_can_filter
{
    uint32_t                u32CODE;        /**< \brief Acceptance CODE */
    uint32_t                u32MASK;        /**< \brief Acceptance MASK */
    en_can_filter_sel_t     enFilterSel;    /**< \brief The Acceptance Filters Enable */
    en_can_acf_format_en_t  enAcfFormat;    /**< \brief The Acceptance Filters Frame Format Check. */
}stc_can_filter_t;

typedef enum
{
    NO_ERROR        = 0U,
    BIT_ERROR       = 1U,
    FORM_ERROR      = 2U,
    STUFF_ERROR     = 3U,
    ACK_ERROR       = 4U,
    CRC_ERROR       = 5U,
    UNKOWN_ERROR    = 6U,
}en_can_error_t;

typedef enum
{
    CanRxActive = 0x04,        /**< \brief Reception active */
    CanTxActive = 0x02,        /**< \brief Transmission active */
    CanBusoff   = 0x01,        /**< \brief Bus off */
}en_can_status_t;

am_static_inline
void amhw_hc32f460_can_mode_config(amhw_hc32f460_can_t *p_hw_can, en_can_mode_t enMode, en_can_functional_state_t enNewState)
{
    if(CanListenOnlyMode == enMode)
    {
        p_hw_can->TCMD_f.LOM = enNewState;
    }else
    {
        if(CanEnable == enNewState)
        {
            p_hw_can->CFG_STAT |= enMode;
        }else
        {
            p_hw_can->CFG_STAT &= ~enMode;
        }
    }
}

#define CAN_RESET_ENABLE(p_hw_can)       (p_hw_can->CFG_STAT_f.RESET = 1u)
#define CAN_RESET_DISABLE(p_hw_can)                                                     \
do{                                                                             \
    do{                                                                         \
        p_hw_can->CFG_STAT_f.RESET = 0u;                                          \
    }while(p_hw_can->CFG_STAT_f.RESET);                                               \
}while(0)

am_static_inline
void amhw_hc32f460_can_lowlevel_set(amhw_hc32f460_can_t *p_hw_can, stc_can_init_config_t *pstcCanInitCfg)
{
    if (NULL != pstcCanInitCfg)
    {
        p_hw_can->RCTRL_f.SACK   = pstcCanInitCfg->enCanSAck;
        p_hw_can->TCTRL_f.TSMODE = pstcCanInitCfg->enCanSTBMode;
        p_hw_can->RCTRL_f.RBALL  = pstcCanInitCfg->enCanRxBufAll;
        p_hw_can->RCTRL_f.ROM    = pstcCanInitCfg->enCanRxBufMode;

        p_hw_can->RTIE = 0x00u;

        CAN_RESET_ENABLE(p_hw_can);

        p_hw_can->BT_f.PRESC = pstcCanInitCfg->stcCanBt.PRESC;
        p_hw_can->BT_f.SEG_1 = pstcCanInitCfg->stcCanBt.SEG_1;
        p_hw_can->BT_f.SEG_2 = pstcCanInitCfg->stcCanBt.SEG_2;
        p_hw_can->BT_f.SJW   = pstcCanInitCfg->stcCanBt.SJW;

        p_hw_can->LIMIT_f.AFWL = pstcCanInitCfg->stcWarningLimit.CanWarningLimitVal;
        p_hw_can->LIMIT_f.EWL  = pstcCanInitCfg->stcWarningLimit.CanErrorWarningLimitVal;

        CAN_RESET_DISABLE(p_hw_can);
    }
}

am_static_inline
void amhw_hc32f460_can_lowlevel_get(amhw_hc32f460_can_t *p_hw_can, stc_can_init_config_t *pstcCanInitCfg)
{
    if (NULL != pstcCanInitCfg)
    {
        pstcCanInitCfg->enCanSAck      = (en_can_self_ack_en_t)p_hw_can->RCTRL_f.SACK;
        pstcCanInitCfg->enCanSTBMode   = (en_can_stb_mode_t)p_hw_can->TCTRL_f.TSMODE;
        pstcCanInitCfg->enCanRxBufAll  = (en_can_rx_buf_all_t)p_hw_can->RCTRL_f.RBALL;
        pstcCanInitCfg->enCanRxBufMode = (en_can_rx_buf_mode_en_t)p_hw_can->RCTRL_f.ROM;

        p_hw_can->RTIE = 0x00u;

        CAN_RESET_ENABLE(p_hw_can);

        pstcCanInitCfg->stcCanBt.PRESC = p_hw_can->BT_f.PRESC;
        pstcCanInitCfg->stcCanBt.SEG_1 = p_hw_can->BT_f.SEG_1;
        pstcCanInitCfg->stcCanBt.SEG_2 = p_hw_can->BT_f.SEG_2;
        pstcCanInitCfg->stcCanBt.SJW   = p_hw_can->BT_f.SJW;

        pstcCanInitCfg->stcWarningLimit.CanWarningLimitVal       = p_hw_can->LIMIT_f.AFWL;
        pstcCanInitCfg->stcWarningLimit.CanErrorWarningLimitVal  = p_hw_can->LIMIT_f.EWL;

        CAN_RESET_DISABLE(p_hw_can);
    }
}


am_static_inline
uint8_t amhw_hc32f460_can_rx_error_cnt_get(amhw_hc32f460_can_t *p_hw_can)
{
    return p_hw_can->RECNT;
}

am_static_inline
void amhw_hc32f460_can_rx_error_cnt_clr(amhw_hc32f460_can_t *p_hw_can)
{
    p_hw_can->RECNT = 0;
}

am_static_inline
uint8_t amhw_hc32f460_can_tx_error_cnt_get(amhw_hc32f460_can_t *p_hw_can)
{
    return p_hw_can->TECNT;
}

am_static_inline
void amhw_hc32f460_can_tx_error_cnt_clr(amhw_hc32f460_can_t *p_hw_can)
{
    p_hw_can->TECNT = 0;
}

am_static_inline
void amhw_hc32f460_can_set_frame(amhw_hc32f460_can_t *p_hw_can, stc_can_txframe_t *pstcTxFrame)
{
    if(NULL != pstcTxFrame)
    {
        p_hw_can->TCMD_f.TBSEL = pstcTxFrame->enBufferSel;
        p_hw_can->TBUF0 = pstcTxFrame->TBUF32_0;
        p_hw_can->TBUF1 = pstcTxFrame->TBUF32_1;
        p_hw_can->TBUF2 = pstcTxFrame->TBUF32_2[0];
        p_hw_can->TBUF3 = pstcTxFrame->TBUF32_2[1];

        if(CanSTBSel == pstcTxFrame->enBufferSel)
        {
            p_hw_can->TCTRL_f.TSNEXT = CanEnable;
        }
    }
}

am_static_inline
en_can_tx_buf_status_t amhw_hc32f460_can_transmit_cmd(amhw_hc32f460_can_t *p_hw_can, en_can_tx_cmd_t enTxCmd)
{
    p_hw_can->TCMD |= enTxCmd;

    return (en_can_tx_buf_status_t)p_hw_can->TCTRL_f.TSSTAT;

}

am_static_inline
en_can_rx_buf_status_t amhw_hc32f460_can_receive(amhw_hc32f460_can_t *p_hw_can, stc_can_rxframe_t *pstcRxFrame)
{
    if(NULL != pstcRxFrame)
    {
        pstcRxFrame->RBUF32_0    = p_hw_can->RBUF0;
        pstcRxFrame->RBUF32_1    = p_hw_can->RBUF1;
        pstcRxFrame->RBUF32_2[0] = p_hw_can->RBUF2;
        pstcRxFrame->RBUF32_2[1] = p_hw_can->RBUF3;

        p_hw_can->RCTRL_f.RREL = 1u;
    }
    return (en_can_rx_buf_status_t)p_hw_can->RCTRL_f.RSSTAT;
}

am_static_inline
am_bool_t amhw_hc32f460_can_irq_flag_get(amhw_hc32f460_can_t *p_hw_can, en_can_irq_flag_type_t enCanIrqFlgType)
{
    volatile uint32_t *u32pIE = NULL;
    am_bool_t bRet = AM_FALSE;

    u32pIE = (volatile uint32_t*)(&p_hw_can->RTIE);
    if( *u32pIE & enCanIrqFlgType)
    {
        bRet = AM_TRUE;
    }
    return bRet;
}

am_static_inline
uint8_t amhw_hc32f460_can_int_status_get(amhw_hc32f460_can_t *p_hw_can)
{    
   return p_hw_can->RTIF;
}

am_static_inline
uint8_t  amhw_hc32f460_can_status_get(amhw_hc32f460_can_t *p_hw_can, en_can_status_t enCanStatus)
{
    am_bool_t bRet = AM_FALSE;

    if(p_hw_can->CFG_STAT & enCanStatus)
    {
        bRet = AM_TRUE;
    }
    return bRet;
}


am_static_inline
void amhw_hc32f460_can_irq_flag_clr(amhw_hc32f460_can_t *p_hw_can, en_can_irq_flag_type_t enCanIrqFlgType)
{
    volatile uint32_t *u32pIE = NULL;

    u32pIE = (volatile uint32_t*)(&p_hw_can->RTIE);

    *u32pIE |= enCanIrqFlgType;
}

am_static_inline
void amhw_hc32f460_can_irq_cmd(amhw_hc32f460_can_t *p_hw_can, en_can_irq_type_t enCanIrqType, en_can_functional_state_t enNewState)
{
    volatile uint32_t *u32pIE;

    u32pIE = (volatile uint32_t*)(&p_hw_can->RTIE);

    if(CanEnable == enNewState)
    {
        *u32pIE |= enCanIrqType;
    }else
    {
        *u32pIE &= ~((uint32_t)enCanIrqType);
    }

}

#define CAN_ACF_ID_REG_SEL                  ((uint8_t)0x00u)
#define CAN_ACF_MASK_REG_SEL                ((uint8_t)0x01u)

am_static_inline
void amhw_hc32f460_can_filter_config(amhw_hc32f460_can_t *p_hw_can, const stc_can_filter_t *pstcFilter, en_can_functional_state_t enNewState)
{
    if(NULL != pstcFilter)
    {
        CAN_RESET_ENABLE(p_hw_can);

        //<<Acceptance filter address
        p_hw_can->ACFCTRL_f.ACFADR  = pstcFilter->enFilterSel;

        //<<ID config
        p_hw_can->ACFCTRL_f.SELMASK = CAN_ACF_ID_REG_SEL;
        p_hw_can->ACF               = pstcFilter->u32CODE;

        //<<MASK config
        p_hw_can->ACFCTRL_f.SELMASK = CAN_ACF_MASK_REG_SEL;
        p_hw_can->ACF               = pstcFilter->u32MASK;

        //<<Frame format config
        p_hw_can->ACF_f.AIDEE = ((pstcFilter->enAcfFormat >> 1ul) & 0x01u);
        p_hw_can->ACF_f.AIDE  = (pstcFilter->enAcfFormat & 0x01ul);

        if(CanEnable == enNewState)
        {
            p_hw_can->ACFEN |= (uint8_t)(1ul << pstcFilter->enFilterSel);
        }else
        {
            p_hw_can->ACFEN &= (uint8_t)(~(1ul << (pstcFilter->enFilterSel)));
        }

        CAN_RESET_DISABLE(p_hw_can);
    }
}

am_static_inline
en_can_error_t amhw_hc32f460_can_error_status_get(amhw_hc32f460_can_t *p_hw_can)
{
    en_can_error_t enRet = UNKOWN_ERROR;

    if(6u > p_hw_can->EALCAP_f.KOER)
    {
        enRet = (en_can_error_t)p_hw_can->EALCAP_f.KOER;
    }
    return enRet;

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
 * @} amhw_hc32f460_if_can
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_CAN_H */

/* end of file */

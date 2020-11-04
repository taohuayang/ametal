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
 *       r_w1  r_w
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-31  zc, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG237_CAN_H
#define __AMHW_ZLG237_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_zlg237_if_can
 * \copydoc amhw_zlg237_can.h
 * @{
 */
/* \brief ��������Ĵ���  */
typedef struct amhw_zlg237_can_tx {
    __IO  uint32_t tir;      /**< \brief 0x180 ���������ʶ���Ĵ��� */
    __IO  uint32_t tdtr;     /**< \brief 0x184 �����������ݳ��Ⱥ�ʱ����Ĵ���*/
    __IO  uint32_t tdlr;     /**< \brief 0x188 ����������ֽ����ݼĴ���*/
    __IO  uint32_t tdhr;     /**< \brief 0x18c ����������ֽ����ݼĴ��� */
}amhw_zlg237_can_tx_t;

/* \brief ����FIFO����Ĵ���  */
typedef struct amhw_zlg237_can_rx {
    __IO  uint32_t rir;      /**< \brief 0x1c0  ����FIFO�����ʶ���Ĵ���*/
    __IO  uint32_t rdtr;     /**< \brief 0x1c4 ����FIFO�������ݳ��Ⱥ�ʱ����Ĵ��� */
    __IO  uint32_t rdlr;     /**< \brief 0x1c8 ����FIFO������ֽ����ݼĴ��� */
    __IO  uint32_t rdhr;     /**< \brief 0x1cc ����FIFO������ֽ����ݼĴ���*/
}amhw_zlg237_can_rx_t;

/* \brief ��������Ĵ���  */
typedef struct amhw_zlg237_can_firx {
    __IO  uint32_t f_r1;     /**< \brief ��������Ĵ��� 1 */
    __IO  uint32_t f_r2;     /**< \brief ��������Ĵ��� 2 */
}amhw_zlg237_can_firx_t;

/**
 * \brief ZLG237 CAN�Ĵ�����ṹ��
 */
typedef struct amhw_zlg237_can {

    __IO  uint32_t mcr;             /**< \brief 0x00 �����ƼĴ��� */
    __IO  uint32_t msr;             /**< \brief 0x04 ��״̬�Ĵ��� */
    __IO  uint32_t tsr;             /**< \brief 0x08 ����״̬�Ĵ��� */
    __IO  uint32_t rf_0r;           /**< \brief 0x0c ����FIFO 0 �Ĵ��� */
    __IO  uint32_t rf_1r;           /**< \brief 0x10 ����FIFO 1 �Ĵ��� */
    __IO  uint32_t ier;             /**< \brief 0x14 �ж�ʹ�ܼĴ��� */
    __IO  uint32_t esr;             /**< \brief 0x18 ����״̬�Ĵ��� */
    __IO  uint32_t btr;             /**< \brief 0x1c λʱ��ʹ�ܼĴ��� */

          uint32_t reserve_0[88];   /**< \brief ����λ*/

    /**< \brief 0x180...0x1ac ��������Ĵ��� */
    __IO  amhw_zlg237_can_tx_t tx_mail[3];

    /**< \brief 0x1b0...0x1cc ����FIFO����Ĵ��� */
    __IO  amhw_zlg237_can_rx_t rx_mail[2];

          uint32_t reserve_1[12];   /**< \brief ����λ*/

    __IO  uint32_t fmr;             /**< \brief 0x200 ���������ؼĴ��� */
    __IO  uint32_t fm_1r;           /**< \brief 0x204 ������ģʽ�Ĵ��� */
          uint32_t reserve_2;       /**< \brief ����λ*/
    __IO  uint32_t fs_1r;           /**< \brief 0x20c ������λ��Ĵ��� */
          uint32_t reserve_3;       /**< \brief ����λ*/
    __IO  uint32_t ffa_1r;          /**< \brief 0x214 ������FIFO�����Ĵ��� */
          uint32_t reserve_4;       /**< \brief ����λ*/
    __IO  uint32_t fa_1r;           /**< \brief 0x21c ����������Ĵ��� */
          uint32_t reserve_5[8];    /**< \brief ����λ*/

    /**< \brief 0x240...0x31c ��������Ĵ��� */
    __IO  amhw_zlg237_can_firx_t fi_rx[14];


}amhw_zlg237_can_t;

/**<brief ������Ϣ */
typedef struct {
    uint32_t std_id;    /**< \brief ��ʶ�� */
    uint32_t ext_id;    /**< \brief ��չ��ʶ��*/
    uint8_t  ide;       /**< \brief ��ʶ��ѡ��*/
    uint8_t  rtr;       /**< \brief Զ�̷������� ����֡    Զ��֡*/
    uint8_t  dlc;       /**< \brief �������ݳ���*/
    uint8_t  data[8];   /**< \brief �����͵�����*/
} amhw_zlg237_can_tx_msg_t;

/**<brief ������Ϣ */
typedef struct {
    uint32_t std_id;    /**< \brief ��ʶ�� */
    uint32_t ext_id;    /**< \brief ��չ��ʶ��*/
    uint8_t  ide;       /**< \brief ��ʶ��ѡ��*/
    uint8_t  rtr;       /**< \brief Զ�̷������� ����֡    Զ��֡*/
    uint8_t  dlc;       /**< \brief �������ݳ���*/
    uint8_t  data[8];   /**< \brief �����͵�����*/
    uint8_t  fmi;       /**< \brief ������ƥ�����*/
} amhw_zlg237_can_rx_msg_t;

/**
 * \brief CAN����ģʽ����
 */
typedef enum amhw_zlg237_can_operating_type {
    AMHW_ZLG237_CAN_OPERATING_MODE_INIT= 1,      /**< \brief ��ʼ��ģʽ */
    AMHW_ZLG237_CAN_OPERATING_NORMAL,            /**< \brief ����ģʽ*/
    AMHW_ZLG237_CAN_OPERATING_SLEEP,             /**< \brief ˯��ģʽ*/
}amhw_zlg237_can_mode_t;

/**
 * \brief CAN�Բ�ģʽ����
 */
typedef enum  {
    AMHW_ZLG237_CAN_MODE_NORMAL = 0,            /**< \brief ����ģʽ*/
    AMHW_ZLG237_CAN_MODE_LOOPBACK,            /**< \brief ����ģʽ*/
    AMHW_ZLG237_CAN_MODE_SILENT,              /**< \brief ��Ĭģʽ*/
    AMHW_ZLG237_CAN_MODE_SIEENT_LOOPBACK,     /**< \brief ���ؾ�Ĭ*/
}amhw_zlg237_can_test_mode_t;

/**\brief �ж�Դ���� */
typedef enum {
    AMHW_ZLG237_CAN_INT_TMEIE = 0,            /**< \brief ����������ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_FMPIE0,               /**< \brief FIFO 0 ��Ϣ�Һ��ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_FFIE0,                /**< \brief FIFO 0 ���ж��ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_FOVIE0,               /**< \brief FIFO 0 ����ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_FMPIE1,               /**< \brief FIFO 1 ��Ϣ�Һ��ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_FFIE1,                /**< \brief FIFO 1 ���ж��ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_FOVIE1,               /**< \brief FIFO 1 ����ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_EWGIE = 8,            /**< \brief ���󾯸��ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_EPVIE,                /**< \brief ���󱻶��ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_BOFIE,                /**< \brief �����ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_LECIE,                /**< \brief �ϴδ�����ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_ERRIE = 15,           /**< \brief �����ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_WKUIE,                /**< \brief �����ж�ʹ�� */
    AMHW_ZLG237_CAN_INT_SLKIE,                /**< \brief ˯���ж�ʹ�� */
}amhw_zlg237_can_int_t;

#define AMHW_ZLG237_CAN_FLAG_TSR    ((uint32_t)0x08000000)
#define AMHW_ZLG237_CAN_FLAG_RF1R   ((uint32_t)0x04000000)
#define AMHW_ZLG237_CAN_FLAG_RF0R   ((uint32_t)0x02000000)
#define AMHW_ZLG237_CAN_FLAG_MSR    ((uint32_t)0x01000000)
#define AMHW_ZLG237_CAN_FLAG_ESR    ((uint32_t)0x00F00000)

/**\brief flag��־λ���� */
typedef enum {
    /* ����*/
    AMHW_ZLG237_CAN_FLAG_RQCP0 = 0X38000001,  /**< \brief ����0������� */
    AMHW_ZLG237_CAN_FLAG_RQCP1 = 0X38000100,  /**< \brief ����1������� */
    AMHW_ZLG237_CAN_FLAG_RQCP2 = 0X38010000,  /**< \brief ����2������� */

    /* ���� */
    AMHW_ZLG237_CAN_FLAG_FMP0  = 0X12000003,  /**< \brief FIFO 0 �Һ�*/
    AMHW_ZLG237_CAN_FLAG_FF0   = 0X32000008,  /**< \brief FIFO 0 �� */
    AMHW_ZLG237_CAN_FLAG_FOV0  = 0X32000010,  /**< \brief FIFO 0 ��� */
    AMHW_ZLG237_CAN_FLAG_FMP1  = 0X14000003,  /**< \brief FIFO 1 �Һ� */
    AMHW_ZLG237_CAN_FLAG_FF1   = 0X34000008,  /**< \brief FIFO 1 ��  */
    AMHW_ZLG237_CAN_FLAG_FOV1  = 0X34000010,  /**< \brief FIFO 1 ��� */

    /* ����ģʽ */
    AMHW_ZLG237_CAN_FLAG_WKU   = 0X31000008,  /**< \brief ���ѱ�ʶλ */
    AMHW_ZLG237_CAN_FLAG_SKAK  = 0X31000012,  /**< \brief ˯��Ӧ�� */

    AMHW_ZLG237_CAN_FLAG_ERI   = 0x31000040,  /**< \brief �����жϹҺ� */

    /* ���� */
    AMHW_ZLG237_CAN_FLAG_EWG   = 0X10f00001,  /**< \brief ���󾯸� */
    AMHW_ZLG237_CAN_FLAG_EPV   = 0X10f00002,  /**< \brief ���󱻶� */
    AMHW_ZLG237_CAN_FLAG_BOF   = 0X10f00004,  /**< \brief ���� */
    AMHW_ZLG237_CAN_FLAG_LEC   = 0x30f00070,  /**< \brief �ϴδ������ */

}amhw_zlg237_can_flag_t;

/** \brief �жϱ�־ */
typedef enum {
    AMHW_ZLG237_CAN_INT_FLAG_TME  = ((uint32_t)0x00000001),
    AMHW_ZLG237_CAN_INT_FLAG_RQCP0 = AMHW_ZLG237_CAN_INT_FLAG_TME,
    AMHW_ZLG237_CAN_INT_FLAG_RQCP1 = AMHW_ZLG237_CAN_INT_FLAG_TME,
    AMHW_ZLG237_CAN_INT_FLAG_RQCP2 = AMHW_ZLG237_CAN_INT_FLAG_TME,
    AMHW_ZLG237_CAN_INT_FLAG_FMP0 = ((uint32_t)0x00000002),
    AMHW_ZLG237_CAN_INT_FLAG_FF0  = ((uint32_t)0x00000004),
    AMHW_ZLG237_CAN_INT_FLAG_FOV0 = ((uint32_t)0x00000008),
    AMHW_ZLG237_CAN_INT_FLAG_FMP1 = ((uint32_t)0x00000010),
    AMHW_ZLG237_CAN_INT_FLAG_FF1  = ((uint32_t)0x00000020),
    AMHW_ZLG237_CAN_INT_FLAG_FOV1 = ((uint32_t)0x00000040),

    AMHW_ZLG237_CAN_INT_FLAG_WKU = ((uint32_t)0x00010000),
    AMHW_ZLG237_CAN_INT_FLAG_SLK = ((uint32_t)0x00020000),
    AMHW_ZLG237_CAN_INT_FLAG_EWG = ((uint32_t)0x00000100),
    AMHW_ZLG237_CAN_INT_FLAG_EPV = ((uint32_t)0x00000200),
    AMHW_ZLG237_CAN_INT_FLAG_BOF = ((uint32_t)0x00000400),
    AMHW_ZLG237_CAN_INT_FLAG_LEC = ((uint32_t)0x00000800),
    AMHW_ZLG237_CAN_INT_FLAG_ERR = ((uint32_t)0x00008000),
}amhw_zlg237_can_int_flag_t;




typedef enum  {
    AMHW_ZLG237_CAN_BS1_1TQ = 0,
    AMHW_ZLG237_CAN_BS1_2TQ,
    AMHW_ZLG237_CAN_BS1_3TQ,
    AMHW_ZLG237_CAN_BS1_4TQ,
    AMHW_ZLG237_CAN_BS1_5TQ,
    AMHW_ZLG237_CAN_BS1_6TQ,
    AMHW_ZLG237_CAN_BS1_7TQ,
    AMHW_ZLG237_CAN_BS1_8TQ,
    AMHW_ZLG237_CAN_BS1_9TQ,
    AMHW_ZLG237_CAN_BS1_10TQ,
    AMHW_ZLG237_CAN_BS1_11TQ,
    AMHW_ZLG237_CAN_BS1_12TQ,
    AMHW_ZLG237_CAN_BS1_13TQ,
    AMHW_ZLG237_CAN_BS1_14TQ,
    AMHW_ZLG237_CAN_BS1_15TQ,
    AMHW_ZLG237_CAN_BS1_16TQ,
}amhw_zlg237_can_bs1_t;

typedef enum  {
    AMHW_ZLG237_CAN_BS2_1TQ = 0,
    AMHW_ZLG237_CAN_BS2_2TQ,
    AMHW_ZLG237_CAN_BS2_3TQ,
    AMHW_ZLG237_CAN_BS2_4TQ,
    AMHW_ZLG237_CAN_BS2_5TQ,
    AMHW_ZLG237_CAN_BS2_6TQ,
    AMHW_ZLG237_CAN_BS2_7TQ,
    AMHW_ZLG237_CAN_BS2_8TQ,
}amhw_zlg237_can_bs2_t;

#define CAN_DISABLE 0x00
#define CAN_ENABLE  0x01


#define AMHW_ZLG237_CAN_SJW_1TQ    ((uint8_t)0x00)      /**< \brief 1��ʱ�䵥Ԫ */
#define AMHW_ZLG237_CAN_SJW_2TQ    ((uint8_t)0x01)      /**< \brief 2��ʱ�䵥Ԫ */
#define AMHW_ZLG237_CAN_SJW_3TQ    ((uint8_t)0x02)      /**< \brief 3��ʱ�䵥Ԫ */
#define AMHW_ZLG237_CAN_SJW_4TQ    ((uint8_t)0x03)      /**< \brief 4��ʱ�䵥Ԫ */

/**< \brief ��׼��ʶ�� */
#define AMHW_ZLG237_CAN_ID_STANDARD    ((uint32_t)0x00000000)

/**< \brief ��չ��ʶ�� */
#define AMHW_ZLG237_CAN_ID_EXTENDED    ((uint32_t)0x00000001)

#define CAN_IS_STD      AMHW_ZLG237_CAN_ID_STANDARD
#define CAN_ID_EXT      AMHW_ZLG237_CAN_ID_EXTENDED

/**< \brief ����֡ */
#define AMHW_ZLG237_CAN_RTR_DATA       ((uint32_t)0x00000000)

/**< \brief Զ��֡ */
#define AMHW_ZLG237_CAN_RTR_REMOTE     ((uint32_t)0x00000001)

#define CAN_RTR_DATA        AMHW_ZLG237_CAN_RTR_DATA
#define CAN_RTR_REMOTE      AMHW_ZLG237_CAN_RTR_REMOTE

/** \brief �˲���λ�� */
#define AMHW_ZLG237_CAN_FILTER_SCALE_16BIT  0X00
#define AMHW_ZLG237_CAN_FILTER_SCALE_32BIT  0X01

/** \brief �˲���ģʽ */
#define AMHW_ZLG237_CAN_FILTER_MODE_IDMASK  0X00    /**< \brief ����λģʽ */
#define AMHW_ZLG237_CAN_FILTER_MODE_IDLIST  0X01    /**< \brief ��ʶ���б�ģʽ */

/** \brief �˲���FIFO ���� */
#define AMHW_ZLG237_CAN_FILTER_FIFO0  0X00    /**< \brief FIFO 0  */
#define AMHW_ZLG237_CAN_FILTER_FIFO1  0X01    /**< \brief FIFO 1 */

#define AMHW_ZLG237_CAN_LEC_NOERR      0X00    /**< \brief �޴���  */
#define AMHW_ZLG237_CAN_LEC_STUFER     0X01    /**< \brief λ������  */
#define AMHW_ZLG237_CAN_LEC_FORMER     0X02    /**< \brief ��ʽ����  */
#define AMHW_ZLG237_CAN_LEC_ACKER      0X03    /**< \brief ȷ�ϴ���  */
#define AMHW_ZLG237_CAN_LEC_BRCER      0X04    /**< \brief ���Դ���  */
#define AMHW_ZLG237_CAN_LEC_BDERR      0X05    /**< \brief ���Դ��� */
#define AMHW_ZLG237_CAN_LEC_CRCER      0X06    /**< \brief CRC���� */
#define AMHW_ZLG237_CAN_LEC_SOFTER     0X07    /**< \brief ���������  */


/**< \brief ���Զ��� */
#define AMHW_ZLG237_CAN_MCR_DBF        ((uint32_t)(1ul << 16))

/**< \brief �����λ */
#define AMHW_ZLG237_CAN_MCR_RESET      ((uint32_t)(1ul << 15))

/**< \brief ʱ��ͨ�Ŵ���ģʽ */
#define AMHW_ZLG237_CAN_MCR_TTCM       ((uint32_t)(1ul << 7))

/**< \brief �Զ����߹��� */
#define AMHW_ZLG237_CAN_MCR_ABOM       ((uint32_t)(1ul << 6))

/**< \brief �Զ�����ģʽ */
#define AMHW_ZLG237_CAN_MCR_AWUM       ((uint32_t)(1ul << 5))

/**< \brief ��ֹ�����Զ��ش� */
#define AMHW_ZLG237_CAN_MCR_NART       ((uint32_t)(1ul << 4))

/**< \brief ����FIFO����ģʽ*/
#define AMHW_ZLG237_CAN_MCR_RFLM       ((uint32_t)(1ul << 3))

/**< \brief ����FIFO���ȼ� */
#define AMHW_ZLG237_CAN_MCR_TXFP       ((uint32_t)(1ul << 2))

/**< \brief ˯��ģʽ���� */
#define AMHW_ZLG237_CAN_MCR_SLEEP      ((uint32_t)(1ul << 1))

/**< \brief ��ʼ������ */
#define AMHW_ZLG237_CAN_MCR_INRQ       ((uint32_t)(1ul << 0))


/**< \brief ��ʼ��ȷ��*/
#define AMHW_ZLG237_CAN_MSR_INAK       ((uint32_t)(1ul << 0))

/**< \brief ˯��ģʽȷ��*/
#define AMHW_ZLG237_CAN_MSR_SLAK       ((uint32_t)(1ul << 1))

/**< \brief �����жϹҺ�*/
#define AMHW_ZLG237_CAN_MSR_ERRI       ((uint32_t)(1ul << 2))

/**< \brief �����жϹҺ�*/
#define AMHW_ZLG237_CAN_MSR_WKUI       ((uint32_t)(1ul << 3))

/**< \brief ˯��ģȷ���ж�*/
#define AMHW_ZLG237_CAN_MSR_SLAKI      ((uint32_t)(1ul << 4))

/**< \brief FIFO 0 ������Ŀ */
#define AMHW_ZLG237_CAN_RF0R_FMP0      ((uint32_t)(3ul << 0))
/**< \brief FIFO 0 ��*/
#define AMHW_ZLG237_CAN_RF0R_FULL0     ((uint32_t)(1ul << 3))
/**< \brief FIFO 0 ���*/
#define AMHW_ZLG237_CAN_RF0R_FOVR0     ((uint32_t)(1ul << 4))
/**< \brief �ͷŽ���FIFO 0�������*/
#define AMHW_ZLG237_CAN_RF0R_RFOM0     ((uint32_t)(1ul << 5))

/**< \brief FIFO 1 ������Ŀ */
#define AMHW_ZLG237_CAN_RF0R_FMP1      ((uint32_t)(3ul << 0))
/**< \brief FIFO 1 ��*/
#define AMHW_ZLG237_CAN_RF0R_FULL1     ((uint32_t)(1ul << 3))
/**< \brief FIFO 1 ���*/
#define AMHW_ZLG237_CAN_RF0R_FOVR1     ((uint32_t)(1ul << 4))
/**< \brief �ͷŽ���FIFO 1�������*/
#define AMHW_ZLG237_CAN_RF1R_RFOM1     ((uint32_t)(1ul << 5))

/**< \brief ������������ */
#define AMHW_ZLG237_CAN_TIR_TXRQ       ((uint32_t)(1ul << 0))

/**< \brief ���󾯸��־*/
#define AMHW_ZLG237_CAN_ESR_EWGF       ((uint32_t)(1ul << 0))

/**< \brief ���󱻶���־*/
#define AMHW_ZLG237_CAN_ESR_EPVF       ((uint32_t)(1ul << 1))

/**< \brief ���߱�־*/
#define AMHW_ZLG237_CAN_ESR_BOFF       ((uint32_t)(1ul << 2))

/**< \brief �ϴδ������ */
#define AMHW_ZLG237_CAN_ESR_LEC        ((uint32_t)(7ul << 4))

/**< \brief ���մ�������� */
#define AMHW_ZLG237_CAN_ESR_REC        ((uint32_t)(0XFFul << 24))

/**< \brief ���մ�������� */
#define AMHW_ZLG237_CAN_ESR_TEC        ((uint32_t)(0XFFul << 16))

/**< \brief ���� 0 �������*/
#define AMHW_ZLG237_CAN_TSR_RQCP0      ((uint32_t)(1ul << 0))

/**< \brief ���� 0 ���ͳɹ�*/
#define AMHW_ZLG237_CAN_TSR_TXOK0      ((uint32_t)(1ul << 1))

/**< \brief ���� 0 ��ֹ����*/
#define AMHW_ZLG237_CAN_TSR_ABRQ0      ((uint32_t)(1ul << 7))

/**< \brief ���� 1 �������*/
#define AMHW_ZLG237_CAN_TSR_RQCP1      ((uint32_t)(1ul << 8))

/**< \brief ���� 1 ���ͳɹ�*/
#define AMHW_ZLG237_CAN_TSR_TXOK1      ((uint32_t)(1ul << 9))

/**< \brief ���� 1 ��ֹ����*/
#define AMHW_ZLG237_CAN_TSR_ABRQ1      ((uint32_t)(1ul << 15))

/**< \brief ���� 2 �������*/
#define AMHW_ZLG237_CAN_TSR_RQCP2      ((uint32_t)(1ul << 16))

/**< \brief ���� 2 ���ͳɹ�*/
#define AMHW_ZLG237_CAN_TSR_TXOK2      ((uint32_t)(1ul << 17))

/**< \brief ���� 2 ��ֹ����*/
#define AMHW_ZLG237_CAN_TSR_ABRQ2      ((uint32_t)(1ul << 23))

/**< \brief �������� 0 Ϊ�� */
#define AMHW_ZLG237_CAN_TSR_TME0       ((uint32_t)(1ul << 26))

/**< \brief �������� 1 Ϊ�� */
#define AMHW_ZLG237_CAN_TSR_TME1       ((uint32_t)(1ul << 27))

/**< \brief �������� 2 Ϊ�� */
#define AMHW_ZLG237_CAN_TSR_TME2       ((uint32_t)(1ul << 28))

/**< \brief ����ʱ��� */
#define AMHW_ZLG237_CAN_TDTR_TGT       ((uint32_t)(1ul << 8))

typedef enum {
    ZLG237_CAN_TX_STATUS_FAILED = 0,    /**< \brief ����ʧ�� */
    ZLG237_CAN_TX_STATUS_OK,            /**< \brief ����ɹ� */
    ZLG237_CAN_TX_STATUS_PENGDING,      /**< \brief ������ */
    ZLG237_CAN_TX_STATUS_NOMAILBOX,     /**< \brief δ�ṩ�յ����� */
}amhw_zlg237_can_tx_status_t;

/**
 * \brief CAN ����ģʽ����
 *
 * \param[in] p_hw_can          : ָ��CAN�Ĵ������ָ��
 * \param[in] operating_mode    : ָ��amhw_zlg237_can_operating_type_t ����
 *
 * \return  CAN��ģʽ����״̬�Ƿ�ɹ�  0  1
 */
uint8_t amhw_zlg237_can_operating_mode_request (amhw_zlg237_can_t     *p_hw_can,
                                                amhw_zlg237_can_mode_t mode);

/**
 * \brief CAN �����Ӧ��־λ�Ƿ�����
 *
 * \param[in] p_hw_can        : ָ��CAN�Ĵ������ָ��
 * \param[in] can_it          : ָ������ amhw_zlg237_can_flag_t
 * \param[in] state           : ״̬   0  1
 * \return  ��
 */
uint8_t amhw_zlg237_can_get_flagstatus(amhw_zlg237_can_t        *p_hw_can,
                                       amhw_zlg237_can_flag_t    can_flag);

/**
 * \brief ��ȡָ���жϵ�״̬
 *
 * \param[in] p_hw_can ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
uint8_t amhw_zlg237_can_get_itstatus (amhw_zlg237_can_t *p_hw_can,
                                      uint32_t           can_it);

/**
 * \brief  ���ָ���жϵı�־λ
 *
 * \param[in] p_hw_can ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
void amhw_zlg237_can_clear_itstatus (amhw_zlg237_can_t *p_hw_can,
                                      uint32_t           can_it);

/**
 * \brief CAN ���Զ������
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] state      : ָ��uint8_t
 * \return ��
 */
am_static_inline
void amhw_zlg237_can_dbf_freeze (amhw_zlg237_can_t *p_hw_can,
                                 uint8_t            state)
{
    if (state != CAN_DISABLE) {

        /* ��Debugʱ�� ����CAN�Ľ���/����   ��Ȼ����������д�Ϳ��ƽ���  FIFO */
        p_hw_can->mcr |= (uint32_t)AMHW_ZLG237_CAN_MCR_DBF;
    } else {

        /* �ڵ���ʱ��CAN�������� */
        p_hw_can->mcr &= ~(uint32_t)AMHW_ZLG237_CAN_MCR_DBF;
    }
}

/**
 * \brief ����CANʱ�䴥��ͨ��ģʽ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] state      : ָ��uint8_t
 * \return ��
 */
am_static_inline
void amhw_zlg237_can_ttcom_mode_set (amhw_zlg237_can_t *p_hw_can,
                                     uint8_t            state)
{
    if (state != CAN_DISABLE) {

        /* ����ʱ�䴥��ͨ��ģʽ */
        p_hw_can->mcr |= AMHW_ZLG237_CAN_MCR_TTCM;

        /* ���÷���ʱ���  */
        p_hw_can->tx_mail[0].tdtr |= AMHW_ZLG237_CAN_TDTR_TGT;
        p_hw_can->tx_mail[1].tdtr |= AMHW_ZLG237_CAN_TDTR_TGT;
        p_hw_can->tx_mail[2].tdtr |= AMHW_ZLG237_CAN_TDTR_TGT;
    } else {

        /* ��ֹʱ�䴥��ͨ��ģʽ */
        p_hw_can->mcr &= ~(uint32_t)AMHW_ZLG237_CAN_MCR_TTCM;

        /* ������ʱ���  */
        p_hw_can->tx_mail[0].tdtr &= ~AMHW_ZLG237_CAN_TDTR_TGT;
        p_hw_can->tx_mail[1].tdtr &= ~AMHW_ZLG237_CAN_TDTR_TGT;
        p_hw_can->tx_mail[2].tdtr &= ~AMHW_ZLG237_CAN_TDTR_TGT;
    }
}

/**
 * \brief ��⴫����Ϣ
 *
 * \param[in] p_hw_can         : ָ��CAN�Ĵ������ָ��
 * \param[in] transmit_mailbox : �������������ID
 *
 * \return  ��ǰ������Ϣ�����״̬
 */
am_static_inline
uint8_t amhw_zlg237_can_transmit_status (amhw_zlg237_can_t    *p_hw_can,
                                         uint8_t               transmit_mailbox)
{
    uint32_t state = 0;

    /* ���Ϊ�������� */
    switch (transmit_mailbox) {

    case 0:
        state = p_hw_can->tsr & (AMHW_ZLG237_CAN_TSR_RQCP0 |
                                 AMHW_ZLG237_CAN_TSR_TXOK0 |
                                 AMHW_ZLG237_CAN_TSR_TME0);
        break;

    case 1:
        state = p_hw_can->tsr & (AMHW_ZLG237_CAN_TSR_RQCP1 |
                                 AMHW_ZLG237_CAN_TSR_TXOK1 |
                                 AMHW_ZLG237_CAN_TSR_TME1);
        break;

    case 2:
        state = p_hw_can->tsr & (AMHW_ZLG237_CAN_TSR_RQCP2 |
                                 AMHW_ZLG237_CAN_TSR_TXOK2 |
                                 AMHW_ZLG237_CAN_TSR_TME2);
        break;

    default:
        state = ZLG237_CAN_TX_STATUS_FAILED;
        break;
    }
    /* ������� ״̬*/
    switch (state) {

    case (0x00):
        state = ZLG237_CAN_TX_STATUS_PENGDING;
        break;

    case (AMHW_ZLG237_CAN_TSR_RQCP0 | AMHW_ZLG237_CAN_TSR_TME0):
        state = ZLG237_CAN_TX_STATUS_FAILED;
        break;

    case (AMHW_ZLG237_CAN_TSR_RQCP1 | AMHW_ZLG237_CAN_TSR_TME1):
        state = ZLG237_CAN_TX_STATUS_FAILED;
        break;

    case (AMHW_ZLG237_CAN_TSR_RQCP2 | AMHW_ZLG237_CAN_TSR_TME2):
        state = ZLG237_CAN_TX_STATUS_FAILED;
        break;

    case (AMHW_ZLG237_CAN_TSR_RQCP0 |
          AMHW_ZLG237_CAN_TSR_TME0  |
          AMHW_ZLG237_CAN_TSR_TXOK0):
        state = ZLG237_CAN_TX_STATUS_OK;
        break;

    case (AMHW_ZLG237_CAN_TSR_RQCP1 |
          AMHW_ZLG237_CAN_TSR_TME1  |
          AMHW_ZLG237_CAN_TSR_TXOK1):
        state = ZLG237_CAN_TX_STATUS_OK;
        break;

    case (AMHW_ZLG237_CAN_TSR_RQCP2 |
          AMHW_ZLG237_CAN_TSR_TME2  |
          AMHW_ZLG237_CAN_TSR_TXOK2):
        state = ZLG237_CAN_TX_STATUS_OK;
        break;

    default:
        state = ZLG237_CAN_TX_STATUS_FAILED;
        break;
    }

    return (uint8_t) state;
}

/**
 * \brief �ͷ�ָ��FIFO
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] rx_message : ָ�������Ϣ�ṹָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_zlg237_can_fifo_release (amhw_zlg237_can_t    *p_hw_can,
                                   uint8_t               fifonum)
{
    if (fifonum == 0) {
        p_hw_can->rf_0r |= AMHW_ZLG237_CAN_RF0R_RFOM0;
    } else {
        p_hw_can->rf_1r |= AMHW_ZLG237_CAN_RF1R_RFOM1;
    }
}

/**
 * \brief ����ָ��FIFO�д�ŵı�����Ŀ(���ڹҺ�״̬�ı���)
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] fifonum    : FIFO ���
 *
 * \return  fifo�еı�����Ŀ
 */
am_static_inline
uint8_t amhw_zlg237_can_message_pending (amhw_zlg237_can_t    *p_hw_can,
                                      uint8_t                  fifonum)
{
    uint8_t message_pending = 0;
    if (fifonum == 0) {
        message_pending = (uint8_t)(p_hw_can->rf_0r & (uint32_t)0x03);
    } else if (fifonum == 1 ){
        message_pending = (uint8_t)(p_hw_can->rf_1r & (uint32_t)0x03);
    } else {
        message_pending = 0;
    }

    return message_pending ;
}

/**
 * \brief ����͹���ģʽ
 *
 * \param[in] p_hw_can          : ָ��CAN�Ĵ������ָ��
 *
 * \return  ����˯��ģʽ״̬ 0 1
 */
am_static_inline
uint8_t amhw_zlg237_can_sleep (amhw_zlg237_can_t *p_hw_can)
{
    uint8_t sleepstatus = CAN_DISABLE;

    /* ����˯��ģʽ */
    p_hw_can->mcr = (((p_hw_can->mcr) & (uint32_t)
                                      (~(uint32_t)AMHW_ZLG237_CAN_MCR_INRQ)) |
                       AMHW_ZLG237_CAN_MCR_SLEEP);
    /* ˯��ģʽ״̬ */
    if ( (p_hw_can->msr & (AMHW_ZLG237_CAN_MSR_SLAK |
                           AMHW_ZLG237_CAN_MSR_INAK)) ==
           AMHW_ZLG237_CAN_MSR_SLAK) {
        sleepstatus = CAN_ENABLE;
    }

    return (uint8_t)sleepstatus;
}

/**
 * \brief ����CAN
 *
 * \param[in] p_hw_can          : ָ��CAN�Ĵ������ָ��
 *
 * \return  �Ƿ�ɹ�����  0  1
 */
am_static_inline
uint8_t amhw_zlg237_can_wakeup (amhw_zlg237_can_t *p_hw_can)
{
    uint32_t  wait_slak   = 0x0000ffff;
    uint8_t   wakeupstatus = CAN_DISABLE;

    /* �������� */
    p_hw_can->mcr &= ~(uint32_t)AMHW_ZLG237_CAN_MCR_SLEEP;

    /* ˯��ģʽ״̬  */
    while ( (p_hw_can->msr & AMHW_ZLG237_CAN_MSR_SLAK) ==
            AMHW_ZLG237_CAN_MSR_SLAK && (wait_slak != 0x00)) {
        wait_slak--;
    }

    if ((p_hw_can->msr & AMHW_ZLG237_CAN_MSR_SLAK) !=
            AMHW_ZLG237_CAN_MSR_SLAK) {
        /* �ɹ�����  ˯��ģʽ�˳� */
        wakeupstatus = CAN_ENABLE;
    }

    return (uint8_t)wakeupstatus;
}

/**
 * \brief ��ȡ�ϴ�CAN�����ϵĴ������
 *
 * \param[in] p_hw_can          : ָ��CAN�Ĵ������ָ��
 *
 * \return  ������ [2:0]
 */
am_static_inline
uint8_t amhw_zlg237_can_get_lasterrorcode (amhw_zlg237_can_t *p_hw_can)
{
    uint8_t errorcode = 0;

    /* ��ȡ�������ֵ */
    errorcode = (((uint8_t)p_hw_can->esr) & (uint8_t)AMHW_ZLG237_CAN_ESR_LEC);

    /* ���ش����� */
    return errorcode ;
}

/**
 * \brief ��ȡCAN ���ܴ����������ֵ REC
 *
 * \param[in] p_hw_can          : ָ��CAN�Ĵ������ָ��
 *
 * \return  �������ֵ
 */
am_static_inline
uint8_t amhw_zlg237_can_get_recverrorcount (amhw_zlg237_can_t *p_hw_can)
{
    uint8_t counter = 0;

    /* ��ȡ�������ֵ */
    counter = (uint8_t)((p_hw_can->esr &
              (uint32_t)AMHW_ZLG237_CAN_ESR_REC) >> 24);

    /* ���ش������ֵ */
    return counter ;
}

/**
 * \brief ��ȡCAN 9λ���ʹ���������ĵ�8λ TEC
 *
 * \param[in] p_hw_can          : ָ��CAN�Ĵ������ָ��
 *
 * \return  �������ֵ
 */
am_static_inline
uint8_t amhw_zlg237_can_get_transerrorcount (amhw_zlg237_can_t *p_hw_can)
{
    uint8_t counter = 0;

    /* ��ȡ�������ֵ */
    counter = (uint8_t)((p_hw_can->esr &
              (uint32_t)AMHW_ZLG237_CAN_ESR_TEC) >> 16);

    /* ���ش������ֵ */
    return counter ;
}

/**
 * \brief CAN �ж�ʹ������
 *
 * \param[in] p_hw_can        : ָ��CAN�Ĵ������ָ��
 * \param[in] can_it          : ָ�����õ��ж�Դ amhw_zlg237_can_int_t
 * \param[in] state           : ״̬   0  1
 * \return  ��
 */
am_static_inline
void amhw_zlg237_can_itconfig(amhw_zlg237_can_t        *p_hw_can,
                              amhw_zlg237_can_int_t     can_it,
                              uint8_t                   state)
{
    if (state != CAN_DISABLE) {
        p_hw_can->ier |= (uint32_t)(1ul << can_it);
    } else {
        p_hw_can->ier &= ~(uint32_t)(1ul << can_it);
    }
}

/**
 * \brief CAN ����Һ�״̬
 *
 * \param[in] p_hw_can        : ָ��CAN�Ĵ������ָ��
 * \param[in] can_it          : ָ������ amhw_zlg237_can_flag_t
 * \note   ������ AMHW_ZLG237_CAN_FLAG_FMP
 *
 *
 * \param[in] state           : ״̬   0  1
 * \return  ��
 */
am_static_inline
void amhw_zlg237_can_clearflag(amhw_zlg237_can_t        *p_hw_can,
                               amhw_zlg237_can_flag_t    can_flag)
{
    uint32_t flagtmp = 0;

    /* ESR register */
    if (can_flag == AMHW_ZLG237_CAN_FLAG_LEC) {
        p_hw_can->esr = (uint32_t)CAN_DISABLE;
    } else {    /* MSR or TSR or RF0R or RF1R */
        flagtmp = can_flag & 0x000fffff;

        if ((can_flag & AMHW_ZLG237_CAN_FLAG_RF0R) != (uint32_t)AM_FALSE) {

            /* ���� */
            p_hw_can->rf_0r |= (uint32_t)flagtmp;
        } else if ((can_flag & AMHW_ZLG237_CAN_FLAG_RF1R) != (uint32_t)AM_FALSE) {
            /* ���� */
            p_hw_can->rf_1r |= (uint32_t)flagtmp;
        } else if ((can_flag & AMHW_ZLG237_CAN_FLAG_TSR) != (uint32_t)AM_FALSE) {
            /* ���� */
            p_hw_can->tsr |= (uint32_t)flagtmp;
        } else { /* msr */
            p_hw_can->msr |= (uint32_t)flagtmp;
        }
    }
}

/**
 * \brief ������Ԥ��ֵ����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] brp        : ������Ԥ��ֵ�� 10bit���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_can_brp_set (amhw_zlg237_can_t *p_hw_can, uint16_t brp)
{
    p_hw_can->btr = (p_hw_can->btr & (~0x3ff)) | (brp & 0x3ff);
}

/**
 * \brief ��ȡ������Ԥ��ֵ
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ������Ԥ��ֵ��10bit
 */
am_static_inline
uint8_t amhw_zlg237_can_brp_get (amhw_zlg237_can_t *p_hw_can)
{
    return (uint16_t)(p_hw_can->btr & 0x3ff);
}

/**
 * \brief ͬ����ת�������
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] sjw        : ͬ����ת���ֵ��2bit���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_can_sjw_set (amhw_zlg237_can_t *p_hw_can, uint8_t sjw)
{
    p_hw_can->btr = (p_hw_can->btr & (~(0x3 << 24))) | ((sjw & 0x3) << 24);
}

/**
 * \brief ��ȡͬ����ת���
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ͬ����ת��ȣ�2bit
 */
am_static_inline
uint8_t amhw_zlg237_can_sjw_get (amhw_zlg237_can_t *p_hw_can)
{
    return (uint8_t)((p_hw_can->btr >> 24) & 0x3);
}

/**
 * \brief ʱ���1����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] tseg1        : ����ģʽֵ��4bit���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_can_tseg1_set (amhw_zlg237_can_t *p_hw_can, uint8_t tseg1)
{
    p_hw_can->btr = (p_hw_can->btr & (~(0xf << 16))) | ((tseg1 & 0xf) << 16);
}

/**
 * \brief ��ȡʱ���1
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 *
 * \return ʱ���1��4bit
 */
am_static_inline
uint8_t amhw_zlg237_can_tseg1_get (amhw_zlg237_can_t *p_hw_can)
{
    return (uint8_t)((p_hw_can->btr >> 16) & 0xf);
}

/**
 * \brief ʱ���2����
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] tseg2        : ����ģʽֵ��3bit���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_can_tseg2_set (amhw_zlg237_can_t *p_hw_can, uint8_t tseg2)
{
    p_hw_can->btr = (p_hw_can->btr & (~(0x7 << 20))) | ((tseg2 & 0x7) << 20);
}

/**
 * \brief ʱ���2����
 *
 * \param[in] p_hw_can ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg237_can_tseg2_get (amhw_zlg237_can_t *p_hw_can)
{
    return (uint8_t)((p_hw_can->btr >> 20) & 0x7);
}

/**
 * \brief ��ȡָ���жϵ�״̬
 *
 * \param[in] p_hw_can ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg237_can_check_itstatus (uint32_t  can_reg,
                                        uint32_t  can_it)
{
    uint8_t state = CAN_DISABLE;

    if (can_reg & can_it) {

        state = CAN_ENABLE;

    } else {
        state = CAN_DISABLE;
    }

    return state;
}


/**
 * @} amhw_zlg237_if_can
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG237_CAN_H */

/* end of file */

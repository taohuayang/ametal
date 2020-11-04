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
 * - 1.00 19-07-24  zc, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG237_I2C_H
#define __AMHW_ZLG237_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_zlg237_rcc.h"
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
 * \addtogroup amhw_zlg237_if_i2c
 * \copydoc amhw_zlg237_i2c.h
 * @{
 */

/**
 * \brief I2C�Ĵ�����ṹ��
 */
typedef struct amhw_zlg237_i2c {

    __IO uint16_t  i2c_cr1;                /**< \brief I2C���ƼĴ��� 1 */
         uint16_t  reserve0;               /**< \brief reserve ����λ */
    __IO uint16_t  i2c_cr2;                /**< \brief I2C���ƼĴ��� 2 */
         uint16_t  reserve1;
    __IO uint16_t  i2c_oar1;               /**< \brief I2C�����ַ�Ĵ��� 1 */
         uint16_t  reserve2;
    __IO uint16_t  i2c_oar2;               /**< \brief I2C�����ַ�Ĵ��� 2 */
         uint16_t  reserve3;
    __IO uint16_t  i2c_dr;                 /**< \brief I2C���ݼĴ���  */
         uint16_t  reserve4;
    __IO uint16_t  i2c_sr1;                /**< \brief I2C״̬�Ĵ��� 1 */
         uint16_t  reserve5;
    __IO uint16_t  i2c_sr2;                /**< \brief I2C״̬�Ĵ��� 2 */
         uint16_t  reserve6;
    __IO uint16_t  i2c_ccr;                /**< \brief I2Cʱ�ӿ��ƼĴ��� */
         uint16_t  reserve7;
    __IO uint16_t  i2c_trise;              /**< \brief I2C TRISE �Ĵ���  */
         uint16_t  reserve8;

} amhw_zlg237_i2c_t;

/** \brief IIC ģʽ  */
typedef enum {

    /** \brief IIC ģʽ */
    AMHW_ZLG237_I2C_MODE_I2C         = (uint16_t)0x0000,
    /** \brief SMBUS �豸 */
    AMHW_ZLG237_I2C_MODE_SMBUSDEVICE = (uint16_t)0x0002,
    /** \brief SMBUS ���� */
    AMHW_ZLG237_I2C_MODE_SMBUSHOST   = (uint16_t)0x000A,

}amhw_zlg237_i2c_mode_t;

/** \brief I2C_acknowledegment */
typedef enum {
    AMHW_ZLG237_I2C_ACK_ENABLE  = (uint16_t)0x0400,    /** \brief ACK ʹ�� */
    AMHW_ZLG237_I2C_ACK_DISABLE = (uint16_t)0x0000,    /** \brief ACK ���� */
}amhw_zlg237_i2c_ack_t;

/** \brief I2C_acknowledged_address */
typedef enum {

    /** \brief 7λ��ַģʽ*/
    AMHW_ZLG237_I2C_ACK_ADDRESS_7_BIT  = (uint16_t)0x4000,

    /** \brief 10 λ��ַģʽ*/
    AMHW_ZLG237_I2C_ACK_ADDRESS_10_BIT = (uint16_t)0xC000,
}amhw_zlg237_i2c_ack_address_t;

/** \brief I2C_fast_mode_duty */
typedef enum {

    /** \brief fast mode Tlow/Thigh = 16/9 */
    AMHW_ZLG237_I2C_DUTY_CYCLE_16_9 = (uint16_t)0x4000,

    /** \brief fast mode Tlow/Thigh = 2 */
    AMHW_ZLG237_I2C_DUTY_CYCLE_2    = (uint16_t)0xBFFF,
}amhw_zlg237_i2c_duty_t;

/** \brief I2Cģ��ʹ�� */
#define AMHW_ZLG237_I2C_CR1_PE                  (0)

/** \brief SMBUSģʽѡ�� */
#define AMHW_ZLG237_I2C_CR1_SMBUS               (1ul)
typedef enum {
    AMHW_ZLG237_I2C_MODE = 0,
    AMHW_ZLG237_SMBUS_MODE,
} amhw_zlg237_i2c_cr1_smbus_t;

/** \brief SMBus���� */
#define AMHW_ZLG237_I2C_CR1_SMBTYPE             (3ul)
typedef enum {
    AMHW_ZLG237_SMBUS_SLV = 0,         /** <brief SMBus �豸 */
    AMHW_ZLG237_SMBUS_MASTER,          /** <brief SMBus ���� */
} amhw_zlg237_i2c_cr1_smbtype_t;

/** \brief arpʹ��
 *  \note : ���SMBTYPE = 0 ,ʹ��SMBus�豸��Ĭ�ϵ�ַ
 *          ���SMBTYPE = 1 ,ʹ��SMBus�豸������ַ
 */
#define AMHW_ZLG237_I2C_CR1_ENARP               (4ul)

/** \brief pecʹ�� */
#define AMHW_ZLG237_I2C_CR1_ENPEC               (5ul)

/** \brief engc �㲥����ʹ�� */
#define AMHW_ZLG237_I2C_CR1_ENGC                (6ul)

/** \brief NOSTRETCH ��ֹʱ���ӳ�����ģʽ��
 *  \note: ��λ���ڵ�ADDR��BTF��־����λ���ڴ�ģʽ�½�ֹʱ���ӳ���ֱ�����������λ
 */
#define AMHW_ZLG237_I2C_CR1_NOSTRETCH           (7ul)

/** \brief start ��ʼ��������
 *  \note: ��������ã�����ʼ�����������PE = 0 ʱ����Ӳ�����
 */
#define AMHW_ZLG237_I2C_CR1_START               (8ul)

/** \brief stop ֹͣ��������
 *  \note: ��������ã��򵱼�⵽ֹͣ��������Ӳ�����������⵽��ʱ����ʱ��Ӳ����λ
 */
#define AMHW_ZLG237_I2C_CR1_STOP                (9ul)

/** \brief ack Ӧ��ʹ��
 *  \note: ��������ø�λ����PE = 0 ʱ����Ӳ�����
 */
#define AMHW_ZLG237_I2C_CR1_ACK                 (10ul)

/** \brief pos Ӧ��/PECλ�ã��������ݽ��ܣ�
 *  \note: ��������ø�λ����PE = 0 ʱ����Ӳ�����
 */
#define AMHW_ZLG237_I2C_CR1_POS                 (11ul)

/** \brief pec ���ݰ�������
 *  \note: ��������ø�λ��������PEC�󣬻���ʼ��ֹͣ����ʱ����PE=0 ʱӲ���������
 *         �ٲö�ʧʱ��PEC����ʧЧ
 */
#define AMHW_ZLG237_I2C_CR1_PEC                 (12ul)

/** \brief alert SMBus ����
 *  \note: ��������ø�λ���� PE = 0 ʱ����Ӳ�����
 */
#define AMHW_ZLG237_I2C_CR1_ALERT               (13ul)

/** \brief swrst �����λ
 *  \note: ������λʱ��I2C���ڸ�λ״̬.�ڸ�λ��λǰȷ��I2C���ű��ͷţ������ǿյ�
 *         ��λ��������BUSYλΪ��1��������������û�м�⵽ֹͣ����ʱ
 */
#define AMHW_ZLG237_I2C_CR1_SWRST               (15ul)

/** \brief freq[5:0] ģ��ʱ��Ƶ�� */
#define AMHW_ZLG237_I2C_CR2_FREQ                (0ul)

/** \brief iterren �����ж�ʹ�� */
#define AMHW_ZLG237_I2C_CR2_ITERREN             (8ul)

/** \brief itevten �¼��ж�ʹ�� */
#define AMHW_ZLG237_I2C_CR2_ITEVTEN             (9ul)

/** \brief itbufen �������ж�ʹ�� */
#define AMHW_ZLG237_I2C_CR2_ITBUFEN             (10ul)

typedef enum {
    I2C_CR2_ITERREN = 0x01,    /* \brief �����ж�*/
    I2C_CR2_ITEVTEN = 0x02,    /* \brief �¼��ж�*/
    I2C_CR2_ITBUFEN = 0x04,    /* \brief �������ж�*/
} amhw_zlg237_i2c_iten_t;

/** \brief dmaen DMA����ʹ�� */
#define AMHW_ZLG237_I2C_CR2_DMAEN               (11ul)

typedef enum {
    /** <brief ��ֹDMA���� */
    AMHW_ZLG237_I2C_DMAEN_DISABLE = 0,

    /** <brief ��TxE = 1��RxNE = 1ʱ������DMA���� */
    AMHW_ZLG237_I2C_DMAEN_ENABLE,
} amhw_zlg237_i2c_cr2_dmaen_t;

/** \brief last DMA���һ�δ���
 *  \note: ������ģʽʹ�ã�ʹ�������һ�ν�������ʱ���Բ���һ��NACK
 */
#define AMHW_ZLG237_I2C_CR2_LAST                (12ul)

/** \brief add0 �ӿڵ�ַ
 *  \note��  7  λ��ַģʽ���ù���
 *         10 λ��ַģʽΪ��ַ��0λ
 */
#define AMHW_ZLG237_I2C_OAR1_ADD0               (0ul)

/** \brief add[7:1] �ӿڵ�ַ ��ַ��7~1λ */
#define AMHW_ZLG237_I2C_OAR1_ADD7_1             (1ul)

/** \brief add[9:8]
 *  \note��  7  λ��ַģʽ���ù���
 *         10 λ��ַģʽΪ��ַ��9~8λ
 * */
#define AMHW_ZLG237_I2C_OAR1_ADD9_8             (8ul)

/** \brief reserve[13:10] ʼ�������λ����Ϊ 1 */
#define AMHW_ZLG237_I2C_OAR1_RESERVE            (10ul)


/** \brief addmode Ѱַģʽ����ģʽ��
 *  \note�� 0�� 7λ�ӵ�ַ  ����Ӧ10λ��ַ
 *         1��10λ�ӵ�ַ ����Ӧ7λ��ַ
 */
#define AMHW_ZLG237_I2C_OAR1_ADDMODE            (15ul)

/** \brief endual ˫��ַģʽʹ��λ */
#define AMHW_ZLG237_I2C_OAR2_ENDUAL             (0ul)

/** \brief add2[7:1] �ӿڵ�ַ ˫��ַģʽ�µ�ַ�� 7~1 λ */
#define AMHW_ZLG237_I2C_OAR2_ADD2               (1ul)

/** \brief sr PEC[7:0] ����ڲ�PEC��ֵ*/
#define AMHW_ZLG237_I2C_SR2_PEC7_1              (8ul)

/** \brief duty ����ģʽ�µ�ռ�ձ� */
#define AMHW_ZLG237_I2C_CCR_DUTY                (14ul)

/******************************************************************************
                             IIC MASTER Events
 *****************************************************************************/
/** \brief EV5  BUSY MSL SB*/
#define I2C_EVENT_MASTER_MODE_SELECT                 ((uint32_t)0x00030001)

/** \brief EV6 BUSY,MSL.ADDR,TXE,TRA */
#define IC2_EVENT_MASTER_TRANSMITTER_MODE_SELECTED   ((uint32_t)0x00070082)
/** \brief EV6 BUSTY,MSL,ADDR */
#define I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED      ((uint32_t)0x00030002)


/** \brief EV9 BUSY,MSL,ADD10 */
#define IC2_EVENT_MASTER_MODE_ADDRESS10              ((uint32_t)0x00030008)

/** \brief EV7 BUSY,MSL,RXNE */
#define I2C_EVENT_MASTER_BYTE_RECEIVED               ((uint32_t)0x00030040)

/** \brief EV8 TRA,BUSY,MSL,TXE */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTNG            ((uint32_t)0x00070080)

/** \brief TRA,BUSY,MSL,TXE,BTF */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTED            ((uint32_t)0x00070084)


/******************************************************************************
                             IIC SLAVE Events
 *****************************************************************************/

/** \brief EV1 BUSY,ADDR */
#define I2C_EVENT_SLAVE_RECEIER_ADDRES_MATCHED       ((uint32_t)0x00020002)
/** \brief EV1 TRA,BUSY,TXE,ADDR */
#define I2C_EVENT_SLAVE_TRAMSMITTER_ADDRESS_MATCHED  ((uint32_t)0x00060082)
/** \brief EV1 DUALF,BUSY */
#define I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED    ((uint32_t)0x00820000)

/** \brief EV1 DUALF,TRA,BUSY,TXE */
#define I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED ((uint32_t)0x00860080)

/** \brief EV1 GENCALL,BUSY */
#define I2C_EVENT_SLAVE_GENRALCALLADDRESS_MATCHED         ((uint32_t)0x00120000)

/** \brief EV2 BUSY��RXNE */
#define I2C_EVENT_SLAVE_BYTE_RECEIVED                     ((uint32_t)0x00020040)

/** \brief EV4 STOPF */
#define I2C_EVENT_SLAVE_STOP_DETECTED                     ((uint32_t)0x00000010)

/** \brief EV3 TRA,BUSY,TXE,BTF */
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTED                  ((uint32_t)0x00060084)


/** \brief EV3 TRA,BUSY,TXE */
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTING                 ((uint32_t)0x00060080)
/** \brief EV3_2 AF */
#define I2C_EVENT_SLAVE_ACK_FAILURE                       ((uint32_t)0x00000400)



/* \brief sr1 sr2 �Ĵ��� ״̬����*/
typedef enum {
    AMHW_ZLG_I2C_FLAG_DUALF      = ((uint32_t)0x00800000),
    AMHW_ZLG_I2C_FLAG_SMBHOST    = ((uint32_t)0x00400000),
    AMHW_ZLG_I2C_FLAG_SMBDEFAULT = ((uint32_t)0x00200000),
    AMHW_ZLG_I2C_FLAG_GENCALL    = ((uint32_t)0x00100000),
    AMHW_ZLG_I2C_FLAG_TRA        = ((uint32_t)0x00040000),
    AMHW_ZLG_I2C_FLAG_BUSY       = ((uint32_t)0x00020000),
    AMHW_ZLG_I2C_FLAG_MSL        = ((uint32_t)0x00010000),
    AMHW_ZLG_I2C_FLAG_SB         = ((uint32_t)0x10000001),
    AMHW_ZLG_I2C_FLAG_ADDR       = ((uint32_t)0x10000002),
    AMHW_ZLG_I2C_FLAG_BTF        = ((uint32_t)0x10000004),
    AMHW_ZLG_I2C_FLAG_ADD10      = ((uint32_t)0x10000008),
    AMHW_ZLG_I2C_FLAG_STOPF      = ((uint32_t)0x10000010),
    AMHW_ZLG_I2C_FLAG_RXNE       = ((uint32_t)0x10000040),
    AMHW_ZLG_I2C_FLAG_TXE        = ((uint32_t)0x10000080),
    AMHW_ZLG_I2C_FLAG_BERR       = ((uint32_t)0x10000100),
    AMHW_ZLG_I2C_FLAG_ARLO       = ((uint32_t)0x10000200),
    AMHW_ZLG_I2C_FLAG_AF         = ((uint32_t)0x10000400),
    AMHW_ZLG_I2C_FLAG_OVR        = ((uint32_t)0x10000800),
    AMHW_ZLG_I2C_FLAG_PECERR     = ((uint32_t)0x10001000),
    AMHW_ZLG_I2C_FLAG_TIMEOUT    = ((uint32_t)0x10004000),
    AMHW_ZLG_I2C_FLAG_SMBALERT   = ((uint32_t)0x10008000),

}amhw_zlg237_flag_t;



/**
 * \brief I2C�жϱ�־
 */
typedef enum {
    AMHW_ZLG_INT_FLAG__SB       = ((uint32_t)0x02000001), /* <brief ��ʼλ����ģʽ�� */
    AMHW_ZLG_INT_FLAG__ADDR     = ((uint32_t)0x02000002), /* <brief ��ַ����/ƥ�� */
    AMHW_ZLG_INT_FLAG__BTF      = ((uint32_t)0x02000004), /* <brief �ֽڷ��ͽ��� */
    AMHW_ZLG_INT_FLAG__ADD10    = ((uint32_t)0x02000008), /* <brief 10λͷ�����ѷ��� */
    AMHW_ZLG_INT_FLAG__STOPF    = ((uint32_t)0x02000010), /* <brief ֹͣ�������λ���ӣ� */
    AMHW_ZLG_INT_FLAG__RXNE     = ((uint32_t)0x06000040), /* <brief ���ݼĴ����ǿ� ���գ�*/
    AMHW_ZLG_INT_FLAG__TXE      = ((uint32_t)0x06000080), /* <brief ���ݼĴ����� ������ */
    AMHW_ZLG_INT_FLAG__BERR     = ((uint32_t)0x01000100), /* <brief ���ߴ��� */
    AMHW_ZLG_INT_FLAG__ARLO     = ((uint32_t)0x01000200), /* <brief �ٲö�ʧ������ */
    AMHW_ZLG_INT_FLAG__AF       = ((uint32_t)0x01000400), /* <brief Ӧ��ʧ�� */
    AMHW_ZLG_INT_FLAG__OVR      = ((uint32_t)0x01000800), /* <brief ����/Ƿ�� */
    AMHW_ZLG_INT_FLAG__PECERR   = ((uint32_t)0x01001000), /* <brief ����ʱ����PEC���� */
    AMHW_ZLG_INT_FLAG__TIMEOUT  = ((uint32_t)0x01004000), /* <brief ��ʱ/tlow���� */
    AMHW_ZLG_INT_FLAG__SMBALERT = ((uint32_t)0x01008000), /* <brief SMBUS���� */
}amhw_zlg237_int_flag_t;

typedef enum {
    DISABLE = 0,
    ENABLE,
}state_t;

/**
 *  \brief ʹ�� I2C����
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_enable (amhw_zlg237_i2c_t *p_hw_i2c)
{
    p_hw_i2c->i2c_cr1 |= (1u) << AMHW_ZLG237_I2C_CR1_PE;
}

/**
 *  \brief ����I2C����
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_disable (amhw_zlg237_i2c_t *p_hw_i2c)
{
    p_hw_i2c->i2c_cr1 &= ~((1u) << AMHW_ZLG237_I2C_CR1_PE);
}



/**
 *  \brief ʹ�ܻ���� I2C����
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state:  0 ����  1 ʹ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_dma_en (amhw_zlg237_i2c_t *p_hw_i2c,
                             state_t           state)
{
    if (state) {

        /** <brief ��TxE = 1 ��RxNE = 1ʱ������DMA����*/
        p_hw_i2c->i2c_cr2 |= 1 << AMHW_ZLG237_I2C_CR2_DMAEN;
    } else {

        /** <brief ��ֹDMA���� */
        p_hw_i2c->i2c_cr2 &= ~(1 << AMHW_ZLG237_I2C_CR2_DMAEN);
    }
}


/**
 *  \brief ���һ�δ���DMA
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state:  0 ����  1 ʹ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_dma_last_en (amhw_zlg237_i2c_t *p_hw_i2c,
                                   state_t           state)
{
    if (state) {

        /** <brief ��һ�ε�DMA��EOT�����Ĵ��� */
        p_hw_i2c->i2c_cr2 |= 1 << AMHW_ZLG237_I2C_CR2_LAST;
    } else {

        /** <brief ��һ��DMA��EOT�������Ĵ��� */
        p_hw_i2c->i2c_cr2 &= ~(1 << AMHW_ZLG237_I2C_CR2_LAST);
    }
}


/**
 *  \brief start ��ʼ��������
 *
 *  \note: ��������ã�����ʼ�����������PE = 0 ʱ����Ӳ�����
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state:  0 ����  1 ʹ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_genstrat (amhw_zlg237_i2c_t *p_hw_i2c,
                               state_t            state)
{
    if (state) {

        /** <brief �ڵ�ǰ�ֽڴ�����ڵ�ǰ��ʼ�������������ֹͣ��������ģʽ��
         *  �ڵ�ǰ�ֽڴ�����ͷ�SCL��SDA�ߣ���ģʽ��*/
        p_hw_i2c->i2c_cr1 |= (uint16_t)(1 << AMHW_ZLG237_I2C_CR1_START);
    } else {

        /** <brief ����ʼ�������������ӣ� */
        p_hw_i2c->i2c_cr1 &= ~(uint16_t)(1 << AMHW_ZLG237_I2C_CR1_START);
    }
}

/* \<brief ��ȡָ���Ĵ���ֵ */
am_static_inline
uint16_t amhw_zlg237_i2c_read_reg(uint16_t  reg)
{
    return (uint16_t)reg;
}

/**
 *  \brief stop ֹͣ��������
 *
 *  \note: ��������ã�����ʼ�����������PE = 0 ʱ����Ӳ�����
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state:  0 ����  1 ʹ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_genstop (amhw_zlg237_i2c_t    *p_hw_i2c,
                              state_t               state)
{
    if (state) {

        /** <brief �ظ�������ʼ��������ģʽ�� �����߿���ʱ��������ʼ��������ģʽ��*/
        p_hw_i2c->i2c_cr1 |= (uint16_t)(1 << AMHW_ZLG237_I2C_CR1_STOP);
    } else {

        /** <brief ����ʼ�������������ӣ� */
        p_hw_i2c->i2c_cr1 &= ~(uint16_t)(1 << AMHW_ZLG237_I2C_CR1_STOP);
    }
}

/**
 *  \brief Ack Ӧ��ʹ��
 *
 *  \note: ��������ã�����ʼ�����������PE = 0 ʱ����Ӳ�����
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state:  0 ����  1 ʹ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_ack_en (amhw_zlg237_i2c_t *p_hw_i2c,
                             state_t            state)
{
    if (state) {

        /** <brief ���յ�һ���ֽں󷵻�һ��Ӧ��ƥ��ĵ�ַ�����ݣ�  */
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_ACK;
    } else {

        /** <brief ��Ӧ�𷵻� */
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_ACK);
    }
}


/** \brief ���������ַ�Ĵ��� 2 oar2
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] address:   ָ��uint8_t ���͵ĵ�ַ
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_oar2_config (amhw_zlg237_i2c_t *p_hw_i2c,
                                  uint8_t            address)
{

    /** <brief ��ʼ�� add2[7:1] */
    p_hw_i2c->i2c_oar2 &= ~(0x7f << AMHW_ZLG237_I2C_OAR2_ADD2);

    /** <brief ���� 7λ��ַ */
    p_hw_i2c->i2c_oar2 |= (uint16_t)((uint16_t)address & (0x7f <<AMHW_ZLG237_I2C_OAR2_ADD2));
}


/** \brief  endual ˫��ַģʽʹ��λ
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state:   0 ����  1 ʹ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_endual (amhw_zlg237_i2c_t    *p_hw_i2c,
                             state_t               state)
{
    if (state) {

        /** <brief ��7λ��ַģʽ�£�oar1��oar2���ܱ�ʶ��*/
        p_hw_i2c->i2c_oar2 |= 1 << AMHW_ZLG237_I2C_OAR2_ENDUAL;
    } else {

        /** <brief ��7λ��ַģʽ�£�ֻ��oar1�ܱ�ʶ��*/
        p_hw_i2c->i2c_oar2 &= ~(1 << AMHW_ZLG237_I2C_OAR2_ENDUAL);
    }
}


/** \brief  engc �㲥����ʹ��λ
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state:   0 ����  1 ʹ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_engc (amhw_zlg237_i2c_t    *p_hw_i2c,
                           state_t               state)
{
    if (state) {

        /** <brief ENGCʹ�� ����㲥���� ��Ӧ����Ӧ��ַ 00h  */
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_ENGC;
    } else {

        /** <brief ENGC���� ��ֹ�㲥���� �Է�Ӧ����Ӧ��ַ 00h */
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_ENGC);
    }
}


/** \brief  �ж�ģʽʹ������
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] mode: ָ��amhw_zlg237_i2c_iten_tl ��enum��Ա
 *  \param[in] state:   0 ����  1 ʹ��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_iten_mode_set (amhw_zlg237_i2c_t      *p_hw_i2c,
                                    uint32_t                mode,
                                    state_t                 state)
{
    if (mode & I2C_CR2_ITERREN) {
        if (state) {
            p_hw_i2c->i2c_cr2 |= 1 << AMHW_ZLG237_I2C_CR2_ITERREN;
        } else {
            p_hw_i2c->i2c_cr2 &= ~(1 << AMHW_ZLG237_I2C_CR2_ITERREN);
        }
    }

    if (mode & I2C_CR2_ITEVTEN) {
        if (state) {
            p_hw_i2c->i2c_cr2 |= 1 << AMHW_ZLG237_I2C_CR2_ITEVTEN;
        } else {
            p_hw_i2c->i2c_cr2 &= ~(1 << AMHW_ZLG237_I2C_CR2_ITEVTEN);
        }
    }

    if (mode & I2C_CR2_ITBUFEN) {
        if (state) {
            p_hw_i2c->i2c_cr2 |= 1 << AMHW_ZLG237_I2C_CR2_ITBUFEN;
        } else {
            p_hw_i2c->i2c_cr2 &= ~(1 << AMHW_ZLG237_I2C_CR2_ITBUFEN);
        }
    }
}

/** \brief  ��������
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] data:   ����
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_send_data (amhw_zlg237_i2c_t *p_hw_i2c,
                                uint8_t            data)
{
    p_hw_i2c->i2c_dr = data;
}

/** \brief  ��������
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *
 *  \return uint8_t���͵�����
 */
am_static_inline
uint8_t amhw_zlg237_i2c_recv_data (amhw_zlg237_i2c_t *p_hw_i2c)
{
    return (uint8_t)p_hw_i2c->i2c_dr;
}

/** \brief  ���͵�ַ ��ѡ����豸
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] address: �����͵Ĵ��豸��ַ  uint8_t
 *  \param[in] slv_mode: �趨���豸�� ģʽ  ��  0 ����    1 ����
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_send7bit_address (amhw_zlg237_i2c_t   *p_hw_i2c,
                                       uint8_t              address,
                                       uint8_t              slv_mode)
{
    /** <brief read */
    p_hw_i2c->i2c_dr  = (address << 1) | (slv_mode & 0x01);
}

/** \brief  �����λ
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state: 0 �����ڸ�λ״̬    1 ���ڸ�λ״̬
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_swrst (amhw_zlg237_i2c_t      *p_hw_i2c,
                            state_t                 state)
{
    if (state) {

        /** <brief  I2Cģ�鴦�ڸ�λ״̬ */
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_SWRST;
    } else {

        /** <brief  I2Cģ�鲻���ڸ�λ״̬ */
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_SWRST);
    }
}

/** \brief  pos ack/pec λ�� ���������ݽ��գ�
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state: 0 ��ǰNACK    1 ��һ���ֽڵ�NACK
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_pos (amhw_zlg237_i2c_t      *p_hw_i2c,
                          state_t                 state)
{
    if (state) {

        /** <brief ack λ���Ƶ�ǰ��λ�Ĵ����ڽ��յ���һ���ֽڵ�(N)ACK. PECλ������ǰ��λ�Ĵ����ڽ��յ���һ���ֽ���PEC*/
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_POS;
    } else {

        /** <brief ack λ���Ƶ�ǰ��λ�Ĵ��������ڽ��յ��ֽڵ�(N)ACK. PECλ������ǰ��λ�Ĵ����ڵ��ֽ���PEC*/
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_POS);
    }
}

/** \brief  alert SMBus����
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state: 0 �ͷ�SMBAlert ����ʹ���ߡ�������Ӧ��ַͷ������NACK�źź���
 *                    1 ����SMBAlert ����ʹ���͡�������Ӧ��ַͷ������ACK�źź���
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_alert (amhw_zlg237_i2c_t      *p_hw_i2c,
                            state_t                 state)
{
    if (state) {
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_ALERT;
    } else {
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_ALERT);
    }
}

/** \brief  pec ���ݰ�������
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state: 0  ��PEC����
 *                    1  PEC���䣨�ڷ��ͻ����ģʽ��
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_pec (amhw_zlg237_i2c_t      *p_hw_i2c,
                          state_t                 state)
{
    if (state) {
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_PEC;
    } else {
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_PEC);
    }
}

/** \brief  enpec pecʹ��
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state: 0  ��ֹPEC����
 *                    1  ����PEC����
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_enpec (amhw_zlg237_i2c_t      *p_hw_i2c,
                            state_t                 state)
{
    if (state) {
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_ENPEC;
    } else {
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_ENPEC);
    }
}

/** \brief  pec[7:0]  ��ȡ�����PEC[7:0] �е�PEC��ֵ
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \return uint8_t���͵� PEC��ֵ
 */
am_static_inline
uint8_t amhw_zlg237_i2c_getpec (amhw_zlg237_i2c_t      *p_hw_i2c)
{
    return (p_hw_i2c->i2c_sr2 >> AMHW_ZLG237_I2C_SR2_PEC7_1);
}

/** \brief  enarp arpʹ��
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state: 0  ��ֹARPʹ��
 *                    1  ʹ��ARP
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_enarp (amhw_zlg237_i2c_t      *p_hw_i2c,
                            state_t                 state)
{
    if (state) {
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_ENARP;
    } else {
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_ENARP);
    }
}

/** \brief  nostretch ��ֹʱ���ӳ�����ģʽ��
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state: 0  ����ʱ���ӳ�
 *                    1  ��ֹʱ���ӳ�
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_nostretch (amhw_zlg237_i2c_t      *p_hw_i2c,
                                state_t                 state)
{
    if (state) {
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CR1_NOSTRETCH;
    } else {
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CR1_NOSTRETCH);
    }
}

/** \brief  duty ����ģʽʱ��ռ�ձ�
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] state: 0  ����ģʽ�£� Tlow/Thigh = 2
 *                    1  ����ģʽ�£� Tlow/Thigh = 16/9
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_fastmodeduty (amhw_zlg237_i2c_t      *p_hw_i2c,
                                   state_t                 state)
{
    if (state) {
        p_hw_i2c->i2c_cr1 |= 1 << AMHW_ZLG237_I2C_CCR_DUTY;
    } else {
        p_hw_i2c->i2c_cr1 &= ~(1 << AMHW_ZLG237_I2C_CCR_DUTY);
    }
}

/** \brief  �����һ���¼��Ƿ�����֪�¼�
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] event��     �¼��궨��
 *
 *  \return �Ƿ��� �Ѷ���ĺ��¼�    0 ����  1 ��
 */
am_static_inline
uint8_t amhw_zlg237_i2c_checkevent(amhw_zlg237_i2c_t      *p_hw_i2c,
                                   uint32_t                event)
{
    static uint32_t lastevent = 0;

    /** <brief ��I2C״̬�Ĵ����л�ȡ ��һ���¼��ĵ�ֵ */
    lastevent = (uint32_t)(((uint32_t)p_hw_i2c->i2c_sr2 << 16) | (uint32_t)p_hw_i2c->i2c_sr1) & 0x00FFFFFF;

    if ((lastevent & event) == event) {

        /** <brief ��һ���¼����ѷ����ĺ궨���¼� */
        return 1;
    } else {

        /** <brief ��һ���¼��붨��ĺ��¼���ͬ */
        return 0;
    }
}

/** \brief  ��ȡ��һ���¼�ֵ
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] event��     �¼��궨��
 *
 *  \return uint32_t���͵��¼���ֵ
 */
am_static_inline
uint32_t amhw_zlg237_i2c_getlastevent(amhw_zlg237_i2c_t      *p_hw_i2c)
{

    /** <brief ��I2C״̬�Ĵ����л�ȡ ��һ���¼��ĵ�ֵ */
    return (((uint32_t)p_hw_i2c->i2c_sr2 << 16) | (uint32_t)p_hw_i2c->i2c_sr1) & 0x00FFFFFF;
}

/** \brief  ���I2C״̬�Ĵ����� ����״̬λ�Ƿ�����
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] flag��     ����λ״̬�Ĵ�������   ָ��amhw_zlg237_flag_t
 *
 *  \return   ��λΪ  0   ��λΪ 1
 */
am_static_inline
int amhw_zlg237_i2c_checkflagstaus(amhw_zlg237_i2c_t      *p_hw_i2c,
                                   amhw_zlg237_flag_t      i2c_flag)
{
    __IO uint32_t i2c_sr_num = 0,i2c_sr_value = 0;

    /** <brief ��ȡ ״̬�Ĵ��� ���    0 1  */
    i2c_sr_num = i2c_flag >> 28;

    /** <brief ��� [23:0] �ļĴ���״̬ */
    i2c_flag &= 0x00FFFFFF;

    if (i2c_sr_num != 0) {

        /** \brief ��ȡsr1�ļĴ���ֵ         */
        i2c_sr_value = p_hw_i2c->i2c_sr1;
    } else {

        /** \brief ��ȡsr2�ļĴ���ֵ         */
        i2c_flag = (amhw_zlg237_flag_t)(i2c_flag >> 16);
        i2c_sr_value = p_hw_i2c->i2c_sr2;
    }

    if ((i2c_sr_value & i2c_flag) != (uint32_t)0) {

        /** \brief ��λ�ѱ��� 1 */
        return 1;
    } else {

        /** \brief ��λ�ѱ���0 */
        return 0;
    }
}

/** \brief  ����SR1�Ĵ���ָ��λ�ϵ�ֵ
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] flag�� amhw_zlg237_flag_t
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_clearflag (amhw_zlg237_i2c_t      *p_hw_i2c,
                                amhw_zlg237_flag_t      i2c_flag)
{
    p_hw_i2c->i2c_sr1 = (uint16_t)~(i2c_flag & 0x00FFFFFF);
}

/** \brief  ��ȡָ���жϵĵ�״̬
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] i2c_it��          ָ��amhw_zlg237_int_flag_t
 *
 *  \return  1 �ж�������    0 �ж�δ����
 */
am_static_inline
int amhw_zlg237_i2c_get_itflagstatus (amhw_zlg237_i2c_t      *p_hw_i2c,
                                      amhw_zlg237_int_flag_t  i2c_it)
{
    uint32_t enablestatus = 0;

    /** <brief ���ָ��IIC�ж�Դ�Ƿ�ʹ�� */
    enablestatus = (uint32_t)(((i2c_it & 0x07000000) >> 16) & p_hw_i2c->i2c_cr2);

    /** <brief ��� bit[23��0]��ֵ */
    i2c_it &= 0x00FFFFFF;

    if (((p_hw_i2c->i2c_sr1 & i2c_it) != (uint32_t)(0)) && enablestatus) {

        /** <brief �ж������� */
        return 1;
    } else {

        /** <brief �ж�δ���� */
        return 0;
    }
}

/** \brief  ��ȡ�жϵĵ�״̬
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] i2c_it��          ָ��amhw_zlg237_int_flag_t
 *
 *  \return  1 �ж�������    0 �ж�δ����
 */
am_static_inline
uint16_t amhw_zlg237_i2c_getitstatus (amhw_zlg237_i2c_t *p_hw_i2c)
{
    return (uint16_t)(p_hw_i2c->i2c_sr1 & 0xdfdf);
}

/** \brief  ����ָ�����ж�����
 *
 *  \param[in] p_hw_i2c : ָ��I2C�Ĵ����ṹ���ָ��
 *  \param[in] i2c_it��                 I2C_IT_BERR
 *                          I2C_IT_ARLO
 *                          I2C_IT_AF
 *                          I2C_IT_OVR
 *                          I2C_IT_PECERR
 *                          I2C_IT_TIMEOUT
 *                          I2C_IT_SMBALERT
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg237_i2c_clearit(amhw_zlg237_i2c_t      *p_hw_i2c,
                             amhw_zlg237_int_flag_t  i2c_it)
{
    p_hw_i2c->i2c_sr1 = (uint16_t)~(i2c_it & 0x00FFFFFF);
}

am_static_inline
void amhw_zlg237_i2c_clearallit(amhw_zlg237_i2c_t      *p_hw_i2c)
{

    /** SB  read sr1 write dr */

    /** ADDR read sr1 read sr2 */

    /** BRF read sr1 read or write dr */

    /** ADD10 read sr1 write cr1 */

    /** STOPF read sr1 write cr1 */

    /** RXNE read or write dr */

    /** TXE write dr */
    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr2);

    p_hw_i2c->i2c_cr1 &= 0xffff;
    p_hw_i2c->i2c_dr  &= 0xffff;

    p_hw_i2c->i2c_sr1 &= (uint16_t)~(0x00FFFFFF);
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
#endif /* __AMHW_ZLG237_I2C_H */

#endif

/* end of file */

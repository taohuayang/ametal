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
 * - 1.00 20-03-18  YRZ, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZSN700_I2C_H
#define __AMHW_ZSN700_I2C_H

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
 * \addtogroup amhw_zsn700_if_i2c
 * \copydoc amhw_zsn700_i2c.h
 * @{
 */

/**
 * \brief I2C�Ĵ�����ṹ��
 */
typedef struct amhw_zsn700_i2c {
    __IO uint32_t i2c_tmrun;    /* i2c�����ʼ�����ʹ�ܼĴ��� */
    __IO uint32_t i2c_tm;       /* i2c�����ʼ��������üĴ��� */
    __IO uint32_t i2c_cr;       /* i2c���üĴ��� */
    __IO uint32_t i2c_data;     /* i2c���ݼĴ��� */
    __IO uint32_t i2c_addr;     /* i2c��ַ�Ĵ��� */
    __I  uint32_t i2c_stat;     /* i2c״̬�Ĵ��� */
} amhw_zsn700_i2c_t;

/**
 * \brief i2c���ñ�־
 */

/** \brief ����ģʽ(1Mbps)ʹ��(i2c_tm < 9ʱ����ʹ��) */
#define AMHW_ZSN700_I2C_HIGH_SPEED          (1ul)

/** \brief Ӧ���־ʹ�� */
#define AMHW_ZSN700_I2C_REPLY_ENABLE        (1ul << 2)

/** \brief �жϱ�־λ */
#define AMHW_ZSN700_I2C_INT_FLAG            (1ul << 3)

/** \brief ֹͣ��־ʹ�� */
#define AMHW_ZSN700_I2C_STOP_ENABLE         (1ul << 4)

/** \brief ��ʼ��־ʹ�� */
#define AMHW_ZSN700_I2C_START_ENABLE        (1ul << 5)

/**
 * \brief I2C״̬��־
 */
typedef enum amhw_zsn700_status_flag{

    /* ��ָ��ģʽ״̬ */
    AMHW_ZSN700_STATUS_FLAG_0   = (0x00),   /**< \brief �������ߴ����I2C����δ�����״̬ */
    AMHW_ZSN700_STATUS_FLAG_1   = (0x08),   /**< \brief �ѷ�����ʼ���� */
    AMHW_ZSN700_STATUS_FLAG_2   = (0x10),   /**< \brief �ѷ����ظ���ʼ���� */

    /* ��������״̬ */
    AMHW_ZSN700_STATUS_FLAG_3   = (0x18),   /**< \brief �ѷ���SLA+W���ѽ���ACK */
    AMHW_ZSN700_STATUS_FLAG_4   = (0x20),   /**< \brief �ѷ���SLA+W���ѽ��շ�ACK */
    AMHW_ZSN700_STATUS_FLAG_5   = (0x28),   /**< \brief �ѷ������ݣ��ѽ���ACK */
    AMHW_ZSN700_STATUS_FLAG_6   = (0x30),   /**< \brief �ѷ������� */
    AMHW_ZSN700_STATUS_FLAG_7   = (0x38),   /**< \brief ��SLA+ ��д��д�����ֽ�ʱ��ʧ�ٲ� */

    /* ��������״̬ */
    AMHW_ZSN700_STATUS_FLAG_8   = (0x40),   /**< \brief �ѷ���SLA +R,�ѽ���ACK */
    AMHW_ZSN700_STATUS_FLAG_9   = (0x48),   /**< \brief �ѷ���SLA +R,�ѽ��շ�ACK */
    AMHW_ZSN700_STATUS_FLAG_10  = (0x50),   /**< \brief �ѽ��������ֽڣ�ACK�ѷ��� */
    AMHW_ZSN700_STATUS_FLAG_11  = (0x58),   /**< \brief �ѽ��������ֽڣ���ACK�ѷ��� */

    /* �ӽ�����״̬ */
    AMHW_ZSN700_STATUS_FLAG_12  = (0x60),   /**< \brief �ѽ��������SLA+W���ѽ���ACK */
    AMHW_ZSN700_STATUS_FLAG_13  = (0x68),   /**< \brief ����ʱ��SLA+��д��ʧ�ٲã��ѽ��������SLA+W���ѷ���ACK�� */
    AMHW_ZSN700_STATUS_FLAG_14  = (0x70),   /**< \brief �ѽ���ͨ�õ��õ�ַ��0x00�����ѷ���ACK */
    AMHW_ZSN700_STATUS_FLAG_15  = (0x78),   /**< \brief ����ʱ��SLA+��д�ж�ʧ�ٲã��ѽ���ͨ�õ��õ�ַ���ѷ���ACK�� */
    AMHW_ZSN700_STATUS_FLAG_16  = (0x80),   /**< \brief ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ���ACK�� */
    AMHW_ZSN700_STATUS_FLAG_17  = (0x88),   /**< \brief ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ��ط�ACK�� */
    AMHW_ZSN700_STATUS_FLAG_18  = (0x90),   /**< \brief ǰһ��Ѱַʹ��ͨ�õ��õ�ַ���ѽ������ݣ��ѷ���ACK�� */
    AMHW_ZSN700_STATUS_FLAG_19  = (0x98),   /**< \brief ǰһ��Ѱַʹ��ͨ�õ��õ�ַ���ѽ������ݣ��ѷ��ط�ACK�� */
    AMHW_ZSN700_STATUS_FLAG_20  = (0xa0),   /**< \brief ��ʹ�ôӽ���/�ӷ���ģʽ�о�̬Ѱַʱ�����յ�ֹͣ�������ظ���ʼ���� */

    /* �ӷ�����״̬ */
    AMHW_ZSN700_STATUS_FLAG_22  = (0xa8),   /**< \brief �ѽ��������SLA+R���ѷ���ACK */
    AMHW_ZSN700_STATUS_FLAG_23  = (0xb0),   /**< \brief ������ʱ��SLA+ ��д�ж�ʧ�ٲã��ѽ�������SLA+R���ѷ���ACK�� */
    AMHW_ZSN700_STATUS_FLAG_24  = (0xb8),   /**< \brief �ѷ������ݣ��ѽ���ACK�� */
    AMHW_ZSN700_STATUS_FLAG_25  = (0xc0),   /**< \brief �ѷ��������ֽڣ��ѽ��շ�ACK; */
    AMHW_ZSN700_STATUS_FLAG_26  = (0xc8),   /**< \brief װ��������ֽ��ѱ����ͣ��ѽ���ACK�� */

    /* ����״̬ */
    AMHW_ZSN700_STATUS_FLAG_27  = (0xf8)    /**< \brief �޿��õ����״̬��Ϣ��si=0�� */
}amhw_zsn700_status_flag_t;

/**
 * \brief ʹ�ܲ����ʼ�����
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_i2c_tm_enable (amhw_zsn700_i2c_t *p_hw_i2c)
{
    p_hw_i2c->i2c_tmrun |= 0x1ul;
}

/**
 * \brief ���ܲ����ʼ�����
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_i2c_tm_disable (amhw_zsn700_i2c_t *p_hw_i2c)
{
    p_hw_i2c->i2c_tmrun = 0x0ul;
}

/**
 * \brief ���ò����ʼĴ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  tm        : ����������ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_i2c_tm_set (amhw_zsn700_i2c_t  *p_hw_i2c,
                             uint8_t             tm)
{
    p_hw_i2c->i2c_tm = tm;
}

/**
 * \brief ���ÿ��ƼĴ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  flag      : i2c���ñ�־�� see:AMHW_ZSN700_I2C_HIGH_SPEED
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_i2c_cr_set (amhw_zsn700_i2c_t  *p_hw_i2c,
                             uint16_t            flag)
{
    p_hw_i2c->i2c_cr |= flag;
}

/**
 * \brief ������ƼĴ���ֵ
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  flag      : i2c���ñ�־��see:AMHW_ZSN700_I2C_HIGH_SPEED
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_i2c_cr_clear (amhw_zsn700_i2c_t    *p_hw_i2c,
                               uint16_t              flag)
{
    p_hw_i2c->i2c_cr &= ~((uint32_t)flag);
}

/**
 * \brief ��ȡ�жϱ�־
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zsn700_i2c_irq_get (amhw_zsn700_i2c_t    *p_hw_i2c)
{
    return ((p_hw_i2c->i2c_cr >> 3) & 0x1);
}

/**
 * \brief ʹ�� I2C ģ��
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_i2c_enable (amhw_zsn700_i2c_t *p_hw_i2c)
{
    p_hw_i2c->i2c_cr |= (0x1ul << 6);
}

/**
 * \brief ���� I2C ģ�飨���ͺͽ��ջ��屣�ֲ���״̬��
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zsn700_i2c_disable (amhw_zsn700_i2c_t *p_hw_i2c)
{
    p_hw_i2c->i2c_cr &= ~(0x1ul << 6);
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
void amhw_zsn700_i2c_dat_write (amhw_zsn700_i2c_t   *p_hw_i2c,
                                uint8_t              dat)
{
    p_hw_i2c->i2c_data = dat;
}

/**
 * \brief ������.
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ����
 */
am_static_inline
uint8_t amhw_zsn700_i2c_dat_read (amhw_zsn700_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->i2c_data);
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
void amhw_zsn700_i2c_slave_addr_set (amhw_zsn700_i2c_t  *p_hw_i2c,
                                     uint16_t            addr)
{
    p_hw_i2c->i2c_addr = (p_hw_i2c->i2c_addr & ~0xfe) | ((addr << 1) & 0xfe);
}

/**
 * \brief I2C���ܹ㲥���� ��Ӧ ACK
 *
 */
am_static_inline
void amhw_zsn700_i2c_gen_call_ack (amhw_zsn700_i2c_t *p_hw_i2c)
{
    p_hw_i2c->i2c_addr |= 0x1ul;
}

/**
 * \brief I2C���ܹ㲥���� ����Ӧ
 *
 */
am_static_inline
void amhw_zsn700_i2c_gen_call_nack (amhw_zsn700_i2c_t *p_hw_i2c)
{
    p_hw_i2c->i2c_addr &= ~0x1ul;
}

/**
 * \brief ��ȡI2C״̬
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ״̬�����ϵ��
 */
am_static_inline
amhw_zsn700_status_flag_t amhw_zsn700_i2c_status_get (amhw_zsn700_i2c_t *p_hw_i2c)
{
    return (amhw_zsn700_status_flag_t)(p_hw_i2c->i2c_stat);
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
#endif /* __AMHW_ZSN700_I2C_H */

#endif

/* end of file */

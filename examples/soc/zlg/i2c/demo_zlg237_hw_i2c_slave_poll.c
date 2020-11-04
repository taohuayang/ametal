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
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOB_6 �������� I2C ������ SCL ���ţ�
 *   2. PIOB_7 �������� I2C ������ SDA ���š�
 *
 * \note
 *    ��ǰ I2C �� SCL ����ʹ�õ��� PIOB_6��SDA ����ʹ�õ��� PIOB_7��
 *    �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_zlg116_hw_i2c_slave_poll.c src_zlg116_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-26  zc, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg116_hw_i2c_slave_poll
 * \copydoc demo_zlg116_hw_i2c_slave_poll.c
 */

/** [src_zlg116_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg237_clk.h"
#include "am_zlg237.h"
#include "hw/amhw_zlg237_i2c.h"
#include "am_delay.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** ���������ӻ���ַ���� */
#define OPERATE_ADDR      (0XB2 >> 1)

#define EEPROM_BUFFER_LEN (0x20)

#define __I2C_SLV_ST_IDLE         0      /*< \brief ����״̬ */
#define __I2C_SLV_ST_ADDR_MATCH   1      /*< \brief ��ַƥ��״̬ */
#define __I2C_SLV_ST_SUBADDR_GET  2      /*< \brief ��ȡ�ӵ�ַ״̬ */
#define __I2C_SLV_ST_TXBYTE_GET   3      /*< \brief ��ȡ���͵�����״̬ */
#define __I2C_SLV_ST_RXBYTE_PUT   4      /*< \brief �������� ״̬*/
#define __I2C_SLV_ST_STOP         5      /*< \brief ֹͣ״̬ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static am_bool_t is_sub_addr = AM_FALSE;      /**< I2C �ӻ���ַ��־ */
static uint8_t   sub_addr;                    /**< I2C �ӻ���ַ */
static uint8_t   eeprom[EEPROM_BUFFER_LEN];   /**< ������ */

/**
 * \brief I2C �ӻ���ʼ�����ú���
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] dev_addr ���������ӻ��ĵ�ַ����
 *
 * \retval AM_OK ��ʼ���������
 */
static int __i2c_slave_init (amhw_zlg237_i2c_t *p_hw_i2c, uint8_t dev_addr)
{
     uint32_t pclk1 = 0;
     uint16_t tmpreg = 0, i2c_freq_value = 0;
     uint16_t result = 0x04;
     uint32_t speed = 100000;
     uint16_t i2c_dutycycle = AMHW_ZLG237_I2C_DUTY_CYCLE_2;
     uint16_t i2c_mode      = AMHW_ZLG237_I2C_MODE_I2C;
     uint16_t i2c_ack       = AMHW_ZLG237_I2C_ACK_ENABLE;

     uint16_t i2c_acknowledgedaddress = AMHW_ZLG237_I2C_ACK_ADDRESS_7_BIT;
     uint16_t i2c_ownaddress1 = dev_addr;

     if (p_hw_i2c == NULL) {
         return -AM_EINVAL;
     }

     /** <breif ���� CR2 */
     tmpreg = p_hw_i2c->i2c_cr2;

     /** <brief ���� freq[5:0] */
     tmpreg &= 0xFFC0;

     /** <brief ���� pclk1  ����freqʱ�� */
     pclk1 = am_clk_rate_get(CLK_APB1);

     i2c_freq_value = (uint16_t)(pclk1/1000000);
     tmpreg |= i2c_freq_value;

     /** <brief д��CR2 */
     p_hw_i2c->i2c_cr2 = tmpreg;

     /** <brief ���� CCR */

     /**
      *  \brief ���� I2C  ���� TRISE ���� F/S DUTY CCR[11:0]
      */
     amhw_zlg237_i2c_disable(p_hw_i2c);
     tmpreg = 0;

     /** <brief ���Ϊ 100khz */
     if (speed <= 100000) {
         /** <brief ��׼ģʽ�ٶȼ��� */
         result = (uint16_t)(pclk1 / (speed << 1));

         if (result < 0x04) {

             /** <brief ������С����ֵ */
             result = 0x04;
         }
         tmpreg |= result;
         /** \brief ���ñ�׼ģʽ������ riseֵ     */
         p_hw_i2c->i2c_trise = i2c_freq_value + 1;
     } else {

         /** <brief ���Ϊ 400khz */
         if (i2c_dutycycle == AMHW_ZLG237_I2C_DUTY_CYCLE_2 ) {
             result = (uint16_t)(pclk1 / (speed *3));
         } else {
             result = (uint16_t)(pclk1 / (speed * 25));
             result |= AMHW_ZLG237_I2C_DUTY_CYCLE_16_9;
         }

         /** < ���� CCR[11:0] �Ƿ�С�� 0x01 */
         if ((result & 0x0FFF) == 0) {

             /** <brief ������С�� CCRֵ */
             result |= (uint16_t)0x0001;
         }

         /** <brief ����speedֵ  ��  F/SΪ ����ģʽ */
         tmpreg |= (uint16_t)(result | (uint16_t)0x8000);
         /** <brief ���ÿ���ģʽ�����riseʱ�� */
         p_hw_i2c->i2c_trise = (uint16_t) (((i2c_freq_value *(uint16_t)300) /
                                           (uint16_t)1000) + (uint16_t)1) ;
     }

     /** <brief д�� ccr */
     p_hw_i2c->i2c_ccr = tmpreg;

     /** <brief ����I2C���� */
     amhw_zlg237_i2c_enable(p_hw_i2c);

     /** <brief ���� CR1 */

     tmpreg = p_hw_i2c->i2c_cr1;

     /** \brief ���� ACK,SMBTYPE,SMBUS */
     tmpreg &= 0xFBF5;

     /**
      *  <brief ���� I2C ģʽ �� acknowledgement
      *  ����I2C��ģʽֵ ���� SMBTYPE �� SMBUS
      *  ����I2C��ACKֵ ����ACKλ
      */
     tmpreg |= (uint16_t)((uint16_t)i2c_mode | i2c_ack);

     /** \breif д��CR1 */
     p_hw_i2c->i2c_cr1 = tmpreg;

     /** \breif I2C OAR1 ���� */
     p_hw_i2c->i2c_oar1 = (i2c_acknowledgedaddress |
                           (i2c_ownaddress1 <<1 ) );

     /* Ĭ�ϲ�ʹ�� 10bit��ַ*/
     amhw_zlg237_i2c_endual(p_hw_i2c,DISABLE);
     amhw_zlg237_i2c_iten_mode_set(p_hw_i2c,
                                   I2C_CR2_ITERREN |
                                   I2C_CR2_ITEVTEN |
                                   I2C_CR2_ITBUFEN,
                                   DISABLE);

     /** ���� I2C����  */
     amhw_zlg237_i2c_enable(p_hw_i2c);

     return AM_OK;
}

/**
 * \brief I2C ״̬������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 *
 * \return ��
 */

static void __i2c_slave_event (amhw_zlg237_i2c_t *p_hw_i2c)
{
    static uint8_t status = __I2C_SLV_ST_IDLE;

    switch (status) {

    /* ����״̬ */
    case __I2C_SLV_ST_IDLE:
        sub_addr = 0;

        /* no break*/

     /* ��ַƥ��״̬ */
    case __I2C_SLV_ST_ADDR_MATCH:
        while(1) {
            if (p_hw_i2c->i2c_sr1 & 0x0002) {
                amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
                amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr2);
                break;
            }
        }

        status = __I2C_SLV_ST_SUBADDR_GET;
        /* no break*/

    /* ��ȡ�ӵ�ַ״̬  */
    case __I2C_SLV_ST_SUBADDR_GET:
        if (is_sub_addr == AM_FALSE) {
            am_udelay(100);
            sub_addr =  amhw_zlg237_i2c_recv_data (p_hw_i2c);
            is_sub_addr = AM_TRUE;
            status = __I2C_SLV_ST_ADDR_MATCH;
        } else {
            if (amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
                    AMHW_ZLG_I2C_FLAG_TRA)) {
                status = __I2C_SLV_ST_TXBYTE_GET;
                is_sub_addr = AM_FALSE;
            } else {
                status = __I2C_SLV_ST_RXBYTE_PUT;
                is_sub_addr = AM_FALSE;
            }
        }

        break;

    /* ��ȡ���͵�����״̬  */
    case __I2C_SLV_ST_TXBYTE_GET:
        if (amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
                AMHW_ZLG_I2C_FLAG_TXE)) {

            amhw_zlg237_i2c_send_data (p_hw_i2c, eeprom[sub_addr++]);
            sub_addr %= EEPROM_BUFFER_LEN;
        }
        if (amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
                   AMHW_ZLG_I2C_FLAG_AF)) {

            amhw_zlg237_i2c_clearflag(p_hw_i2c, AMHW_ZLG_I2C_FLAG_AF);
            status = __I2C_SLV_ST_IDLE;
                }

        break;

    /* �������� ״̬  */
    case __I2C_SLV_ST_RXBYTE_PUT:
        if (amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
                AMHW_ZLG_I2C_FLAG_RXNE)) {

            eeprom[sub_addr++] = amhw_zlg237_i2c_recv_data (p_hw_i2c);
            sub_addr %= EEPROM_BUFFER_LEN;
        }

        if (amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
                AMHW_ZLG_I2C_FLAG_STOPF)) {

            amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
            p_hw_i2c->i2c_cr1 &=0xffff;
            status = __I2C_SLV_ST_IDLE;
        }

        break;

    default:
        break;
    }
}

/**
 * \brief �������
 */
void demo_zlg237_hw_i2c_slave_poll_entry (amhw_zlg237_i2c_t *p_hw_i2c)
{

    __i2c_slave_init(p_hw_i2c, OPERATE_ADDR); /* I2C �ӻ���ʼ������ */

    while(1) {
        __i2c_slave_event(p_hw_i2c);
    }
}
/** [src_zlg116_hw_i2c_slave_poll] */

/* end of file */

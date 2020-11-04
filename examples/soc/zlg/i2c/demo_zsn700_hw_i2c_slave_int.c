/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
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
 *   1. PIOA_11 �������� I2C ������ SCL ���ţ�
 *   2. PIOA_12 �������� I2C ������ SDA ���š�
 *
 * \note
 *    ��ǰ I2C �� SCL ����ʹ�õ��� PIOA_11��SDA ����ʹ�õ��� PIOA_12��
 *    �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_i2c_slave_poll.c src_zsn700_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-16  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_i2c_slave_poll
 * \copydoc demo_zsn700_hw_i2c_slave_poll.c
 */

/** [src_zsn700_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_zsn700_i2c.h"
#include "am_int.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** ���������ӻ���ַ���� */
#define OPERATE_ADDR      0x50

#define EEPROM_BUFFER_LEN (0x20)

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static uint8_t   sub_addr;
static uint8_t   eeprom[EEPROM_BUFFER_LEN] = {0};   /**< ������ */

/**
 * \brief ��ȡ����һ���ֽڻص�
 */
static int __txbyte_get (void *p_arg, uint8_t *p_byte)
{
    *p_byte = eeprom[sub_addr];
    sub_addr++;
    return AM_OK;
}

/**
 * \brief ����һ���ֽڻص�
 */
static int __rxbyte_put(void *p_arg, uint8_t byte)
{
    eeprom[sub_addr] = byte;
    sub_addr++;
    return AM_OK;
}

/**
 * \brief ֹͣ����ص�
 */
static void  __tran_stop(void *p_arg)
{
    sub_addr = 0;
}

/**
 * \brief I2C �ӻ���ʼ�����ú���
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] dev_addr ���������ӻ��ĵ�ַ����
 *
 * \retval AM_OK ��ʼ���������
 */
static int __i2c_slave_init (amhw_zsn700_i2c_t *p_hw_i2c, uint8_t dev_addr)
{
    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    /* ���I2C���ƼĴ��� */
    p_hw_i2c->i2c_cr = 0;

    /* �ӻ�ģʽ������Ӧ�� */
    amhw_zsn700_i2c_cr_set(p_hw_i2c, AMHW_ZSN700_I2C_REPLY_ENABLE);

    /* ���ò����ʼ����� */
    amhw_zsn700_i2c_tm_disable(p_hw_i2c);

    /* ���ôӻ���ַ */
    amhw_zsn700_i2c_slave_addr_set (p_hw_i2c, dev_addr);

    amhw_zsn700_i2c_enable(p_hw_i2c);

    return AM_OK;
}

/**
 * \brief I2C ״̬������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 *
 * \return ��
 */
static void __i2c_slave_event (void *p_i2c_slv)
{
    static uint8_t           rx_len       = 0;
    amhw_zsn700_i2c_t       *p_hw_i2c_slv = p_i2c_slv;
    uint8_t                  state;
    uint8_t                  rx_data;
    uint8_t                  tx_data;

    state = amhw_zsn700_i2c_status_get(p_hw_i2c_slv);

    switch(state) {

    case 0xa0:  /* ���յ�ֹͣ�������ظ���ʼ���� */
        __tran_stop(NULL);
        rx_len = 0;
        amhw_zsn700_i2c_cr_set(p_hw_i2c_slv, AMHW_ZSN700_I2C_REPLY_ENABLE);
        break;

    case 0x60:  /* �ѽ��յ�(������ƥ���)SLA+W���ѽ���ACK */
    case 0x70:  /* �ѽ���ͨ�õ��õ�ַ��0x00�����ѽ���ACK */
        rx_len = 0;
        amhw_zsn700_i2c_cr_set(p_hw_i2c_slv, AMHW_ZSN700_I2C_REPLY_ENABLE);
        break;

    case 0x68:  /* ����ʱ��SLA+��д��ʧ�ٲã��ѽ��������SLA+W���ѷ���ACK */
    case 0x78:  /* ����ʱ��SLA+��д�ж�ʧ�ٲã��ѽ���ͨ�õ��õ�ַ���ѷ���ACK */
    case 0x88:  /* ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ��ط�ACK */
        amhw_zsn700_i2c_cr_set(p_hw_i2c_slv, AMHW_ZSN700_I2C_REPLY_ENABLE);
        break;

    case 0x80:  /* ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ���ACK */
    case 0x98:  /* ǰһ��Ѱַʹ��ͨ�õ��õ�ַ���ѽ������ݣ��ѷ��ط�ACK */
    case 0x90:  /* ǰһ��Ѱַʹ��ͨ�õ��õ�ַ���ѽ������ݣ��ѷ���ACK */
        amhw_zsn700_i2c_cr_set(p_hw_i2c_slv, AMHW_ZSN700_I2C_REPLY_ENABLE);
        rx_data = amhw_zsn700_i2c_dat_read(p_hw_i2c_slv);/* �������� */
        if(rx_len) {    /* ���Խ��յĵ�һ������(�ӻ��豸�ӵ�ַ) */
            __rxbyte_put(NULL, rx_data);    /* ���ܻص� */
        }
        rx_len++;
        break;

    case 0xa8:  /* �ѽ��������SLA+R���ѷ���ACK,��Ҫ�������ݲ����յ�ACKλ */
    case 0xb0:  /* ������ʱ��SLA+��д�ж�ʧ�ٲã��ѽ�������SLA+R���ѷ���ACK */
    case 0xc8:  /* װ��������ֽ��ѱ����ͣ��ѽ���ACK */
    case 0xb8:  /* �ѷ������ݣ��ѽ���ACK */
        __txbyte_get(NULL, &tx_data);
        amhw_zsn700_i2c_dat_write(p_hw_i2c_slv,tx_data);
        break;

    case 0xc0:  /* �������ݣ����շ�ACKn */
        __tran_stop(NULL);
        break;

    default:
        break;
    }

    /* ����жϱ�־ */
    amhw_zsn700_i2c_cr_clear(p_hw_i2c_slv, AMHW_ZSN700_I2C_INT_FLAG);
}

/**
 * \brief �������
 */
void demo_zsn700_hw_i2c_slave_int_entry (void  *p_hw_i2c,
                                         int    inum_num)
{
    __i2c_slave_init(p_hw_i2c, OPERATE_ADDR); /* I2C �ӻ���ʼ������ */

    /* �����ж� */
    am_int_connect(inum_num, __i2c_slave_event, (void *)p_hw_i2c);
    am_int_enable(inum_num);

    while(1) {
        ;
    }
}
/** [src_zsn700_hw_i2c_slave_poll] */

/* end of file */

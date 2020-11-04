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
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ���� EEPROM �� I2C ���ŵ���Ӧ���š�
 *
 * - ʵ������
 *   1. д���ݵ� EEPROM��
 *   2. �����ղ�д������ݣ�
 *   3. ���Դ��ڴ�ӡ���Խ����
 *
 * \par Դ����
 * \snippet demo_zlg116_hw_i2c_master_poll.c src_zlg116_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 19-07-26  zc, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg116_hw_i2c_master_poll
 * \copydoc demo_zlg116_hw_i2c_master_poll.c
 */

/** [src_zlg116_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg237_i2c.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define I2C_M_7BIT    0x0000u          /**< \brief 7-bits �豸��ַ */
#define I2C_M_10BIT   0x0001u          /**< \brief 10-bit �豸��ַ */
#define I2C_M_WR      0x0000u          /**< \brief д���� */
#define I2C_M_RD      0x0002u          /**< \brief ������ */
#define I2C_M_NOSTART 0x0010u          /**< \brief ��������������ʶ */

#define I2C_SPEED     100000            /**< \brief I2C �������ٶȲ������� */
#define EEPROM_ADDR   (0xb2 >> 1)       /**< \brief EEPROM �豸��ַ���� */
#define TEST_LEN      0Xb                 /**< \brief ���� EEPROM ��ҳ��С */

/**
 * \brief I2C ����ṹ�嶨�壬��Ҫ���� I2C ��ѯģʽ��
 */
typedef struct i2c_transfer {

    /** \brief I2C�豸��ַ */
    volatile uint16_t   addr;

    /** \brief I2C �豸�����Լ�transfer��Ҫ�������ʶ */
    volatile uint16_t   flags;

    /** \brief I2C �������ݻ���ָ�� */
    volatile void      *p_buf;

    /** \brief I2C ���ݻ��泤�� */
    volatile uint16_t   length;
} i2c_transfer_t;

/** \brief I2C ����ṹ�� */
static i2c_transfer_t __g_i2c1_transfer;

/**
 * \brief I2C ����ṹ��������ú���
 *
 * \param[in] p_trans ָ�� I2C ����ṹ���ָ��
 * \param[in] addr    �豸��ַ����
 * \param[in] flags   ������Ʊ�ʶλ����
 * \param[in] p_buf   ָ���ͻ��߽������ݻ����ָ��
 * \param[in] length  ������ֽڳ��Ȳ���
 *
 * \retval AM_OK ����ṹ���������
 */
static int __i2c_mktrans (i2c_transfer_t *p_trans,
                          uint16_t        addr,
                          uint16_t        flags,
                          void           *p_buf,
                          uint16_t        length)
{
    if(p_trans == NULL) {
        return -AM_EINVAL;
    }

    p_trans->addr   = addr;
    p_trans->flags  = flags;
    p_trans->p_buf  = p_buf;
    p_trans->length = length;

    return AM_OK;
}



/**
 * \brief I2C �������͵�ַ/����
 *
 * \param[in] p_hw_i2c ָ��I2C�Ĵ������ָ��
 * \param[in] p_trans  ָ��I2C����ṹ���ָ��
 * \param[in] stop     �Ƿ���ֹͣ�ź�
 *                         AM_TRUE  : ��
 *                         AM_FALSE : ��
 *
 * \retval AM_OK �������
 */
static int __i2c_mst_send (amhw_zlg237_i2c_t *p_hw_i2c,
                           i2c_transfer_t    *p_trans,
                           am_bool_t          stop)

{
    uint8_t i;

    for (i = 0; i < p_trans->length; i++) {

        while (!amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
                AMHW_ZLG_I2C_FLAG_TXE));

        if (i == (p_trans->length - 1) && stop ) {
            amhw_zlg237_i2c_send_data(p_hw_i2c,
                    ((uint8_t *)(p_trans->p_buf))[i]);

        } else {
            amhw_zlg237_i2c_send_data(p_hw_i2c,
                    ((uint8_t *)(p_trans->p_buf))[i]);
        }

    }

    if (stop ) {

        while (!amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
            AMHW_ZLG_I2C_FLAG_BTF));

            /* ����ֹͣλ  */
           amhw_zlg237_i2c_genstop(p_hw_i2c, ENABLE);
    }

    return AM_OK;
}

/**
 * \brief I2C �������յ�ַ/����
 *
 * \param[in] p_hw_i2c ָ��I2C�Ĵ������ָ��
 * \param[in] p_trans  ָ��I2C����ṹ���ָ��
 * \param[in] stop     �Ƿ���ֹͣ�ź�
 *                         AM_TRUE  : ��
 *                         AM_FALSE : ��
 *
 * \retval AM_OK �������
 */
static int __i2c_mst_recv (amhw_zlg237_i2c_t *p_hw_i2c,
                           i2c_transfer_t    *p_trans,
                           am_bool_t          stop)
{
    uint8_t i;

    for (i = 0; i < p_trans->length; i++) {
        while (!amhw_zlg237_i2c_checkflagstaus(p_hw_i2c,
                AMHW_ZLG_I2C_FLAG_RXNE));

        /* �������� */
        ((uint8_t *)(p_trans->p_buf))[i] = amhw_zlg237_i2c_recv_data(p_hw_i2c);

        if (i == (p_trans->length - 2) && stop) {

            /* ����ֹͣ�źź�  iic �ص��ӻ�ģʽ */
            amhw_zlg237_i2c_genstop(p_hw_i2c, ENABLE);
            amhw_zlg237_i2c_ack_en(p_hw_i2c, DISABLE);
        }
    }

    return AM_OK;
}

/**
 * \brief I2C ������ʼ������
 *
 * \param[in] p_hw_i2c ָ��I2C�Ĵ������ָ��
 * \param[in] speed    �����ٶȲ���
 *
 * \retval  AM_OK     �������
 * \retval -AM_EINVAL ������Ч
 */
static int __i2c_mst_init (amhw_zlg237_i2c_t *p_hw_i2c,
                           uint32_t           speed,
                           uint32_t           clk_rate)
{

    uint32_t pclk1 = 0;
    uint16_t tmpreg = 0, i2c_freq_value = 0;
    uint16_t result = 0x04;

    uint16_t i2c_dutycycle = AMHW_ZLG237_I2C_DUTY_CYCLE_2;
    uint16_t i2c_mode      = AMHW_ZLG237_I2C_MODE_I2C;
    uint16_t i2c_ack       = AMHW_ZLG237_I2C_ACK_ENABLE;

    uint16_t i2c_acknowledgedaddress = AMHW_ZLG237_I2C_ACK_ADDRESS_7_BIT;
    uint16_t i2c_ownaddress1 = 0x01;

    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    /** <breif ���� CR2 */
    tmpreg = p_hw_i2c->i2c_cr2;

    /** <brief ���� freq[5:0] */
    tmpreg &= 0xFFC0;

    /** <brief ���� pclk1  ����freqʱ�� */
    pclk1 = clk_rate;

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

        /** \brief д��CR1 */
        p_hw_i2c->i2c_cr1 = tmpreg;

        /** \brief I2C OAR1 ���� */
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
 * \brief I2C ������������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] p_trans  ָ�� I2C ����ṹ���ָ��
 *
 * \return ��
 */
static void __i2c_mst_start (amhw_zlg237_i2c_t *p_hw_i2c,
                             i2c_transfer_t    *p_trans,
                             uint32_t           clk_rate)
{
    if(!(p_trans->flags & I2C_M_NOSTART)) {

        __i2c_mst_init (p_hw_i2c, I2C_SPEED, clk_rate);
    }

    /* ������ʼ���� �л�����ģʽ */
    amhw_zlg237_i2c_genstrat(p_hw_i2c, ENABLE);

    /* EV5�¼� �� �ȴ�SB */
    while (!amhw_zlg237_i2c_checkevent(p_hw_i2c,
            I2C_EVENT_MASTER_MODE_SELECT ));

    /* ���SB��־λ */
    amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);

    /* ���ʹӻ���ַ */
    if ( p_trans->flags & I2C_M_RD) {
        /* ��*/
        amhw_zlg237_i2c_send7bit_address(
            p_hw_i2c, p_trans->addr, 1);

    } else {
        /* д */
        amhw_zlg237_i2c_send7bit_address(
            p_hw_i2c, p_trans->addr, 0);
    }

    /* �ȴ�EV6�¼���־λ */
    while (1) {
        if (p_hw_i2c->i2c_sr1 & 0x0002) {

            /* ���addr��־λ */
            amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr1);
            amhw_zlg237_i2c_read_reg(p_hw_i2c->i2c_sr2);
            break;
        }
    }
}
/**
 * \brief �������
 */
void demo_zlg237_hw_i2c_master_poll_entry (amhw_zlg237_i2c_t *p_hw_i2c,
                                           uint32_t           clk_rate)
{
    i2c_transfer_t *p_trans              = &__g_i2c1_transfer;
    uint8_t         eeprom_buf[16]       = {0};
    uint8_t         test_addr[2]         = {0x02};
    uint8_t         i;

    __i2c_mst_init(p_hw_i2c, I2C_SPEED, clk_rate);   /* I2C ������ʼ������ */

     /* ���� transfer �ṹ�������д���ַ */
    __i2c_mktrans(p_trans,
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_WR | I2C_M_NOSTART),
                  (uint8_t *)test_addr,
                  1);

    __i2c_mst_start(p_hw_i2c, p_trans, clk_rate);
    __i2c_mst_send (p_hw_i2c, p_trans, AM_FALSE);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = i + 0xc;
    }

     /* ���� transfer �ṹ�������д������ */
    __i2c_mktrans(p_trans,
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_NOSTART | I2C_M_WR),
                  (uint8_t *)eeprom_buf,
                  TEST_LEN);

    __i2c_mst_start(p_hw_i2c, p_trans, clk_rate);
    __i2c_mst_send(p_hw_i2c, p_trans, AM_TRUE);

    am_mdelay(10);

    /* ���� transfer �ṹ�������д���ַ */
    __i2c_mktrans(p_trans,
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_WR | I2C_M_NOSTART),
                  (uint8_t *)test_addr,
                  1);

    __i2c_mst_start(p_hw_i2c, p_trans, clk_rate);
    __i2c_mst_send (p_hw_i2c, p_trans, AM_FALSE);


   /* ���� transfer �ṹ���������ȡ���� */
    for (i = 0; i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    __i2c_mktrans(p_trans,
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_RD | I2C_M_NOSTART),
                  (uint8_t *)eeprom_buf,
                  TEST_LEN);

    __i2c_mst_start(p_hw_i2c, p_trans, clk_rate);
    __i2c_mst_recv(p_hw_i2c, p_trans, AM_TRUE);

    am_mdelay(10);

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < TEST_LEN; i++) {
        am_kprintf("Read EEPROM the %2dth data is  : 0x%02x\r\n", i, eeprom_buf[i]);

        /* У��ʧ�� */
        if(eeprom_buf[i] != (i + 0xc)) {
            am_kprintf("verify failed!\r\n");
            break;
        }
    }

    if (TEST_LEN == i) {
        am_kprintf("verify success!\r\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg116_hw_i2c_master_poll] */

/* end of file */

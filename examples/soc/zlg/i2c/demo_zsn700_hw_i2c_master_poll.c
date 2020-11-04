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
 * \snippet demo_zsn700_hw_i2c_master_poll.c src_zsn700_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 20-03-16  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_i2c_master_poll
 * \copydoc demo_zsn700_hw_i2c_master_poll.c
 */

/** [src_zsn700_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_errno.h"
#include "hw/amhw_zsn700_i2c.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define I2C_M_7BIT          0x0000u     /**< \brief 7-bits �豸��ַ */
#define I2C_M_10BIT         0x0001u     /**< \brief 10-bit �豸��ַ */
#define I2C_M_WR            0x0000u     /**< \brief д���� */
#define I2C_M_RD            0x0002u     /**< \brief ������ */
#define I2C_M_NOSTART       0x0004u     /**< \brief ��������������ʶ */

#define I2C_SUBADDR_NONE    0x0000u     /**< \brief ���ӵ�ַ(Ĭ��)  */
#define I2C_SUBADDR_1BYTE   0x1000u     /**< \brief �ӵ�ַ���1�ֽ� */
#define I2C_SUBADDR_2BYTE   0x2000u     /**< \brief �ӵ�ַ���2�ֽ� */

#define I2C_SPEED           100000      /**< \brief I2C �������ٶȲ������� */
#define EEPROM_ADDR         0x50        /**< \brief EEPROM �豸��ַ���� */
#define TEST_LEN            0x08        /**< \brief ���� EEPROM ��ҳ��С */

#define __I2C_ST_IDLE       (0x10u)     /* ����״̬ */
#define __I2C_ST_MSG_START  (0x11u)     /* ��Ϣ���俪ʼ״̬ */

/**
 * \brief I2C ����ṹ�嶨�壬��Ҫ���� I2C ��ѯģʽ��
 */
typedef struct i2c_transfer {

    /** \brief I2C�豸��ַ */
    volatile uint16_t   addr;

    /** \brief I2C �豸�����Լ�transfer��Ҫ�������ʶ */
    uint16_t            flags;

    /** \brief I2C �������ݻ���ָ�� */
    uint8_t            *p_buf;

    /** \brief I2C ���ݻ��泤�� */
    uint16_t            length;
} i2c_transfer_t;

typedef struct i2c_message {
    i2c_transfer_t     *p_transfer;
    uint16_t            trans_num;      /**< \brief ������Ĵ������          */
    uint16_t            done_num;       /**< \brief �ɹ�����Ĵ������          */
    int                 status;         /**< \brief ��Ϣ��״̬                         */
} i2c_message_t;

/** \brief I2C ����ṹ�� */
static i2c_transfer_t __g_i2c1_transfer[4];

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

static void __i2c_mkmsg (i2c_message_t  *p_msg,
                         i2c_transfer_t *p_transfer,
                         uint16_t        trans_num)
{
    p_msg->p_transfer   = p_transfer;
    p_msg->trans_num    = trans_num;
    p_msg->done_num     = 0;
    p_msg->status       = -AM_ENOTCONN;
}

/**
 * \brief I2C ������������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] p_trans  ָ�� I2C ����ṹ���ָ��
 *
 * \return ��
 */
static am_err_t __i2c_msg_start (amhw_zsn700_i2c_t  *p_hw_i2c,
                                 i2c_message_t      *p_msg)
{
    int     state;
    uint8_t data_ptr = 0;

    i2c_transfer_t *p_cur_trans = p_msg->p_transfer;

    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    /* ������ʼ���� */
    amhw_zsn700_i2c_cr_set(p_hw_i2c, AMHW_ZSN700_I2C_START_ENABLE);

    while(1) {
        /* ��ȡ�жϱ�־ */
        while(0 == amhw_zsn700_i2c_irq_get(p_hw_i2c));
        p_msg->status = __I2C_ST_MSG_START;

        /* ��ȡI2C״̬ */
        state = amhw_zsn700_i2c_status_get(p_hw_i2c);

        if(p_cur_trans[p_msg->done_num].flags & I2C_M_RD) {  /* ������ */
            switch (state) {

            case 0x08: /* �ѷ�����ʼ���� */
            case 0x10: /* �ѷ����ظ���ʼ���� */

                /* �����ʼ���� */
                amhw_zsn700_i2c_cr_clear(p_hw_i2c,
                                         AMHW_ZSN700_I2C_START_ENABLE);

                /* ����ӻ���ַ�Ͷ����� */
                amhw_zsn700_i2c_dat_write(p_hw_i2c,
                                          ((p_cur_trans->addr << 1) | 0x1));
                break;

            case 0x18: /* �ѷ���SLA+W���ѽ���ACK */

                /* ����Ŀ���ַ */
                amhw_zsn700_i2c_dat_write(p_hw_i2c,
                        p_cur_trans[p_msg->done_num - 1].p_buf[data_ptr]);
                break;

            case 0x28: /* �ѷ������ݣ��ѽ���ACK */

                /* �����ظ���ʼ���� */
                amhw_zsn700_i2c_cr_set(p_hw_i2c, AMHW_ZSN700_I2C_START_ENABLE);
                break;

            case 0x40: /* �ѷ���SLA +R,�ѽ���ACK */

                /* ʹ��Ӧ�� */
                if(p_cur_trans[p_msg->done_num].length > 1) {
                    amhw_zsn700_i2c_cr_set(p_hw_i2c,
                                           AMHW_ZSN700_I2C_REPLY_ENABLE);
                }
                break;

            case 0x48: /* �ѷ���SLA +R,�ѽ��շ�ACK */
                amhw_zsn700_i2c_cr_set(p_hw_i2c, AMHW_ZSN700_I2C_STOP_ENABLE);
                amhw_zsn700_i2c_cr_set(p_hw_i2c, AMHW_ZSN700_I2C_START_ENABLE);
                break;

            case 0x50:/* �ѽ��������ֽڣ�ACK�ѷ��� */

                /* �������� */
                p_cur_trans[p_msg->done_num].p_buf[data_ptr++] = \
                    amhw_zsn700_i2c_dat_read(p_hw_i2c);

                if(data_ptr == p_cur_trans[p_msg->done_num].length - 1) {

                    /* ����Ӧ�� */
                    amhw_zsn700_i2c_cr_clear(p_hw_i2c,
                                             AMHW_ZSN700_I2C_REPLY_ENABLE);
                }
                break;

            case 0x58:/* �ѽ��������ֽڣ���ACK�ѷ��� */

                /* �������һ������ */
                p_cur_trans[p_msg->done_num].p_buf[data_ptr++] = \
                    amhw_zsn700_i2c_dat_read(p_hw_i2c);
                p_msg->status = __I2C_ST_IDLE;
                break;

            case 0x38: /* ��SLA+ ��д��д�����ֽ�ʱ��ʧ�ٲ� */
            default:
                p_msg->status = __I2C_ST_IDLE;
                break;
            }
        } else {    /* д���� */
            switch (state) {

            case 0x08: /* �ѷ�����ʼ���� */

                /* �����ʼ���� */
                amhw_zsn700_i2c_cr_clear(p_hw_i2c,
                                         AMHW_ZSN700_I2C_START_ENABLE);

                /* ����ӻ���ַ��д���� */
                amhw_zsn700_i2c_dat_write(p_hw_i2c, (p_cur_trans->addr << 1));
                break;

            case 0x18: /* �ѷ���SLA+W���ѽ���ACK */
            case 0x28: /* �ѷ������ݣ��ѽ���ACK */
                if(p_msg->done_num <= p_msg->trans_num) {

                    /* �������� */
                    amhw_zsn700_i2c_dat_write(p_hw_i2c,
                                              p_cur_trans[p_msg->done_num].\
                                              p_buf[data_ptr++]);
                }
                break;

            case 0x20: /* �ѷ���SLA+W���ѽ��շ�ACK */
            case 0x30: /* �ѷ������� */
            case 0x38: /* ��SLA+ ��д��д�����ֽ�ʱ��ʧ�ٲ� */
            default:
                p_msg->status = __I2C_ST_IDLE;
                break;
            }
        }

        /* �ж���Ϣ�Ƿ������ */
        if(data_ptr >= p_cur_trans[p_msg->done_num].length) {
            p_msg->done_num++;
            data_ptr = 0;
        }

        if(p_msg->status == __I2C_ST_IDLE ||
           p_msg->done_num > p_msg->trans_num) {

            /* ����ֹֹͣͣ��־ */
            amhw_zsn700_i2c_cr_set(p_hw_i2c, AMHW_ZSN700_I2C_STOP_ENABLE);

            /* ����жϱ�־λ */
            amhw_zsn700_i2c_cr_clear(p_hw_i2c, AMHW_ZSN700_I2C_INT_FLAG);
            break;
        } else if(p_msg->done_num == p_msg->trans_num) {
            p_msg->done_num++;
        }

        /* ����жϱ�־λ */
        amhw_zsn700_i2c_cr_clear(p_hw_i2c, AMHW_ZSN700_I2C_INT_FLAG);
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
static int __i2c_mst_init (amhw_zsn700_i2c_t *p_hw_i2c,
                           uint32_t        speed,
                           uint32_t        clk_rate)
{
    uint16_t count = ((clk_rate / speed) >> 3) - 1;

    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c->i2c_cr = 0;

    /* �������� */
    if (speed < 100000) {
        amhw_zsn700_i2c_cr_clear(p_hw_i2c, AMHW_ZSN700_I2C_HIGH_SPEED);
    } else {
        amhw_zsn700_i2c_cr_set(p_hw_i2c, AMHW_ZSN700_I2C_HIGH_SPEED);
    }
    amhw_zsn700_i2c_tm_set(p_hw_i2c, count);
    amhw_zsn700_i2c_tm_enable(p_hw_i2c);

    amhw_zsn700_i2c_enable(p_hw_i2c);

    return AM_OK;
}

/**
 * \brief �������
 */
void demo_zsn700_hw_i2c_master_poll_entry (void        *p_hw_i2c,
                                           uint32_t     clk_rate)
{
    i2c_message_t   msg;
    i2c_transfer_t *p_trans              = __g_i2c1_transfer;
    uint8_t         eeprom_buf[16]       = {0};
    uint8_t         test_addr[2]         = {0x02};
    uint8_t         i;

    __i2c_mst_init(p_hw_i2c, I2C_SPEED, clk_rate);   /* I2C ������ʼ������ */

     /* ���� transfer �ṹ�������д���ַ */
    __i2c_mktrans(&p_trans[0],
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_SUBADDR_1BYTE | I2C_M_WR),
                  (uint8_t *)test_addr,
                  1);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = i + 0xA;
    }

     /* ���� transfer �ṹ�������д������ */
    __i2c_mktrans(&p_trans[1],
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_SUBADDR_1BYTE |
                   I2C_M_NOSTART | I2C_M_WR),
                  (uint8_t *)eeprom_buf,
                  TEST_LEN);

    __i2c_mkmsg(&msg, p_trans, 2);
    __i2c_msg_start(p_hw_i2c, &msg);

    am_mdelay(10);

    /* ���� transfer �ṹ�������д���ַ */
    __i2c_mktrans(&p_trans[0],
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_WR | I2C_SUBADDR_1BYTE),
                  (uint8_t *)test_addr,
                  1);

   /* ���� transfer �ṹ���������ȡ���� */
    for (i = 0; i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    __i2c_mktrans(&p_trans[1],
                  EEPROM_ADDR,
                  (I2C_M_7BIT | I2C_M_RD | I2C_SUBADDR_1BYTE),
                  (uint8_t *)eeprom_buf,
                  TEST_LEN);

    __i2c_mkmsg(&msg, p_trans, 2);
    __i2c_msg_start(p_hw_i2c, &msg);

    am_mdelay(10);

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < TEST_LEN; i++) {
        am_kprintf("Read EEPROM the %2dth data is : 0x%02x\r\n",
                   i,
                   eeprom_buf[i]);

        /* У��ʧ�� */
        if(eeprom_buf[i] != (i + 0xA)) {
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
/** [src_zsn700_hw_i2c_master_poll] */

/* end of file */

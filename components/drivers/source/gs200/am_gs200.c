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
 * \brief GS200 driver implement
 *
 * \internal
 * \par Modification History
 * - 1.00 19-12-16  fzb, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_gs200.h"
#include "am_int.h"
#include "am_uart.h"
#include "am_uart_rngbuf.h"
#include "am_vdebug.h"
#include "am_wait.h"
#include "string.h"

/*
 *  1.GS200���Ƽ��ģ��Ĭ�ϲ���9600�Ĳ���������������ͨѶ��ͬʱ֧��4800��115200�Ĳ�����
 *         ����ͨѶ���ڽ��в������޸�ʱ����ָ������ģ�齫����1ms�ڷ�����ͬ��ָ���
 *         ģ���޸������õĲ����ʲ����ɹ���ģ�齫��10ms���������õĲ������ٴη�����ͬ��
 *         ����ָ�
 *
 *  ע�⣺ģ�����󲻱����Ѿ����õĲ����ʣ������ϵ��Ĭ�ϲ�����Ϊ9600��
 *
 *  2.�û���ʵ��ʹ��ʱ�����Ը��ݾ�����������Ҫ�����ƽ��н��ܺ�ʹ�ܵ����á��ϵ��
 *      Ĭ���ϡ��¡��������ƶ���ʹ�ܣ���ͣ����Ĭ�Ͻ��ܡ�
 *
 *  3.��ͣ����ָ�����Ĭ�ϲ��ñ�����ͣ����500ms�����100ms����������ͣ��ʱ�������ʱ��
 *      ���Ը��Ķ�ʱ���ʱ���������õ��δ������ģʽʱ�����Ը��ĵ��δ�����ʱ����
        �����Ĭ����Сʱ��Ϊ200ms��
 */

/* \brief   ������ս���״̬��  */
#define __GS200_CMD_PROC_STAT_NONE              0       /* ����������       */
#define __GS200_CMD_PROC_STAT_START             1       /* ������������     */
#define __GS200_CMD_PROC_STAT_SEND              2       /* �����         */
#define __GS200_CMD_PROC_STAT_RECV_HEAD         3       /* ���յ�֡ͷ       */
#define __GS200_CMD_PROC_STAT_RECV_FRAMEID      4       /* ���յ�֡��ʶ     */
#define __GS200_CMD_PROC_STAT_RECV_DATA1        5       /* ���յ�����1      */
#define __GS200_CMD_PROC_STAT_RECV_DATA2        6       /* ���յ�����2      */
#define __GS200_CMD_PROC_STAT_RECV_END          7       /* ����������     */
#define __GS200_CMD_PROC_STAT_RECV_OVERFLOW     8       /* �����������     */
#define __GS200_CMD_PROC_STAT_RECV_ERR          9       /* �����������     */

/*
 * \brief   ͨ��Э��֡��ʽ  
 * 
 *      ֡ͷ            ֡��ʶ          ֡����1         ֡����2         ֡У��CRC-8
 *    1Byte(0x1A)       1Byte           1Byte           1Byte           1Byte
 *
 */

#define __GS200_COM_FRAME_HEAD                  (0x1A)  /* ֡ͷ */

/* ָ��(֡��ʶ) */
#define __GS200_CMD_GESTURE_REPORTING           (0x00)  /* ���������ϱ�����ָ��             */
#define __GS200_CMD_SET_BAUDRATE                (0x01)  /* ����ģ��ͨѶ�ӿڲ�����ָ��       */
#define __GS200_CMD_SET_GESTURE_STATE           (0x02)  /* ����ģ�����ƹ���ʹ�������ָ��   */
#define __GS200_CMD_SET_WORKING_CONDITION       (0x03)  /* ���ù���״ָ̬��                 */
#define __GS200_CMD_WORKING_STATUS_INDICATOR    (0x04)  /* ģ�鹤��״ָ̬ʾָ��             */
#define __GS200_CMD_SET_HOVERING_GESTURE        (0x0A)  /* ������ͣ�������ָ��             */

/* ������ͣ�������ʹ�� */
#define __GS200_SET_OUTPUT_TIMING_ENABLE        (0x02)  /* ����GS200��ָͣ�ʱ���ʹ�� */
#define __GS200_SET_OUTPUT_SINGLE_ENABLE        (0x03)  /* ����GS200��ָͣ������ʹ�� */

/*******************************************************************************
* ��������
*******************************************************************************/

/** 
 * \brief GS200 ֡����У��
 */
am_local uint8_t __gs200_frame_check(uint8_t *ptr, uint32_t len);

/** 
 * \brief GS200 �����
 */
am_local int __gs200_cmd_send (am_gs200_dev_t   *p_this,
                               uint8_t           frame_id,      //֡��ʶ
                               uint8_t           frame_data1,   //֡����λ1
                               uint8_t           frame_data2,   //֡����λ2
                               am_bool_t         need_check);

/** 
 * \brief GS200 �����ֽڷ���
 */
am_local int __gs200_cmd_char_send(am_gs200_dev_t   *p_this,
                                   char              ch);

/** 
 * \brief GS200 ���ݷ���
 */
am_local int __gs200_data_send (am_gs200_dev_t      *p_this,
                                const uint8_t       *p_buf,
                                int                  len);

/** 
 * \brief GS200 ���ͻص�����
 */
am_local int __gs200_uart_txchar_get (void *p_arg, char *p_outchar);

/** 
 * \brief GS200 ���ͽ�� (�ȴ��������)
 */
am_local int __gs200_cmd_result (am_gs200_dev_t *p_this,
                                 uint8_t         frame_id,      //֡��ʶ
                                 am_bool_t       need_check);

/** 
 * \brief GS200 ���ջص�����
 */
am_local int __gs200_uart_rxchar_put (void *p_arg, char inchar);

/** 
 * \brief GS200 ����������ɺ�,�ӻ��ظ�
 */
am_local int __gs200_cmd_ack_recv_proc (am_gs200_dev_t *p_this, char inchar);

/** 
 * \brief GS200 ���ͽ����Ϣ��ȡ (����У��)
 */
am_local int __gs200_cmd_result_info_get (am_gs200_dev_t    *p_this,
                                          uint8_t            frame_id,      //֡��ʶ
                                          am_bool_t          need_check);

/** 
 * \brief GS200 ���ݽ���
 */
am_local int __gs200_data_recv (am_gs200_dev_t      *p_this,
                                uint8_t             *p_buf,
                                int                  len);


/******************************************************************************/

/** 
 * \brief GS200 ֡����У��
 */
am_local uint8_t __gs200_frame_check(uint8_t *ptr, uint32_t len)
{
    uint8_t crc, i;

    crc = 0xFF;
    while(len--) {
        crc ^= *ptr++;
        for(i = 0; i < 8; i++) {
            if (crc &0x80) {
                crc = (crc << 1) ^ 0x131;
            } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}

/******************************************************************************/

/** 
 * \brief GS200 �����
 */
am_local int __gs200_cmd_send (am_gs200_dev_t   *p_this,
                               uint8_t           frame_id,      //֡��ʶ
                               uint8_t           frame_data1,   //֡����λ1
                               uint8_t           frame_data2,   //֡����λ2
                               am_bool_t         need_check)
{
    uint8_t i;

    p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_START;

    /* The tx buffer temp for receive cmd ack, only used after send complete */
    p_this->p_cmd_rxbuf     = p_this->p_devinfo->p_uart_txbuf;
    p_this->cmd_rxbuf_len   = p_this->p_devinfo->txbuf_size;
    p_this->cmd_rx_len      = 0;

    /* ����ͨ��֡���� */
    p_this->p_devinfo->p_cmd_txbuf[0]  = __GS200_COM_FRAME_HEAD;
    p_this->p_devinfo->p_cmd_txbuf[1]  = frame_id;
    p_this->p_devinfo->p_cmd_txbuf[2]  = frame_data1;
    p_this->p_devinfo->p_cmd_txbuf[3]  = frame_data2;

    if (need_check == AM_TRUE) {    //֡У���ֽ�����
        p_this->p_devinfo->p_cmd_txbuf[4] = __gs200_frame_check(&p_this->p_devinfo->p_cmd_txbuf[1], 3);//֡У���ֽ�����
    }

    /* �˴�ѡ�������ֽڷ�������Ϊ���������ֽ�֮����ź�Ҫ��200us���ϵ�ʱ���� */
    for (i = 0; i < p_this->p_devinfo->cmd_txbuf_len; i++) {
        __gs200_cmd_char_send(p_this, p_this->p_devinfo->p_cmd_txbuf[i]);
    }

    return AM_OK;
}

/******************************************************************************/

/** 
 * \brief GS200 �����ֽڷ���
 */
am_local int __gs200_cmd_char_send(am_gs200_dev_t   *p_this,
                                   char              ch)
{
    return __gs200_data_send(p_this, (const uint8_t *)(&ch), 1);
}

/******************************************************************************/

/** 
 * \brief GS200 ���ݷ���
 */
am_local int __gs200_data_send (am_gs200_dev_t      *p_this,
                                const uint8_t       *p_buf,
                                int                  len)
{
    am_rngbuf_t rb     = &(p_this->tx_rngbuf);
    uint32_t    nbytes = len;

    uint32_t rb_ct, write_ct;

    if (am_rngbuf_isfull(rb) == AM_TRUE) {      //���λ������Ƿ�����
        return -AM_ENOSPC;                      //�豸ʣ��ռ䲻��
    }

    rb_ct = am_rngbuf_freebytes(rb);            //��ȡ���λ��������пռ��С
    write_ct = (rb_ct > len) ? len : rb_ct;

    am_rngbuf_put(rb, (const char *)p_buf, write_ct);//��������ֽڵ����λ�����

    p_buf += write_ct;
    len   -= write_ct;

    am_uart_tx_startup(p_this->uart_handle);    //����UART�ж�ģʽ���ݴ���

    return nbytes - len;
}

/******************************************************************************/

/** 
 * \brief GS200 ���ͻص�����
 */
am_local int __gs200_uart_txchar_get (void *p_arg, char *p_outchar)
{
    am_gs200_dev_t  *p_dev      =   (am_gs200_dev_t *)p_arg;
    am_rngbuf_t     rb          =   &(p_dev->tx_rngbuf);
    uint32_t        key         =   am_int_cpu_lock();

    /* Success pop one data from ring buffer */
    if (am_rngbuf_getchar(rb, p_outchar) == 1) {    //�ӻ��λ�����ȡ��һ���ֽ�����
        am_int_cpu_unlock(key);     //1:���ݳɹ�ȡ��    0:����ȡ��ʧ�ܣ�������Ϊ��
        return AM_OK;
    }

    if (p_dev->cmd_proc_state == __GS200_CMD_PROC_STAT_START) {

        p_dev->cmd_proc_state = __GS200_CMD_PROC_STAT_SEND;

        /* send complete  */
        am_wait_done(&p_dev->ack_wait);
    }

    am_int_cpu_unlock(key);

    return -AM_EEMPTY;     /* No data to transmit,return -AM_EEMPTY */
}

/******************************************************************************/

/** 
 * \brief GS200 ���ͽ�� (�ȴ��������)
 */
am_local int __gs200_cmd_result (am_gs200_dev_t *p_this,
                                 uint8_t         frame_id,      //֡��ʶ
                                 am_bool_t       need_check)
{
    int          key;

    /* �ȴ�������� */
    am_wait_on(&p_this->ack_wait);

    /* һ֡����Ҫ��10ms�ڽ�����ϣ������ж�Ϊ֡���ݽ��ճ�ʱ */
    am_softimer_start(&p_this->timer, 10);

    am_rngbuf_init(&(p_this->tx_rngbuf),
                    (char *)p_this->p_devinfo->p_uart_txbuf,
                    p_this->p_devinfo->txbuf_size);

    while (1) {

        /* wait 20ms */
        if (am_wait_on_timeout(&p_this->ack_wait, 20) == AM_OK) {

            key = am_int_cpu_lock();

            /* success process */
            if (p_this->cmd_proc_state == __GS200_CMD_PROC_STAT_RECV_END) {

                p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_NONE;
                am_int_cpu_unlock(key);

                return __gs200_cmd_result_info_get(p_this,
                                                   frame_id,
                                                   need_check);
            }

            if (p_this->cmd_proc_state != __GS200_CMD_PROC_STAT_RECV_ERR) {

                am_int_cpu_unlock(key);
                continue;
            }

            am_int_cpu_unlock(key);
        }

        /* run to here, some error happen */
        key = am_int_cpu_lock();

        /* move the data to rx rngbuf */
        if (p_this->cmd_rx_len != 0) {
            am_rngbuf_put(&(p_this->rx_rngbuf),
                          (const char *)(p_this->p_cmd_rxbuf),
                           p_this->cmd_rx_len);

            am_wait_done(&(p_this->rx_wait));
        }

        p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_NONE;

        am_int_cpu_unlock(key);

        return AM_ERROR;
    }
}

/******************************************************************************/

/** 
 * \brief GS200 ���ջص�����
 */
am_local int __gs200_uart_rxchar_put (void *p_arg, char inchar)
{
    am_gs200_dev_t *p_dev  = (am_gs200_dev_t *)p_arg;
    am_rngbuf_t     rx_rb  = &(p_dev->rx_rngbuf);

    if (p_dev->cmd_proc_state >= __GS200_CMD_PROC_STAT_SEND) {
        /* success process by cmd ack */
        if (__gs200_cmd_ack_recv_proc(p_dev, inchar) == AM_OK) {
             return AM_OK;
        }
    }

    /* wait done */
    am_wait_done(&p_dev->rx_wait);      //����֮ǰ�����Ľ������ݵĵȴ�

    if (am_rngbuf_putchar(rx_rb, inchar) == 1) {        /* ���һ���ֽڵ����λ����� */
        return AM_OK;                                   //1:���ݳɹ����    0:���ݴ��ʧ�ܣ���������
    }

    return -AM_EFULL;          /* No data to receive,return -AM_EFULL */
}

/******************************************************************************/

/** 
 * \brief GS200 ����������ɺ�,�ӻ��ظ�
 */
am_local int __gs200_cmd_ack_recv_proc (am_gs200_dev_t *p_this, char inchar)
{
    int ret = AM_ERROR;

    switch (p_this->cmd_proc_state) {

    case __GS200_CMD_PROC_STAT_SEND:  /* Cmd send complete       */
        memset(p_this->p_cmd_rxbuf, 0 , 10);
        ret = AM_OK;
        p_this->p_cmd_rxbuf[p_this->cmd_rx_len++] = inchar;
        p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_HEAD;           //���յ�֡ͷ
        break;

    case __GS200_CMD_PROC_STAT_RECV_HEAD:
        ret = AM_OK;
        p_this->p_cmd_rxbuf[p_this->cmd_rx_len++] = inchar;
        p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_FRAMEID;        //���յ�֡��ʶ
        break;

    case __GS200_CMD_PROC_STAT_RECV_FRAMEID:
        ret = AM_OK;
        p_this->p_cmd_rxbuf[p_this->cmd_rx_len++] = inchar;
        p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_DATA1;          //���յ�����1
        break;

    case __GS200_CMD_PROC_STAT_RECV_DATA1:
        ret = AM_OK;
        p_this->p_cmd_rxbuf[p_this->cmd_rx_len++] = inchar;
        p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_DATA2;          //���յ�����2
        break;

    case __GS200_CMD_PROC_STAT_RECV_DATA2:
        ret = AM_OK;
        p_this->p_cmd_rxbuf[p_this->cmd_rx_len++] = inchar;
        p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_END;            //����������
        am_softimer_stop(&p_this->timer);       //�رս��ճ�ʱ��ⶨʱ��
        break;

    default:
        ret = -AM_ESRCH;
        p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_ERR;            //�����������
        break;
    }

    if (ret != AM_OK) {

        if (p_this->cmd_rx_len != 0) {  /* not empty, error happen */
            p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_ERR;        //�����������
        }
    } else {

        /* full */
        if ((p_this->cmd_rx_len     == p_this->cmd_rxbuf_len) &&
            (p_this->cmd_proc_state != __GS200_CMD_PROC_STAT_RECV_END)) {

            p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_ERR;        //�����������
        }
    }

    /* receive one ack data */
    am_wait_done(&p_this->ack_wait);

    return ret;
}

/******************************************************************************/

/** 
 * \brief GS200 ���ͽ����Ϣ��ȡ (����У��)
 */
am_local int __gs200_cmd_result_info_get (am_gs200_dev_t    *p_this,
                                          uint8_t            frame_id,      //֡��ʶ
                                          am_bool_t          need_check)
{
    uint8_t i;

    if (p_this->p_cmd_rxbuf[0] != __GS200_COM_FRAME_HEAD) {
        return AM_ERROR;            //֡ͷ����
    }

    if (need_check == AM_TRUE) {    //����֡У���ж�
        if (__gs200_frame_check(&(p_this->p_cmd_rxbuf[1]), 4) == 0) {
            if (frame_id == __GS200_CMD_SET_WORKING_CONDITION) {    //֡��ʶΪ���ù���״ָ̬��
                //�˴��������ģ���л�״̬��ָ��
                return AM_OK;       //���յ���֡��������У��ͨ��
            }
        } else {
            return AM_ERROR;        //У��ʧ�ܣ����ش���
        }
    }

    for (i = 0; i < p_this->cmd_rx_len; i++) {
        if (p_this->p_cmd_rxbuf[i] != p_this->p_devinfo->p_cmd_txbuf[i]) {
            break;
        }
    }
    if (i == p_this->cmd_rx_len) {
        return AM_OK;       //����������ӻ��ظ�����һ��
    } else {
        return AM_ERROR;    //����������ӻ��ظ����ݲ�һ��
    }

}

/******************************************************************************/

/** 
 * \brief GS200 ���ݽ���
 */
am_local int __gs200_data_recv (am_gs200_dev_t      *p_this,
                                uint8_t             *p_buf,
                                int                  len)
{
    am_rngbuf_t rb = &(p_this->rx_rngbuf);

    uint32_t rb_ct, read_ct;
    uint32_t nbytes = 0;

    while (len > 0) {

        if (am_rngbuf_isempty(rb) == AM_TRUE) {

            if (p_this->timeout_ms == (uint32_t)AM_WAIT_FOREVER) {

                am_wait_on(&p_this->rx_wait);       //�ȴ���������

            } else if (p_this->timeout_ms != AM_NO_WAIT) {

                if (am_wait_on_timeout(&p_this->rx_wait,
                                       p_this->timeout_ms) != AM_OK) {
                    return nbytes;
                }

            } else {
                return nbytes;
            }
        }

        rb_ct   = am_rngbuf_nbytes(rb); //��ȡ���λ������������������ֽڸ���

        read_ct = (rb_ct > len) ? len : rb_ct;

        am_rngbuf_get(rb, (char *)p_buf, read_ct);  //�ӻ��λ�������ȡ����

        p_buf   += read_ct;
        len     -= read_ct;
        nbytes  += read_ct;
    }

    return nbytes;
}

/******************************************************************************/

/** 
 * \brief GS200 ���ճ�ʱ�ص�����
 */
am_local void __gs200_timeout_cb (void *p_arg)
{
    am_gs200_dev_t  *p_this = (am_gs200_dev_t *)p_arg;
    int              key    = am_int_cpu_lock();

    am_softimer_stop(&(p_this->timer));         //�رս��ճ�ʱ��ⶨʱ��
    p_this->cmd_proc_state = __GS200_CMD_PROC_STAT_RECV_END;
    am_wait_done(&(p_this->rx_wait));
    am_int_cpu_unlock(key);
}

/******************************************************************************/

/** 
 * \brief GS200 ��ʼ��
 */
am_gs200_handle_t am_gs200_init (am_gs200_dev_t             *p_dev,
                                 const am_gs200_devinfo_t   *p_devinfo,
                                 am_uart_handle_t            uart_handle)
{

    if ((p_dev                   == NULL) ||
        (p_devinfo               == NULL) ||
        (p_devinfo->p_uart_rxbuf == NULL) ||
        (p_devinfo->p_uart_txbuf == NULL)) {

        return NULL;
    }

    p_dev->uart_handle    = uart_handle;
    p_dev->p_devinfo      = p_devinfo;
    p_dev->timeout_ms     = (uint32_t)AM_WAIT_FOREVER;
    p_dev->cmd_proc_state = __GS200_CMD_PROC_STAT_NONE;

    am_wait_init(&(p_dev->rx_wait));
    am_wait_init(&(p_dev->ack_wait));

    am_softimer_init(&p_dev->timer, __gs200_timeout_cb , (void *)p_dev);

    am_uart_ioctl(uart_handle, AM_UART_BAUD_SET, (void *)(p_devinfo->baudrate));

    /* Initialize the ring-buffer */
    am_rngbuf_init(&(p_dev->rx_rngbuf),
                   (char *)p_devinfo->p_uart_rxbuf,
                   p_devinfo->rxbuf_size);

    am_rngbuf_init(&(p_dev->tx_rngbuf),
                   (char *)p_devinfo->p_uart_txbuf,
                   p_devinfo->txbuf_size);

    am_uart_ioctl(uart_handle, AM_UART_MODE_SET, (void *)AM_UART_MODE_INT);

    am_uart_callback_set(uart_handle,
                         AM_UART_CALLBACK_TXCHAR_GET,
        (int (*)(void *))__gs200_uart_txchar_get,
                         (void *)(p_dev));

    am_uart_callback_set(uart_handle,
                         AM_UART_CALLBACK_RXCHAR_PUT,
        (int (*)(void *))__gs200_uart_rxchar_put,
                         (void *)(p_dev));

    return p_dev;
}

/******************************************************************************/

/** 
 * \brief GS200 ���ƺ���
 */
int am_gs200_ioctl (am_gs200_handle_t   handle,
                    int                 cmd,
                    void               *p_arg)
{
    int ret = -AM_EIO;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    switch (cmd) {
        case AM_GS200_SET_BAUDRATE:                 //���ò�����ָ��
            ret = __gs200_cmd_send(handle,
                                   __GS200_CMD_SET_BAUDRATE,
                                   (uint8_t)(int)p_arg,
                                   0x00,
                                   AM_TRUE);
            if (ret != AM_OK) {
                return ret;
            }
            ret = __gs200_cmd_result(handle,
                                     __GS200_CMD_SET_BAUDRATE,
                                     AM_TRUE);
            break;

        case AM_GS200_SET_GESTURE_STATE:            //����ģ�����ƹ���ʹ�������ָ��
            ret = __gs200_cmd_send(handle,
                                   __GS200_CMD_SET_GESTURE_STATE,
                                   (uint8_t)(int)p_arg,
                                   0x00,
                                   AM_TRUE);
            if (ret != AM_OK) {
                return ret;
            }
            ret = __gs200_cmd_result(handle,
                                     __GS200_CMD_SET_GESTURE_STATE,
                                     AM_TRUE);
            break;

        case AM_GS200_SET_WORKING_CONDITION:        //���ù���״ָ̬��
            ret = __gs200_cmd_send(handle,
                                   __GS200_CMD_SET_WORKING_CONDITION,
                                   (uint8_t)(int)p_arg,
                                   0x00,
                                   AM_TRUE);
            if (ret != AM_OK) {
                return ret;
            }
            ret = __gs200_cmd_result(handle,
                                     __GS200_CMD_SET_WORKING_CONDITION,
                                     AM_TRUE);
            break;

        case AM_GS200_SET_HOVERING_GESTURE_MODE:    //������ͣ����(��ʱ/����)���ָ��
            ret = __gs200_cmd_send(handle,
                                   __GS200_CMD_SET_HOVERING_GESTURE,
                                   (uint8_t)(int)p_arg,
                                   0x00,
                                   AM_TRUE);
            if (ret != AM_OK) {
                return ret;
            }
            ret = __gs200_cmd_result(handle,
                                     __GS200_CMD_SET_HOVERING_GESTURE,
                                     AM_TRUE);
            break;

        case AM_GS200_SET_HOVERING_TIMING_TIME:    //������ͣ���ƶ�ʱ���ʱ����
            ret = __gs200_cmd_send(handle,
                                   __GS200_CMD_SET_HOVERING_GESTURE,
                                   __GS200_SET_OUTPUT_TIMING_ENABLE,
                                   (uint8_t)(((int)p_arg) / 50),
                                   AM_TRUE);
            if (ret != AM_OK) {
                return ret;
            }
            ret = __gs200_cmd_result(handle,
                                     __GS200_CMD_SET_HOVERING_GESTURE,
                                     AM_TRUE);
            break;

        case AM_GS200_SET_HOVERING_SINGLE_TIME:    //������ͣ���Ƶ��δ���ʱ��
            ret = __gs200_cmd_send(handle,
                                   __GS200_CMD_SET_HOVERING_GESTURE,
                                   __GS200_SET_OUTPUT_SINGLE_ENABLE,
                                   (uint8_t)((((int)p_arg) - 200) / 50),
                                   AM_TRUE);
            if (ret != AM_OK) {
                return ret;
            }
            ret = __gs200_cmd_result(handle,
                                     __GS200_CMD_SET_HOVERING_GESTURE,
                                     AM_TRUE);
            break;

        case AM_GS200_NREAD:
            *(int *)p_arg = am_rngbuf_nbytes(&handle->rx_rngbuf);
            ret = AM_OK;
            break;

        case AM_GS200_NWRITE:
            *(int *)p_arg = am_rngbuf_nbytes(&handle->tx_rngbuf);
            ret = AM_OK;
            break;

        case AM_GS200_FLUSH:
        {
            int key = am_int_cpu_lock();

            am_rngbuf_flush(&handle->rx_rngbuf);
            am_rngbuf_flush(&handle->tx_rngbuf);
            am_int_cpu_unlock(key);
            ret = AM_OK;
            break;
        }

        case AM_GS200_WFLUSH :
        {
            int key = am_int_cpu_lock();

            am_rngbuf_flush(&handle->tx_rngbuf);
            am_int_cpu_unlock(key);
            ret = AM_OK;
            break;
        }

        case AM_GS200_RFLUSH :
        {
            int key = am_int_cpu_lock();

            am_rngbuf_flush(&handle->rx_rngbuf);
            am_int_cpu_unlock(key);
            ret = AM_OK;
            break;
        }

        case AM_GS200_TIMEOUT:
            handle->timeout_ms = (uint32_t)p_arg;
            ret = AM_OK;
            break;

        default:
            ret = -AM_ENOTSUP;
            break;
    }

    return ret;
}

/******************************************************************************/

/** 
 * \brief GS200 ����
 */
int am_gs200_send (am_gs200_handle_t    handle,
                   const uint8_t        *p_buf,
                   int                  len)
{
    if (handle == NULL) {
        return -AM_EINVAL;
    }

    /* in cmd process, can't send data now */
    if (handle->cmd_proc_state != __GS200_CMD_PROC_STAT_NONE) {
        return -AM_EPERM;
    }

    return __gs200_data_send(handle, p_buf, len);
}

/******************************************************************************/

/** 
 * \brief GS200 ����
 */
int am_gs200_recv (am_gs200_handle_t    handle,
                   uint8_t              *p_buf,
                   int                  len)
{
    if (handle == NULL) {
        return -AM_EINVAL;
    }

    return __gs200_data_recv(handle, p_buf, len);
}


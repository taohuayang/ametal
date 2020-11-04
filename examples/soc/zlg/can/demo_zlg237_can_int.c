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
 * \brief CAN�ж���ʾ����
 *
 * - �������裺
 *   1. �۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_3 �������� PC ���ڵ� TXD��
 *      PIOA_2 �������� PC ���ڵ� RXD��
 *   2. ����CAN1��������ŵ�CAN�շ������ٽ�CAN�շ����ӿ���USBCAN-II�豸������
 *   3. ��CAN��λ�������ò�����Ϊ�궨��CAN_BAUD��ֵ��
 *   4. �򿪴��ڵ����նˣ�������115200-8-N-1.
 *
 * - ʵ������
 *   1. ��������жϺ󣬴�ӡ��ʾ��Ϣ��
 *
 *      �����жϣ����ڴ�ӡ�ȴ�������ʾ��Ϣ����λ������һ�����ݺ󣬳ɹ����ѣ�����ӡ��ʾ��Ϣ��
 *      �����жϣ�ÿ���յ�һ�����ݣ����ڴ�ӡID�ţ��ֽ����ݡ�
 *      ����жϣ�FIFO(����3)����󣬴��ڴ�ӡFIFO�յ��ĵ�һ�����ݣ�ID�ţ��ֽ����ݡ�
 *      �����жϣ�ÿ500ms��whileѭ���з���һ�����ݣ����ݷ��ͳɹ������뷢���жϣ����ڴ�ӡ��ʾ��Ϣ��
 *      ���󾯸��жϣ����ڴ�ӡ��ʾ��Ϣ���Ҵ�ӡ���ʹ������ֵ�����մ������ֵ��
 *      ���󱻶��жϣ����ڴ�ӡ��ʾ��Ϣ���Ҵ�ӡ���ʹ������ֵ�����մ������ֵ��
 *
 *      ���Ľṹ��can_rcv_msg��demo_zlg237_can_int_entry()��ʹ�õ���ȫ�ֱ�������������(�ѻ���)��
 *      �����˽��ջ�����жϺ���λ�����͵����ݣ������Թ��̻�ÿ500ms���ظ���λ����
 *
 *   2. ���ڴ�ӡ��ص�����Ϣ��
 *
 * \par Դ����
 * \snippet src_zlg237_can_int.c
 *
 * \internal
 * \par Modification History
 * - 19-08-08, zp, first implementation.
 * - 19-12-18, zc, add filter table extern 
 * \endinternal
 */

/**
 * \addtogroup demo_zlg237_can_int
 * \copydoc demo_zlg237_can_int.c
 */

/** [src_std_can] */
#include "ametal.h"
#include "am_can.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "amhw_zlg237_can.h"
#include "am_zlg237_can.h"

am_bool_t int_err_flag   = AM_FALSE;
am_bool_t int_sleep_flag = AM_FALSE;

am_can_message_t can_rcv_msg;

/* �жϷ������������жϺ���Ҫ�ֶ������Ӧ��־λ�������һֱ�����ж�*/
void can_int_handle(void *p_arg)
{

    am_zlg237_can_dev_t *p_dev    = (am_zlg237_can_dev_t *)p_arg;
    amhw_zlg237_can_t   *p_hw_can = NULL;

    am_can_int_type_t p_int_type     = 0;
    am_can_bus_err_t  p_bus_err      = 0;
    uint8_t           i              = 0;

    p_hw_can = (amhw_zlg237_can_t *)p_dev->p_devinfo->regbase;

    am_can_status_get(p_arg, &p_int_type , &p_bus_err);

    /* FIFO���������Ϊ3��>3���������־��Ч */
    if(p_int_type & AM_CAN_INT_DATAOVER) {

        am_kprintf("\r\nCAN int data over!\r\n");

        /* ���Զ�ȡ���� */
        if(am_can_msg_recv(p_arg, &can_rcv_msg) == AM_CAN_NOERROR){

            am_kprintf("can recv id: 0x%x data:",can_rcv_msg.id);
            for (i = 0; i < can_rcv_msg.msglen; i++) {
                am_kprintf("0x%x  ",can_rcv_msg.msgdata[i]);
            }
            am_kprintf("\r\n");
        }

        /* ����FIFO���ԡ���ȡһ��֮�����ݼ���һ�顣
         * ��������ִ��һ�ζ�ȡ������ɲ���ִ�����������ʵ��Ϊ�ͷ�FIFOһ�Σ���
         * ��ȡ���ͷ����ֻ����һ�ֲ����������������ݶ�ʧ��
         */

//        /* �ͷ�һ��FIFO 0����������ñ�־ */
//        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_FOVIE0);
//
//        /* �ͷ�һ��FIFO 1����������ñ�־ */
//        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_FOVIE1);
    }

    /* FIFO�ǿգ�����Ϊ3��>0�������ձ�־��Ч */
    if(p_int_type & AM_CAN_INT_RX) {

        am_kprintf("\r\nCAN int rx!\r\n");

        /* ���Զ�ȡ���� */
        if(am_can_msg_recv(p_arg, &can_rcv_msg) == AM_CAN_NOERROR){

            am_kprintf("can recv id: 0x%x\r\ndata:",can_rcv_msg.id);
            for (i = 0; i < can_rcv_msg.msglen; i++) {
                am_kprintf("0x%x  ",can_rcv_msg.msgdata[i]);
            }
            am_kprintf("\r\n");
        }

        /* ����FIFO���ԡ���ȡһ��֮�����ݼ���һ�顣
         * ��������ִ��һ�ζ�ȡ������ɲ���ִ�����������ʵ��Ϊ�ͷ�FIFOһ�Σ���
         * ��ȡ���ͷ����ֻ����һ�ֲ����������������ݶ�ʧ��
         */

//        /* �ͷ�һ��FIFO 0��FIFOΪ��ʱ����������ñ�־*/
//        amhw_zlg237_can_clear_itstatus(p_hw_can, AMHW_ZLG237_CAN_INT_FMPIE0);
//
//        /* �ͷ�һ��FIFO 1��FIFOΪ��ʱ����������ñ�־*/
//        amhw_zlg237_can_clear_itstatus(p_hw_can, AMHW_ZLG237_CAN_INT_FMPIE1);
    }

    /* ���ͽ��������ͱ�־��Ч */
    if(p_int_type & AM_CAN_INT_TX) {

        am_kprintf("\r\nCAN int tx!\r\n");

        /* �ͷ�һ��FIFO��FIFOΪ��ʱ����������ñ�־*/
        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_TMEIE);
    }

    /* ��˯��ģʽ�£����յ�֡��SOFλ�����ѱ�־��Ч */
    if(p_int_type & AM_CAN_INT_WAKE_UP) {
        am_kprintf("\r\nCAN int wake up!\r\n");

        int_sleep_flag = AM_FALSE;

        /* ������ѱ�־ */
        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_WKUIE);
    }

    /* ���������������ֵ���̶������ɸ��ģ���������ͬ�����־�������յ���ȷ���ݣ�����ֵ��С��1 */
    if(p_int_type & AM_CAN_INT_ERROR) {

        int_err_flag = AM_TRUE;

        am_kprintf("\r\nCAN int error  ");

        /* �������ֵ>96,���󾯸��־��Ч */
        if(p_int_type & AM_CAN_INT_WARN) {
            am_kprintf("warning!");
        }

        /* �������ֵ>127,���󱻶���־��Ч */
        if(p_int_type & AM_CAN_INT_ERROR_PASSIVE) {
            am_kprintf("passive!");
        }

        /* �������ֵ>255,���߱�־��Ч */
        if(p_int_type & AM_CAN_INT_BUS_OFF) {
            am_kprintf("off!");
        }

        /* ��������־*/
        amhw_zlg237_can_clear_itstatus (p_hw_can, AMHW_ZLG237_CAN_INT_ERRIE);
    }
}

/* ������Ϣ��ӡ���� */
void can_err_printf(am_can_handle_t  handle)
{
    int_err_flag = AM_FALSE;

    am_can_int_type_t p_int_type     = 0;
    am_can_bus_err_t  p_bus_err      = 0;
    am_can_err_cnt_t  am_can_err_cnt = {0, 0};

    am_can_status_get(handle, &p_int_type , &p_bus_err);

    /* ��ʽ���� */
    if (AM_CAN_BUS_ERR_FORM & p_bus_err) {
        am_kprintf("  lasterror_code form!");
    }

    /* ������ */
    if (AM_CAN_BUS_ERR_STUFF & p_bus_err) {
        am_kprintf("  lasterror_code stuff!");
    }

    /* δ֪����     ���Դ���   ���Դ���  ��������ô���*/
    if (AM_CAN_BUS_ERR_UNKNOWN & p_bus_err) {
        am_kprintf("  lasterror_code unknown!");
    }

    /* ACK���� */
    if (AM_CAN_BUS_ERR_ACK & p_bus_err) {
        am_kprintf("  lasterror_code ack!");
    }

    /* CRC���� */
    if (AM_CAN_BUS_ERR_CRC & p_bus_err) {

    }

    /* ��ȡ�������ֵ */
    am_can_err_cnt_get (handle, &am_can_err_cnt);

    /* ��ӡ�������*/
    am_kprintf("   err_rx:%d , err_tx:%d\r\n",
               am_can_err_cnt.rx_error_cnt,
               am_can_err_cnt.tx_error_cnt);
}

/**
 * \brief �������
 */
void demo_zlg237_can_int_entry (am_can_handle_t     can_handle,
                                am_can_bps_param_t *can_btr_baud,
                                am_can_int_type_t   int_type,
                                am_can_filter_t    *p_filterbuff,
                                size_t              lenth)
{
    am_can_err_t ret;

    can_rcv_msg.id         = 0x54;
    can_rcv_msg.msglen     = 3;
    can_rcv_msg.msgdata[0] = 0x78;
    can_rcv_msg.msgdata[0] = 0xfd;
    can_rcv_msg.msgdata[0] = 0xa8;

    /* ���ò����� */
    ret = am_can_baudrate_set (can_handle, can_btr_baud);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller baudrate set ok. \r\n");
    } else {
        am_kprintf("\r\nCAN: controller baudrate set error! %d \r\n", ret);
    }

    /* �����˲��� */
    ret = am_can_filter_tab_ext_set(can_handle,p_filterbuff, lenth);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller filter tab set ok. \r\n");
    } else {
        am_kprintf("\r\nCAN: controller filter tab set error! %d \r\n", ret);
    }

    /* �����жϷ�����  */
    /* �ڶ�����������ΪNULLʱ�������ڲ�Ĭ���жϷ������� __can_zlg237_int_handle
     * �ɵ���am_can_intcb_connect���������û��жϻص�����
     */
    am_can_connect(can_handle,can_int_handle,(void *)can_handle->p_drv);

    /* CAN�ж�ʹ�ܺ��� */
    am_can_int_enable(can_handle,int_type);

    /* ����can */
    ret = am_can_start (can_handle);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller start \r\n");
    } else {
        am_kprintf("\r\nCAN: controller start error! %d \r\n", ret);
    }

    if(int_type & AM_CAN_INT_WAKE_UP)
    {
        if(am_can_sleep(can_handle) == AM_CAN_NOERROR) {
            int_sleep_flag = AM_TRUE;
        }
    }

    AM_FOREVER {

        /* �����ڵȴ�����״̬ʱ���������� */
        if(int_sleep_flag == AM_FALSE) {

            /* ���ͱ��� */
            am_can_msg_send(can_handle, &can_rcv_msg);
        } else {

            /* ���ڵȴ�����״̬����ӡ��ʾ��Ϣ��CAN��Ҫ���ܱ��ģ����ߵ��û��Ѻ���*/
            am_kprintf("\r\nCAN: sleep mode! waiting for wakeup!\r\n");
        }

        /* �����־��Ч�����ô����ӡ���� */
        if(AM_TRUE == int_err_flag) {
            can_err_printf(can_handle);
        } else {
            am_mdelay(500);
        }

    }
}
/** [src_zlg237_can_int] */

/* end of file */

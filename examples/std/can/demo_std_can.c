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
 * \brief CAN��ʾ����
 *
 * - �������裺
 *   1. ����������am_prj_params.hͷ�ļ���ʹ��
 *   - ��Ӧƽ̨��CAN�豸��(AM_DEV_XXXXX_CAN1);
 *   - AM_COM_CONSOLE;
 *   -  ��Ӧƽ̨�Ĵ����豸��(AM_DEV_XXXXX_UART1)��
 *   2. ����CAN1��������ŵ�CAN�շ������ٽ�CAN�շ����ӿ���USBCAN-II�豸������
 *   3. ��CAN��λ�������ò�����Ϊ250k��
 *   4. �򿪴��ڵ����նˣ�������115200-8-N-1.
 *
 * - ʵ������
 *   1. ��λ���������ݺ��յ����͵����ݡ�
 *   2. ���ڴ�ӡ��ص�����Ϣ��
 *
 * - ��ע��
 *   1. ���� CAN ID �� ���������� ��Ҫ���ݾ���Ӳ��ƽ̨�޸ġ�
 *   2. ��basicģʽ�²�֧����չ֡��
 *   3. zmf159 �˲�������������ʱ�����ض�����»���ֱ�׼֡����չ֡ ���ɽ���
 *      �����˲����Ĵ���ʵ�ʴ洢��ʽ�����ģ�
 *   4. ���������� 1 �� ����
 *              0 �� ������
 *
 * \par Դ����
 * \snippet demo_std_crc.c src_std_can
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-09  bzq, first implementation
 * - 1.00 19-12-18  zc,  adapt filter extern api
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_can
 * \copydoc demo_std_can.c
 */

/** [src_std_can] */
#include "ametal.h"
#include "am_can.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**\brief �˲��� */
static am_can_filter_t table[1] = {
        {
                AM_CAN_FRAME_TYPE_EXT,
                AM_CAN_FRAME_FORMAT_NOCARE,
                {0x00},
                {0x00},
        }
};

/**
 * \brief �����ж�
 */
void __can_err_sta( am_can_bus_err_t err)
{

    if (err & AM_CAN_BUS_ERR_BIT) {    /**< \brief λ���� */
        am_kprintf(("AM_CAN_BUS_ERR_BIT\n"));
    }
    if (err &AM_CAN_BUS_ERR_ACK) {     /**< \brief Ӧ����� */
        am_kprintf(("AM_CAN_BUS_ERR_ACK\n"));
    }
    if (err &AM_CAN_BUS_ERR_CRC) {     /**< \brief CRC���� */
        am_kprintf(("AM_CAN_BUS_ERR_CRC\n"));
    }
    if (err &AM_CAN_BUS_ERR_FORM) {    /**< \brief ��ʽ���� */
        am_kprintf(("AM_CAN_BUS_ERR_FORM\n"));
    }
    if (err &AM_CAN_BUS_ERR_STUFF) {   /**< \brief ������ */
        am_kprintf(("AM_CAN_BUS_ERR_STUFF\n"));
    }
}

/**
 * \brief �������
 */
void demo_std_can_entry (am_can_handle_t can_handle, am_can_bps_param_t  *can_btr_baud)
{
    am_can_err_t ret;
    uint8_t      i = 0;
    am_can_message_t    can_rcv_msg = {0};
    am_can_bus_err_t    can_bus_err_status;
    am_can_int_type_t   can_int_status;

    /* ���ò����� */
    ret = am_can_baudrate_set (can_handle, can_btr_baud);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller baudrate set ok. \r\n");
    } else {
        am_kprintf("\r\nCAN: controller baudrate set error! %d \r\n", ret);
    }

    /* �����˲��� */
    ret = am_can_filter_tab_ext_set(can_handle,
                                    table,
                                    1);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller filter tab set ok. \r\n");
    } else {
        am_kprintf("\r\nCAN: controller filter tab set error! %d \r\n", ret);
    }

    /* ����can */
    ret = am_can_start (can_handle);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller start \r\n");
    } else {
        am_kprintf("\r\nCAN: controller start error! %d \r\n", ret);
    }

    AM_FOREVER {

        ret = am_can_msg_recv (can_handle, &can_rcv_msg);

        if (can_rcv_msg.msglen) {
            am_kprintf("can recv id: 0x%x\r\n",can_rcv_msg.id);
            /* ����ӡԶ��֡ʱ�����ݻ��� */
            if ((can_rcv_msg.flags & AM_CAN_REMOTE_FLAG) != AM_CAN_REMOTE_FLAG) {
                for (i = 0; i < can_rcv_msg.msglen; i++) {
                    am_kprintf("data: 0x%x \r\n",can_rcv_msg.msgdata[i]);
                }
            }
                ret = am_can_msg_send (can_handle, &can_rcv_msg);

                if (ret == AM_CAN_NOERROR) {
                    am_kprintf(("\r\nCAN: controller rcv data ok. \r\n"));
                } else {
                    am_kprintf("\r\nCAN: controller no rcv data! \r\n");
                }

        }

        ret = am_can_status_get (can_handle, &can_int_status, &can_bus_err_status);

        am_mdelay(10);
        if (can_bus_err_status != AM_CAN_BUS_ERR_NONE) {
            __can_err_sta(can_bus_err_status);
        }
    }
}
/** [src_std_can] */

/* end of file */

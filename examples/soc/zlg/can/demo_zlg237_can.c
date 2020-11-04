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
 *   1. ����������am_prj_config.hͷ�ļ���ʹ��
 *   -  ��Ӧƽ̨�Ĵ����豸��(AM_DEV_XXXXX_UART1)��
 *   2. ����CAN1��������ŵ�CAN�շ������ٽ�CAN�շ����ӿ���USBCAN-II�豸������
 *   3. ��CAN��λ�������ò�����Ϊ50k��
 *   4. �򿪴��ڵ����նˣ�������115200-8-N-1.
 *   5. ��λ�� ����֡��ʽΪ ��չ֡  Զ��������Ҫ��(����֡��Զ��֡����) IDΪ 0x -7- ��  ��4-6 λΪ1
 *   6. ��Ҫ�޸� �����ļ�ע����λ�����͵�֡��ʽ������  �����ļ��� amh_hwconf_zlg237_can.c
 *    Ĭ�������� CAN_ID_EXT
 *               AMHW_ZLG237_CAN_FILTER_MODE_IDMASK 
 *               AMHW_ZLG237_CAN_FILTER_SCALE_32BIT
 *      �޸�֡��ʽ�����ͺ� �� ��Ҫ��ע��table������ ��ʽ�仯
 *      ����� �·�ע�� �� ZLG237�û��ֲ�17.6.4��  ��ʶ������
 * - ʵ������
 *   1. ��λ���������ݺ��յ����͵����ݡ�
 *   2. ���ڴ�ӡ��ص�����Ϣ��
 *
 *
 * \par Դ����
 * \snippet demo_zlg237_can.c src_std_can
 *
 * \internal
 * \par Modification History
 * - 19-8-12, zc, first implementation.
 * - 19-12-18     add filter table extern 
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
#include "amhw_zlg237_can.h"
#include "am_zlg237_can.h"


/**\brief �˲��� */

am_can_filter_t tab[4] = {
        {
                AM_CAN_FRAME_TYPE_EXT,
                AM_CAN_FRAME_FORMAT_DATA,
                {0x10000000},
                {0x10000000},

        },
        {
                AM_CAN_FRAME_TYPE_EXT,
                AM_CAN_FRAME_FORMAT_REMOTE,
                {0x10000001},
                {0x10000001},

        },
        {
                AM_CAN_FRAME_TYPE_STD,
                AM_CAN_FRAME_FORMAT_DATA,
                {0x01},
                {0x01},

        },
        {
                AM_CAN_FRAME_TYPE_STD,
                AM_CAN_FRAME_FORMAT_REMOTE,
                {0x02},
                {0x02},

        },
};

am_can_filter_t get_tab[4]={0};

/**
 * \brief �����ж�
 */
static void __can_err_sta( am_can_bus_err_t err)
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
void demo_zlg237_can_entry (am_can_handle_t      can_handle,
                            am_can_bps_param_t  *can_btr_baud)
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
    ret = am_can_filter_tab_ext_set(can_handle,tab,
                                    sizeof(tab)/sizeof(am_can_filter_t));

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller filter table set ok. \r\n");
    } else {
        am_kprintf("\r\nCAN: controller filter table set error! %d \r\n", ret);
    }

    size_t len = 0;
    ret = am_can_filter_tab_ext_get(can_handle,get_tab,&len);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller filter table get ok. \r\n");
    } else {
        am_kprintf("\r\nCAN: controller filter table get error! %d \r\n", ret);
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

        ret = am_can_status_get (can_handle,
                                &can_int_status,
                                &can_bus_err_status);

        am_mdelay(10);
        if (can_bus_err_status != AM_CAN_BUS_ERR_NONE) {
            __can_err_sta(can_bus_err_status);
        }
    }
}
/** [src_zlg237_can] */

/* end of file */

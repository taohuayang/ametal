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
 *   6. ��Ҫ�޸� �����ļ�ע����λ�����͵�֡��ʽ������  �����ļ��� amh_hwconf_hk32f103rbt6_can.c
 *    Ĭ�������� CAN_ID_EXT
 *               AMHW_HK32F103RBT6_CAN_FILTER_MODE_IDMASK 
 *               AMHW_HK32F103RBT6_CAN_FILTER_SCALE_32BIT
 *      �޸�֡��ʽ�����ͺ� �� ��Ҫ��ע��table������ ��ʽ�仯
 *      ����� �·�ע�� �� HK32F103RBT6�û��ֲ�17.6.4��  ��ʶ������
 * - ʵ������
 *   1. ��λ���������ݺ��յ����͵����ݡ�
 *   2. ���ڴ�ӡ��ص�����Ϣ��
 *
 *
 * \par Դ����
 * \snippet demo_hk32f103rbt6_can.c src_std_can
 *
 * \internal
 * \par Modification History
 * - 19-8-12, zc, first implementation.
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
#include "amhw_hk32f103rbt6_can.h"
#include "am_hk32f103rbt6_can.h"

/**
 *  \brief 2��16λ������  ��ʶ������λģʽ
 *  ����am_hwconf_hk32f103rbt6_can.c�е�__g_can_filter����Ϊ
 *  AMHW_HK32F103RBT6_CAN_FILTER_MODE_IDMASK  
 *  AMHW_HK32F103RBT6_CAN_FILTER_SCALE_16BIT
 *
 *  �˲���table˵����
 *    �ڴ�ģʽ��  table�а���2�� (ID + ID_MASK)
 *    ��ʱIDΪ     EXID[17:15] STID[10:3] STID[2:0] (EXT_ID)
 *        ����     STID[10:3] STID[2:0](STD_ID)
 *    
 *    ֡����                                       EXT_ID                           STD_ID
 *    table[0] ID_H:      EXID[17:15] STID[10:8]           STID[10:8]
 *    table[1] ID_L:      STID[7:0]                        STID[7:0]
 *
 *    ��ʱMASKΪ�� STID[10:3] STID[2:0] RTR IDR EXID[17:15]
 *    ֡����                                       EXT_ID                            STD_ID
 *    table[2] MASK_H:    STID[10:3]                        STID[10:3]
 *    table[3] MASK_L:    STID[2:0] RTR IDE EXID[17:15]    (STID[2:0] 
 *                                                          RTR IDE EXID[17:15])
 *                                               (STD_ID ģʽ�� EXID[17:15] ȫΪ 0)
 *
 *            table[4]-table[7] Ϊ��һ��
 *  ע�� ��
 *      ������ ��չ��ʶ��ģʽʱ��������Ϊ����ֻ��������EXID 
        ����������STID��λ�� �������ݷ��޷�����
 *
 *      ������Ϊ��׼��ʶ��ģʽʱ��������λֻ��������STIDλ��
 *      ����������EXID��  ���������޷�����
 *
 *
 * �������ļ����޸�֡���� Ϊ  CAN_ID_EXT
 * static uint8_t table[8] = {0x28, 0x00, 0x00,  0x07,  0x28, 0x00, 0x00, 0x07};
 *      �� ID_H 0X28 ID_L  0X00  ��ID��ʵ��ֵΪ 0x28000
 *      ������λ������ʱ��������ID(0x28,0x00)Ϊ   0x28000 (��Ϊ18λ����չID)
 *      ����0x7 Ϊ ��չ��ʶ������ STID[17:15] ÿһλ����ƥ��
 *      ��λ������IDλ 28xxx ��ʶ��Ϊ��չ  Զ��������Ҫ��
 *
 * �������ļ����޸�֡����Ϊ CAN_IS_STD
 * static uint8_t table[8] = {0x00, 0x01, 0x00,  0x20,  0x00, 0x02, 0x00, 0x40};
 *       ���˲����  ����Ϊ �������ID�ĵ�0λ ��� 1 λ Ϊ 1 ���ɴ���FIFO��
 *       ��λ����������Ϊ   ��ʶ��Ϊ��׼֡ Զ��������Ҫ��
 *    STID[10:3] STID[2:0] RTR IDR EXID[17:15]
 * 
 */

/**
 * \brief 4��16λ ��ʶ���б��˲���
 * ����am_hwconf_hk32f103rbt6_can.c�е�__g_can_filter����Ϊ
 * AMHW_HK32F103RBT6_CAN_FILTER_MODE_IDLIST  
 * AMHW_HK32F103RBT6_CAN_FILTER_SCALE_16BIT
 *
 *  �˲���table˵����
 *    �ڴ�ģʽ��  table�а�4�� (ID)
 *    ��ʱIDΪ     EXID[17:15] STID[10:3] STID[2:0] (EXT_ID)
 *        ����     STID[10:3] STID[2:0](STD_ID)
 *    
 *    ֡����                                       EXT_ID                           STD_ID
 *    table[0] ID_H:      EXID[17:15] STID[10:8]           STID[10:8]
 *    table[1] ID_L:      STID[7:0]                        STID[7:0]
 * 
 *    ÿ����Ԫ��Ϊһ��ID��������
 * 
 * ע��: ����չģʽ��ֻ�ܶ���չID��EID[17:15] �������� ����λ��������
 *                                         �����������ñ�׼ID��ֵ��
 *       �ڱ�׼ģʽ��ֻ�ܶԱ�׼ID�Ľ�������  ����������չID��ֵ
 *
 * �������ļ����޸�֡���� Ϊ  CAN_ID_EXT
 * static uint8_t table[8] = {0x08, 0x00, 0x18, 0x00, 0x20, 0x00, 0x30, 0x00};
 *  ��table�ɹ��˵�IDΪ       0x8xxx      0x18xxx     0x2xxxx     0x3xxxx
 *  ֡ģʽΪ  ��չ֡  Զ��֡������Ҫ�������ļ������õ�ƥ��
 *
 * ����չ֡ģʽ�±�������չIDΪ����IDֵ ��EXID[17:15] ������һλΪ 1
 *
 * �������ļ����޸�֡����Ϊ CAN_IS_STD
 *                             
 * static uint8_t table[16] = {0x00, 0x01, 0x00, 0X02, 0x00, 0x03, 0x00, 0x04,
 *                             0x00, 0x05, 0x00, 0X06, 0x00, 0x07, 0x00, 0x08};
 *  ��table����IDΪ           0x1 0x2 0x3 0x4 0x5 0x6 0x7 0x8
 *  ֡ģʽΪ  ��׼֡  Զ��֡������Ҫ�������ļ������õ�ƥ��
 *
 *
 */

/**
 *  \brief 1��32λ������  ��ʶ������
 *  ����am_hwconf_hk32f103rbt6_can.c�е�__g_can_filter����Ϊ
 *  AMHW_HK32F103RBT6_CAN_FILTER_MODE_IDMASK 
 *  AMHW_HK32F103RBT6_CAN_FILTER_SCALE_32BIT
 * 
 *  �����ע֡��ʽ���������ú�ID�����������Ƿ�ƥ��
 *
 *   �˲���table˵��
 *   table�а��� 1 ��(ID + ID_MASK)
 *   ��ʱIDΪ��STID[10:3] STID[2:0] EXID[17:13] EXID[12:5] EXID[4:0] (EXID[28:0])
 *   ����      STID[10:3] STID[2:0]
 *     ֡����                                                   EXT_ID                     STD_ID
 *   table[0] ID_H :            EXID[28:24]                     
 *   table[1] ID_H :            EXID[23:16]
 *   table[2] ID_L :            EXID[15:8]                 STD_ID[10:8]
 *   table[3] ID_L :            EXID[7:0]                  STD_ID[7:0]
 *
 *   ��ʱID����Ϊ��STID[10:3] STID[2:0] EXID[17:13] EXID[12:5] EXID[4:0] IDE RTR  
 *   ����          STID[10:3] STID[2:0] IDE RTR
 *     ֡����                                                   EXT_ID                     STD_ID
 *    table[4] MASK_H :         EXID[28:22]                     
 *    table[5] MASK_H :         EXID[21:14]
 *    table[6] MASK_L :         EXID[13:6]                 STD_ID[10:6]
 *    table[7] MASK_L :         EXID[5:0]  IDE RTR         STD_ID[5:0]  IDE RTR
 * 
 *    IDE(1bit) ֡��������λ 
 *             0 : ������֡����   
 *             1 ��֡����ƥ�� �������ļ�(am_hwconf_hk32f103rbt6_can.c)��һ�²Ž������� 
 *
 *    RTR(1bit) ֡��ʽ����λ
 *             0 : ������֡��ʽ
 *             1 ��֡��ʽƥ�� �������ļ�(am_hwconf_hk32f103rbt6_can.c)��һ�²Ž������� 
 *    ע�⣺ ��RTR����Ϊ���ģ� ID��������Ϊ����ʱ������λ�����õ�֡����Ҳ������
 *           �����ļ��е�һ�²Ž���
 *
 *  ����ID Ϊ 0x70                         0b1 1100 00
 *   ���������ù���ʱ Ϊ table[7]   0x01 0xc0  0b1 1100 0000 (�����λΪ IDE RTR)
 *   MASK :    EXIT[28:0] IDE RTR
 *         ����  STID[10:0] IDE RTR
 *
 * �������ļ����޸�Ϊ CAN_ID_EXT
 *                            ID_H  ID_H  ID_L  ID_L MASK_H MASK_H MASK_L MASK_L
 * static uint8_t table[8] = {0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x01, 0xc0};
 * ��λ������IDΪ 0x x7x  ֡��ʽΪ ��չ֡ Զ��������Ҫ��
 *
 * �������ļ����޸�Ϊ CAN_IS_STD
 *                            ID_H  ID_H  ID_L  ID_L MASK_H MASK_H MASK_L MASK_L
 * static uint8_t table[8] = {0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x01, 0xc0};
 * ��λ������IDΪ 0x x7x  ֡��ʽΪ ��׼֡  Զ��������Ҫ��
 *
 *
 */


/**
 *  \brief 2��32λ������  ��ʶ���б�
 *  ����am_hwconf_hk32f103rbt6_can.c�е�__g_can_filter����Ϊ
 *  AMHW_HK32F103RBT6_CAN_FILTER_MODE_IDLIST
 *  AMHW_HK32F103RBT6_CAN_FILTER_SCALE_32BIT
 *   
 *  �˲���table˵����
 *   table�а��� 2 �� (ID):
 *   ��ʱIDΪ�� STID[10:3] STID[2:0] EXID[17:13] EXID[12:5] EXID[4:0] 
 *   ����       STID[10:3] STID[2:0]
 *      ֡����                                           EXT_ID                       STD_ID
 *  table[0] ID_H :           EXID[28:24]                     
 *  table[1] ID_H :           EXID[23:16]
 *  table[2] ID_L :           EXID[15:8]                   STD_ID[10:8]
 *  table[3] ID_L :           EXID[7:0]                    STD_ID[7:0]
 *
 *  table[4] - table[7] ��������
 *
 *
 * static uint8_t table[16] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02,
 *                             0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04};
 *
 * ��table����IDΪ  0x1 0x2 0x3 0x4  ֡���ͺ�֡��ʽ��������õĽ���ƥ��
 *
 *
 *
 */

/**\brief �˲��� */
 static uint8_t table[8] = {0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x01, 0xc0};

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
void demo_hk32f103rbt6_can_entry (am_can_handle_t      can_handle,
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
    ret = am_can_filter_tab_set(can_handle,table,
                                sizeof(table)/sizeof(uint8_t));

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

        if (can_rcv_msg.msglen  || can_rcv_msg.flags || can_rcv_msg.id) {
            am_kprintf("can recv id: 0x%x\r\n",can_rcv_msg.id);
            for (i = 0; i < can_rcv_msg.msglen; i++) {
                am_kprintf("data: 0x%x \r\n",can_rcv_msg.msgdata[i]);
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
/** [src_hk32f103rbt6_can] */

/* end of file */

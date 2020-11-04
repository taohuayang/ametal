/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief amks16rfid8 �������̺����������������ֻ����fm175xx���demo��
 *  ����demo�����am116_core�е�demo
 * \sa demo_amks16rfid8_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-03  htf, first implementation.
 * \endinternal
 */

/**
 * \brief CPU����������
 */
void demo_amks16rfid8_fm175xx_cpu_card (void);

/**
 * \brief LPCDģʽ
 */
void demo_amks16rfid8_fm175xx_lpcd_read_id (void);

/**
 * \brief 8���߶�ȡA�࿨��������
 */
void demo_amks16rfid8_fm175xx_picca_8ante_read_id (void);

/**
 * \brief A�࿨���д����
 */
void demo_amks16rfid8_fm175xx_picca_block (void);

/**
 * \brief A�࿨�����߿�����
 */
void demo_amks16rfid8_fm175xx_picca_halt (void);

/**
 * \brief A�࿨�������ͺͿ�������
 */
void demo_amks16rfid8_fm175xx_picca_read_id (void);

/**
 * \brief A�࿨ֵ��������
 */
void demo_amks16rfid8_fm175xx_picca_val_operate (void);

/**
 * \brief LPCDģʽ  ���MCU�͹���ģʽ
 */
void demo_amks16rfid8_dr_fm175xx_lpcd_vlps_read_id (void);


void demo_amks16rfid8_uartcmd_handle_entry (void);

/**
 * \uartcmd 8���߶�ȡ��ƬID
 */
void demo_amks16rfid8_uartcmd_picca_8ante_read_id_entry (void);

/**
 * \uartcmd �Զ�����������
 */
void demo_amks16rfid8_uartcmd_picca_auto_detect_entry (void);

/**
 * \brief uartcmd ��ȡдultralight��
 */
void demo_amks16rfid8_uartcmd_ultralight_write_block_entry (void);

/* end of file */

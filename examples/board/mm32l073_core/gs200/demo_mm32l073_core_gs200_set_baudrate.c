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
 * \brief GS200 ģ���л����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��Ƭ���л����������� GS200 ģ�飻
 *   2. ����л��ɹ���ͨ�����ڴ�ӡ��ǰ�Ĳ����ʣ���������ƶ������ɹ�������ƶ������л� LED1 ״̬����
 *      ���� LED0 �� 100 ms �ļ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOB_1 ���ƣ�LED1 ��Ҫ�̽� J10 ����ñ�����ܱ� PIOB_2 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    3. ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��
 *       AM_CFG_KEY_ENABLE �� AM_CFG_SOFTIMER_ENABLE ����Ϊ 1������Щ��
 *       �Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *    4. GS200 ģ���� MCU �Ĵ��� 2 ͨ�š�
 *
 *
 * \par Դ����
 * \snippet demo_mm32l073_core_gs200_set_baudrate.c src_mm32l073_core_gs200_set_baudrate
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-23  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l073_core_gs200_set_baudrate
 * \copydoc demo_mm32l073_core_gs200_set_baudrate.c
 */

/** [src_mm32l073_core_mm32l073_set_baudrate] */
#include "ametal.h"
#include "am_gs200.h"
#include "am_hwconf_gs200.h"
#include "demo_components_entries.h"
#include "demo_mm32l073_core_entries.h"

void demo_mm32l073_core_gs200_set_baudrate_entry()
{
    am_gs200_handle_t  handle = am_gs200_inst_init();

    demo_gs200_baudrate_entry(handle, AM_GS200_BAUDRATE_115200);
}


/** [src_mm32l073_core_gs200_set_baudrate] */

/* end of file */


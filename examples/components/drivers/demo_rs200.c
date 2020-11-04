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
 * \brief RS200 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� RS200 ���ӵ� UART �ӿڡ�
 *
 * - ʵ������
 *   ���ڴ�ӡ����״̬�����
 *
 * \par Դ����
 * \snippet demo_rs200.c src_rs200
 *
 * \internal
 * \par Modification history
 * - 1.00  19-12-26  rz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_rs200
 * \copydoc demo_rs200.c
 */

/** [src_rs200] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_rs200.h"

/**
 * \brief �������
 */
void demo_rs200_entry (am_rs200_handle_t handle)
{
    uint8_t data[5];
    
    AM_FOREVER {
        
        if (am_rs200_recv (handle, data, 5) == 5) {
            AM_DBG_INFO("rs200 data: 0x%x 0x%x 0x%x 0x%x 0x%x\r\n\r\n",
                        data[0], data[1],data[2], data[3], data[4]);
        }
    }
}
/** [src_rs200] */

/* end of file */

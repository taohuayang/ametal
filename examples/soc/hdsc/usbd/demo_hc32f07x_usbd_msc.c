/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USBģ��U�����̣�ͨ��driver��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. ��USB�����ϵ��Ժ����س���
 *   2. �ڵ����ϻ���ʾ��һ���̷���
 *
 * - ʵ������
 *   1. ���̷������Կ���������һ��README.TXT�ļ���
 *   2. ������U���������϶��ļ�,���ڻ���ʾ���϶��ļ�����Ϣ��
 *
 * \note
 *
 *
 *
 * \par Դ����
 * \snippet demo_usbd_msc.c src_usbd_msc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-01-15  adw, first implementation
 * \endinternal
 */
/**
 * \brief �������
 */
#include "ametal.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_usbd_msc.h"
#include "am_rngbuf.h"
#include "demo_hc32f07x_entries.h"

#define   __USND_MSC_REC_BUFFER_SIZE    1024

static void __rec_buffer_cb(void *p_arg, uint8_t *p_buff, uint16_t len)
{
	//����д�� flash����
}

/**
 * \brief �������
 */
void demo_usbd_msc_entry (void* p_handle)
{

    am_usbd_msc_handle handle = p_handle;
    am_usbd_msc_recv_callback(handle, __rec_buffer_cb, (void *)handle);

    /* ��λ����ʱһ��ʱ�䣬ģ��USB�豸�γ��Ķ��� */
    am_mdelay(3000);

    while (1) {


    }
}
/**
 * \addtogroup demo_if_usbd_msc
 * \copydoc demo_usbd_msc.c
 */

/** [src_usbd_msc] */

/* end of file */

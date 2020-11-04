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
 * \brief USB printer_counter ����
 *
 * - ʵ������
 * 1.��USB����˵����PC����
 * 2.��������¼�����̣��ȴ�3��(��������3����ʱ��Ϊ��ģ��USB�γ�����)��3���pc������ʾ��װ������
 *   ����Ĭ�ϰ�װwindows ͨ�ô�ӡ����������ϸ�ɿ�������װ˵���ĵ�������û���Ҫ���Լ����������������и��¡�
 * 3.�ڵ��������½�һ��txt�ļ��������ַ���,֮�����ļ���ӡ�����ڴ����п��Կ����ļ�����.
 *
 * \par Դ����
 * \snippet demo_usbd_printer.c src_usbd_printer
 *
 * \internal
 * \par Modification History
 * - 1.00 19-1-09  adw, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_usbd_printer
 * \copydoc demo_usbd_printer.c
 */

/** [src_usbd_printer] */
#include "ametal.h"
#include "string.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_rngbuf.h"
#include "am_vdebug.h"
#include "am_softimer.h"
#include "am_zmf159_usbd.h"
#include "am_usbd_printer.h"
#include "am_zmf159_inst_init.h"

#define __RNG_BUFF_SIZE    512                   /**< ��������С. */

static char __g_rng_buff[__RNG_BUFF_SIZE] = {0}; /**< \brief ���λ�����buff*/

static char __g_buff[__RNG_BUFF_SIZE]     = {0}; /**< \brief ���ݶ�ȡbuff*/

static struct am_rngbuf __g_rngbuff;             /**< \brief ����һ�����λ�����ʵ��*/

/**
 * \brief ��ӡ�������ж�����ص�����
 *
 * param[in] p_arg  : �ص���������
 * param[in] p_data : ��������buff
 * param[in] len    : �������ݵ���Ч���ȣ���������
 */
static void __printer_recv_callback(void *p_arg, uint8_t *p_data, uint8_t len)
{
    am_rngbuf_put(&__g_rngbuff, (char *)p_data, len); /* ��价�λ�����*/
}

/**
 * \brief ��ӡ�������ж�����ص�����
 *
 * param[in] p_arg  : �ص���������
 */
static void __printer_send_callback(void *p_arg)
{
    //�ú���Ϊ��ӡ����������,������������USB device ��������(����Ķ˵�����)ʱ���ͻ����ú���
    uint8_t data[] = "ZLG printer demo test string";
    am_usbd_printer_handle handle = (am_usbd_printer_handle)p_arg;

    am_usbd_printer_send(handle, AM_USBD_PRINTER_BULK_EP_IN, data, sizeof(data));
}

/**
 * \brief �������
 */
void demo_zmf159_usbd_printer_entry (void)
{
    uint32_t key = 0;
    am_kprintf("printer demo\n");

    am_mdelay(3000);                               /* ģ��USB�豸�γ��Ķ��� */
    am_usbd_printer_handle handle = NULL;

    /* ��ʼ�����λ�����*/
    am_rngbuf_init(&__g_rngbuff, __g_rng_buff, __RNG_BUFF_SIZE);

    handle = am_zmf159_usbd_printer_inst_init();    /* usb��ӡ��ʵ����ʼ��*/

    /* ���������ʱ�����պͷ�������ص�����*/
    am_usbd_printer_recv_request_callback(handle, __printer_recv_callback, handle);
    am_usbd_printer_send_request_callback(handle, __printer_send_callback, handle);


    while (1) {
        /* ������λ�������Ϊ�գ���������*/
        if (!am_rngbuf_isempty(&__g_rngbuff)) {
            key = am_int_cpu_lock();
            am_rngbuf_get(&__g_rngbuff, __g_buff, __RNG_BUFF_SIZE);

            am_kprintf("%s", __g_buff);

            memset(__g_buff, 0, __RNG_BUFF_SIZE);
            am_int_cpu_unlock(key);
        }
    }
}
/** [src_usbd_printer] */

/* end of file */

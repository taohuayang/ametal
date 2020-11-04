/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB Vcom ����
 *
 * - ʵ������
 * 1. ��������PC����USB���������ӡ�
 * 2. PC���ô�������(xcom)�����ӷ������ݣ���������յ����ݣ���ش���recv success��.
 *
 * \par Դ����
 * \snippet demo_usbd_vcom.c src_usbd_vcom
 *
 * \internal
 * \par Modification History
 * - 1.00 19-1-09  adw, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_usbd_vcom
 * \copydoc demo_usbd_vcom.c
 */

/** [src_usbd_vcom] */
#include "ametal.h"
#include "string.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_rngbuf.h"
#include "am_vdebug.h"
#include "am_softimer.h"
#include "am_zmf159_usbd.h"
#include "am_zmf159_inst_init.h"
#include "am_usbd_cdc_vcom.h"

#define __RNG_BUFF_SIZE    256                   /**< ��������С. */

static char __g_rng_buff[__RNG_BUFF_SIZE] = {0}; /**< \brief ���λ�����buff*/

static char __g_buff[__RNG_BUFF_SIZE]     = {0}; /**< \brief ���ݶ�ȡbuff*/

static struct am_rngbuf __g_rngbuff;             /**< \brief ����һ�����λ�����ʵ��*/


static void __test_function(void *p_arg, uint8_t *p_buffer, uint8_t len)
{
    am_rngbuf_put(&__g_rngbuff, (char *)p_buffer, len); /* ��价�λ�����*/
}

/**
 * \brief �������
 */
void demo_zmf159_usbd_vcom_entry (void)
{
    uint32_t key = 0;
    am_kprintf("zmf159 vcom demo \r\n");

    am_usbd_cdc_vcom_handle handle = am_zmf159_usbd_vcom_inst_init();

    // ���ô��ڽ����ж�
    am_usbd_cdc_vcom_recv_cb(handle, __test_function, NULL);

    am_rngbuf_init(&__g_rngbuff, __g_rng_buff, __RNG_BUFF_SIZE);

    for (;;){

        /* ������λ�������Ϊ�գ���������*/
        if (!am_rngbuf_isempty(&__g_rngbuff)) {
            key = am_int_cpu_lock();
            am_rngbuf_get(&__g_rngbuff, __g_buff, __RNG_BUFF_SIZE);

            am_kprintf("%s", __g_buff);

            // �����ڷ����� ���ֻ�ܷ�64 �ֽڣ��������64�ֽ����ϣ�����ֶη���
            am_usbd_cdc_vcom_send(handle,
                                 (uint8_t *)"recv success\r\n",
								 sizeof("recv success\r\n"));

            memset(__g_buff, 0, __RNG_BUFF_SIZE);
            am_int_cpu_unlock(key);
        }
    }

}
/** [src_usbd_vcom] */

/* end of file */

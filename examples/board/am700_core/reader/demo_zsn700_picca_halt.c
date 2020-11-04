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
 * \brief zsn700_readerʹ�ò�ͬ�ķ�����ȡ��Ƭ��Ϣ��ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. �����Ƭ֧��haltָ���ÿ�����½����������߸�Ӧ���󣬴���ֻ�ܴ�ӡ�����ο�Ƭ��Ϣ��
 *   2. �����Ƭ��֧��haltָ��򽫿��������߸�Ӧ���󣬴������������ϵĴ�ӡ����Ƭ��Ϣ��
 *
 * \par Դ����
 * \snippet demo_zsn700_reader_picca_halt.c src_zsn700_reader_picca_halt
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-02  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_reader_picca_halt
 * \copydoc demo_zsn700_reader_picca_halt.c
 */

/** [src_zsn700_reader_picca_halt] */
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_zsn700_reader.h"
#include "am_zsn700_reader_reg.h"
#include "am_hwconf_zsn700_reader.h"

/**
 * \brief A�࿨�����߿�����
 */
void demo_zsn700_reader_picca_halt (void)
{
    uint8_t tag_type[2] = { 0 };      /* ATQA */
    uint8_t uid[10]     = { 0 };      /* UID */
    uint8_t uid_real_len = 0;         /* ���յ���UID�ĳ��� */
    uint8_t sak[3]      = { 0 };      /* SAK */
    uint8_t i;
    am_zsn700_reader_handle_t handle = am_zsn700_reader_inst_init();
    while (1) {

        /* Ѱ����δ���ߣ�halt���Ŀ� */
        am_kprintf("read idle...\n");
        if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_active\
                                         (handle,
                                          AM_ZSN700_READER_PICCA_REQ_IDLE,
                                          tag_type,
                                          uid,
                                          &uid_real_len,
                                          sak)) {
            am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

            am_kprintf("UID  :");
            for (i = 0; i < uid_real_len; i++) {
                am_kprintf("%02x ", uid[i]);
            }
            am_kprintf("\n");
            am_kprintf("SAK  :%02x\n\n", sak[0]);

            am_zsn700_reader_picca_halt(handle);  /* �ÿ�Ƭ���� */
            am_kprintf("halt\n");
            am_kprintf("read halt...\n");
            /* �����еĿ����ܶ������ߵĿ��� */
            if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_active\
                                             (handle,
                                              AM_ZSN700_READER_PICCA_REQ_ALL,
                                              tag_type,
                                              uid,
                                              &uid_real_len,
                                              sak)) {

                am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

                am_kprintf("UID  :");
                for (i = 0; i < uid_real_len; i++) {
                    am_kprintf("%02x ", uid[i]);
                }
                am_kprintf("\n");
                am_kprintf("SAK  :%02x\n\n", sak[0]);
            }
        }
        am_mdelay(500);
    }
}

/** [src_zsn700_reader_picca_halt] */

/* end of file */

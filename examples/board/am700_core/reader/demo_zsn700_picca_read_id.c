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
 * \brief ZSN700 ����������
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����

 *
 * \par Դ����
 * \snippet demo_zsn700_reader_read_id.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-02  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_reader_read_id
 * \copydoc demo_zsn700_reader_read_id.c
 */

/** [src_std_led] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_zsn700_reader.h"
#include "demo_std_entries.h"
#include "demo_am700_core_entries.h"
#include "am_hwconf_zsn700_reader.h"

/**
 * \brief A�࿨�������ͺͿ�������
 */
void demo_zsn700_reader_picca_read_id (void)
{
    uint8_t              tag_type[2]  = { 0 };      /* ATQA */
    uint8_t              uid[10]      = { 0 };      /* UID */
    uint8_t              uid_real_len =   0;         /* ���յ���UID�ĳ��� */
    uint8_t              sak[3]       = { 0 };      /* SAK */

    am_zsn700_reader_handle_t handle = am_zsn700_reader_inst_init();
    while (1) {
        int i ;
        if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_active\
                                                  (handle,
                                                    AM_ZSN700_READER_PICCA_REQ_IDLE,
                                                    tag_type,
                                                    uid,
                                                   &uid_real_len,
                                                    sak)) {
            am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

            /* ��ӡUID */
            am_kprintf("UID  :");
            for (i = 0; i < uid_real_len; i++) {
                am_kprintf("%02x ", uid[i]);
            }
            am_kprintf("\n");

            /* ��ӡSAK */
            am_kprintf("SAK  :");
            for (i = 4; i <= uid_real_len; i+=3) {
                am_kprintf("%02x ", sak[(i - 4) / 3]);
            }
            am_kprintf("\n\n");
        }
    }
}
/** [src_std_led] */

/* end of file */

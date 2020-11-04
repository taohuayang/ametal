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
 *   3. ��CPU���������߸�Ӧ����

 *
 * \par Դ����
 * \snippet demo_zsn700_reader_read_cpu_card.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-02  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_reader_read_cpu_card
 * \copydoc demo_zsn700_reader_read_cpu_card.c
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
 * \brief CPU���������ͺͿ�������
 */
void demo_zsn700_reader_picca_read_cpu_card (void)
{
    uint8_t tag_type[2]  = { 0 };         /* ATQA */
    uint8_t uid[10]      = { 0 };         /* UID */
    uint8_t uid_real_len =   0;           /* ���յ���UID�ĳ��� */
    uint8_t sak[3]       = { 0 };         /* SAK */
    uint8_t i, j;

    /* cpu������ʱ�õ����²��� */
    uint8_t  cid           = 0x00;        /* FSDI/CID */
    uint8_t  ats[20]       = { 0 };       /* ���RATSָ���ATS��Ӧ */
    uint8_t  sellect_MF[7] = {0x00 ,0xA4 ,0x00 ,0x00 ,0x02 ,0x3F ,0x00};  /* ѡ�����ļ����� */
    uint32_t ats_nbytes    =   0;          /* ATS��Ӧ���ݵĳ��� */
    uint8_t  rbuf[200]     = { 0 };        /* �ļ�����ʱ���������ݽ��ջ����� */
    uint32_t r_nbyte       =   0;          /* ÿ�ν����ļ�ʱ�����յ������ݳ��� */

    am_zsn700_reader_handle_t handle = am_zsn700_reader_inst_init();
    while (1) {

        if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_active\
                                                  (handle,
                                                    AM_ZSN700_READER_PICCA_REQ_IDLE,
                                                    tag_type,
                                                    uid,
                                                   &uid_real_len,
                                                    sak)) {
            am_kprintf("UID : ");
            for (i = 0; i < uid_real_len; i++) {
                am_kprintf("%02x ", uid[i]);
            }
            am_kprintf("\r\n");

            if(AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_rats_get(
                                            handle,
                                            cid,
                                            ats,
                                            20,
                                            &ats_nbytes
                                                )) {
                 am_kprintf("ATS data: ");
                 for (j = 0; j < ats_nbytes; j++) {
                     am_kprintf(" %02x ",ats[j]);
                 }
                 am_kprintf("\r\n");

                 if(AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_transfer(
                                                 handle,
                                                 sellect_MF,
                                                 7,   /* ����ΪCOSָ��ĳ��ȣ��˴�Ϊ��ѡ�����ļ�00 A4 00 00 02 3F 00������ĳ���*/
                                                 rbuf,
                                                 200,
                                                 &r_nbyte )) {

                     am_kprintf("send data : ");
                     for (j = 0; j < 7; j++) {
                         am_kprintf(" %02x ",sellect_MF[j]);
                     }
                     am_kprintf("\r\n");

                     am_kprintf("return data : ");
                     for (j = 0; j < r_nbyte; j++) {
                         am_kprintf(" %02x ",rbuf[j]);
                     }
                     am_kprintf("\r\n");
                 }
                 else {
                     am_kprintf("sellect_MF err!");
                 }
             }
             else {
                 am_kprintf("RATS err!\r\n");
             }
             am_kprintf("\r\n\r\n\r\n\r\n");
        }
    }
}
/** [src_std_led] */

/* end of file */

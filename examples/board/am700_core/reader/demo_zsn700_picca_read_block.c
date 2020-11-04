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
 * \brief zsn700_reader�������ݣ�ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ������ԿA�Կ�Ƭ�Ŀ�2������֤�������֤��ͨ�����ӡkey A authent failed��
 *   2. �����֤�ɹ������ȡ��0��������Ƭ���кţ�����3��������ԿA����ȡ���Ʋ��ֺ���ԿB������4���Ϳ�2
 *      ����ͬһ��������������ӡ������
 *
 * - ע�⣺
 *   1. ÿ����������4���飬���е�0����2����Ϊ���ݿ飬��3����Ϊ���ƿ顣��֤��ʵ�Ƕ��������Եģ����Ǹ�
 *      am_zsn700_reader_picca_m1_authent()������������һ������Ϊ���ַ����˸ú���������
 *      ��ʵ����֤����Ŀ����ڵ���������֤�ɹ������Ը��ݿ��ƿ��еĿ���Ȩ�޶Ա��������еĿ���ж�д��
 *   2. ��0�е������ǿ�Ƭ���кţ��ÿ�ֻ����
 *   3. ��3λ���ƿ飬��Ȼ���������A��ԿΪȫF�����Ƕ�ȡ������A��ԿȴΪȫ0����ΪA��Կ���κ�����¶�û��
 *      ����Ȩ�ޡ�
 *   4. ��4����֤�Ŀ�2����ͬһ����������˶������������ǲ���ȷ�ģ����ǶԿ�4���ڵ�����������֤��
 *
 * \par Դ����
 * \snippet demo_zsn700_reader_picca_read_block.c src_zsn700_reader_picca_read_block
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-21  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_reader_picca_read_block
 * \copydoc demo_zsn700_reader_picca_read_block.c
 */

/** [src_zsn700_reader_picca_read_block] */
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_zsn700_reader.h"
#include "am_zsn700_reader_reg.h"
#include "am_hwconf_zsn700_reader.h"
 
/**
 * \brief A�࿨��������
 */
void demo_zsn700_reader_picca_read_block (void)
{
    uint8_t tag_type[2]  = { 0 };      /* ATQA */
    uint8_t uid[10]      = { 0 };      /* UID */
    uint8_t uid_real_len =   0;        /* ���յ���UID�ĳ��� */
    uint8_t sak[1]       = { 0 };      /* SAK */
    uint8_t keya[6]      = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};  /* ��֤��ԿA */
    uint8_t buff[16]     = { 0 };      /* ���ڴ洢�����ݵĻ����� */
    uint8_t i;
    am_zsn700_reader_handle_t handle = am_zsn700_reader_inst_init();
    while (1) {

        /* Ѱ����δ���ߣ�halt���Ŀ� */
        if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_active\
                                         (handle,
                                          AM_ZSN700_READER_PICCA_REQ_IDLE,
                                          tag_type,
                                          uid,
                                          &uid_real_len,
                                          sak)) {
            am_kprintf("actived\n");

            /* ��֤A��Կ */
            if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_authent\
                    (handle,
                     AM_ZSN700_READER_IC_KEY_TYPE_A,
                     uid,
                     keya,
                     2)) {     /* ��֤���ǿ�2 */

                /* �������� */
                am_zsn700_reader_picca_read(handle, 0, buff); /* ��ȡ��0 */
                am_kprintf("block0: ");
                for (i = 0; i < 16; i++) {
                    am_kprintf("%02x ", buff[i]);
                }
                am_kprintf("\n");

                am_zsn700_reader_picca_read(handle, 3, buff); /* ��ȡ��3 */
                am_kprintf("block3: ");
                for (i = 0; i < 16; i++) {
                    am_kprintf("%02x ", buff[i]);
                }
                am_kprintf("\n");

                am_zsn700_reader_picca_authent(handle,
                                               AM_ZSN700_READER_IC_KEY_TYPE_A,
                                               uid,
                                               keya,
                                               4);

                am_zsn700_reader_picca_read(handle, 4, buff); /* ��ȡ��4 */
                am_kprintf("block4: ");
                for (i = 0; i < 16; i++) {
                    am_kprintf("%02x ", buff[i]);
                }
                am_kprintf("\n\n");
            } else {
                am_kprintf("key A authent failed\n\n");
            }
        }
        am_mdelay(200);
    }
}

/** [src_zsn700_reader_picca_read_block] */

/* end of file */

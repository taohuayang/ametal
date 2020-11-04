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
 * \brief zsn700_readerд�����ݣ�ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ������ԿA�Կ�Ƭָ���Ŀ������֤�������֤��ͨ�����ӡkey A authent failed��
 *   2. �����֤�ɹ�������ָ���Ŀ��еĸ�ʽΪ��ֵ��ĸ�ʽ��ô�����е���ֵ��5�ٴ�ӡ������
 *   3. �����֤�ɹ�������ָ�����еĸ�ʽ������ֵ��ĸ�ʽ����ô�����ӡ��ֵ����ʱ���Խ�130�е���������
 *      ��Ϊ1�������ִ�У�ˢ��ʱ�᲻�ϵĴ�ӡͬһ�����֣�֮���ٽ�130�е����������Ϊ0�������ִ�У���
 *      ˢ�����򴮿ڽ���ӡ����15��ʼ������-5����ֵ��
 *
 * \par Դ����
 * \snippet demo_zsn700_reader_picca_val_operate.c src_zsn700_reader_picca_val_operate
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-22  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_reader_picca_val_operate
 * \copydoc demo_zsn700_reader_picca_val_operate.c
 */

/** [src_zsn700_reader_picca_val_operate] */
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_zsn700_reader.h"
#include "am_zsn700_reader_reg.h"
#include "am_hwconf_zsn700_reader.h"

/**
 * \brief A�࿨ֵ��������
 */
void demo_zsn700_reader_picca_val_operate (void)
{
 
    uint8_t tag_type[2]  = { 0 };      /* ATQA */
    uint8_t uid[10]      = { 0 };      /* UID */
    uint8_t uid_real_len = 0;          /* ���յ���UID�ĳ��� */
    uint8_t sak[3]       = { 0 };      /* SAK */
    uint8_t keya[6]      = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};  /* ��֤��ԿA */
    uint8_t blocknum     = 9;          /* Ҫ��д�Ŀ� */
    int32_t value        = 0;          /* ��ֵ���е�ֵ */
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
            if (AM_ZSN700_READER_STATUS_SUCCESS == \
                    am_zsn700_reader_picca_authent (handle,
                                                    AM_ZSN700_READER_IC_KEY_TYPE_A,
                                                    uid,
                                                    keya,
                                                    blocknum)) {

#if 0
                /* �������ʽ������ֵ��ĸ�ʽ����ʹ��������γ��򽫿����ʼ��Ϊ��ֵ��ĸ�ʽ */
                uint8_t once_flag = 0;            /* ֻ����һ�γ�ʼ����ı�ʶ */
                if (once_flag == 0) {
                    once_flag = 1;
                    /* �Ƚ����ݿ��ʼ��Ϊֵ��ĸ�ʽ����ʼֵΪ20 */
                    am_zsn700_reader_picca_val_set(handle,
                                                   blocknum,
                                                   20);
                }
#endif

                /* ��ֵ��������5 */
                if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_val_operate\
                                                  (handle,
                                                   AM_ZSN700_READER_PICCA_PICC_SUB,
                                                   blocknum,
                                                   blocknum,
                                                   5)) {
                    /* ��ֵ������ */
                    if (AM_ZSN700_READER_STATUS_SUCCESS == am_zsn700_reader_picca_val_get\
                            (handle, blocknum, &value)) {
                        am_kprintf("value :%d\n", value);
                    }
                } else {
                    am_kprintf("value operate failed\n");
                }
            } else {
                am_kprintf("key A authent failed\n\n");
            }
        }
        am_mdelay(200);
    }
}

/** [src_zsn700_reader_picca_val_operate] */

/* end of file */

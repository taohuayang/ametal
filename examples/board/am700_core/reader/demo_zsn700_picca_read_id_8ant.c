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
 * \snippet demo_zsn700_reader_read_id_8_ant.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-02  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_reader_read_id_8_ant
 * \copydoc demo_zsn700_reader_read_id_8_ant.c
 */

/** [src_std_led] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "zsn700_pin.h"
#include "am_zsn700_reader.h"
#include "demo_std_entries.h"
#include "demo_am700_core_entries.h"
#include "am_hwconf_zsn700_reader.h"

#define ANT_CHANNEL_PIN1     PIOB_5
#define ANT_CHANNEL_PIN2     PIOB_4
#define ANT_CHANNEL_PIN3     PIOB_3
#define ANT_CHANNEL_PINE     PIOB_2


void am_zsn700_reader_ant_init()
{
    am_gpio_pin_cfg(ANT_CHANNEL_PIN1, AM_GPIO_OUTPUT_INIT_LOW);
    am_gpio_pin_cfg(ANT_CHANNEL_PIN2, AM_GPIO_OUTPUT_INIT_LOW);
    am_gpio_pin_cfg(ANT_CHANNEL_PIN3, AM_GPIO_OUTPUT_INIT_LOW);
    am_gpio_pin_cfg(ANT_CHANNEL_PINE, AM_GPIO_OUTPUT_INIT_LOW);
}


void am_zsn700_reader_ant_select(uint8_t chan)
{
    am_gpio_set(ANT_CHANNEL_PIN1, (chan & 0x01));
    am_gpio_set(ANT_CHANNEL_PIN2, ((chan >> 1) & 0x01));
    am_gpio_set(ANT_CHANNEL_PIN3, ((chan >> 2) & 0x01));
}

/**
 * \brief A�࿨�������ͺͿ�������(8����)
 */
void demo_zsn700_reader_picca_read_id_8ant (void)
{
    uint8_t              tag_type[2]  = { 0 };      /* ATQA */
    uint8_t              uid[10]      = { 0 };      /* UID */
    uint8_t              uid_real_len =   0;         /* ���յ���UID�ĳ��� */
    uint8_t              sak[3]       = { 0 };      /* SAK */
    am_zsn700_reader_handle_t handle;

    handle = am_zsn700_reader_inst_init();
    am_zsn700_reader_ant_init();

    while (1) {
        int i  = 0;

        for(uint8_t chan = 0 ; chan < 8; chan ++){
            am_zsn700_reader_ant_select(chan);
            am_kprintf("Ant channel %d : \n", chan);
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
}
/** [src_zsn700_reader_read_id_8_ant] */

/* end of file */

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
 * \brief �����¼��������������
 *
 * \sa am_servconf_event_input.c
 * \internal
 * \par modification history
 * - 1.00 15-01-19  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_event_category_input.h"
#include "am_event_input_key.h"

/**
 * \addtogroup am_if_src_servconf_event_input
 * \copydoc am_servconf_event_input.c
 * @{
 */

/* ���֧��2������ͬʱ���������󲿷�Ӧ�ã�ֻ��ʹ�õ�һ��  */
#define __KEY_LONG_PRESS_MAX_NUM   2

/* ���建�棬��������ʱʹ�� */
am_local am_event_input_key_long_press_t __g_key_long_press_buf[__KEY_LONG_PRESS_MAX_NUM];

/**
 * \brief NVRAM �������������Ϣ
 */
am_local am_const am_event_input_key_info_t __g_event_input_key_info = {
    1000,                              /* ����1s��ʼ��Ӧ���ϱ������¼�      */
    100,                               /* ����ʱ���ϱ������¼���������100ms   */
    __KEY_LONG_PRESS_MAX_NUM,          /* ͬʱ�����İ��������Ŀ              */
    __g_key_long_press_buf             /* ����֧�ֶ��ͬʱ�����Ļ���          */
};

/**
 * \brief �¼�����������������������룩�����ʼ��
 */
void am_event_input_inst_init (void)
{
    /* ��ʼ�������¼������� */
    am_event_category_input_init();

    /* ��ʼ��������������� */
    am_event_input_key_init(&__g_event_input_key_info);
}

/**
 * @}
 */

/* end of file */

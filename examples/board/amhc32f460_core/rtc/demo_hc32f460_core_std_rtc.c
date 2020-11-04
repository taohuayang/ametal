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
 * \brief RTC ���̣�ͨ����׼�ӿں��м������㺯��ʵ��
 *
 * - ʵ������
 *   1. ÿ10�뷢��һ�������жϣ����ڲ���ӡ����ǰʱ����Ϣ��
 *   2. ���ĵ�11��21��0����������жϣ���ӡ����"alarm clock int!"��ʾ��Ϣ��
 *   3. ����am_hwconf_hc32f460_rtc.c�ļ�������1Hz������ƣ���ʹ�ܣ�PIOB_14�����1Hz�ķ�����
 *   4. �ر�ʱ�Ӳ���������£����1Hz������ʵ��Ƶ�ʣ��������м���ʽ���㣺
 *           ppm = ��1Hz������ʵ��Ƶ�� - 1Hz��* 10^6
 *      ��������Ľ������am_hwconf_hc32f460_rtc.c���豸��Ϣ��Ӧλ�ã������о����Ƿ�ʹ�ܸ��ٲ���ʱ�ӡ�
 *      ���롢���أ�����˿ڽ�������Ƚϸߵ�1Hz����
 *
 * \note
 *    
 *
 * \par Դ����
 * \snippet demo_hc32f460_std_rtc.c src_hc32f460_std_rtc
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-17  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_rtc
 * \copydoc demo_hc32f460_std_rtc.c
 */

/** [src_hc32f460_std_rtc] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_rtc.h"
#include "am_hc32f460_rtc.h"
#include "demo_std_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_core_entries.h"


/**
 * \brief �������
 */
void demo_hc32f460_core_std_rtc_entry (void)
{    
    AM_DBG_INFO("demo hc32f460_core std rtc entry!\r\n");
    demo_std_rtc_entry(am_hc32f460_rtc_inst_init());
}
/** [src_hc32f460_std_rtc] */

/* end of file */

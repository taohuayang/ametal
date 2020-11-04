/*******************************************************************************
*                                 AMorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief CAN�ж���ʾ����
 *
 * - �������裺
 *   1. �۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_3 �������� PC ���ڵ� TXD��
 *      PIOA_2 �������� PC ���ڵ� RXD��
 *   2. ����CAN1��������ŵ�CAN�շ������ٽ�CAN�շ����ӿ���USBCAN-II�豸������
 *   3. ��CAN��λ�������ò�����Ϊ�궨��CAN_BAUD��ֵ��
 *   4. �򿪴��ڵ����նˣ�������115200-8-N-1.
 *
 * - ʵ������
 *   1. ��������жϺ󣬴�ӡ��ʾ��Ϣ��
 *
 *      �����жϣ����ڴ�ӡ�ȴ�������ʾ��Ϣ����λ������һ�����ݺ󣬳ɹ����ѣ�����ӡ��ʾ��Ϣ��
 *      �����жϣ�ÿ���յ�һ�����ݣ����ڴ�ӡID�ţ��ֽ����ݡ�
 *      ����жϣ�FIFO(����3)����󣬴��ڴ�ӡFIFO�յ��ĵ�һ�����ݣ�ID�ţ��ֽ����ݡ�
 *      �����жϣ�ÿ500ms��whileѭ���з���һ�����ݣ����ݷ��ͳɹ������뷢���жϣ����ڴ�ӡ��ʾ��Ϣ��
 *      ���󾯸��жϣ����ڴ�ӡ��ʾ��Ϣ���Ҵ�ӡ���ʹ������ֵ�����մ������ֵ��
 *      ���󱻶��жϣ����ڴ�ӡ��ʾ��Ϣ���Ҵ�ӡ���ʹ������ֵ�����մ������ֵ��
 *
 *      ���Ľṹ��can_rcv_msg��demo_stm32f103rbt6_can_int_entry()��ʹ�õ���ȫ�ֱ�������������(�ѻ���)��
 *      �����˽��ջ�����жϺ���λ�����͵����ݣ������Թ��̻�ÿ500ms���ظ���λ����
 *
 *   2. ���ڴ�ӡ��ص�����Ϣ��
 *
 * \note ��ʹ�á��򡯲�����������жϡ�
 *
 *       ע�⣬�벻Ҫͬʱ��������ͽ����жϡ�
 *       ԭ�򣬳�����ƣ������ж�ʹ�ܺ�Ϊ����һֱ���������жϣ����FIFO�ڵı��Ľ���������ȡ������
 *           ����������£�����ж��ǲ����ܴ����ġ�
 *
 *       ���������ж�ʱ����Ҫ��λ���ȷ���һ�鱨���Ի���CAN��
 *       ���������ж�ʱ����Ҫ��λ�����������������óɲ�ƥ�䣬����CAN����ʧ�ܡ���������Ψһ��������ģ������䣩
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_can_int.c demo_stm32f103rbt6_can_int
 *
 * \internal
 * \par modification history:
 * - 19-08-08, zp, first implementation.
 * - 19-12-18, zc, add filter table extern
 * \endinternal
 */

#include "ametal.h"
#include "am_can.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "demo_zlg_entries.h"

#define  APB1_CLK        36000000 /*CAN ������ʱ�� */
#define  CAN_BAUD        50000    /*CAN �Ĳ����� */

/**\brief �˲������飬����趨��ο�demo_stm32f103rbt6_core_can.c���� */
am_can_filter_t table[1] = {
        {
                AM_CAN_FRAME_TYPE_EXT,
                AM_CAN_FRAME_FORMAT_DATA,
                {0x00},
                {0x00},
        }
};

/**
 * \brief ��ȡ��Ӧ����������ֵ  CAN_BAUD = APB1/((BRP + 1) * (TEG1 + TEG2 + 3))
 */
static void __can_auto_cfg_baud(am_can_bps_param_t *can_btr_baud,
                                uint32_t            src_clk,
                                uint32_t            baud )
{
    uint32_t i,value = baud,record = 1;
    uint32_t remain = 0,sum_prescaler = 0;
    while(( baud == 0 )||( src_clk == 0 ));
    sum_prescaler = src_clk / baud;
    for ( i = 25; i > 3; i-- ) {
        remain = sum_prescaler - ((sum_prescaler / i)*i);
        if( remain == 0 ) {
          record = i;
          break;
        } else {
          if (remain < value) {
              value = remain;
              record = i;
          }
        }
    }
    can_btr_baud->sjw = 2;
    can_btr_baud->brp = (sum_prescaler/record) - 1;
    can_btr_baud->tesg2 = (record - 3) / 3;
    can_btr_baud->tesg1 = (record - 3) - can_btr_baud->tesg2;
}
/**
 * \brief CAN �ж��������
 *
 * \return ��
 */
void demo_stm32f103rbt6_core_can_int_entry (void)
{
    am_can_bps_param_t  can_btr_baud = {0};
    am_can_int_type_t   int_type;

    AM_DBG_INFO("demo stm32f103rbt6_core std can!\r\n");

    __can_auto_cfg_baud(&can_btr_baud, APB1_CLK, CAN_BAUD);

    /* ��ʹ�á��򡯲�����������ж�
     * ע�⣬�벻Ҫͬʱ��������ͽ����жϡ�
     * ԭ�򣬳�����ƣ������ж�ʹ�ܺ�Ϊ����һֱ���������жϣ����FIFO�ڵı��Ľ���������ȡ������
     *     ����������£�����ж��ǲ����ܴ����ġ�
     *
     *     ���������ж�ʱ����Ҫ��λ���ȷ���һ�鱨���Ի���CAN��
     *     ���������ж�ʱ����Ҫ��λ�����������������óɲ�ƥ�䣬����CAN����ʧ�ܡ���������Ψһ��������ģ������䣩
     */
    int_type = AM_CAN_INT_WARN          |
               AM_CAN_INT_ERROR_PASSIVE |
               AM_CAN_INT_WAKE_UP       |
               AM_CAN_INT_TX            |
               AM_CAN_INT_DATAOVER ;

    demo_stm32f103rbt6_can_int_entry (am_stm32f103rbt6_can_inst_init(),
                               &can_btr_baud,
                               int_type,
                               table,
                               1);
}

/** [demo_stm32f103rbt6_can_int] */

/* end of file */

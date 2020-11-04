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
* \brief CAN��ʾ���� 
* 
* - �������裺 
*   1. ����������am_prj_params.hͷ�ļ���ʹ�� 
*   - ��Ӧƽ̨��CAN�豸��(AM_DEV_XXXXX_CAN1); 
*   - AM_COM_CONSOLE; 
*   -  ��Ӧƽ̨�Ĵ����豸��(AM_DEV_XXXXX_UART1)�� 
*   2. ����CAN1��������ŵ�CAN�շ������ٽ�CAN�շ����ӿ���USBCAN-II�豸������ 
*   3. ��CAN��λ�������ò�����Ϊ250k�� 
*   4. �򿪴��ڵ����նˣ�������115200-8-N-1. 
* 
* - ʵ������ 
*   1. ��λ���������ݺ��յ����͵����ݡ� 
*   2. ���ڴ�ӡ��ص�����Ϣ�� 
* 
* - ��ע�� 
*   1. ���� CAN ID �� ���������� ��Ҫ���ݾ���Ӳ��ƽ̨�޸ġ� 
* 
* \par Դ���� 
* \snippet test_flexcan.c src_test_flexcan 
* 
* \internal 
* \par modification history: 
* - 
* \endinternal 
*/


#include "ametal.h"
#include "am_can.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_hc32f460_inst_init.h"
#include "demo_std_entries.h"

#define  CAN_CHN         0         /*CAN ID�����ݾ���ƽ̨�޸� */
#define  APB1_CLK        8000000  /*CAN ������ʱ�� */
#define  CAN_BAUD        250000    /*CAN �Ĳ����� */

/**
 * \brief ��ȡ��Ӧ����������ֵ ��ȡ��Ӧ����������ֵ  
 */
void __can_auto_cfg_baud(am_can_bps_param_t  *can_btr_baud,uint32_t src_clk,uint32_t baud )
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
    can_btr_baud->sjw = 0;
    can_btr_baud->brp = (sum_prescaler/record) - 1;
    can_btr_baud->tesg2 = (record - 3) / 3;
    can_btr_baud->tesg1 = (record - 3) - can_btr_baud->tesg2;
}

/**
 * \brief CAN �������
 *
 * \return ��
 */
void demo_hc32f460_core_std_can_entry (void)
{
    am_can_bps_param_t  can_btr_baud = {0};

    AM_DBG_INFO("demo hc32f460_core std can!\r\n");

    __can_auto_cfg_baud(&can_btr_baud, APB1_CLK, CAN_BAUD);

    demo_std_can_entry (am_hc32f460_can_inst_init (), &can_btr_baud);
}

/** [src_test_flexcan] */

/* end of file */

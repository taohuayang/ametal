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
 * \brief DAC��ģת�����̣�ͨ��STD�ӿ�ʵ��
 *
 * - ʵ������
 *   1. DAC���1523mv��ѹ��
 *
 *
 * \par Դ����
 * \snippet demo_zlg118_std_dac.c src_zlg118_std_dac
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-25  ly, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_std_dac
 * \copydoc demo_zlg118_std_dac.c
 */

 /** [src_std_dac] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg118_inst_init.h"
#include "demo_std_entries.h"

const static uint32_t mv_out = 1523;

/**
 * \brief DAC�����ѹ����׼�ӿڲ�ʵ��
 * \return ��
 */
void demo_zlg118_core_std_dac_entry (void)
{
    am_dac_handle_t adc_handle = NULL;
    
    AM_DBG_INFO("demo am118_core std dac convert test!\r\n");
    
    adc_handle = am_zlg118_dac_inst_init();

    demo_std_dac_entry(adc_handle, 0, mv_out);
}


 /** [src_std_dac] */

/* end of file */


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
/** [src_mm32l073_core_mk100_test] */
#include "demo_std_entries.h"
#include "demo_mm32l073_core_entries.h"
#include "am_hwconf_mk100_uart.h"
#include "demo_components_entries.h"
#include "am_mm32l073_inst_init.h"
/**
 * \brief �������
 */
void demo_mm32l073_core_mk100_test_entry (void)
{
    am_mk100_handle_t handle = am_mk100_uart2_inst_init();
    demo_mk100_entry(handle);
}
/** [src_mm32l073_core_mk100_test] */

/* end of file */

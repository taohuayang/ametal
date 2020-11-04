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
 * \brief TIM1 定时器 CAP 例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 使用杜邦线，将 PIOE_2 与 PIOE_11 连接。
 *
 * - 实验现象：
 *   1. TIMEA1 通过 PIOE_2 引脚输出 2KHz 的 PWM；
 *   2. ADTIM61 捕获输入通道 1 使用 PIOE_11 引脚捕获；
 *   3. 串口打印出利用捕获功能得到的 PWM 信号的周期和频率。
 *
 * \note
 *    
 *       
 *
 * \par 源代码
 * \snippet demo_hc32f460_std_tim0_cap.c src_hc32f460_std_adtim_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_std_adtim_cap
 * \copydoc demo_hc32f460_std_tim_cap.c
 */

/** [src_hc32f460_std_tim0_cap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_hc32f460_adtim_cap.h"
#include "am_hc32f460_timea_pwm.h"
#include "am_hc32f460_inst_init.h"
#include "demo_std_entries.h"
#include "demo_hc32f460_core_entries.h"

/**
 * \brief 娓氬鈻奸崗銉ュ�?
 */
void demo_hc32f460_core_std_adtim62_cap_entry (void)
{
    am_pwm_handle_t timea3_pwm_handle = am_hc32f460_timea3_pwm_inst_init();
    am_cap_handle_t adtim62_cap_handle = am_hc32f460_adtim62_cap_inst_init();
    
    AM_DBG_INFO("demo hc32f460_core std adtim62 cap!\r\n");

    /* TIM0 鏉堟挸鍤０鎴犲芳娑擄拷 2KHz 閻�?PWM */
    am_pwm_config(timea3_pwm_handle, TIMERA_CH5, 500000 / 2, 500000);
    am_pwm_enable(timea3_pwm_handle, TIMERA_CH5);

    demo_std_timer_cap_entry(adtim62_cap_handle, AMHW_HC32F460_ADTIM_CHX_A);
}
/** [src_hc32f460_std_tim0_cap] */

/* end of file */

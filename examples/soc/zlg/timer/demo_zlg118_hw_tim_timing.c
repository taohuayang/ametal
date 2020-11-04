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
 * \brief ��ʱ����ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ж�ʱ���Դ��ڴ�ӡ��Ϣ��
 *   2. LED0 ��ת
 *
 * \par Դ����
 * \snippet demo_zlg118_hw_tim_timing.c src_zlg118_hw_tim_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zlg118_hw_tim_timing
 * \copydoc demo_zlg118_hw_tim_timing.c
 */

/** [src_zlg118_hw_tim_timing] */
#include "ametal.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg118_tim.h"
#include "am_led.h"

#define LED0   0

/**
 * \brief PWM �жϷ�����
 */
static void __zlg118_tim_hw_timing_irq_handler (void *p_arg)
{
    amhw_zlg118_tim_t *p_hw_tim = (amhw_zlg118_tim_t *)p_arg;

    if (amhw_zlg118_tim_mode0_int_update_flag_check(p_hw_tim) == AM_TRUE ) {

        AM_DBG_INFO("timing irq!\r\n");

        am_led_toggle(LED0);

        /* ��������־ */
        amhw_zlg118_tim_mode0_int_update_flag_clr(p_hw_tim);
    }
}

/**
 * \brief ���ö�ʱ��TIMΪ��ʱ����timing
 *
 * \param[in] p_hw_tim : ָ��ʱ���Ĵ������ָ��
 * \param[in] cnt      : ����ֵ������ڶ�ʱ������ʱ��Ƶ��������
 *
 * \return ��
 */
void tim_timing_chan_config (amhw_zlg118_tim_t *p_hw_tim, uint32_t cnt)
{
    uint32_t match;
    uint16_t pre_real = 1;

    /* ���÷�Ƶֵ */
    amhw_zlg118_tim_mode_clkdiv_set(p_hw_tim, AMHW_ZLG118_TIM_CLK_DIV256);

    pre_real = 256;

    /* �����Զ�����ֵ */
    match = cnt / pre_real ;

    if(match > 65535) {
        return;
    }

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zlg118_tim_arr_count_set(p_hw_tim, 65535 - (match - 1));

    /* ���ü����� */
    amhw_zlg118_tim_cnt16_count_set(p_hw_tim, 65535 - (match - 1));
}

/**
 * \brief ʹ�ܶ�ʱ��Ϊ��ʱ����
 */
void tim_timing_enable (amhw_zlg118_tim_t *p_hw_tim, uint8_t int_num)
{

    /* �����жϻص����� */
    am_int_connect(int_num, __zlg118_tim_hw_timing_irq_handler, (void *)p_hw_tim);

    am_int_enable(int_num);

    /* ���¶�ʱ��ʱ����������¼�,�����־λ */
    amhw_zlg118_tim_mode0_int_update_flag_clr(p_hw_tim);

    /* ��������ж� */
    amhw_zlg118_tim_mode0_int_update_enable(p_hw_tim);

    /* ʹ�ܶ�ʱ��TIM������� */
    amhw_zlg118_tim_enable(p_hw_tim);
}

/**
 * \brief ��ʱ��TIM timing��ʼ������
 */
void tim_timing_init (amhw_zlg118_tim_t *p_hw_tim, amhw_zlg118_tim_type_t type)
{
    /* 16λ���ؼ����� */
    amhw_zlg118_tim_mode0_counter_set(p_hw_tim,
                                      AMHW_ZLG118_TIM_MODE0_COUNTER_16);

    /* ���ö�ʱ��ģʽ0 */
    amhw_zlg118_tim_mode_set(p_hw_tim, AMHW_ZLG118_TIM_MODE_TIMING);

    /* ����ʱ������ */
    amhw_zlg118_tim_mode_clk_src_set(p_hw_tim,AMHW_ZLG118_TIM_CLK_SRC_TCLK);
}

/**
 * \brief �������
 */
void demo_zlg118_hw_tim_timing_entry (void    *p_hw_tim,
                                      uint8_t  type,
                                      uint32_t clk_rate,
                                      int32_t  int_num)
{
    amhw_zlg118_tim_t *p_tim = (amhw_zlg118_tim_t *)p_hw_tim;

    /* ��ʼ����ʱ��Ϊ��ʱ���� */
    tim_timing_init(p_tim, (amhw_zlg118_tim_type_t)type);

    tim_timing_chan_config(p_tim, clk_rate / 20);

    tim_timing_enable(p_tim, int_num);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg118_hw_tim_timing] */

/* end of file */

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
 * \snippet demo_stm32f103rbt6_hw_tim_timing.c src_stm32f103rbt6_hw_tim_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_stm32f103rbt6_hw_tim_timing
 * \copydoc demo_stm32f103rbt6_hw_tim_timing.c
 */

/** [src_stm32f103rbt6_hw_tim_timing] */
#include "ametal.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_stm32f103rbt6_tim.h"
#include "am_led.h"

#define LED0   0
/**
 * \brief PWM �жϷ�����
 */
static void __stm32f103rbt6_tim_hw_timing_irq_handler (void *p_arg)
{
    amhw_stm32f103rbt6_tim_t *p_hw_tim = (amhw_stm32f103rbt6_tim_t *)p_arg;

    AM_DBG_INFO("timing irq!\r\n");

    am_led_toggle(LED0);

    /* ������±�־ */
    amhw_stm32f103rbt6_tim_status_flg_clr(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIF);
}

/**
 * \brief ���ö�ʱ��TIMΪ��ʱ����timing
 *
 * \param[in] p_hw_tim : ָ��ʱ���Ĵ������ָ��
 * \param[in] cnt      : ����ֵ������ڶ�ʱ������ʱ��Ƶ��������
 *
 * \return ��
 */
void tim_timing_chan_config (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint32_t cnt)
{
    uint32_t match, temp;
    uint16_t pre_real = 1, pre_reg = 0;

    {
        temp = cnt;

        /* 16λ���������ֵ65536, ��Ƶ�����ֵ65536 */
        if (temp  > 4294967295UL) {
            return ;
        }

        /* ������С��65536ʱ������Ƶ(ֵΪ1,1����Ϊ1��Ƶ) */
        temp = cnt  / 65536 + 1;

        /* 16λ��ʱ����Ҫ����ȡ�ú��ʵķ�Ƶֵ */
        for (pre_real = 1; pre_real < temp; ) {
            pre_reg++;           /* ����д��Ĵ����ķ�Ƶֵ0,1,2,... */
            pre_real++;          /* ��Ƶ�� */
        }
    }

    /* �����Զ�����ֵ */
    match = cnt / pre_real ;

    /* ���÷�Ƶֵ */
    amhw_stm32f103rbt6_tim_prescale_set(p_hw_tim, pre_reg);

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_stm32f103rbt6_tim_arr_set(p_hw_tim, match - 1);

    /* �������� 0 */
    amhw_stm32f103rbt6_tim_count_set(p_hw_tim, 0);
}

/**
 * \brief ʹ�ܶ�ʱ��Ϊ��ʱ����
 */
void tim_timing_enable (amhw_stm32f103rbt6_tim_t *p_hw_tim, uint8_t int_num)
{

    /* ���������¼������³�ʼ��Prescaler������ ��Repetition������ */
    amhw_stm32f103rbt6_tim_egr_set(p_hw_tim, AMHW_STM32F103RBT6_TIM_UG);

    if (amhw_stm32f103rbt6_tim_status_flg_get(p_hw_tim, AMHW_STM32F103RBT6_TIM_UG) != 0) {

        /* ���¶�ʱ��ʱ����������¼�,�����־λ */
        amhw_stm32f103rbt6_tim_status_flg_clr(p_hw_tim, AMHW_STM32F103RBT6_TIM_UG);
    }

    /* �����жϻص����� */
    am_int_connect(int_num, __stm32f103rbt6_tim_hw_timing_irq_handler, (void *)p_hw_tim);

    /* ʹ�ܸ����ж� */
    amhw_stm32f103rbt6_tim_int_enable(p_hw_tim, AMHW_STM32F103RBT6_TIM_UIE);

    am_int_enable(int_num);

    /*��ʹ�ܶ�ʱ��TIM������� */
    amhw_stm32f103rbt6_tim_enable(p_hw_tim);
}

/**
 * \brief ��ʱ��TIM timing��ʼ������
 */
void tim_timing_init (amhw_stm32f103rbt6_tim_t *p_hw_tim, amhw_stm32f103rbt6_tim_type_t type)
{
    if ((AMHW_STM32F103RBT6_TIM_TYPE0 == type) || (AMHW_STM32F103RBT6_TIM_TYPE1 == type)) {

        /* ���ض���ģʽ */
        amhw_stm32f103rbt6_tim_cms_set(p_hw_tim, 0);

        /* ���ϼ��� */
        amhw_stm32f103rbt6_tim_dir_set(p_hw_tim, 0);
    }

    /* ����ʱ�ӷָ�:TDTS = Tck_tin */
    amhw_stm32f103rbt6_tim_ckd_set(p_hw_tim, 0);

    /* ��������¼� */
    amhw_stm32f103rbt6_tim_udis_enable(p_hw_tim);

}

/**
 * \brief �������
 */
void demo_stm32f103rbt6_hw_tim_timing_entry (amhw_stm32f103rbt6_tim_t     *p_hw_tim,
                                   amhw_stm32f103rbt6_tim_type_t type,
                                   uint32_t            clk_rate,
                                   int32_t             int_num)
{

    /* ��ʼ����ʱ��Ϊ��ʱ���� */
    tim_timing_init(p_hw_tim, type);

    tim_timing_chan_config(p_hw_tim, clk_rate / 2);

    tim_timing_enable(p_hw_tim, int_num);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_stm32f103rbt6_hw_tim_timing] */

/* end of file */

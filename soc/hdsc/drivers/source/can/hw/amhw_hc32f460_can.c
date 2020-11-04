/*******************************************************************************
*                                 AMetal
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief CAN
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-06  zcb, first implementation.
 * \endinternal
 */
#include "hw/amhw_hc32f460_can.h"

#if 0
/**
 * \brief can ģʽ����
 */
void amhw_hc32f460_can_mode_set (amhw_hc32f460_can_t      *p_hw_can,
                                 amhw_hc32f460_can_type_t type,
                                 amhw_hc32f460_can_mode_t *p_now,
                                 amhw_hc32f460_can_mode_t update)
{
    if (NULL == p_hw_can || NULL == p_now) {
        return;
    }

    /* ����ģʽ��ԭģʽ�����ֱ���˳� */
    if (update == *p_now) {
        return;
    }

    /* ���CAN����˯��ģʽ���ҽ�����Ϊ����ģʽ�����Ȼ���CAN�������������ж� */
    if (*p_now == AMHW_HC32F460_CAN_MODE_SLEEP) {
        if (AMHW_HC32F460_CAN_BASIC_CAN == type) {
            amhw_hc32f460_basic_can_wake_up(p_hw_can);
        } else {
            amhw_hc32f460_peli_can_mod_clr(p_hw_can,
                                           AMHW_HC32F460_CAN_PELI_MODE_SM);
        }
    }

    /* basic CANģʽ */
    if (AMHW_HC32F460_CAN_BASIC_CAN == type) {

        /* �л�״̬������ģʽ */
        if (AMHW_HC32F460_CAN_MODE_RESET == *p_now) {
            amhw_hc32f460_basic_can_reset_clr(p_hw_can);
        } else if (AMHW_HC32F460_CAN_MODE_SLEEP == *p_now) {
            amhw_hc32f460_basic_can_wake_up(p_hw_can);
        }

        /* ����״̬ */
        if (AMHW_HC32F460_CAN_MODE_RESET == update) {
            amhw_hc32f460_basic_can_reset_set(p_hw_can);
        } else if (AMHW_HC32F460_CAN_MODE_SLEEP == *p_now) {
            amhw_hc32f460_basic_can_go_to_sleep(p_hw_can);
        }

    } else {

        /* peli CAN,�л�������ģʽ */
        amhw_hc32f460_peli_can_mod_clr(p_hw_can, *p_now);

        /* ֻ��ģʽֻ���ڸ�λģʽ�½��� */
        if (AMHW_HC32F460_CAN_MODE_ONLY_LISTEN == update) {
            amhw_hc32f460_peli_can_mod_set(p_hw_can,
                                           AMHW_HC32F460_CAN_MODE_RESET);
        }

        /* ����ģʽ */
        if (AMHW_HC32F460_CAN_MODE_RUN != update) {
            amhw_hc32f460_peli_can_mod_set(p_hw_can, update);
        }

    }

    *p_now = update;
}
#endif
/* end of file */

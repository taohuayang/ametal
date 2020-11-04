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
 * \brief RESET
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */
 
#include "hw/amhw_zsn700_rcc_reset.h"

/* ʹĳЩ���踴λ���������� */
static void __reset_cmd(amhw_zsn700_rcc_reset_peripheral peri, uint8_t cmd)
{
    if(peri > 31) {

        if (cmd) {
            ZSN700_RCC_RESET->reset[1] |= (1ul << (peri - 31));
        } else {
            ZSN700_RCC_RESET->reset[1] &= ~(1ul << (peri - 31));
        }
    } else {

        if (cmd) {
            ZSN700_RCC_RESET->reset[0] |= (1ul << peri);
        } else {
            ZSN700_RCC_RESET->reset[0] &= ~(1ul << peri);
        }
    }
}

/**
 * \brief ʹĳЩ���踴λ
 *
 * \param[in]  peri ����Ҫ��λ������
 *
 * \return ��
 *
 */
void amhw_zsn700_rcc_reset (amhw_zsn700_rcc_reset_peripheral peri)
{
    __reset_cmd(peri, 0);
}

/**
 * \brief ʹĳЩ������������
 *
 * \param[in]  peri ����Ҫ��������������
 *
 * \return ��
 *
 */
void amhw_zsn700_rcc_reset_stop (amhw_zsn700_rcc_reset_peripheral peri)
{
    __reset_cmd(peri, 1);
}

/* end of file */

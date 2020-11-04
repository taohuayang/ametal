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
 * - 1.00 19-09-05  zp, first implementation
 * \endinternal
 */
 
#include "hw/amhw_zlg118_rcc_reset.h"

/* ʹĳЩ���踴λ���������� */
static void __reset_cmd(amhw_zlg118_rcc_reset_peripheral peri, uint8_t cmd)
{
    if(peri > 31) {

        if (cmd) {
            ZLG118_RCC_RESET->reset[1] |= (1ul << (peri - 31));
        } else {
            ZLG118_RCC_RESET->reset[1] &= ~(1ul << (peri - 31));
        }
    } else {

        if (cmd) {
            ZLG118_RCC_RESET->reset[0] |= (1ul << peri);
        } else {
            ZLG118_RCC_RESET->reset[0] &= ~(1ul << peri);
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
void amhw_zlg118_rcc_reset (amhw_zlg118_rcc_reset_peripheral peri)
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
void amhw_zlg118_rcc_reset_stop (amhw_zlg118_rcc_reset_peripheral peri)
{
    __reset_cmd(peri, 1);
}

/* end of file */

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
 * \brief RCC
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */
 
#include "hw/amhw_zsn700_rcc.h"

/* ʹ�ܻ�������� */
static void __rcc_cmd(amhw_zsn700_peripheral peri, uint8_t cmd)
{
    if(peri > 31) {

        if (cmd) {
            ZSN700_RCCCTRL->peri_clken[1] |= (1ul << (peri - 31));
        } else {
            ZSN700_RCCCTRL->peri_clken[1] &= ~(1ul << (peri - 31));
        }
    } else {

        if (cmd) {
            ZSN700_RCCCTRL->peri_clken[0] |= (1ul << (peri));
        } else {
            ZSN700_RCCCTRL->peri_clken[0] &= ~(1ul << (peri));
        }
    }
}

/**
 * \brief ʹ��AHB����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 *
 */
void amhw_zsn700_rcc_peripheral_enable (amhw_zsn700_peripheral peri)
{
    __rcc_cmd(peri, 1);
}

/**
 * \brief ���ĳ����ʱ���Ƿ�ʹ��
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return 1: ��ǰ����ʱ����ʹ�ܣ������ٴ�ʹ��
 *         0: ��ǰ����ʱ��δʹ��
 *
 */
int amhw_zsn700_rcc_peripheral_enable_check (amhw_zsn700_peripheral peri)
{
    if(peri > 31) {
        return ((ZSN700_RCCCTRL->peri_clken[1] >> (peri - 31)) & 0x01);
    } else {
        return ((ZSN700_RCCCTRL->peri_clken[0] >> peri) & 0x01);
    }
}


/**
 * \brief ����AHB����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
void amhw_zsn700_rcc_peripheral_disable (amhw_zsn700_peripheral peri)
{
    __rcc_cmd(peri, 0);
}

/* end of file */

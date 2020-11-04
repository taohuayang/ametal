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
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */
 
#include "hw/amhw_zlg118_rcc.h"

/* ʹ�ܻ�������� */
static void __rcc_cmd(amhw_zlg118_peripheral peri, uint8_t cmd)
{
    if(peri > 31) {

        if (cmd) {
            ZLG118_RCCCTRL->peri_clken[1] |= (1ul << (peri - 31));
        } else {
            ZLG118_RCCCTRL->peri_clken[1] &= ~(1ul << (peri - 31));
        }
    } else {

        if (cmd) {
            ZLG118_RCCCTRL->peri_clken[0] |= (1ul << (peri));
        } else {
            ZLG118_RCCCTRL->peri_clken[0] &= ~(1ul << (peri));
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
void amhw_zlg118_rcc_peripheral_enable (amhw_zlg118_peripheral peri)
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
int amhw_zlg118_rcc_peripheral_enable_check (amhw_zlg118_peripheral peri)
{
    if(peri > 31) {
        return ((ZLG118_RCCCTRL->peri_clken[1] >> (peri - 31)) & 0x01);
    } else {
        return ((ZLG118_RCCCTRL->peri_clken[0] >> peri) & 0x01);
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
void amhw_zlg118_rcc_peripheral_disable (amhw_zlg118_peripheral peri)
{
    __rcc_cmd(peri, 0);
}

/* end of file */

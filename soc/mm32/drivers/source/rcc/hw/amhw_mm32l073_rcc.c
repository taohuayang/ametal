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
 * ����ֱ��ʹ���� MM32L073 ����Ĵ�������ַ�� ��ˣ��������������� MM32L073
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  sdy, first implementation
 * \endinternal
 */
#include "hw/amhw_mm32l073_rcc.h"

/* ʹ�ܻ�������� */
static void __rcc_ahb_cmd (amhw_mm32l073_ahb_peripheral peri, uint8_t cmd)
{
    uint32_t tempa = 0;
    uint32_t tempb = 0;

    tempa = MM32L073_RCC->ahbenr;
    tempb = 0x0f000000 & tempa;
    tempb = tempb >> 7;

    tempa = 0x000000ff & tempa;
    tempa = tempa | tempb;

    if (cmd) {
        tempa = (1ul << peri) | tempa;
    } else {
        tempa = (~(1ul << peri)) & tempa;
    }

    MM32L073_RCC->ahbenr = tempa;
}

/**
 * \brief ʹ��AHB����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 *
 */
void amhw_mm32l073_rcc_ahb_enable (amhw_mm32l073_ahb_peripheral peri)
{
    __rcc_ahb_cmd(peri, 1);
}

/**
 * \brief ����AHB����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
void amhw_mm32l073_rcc_ahb_disable (amhw_mm32l073_ahb_peripheral peri)
{
    __rcc_ahb_cmd(peri, 0);
}

/* end of file */

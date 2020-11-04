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
 * ����ֱ��ʹ���� ZML165 ����Ĵ�������ַ�� ��ˣ��������������� ZML165
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  sdy, first implementation
 * \endinternal
 */
#include "hw/amhw_zml165_rcc.h"

#ifdef ZML165
/* ʹ�ܻ�������� */
static void __rcc_ahb_cmd (amhw_zml165_ahb_peripheral peri, uint8_t cmd)
{
    uint32_t tempa = 0;

    tempa = ZML165_RCC->ahbenr;

    if (cmd) {
        tempa = (1ul << peri) | tempa;
    } else {
        tempa = (~(1ul << peri)) & tempa;
    }

    ZML165_RCC->ahbenr = tempa;
}
#else
/* ʹ�ܻ�������� */
static void __rcc_ahb_cmd (amhw_zml165_ahb_peripheral peri, uint8_t cmd)
{
    uint32_t tempa = 0;
    uint32_t tempb = 0;

    tempa = ZML165_RCC->ahbenr;
    tempb = 0x0f000000 & tempa;
    tempb = tempb >> 7;

    tempa = 0x000000ff & tempa;
    tempa = tempa | tempb;

    if (cmd) {
        tempa = (1ul << peri) | tempa;
    } else {
        tempa = (~(1ul << peri)) & tempa;
    }

    ZML165_RCC->ahbenr = tempa;
}
#endif




/**
 * \brief ʹ��AHB����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 *
 */
void amhw_zml165_rcc_ahb_enable (amhw_zml165_ahb_peripheral peri)
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
void amhw_zml165_rcc_ahb_disable (amhw_zml165_ahb_peripheral peri)
{
    __rcc_ahb_cmd(peri, 0);
}

/* end of file */

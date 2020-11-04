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
 * \brief �ж�������
 *
 * \internal
 * \par modification history
 * - 1.02 17-12-11  pea, amend annotation
 * - 1.01 11-04-29  mifi, call SystemInit, and set the Vector Table Offset
*                   before copy of data and bss segment
 * - 1.00 11-04-09  mifi, first implementationS
 * \endinternal
 */

#define __CRT_C__

#include <stdint.h>
/***************************************************************************
  �ⲿ��������
***************************************************************************/
extern unsigned long _stext;
extern unsigned long _etext;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

/***************************************************************************
  �ⲿ��������
***************************************************************************/
extern int main (void);

/***************************************************************************
  ���غ�������
***************************************************************************/
void SystemInit (void) __attribute__((weak));
#include "hw/amhw_hc32f460_rcc.h"
/***************************************************************************
  ���غ�������
***************************************************************************/
#if !defined (HRC_VALUE)
#define HRC_VALUE ((uint32_t)16000000)  /*!< Internal high speed RC freq. */
#endif

#if !defined (MRC_VALUE)
#define MRC_VALUE ((uint32_t)8000000)   /*!< Internal middle speed RC freq. */
#endif

#if !defined (LRC_VALUE)
#define LRC_VALUE ((uint32_t)32768)     /*!< Internal low speed RC freq. */
#endif

#if !defined (XTAL_VALUE)
#define XTAL_VALUE ((uint32_t)8000000)  /*!< External high speed OSC freq. */
#endif

#if !defined (XTAL32_VALUE)
#define XTAL32_VALUE ((uint32_t)32768)  /*!< External low speed OSC freq. */
#endif


uint32_t SystemCoreClock = MRC_VALUE;

void SystemCoreClockUpdate(void)  // Update SystemCoreClock variable
{
    uint8_t tmp = 0u;
    uint32_t plln = 19u, pllp = 1u, pllm = 0u, pllsource = 0u;

    tmp = HC32F460_SYSCREG->CMU_CKSWR & 0x7;
    switch (tmp)
    {
        case 0x00:  /* use internal high speed RC */
            SystemCoreClock = HRC_VALUE;
            break;
        case 0x01:  /* use internal middle speed RC */
            SystemCoreClock = MRC_VALUE;
            break;
        case 0x02:  /* use internal low speed RC */
            SystemCoreClock = LRC_VALUE;
            break;
        case 0x03:  /* use external high speed RC */
            SystemCoreClock = XTAL_VALUE;
            break;
        case 0x04:  /* use external low speed RC */
            SystemCoreClock = XTAL32_VALUE;
            break;
        case 0x05:  /* use MPLL */
            /* PLLCLK = ((pllsrc / pllm) * plln) / pllp */
        	pllsource = (HC32F460_SYSCREG->CMU_PLLCFGR >> 7) & 0x1;
        	plln = (HC32F460_SYSCREG->CMU_PLLCFGR >> 8) & 0xff;
        	pllp = (HC32F460_SYSCREG->CMU_PLLCFGR >> 28) & 0x7;
        	pllm = (HC32F460_SYSCREG->CMU_PLLCFGR >> 0) & 0x1f;

            /* use exteranl high speed OSC as PLL source */
            if (0ul == pllsource)
            {
                SystemCoreClock = (XTAL_VALUE) / (pllm + 1ul) * (plln + 1ul) / (pllp + 1ul);
            }
            /* use interanl high RC as PLL source */
            else if (1ul == pllsource)
            {
                SystemCoreClock = (HRC_VALUE) / (pllm + 1ul) * (plln + 1ul) / (pllp + 1ul);
            }
            else
            {
                /* Reserved */
            }
            break;
    }
}


/**
 * \brief SystemInit() �� CMSIS �ӿ�����Ҫ��һ�����������û�������������ʱ
 *        ��������������ﶨ��һ�� weak ����
 */
void SystemInit (void)
{
    SystemCoreClockUpdate();
}
#pragma GCC push_options
#pragma GCC optimize("O0")
/**
 * \brief ��λ�жϴ���������ʼ�� C ���л����������ж�������.data �Ρ�.bss �Σ�
 *        ������ main() ����
 */
void ResetHandler_function (void)
{
    uint32_t *p_src;
    uint32_t *p_dest;

    unsigned int *pSCB_CPACR = (unsigned int *) (0xE000E088UL);

    SystemInit();

    /* set sram3 wait */
    *((volatile uint32_t*)0x40050804) = 0x77;
    *((volatile uint32_t*)0x4005080C) = 0x77;
    *((volatile uint32_t*)0x40050800) = 0x1100;
    *((volatile uint32_t*)0x40050804) = 0x76;
    *((volatile uint32_t*)0x4005080C) = 0x76;


    /* �ж��������ض�λ */
    *((uint32_t*)0xE000ED08) = (uint32_t)&_stext;

    /* ʹ�ܸ��㵥ԪΪȫ���� */
    *pSCB_CPACR |= 0x00F00000;

    /* �� .text ���ж�ȡ���ݳ�ʼ�� .data �� */
    p_src  = &_etext;
    p_dest = &_sdata;
    while (p_dest < &_edata) {
        *p_dest++ = *p_src++;
    }

    /* ��ʼ�� .bss ��Ϊ 0 */
    p_dest = &_sbss;
    while (p_dest < &_ebss) {
        *p_dest++ = 0;
    }

    (void)main();

    /* ��������²�Ӧ�����е����� */
    while (1) {
        ; /* VOID */
    }
}
/* end of file */

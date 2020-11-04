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
 * \brief HC32F460 CLK �û������ļ�
 * \sa am_hwconf_hc32f460_clk.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-30  cds, first implementation
 * \endinternal
 */
#include "am_gpio.h"

#include "am_hc32f460_clk.h"
#include "hw/amhw_hc32f460_rcc.h"
/**
 * \addtogroup am_if_src_hwconf_hc32f460_clk
 * \copydoc am_hwconf_hc32f460_clk.c
 * @{
 */
/** \brief CLK ƽ̨��ʼ�� */
static void __hc32f460_clk_plfm_init (void)
{
}

/** \brief CLK ��ƽ̨��ʼ�� */
static void __hc32f460_clk_plfm_deinit (void)
{
}

/*
 *
 * ϵͳʱ��Դ��ѡ����Ҫ�����֣�  HRC  ---  �ڲ���������(16MHz/20MHz)
 *                       MRC  ---  �ⲿ��������(8MHz)
 *                       LRC  ---  �ڲ���������(32.768KHz)
 *                       XTAL  ---  �ⲿ��������(�����Ƶ�ʷ�Χ��4 ~ 24MHz,�ⲿʱ�� ���룺���24MHz)
 *                       XTAL32  --- �����Ƶ�ʷ�Χ��32.768KHz
 *                       MPLLP  --- MPLLP  = PLL����ʱ�� / MPLL��Ƶϵ�� * MPLL��Ƶϵ�� / MPLLP��Ƶϵ��
 *
 * ϵͳʱ��Դѡ������õ����¹�ϵ
 *
 * SYSCLK = ��ѡ���ϵͳʱ��Դ
 * HCLK   = SYSCLK / HCLK_DIV
 * EXCLK  = SYSCLK / EXCLK_DIV
 * PCLK0  = SYSCLK / PCLK0_DIV
 * PCLK1  = SYSCLK / PCLK1_DIV
 * PCLK2  = SYSCLK / PCLK2_DIV
 * PCLK3  = SYSCLK / PCLK3_DIV
 * PCLK4  = SYSCLK / PCLK4_DIV
 *
 */
/** \brief CLK�豸��Ϣ */
static const am_hc32f460_clk_devinfo_t __g_clk_devinfo =
{
    /**
     * \brief XTH�ⲿ����ʱ�Ӿ���Ƶ�ʣ�Hz��
     */
    8000000,

    /**
     * \brief XTL�ⲿ����ʱ�Ӿ���Ƶ�ʣ�Hz��
     */
    32768,

    /**
     * \brief HRC�ڲ�����ʱ�Ӿ���Ƶ�ʣ�Hz��
     *
     * \note Ƶ��ѡ�� 20M��16M
     */
    AMHW_HC32F460_HRC_16M,

    /** \brief
     *    PLLʱ��Դѡ��
     *    -# AMHW_HC32F460_CLK_PLLSRC_XTAL : ѡ���ⲿ����������Ϊ����ʱ��
     *    -# AMHW_HC32F460_CLK_PLLSRC_HRC : ѡ���ڲ�����������Ϊ����ʱ��
     */
    AMHW_HC32F460_CLK_PLLSRC_XTAL,

    /**
     * \brief MPLL ���ʱ������
     *        MPLLP = PLLIN / mpll_div * mpll_mul / mpllp_div��
     *        MPLLQ = PLLIN / mpll_div * mpll_mul / mpllq_div��
     *        MPLLR = PLLIN / mpll_div * mpll_mul / mpllr_div��
     */
    1,     /* MPLL ����ʱ�ӷ�Ƶϵ��,1~24��Ӧȷ��MPLLIN����1MHz��12MHz֮�� */
    42,    /* MPLL ���ʱ�ӱ�Ƶϵ����20~480��,240M~480M */
    2,     /* MPLLPʱ�ӷ�Ƶϵ����2~16 */
    2,     /* MPLLQʱ�ӷ�Ƶϵ����2~16 */
    2,     /* MPLLRʱ�ӷ�Ƶϵ����2~16 */

    /**
     * \brief UPLL ����ʱ�ӷ�Ƶϵ��
     *        UPLLP = PLLIN / upll_div * upll_mul / upllp_div��
     *        UPLLQ = PLLIN / upll_div * upll_mul / upllq_div��
     *        UPLLR = PLLIN / upll_div * upll_mul / upllr_div��
     */
    2,     /* UPLL ����ʱ�ӷ�Ƶϵ����Ӧȷ��UPLLIN����1MHz��12MHz֮�� */
    84,    /* UPLL ���ʱ�ӱ�Ƶϵ����20~480��,240M~480M */
    7,     /* UPLLPʱ�ӷ�Ƶϵ����2~16 */
    7,     /* UPLLQʱ�ӷ�Ƶϵ����2~16 */
    7,     /* UPLLRʱ�ӷ�Ƶϵ����2~16 */

    /** \brief
     *    ϵͳ ʱ��Դѡ��
     *    -# AMHW_HC32F460_SYSCLK_HRC : �ڲ�����������Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_MRC : �ⲿ����������Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_LRC : �ڲ�����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_XTAL ��  �ⲿ����������Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_XTAL32 �� �ⲿ����������Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_MPLL �� MPLL��Ϊϵͳʱ��
     */
    AMHW_HC32F460_SYSCLK_MPLL,

    /** \brief
     *    USBCKʱ��Դѡ��
     *    -# AMHW_HC32F460_CLK_USBCKS_SYSCLK_DIV_2 : ϵͳʱ��2��Ƶ
     *    -# AMHW_HC32F460_CLK_USBCKS_SYSCLK_DIV_3 : ϵͳʱ��3��Ƶ
     *    -# AMHW_HC32F460_CLK_USBCKS_SYSCLK_DIV_4 : ϵͳʱ��4��Ƶ
     *    -# AMHW_HC32F460_CLK_USBCKS_MPLL_P �� MPLL/P
     *    -# AMHW_HC32F460_CLK_USBCKS_MPLL_Q �� MPLL/Q
     *    -# AMHW_HC32F460_CLK_USBCKS_MPLL_R : MPLL/R
     *    -# AMHW_HC32F460_CLK_USBCKS_UPLL_P : UPLL/P
     *    -# AMHW_HC32F460_CLK_USBCKS_UPLL_Q : UPLL/Q
     *    -# AMHW_HC32F460_CLK_USBCKS_UPLL_R ��  UPLL/R
     */
    AMHW_HC32F460_CLK_USBCKS_UPLL_P,


    /*
     * HCLK = SYSCLK / HCLK_DIV�����168MHz
     * ���÷�Χ��CPU��DMAn(n=1,2)��EFM(������)��SRAM0��SRAM1��SRAM2��SRAMHS��Ret-SRAM��
     *         MPU��GPIO��DCU��INTC��QSPI.
     **/
    AMHW_HC32F460_SYSCLK_DIV_1,

    /*
     * EXCLK = SYSCLK / EXCLK_DIV�����84MHz
     * ���÷�Χ��SDIOn(n=1,2)�� CAN
     **/
    AMHW_HC32F460_SYSCLK_DIV_2,

    /*
     *  PCLK0 = SYSCLK / PCLK0_DIV�����168MHz
     *  ���÷�Χ��Timer6��������ʱ��
     **/
    AMHW_HC32F460_SYSCLK_DIV_1,

    /*
     * PCLK1 = SYSCLK / PCLK1_DIV�����84MHz
     * ���÷�Χ��USARTn(n = 1~4)��SPIn(n=1~4)��USBFS(�����߼�)��Timer0n(n=1��2)��TimerAn(n=1~6)��
     *         Timer6(�����߼�)��EMB��CRC��HASH��AES��I2Sn(n=1~4)�����߼�
     **/
    AMHW_HC32F460_SYSCLK_DIV_2,

    /*
     * PCLK2 = SYSCLK / PCLK2_DIV�����60MHz
     * ���÷�Χ��AD�任ʱ��
     **/
    AMHW_HC32F460_SYSCLK_DIV_4,

    /*
     * PCLK3 = SYSCLK / PCLK3_DIV�����42MHz
     * ���÷�Χ��RTC(�����߼�)��I2Cn(n=1��2��3)��CMP��WDT��SWDT(�����߼�)
     **/
    AMHW_HC32F460_SYSCLK_DIV_4,

    /*
     * PCLK4 = SYSCLK / PCLK4_DIV�����84MHz
     * ���÷�Χ�� ADC(�����߼�)��TRNG
     **/
    AMHW_HC32F460_SYSCLK_DIV_2,

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    __hc32f460_clk_plfm_init,

    /** \brief ƽ̨���ʼ������ */
    __hc32f460_clk_plfm_deinit,
};

/** \brief ʱ���豸ʵ�� */
static am_hc32f460_clk_dev_t __g_clk_dev;

/**
 * \brief CLK ʵ����ʼ������ʼ��ϵͳʱ��
 *
 * \retval AM_OK : ʱ�ӳɹ���ʼ��
 */
int am_hc32f460_clk_inst_init (void)
{
    return am_hc32f460_clk_init(&__g_clk_dev, &__g_clk_devinfo);
}

/**
 * @}
 */

/* end of file */

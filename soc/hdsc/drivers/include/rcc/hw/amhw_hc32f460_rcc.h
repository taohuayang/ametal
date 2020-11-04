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
 * \brief
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-23  cds, first implementation
 * \endinternal
 */

#ifndef __AMHW_HC32F460_RCC_H
#define __AMHW_HC32F460_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_clk.h"
#include "hc32f460_regbase.h"
#include "hc32f460_clk.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_hc32f460_if_cmu
 * \copydoc amhw_hc32f460_cmu.h
 * @{
 */

/**
 * \brief sysc�Ĵ�����ṹ��
 */
typedef struct hc32f460_sysc_regs {
         uint8_t  RESERVED0[12];   /**< \brief ���� */
    __IO uint16_t PWR_STPMCR;      /**< \brief STOPģʽ���ѿ��ƼĴ��� */
         uint8_t  RESERVED1[2];    /**< \brief ���� */
    __IO uint16_t CMU_PERICKSEL;   /**< \brief CMU AD/TRNGʱ�����üĴ��� */
    __IO uint16_t CMU_I2SCKSEL;    /**< \brief CMU I2Sʱ�����üĴ��� */
    __IO uint32_t PWR_RAMPC0;      /**< \brief RAM���Ŀ��ƼĴ���0 */
    __IO uint32_t PWR_RAMOPM;      /**< \brief RAM���������Ĵ��� */
    __IO uint32_t MPU_IPPR;        /**< \brief IP���ʱ����Ĵ��� */
    __IO uint32_t CMU_SCFGR;       /**< \brief CMU ʱ�ӷ�Ƶ���üĴ��� */
    __IO uint8_t  CMU_UFSCKCFGR;   /**< \brief CMU USBFSʱ�ӷ�Ƶ���üĴ��� */
         uint8_t  RESERVED8[1];    /**< \brief ���� */
    __IO uint8_t  CMU_CKSWR;       /**< \brief CMU ϵͳʱ��Դ�л��Ĵ��� */
         uint8_t  RESERVED9[3];    /**< \brief ���� */
    __IO uint8_t  CMU_PLLCR;       /**< \brief CMU MPLL���ƼĴ��� */
         uint8_t  RESERVED10[3];   /**< \brief ���� */
    __IO uint8_t  CMU_UPLLCR;      /**< \brief CMU UPLL���ƼĴ��� */
         uint8_t  RESERVED11[3];   /**< \brief ���� */
    __IO uint8_t  CMU_XTALCR;      /**< \brief CMU XTAL���ƼĴ��� */
         uint8_t  RESERVED12[3];   /**< \brief ���� */
    __IO uint8_t  CMU_HRCCR;       /**< \brief CMU HRC���ƼĴ��� */
         uint8_t  RESERVED13[1];   /**< \brief ���� */
    __IO uint8_t  CMU_MRCCR;       /**< \brief CMU MRC���ƼĴ��� */
         uint8_t  RESERVED14[3];   /**< \brief ���� */
    __IO uint8_t  CMU_OSCSTBSR;    /**< \brief CMU ʱ��Դ�ȶ�״̬�Ĵ��� */
    __IO uint8_t  CMU_MCO1CFGR;    /**< \brief CMU MCO1���üĴ��� */
    __IO uint8_t  CMU_MCO2CFGR;    /**< \brief CMU MCO2���üĴ��� */
    __IO uint8_t  CMU_TPIUCKCFGR;  /**< \brief CMU ����ʱ�����üĴ��� */
    __IO uint8_t  CMU_XTALSTDCR;   /**< \brief CMU XTAL�񵴹��Ͽ��ƼĴ��� */
    __IO uint8_t  CMU_XTALSTDSR;   /**< \brief CMU XTAL�񵴹���״̬�Ĵ��� */
         uint8_t  RESERVED20[31];  /**< \brief ���� */
    __IO uint8_t  CMU_MRCTRM;      /**< \brief CMU MRCУ׼�Ĵ��� */
    __IO uint8_t  CMU_HRCTRM;      /**< \brief CMU HRCУ׼�Ĵ��� */
         uint8_t  RESERVED22[63];  /**< \brief ���� */
    __IO uint8_t  CMU_XTALSTBCR;   /**< \brief CMU XTAL�ȶ�ʱ�����üĴ��� */
         uint8_t  RESERVED23[29];  /**< \brief ���� */
    __IO uint16_t RMU_RSTF0;       /**< \brief ��λ��־�Ĵ��� */
         uint8_t  RESERVED24[30];  /**< \brief ���� */
    __IO uint8_t  PWR_PVDICR;      /**< \brief PVD�жϿ��ƼĴ��� */
    __IO uint8_t  PWR_PVDDSR;      /**< \brief PVD���״̬�Ĵ��� */
         uint8_t  RESERVED26[30];  /**< \brief ���� */
    __IO uint32_t CMU_PLLCFGR;     /**< \brief CMU MPLL���üĴ��� */
    __IO uint32_t CMU_UPLLCFGR;    /**< \brief CMU UPLL���ƼĴ��� */
         uint8_t  RESERVED28[758]; /**< \brief ���� */
    __IO uint16_t PWR_FPRC;        /**< \brief ���ܱ������ƼĴ���*/
    __IO uint8_t  PWR_PWRC0;       /**< \brief ��Դģʽ���ƼĴ���0*/
    __IO uint8_t  PWR_PWRC1;       /**< \brief ���ܱ������ƼĴ���1*/
    __IO uint8_t  PWR_PWRC2;       /**< \brief ���ܱ������ƼĴ���2*/
    __IO uint8_t  PWR_PWRC3;       /**< \brief ���ܱ������ƼĴ���3*/
    __IO uint8_t  PWR_PDWKE0;      /**< \brief ���绽��ʹ�ܼĴ���0*/
    __IO uint8_t  PWR_PDWKE1;      /**< \brief ���绽��ʹ�ܼĴ���1*/
    __IO uint8_t  PWR_PDWKE2;      /**< \brief ���绽��ʹ�ܼĴ���2*/
    __IO uint8_t  PWR_PDWKES;      /**< \brief ���绽���¼�����ѡ��Ĵ���*/
    __IO uint8_t  PWR_PDWKF0;      /**< \brief ���绽�ѱ�־�Ĵ���0*/
    __IO uint8_t  PWR_PDWKF1;      /**< \brief ���绽�ѱ�־�Ĵ���1*/
    __IO uint8_t  PWR_PWCMR;       /**< \brief ��Դ���Ĵ���*/
         uint8_t  RESERVED40[4];   /**< \brief ���� */
    __IO uint8_t  PWR_MDSWCR;      /**< \brief ģʽ�л����ƼĴ��� */
    __IO uint8_t  CMU_XTALCFGR;    /**< \brief CMU XTAL���üĴ��� */
         uint8_t  RESERVED42[1];   /**< \brief ���� */
    __IO uint8_t  PWR_PVDCR0;      /**< \brief PVD���ƼĴ���0 */
    __IO uint8_t  PWR_PVDCR1;      /**< \brief PVD���ƼĴ���1 */
    __IO uint8_t  PWR_PVDFCR;      /**< \brief PVD�˲����ƼĴ��� */
    __IO uint8_t  PWR_PVDLCR;      /**< \brief PVD��ƽ���ƼĴ��� */
         uint8_t  RESERVED46[10];  /**< \brief ���� */
    __IO uint8_t  CMU_XTAL32CR;    /**< \brief CMU XTAL32���ƼĴ��� */
    __IO uint8_t  CMU_XTAL32CFGR;  /**< \brief CMU XTAL32���üĴ��� */
         uint8_t  RESERVED48[3];   /**< \brief ���� */
    __IO uint8_t  CMU_XTAL32NFR;   /**< \brief CMU XTAL32�˲��Ĵ��� */
         uint8_t  RESERVED49[1];   /**< \brief ���� */
    __IO uint8_t  CMU_LRCCR;       /**< \brief CMU LRC���ƼĴ��� */
         uint8_t  RESERVED50[1];   /**< \brief ���� */
    __IO uint8_t  CMU_LRCTRM;      /**< \brief CMU LRCУ׼�Ĵ��� */
         uint8_t  RESERVED51[1];   /**< \brief ���� */
    __IO uint8_t  PWR_XTAL32CS;    /**< \brief XTAL32�������ƼĴ��� */
} hc32f460_sysc_regs_t;

#define HC32F460_SYSCREG            ((hc32f460_sysc_regs_t *)HC32F460_SYSC_BASE)

typedef struct hc32f460_mstp_regs {

    __IO uint32_t FCG0;
    __IO uint32_t FCG1;
    __IO uint32_t FCG2;
    __IO uint32_t FCG3;
    __IO uint32_t FCG0_PC;
} hc32f460_mstp_regs_t;

#define HC32F460_MSTP        ((hc32f460_mstp_regs_t *)HC32F460_MSTP_BASE)

/**
 * \brief ����ö��
 */
typedef enum {
    AMHW_HC32F460_HRC_16M = 0,
    AMHW_HC32F460_HRC_20M = 1,
}amhw_hc32f460_clk_hrc_freq;


/**
 * \brief ϵͳʱ��Դ
 */
typedef enum {
    AMHW_HC32F460_SYSCLK_HRC = 0,   /**< \brief �ڲ�����������Ϊϵͳʱ�� */
    AMHW_HC32F460_SYSCLK_MRC,       /**< \brief �ⲿ����������Ϊϵͳʱ�� */
    AMHW_HC32F460_SYSCLK_LRC,       /**< \brief �ڲ�����������Ϊϵͳʱ�� */
    AMHW_HC32F460_SYSCLK_XTAL,      /**< \brief �ⲿ����������Ϊϵͳʱ�� */
    AMHW_HC32F460_SYSCLK_XTAL32,    /**< \brief �ⲿ����������Ϊϵͳʱ�� */
    AMHW_HC32F460_SYSCLK_MPLL = 5,  /**< \brief MPLL��Ϊϵͳʱ�� */
}amhw_hc32f460_sys_clk_src;

/**
 * \brief ϵͳʱ�ӷ�Ƶϵ��(�����������ʱ��)
 */
typedef enum {
    AMHW_HC32F460_SYSCLK_DIV_1 = 0,  /**< \brief ϵͳʱ�ӵ�1��Ƶ */
    AMHW_HC32F460_SYSCLK_DIV_2 = 1,      /**< \brief ϵͳʱ�ӵ�2��Ƶ */
    AMHW_HC32F460_SYSCLK_DIV_4 = 2,      /**< \brief ϵͳʱ�ӵ�4��Ƶ */
    AMHW_HC32F460_SYSCLK_DIV_8 = 3,      /**< \brief ϵͳʱ�ӵ�8��Ƶ */
    AMHW_HC32F460_SYSCLK_DIV_16 = 4,     /**< \brief ϵͳʱ�ӵ�16��Ƶ */
    AMHW_HC32F460_SYSCLK_DIV_32 = 5,     /**< \brief ϵͳʱ�ӵ�32��Ƶ */
    AMHW_HC32F460_SYSCLK_DIV_64 =6     /**< \brief ϵͳʱ�ӵ�64��Ƶ */
}amhw_hc32f460_sys_clk_div;

typedef enum {
    AMHW_HC32F460_CMU_XTAL_SUPDRV_DISABLE = 0,/**< \brief ��ֹ����������*/
    AMHW_HC32F460_CMU_XTAL_SUPDRV_ENABLE,     /**< \brief ������������ */
}amhw_hc32f460_cmu_xtalcfgr_supdrv;

typedef enum {
    AMHW_HC32F460_CMU_XTAL_MODE_OSC    = 0,/**< \brief ����ģʽ */
    AMHW_HC32F460_CMU_XTAL_MODE_INPUT,     /**< \brief �ⲿʱ������ģʽ */
}amhw_hc32f460_cmu_xtalcfgr_mode;

typedef enum {
    AMHW_HC32F460_CMU_XTAL_DRV_HIGH = 0,   /**< \brief ���������� */
    AMHW_HC32F460_CMU_XTAL_DRV_MIDDLER,    /**< \brief ���������� */
    AMHW_HC32F460_CMU_XTAL_DRV_LOW,        /**< \brief С�������� */
    AMHW_HC32F460_CMU_XTAL_DRV_SUPERLOW,   /**< \brief ��С�������� */
}amhw_hc32f460_cmu_xtalcfgr_drv;

typedef struct {
    amhw_hc32f460_cmu_xtalcfgr_supdrv supdrv;
    amhw_hc32f460_cmu_xtalcfgr_mode   mode;
    amhw_hc32f460_cmu_xtalcfgr_drv    drv;
}amhw_hc32f460_cmu_xtalcfg_t;

typedef enum {
    AMHW_HC32F460_CLK_PLLSRC_XTAL = 0,   /**< \brief ѡ���ⲿ����������Ϊ����ʱ�� */
    AMHW_HC32F460_CLK_PLLSRC_HRC,        /**< \brief ѡ���ڲ�����������Ϊ����ʱ�� */
}amhw_hc32f460_clk_pll_src;

typedef struct amhw_hc32f460_clk_pll_cfg{
    uint32_t         PllpDiv;       /**< \brief Pllp clk, division factor of VCO out. */
    uint32_t         PllqDiv;       /**< \brief Pllq clk, division factor of VCO out. */
    uint32_t         PllrDiv;       /**< \brief Pllr clk, division factor of VCO out. */
    uint32_t         plln;          /**< \brief Multiplication factor of vco out, ensure between 240M~480M */
    uint32_t         pllmDiv;       /**< \brief Division factor of VCO in, ensure between 1M~12M. */
}amhw_hc32f460_clk_pll_cfg_t;


/**
 * \brief USBCKʱ��Դ
 */
typedef enum {
    AMHW_HC32F460_CLK_USBCKS_SYSCLK_DIV_2 = 2,   /**< \brief ϵͳʱ��2��Ƶ */
    AMHW_HC32F460_CLK_USBCKS_SYSCLK_DIV_3 = 3,   /**< \brief ϵͳʱ��3��Ƶ */
    AMHW_HC32F460_CLK_USBCKS_SYSCLK_DIV_4 = 4,   /**< \brief ϵͳʱ��4��Ƶ */
    AMHW_HC32F460_CLK_USBCKS_MPLL_P       = 8,   /**< \brief MPLL/P */
    AMHW_HC32F460_CLK_USBCKS_MPLL_Q       = 9,   /**< \brief MPLL/Q */
    AMHW_HC32F460_CLK_USBCKS_MPLL_R       = 10,  /**< \brief MPLL/R */
    AMHW_HC32F460_CLK_USBCKS_UPLL_P       = 11,  /**< \brief UPLL/P */
    AMHW_HC32F460_CLK_USBCKS_UPLL_Q       = 12,  /**< \brief UPLL/Q */
    AMHW_HC32F460_CLK_USBCKS_UPLL_R       = 13,  /**< \brief UPLL/R */
}amhw_hc32f460_clk_usbcks_t;

/**
 * \brief ����ö��
 */
typedef enum {
    /** \brief PWR_CFG0�Ĵ������Ƶ�����ʹ��λ  */
    AMHW_HC32F460_RCC_RAMHS = 0,
    AMHW_HC32F460_RCC_RAM0 = 4,
    AMHW_HC32F460_RCC_ECCRAM = 8,
    AMHW_HC32F460_RCC_RETRAM = 10,
    AMHW_HC32F460_RCC_DMA1 = 14,
    AMHW_HC32F460_RCC_DMA2 = 15,
    AMHW_HC32F460_RCC_FCM = 16,
    AMHW_HC32F460_RCC_PTDIS = 17,
    AMHW_HC32F460_RCC_AES = 20,
    AMHW_HC32F460_RCC_HASH = 21,
    AMHW_HC32F460_RCC_TRNG = 22,
    AMHW_HC32F460_RCC_CRC = 23,
    AMHW_HC32F460_RCC_DCU1 = 24,
    AMHW_HC32F460_RCC_DCU2 = 25,
    AMHW_HC32F460_RCC_DCU3 = 26,
    AMHW_HC32F460_RCC_DCU4 = 27,
    AMHW_HC32F460_RCC_KEY = 31,

    /** \brief PWR_CFG1�Ĵ������Ƶ�����ʹ��λ  */
    AMHW_HC32F460_RCC_CAN  = 0 + 32,
    AMHW_HC32F460_RCC_QSPI = 3 + 32,
    AMHW_HC32F460_RCC_IIC1 = 4 + 32,
    AMHW_HC32F460_RCC_IIC2 = 5 + 32,
    AMHW_HC32F460_RCC_IIC3 = 6 + 32,
    AMHW_HC32F460_RCC_USBFS = 8 + 32,
    AMHW_HC32F460_RCC_SDIOC1 = 10 + 32,
    AMHW_HC32F460_RCC_SDIOC2 = 11 + 32,
    AMHW_HC32F460_RCC_I2S1 = 12 + 32,
    AMHW_HC32F460_RCC_I2S2 = 13 + 32,
    AMHW_HC32F460_RCC_I2S3 = 14 + 32,
    AMHW_HC32F460_RCC_I2S4 = 15 + 32,
    AMHW_HC32F460_RCC_SPI1 = 16 + 32,
    AMHW_HC32F460_RCC_SPI2 = 17 + 32,
    AMHW_HC32F460_RCC_SPI3 = 18 + 32,
    AMHW_HC32F460_RCC_SPI4 = 19 + 32,
    AMHW_HC32F460_RCC_USART1 = 24 + 32,
    AMHW_HC32F460_RCC_USART2 = 25 + 32,
    AMHW_HC32F460_RCC_USART3 = 26 + 32,
    AMHW_HC32F460_RCC_USART4 = 27 + 32,

    /** \brief PWR_CFG2�Ĵ������Ƶ�����ʱ��ʹ��λ  */
    AMHW_HC32F460_RCC_TIMER0_1 = 0 + 64,
    AMHW_HC32F460_RCC_TIMER0_2 = 1 + 64,
    AMHW_HC32F460_RCC_TIMERA_1 = 2 + 64,
    AMHW_HC32F460_RCC_TIMERA_2 = 3 + 64,
    AMHW_HC32F460_RCC_TIMERA_3 = 4 + 64,
    AMHW_HC32F460_RCC_TIMERA_4 = 5 + 64,
    AMHW_HC32F460_RCC_TIMERA_5 = 6 + 64,
    AMHW_HC32F460_RCC_TIMERA_6 = 7 + 64,
    AMHW_HC32F460_RCC_TIMER4_1 = 8 + 64,
    AMHW_HC32F460_RCC_TIMER4_2 = 9 + 64,
    AMHW_HC32F460_RCC_TIMER4_3 = 10 + 64,
    AMHW_HC32F460_RCC_EMB      = 15 + 64,
    AMHW_HC32F460_RCC_TIMER6_1 = 16 + 64,
    AMHW_HC32F460_RCC_TIMER6_2 = 17 + 64,
    AMHW_HC32F460_RCC_TIMER6_3 = 18 + 64,

    /** \brief PWR_CFG3�Ĵ������Ƶ�����ʱ��ʹ��λ  */
    AMHW_HC32F460_RCC_ADC1 = 0 + 96,
    AMHW_HC32F460_RCC_ADC2 = 1 + 96,
    AMHW_HC32F460_RCC_DAC  = 4 + 96,
    AMHW_HC32F460_RCC_CMP  = 8 + 96,
    AMHW_HC32F460_RCC_OTS  = 12 + 96,
} amhw_hc32f460_peripheral;




/**
 * \brief ��ȡ��ǰϵͳʱ��Դ
 *
 * \return ϵͳʱ��Դ��־
 */
am_static_inline
amhw_hc32f460_sys_clk_src amhw_hc32f460_clk_get_sysclk_src(void) {
    return (amhw_hc32f460_sys_clk_src)(HC32F460_SYSCREG->CMU_CKSWR & 0x7);
}

/**
 * \brief ����ʱ�ӼĴ���д���ص�д������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_fprcb0_reg_write_enable (void) {
    HC32F460_SYSCREG->PWR_FPRC = 0xa501;
}

/**
 * \brief ��ֹʱ�ӼĴ���д������д������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_fprcb0_reg_write_disable (void) {
    HC32F460_SYSCREG->PWR_FPRC = 0xa500;
}

/**
 * \brief ����ʱ�ӼĴ���д���ص�д������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_fprcb1_reg_write_enable (void) {
    HC32F460_SYSCREG->PWR_FPRC = 0xa502;
}

/**
 * \brief ��ֹʱ�ӼĴ���д������д������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_fprcb1_reg_write_disable (void) {
    HC32F460_SYSCREG->PWR_FPRC = 0xa500;
}

/**
 * \brief ����ʱ�ӼĴ���д���ص�д������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_fprcb3_reg_write_enable (void) {
    HC32F460_SYSCREG->PWR_FPRC = 0xa508;
}

/**
 * \brief ��ֹʱ�ӼĴ���д������д������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_fprcb3_reg_write_disable (void) {
    HC32F460_SYSCREG->PWR_FPRC = 0xa500;
}

/**
 * \brief ������ʱ�ӼĴ���0��FCG0��д���ص�д������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_fcg0_reg_write_enable (void) {
    HC32F460_MSTP->FCG0_PC = 0xa5a50001;
}

/**
 * \brief ��ֹ����ʱ�ӼĴ���0��FCG0���Ĵ���д������д������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_fcg0_reg_write_disable (void) {
    HC32F460_MSTP->FCG0_PC = 0xa5a50000;
}

/**
 * \brief CMUʱ�ӷ�Ƶ����
 *
 * \param[in] clk_div CMUʱ�ӷ�Ƶ��������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_sysclk_cfg (uint32_t             clk_div)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_SCFGR = clk_div;
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief ��λ����ʱ�ӿ��ƼĴ���
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_reset_mstb_fcg (void) {
    HC32F460_MSTP->FCG0_PC = 0XA5A50001;
    HC32F460_MSTP->FCG0 = 0XFFFFFAEE;
    HC32F460_MSTP->FCG0_PC = 0XA5A50000;
    HC32F460_MSTP->FCG1 = 0XF7FFFFFF;
    HC32F460_MSTP->FCG2 = 0XFFFFFFFF;
    HC32F460_MSTP->FCG3 = 0XFFFFFFFF;
}

/**
 * \brief ��ȡ��ǰFCG�Ĵ�����ֵ
 *
 * \param[in] value_reg ���ڴ�Ŷ�ȡֵ��buffer
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_get_mstb_fcg (uint32_t* value_reg)
{
    value_reg[0] = HC32F460_MSTP->FCG0;
    value_reg[1] = HC32F460_MSTP->FCG1;
    value_reg[2] = HC32F460_MSTP->FCG2;
    value_reg[3] = HC32F460_MSTP->FCG3;
}

/**
 * \brief ����д��FCG�Ĵ�����ֵ
 *
 * \param[in] value_reg ���ڴ��д��ֵ��buffer
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_set_mstb_fcg (uint32_t* value_reg)
{
    HC32F460_MSTP->FCG0_PC = 0XA5A50001;
    HC32F460_MSTP->FCG0 = value_reg[0];
    HC32F460_MSTP->FCG0_PC = 0XA5A50000;
    HC32F460_MSTP->FCG1 = value_reg[1];
    HC32F460_MSTP->FCG2 = value_reg[2];
    HC32F460_MSTP->FCG3 = value_reg[3];
}

/**
 * \brief ϵͳʱ��Դ����
 *
 * \param[in] clk_src ϵͳʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_set_sysclk_src(amhw_hc32f460_sys_clk_src  clk_src)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_CKSWR = clk_src;
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}




/**
 * \brief XTAL����
 *
 * \param[in] xtal_cfg ���ò����ṹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_xtal_cfg (amhw_hc32f460_cmu_xtalcfg_t xtal_cfg)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_XTALCFGR = (xtal_cfg.drv    << 4) |
                                     (xtal_cfg.mode   << 6) |
                                     (xtal_cfg.supdrv << 7);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();

}

/**
 * \brief XTAL������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_xtal_cfg_enable(void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_XTALCR &= ~(0x1ul);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief XTAL����ֹͣ
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_xtal_cfg_disable(void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_XTALCR |=  (0x1ul);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief HRC������
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_hrc_cfg_enable(void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_HRCCR &= ~(0x1ul);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief HRCֹͣ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_hrc_cfg_disable(void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_HRCCR |=  (0x1ul);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief PLLʱ��Դ����
 *
 * \param[in] pll_src ʱ��Դ��amhw_hc32f460_clk_pll_src��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_pll_src_set(amhw_hc32f460_clk_pll_src pll_src)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    if (pll_src == AMHW_HC32F460_CLK_PLLSRC_XTAL) {
        HC32F460_SYSCREG->CMU_PLLCFGR &=  ~(1 << 7);
    } else {
        HC32F460_SYSCREG->CMU_PLLCFGR |=  (1 << 7);
    }
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief MPLLʱ������
 *
 * \param[in] mpll_cfg ���ò����ṹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_mpll_cfg(amhw_hc32f460_clk_pll_cfg_t mpll_cfg)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();

    HC32F460_SYSCREG->CMU_PLLCFGR &= (1 << 7);

    HC32F460_SYSCREG->CMU_PLLCFGR |= (mpll_cfg.pllmDiv  - 1)        |
                                     ((mpll_cfg.plln    - 1) << 8)  |
                                     ((mpll_cfg.PllrDiv - 1) << 20) |
                                     ((mpll_cfg.PllqDiv - 1) << 24) |
                                     ((mpll_cfg.PllqDiv - 1) << 28);

    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief UPLLʱ��ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_upll_enable(void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_UPLLCR &= ~(1ul);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief UPLLʱ������
 *
 * \param[in] upll_cfg ���ò����ṹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_upll_cfg(amhw_hc32f460_clk_pll_cfg_t upll_cfg)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();

    HC32F460_SYSCREG->CMU_UPLLCFGR &= (1 << 7);

    HC32F460_SYSCREG->CMU_UPLLCFGR |= (upll_cfg.pllmDiv  - 1)        |
                                      ((upll_cfg.plln    - 1) << 8)  |
                                      ((upll_cfg.PllrDiv - 1) << 20) |
                                      ((upll_cfg.PllqDiv - 1) << 24) |
                                      ((upll_cfg.PllpDiv - 1) << 28);

    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief MPLLʱ��ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_mpll_enable(void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_PLLCR &= ~(1ul);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}



/**
 * \brief ��ȡʱ��Դ�ȶ�״̬
 *
 * \param[in] clk_src ʱ��ԴID
 *
 * \return ��
 */
am_static_inline
int amhw_hc32f460_clk_status_get(uint32_t clk_src_id)
{
    switch (clk_src_id) {

    case CLK_XTAL:
        if ((HC32F460_SYSCREG->CMU_OSCSTBSR & (1 << 3)) != 0) {
            return 1;/*�ȶ�*/
        } else {
            return 0;
        }
    case CLK_MPLL:
        if ((HC32F460_SYSCREG->CMU_OSCSTBSR & (1 << 5)) != 0) {
            return 1;/*�ȶ�*/
        } else {
            return 0;
        }
    case CLK_UPLL:
        if ((HC32F460_SYSCREG->CMU_OSCSTBSR & (1 << 6)) != 0) {
            return 1;/*�ȶ�*/
        } else {
            return 0;
        }
    case CLK_HRC:
        if ((HC32F460_SYSCREG->CMU_OSCSTBSR & (1 << 3)) != 0) {
            return 1;/*�ȶ�*/
        } else {
            return 0;
        }
    default:
        return AM_ERROR;
    }
}

/**
 * \brief MPLLʱ��ֹͣ
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_mpll_disable(void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_PLLCR |= (1ul);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief CMUʱ�ӷ�Ƶ��ȡ
 *
 * \param[in] clk_src ʱ��ԴID
 *
 * \return ʱ�ӷ�Ƶ
 */
am_static_inline
int amhw_hc32f460_clk_cmu_scfgr_div_get(am_clk_id_t clk_id)
{
    uint8_t clk_div = 1;
    uint32_t reg_val = 0;

    switch (clk_id) {

    case CLK_HCLK:
        reg_val = (HC32F460_SYSCREG->CMU_SCFGR >> 24) & 0X7;
        break;
    case CLK_EXCLK:
        reg_val = (HC32F460_SYSCREG->CMU_SCFGR >> 20) & 0X7;
        break;
    case CLK_PCLK4:
        reg_val = (HC32F460_SYSCREG->CMU_SCFGR >> 16) & 0X7;
        break;
    case CLK_PCLK3:
        reg_val = (HC32F460_SYSCREG->CMU_SCFGR >> 12) & 0X7;
        break;
    case CLK_PCLK2:
        reg_val = (HC32F460_SYSCREG->CMU_SCFGR >> 8) & 0X7;
        break;
    case CLK_PCLK1:
        reg_val = (HC32F460_SYSCREG->CMU_SCFGR >> 4) & 0X7;
        break;
    case CLK_PCLK0:
        reg_val = (HC32F460_SYSCREG->CMU_SCFGR >> 0) & 0X7;
        break;
    default :
        return AM_ERROR;
    }

    while(reg_val--){
        clk_div *= 2;
    }

    return clk_div;
}

/**
 * \brief USBʱ��Դ����
 *
 * \param[in] clk_src ʱ��ԴID
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_clk_cmu_usbcks_set(amhw_hc32f460_clk_usbcks_t clk_src)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_UFSCKCFGR = (clk_src << 4);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief USBʱ��Դ��ȡ
 *
 * \return ʱ��Դʱ��ID
 */
am_static_inline
am_clk_id_t amhw_hc32f460_clk_cmu_usbcks_get(void)
{
    uint32_t reg_val = 0;
    am_clk_id_t clk_id = 0;

    reg_val = (HC32F460_SYSCREG->CMU_UFSCKCFGR >> 4) &(0xF);

    switch (reg_val){

    case 2:
        clk_id = CLK_SYSCLK_DIV2;
        break;
    case 3:
        clk_id = CLK_SYSCLK_DIV3;
        break;
    case 4:
        clk_id = CLK_SYSCLK_DIV4;
        break;
    case 8:
        clk_id = CLK_MPLLP;
        break;
    case 9:
        clk_id = CLK_MPLLQ;
        break;
    case 10:
        clk_id = CLK_MPLLR;
        break;
    case 11:
        clk_id = CLK_UPLLP;
        break;
    case 12:
        clk_id = CLK_UPLLQ;
        break;
    case 13:
        clk_id = CLK_UPLLR;
        break;
    }
    return clk_id;
}

/**
 * \brief TPIUʱ��Դ��ȡ
 *
 * \return ʱ��Դʱ��ID
 */
am_static_inline
am_clk_id_t amhw_hc32f460_clk_cmu_tpiu_src_get(void)
{
    uint8_t reg_val = 0;

    if ((HC32F460_SYSCREG->CMU_TPIUCKCFGR & (1<<7)) == 0) {
        return AM_ERROR;
    }

    reg_val = (HC32F460_SYSCREG->CMU_TPIUCKCFGR) & (0x3ul);

    switch (reg_val) {

    case 0:
        return CLK_SYSCLK_DIV1;
    case 1:
        return CLK_SYSCLK_DIV2;
    case 2:
        return CLK_SYSCLK_DIV4;
    default:
        return AM_ERROR;
    }
}

/**
 * \brief I2Sʱ��Դ��ȡ
 *
 * \param[in]  clk_id ��ʱ��ID
 *
 * \return ʱ��Դʱ��ID
 */
am_static_inline
am_clk_id_t amhw_hc32f460_clk_i2s_src_get(am_clk_id_t clk_id)
{
    am_clk_id_t clk_src_id = 0;
    uint32_t reg_val = 0;

    reg_val = HC32F460_SYSCREG->CMU_I2SCKSEL;

    switch (clk_id) {

    case CLK_I2S1CLK:
        reg_val = (reg_val >> 0) & 0xF;
        break;
    case CLK_I2S2CLK:
        reg_val = (reg_val >> 4) & 0xF;
        break;
    case CLK_I2S3CLK:
        reg_val = (reg_val >> 8) & 0xF;
        break;
    case CLK_I2S4CLK:
        reg_val = (reg_val >> 12) & 0xF;
        break;
    default:
        return AM_ERROR;
    }

    switch (reg_val) {
        case 0:
            clk_src_id = CLK_PCLK3;
            break;
        case 8:
            clk_src_id = CLK_MPLLP;
            break;
        case 9:
            clk_src_id = CLK_MPLLQ;
            break;
        case 10:
            clk_src_id = CLK_MPLLR;
            break;
        case 11:
            clk_src_id = CLK_UPLLP;
            break;
        case 12:
            clk_src_id = CLK_UPLLQ;
            break;
        case 13:
            clk_src_id = CLK_UPLLR;
            break;
        default :
            return AM_ERROR;
    }

    return clk_src_id;
}

/**
 * \brief ʹ������
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 *
 */
void amhw_hc32f460_rcc_peripheral_enable (amhw_hc32f460_peripheral peri);

/**
 * \brief ���ĳ����ʱ���Ƿ�ʹ��
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return 1: ��ǰ����ʱ����ʹ�ܣ������ٴ�ʹ��
 *         0: ��ǰ����ʱ��δʹ��
 *
 */
int amhw_hc32f460_rcc_peripheral_enable_check (amhw_hc32f460_peripheral peri);

/**
 * \brief ��������
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
void amhw_hc32f460_rcc_peripheral_disable (amhw_hc32f460_peripheral peri);

/**
 * \brief MCO1���ʹ��
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hc32f460_rcc_mco1_enable (void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_MCO1CFGR |= (1 << 7);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief MCO1�����ֹ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hc32f460_rcc_mco1_disable (void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_MCO1CFGR &= ~(1 << 7);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief MCO2���ʹ��
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hc32f460_rcc_mco2_enable (void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_MCO2CFGR |= (1 << 7);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief MCO2�����ֹ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hc32f460_rcc_mco2_disable (void)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    HC32F460_SYSCREG->CMU_MCO2CFGR &= ~(1 << 7);
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}


typedef enum {
    AMHW_HC32F460_RCC_MCO_DIV_1 = 0,
    AMHW_HC32F460_RCC_MCO_DIV_2,
    AMHW_HC32F460_RCC_MCO_DIV_4,
    AMHW_HC32F460_RCC_MCO_DIV_8,
    AMHW_HC32F460_RCC_MCO_DIV_16,
    AMHW_HC32F460_RCC_MCO_DIV_32,
    AMHW_HC32F460_RCC_MCO_DIV_64,
    AMHW_HC32F460_RCC_MCO_DIV_128,
} amhw_hc32f460_rcc_mco_div_t;

typedef enum {
    AMHW_HC32F460_RCC_MCO_SRC_HRC    = 0,
    AMHW_HC32F460_RCC_MCO_SRC_MRC    = 1,
    AMHW_HC32F460_RCC_MCO_SRC_LRC    = 2,
    AMHW_HC32F460_RCC_MCO_SRC_XTAL   = 3,
    AMHW_HC32F460_RCC_MCO_SRC_XTAL32 = 4,
    AMHW_HC32F460_RCC_MCO_SRC_MPLLP  = 6,
    AMHW_HC32F460_RCC_MCO_SRC_UPLLP  = 7,
    AMHW_HC32F460_RCC_MCO_SRC_MPLLQ  = 8,
    AMHW_HC32F460_RCC_MCO_SRC_UPLLQ  = 9,
    AMHW_HC32F460_RCC_MCO_SRC_SYSCLK = 11,
} amhw_hc32f460_rcc_mco_src_t;

/**
 * \brief MCO1��Ƶѡ��
 *
 * \param[in]  clk_div ��ʱ�ӷ�Ƶ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hc32f460_rcc_mco1_div_set (amhw_hc32f460_rcc_mco_div_t mco1_div)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    uint8_t reg_val = HC32F460_SYSCREG->CMU_MCO1CFGR;
    reg_val &= ~(0x7 << 4);
    reg_val |= (mco1_div << 4);
    HC32F460_SYSCREG->CMU_MCO1CFGR = reg_val;
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief MCO1ʱ��Դѡ��
 *
 * \param[in]  clk_src ��ʱ��Դ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hc32f460_rcc_mco1_src_set (amhw_hc32f460_rcc_mco_src_t mco1_src)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    uint8_t reg_val = HC32F460_SYSCREG->CMU_MCO1CFGR;
    reg_val &= ~0xF;
    reg_val |= mco1_src;
    HC32F460_SYSCREG->CMU_MCO1CFGR = reg_val;
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief MCO2��Ƶѡ��
 *
 * \param[in]  clk_div ��ʱ�ӷ�Ƶ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hc32f460_rcc_mco2_div_set (amhw_hc32f460_rcc_mco_div_t mco2_div)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    uint8_t reg_val = HC32F460_SYSCREG->CMU_MCO2CFGR;
    reg_val &= ~(0x7 << 4);
    reg_val |= (mco2_div << 4);
    HC32F460_SYSCREG->CMU_MCO2CFGR = reg_val;
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/**
 * \brief MCO2ʱ��Դѡ��
 *
 * \param[in]  clk_src ��ʱ��Դ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_hc32f460_rcc_mco2_src_set (amhw_hc32f460_rcc_mco_src_t mco2_src)
{
    amhw_hc32f460_clk_fprcb0_reg_write_enable();
    uint8_t reg_val = HC32F460_SYSCREG->CMU_MCO2CFGR;
    reg_val &= ~0xF;
    reg_val |= mco2_src;
    HC32F460_SYSCREG->CMU_MCO2CFGR = reg_val;
    amhw_hc32f460_clk_fprcb0_reg_write_disable();
}

/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __HC32F460_RCC_H */

#endif

/* end of file */

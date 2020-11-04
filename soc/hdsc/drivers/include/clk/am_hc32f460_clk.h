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
 * \brief CLK������ʱ�ӱ�׼����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-23  cds, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_CLK_H
#define __AM_HC32F460_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_clk.h"
#include "hw/amhw_hc32f460_rcc.h"

/**
 * \addtogroup am_hc32f460_if_clk
 * \copydoc am_hc32f460_clk.h
 * @{
 */

/**
 * \brief CLK �豸��Ϣ�����ṹ��
 */
typedef struct am_hc32f460_clk_devinfo {

    /**
     * \brief XTHOSC�ⲿ����Ƶ��
     */
    uint32_t xth_osc;

    /**
     * \brief XTLOSC�ⲿ����Ƶ��
     */
    uint32_t xtl_osc;

    /**
     * \brief HRC�ڲ�����ʱ�Ӿ���Ƶ�ʣ�Hz��
     *
     * \note Ƶ��ѡ��    24M�� 22.12M��16M�� 8M��4M
     *       ��������Ƶ�ʣ���Ĭ��ʹ��4M
     */
    amhw_hc32f460_clk_hrc_freq hrc_osc;


    /** \brief
     *    PLL ʱ��Դѡ��
     *    -# AMHW_HC32F460_CLK_PLLSRC_XTAL : �ⲿ����������Ϊ����ʱ��
     *    -# AMHW_HC32F460_CLK_PLLSRC_HRC : �ڲ�����������Ϊ����ʱ��
     */
    amhw_hc32f460_clk_pll_src pllin_src;

    /**
     * \brief MPLL ���ʱ������
     *        MPLLP = PLLIN / mpll_div * mpll_mul / mpllp_div��
     *        MPLLQ = PLLIN / mpll_div * mpll_mul / mpllq_div��
     *        MPLLR = PLLIN / mpll_div * mpll_mul / mpllr_div��
     */
    uint8_t mpll_div;     /* MPLL ����ʱ�ӷ�Ƶϵ��,Ӧȷ��MPLLIN����1MHz��12MHz֮�� */
    uint8_t mpll_mul;     /* MPLL ���ʱ�ӱ�Ƶϵ�� */
    uint8_t mpllp_div;    /* MPLLPʱ�ӷ�Ƶϵ�� */
    uint8_t mpllq_div;    /* MPLLQʱ�ӷ�Ƶϵ�� */
    uint8_t mpllr_div;    /* MPLLRʱ�ӷ�Ƶϵ�� */

    /**
     * \brief UPLL ����ʱ�ӷ�Ƶϵ��
     *        UPLLP = PLLIN / upll_div * upll_mul / upllp_div��
     *        UPLLQ = PLLIN / upll_div * upll_mul / upllq_div��
     *        UPLLR = PLLIN / upll_div * upll_mul / upllr_div��
     */
    uint8_t upll_div;     /* UPLL ����ʱ�ӷ�Ƶϵ��,Ӧȷ��UPLLIN����1MHz��12MHz֮�� */
    uint8_t upll_mul;     /* UPLL ���ʱ�ӱ�Ƶϵ�� */
    uint8_t upllp_div;    /* UPLLPʱ�ӷ�Ƶϵ�� */
    uint8_t upllq_div;    /* UPLLQʱ�ӷ�Ƶϵ�� */
    uint8_t upllr_div;    /* UPLLRʱ�ӷ�Ƶϵ�� */

    /** \brief
     *    ϵͳʱ��Դѡ��
     *    -# AMHW_HC32F460_SYSCLK_RCH : �ڲ�����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_XTH : �ⲿ����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_RCL : �ڲ�����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_XTL ��  �ⲿ����ʱ����Ϊϵͳʱ��
     *    -# AMHW_HC32F460_SYSCLK_PLL �� �ڲ�PLL��Ϊϵͳʱ��
     */
    amhw_hc32f460_sys_clk_src sysclk_src;

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
    amhw_hc32f460_clk_usbcks_t usbck_src;

    uint8_t hclk_div;

    uint8_t exclk_div;

    uint8_t pclk0_div;

    uint8_t pclk1_div;

    uint8_t pclk2_div;

    uint8_t pclk3_div;

    uint8_t pclk4_div;

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    void  (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void  (*pfn_plfm_deinit)(void);

} am_hc32f460_clk_devinfo_t;

/**
 * \brief CLK �豸�ṹ��
 */
typedef struct am_hc32f460_clk_dev {

    /** \brief ָ��CLK �豸��Ϣ��ָ�� */
    const am_hc32f460_clk_devinfo_t *p_devinfo;

    /** \brief PLL����Ƶ�� */
    uint32_t pllin_clk;

    /** \brief MPLL���Ƶ�� */
    uint32_t mpllout_clk;

    /** \brief UPLL���Ƶ�� */
    uint32_t upllout_clk;

    /** \brief MPLLP���Ƶ�� */
    uint32_t mpllpout_clk;
    /** \brief MPLLQ���Ƶ�� */
    uint32_t mpllqout_clk;
    /** \brief MPLLR���Ƶ�� */
    uint32_t mpllrout_clk;

    /** \brief UPLLP���Ƶ�� */
    uint32_t upllpout_clk;
    /** \brief UPLLQ���Ƶ�� */
    uint32_t upllqout_clk;
    /** \brief UPLLR���Ƶ�� */
    uint32_t upllrout_clk;

    /** \brief sys���Ƶ�� */
    uint32_t sys_clk;

    /** \brief sys���� */
    amhw_hc32f460_sys_clk_src sys_type;

    /** \brief ϵͳʱ��Ƶ�� */
    uint32_t hclk;

    /** \brief ����ʱ��Ƶ�� */
    uint32_t pclk0;

    /** \brief ����ʱ��Ƶ�� */
    uint32_t pclk1;

    /** \brief ����ʱ��Ƶ�� */
    uint32_t pclk2;

    /** \brief ����ʱ��Ƶ�� */
    uint32_t pclk3;

    /** \brief ����ʱ��Ƶ�� */
    uint32_t pclk4;
} am_hc32f460_clk_dev_t;

/**
 * \brief CLK ��ʼ��
 *
 * \param[in] p_dev     : ָ��CLK�豸��ָ��
 * \param[in] p_devinfo : ָ��CLK�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_hc32f460_clk_init (am_hc32f460_clk_dev_t           *p_dev,
                          const am_hc32f460_clk_devinfo_t *p_devinfo);

/**
 * \brief CLK ���踴λ
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \retval AM_OK : �����ɹ�
 */
int am_hc32f460_clk_reset (am_clk_id_t clk_id);

/**
 * \brief ��������Ƶ��ֵ
 *
 *  ������Ƶ�ʱ���������ʱ����Ҫ���ô˺������������ڲ��洢��Ƶ��ֵ
 *  ����CLK_AHB��CLK_APB1��CLK_APB2��Ч
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 * \param[in] clk     ���µ�Ƶ��ֵ
 *
 * \retval AM_OK : �����ɹ�
 *
 * \note ע���˺�������
 */
int am_hc32f460_clk_update (am_clk_id_t clk_id, int clk);

/**
 * \brief ��ȡPLL������ʱ��Դ
 *  ����CLK_AHB��CLK_APB1��CLK_APB2��Ч
 *
 * \return clk��ʱ��������Ϣ
 */
const am_hc32f460_clk_dev_t *am_hc32f460_clk_devinfo_get (void);

/**
 * \brief �������߻������CLK��Ƶֵ
 *
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \return: ���ض�Ӧ���߻�����ķ�Ƶֵ
 *
 */
int am_hc32f460_div_get (am_clk_id_t clk_id);

void SystemClk_Init(void);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_CLK_H */

/* end of file */

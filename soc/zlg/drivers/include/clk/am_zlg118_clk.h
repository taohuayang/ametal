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
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG118_CLK_H
#define __AM_ZLG118_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_clk.h"
#include "hw/amhw_zlg118_rcc.h"

/**
 * \addtogroup am_zlg118_if_clk
 * \copydoc am_zlg118_clk.h
 * @{
 */

/**
 * \brief CLK �豸��Ϣ�����ṹ��
 */
typedef struct am_zlg118_clk_devinfo {

    /**
     * \brief XTHOSC�ⲿ����Ƶ��
     */
    uint32_t xth_osc;

    /**
     * \brief XTLOSC�ⲿ����Ƶ��
     */
    uint32_t xtl_osc;

    /**
     * \brief RCH�ڲ�����ʱ�Ӿ���Ƶ�ʣ�Hz��
     *
     * \note Ƶ��ѡ��    24M�� 22.12M��16M�� 8M��4M
     *       ��������Ƶ�ʣ���Ĭ��ʹ��4M
     */
    amhw_zlg118_rch_fre_t rch_osc;

    /**
     * \brief RCL�ڲ�����ʱ�Ӿ���Ƶ�ʣ�Hz��
     *
     * \note Ƶ��ѡ��    38.4k  ��      32.768K
     *       ��������Ƶ�ʣ���Ĭ��ʹ��38.4k
     */
    amhw_zlg118_rcl_fre_t rcl_osc;

    /** \brief
     *    PLL ʱ��Դѡ��
     *    -# AMHW_ZLG118_PLL_INPUT_FRE_SRC_XTH_XTAL : XTH�������ɵ�ʱ��
     *    -# AMHW_ZLG118_PLL_INPUT_FRE_SRC_XTH_PF00 : XTH�ӹܽ�PF00�����ʱ��
     *    -# AMHW_ZLG118_PLL_INPUT_FRE_SRC_XTH_RCH  : RCHʱ��
     */
    amhw_zlg118_pll_input_fre_src pllin_src;

    /**
     * \brief PLL ��Ƶϵ��������Χ0X2~0XC
     *        PLLOUT = PLLIN * pll_mul
     */
    uint8_t pll_mul;

    /** \brief
     *    ϵͳʱ��Դѡ��
     *    -# AMHW_ZLG118_SYSCLK_RCH : �ڲ�����ʱ����Ϊϵͳʱ��
     *    -# AMHW_ZLG118_SYSCLK_XTH : �ⲿ����ʱ����Ϊϵͳʱ��
     *    -# AMHW_ZLG118_SYSCLK_RCL : �ڲ�����ʱ����Ϊϵͳʱ��
     *    -# AMHW_ZLG118_SYSCLK_XTL ��  �ⲿ����ʱ����Ϊϵͳʱ��
     *    -# AMHW_ZLG118_SYSCLK_PLL �� �ڲ�PLL��Ϊϵͳʱ��
     */
    amhw_zlg118_sys_clk_src sysclk_src;

    /**
     * \brief HCLK = SYSCLK / (2 ^ hclk_div)
     */
    uint8_t hclk_div;

    /**
     * \brief PCLK��Ƶϵ����PCLK = HCLK / (2 ^ pclk_div)
     */
    uint8_t pclk_div;

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    void  (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void  (*pfn_plfm_deinit)(void);

} am_zlg118_clk_devinfo_t;

/**
 * \brief CLK �豸�ṹ��
 */
typedef struct am_zlg118_clk_dev {

    /** \brief ָ��CLK �豸��Ϣ��ָ�� */
    const am_zlg118_clk_devinfo_t *p_devinfo;

    /** \brief PLL����Ƶ�� */
    uint32_t pllin_clk;

    /** \brief PLL���Ƶ�� */
    uint32_t pllout_clk;

    /** \brief sys���Ƶ�� */
    uint32_t sys_clk;

    /** \brief sys���� */
    amhw_zlg118_sys_clk_src sys_type;

    /** \brief ϵͳʱ��Ƶ�� */
    uint32_t hclk;

    /** \brief ����ʱ��Ƶ�� */
    uint32_t pclk;
} am_zlg118_clk_dev_t;

/**
 * \brief CLK ��ʼ��
 *
 * \param[in] p_dev     : ָ��CLK�豸��ָ��
 * \param[in] p_devinfo : ָ��CLK�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zlg118_clk_init (am_zlg118_clk_dev_t           *p_dev,
                        const am_zlg118_clk_devinfo_t *p_devinfo);

/**
 * \brief CLK ���踴λ
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zlg118_clk_reset (am_clk_id_t clk_id);

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
int am_zlg118_clk_update (am_clk_id_t clk_id, int clk);

/**
 * \brief ��ȡPLL������ʱ��Դ
 *  ����CLK_AHB��CLK_APB1��CLK_APB2��Ч
 *
 * \return clk��ʱ��������Ϣ
 */
const am_zlg118_clk_dev_t *am_zlg118_clk_devinfo_get (void);

/**
 * \brief �������߻������CLK��Ƶֵ
 *
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \return: ���ض�Ӧ���߻�����ķ�Ƶֵ
 *
 */
int am_zlg118_div_get (am_clk_id_t clk_id);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_CLK_H */

/* end of file */

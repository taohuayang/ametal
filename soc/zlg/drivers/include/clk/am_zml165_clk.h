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
 * - 1.00 17-04-12  sdy, first implementation
 * \endinternal
 */

#ifndef __AM_ZML165_CLK_H
#define __AM_ZML165_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_clk.h"
#include "hw/amhw_zml165_rcc.h"

/**
 * \addtogroup am_zml165_if_clk
 * \copydoc am_zml165_clk.h
 * @{
 */
/* \brief �ڲ���������Ƶ��������  */
#define  AM_ZML165_HSI_72M         72000000
#define  AM_ZML165_HSI_48M         48000000


/**
 * \brief CLK �豸��Ϣ�����ṹ��
 */
typedef struct am_zml165_clk_devinfo {

    /**
     * \brief HSEOSC�ⲿ����Ƶ��
     *
     *  ���pllin_srcѡ�� AMHW_ZML165_PLLCLK_HSE �� PLLIN = hse_osc��
     */
    uint32_t input_clk;

    /**
     * \brief ϵͳʱ��Դѡ��
     */
    amhw_zml165_sys_clk_src sys_clk_src;
    /**
     * \brief AHB��Ƶϵ����AHBCLK = PLLOUT / DIV,AHB���Ƶ��Ϊ48Mhz
     *
     *    ahb_div |  DIV
     *   ---------------------
     *        0-7 |   1
     *        8   |   2
     *        9   |   4
     *        10  |   8
     *        11  |   16
     *        12  |   64
     *        13  |  128
     *        14  |  256
     *        15  |  512
     */
    uint8_t ahb_div;

    /**
     * \brief APB1��Ƶϵ����APB1CLK = AHBCLK / (2 ^ apb1_div)
     *        APB1���Ƶ��Ϊ48Mhz
     */
    uint8_t apb1_div;

    /**
     * \brief APB2��Ƶϵ����APB2CLK = AHBCLK / (2 ^ apb2_div)
     *        APB2���Ƶ��Ϊ48Mhz
     */
    uint8_t apb2_div;

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    void  (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void  (*pfn_plfm_deinit)(void);

} am_zml165_clk_devinfo_t;

/**
 * \brief CLK �豸�ṹ��
 */
typedef struct am_zml165_clk_dev {

    /** \brief ָ��CLK �豸��Ϣ��ָ�� */
    const am_zml165_clk_devinfo_t *p_devinfo;

    /** \brief ϵͳ����Ƶ�� */
    uint32_t sys_clk;

    /** \brief AHBʱ��Ƶ�� */
    uint32_t ahb_clk;

    /** \brief APB1ʱ��Ƶ�� */
    uint32_t apb1_clk;

    /** \brief APB2ʱ��Ƶ�� */
    uint32_t apb2_clk;

    /** \brief USBʱ��Ƶ�� */
    uint32_t usb_clk;

} am_zml165_clk_dev_t;

/**
 * \brief CLK ��ʼ��
 *
 * \param[in] p_dev     : ָ��CLK�豸��ָ��
 * \param[in] p_devinfo : ָ��CLK�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zml165_clk_init (am_zml165_clk_dev_t           *p_dev,
                        const am_zml165_clk_devinfo_t *p_devinfo);

/**
 * \brief CLK ���踴λ
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zml165_clk_reset (am_clk_id_t clk_id);

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
int am_zml165_clk_update (am_clk_id_t clk_id, int clk);

/**
 * \brief ��ȡPLL������ʱ��Դ
 *  ����CLK_AHB��CLK_APB1��CLK_APB2��Ч
 *
 * \return clk��ʱ��������Ϣ
 */
const am_zml165_clk_dev_t *am_zml165_clk_devinfo_get (void);

/**
 * \brief �������߻������CLK��Ƶֵ
 *
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \return: ���ض�Ӧ���߻�����ķ�Ƶֵ
 *
 */
int am_zml165_div_get (am_clk_id_t clk_id);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZML165_CLK_H */

/* end of file */

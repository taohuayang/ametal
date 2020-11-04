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
 * \brief ZML165��Դ����(�͹���ģʽ�����ļ�)
 * \sa am_hwconf_zml165_pwr.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-18  nwt, first implementation.
 * \endinternal
 */

#include "am_zml165.h"
#include "am_zml165_pwr.h"
#include "am_zml165_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zml165_pwr
 * \copydoc am_hwconf_zml165_pwr.c
 * @{
 */

/** \brief PWRƽ̨��ʼ�� */
void __zml165_plfm_pwr_init (void)
{

    /* PWR��Դ�ӿ�ʱ��ʹ�� */
    am_clk_enable(CLK_PWR);

    /* ��λPWR��Դ�ӿ� */
    am_zml165_clk_reset(CLK_PWR);
}

/** \brief PWRƽ̨ȥ��ʼ�� */
void __zml165_plfm_pwr_deinit (void)
{

    /* ��λPWR��Դ�ӿ� */
    am_zml165_clk_reset(CLK_PWR);

    /* ����PWR�������ʱ�� */
    am_clk_disable(CLK_PWR);

}
/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct am_zml165_pwr_mode_init __g_pwr_mode_init[3] = {
     {AM_ZML165_PWR_MODE_SLEEP,   PIOA_8},
     {AM_ZML165_PWR_MODE_STOP,    PIOA_8},
     {AM_ZML165_PWR_MODE_STANBY,  PIOA_0},
};

/** \brief PVD������Ϣ�ڴ� */
static struct am_zml165_pwr_pvd_info __g_pwr_pvd_info = {
     AMHW_ZLG_PVD_LEVER_3_3V,    /**< \brief PVD��ص�ѹ */
     AM_TRUE,                    /**< \brief ʹ�ܼ�ص�ѹ */
     2,                          /**< \brief ��ص�ѹģʽ */
};

/** \brief PWR�豸��Ϣ */
const am_zml165_pwr_devinfo_t __g_pwr_devinfo = {
    ZML165_PWR_BASE,        /**< \brief PWR�������Ĵ������ַ */
    ZML165_BKP_BASE,        /**< \brief BKP���üĴ������ַ */
	ZML165_EXTI_BASE,       /**< \brief EXTI�Ĵ������ַ */
    CLK_AHB,                /**< \brief AHBʱ��ID */
    CLK_APB1,               /**< \brief APB1ʱ��ID */
    CLK_APB2,               /**< \brief APB2ʱ��ID */
    INUM_PVD,               /**< \brief pvd�ж�ID */
    __g_pwr_mode_init,      /**< \brief ָ��pwr����ģʽ�����ָ�� */
    &__g_pwr_pvd_info,      /**< \brief ָ��pvd��ѹ�����Ϣ��ָ�� */
    __zml165_plfm_pwr_init,
    __zml165_plfm_pwr_deinit
};

/** \brief PWR�豸ʵ�� */
am_zml165_pwr_dev_t __g_pwr_dev;

/** \brief PWR ʵ����ʼ�� */
am_zml165_pwr_handle_t am_zml165_pwr_inst_init (void)
{
    return am_zml165_pwr_init(&__g_pwr_dev, &__g_pwr_devinfo);
}

/** \brief PWR ʵ�����ʼ�� */
void am_zml165_pwr_inst_deinit (void)
{
    am_zml165_pwr_deinit();
}

/**
 * @}
 */

/* end of file */

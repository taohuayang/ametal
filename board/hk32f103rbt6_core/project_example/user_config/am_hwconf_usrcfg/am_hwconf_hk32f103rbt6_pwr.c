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
 * \brief HK32F103RBT6 ��Դ����(�͹���ģʽ)�û������ļ�
 * \sa am_hwconf_hk32f103rbt6_pwr.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-13  fra, first implementation
 * \endinternal
 */

#include <am_hk32f103rbt6.h>
#include <am_hk32f103rbt6_clk.h>
#include <am_hk32f103rbt6_pwr.h>

/**
 * \addtogroup am_if_src_hwconf_hk32f103rbt6_pwr
 * \copydoc am_hwconf_hk32f103rbt6_pwr.c
 * @{
 */

/** \brief PWRƽ̨��ʼ�� */
void __hk32f103rbt6_plfm_pwr_init (void)
{
    am_clk_enable(CLK_PWR);
    am_hk32f103rbt6_clk_reset(CLK_PWR);
}

/** \brief PWRƽ̨ȥ��ʼ�� */
void __hk32f103rbt6_plfm_pwr_deinit (void)
{
    am_hk32f103rbt6_clk_reset(CLK_PWR);
    am_clk_disable(CLK_PWR);
}

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct am_hk32f103rbt6_pwr_mode_init __g_pwr_mode_init[3] = {
     {AM_HK32F103RBT6_PWR_MODE_SLEEP,  PIOC_7},
     {AM_HK32F103RBT6_PWR_MODE_STOP,   PIOC_7},
     {AM_HK32F103RBT6_PWR_MODE_STANBY, PIOA_0},
};

/** \brief PVD������Ϣ�ڴ� */
static struct am_hk32f103rbt6_pwr_pvd_info __g_pwr_pvd_info = {
     AMHW_HK32F103RBT6_PVD_LEVER_2_9V,    /**< \brief PVD��ص�ѹ */
     2,                             /**< \brief ��ص�ѹģʽ */
     AM_TRUE,                       /**< \brief ʹ�ܼ�ص�ѹ */
};

/** \brief PWR�豸��Ϣ */
const am_hk32f103rbt6_pwr_devinfo_t __g_pwr_devinfo = {
    HK32F103RBT6_PWR_BASE,            /**< \brief PWR�������Ĵ������ַ */
    HK32F103RBT6_BKP_BASE,            /**< \brief BKP���üĴ������ַ */
    CLK_AHB,                    /**< \brief AHBʱ��ID */
    CLK_APB1,                   /**< \brief APB1ʱ��ID */
    CLK_APB2,                   /**< \brief APB2ʱ��ID */
    INUM_PVD,                   /**< \brief pvd�ж�ID */
    __g_pwr_mode_init,          /**< \brief ָ��pwr����ģʽ�����ָ�� */
    &__g_pwr_pvd_info,          /**< \brief ָ��pvd��ѹ�����Ϣ��ָ�� */
    __hk32f103rbt6_plfm_pwr_init,
    __hk32f103rbt6_plfm_pwr_deinit
};

/** \brief PWR�豸ʵ�� */
am_hk32f103rbt6_pwr_dev_t __g_pwr_dev;

/** \brief PWR ʵ����ʼ�� */
am_hk32f103rbt6_pwr_handle_t am_hk32f103rbt6_pwr_inst_init (void)
{
    return am_hk32f103rbt6_pwr_init(&__g_pwr_dev, &__g_pwr_devinfo);
}

/** \brief PWR ʵ�����ʼ�� */
void am_hk32f103rbt6_pwr_inst_deinit (void)
{
    am_hk32f103rbt6_pwr_deinit();
}

/**
 * @}
 */

/* end of file */

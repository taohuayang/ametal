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
 * \brief STM32F103RBT6 WWDT �û������ļ�
 * \sa am_hwconf_stm32f103rbt6_wwdg.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-24  zcb, first implementation
 * \endinternal
 */

#include "am_stm32f103rbt6.h"
#include "am_stm32f103rbt6_wwdg.h"
#include "am_stm32f103rbt6_clk.h"
#include "amhw_stm32f103rbt6_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_stm32f103rbt6_wwdg
 * \copydoc am_hwconf_stm32f103rbt6_wwdg.c
 * @{
 */

/** \brief WWDT ƽ̨��ʼ�� */
static void __stm32f103rbt6_wwdg_plfm_init (void)
{
    am_clk_enable(CLK_WWDG);
    am_stm32f103rbt6_clk_reset(CLK_WWDG);

    /* ��鸴λ�Ƿ��ɿ��Ź���ɵ� */
    if (amhw_stm32f103rbt6_rcc_reset_flag() & AMHW_STM32F103RBT6_RCC_CSR_WWDGRSTF) {
        amhw_stm32f103rbt6_rcc_reset_flag_clear();
    }
}

/** \brief ���WWDT ƽ̨��ʼ�� */
static void __stm32f103rbt6_wwdg_plfm_deinit (void)
{
    am_clk_disable(CLK_WWDG);
}

/** \brief WWDT �豸��Ϣ */
static const am_stm32f103rbt6_wwdg_devinfo_t  __g_wwdg_devinfo = {
    STM32F103RBT6_WWDG_BASE,          /**< \brief WWDT�Ĵ�����ַ */
    CLK_WWDG,                  /**< \brief ʱ��ID */
    __stm32f103rbt6_wwdg_plfm_init,   /**< \brief WWDT ƽ̨��ʼ�� */
    __stm32f103rbt6_wwdg_plfm_deinit, /**< \brief ���WWDT ƽ̨��ʼ�� */
};

/** \brief WWDT�豸ʵ�� */
static am_stm32f103rbt6_wwdg_dev_t __g_wwdg_dev;

/**
 * \brief WWDT ʵ����ʼ�������WDT��׼������
 */
am_wdt_handle_t am_stm32f103rbt6_wwdg_inst_init (void)
{
    return am_stm32f103rbt6_wwdg_init(&__g_wwdg_dev, &__g_wwdg_devinfo);
}

/**
 * \brief WWDT ʵ�����ʼ��
 */
void am_stm32f103rbt6_wwdg_inst_deinit (am_wdt_handle_t handle)
{
    am_stm32f103rbt6_wwdg_deinit(handle);
}

/**
 * @}
 */

/* end of file */

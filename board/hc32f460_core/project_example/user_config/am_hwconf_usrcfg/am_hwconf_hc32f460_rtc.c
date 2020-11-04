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
 * \brief HC32F460 RTC �û������ļ�
 * \sa am_hwconf_hc32f460_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-17  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_hc32f460.h"
#include "am_clk.h"
#include "am_hc32f460_rtc.h"
#include "hw/amhw_hc32f460_rcc.h"
#include "am_hc32f460_inst_init.h"
#include "hc32f460_periph_map.h"
#include "hc32f460_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_rtc
 * \copydoc am_hwconf_hc32f460_rtc.c
 * @{
 */

/** \brief RTC ƽ̨��ʼ�� */
void __hc32f460_plfm_rtc_init()
{
    am_clk_enable(CLK_XTAL32);
}

/** ��� RTC ƽ̨��ʼ�� */
void __hc32f460_plfm_rtc_deinit(void)
{
    am_clk_disable(CLK_XTAL32);
}

/** \brief RTC�豸��Ϣ */
const struct am_hc32f460_rtc_devinfo __g_rtc_devinfo = {

    /** \brief RTC�豸����ַ */
    HC32F460_RTC_BASE,

    /**< \brief RTC �жϺ� */
    INUM_RTC,

    /** \brief ƽ̨��ʼ������ */
    __hc32f460_plfm_rtc_init,

    /** \brief ƽ̨ȥ��ʼ������ */
    __hc32f460_plfm_rtc_deinit
};

/** \brief RTC�豸 */
am_hc32f460_rtc_dev_t __g_rtc_dev;

/** \brief rtc ʵ����ʼ�������rtc��׼������ */
am_rtc_handle_t am_hc32f460_rtc_inst_init (void)
{
    return am_hc32f460_rtc_init(&__g_rtc_dev, &__g_rtc_devinfo);
}

/**
 * \brief rtc ʵ�����ʼ��
 * \param[in] handle : rtc���ֵ
 */
void am_hc32f460_rtc_inst_deinit (am_rtc_handle_t handle)
{
    am_hc32f460_rtc_deinit(handle);
}

/**
 * @}
 */

/** end of file */

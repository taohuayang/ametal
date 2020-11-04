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
 * \brief HC32 RTC �û������ļ�
 * \sa am_hwconf_hc32_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-17  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_hc32.h"
#include "am_clk.h"
#include "am_hc32_rtc.h"
#include "hw/amhw_hc32_rcc.h"
#include "am_hc32f03x_inst_init.h"
#include "hc32_periph_map.h"
#include "hc32_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_rtc
 * \copydoc am_hwconf_hc32_rtc.c
 * @{
 */

/** \brief RTC ƽ̨��ʼ�� */
void __hc32_plfm_rtc_init()
{
    /* �ⲿ������������ѡ�� */
    amhw_hc32_rcc_xtl_xtal_driver_set(AMHW_HC32_XTL_XTAL_DRIVER_DEFAULT);

    /* XTL�����񵴷��ȵĵ��� */
    amhw_hc32_rcc_xtl_xtal_amplitude_set(
    AMHW_HC32_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

    /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
    amhw_hc32_rcc_xtl_waittime_set(AMHW_HC32_XTL_WAITTIME_16384);

    amhw_hc32_rcc_set_start(0x5A5A);
    amhw_hc32_rcc_set_start(0xA5A5);
    amhw_hc32_rcc_xtl_enable();

    /* �ȴ��ȶ�*/
    while(amhw_hc32_rcc_xtl_state_get() == AM_FALSE);

    am_clk_enable(CLK_RTC);

    /* RTC ʱ��Դѡ�� */
    amhw_hc32_rtc_clk_src_sel(HC32_RTC, AMHW_HC32_RTC_CLK_SRC_XTL_32768Hz);
}

/** ��� RTC ƽ̨��ʼ�� */
void __hc32_plfm_rtc_deinit(void)
{
    am_clk_disable(CLK_RTC);
}

/** \brief RTC�豸��Ϣ */
const struct am_hc32_rtc_devinfo __g_rtc_devinfo = {

    /** \brief RTC�豸����ַ */
    HC32_RTC_BASE,

    /**< \brief RTC �жϺ� */
    INUM_RTC,

    /** \brief �� 1970-1-1 0:0:0 ��ʼ���� */
    1970,

    /** \brief ƽ̨��ʼ������ */
    __hc32_plfm_rtc_init,

    /** \brief ƽ̨ȥ��ʼ������ */
    __hc32_plfm_rtc_deinit
};

/** \brief RTC�豸 */
am_hc32_rtc_dev_t __g_rtc_dev;

/** \brief rtc ʵ����ʼ�������rtc��׼������ */
am_rtc_handle_t am_hc32_rtc_inst_init (void)
{
    return am_hc32_rtc_init(&__g_rtc_dev, &__g_rtc_devinfo);
}

/**
 * \brief rtc ʵ�����ʼ��
 * \param[in] handle : rtc���ֵ
 */
void am_hc32_rtc_inst_deinit (am_rtc_handle_t handle)
{
    am_hc32_rtc_deinit(handle);
}

/**
 * @}
 */

/** end of file */

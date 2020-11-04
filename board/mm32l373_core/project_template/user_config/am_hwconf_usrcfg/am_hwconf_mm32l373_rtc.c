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
 * \brief ZLG117 RTC �û������ļ�
 * \sa am_hwconf_mm32l373_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-28  lqy, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_mm32l373.h"
#include "am_mm32l373_rtc.h"
#include "amhw_mm32l373_rcc.h"
#include "am_mm32l373_inst_init.h"
#include "amhw_mm32_pwr.h"
#include "mm32l373_periph_map.h"


#define RTC_CLK_SOUR  AMHW_MM32L373_RTCCLK_HSE_DIV128
/**
 * \addtogroup am_if_src_hwconf_mm32l373_rtc
 * \copydoc am_hwconf_mm32l373_rtc.c
 * @{
 */

/** \brief RTC ƽ̨��ʼ�� */
void __mm32l373_plfm_rtc_init()
{
    amhw_mm32l373_rcc_apb1_enable(AMHW_MM32L373_RCC_APB1_PWR); /* ʹ�ܵ�Դʱ�� */
    amhw_mm32l373_rcc_apb1_enable(AMHW_MM32L373_RCC_APB1_BKP); /* ʹ�ܱ���ʱ�� */
    amhw_mm32_pwr_bkp_access_enable(MM32L373_PWR,1);          /* ȡ���������д���� */
    amhw_mm32l373_rcc_bdcr_bdrst_reset();                    /* �������������λ */
    am_udelay(5);
    amhw_mm32l373_rcc_bdcr_bdrst_reset_end();                /* �����������λ���� */
    amhw_mm32l373_rcc_bdcr_rtc_clk_set((amhw_mm32l373_rtc_clk_src)RTC_CLK_SOUR);/* RTC ʱ��Դѡ��Ϊ�ⲿRTCʱ��Դ */
    am_mdelay(1);
    amhw_mm32l373_rcc_bdcr_rtc_enable();                     /* RTCʱ��ʹ�� */

}

/** ��� RTC ƽ̨��ʼ�� */
void __mm32l373_plfm_rtc_deinit(void)
{
    amhw_mm32l373_rcc_apb1_disable(AMHW_MM32L373_RCC_APB1_PWR); /* ���ܵ�Դʱ�� */
    amhw_mm32l373_rcc_apb1_disable(AMHW_MM32L373_RCC_APB1_BKP); /* ���ܱ���ʱ�� */
    amhw_mm32_pwr_bkp_access_enable(MM32L373_PWR,0);           /* �������д���� */
    amhw_mm32l373_rcc_bdcr_rtc_disable();                     /* RTCʱ�ӽ��� */
}

/** \brief RTC�豸��Ϣ */
const struct am_mm32l373_rtc_devinfo __g_rtc_devinfo = {

    /** \brief RTC�豸����ַ */
    MM32L373_RTC_BASE,

	/** \brief ��Դ����PWR����ַ */
	MM32L373_PWR_BASE,

	/** \brief ���ݿ���BKP����ַ */
	MM32L373_BKP_BASE,

	/**< \brief RTC �жϺ� */
	INUM_RTC,

    /** \brief RTC�豸ʱ��Դ */
	RTC_CLK_SOUR,

    /** \brief ƽ̨��ʼ������ */
    __mm32l373_plfm_rtc_init,

    /** \brief ƽ̨ȥ��ʼ������ */
    __mm32l373_plfm_rtc_deinit
};

/** \brief RTC�豸 */
am_mm32l373_rtc_dev_t __g_rtc_dev;

/** \brief rtc ʵ����ʼ�������rtc��׼������ */
am_rtc_handle_t am_mm32l373_rtc_inst_init (void)
{
    return am_mm32l373_rtc_init(&__g_rtc_dev, &__g_rtc_devinfo);
}

/**
 * \brief rtc ʵ�����ʼ��
 * \param[in] handle : rtc���ֵ
 */
void am_mm32l373_rtc_inst_deinit (am_rtc_handle_t handle)
{
    am_mm32l373_rtc_deinit(handle);
}

/**
 * @}
 */

/** end of file */

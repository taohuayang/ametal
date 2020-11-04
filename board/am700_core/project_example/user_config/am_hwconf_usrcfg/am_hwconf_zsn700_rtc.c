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
 * \brief ZSN700 RTC �û������ļ�
 * \sa am_hwconf_zsn700_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-17  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_zsn700.h"
#include "am_clk.h"
#include "am_zsn700_rtc.h"
#include "hw/amhw_zsn700_rcc.h"
#include "am_zsn700_inst_init.h"
#include "zsn700_periph_map.h"
#include "zsn700_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zsn700_rtc
 * \copydoc am_hwconf_zsn700_rtc.c
 * @{
 */

/** \brief RTC ƽ̨��ʼ�� */
void __zsn700_plfm_rtc_init()
{
    am_clk_enable(CLK_RTC);

    am_gpio_pin_cfg(PIOB_14, PIOB_14_RTC_1HZ | PIOB_14_OUT_PP);
}

/** ��� RTC ƽ̨��ʼ�� */
void __zsn700_plfm_rtc_deinit(void)
{
    am_clk_disable(CLK_RTC);

    am_gpio_pin_cfg(PIOB_14, PIOB_14_GPIO | PIOB_14_INPUT_PU);
}

/** \brief RTC�豸��Ϣ */
const struct am_zsn700_rtc_devinfo __g_rtc_devinfo = {

    /** \brief RTC�豸����ַ */
    ZSN700_RTC_BASE,

    /** \brief RTC�豸ʱ��Դ */
    AMHW_ZSN700_RTC_CLK_SRC_XTL_32768Hz,

    /**< \brief RTC �жϺ� */
    INUM_RTC,

    {
        AM_TRUE,                      /* �Ƿ�ʹ��1Hz�������
                                       * AM_TRUE �� ʹ�� �����Ķ������������õ�ע�ͣ�
                                       * AM_FALSE�� ���ܣ���������������Ч��
                                       */
        -92.554,                      /* ����ֵ��-274.6 ~ 212.6��ppm����Χ�����ر�*/
        AM_TRUE,                      /* ��ppm���ڷ�Χ��ʱ������������������£���
                                       * ѡ���Ƿ�������ʱ����Ϊ����ʱ��
                                       *
                                       * AM_TRUE �� ��������ʱ����Ϊ����ʱ��
                                       * AM_FALSE�� �رո���ʱ����Ϊ����ʱ��
                                       */
        AMHW_ZSN700_RTCCLK_ADJUST_24M,/* ����ʱ�Ӳ���ʱ��ѡ�� ����PCLKƵ�ʱ���һ����ͬ  */
    },

    /** \brief ƽ̨��ʼ������ */
    __zsn700_plfm_rtc_init,

    /** \brief ƽ̨ȥ��ʼ������ */
    __zsn700_plfm_rtc_deinit
};

/** \brief RTC�豸 */
am_zsn700_rtc_dev_t __g_rtc_dev;

/** \brief rtc ʵ����ʼ�������rtc��׼������ */
am_rtc_handle_t am_zsn700_rtc_inst_init (void)
{
    return am_zsn700_rtc_init(&__g_rtc_dev, &__g_rtc_devinfo);
}

/**
 * \brief rtc ʵ�����ʼ��
 * \param[in] handle : rtc���ֵ
 */
void am_zsn700_rtc_inst_deinit (am_rtc_handle_t handle)
{
    am_zsn700_rtc_deinit(handle);
}

/**
 * @}
 */

/** end of file */

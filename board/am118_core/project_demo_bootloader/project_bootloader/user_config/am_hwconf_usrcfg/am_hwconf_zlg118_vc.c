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
 * \brief ZLG VC �û������ļ�
 * \sa am_hwconf_zlg118_vc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_zlg118.h"
#include "am_zlg118_vc.h"
#include "hw/amhw_zlg118_vc.h"
#include "zlg118_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zlg118_vc
 * \copydoc am_hwconf_zlg118_vc.c
 * @{
 */

/**
 * \brief VC ƽ̨��ʼ��
 */
void __zlg118_plfm_vc_init (void)
{

    /* ����PIOA_6ΪVC_OUT���� */
    am_gpio_pin_cfg(PIOA_6, PIOA_6_VC0_OUT | PIOA_6_OUT_PP);

    /* ����PIOC_0ΪVC0 P������ */
    am_gpio_pin_cfg(PIOC_0, PIOC_0_AIN);

    /* ����PIOA_7ΪVC0 P������ */
    am_gpio_pin_cfg(PIOA_7, PIOA_7_AIN);

    /* ����VCʱ�� */
    am_clk_enable(CLK_VC_LVD);

    /* ����BGRʱ�� */
    am_clk_enable(CLK_ADC_BGR);
}

/**
 * \brief VC ƽ̨ȥ��ʼ��
 */
void __zlg118_plfm_vc_deinit (void)
{
    /* �ر�DACʱ�� */
    am_clk_disable(CLK_VC_LVD);
}

/** \brief VC �豸��Ϣ */
static const am_zlg118_vc_devinfo_t __g_vc_devinfo =
{
    /**< \brief ָ��VC�Ĵ������ָ�� */
    ZLG118_VC_BASE,

    /**< \brief VC�жϱ�� */
    INUM_VC0,

    /**
     * \brief VC ͨ��0���û�����ֵ�鿴�궨�壺ģ��Ƚ���ͨ��ѡ������
     */
    AMHW_ZLG118_VC0,

    /**
     * \brief VC�ο� ѡ���û�����ֵ�鿴�궨�壺VC_DIV �ο���ѹVrefѡ������
     *
     */
    AMHW_ZLG118_VC_REF2P5_VCC,

    /**
     * \brief VC ͨ��0���͵�ѹ10mv ,ΪNULL���ʾû�г���
     *        �û�����ֵ�鿴�궨�壺VC0-2 ���͵�ѹѡ������
     */
    AMHW_ZLG118_VC0_HYS_10_MV,

    /**
     * \brief VC ����ѡ���û�����ֵ�鿴�궨�壺VC0-2 ����ѡ������
     *
     * \note :����Խ����Ӧʱ��Խ�졣������ѡ��>=10uA��Ҫ����BGR��BGR����ʱ���Լ20us
     */
    AMHW_ZLG118_VC0_BIAS_1_2_UA,

    /**
     * \brief VC �˲�ʱ�䣬�û�����ֵ�鿴ö��amhw_zlg118_vc_deb_time��
     *
     * \note ���˲�ʱ�������ֻ���� FLTEN=1 ʱ����Ч,�粻��Ҫ�˲�ֵΪ��AMHW_ZLG118_DEB_TIME_NO
     */
    AMHW_ZLG118_DEB_TIME_28_US,

    /**
     * \brief VC p������ ѡ���û�����ֵ�鿴ö�٣�VC0-2 ��+��������ѡ��
     *
     * \note :ÿ��ͨ������˿�ö�ٲ�ͬ����Ҫ�鿴��Ӧʹ��ͨ����ö�ٶ���
     */
    AMHW_ZLG118_VC0_P_INPUT_PC0,

    /**
     * \brief VC n������ ѡ���û�����ֵ�鿴ö�٣�VC0-2 ��-��������ѡ��
     *
     * \note :ÿ��ͨ������˿�ö�ٲ�ͬ����Ҫ�鿴��Ӧʹ��ͨ����ö�ٶ���
     */
    AMHW_ZLG118_VC0_N_INPUT_PA7,

    /**
     * \brief VC ������ã��û�����ֵ�ο���VC0-2 ����Ĵ�������ʹ�ܺ�
     *
     * \note :����ʱ������ܣ�����дΪNULL����д��AMHW_ZLG118_VC_OUT_CFG_DISABLE
     */
    AMHW_ZLG118_VC_OUT_CFG_DISABLE,

    /**
     *  \brief VC ��������ж�����ѡ���û����òο��궨�壺VC0-2 ����źŴ����ж�ѡ������
     *
     */
    AMHW_ZLG118_VC_OUT_TRI_INT_RISING,

    /**< \brief VCƽ̨��ʼ������ */
    __zlg118_plfm_vc_init,

    /**< \brief VCƽ̨���ʼ������  */
    __zlg118_plfm_vc_deinit,
};

/** \brief VC�豸ʵ�� */
static am_zlg118_vc_dev_t __g_vc_dev;

/** \brief VC ʵ����ʼ�������VC��׼������ */
am_vc_handle_t am_zlg118_vc_inst_init (void)
{
    return am_zlg118_vc_init(&__g_vc_dev, &__g_vc_devinfo);
}

/** \brief VC ʵ�����ʼ�� */
void am_zlg118_vc_inst_deinit (am_vc_handle_t handle)
{
    am_zlg118_vc_deinit(handle);
}

/**
 * @}
 */

/* end of file */

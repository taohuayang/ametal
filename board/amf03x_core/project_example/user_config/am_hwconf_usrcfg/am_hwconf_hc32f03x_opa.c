/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2020 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ZLG OPA �û������ļ�
 * \sa am_hwconf_hc32_opa.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-13
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "am_hc32x3x_opa.h"
#include "hw/amhw_hc32x3x_opa.h"
#include "hc32x3x_pin.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_opa
 * \copydoc am_hwconf_hc32_opa.c
 * @{
 */
/********************************OPA1����***************************************/
/**
 * \brief OPA1 ƽ̨��ʼ��
 */
void __hc32_plfm_opa1_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /**< \brief ��ͬͨ����Ҫ��ʼ����ͬ���� */
    am_gpio_pin_cfg (PIOC_6,  PIOC_6_AIN);
    am_gpio_pin_cfg (PIOB_15, PIOB_15_AIN);
    am_gpio_pin_cfg (PIOC_7,  PIOC_7_AOUT);
}

/**
 * \brief OPA1 ƽ̨ȥ��ʼ��
 */
void __hc32_plfm_opa1_deinit (void)
{
    /* �ر�OPAʱ�� */
    am_clk_disable (CLK_OPA);

    /* �ر�BGRʱ�� */
    am_clk_disable (CLK_ADC_BGR);
}

/** \brief OPA �豸��Ϣ */
static const am_hc32_opa_devinfo_t __g_opa1_devinfo =
{
    /**< \brief ָ��OPA�Ĵ������ָ�� */
    HC32_OPA_BASE,

    /**
     *  \brief OPAģʽ��һ������ģʽ����ֵ�ο�amhw_hc32_opa.h�궨�壺OPA����ģʽѡ������
     *
     */
    AMHW_HC32_OPA_MODE_UNITY_GAIN,

    /**
     * \brief OPA���� ,�ο�amhw_hc32_opa.h�궨�壺OPA ��������ѡ������   OPA ��������ѡ������
     *        ע��ģʽ��ͬѡ��������߷������棬������������ �����������벻֧��7�� 14�����档��λ����
     *        ģʽ�����棬ѡ��AWHW_HC32_OPA_NO_GAIN��
     *        ���������ͷ�����ģʽ�£���Ҫʹ����������ͨ����������������ͨ����ͬ����
     */
    AWHW_HC32_OPA_NO_GAIN,

    /**
     * \brief IO�˿����ڲ����ӿ���,�ο�amhw_hc32_opa.h�궨�壺IO�˿����ڲ����ӿ��ƺ�
     */
    AWHW_HC32_OPA_PO_EN,

    /**< \brief OPAƽ̨��ʼ������ */
    __hc32_plfm_opa1_init,

    /**< \brief OPAƽ̨���ʼ������  */
    __hc32_plfm_opa1_deinit,
};

/** \brief OPA1�豸ʵ�� */
static am_hc32_opa_dev_t __g_opa1_dev;

/** \brief OPA1 ʵ����ʼ�������OPA1��׼������ */
am_opa_handle_t am_hc32_opa1_inst_init (void)
{
    return am_hc32_opa_init(&__g_opa1_dev, &__g_opa1_devinfo);
}

/** \brief OPA1 ʵ�����ʼ�� */
void am_hc32_opa1_inst_deinit (am_opa_handle_t handle)
{
    am_hc32_opa_deinit(handle);
}

/********************************OPA2����***************************************/
/**
 * \brief OPA2 ƽ̨��ʼ��
 */
void __hc32_plfm_opa2_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /**< \brief ��ͬͨ����Ҫ��ʼ����ͬ���� */
    /* OPA2 P N OUT�� */
    am_gpio_pin_cfg (PIOB_13, PIOB_13_AIN);
    am_gpio_pin_cfg (PIOB_12, PIOB_12_AIN);
    am_gpio_pin_cfg (PIOB_14, PIOB_14_AOUT);
}

/**
 * \brief OPA2 ƽ̨ȥ��ʼ��
 */
void __hc32_plfm_opa2_deinit (void)
{
    /* �ر�OPAʱ�� */
    am_clk_disable (CLK_OPA);

    /* �ر�BGRʱ�� */
    am_clk_disable (CLK_ADC_BGR);
}

/** \brief OPA �豸��Ϣ */
static const am_hc32_opa_devinfo_t __g_opa2_devinfo =
{
    /**< \brief ָ��OPA�Ĵ������ָ�� */
    HC32_OPA_BASE,

    /**
     *  \brief OPAģʽ��һ������ģʽ����ֵ�ο�amhw_hc32_opa.h�궨�壺OPA����ģʽѡ������
     *
     */
    AMHW_HC32_OPA_MODE_UNITY_GAIN,

    /**
     * \brief OPA���� ,�ο�amhw_hc32_opa.h�궨�壺OPA ��������ѡ������   OPA ��������ѡ������
     *        ע��ģʽ��ͬѡ��������߷������棬������������ �����������벻֧��7�� 14�����档��λ����
     *        ģʽ�����棬ѡ��AWHW_HC32_OPA_NO_GAIN��
     *        ���������ͷ�����ģʽ�£���Ҫʹ����������ͨ����������������ͨ����ͬ����
     */
    AWHW_HC32_OPA_NO_GAIN,

    /**
     * \brief IO�˿����ڲ����ӿ���,�ο�amhw_hc32_opa.h�궨�壺IO�˿����ڲ����ӿ��ƺ�
     */
    AWHW_HC32_OPA_PO_EN,

    /**< \brief OPA2ƽ̨��ʼ������ */
    __hc32_plfm_opa2_init,

    /**< \brief OPA2ƽ̨���ʼ������  */
    __hc32_plfm_opa2_deinit,
};

/** \brief OPA2�豸ʵ�� */
static am_hc32_opa_dev_t __g_opa2_dev;

/** \brief OPA2 ʵ����ʼ�������OPA2��׼������ */
am_opa_handle_t am_hc32_opa2_inst_init (void)
{
    return am_hc32_opa_init(&__g_opa2_dev, &__g_opa2_devinfo);
}

/** \brief OPA2 ʵ�����ʼ�� */
void am_hc32_opa2_inst_deinit (am_opa_handle_t handle)
{
    am_hc32_opa_deinit(handle);
}

/********************************OPA3����***************************************/
/**
 * \brief OPA3 ƽ̨��ʼ��
 */
void __hc32_plfm_opa3_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /**< \brief ��ͬͨ����Ҫ��ʼ����ͬ���� */
    /* OPA3 P N OUT�� */
    am_gpio_pin_cfg (PIOB_10, PIOB_10_AIN);
    am_gpio_pin_cfg (PIOB_2,  PIOB_2_AIN);
    am_gpio_pin_cfg (PIOB_11, PIOB_11_AOUT);
}

/**
 * \brief OPA3 ƽ̨ȥ��ʼ��
 */
void __hc32_plfm_opa3_deinit (void)
{
    /* �ر�OPAʱ�� */
    am_clk_disable (CLK_OPA);

    /* �ر�BGRʱ�� */
    am_clk_disable (CLK_ADC_BGR);
}

/** \brief OPA �豸��Ϣ */
static const am_hc32_opa_devinfo_t __g_opa3_devinfo =
{
    /**< \brief ָ��OPA�Ĵ������ָ�� */
    HC32_OPA_BASE,

    /**
     *  \brief OPAģʽ��һ������ģʽ����ֵ�ο�amhw_hc32_opa.h�궨�壺OPA����ģʽѡ������
     *
     */
    AMHW_HC32_OPA_MODE_FORWARD_IN,

    /**
     * \brief OPA���� ,�ο�amhw_hc32_opa.h�궨�壺OPA ��������ѡ������   OPA ��������ѡ������
     *        ע��ģʽ��ͬѡ��������߷������棬������������ �����������벻֧��7�� 14�����档��λ����
     *        ģʽ�����棬ѡ��AWHW_HC32_OPA_NO_GAIN��
     *        ���������ͷ�����ģʽ�£���Ҫʹ����������ͨ����������������ͨ����ͬ����
     */
    AMHW_HC32_OPA_NONGAIN_16,

    /**
     * \brief IO�˿����ڲ����ӿ���,�ο�amhw_hc32_opa.h�궨�壺IO�˿����ڲ����ӿ��ƺ�
     */
    AWHW_HC32_OPA_PO_EN,

    /**< \brief OPA2ƽ̨��ʼ������ */
    __hc32_plfm_opa3_init,

    /**< \brief OPA2ƽ̨���ʼ������  */
    __hc32_plfm_opa3_deinit,
};

/** \brief OPA3�豸ʵ��  */
static am_hc32_opa_dev_t __g_opa3_dev;

/** \brief OPA3 ʵ����ʼ�������OPA3��׼������ */
am_opa_handle_t am_hc32_opa3_inst_init (void)
{
    return am_hc32_opa_init(&__g_opa3_dev, &__g_opa3_devinfo);
}

/** \brief OPA3 ʵ�����ʼ�� */
void am_hc32_opa3_inst_deinit (am_opa_handle_t handle)
{
    am_hc32_opa_deinit(handle);
}
/**
 * @}
 */

/* end of file */

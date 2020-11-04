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
 * \brief ZLG OPA �û������ļ�
 * \sa am_hwconf_hc32_opa.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */
#include "hw/amhw_hc32f07x_opa.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "am_hc32f07x_opa.h"
#include "hc32f07x_pin.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_opa
 * \copydoc am_hwconf_hc32_opa.c
 * @{
 */

/**
 * \brief OPA ƽ̨��ʼ��
 */
void __hc32_plfm_opa0_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /* PB15 OPA���� */
    am_gpio_pin_cfg (PIOB_15, PIOB_15_AIN);
}

void __hc32_plfm_opa1_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /* PB15 OPA���� */
    am_gpio_pin_cfg (PIOB_12, PIOB_12_AIN);
}

void __hc32_plfm_opa2_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /* PB15 OPA���� */
    am_gpio_pin_cfg (PIOB_2, PIOB_2_AIN);
}

void __hc32_plfm_opa3_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /* PB15 OPA���� */
    am_gpio_pin_cfg (PIOC_5, PIOC_5_AIN);
}

void __hc32_plfm_opa4_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /* PB15 OPA���� */
    am_gpio_pin_cfg (PIOA_6, PIOA_6_AIN);
}

/**
 * \brief OPA ƽ̨ȥ��ʼ��
 */
void __hc32_plfm_opa_deinit (void)
{
    /* �ر�OPAʱ�� */
    am_clk_disable (CLK_OPA);

    /* �ر�BGRʱ�� */
    am_clk_disable (CLK_ADC_BGR);
}

/**
 *  \brief  OPA0������������Ϣ�б�
 *
 *  \note1 ÿ����Ա����ÿ��OPA0���ͨ������������
 *
 */
am_hc32_opa_ioinfo_t __g_opa0_ioinfo_list[] = {
	  {AMHW_HC32F07X_OPA0_2_OEN0 ,  PIOC_7 , PIOC_7_AOUT },
    {AMHW_HC32F07X_OPA0_2_OEN1 ,  PIOD_11, PIOD_11_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN2 ,  PIOD_10, PIOD_10_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN3 ,  PIOD_9 , PIOD_9_AOUT },
    {AMHW_HC32F07X_OPA0_2_OEN4 ,  PIOD_8 , PIOD_8_AOUT },
};

/**
 *  \brief  OPA1������������Ϣ�б�
 *
 *  \note1 ÿ����Ա����ÿ��OPA1���ͨ������������
 *
 */
am_hc32_opa_ioinfo_t __g_opa1_ioinfo_list[] = {
	  {AMHW_HC32F07X_OPA0_2_OEN0 ,  PIOB_14, PIOB_14_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN1 ,  PIOE_15, PIOE_15_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN2 ,  PIOE_14, PIOE_14_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN3 ,  PIOE_13, PIOE_13_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN4 ,  PIOE_12, PIOE_12_AOUT},
};

/**
 *  \brief  OPA2������������Ϣ�б�
 *
 *  \note1 ÿ����Ա����ÿ��OPA1���ͨ������������
 *
 */
am_hc32_opa_ioinfo_t __g_opa2_ioinfo_list[] = {
	  {AMHW_HC32F07X_OPA0_2_OEN0 ,  PIOB_11, PIOB_11_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN1 ,  PIOE_11, PIOE_11_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN2 ,  PIOE_10, PIOE_10_AOUT},
    {AMHW_HC32F07X_OPA0_2_OEN3 ,  PIOE_9 , PIOE_9_AOUT },
    {AMHW_HC32F07X_OPA0_2_OEN4 ,  PIOE_8 , PIOE_8_AOUT },
};

/**
 *  \brief  OPA3������������Ϣ�б�
 *
 *  \note1 ÿ����Ա����ÿ��OPA3���ͨ������������
 *
 */
am_hc32_opa_ioinfo_t __g_opa3_ioinfo_list[] = {
	  {AMHW_HC32F07X_OPA3_4_OEN ,  PIOA_4, PIOA_4_AOUT},
};

/**
 *  \brief  OPA4������������Ϣ�б�
 *
 *  \note1 ÿ����Ա����ÿ��OPA4���ͨ������������
 *
 */
am_hc32_opa_ioinfo_t __g_opa4_ioinfo_list[] = {
	  {AMHW_HC32F07X_OPA3_4_OEN ,  PIOA_5, PIOA_5_AOUT},
};

/** \brief OPA �豸��Ϣ */
static const am_hc32f07x_opa_devinfo_t __g_opa0_devinfo =
{
    /**< \brief ָ��OPA�Ĵ������ָ�� */
    HC32_OPA_BASE,

	  AMHW_HC32F07X_OP0,
	
    /**
     *  \brief OPA�Զ�У׼�����û�����ֵ�ο�ö�٣��Զ�У׼����������
     *
     *  \note :����У׼ʱ��10us
     */
    AMHW_HC32F07X_OPA_CLK_16,

    /**
     * \brief OPAУ׼��ʽ,�ο��궨�壺OPA �Զ�У��ѡ������
     */
    AMHW_HC32F07X_OPA_AZ_SW,

    /**
     * \brief OPA����ģʽ ,�ο�am_hc32_opa.h�궨�壺OPA����ģʽѡ��
     */
    AM_HC32F07X_OPA0_4_GENERAL,
	
	  &__g_opa0_ioinfo_list[0],

    /**< \brief LVDƽ̨��ʼ������ */
    __hc32_plfm_opa0_init,

    /**< \brief LVDƽ̨���ʼ������  */
    __hc32_plfm_opa_deinit,
};

/** \brief OPA�豸ʵ�� */
static am_hc32f07x_opa_dev_t __g_opa0_dev;

/** \brief OPA ʵ����ʼ�������OPA��׼������ */
am_opa_handle_t am_hc32_opa0_inst_init (void)
{
    return am_hc32f07x_opa_init(&__g_opa0_dev, &__g_opa0_devinfo);
}

/** \brief OPA �豸��Ϣ */
static const am_hc32f07x_opa_devinfo_t __g_opa1_devinfo =
{
    /**< \brief ָ��OPA�Ĵ������ָ�� */
    HC32_OPA_BASE,

	  AMHW_HC32F07X_OP1,
	
    /**
     *  \brief OPA�Զ�У׼�����û�����ֵ�ο�ö�٣��Զ�У׼����������
     *
     *  \note :����У׼ʱ��10us
     */
    AMHW_HC32F07X_OPA_CLK_16,

    /**
     * \brief OPAУ׼��ʽ,�ο��궨�壺OPA �Զ�У��ѡ������
     */
    AMHW_HC32F07X_OPA_AZ_SW,

    /**
     * \brief OPA����ģʽ ,�ο�am_hc32_opa.h�궨�壺OPA����ģʽѡ��
     */
    AM_HC32F07X_OPA0_4_GENERAL,
	
	  &__g_opa1_ioinfo_list[0],

    /**< \brief LVDƽ̨��ʼ������ */
    __hc32_plfm_opa1_init,

    /**< \brief LVDƽ̨���ʼ������  */
    __hc32_plfm_opa_deinit,
};

/** \brief OPA�豸ʵ�� */
static am_hc32f07x_opa_dev_t __g_opa1_dev;

/** \brief OPA ʵ����ʼ�������OPA��׼������ */
am_opa_handle_t am_hc32_opa1_inst_init (void)
{
    return am_hc32f07x_opa_init(&__g_opa1_dev, &__g_opa1_devinfo);
}

static const am_hc32f07x_opa_devinfo_t __g_opa2_devinfo=
{
    HC32_OPA_BASE,
	  AMHW_HC32F07X_OP2,
	  AMHW_HC32F07X_OPA_CLK_16,
	  AMHW_HC32F07X_OPA_AZ_SW,
	  AM_HC32F07X_OPA0_4_GENERAL,
	  &__g_opa2_ioinfo_list[0],
	  __hc32_plfm_opa2_init,
	  __hc32_plfm_opa_deinit,
};

/** \brief OPA�豸ʵ�� */
static am_hc32f07x_opa_dev_t __g_opa2_dev;

/** \brief OPA ʵ����ʼ�������OPA��׼������ */
am_opa_handle_t am_hc32_opa2_inst_init (void)
{
    return am_hc32f07x_opa_init(&__g_opa2_dev, &__g_opa2_devinfo);
}

static const am_hc32f07x_opa_devinfo_t __g_opa3_devinfo=
{
    HC32_OPA_BASE,
	  AMHW_HC32F07X_OP2,
	  AMHW_HC32F07X_OPA_CLK_16,
	  AMHW_HC32F07X_OPA_AZ_SW,
	  AM_HC32F07X_OPA3_4_DAC,
	  &__g_opa3_ioinfo_list[0],
	  __hc32_plfm_opa3_init,
	  __hc32_plfm_opa_deinit,
};

/** \brief OPA�豸ʵ�� */
static am_hc32f07x_opa_dev_t __g_opa3_dev;

/** \brief OPA ʵ����ʼ�������OPA��׼������ */
am_opa_handle_t am_hc32_opa3_inst_init (void)
{
    return am_hc32f07x_opa_init(&__g_opa3_dev, &__g_opa3_devinfo);
}

static const am_hc32f07x_opa_devinfo_t __g_opa4_devinfo=
{
    HC32_OPA_BASE,
	  AMHW_HC32F07X_OP4,
	  AMHW_HC32F07X_OPA_CLK_16,
	  AMHW_HC32F07X_OPA_AZ_SW,
	  AM_HC32F07X_OPA3_4_DAC,
	  &__g_opa4_ioinfo_list[0],
	  __hc32_plfm_opa4_init,
	  __hc32_plfm_opa_deinit,
};

/** \brief OPA�豸ʵ�� */
static am_hc32f07x_opa_dev_t __g_opa4_dev;

/** \brief OPA ʵ����ʼ�������OPA��׼������ */
am_opa_handle_t am_hc32_opa4_inst_init (void)
{
    return am_hc32f07x_opa_init(&__g_opa4_dev, &__g_opa4_devinfo);
}

/** \brief OPA ʵ�����ʼ�� */
void am_hc32_opa_inst_deinit (am_opa_handle_t handle)
{
    am_hc32f07x_opa_deinit(handle);
}





/**
 * @}
 */

/* end of file */

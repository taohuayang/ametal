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
 * \brief HC32 PCA �û������ļ�
 * \sa am_hwconf_hc32l13x_pca.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "hc32_clk.h"
#include "hc32_inum.h"
#include "hc32_regbase.h"
#include "am_hc32_clk.h"
#include "am_hc32_pca.h"

/**
 * \addtogroup am_if_src_hwconf_hc32l13x_pca
 * \copydoc am_hwconf_hc32l13x_pca.c
 * @{
 */

/** \brief ����������Ϣ�б� */
am_hc32_pca_ioinfo_t __g_pca_ioinfo_list[] = {
        {PIOB_4, PIOB_4_PCA_CH0 | PIOB_4_OUT_PP,
                 PIOB_4_PCA_CH0 | PIOB_4_INPUT_PU},
        {PIOB_5, PIOB_5_PCA_CH1 | PIOB_5_OUT_PP,
                 PIOB_5_PCA_CH1 | PIOB_5_INPUT_PU},
        {PIOC_8, PIOC_8_PCA_CH2 | PIOC_8_OUT_PP,
                 PIOC_8_PCA_CH2 | PIOC_8_INPUT_PU},
        {PIOC_9, PIOC_9_PCA_CH3 | PIOC_9_OUT_PP,
                 PIOC_9_PCA_CH3 | PIOC_9_INPUT_PU},
        {PIOC_5, PIOC_5_PCA_CH4 | PIOC_5_OUT_PP,
                 PIOC_5_PCA_CH4 | PIOC_5_INPUT_PU}
};

/**
 * \brief PCA ƽ̨��ʼ������
 */
am_local void __hc32l13x_pca_plfm_init (void)
{
    am_clk_enable(CLK_PCA);
}

/**
 * \brief PCA ƽ̨���ʼ������
 */
am_local void __hc32l13x_pca_plfm_deinit (void)
{
    am_clk_disable(CLK_PCA);
}

/** \brief PCA �豸��Ϣ */
am_local am_const am_hc32_pca_devinfo_t __g_hc32l13x_pca_devinfo = {
        HC32_PCA_BASE,
        CLK_PCA,
        INUM_PCA,
        HC32_PCA_PCLK32,
        __g_pca_ioinfo_list,
        __hc32l13x_pca_plfm_init,
        __hc32l13x_pca_plfm_deinit
};

/** \brief PCA �豸ʵ�� */
am_local am_hc32_pca_dev_t __g_hc32l13x_pca_dev;

/**
 * \brief PCA ʵ����ʼ��
 */
am_hc32_pca_handle_t am_hc32_pca1_inst_init (void)
{
    return am_hc32_pca_init(&__g_hc32l13x_pca_dev, &__g_hc32l13x_pca_devinfo);
}

/**
 * \brief PCA ʵ�����ʼ��
 */
void am_hc32_pca_inst_deinit (am_hc32_pca_handle_t handle)
{
    am_hc32_pca_deinit(handle);
}

/**
 * @}
 */

/* end of file */

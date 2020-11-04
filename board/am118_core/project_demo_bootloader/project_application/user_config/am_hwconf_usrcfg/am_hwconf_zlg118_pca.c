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
 * \brief ZLG118 PCA �û������ļ�
 * \sa am_hwconf_zlg118_pca.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-12
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_zlg118.h"
#include "zlg118_clk.h"
#include "zlg118_inum.h"
#include "zlg118_regbase.h"
#include "am_zlg118_clk.h"
#include "am_zlg118_pca.h"

/**
 * \addtogroup am_if_src_hwconf_zlg118_pca
 * \copydoc am_hwconf_zlg118_pca.c
 * @{
 */

/** \brief ����������Ϣ�б� */
am_zlg118_pca_ioinfo_t __g_pca_ioinfo_list[] = {
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
am_local void __zlg118_pca_plfm_init (void)
{
    am_clk_enable(CLK_PCA);
}

/**
 * \brief PCA ƽ̨���ʼ������
 */
am_local void __zlg118_pca_plfm_deinit (void)
{
    am_clk_disable(CLK_PCA);
}

/** \brief PCA �豸��Ϣ */
am_local am_const am_zlg118_pca_devinfo_t __g_zlg118_pca_devinfo = {
        ZLG118_PCA_BASE,
        CLK_PCA,
        INUM_PCA,
        ZLG118_PCA_PCLK32,
        __g_pca_ioinfo_list,
        __zlg118_pca_plfm_init,
        __zlg118_pca_plfm_deinit
};

/** \brief PCA �豸ʵ�� */
am_local am_zlg118_pca_dev_t __g_zlg118_pca_dev;

/**
 * \brief PCA ʵ����ʼ��
 */
am_zlg118_pca_handle_t am_zlg118_pca1_inst_init (void)
{
    return am_zlg118_pca_init(&__g_zlg118_pca_dev, &__g_zlg118_pca_devinfo);
}

/**
 * \brief PCA ʵ�����ʼ��
 */
void am_zlg118_pca_inst_deinit (am_zlg118_pca_handle_t handle)
{
    am_zlg118_pca_deinit(handle);
}

/**
 * @}
 */

/* end of file */

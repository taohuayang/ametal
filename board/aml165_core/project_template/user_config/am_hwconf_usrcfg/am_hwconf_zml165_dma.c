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
 * \brief ZML165 DMA �û������ļ�
 * \sa am_hwconf_zml165_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-20  ari, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_zml165.h"
#include "am_zlg_dma.h"
#include "hw/amhw_zml165_rcc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zml165_dma
 * \copydoc am_hwconf_zml165_dma.c
 * @{
 */

/**
 * \brief DMA ƽ̨��ʼ����
 */
void __zml165_plfm_dma_init (void)
{

    /* ʱ��DMA���ģ��ʱ�ӻ��Դ */
    am_clk_enable(CLK_DMA);
}

/**
 * \brief EDMA ƽ̨ȥ��ʼ����
 */
void __zml165_plfm_dma_deinit (void)
{

    /* ʱ��DMA���ģ��ʱ�ӻ��Դ */
    am_clk_disable(CLK_DMA);
}

/** \brief DMA �豸��Ϣ */
static const am_zlg_dma_devinfo_t __g_dma_devinfo = {
    ZML165_DMA_BASE,         /**< \brief ָ��DMA�Ĵ������ָ�� */
    INUM_DMA1_1,             /**< \brief DMA�ж������ſ�ʼ */
    INUM_DMA1_4_5,           /**< \brief DMA�ж������Ž��� */
    __zml165_plfm_dma_init,  /**< \brief DMAƽ̨��ʼ�� */
    __zml165_plfm_dma_deinit /**< \brief DMAƽ̨���ʼ�� */
};

/** \brief DMA�豸ʵ�� */
static am_zlg_dma_dev_t __g_dma_dev;

/**
 * \brief DMA ʵ����ʼ��
 * \return ��
 */
int am_zml165_dma_inst_init (void)
{
    return am_zlg_dma_init(&__g_dma_dev, &__g_dma_devinfo);
}

/**
 * \brief DMA ʵ�����ʼ��
 * \return ��
 */
void am_zml165_dma_inst_deinit (void)
{
    am_zlg_dma_deinit();
}

/**
 * @}
 */

/* end of file */

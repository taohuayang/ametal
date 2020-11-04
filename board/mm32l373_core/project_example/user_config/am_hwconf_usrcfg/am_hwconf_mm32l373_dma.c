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
 * \brief MM32L373 DMA �û������ļ�
 * \sa am_hwconf_mm32l373_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "am_clk.h"
#include "am_mm32l373.h"
#include "amhw_mm32l373_rcc.h"
#include "am_mm32_dma.h"
/**
 * \addtogroup am_if_src_hwconf_mm32l373_dma
 * \copydoc am_hwconf_mm32l373_dma.c
 * @{
 */

/**
 * \brief DMA ƽ̨��ʼ����
 */
static void __mm32l373_plfm_dma_init (void)
{
    am_clk_enable(CLK_DMA);
}

/**
 * \brief DMA ƽ̨ȥ��ʼ����
 */
static void __mm32l373_plfm_dma_deinit (void)
{
    am_clk_disable(CLK_DMA);
}

/** \brief DMA �豸��Ϣ */
static const am_mm32_dma_devinfo_t __g_dma_devinfo = {
    MM32L373_DMA_BASE,           /**< \brief ָ��DMA�Ĵ������ָ�� */
    INUM_DMA1_1,               /**< \brief DMA�ж������ſ�ʼ */
    INUM_DMA1_7,               /**< \brief DMA�ж������Ž��� */
    __mm32l373_plfm_dma_init,    /**< \brief DMAƽ̨��ʼ�� */
    __mm32l373_plfm_dma_deinit   /**< \brief DMAƽ̨���ʼ�� */
};

/** \brief DMA�豸ʵ�� */
static am_mm32_dma_dev_t __g_dma_dev;

/**
 * \brief DMA ʵ����ʼ��
 * \return ��
 */
int am_mm32l373_dma_inst_init (void)
{
    //return am_mm32l373_dma_init(&__g_dma_dev, &__g_dma_devinfo);
    return am_mm32_dma_init(&__g_dma_dev, &__g_dma_devinfo);
}

/**
 * \brief DMA ʵ�����ʼ��
 * \return ��
 */
void am_mm32l373_dma_inst_deinit (void)
{
    am_mm32_dma_deinit();
}

/**
 * @}
 */

/* end of file */

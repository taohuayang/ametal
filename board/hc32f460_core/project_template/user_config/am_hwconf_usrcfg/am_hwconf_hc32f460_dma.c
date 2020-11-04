/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief HC32F460 DMA �û������ļ�
 * \sa am_hwconf_hc32f460_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-02-27  cds, first implementation
 * \endinternal
 */

#include "am_clk.h"
#include "am_hc32f460.h"
#include "hw/amhw_hc32f460_rcc.h"
#include "am_hc32f460_dma.h"
/**
 * \addtogroup am_if_src_hwconf_hc32f460_dma
 * \copydoc am_hwconf_hc32f460_dma.c
 * @{
 */

/**
 * \brief DMA1 ƽ̨��ʼ����
 */
static void __hc32f460_plfm_dma1_init (void)
{
    am_clk_enable(CLK_DMA1);
}

/**
 * \brief DMA1 ƽ̨ȥ��ʼ����
 */
static void __hc32f460_plfm_dma1_deinit (void)
{
    am_clk_disable(CLK_DMA1);
}

/** \brief DMA1 �豸��Ϣ */
static const am_hc32f460_dma_devinfo_t __g_dma1_devinfo = {
    HC32F460_DMA1_BASE,           /**< \brief ָ��DMA�Ĵ������ָ�� */
	INUM_DMA1,                    /**< \brief DMA�ж������� */
	1,                            /**< \brief DMA�豸ID */
    __hc32f460_plfm_dma1_init,    /**< \brief DMAƽ̨��ʼ�� */
    __hc32f460_plfm_dma1_deinit   /**< \brief DMAƽ̨���ʼ�� */
};

/** \brief DMA1�豸ʵ�� */
am_hc32f460_dma_dev_t __g_dma1_dev;

/**
 * \brief DMA1 ʵ����ʼ��
 * \return ��
 */
int am_hc32f460_dma1_inst_init (void)
{
    return am_hc32f460_dma_init(&__g_dma1_dev, &__g_dma1_devinfo);
}

/**
 * \brief DMA1 ʵ�����ʼ��
 * \return ��
 */
void am_hc32f460_dma1_inst_deinit (void)
{
    am_hc32f460_dma_deinit(&__g_dma1_dev);
}


/**
 * \brief DMA2 ƽ̨��ʼ����
 */
static void __hc32f460_plfm_dma2_init (void)
{
    am_clk_enable(CLK_DMA2);
}

/**
 * \brief DMA1 ƽ̨ȥ��ʼ����
 */
static void __hc32f460_plfm_dma2_deinit (void)
{
    am_clk_disable(CLK_DMA2);
}

/** \brief DMA2 �豸��Ϣ */
static const am_hc32f460_dma_devinfo_t __g_dma2_devinfo = {
    HC32F460_DMA2_BASE,           /**< \brief ָ��DMA2�Ĵ������ָ�� */
	INUM_DMA2,                    /**< \brief DMA2�ж������� */
	2,                            /**< \brief DMA2�豸ID */
    __hc32f460_plfm_dma2_init,    /**< \brief DMA2ƽ̨��ʼ�� */
    __hc32f460_plfm_dma2_deinit   /**< \brief DMA2ƽ̨���ʼ�� */
};

/** \brief DMA2�豸ʵ�� */
am_hc32f460_dma_dev_t __g_dma2_dev;

/**
 * \brief DMA2 ʵ����ʼ��
 * \return ��
 */
int am_hc32f460_dma2_inst_init (void)
{
    return am_hc32f460_dma_init(&__g_dma2_dev, &__g_dma2_devinfo);
}

/**
 * \brief DMA2 ʵ�����ʼ��
 * \return ��
 */
void am_hc32f460_dma2_inst_deinit (void)
{
    am_hc32f460_dma_deinit(&__g_dma2_dev);
}

/**
 * @}
 */

/* end of file */

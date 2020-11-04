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
 * \brief ZLG118 DMA �û������ļ�
 * \sa am_hwconf_zlg118_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-18  zp, first implementation
 * \endinternal
 */

#include "am_clk.h"
#include "am_zlg118.h"
#include "hw/amhw_zlg118_rcc.h"
#include "am_zlg118_dma.h"
/**
 * \addtogroup am_if_src_hwconf_zlg118_dma
 * \copydoc am_hwconf_zlg118_dma.c
 * @{
 */

/**
 * \brief DMA ƽ̨��ʼ����
 */
static void __zlg118_plfm_dma_init (void)
{
    am_clk_enable(CLK_DMA);
}

/**
 * \brief DMA ƽ̨ȥ��ʼ����
 */
static void __zlg118_plfm_dma_deinit (void)
{
    am_clk_disable(CLK_DMA);
}

/** \brief DMA �豸��Ϣ */
static const am_zlg118_dma_devinfo_t __g_dma_devinfo = {
    ZLG118_DMA_BASE,           /**< \brief ָ��DMA�Ĵ������ָ�� */
    INUM_DMA,                  /**< \brief DMA�ж������� */
    __zlg118_plfm_dma_init,    /**< \brief DMAƽ̨��ʼ�� */
    __zlg118_plfm_dma_deinit   /**< \brief DMAƽ̨���ʼ�� */
};

/** \brief DMA�豸ʵ�� */
static am_zlg118_dma_dev_t __g_dma_dev;

/**
 * \brief DMA ʵ����ʼ��
 * \return ��
 */
int am_zlg118_dma_inst_init (void)
{
    return am_zlg118_dma_init(&__g_dma_dev, &__g_dma_devinfo);
}

/**
 * \brief DMA ʵ�����ʼ��
 * \return ��
 */
void am_zlg118_dma_inst_deinit (void)
{
    am_zlg118_dma_deinit();
}

/**
 * @}
 */

/* end of file */

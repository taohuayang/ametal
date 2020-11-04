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
 * \brief DACת�� DMA�����������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   1. ���ڴ�ӡ�� "DAC DMA transfer done!"��
 *   2. ��ӡ����ǰDAC�����ѹֵ��(�����ѹ����Ϊһ�����Ҳ�������ֵ0mv ������ֵ 3300 mv)
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_dac_dma.c src_zsn700_hw_dac_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-25  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_dac_dma
 * \copydoc demo_zsn700_hw_dac_dma.c
 */

/** [src_zsn700_hw_dac_dma] */
#include "ametal.h"
#include "am_zsn700.h"
#include "demo_zlg_entries.h"
#include "am_zsn700_inst_init.h"
#include "demo_am700_core_entries.h"
#include "hw/amhw_zsn700_dac.h"
#include "math.h"

#define PI 3.14159265358979           //Բ����

/**< \brief DAC���õ�ѹֵ������  */
static uint16_t vol_val[128] = {0};

/*******************************************************************************
** \brief  �������Ҳ��Ĳ�����
** \param  buf:���ڴ�����Ҳ�������Ļ���
** \return ��
******************************************************************************/
static void _BufProduce(uint16_t* vol_val)
{
   uint8_t tmp;
   double tmp1;
   tmp1=PI/64;
   for(tmp=0; tmp<128; tmp++)
   {
       vol_val[tmp] =(uint16_t)(((sin(tmp1*tmp))*2047)+2048);
   }
}

/**
 * \brief �������
 */
void demo_zsn700_core_hw_dac_dma_entry (void)
{
    AM_DBG_INFO("demo am700_core hw dac dma test!\r\n");

    /* ����PIOA_4ΪDAC1_OUT���� */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AOUT);

    /* ����DACʱ�� */
    am_clk_enable(CLK_DAC);

    _BufProduce(vol_val);

    demo_zsn700_hw_dac_dma_entry(ZSN700_DAC,
                                 ZSN700_DMA_SRC_TYPE_DAC0,
                                 DMA_CHAN_1,
                                 vol_val);

}

/* end of file */

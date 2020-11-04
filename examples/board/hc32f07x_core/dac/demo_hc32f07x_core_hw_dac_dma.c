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
 * \snippet demo_hc32f07x_hw_dac_dma.c src_hc32f07x_hw_dac_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-25  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f07x_hw_dac_dma
 * \copydoc demo_hc32f07x_hw_dac_dma.c
 */

/** [src_hc32f07x_hw_dac_dma] */
#include "ametal.h"
#include "am_hc32f07x.h"
#include "demo_hc32f07x_entries.h"
#include "am_hc32f07x_inst_init.h"
#include "math.h"
#include "hw/amhw_hc32f07x_dac.h"
#include "hw/amhw_hc32f07x_opa.h"
#define PI 3.14159265358979           //Բ����

/**< \brief DAC���õ�ѹֵ������  */
static uint16_t vol_val[128] = {0};
amhw_hc32f07x_opa_t *gp_hw_opa   =(amhw_hc32f07x_opa_t *) HC32_OPA_BASE;
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
void demo_hc32f07x_core_hw_dac_dma_entry (void)
{
    AM_DBG_INFO("demo amf07x_core hw dac dma test!\r\n");

    /* ����PIOA_4ΪDAC0_OUT���� */
    am_gpio_pin_cfg(PIOA_5, PIOA_5_AOUT);

    /* ����DACʱ�� */
    am_clk_enable(CLK_DAC);
    am_clk_enable (CLK_OPA);
	
    _BufProduce(vol_val);
    amhw_hc32f07x_opa4buf_en (gp_hw_opa);
    demo_hc32f07x_hw_dac_dma_entry(HC32_DAC,
                                 HC32_DMA_SRC_TYPE_DAC1,
                                 DMA_CHAN_1,
                                 vol_val);

}

/* end of file */

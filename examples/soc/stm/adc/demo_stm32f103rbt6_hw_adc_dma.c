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
 * \brief ADC��ͨ��ͨ��DMA���䣬ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��ӦADCͨ����ӡ��ѹֵ��
 *
 * \par Դ����
 * \snippet demo_stm32f103rbt6_adc_dma.c src_stm32f103rbt6_adc_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-27  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_stm32f103rbt6_adc_dma
 * \copydoc demo_stm32f103rbt6_adc_dma.c
 */

/** [src_stm32f103rbt6_adc_dma] */
#include "am_stm32f103rbt6.h"
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_stm32f103rbt6_dma.h"
#include "am_stm32f103rbt6_clk.h"
#include "hw/amhw_stm32f103rbt6_dma.h"
#include "hw/amhw_stm32f103rbt6_adc.h"

#define  BUF_SIZE    2*4                 /**< \brief �����趨��������С
                                          *    �����޸ĳ�adc_chan_num��2����ϵ
                                          */

static uint32_t __g_buf_dst[BUF_SIZE];   /**< \brief Ŀ������ݻ����� */

static uint16_t __g_adc_dat[BUF_SIZE];   /**< \brief ADC���ݻ����� */

static am_bool_t g_trans_done;           /**< \brief ������ɱ�־ */

static amhw_stm32f103rbt6_dma_xfer_desc_t g_desc;  /**< \brief DMA������ */


/**
 * \brief DMA �жϷ������
 */
static void dma_isr (void *p_arg , uint32_t flag)
{
    int i;

    if (flag == AM_STM32F103RBT6_DMA_INT_NORMAL) {

        for (i = 0; i < BUF_SIZE; i++) {

            /* ��12λΪADC�ɼ����� */
            __g_adc_dat[i] = __g_buf_dst[i] & 0xfff;
        }

        g_trans_done = AM_TRUE;
    }
}

static void __stm32f103rbt6_adc_init (amhw_stm32f103rbt6_adc_t *p_hw_adc,
                            int               *p_adc_chan,
                            int                adc_chan_num)
{
    int i;

    /* ����ADC����Ƶ�ʣ�72MHz��8��Ƶ */
    amhw_stm32f103rbt6_rcc_adc_div_set (2);

    /* ADC���� */
    amhw_stm32f103rbt6_adc_disable(p_hw_adc);

    /* ����ADC������ͨ������ */
    if(adc_chan_num < 16) {
        amhw_stm32f103rbt6_adc_regular_channel_length_set(
            p_hw_adc,
            (amhw_stm32f103rbt6_adc_regular_channel_length_t)(adc_chan_num - 1));
    }

    for(i=0;i<adc_chan_num;i++) {

        /* ���ӹ���ͨ�����к�ADC����ͨ�� */
        amhw_stm32f103rbt6_adc_regular_channel_order_set(
            p_hw_adc,
           (amhw_stm32f103rbt6_adc_regular_channel_order_t)(AMHW_STM32F103RBT6_ADC_REGULAR_CHAN_ORDER_1st + i),
           (amhw_stm32f103rbt6_adc_channel_t)p_adc_chan[i]);

        /* ���ò���ͨ���Ĳ������� */
        amhw_stm32f103rbt6_adc_smpr_set(
            p_hw_adc,
            AMHW_STM32F103RBT6_ADC_CHAN_ST55_5,
            (amhw_stm32f103rbt6_adc_channel_t)p_adc_chan[i]);
    }

    /* ����ɨ��ģʽ */
    amhw_stm32f103rbt6_adc_scan_mode_enable(p_hw_adc);

    /* ����ת�� */
    amhw_stm32f103rbt6_adc_cont_set(p_hw_adc, AMHW_STM32F103RBT6_ADC_CONVERSION_CONTINUOUS);

    /* ���óɶ���ģʽ */
    amhw_stm32f103rbt6_adc_dul_mode_set(p_hw_adc, AMHW_STM32F103RBT6_ADC_DUL_MODE_0);

    /* ���뷽ʽ--�Ҷ��� */
    amhw_stm32f103rbt6_adc_data_alignment_set(p_hw_adc,AMHW_STM32F103RBT6_ADC_DATA_RIGHT);

    /* �ر�ADC16ͨ���ڲ��¶ȴ���������ADC1��Ч��*/
    amhw_stm32f103rbt6_adc_tsvrefe_disable(p_hw_adc);

    /* ����ADC��DMA���� */
    amhw_stm32f103rbt6_adc_dma_enable(p_hw_adc);
}

/**
 * \brief �������
 */
void demo_stm32f103rbt6_hw_adc_dma_entry (amhw_stm32f103rbt6_adc_t *p_hw_adc,
                                   int               *p_adc_chan,
                                   int                adc_chan_num,
                                   uint8_t            dma_chan)
{
    uint32_t adc_mv = 0;    /* ������ѹ */
    uint32_t flags;
    int      i;

    /* ʹ�÷�Ĭ��demo����ʱ�����ȸ��ݾ���ʹ�õ�ADCͨ�������޸�BUF_SIZE�궨��*/

    am_kprintf("The ADC HW dma Demo\r\n");

    /* adc��س�ʼ������ */
    __stm32f103rbt6_adc_init(p_hw_adc, p_adc_chan, adc_chan_num);

    /* ADCʹ��*/
    /* ��CR2�Ĵ�������ADONһ��������λ���ı䣬��ת����������������Ϊ�˷�ֹ���������ת����*/
    amhw_stm32f103rbt6_adc_enable(p_hw_adc);

    /* DMA �������� */
    flags = AMHW_STM32F103RBT6_DMA_CHAN_PRIORITY_HIGH         |  /* �ж����ȼ� �� */
            AMHW_STM32F103RBT6_DMA_CHAN_MEM_SIZE_32BIT        |  /* �ڴ����ݿ�� 2 �ֽ� */
            AMHW_STM32F103RBT6_DMA_CHAN_PER_SIZE_32BIT        |  /* �������ݿ�� 2 �ֽ� */
            AMHW_STM32F103RBT6_DMA_CHAN_MEM_ADD_INC_ENABLE    |  /* �ڴ��ַ���� */
            AMHW_STM32F103RBT6_DMA_CHAN_PER_ADD_INC_DISABLE   |  /* �����ַ������ */
            AMHW_STM32F103RBT6_DMA_CHAN_CIRCULAR_MODE_ENABLE  |  /* ��ѭ��ģʽ */
            AMHW_STM32F103RBT6_DMA_CHAN_INT_TX_CMP_ENABLE;       /* ʹ��DMA��������ж� */

    /* ���� DMA �жϷ����� */
    am_stm32f103rbt6_dma_isr_connect(dma_chan, dma_isr, (void *)p_hw_adc);

    /* ����ͨ�������� */
    am_stm32f103rbt6_dma_xfer_desc_build(&g_desc,                      /* ͨ�������� */
                               (uint32_t)(&p_hw_adc->dr),    /* Դ�����ݻ����� */
                               (uint32_t)(__g_buf_dst),      /* Ŀ������ݻ����� */
                               sizeof(__g_buf_dst),          /* �����ֽ��� */
                               flags);                       /* �������� */

    /* DMA�Ĵ������� */
    am_stm32f103rbt6_dma_xfer_desc_chan_cfg(&g_desc,
                                   AMHW_STM32F103RBT6_DMA_PER_TO_MER, /* ���赽�ڴ� */
                                   dma_chan);

    /* ���� DMA ���䣬���Ͽ�ʼ���� */
    am_stm32f103rbt6_dma_chan_start(dma_chan);

    /* ADCת������δ�����ⲿ��������Ҫע����ǣ��˴��ǵڶ���ADCʹ�ܣ����ε�ʵ�������ǿ���ADCת��*/
    amhw_stm32f103rbt6_adc_enable(p_hw_adc);

    while(1) {

        /* �ȴ�������� */
        while(g_trans_done == AM_FALSE);

        for (i = 0; i < adc_chan_num; i++) {

            /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
            adc_mv = __g_adc_dat[i] * 3300 / ((1UL << 12) -1);

            /* ���ڴ�ӡ����*/
            am_kprintf("chan: %d, Sample : %d, Vol: %d mv\r\n", p_adc_chan[i],
                                                                __g_adc_dat[i],
                                                                adc_mv);
        }

        am_kprintf("\r\n");
        am_mdelay(500);

        /* DMA�����־ʧЧ */
        g_trans_done = AM_FALSE;

    }
}
/** [src_stm32f103rbt6_adc_dma] */

/* end of file */

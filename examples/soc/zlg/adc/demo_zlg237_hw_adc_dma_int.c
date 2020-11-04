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
 * \brief ADC1 �� ADC2ͬʱ�ɼ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 *        ADC1 ʹ�� ������ DMAͨ��, ADC2 ʹ�� ע���� �ж�ͨ��
 *
 * - �������裺
 *   1. PIOA_2 (ADC ͨ�� 2) ����ģ�����롣
 *   2. PIOA_3 (ADC ͨ�� 3) ����ģ�����롣
 *   3. PIOA_4 (ADC ͨ�� 4) ����ģ�����롣
 *   4. PIOA_5 (ADC ͨ�� 5) ����ģ�����롣
 *   5. PIOA_6 (ADC ͨ�� 6) ����ģ�����롣
 *   6. PIOA_7 (ADC ͨ�� 7) ����ģ�����롣
 *   7. PIOC_1 (ADC ͨ�� 11) ����ģ�����롣
 *   8. PIOC_2 (ADC ͨ�� 12) ����ģ�����롣
 *   9. PIOC_3 (ADC ͨ�� 13) ����ģ�����롣
 *
 * - ʵ������
 *   1. ��ӦADCͨ����ӡ��ѹֵ��
 *
 * \par Դ����
 * \snippet demo_zlg237_hw_adc_dma_int.c src_zlg237_hw_adc_dma_int
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-27  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg237_hw_adc_dma_int
 * \copydoc demo_zlg237_hw_adc_dma_int.c
 */

/** [src_zlg237_hw_adc_dma_int] */
#include "am_zlg237.h"
#include "ametal.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_zlg_dma.h"
#include "am_zlg237_clk.h"
#include "hw/amhw_zlg_dma.h"
#include "hw/amhw_zlg237_adc.h"

#define  BUF_SIZE1    6                 /**< \brief �����趨��������С
                                          *    �����޸ĳ�adc_chan_num��2����ϵ
                                          */
#define  BUF_SIZE2    3                 /**< \brief �����趨��������С
                                          *    �����޸ĳ�adc_chan_num��2����ϵ
                                          */
static uint32_t __g_buf_dst1[BUF_SIZE1];   /**< \brief Ŀ������ݻ����� */

static uint16_t __g_adc_dat1[BUF_SIZE1];   /**< \brief ADC���ݻ����� */
static uint16_t __g_adc_dat2[BUF_SIZE2];   /**< \brief ADC���ݻ����� */

static am_bool_t g_trans_done1;           /**< \brief ������ɱ�־ */
static am_bool_t g_trans_done2;           /**< \brief ������ɱ�־ */

static amhw_zlg_dma_xfer_desc_t g_desc1;  /**< \brief DMA������ */

/**
 * \brief DMA �жϷ������
 */
static void dma_isr1 (void *p_arg , uint32_t flag)
{
    int i;

    if (flag == AM_ZLG_DMA_INT_NORMAL) {

        for (i = 0; i < BUF_SIZE1; i++) {

            /* ��12λΪADC�ɼ����� */
            __g_adc_dat1[i] = __g_buf_dst1[i] & 0xfff;
        }

        g_trans_done1 = AM_TRUE;
    }
}

static void __adc2_isr (void *p_arg)
{
    int i;
    amhw_zlg237_adc_t *p_hw_adc = (amhw_zlg237_adc_t *)p_arg;

    amhw_zlg237_adc_status_flag_clr(p_hw_adc, AMHW_ZLG237_ADC_INJECTED_CHAN_END_FLAG);

    for (i = 0 ; i < 3; i++) {

        /* ADֵ�Ļ�ȡ */
        /* �ر�ע�� �������ݼĴ����Ķ�����ֵ = ADʵ��ת��ֵ - ����ƫ�ƼĴ�����ƫ��ֵ*/
        __g_adc_dat2[i]  = amhw_zlg237_adc_injected_data_get(p_hw_adc, i);
        __g_adc_dat2[i] &= 0x0fff;
    }

    g_trans_done2 = AM_TRUE;
}

static void __zlg_adc1_init (amhw_zlg237_adc_t *p_hw_adc,
                            int                *p_adc_chan,
                            int                 adc_chan_num,
                            uint8_t             dma_chan)
{
    int i;
    uint32_t flags;

    /* ADC���� */
    amhw_zlg237_adc_disable(p_hw_adc);

    /* ����ADC������ͨ������ */
    if(adc_chan_num < 16) {
        amhw_zlg237_adc_regular_channel_length_set(
            p_hw_adc,
            (amhw_zlg237_adc_regular_channel_length_t)adc_chan_num-1);
    }

    for(i=0;i<adc_chan_num;i++) {

        /* ���ӹ���ͨ�����к�ADC����ͨ�� */
        amhw_zlg237_adc_regular_channel_order_set(
            p_hw_adc,
            AMHW_ZLG237_ADC_REGULAR_CHAN_ORDER_1st + i,
           (amhw_zlg237_adc_channel_t)p_adc_chan[i]);

        /* ���ò���ͨ���Ĳ������� */
        amhw_zlg237_adc_smpr_set(
            p_hw_adc,
            AMHW_ZLG237_ADC_CHAN_ST55_5,
            (amhw_zlg237_adc_channel_t)p_adc_chan[i]);
    }
    /* ���ù���ͨ���ⲿ�����������ó����������ʽ */
    amhw_zlg237_adc_extirig_enable(p_hw_adc);
    amhw_zlg237_adc_extsel_set(p_hw_adc, AMHW_ZLG237_ADC12_REGULAR_SWSTART);


    /* ����ɨ��ģʽ */
    amhw_zlg237_adc_scan_mode_enable(p_hw_adc);

    /* ����ת�� */
    amhw_zlg237_adc_cont_set(p_hw_adc, AMHW_ZLG237_ADC_CONVERSION_SINGLE);

    /* ���óɶ���ģʽ */
    amhw_zlg237_adc_dul_mode_set(p_hw_adc, AMHW_ZLG237_ADC_DUL_MODE_0);

    /* ���뷽ʽ--�Ҷ��� */
    amhw_zlg237_adc_data_alignment_set(p_hw_adc,AMHW_ZLG237_ADC_DATA_RIGHT);

    /* �ر�ADC16ͨ���ڲ��¶ȴ���������ADC1��Ч��*/
    amhw_zlg237_adc_tsvrefe_disable(p_hw_adc);

    /* ����ADC��DMA���� */
    amhw_zlg237_adc_dma_enable(p_hw_adc);

    /* ADCʹ��*/
    amhw_zlg237_adc_enable(p_hw_adc);

    /* DMA �������� */
    flags = AMHW_ZLG_DMA_CHAN_PRIORITY_HIGH         |  /* �ж����ȼ� �� */
            AMHW_ZLG_DMA_CHAN_MEM_SIZE_32BIT        |  /* �ڴ����ݿ�� 2 �ֽ� */
            AMHW_ZLG_DMA_CHAN_PER_SIZE_32BIT        |  /* �������ݿ�� 2 �ֽ� */
            AMHW_ZLG_DMA_CHAN_MEM_ADD_INC_ENABLE    |  /* �ڴ��ַ���� */
            AMHW_ZLG_DMA_CHAN_PER_ADD_INC_DISABLE   |  /* �����ַ������ */
            AMHW_ZLG_DMA_CHAN_CIRCULAR_MODE_ENABLE  |  /* ��ѭ��ģʽ */
            AMHW_ZLG_DMA_CHAN_INT_TX_CMP_ENABLE;       /* ʹ��DMA��������ж� */


    /* ���� DMA �жϷ����� */
    am_zlg_dma_isr_connect(dma_chan, dma_isr1, (void *)p_hw_adc);

    /* ����ͨ�������� */
    am_zlg_dma_xfer_desc_build(&g_desc1,                      /* ͨ�������� */
                               (uint32_t)(&p_hw_adc->dr),    /* Դ�����ݻ����� */
                               (uint32_t)(__g_buf_dst1),      /* Ŀ������ݻ����� */
                               sizeof(__g_buf_dst1),          /* �����ֽ��� */
                               flags);                       /* �������� */
    /* DMA�Ĵ������� */
    am_zlg_dma_xfer_desc_chan_cfg(&g_desc1,
                                   AMHW_ZLG_DMA_PER_TO_MER, /* ���赽�ڴ� */
                                   dma_chan);

    /* ���� DMA ���䣬���Ͽ�ʼ���� */
    am_zlg_dma_chan_start(dma_chan);
}

static void __zlg_adc2_init (amhw_zlg237_adc_t *p_hw_adc,
                            int                *p_adc_chan,
                            int                 adc_chan_num)
{
    int i;
    /* ADC���� */
    amhw_zlg237_adc_disable(p_hw_adc);
     /* ����ADCע��ͨ������ */
   if(adc_chan_num < 4) {
       amhw_zlg237_adc_injected_channel_length_set(
           p_hw_adc,
           (amhw_zlg237_adc_injected_channel_length_t)(adc_chan_num-1));
   }
   else
   {
       amhw_zlg237_adc_injected_channel_length_set(
           p_hw_adc, AMHW_ZLG237_ADC_INJECTED_CHAN_LENGTH_4);

   }

   /**
    * \note : ��ͬ�ڹ���ת�����У���� JL[1:0]�ĳ���С�� 4����ת��������˳���Ǵ�(4-JL)��ʼ��
    *         ���磺ADC_JSQR[21:0] =   10    00011   00011   00111  00010
    *                               3��ת��            3       3       7      2
    *         ��ζ��ɨ��ת����������ͨ��˳��ת����7�� 3��3�������� 2��7��3��
    *
    *         ���������ͨ��������ADC����ͨ���������Ƿ����
    */
   for(i=0;i<adc_chan_num;i++) {

       /* ����ע��ͨ�����к�ADC����ͨ�� */
       amhw_zlg237_adc_injected_channel_order_set(
           p_hw_adc,
           AMHW_ZLG237_ADC_INJECTED_CHAN_ORDER_4th - i,
           p_adc_chan[adc_chan_num - 1 - i]);

       /* ע��ͨ������ƫ�ƼĴ�����ֵ����λֵΪ0�� */
       /* ���ݼĴ�����ֵ = ʵ��ת��ֵ - ƫ��ֵ*/
       amhw_zlg237_adc_jofr_set(
           p_hw_adc,
           AMHW_ZLG237_ADC_INJECTED_DATA_CHAN_4 - i,
           0);

       /* ���ò���ͨ���Ĳ������� */
       amhw_zlg237_adc_smpr_set(
           p_hw_adc,
           AMHW_ZLG237_ADC_CHAN_ST55_5,
           p_adc_chan[adc_chan_num - 1 - i]);

   }

   /* ����ɨ��ģʽ */
   amhw_zlg237_adc_scan_mode_enable(p_hw_adc);

   /* �ر�ע��ͨ�����ģʽ������ͨ�����ģʽ*/
   amhw_zlg237_adc_injected_disc_disable(p_hw_adc);
   amhw_zlg237_adc_regular_disc_disable(p_hw_adc);

   /* ����ת�� */
   amhw_zlg237_adc_cont_set(p_hw_adc, AMHW_ZLG237_ADC_CONVERSION_SINGLE);

   /* ����ע��ͨ���ⲿ�����������ó����������ʽ */
   amhw_zlg237_adc_jextirig_enable(p_hw_adc);
   amhw_zlg237_adc_jextsel_set(p_hw_adc, AMHW_ZLG237_ADC12_INJECTED_JSWSTART);

   /* ���óɶ���ģʽ,ADC1��ADC2��������*/
   amhw_zlg237_adc_dul_mode_set(p_hw_adc, AMHW_ZLG237_ADC_DUL_MODE_0);

   /* ���뷽ʽ--�Ҷ���*/
   amhw_zlg237_adc_data_alignment_set(p_hw_adc,AMHW_ZLG237_ADC_DATA_RIGHT);

   /* ADCʹ��*/
   amhw_zlg237_adc_enable(p_hw_adc);

   /* ���ø�λУ׼*/
   amhw_zlg237_adc_rstcal_enable(p_hw_adc);

   /* �ȴ���λУ׼����*/
   while(amhw_zlg237_adc_rstcal_check(p_hw_adc) == AM_FALSE);

   /* ����ADУ׼*/
   amhw_zlg237_adc_cal_enable(p_hw_adc);

   /* �ȴ�ADУ׼����*/
   while(amhw_zlg237_adc_cal_check(p_hw_adc) == AM_FALSE);

   /* ����ת������ж� */
   am_int_connect(INUM_ADC1_2, __adc2_isr, p_hw_adc);
   am_int_enable(INUM_ADC1_2);

   /* ת�������ж�ʹ��*/
   amhw_zlg237_adc_int_enable(p_hw_adc, AMHW_ZLG237_ADC_INT_INJECTED_END);

}
/**
 * \brief �������
 */
void demo_zlg237_hw_adc_dma_double_entry (amhw_zlg237_adc_t *p_hw_adc1,
                                          int               *p_adc1_chan,
                                          int                adc1_chan_num,
                                          uint8_t            dma_chan,
                                          amhw_zlg237_adc_t *p_hw_adc2,
                                          int               *p_adc2_chan,
                                          int                adc2_chan_num)
{
    uint32_t adc_mv = 0;    /* ������ѹ */
    int      i;

    /* ʹ�÷�Ĭ��demo����ʱ�����ȸ��ݾ���ʹ�õ�ADCͨ�������޸�BUF_SIZE�궨��*/
    am_kprintf("The ADC HW dma Demo\r\n");
    /* ����ADC����Ƶ�ʣ�72MHz��8��Ƶ */
    amhw_zlg237_rcc_adc_div_set (2);

    /* adc��س�ʼ������ */
    __zlg_adc1_init(p_hw_adc1, p_adc1_chan, adc1_chan_num, dma_chan);
    __zlg_adc2_init(p_hw_adc2, p_adc2_chan, adc2_chan_num);


    while(1) {
        /* ��ʼת�� */
        amhw_zlg237_adc_swstart_enable(p_hw_adc1);
        amhw_zlg237_adc_jswstart_enable(p_hw_adc2);

        while((g_trans_done1 == AM_FALSE) && (g_trans_done2 == AM_FALSE) );
        /* �ȴ�������� */
        if(g_trans_done1 == AM_TRUE) {
            for (i = 0; i < adc1_chan_num; i++) {

                /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
                adc_mv = __g_adc_dat1[i] * 3300 / ((1UL << 12) -1);

                /* ���ڴ�ӡ����*/
                am_kprintf("ADC1 chan: %d, Sample : %d, Vol: %d mv\r\n", p_adc1_chan[i],
                                                                       __g_adc_dat1[i],
                                                                        adc_mv);
            }
            am_kprintf("\r\n");
            g_trans_done1 = AM_FALSE;
        }

        if(g_trans_done2 == AM_TRUE) {
            for (i = 0; i < adc2_chan_num; i++) {

                /* ת��Ϊ��ѹֵ��Ӧ������ֵ */
                adc_mv = __g_adc_dat2[i] * 3300 / ((1UL << 12) -1);

                /* ���ڴ�ӡ����*/
                am_kprintf("ADC2 chan: %d, Sample : %d, Vol: %d mv\r\n", p_adc2_chan[i],
                                                                       __g_adc_dat2[i],
                                                                         adc_mv);
            }
            am_kprintf("\r\n");
            g_trans_done2 = AM_FALSE;
        }

        am_mdelay(2000);

        /* DMA�����־ʧЧ */
    }
}
/** [src_zlg237_hw_adc_dma_int] */

/* end of file */

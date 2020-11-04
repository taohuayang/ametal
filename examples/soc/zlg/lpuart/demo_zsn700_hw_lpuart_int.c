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
 * \brief LPUART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� "HW example---LPUART test in interrupt mode:"��
 *   2. ָ������������յ����ַ���
 *
 * \note
 *   1.���ô�������Դ���һ�£���رյ��Դ�������Ӱ��Ч��
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_lpuart_int.c src_zsn700_hw_lpuart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-06  YRZ, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zsn700_hw_lpuart_int
 * \copydoc demo_zsn700_hw_lpuart_int.c
 */

/** [src_zsn700_hw_lpuart_int] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_zsn700_lpuart.h"
#include "hw/amhw_zsn700_rcc.h"

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static const uint8_t hw_polling_str[] =
                         {"HW example---LPUART test in interrupt mode:\r\n"};

static const uint8_t   *gp_tx_buf   = NULL; /**< \brief ���ͻ����� */
static volatile uint8_t g_tx_index  = 0;    /**< \brief ��ǰ������������ */
static volatile uint8_t g_tx_nbytes = 0;    /**< \brief ��Ҫ���͵����ֽ��� */

static uint32_t lpuart_baudrate = 0;

/**
 * \brief ���ڷ������ݣ��ж�ģʽ�£��ú�������������
 *
 * \param[in] p_hw_lpuartָ������ƵĴ����豸�ṹ��
 * \param[in] p_buf    ָ�������ݵĻ�����
 * \param[in] len      ���͵��ֽ���
 *
 * \retval 1 ���;���
 * \retval 0 ����ģ��æµ���޷�����
 *
 * \note ���ͻ����������ȫ�ֵģ���֤���������ݷ������ǰ��������û�б��ͷŵ�
 */
static uint8_t lpuart_int_send (amhw_zsn700_lpuart_t *p_hw_lpuart,
                                const uint8_t   *p_buf,
                                uint32_t         len)
{
    if (g_tx_index >= g_tx_nbytes)  {   /* �ϴη����Ѿ�������� */
        gp_tx_buf   = p_buf;            /* ���¶��巢�ͻ������� */
        g_tx_index  = 0;                /* �ӻ�������ʼ�ֽڿ�ʼ���� */
        g_tx_nbytes = len;              /* ����g_tx_nbytes���ֽ� */

        /* ������дһ��һ���ֽڵ����ݲ��Բ��������ж� */
        while(amhw_zsn700_lpuart_flag_check(
                  p_hw_lpuart,
                  AMHW_ZSN700_LPUART_FLAG_TX_EMPTY) ==
                  AM_FALSE);

        amhw_zsn700_lpuart_data_write(p_hw_lpuart, p_buf[g_tx_index++]);

        amhw_zsn700_lpuart_int_enable(p_hw_lpuart,
                                      AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE);

        return 1;
    }

    return 0;
}

/**
 * \brief �����жϷ�����
 *
 * \param[in] p_arg ָ������ƵĴ����豸�ṹ�� ���� am_int_connect() ע��
 */
static void lpuart_hw_irq_handler (void *p_arg)
{
    amhw_zsn700_lpuart_t *p_hw_lpuart = (amhw_zsn700_lpuart_t *)p_arg;
    uint8_t             data;

    if (amhw_zsn700_lpuart_flag_check(p_hw_lpuart,
                                      AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE) ==
                                      AM_TRUE) {

        amhw_zsn700_lpuart_flag_clr(p_hw_lpuart,
                                    AMHW_ZSN700_LPUART_FLAG_RX_COMPLETE);

        /* ��ȡ�½������ݣ������ͳ�ȥ */
        data = amhw_zsn700_lpuart_data_read(p_hw_lpuart);
        amhw_zsn700_lpuart_data_write(p_hw_lpuart, data);

    } else  if (amhw_zsn700_lpuart_flag_check(
                    p_hw_lpuart,
                    AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE) ==
                    AM_TRUE) {

        amhw_zsn700_lpuart_flag_clr(p_hw_lpuart,
                                    AMHW_ZSN700_LPUART_FLAG_TX_COMPLETE);

        /* �����ж� */
        if(g_tx_index < g_tx_nbytes) {

            /* ���������д��������� */
            amhw_zsn700_lpuart_data_write(p_hw_lpuart, gp_tx_buf[g_tx_index++]);

        } else {

            /* ������û�з������ݣ��رշ����ж� */
            amhw_zsn700_lpuart_int_disable(p_hw_lpuart,
                                           AMHW_ZSN700_LPUART_INT_TX_COMPLETE);
        }
    }
}

/**
 * \brief LPUART hw �ж��շ���ʼ��
 */
void lpuart_int_init (amhw_zsn700_lpuart_t *p_hw_lpuart,
                      void (* pfn_init)(void),
                      uint8_t               clk_src,
                      uint32_t              clk_rate,
                      unsigned long         lpuart_base,
                      unsigned char         inum_lpuart)
{
    /* ����ģʽ����  */
    amhw_zsn700_lpuart_mode_sel(p_hw_lpuart, AMHW_ZSN700_LPUART_WORK_MODE_1);

    /* ����ͨ��ʱ��Դ */
    amhw_zsn700_lpuart_clk_src_sel(p_hw_lpuart,
                                   (amhw_zsn700_lpuart_sclk_src_t)clk_src);

    if(clk_src == AMHW_ZSN700_LPUART_SCLK_SRC_XTL) {

        /* �ⲿ������������ѡ�� */
        amhw_zsn700_rcc_xtl_xtal_driver_set(AMHW_ZSN700_XTL_XTAL_DRIVER_DEFAULT);

        /* XTL�����񵴷��ȵĵ��� */
        amhw_zsn700_rcc_xtl_xtal_amplitude_set(
            AMHW_ZSN700_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

        /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
        amhw_zsn700_rcc_xtl_waittime_set(AMHW_ZSN700_XTL_WAITTIME_16384);

        amhw_zsn700_rcc_set_start(0x5A5A);
        amhw_zsn700_rcc_set_start(0xA5A5);

        amhw_zsn700_rcc_xtl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zsn700_rcc_xtl_state_get() == AM_FALSE);

    } else if(clk_src == AMHW_ZSN700_LPUART_SCLK_SRC_RCL) {

        /* ����RCLʱ��Ƶ��У׼ֵ ��38.4KHz��*/
        amhw_zsn700_rcc_rcl_trim_set(*((uint16_t*)0x00100C20));

        amhw_zsn700_rcc_rcl_waittime_set(AMHW_ZSN700_RCL_WAITTIME_256);

        amhw_zsn700_rcc_set_start(0x5A5A);
        amhw_zsn700_rcc_set_start(0xA5A5);

        amhw_zsn700_rcc_rcl_enable();

        /* �ȴ��ȶ�*/
        while(amhw_zsn700_rcc_rcl_state_get() == AM_FALSE);
    }

    /* ��Ƶϵ������  */
    amhw_zsn700_lpuart_clk_div_sel(p_hw_lpuart,
                                   AMHW_ZSN700_LPUART_SCLK_DIV_MODE13_4);

    /* ֹͣλ���� */
    amhw_zsn700_lpuart_stop_bit_sel(p_hw_lpuart,
                                    AMHW_ZSN700_LPUART_STOP_1_0_BIT);

    /* У������ */
    amhw_zsn700_lpuart_parity_bit_sel(p_hw_lpuart,
                                      AMHW_ZSN700_LPUART_PARITY_NO);

    /* ���������� */
    amhw_zsn700_lpuart_baudrate_set( p_hw_lpuart, clk_rate, lpuart_baudrate);

    /* ��������ж�ʹ�� */
    amhw_zsn700_lpuart_int_enable(p_hw_lpuart,
                                  AMHW_ZSN700_LPUART_INT_RX_COMPLETE);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zsn700_lpuart_enable(p_hw_lpuart,AMHW_ZSN700_LPUART_RX);

    /* �����ж������ţ������ж� */
    am_int_connect(inum_lpuart, lpuart_hw_irq_handler, (void *)p_hw_lpuart);
    am_int_enable(inum_lpuart);
    if(pfn_init != NULL){
        pfn_init();
    }
}

/**
 * \brief �������
 */
void demo_zsn700_hw_lpuart_int_entry (void             *p_hw_lpuart,
                                      void (* pfn_init)(void),
                                      uint8_t           sclk_src,
                                      uint32_t          sclk_rate,
                                      uint32_t          baudrate,
                                      unsigned long     lpuart_base,
                                      unsigned char     inum_lpuart)
{
    amhw_zsn700_lpuart_t *p_lpuart = (amhw_zsn700_lpuart_t *)p_hw_lpuart;

    lpuart_baudrate = baudrate;

    if (pfn_init == NULL) {
        return;
    }

    lpuart_int_init(p_lpuart,
                    pfn_init,
                    sclk_src,
                    sclk_rate,
                    lpuart_base,
                    inum_lpuart);

    lpuart_int_send(p_lpuart, hw_polling_str, sizeof(hw_polling_str));

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zsn700_hw_lpuart_int] */

/* end of file */

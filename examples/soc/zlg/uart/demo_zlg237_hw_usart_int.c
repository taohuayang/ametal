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
 * \brief USART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� "HW example---USART test in interrupt mode:"��
 *   2. ָ������������յ����ַ���
 *
 * \note
 *   1.���ô�������Դ���һ�£���رյ��Դ�������Ӱ��Ч��
 *
 * \par Դ����
 * \snippet demo_zlg237_hw_usart_int.c src_zlg237_hw_usart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-01-20  ari, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zlg237_hw_usart_int
 * \copydoc demo_zlg237_hw_usart_int.c
 */

/** [src_zlg237_hw_usart_int] */
#include "amhw_zlg237_usart.h"
#include "ametal.h"
#include "am_int.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define USART_BAUDRATE      (115200)           /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static const uint8_t hw_polling_str[] =
                              {"HW example---USART test in interrupt mode:\r\n"};

static const uint8_t   *gp_tx_buf   = NULL; /**< \brief ���ͻ����� */
static volatile uint8_t g_tx_index  = 0;    /**< \brief ��ǰ������������ */
static volatile uint8_t g_tx_nbytes = 0;    /**< \brief ��Ҫ���͵����ֽ��� */

/**
 * \brief ���ڷ������ݣ��ж�ģʽ�£��ú�������������
 *
 * \param[in] p_hw_usartָ������ƵĴ����豸�ṹ��
 * \param[in] p_buf    ָ�������ݵĻ�����
 * \param[in] len      ���͵��ֽ���
 *
 * \retval 1 ���;���
 * \retval 0 ����ģ��æµ���޷�����
 *
 * \note ���ͻ����������ȫ�ֵģ���֤���������ݷ������ǰ��������û�б��ͷŵ�
 */
static uint8_t usart_int_send (amhw_zlg237_usart_t *p_hw_usart,
                               const uint8_t       *p_buf,
                               uint32_t             len)
{
    if (g_tx_index >= g_tx_nbytes)  {   /* �ϴη����Ѿ�������� */
        gp_tx_buf   = p_buf;            /* ���¶��巢�ͻ������� */
        g_tx_index  = 0;                /* �ӻ�������ʼ�ֽڿ�ʼ���� */
        g_tx_nbytes = len;              /* ����g_tx_nbytes���ֽ� */

        /* ������дһ��һ���ֽڵ����ݲ��Բ��������ж� */
        while(amhw_zlg237_usart_status_flag_check(p_hw_usart,
        									      AMHW_ZLG237_USART_TX_COMPLETE_FLAG)
                                                  == AM_FALSE);

        amhw_zlg237_usart_data_write(p_hw_usart, p_buf[g_tx_index++]);

        amhw_zlg237_usart_int_enable(p_hw_usart,AMHW_ZLG237_USART_INT_TX_EMPTY_ENABLE);

        return 1;
    }

    return 0;
}

/**
 * \brief �����жϷ�����
 *
 * \param[in] p_arg ָ������ƵĴ����豸�ṹ�� ���� am_int_connect() ע��
 */
static void usart_hw_irq_handler (void *p_arg)
{
    amhw_zlg237_usart_t *p_hw_usart = (amhw_zlg237_usart_t *)p_arg;
    uint8_t          data;

    if (amhw_zlg237_usart_status_flag_check(
            p_hw_usart, AMHW_ZLG237_USART_RX_NOT_EMPTY_FLAG) == AM_TRUE) {
        amhw_zlg237_usart_status_flag_clr(p_hw_usart, AMHW_ZLG237_USART_RX_NOT_EMPTY_FLAG);

        /* ��ȡ�½������ݣ������ͳ�ȥ */

        data = amhw_zlg237_usart_data_read(p_hw_usart);
        amhw_zlg237_usart_data_write(p_hw_usart, data);

    } else if (amhw_zlg237_usart_status_flag_check(p_hw_usart,
    		                                AMHW_ZLG237_USART_TX_EMPTY_FLAG) == AM_TRUE) {
        amhw_zlg237_usart_status_flag_clr(p_hw_usart,
        		                   AMHW_ZLG237_USART_TX_EMPTY_FLAG);
        /* �����ж� */
        if(g_tx_index < g_tx_nbytes) {

            /* ���������д��������� */
            amhw_zlg237_usart_data_write(p_hw_usart, gp_tx_buf[g_tx_index++]);

        } else {

            /* ������û�з������ݣ��رշ����ж� */
        	amhw_zlg237_usart_int_disable(p_hw_usart, AMHW_ZLG237_USART_INT_TX_EMPTY_ENABLE);
        }
    }
}

/**
 * \brief USART hw �ж��շ���ʼ��
 */
void usart_int_init (amhw_zlg237_usart_t *p_hw_usart,
                     void (* pfn_init)(void),
                     uint32_t         clk_rate,
                     unsigned long    usart_base,
                     unsigned char    inum_usart)
{
    uint8_t inum = 0;

    amhw_zlg237_usart_stop_bit_sel(p_hw_usart, AMHW_ZLG237_USART_STOP_10_BIT);
    amhw_zlg237_usart_word_length_sel(p_hw_usart, AMHW_ZLG237_USART_DATA_8BIT);
    amhw_zlg237_usart_parity_bit_sel(p_hw_usart,  AMHW_ZLG237_USART_PARITY_NO);

    /* ���ô��ڲ����� */
    amhw_zlg237_usart_baudrate_set(p_hw_usart, clk_rate, USART_BAUDRATE);

    /* �ر����д����ж� */
    amhw_zlg237_usart_int_disable(p_hw_usart, AMHW_ZLG237_USART_INT_ALL_ENABLE_MASK);

    /* �������ͬ���ڶ�Ӧ���ж������� */
    if ((uint32_t)p_hw_usart - usart_base) {
        inum = inum_usart + 1;
    } else {
        inum = inum_usart;
    }

    /* ʹ�ܴ��� */
    amhw_zlg237_usart_receiver_enable(p_hw_usart);
    amhw_zlg237_usart_transmitter_enable(p_hw_usart);
    amhw_zlg237_usart_enable(p_hw_usart);

    /* ʹ�ܽ���׼�ж� */
    amhw_zlg237_usart_int_enable(p_hw_usart,AMHW_ZLG237_USART_INT_RX_NOT_EMPTY_ENABLE);

    /* �����ж������ţ������ж� */
    am_int_connect(inum, usart_hw_irq_handler, (void *)p_hw_usart);
    am_int_enable(inum);
    if(pfn_init != NULL){
        pfn_init();
    }
}

/**
 * \brief �������
 */
void demo_zlg237_hw_usart_int_entry (amhw_zlg237_usart_t *p_hw_usart,
                                     void (* pfn_init)(void),
                                     uint32_t             clk_rate,
                                     unsigned long        usart_base,
                                     unsigned char        inum_usart)
{
    if (pfn_init == NULL) {
        return;
    }
    usart_int_init(p_hw_usart, pfn_init, clk_rate , usart_base, inum_usart);

    usart_int_send(p_hw_usart, hw_polling_str, sizeof(hw_polling_str));

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg237_hw_usart_int] */

/* end of file */

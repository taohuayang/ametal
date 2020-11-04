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
 * \brief SPI �ӻ�������ʵ�ֺ���(DMA ��ʽ)
 *
 * \internal
 * \par Modification History
 * -1.00 20-04-01 cds, first implementation
 * \endinternal
 */

/*******************************************************************************
includes
*******************************************************************************/

#include "ametal.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "am_hc32f460_dma.h"
#include "am_hc32f460_spi_slv_dma.h"
#include "hw/amhw_hc32f460_spi.h"

/*******************************************************************************
  ģ���ں�������
*******************************************************************************/
extern am_hc32f460_dma_dev_t __g_dma1_dev;
extern am_hc32f460_dma_dev_t __g_dma2_dev;

/** \brief SPI �ӻ�Ӳ����ʼ�� */
static int __spi_slv_hard_init (am_hc32f460_spi_slv_dma_dev_t *p_dev);

/** \brief SPI �ӻ� DMA �жϴ����� */
static void __spi_slv_dma_isr (void *p_arg, uint32_t stat);

/** \brief SPI �ӻ� DMA ���䴦���� */
static int __spi_slv_transfer_data (am_hc32f460_spi_slv_dma_dev_t *p_dev);

/*******************************************************************************
  SPI ������������
*******************************************************************************/

/** \brief ���� SPI �ӻ��豸  */
static int __spi_slv_setup (void *p_drv, am_spi_slv_device_t *p_dev);
/** \brief �ر� SPI �ӻ��豸  */
static int __spi_slv_shutdown (void *p_drv, am_spi_slv_device_t *p_dev);

/**
 * \brief SPI ���豸������������
 */
static const struct am_spi_slv_drv_funcs __g_spi_slv_drv_funcs = {
    __spi_slv_setup,
    __spi_slv_shutdown,
};

/**
 * \brief SPI Ӳ����ʼ��
 */
static int __spi_slv_hard_init (am_hc32f460_spi_slv_dma_dev_t *p_this)
{
    amhw_hc32f460_spi_t *p_hw_spi = (amhw_hc32f460_spi_t *)
                                    (p_this->p_devinfo->spi_reg_base);

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    amhw_hc32f460_spi_enable(p_hw_spi, AM_FALSE);

    /* ����SPIͨ��ģʽ */
    amhw_hc32f460_spi_trans_mode_sel(p_hw_spi,
                                     AMHW_HC32F460_SPI_TRANS_MODE_FULL_DUPLEX);

    /* ����SPI����ģʽ */
    amhw_hc32f460_spi_work_mode_sel(p_hw_spi,
                                    AMHW_HC32F460_SPI_WORK_MODE_4LINE);

    /* �������ݳ��� */
    amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                      AMHW_HC32F460_SPI_DATA_LENGTH_BIT8);

    /* ����Ϊ�ӻ�ģʽ */
    amhw_hc32f460_spi_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_MODE_SLAVE);

    amhw_hc32f460_spi_frame_number_set(p_hw_spi, AMHW_HC32F460_SPI_FRAME_NUMBER1);

    amhw_hc32f460_spi_first_bit_position_set(p_hw_spi, AMHW_HC32F460_SPI_MSB_FIRST);
    amhw_hc32f460_spi_sck_polarity_set(p_hw_spi, AMHW_HC32F460_SPI_SCK_IDLE_LEVEL_LOW);

    /* ����SPIģʽ��ʱ����λ�ͼ��ԣ� */
    amhw_hc32f460_spi_clk_mode_set(p_hw_spi, 0x3 & AM_SPI_SLV_MODE_0);

    return AM_OK;
}

/**
 * \brief �ӻ�����
 */
static int __spi_slv_cfg (am_hc32f460_spi_slv_dma_dev_t *p_this,
                          am_spi_slv_device_t           *p_slv_dev)
{
    amhw_hc32f460_spi_t         *p_hw_spi =
            (amhw_hc32f460_spi_t *) (p_this->p_devinfo->spi_reg_base);

    /* Ĭ������Ϊ 8 λ����󲻳��� 32 λ */
    if (p_slv_dev->bits_per_word == 0) {
        p_slv_dev->bits_per_word = 8;
    } else if (p_slv_dev->bits_per_word > 32) {
        return -AM_ENOTSUP;
    }

    /* ��8λ��1~32 �����շ�ֻ֧�� LSB ģʽ */
    if (!(p_slv_dev->mode & AM_SPI_SLV_LSB_FIRST) &&
         (p_slv_dev->bits_per_word != 8) ) {
        return -AM_ENOTSUP;
    }

    /* ���� LSB �� MSB */
    if (p_slv_dev->mode & AM_SPI_SLV_LSB_FIRST) {
    	amhw_hc32f460_spi_first_bit_position_set(p_hw_spi, AMHW_HC32F460_SPI_LSB_FIRST);
    } else {
    	amhw_hc32f460_spi_first_bit_position_set(p_hw_spi, AMHW_HC32F460_SPI_MSB_FIRST);
    }

    /* �������ݳ��� */
    switch (p_slv_dev->bits_per_word) {

    case 4:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT4);
        break;
    case 5:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT5);
        break;
    case 6:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT6);
        break;
    case 7:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT7);
        break;
    case 8:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT8);
        break;
    case 9:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT9);
        break;
    case 10:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT10);
        break;
    case 11:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT11);
        break;
    case 12:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT12);
        break;
    case 13:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT13);
        break;
    case 14:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT14);
        break;
    case 15:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT15);
        break;
    case 16:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT16);
        break;
    case 20:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT20);
        break;
    case 24:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT24);
        break;
    case 32:
        amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                          AMHW_HC32F460_SPI_DATA_LENGTH_BIT32);
        break;
    }

    /* ����SPIģʽ��ʱ����λ�ͼ��ԣ� */
    amhw_hc32f460_spi_clk_mode_set(p_hw_spi, p_slv_dev->mode);

    return AM_OK;
}

/**
 * \brief Ƭѡ�ж�
 */
void __cs_irq_handle (void *p_arg)
{
    am_hc32f460_spi_slv_dma_dev_t *p_this    = ( am_hc32f460_spi_slv_dma_dev_t *)p_arg;
    amhw_hc32f460_spi_t           *p_hw_spi  = (amhw_hc32f460_spi_t *) (p_this->p_devinfo->spi_reg_base);
    am_spi_slv_device_t           *p_dev     = p_this->p_spi_slv_dev;
    uint8_t                        cs_status = am_gpio_get(p_this->p_devinfo->cs_pin);
    size_t                         count     = 0;
    am_hc32f460_dma_dev_t         *p_dma_dev = &__g_dma1_dev;

    if((cs_status == 1)) { /* ������� */
        count = p_this->sum_nbytes - \
             am_hc32f460_dma_tran_data_get(p_dma_dev, p_this->p_devinfo->dma_chan_rx);

         if(p_dev->p_slv_cb_funcs->pfn_cs_inactive) {
             p_dev->p_slv_cb_funcs->pfn_cs_inactive(p_dev->p_arg, count);
         }

         /* �رշ��� DMA ����  */
         am_hc32f460_dma_chan_stop(p_dma_dev, p_this->p_devinfo->dma_chan_tx);

         /* �ر� SPI��ͬʱ������ջ���������λ�Ĵ����е����� */
         amhw_hc32f460_spi_enable(p_hw_spi, AM_FALSE);
         amhw_hc32f460_spi_enable(p_hw_spi, AM_TRUE);

         /* ģ��һ�� DMA ������ɣ�SPI �� 8 �ֽڵ� FIFO��û��ʱ����Ҳ���� DMA ���� */
         am_hc32f460_dma_xfer_desc_build(&(p_this->g_desc[0]),                /* ͨ�������� */
                                          (uint32_t)(&(p_this->dummy_txbuf)), /* Դ�������׵�ַ */
                                          (uint32_t)(&(p_hw_spi->DR)),        /* Ŀ�Ļ������׵�ַ */
                                          1,                                  /* �����ֽ��� */
                                          p_this->dummy_dma_flags);           /* �������� */

         if (am_hc32f460_dma_xfer_desc_chan_cfg(p_dma_dev,
                                                &(p_this->g_desc[0]),
                                                AMHW_HC32F460_DMA_MER_TO_PER,     /* �ڴ浽���� */
                                                p_this->p_devinfo->dma_chan_tx) == AM_OK) {
             am_hc32f460_dma_chan_start(p_dma_dev, p_this->p_devinfo->dma_chan_tx);
         }

         /* ������ֽ��� ���ر� SPI��Ƭѡ��Чʱ�����д��� */
         amhw_hc32f460_spi_enable(p_hw_spi, AM_FALSE);

    } else { /* ���俪ʼ */

        if(p_dev->p_slv_cb_funcs->pfn_cs_active) {
            p_dev->p_slv_cb_funcs->pfn_cs_active(p_dev->p_arg);
        }

        p_this->sum_nbytes = 0;

        /* ���� DMA ֮ǰ����ر� DMA ͨ�� */
        am_hc32f460_dma_chan_stop(p_dma_dev, p_this->p_devinfo->dma_chan_tx);
        am_hc32f460_dma_chan_stop(p_dma_dev, p_this->p_devinfo->dma_chan_rx);

        /* ���� DMA ���� */
        __spi_slv_transfer_data(p_this);

        amhw_hc32f460_spi_enable(p_hw_spi, AM_TRUE);
    }
}

/**
 * \brief ʹ�� CS �����ⲿ�ж�
 */
static int __cs_irq_cfg (am_hc32f460_spi_slv_dma_dev_t *p_this)
{
    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    /* �����жϻص����� */
    am_gpio_trigger_connect(p_this->p_devinfo->cs_pin, __cs_irq_handle, p_this);

    /* ����Ϊ˫���ش��� */
    am_gpio_trigger_cfg(p_this->p_devinfo->cs_pin, AM_GPIO_TRIGGER_BOTH_EDGES);

    /* ʹ�����Ŵ��� */
    am_gpio_trigger_on(p_this->p_devinfo->cs_pin);

    return AM_OK;
}

/**
 * \brief Ƭѡ���ʼ��
 */
static int __cs_irq_cfg_deinit (am_hc32f460_spi_slv_dma_dev_t *p_this)
{
    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    am_gpio_trigger_disconnect(p_this->p_devinfo->cs_pin,
                               __cs_irq_handle,
                               p_this);

    am_gpio_trigger_off(p_this->p_devinfo->cs_pin);

    return AM_OK;
}

/******************************************************************************/

/**
 * \brief ���� SPI ���豸
 */
static int __spi_slv_setup (void *p_drv, am_spi_slv_device_t *p_dev)
{
    am_hc32f460_spi_slv_dma_dev_t *p_this = (am_hc32f460_spi_slv_dma_dev_t *)p_drv;

    if (p_dev == NULL || p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (p_this->p_spi_slv_dev == NULL) {
        p_this->p_spi_slv_dev = p_dev;
    } else {
        return -AM_ENOTSUP;
    }

    /* ���ô� SPI */
    if (AM_OK != __spi_slv_cfg(p_this, p_dev) ) {
        return -AM_ENOTSUP;
    }

    /* ����Ƭѡ�ж� */
    __cs_irq_cfg(p_this);

    return AM_OK;
}

/**
 * \brief SPI �ӻ��رպ���
 */
static int __spi_slv_shutdown(void *p_drv, struct am_spi_slv_device *p_dev)
{
     am_hc32f460_spi_slv_dma_dev_t *p_this;
    
    if ( (p_drv   == NULL) ||
         (p_dev   == NULL)) {
        return -AM_EINVAL;
    }

    p_this = (am_hc32f460_spi_slv_dma_dev_t *)p_drv;

    __cs_irq_cfg_deinit(p_this);

    p_this->p_spi_slv_dev = NULL;

    return AM_OK;
}

/******************************************************************************/

/**
 * \brief SPI �ӻ� DMA �жϴ���
 */
static void __spi_slv_dma_isr (void *p_arg, uint32_t stat)
{
    am_hc32f460_spi_slv_dma_dev_t *p_this = (am_hc32f460_spi_slv_dma_dev_t *)p_arg;

    /* �жϷ��� */
    if (stat == AM_HC32F460_DMA_INT_COMPLETE)
    {

        /* ������ɻص� */
        __spi_slv_transfer_data(p_this);

    } else {

        /* �ж�Դ��ƥ�� */
    }
}

/**
 * \brief SPI �ӻ���������
 */
static int __spi_slv_transfer_data (am_hc32f460_spi_slv_dma_dev_t *p_dev)
{
    amhw_hc32f460_spi_t *p_hw_spi;
    am_spi_slv_device_t *p_slv_dev;
    am_hc32f460_dma_dev_t *p_dma_dev = &__g_dma1_dev;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_spi = (amhw_hc32f460_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    p_slv_dev = p_dev->p_spi_slv_dev;

    /* �����ֽ�����Ч�Լ�� */
    if (p_dev->tansfer.bits_per_word > 32) {
        return -AM_EINVAL;
    }

    /* �������ݻص� */
    if (p_slv_dev->p_slv_cb_funcs->pfn_tansfer_get) {
        if ( p_slv_dev->p_slv_cb_funcs->pfn_tansfer_get(p_slv_dev->p_arg,
                              &(p_dev->tansfer))  != AM_OK ) {
            return AM_OK;
        }
    } else {
        return -AM_ENODEV;
    }

    /* ����Ҫ���д��� */
    if (p_dev->tansfer.nbytes == 0 ) {
        return AM_OK;
    }

    /* 0 Ĭ��Ϊ���豸��ֵ */
    if (p_dev->tansfer.bits_per_word == 0 ) {
        p_dev->tansfer.bits_per_word = p_dev->p_spi_slv_dev->bits_per_word;
    }

    /* �ж��Ƿ���Ч  */
    if (!(p_slv_dev->mode & AM_SPI_SLV_LSB_FIRST) &&
           (p_slv_dev->bits_per_word != 8) ) {
        return -AM_ENOTSUP;
    }

    /* ͳ���ֽ��� */
    p_dev->sum_nbytes += p_dev->tansfer.nbytes;


    /* ��������ͨ�������� */
    if (p_dev->tansfer.p_tx_buf) {

        am_hc32f460_dma_xfer_desc_build(&(p_dev->g_desc[0]),                 /* ͨ�������� */
                                        (uint32_t)(p_dev->tansfer.p_tx_buf), /* Դ�������׵�ַ */
                                        (uint32_t)(&(p_hw_spi->DR)),         /* Ŀ�Ļ������׵�ַ */
                                         p_dev->tansfer.nbytes ,             /* �����ֽ��� */
                                         p_dev->dma_tx_flags);               /* �������� */

    } else {

        am_hc32f460_dma_xfer_desc_build(&(p_dev->g_desc[0]),                /* ͨ�������� */
                                        (uint32_t)(&(p_dev->dummy_txbuf)),  /* Դ�������׵�ַ */
                                        (uint32_t)(&(p_hw_spi->DR)),        /* Ŀ�Ļ������׵�ַ */
                                        p_dev->tansfer.nbytes,              /* �����ֽ��� */
                                        p_dev->dummy_dma_flags);            /* �������� */
    }

    /* ��������ͨ�������� */
    if ( p_dev->tansfer.p_rx_buf) {
        am_hc32f460_dma_xfer_desc_build(&(p_dev->g_desc[1]),                 /* ͨ�������� */
                                        (uint32_t)(&(p_hw_spi->DR)),         /* Դ�������׵�ַ */
                                        (uint32_t)(p_dev->tansfer.p_rx_buf), /* Ŀ�Ļ������׵�ַ */
                                         p_dev->tansfer.nbytes,              /* �����ֽ��� */
                                         p_dev->dma_rx_flags);               /* �������� */

    } else {
        am_hc32f460_dma_xfer_desc_build(&(p_dev->g_desc[1]),                /* ͨ�������� */
                                        (uint32_t)(&(p_hw_spi->DR)),        /* Դ�������׵�ַ */
                                        (uint32_t)(&(p_dev->dummy_rxbuf)),  /* Ŀ�Ļ������׵�ַ */
                                        p_dev->tansfer.nbytes ,             /* �����ֽ��� */
                                        p_dev->dummy_dma_flags);            /* �������� */

    }

    if (am_hc32f460_dma_xfer_desc_chan_cfg(p_dma_dev,
                                           &(p_dev->g_desc[1]),
                                           AMHW_HC32F460_DMA_PER_TO_MER,         /* ���赽�ڴ� */
                                           p_dev->p_devinfo->dma_chan_rx) == AM_ERROR) {
        return AM_ERROR;
    }

    if (am_hc32f460_dma_xfer_desc_chan_cfg(p_dma_dev,
                                           &(p_dev->g_desc[0]),
                                           AMHW_HC32F460_DMA_MER_TO_PER,        /* �ڴ浽���� */
                                           p_dev->p_devinfo->dma_chan_tx) == AM_ERROR) {
        return AM_ERROR;
    }

    am_hc32f460_dma_block_data_size(p_dma_dev, p_dev->p_devinfo->dma_chan_rx, 1);
    am_hc32f460_dma_block_data_size(p_dma_dev, p_dev->p_devinfo->dma_chan_tx, 1);


    /* ����DMA����Դ*/
    if((p_dev->p_devinfo->dev_id) == 1) {
        am_hc32f460_dma_chan_src_set(p_dma_dev, p_dev->p_devinfo->dma_chan_rx, EVT_SPI1_SRRI);
        am_hc32f460_dma_chan_src_set(p_dma_dev, p_dev->p_devinfo->dma_chan_tx, EVT_SPI1_SRTI);
    } else if((p_dev->p_devinfo->dev_id) == 2) {
        am_hc32f460_dma_chan_src_set(p_dma_dev, p_dev->p_devinfo->dma_chan_rx, EVT_SPI2_SRRI);
        am_hc32f460_dma_chan_src_set(p_dma_dev, p_dev->p_devinfo->dma_chan_tx, EVT_SPI2_SRTI);
    } else if((p_dev->p_devinfo->dev_id) == 3) {
        am_hc32f460_dma_chan_src_set(p_dma_dev, p_dev->p_devinfo->dma_chan_rx, EVT_SPI3_SRRI);
        am_hc32f460_dma_chan_src_set(p_dma_dev, p_dev->p_devinfo->dma_chan_tx, EVT_SPI3_SRTI);
    } else if((p_dev->p_devinfo->dev_id) == 4) {
        am_hc32f460_dma_chan_src_set(p_dma_dev, p_dev->p_devinfo->dma_chan_rx, EVT_SPI4_SRRI);
        am_hc32f460_dma_chan_src_set(p_dma_dev, p_dev->p_devinfo->dma_chan_tx, EVT_SPI4_SRTI);
    }

    am_hc32f460_dma_chan_start(p_dma_dev, p_dev->p_devinfo->dma_chan_rx);
    am_hc32f460_dma_chan_start(p_dma_dev, p_dev->p_devinfo->dma_chan_tx);

    return AM_OK;
}

/******************************************************************************/

/**
 * \brief SPI ��ʼ��
 *
 */
am_spi_slv_handle_t
am_hc32f460_spi_slv_dma_init (am_hc32f460_spi_slv_dma_dev_t           *p_dev,
                              const am_hc32f460_spi_slv_dma_devinfo_t *p_devinfo)
{
    if (NULL == p_devinfo || NULL == p_dev ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->spi_slv_serve.p_funcs = (struct am_spi_slv_drv_funcs *)&__g_spi_slv_drv_funcs;
    p_dev->spi_slv_serve.p_drv   = p_dev;

    if (p_devinfo->dma_dev_id == 1) {
        p_dev->p_dma_dev = &__g_dma1_dev;
    } else if (p_devinfo->dma_dev_id == 2) {
        p_dev->p_dma_dev = &__g_dma2_dev;
    }

    p_dev->p_devinfo = p_devinfo;

    p_dev->p_spi_slv_dev    = NULL;

    p_dev->tansfer.nbytes        = 0;
    p_dev->tansfer.bits_per_word = 0;
    p_dev->tansfer.p_rx_buf      = NULL;
    p_dev->tansfer.p_tx_buf      = NULL;
    p_dev->sum_nbytes      = 0;

    p_dev->dummy_txbuf      = 0;

    p_dev->dma_tx_flags = AMHW_HC32F460_DMA_CHAN_CFG_INT_ENABLE            |  /* ͨ���ж�ʹ�� */
                          AMHW_HC32F460_DMA_CHAN_CFG_SIZE_8BIT             |  /* ���ݿ�� 1 �ֽ� */
                          AMHW_HC32F460_DMA_CHAN_CFG_LLP_DISABLE           |  /* ����������� */
                          AMHW_HC32F460_DMA_CHAN_CFG_DSTADD_NOTSEQ_DISABLE |  /* Ŀ���ַ������������� */
                          AMHW_HC32F460_DMA_CHAN_CFG_SRCADD_NOTSEQ_DISABLE |  /* Դ��ַ������������� */
                          AMHW_HC32F460_DMA_CHAN_CFG_DST_DRPT_DISABLE      |  /* Ŀ���ظ�������� */
                          AMHW_HC32F460_DMA_CHAN_CFG_SRC_DRPT_DISABLE      |  /* Դ�ظ�������� */
                          AMHW_HC32F460_DMA_CHAN_SRC_ADD_INCREASING        |  /* Դ��ַ���� */
                          AMHW_HC32F460_DMA_CHAN_DST_ADD_FIXED;               /* Ŀ���ַ�̶� */

    p_dev->dma_rx_flags = AMHW_HC32F460_DMA_CHAN_CFG_INT_ENABLE            |  /* ͨ���ж�ʹ�� */
                          AMHW_HC32F460_DMA_CHAN_CFG_SIZE_8BIT             |  /* ���ݿ�� 1 �ֽ� */
                          AMHW_HC32F460_DMA_CHAN_CFG_LLP_DISABLE           |  /* ����������� */
                          AMHW_HC32F460_DMA_CHAN_CFG_DSTADD_NOTSEQ_DISABLE |  /* Ŀ���ַ������������� */
                          AMHW_HC32F460_DMA_CHAN_CFG_SRCADD_NOTSEQ_DISABLE |  /* Դ��ַ������������� */
                          AMHW_HC32F460_DMA_CHAN_CFG_DST_DRPT_DISABLE      |  /* Ŀ���ظ�������� */
                          AMHW_HC32F460_DMA_CHAN_CFG_SRC_DRPT_DISABLE      |  /* Դ�ظ�������� */
                          AMHW_HC32F460_DMA_CHAN_SRC_ADD_FIXED             |  /* Դ��ַ�̶� */
                          AMHW_HC32F460_DMA_CHAN_DST_ADD_INCREASING;          /* Ŀ���ַ���� */

    p_dev->dummy_dma_flags = AMHW_HC32F460_DMA_CHAN_CFG_INT_ENABLE            |  /* ͨ���ж�ʹ�� */
                             AMHW_HC32F460_DMA_CHAN_CFG_SIZE_8BIT             |  /* ���ݿ�� 1 �ֽ� */
                             AMHW_HC32F460_DMA_CHAN_CFG_LLP_DISABLE           |  /* ����������� */
                             AMHW_HC32F460_DMA_CHAN_CFG_DSTADD_NOTSEQ_DISABLE |  /* Ŀ���ַ������������� */
                             AMHW_HC32F460_DMA_CHAN_CFG_SRCADD_NOTSEQ_DISABLE |  /* Դ��ַ������������� */
                             AMHW_HC32F460_DMA_CHAN_CFG_DST_DRPT_DISABLE      |  /* Ŀ���ظ�������� */
                             AMHW_HC32F460_DMA_CHAN_CFG_SRC_DRPT_DISABLE      |  /* Դ�ظ�������� */
                             AMHW_HC32F460_DMA_CHAN_SRC_ADD_FIXED             |  /* Դ��ַ���� */
                             AMHW_HC32F460_DMA_CHAN_DST_ADD_FIXED;               /* Ŀ���ַ�̶� */


    /* ��ʼ��Ӳ�� */
    if (__spi_slv_hard_init(p_dev) != AM_OK) {
        return NULL;
    }

    /* ���� DMA �жϷ����� */
    am_hc32f460_dma_isr_connect(p_dev->p_dma_dev,
                                p_dev->p_devinfo->dma_chan_rx,
                                __spi_slv_dma_isr,
                                (void *)p_dev);

    return &(p_dev->spi_slv_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_hc32f460_spi_slv_dma_deinit (am_spi_slv_handle_t handle)
{
    am_hc32f460_spi_slv_dma_dev_t *p_dev     = (am_hc32f460_spi_slv_dma_dev_t *)handle;
    amhw_hc32f460_spi_t           *p_hw_spi  = (amhw_hc32f460_spi_t *)(p_dev->p_devinfo->spi_reg_base);
    am_hc32f460_dma_dev_t         *p_dma_dev = (am_hc32f460_dma_dev_t *)&__g_dma1_dev;

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_slv_serve.p_funcs = NULL;
    p_dev->spi_slv_serve.p_drv   = NULL;

    /* ���� SPI */
    amhw_hc32f460_spi_enable(p_hw_spi, AM_FALSE);

    am_hc32f460_dma_isr_disconnect(p_dma_dev,
                                   p_dev->p_devinfo->dma_chan_rx,
                                   __spi_slv_dma_isr,
                                   (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */

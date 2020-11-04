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
 * -1.00 19-07-18 fra, first implementation
 * \endinternal
 */

/*******************************************************************************
includes
*******************************************************************************/

#include "ametal.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_zlg_dma.h"
#include "am_zlg237_spi_slv_dma.h"
#include "hw/amhw_zlg237_spi.h"

/*******************************************************************************
  ģ���ں�������
*******************************************************************************/

/** \brief SPI �ӻ�Ӳ����ʼ�� */
static int __spi_slv_hard_init (am_zlg237_spi_slv_dma_dev_t *p_dev);

/** \brief SPI �ӻ� DMA �жϴ����� */
static void __spi_slv_dma_isr (void *p_arg, uint32_t stat);

/** \brief SPI �ӻ� DMA ���䴦���� */
static int __spi_slv_transfer_data (am_zlg237_spi_slv_dma_dev_t *p_dev);

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
static int __spi_slv_hard_init (am_zlg237_spi_slv_dma_dev_t *p_this)
{
    amhw_zlg237_spi_t *p_hw_spi = (amhw_zlg237_spi_t *)
                                  (p_this->p_devinfo->spi_reg_base);

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    amhw_zlg237_spi_disable(p_hw_spi);

    /* ����SPIģʽ��ʱ����λ�ͼ��ԣ� */
    amhw_zlg237_spi_clk_mode_set(p_hw_spi, 0x3 & p_this->p_spi_slv_dev->mode);

    /* ����֡��ʽ���ȷ���MSB */
    amhw_zlg237_spi_lsbfirst_set(p_hw_spi, AMHW_ZLG237_SPI_LSB_FIRST_SEND_MSB);

    /* �������ݳ��� */
    amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_8BIT);

    /* ����Ϊ�ӻ�ģʽ */
    amhw_zlg237_spi_master_salver_set(p_hw_spi, AMHW_ZLG237_SPI_SLAVER);

    /* ʹ��Ϊ DMA ��ʽ */
    amhw_zlg237_spi_dma_tx_enable(p_hw_spi);
    amhw_zlg237_spi_dma_rx_enable(p_hw_spi);

    /* ʹ��SPI */
    amhw_zlg237_spi_enable(p_hw_spi);

    return AM_OK;
}

/**
 * \brief �ӻ�����
 */
static int __spi_slv_cfg (am_zlg237_spi_slv_dma_dev_t *p_this,
                          am_spi_slv_device_t         *p_slv_dev)
{
    amhw_zlg237_spi_t *p_hw_spi = (amhw_zlg237_spi_t *)
                                  (p_this->p_devinfo->spi_reg_base);


    amhw_zlg237_spi_disable(p_hw_spi);

    /* Ĭ������Ϊ 8 λ����󲻳��� 32 λ */
    if (p_slv_dev->bits_per_word == 0) {
        p_slv_dev->bits_per_word = 8;
    } else if (p_slv_dev->bits_per_word > 32) {
        return -AM_ENOTSUP;
    }

    /* ����SPI���ݳ��Ⱥ�֡��ʽ */
    if (p_slv_dev->bits_per_word == 8) {
        amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_8BIT);
    }
    else if (p_slv_dev->bits_per_word == 16) {
        amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_16BIT);
    }
    else if ((p_slv_dev->bits_per_word >= 1) ||
             (p_slv_dev->bits_per_word <= 32)) {
        amhw_zlg237_spi_flex_length_set(p_hw_spi,p_slv_dev->bits_per_word);
        amhw_zlg237_spi_flexlength_enable(p_hw_spi);
    }
    else {
         amhw_zlg237_spi_data_length_set(p_hw_spi, AMHW_ZLG237_SPI_DATA_8BIT);
    }

    /* ����SPIģʽ��ʱ����λ�ͼ��ԣ� */
    amhw_zlg237_spi_clk_mode_set(p_hw_spi, 0x3 & p_slv_dev->mode);

    /* ����֡��ʽ���ȷ���MSB */
    amhw_zlg237_spi_lsbfirst_set(p_hw_spi, AMHW_ZLG237_SPI_LSB_FIRST_SEND_MSB);

    return AM_OK;
}

/**
 * \brief Ƭѡ�ж�
 */
void __cs_irq_handle (void *p_arg)
{

    am_zlg237_spi_slv_dma_dev_t *p_this     = ( am_zlg237_spi_slv_dma_dev_t *)
                                              p_arg;
    amhw_zlg237_spi_t           *p_hw_spi   = (amhw_zlg237_spi_t *)
                                              (p_this->p_devinfo->spi_reg_base);
    am_spi_slv_device_t         *p_dev      = p_this->p_spi_slv_dev;
    uint8_t                      cs_status  = am_gpio_get(
                                                  p_this->p_devinfo->cs_pin);
    size_t                       count      = 0;
    static uint8_t               start_flag = 0;

    /* ���α��ش����󣬼�⵽��CS��ƽΪ�ߣ��ҿ�ʼ��־��Ч������£��Ž��д�������Ĳ���*/
    if( (cs_status == 1) && (start_flag == 1)) { /* ������� */

        start_flag = 0;

        count      = p_this->sum_nbytes -
                     am_zlg_dma_tran_data_get(p_this->p_devinfo->dma_chan_rx);


         amhw_zlg237_spi_disable(p_hw_spi);

        if(p_dev->p_slv_cb_funcs->pfn_cs_inactive) {
            p_dev->p_slv_cb_funcs->pfn_cs_inactive(p_dev->p_arg, count);
        }

        /* �ر� SPI��ͬʱ������ջ���������λ�Ĵ����е����� */

        /* �رշ��� DMA ����  */
        am_zlg_dma_chan_stop( p_this->p_devinfo->dma_chan_tx);

        /* �ر� SPI��ͬʱ������ջ���������λ�Ĵ����е����� */
        amhw_zlg237_spi_disable(p_hw_spi);

        amhw_zlg237_spi_enable(p_hw_spi);

        /* ģ��һ�� DMA ������ɣ�SPI �� 8 �ֽڵ� FIFO��û��ʱ����Ҳ���� DMA ���� */
        am_zlg_dma_xfer_desc_build(&(p_this->g_desc[0]),        /* ͨ�������� */
                                    (uint32_t)(&(p_this->dummy_txbuf)),
                                    (uint32_t)(&(p_hw_spi->dr)),/* Ŀ�Ļ������׵�ַ */
                                     1,                         /* �����ֽ��� */
                                     p_this->dummy_dma_flags);  /* �������� */

        if (am_zlg_dma_xfer_desc_chan_cfg(&(p_this->g_desc[0]),
                                          AMHW_ZLG_DMA_MER_TO_PER,  /* �ڴ浽���� */
                                          p_this->p_devinfo->dma_chan_tx) ==
                                          AM_OK) {
            am_zlg_dma_chan_start(p_this->p_devinfo->dma_chan_tx);
        }

        /* ������ֽ��� ���ر� SPI��Ƭѡ��Чʱ�����д��� */
        amhw_zlg237_spi_disable(p_hw_spi);

    } else { /* ���俪ʼ */

        start_flag = 1;

        if(p_dev->p_slv_cb_funcs->pfn_cs_active) {
            p_dev->p_slv_cb_funcs->pfn_cs_active(p_dev->p_arg);
        }

        p_this->sum_nbytes = 0;

        /* ���� DMA ֮ǰ����ر� DMA ͨ�� */
        am_zlg_dma_chan_stop(p_this->p_devinfo->dma_chan_tx);
        am_zlg_dma_chan_stop(p_this->p_devinfo->dma_chan_rx);

        /* ���� DMA ���� */
        __spi_slv_transfer_data(p_this);

        amhw_zlg237_spi_enable(p_hw_spi);
    }
}

/**
 * \brief ʹ�� CS �����ⲿ�ж�
 */
static int __cs_irq_cfg (am_zlg237_spi_slv_dma_dev_t *p_this)
{
    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    /* �����ն˻ص����� */
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
static int __cs_irq_cfg_deinit (am_zlg237_spi_slv_dma_dev_t *p_this)
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
    am_zlg237_spi_slv_dma_dev_t *p_this = (am_zlg237_spi_slv_dma_dev_t *)p_drv;

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
     am_zlg237_spi_slv_dma_dev_t *p_this;
    
    if ( (p_drv   == NULL) ||
         (p_dev   == NULL)) {
        return -AM_EINVAL;
    }

    p_this = (am_zlg237_spi_slv_dma_dev_t *)p_drv;

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
    am_zlg237_spi_slv_dma_dev_t *p_this = (am_zlg237_spi_slv_dma_dev_t *)p_arg;

    /* �жϷ��� */
    if (stat == AM_ZLG_DMA_INT_NORMAL)
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
static int __spi_slv_transfer_data (am_zlg237_spi_slv_dma_dev_t *p_dev)
{
    amhw_zlg237_spi_t      *p_hw_spi;
    am_spi_slv_device_t *p_slv_dev;
    
    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_spi = (amhw_zlg237_spi_t *)(p_dev->p_devinfo->spi_reg_base);

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

        am_zlg_dma_xfer_desc_build(&(p_dev->g_desc[0]),                  /* ͨ�������� */
                                    (uint32_t)(p_dev->tansfer.p_tx_buf), /* Դ�������׵�ַ */
                                    (uint32_t)(&(p_hw_spi->dr)),         /* Ŀ�Ļ������׵�ַ */
                                     p_dev->tansfer.nbytes ,             /* �����ֽ��� */
                                     p_dev->dma_flags);                  /* �������� */

    } else {

        am_zlg_dma_xfer_desc_build(&(p_dev->g_desc[0]),                  /* ͨ�������� */
                                    (uint32_t)(&(p_dev->dummy_txbuf)),   /* Դ�������׵�ַ */
                                    (uint32_t)(&(p_hw_spi->dr)),         /* Ŀ�Ļ������׵�ַ */
                                     p_dev->tansfer.nbytes,              /* �����ֽ��� */
                                     p_dev->dummy_dma_flags);            /* �������� */
    }

    /* ��������ͨ�������� */
    if ( p_dev->tansfer.p_rx_buf) {
        am_zlg_dma_xfer_desc_build(&(p_dev->g_desc[1]),                  /* ͨ�������� */
                                    (uint32_t)(&(p_hw_spi->dr)),         /* Դ�������׵�ַ */
                                    (uint32_t)(p_dev->tansfer.p_rx_buf), /* Ŀ�Ļ������׵�ַ */
                                     p_dev->tansfer.nbytes,              /* �����ֽ��� */
                                     p_dev->dma_flags);                  /* �������� */

    } else {
        am_zlg_dma_xfer_desc_build(&(p_dev->g_desc[1]),                  /* ͨ�������� */
                                    (uint32_t)(&(p_hw_spi->dr)),         /* Դ�������׵�ַ */
                                    (uint32_t)(&(p_dev->dummy_rxbuf)),   /* Ŀ�Ļ������׵�ַ */
                                     p_dev->tansfer.nbytes ,             /* �����ֽ��� */
                                     p_dev->dummy_dma_flags);            /* �������� */

    }

    if (am_zlg_dma_xfer_desc_chan_cfg(&(p_dev->g_desc[1]),
                                        AMHW_ZLG_DMA_PER_TO_MER,         /* ���赽�ڴ� */
                                        p_dev->p_devinfo->dma_chan_rx) == AM_ERROR) {
        return AM_ERROR;
    }

    if (am_zlg_dma_xfer_desc_chan_cfg(&(p_dev->g_desc[0]),
                                      AMHW_ZLG_DMA_MER_TO_PER,        /* �ڴ浽���� */
                                      p_dev->p_devinfo->dma_chan_tx) == AM_ERROR) {
        return AM_ERROR;
    }

    am_zlg_dma_chan_start(p_dev->p_devinfo->dma_chan_rx);
    am_zlg_dma_chan_start(p_dev->p_devinfo->dma_chan_tx);

    return AM_OK;
}

/******************************************************************************/

/**
 * \brief SPI ��ʼ��
 */
am_spi_slv_handle_t
am_zlg237_spi_slv_dma_init (am_zlg237_spi_slv_dma_dev_t           *p_dev,
                            const am_zlg237_spi_slv_dma_devinfo_t *p_devinfo)
{
    if (NULL == p_devinfo || NULL == p_dev ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->spi_slv_serve.p_funcs = (struct am_spi_slv_drv_funcs *)&__g_spi_slv_drv_funcs;
    p_dev->spi_slv_serve.p_drv   = p_dev;

    p_dev->p_devinfo             = p_devinfo;

    p_dev->p_spi_slv_dev         = NULL;

    p_dev->tansfer.nbytes        = 0;
    p_dev->tansfer.bits_per_word = 0;
    p_dev->tansfer.p_rx_buf      = NULL;
    p_dev->tansfer.p_tx_buf      = NULL;
    p_dev->sum_nbytes            = 0;

    p_dev->dummy_txbuf           = 0;

    p_dev->dma_flags       = AMHW_ZLG_DMA_CHAN_PRIORITY_HIGH       |  /* �ж����ȼ��� */
                             AMHW_ZLG_DMA_CHAN_MEM_SIZE_8BIT       |  /* �ڴ����ݿ�� 1 �ֽ� */
                             AMHW_ZLG_DMA_CHAN_PER_SIZE_8BIT       |  /* �������ݿ�� 1 �ֽ� */
                             AMHW_ZLG_DMA_CHAN_MEM_ADD_INC_ENABLE  |  /* �ڴ��ַ���� */
                             AMHW_ZLG_DMA_CHAN_PER_ADD_INC_DISABLE |  /* �����ַ������ */
                             AMHW_ZLG_DMA_CHAN_CIRCULAR_MODE_DISABLE; /* �ر�ѭ��ģʽ */


    p_dev->dummy_dma_flags = AMHW_ZLG_DMA_CHAN_PRIORITY_HIGH       |  /* �ж����ȼ��� */
                             AMHW_ZLG_DMA_CHAN_MEM_SIZE_8BIT       |  /* �ڴ����ݿ�� 1 �ֽ� */
                             AMHW_ZLG_DMA_CHAN_PER_SIZE_8BIT       |  /* �������ݿ�� 1 �ֽ� */
                             AMHW_ZLG_DMA_CHAN_MEM_ADD_INC_DISABLE |  /* �ڴ��ַ������ */
                             AMHW_ZLG_DMA_CHAN_PER_ADD_INC_DISABLE |  /* �����ַ������ */
                             AMHW_ZLG_DMA_CHAN_CIRCULAR_MODE_DISABLE; /* �ر�ѭ��ģʽ */
    /* ��ʼ��Ӳ�� */
    if (__spi_slv_hard_init(p_dev) != AM_OK) {
        return NULL;
    }

    /* ���� DMA �жϷ����� */
    am_zlg_dma_isr_connect(p_dev->p_devinfo->dma_chan_rx,
                           __spi_slv_dma_isr,
                           (void *)p_dev);

    return &(p_dev->spi_slv_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_zlg237_spi_slv_dma_deinit (am_spi_slv_handle_t handle)
{
    am_zlg237_spi_slv_dma_dev_t *p_dev    = (am_zlg237_spi_slv_dma_dev_t *)handle;
    amhw_zlg237_spi_t           *p_hw_spi = (amhw_zlg237_spi_t *)(p_dev->p_devinfo->spi_reg_base);

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_slv_serve.p_funcs = NULL;
    p_dev->spi_slv_serve.p_drv   = NULL;

    /* ���� SPI */
    amhw_zlg237_spi_disable(p_hw_spi);

    am_zlg_dma_isr_disconnect(p_dev->p_devinfo->dma_chan_rx,
                              __spi_slv_dma_isr,
                              (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */

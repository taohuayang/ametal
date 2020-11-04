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
 * \brief SPI����������SPI��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-23  cds, first implementation
 * \endinternal
 */

#ifndef __AM_HC32F460_SPI_POLL_H
#define __AM_HC32F460_SPI_POLL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_spi.h"
#include "am_int.h"

#include "hw/amhw_hc32f460_spi.h"

/**
 * \addtogroup am_hc32f460_if_spi_poll
 * \copydoc am_hc32f460_spi_poll.h
 * @{
 */

/**
 * \name SPI����ģʽ
 * @{
 */

/** @} */


typedef struct amhw_hc32f460_spi_ss_pin {
   uint32_t    pin_ss0;
   uint32_t    pin_ss1;
   uint32_t    pin_ss2;
   uint32_t    pin_ss3;
} amhw_hc32f460_spi_ss_pin_t;

/**
 * \brief SPI�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f460_spi_poll_devinfo {
    uint32_t  spi_reg_base;   /**< \brief SPI�Ĵ�����Ļ���ַ */
    int       clk_id;         /**< \brief ʱ��ID */

    /** \brief SPIƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void    (*pfn_plfm_init)(void);

    /** \brief SPIƽ̨���ʼ������ */
    void    (*pfn_plfm_deinit)(void);

} am_hc32f460_spi_poll_devinfo_t;

/**
 * \brief SPI�豸
 */
typedef struct am_hc32f460_spi_poll_dev {

    am_spi_serv_t                   spi_serve;       /**< \brief SPI��׼������ */
    const am_hc32f460_spi_poll_devinfo_t *p_devinfo; /**< \brief SPI�豸��Ϣ��ָ�� */

    /** \brief ָ��SPI��Ϣ�ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ����Ϣ */
    am_spi_message_t          *p_cur_msg;

    /** \brief ָ��SPI����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_spi_transfer_t         *p_cur_trans;

    am_spi_device_t           *p_cur_spi_dev;     /**< \brief ��ǰ�����SPI�豸 */
    am_spi_device_t           *p_tgl_dev;         /**< \brief ��ǰ������SPI�豸 */

    uint32_t                   nbytes_to_recv;    /**< \brief �����յ��ֽ��� */
    uint32_t                   data_ptr;          /**< \brief ���ݴ������ */

    am_bool_t                  lsbfirst;          /**< \brief ��λ�ȷ��ͱ�־ */
    am_bool_t                  busy;              /**< \brief SPIæ��ʶ */
    uint32_t                   state;             /**< \brief SPI������״̬��״̬ */

    uint8_t                    bef_bits_per_word; /**< \brief SPI�ϴδ����ֵ��ֽ���*/
    uint32_t                   bef_speed_hz;      /**< \brief SPI�ϴδ�����ٶ�*/
} am_hc32f460_spi_poll_dev_t;

/**
 * \brief SPI��ʼ��
 *
 * \param[in] p_dev     : ָ��SPI�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SPI�豸��Ϣ�ṹ���ָ��
 *
 * \return SPI��׼����������
 */
am_spi_handle_t am_hc32f460_spi_poll_init (am_hc32f460_spi_poll_dev_t               *p_dev,
                                           const am_hc32f460_spi_poll_devinfo_t *p_devinfo);

/**
 * \brief ���SPI��ʼ��
 *
 * \param[in] handle : SPI��׼����������
 *
 * \return ��
 */
void am_hc32f460_spi_poll_deinit (am_spi_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_SPI_POLL_H */

/* end of file */

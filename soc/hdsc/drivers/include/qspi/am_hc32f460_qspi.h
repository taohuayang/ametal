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
 * \brief QSPI����������QSPI��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-05-28
 * \endinternal
 */

#ifndef __AM_HC32F460_QSPI_H
#define __AM_HC32F460_QSPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hw/amhw_hc32f460_qspi.h"

/**
 * \brief hc32f460 qspi �豸��Ϣ
 */
typedef struct am_hc32f460_qspi_devinfo {

    /** \brief �Ĵ�������ַ */
    uint32_t          regbase;

    /** \brief ����ʱ��ID */
    uint32_t          clk_id;

    /** \brief �жϺ� */
    int               inum;

    uint8_t           clk_div;       /**< \brief ��׼ʱ������ */
    uint8_t           protocol_data; /**< \brief ���ݽ��ս׶�SPIЭ�� */
    uint8_t           protocol_addr; /**< \brief ��ַ���ͽ׶�SPIЭ�� */
    uint8_t           protocol_cmd;  /**< \brief ָ��ͽ׶�SPIЭ�� */
    uint8_t           spi_mode;      /**< \brief spiģʽ */
    uint8_t           read_mode;     /**< \brief ��ȡģʽ */

    /** \brief ƽ̨��ʼ������ */
    void (*pfn_plfm_init) (void);
    /** \brief ƽ̨���ʼ������ */
    void (*pfn_plfm_deinit) (void);
} am_hc32f460_qspi_devinfo_t;

/**
 *
 * \brief hc32f460 spifi �豸ʵ��
 */
typedef struct am_hc32f460_qspi_dev {

    /**< \brief ָ���豸��Ϣ������ָ�� */
    const am_hc32f460_qspi_devinfo_t *p_devinfo;
}am_hc32f460_qspi_dev_t;

/** \brief qspi��׼�������������Ͷ��� */
typedef am_hc32f460_qspi_dev_t *am_qspi_handle_t;


/**
 * \brief QSPI ������
 *
 * \param[in] : p_dev  ָ��QSPI�豸��ָ��
 * \param[in] : addr   ��ȡ�ĵ�ַ
 * \param[in] : p_buf  ���ڴ�Ŷ�ȡ�������ݵ�buffer
 * \param[in] : nbytes ��ȡ�ĳ���
 *
 * \retval : AM_OK     ��ȡ�ɹ�
 *           AM_EINVAL ������Ч
 */
int am_hc32f460_qspi_read (am_hc32f460_qspi_dev_t *p_dev,
                           uint32_t                addr,
                           uint8_t                *p_buf,
                           uint32_t                nbytes);


/**
 * \brief QSPI ����ֱ��ͨ��ģʽ
 *
 * \param[in] : p_dev  ָ��QSPI�豸��ָ��
 *
 * \retval : AM_OK     �����ɹ�
 *           AM_EINVAL ������Ч
 */
int am_hc32f460_qspi_enter_directcom (am_hc32f460_qspi_dev_t *p_dev);


/**
 * \brief QSPI �˳�ֱ��ͨ��ģʽ
 *
 * \param[in] : p_dev  ָ��QSPI�豸��ָ��
 *
 * \retval : AM_OK     �����ɹ�
 *           AM_EINVAL ������Ч
 */
int am_hc32f460_qspi_exit_directcom (am_hc32f460_qspi_dev_t *p_dev);


/**
 * \brief QSPI ֱ��ͨ��ģʽ��ȡ����
 *
 * \param[in] : p_dev  ָ��QSPI�豸��ָ��
 *
 * \retval :    ��ȡ��������
 */
uint8_t am_hc32f460_qspi_directcom_read (am_hc32f460_qspi_dev_t *p_dev);


/**
 * \brief QSPI ֱ��ͨ��ģʽд����
 *
 * \param[in] : p_dev  ָ��QSPI�豸��ָ��
 * \param[in] : data   Ҫд�������
 *
 * \retval : AM_OK     �����ɹ�
 *           AM_EINVAL ������Ч
 */
int am_hc32f460_qspi_directcom_write (am_hc32f460_qspi_dev_t *p_dev,
                                      uint8_t                 data);


/**
 * \brief QSPI �豸��ʼ��
 *
 * \param[in] : p_dev     ָ��QSPI�豸��ָ��
 * \param[in] : p_devinfo �豸��Ϣ��ʼ��ʵ��
 *
 * \retval : qspi��׼����������
 */
am_qspi_handle_t am_hc32f460_qspi_init (am_hc32f460_qspi_dev_t            *p_dev,
                                        const am_hc32f460_qspi_devinfo_t  *p_devinfo);

/**
 * \brief QSPI �豸���ʼ��
 *
 * \param[in] : p_dev     qspi��׼����������
 *
 * \retval : ��
 */
void am_hc32f460_qspi_deinit (am_qspi_handle_t p_dev);



/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32F460_QSPI_H */

/* end of file */

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
 * \brief ֧���豸������ָ��ı�׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-11-27  win, first implementation.
 * \endinternal
 */
#ifndef __AM_READER_CARD_H
#define __AM_READER_CARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \name ����оƬ֧�ֵ�ISOЭ������
 * @{
 */

/** \brief ISO14443 Type A */
#define AM_READER_CARD_ISO14443A          0x00

/** \brief ISO14443 Type B */
#define AM_READER_CARD_ISO14443B          0x01

/** \brief ISO15693 ����ģʽ */
#define AM_READER_CARD_ISO15693_FAST      0x02

/** \brief ISO15693 ��׼ģʽ */
#define AM_READER_CARD_ISO15693_STANDARD  0x03

/** @} */

/**
 * \name ���ߵ�����ģʽ (TX1,TX2������ʽ)
 * @{
 */

/** \brief ͬʱ�ر�TX1��TX2 */
#define AM_READER_CARD_ALL_OFF            0x00

/** \brief ��TX1�������� */
#define AM_READER_CARD_TX1_ON             0x01

/** \brief ��TX2�������� */
#define AM_READER_CARD_TX2_ON             0x02

/** \brief TX1��TX2ͬʱ�������� */
#define AM_READER_CARD_ALL_ON             0x03

/** @} */

/**
 * \brief ����оƬ���������ṹ��
 */
struct am_reader_card_drv_funcs {

    /** \brief �ر�оƬ */
    int (*pfn_cd_close) (void *p_drv);

    /** \brief ��λоƬ */
    int (*pfn_cd_reset) (void *p_drv);

    /** \brief ����оƬ */
    int (*pfn_cd_config) (void *p_drv);

    /** \brief ����оƬISOЭ������ */
    int (*pfn_cd_iso_type_set) (void *p_drv, uint8_t type);
	
	  /** \brief ����Txͨ����*/
    int (*pfn_cd_channal_set) (void *p_drv, uint8_t channal_num);

    /** \brief ����оƬ�Ĵ�����ֵ */
    int (*pfn_cd_reg_write) (void     *p_drv,
                             uint32_t  reg_addr,
                             void     *p_tx_buf,
                             uint32_t  nbytes);

    /** \brief ��ȡоƬ�Ĵ�����ֵ */
    int (*pfn_cd_reg_read) (void     *p_drv,
                            uint32_t  reg_addr,
                            uint32_t *p_rx_buf,
                            uint32_t  nbytes);

    /** \brief �������ߵ�����ģʽ */
    int (*pfn_cd_antenna_mode_set) (void *p_drv, uint32_t mode);

    /** \brief ��ȡ���ߵ�����ģʽ */
    int (*pfn_cd_antenna_mode_get) (void *p_drv, uint32_t *p_mode);

    /** \brief ���ݽ��� */
    int (*pfn_cd_block_exchange) (void     *p_drv,
                                  uint8_t  *p_tx_buf,
                                  uint32_t  tx_nbytes,
                                  uint8_t  *p_rx_buf,
                                  uint32_t  rx_buf_size,
                                  uint32_t *p_rx_nbytes,
                                  uint8_t   nwtxm_crc,
                                  uint8_t   nfwi);

    /** \brief �ز���ͣ */
    int (*pfn_cd_wave_pause) (void     *p_drv,
                              uint32_t  pause_ms,
                              uint32_t  wait_ms);

    /** \brief ��ȡ���֤ID */
    int (*pfn_cd_sid_get) (void     *p_drv,
                           uint8_t  *p_uid,
                           uint32_t *p_rx_nbytes);

    /** \brief ��ȡ��λ���� */
    int (*pfn_cd_reset_count_get) (void *p_drv, uint32_t *p_count);

};

/**
 * \brief ����оƬ����ṹ��
 */
typedef struct am_reader_card_serv {

    /** \brief ����оƬ���������ṹ��ָ�� */
    struct am_reader_card_drv_funcs *p_funcs;

    /** \brief �������������ĵ�һ������ */
    void                            *p_drv;

} am_reader_card_serv_t;

/** \brief �������оƬ������ */
typedef am_reader_card_serv_t *am_reader_card_handle_t;

/**
 * \brief �رն���оƬ
 *
 * \param[in] handle : ����оƬ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_close (am_reader_card_handle_t handle)
{
    return handle->p_funcs->pfn_cd_close(handle->p_drv);
}

/**
 * \brief ��λоƬ
 *
 * \param[in] handle : ����оƬ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_reset (am_reader_card_handle_t handle)
{
    return handle->p_funcs->pfn_cd_reset(handle->p_drv);
}

/**
 * \brief ����оƬ
 *
 * \param[in] handle : ����оƬ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_config (am_reader_card_handle_t handle)
{
    return handle->p_funcs->pfn_cd_config(handle->p_drv);
}

/**
 * \brief ����оƬISOЭ������
 *
 * \param[in] handle : ����оƬ������
 * \param[in] type   : ISOЭ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_iso_type_set (am_reader_card_handle_t handle,
                                 uint8_t                 type)
{
    return handle->p_funcs->pfn_cd_iso_type_set(handle->p_drv,
                                                type);
}

/**
 * \brief ����оƬTxͨ����
 *
 * \param[in] handle : ����оƬ������
 * \param[in] type   : ͨ����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_tx_channal_set (am_reader_card_handle_t handle,
                                   uint8_t                 num)
{
    return handle->p_funcs->pfn_cd_channal_set(handle->p_drv, num);
}

/**
 * \brief ����оƬ�Ĵ�����ֵ
 * \note  �Ĵ�����ַ�Զ�����
 *
 * \param[in] handle   : ����оƬ������
 * \param[in] reg_addr : оƬ�ڲ��Ĵ����ĵ�ַ
 * \param[in] p_tx_buf : ���õ�ֵ����Ż�����
 * \param[in] nbytes   : ���͵��ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_reg_write (am_reader_card_handle_t  handle,
                              uint32_t                 reg_addr,
                              void                    *p_tx_buf,
                              uint32_t                 nbytes)
{
    return handle->p_funcs->pfn_cd_reg_write(handle->p_drv,
                                            reg_addr,
                                            p_tx_buf,
                                            nbytes);
}

/**
 * \brief ��ȡоƬ�Ĵ�����ֵ
 * \note  �Ĵ�����ַ�Զ�����
 *
 * \param[in] handle   : ����оƬ������
 * \param[in] reg_addr : оƬ�ڲ��Ĵ����ĵ�ַ
 * \param[in] p_tx_buf : ��ȡ��ֵ����ŵĻ�����
 * \param[in] nbytes   : ���յ��ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_reg_read (am_reader_card_handle_t  handle,
                             uint32_t                 reg_addr,
                             void                    *p_rx_buf,
                             uint32_t                 nbytes)
{
    return handle->p_funcs->pfn_cd_reg_read(handle->p_drv,
                                            reg_addr,
                                            p_rx_buf,
                                            nbytes);
}

/**
 * \brief �������ߵ�����ģʽ
 *
 * \param[in] handle : ����оƬ������
 * \param[in] mode   : ����ģʽ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_antenna_mode_set (am_reader_card_handle_t  handle,
                                     uint32_t                 mode)
{
    return handle->p_funcs->pfn_cd_antenna_mode_set(handle->p_drv, mode);
}

/**
 * \brief ��ȡ���ߵ�����ģʽ
 *
 * \param[in] handle : ����оƬ������
 * \param[in] p_mode : ����ģʽ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_antenna_mode_get (am_reader_card_handle_t   handle,
                                     uint32_t                 *p_mode)
{
    return handle->p_funcs->pfn_cd_antenna_mode_get(handle->p_drv, p_mode);
}

/**
 * \brief ���ݽ���
 *
 * \param[in] handle      : ����оƬ������
 * \param[in] p_tx_buf    : �����͵�����
 * \param[in] tx_nbytes   : �������ݵĳ���
 * \param[in] p_rx_buf    : �����յ�����
 * \param[in] rx_buf_size : ���ջ�������С
 * \param[in] p_rx_nbytes : �����յ������ֽ�
 * \param[in] nwtxm_crc   : crcУ�����
 * \param[in] nfwi        : ��ʱ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_block_exchange (am_reader_card_handle_t  handle,
                                   uint8_t                 *p_tx_buf,
                                   uint32_t                 tx_nbytes,
                                   uint8_t                 *p_rx_buf,
                                   uint32_t                 rx_buf_size,
                                   uint32_t                *p_rx_nbytes,
                                   uint8_t                  nwtxm_crc,
                                   uint8_t                  nfwi)
{
    return handle->p_funcs->pfn_cd_block_exchange(handle->p_drv,
                                                  p_tx_buf,
                                                  tx_nbytes,
                                                  p_rx_buf,
                                                  rx_buf_size,
                                                  p_rx_nbytes,
                                                  nwtxm_crc,
                                                  nfwi);
}

/**
 * \brief �ز���ͣ
 *
 * \param[in] handle   : ����оƬ������
 * \param[in] pause_ms : ��ͣʱ�䣬�ر�RF����ʱ������´򿪣���Ϊ0�����´�
 * \param[in] wait_ms  : RF�����´򿪺�����ȴ���ʱ�䣬��Ϊ0�򲻵ȴ�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_wave_pause (am_reader_card_handle_t handle,
                               uint32_t                pause_ms,
                               uint32_t                wait_ms)
{
    return handle->p_funcs->pfn_cd_wave_pause(handle->p_drv,
                                              pause_ms,
                                              wait_ms);
}

/**
 * \brief ��ȡ���֤ID
 *
 * \param[in] handle      : ����оƬ������
 * \param[in] p_uid       : ���ص����֤ID
 * \param[in] p_rx_nbytes : ���֤ID���ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_sid_get (am_reader_card_handle_t  handle,
                            uint8_t                 *p_uid,
                            uint32_t                *p_rx_nbytes)
{
    return handle->p_funcs->pfn_cd_sid_get(handle->p_drv,
                                           p_uid,
                                           p_rx_nbytes);
}

/**
 * \brief ��ȡ����оƬ��λ����
 *
 * \param[in]  handle  : ����оƬ������
 * \param[out] p_count : ���ظ�λ����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_reader_card_reset_count_get (am_reader_card_handle_t  handle,
                                    uint32_t                *p_count)
{
    return handle->p_funcs->pfn_cd_reset_count_get(handle->p_drv, p_count);
}

#ifdef __cplusplus
}
#endif

#endif /* __AM_READER_CARD_H */

/* end of file */

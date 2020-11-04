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
 * \brief 
 *
 * \internal
 * \par Modification History
 * - 1.00 15-09-  win, first implementation.
 * \endinternal
 */
#ifndef __AM_IC_MIFARE_H
#define __AM_IC_MIFARE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_uartcmd_ic_iso14443.h"

/**
 * \name Mifare����Կ����
 * @{
 */

#define AM_IC_MIFARE_KEY_TYPE_MASK    0x7F    /**< \brief ��Կ�������� */
#define AM_IC_MIFARE_KEY_TYPE_A       0x60    /**< \brief ��ԿA��֤ */
#define AM_IC_MIFARE_KEY_TYPE_B       0x61    /**< \brief ��ԿB��֤ */

#define AM_IC_MIFARE_KEY_SRC_MASK     0x80    /**< \brief ��Կ����Դ���� */
#define AM_IC_MIFARE_KEY_SRC_EXT      0x00    /**< \brief ʹ���ⲿ�������Կ��֤ */
#define AM_IC_MIFARE_KEY_SRC_E2       0x80    /**< \brief ʹ���ڲ�E2����Կ��֤ */

/** @} */

/**
 * \brief Mifare �������
 * @{
 */
#define AM_IC_MIFARE1_CMD_READ            0x30    /**< \brief ������(16�ֽ�) */
#define AM_IC_MIFARE1_CMD_WRITE           0xA0    /**< \brief д����(16�ֽ�) */
#define AM_IC_MIFARE1_CMD_TRANSFER        0xB0    /**< \brief �������� */
#define AM_IC_MIFARE1_CMD_NO_COMMAND      0x00    /**< \brief ������ */
#define AM_IC_MIFARE1_CMD_INCREMENT       0xC1    /**< \brief ֵ������ */
#define AM_IC_MIFARE1_CMD_DECREMENT       0xC0    /**< \brief ֵ������ */
#define AM_IC_MIFARE1_CMD_RESTORE         0xC2    /**< \brief �������� */
#define AM_IC_MIFARE0_CMD_WRITE           0xA2    /**< \brief UltraLight д����(4�ֽ�) */
#define AM_IC_MIFARE0_CMD_AUTH            0xA3    /**< \brief UltraLight ��֤���� */

/** @} */

/**
 * \brief Mifare����׼������������
 */
struct am_ic_mifare_drv_funcs {

    /** \brief ��Կ��֤ */
    int (*pfn_ic_key_auth) (void       *p_drv,
                            uint8_t     mode,
                            const void *p_key,
                            uint32_t    key_nbytes,
                            const void *p_uid,
                            uint32_t    uid_nbytes,
                            uint8_t     block);

    /** \brief Mifare����չ���� */
    int (*pfn_ic_activate) (void                 *p_drv,
                            uint8_t               mode,
                            uint8_t               req_code,
                            am_ic_a_reset_info_t *p_reset_info);

    /** \brief Mifare����ȡ��������� */
    int (*pfn_ic_blocks_read) (void    *p_drv,
                               uint8_t  start_block,
                               uint8_t  block_num,
                               void    *p_buf);

    /** \brief Mifare��д����� */
    int (*pfn_ic_blocks_write) (void       *p_drv,
                                uint8_t     start_block,
                                uint8_t     block_num,
                                const void *p_buf);

    /** \brief Mifare����ȡֵ������ */
    int (*pfn_ic_value_block_get) (void    *p_drv,
                                   uint8_t  block,
                                   int32_t *p_value);

    /** \brief Mifare������ֵ���ֵ */
    int (*pfn_ic_value_block_set) (void    *p_drv,
                                   uint8_t  block,
                                   int32_t  value);

    /** \brief Mifare��ֵ����� */
    int (*pfn_ic_value_operation) (void    *p_drv,
                                   uint8_t  mode,
                                   uint8_t  src_block,
                                   int32_t  value,
                                   uint8_t  dst_block);

    /** \brief Mifare UltraLight����ȡ��������� */
    int (*pfn_ic_ultralight_blocks_read) (void    *p_drv,
                                          uint8_t  start_block,
                                          uint8_t  block_num,
                                          void    *p_buf);

    /** \brief Mifare UltraLight�����ö���� */
    int (*pfn_ic_ultralight_blocks_write) (void       *p_drv,
                                           uint8_t     start_block,
                                           uint8_t     block_num,
                                           const void *p_buf);

    /** \brief Mifare UltraLight������ */
    int (*pfn_ic_ultralight_transfer) (void       *p_drv,
                                       const void *p_txbuf,
                                       void       *p_rxbuf,
                                       uint32_t   *p_rx_nbytes);
};

/**
 * \brief Mifare��׼����ṹ��
 */
typedef struct am_ic_mifare_serv {

    /** Mifare����׼�������������ṹ��ָ�� */
    struct am_ic_mifare_drv_funcs *p_funcs;

    /* \brief �������������ĵ�һ������ */
    void                          *p_drv;
} am_ic_mifare_serv_t;

/** \brief Mifare����׼������ */
typedef am_ic_mifare_serv_t *am_ic_mifare_handle_t;

/**
 * \brief Mifare����Կ��֤
 *
 * \param[in] handle     : Mifare����׼������
 * \param[in] mode       : ��֤ģʽ
 *                         - mode.7         -- ��Կ��Դ
 *                           - AM_IC_MIFARE_KEY_SRC_EXT ʹ���ⲿ�������Կ
 *                           - AM_IC_MIFARE_KEY_SRC_E2  ʹ���ڲ�E2����Կ
 *                         - mode.6-0       -- ��Կ����
 *                           - AM_IC_MIFARE_KEY_TYPE_A  ��ԿA
 *                           - AM_IC_MIFARE_KEY_TYPE_B  ��ԿB
 * \param[in] p_key      : ��Կ
 * \param[in] key_nbytes : ��Կ����
 * \param[in] p_uid      : UID
 * \param[in] uid_nbytes : UID����
 * \param[in] block      : ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_key_auth (am_ic_mifare_handle_t  handle,
                           uint8_t                mode,
                           const void            *p_key,
                           uint32_t               key_nbytes,
                           const void            *p_uid,
                           uint32_t               uid_nbytes,
                           uint8_t                block)
{
    return handle->p_funcs->pfn_ic_key_auth(handle->p_drv,
                                            mode,
                                            p_key,
                                            key_nbytes,
                                            p_uid,
                                            uid_nbytes,
                                            block);
}

/**
 * \brief Mifare������
 *
 * \param[in] handle       : Mifare����׼������
 * \param[in] mode         : ����ײģʽ
 *                           - 0  ִ�з���ײѭ����
 *                           - 1  ִֻ��һ�η���ײ
 * \param[in] req_code     : �������
 *                           - AM_IC_ISO14443_3A_REQIDL ������п�
 *                           - AM_IC_ISO14443_3A_REQALL �������п�
 * \param[in] p_reset_info : ISO14443-3A�������Ӧ��Ϣ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_activate (am_ic_mifare_handle_t  handle,
                           uint8_t                mode,
                           uint8_t                req_code,
                           am_ic_a_reset_info_t  *p_reset_info)
{
    return handle->p_funcs->pfn_ic_activate(handle->p_drv,
                                            mode,
                                            req_code,
                                            p_reset_info);
}

/**
 * \brief Mifare����ȡ���������
 *
 * \param[in] handle       : Mifare����׼������
 * \param[in] start_block  : ������ʼ���
 * \param[in] block_num    : ���Ŀ��������п������ͬһ������
 * \param[in] p_buf        : ������16 * block_num �ֽ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_blocks_read (am_ic_mifare_handle_t  handle,
                              uint8_t                start_block,
                              uint8_t                block_num,
                              void                  *p_buf)
{
    return handle->p_funcs->pfn_ic_blocks_read(handle->p_drv,
                                               start_block,
                                               block_num,
                                               p_buf);

}

/**
 * \brief Mifare��д�����
 *
 * \param[in] handle       : Mifare����׼������
 * \param[in] start_block  : д����ʼ���
 * \param[in] block_num    : д�Ŀ��������п������ͬһ������
 * \param[in] p_buf        : д���16 * block_num �ֽ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_blocks_write (am_ic_mifare_handle_t  handle,
                               uint8_t                start_block,
                               uint8_t                block_num,
                               const void            *p_buf)
{
    return handle->p_funcs->pfn_ic_blocks_write(handle->p_drv,
                                                start_block,
                                                block_num,
                                                p_buf);
}

/**
 * \brief Mifare����ȡֵ������
 *
 * \param[in] handle  : Mifare����׼������
 * \param[in] block   : ���
 * \param[in] p_value : ֵ(�з�����)
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_value_block_get (am_ic_mifare_handle_t  handle,
                                  uint8_t                block,
                                  int32_t               *p_value)
{
    return handle->p_funcs->pfn_ic_value_block_get(handle->p_drv,
                                                   block,
                                                   p_value);
}

/**
 * \brief Mifare������ֵ���ֵ
 *
 * \param[in] handle : Mifare����׼������
 * \param[in] block  : ���
 * \param[in] value  : ֵ(�з�����)
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_value_block_set (am_ic_mifare_handle_t handle,
                                  uint8_t               block,
                                  int32_t               value)
{
    return handle->p_funcs->pfn_ic_value_block_set(handle->p_drv,
                                                   block,
                                                   value);
}

/**
 * \brief Mifare��ֵ�����
 *
 * \param[in] handle    : Mifare����׼������
 * \param[in] mode      : ֵ����ģʽ
 *                        - AM_IC_MIFARE1_CMD_INCREMENT ��Դ���ֵ����ָ����ֵ��ŵ�Ŀ�Ŀ�
 *                        - AM_IC_MIFARE1_CMD_DECREMENT ��Դ���ֵ��ȥָ����ֵ��ŵ�Ŀ�Ŀ�
 *                        - AM_IC_MIFARE1_CMD_RESTORE   ��Դ���ֵ���Ƶ�Ŀ�Ŀ�
 * \param[in] src_block : Դ��
 * \param[in] value     : ֵ(���λ��Ч, ��û�з���λ)
 * \param[in] dst_block : Ŀ�Ŀ�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_value_operation (am_ic_mifare_handle_t handle,
                                  uint8_t               mode,
                                  uint8_t               src_block,
                                  int32_t               value,
                                  uint8_t               dst_block)
{
    return handle->p_funcs->pfn_ic_value_operation(handle->p_drv,
                                                   mode,
                                                   src_block,
                                                   value,
                                                   dst_block);
}

/**
 * \brief Mifare UltraLight����ȡ���������
 *
 * \param[in] handle      : Mifare����׼������
 * \param[in] start_block : ������ʼ���
 * \param[in] block_num   : ���Ŀ���
 * \param[in] p_buf       : ������4 * block_num�ֽ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_ultralight_blocks_read (am_ic_mifare_handle_t   handle,
                                         uint8_t                 start_block,
                                         uint8_t                 block_num,
                                         void                   *p_buf)
{
    return handle->p_funcs->pfn_ic_ultralight_blocks_read(handle->p_drv,
                                                          start_block,
                                                          block_num,
                                                          p_buf);
}

/**
 * \brief Mifare UltraLight�����ö����
 *
 * \param[in] handle      : Mifare����׼������
 * \param[in] start_block : д����ʼ���
 * \param[in] block_num   : д�Ŀ���
 * \param[in] p_buf       : д���4 * block_num�ֽ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_ultralight_blocks_write (am_ic_mifare_handle_t   handle,
                                          uint8_t                 start_block,
                                          uint8_t                 block_num,
                                          const void             *p_buf)
{
    return handle->p_funcs->pfn_ic_ultralight_blocks_write(handle->p_drv,
                                                           start_block,
                                                           block_num,
                                                           p_buf);
}

/**
 * \brief Mifare UltraLight������
 *
 * \param[in] handle      : Mifare����׼������
 * \param[in] p_txbuf     : ���ͻ����������Ҫ���͸���Ƭ������
 * \param[in] p_rxbuf     : ���ջ���������Ŵӿ�Ƭ��ȡ����������
 * \param[in] p_rx_nbytes : ���ܵ����ݳ��ȣ��ֽڣ�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_mifare_ultralight_transfer (am_ic_mifare_handle_t   handle,
                                      const void             *p_txbuf,
                                      void                   *p_rxbuf,
                                      uint32_t               *p_rx_nbytes)
{
    return handle->p_funcs->pfn_ic_ultralight_transfer(handle->p_drv,
                                                       p_txbuf,
                                                       p_rxbuf,
                                                       p_rx_nbytes);
}

#ifdef __cplusplus
}
#endif

#endif /* __AM_IC_MIFARE_H */

/* end of file */

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
 * \brief CPU PLUS����׼����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-01-05  win, first implementation.
 * \endinternal
 */
#ifndef __AM_IC_CPU_PLUS_H
#define __AM_IC_CPU_PLUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \name SL3����ģʽ
 * @{
 */

/** \brief ����ģʽ0; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_READ_MODE0           0x30

/** \brief ����ģʽ1; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_READ_MODE1           0x31

/** \brief ����ģʽ2; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_READ_MODE2           0x32

/** \brief ����ģʽ3; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_READ_MODE3           0x33

/** \brief ����ģʽ4; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_READ_MODE4           0x34

/** \brief ����ģʽ5; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_READ_MODE5           0x35

/** \brief ����ģʽ6; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_READ_MODE6           0x36

/** \brief ����ģʽ7; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_READ_MODE7           0x37

/** @} */

/**
 * \name SL3д��ģʽ
 * @{
 */

/** \brief д��ģʽ0; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_WRITE_MODE0          0xA0

/** \brief д��ģʽ1; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_WRITE_MODE1          0xA1

/** \brief д��ģʽ2; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_WRITE_MODE2          0xA2

/** \brief д��ģʽ3; ������MAC; ��������; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_WRITE_MODE3          0xA3

/** @} */

/**
 * \name SL3����ģʽ������/��������
 * @{
 */

/** \brief ��ֵ����ģʽ0; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_INC_TRAN_MODE0       0xB6

/** \brief ��ֵ����ģʽ1; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_INC_TRAN_MODE1       0xB7

/** \brief ��ֵ����ģʽ0; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_DEC_TRAN_MODE0       0xB8

/** \brief ��ֵ����ģʽ1; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_DEC_TRAN_MODE1       0xB9

/** @} */

/**
 * \name SL3��λģʽ
 * @{
 */

/** \brief �ָ�ģʽ0; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_RESTORE_MODE0        0xC2

/** \brief �ָ�ģʽ1; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_RESTORE_MODE1        0xC3

/** @} */

/**
 * \name SL3����ģʽ��������/��������
 * @{
 */

/** \brief ����ģʽ0; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_TRANSFER_MODE0        0xB4

/** \brief ����ģʽ1; ��Ӧ��MAC */
#define AM_IC_CPU_PLUS_SL3_TRANSFER_MODE1        0xB5

/** @} */

/**
 * \brief CPU PLUS����׼������������
 */
struct am_ic_cpu_plus_drv_funcs {

    /** \brief ��Ƭ���˻�ʱд�����ݻ�����Կ(SL0ר������) */
    int (*pfn_ic_personal_data_write) (void     *p_drv,
                                       uint32_t  addr,
                                       uint8_t  *p_buf);

    /** \brief �ύ���˻�(ԾǨ��SL1,SL0ר������) */
    int (*pfn_ic_personal_commit) (void *p_drv);

    /** \brief �״���֤��Կ */
    int (*pfn_ic_first_key_auth) (void          *p_drv,
                                  uint32_t       key_addr,
                                  const uint8_t *p_key,
                                  uint32_t       nbytes);

    /** \brief ������֤��Կ */
    int (*pfn_ic_follow_key_auth) (void     *p_drv,
                                   uint32_t  key_addr,
                                   uint8_t  *p_key,
                                   uint32_t  nbytes);

    /** \brief ��λ��֤ */
    int (*pfn_ic_reset_auth) (void *p_drv);

    /** \brief SL3���������� */
    int (*pfn_ic_data_read) (void     *p_drv,
                             uint8_t   mode,
                             uint8_t  *p_buf,
                             uint32_t  block_addr,
                             uint8_t   block_num);

    /** \brief SL3д�������� */
    int (*pfn_ic_data_write) (void          *p_drv,
                              uint8_t        mode,
                              const uint8_t *p_buf,
                              uint32_t       block_addr,
                              uint8_t        block_num);

    /** \brief ֵ��д����(SL3) */
    int (*pfn_ic_value_block_write) (void    *p_drv,
                                     uint8_t  mode,
                                     uint32_t addr,
                                     int32_t  value);

    /** \brief ��ȡֵ������ݣ�SL3��*/
    int (*pfn_ic_value_block_read) (void     *p_drv,
                                    uint8_t   mode,
                                    uint32_t  addr,
                                    int32_t  *p_value);

    /** \brief ֵ�����(��/�����Դ�����ģʽ��SL3) */
    int (*pfn_ic_value_operation) (void     *p_drv,
                                   uint8_t   mode,
                                   uint32_t  src_addr,
                                   uint32_t  dst_addr,
                                   int32_t   value);

    /** \brief ֵ��ָ�����ָ����ַ��ֵ���Ƶ��������� */
    int (*pfn_ic_restore) (void     *p_drv,
                           uint8_t   mode,
                           uint32_t  src_addr);

    /** \brief ֵ�鴫�䣬��ֵ��������(������)���䵽ָ���Ŀ� */
    int (*pfn_ic_transfer) (void     *p_drv,
                            uint8_t   mode,
                            uint32_t  dst_addr);
};

/**
 * \brief CPU PLUS����׼����ṹ��
 */
typedef struct am_ic_cpu_plus_serv {

    /** CPU PLUS����׼�������������ṹ��ָ�� */
    struct am_ic_cpu_plus_drv_funcs *p_funcs;

    /* \brief �������������ĵ�һ������ */
    void                            *p_drv;
} am_ic_cpu_plus_serv_t;

typedef am_ic_cpu_plus_serv_t *am_ic_cpu_plus_handle_t;

/**
 * \brief ��Ƭ���˻�ʱд�����ݻ�����Կ(SL0ר������)
 *
 * \param[in] handle : CPU PLUS����׼������
 * \param[in] addr   : ���ݿ����Կ��ַ
 * \param[in] p_buf  : 16�ֽ����ݻ���Կ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_personal_data_write (am_ic_cpu_plus_handle_t  handle,
                                        uint32_t                 addr,
                                        uint8_t                 *p_buf)
{
    return handle->p_funcs->pfn_ic_personal_data_write(handle->p_drv,
                                                       addr,
                                                       p_buf);
}

/**
 * \brief �ύ���˻�(ԾǨ��SL1,SL0ר������)
 *
 * \param[in] handle : CPU PLUS����׼������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_personal_commit (am_ic_cpu_plus_handle_t handle)
{
    return handle->p_funcs->pfn_ic_personal_commit(handle->p_drv);
}

/**
 * \brief �״���֤��Կ
 *
 * \param[in] handle   : CPU PLUS����׼������
 * \param[in] key_addr : ��Կ��ַ
 * \param[in] p_key    : 16�ֽ���Կ
 * \param[in] nbytes   : ��Կ����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_first_key_auth (am_ic_cpu_plus_handle_t  handle,
                                   uint32_t                 key_addr,
                                   const uint8_t           *p_key,
                                   uint32_t                 nbytes)
{
    return handle->p_funcs->pfn_ic_first_key_auth(handle->p_drv,
                                                  key_addr,
                                                  p_key,
                                                  nbytes);
}

/**
 * \brief ������֤��Կ
 *
 * \param[in] handle   : CPU PLUS����׼������
 * \param[in] key_addr : ��Կ��ַ
 * \param[in] p_key    : 16�ֽ���Կ
 * \param[in] nbytes   : ��Կ����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_follow_key_auth (am_ic_cpu_plus_handle_t  handle,
                                    uint32_t                 key_addr,
                                    uint8_t                 *p_key,
                                    uint32_t                 nbytes)
{
    return handle->p_funcs->pfn_ic_follow_key_auth(handle->p_drv,
                                                   key_addr,
                                                   p_key,
                                                   nbytes);
}

/**
 * \brief ��λ��֤
 *
 * \param[in] handle : CPU PLUS����׼������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_reset_auth (am_ic_cpu_plus_handle_t handle)
{
    return handle->p_funcs->pfn_ic_reset_auth(handle->p_drv);
}

/**
 * \brief SL3����������
 *
 * \param[in] handle    : CPU PLUS����׼������
 * \param[in] mode      : Ĭ��ΪSL3_READ_MODE3  PLUS S��ֻ֧��ģʽSL3����ģʽ
 *                         - AM_IC_CPU_PLUS_SL3_READ_MODE0  -- ����ģʽ0
 *                         - AM_IC_CPU_PLUS_SL3_READ_MODE1  -- ����ģʽ1
 *                         - AM_IC_CPU_PLUS_SL3_READ_MODE2  -- ����ģʽ2
 *                         - AM_IC_CPU_PLUS_SL3_READ_MODE3  -- ����ģʽ3
 *                         - AM_IC_CPU_PLUS_SL3_READ_MODE4  -- ����ģʽ4
 *                         - AM_IC_CPU_PLUS_SL3_READ_MODE5  -- ����ģʽ5
 *                         - AM_IC_CPU_PLUS_SL3_READ_MODE6  -- ����ģʽ6
 *                         - AM_IC_CPU_PLUS_SL3_READ_MODE7  -- ����ģʽ7
 * \param[out] p_buf     : ������16 * block_num����
 * \param[in] block_addr : ������ʼ���ַ
 * \param[in] block_num  : ���Ŀ�����ȡֵΪ1��216��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_data_read (am_ic_cpu_plus_handle_t  handle,
                              uint8_t                  mode,
                              uint8_t                 *p_buf,
                              uint32_t                 block_addr,
                              uint8_t                  block_num)
{
    return handle->p_funcs->pfn_ic_data_read(handle->p_drv,
                                             mode,
                                             p_buf,
                                             block_addr,
                                             block_num);
}

/**
 * \brief SL3д��������
 *
 * \param[in] handle    : CPU PLUS����׼������
 * \param[in] mode      : �ο�˵����дģʽ����
 *                           AM_IC_CPU_PLUS_SL3_WRITE_MODE0  д��ģʽ0
 *                           AM_IC_CPU_PLUS_SL3_WRITE_MODE1  д��ģʽ1
 *                           AM_IC_CPU_PLUS_SL3_WRITE_MODE2  д��ģʽ2
 *                           AM_IC_CPU_PLUS_SL3_WRITE_MODE3  д��ģʽ3
 *                           Ĭ��Ϊ SL3_WRITE_MODE3
 * \param[in] p_buf      : д���16 * block_num�ֽ�����
 * \param[in] block_addr : д����ʼ���ַ
 * \param[in] block_num  : д�Ŀ�����ȡֵΪ1��3��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_data_write (am_ic_cpu_plus_handle_t  handle,
                               uint8_t                  mode,
                               const uint8_t           *p_buf,
                               uint32_t                 block_addr,
                               uint8_t                  block_num)
{
    return handle->p_funcs->pfn_ic_data_write(handle->p_drv,
                                              mode,
                                              p_buf,
                                              block_addr,
                                              block_num);
}

/**
 * \brief ֵ��д����(SL3)
 *
 * \param[in] handle : CPU PLUS����׼������
 * \param[in] mode   : д���ģʽ(��am_ic_cpu_plus_data_write()��ͬ)
 * \param[in] addr   : ֵ��ŵ�ַ
 * \param[in] value  : д��ֵ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_value_block_write (am_ic_cpu_plus_handle_t handle,
                                      uint8_t                 mode,
                                      uint32_t                addr,
                                      int32_t                 value)
{
    return handle->p_funcs->pfn_ic_value_block_write(handle->p_drv,
                                                     mode,
                                                     addr,
                                                     value);
}

/**
 * \brief ��ȡֵ������ݣ�SL3��
 *
 * \param[in] handle    : CPU PLUS����׼������
 * \param[in] mode      : ����ģʽ����am_ic_cpu_plus_data_read()��ͬ��
 * \param[in] addr      : ֵ��ŵ�ַ
 * \param[out] P_value  : ��������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_value_block_read (am_ic_cpu_plus_handle_t  handle,
                                     uint8_t                  mode,
                                     uint32_t                 addr,
                                     int32_t                 *p_value)
{
    return handle->p_funcs->pfn_ic_value_block_read(handle->p_drv,
                                                    mode,
                                                    addr,
                                                    p_value);
}

/**
 * \brief ֵ�����(��/�����Դ�����ģʽ��SL3)
 *
 * \param[in] handle   : CPU PLUS����׼������
 * \param[in] mode     : ֵ�������ģʽ, ֻ֧������ģʽ
 *                        AM_IC_CPU_PLUS_SL3_INC_TRAN_MODE0 ��ֵ����ģʽ0
 *                        AM_IC_CPU_PLUS_SL3_INC_TRAN_MODE1 ��ֵ����ģʽ1
 *                        AM_IC_CPU_PLUS_SL3_DEC_TRAN_MODE0 ��ֵ����ģʽ0
 *                        AM_IC_CPU_PLUS_SL3_DEC_TRAN_MODE1 ��ֵ����ģʽ1
 * \param[in] src_addr : ֵ���Դ��ַ
 * \param[in] dst_addr : ������ֵ��ŵĵ�ַ
 * \param[in] value    : ֵ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_value_operation (am_ic_cpu_plus_handle_t handle,
                                    uint8_t                 mode,
                                    uint32_t                src_addr,
                                    uint32_t                dst_addr,
                                    int32_t                 value)
{
    return handle->p_funcs->pfn_ic_value_operation(handle->p_drv,
                                                   mode,
                                                   src_addr,
                                                   dst_addr,
                                                   value);
}

/**
 * \brief ֵ��ָ�����ָ����ַ��ֵ���Ƶ���������
 *
 * \param[in] handle   : CPU PLUS����׼������
 * \param[in] mode     : ֵ�������ģʽ, ֻ֧������ģʽ
 *                       AM_IC_CPU_PLUS_SL3_RESTORE_MODE0  �ָ�ģʽ0
 *                       AM_IC_CPU_PLUS_SL3_RESTORE_MODE1  �ָ�ģʽ1
 * \param[in] src_addr : ֵ������Դ��ַ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_restore (am_ic_cpu_plus_handle_t handle,
                            uint8_t                 mode,
                            uint32_t                src_addr)
{
    return handle->p_funcs->pfn_ic_restore(handle->p_drv,
                                           mode,
                                           src_addr);
}

/**
 * \brief ֵ�鴫�䣬��ֵ��������(������)���䵽ָ���Ŀ�
 *
 * \param[in] handle   : CPU PLUS����׼������
 * \param[in] mode     : ֵ�������ģʽ, ֻ֧������ģʽ
 *                       AM_IC_CPU_PLUS_SL3_TRANSFER_MODE0 ����ģʽ0
 *                       AM_IC_CPU_PLUS_SL3_TRANSFER_MODE1 ����ģʽ1
 * \param[in] dst_addr : ֵ����Ŀ�ĵ�ַ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_cpu_plus_transfer (am_ic_cpu_plus_handle_t handle,
                             uint8_t                 mode,
                             uint32_t                dst_addr)
{
    return handle->p_funcs->pfn_ic_transfer(handle->p_drv,
                                            mode,
                                            dst_addr);
}

#ifdef __cplusplus
}
#endif

#endif /* __AM_IC_CPU_PLUS_H */

/* end of file */


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
 * - 1.00 16-01-04  win, first implementation.
 * \endinternal
 */
#ifndef __AM_IC_ISO14443_H
#define __AM_IC_ISO14443_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup if_iso14443
 * \copydoc iso14443.h
 * @{
 */

/**
 * \name ISO14443����
 * @{
 */

#define AM_IC_A_REQUEST_EN       1   /**< \brief �������� */
#define AM_IC_A_ANTICOLL_EN      1   /**< \brief ����ײ���� */
#define AM_IC_A_SELECT_EN        1   /**< \brief ѡ������ */
#define AM_IC_A_HALT_EN          1   /**< \brief �������� */
#define AM_IC_A_ACTIVATE_EN      1   /**< \brief ���� */

#define AM_IC_B_REQUEST_EN       1   /**< \brief ISO14443-3B������ */
#define AM_IC_B_SLOT_MARKER_EN   0   /**< \brief ISO14443-3B��ʱ϶����ײ */
#define AM_IC_B_ATTRIB_EN        1   /**< \brief ISO14443-3B��ѡ�� */
#define AM_IC_B_HALT_EN          1   /**< \brief ISO14443-3B������ */
#define AM_IC_B_ACTIVATE_EN      1   /**< \brief ISO14443-3B������ */

#define AM_IC_A_RATS_EN          1   /**< \brief RATS           (ISO14443A) */
#define AM_IC_A_PPS_EN           1   /**< \brief PPS            (ISO14443A) */
#define AM_IC_A_DESELECT_EN      1   /**< \brief DESELECT       (ISO14443A) */
#define AM_IC_B_PROT_PARSE_EN    1   /**< \brief B�Ϳ���������       (ISO14443B) */
#define AM_IC_TPCL_EN            1   /**< \brief TPCL           (ISO14443)  */

/** @} */

/**
 * \name ISO14443Э�������� -- A�Ϳ��������
 * @{
 */

#define AM_IC_ISO14443_3A_REQALL            0x52    /**< \brief �������еĿ� */
#define AM_IC_ISO14443_3A_REQIDL            0x26    /**< \brief ������еĿ� */
#define AM_IC_ISO14443_3A_SELECT_LEVEL_1    0x93    /**< \brief һ������ײ/ѡ�� */
#define AM_IC_ISO14443_3A_SELECT_LEVEL_2    0x95    /**< \brief ��������ײ/ѡ�� */
#define AM_IC_ISO14443_3A_SELECT_LEVEL_3    0x97    /**< \brief ��������ײ/ѡ�� */

/** @} */

/**
 * \name ISO14443Э�������� -- B�Ϳ��������
 * @{
 */

#define AM_IC_ISO14443_3B_REQIDL            0x00    /**< \brief IDLE */
#define AM_IC_ISO14443_3B_REQALL            0x08    /**< \brief ALL */

/** @} */

/**
 * \brief ISO14443��Э������
 */
typedef enum am_ic_iso14443_subprot_type {
    AM_IC_ISO14443A_106       = 0x00,     /**< \brief ISO14443A */
    AM_IC_ISO14443A_212       = 0x01,     /**< \brief ISO14443A */
    AM_IC_ISO14443A_424       = 0x02,     /**< \brief ISO14443A */
    AM_IC_ISO14443A_847       = 0x03,     /**< \brief ISO14443A */
    AM_IC_ISO14443B_106       = 0x04,     /**< \brief ISO14443B */
    AM_IC_ISO14443B_212       = 0x05,     /**< \brief ISO14443B */
    AM_IC_ISO14443B_424       = 0x06,     /**< \brief ISO14443B */
    AM_IC_ISO14443B_847       = 0x07,     /**< \brief ISO14443B */
} am_ic_iso14443_subprot_type_t;

/**
 * \brief ISO14443-3A������Ļ�Ӧ��Ϣ(������RATS)
 *        ISO14443Э�鿨Ƭ�������ݽṹ�嶨��
 */
typedef struct am_ic_a_reset_info {
    uint8_t     atq[2];         /**< \brief ����Ӧ�� */
    uint8_t     sak;            /**< \brief ѡ���Ӧ */
    uint8_t     n_uid_len;      /**< \brief UID(��Ψһ���к�)���ȣ�4��7��10 */
    uint8_t     uid[10];        /**< \brief UID */
} am_ic_a_reset_info_t;

/**
 * \brief ISO14443-3B������Ļ�Ӧ��Ϣ
 *        ISO14443Э�鿨Ƭ�������ݽṹ�嶨��
 */
typedef struct am_ic_b_reset_info {
    uint8_t     pupi[4];        /**< \brief αΨһPICC ��ʶ�� */
    uint8_t     app_data[4];    /**< \brief Ӧ������ */
    uint8_t     prot_info[4];   /**< \brief ������Ϣ,����Ϊ3�ֽ�,��չ��Ϊ4�ֽ� */
} am_ic_b_reset_info_t;

/**
 * \brief ISO14443���������ṹ��
 */
struct am_ic_iso14443_drv_funcs {

    /** \brief ISO14443-3 A������ */
    int (*pfn_ic_a_request) (void     *p_drv,
                             uint8_t   req_code,
                             uint8_t  *p_atq,
                             uint32_t *p_nbytes);

    /** \brief ISO14443-3 A��λ��ʽ����ײ */
    int (*pfn_ic_a_anticoll) (void     *p_drv,
                              uint8_t   mode,
                              uint8_t   level,
                              uint8_t  *p_uid,
                              uint8_t   bits,
                              uint32_t *p_nbytes);

    /** \brief ISO14443-3 A��ѡ��Ƭ */
    int (*pfn_ic_a_select) (void          *p_drv,
                            uint8_t        sel_code,
                            const uint8_t *p_uid,
                            uint32_t       nbytes,
                            uint8_t       *p_sak);

    /** \brief ISO14443-3 A����ΪHALT״̬ */
    int (*pfn_ic_a_halt) (void *p_drv);

    /** \brief ISO14443-3 A������ */
    int (*pfn_ic_a_activate) (void                 *p_drv,
                              uint8_t               mode,
                              uint8_t               req_code,
                              am_ic_a_reset_info_t *p_reset_info);

    /** \brief ISO14443-3 B������ */
    int (*pfn_ic_b_request) (void                 *p_drv,
                             uint8_t               req_code,
                             uint8_t               afi,
                             uint8_t               n,
                             am_ic_b_reset_info_t *p_reset_info);

    /** \brief ISO14443-3 B��ʱ϶��Ƿ���ײ */
    int (*pfn_ic_b_slot_mark) (void                 *p_drv,
                               uint8_t               n,
                               am_ic_b_reset_info_t *p_reset_info);

    /** \brief ISO14443-3 B���޸����Բ�ѡ�� */
    int (*pfn_ic_b_attrib_set) (void       *p_drv,
                                const void *p_pupi,
                                uint32_t    nbytes,
                                uint8_t     cid,
                                uint8_t     pro_type);

    /** \brief ISO14443-3 B����ΪHALT״̬ */
    int (*pfn_ic_b_halt) (void *p_drv, uint8_t *p_pupi, uint32_t nbytes);

    /** \brief ISO14443-3 B������ */
    int (*pfn_ic_b_activate) (void                 *p_drv,
                              uint8_t               req_code,
                              uint8_t               afi,
                              am_ic_b_reset_info_t *p_reset_info);

    /** \brief ISO14443-4 A������Ӧ������Ӧ*/
    int (*pfn_ic_a_rats_get) (void     *p_drv,
                              uint8_t   cid,
                              void     *p_rats,
                              uint32_t  buf_size,
                              uint32_t *p_nbytes);

    /** \brief ISO14443-4 A��Э��Ͳ���ѡ������ */
    int (*pfn_ic_a_pps_set) (void *p_drv, uint8_t flags);

    /** \brief ISO14443-4 A��ȡ��ѡ�� */
    int (*pfn_ic_a_deselect) (void *p_drv);

    /** \brief ISO14443 ���䣨T=CL��*/
    int (*pfn_ic_transfer) (void       *p_drv,
                            const void *p_txbuf,
                            uint32_t    n_tx,
                            void       *p_rxbuf,
                            uint32_t    buf_size,
                            uint32_t   *p_n_rx);
                           
};

/**
 * \brief ISO14443 ����ṹ��
 */
typedef struct am_ic_iso14443_serv {

    /** \brief ISO14443���������ṹ��ָ�� */
    struct am_ic_iso14443_drv_funcs *p_funcs;

    /** \brief �������������ĵ�һ������ */
    void                            *p_drv;
} am_ic_iso14443_serv_t;

/** \brief ����ISO14443��������� */
typedef am_ic_iso14443_serv_t *am_ic_iso14443_handle_t;

/**
 * \brief ISO14443-3 A������
 *
 * \param[in]  handle   : ISO14443������
 * \param[in]  req_code : �������
 *                       - AM_IC_ISO14443_3A_REQIDL ������п�
 *                       - AM_IC_ISO14443_3A_REQALL �������п�
 * \param[out] p_atq    : ���󷵻���Ϣ
 * \param[out] p_nbytes : ���󷵻���Ϣ���ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_a_request (am_ic_iso14443_handle_t  handle,
                              uint8_t                  req_code,
                              uint8_t                 *p_atq,
                              uint32_t                *p_nbytes)
{
    return handle->p_funcs->pfn_ic_a_request(handle->p_drv,
                                             req_code,
                                             p_atq,
                                             p_nbytes);
}

/**
 * \brief ISO14443-3 A��λ��ʽ����ײ
 *
 * \param[in] handle : ISO14443������
 * \param[in] mode   : ����ײģʽ
 *                       - 0x00 -- ִ�з���ײѭ����
 *                       - 0x01 -- ִֻ��һ�η���ײ
 * \param[in] level  : ����ײ�ȼ�
 *                       - 0x93����1��
 *                       - 0x95����2��
 *                       - 0x97����3��
 * \param[in, out] p_uid  : ������֪��UID����������UID
 * \param[in] bits        : ��֪UID��λ��
 * \param[out] p_nbytes   : ����UID���ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_a_anticoll (am_ic_iso14443_handle_t  handle,
                               uint8_t                  mode,
                               uint8_t                  level,
                               uint8_t                 *p_uid,
                               uint8_t                  bits,
                               uint32_t                *p_nbytes)
{
    return handle->p_funcs->pfn_ic_a_anticoll(handle->p_drv,
                                              mode,
                                              level,
                                              p_uid,
                                              bits,
                                              p_nbytes);
}

/**
 * \brief ISO14443-3 A��ѡ��Ƭ
 *
 * \param[in] handle    : ISO14443������
 * \param[in] level     : ����ײ�ȼ�
 *                         - 0x93����1��
 *                         - 0x95����2��
 *                         - 0x97����3��
 * \param[in]  p_uid    : ����UID
 * \param[out] nbytes   : UID���ֽ���
 * \param[out] p_sak    : ѡ��Ӧ��(1�ֽ�)
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_a_select (am_ic_iso14443_handle_t  handle,
                             uint8_t                  level,
                             const uint8_t           *p_uid,
                             uint32_t                 nbytes,
                             uint8_t                 *p_sak)
{
    return handle->p_funcs->pfn_ic_a_select(handle->p_drv,
                                            level,
                                            p_uid,
                                            nbytes,
                                            p_sak);
}

/**
 * \brief ISO14443-3 A����ΪHALT״̬
 *
 * \param[in] handle : ISO14443������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_a_halt (am_ic_iso14443_handle_t handle)
{
    return handle->p_funcs->pfn_ic_a_halt(handle->p_drv);
}

/**
 * \brief ISO14443-3 A������
 *
 * \param[in] handle        : ISO14443������
 * \param[in] mode          : ����ײģʽ
 *                             - 0x00 -- ִ�з���ײѭ����
 *                             - 0x01 -- ִֻ��һ�η���ײ
 * \param[in] req_code      : �������
 *                             - 0x26 IDLE
 *                             - 0x52 ALL
 * \param[out] p_reset_info : ISO14443-3 A�������Ӧ��Ϣ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_a_activate (am_ic_iso14443_handle_t  handle,
                               uint8_t                  mode,
                               uint8_t                  req_code,
                               am_ic_a_reset_info_t    *p_reset_info)
{
    return handle->p_funcs->pfn_ic_a_activate(handle->p_drv,
                                              mode,
                                              req_code,
                                              p_reset_info);
}

/**
 * \brief ISO14443-3 B������
 *
 * \param[in] handle        : ISO14443������
 * \param[in] req_code      : �������
 *                             - 0x26 IDLE
 *                             - 0x52 ALL
 * \param[in] afi           : Ӧ�ñ�ʶ����0x00��ȫѡ
 * \param[in] n             : ʱ϶����,ȡֵ��Χ0--4
 * \param[out] p_reset_info : ISO14443-3 B�������Ӧ��Ϣ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_b_request (am_ic_iso14443_handle_t  handle,
                              uint8_t                  req_code,
                              uint8_t                  afi,
                              uint8_t                  n,
                              am_ic_b_reset_info_t    *p_reset_info)
{
    return handle->p_funcs->pfn_ic_b_request(handle->p_drv,
                                             req_code,
                                             afi,
                                             n,
                                             p_reset_info);
}

/**
 * \brief ISO14443-3 B��ʱ϶��Ƿ���ײ
 *
 * \param[in] handle       : ISO14443������
 * \param[in] n            : ʱ϶��ǣ�ȡֵ��Χ2-16
 * \param[in] p_reset_info : ISO14443-3 B�������Ӧ��Ϣ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_b_slot_mark (am_ic_iso14443_handle_t  handle,
                                uint8_t                  n,
                                am_ic_b_reset_info_t    *p_reset_info)
{
    return handle->p_funcs->pfn_ic_b_slot_mark(handle->p_drv,
                                               n,
                                               p_reset_info);
}

/**
 * \brief ISO14443-3 B���޸����Բ�ѡ��
 *
 * \param[in] handle   : ISO14443������
 * \param[in] p_pupi   : ICΨһ��ʶ��
 * \param[in] nbytes   : ��ʶ���ֽ���
 * \param[in] cid      : ȡֵ��ΧΪ 0 - 14, ����֧��CID��������Ϊ0
 * \param[in] pro_type : ֧�ֵ�Э�飬�������Ӧ�е�ProtocolTypeָ��
 *                        - pro_type.3      -- PCD ��PICC �Ƿ����ͨ��
 *                            - 1              -- PCD ��ֹ��PICC ����ͨ��
 *                            - 0              -- PCD ��PICC ����ͨ��
 *                        - pro_type.2:1    -- PICC EOF ��PCD SOF�����С�ӳ�
 *                            - 11             -- 10 etu + 512 / fs
 *                            - 10             -- 10 etu + 256 / fs
 *                            - 01             -- 10 etu + 128 / fs
 *                            - 00             -- 10 etu + 32 / fs
 *                        - pro_type.0      -- �Ƿ���ѭISO14443-4
 *                            - 1              -- ��ѭISO14443-4;
 *                            - 0              -- ����ѭISO14443-4. (����֤����Ϊ1)
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_b_attrib_set (am_ic_iso14443_handle_t  handle,
                                 const void              *p_pupi,
                                 uint32_t                 nbytes,
                                 uint8_t                  cid,
                                 uint8_t                  pro_type)
{
    return handle->p_funcs->pfn_ic_b_attrib_set(handle->p_drv,
                                                p_pupi,
                                                nbytes,
                                                cid,
                                                pro_type);
}

/**
 * \brief ISO14443-3 B����ΪHALT״̬
 *
 * \param[in] handle : ISO14443������
 * \param[in] p_pupi : ICΨһ��ʶ��
 * \param[in] nbytes : ��ʶ���ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_b_halt (am_ic_iso14443_handle_t  handle,
                           uint8_t                 *p_pupi,
                           uint32_t                 nbytes)
{
    return handle->p_funcs->pfn_ic_b_halt(handle->p_drv,
                                          p_pupi,
                                          nbytes);
}

/**
 * \brief ISO14443-3 B������
 *
 * \param[in] handle        : ISO14443������
 * \param[in] req_code      : �������
 *                           - 0x00 -- ���еĿ�
 *                           - 0x08 -- ���еĿ�
 * \param[in] afi           : Ӧ�ñ�ʶ����0x00��ȫѡ
 * \param[out] p_reset_info : ISO14443-3 B�������Ӧ��Ϣ
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_b_activate (am_ic_iso14443_handle_t  handle,
                               uint8_t                  req_code,
                               uint8_t                  afi,
                               am_ic_b_reset_info_t    *p_reset_info)
{
    return handle->p_funcs->pfn_ic_b_activate(handle->p_drv,
                                              req_code,
                                              afi,
                                              p_reset_info);
}

/**
 * \brief ISO14443-4 A������Ӧ������Ӧ
 *
 * \param[in]  handle   : ISO14443������
 * \param[in]  cid      : ��ʶ��ţ�ȡֵ��Χ0--14
 * \param[out] p_rats   : ����Ӧ������Ӧ��Ϣ
 * \param[out] p_nbytes : ����Ӧ������Ӧ��Ϣ���ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_a_rats_get (am_ic_iso14443_handle_t  handle,
                               uint8_t                  cid,
                               void                    *p_rats,
                               uint32_t                 buf_size,
                               uint32_t                *p_nbytes)
{
    return handle->p_funcs->pfn_ic_a_rats_get(handle->p_drv,
                                              cid,
                                              p_rats,
                                              buf_size,
                                              p_nbytes);
}

/**
 * \brief ISO14443-4 A��Э��Ͳ���ѡ������
 *
 * \param[in] handle : ISO14443������
 * \param[in] flags  : λ�ʱ���
 *                      - b3:2 -- PCD  -> PICC��λ�ʱ���
 *                      - b1:0 -- PICC -> PCD ��λ�ʱ���
 *                          - (00)b -> 106Kb
 *                          - (01)b -> 212Kb
 *                          - (10)b -> 424Kb
 *                          - (11)b -> 847Kb
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_a_pps_set (am_ic_iso14443_handle_t handle,
                              uint8_t                 flags)
{
    return handle->p_funcs->pfn_ic_a_pps_set(handle->p_drv, flags);
}

/**
 * \brief ISO14443-4 A��ȡ��ѡ��
 *
 * \param[in] handle : ISO14443������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_a_deselect (am_ic_iso14443_handle_t handle)
{
    return handle->p_funcs->pfn_ic_a_deselect(handle->p_drv);
}

/**
 * \brief ISO14443 ���䣨T=CL��
 *
 * \param[in] handle  : ISO14443������
 * \param[in] p_txbuf : ��������ݻ�����
 * \param[in] n_tx    : ��Ҫ����������ֽ���
 * \param[in] p_rxbuf : �������ݵĻ�����
 * \param[in] n_rx    : ��Ҫ���յ��ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
int am_ic_iso14443_transfer (am_ic_iso14443_handle_t  handle,
                             const void              *p_txbuf,
                             uint32_t                 n_tx,
                             void                    *p_rxbuf,
                             uint32_t                 buf_size,
                             uint32_t                *p_n_rx)
{
    return handle->p_funcs->pfn_ic_transfer(handle,
                                            p_txbuf,
                                            n_tx,
                                            p_rxbuf,
                                            buf_size,
                                            p_n_rx);
}

/**
 * @} if_iso14443
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_IC_ISO14443_H */

/* end of file */

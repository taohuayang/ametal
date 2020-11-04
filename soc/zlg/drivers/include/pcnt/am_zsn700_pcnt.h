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
 * \brief PCNT�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-14
 * \endinternal
 */

#ifndef __AM_ZSN700_PCNT_H
#define __AM_ZSN700_PCNT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "hw/amhw_zsn700_pcnt.h"

/* ͨ������ѡ��ö�� */
typedef enum am_zsn700_pcnt_polar {
    ZSN700_PCNT_S0PNOINVERT = (0u),   /* S0ͨ�����Բ�ȡ�� */
    ZSN700_PCNT_S0PINVERT   = (1u),   /* S0ͨ��ȡ�� */
    ZSN700_PCNT_S1PNOINVERT = (2u),   /* S1ͨ�����Բ�ȡ�� */
    ZSN700_PCNT_S1PINVERT   = (3u)    /* S1ͨ��ȡ�� */
} am_zsn700_pcnt_polar_t;

/* ʱ��ѡ��ö�� */
typedef enum am_zsn700_pcnt_clk {
    ZSN700_PCNT_PCLK = (1u),
    ZSN700_PCNT_XTL  = (2u),
    ZSN700_PCNT_RCL  = (3u)
} am_zsn700_pcnt_clk_t;

/* �������ģʽѡ��ö�� */
typedef enum am_zsn700_pcnt_mode {
    ZSN700_PCNT_SINGLE  = (1u), /* ��ͨ���������ģʽ */
    ZSN700_PCNT_SPECIAL = (2u), /* ˫ͨ���������������ģʽ */
    ZSN700_PCNT_DOUBLE  = (3u)  /* ˫ͨ�������������ģʽ */
} am_zsn700_pcnt_mode_t;

/* �������ģʽѡ��ö�� */
typedef enum am_zsn700_pcnt_dir {
    ZSN700_PCNT_UP   = (0u), /* ���ϼ���ģʽ */
    ZSN700_PCNT_DOWN = (1u), /* ���¼���ģʽ */
} am_zsn700_pcnt_dir_t;

/* �жϱ�־ö�� */
typedef enum am_zsn700_pcnt_int {
    ZSN700_PCNT_INT_S1E = (1u << 7), /* S1���������� */
    ZSN700_PCNT_INT_S0E = (1u << 6), /* S0���������� */
    ZSN700_PCNT_INT_BB  = (1u << 5), /* �м��޵�״̬ */
    ZSN700_PCNT_INT_FE  = (1u << 4), /* ����ȷ�ǽ�����֡ */
    ZSN700_PCNT_INT_DIR = (1u << 3), /* �������巽��ı� */
    ZSN700_PCNT_INT_TO  = (1u << 2), /* ��ʱ�ж� */
    ZSN700_PCNT_INT_OV  = (1u << 1), /* ������ж� */
    ZSN700_PCNT_INT_UF  = (1u << 0)  /* ������ж� */
} am_zsn700_pcnt_int_t;

/* PCNT����ö�� */
typedef enum am_zsn700_pcnt_cmd {
    ZSN700_PCNT_B2C = (4u), /* ������BUF�е�ֵͬ����CNT */
    ZSN700_PCNT_B2T = (2u), /* ������BUF�е�ֵͬ����TOP */
    ZSN700_PCNT_T2C = (1)   /* ������TOP�е�ֵͬ����CNT */
} am_zsn700_pcnt_cmd_t;

/* ���ѡ�� */
typedef enum am_zsn700_pcnt_dgb {
    ZSN700_PCNT_DGB_0   = (0),  /* �̶�Ϊ0 */
    ZSN700_PCNT_DGB_SA  = (4u), /* ����ͬ��֮��������S0A/S1A�� */
    ZSN700_PCNT_DGB_SP  = (2u), /* ���弫��ѡ��֮��������S0P/S1P�� */
    ZSN700_PCNT_DGB_SPF = (1)   /* �����˲�֮��������S0PF/S1PF�� */
} am_zsn700_pcnt_dgb_t;

/**
 * \brief PCNT�豸��Ϣ�����ṹ��
 */
typedef struct am_zsn700_pcnt_devinfo {
    uint32_t                pcnt_regbase;   /* �Ĵ�����ַ */
    uint32_t                clk_num;        /* ʱ��ID */
    uint16_t                inum;           /* �жϺ� */
    void                    (*pfn_plfm_init)(void);         /*ƽ̨��ʼ������ */
    void                    (*pfn_plfm_deinit)(void);       /* ƽ̨���ʼ������ */
} am_zsn700_pcnt_devinfo_t;

typedef struct am_zsn700_pcnt_dev {
    amhw_zsn700_pcnt_t             *p_hw_pcnt;
    const am_zsn700_pcnt_devinfo_t *p_devinfo;
} am_zsn700_pcnt_dev_t;

typedef am_zsn700_pcnt_dev_t* am_zsn700_pcnt_handle_t;

/**
 * \addtogroup am_zlg_if_pcnt
 * \copydoc am_zlg_pcnt.h
 * @{
 */

/**
 * \brief PCNT��ʼ��
 *
 * \param[in] p_dev     : ָ��PCNT�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��PCNT�豸��Ϣ�ṹ���ָ��
 *
 * \return PCNT����������
 */
am_zsn700_pcnt_handle_t am_zsn700_pcnt_init (
        am_zsn700_pcnt_dev_t           *p_dev,
        const am_zsn700_pcnt_devinfo_t *p_devinfo);

/**
 * \brief ���PCNT��ʼ��
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 *
 * \return ��
 */
void am_zsn700_pcnt_deinit (am_zsn700_pcnt_handle_t handle);

/**
 * \brief ����ʱ������
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] clk    : ʱ��
 *
 * \return ��
 */
void am_zsn700_pcnt_clk_sel (am_zsn700_pcnt_handle_t handle,
                             am_zsn700_pcnt_clk_t    clk);

/**
 * \brief ͨ����������
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] polar  : ͨ������ѡ��
 *
 * \return ��
 */
void am_zsn700_pcnt_polar_set (am_zsn700_pcnt_handle_t handle,
                               am_zsn700_pcnt_polar_t  polar);

/**
 * \brief �˲�ʹ��
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] debtop : �˲���������ֵ
 * \param[in] clkdiv : �˲�ʱ�ӷ�Ƶϵ��
 *
 * \return ��
 */
void am_zsn700_pcnt_flt_enable (am_zsn700_pcnt_handle_t handle,
                                uint8_t                 debtop,
                                uint16_t                clkdiv);

/**
 * \brief �˲�����
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 *
 * \return ��
 */
void am_zsn700_pcnt_flt_disable (am_zsn700_pcnt_handle_t handle);

/**
 * \brief ��ʱʹ��
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] th     : ��ʱ��ֵ
 *
 * \return ��
 */
void am_zsn700_pcnt_timeover_enable (am_zsn700_pcnt_handle_t handle,
                                     uint16_t                th);

/**
 * \brief ��ʱ����
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 *
 * \return ��
 */
void am_zsn700_pcnt_timeover_disable (am_zsn700_pcnt_handle_t handle);

/**
 * \brief PCNTʹ��
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] mode   : ����ģʽ
 * \param[in] dir    : ��������
 * \param[in] value  : ���ֵ
 * \param[in] dgb    : ���ѡ��
 *
 * \return ��
 */
void am_zsn700_pcnt_start (am_zsn700_pcnt_handle_t handle,
                           am_zsn700_pcnt_mode_t   mode,
                           am_zsn700_pcnt_dir_t    dir,
                           uint16_t                value,
                           am_zsn700_pcnt_dgb_t    dgb);

/**
 * \brief PCNT����
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 *
 * \return ��
 */
void am_zsn700_pcnt_stop (am_zsn700_pcnt_handle_t handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_PCNT_H */

/* end of file */

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
 * \brief PCA�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-09
 * \endinternal
 */

#ifndef __AM_HC32_PCA_H
#define __AM_HC32_PCA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "hw/amhw_hc32_pca.h"

/* �жϱ�־ö�� */
typedef enum am_hc32_pca_int {
    HC32_PCA_CF   = (0x1 << 7),   /* �����������־ */
    HC32_PCA_CCF4 = (0x1 << 4),   /* ������ģ��4�Ƚ�/�����־λ */
    HC32_PCA_CCF3 = (0x1 << 3),   /* ������ģ��3�Ƚ�/�����־λ */
    HC32_PCA_CCF2 = (0x1 << 2),   /* ������ģ��2�Ƚ�/�����־λ */
    HC32_PCA_CCF1 = (0x1 << 1),   /* ������ģ��1�Ƚ�/�����־λ */
    HC32_PCA_CCF0 = (0x1 << 0)    /* ������ģ��0�Ƚ�/�����־λ */
} am_hc32_pca_int_t;

/* ʱ��Դö�� */
typedef enum am_hc32_pca_clk {
    HC32_PCA_PCLK32  = (0x0),  /* PCLK/32 */
    HC32_PCA_PCLK16  = (0x1),  /* PCLK/16 */
    HC32_PCA_PCLK8   = (0x2),  /* PCLK/8 */
    HC32_PCA_PCLK4   = (0x3),  /* PCLK/4 */
    HC32_PCA_PCLK2   = (0x4),  /* PCLK/2 */
    HC32_PCA_TIM0_OF = (0x5),  /* timer0 overflow */
    HC32_PCA_TIM1_OF = (0x6),  /* timer1 overflow */
    HC32_PCA_EC1     = (0x7),  /* ECI �ⲿʱ�ӣ�ʱ��PCLK�ķ�Ƶ���� */
} am_hc32_pca_clk_t;

/* �Ƚϲ���ģʽ����ö�� */
typedef enum am_hc32_pca_ccapm {
    HC32_PCA_ECOM = (0x1 << 6),   /* ����Ƚ������ܿ���λ */
    HC32_PCA_MAT  = (0x1 << 3),   /* ����ƥ�����λ */
    HC32_PCA_PWM  = (0x1 << 1),   /* ������ƿ���λ */
    HC32_PCA_CCIE = (0x1 << 0)    /* PCAʹ���ж� */
} am_hc32_pca_ccapm_t;

/* ���ز���ö�� */
typedef enum am_hc32_pca_capn {
    HC32_PCA_CAPP_EN  = (0x1 << 1),   /* �������ز��� */
    HC32_PCA_CAPP_DIS = (0x0 << 1),   /* ��ֹ���ز��� */
    HC32_PCA_CAPN_EN  = (0x1),        /* �����ز��� */
    HC32_PCA_CAPN_DIS = (0x0),        /* ��ֹ���ز��� */
} am_hc32_pca_capn_t;

/* ��ת����ö�� */
typedef enum am_hc32_pca_tog {
    HC32_PCA_TOG_EN   = (0x1),   /* ʹ�ܷ�ת */
    HC32_PCA_TOG_DIS  = (0x0),   /* ���ܷ�ת */
} am_hc32_pca_tog_t;

/* PWM����ѡ�� */
typedef enum am_hc32_pca_pwm {
    HC32_PCA_PWM_8  = 0,   /* 8λPWM */
    HC32_PCA_PWM_16 = 1    /* 16λPWM */
} am_hc32_pca_pwm_t;

/**
 * \brief PCA��Ӧͨ����GPIO��Ϣ
 */
typedef struct {
    uint32_t gpio;          /**< \brief ��Ӧ��GPIO�ܽź� */
    uint32_t pwmunc;        /**< \brief PWMģʽ��Ӧ��GPIO�������� */
    uint32_t capfunc;       /**< \brief CAPģʽ��Ӧ��GPIO����Ĭ������ */
} am_hc32_pca_ioinfo_t;

/**
 * \brief PCNT�豸��Ϣ�����ṹ��
 */
typedef struct am_hc32_pca_devinfo {
    uint32_t                pca_regbase;        /* �Ĵ�����ַ */
    uint32_t                clk_num;            /* ʱ��ID */
    uint16_t                inum;               /* �жϺ� */
    am_hc32_pca_clk_t     clk_src;            /* ʱ��Դѡ�� */
    am_hc32_pca_ioinfo_t  *ioinfo;            /* ����������Ϣ */
    void                    (*pfn_plfm_init)(void);         /*ƽ̨��ʼ������ */
    void                    (*pfn_plfm_deinit)(void);       /* ƽ̨���ʼ������ */
} am_hc32_pca_devinfo_t;

typedef struct am_hc32_pca_dev {
    amhw_hc32_pca_t             *p_hw_pca;
    const am_hc32_pca_devinfo_t *p_devinfo;
} am_hc32_pca_dev_t;

typedef am_hc32_pca_dev_t* am_hc32_pca_handle_t;

/**
 * \addtogroup am_zlg_if_pca
 * \copydoc am_zlg_pca.h
 * @{
 */

/**
 * \brief PCA��ʼ��
 *
 * \return PCA����������
 */
am_hc32_pca_handle_t am_hc32_pca_init (
        am_hc32_pca_dev_t             *p_dev,
        const am_hc32_pca_devinfo_t   *p_devinfo);

/**
 * \brief ���PCA��ʼ��
 *
 * \param[in] handle : ����豸������PCA��׼����������
 *
 * \return ��
 */
void am_hc32_pca_deinit (am_hc32_pca_handle_t handle);

/**
 * \brief PCA���ز���ģʽ����
 *
 * \param[in] handle : ����豸������PCA��׼����������
 * \param[in] num    : PCA ģ����
 * \param[in] chan   : ͨ����
 * \param[in] cap    : �������ѡ��
 *
 * \return AM_OK:�ɹ�
 *         ����:ʧ��
 */
int am_hc32_pca_cap_set (am_hc32_pca_handle_t handle,
                           uint8_t                num,
                           uint8_t                chan,
                           am_hc32_pca_capn_t   cap);

/**
 * \brief PCA�Ƚϼ���ģʽ����
 *
 * \param[in] handle : ����豸������PCA��׼����������
 * \param[in] num    : PCA ģ����
 * \param[in] carr   : ���ڼĴ���ֵ
 * \param[in] ccap   : �Ƚϲ���Ĵ���ֵ
 *
 * \return AM_OK:�ɹ�
 *         ����:ʧ��
 */
int am_hc32_pca_cmp_cnt_set (am_hc32_pca_handle_t handle,
                               uint8_t                num,
                               uint16_t               carr,
                               uint16_t               ccap);

/**
 * \brief PCA�������ģʽ����
 *
 * \param[in] handle  : ����豸������PCA��׼����������
 * \param[in] num     : PCA ģ����
 * \param[in] chan    : ͨ����
 * \param[in] pwm_sel : PWM����ѡ��
 * \param[in] carr    : ���ڼĴ���ֵ
 * \param[in] ccap    : �Ƚϲ���Ĵ���ֵ
 *
 * 8bitռ�ձ�  = (255 - ccap) / 100 * 100%
 * 16bitռ�ձ�= (carr - ccap) / carr * 100%
 *
 * \return AM_OK:�ɹ�
 *         ����:ʧ��
 */
int am_hc32_pca_pwm_set (am_hc32_pca_handle_t handle,
                           uint8_t                num,
                           uint8_t                chan,
                           am_hc32_pca_pwm_t    pwm_sel,
                           uint16_t               carr,
                           uint16_t               ccap);

/**
 * \brief PCA��ʼ����
 *
 * \param[in] handle : ����豸������PCA��׼����������
 *
 * \return
 */
void am_hc32_pca_start(am_hc32_pca_handle_t handle);

/**
 * \brief PCAֹͣ����
 *
 * \param[in] handle : ����豸������PCA��׼����������
 *
 * \return
 */
void am_hc32_pca_stop(am_hc32_pca_handle_t handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32_PCA_H */

/* end of file */

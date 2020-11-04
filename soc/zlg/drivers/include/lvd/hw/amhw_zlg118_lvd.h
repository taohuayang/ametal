/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief LVD �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 19-10-08
 * \endinternal
 */

#ifndef __AMHW_ZLG118_LVD_H
#define __AMHW_ZLG118_LVD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zlg118_if_lvd
 * \copydoc amhw_zlg118_lvd.h
 * @{
 */

/**
 * \brief LVD - �Ĵ�����
 */
typedef struct amhw_zlg118_lvd {
         uint8_t   res[40];      /**< \brief  ���� */
    __IO uint32_t  lvccr;        /**< \brief  LVD ���üĴ��� */
    __IO uint32_t  lvcifr;       /**< \brief  LVD �жϼĴ��� */
} amhw_zlg118_lvd_t;

/**
 * \brief LVD �ж�ʹ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_int_enable (amhw_zlg118_lvd_t *p_hw_lvd)
{
    p_hw_lvd->lvccr |= (1 << 15);
}

/**
 * \brief LVD �жϽ���
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_int_disable (amhw_zlg118_lvd_t *p_hw_lvd)
{
    p_hw_lvd->lvccr &= ~(1 << 15);
}

/*
 * \brief LVD ����ʹ������
 */
#define AMHW_ZLG118_LVD_HTEN    (1U << 14)    /**< \brief �ߵ�ƽ����ʹ�� */
#define AMHW_ZLG118_LVD_RTEN    (1U << 13)    /**< \brief �����ش���ʹ�� */
#define AMHW_ZLG118_LVD_FTEN    (1U << 12)    /**< \brief �½��ش���ʹ�� */

/**
 * \brief LVD ����ʹ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 * \param[in] flag    : �ο��궨�壺LVD ����ʹ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_tri_enable (amhw_zlg118_lvd_t *p_hw_lvd, uint32_t flag)
{
    switch (flag){

        case AMHW_ZLG118_LVD_FTEN : p_hw_lvd->lvccr |= flag;
                                    p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_RTEN;
                                    p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_HTEN;
            break;
        case AMHW_ZLG118_LVD_RTEN : p_hw_lvd->lvccr |= flag;
                                    p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_FTEN;
                                    p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_HTEN;
            break;
        case AMHW_ZLG118_LVD_HTEN : p_hw_lvd->lvccr |= flag;
                                    p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_FTEN;
                                    p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_RTEN;
            break;
        case AMHW_ZLG118_LVD_FTEN | AMHW_ZLG118_LVD_RTEN :
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_FTEN;
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_RTEN;
            p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_HTEN;
            break;
        case AMHW_ZLG118_LVD_FTEN | AMHW_ZLG118_LVD_HTEN :
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_FTEN;
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_HTEN;
            p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_RTEN;
            break;
        case AMHW_ZLG118_LVD_HTEN | AMHW_ZLG118_LVD_RTEN :
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_HTEN;
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_RTEN;
            p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_FTEN;
            break;
        case AMHW_ZLG118_LVD_HTEN | AMHW_ZLG118_LVD_RTEN | AMHW_ZLG118_LVD_FTEN:
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_HTEN;
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_RTEN;
            p_hw_lvd->lvccr |= AMHW_ZLG118_LVD_FTEN;
            break;
        default:
            p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_HTEN;
            p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_RTEN;
            p_hw_lvd->lvccr &= ~AMHW_ZLG118_LVD_FTEN;
    }
}

/* * \brief LVD ������������
 */
#define AMHW_ZLG118_LVD_HTDIS    (1U << 14)    /**< \brief �ߵ�ƽ�������� */
#define AMHW_ZLG118_LVD_RTDIS    (1U << 13)    /**< \brief �����ش������� */
#define AMHW_ZLG118_LVD_FTDIS    (1U << 12)    /**< \brief �½��ش������� */

/**
 * \brief LVD ��������
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 * \param[in] flag    : �ο��궨�壺LVD ������������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_tri_disable (amhw_zlg118_lvd_t *p_hw_lvd, uint32_t flag)
{
    p_hw_lvd->lvccr &= ~flag;
}

/**
 * \brief LVD �����˲�ʱ��
 */
typedef enum amhw_zlg118_lvd_deb_time {
    AMHW_ZLG118_LVD_DEB_TIME_7_US = 0,
    AMHW_ZLG118_LVD_DEB_TIME_14_US,
    AMHW_ZLG118_LVD_DEB_TIME_28_US,
    AMHW_ZLG118_LVD_DEB_TIME_112_US,
    AMHW_ZLG118_LVD_DEB_TIME_450_US,
    AMHW_ZLG118_LVD_DEB_TIME_1P8_MS,
    AMHW_ZLG118_LVD_DEB_TIME_7P2_MS,
    AMHW_ZLG118_LVD_DEB_TIME_28P8_MS,
}amhw_zlg118_lvd_deb_time_t;

/**
 * \brief LVD �����˲�ʱ��ѡ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 * \param[in] flag    : �ο�ö�٣�LVD �����˲�ʱ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_deb_time_sel (amhw_zlg118_lvd_t *p_hw_lvd, uint32_t flag)
{
    p_hw_lvd->lvccr = (p_hw_lvd->lvccr & (~(0x7 << 9))) | (flag << 9);
}

/**
 * \brief LVD �����˲�ʹ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_deb_time_enable (amhw_zlg118_lvd_t *p_hw_lvd)
{
    p_hw_lvd->lvccr |= (1 << 8);
}

/**
 * \brief LVD �����˲�����
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_deb_time_disable (amhw_zlg118_lvd_t *p_hw_lvd)
{
    p_hw_lvd->lvccr &= ~(1 << 8);
}

/**
 * \brief LVD ��ֵ��ѹ
 */
typedef enum amhw_zlg118_lvd_vids {
    AMHW_ZLG118_LVD_VIDS_1P8_V = 0,
    AMHW_ZLG118_LVD_VIDS_1P9_V,
    AMHW_ZLG118_LVD_VIDS_2P0_V,
    AMHW_ZLG118_LVD_VIDS_2P1_V,
    AMHW_ZLG118_LVD_VIDS_2P2_V,
    AMHW_ZLG118_LVD_VIDS_2P3_V,
    AMHW_ZLG118_LVD_VIDS_2P4_V,
    AMHW_ZLG118_LVD_VIDS_2P5_V,
    AMHW_ZLG118_LVD_VIDS_2P6_V,
    AMHW_ZLG118_LVD_VIDS_2P7_V,
    AMHW_ZLG118_LVD_VIDS_2P8_V,
    AMHW_ZLG118_LVD_VIDS_2P9_V,
    AMHW_ZLG118_LVD_VIDS_3P0_V,
    AMHW_ZLG118_LVD_VIDS_3P1_V,
    AMHW_ZLG118_LVD_VIDS_3P2_V,
    AMHW_ZLG118_LVD_VIDS_3P3_V,
}amhw_zlg118_lvd_vids_t;

/**
 * \brief LVD ��ֵ��ѹѡ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 * \param[in] flag    : �ο�ö�٣�LVD ��ֵ��ѹ
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_vids_sel (amhw_zlg118_lvd_t *p_hw_lvd, uint32_t flag)
{
    p_hw_lvd->lvccr = (p_hw_lvd->lvccr & (~(0xf << 4))) | (flag << 4);
}

/*
 * \brief LVD �����Դѡ������
 */
#define ANHW_ZLG118_LVD_SRC_PB07 (3U) /**< \brief PB07�˿������ѹ */
#define ANHW_ZLG118_LVD_SRC_PB08 (2U) /**< \brief PB08�˿������ѹ */
#define ANHW_ZLG118_LVD_SRC_PC13 (1U) /**< \brief PC13�˿������ѹ */
#define ANHW_ZLG118_LVD_SRC_AVCC (0U) /**< \brief AVCC��Դ��ѹ*/

/**
 * \brief LVD �����Դѡ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 * \param[in] flag    : �ο��궨�壺LVD �����Դѡ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_src_sel (amhw_zlg118_lvd_t *p_hw_lvd, uint32_t flag)
{
    p_hw_lvd->lvccr = (p_hw_lvd->lvccr & (~(0x3 << 2))) | (flag << 2);
}

/*
 * \brief LVD ��������ѡ������
 */
#define ANHW_ZLG118_LVD_TRI_ACT_SYSTEM_RESET  (1U)   /**< \brief ϵͳ��λ */
#define ANHW_ZLG118_LVD_TRI_ACT_NVIC_INT      (0U)   /**< \brief NVIC�ж� */

/**
 * \brief LVD ��������ѡ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 * \param[in] flag    : �ο��궨�壺LVD ��������ѡ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_tri_act_sel (amhw_zlg118_lvd_t *p_hw_lvd, uint32_t flag)
{
    p_hw_lvd->lvccr = (p_hw_lvd->lvccr & (~(0x1 << 1))) | (flag << 1);
}

/**
 * \brief LVD ʹ��
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_enable (amhw_zlg118_lvd_t *p_hw_lvd)
{
    p_hw_lvd->lvccr |= (1 << 0);
}

/**
 * \brief LVD ����
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_disable (amhw_zlg118_lvd_t *p_hw_lvd)
{
    p_hw_lvd->lvccr &= ~(1 << 0);
}

/**
 * \brief LVD cr�Ĵ�������
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_lvd_cr_clr (amhw_zlg118_lvd_t *p_hw_lvd)
{
    p_hw_lvd->lvccr = 0;
}

/**
 * \brief LVD �˲�״̬��ȡ
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : LVD �˲�״̬
 */
am_static_inline
int amhw_zlg118_flt_status_check (amhw_zlg118_lvd_t *p_hw_lvd)
{
    return (p_hw_lvd->lvcifr & (1 << 1));
}

/**
 * \brief LVD �ж�״̬��ȡ
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : LVD �ж�״̬
 */
am_static_inline
int amhw_zlg118_int_status_check (amhw_zlg118_lvd_t *p_hw_lvd)
{
    return (p_hw_lvd->lvcifr & 0x1);
}

/**
 * \brief �ж�״̬��־���
 *
 * \param[in] p_hw_lvd : ָ��LVD�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_int_falg_clr (amhw_zlg118_lvd_t *p_hw_lvd)
{
    p_hw_lvd->lvcifr &= ~(1 << 0);
}

/**
 * @} amhw_if_zlg118_lvd
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG118_LVD_H */

/* end of file */

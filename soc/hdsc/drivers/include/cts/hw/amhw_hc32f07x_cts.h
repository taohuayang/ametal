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
 * \brief CTS�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-11
 * \endinternal
 */

#ifndef __AMHW_HC32F07X_CTS_H
#define __AMHW_HC32F07X_CTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__GNUC__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_hc32f07x_if_cts
 * \copydoc amhw_hc32f07x_cts.h
 * @{
 */

/**
 * \brief PCNT�Ĵ�����ṹ��
 */
typedef struct amhw_hc32f07x_cts {
    __IO uint32_t cr;        /* ���ƼĴ��� */
    __IO uint32_t cfgr;      /* ���üĴ��� */	
    __IO uint32_t isr;       /* �жϺ�״̬�Ĵ��� */
    __IO uint32_t icr;       /* �жϱ�־����Ĵ��� */	
} amhw_hc32f07x_cts_t;

/**
 * \brief CTS ��ʱ����������
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f07x_cts_tim_enable (amhw_hc32f07x_cts_t *p_hw_cts)
{
    p_hw_cts->cr |= (0x1ul << 15);
}

/**
 * \brief CTS ��ʱ������ֹͣ
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f07x_cts_tim_disable (amhw_hc32f07x_cts_t *p_hw_cts)
{
    p_hw_cts->cr &= ~(0x1ul << 15);
}

/**
 * \brief CTS ��΢��ֵ����
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  value     : ΢��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f07x_cts_trim_set (amhw_hc32f07x_cts_t *p_hw_cts,
	                               uint8_t              value)
{
    p_hw_cts->cr = (p_hw_cts->cr & ~(0x7f << 8)) | 
	                  ((value & 0x7f) << 8);
}

/**
 * \brief CTS ��΢��ֵ��ȡ
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return  value  ΢��ֵ
 */
am_static_inline
uint8_t amhw_hc32f07x_cts_trim_get (amhw_hc32f07x_cts_t *p_hw_cts)
{
    return ((p_hw_cts->cr >> 8) & 0x7f );
}

/**
 * \brief CTS ���ͬ������
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_swsync_set (amhw_hc32f07x_cts_t *p_hw_cts)
{
    p_hw_cts->cr |= (0x01 << 7);
}

/**
 * \brief CTS �Զ�΢��ʹ��
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_auto_trim_enable (amhw_hc32f07x_cts_t *p_hw_cts)
{
    p_hw_cts->cr |= (0x01 << 6);
}

/**
 * \brief CTS �Զ�΢������
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_auto_trim_disable (amhw_hc32f07x_cts_t *p_hw_cts)
{
    p_hw_cts->cr &= ~(0x01 << 6);
}

/**
 * \brief CTS Ƶ����������/��ʱ��ʹ��
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_cen_enable (amhw_hc32f07x_cts_t *p_hw_cts)
{
    p_hw_cts->cr |= (0x01 << 5);
}

/**
 * \brief CTS Ƶ����������/��ʱ������
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_cen_disable (amhw_hc32f07x_cts_t *p_hw_cts)
{
    p_hw_cts->cr &= ~(0x01 << 5);
}

/**
 * \biref �ж�ʹ�ܿ���
 */
#define AMHW_HC32F07X_CTS_INT_CAPIE  (0X01 << 4U)  /**< \brief ��ʱ��ģʽ�����ж�ʹ�� */
#define AMHW_HC32F07X_CTS_INT_UDFIE  (0X01 << 3U)  /**< \brief ������������ж�ʹ�� */
#define AMHW_HC32F07X_CTS_INT_ERRIE  (0X01 << 2U)  /**< \brief У׼�����ж�ʹ�� */
#define AMHW_HC32F07X_CTS_INT_WARNIE (0X01 << 1U)  /**< \brief У׼�����ж�ʹ�� */
#define AMHW_HC32F07X_CTS_INT_OKIE   (0X01 << 0U)  /**< \brief У׼�����ж�ʹ�� */

/**
 * \brief CTS �ж�ʹ��
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  ie        : �ο������궨��AMHW_HC32F07X_CTS_INT_
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_int_enable (amhw_hc32f07x_cts_t *p_hw_cts,
	                                 uint8_t              ie)
{
    p_hw_cts->cr |= ie;
}

/**
 * \brief CTS �жϽ���
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  ie        : �ο������궨��AMHW_HC32F07X_CTS_INT_
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_int_disable (amhw_hc32f07x_cts_t *p_hw_cts,
	                                 uint8_t              ie)
{
    p_hw_cts->cr &= ~ie;
}

/**
 * \brief CTS У׼ʱ��
 */
typedef enum amhw_hc32f07x_cts_clksrc {
    AMHW_HC32F07X_CTS_CLKSRC_RC48M = 0,
    AMHW_HC32F07X_CTS_CLKSRC_RCH ,
    AMHW_HC32F07X_CTS_CLKSRC_XTH ,
    AMHW_HC32F07X_CTS_CLKSRC_RFFCLK ,    /* ���޶�ʱ��ģʽʹ�� */
}amhw_hc32f07x_cts_clksrc_t;

/**
 * \brief CTS ʱ��ѡ��
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  src        : �ο�ö����amhw_hc32f07x_cts_clksrc_t
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_clksrc_set (amhw_hc32f07x_cts_t        *p_hw_cts,
                                   amhw_hc32f07x_cts_clksrc_t  src)
{
    p_hw_cts->cfgr = (p_hw_cts->cfgr & ~(0x03u << 30)) | 
                      (src << 30);
}

/**
 * \brief CTS �ź�Դ
 */
typedef enum amhw_hc32f07x_cts_refsrc {
    AMHW_HC32F07X_CTS_REFSRC_USB_SOF = 0,
    AMHW_HC32F07X_CTS_REFSRC_XTL,
    AMHW_HC32F07X_CTS_REFSRC_GPIO,
    AMHW_HC32F07X_CTS_REFSRC_LPTIM_TOG,
}amhw_hc32f07x_cts_refsrc_t;

/**
 * \brief CTS �ź�Դѡ��
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  src        : �ο�ö����amhw_hc32f07x_cts_refsrc_t
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_refsrc_set (amhw_hc32f07x_cts_t   *p_hw_cts,
                                   amhw_hc32f07x_cts_refsrc_t  src)
{
    p_hw_cts->cfgr = (p_hw_cts->cfgr & ~(0x03u << 28)) | 
                      (src << 28);
}

/**
 * \brief CTS ͬ������
 */
typedef enum amhw_hc32f07x_cts_pol {
    AMHW_HC32F07X_CTS_POL_UP = 0,
    AMHW_HC32F07X_CTS_POL_DOWN,
}amhw_hc32f07x_cts_pol_t;

/**
 * \brief CTS �ź�Դѡ��
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  src        : �ο�ö����amhw_hc32f07x_cts_pol_t
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_pol_set (amhw_hc32f07x_cts_t   *p_hw_cts,
	                              amhw_hc32f07x_cts_pol_t  src)
{
    p_hw_cts->cfgr = (p_hw_cts->cfgr & ~(0x01 << 27)) | 
	                   (src << 27);
}

/**
 * \brief CTS Ԥ��Ƶ
 */
typedef enum amhw_hc32f07x_cts_prs {
    AMHW_HC32F07X_CTS_PRS_0DIV = 0,    /* ����Ƶ */
    AMHW_HC32F07X_CTS_PRS_2DIV,        /* 2��Ƶ */
    AMHW_HC32F07X_CTS_PRS_4DIV,        /* 4��Ƶ */
    AMHW_HC32F07X_CTS_PRS_8DIV,        /* 8��Ƶ */
    AMHW_HC32F07X_CTS_PRS_16DIV,       /* 16��Ƶ */
    AMHW_HC32F07X_CTS_PRS_32DIV,       /* 32��Ƶ */
    AMHW_HC32F07X_CTS_PRS_64DIV,       /* 64��Ƶ */
    AMHW_HC32F07X_CTS_PRS_256DIV,      /* 256��Ƶ */
}amhw_hc32f07x_cts_prs_t;

/**
 * \brief CTS Ԥ��Ƶ����
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  src        : �ο�ö����amhw_hc32f07x_cts_pol_t
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_prs_set (amhw_hc32f07x_cts_t   *p_hw_cts,
                                amhw_hc32f07x_cts_prs_t  src)
{
    p_hw_cts->cfgr = (p_hw_cts->cfgr & ~(0x07 << 24)) | 
                      (src << 24);
}

/**
 * \brief CTS Ƶ�������ֵ����
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  value     : �����ֵ
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_felim_set (amhw_hc32f07x_cts_t   *p_hw_cts,
	                                uint8_t                value)
{
    p_hw_cts->cfgr = (p_hw_cts->cfgr & ~(0xff << 16)) | 
	                   (value << 16);
}

/**
 * \brief CTS ����������ֵ
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  value     : ����ֵ
 *
 * \return  ��
 */
am_static_inline
void amhw_hc32f07x_cts_arr_set (amhw_hc32f07x_cts_t   *p_hw_cts,
	                                uint16_t                value)
{
    p_hw_cts->cfgr = (p_hw_cts->cfgr & ~(0xffff << 0)) | 
	                   (value << 0);
}

/**
 * \brief CTS Ƶ������ֵ��ȡ
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return  Ƶ������ֵ
 */
am_static_inline
uint16_t amhw_hc32f07x_cts_fecap_get (amhw_hc32f07x_cts_t   *p_hw_cts)
{
    return  ((p_hw_cts->isr >> 16) & 0xffff);
}

/**
 * \brief CTS Ƶ������
 */
typedef enum amhw_hc32f07x_cts_dir {
    AMHW_HC32F07X_CTS_DIR_UP = 0,   /* ������������ʵ��Ƶ�ʸ���Ŀ��Ƶ�� */
    AMHW_HC32F07X_CTS_DIR_DOWN ,    /* �ݼ���������ʵ��Ƶ�ʵ���Ŀ��Ƶ�� */
}amhw_hc32f07x_cts_dir_t;

/**
 * \brief CTS Ƶ�������ȡ
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 *
 * \return  �ο�ö����amhw_hc32f07x_cts_dir_t
 */
am_static_inline
amhw_hc32f07x_cts_dir_t 
amhw_hc32f07x_cts_dir_get (amhw_hc32f07x_cts_t   *p_hw_cts)
{
    return  (amhw_hc32f07x_cts_dir_t)((p_hw_cts->isr >> 15) & 0x01);
}

/**
 * \biref ��־����
 */
#define AMHW_HC32F07X_CTS_FLAG_OVF  (10U)  /**< \brief TRIM��� */
#define AMHW_HC32F07X_CTS_FLAG_MISS (9U)  /**< \brief У׼�ο�ͬ����ʧ */
#define AMHW_HC32F07X_CTS_FLAG_ERR  (8U)  /**< \brief У׼���� */

#define AMHW_HC32F07X_CTS_FLAG_CAPF  (4U)  /**< \brief �����־ */
#define AMHW_HC32F07X_CTS_FLAG_UDFF  (3U)  /**< \brief �������������־ */
#define AMHW_HC32F07X_CTS_FLAG_ERRF  (2U)  /**< \brief �����־ */
#define AMHW_HC32F07X_CTS_FLAG_WARNF (1U)  /**< \brief У׼�����־ */
#define AMHW_HC32F07X_CTS_FLAG_OKF   (0U)  /**< \brief У׼������־ */

/**
 * \brief CTS ��־��ȡ
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  flag      : �ο��궨��AMHW_HC32F07X_CTS_FLAG
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f07x_cts_flag_get (amhw_hc32f07x_cts_t   *p_hw_cts,
                                      uint16_t              flag)
{
    return  ((p_hw_cts->isr >> flag) & 0x01)? AM_TRUE : AM_FALSE;
}

/**
 * \biref ״̬�������
 */
#define AMHW_HC32F07X_CTS_CLR_CAPC  (1U << 4)  /**< \brief �����־��� */
#define AMHW_HC32F07X_CTS_CLR_UDFC  (1U << 3)  /**< \brief Ԥ��ͬ����־��� */
#define AMHW_HC32F07X_CTS_CLR_ERRC  (1U << 2)  /**< \brief У׼�����־��� */
#define AMHW_HC32F07X_CTS_CLR_WARNC (1U << 1)  /**< \brief У׼�����־��� */
#define AMHW_HC32F07X_CTS_CLR_OKC   (1U << 0)  /**< \brief У׼������־��� */

/**
 * \brief CTS ״̬���
 *
 * \papcnt[in]  p_hw_cts  : ָ��CTS�Ĵ����ṹ���ָ��
 * \papcnt[in]  flag      : �ο��궨��AMHW_HC32F07X_CTS_CLR
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f07x_cts_flag_clr (amhw_hc32f07x_cts_t   *p_hw_cts,
                                uint8_t              clr)
{
    p_hw_cts->icr &= ~clr;
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__GNUC__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __AMHW_HC32f07x_CTS_H */

#endif

/* end of file */

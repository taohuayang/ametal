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
 * \brief ʱ��У׼ģ�飨CLKTRIM��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29
 *
 * \endinternal
 */

#ifndef __AMHW_ZLG118_CLKTRIM_H
#define __AMHW_ZLG118_CLKTRIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zlg_if_clktrim
 * \copydoc amhw_zlg_clktrim.h
 * @{
 */

/**
 * \brief CLKTRIM - Register Layout Typedef
 */
typedef struct amhw_zlg_clktrim {
    __IO uint32_t cr;        /**< \brief ���üĴ��� */
    __IO uint32_t refcon;    /**< \brief �ο���������ֵ���üĴ��� */
    __I  uint32_t refcnt;    /**< \brief �ο�������ֵ�Ĵ��� */
    __I  uint32_t calcnt;    /**< \brief У׼������ֵ�Ĵ��� */
    __IO uint32_t ifr;       /**< \brief �жϱ�־λ�Ĵ��� */
    __IO uint32_t iclr;      /**< \brief �жϱ�־λ����Ĵ��� */
    __IO uint32_t calcon;    /**< \brief У׼���������ֵ���üĴ��� */
} amhw_zlg118_clktrim_t;

/* ��У׼/���ʱ��Դ */
typedef enum amhw_clktrim_calclk_sel {
    AMHW_CLKTRIM_CALCLK_RCH = 0x0,
    AMHW_CLKTRIM_CALCLK_XTH = 0x1,
    AMHW_CLKTRIM_CALCLK_RCL = 0x2,
    AMHW_CLKTRIM_CALCLK_XTL = 0x3,
    AMHW_CLKTRIM_CALCLK_PLL = 0x10
} amhw_clktrim_calclk_sel_t;

/* �ο�ʱ��Դ */
typedef enum amhw_clktrim_refclk_sel {
    AMHW_CLKTRIM_REFCLK_RCH        = 0x0,
    AMHW_CLKTRIM_REFCLK_XTH        = 0x1,
    AMHW_CLKTRIM_REFCLK_RCL        = 0x2,
    AMHW_CLKTRIM_REFCLK_XTL        = 0x3,
    AMHW_CLKTRIM_REFCLK_IRC10K     = 0x4,
    AMHW_CLKTRIM_REFCLK_EXT_CLK_IN = 0x5
} amhw_clktrim_refclk_sel_t;

typedef enum amhw_clktrim_ifr {
    AMHW_CLKTRIM_STOP      = (1),       /**< \brief �ο�������ֹͣ��־ */
    AMHW_CLKTRIM_CALCNT_OF = (1 << 1),  /**< \brief У׼�����������־ */
    AMHW_CLKTRIM_XTL_FAULT = (1 << 2),  /**< \brief XTL ʧЧ��־ */
    AMHW_CLKTRIM_XTH_FAULT = (1 << 3),  /**< \brief XTH ʧЧ��־ */
    AMHW_CLKTRIM_PLL_FAULT = (1 << 4)   /**< \brief PLL ʧЧ��־ */
} amhw_clktrim_ifr_t;

/**
 * \brief ��У׼/���ʱ��ѡ��
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] calclk_sel   : ��У׼/���ʱ��ѡ��
 *
 * retval : none
 */
am_static_inline
void amhw_zlg118_clktrim_calclk_sel (amhw_zlg118_clktrim_t      *p_hw_clktrim,
                                     amhw_clktrim_calclk_sel_t   calclk_sel)
{
    p_hw_clktrim->cr &= 0x4f;
    p_hw_clktrim->cr |= calclk_sel << 4;
}

/**
 * \brief �ж�ʹ�ܿ���
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] enable       : ʹ��ѡ��   1��ʹ��
 *                                    0������
 *
 * retval : none
 */
am_static_inline
void amhw_zlg118_clktrim_int_enable (amhw_zlg118_clktrim_t *p_hw_clktrim,
                                     uint8_t                enable)
{
    if(enable != 0 && enable != 1) {
        return;
    }
    p_hw_clktrim->cr &= ~(1 << 7);
    p_hw_clktrim->cr |= (enable << 7);
}

/**
 * \brief ���ģʽʹ�ܿ���
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] enable       : ʹ��ѡ��   1��ʹ��
 *                                    0������
 *
 * retval : none
 */
am_static_inline
void amhw_zlg118_clktrim_mon_enable (amhw_zlg118_clktrim_t *p_hw_clktrim,
                                     uint8_t                enable)
{
    if(enable != 0 && enable != 1) {
        return;
    }
    p_hw_clktrim->cr &= ~(1 << 6);
    p_hw_clktrim->cr |= (enable << 6);
}

/**
 * \brief �ο�ʱ��ѡ��
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] refclk_sel   : ��У׼/���ʱ��ѡ��
 *
 * retval : none
 */
am_static_inline
void amhw_zlg118_clktrim_refclk_sel (amhw_zlg118_clktrim_t      *p_hw_clktrim,
                                     amhw_clktrim_refclk_sel_t   refclk_sel)
{
    p_hw_clktrim->cr &= ~0x0e;
    p_hw_clktrim->cr |= (refclk_sel << 1);
}

/**
 * \brief У׼/��⿪ʼ����
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] start        : ��ʼѡ��   1����ʼ
 *                                    0��ֹͣ
 *
 * retval : none
 */
am_static_inline
void amhw_zlg118_clktrim_trim_start (amhw_zlg118_clktrim_t *p_hw_clktrim,
                                     uint8_t                start)
{
    if(start != 0 && start != 1) {
        return;
    }
    p_hw_clktrim->cr &= ~1;
    p_hw_clktrim->cr |= start;
}

/**
 * \brief �ο���������ֵ����
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] rcntval      : �ο���������ʼֵ
 *
 * retval : none
 */
am_static_inline
void amhw_zlg118_clktrim_refcon_set (amhw_zlg118_clktrim_t *p_hw_clktrim,
                                     uint16_t               rcntval)
{
    p_hw_clktrim->refcon = rcntval;
}

/**
 * \brief ��ȡ�ο�������ֵ
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 *
 * retval : ������ֵ
 */
am_static_inline
uint16_t amhw_zlg118_clktrim_refcnt_get (amhw_zlg118_clktrim_t *p_hw_clktrim)
{
    return p_hw_clktrim->refcnt;
}

/**
 * \brief ��ȡУ׼������ֵ
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 *
 * retval : ������ֵ
 */
am_static_inline
uint16_t amhw_zlg118_clktrim_calcnt_get (amhw_zlg118_clktrim_t *p_hw_clktrim)
{
    return p_hw_clktrim->calcnt;
}

/**
 * \brief ��ȡ�жϱ�־
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] ifr          : �жϱ�־
 *
 * retval : 0�����жϱ�־
 *         ��0�����жϱ�־
 */
am_static_inline
uint8_t amhw_zlg118_clktrim_ifr_get (amhw_zlg118_clktrim_t *p_hw_clktrim,
                                     amhw_clktrim_ifr_t     ifr)
{
    return p_hw_clktrim->ifr & ifr;
}

/**
 * \brief ����жϱ�־
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] ifr          : �жϱ�־
 *
 * retval : AM_OK���ɹ�
 *         -AM_EPERM������������
 */
am_static_inline
uint8_t amhw_zlg118_clktrim_ifr_clear (amhw_zlg118_clktrim_t *p_hw_clktrim,
                                       amhw_clktrim_ifr_t     ifr)
{
    if(ifr < 4) {
        return AM_EPERM;
    }
    p_hw_clktrim->ifr &= ~ifr;
    return AM_OK;
}

/**
 * \brief У׼���������ֵ����
 *
 * \param[in] p_hw_clktrim : ָ��clktrim�Ĵ�����ַ��ָ��
 * \param[in] ccntval      : У׼���������ֵ
 *
 * retval : none
 */
am_static_inline
void amhw_zlg118_clktrim_calcon_set (amhw_zlg118_clktrim_t *p_hw_clktrim,
                                     uint16_t               ccntval)
{
    p_hw_clktrim->calcon = ccntval;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG118_CLKTRIM_H */

/* end of file */

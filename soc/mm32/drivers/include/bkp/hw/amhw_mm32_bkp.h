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
 * \brief ���ݼĴ����ӿ�
 *
 * \internal
 * \par History
 * - 1.00 17-04-17  nwt, first implementation
 * \endinternal
 */

#ifndef __AMHW_MM32_BKP_H
#define __AMHW_MM32_BKP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_mm32_if_bkp
 * \copydoc amhw_mm32_bkp.h
 * @{
 */

/** \brief CSR register CTE bit mask */
#define AMHW_BKP_CSR_CTE_SET       ((uint16_t)0x0001)

/** \brief CSR register CTI bit mask */
#define AMHW_BKP_CSR_CTI_SET       ((uint16_t)0x0002)

/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef struct amhw_mm32_bkp {
    __I  uint32_t reserve;        /**< \brief ���� */
    __IO uint32_t reserve_dr[10]; /**< \brief �����������ݼĴ���.(����) */
    __IO uint32_t rtc_cr;         /**< \brief rtc���ƼĴ��� */
    __IO uint32_t cr;             /**< \brief BKP���ƼĴ��� */
    __IO uint32_t csr;            /**< \brief ʱ�Ӽ��״̬�Ĵ��� */
    __I  uint32_t reserve1[6];    /**< \brief ���� */
    __IO uint32_t dr[10];         /**< \brief �����������ݼĴ���, offest 0x50 */
} amhw_mm32_bkp_t;

/**
 * \brief Clears Tamper Pin Event pending flag.
 *
 * \param[in] p_hw_bkp : ָ��ϵͳ���üĴ������ָ��
 * \param[in] flag     : see AMHW_BKP_CSR_CTE_SET or AMHW_BKP_CSR_CTI_SET
 *
 * \return None
 */
am_static_inline
void amhw_mm32_bkp_clear_flag (amhw_mm32_bkp_t *p_hw_bkp, uint32_t flag)
{
    /* Set CTE bit to clear Tamper Pin Event flag */
    p_hw_bkp->csr |= flag;
}

/**
 * \brief д�����������ݼĴ���
 *
 * \param[in] p_hw_bkp ��ָ��ϵͳ���üĴ������ָ��
 * \param[in] index    : �����������ݼĴ���������ֵΪ 0 ~ 9
 * \param[in] value    : д�뱸���������ݼĴ�����ֵ��ֵΪ 0 ~ 65536
 *
 * \return ��
 */
am_static_inline
void amhw_mm32_bkp_dr_write (amhw_mm32_bkp_t    *p_hw_bkp,
                            uint8_t            index,
                            uint16_t           value)
{
    p_hw_bkp->dr[index] = value;
}

/**
 * \brief д�����������ݼĴ���
 *
 * \param[in] index    : �����������ݼĴ���������ֵΪ 0 ~ 9
 * \param[in] p_hw_bkp ��ָ��ϵͳ���üĴ������ָ��
 *
 * \return ���ض�Ӧ���ݼĴ�����ֵ
 */
am_static_inline
uint32_t amhw_mm32_bkp_dr_read (amhw_mm32_bkp_t *p_hw_bkp, uint8_t index)
{
    return (p_hw_bkp->dr[index]);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MM32_BKP_H */

/* end of file */

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
 * \brief ��Դ����ӿ�
 *
 * \internal
 * \par History
 * - 1.00 17-04-17  nwt, first implementation
 * \endinternal
 */

#ifndef __AMHW_MM32_PWR_H
#define __AMHW_MM32_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_mm32_if_pwr
 * \copydoc amhw_mm32_pwr.h
 * @{
 */

/**
 * \name �������λ�뻽��λ���
 * @{
 */

#define AM_MM32_STANDBY_FLAG_CLEAR  (1UL << 3)
#define AM_MM32_WAKEUP_FLAG_CLEAR   (1UL << 2)

/** @} */

/**
 * \name �������˯��ģʽ
 * @{
 */

#define AM_MM32_PDDS_STANDBY_MODE  1
#define AM_MM32_PDDS_STOP_MODE     0

/** @} */

/**
 * \name Դ��ѹ�������PVD��ʹ��
 * @{
 */
#define AM_MM32_PVDE_ENABLE        1
#define AM_MM32_PVDE_DISABLE       0

/** @} */

/**
 * \name BKP���ݼĴ�������ʹ��
 * @{
 */
#define AM_MM32_BKP_ENABLE         1
#define AM_MM32_BKP_DISABLE        0

/** @} */

/**
 * \name WAKE_UP��������ʹ��
 * @{
 */
#define AM_MM32_WAKEUP_ENABLE      1
#define AM_MM32_WAKEUP_DISABLE     0

/** @} */

/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef struct amhw_mm32_pwr {
    __IO  uint32_t cr;          /**< \brief ��Դ���ƼĴ��� */
    __IO  uint32_t csr;         /**< \brief ��Դ����/״̬�Ĵ��� */
} amhw_mm32_pwr_t;

/**
 * \brief PVD��ƽѡ��
 */
typedef enum amhw_mm32_pvd_lever_set {
    AMHW_MM32_PVD_LEVER_1_8V  = 0,  /**< \brief 1.8V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_2_1V  = 1,  /**< \brief 2.1V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_2_4V  = 2,  /**< \brief 2.4V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_2_7V  = 3,  /**< \brief 2.7V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_3_0V  = 4,  /**< \brief 3.0V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_3_3V  = 5,  /**< \brief 3.3V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_3_6V  = 6,  /**< \brief 3.6V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_3_9V  = 7,  /**< \brief 3.9V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_4_2V  = 8,  /**< \brief 4.2V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_4_5V  = 9,  /**< \brief 4.5V PVD����ѹ */
    AMHW_MM32_PVD_LEVER_4_8V  = 10, /**< \brief 4.8V PVD����ѹ */
} amhw_mm32_pvd_lever_set_t;

/**
 * \brief ��Դ����״̬��־
 */
typedef enum amhw_mm32_pwr_status_flag {
    AMHW_MM32_PVD_OUTPUT_FLAG  = (1UL << 2),  /**< \brief PVD�����־λ */
    AMHW_MM32_PVD_SBF_FLAG     = (1UL << 1),  /**< \brief ������־λ */
    AMHW_MM32_PVD_WUF_FLAG     = (1UL << 0),  /**< \brief ���ѱ�־λ */
} amhw_mm32_pwr_status_flag_t;

/**
 * \brief ��ȵ���ģʽѡ��
 *
 * \param[in] pdds_mode �� ��ȵ���ģʽ����,ֵΪ  AM_MM32_PDDS_*_MODE ��һ���
 *                         (# AM_MM32_PDDS_STOP_MODE)
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_mm32_pwr_pdds_mode_set (amhw_mm32_pwr_t *p_hw_pwr, uint8_t pdds_mode)
{
    AM_BITS_SET(p_hw_pwr->cr, 0, 2, (pdds_mode << 1));
}

/**
 * \brief PVD��ѹ���ʹ��
 *
 * \param[in] p_hw_pwr    ��ָ���Դ���ƼĴ������ָ��
 * \param[in] pvd_enable  ����ѹ���ʹ�ܣ�ֵΪ  AM_MM32_PVDE_* ��һ���
 *                           (# AM_MM32_PVDE_ENABLE)
 *
 * \return ��
 */
am_static_inline
void amhw_mm32_pwr_pvd_detect_enable (amhw_mm32_pwr_t *p_hw_pwr, uint8_t pvd_enable)
{
    AM_BIT_MODIFY(p_hw_pwr->cr, 4, pvd_enable);
}

/**
 * \brief ���ʱ��ݼĴ���ʹ��
 *
 * \param[in] p_hw_pwr    ��ָ���Դ���ƼĴ������ָ��
 * \param[in] bkp_enable  ����ѹ���ʹ�ܣ�ֵΪ  AM_MM32_BKP_* ��һ���
 *                           (# AM_MM32_BKP_ENABLE)
 *
 * \return ��
 */
am_static_inline
void amhw_mm32_pwr_bkp_access_enable (amhw_mm32_pwr_t *p_hw_pwr, uint8_t bkp_enable)
{
    AM_BIT_MODIFY(p_hw_pwr->cr, 8, bkp_enable);
}

/**
 * \brief ���������־λ�뻽��λ
 *
 * \param[in] p_hw_pwr    ��ָ���Դ���ƼĴ������ָ��
 * \param[in] status_flg  ����־λ���ѡ��ֵΪ  AM_MM32_*_FLAG_CLEAR ��һ���
 *                           (# AM_MM32_STANDBY_FLAG_CLEAR)
 *
 * \return ��
 */
am_static_inline
void amhw_mm32_pwr_stauts_flag_clear (amhw_mm32_pwr_t *p_hw_pwr, uint8_t status_flg)
{
    AM_BIT_SET_MASK(p_hw_pwr->cr, status_flg);
}

/**
 * \brief PV����ѹѡ��
 *
 * \param[in] p_hw_pwr ��ָ���Դ���ƼĴ������ָ��
 * \param[in] pvd_lever����ѹ��ⷶΧѡ��, ֵΪ amhw_mm32_pvd_lever_set_t ��һö�����͵�ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_mm32_pvd_lever_set (amhw_mm32_pwr_t *p_hw_pwr, uint8_t pvd_lever)
{
    AM_BITS_SET(p_hw_pwr->cr, 9, 4, pvd_lever);
}

/**
 * \brief ʹ��WAKE_UP����
 *
 * \param[in] p_hw_pwr ��ָ���Դ���ƼĴ������ָ��
 * \param[in] wakeup_en����������ʹ�����ֵΪ AM_MM32_WAKEUP_* ��һ��꣬
 *                      (# AM_MM32_WAKEUP_ENABLE)
 *
 * \return ��
 */
am_static_inline
void amhw_mm32_wake_up_enable (amhw_mm32_pwr_t *p_hw_pwr, uint8_t wakeup_en)
{
    p_hw_pwr->csr |= (wakeup_en << 8);
}

/**
 * \brief ��ȡ��Դ�������״̬λ
 *
 * \param[in] p_hw_pwr   ��ָ���Դ���ƼĴ������ָ��
 * \param[in] status_flag����Դ����״̬λ��ֵΪ amhw_mm32_pwr_status_flag_t ��һö������
 *
 * \return ������ֵ��Ϊ0ʱ������ñ�־λ��1
 */
am_static_inline
uint32_t amhw_mm32_pwr_csr_status_get (amhw_mm32_pwr_t *p_hw_pwr, uint8_t status_flag)
{
    return p_hw_pwr->csr & status_flag;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MM32_PWR_H */

/* end of file */

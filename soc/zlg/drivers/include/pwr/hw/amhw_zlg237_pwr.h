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
 * - 1.00 19-07-18  zp, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG237_PWR_H
#define __AMHW_ZLG237_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"

/**
 * \addtogroup amhw_zlg237_if_pwr
 * \copydoc amhw_zlg237_pwr.h
 * @{
 */

/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef struct amhw_zlg237_pwr {
    __IO  uint32_t cr;          /**< \brief ��Դ���ƼĴ��� */
    __IO  uint32_t csr;         /**< \brief ��Դ����/״̬�Ĵ��� */
    __I   uint32_t reserve[2];  /**< \brief ���� */
    __IO  uint32_t ldo;         /**< \brief Ƭ�� LDO ����ģʽ�����ѹ���ƼĴ��� */
    __IO  uint32_t ldo_stop;    /**< \brief Ƭ�� LDO STOPģʽ�����ѹ���ƼĴ��� */
} amhw_zlg237_pwr_t;

/**
 * \name �������˯��ģʽ ��ͣ��ģʽ�£���ѹ��ѹ������Э����������鿴ԭ�ֲᣩ
 * @{
 */
#define AM_ZLG237_PDDS_STOP_MODE_LDO_ON      0 /* 00 ͣ��ģʽ  ��ѹ��ѹ��(LDO)����*/
#define AM_ZLG237_PDDS_STOP_MODE_LDO_OFF     1 /* 01 ͣ��ģʽ  ��ѹ��ѹ��(LDO)�͹���ģʽ*/
#define AM_ZLG237_PDDS_STANDBY_MODE_LDO_ON   2 /* 10 ����ģʽ */
#define AM_ZLG237_PDDS_STANDBY_MODE_LDO_OFF  3 /* 11 ����ģʽ */
/** @} */

/**
 * \brief ��ȵ���ģʽѡ��
 *
 * \param[in] mode      �� ��ȵ���ģʽ����,ֵΪ  AM_ZLG237_PDDS_STOP_MODE_LDO_ON     ��
 *                                       AM_ZLG237_PDDS_STOP_MODE_LDO_OFF    ��
 *                                       AM_ZLG237_PDDS_STANDBY_MODE_LDO_ON  ��
 *                                       AM_ZLG237_PDDS_STANDBY_MODE_LDO_OFF
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_pwr_pdds_lpds_mode_set (amhw_zlg237_pwr_t *p_hw_pwr,
                                         uint8_t            mode)
{
    p_hw_pwr->cr = (p_hw_pwr->cr & (~(3ul << 0))) | (mode << 0) ;
}

/**
 * \name �������λ�뻽��λ���
 * @{
 */
#define AM_ZLG237_STANDBY_FLAG_CLEAR  (1UL << 3)
#define AM_ZLG237_WAKEUP_FLAG_CLEAR   (1UL << 2)
/** @} */
/**
 * \brief ���������־λ�뻽��λ
 *
 * \param[in] p_hw_pwr    ��ָ���Դ���ƼĴ������ָ��
 * \param[in] status_flg  ����־λ���ѡ��ֵΪ  AM_ZLG237_*_FLAG_CLEAR ��һ���
 *                           (# AM_ZLG237_STANDBY_FLAG_CLEAR)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_pwr_stauts_flag_clear (amhw_zlg237_pwr_t *p_hw_pwr,
                                        uint8_t            status_flg)
{
    p_hw_pwr->cr |= status_flg;
}


/**
 * \name Դ��ѹ�������PVD��ʹ��
 * @{
 */
#define AM_ZLG237_PVDE_ENABLE        1
#define AM_ZLG237_PVDE_DISABLE       0
/** @} */
/**
 * \brief PVD��ѹ���ʹ��
 *
 * \param[in] p_hw_pwr    ��ָ���Դ���ƼĴ������ָ��
 * \param[in] pvd_enable  ����ѹ���ʹ�ܣ�ֵΪ  AM_ZLG237_PVDE_* ��һ���
 *                           (# AM_ZLG237_PVDE_ENABLE)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_pwr_pvd_detect_enable (amhw_zlg237_pwr_t *p_hw_pwr,
                                        uint8_t            pvd_enable)
{
    p_hw_pwr->cr = (p_hw_pwr->cr & (~(1ul << 4))) | (pvd_enable << 4) ;
}

/**
 * \brief PVD��ƽѡ��
 */
typedef enum amhw_zlg237_pvd_lever_set {
    AMHW_ZLG237_PVD_LEVER_2_2V  = 0,  /**< \brief 2.2V PVD����ѹ */
    AMHW_ZLG237_PVD_LEVER_2_3V  = 1,  /**< \brief 2.3V PVD����ѹ */
    AMHW_ZLG237_PVD_LEVER_2_4V  = 2,  /**< \brief 2.4V PVD����ѹ */
    AMHW_ZLG237_PVD_LEVER_2_5V  = 3,  /**< \brief 2.5V PVD����ѹ */
    AMHW_ZLG237_PVD_LEVER_2_6V  = 4,  /**< \brief 2.6V PVD����ѹ */
    AMHW_ZLG237_PVD_LEVER_2_7V  = 5,  /**< \brief 2.7V PVD����ѹ */
    AMHW_ZLG237_PVD_LEVER_2_8V  = 6,  /**< \brief 2.8V PVD����ѹ */
    AMHW_ZLG237_PVD_LEVER_2_9V  = 7,  /**< \brief 2.9V PVD����ѹ */
} amhw_zlg237_pvd_lever_set_t;
/**
 * \brief PV����ѹѡ��
 *
 * \param[in] p_hw_pwr ��ָ���Դ���ƼĴ������ָ��
 * \param[in] pvd_lever����ѹ��ⷶΧѡ��, ֵΪ amhw_zlg237_pvd_lever_set_t ��һö�����͵�ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_pvd_lever_set (amhw_zlg237_pwr_t           *p_hw_pwr,
                                amhw_zlg237_pvd_lever_set_t  pvd_lever)
{
    p_hw_pwr->cr = (p_hw_pwr->cr & (~(7ul << 5))) | (pvd_lever << 5) ;
}

/**
 * \name BKP���ݼĴ�������ʹ��
 * @{
 */
#define AM_ZLG237_BKP_ENABLE         1
#define AM_ZLG237_BKP_DISABLE        0
/** @} */
/**
 * \brief ���ʱ��ݼĴ���ʹ��
 *
 * \param[in] p_hw_pwr    ��ָ���Դ���ƼĴ������ָ��
 * \param[in] bkp_enable  ����ѹ���ʹ�ܣ�ֵΪ  AM_ZLG237_BKP_* ��һ���
 *                           (# AM_ZLG237_BKP_ENABLE)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_pwr_bkp_access_enable (amhw_zlg237_pwr_t *p_hw_pwr,
                                        uint8_t            bkp_enable)
{
    p_hw_pwr->cr = (p_hw_pwr->cr & (~(1ul << 8))) | (bkp_enable << 8) ;
}

/**
 * \name WAKE_UP��������ʹ��
 * @{
 */
#define AM_ZLG237_WAKEUP_ENABLE      1
#define AM_ZLG237_WAKEUP_DISABLE     0
/** @} */
/**
 * \brief ʹ��WAKE_UP����
 *
 * \param[in] p_hw_pwr ��ָ���Դ���ƼĴ������ָ��
 * \param[in] wakeup_en����������ʹ�����ֵΪ  AM_ZLG237_WAKEUP_ENABLE  ��
 *                                      AM_ZLG237_WAKEUP_DISABLE
 *
 * \return ��
 */
am_static_inline
void amhw_zlg237_wake_up_enable (amhw_zlg237_pwr_t *p_hw_pwr, uint8_t wakeup_en)
{
    p_hw_pwr->csr = (p_hw_pwr->csr & (~(1ul << 8))) | (wakeup_en << 8) ;
}


/**
 * \brief ��Դ����״̬��־
 */
typedef enum amhw_zlg237_pwr_status_flag {
    AMHW_ZLG237_PVD_OUTPUT_FLAG  = (1UL << 2),  /**< \brief PVD�����־λ */
    AMHW_ZLG237_PVD_SBF_FLAG     = (1UL << 1),  /**< \brief ������־λ */
    AMHW_ZLG237_PVD_WUF_FLAG     = (1UL << 0),  /**< \brief ���ѱ�־λ */
} amhw_zlg237_pwr_status_flag_t;
/**
 * \brief ��ȡ��Դ�������״̬λ
 *
 * \param[in] p_hw_pwr   ��ָ���Դ���ƼĴ������ָ��
 * \param[in] status_flag����Դ����״̬λ��ֵΪ amhw_zlg237_pwr_status_flag_t ��һö������
 *
 * \return ������ֵ��Ϊ0ʱ������ñ�־λ��1
 */
am_static_inline
uint32_t amhw_zlg237_pwr_csr_status_get (
    amhw_zlg237_pwr_t *p_hw_pwr, amhw_zlg237_pwr_status_flag_t status_flag)
{
    return p_hw_pwr->csr & status_flag;
}

/**
 * \brief MCU��RUNģʽ�£�Ƭ��LDO�������ѹ
 */
typedef enum amhw_zlg237_pwr_ldo_run_set {
    AMHW_ZLG237_PWR_LDO_RUN_1_20V  = 0,     /**< \brief 1.20V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_24V  = 1,     /**< \brief 1.24V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_28V  = 2,     /**< \brief 1.28V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_32V  = 3,     /**< \brief 1.32V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_36V  = 4,     /**< \brief 1.36V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_40V  = 5,     /**< \brief 1.40V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_44V  = 6,     /**< \brief 1.44V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_52V  = 7,     /**< \brief 1.52V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_56V  = 8,     /**< \brief 1.56V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_60V  = 9,     /**< \brief 1.60V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_64V  = 10,    /**< \brief 1.64V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_LDO_RUN_1_68V  = 11,    /**< \brief 1.68V Ƭ�� LDO�����ѹ */
} amhw_zlg237_pwr_ldo_run_t;
/**
 * \brief Ƭ��LDO ����ģʽ�����ѹ���ƼĴ���
 *
 * \param[in] p_hw_pwr   ��ָ���Դ���ƼĴ������ָ��
 * \param[in] status_flag����Դ����״̬λ��ֵΪ amhw_zlg237_pwr_ldo_run_t ��һö������
 *
 * \note �����Ĵ�������λ����оƬ�ڲ����ԼĴ�������ֹ�ı����ʼֵ������оƬ���ܿ����쳣��
 *
 * \return   AM_OK   :���óɹ���
 *           AM_ERROR������ʧ�ܣ���������
 */
am_static_inline
int amhw_zlg237_pwr_ldo_run_set (
    amhw_zlg237_pwr_t *p_hw_pwr, amhw_zlg237_pwr_ldo_run_t ldo_run_vol)
{
    if((ldo_run_vol & 0xful) <= AMHW_ZLG237_PWR_LDO_RUN_1_68V) {

        /* ���ݲ�������Ϊö�����ͱ��������ܽ��ж�Ӧ���� */
        p_hw_pwr->ldo = (p_hw_pwr->ldo & (~(0xful << 0))) |
                        ((ldo_run_vol & 0xful) << 0) ;

        return AM_OK;
    } else {

        return AM_ERROR;
    }
}

/**
 * \brief MCU��STOPģʽ�£�Ƭ��LDO�������ѹ
 */
typedef enum amhw_zlg237_pwr_ldo_stop_set {
    AMHW_ZLG237_PWR_STOP_1_20V  = 0,     /**< \brief 1.20V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_24V  = 1,     /**< \brief 1.24V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_28V  = 2,     /**< \brief 1.28V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_32V  = 3,     /**< \brief 1.32V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_36V  = 4,     /**< \brief 1.36V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_40V  = 5,     /**< \brief 1.40V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_44V  = 6,     /**< \brief 1.44V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_52V  = 7,     /**< \brief 1.52V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_56V  = 8,     /**< \brief 1.56V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_60V  = 9,     /**< \brief 1.60V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_64V  = 10,    /**< \brief 1.64V Ƭ�� LDO�����ѹ */
    AMHW_ZLG237_PWR_STOP_1_68V  = 11,    /**< \brief 1.68V Ƭ�� LDO�����ѹ */
} amhw_zlg237_pwr_ldo_stop_set_t;
/**
 * \brief Ƭ��LDO STOPģʽģʽ�����ѹ���ƼĴ���
 *
 * \param[in] p_hw_pwr   ��ָ���Դ���ƼĴ������ָ��
 * \param[in] status_flag����Դ����״̬λ��
 *                         ֵΪ amhw_zlg237_pwr_ldo_stop_set_t ��һö������
 *
 * \note �����Ĵ�������λ����оƬ�ڲ����ԼĴ�������ֹ�ı����ʼֵ������оƬ���ܿ����쳣��
 *
 * \return   AM_OK   :���óɹ���
 *           AM_ERROR������ʧ�ܣ���������
 */
am_static_inline
int amhw_zlg237_pwr_ldo_stop_set (
    amhw_zlg237_pwr_t *p_hw_pwr, amhw_zlg237_pwr_ldo_stop_set_t ldo_stop_vol)
{
    if((ldo_stop_vol & 0xful) <= AMHW_ZLG237_PWR_STOP_1_68V) {

        /* ���ݲ�������Ϊö�����ͱ��������ܽ��ж�Ӧ���� */
        p_hw_pwr->ldo_stop = (p_hw_pwr->ldo_stop & (~(0xful << 0))) |
                             ((ldo_stop_vol & 0xful) << 0) ;

        return AM_OK;
    }
    return AM_ERROR;
}

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG237_PWR_H */

/* end of file */

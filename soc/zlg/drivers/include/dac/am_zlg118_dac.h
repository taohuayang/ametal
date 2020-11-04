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
 * \brief DAC����������DAC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-24
 * \endinternal
 */

#ifndef  __AM_ZLG118_DAC_H
#define  __AM_ZLG118_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_dac.h"

/**
 * \addtogroup am_zlg118_if_dac
 * \copydoc am_zlg118_dac.h
 * @{
 */

/**
 * \brief DAC���ݶ��뷽ʽ
 */
#define AM_ZLG118_DAC_ALIGN_WAY_12_RIGHT 0  /** \brief 12λ�����Ҷ��� */
#define AM_ZLG118_DAC_ALIGN_WAY_12_LEFT  1  /** \brief 12λ��������� */
#define AM_ZLG118_DAC_ALIGN_WAY_8_RIGHT  2  /** \brief 8 λ�����Ҷ��� */

/**
 * \brief DAC������ʽ
 */
#define AM_ZLG118_DAC_CHAN_TIM0_TRGO    (0U)    /** \brief TIM0 */
#define AM_ZLG118_DAC_CHAN_TIM1_TRGO    (1U)    /** \brief TIM1 */
#define AM_ZLG118_DAC_CHAN_TIM2_TRGO    (2U)    /** \brief TIM2 */
#define AM_ZLG118_DAC_CHAN_TIM3_TRGO    (3U)    /** \brief TIM3 */
#define AM_ZLG118_DAC_CHAN_TIM4_TRGO    (4U)    /** \brief TIM4 */
#define AM_ZLG118_DAC_CHAN_TIM5_TRGO    (5U)    /** \brief TIM5 */
#define AM_ZLG118_DAC_CHAN_SOFTWARE_TRG (6U)    /** \brief ������� */
#define AM_ZLG118_DAC_CHAN_EXTER        (7U)    /** \brief �ⲿ�¼����� */

/**
 * \brief DAC�豸��Ϣ
 */
typedef struct am_zlg118_dac_devinfo {

    /** \brief DAC�Ĵ��������ַ */
    uint32_t   dac_reg_base;

    /** \brief DACת������ */
    uint8_t    bits;

    /**
     * \brief DAC�ο���ѹԴ
     */
    uint32_t   vref_rsc;

    /**
     * \brief DAC�ο���ѹ����λ��mV
     *
     * \note �òο���ѹ�ɾ���ĵ�·����
     *
     */
    uint32_t   vref;

    /**
     * \brief DAC���ݶ��뷽ʽ
     */
    uint8_t    align_way;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_zlg118_dac_devinfo_t;

/**
 * \brief DAC�豸ʵ��
 */
typedef struct am_zlg118_dac_dev {

    /** \brief DAC��׼���� */
    am_dac_serv_t               dac_serve;

    /** \brief ָ��DAC�豸��Ϣ��ָ�� */
    const am_zlg118_dac_devinfo_t *p_devinfo;

    /** \brief ��ǰת����ͨ�� */
    uint32_t                    chan;

} am_zlg118_dac_dev_t;

/**
 * \brief DAC��ʼ��
 *
 *
 * \param[in] p_dev     : ָ��DAC�豸��ָ��
 * \param[in] p_devinfo : ָ��DAC�豸��Ϣ��ָ��
 *
 * \return DAC��׼���������� ���Ϊ NULL��������ʼ��ʧ��
 */
am_dac_handle_t am_zlg118_dac_init (am_zlg118_dac_dev_t           *p_dev,
                                    const am_zlg118_dac_devinfo_t *p_devinfo);

/**
 * \brief DACȥ��ʼ��
 *
 *
 * \param[in] handle : DAC�豸�ľ��ֵ
 *
 * \return ��
 */
void am_zlg118_dac_deinit (am_dac_handle_t handle);

/**
 * \brief DAC ������ʽѡ��
 */
int am_zlg118_dac_tri_way_sel (am_dac_handle_t handle, uint32_t tri_way);

/**
 * \brief DAC�������
 *
 * \param[in] handle : �豸���
 *
 * \return : ��
 */
void am_zlg118_dac_soft_tri (am_dac_handle_t handle);

/**
 * \brief DAC ת�����ݻ�ȡ
 */
void am_zlg118_dac_convt_data_get (am_dac_handle_t handle, uint16_t *p_out_data);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG118_DAC_H */

/* end of file */

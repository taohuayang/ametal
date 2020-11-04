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
 * - 1.00 17-08-28  fra, first implementation
 * \endinternal
 */

#ifndef  __AM_MM32_DAC_H
#define  __AM_MM32_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_dac.h"
#include "hw/amhw_mm32_dac.h"

/**
 * \addtogroup am_mm32_if_dac
 * \copydoc am_mm32_dac.h
 * @{
 */
/**
 * \brief DAC�豸��Ϣ
 */
typedef struct am_mm32_dac_devinfo {

    /** \brief DAC�Ĵ��������ַ */
    uint32_t   dac_reg_base;

    /** \brief DACת������ */
    uint8_t    bits;

    /**
     * \brief DAC�ο���ѹ����λ��mV
     *
     * \note �òο���ѹ�ɾ���ĵ�·����
     *
     */
    uint32_t   vref;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_mm32_dac_devinfo_t;

/**
 * \brief DAC�豸ʵ��
 */
typedef struct am_mm32_dac_dev {

    /** \brief DAC��׼���� */
    am_dac_serv_t               dac_serve;

    /** \brief ָ��DAC�豸��Ϣ��ָ�� */
    const am_mm32_dac_devinfo_t *p_devinfo;

    /** \brief ��ǰת����ͨ�� */
    uint32_t                    chan;

} am_mm32_dac_dev_t;

/**
 * \brief DAC��ʼ��
 *
 *
 * \param[in] p_dev     : ָ��DAC�豸��ָ��
 * \param[in] p_devinfo : ָ��DAC�豸��Ϣ��ָ��
 *
 * \return DAC��׼���������� ���Ϊ NULL��������ʼ��ʧ��
 */
am_dac_handle_t am_mm32_dac_init (am_mm32_dac_dev_t           *p_dev,
                                 const am_mm32_dac_devinfo_t *p_devinfo);

/**
 * \brief DACȥ��ʼ��
 *
 *
 * \param[in] handle : DAC�豸�ľ��ֵ
 *
 * \return ��
 */
void am_mm32_dac_deinit (am_dac_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_MM32_DAC_H */

/* end of file */

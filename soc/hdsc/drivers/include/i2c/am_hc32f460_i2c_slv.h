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
 * \brief I2C�ӻ�����������I2C�ӻ���׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-06  vir, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG_I2C_SLV_H
#define __AM_ZLG_I2C_SLV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_int.h"
#include "am_i2c_slv.h"
#include "am_softimer.h"

/**
 * \addtogroup am_zlg_if_i2c_slv
 * \copydoc am_hc32f460_i2c_slv.h
 * @{
 */

/**
 * \brief I2C�豸��Ϣ�����ṹ��
 */
typedef struct am_hc32f460_i2c_slv_devinfo {

    /** \brief I2C �Ĵ������ַ */
    uint32_t  i2c_regbase;

    /** \brief ʱ��ID */
    int       clk_num;

    /** \brief I2C ���������жϺ� */
    uint16_t  inum;

    /** \brief I2C���� */
    uint32_t  speed;

    /** \brief ƽ̨��ʼ������ */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_hc32f460_i2c_slv_devinfo_t;

/**
 * \brief I2C�豸�ṹ��
 */
typedef struct am_hc32f460_i2c_slv_dev {

    /** \brief ��׼I2C���豸���� */
    am_i2c_slv_serv_t                  i2c_slv_serv;

   /** \brief �ӻ��豸,ֻ�ܴ�һ���ӻ���ַ,ֻ������һ���豸 */
    am_i2c_slv_device_t               *p_i2c_slv_dev[1];

    /** \brief HC32���������Ĵӻ��������ɷŶ��ٸ��ӻ���ַ,�� p_i2c_slv_dev�����������һ��, */
    uint8_t                            zlg_i2c_slv_dev_num;

    /** \brief �㲥���� ��־ */
    am_bool_t                          is_gen_call;

    /** �����ʱ��,���ڳ�ʱ���� */
    am_softimer_t                      softimer;

    /** \brief ָ��I2C�豸��Ϣ��ָ�� */
    const am_hc32f460_i2c_slv_devinfo_t    *p_devinfo;

} am_hc32f460_i2c_slv_dev_t;

/**
 * \brief I2C��ʼ��
 *
 * \param[in] p_dev     : ָ���I2C�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ���I2C�豸��Ϣ�ṹ���ָ��
 *
 * \return ��I2C��׼����������
 */
am_i2c_slv_handle_t am_hc32f460_i2c_slv_init (am_hc32f460_i2c_slv_dev_t           *p_dev,
                                         const am_hc32f460_i2c_slv_devinfo_t *p_devinfo);

/**
 * \brief ���I2C��ʼ��
 * \param[in] handle : ����豸�����Ĵ�I2C��׼����������
 * \return ��
 */
void am_hc32f460_i2c_slv_deinit (am_i2c_slv_handle_t handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG_I2C_SLV_H */

/* end of file */

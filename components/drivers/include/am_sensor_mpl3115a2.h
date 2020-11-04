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
 * \brief ��ѹ������ MPL3115A2 ͷ�ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-11  fzb, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_MPL3115A2_H
#define __AM_SENSOR_MPL3115A2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������MPL3115A2�ṩ������ͨ��ID����
 */
#define AM_MPL3115A2_CHAN_1      0           /* MPL3115A2 ��ͨ��1����ѹ/���δ�����ͨ�� */
#define AM_MPL3115A2_CHAN_2      1           /* MPL3115A2 ��ͨ��2���¶ȴ�����ͨ��      */

/**
 * \brief ������MPL3115A2ģʽ
 */
#define __MPL3115A2_PRE_MODE    0x00    /**< \brief ��ѹ��ģʽ            */
#define __MPL3115A2_ALT_MODE    0x01    /**< \brief ���μ�ģʽ            */

/*******************************************************************************
  ������MPL3115A2���޸ĺ궨��
*******************************************************************************/
/**< \brief ��������Ϊ2^(__MPL3115A2_OS_VAL)��7:2^7 = 128 */
#define __MPL3115A2_OS_VAL      0x07

/**
 * \brief ������MPL3115A2ģʽ����
 * \param:__MPL3115A2_PRE_MODE����ѹ��ģʽ
          __MPL3115A2_ALT_MODE�����μ�ģʽ
 */
#define __MPL3115A2_MODE        __MPL3115A2_PRE_MODE

/**
 * \brief ������ MPL3115A2 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_mpl3115a2_devinfo {
    
    /**
     * \brief ����׼��������������
     */
    int     trigger_pin;

    /**
     * \brief I2C 7λ �豸��ַ
     *
     * ���豸7λ��ַΪ 0xC0 �� 0xC1
     */
    uint8_t i2c_addr;

    /** \brief I2C����ʵ����ʼ������ */
    am_i2c_handle_t    (*pfn_i2c_inst_init)(void);

    /** \brief I2C���ʼ������ */
    void    (*pfn_i2c_inst_deinit)(am_i2c_handle_t);
} am_sensor_mpl3115a2_devinfo_t;

/**
 * \breif ������ MPL3115A2 �豸�ṹ�嶨��
 */
typedef struct am_sensor_mpl3115a2_dev {
    am_sensor_serv_t               mpl3115a2_dev;/**< \breif ��������׼����   */
    am_i2c_device_t                i2c_dev;      /**< \brief i2c�豸ʵ��      */
    void                          *p_arg[2];     /**< \brief �����ص��������� */
    uint8_t                        flags[2];     /**< \brief ������־λ       */
    am_isr_defer_job_t             g_myjob;      /**< \brief �ж���ʱ�������� */
    am_sensor_val_t                sam_rate;     /**< \brief ����Ƶ��         */
    uint8_t                        trigger;      /**< \brief ��¼��־λ       */
    am_sensor_val_t                data[2];      /**< \brief �ڲ����ݻ���     */
    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t         pfn_trigger_cb[2];
    
    /** \brief �豸��Ϣ */
    const am_sensor_mpl3115a2_devinfo_t *dev_info;

} am_sensor_mpl3115a2_dev_t;

/**
 * \brief ������ MPL3115A2 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���MPL3115A2�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���MPL3115A2�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_mpl3115a2_init (
        am_sensor_mpl3115a2_dev_t           *p_dev,
        const am_sensor_mpl3115a2_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle);

/**
 * \brief ������ MPL3115A2 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_mpl3115a2_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_mpl3115a2_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_MPL3115A2_H */

/* end of file */

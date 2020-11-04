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
 * \brief  zlg237 I2C�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-07-24  zc, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG_I2C_H
#define __AM_ZLG_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_int.h"
#include "am_i2c.h"
#include "am_list.h"
#include "am_softimer.h"

#include "am_vdebug.h"
#include "hw/amhw_zlg237_i2c.h"

/**
 * \addtogroup am_zlg237_if_i2c
 * \copydoc am_zlg_i2c.h
 * @{
 */

/**
 * \brief I2C�豸��Ϣ�����ṹ��
 */
typedef struct am_zlg237_i2c_devinfo {

    /** \brief I2C�Ĵ������ַ */
    uint32_t  i2c_regbase;

    /** \brief ʱ��ID */
    int       clk_num;

    /** \brief I2C���������жϺ� */
    uint16_t  inum;

    /** \brief I2C���� */
    uint32_t  speed;

    /**
     * \brief ��ʱʱ��ֵ
     *
     * I2C���������ݴ����ڼ䣬���˶�ʱ����ʱ�������κ���Ӧ,����Ϊ��ʱ��
     * ������ǰ���䲢��λ�ڲ��߼�
     */
    uint32_t  timeout_ms;

    /** \brief I2C���߻ָ����� */
    void    (*pfn_bus_clean)(void);

    /** \brief ƽ̨��ʼ������ */
    void    (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void    (*pfn_plfm_deinit)(void);

} am_zlg237_i2c_devinfo_t;

/**
 * \brief I2C�豸�ṹ��
 */
typedef struct am_zlg237_i2c_dev {

    /** \brief ��׼I2C���� */
    am_i2c_serv_t                           i2c_serv;

    /** \brief I2C��������Ϣ���� */
    struct am_list_head                     msg_list;

    /** \brief ָ��I2C����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_i2c_transfer_t                      *p_cur_trans;

    /** \brief ��ǰ���ڴ������Ϣ */
    am_i2c_message_t                       *p_cur_msg;

    /** \brief �Ƿ���ɱ�����Ϣ */
    volatile am_bool_t                      is_complete;

    /** \brief �������ݽ���/���ͼ��� */
    volatile uint32_t                       data_ptr;

    /** \brief ��ǰ����״̬��0���˴δ����˴ӻ���ַ��1���˴�û�д���ӻ���ַ�� */
    volatile uint8_t                        trans_state;

    /** \brief æ��ʶ */
    volatile am_bool_t                      busy;

    /** \brief ״̬ */
    volatile uint8_t                        state;

    /** \brief �ӻ���ַ */
    volatile uint16_t                       slave_addr;

    /** \brief ��ʱ�����ʱ�� */
    am_softimer_t                           softimer;

    /** \brief ��ʱ�����ʱ��״̬ */
    volatile am_bool_t                      softimer_state;

    /** \brief �Ƿ��ж�״̬�� */
    volatile am_bool_t                      is_abort;

    /** \brief ʱ��Ƶ�� */
    volatile uint32_t                       i2c_clock_speed;

    /** \brief I2Cģʽ    IIC  SMBus ģʽ  */
    volatile amhw_zlg237_i2c_mode_t         i2c_mode;

    /** \brief I2C����ģʽ��ռ�ձ� */
    volatile amhw_zlg237_i2c_duty_t         i2c_dutycycle;

    /** \brief I2C �����ַ */
    volatile uint16_t                       i2c_ownaddress1;

    /** \brief I2C ACK�ź�ʹ��״̬  ʹ�� ���� */
    volatile amhw_zlg237_i2c_ack_t          i2c_ack;

    /** \brief I2C 7λ��10λ��ַ�� ack�źŵ�ַ */
    volatile amhw_zlg237_i2c_ack_address_t  i2c_acknowledgedaddress;

    /** \brief ָ��I2C�豸��Ϣ��ָ�� */
    const am_zlg237_i2c_devinfo_t             *p_devinfo;

} am_zlg237_i2c_dev_t;

/**
 * \brief I2C��ʼ��
 *
 * \param[in] p_dev     : ָ��I2C�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��I2C�豸��Ϣ�ṹ���ָ��
 *
 * \return I2C��׼����������
 */
am_i2c_handle_t am_zlg237_i2c_init (am_zlg237_i2c_dev_t           *p_dev,
                                 const am_zlg237_i2c_devinfo_t *p_devinfo);

/**
 * \brief ���I2C��ʼ��
 *
 * \param[in] handle : ����豸������I2C��׼����������
 *
 * \return ��
 */
void am_zlg237_i2c_deinit (am_i2c_handle_t handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG_I2C_H */

/* end of file */

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
 * \brief ������ MPL3115A2 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-11  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_mpl3115a2.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "math.h"
#include "am_delay.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#define __MPL3115A2_REG_STATUS              0x00  /**< \brief ������״̬�Ĵ���      */
#define __MPL3115A2_REG_OUT_P_MSB           0x01  /**< \brief ��ѹ���ݸ߰�λ        */
#define __MPL3115A2_REG_OUT_P_CSB           0x02  /**< \brief ��ѹ�����а�λ        */
#define __MPL3115A2_REG_OUT_P_LSB           0x03  /**< \brief ��ѹ���ݵͰ�λ        */
#define __MPL3115A2_REG_OUT_T_MSB           0x04  /**< \brief �¶����ݸ߰�λ        */
#define __MPL3115A2_REG_OUT_T_LSB           0x05  /**< \brief �¶����ݵͰ�λ        */
#define __MPL3115A2_REG_DR_STATUS           0x06  /**< \brief ״̬�Ĵ���            */
#define __MPL3115A2_REG_OUT_P_DELTA_MSB     0x07  /**< \brief ��ѹ�������ݸ߰�λ    */
#define __MPL3115A2_REG_OUT_P_DELTA_CSB     0x08  /**< \brief ��ѹ���������а�λ    */
#define __MPL3115A2_REG_OUT_P_DELTA_LSB     0x09  /**< \brief ��ѹ�������ݵͰ�λ    */
#define __MPL3115A2_REG_OUT_T_DELTA_MSB     0x0A  /**< \brief �¶��������ݸ߰�λ    */
#define __MPL3115A2_REG_OUT_T_DELTA_LSB     0x0B  /**< \brief �¶��������ݵͰ�λ    */
#define __MPL3115A2_REG_WHO_AM_I            0x0C  /**< \brief �������Ĵ�������ID��*/
#define __MPL3115A2_REG_F_STATUS            0x0D  /**< \brief FIFO״̬�Ĵ���        */
#define __MPL3115A2_REG_F_DATA              0x0E  /**< \brief FIFO8λ����ͨ��       */
#define __MPL3115A2_REG_F_SETUP             0x0F  /**< \brief FIFO���üĴ���        */
#define __MPL3115A2_REG_TIME_DLY            0x10  /**< \brief ʱ���ӳټĴ���        */
#define __MPL3115A2_REG_SYSMOD              0x11  /**< \brief ϵͳģʽ�Ĵ���        */
#define __MPL3115A2_REG_INT_SOURCE          0x12  /**< \brief �ж�Դ�Ĵ���          */
#define __MPL3115A2_REG_PT_DATA_CFG         0x13  /**< \brief PT�������üĴ���      */
#define __MPL3115A2_REG_BAR_IN_MSB          0x14  /**< \brief ���μ�����ѹ����߰�λ*/
#define __MPL3115A2_REG_BAR_IN_LSB          0x15  /**< \brief ���μ�����ѹ����Ͱ�λ*/
#define __MPL3115A2_REG_P_TGT_MSB           0x16  /**< \brief Ŀ����ѹ�߰�λ        */
#define __MPL3115A2_REG_P_TGT_LSB           0x17  /**< \brief Ŀ����ѹ�Ͱ�λ        */
#define __MPL3115A2_REG_T_TGT               0x18  /**< \brief Ŀ���¶ȼĴ���        */
#define __MPL3115A2_REG_P_WND_MSB           0x19  /**< \brief ��ѹ/���δ��ڸ߰�λ   */
#define __MPL3115A2_REG_P_WND_LSB           0x1A  /**< \brief ��ѹ/���δ��ڵͰ�λ   */
#define __MPL3115A2_REG_T_WND               0x1B  /**< \brief �¶ȴ��ڼĴ���        */
#define __MPL3115A2_REG_P_MIN_MSB           0x1C  /**< \brief ��С��ѹ���ݸ߰�λ    */
#define __MPL3115A2_REG_P_MIN_CSB           0x1D  /**< \brief ��С��ѹ�����а�λ    */
#define __MPL3115A2_REG_P_MIN_LSB           0x1E  /**< \brief ��С��ѹ���ݵͰ�λ    */
#define __MPL3115A2_REG_T_MIN_MSB           0x1F  /**< \brief ��С�¶����ݸ߰�λ    */
#define __MPL3115A2_REG_T_MIN_LSB           0x20  /**< \brief ��С�¶����ݵͰ�λ    */
#define __MPL3115A2_REG_P_MAX_MSB           0x21  /**< \brief �����ѹ���ݸ߰�λ    */
#define __MPL3115A2_REG_P_MAX_CSB           0x22  /**< \brief �����ѹ�����а�λ    */
#define __MPL3115A2_REG_P_MAX_LSB           0x23  /**< \brief �����ѹ���ݵͰ�λ    */
#define __MPL3115A2_REG_T_MAX_MSB           0x24  /**< \brief ����¶����ݸ߰�λ    */
#define __MPL3115A2_REG_T_MAX_LSB           0x25  /**< \brief ����¶����ݵͰ�λ    */
#define __MPL3115A2_REG_CTRL_REG1           0x26  /**< \brief ���ƼĴ���1           */
#define __MPL3115A2_REG_CTRL_REG2           0x27  /**< \brief ���ƼĴ���2           */
#define __MPL3115A2_REG_CTRL_REG3           0x28  /**< \brief ���ƼĴ���3           */
#define __MPL3115A2_REG_CTRL_REG4           0x29  /**< \brief ���ƼĴ���4           */
#define __MPL3115A2_REG_CTRL_REG5           0x2A  /**< \brief ���ƼĴ���5           */
#define __MPL3115A2_REG_OFF_P               0x2B  /**< \brief ��ѹ����ƫ�ƼĴ���    */
#define __MPL3115A2_REG_OFF_T               0x2C  /**< \brief �¶�����ƫ�ƼĴ���    */
#define __MPL3115A2_REG_OFF_H               0x2D  /**< \brief ��������ƫ�ƼĴ���    */

#define __MPL3115A2_MY_ID                   0xC4    /**< \brief IDֵ                */
#define __MPL3115A2_CMD_RESET               0x04    /**< \brief ��λ����            */

/**
 * \brief �¶ȱ���ֵ
          Ŀ����ֵ�жϣ�__MPL3115A2_T_WND_VALUE = 0�������ж� ��= 0
          Ŀ����ֵ�жϿ��Ŀ����ֵ������һ���жϣ������ж��ڴ��ڷ�Χ���ظ��ж�
 */
#define __MPL3115A2_T_TGT_VALUE             27      /* �¶ȱ���Ŀ��ֵ  */
#define __MPL3115A2_T_WND_VALUE             2       /* �¶ȱ�������ֵ  */

/**
 * \brief MPL3115�ж����ż�����
 */
#define __MPL3115A2_INT1                    1   /* �ж�INT1                  */
#define __MPL3115A2_INT2                    0   /* �ж�INT2                  */

#define __MPL3115A2_OD_MODE                 1   /* ����INT��1����©ģʽ       */
#define __MPL3115A2_PP_MODE                 0   /* ����INT��0������ģʽ���ڲ������� */

#define __MPL3115A2_IPOL_H                  1   /* ����INT��1���жϸߵ�ƽ��Ч  */
#define __MPL3115A2_IPOL_L                  0   /* ����INT��0���жϵ͵�ƽ��Ч  */

/**
 * \brief MPL3115�ж��¼���ʶ���ж�ʹ�ܽ������� 
 */
#define __MPL3115A2_INT_CFG_DRDY            7   /* ���ݾ����ж� */
#define __MPL3115A2_INT_CFG_FIFO            6   /* FIFO�ж�    */
#define __MPL3115A2_INT_CFG_PW              5   /* ��ѹ�����ж� */
#define __MPL3115A2_INT_CFG_TW              4   /* �¶ȴ����ж� */
#define __MPL3115A2_INT_CFG_PTH             3   /* ��ѹ��ֵ�ж� */
#define __MPL3115A2_INT_CFG_TTH             2   /* �¶���ֵ�ж� */
#define __MPL3115A2_INT_CFG_PCHG            1   /* ��ѹ�仯�ж� */
#define __MPL3115A2_INT_CFG_TCHG            0   /* �¶ȱ仯�ж� */

/** \brief ���ò���ʱ�䲽�� */
#define __MPL3115A2_RATE_SET(data, mask)        (((data) & (~0xF)) | mask)

/** \brief ���ù������� */
#define __MPL3115A2_OS_SET(data, mask)          (((data) & (~(0x7 << 3))) | (mask << 3))

/** \brief ��ѹ��/���μ�ģʽ���� */
#define __MPL3115A2_MODE_SET(data, mask)        (((data) & (~(0x1 << 7))) | (mask << 7))

/** \brief �ж����λ���� */
#define __MPL3115A2_INT_CLR_BIT(data, bit)      ((data) & (~(0x1 << bit)))

/** \brief �ж����λ������ */
#define __MPL3115A2_INT_CLR_MASK(data, mask)    ((data) & (~(0x3 << mask)))

/** \brief ����ѹ/���������¼���־ʹ�� */
#define __MPL3115A2_PDEFE                       (0x1 << 1)

/** \brief ����ѹ/���������¼���־ʹ�� */
#define __MPL3115A2_TDEFE                       (0x1 << 0) 

/** \brief ��ʼһ�����ݲɼ� */
#define __MPL3115A2_ONE_SHOT_START              (0x1)

/** \brief OSTλ��1 */
#define __MPL3115A2_OST_SET_BIT                 (0x1 << 1)

/** \brief OSTλ���� */
#define __MPL3115A2_OST_CLEAR_BIT               (~(0x1 << 1))

/** \brief ��ȡPRESS״̬λ */
#define __MPL3115A2_GET_PRESS_STATUS(reg)       ((reg >> 2) & 0x1)

/** \brief ��ȡTEM״̬λ */
#define __MPL3115A2_GET_TEM_STATUS(reg)         ((reg >> 1) & 0x1)

/** \brief ��ȡ��ǰģʽ */
#define __MPL3115A2_GET_MODE(reg)               ((reg >> 7) & 0x1)

/** \brief ������int8ת��Ϊһ��int16_t���� */
#define __MPL3115A2_UINT8_TO_UINT16(buff) \
                       (int16_t)(((uint16_t)(buff[0]) << 8) \
                               | ((uint16_t)(buff[1])))

/** \brief ������int8ת��Ϊһ��int32_t���� */
#define __MPL3115A2_UINT8_TO_UINT32(buff) \
                       (uint32_t)(((uint32_t)(buff[0]) << 16) \
                               | ((uint32_t)(buff[1]) << 8)  \
                               | ((uint32_t)(buff[2])))

/*******************************************************************************
 * ���غ�������
 ******************************************************************************/
/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id);

/** \brief ��ȡ������ͨ���������� */
am_local am_err_t __pfn_data_get (void            *p_drv,
                                  const int       *p_ids,
                                  int              num,
                                  am_sensor_val_t *p_buf);

/** \brief ʹ�ܴ�����ͨ�� */
am_local am_err_t __pfn_enable (void            *p_drv,
                                const int       *p_ids,
                                int              num,
                                am_sensor_val_t *p_result);

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result);

/** \brief ���ô�����ͨ������ */
am_local am_err_t __pfn_attr_set (void                  *p_drv,
                                  int                    id,
                                  int                    attr,
                                  const am_sensor_val_t *p_val);

/** \brief ��ȡ������ͨ������ */
am_local am_err_t __pfn_attr_get (void            *p_drv,
                                  int              id,
                                  int              attr,
                                  am_sensor_val_t *p_val);

/** \brief ���ô�����һ��ͨ����������һ�������ص����� */
am_local am_err_t __pfn_trigger_cfg (void                   *p_drv,
                                     int                     id,
                                     uint32_t                flags,
                                     am_sensor_trigger_cb_t  pfn_cb,
                                     void                   *p_arg);

/** \brief �򿪴��� */
am_local am_err_t __pfn_trigger_on (void *p_drv, int id);

/** \brief �رմ��� */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id);

/** \brief ��������׼���� */
am_local am_const struct am_sensor_drv_funcs __g_sensor_mpl3115a2_funcs = {
        __pfn_type_get,
        __pfn_data_get,
        __pfn_enable,
        __pfn_disable,
        __pfn_attr_set,
        __pfn_attr_get,
        __pfn_trigger_cfg,
        __pfn_trigger_on,
        __pfn_trigger_off
};
/*******************************************************************************
  Local functions
*******************************************************************************/
/**
 * \brief MPL3115A2 д����
 */
am_local am_err_t __mpl3115a2_write (am_sensor_mpl3115a2_dev_t *p_this,
                                  uint32_t                subaddr,
                                  uint8_t                *p_buf,
                                  uint32_t                nbytes)
{
    return am_i2c_write(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief MPL3115A2 ������
 */
am_local am_err_t __mpl3115a2_read (am_sensor_mpl3115a2_dev_t *p_this,
                                 uint32_t                subaddr,
                                 uint8_t                *p_buf,
                                 uint32_t                nbytes)
{
    return am_i2c_read(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief ��ȡ����ֵ��������10^6��
 */
am_local int32_t __mpl3115a2_get_altitude_value (uint32_t altitude)
{
    uint8_t pmsb = (altitude >> 16) & 0xff;
    uint8_t pcsb = (altitude >> 8) & 0xff;
    uint8_t plsb = altitude & 0xff;
    uint16_t plsb_dec = 0;
    uint16_t alt_word = 0;

    int32_t alt;

    if (pmsb > 0x7F) {      /* �����β��� */
        am_kprintf("Altitude: Negative \r\n");
        alt_word = (pmsb << 8) | pcsb;
        alt_word = ~alt_word + 1;
    } else {
        am_kprintf("Altitude: Positive \r\n");
        alt_word = (pmsb << 8) | pcsb;
    }
    plsb_dec = (plsb >> 4) * 625;   /* ����С������ */

    alt = (int32_t)((alt_word * 1000000) + (plsb_dec * 100));

    return alt;
}

/**
 * \brief ��ȡ��ѹֵ����λ��KPa����������10^6��
 */
am_local int32_t __mpl3115a2_get_press_value (uint32_t press)
{
    uint8_t pmsb = (press >> 16) & 0xff;
    uint8_t pcsb = (press >> 8) & 0xff;
    uint8_t plsb = press & 0xff;
    uint16_t plsb_dec = 0;
    uint32_t pre_word = 0;
    uint32_t pre;

    pre_word = ((pmsb << 10) |                    /* ��ѹ�������� */
                (pcsb << 2)  | 
                (plsb_dec >> 6)) & 0x3ffff;

    plsb_dec = ((plsb >> 4) & 0x03) * 25;         /* ��ѹС������ */

    /* ԭʼ���ݵ�λΪPa���˴�ת��ΪKPa��������10^6�� */
    pre = (uint32_t)((pre_word * 1000) + (plsb_dec * 10));

    return pre;
}

/**
 * \brief ��ȡ�¶�ֵ��������10^6��
 */
am_local int32_t __mpl3115a2_get_tem_value (uint32_t temperature)
{
    int8_t      tmsb = (temperature >> 8) & 0xff;
    uint16_t    tlsb = temperature & 0xff;
    int32_t     temp;

    tlsb = (tlsb >> 4) * 625;
    temp = (int32_t)((tmsb * 1000000) + (tlsb * 100));

    return temp;
}

/** \breif �жϻص����� */
am_local void __mpl3115a2_alarm_callback (void *p_arg)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /*< \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_arg;

    uint8_t reg_data[3];
    uint8_t measure_type = 0;
    int32_t tem_data   = 0;

    /** \brief ��ȡ��ѹ���ݼĴ���ֵ */
    __mpl3115a2_read(p_this, __MPL3115A2_REG_OUT_P_MSB, reg_data, 3);

    tem_data = __MPL3115A2_UINT8_TO_UINT32(reg_data);

    /** \brief ��ȡMPL3115A2��ǰģʽ */
    __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG1, &measure_type, 1);
    if (__MPL3115A2_GET_MODE(measure_type)) {
        /** \brief ���μ�ģʽ */
        p_this->data[0].val = __mpl3115a2_get_altitude_value(tem_data); 
        p_this->data[0].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/
    } else {
        /** \brief ��ѹ��ģʽ */
        p_this->data[0].val = __mpl3115a2_get_press_value(tem_data); 
        p_this->data[0].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/
    }

    /** \brief ��ȡ�¶� */
    __mpl3115a2_read(p_this, __MPL3115A2_REG_OUT_T_MSB, reg_data, 2);

    tem_data = __MPL3115A2_UINT8_TO_UINT16(reg_data);

    /** \brief �¶� */
    p_this->data[1].val = __mpl3115a2_get_tem_value(tem_data); 
    p_this->data[1].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/

    if (p_this->pfn_trigger_cb[0] &&
            (p_this->flags[0] & AM_SENSOR_TRIGGER_DATA_READY)) {
        p_this->pfn_trigger_cb[0](p_this->p_arg[0],
                                  AM_SENSOR_TRIGGER_DATA_READY);
    }

    if (p_this->pfn_trigger_cb[1] &&
            (p_this->flags[1] & AM_SENSOR_TRIGGER_DATA_READY)) {
        p_this->pfn_trigger_cb[1](p_this->p_arg[1],
                                  AM_SENSOR_TRIGGER_DATA_READY);
    }
}

/**
 * \brief ����ѡ��
 */
am_local am_err_t __reg_attr_set (am_sensor_mpl3115a2_dev_t *p_this, uint8_t rate)
{
    am_err_t ret = AM_OK;

    uint8_t rate_cfg = 0;

    ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG2, &rate_cfg, 1);
    if (ret != AM_OK) {
        am_kprintf("read error! \r\n");
        return ret;
    }

    rate_cfg = __MPL3115A2_RATE_SET(rate_cfg, rate);
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG2, &rate_cfg, 1);
    if (ret != AM_OK) {
        return ret;
    }
    return ret;
}

/**
 * \brief �ж���������
 *
 * \param[in] p_this    : ָ��MPL3115A2�豸��ָ��
 * \param[in] int_num   : �¼��ж��ź��������
                          (__MPL3115A2_INT1���ж����ӵ�INT1)
                          (__MPL3115A2_INT2���ж����ӵ�INT2)
 * \param[in] int_pp_od : �ж����Žṹѡ�������   
                          (__MPL3115A2_PP_MODE���ж�����ṹ��
                           __MPL3115A2_OD_MODE���жϿ�©�ṹ)
 * \param[in] int_ipol  : �ж�������Ч��ƽ������    
                          (__MPL3115A2_IPOL_L���жϵ͵�ƽ��Ч��
                           __MPL3115A2_IPOL_H���жϸߵ�ƽ��Ч)
 *
 * \return  AM_OK : �ж������������
 */
am_local am_err_t __mpl3115a2_pin_int_set (am_sensor_mpl3115a2_dev_t *p_this,
                                           uint8_t int_num,
                                           uint8_t int_pp_od,
                                           uint8_t int_ipol)
{
    am_err_t ret = AM_OK;

    uint8_t ctrl_reg3 = 0;
    
    ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG3, &ctrl_reg3, 1);
    if ( ret != AM_OK) {
        return ret;
    }

    switch (int_num) {
    case __MPL3115A2_INT1:
        ctrl_reg3 = ((int_pp_od << 4)| (int_ipol << 5)) | 
                      __MPL3115A2_INT_CLR_MASK(ctrl_reg3, 4);
        break;
    case __MPL3115A2_INT2:
        ctrl_reg3 = ((int_pp_od << 0)| (int_ipol << 1)) | 
                      __MPL3115A2_INT_CLR_MASK(ctrl_reg3, 0);
        break;
    default:
        break;
    }

    return __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG3, &ctrl_reg3, 1);
}

/**
 * \brief �ж�������������Լ�ʹ��
 *
 * \param[in] p_this    : ָ��MPL3115A2�豸��ָ��
 * \param[in] int_event : ��Ҫ���õ��ж��¼���MPL3115�а����ж��¼��������ݾ����¼���INT_CFG_DRDY��
 * \param[in] int_num   : �¼��ж��ź��������
                          (__MPL3115A2_INT1���ж����ӵ�INT1)
                          (__MPL3115A2_INT2���ж����ӵ�INT2)
 * \param[in] is_enable : �¼��ж�ʹ�������
                          (AM_TRUE�� �¼��ж�ʹ��)
                          (AM_FALSE���¼��жϽ���)
 *
 * \return  AM_OK : �ж�����������
 */
am_local am_err_t __mpl3115a2_event_int_set (am_sensor_mpl3115a2_dev_t *p_this,
                                             uint8_t int_event,
                                             uint8_t int_num,
                                             uint8_t is_enable)
{
    am_err_t ret = AM_OK;

    uint8_t ctrl_reg4 = 0;
    uint8_t ctrl_reg5 = 0;

    ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG5, &ctrl_reg5, 1);
    if ( ret != AM_OK) {
        return ret;
    }

    ctrl_reg5 = (int_num << int_event) | __MPL3115A2_INT_CLR_BIT(ctrl_reg5, int_event);
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG5, &ctrl_reg5, 1);
    if ( ret != AM_OK) {
        return ret;
    }

    ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG4, &ctrl_reg4, 1);
    if ( ret != AM_OK) {
        return ret;
    }

    ctrl_reg4 = (is_enable << int_event) | __MPL3115A2_INT_CLR_BIT(ctrl_reg4, int_event);
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG4, &ctrl_reg4, 1);
    if ( ret != AM_OK) {
        return ret;
    }

    return ret;
}

/**
 * \brief �����¶ȱ���Ŀ��ֵ�봰��ֵ
 *
 * \param[in] p_this    : ָ��MPL3115A2�豸��ָ��
 * \param[in] int_num   : �¼��ж��ź��������
                          (__MPL3115A2_INT1���ж����ӵ�INT1)
                          (__MPL3115A2_INT2���ж����ӵ�INT2)
 * \param[in] t_tgt_data: �¶ȱ���Ŀ��ֵ
 * \param[in] t_wnd_data: �¶ȱ�������ֵ
 *
 * \return  AM_OK : �����¶ȱ���Ŀ��ֵ�봰��ֵ���
 */
am_local am_err_t __mpl3115a2_t_alarm_set (am_sensor_mpl3115a2_dev_t *p_this,
                                             uint8_t int_num,
                                             int8_t t_tgt_data,
                                             uint8_t t_wnd_data)
{
    am_err_t ret = AM_OK;

    /* �����¶ȱ���Ŀ��ֵ */
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_T_TGT, (uint8_t *)&t_tgt_data, 1);
    if ( ret != AM_OK) {
        return ret;
    }

    /* �����¶ȱ�������ֵ */
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_T_WND, &t_wnd_data, 1);
    if ( ret != AM_OK) {
        return ret;
    }

    if (t_wnd_data != 0) {
        __mpl3115a2_event_int_set(p_this, __MPL3115A2_INT_CFG_TW, int_num, AM_TRUE);
    } else {
        __mpl3115a2_event_int_set(p_this, __MPL3115A2_INT_CFG_TTH, int_num, AM_TRUE);
    }

    return ret;
}

/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (id == AM_MPL3115A2_CHAN_1) {
        return AM_SENSOR_TYPE_PRESS;
    } else if (id == AM_MPL3115A2_CHAN_2) {
        return AM_SENSOR_TYPE_TEMPERATURE;
    } else {
        return -AM_ENODEV;
    }
}

/** \brief ��ȡ������ͨ���������� */
am_local am_err_t __pfn_data_get (void            *p_drv,
                                  const int       *p_ids,
                                  int              num,
                                  am_sensor_val_t *p_buf)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_drv;
    
    am_err_t ret        = AM_OK;
    uint8_t status_val  = 0;
    uint8_t reg_data[3] = {0};
    uint8_t measure_type = 0;
    uint32_t tem_data   = 0;

    int cur_id = 0;
    int i = 0;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (AM_BIT_GET(p_this->trigger, 7) != 1) {
        return -AM_EPERM;
    }

    for (i = 0; i < num; i++) {
        p_buf[i].unit = AM_SENSOR_UNIT_INVALID;
    }

    /* ��Ϊ1�������������׼�����������ص�������ʹ�� */
    if (num == 1) {
        cur_id = p_ids[0];
        /* ��������׼������������ʽ����ֱ�Ӹ�ֵ */
        if ((AM_BIT_GET(p_this->trigger, 2)) &&
                ((p_this->flags[0] & AM_SENSOR_TRIGGER_DATA_READY) ||
                 (p_this->flags[1] & AM_SENSOR_TRIGGER_DATA_READY))) {
            p_buf[0].val = p_this->data[cur_id].val;
            p_buf[0].unit= p_this->data[cur_id].unit;
            return AM_OK;
        }
    }

    /** \brief ��ȡ�ɶ�״ֵ̬ */
    do {
        ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_DR_STATUS, &status_val, 1);
        if (ret != AM_OK) {
            return ret;
        }
    } while (__MPL3115A2_GET_PRESS_STATUS(status_val) != 0x1 ||
             __MPL3115A2_GET_TEM_STATUS(status_val) != 0x1);

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            /** \brief ��ȡ��ѹ���ݼĴ���ֵ */
            ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_OUT_P_MSB, reg_data, 3);

            tem_data = __MPL3115A2_UINT8_TO_UINT32(reg_data);

            /** \brief ��ȡMPL3115A2��ǰģʽ */
            __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG1, &measure_type, 1);
            if (__MPL3115A2_GET_MODE(measure_type)) {
                /** \brief ���μ�ģʽ */
                p_buf[i].val = __mpl3115a2_get_altitude_value(tem_data); 
                p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/
            } else {
                /** \brief ��ѹ��ģʽ */
                p_buf[i].val = __mpl3115a2_get_press_value(tem_data); 
                p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/
            }

        } else if (cur_id == 1) {

            /** \brief ��ȡ�¶� */
            ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_OUT_T_MSB, reg_data, 2);

            tem_data = __MPL3115A2_UINT8_TO_UINT16(reg_data);
           
            /** \brief �¶� */
            p_buf[i].val = __mpl3115a2_get_tem_value(tem_data); 
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/

        }else {
            return -AM_ENODEV;  /*< \brief ���˴�ͨ�������ڸô�������ֱ�ӷ��� */
        }
    }
    
    ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG1, &status_val, 1);
    if (ret != AM_OK) {
        return ret;
    }

    /* OST�����㣬����λ����������һ������ */
    status_val &= __MPL3115A2_OST_CLEAR_BIT;
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG1, &status_val, 1);
    if (ret != AM_OK) {
        return ret;
    }
    status_val |= __MPL3115A2_OST_SET_BIT;
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG1, &status_val, 1);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ʹ�ܴ�����ͨ�� */
am_local am_err_t __pfn_enable (void            *p_drv,
                                const int       *p_ids,
                                int              num,
                                am_sensor_val_t *p_result)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    uint8_t open_one_shot = 0;
    uint8_t ctrl_reg1  = 0;
    uint8_t pt_data_cfg = 0;

    am_err_t ret = -AM_ENODEV;
    am_err_t curent_ret = AM_OK;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0 || cur_id == 1) {
            if (p_result != NULL) {
                p_result[i].val = AM_OK;
            }
            ret = AM_OK;
        } else {
            if (p_result != NULL) {
                p_result[i].val = -AM_ENODEV;
            }
            curent_ret = -AM_ENODEV;
        }
    }

    if (ret != AM_OK) {    /**< \breif �������û�иô�������ͨ�����룬���˳� */
        return curent_ret;
    }

    if (ret == AM_OK) {
        AM_BIT_SET(p_this->trigger, 7);
        AM_BIT_SET(p_this->trigger, 6);
        AM_BIT_SET(p_this->trigger, 5);
    }    

    /* ���Ȼ�ȡ���ƼĴ���1��ֵ */
    ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG1, &ctrl_reg1, 1); 
    if (ret != AM_OK) {
        curent_ret = ret;
    }
    /* ���ù�������ֵ ��ģʽ����*/
    ctrl_reg1 = __MPL3115A2_OS_SET(ctrl_reg1, __MPL3115A2_OS_VAL);
    ctrl_reg1 = __MPL3115A2_MODE_SET(ctrl_reg1, __MPL3115A2_MODE);
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG1, &ctrl_reg1, 1); 
    if (ret != AM_OK) {
        curent_ret = ret;
    }

    ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_PT_DATA_CFG, &pt_data_cfg, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }
    /* ��ѹ/���� �¶������¼���־ʹ�� */
    pt_data_cfg |= __MPL3115A2_PDEFE;
    pt_data_cfg |= __MPL3115A2_TDEFE;
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_PT_DATA_CFG, &pt_data_cfg, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }

    ret = __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG1, &open_one_shot, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }
    /* ����ACTIVEģʽ������STλ��ֵ���в��� */
    open_one_shot |= __MPL3115A2_ONE_SHOT_START;
    /* Ĭ����ѯ״̬��OST��1 �������������� */
    open_one_shot |= __MPL3115A2_OST_SET_BIT;
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG1, &open_one_shot, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }

    return curent_ret;
}

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            AM_BIT_CLR(p_this->trigger, 6);
            ret = AM_OK;

        } else if (cur_id == 1) {

            AM_BIT_CLR(p_this->trigger, 5);
            ret = AM_OK;

        } else {
            ret = -AM_ENODEV;
        }

        if (p_result != NULL) {
            p_result[i].val = ret;
        }
    }

    if ((AM_BIT_GET(p_this->trigger, 6) == 0)
            && (AM_BIT_GET(p_this->trigger, 5) == 0)) {

        if (cur_ret == AM_OK) {
            AM_BIT_CLR(p_this->trigger, 7);
        }
    }

    return cur_ret;
}

/** \brief ���ô�����ͨ������ */
am_local am_err_t __pfn_attr_set (void                  *p_drv,
                                  int                    id,
                                  int                    attr,
                                  const am_sensor_val_t *p_val)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    am_sensor_val_t sensor_val = {0, 0};

    am_sensor_val_t __sampling_rate = {0, 0};

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if ((id != AM_MPL3115A2_CHAN_1) && (id != AM_MPL3115A2_CHAN_2)) {
        return -AM_ENODEV;
    }

    switch (attr) {

    /* �޸�Ƶ�� */
    case AM_SENSOR_ATTR_SAMPLING_RATE:

        if (p_val->val < 0 || p_val->val > 15) {
            return -AM_ENOTSUP;
        }

        sensor_val.unit = p_val->unit;
        sensor_val.val  = p_val->val;
        am_sensor_val_unit_convert(&sensor_val, 1, AM_SENSOR_UNIT_BASE);

        ret = __reg_attr_set(p_this, sensor_val.val);

        if (ret != AM_OK) {
            cur_ret = ret;
        } else {
            p_this->sam_rate.val  = __sampling_rate.val;
            p_this->sam_rate.unit = __sampling_rate.unit;
        }

        break;

    default:
        cur_ret = -AM_ENOTSUP;
        break;
    }

    return cur_ret;
}

/** \brief ��ȡ������ͨ������ */
am_local am_err_t __pfn_attr_get (void            *p_drv,
                                  int              id,
                                  int              attr,
                                  am_sensor_val_t *p_val)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_drv;

    am_err_t ret = AM_OK;

    if ((id != AM_MPL3115A2_CHAN_1) && (id != AM_MPL3115A2_CHAN_2)) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    switch (attr) {

    /* ��ȡ����Ƶ�� */
    case AM_SENSOR_ATTR_SAMPLING_RATE:

        p_val->val  = p_this->sam_rate.val;
        p_val->unit = p_this->sam_rate.unit;
        break;

    default:
        ret = -AM_ENOTSUP;
        break;

    }

    return ret;
}

/** \brief ���ô�����һ��ͨ����������һ�������ص����� */
am_local am_err_t __pfn_trigger_cfg (void                   *p_drv,
                                     int                     id,
                                     uint32_t                flags,
                                     am_sensor_trigger_cb_t  pfn_cb,
                                     void                   *p_arg)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_drv;

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    switch (flags) {
    case AM_SENSOR_TRIGGER_DATA_READY:
        break;
    default:
        return -AM_ENOTSUP;
    }

    p_this->pfn_trigger_cb[id] = pfn_cb;
    p_this->p_arg[id]          = p_arg;
    p_this->flags[id]          = flags;

    return AM_OK;
}

/** \brief �򿪴��� */
am_local am_err_t __pfn_trigger_on (void *p_drv, int id)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t reg_clear[5];
    uint8_t ctrl_reg1 = 0;

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (p_this->trigger & 0x4) {
        return AM_OK;
    }

    /* �ж��������� */
    ret = __mpl3115a2_pin_int_set(p_this, 
                                  __MPL3115A2_INT1,
                                  __MPL3115A2_PP_MODE,
                                  __MPL3115A2_IPOL_L);
    if (ret != AM_OK) {
        cur_ret = ret;
    }

    /* �����¶ȱ���Ŀ��ֵ�봰��ֵ */
    ret = __mpl3115a2_t_alarm_set(p_this,
                                  __MPL3115A2_INT1,
                                  __MPL3115A2_T_TGT_VALUE,
                                  __MPL3115A2_T_WND_VALUE);
    if (ret != AM_OK) {
        cur_ret = ret;
    }

    /* �ж�������INT1, ��ʹ�����ݾ����ж� */
    ret = __mpl3115a2_event_int_set(p_this, 
                                    __MPL3115A2_INT_CFG_DRDY,
                                    __MPL3115A2_INT1,
                                    AM_TRUE);
    if (ret != AM_OK) {
        cur_ret = ret;
    }

    /* �ж�״̬��OSTλ���� */
    __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG1, &ctrl_reg1, 1);
    ctrl_reg1 &= __MPL3115A2_OST_CLEAR_BIT;
    ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG1, &ctrl_reg1, 1);
    if ( ret != AM_OK) {
        cur_ret = ret;
    }

    /* ���ô������� */
    if (p_this->dev_info->trigger_pin != -1) {    
        __mpl3115a2_read(p_this, __MPL3115A2_REG_OUT_P_MSB, reg_clear, 5);
        ret = am_gpio_trigger_on(p_this->dev_info->trigger_pin);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }

    if (cur_ret == AM_OK && id == 0) {
        AM_BIT_SET(p_this->trigger, 0);
        AM_BIT_SET(p_this->trigger, 2);
    }
    if (cur_ret == AM_OK && id == 1) {
        AM_BIT_SET(p_this->trigger, 1);
        AM_BIT_SET(p_this->trigger, 2);
    }

    return cur_ret;
}

/** \brief �رմ��� */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id)
{
    am_sensor_mpl3115a2_dev_t* p_this = (am_sensor_mpl3115a2_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    am_sensor_val_t p_val = {0, 0};

    uint8_t ctrl_reg1  = 0;

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    p_this->pfn_trigger_cb[id] = NULL;
    p_this->p_arg[id]          = NULL;
    p_this->flags[id]          = 0;

    AM_BIT_CLR(p_this->trigger, id);

    if ((p_this->trigger & 0x3) == 0) {

        /* �������ݾ����ж� */
        __mpl3115a2_event_int_set(p_this, __MPL3115A2_INT_CFG_DRDY, __MPL3115A2_INT1, AM_FALSE);

        ret = __pfn_attr_set(p_drv, id, AM_SENSOR_ATTR_SAMPLING_RATE, &p_val);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        if ((p_this->dev_info->trigger_pin != -1) && (cur_ret == AM_OK)) {
            ret = am_gpio_trigger_off(p_this->dev_info->trigger_pin);
            if (ret != AM_OK) {
                cur_ret = ret;
            }
        }

        if (cur_ret == AM_OK) {
            AM_BIT_CLR(p_this->trigger, 2);
        }

        /* �ָ���ѯ״̬��OST��1 */
        __mpl3115a2_read(p_this, __MPL3115A2_REG_CTRL_REG1, &ctrl_reg1, 1);
        ctrl_reg1 |= __MPL3115A2_OST_SET_BIT;
        ret = __mpl3115a2_write(p_this, __MPL3115A2_REG_CTRL_REG1, &ctrl_reg1, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ MPL3115A2 ��ʼ��
 */
am_sensor_handle_t am_sensor_mpl3115a2_init (
        am_sensor_mpl3115a2_dev_t           *p_dev,
        const am_sensor_mpl3115a2_devinfo_t *p_devinfo,
        am_i2c_handle_t                      handle)
{
    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t ctrl_reg1  = 0;
    uint8_t mpl3115a2_id = 0;

    am_i2c_handle_t i2c_handle = NULL;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->mpl3115a2_dev.p_drv   = p_dev;
    p_dev->mpl3115a2_dev.p_funcs = &__g_sensor_mpl3115a2_funcs;
    p_dev->dev_info            = p_devinfo;
    p_dev->pfn_trigger_cb[0]   = NULL;
    p_dev->pfn_trigger_cb[1]   = NULL;
    p_dev->p_arg[0]            = NULL;
    p_dev->p_arg[1]            = NULL;
    p_dev->flags[0]            = 0;
    p_dev->flags[1]            = 0;
    p_dev->sam_rate.val        = 0;
    p_dev->sam_rate.unit       = 0;
    p_dev->trigger             = 0;
    p_dev->data[0].val         = 0;
    p_dev->data[0].unit        = AM_SENSOR_UNIT_INVALID;
    p_dev->data[1].val         = 0;
    p_dev->data[1].unit        = AM_SENSOR_UNIT_INVALID;

    /* �ⲿ�ж����� */
    if (p_devinfo->trigger_pin != -1) {
        am_gpio_pin_cfg(p_devinfo->trigger_pin, AM_GPIO_INPUT);
        am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                __mpl3115a2_alarm_callback,
                                (void*)p_dev);
        am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_FALL); /* �½��ش��� */
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    /* ���ID */
    ret = __mpl3115a2_read(p_dev, __MPL3115A2_REG_WHO_AM_I, &mpl3115a2_id, 1);
    if (ret != AM_OK || mpl3115a2_id != __MPL3115A2_MY_ID) {
        cur_ret = ret;
        am_kprintf("Device ID:%x \r\n", mpl3115a2_id);
    }

    /* ���Ȼ�ȡ���ƼĴ���1��ֵ */
    ret = __mpl3115a2_read(p_dev, __MPL3115A2_REG_CTRL_REG1, &ctrl_reg1, 1);
    if (ret != AM_OK) {
        cur_ret = ret;
    }
    /* ��λMPL3115A2 */
    ctrl_reg1 |= __MPL3115A2_CMD_RESET; 
    ret = __mpl3115a2_write(p_dev, __MPL3115A2_REG_CTRL_REG1, &ctrl_reg1, 1);
    am_mdelay(10);
    if (ret != AM_OK) {
        cur_ret = ret;
    }

    /* ����I2C */
    p_dev->dev_info->pfn_i2c_inst_deinit(handle); /* ���ͷ�I2C��Դ */

    i2c_handle = p_dev->dev_info->pfn_i2c_inst_init(); /* ���³�ʼ��I2C */

    am_i2c_mkdev(&p_dev->i2c_dev,
                 i2c_handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);


    if (cur_ret != AM_OK) {
        am_kprintf("\r\nSensor MPL3115A2 Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->mpl3115a2_dev);
}

/**
 * \brief ������ MPL3115A2 ���ʼ��
 */
am_err_t am_sensor_mpl3115a2_deinit (am_sensor_handle_t handle)
{
    am_sensor_mpl3115a2_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->mpl3115a2_dev.p_drv   = NULL;
    p_dev->mpl3115a2_dev.p_funcs = NULL;
    p_dev->dev_info              = NULL;

    return AM_OK;
}



/* end of file */

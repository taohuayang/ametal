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
 * \brief ������ FXOS8700CQ �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_fxos8700cq.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_delay.h"

/*******************************************************************************
 * �궨��
 ******************************************************************************/
#define  __FXOS8700CQ_REG_STATUS            0x00 
#define  __FXOS8700CQ_REG_OUT_X_MSB         0x01 
#define  __FXOS8700CQ_REG_OUT_X_LSB         0x02 
#define  __FXOS8700CQ_REG_OUT_Y_MSB         0x03 
#define  __FXOS8700CQ_REG_OUT_Y_LSB         0x04 
#define  __FXOS8700CQ_REG_OUT_Z_MSB         0x05 
#define  __FXOS8700CQ_REG_OUT_Z_LSB         0x06 

#define  __FXOS8700CQ_REG_F_SETUP           0x09 
#define  __FXOS8700CQ_REG_TRIG_CFG          0x0A 
#define  __FXOS8700CQ_REG_SYSMOD            0x0B 
#define  __FXOS8700CQ_REG_INT_SOURCE        0x0C 
#define  __FXOS8700CQ_REG_WHO_AM_I          0x0D 
#define  __FXOS8700CQ_REG_XYZ_DATA_CFG      0x0E 
#define  __FXOS8700CQ_REG_HP_FILTER_CUTOFF  0x0F 
#define  __FXOS8700CQ_REG_PL_STATUS         0x10 
#define  __FXOS8700CQ_REG_PL_CFG            0x11 
#define  __FXOS8700CQ_REG_PL_COUNT          0x12 
#define  __FXOS8700CQ_REG_PL_BF_ZCOMP       0x13 
#define  __FXOS8700CQ_REG_PL_THS_REG        0x14 
#define  __FXOS8700CQ_REG_A_FFMT_CFG        0x15 
#define  __FXOS8700CQ_REG_A_FFMT_SRC        0x16 
#define  __FXOS8700CQ_REG_A_FFMT_THS        0x17 
#define  __FXOS8700CQ_REG_A_FFMT_COUNT      0x18 

#define  __FXOS8700CQ_REG_TRANSIENT_CFG     0x1D 
#define  __FXOS8700CQ_REG_TRANSIENT_SRC     0x1E 
#define  __FXOS8700CQ_REG_TRANSIENT_THS     0x1F 
#define  __FXOS8700CQ_REG_TRANSIENT_COUNT   0x20
#define  __FXOS8700CQ_REG_PULSE_CFG         0x21 
#define  __FXOS8700CQ_REG_PULSE_SRC         0x22 
#define  __FXOS8700CQ_REG_PULSE_THSX        0x23 
#define  __FXOS8700CQ_REG_PULSE_THSY        0x24 
#define  __FXOS8700CQ_REG_PULSE_THSZ        0x25 
#define  __FXOS8700CQ_REG_PULSE_TMLT        0x26 
#define  __FXOS8700CQ_REG_PULSE_LTCY        0x27
#define  __FXOS8700CQ_REG_PULSE_WIND        0x28 
#define  __FXOS8700CQ_REG_ASLP_COUNT        0x29 
#define  __FXOS8700CQ_REG_CTRL_REG1         0x2A 
#define  __FXOS8700CQ_REG_CTRL_REG2         0x2B 
#define  __FXOS8700CQ_REG_CTRL_REG3         0x2C 
#define  __FXOS8700CQ_REG_CTRL_REG4         0x2D 
#define  __FXOS8700CQ_REG_CTRL_REG5         0x2E 
#define  __FXOS8700CQ_REG_OFF_X             0x2F 
#define  __FXOS8700CQ_REG_OFF_Y             0x30 
#define  __FXOS8700CQ_REG_OFF_Z             0x31 
#define  __FXOS8700CQ_REG_M_DR_STATUS       0x32 
#define  __FXOS8700CQ_REG_M_OUT_X_MSB       0x33 
#define  __FXOS8700CQ_REG_M_OUT_X_LSB       0x34 
#define  __FXOS8700CQ_REG_M_OUT_Y_MSB       0x35 
#define  __FXOS8700CQ_REG_M_OUT_Y_LSB       0x36 
#define  __FXOS8700CQ_REG_M_OUT_Z_MSB       0x37 
#define  __FXOS8700CQ_REG_M_OUT_Z_LSB       0x38 
#define  __FXOS8700CQ_REG_CMP_X_MSB         0x39 
#define  __FXOS8700CQ_REG_CMP_X_LSB         0x3A 
#define  __FXOS8700CQ_REG_CMP_Y_MSB         0x3B 
#define  __FXOS8700CQ_REG_CMP_Y_LSB         0x3C 
#define  __FXOS8700CQ_REG_CMP_Z_MSB         0x3D 
#define  __FXOS8700CQ_REG_CMP_Z_LSB         0x3E 
#define  __FXOS8700CQ_REG_M_OFF_X_MSB       0x3F 
#define  __FXOS8700CQ_REG_M_OFF_X_LSB       0x40 
#define  __FXOS8700CQ_REG_M_OFF_Y_MSB       0x41 
#define  __FXOS8700CQ_REG_M_OFF_Y_LSB       0x42 
#define  __FXOS8700CQ_REG_M_OFF_Z_MSB       0x43 
#define  __FXOS8700CQ_REG_M_OFF_Z_LSB       0x44 
#define  __FXOS8700CQ_REG_MAX_X_MSB         0x45 
#define  __FXOS8700CQ_REG_MAX_X_LSB         0x46 
#define  __FXOS8700CQ_REG_MAX_Y_MSB         0x47 
#define  __FXOS8700CQ_REG_MAX_Y_LSB         0x48 
#define  __FXOS8700CQ_REG_MAX_Z_MSB         0x49 
#define  __FXOS8700CQ_REG_MAX_Z_LSB         0x4A 
#define  __FXOS8700CQ_REG_MIN_X_MSB         0x4B 
#define  __FXOS8700CQ_REG_MIN_X_LSB         0x4C 
#define  __FXOS8700CQ_REG_MIN_Y_MSB         0x4D 
#define  __FXOS8700CQ_REG_MIN_Y_LSB         0x4E 
#define  __FXOS8700CQ_REG_MIN_Z_MSB         0x4F 
#define  __FXOS8700CQ_REG_MIN_Z_LSB         0x50 
#define  __FXOS8700CQ_REG_TEMP              0x51 
#define  __FXOS8700CQ_REG_M_THS_CFG         0x52 
#define  __FXOS8700CQ_REG_M_THS_SRC         0x53 
#define  __FXOS8700CQ_REG_M_THS_X_MSB       0x54 
#define  __FXOS8700CQ_REG_M_THS_X_LSB       0x55 
#define  __FXOS8700CQ_REG_M_THS_Y_MSB       0x56 
#define  __FXOS8700CQ_REG_M_THS_Y_LSB       0x57 
#define  __FXOS8700CQ_REG_M_THS_Z_MSB       0x58 
#define  __FXOS8700CQ_REG_M_THS_Z_LSB       0x59 
#define  __FXOS8700CQ_REG_M_THS_COUNT       0x5A 
#define  __FXOS8700CQ_REG_M_CTRL_REG1       0x5B 
#define  __FXOS8700CQ_REG_M_CTRL_REG2       0x5C 
#define  __FXOS8700CQ_REG_M_CTRL_REG3       0x5D 
#define  __FXOS8700CQ_REG_M_INT_SRC         0x5E 
#define  __FXOS8700CQ_REG_A_VECM_CFG        0x5F 
#define  __FXOS8700CQ_REG_A_VECM_THS_MSB    0x60 
#define  __FXOS8700CQ_REG_A_VECM_THS_LSB    0x61 
#define  __FXOS8700CQ_REG_A_VECM_CNT        0x62 
#define  __FXOS8700CQ_REG_A_VECM_INITX_MSB  0x63 
#define  __FXOS8700CQ_REG_A_VECM_INITX_LSB  0x64 
#define  __FXOS8700CQ_REG_A_VECM_INITY_MSB  0x65 
#define  __FXOS8700CQ_REG_A_VECM_INITY_LSB  0x66 
#define  __FXOS8700CQ_REG_A_VECM_INITZ_MSB  0x67 
#define  __FXOS8700CQ_REG_A_VECM_INITZ_LSB  0x68 
#define  __FXOS8700CQ_REG_M_VECM_CFG        0x69 
#define  __FXOS8700CQ_REG_M_VECM_THS_MSB    0x6A 
#define  __FXOS8700CQ_REG_M_VECM_THS_LSB    0x6B 
#define  __FXOS8700CQ_REG_M_VECM_CNT        0x6C 
#define  __FXOS8700CQ_REG_M_VECM_INITX_MSB  0x6D 
#define  __FXOS8700CQ_REG_M_VECM_INITX_LSB  0x6E 
#define  __FXOS8700CQ_REG_M_VECM_INITY_MSB  0x6F 
#define  __FXOS8700CQ_REG_M_VECM_INITY_LSB  0x70 
#define  __FXOS8700CQ_REG_M_VECM_INITZ_MSB  0x71 
#define  __FXOS8700CQ_REG_M_VECM_INITZ_LSB  0x72 
#define  __FXOS8700CQ_REG_A_FFMT_THS_X_MSB  0x73 
#define  __FXOS8700CQ_REG_A_FFMT_THS_X_LSB  0x74 
#define  __FXOS8700CQ_REG_A_FFMT_THS_Y_MSB  0x75 
#define  __FXOS8700CQ_REG_A_FFMT_THS_Y_LSB  0x76 
#define  __FXOS8700CQ_REG_A_FFMT_THS_Z_MSB  0x77 
#define  __FXOS8700CQ_REG_A_FFMT_THS_Z_LSB  0x78 

#define  __FXOS8700CQ_MY_ID                 0XC7        /**< \brief IDֵ            */

#define  __FXOS8700CQ_SOFTWARE_RESET        (1 << 6)    /**< \brief RESET           */

/** \brief ��������ģʽ */
#define  __FXOS8700CQ_STANDBY_MODE          (~(1 << 0)) /**< \brief STANDBYģʽ         */
#define  __FXOS8700CQ_ACTIVE_MODE           (1 << 0)    /**< \brief ACTIVEģʽ          */

/** \brief ���ò�����Χ */
#define  __FXOS8700CQ_RANGE_SET_2G  (0 << 0) /**< \brief ���ò�����ΧΪ��2G      */     //0.244 mg/LSB
#define  __FXOS8700CQ_RANGE_SET_4G  (1 << 0) /**< \brief ���ò�����ΧΪ��4G      */     //0.488 mg/LSB
#define  __FXOS8700CQ_RANGE_SET_8G  (2 << 0) /**< \brief ���ò�����ΧΪ��8G      */     //0.976 mg/LSB

/** \brief ��ȡ���ٶ����ݼĴ���״̬λ��STATUS(0x00)��zyxowλ */
#define  __FXOS8700CQ_GET_ACC_DR_STATUS(reg)        ((reg >> 7) & 0x1)

/** \brief ��ȡ�������ݼĴ���״̬λ��M_DR_STATUS(0x32)��xyzowλ */
#define  __FXOS8700CQ_GET_MAG_DR_STATUS(reg)        ((reg >> 7) & 0x1)

/** \brief �жϴ������� */
#define  __FXOS8700CQ_INT_DRDY_ENABLE       (1 << 0)    /**< \brief ʹ������׼�������ж�        */
#define  __FXOS8700CQ_INT_DRDY_DISABLE      (0 << 0)    /**< \brief ��������׼�������ж�        */
#define  __FXOS8700CQ_EN_INT1_DRDY          (1 << 0)    /**< \brief ʹ�������ж�                */

/** \brief ������int8ת��Ϊһ��int16_t���� */
#define  __FXOS8700CQ_UINT8_TO_UINT16(buff) \
                       (int16_t)(((int16_t)(buff[0]) << 8) \
                                | (int16_t)buff[1])

/** \brief ������ٶ�,������10^6�� */
#define  __FXOS8700CQ_GET_ACCEL_VALUE_2G(data)  ((int32_t)((data >> 2) * 244000))
#define  __FXOS8700CQ_GET_ACCEL_VALUE_4G(data)  ((int32_t)((data >> 2) * 488000))
#define  __FXOS8700CQ_GET_ACCEL_VALUE_8G(data)  ((int32_t)((data >> 2) * 976000))

/** \brief �������,������10^6�� */             //0.1uT/LSB     0.1uT = 1 gauss
#define  __FXOS8700CQ_GET_MAG_VALUE(data)       ((int32_t)(data * 1000000))

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
am_local am_const struct am_sensor_drv_funcs __g_sensor_fxos8700cq_funcs = {
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
 * \brief FXOS8700CQ д����
 */
am_local am_err_t __fxos8700cq_write (am_sensor_fxos8700cq_dev_t *p_this,
                                   uint32_t                subaddr,
                                   uint8_t                *p_buf,
                                   uint32_t                nbytes)
{
    return am_i2c_write(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief FXOS8700CQ ������
 */
am_local am_err_t __fxos8700cq_read (am_sensor_fxos8700cq_dev_t *p_this,
                                  uint32_t                subaddr,
                                  uint8_t                *p_buf,
                                  uint32_t                nbytes)
{
    return am_i2c_read(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief �������̽����ת���ɼ��ٶ�ʵ��ֵ
 */
am_local int32_t __fxos8700cq_get_accel_value (am_sensor_fxos8700cq_dev_t* p_this,
                                            uint32_t                 data)
{
    int32_t real_data = 0;
    
    if (p_this == NULL) {
        return NULL;
    }
    real_data = __FXOS8700CQ_GET_ACCEL_VALUE_4G(data);
    switch (p_this->sam_range.val) {
    case 2:
        real_data = __FXOS8700CQ_GET_ACCEL_VALUE_2G(data);
        break;
    case 4:
        real_data = __FXOS8700CQ_GET_ACCEL_VALUE_4G(data);
        break;
    case 8:
        real_data = __FXOS8700CQ_GET_ACCEL_VALUE_8G(data);
        break;
    default:
        real_data = -AM_EINVAL;
        break;
    }
    return real_data;
}

/** \breif �жϻص����� */
am_local void __fxos8700cq_alarm_callback (void *p_arg)
{
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /*< \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_arg;

    uint8_t reg_data[2];
    uint8_t i = 0;
    int32_t tem_data   = 0;

    /** \brief ��ȡX����ٶ� */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_OUT_X_MSB, reg_data, 2);

    tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);

    /** \brief X����ٶ� */
    p_this->data[0].val = __fxos8700cq_get_accel_value(p_this, tem_data);
    p_this->data[0].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6) */

    /** \brief ��ȡY����ٶ� */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_OUT_Y_MSB, reg_data, 2);

    tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);

    /** \brief Y����ٶ� */
    p_this->data[1].val = __fxos8700cq_get_accel_value(p_this, tem_data);
    p_this->data[1].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6) */

    /** \brief ��ȡZ����ٶ� */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_OUT_Z_MSB, reg_data, 2);

    tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);

    /** \brief Z����ٶ� */
    p_this->data[2].val = __fxos8700cq_get_accel_value(p_this, tem_data);
    p_this->data[2].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6) */

    /** \brief ��ȡX����� */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_OUT_X_MSB, reg_data, 2);

    tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);

    /** \brief X����� */
    p_this->data[3].val = __FXOS8700CQ_GET_MAG_VALUE(tem_data);
    p_this->data[3].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

    /** \brief ��ȡY����� */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_OUT_Y_MSB, reg_data, 2);

    tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);

    /** \brief Y����� */
    p_this->data[4].val = __FXOS8700CQ_GET_MAG_VALUE(tem_data);
    p_this->data[4].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

    /** \brief ��ȡZ����� */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_OUT_Z_MSB, reg_data, 2);

    tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);

    /** \brief Z����� */
    p_this->data[5].val = __FXOS8700CQ_GET_MAG_VALUE(tem_data);
    p_this->data[5].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

    for (i = 0; i < 6; i++) {
        if (p_this->pfn_trigger_cb[i] &&
                (p_this->flags[i] & AM_SENSOR_TRIGGER_DATA_READY)) {
            p_this->pfn_trigger_cb[i](p_this->p_arg[i],
                                      AM_SENSOR_TRIGGER_DATA_READY);
        }
    }
}

/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (id == AM_FXOS8700CQ_CHAN_1 || id == AM_FXOS8700CQ_CHAN_2 ||
        id == AM_FXOS8700CQ_CHAN_3) {
        return AM_SENSOR_TYPE_ACCELEROMETER;
    } else if (id == AM_FXOS8700CQ_CHAN_4 || id == AM_FXOS8700CQ_CHAN_5 ||
        id == AM_FXOS8700CQ_CHAN_6) {
        return AM_SENSOR_TYPE_MAGNETIC;
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
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_drv;
    
    am_err_t ret        = AM_OK;
    uint8_t reg_data[2] = {0};
    uint32_t tem_data   = 0;
    uint8_t status_val  = 0;
    uint8_t m_dr_status_val = 0;

    int cur_id = 0;
    int i = 0;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (AM_BIT_GET(p_this->trigger, 15) != 1) {
        return -AM_EPERM;
    }

    for (i = 0; i < num; i++) {
        p_buf[i].unit = AM_SENSOR_UNIT_INVALID;
    }

    /* ��Ϊ1�������������׼�����������ص�������ʹ�� */
    if (num == 1) {
        cur_id = p_ids[0];
        /* ��������׼������������ʽ����ֱ�Ӹ�ֵ */
        if ((AM_BIT_GET(p_this->trigger, 6)) &&
                ((p_this->flags[0] & AM_SENSOR_TRIGGER_DATA_READY) ||
                 (p_this->flags[1] & AM_SENSOR_TRIGGER_DATA_READY) ||
                 (p_this->flags[2] & AM_SENSOR_TRIGGER_DATA_READY) ||
                 (p_this->flags[3] & AM_SENSOR_TRIGGER_DATA_READY) ||
                 (p_this->flags[4] & AM_SENSOR_TRIGGER_DATA_READY) ||
                 (p_this->flags[5] & AM_SENSOR_TRIGGER_DATA_READY))) {
            p_buf[0].val = p_this->data[cur_id].val;
            p_buf[0].unit= p_this->data[cur_id].unit;
            return AM_OK;
        }
    } 

    /** \brief ��ȡ�ɶ�״ֵ̬ */
    do {
        ret = __fxos8700cq_read(p_this, __FXOS8700CQ_REG_STATUS, &status_val, 1);
        if (ret != AM_OK) {
            return ret;
        }
        ret = __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_DR_STATUS, &m_dr_status_val, 1);
        if (ret != AM_OK) {
            return ret;
        }
    } while (__FXOS8700CQ_GET_ACC_DR_STATUS(status_val) != 0x1 ||
             __FXOS8700CQ_GET_MAG_DR_STATUS(m_dr_status_val) != 0x1);

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            /** \brief ��ȡX����ٶ� */
            ret = __fxos8700cq_read(p_this, __FXOS8700CQ_REG_OUT_X_MSB, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);

            /** \brief X����ٶ� */
            p_buf[i].val = __fxos8700cq_get_accel_value(p_this, tem_data); 
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

        } else if (cur_id == 1) {

            /** \brief ��ȡY����ٶ� */
            ret = __fxos8700cq_read(p_this, __FXOS8700CQ_REG_OUT_Y_MSB, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);
           
            /** \brief Y����ٶ� */
            p_buf[i].val = __fxos8700cq_get_accel_value(p_this, tem_data); 
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

        } else if (cur_id == 2) {

            /** \brief ��ȡZ����ٶ� */
            ret = __fxos8700cq_read(p_this, __FXOS8700CQ_REG_OUT_Z_MSB, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);
           
            /** \brief Z����ٶ� */
            p_buf[i].val = __fxos8700cq_get_accel_value(p_this, tem_data);
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

        } else if (cur_id == 3) {

            /** \brief ��ȡX����� */
            ret = __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_OUT_X_MSB, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);
           
            /** \brief X����� */
            p_buf[i].val = __FXOS8700CQ_GET_MAG_VALUE(tem_data);
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

        } else if (cur_id == 4) {

            /** \brief ��ȡY����� */
            ret = __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_OUT_Y_MSB, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);
           
            /** \brief Y����� */
            p_buf[i].val = __FXOS8700CQ_GET_MAG_VALUE(tem_data);
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

        } else if (cur_id == 5) {

            /** \brief ��ȡZ����� */
            ret = __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_OUT_Z_MSB, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __FXOS8700CQ_UINT8_TO_UINT16(reg_data);
           
            /** \brief Z����� */
            p_buf[i].val = __FXOS8700CQ_GET_MAG_VALUE(tem_data);
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO;/*< \brief ��λĬ��Ϊ0:10^(-6)*/

        } else {
            return -AM_ENODEV;  /*< \brief ���˴�ͨ�������ڸô�������ֱ�ӷ��� */
        }
    }

    return ret;
}

/*
 * \brief ����ѡ������
 */
am_local am_err_t  __reg_attr_range_set (am_sensor_fxos8700cq_dev_t *p_this, 
                                         uint8_t                 range)
{
    uint8_t range_cfg = 0;

    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_XYZ_DATA_CFG, &range_cfg, 1);
    range_cfg &= (~(0x03 << 0));

    switch (range) {
    case 2:
        range_cfg |= __FXOS8700CQ_RANGE_SET_2G;
        break;
    case 4:
        range_cfg |= __FXOS8700CQ_RANGE_SET_4G;
        break;
    case 8:
        range_cfg |= __FXOS8700CQ_RANGE_SET_8G;
        break;
    default:
        break;
    }

    return __fxos8700cq_write(p_this, __FXOS8700CQ_REG_XYZ_DATA_CFG, &range_cfg, 1);
}

/** \brief ʹ�ܴ�����ͨ�� */
am_local am_err_t __pfn_enable (void            *p_drv,
                                const int       *p_ids,
                                int              num,
                                am_sensor_val_t *p_result)
{
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    uint8_t ctrl_reg1 = 0;
    uint8_t ctrl_reg2 = 0;
    uint8_t m_ctrl_reg1 = 0;
    uint8_t m_ctrl_reg2 = 0;

    am_err_t ret = -AM_ENODEV;
    am_err_t curent_ret = AM_OK;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0 || cur_id == 1 || cur_id == 2 || 
            cur_id == 3 || cur_id == 4 || cur_id == 5) {
            if (p_result != NULL) {
                p_result[i].val = AM_OK;
            }

            AM_BIT_SET(p_this->trigger, 14 - cur_id);

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
        AM_BIT_SET(p_this->trigger, 15);
    }    

    /* �������ģʽʱ���û������޸ĸ��Ĵ�����ֵ */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_CTRL_REG1, &ctrl_reg1, 1);
    ctrl_reg1 &= __FXOS8700CQ_STANDBY_MODE;
    ret = __fxos8700cq_write(p_this, __FXOS8700CQ_REG_CTRL_REG1, &ctrl_reg1, 1);
    if (ret != AM_OK) {
        am_kprintf("\r\nSensor FXOS8700CQ failed to enter standby mode! \r\n");
    }

    /* ��У׼�����ù����������ģʽ */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_CTRL_REG1, &m_ctrl_reg1, 1);
    m_ctrl_reg1 |= (p_this->dev_info->m_hms_type |
                    ((p_this->dev_info->m_os) << 2)|
                    ((p_this->dev_info->m_acal) << 7));
    __fxos8700cq_write(p_this, __FXOS8700CQ_REG_M_CTRL_REG1, &m_ctrl_reg1, 1);

    /* ʹ�ܻ��ģʽ�µ�ַ���� */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_M_CTRL_REG2, &m_ctrl_reg2, 1);
    m_ctrl_reg2 |= ((p_this->dev_info->hyb_autoinc_mode) << 5);
    __fxos8700cq_write(p_this, __FXOS8700CQ_REG_M_CTRL_REG2, &m_ctrl_reg2, 1);

    if (p_this->sam_range.val == 0) {
        /* Ĭ������Ϊ��4G */
        p_this->sam_range.val  = 4;
        p_this->sam_range.unit = AM_SENSOR_UNIT_BASE;
    }

    /* �������� */ 
    ret = __reg_attr_range_set(p_this, p_this->sam_range.val);
    if (ret != AM_OK) {
        curent_ret = ret;
    }

    //�߷ֱ���ģʽ
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_CTRL_REG2, &ctrl_reg2, 1);
    ctrl_reg2 &= (~(0x03 << 0));
    ctrl_reg2 |= ((p_this->dev_info->mods) << 0);
    __fxos8700cq_write(p_this, __FXOS8700CQ_REG_CTRL_REG2, &ctrl_reg2, 1);

    /* ����ODR������������ʹ������ģʽ */
    ctrl_reg1 &= 0xC2;
    ctrl_reg1 |= (((p_this->dev_info->odr_selection) << 3) | 
                    ((p_this->dev_info->lnoise) << 2) |
                    __FXOS8700CQ_ACTIVE_MODE);
    ret = __fxos8700cq_write(p_this, __FXOS8700CQ_REG_CTRL_REG1, &ctrl_reg1, 1);
    if (ret != AM_OK) {
        am_kprintf("\r\nSensor FXOS8700CQ failed to enable! \r\n");
    }

    return curent_ret;
}

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result)
{
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;
    uint8_t ctrl_reg1 = 0;
    
    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0 || cur_id == 1 || cur_id == 2 || 
            cur_id == 3 || cur_id == 4 || cur_id == 5) {

            AM_BIT_CLR(p_this->trigger, 14 - cur_id);
            ret = AM_OK;

        } else {
            ret = -AM_ENODEV;
        }

        if (p_result != NULL) {
            p_result[i].val = ret;
        }
    }

    if ((AM_BIT_GET(p_this->trigger, 14) == 0)
            && (AM_BIT_GET(p_this->trigger, 13) == 0)
            && (AM_BIT_GET(p_this->trigger, 12) == 0)
            && (AM_BIT_GET(p_this->trigger, 11) == 0)
            && (AM_BIT_GET(p_this->trigger, 10) == 0)
            && (AM_BIT_GET(p_this->trigger, 9) == 0)) {

        /* ����Ϊ����ģʽ */
        ret = __fxos8700cq_write (p_this, __FXOS8700CQ_REG_CTRL_REG1, &ctrl_reg1, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        if (cur_ret == AM_OK) {
            AM_BIT_CLR(p_this->trigger, 15);
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
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_drv;

    am_err_t cur_ret = AM_OK;

    am_sensor_val_t sensor_val = {0, 0};

    am_sensor_val_t __sampling_range = {0, 0};

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if ((id != AM_FXOS8700CQ_CHAN_1) && (id != AM_FXOS8700CQ_CHAN_2) &&
        (id != AM_FXOS8700CQ_CHAN_3)) {
        return -AM_ENODEV;
    }

    switch (attr) {

    /* �޸����� */
    case AM_SENSOR_ATTR_FULL_SCALE:

        sensor_val.unit = p_val->unit;
        sensor_val.val  = p_val->val;
    
        if (sensor_val.val < 2 || sensor_val.val > 8) {
            return -AM_ENOTSUP;
        }

        am_sensor_val_unit_convert(&sensor_val, 1, AM_SENSOR_UNIT_BASE);

        if (sensor_val.val == 2) {
            __sampling_range.val = 2;
        } else if (sensor_val.val == 4) {
            __sampling_range.val = 4;
        } else if (sensor_val.val == 8) {
            __sampling_range.val = 8;
        }

        __reg_attr_range_set(p_this, __sampling_range.val);

        /* ����������Ϣ */
        p_this->sam_range.val  = __sampling_range.val;
        p_this->sam_range.unit = __sampling_range.unit;

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
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_drv;

    am_err_t ret = AM_OK;

    if ((id != AM_FXOS8700CQ_CHAN_1) && (id != AM_FXOS8700CQ_CHAN_2)&&
        (id != AM_FXOS8700CQ_CHAN_3)) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    switch (attr) {

    /* ��ȡ���� */
    case AM_SENSOR_ATTR_FULL_SCALE:

        p_val->val  = p_this->sam_range.val;
        p_val->unit = p_this->sam_range.unit;
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
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_drv;

    if (id != 0 && id != 1 && id != 2 && 
        id != 3 && id != 4 && id != 5) {
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
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;
    uint8_t reg_data = 0;
    uint8_t ctrl_reg1 = 0;

    if (id != 0 && id != 1 && id != 2 && 
        id != 3 && id != 4 && id != 5) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (p_this->trigger & 0x40) {
        return AM_OK;
    }

    /* �������ģʽʱ���û������޸ĸ��Ĵ�����ֵ */
    __fxos8700cq_read(p_this, __FXOS8700CQ_REG_CTRL_REG1, &ctrl_reg1, 1);
    ctrl_reg1 &= __FXOS8700CQ_STANDBY_MODE;
    __fxos8700cq_write(p_this, __FXOS8700CQ_REG_CTRL_REG1, &ctrl_reg1, 1);

    /** \brief ʹ������׼�������ж� */
    reg_data = __FXOS8700CQ_INT_DRDY_ENABLE;
    ret = __fxos8700cq_write(p_this, __FXOS8700CQ_REG_CTRL_REG4, &reg_data, 1);
    if ( ret != AM_OK) {
        cur_ret = ret;
    }

    /** \brief ����׼�������жϱ����͵�INT1 */
    reg_data = __FXOS8700CQ_EN_INT1_DRDY;
    ret = __fxos8700cq_write(p_this, __FXOS8700CQ_REG_CTRL_REG5, &reg_data, 1);
    if ( ret != AM_OK) {
        cur_ret = ret;
    }

    /* ACTIVEģʽ */
    ctrl_reg1 |= __FXOS8700CQ_ACTIVE_MODE;
    __fxos8700cq_write(p_this, __FXOS8700CQ_REG_CTRL_REG1, &ctrl_reg1, 1);

    if (p_this->dev_info->trigger_pin != -1) {
        
        /* �򿪴������� */
        ret = am_gpio_trigger_on(p_this->dev_info->trigger_pin);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }

    if (cur_ret == AM_OK && id == 0) {
        AM_BIT_SET(p_this->trigger, 0);
        AM_BIT_SET(p_this->trigger, 6);
    }
    if (cur_ret == AM_OK && id == 1) {
        AM_BIT_SET(p_this->trigger, 1);
        AM_BIT_SET(p_this->trigger, 6);
    }
    if (cur_ret == AM_OK && id == 2) {
        AM_BIT_SET(p_this->trigger, 2);
        AM_BIT_SET(p_this->trigger, 6);
    }
    if (cur_ret == AM_OK && id == 3) {
        AM_BIT_SET(p_this->trigger, 3);
        AM_BIT_SET(p_this->trigger, 6);
    }
    if (cur_ret == AM_OK && id == 4) {
        AM_BIT_SET(p_this->trigger, 4);
        AM_BIT_SET(p_this->trigger, 6);
    }
    if (cur_ret == AM_OK && id == 5) {
        AM_BIT_SET(p_this->trigger, 5);
        AM_BIT_SET(p_this->trigger, 6);
    }
    return cur_ret;
}

/** \brief �رմ��� */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id)
{
    am_sensor_fxos8700cq_dev_t* p_this = (am_sensor_fxos8700cq_dev_t*)p_drv;

    am_err_t cur_ret = AM_OK;
    am_err_t ret     = AM_OK;
    uint8_t reg_data = 0;
    
    if (id != 0 && id != 1 && id != 2 && 
        id != 3 && id != 4 && id != 5) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    p_this->pfn_trigger_cb[id] = NULL;
    p_this->p_arg[id]          = NULL;
    p_this->flags[id]          = 0;

    AM_BIT_CLR(p_this->trigger, id);

    if ((p_this->trigger & 0x3F) == 0) {

        /** \brief ��������׼�������ж� */
        reg_data = __FXOS8700CQ_INT_DRDY_DISABLE;
        ret = __fxos8700cq_write(p_this, __FXOS8700CQ_REG_CTRL_REG4, &reg_data, 1);
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
            AM_BIT_CLR(p_this->trigger, 6);
        }
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ FXOS8700CQ ��ʼ��
 */
am_sensor_handle_t am_sensor_fxos8700cq_init (
        am_sensor_fxos8700cq_dev_t           *p_dev,
        const am_sensor_fxos8700cq_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle)
{
    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t fxos8700cq_id = 0;
    uint8_t ctrl_reg2 = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->fxos8700cq_dev.p_drv   = p_dev;
    p_dev->fxos8700cq_dev.p_funcs = &__g_sensor_fxos8700cq_funcs;
    p_dev->dev_info            = p_devinfo;
    p_dev->pfn_trigger_cb[0]   = NULL;
    p_dev->pfn_trigger_cb[1]   = NULL;
    p_dev->pfn_trigger_cb[2]   = NULL;
    p_dev->pfn_trigger_cb[3]   = NULL;
    p_dev->pfn_trigger_cb[4]   = NULL;
    p_dev->pfn_trigger_cb[5]   = NULL;
    p_dev->p_arg[0]            = NULL;
    p_dev->p_arg[1]            = NULL;
    p_dev->p_arg[2]            = NULL;
    p_dev->p_arg[3]            = NULL;
    p_dev->p_arg[4]            = NULL;
    p_dev->p_arg[5]            = NULL;
    p_dev->flags[0]            = 0;
    p_dev->flags[1]            = 0;
    p_dev->flags[2]            = 0;
    p_dev->flags[3]            = 0;
    p_dev->flags[4]            = 0;
    p_dev->flags[5]            = 0;
    p_dev->trigger             = 0;
    p_dev->data[0].val         = 0;
    p_dev->data[0].unit        = AM_SENSOR_UNIT_INVALID;
    p_dev->data[1].val         = 0;
    p_dev->data[1].unit        = AM_SENSOR_UNIT_INVALID;
    p_dev->data[2].val         = 0;
    p_dev->data[2].unit        = AM_SENSOR_UNIT_INVALID;
    p_dev->data[3].val         = 0;
    p_dev->data[3].unit        = AM_SENSOR_UNIT_INVALID;
    p_dev->data[4].val         = 0;
    p_dev->data[4].unit        = AM_SENSOR_UNIT_INVALID;
    p_dev->data[5].val         = 0;
    p_dev->data[5].unit        = AM_SENSOR_UNIT_INVALID;
    p_dev->sam_range.val       = 0;
    p_dev->sam_range.unit      = AM_SENSOR_UNIT_INVALID;

    /* �ⲿ�ж����� */
    if (p_devinfo->trigger_pin != -1) {
        am_gpio_pin_cfg(p_devinfo->trigger_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);
        am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                __fxos8700cq_alarm_callback,
                                (void*)p_dev);
        am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_FALL); /* �½��ش��� */
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    /* ��ȡID */
    ret = __fxos8700cq_read(p_dev, __FXOS8700CQ_REG_WHO_AM_I, &fxos8700cq_id, 1);
    if (ret != AM_OK || fxos8700cq_id != __FXOS8700CQ_MY_ID) {
        cur_ret = ret;
    }

    if (cur_ret != AM_OK) {
        am_kprintf("fxos8700cq_id = 0x%x", fxos8700cq_id);
        am_kprintf("\r\nSensor FXOS8700CQ Init is ERROR! \r\n");
        return NULL;
    }

    //��λFXOS8700CQ
    ctrl_reg2 |= __FXOS8700CQ_SOFTWARE_RESET;
    ret = __fxos8700cq_write(p_dev, __FXOS8700CQ_REG_CTRL_REG2, &ctrl_reg2, 1);
    if (ret != AM_OK) {
        am_kprintf("\r\nSensor FXOS8700CQ reset failed! \r\n");
    }

    am_mdelay(2);

    return &(p_dev->fxos8700cq_dev);
}

/**
 * \brief ������ FXOS8700CQ ȥ��ʼ��
 */
am_err_t am_sensor_fxos8700cq_deinit (am_sensor_handle_t handle)
{
    am_sensor_fxos8700cq_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->fxos8700cq_dev.p_drv   = NULL;
    p_dev->fxos8700cq_dev.p_funcs = NULL;
    p_dev->dev_info            = NULL;

    return AM_OK;
}


/* end of file */

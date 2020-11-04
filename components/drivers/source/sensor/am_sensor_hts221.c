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
 * \brief ������ HTS221 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-26  wan, first implementation.
 * \endinternal
 */

#include "am_sensor_hts221.h"
#include "am_sensor.h"
#include "am_gpio.h"
#include "am_vdebug.h"

/*******************************************************************************
 * �궨��
 ******************************************************************************/
#define __HTS221_REG_WHO_IM_I     (0x0F)    /*< \brief �豸ID��ַ             */
#define __HTS221_MY_ID            (0xBC)    /*< \brief �豸ID                 */
#define __HTS221_REG_AV_CONF      (0x10)    /*< \brief ���ò���������ֵ��ַ   */
#define __HTS221_REG_CTRL_REG1    (0x20)    /*< \brief ���ƼĴ���1��ַ        */
#define __HTS221_REG_CTRL_REG2    (0x21)    /*< \brief ���ƼĴ���2��ַ        */
#define __HTS221_REG_CTRL_REG3    (0x22)    /*< \brief ���ƼĴ���3��ַ        */
#define __HTS221_REG_STATUS       (0x27)    /*< \brief ״̬�Ĵ�����ַ         */
#define __HTS221_REG_H_OUT_L      (0x28)    /*< \brief ʪ�ȵ��ֽڵ�ַ         */
#define __HTS221_REG_H_OUT_H      (0x29)    /*< \brief ʪ�ȸ��ֽڵ�ַ         */
#define __HTS221_REG_T_OUT_L      (0x2A)    /*< \brief �¶ȵ��ֽڵ�ַ         */
#define __HTS221_REG_T_OUT_H      (0x2B)    /*< \brief �¶ȸ��ֽڵ�ַ         */

#define __HTS221_REG_H0_OUT       (0x36)    /*< \brief ʪ��У׼ֵ0��ַ        */
#define __HTS221_REG_H0_OUT_LEN   (2)       /*< \brief ʪ��У׼ֵ0��ַ����    */
#define __HTS221_REG_H1_OUT       (0x3A)    /*< \brief ʪ��У׼ֵ1��ַ        */
#define __HTS221_REG_H1_OUT_LEN   (2)       /*< \brief ʪ��У׼ֵ1��ַ����    */
#define __HTS221_REG_H0_rH_2      (0x30)    /*< \brief ʪ��У׼����0��ַ      */
#define __HTS221_REG_H1_rH_2      (0x31)    /*< \brief ʪ��У׼����1��ַ      */

#define __HTS221_REG_T0_OUT       (0x3C)    /*< \brief �¶�У׼ֵ0��ַ        */
#define __HTS221_REG_T0_OUT_LEN   (2)       /*< \brief �¶�У׼ֵ0��ַ����    */
#define __HTS221_REG_T1_OUT       (0x3E)    /*< \brief �¶�У׼ֵ1��ַ        */
#define __HTS221_REG_T1_OUT_LEN   (2)       /*< \brief �¶�У׼ֵ1��ַ����    */
#define __HTS221_REG_T0_degC_8    (0x32)    /*< \brief �¶�У׼����0��ַ      */
#define __HTS221_REG_T1_degC_8    (0x33)    /*< \brief �¶�У׼����1��ַ      */

#define __HTS221_REG_T1_T0_MSB    (0x35)    /*< \brief �¶ȸ�λ������ַ       */

/** \brief ����У׼ֵx0��y0��x1��y1 ���������x���¶�ʪ��ʵ��ֵ ������10^6�� */
#define __GET_VALUE(x, x0, y0, x1, y1)                                 \
        ((int32_t)(1000000 * (int64_t)(((y1)-(y0))*(x) + (x1)*(y0) -   \
         (x0)*(y1)) / ((x1) - (x0))))

/** \brief ������int8ת��Ϊһ��int16���� */
#define __HTS221_UINT8_TO_UINT16(buff) ((int16_t)((buff[1] << 8) | buff[0]))

/** \brief ������ȡ�Ĵ��� */
#define __HTS221_IIC_CONTINUE_READ     (0x80)

/** \brief ����Ƶ��Ϊһ�� */
#define __HTS221_RATE_SET_ONE(data)    (((data) & (~0x3)) | 0x0)

/** \brief ����Ƶ��Ϊ1 */
#define __HTS221_RATE_SET_1S(data)     (((data) & (~0x3)) | 0x1)

/** \brief ����Ƶ��Ϊ7 */
#define __HTS221_RATE_SET_7S(data)     (((data) & (~0x3)) | 0x2)

/** \brief ����Ƶ��Ϊ12 */
#define __HTS221_RATE_SET_12S(data)    (((data) & (~0x3)) | 0x3)

/** \brief ��ʼһ�����ݲɼ� */
#define __HTS221_ONE_SHOT_START        (0x1)

/** \brief ģ������ */
#define __HTS221_START                 (0x1<<7)

/** \brief ģ��ر� */
#define __HTS221_CLOSE                 (~(0x1<<7))

/** \brief ��ȡHUM״̬λ */
#define __HTS221_GET_HUM_STATUS(reg)   (((reg) >> 1) & 0x1)

/** \brief ��ȡTEM״̬λ */
#define __HTS221_GET_TEM_STATUS(reg)   ((reg) & 0x1)

/** \brief ʹ�����ݿɶ����� */
#define __HTS221_TRIGGER_READ          (0x1<<2)

/** \brief �������ݿɶ����� */
#define __HTS221_TRIGGER_CLOSE         (~(0x1<<2))

/** \brief ��ȡ�¶�У׼ֵ1 */
#define __HTS221_GET_TEM_VALUE1(val, data) \
                      ((int8_t)(((((val) & 0x3) << 8) | (data)) >> 3))

/** \brief ��ȡ�¶�У׼ֵ2 */
#define __HTS221_GET_TEM_VALUE2(val, data) \
                      ((int8_t)(((((val) & 0xc) << 6) | (data)) >> 3))

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
am_local am_const struct am_sensor_drv_funcs __g_sensor_hts221_funcs = {
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
/*
 * \brief hts221 д����
 */
am_local am_err_t __hts221_write (am_sensor_hts221_dev_t *p_this,
                                  uint32_t                subaddr,
                                  uint8_t                *p_buf,
                                  uint32_t                nbytes)
{
    return am_i2c_write(&p_this->i2c_dev,
                        subaddr | __HTS221_IIC_CONTINUE_READ,
                        p_buf,
                        nbytes);
}

/*
 * \brief hts221 ������
 */
am_local am_err_t __hts221_read (am_sensor_hts221_dev_t *p_this,
                                 uint32_t                subaddr,
                                 uint8_t                *p_buf,
                                 uint32_t                nbytes)
{
    return am_i2c_read(&p_this->i2c_dev,
                       subaddr | __HTS221_IIC_CONTINUE_READ,
                       p_buf,
                       nbytes);
}

/** \breif �жϻص����� */
am_local void __hts221_alarm_callback (void *p_arg)
{
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /*< \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_arg;

    am_hts221_calibration_data_t *hum = &p_this->cal_val[0];
    am_hts221_calibration_data_t *tem = &p_this->cal_val[1];

    uint8_t current_data[4] = {0};
    uint8_t *p_current_data = current_data + 2;

    int16_t hum_data = 0;
    int16_t tem_data = 0;

    /* �������ݺ��Զ����жϱ�־λ */
    __hts221_read(p_this, __HTS221_REG_H_OUT_L, current_data, 4);

    /* ��ȡʪ�� */
    hum_data = __HTS221_UINT8_TO_UINT16(current_data);
    p_this->data[0].val = __GET_VALUE(hum_data,
                                      hum->x0,
                                      hum->y0,
                                      hum->x1,
                                      hum->y1);
    p_this->data[0].unit = AM_SENSOR_UNIT_MICRO;

    /* ��ȡ�¶� */
    tem_data = __HTS221_UINT8_TO_UINT16(p_current_data);
    p_this->data[1].val = __GET_VALUE(tem_data,
                                      tem->x0,
                                      tem->y0,
                                      tem->x1,
                                      tem->y1);
    p_this->data[1].unit = AM_SENSOR_UNIT_MICRO;

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

/*
 * \brief ����ѡ��
 */
am_local am_err_t  __reg_attr_set (am_sensor_hts221_dev_t *p_this, uint8_t rate)
{
     am_err_t ret = AM_OK;

     uint8_t rate_cfg = 0;

     ret = __hts221_read(p_this, __HTS221_REG_CTRL_REG1, &rate_cfg, 1);
     if (ret != AM_OK) {
         return ret;
     }

     switch (rate) {
     case 0:
         rate_cfg = __HTS221_RATE_SET_ONE(rate_cfg);
         break;
     case 1:
         rate_cfg = __HTS221_RATE_SET_1S(rate_cfg);
         break;
     case 2:
         rate_cfg = __HTS221_RATE_SET_7S(rate_cfg);
         break;
     case 3:
         rate_cfg = __HTS221_RATE_SET_12S(rate_cfg);
         break;
     default:
         break;
     }

     return __hts221_write(p_this, __HTS221_REG_CTRL_REG1, &rate_cfg, 1);
}

/*
 * \brief ��ȡʪ��У׼ֵ
 */
am_local am_err_t __hts221_get_hum_cal (am_sensor_hts221_dev_t *p_this)
{
    uint8_t buff[2] = {0};

    am_err_t ret = AM_OK;

    /*
     * \brief ����Ϊ��ȡʪ�ȵ�У׼���ݵ�2��
     */
    ret = __hts221_read(p_this,
                        __HTS221_REG_H0_OUT,
                        buff,
                        __HTS221_REG_H0_OUT_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val[0].x0 = __HTS221_UINT8_TO_UINT16(buff);

    ret = __hts221_read(p_this, __HTS221_REG_H0_rH_2, buff, 1);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val[0].y0 = (int8_t)(buff[0] >> 1);

    ret = __hts221_read(p_this,
                        __HTS221_REG_H1_OUT,
                        buff,
                        __HTS221_REG_H1_OUT_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val[0].x1 = __HTS221_UINT8_TO_UINT16(buff);

    ret = __hts221_read(p_this, __HTS221_REG_H1_rH_2, buff, 1);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val[0].y1 = (int8_t)(buff[0] >> 1);

    return ret;
}

/*
 * \brief ��ȡ�¶�У׼ֵ
 */
am_local am_err_t __hts221_get_tem_cal (am_sensor_hts221_dev_t *p_this)
{
    uint8_t buff[2] = {0};

    uint8_t tem_msb_val = 0;

    am_err_t ret = AM_OK;

    /*
     * \brief ����Ϊ��ȡ�¶ȵ�У׼���ݵ�2��
     */
    ret = __hts221_read(p_this, __HTS221_REG_T1_T0_MSB, &buff[0], 1);
    if (ret != AM_OK) {
        return ret;
    }
    tem_msb_val = buff[0];

    ret = __hts221_read(p_this,
                        __HTS221_REG_T0_OUT,
                        buff,
                        __HTS221_REG_T0_OUT_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val[1].x0 = __HTS221_UINT8_TO_UINT16(buff);

    ret = __hts221_read(p_this, __HTS221_REG_T0_degC_8, buff, 1);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val[1].y0 = __HTS221_GET_TEM_VALUE1(tem_msb_val, buff[0]);

    ret = __hts221_read(p_this,
                        __HTS221_REG_T1_OUT,
                        buff,
                        __HTS221_REG_T1_OUT_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val[1].x1 = __HTS221_UINT8_TO_UINT16(buff);

    ret = __hts221_read(p_this, __HTS221_REG_T1_degC_8, buff, 1);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val[1].y1 = __HTS221_GET_TEM_VALUE2(tem_msb_val, buff[0]);

    return ret;
}

/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (id == AM_HTS221_CHAN_1) {
        return AM_SENSOR_TYPE_HUMIDITY;
    } else if (id == AM_HTS221_CHAN_2) {
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
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_drv;

    am_hts221_calibration_data_t *hum = &p_this->cal_val[0];
    am_hts221_calibration_data_t *tem = &p_this->cal_val[1];

    am_err_t ret = AM_OK;

    uint8_t status_val = 0;

    uint8_t reg_data[2] = {0};

    int16_t hum_data = 0;
    int16_t tem_data = 0;

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
        ret = __hts221_read(p_this, __HTS221_REG_STATUS, &status_val, 1);
        if (ret != AM_OK) {
            return ret;
        }
    } while (__HTS221_GET_HUM_STATUS(status_val) != 0x1 ||
             __HTS221_GET_TEM_STATUS(status_val) != 0x1 );

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            /** \brief ��ȡʪ��*/
            ret = __hts221_read(p_this, __HTS221_REG_H_OUT_L, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            hum_data = __HTS221_UINT8_TO_UINT16(reg_data);
            p_buf[i].val  = __GET_VALUE(hum_data,
                                        hum->x0,
                                        hum->y0,
                                        hum->x1,
                                        hum->y1); /*< \brief ʪ�� */
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/

        } else if (cur_id == 1) {

            /** \brief ��ȡ�¶� */
            ret = __hts221_read(p_this, __HTS221_REG_T_OUT_L, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __HTS221_UINT8_TO_UINT16(reg_data);
            p_buf[i].val  = __GET_VALUE(tem_data,
                                        tem->x0,
                                        tem->y0,
                                        tem->x1,
                                        tem->y1); /*< \brief �¶� */
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/

        } else {
            return -AM_ENODEV;  /*< \brief ���˴�ͨ�������ڸô�������ֱ�ӷ��� */
        }
    }

    ret = __hts221_read(p_this, __HTS221_REG_CTRL_REG2, &status_val, 1);
    if (ret != AM_OK) {
        return ret;
    }

    status_val |= __HTS221_ONE_SHOT_START;
    ret = __hts221_write(p_this, __HTS221_REG_CTRL_REG2, &status_val, 1);
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
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    uint8_t ctrl_reg1 = 0;
    uint8_t open_one_shot = 0;

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

    if (ret != AM_OK) {     /*< \breif �������û�иô�������ͨ�����룬���˳� */
        return curent_ret;
    }

    ret = __hts221_read(p_this, __HTS221_REG_CTRL_REG1, &ctrl_reg1, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }

    /** \brief ʹ�ܸ�ͨ�� */
    ctrl_reg1 |= __HTS221_START;
    ret = __hts221_write(p_this, __HTS221_REG_CTRL_REG1, &ctrl_reg1, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }

    if (ret == AM_OK) {
        AM_BIT_SET(p_this->trigger, 7);
        AM_BIT_SET(p_this->trigger, 6);
        AM_BIT_SET(p_this->trigger, 5);
    }

    ret = __hts221_read(p_this, __HTS221_REG_CTRL_REG2, &open_one_shot, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }

    open_one_shot |= __HTS221_ONE_SHOT_START;
    ret = __hts221_write(p_this, __HTS221_REG_CTRL_REG2, &open_one_shot, 1);
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
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t ctrl_reg = 0;

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

        ret = __hts221_read(p_this, __HTS221_REG_CTRL_REG1, &ctrl_reg, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        /** \brief �رո�ͨ�� */
        ctrl_reg &= __HTS221_CLOSE;
        ret = __hts221_write(p_this, __HTS221_REG_CTRL_REG1, &ctrl_reg, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

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
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    am_sensor_val_t sensor_val = {0, 0};

    am_sensor_val_t __sampling_rate = {0, 0};

    uint8_t rate = 0;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if ((id != AM_HTS221_CHAN_1) && (id != AM_HTS221_CHAN_2)) {
        return -AM_ENODEV;
    }

    switch (attr) {

    /* �޸�Ƶ�� */
    case AM_SENSOR_ATTR_SAMPLING_RATE:

        if (sensor_val.val < 0 || sensor_val.val > 13) {
            return -AM_ENOTSUP;
        }

        sensor_val.unit = p_val->unit;
        sensor_val.val  = p_val->val;
        am_sensor_val_unit_convert(&sensor_val, 1, AM_SENSOR_UNIT_BASE);

        if (sensor_val.val == 0) {
            rate = 0;
            __sampling_rate.val = 0;
        } else if (sensor_val.val > 0 && sensor_val.val < 4) {
            rate = 1;
            __sampling_rate.val = 1;
        } else if (sensor_val.val >= 4 && sensor_val.val < 10) {
            rate = 2;
            __sampling_rate.val = 7;
        } else if (sensor_val.val >= 10 && sensor_val.val <= 13) {
            rate = 3;
            __sampling_rate.val = 125;
            __sampling_rate.unit = AM_SENSOR_UNIT_DECI;
        }

        ret = __reg_attr_set(p_this, rate);
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
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_drv;

    am_err_t ret = AM_OK;

    if ((id != AM_HTS221_CHAN_1) && (id != AM_HTS221_CHAN_2)) {
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
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_drv;

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
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t reg_data = 0;

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (p_this->trigger & 0x4) {
        return AM_OK;
    }

    ret = __hts221_read(p_this, __HTS221_REG_CTRL_REG3, &reg_data, 1);
    if ( ret != AM_OK) {
        cur_ret = ret;
    }

    /** \brief ʹ�����ݿɶ����� */
    reg_data |= __HTS221_TRIGGER_READ;
    ret = __hts221_write(p_this, __HTS221_REG_CTRL_REG3, &reg_data, 1);
    if ( ret != AM_OK) {
        cur_ret = ret;
    }

    if (p_this->dev_info->trigger_pin != -1) {
        __hts221_read(p_this, __HTS221_REG_H_OUT_H, &reg_data, 1);
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
    am_sensor_hts221_dev_t* p_this = (am_sensor_hts221_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t reg_data = 0;

    am_sensor_val_t p_val = {0, 0};

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

        ret = __hts221_read(p_this, __HTS221_REG_CTRL_REG3, &reg_data, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /** \brief �������ݿɶ����� */
        reg_data &= __HTS221_TRIGGER_CLOSE;
        ret = __hts221_write(p_this, __HTS221_REG_CTRL_REG3, &reg_data, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

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
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ HTS221 ��ʼ��
 */
am_sensor_handle_t am_sensor_hts221_init (
        am_sensor_hts221_dev_t           *p_dev,
        const am_sensor_hts221_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle)
{
    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t hts221_id = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->hts221_dev.p_drv   = p_dev;
    p_dev->hts221_dev.p_funcs = &__g_sensor_hts221_funcs;
    p_dev->dev_info           = p_devinfo;
    p_dev->pfn_trigger_cb[0]  = NULL;
    p_dev->pfn_trigger_cb[1]  = NULL;
    p_dev->p_arg[0]           = NULL;
    p_dev->p_arg[1]           = NULL;
    p_dev->flags[0]           = 0;
    p_dev->flags[1]           = 0;
    p_dev->sam_rate.val       = 0;
    p_dev->sam_rate.unit      = 0;
    p_dev->trigger            = 0;
    p_dev->data[0].val        = 0;
    p_dev->data[0].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[1].val        = 0;
    p_dev->data[1].unit       = AM_SENSOR_UNIT_INVALID;

    if (p_devinfo->trigger_pin != -1) {
        am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                __hts221_alarm_callback,
                                (void*)p_dev);
        am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_RISE);
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    ret = __hts221_read(p_dev, __HTS221_REG_WHO_IM_I, &hts221_id, 1);
    if (ret != AM_OK || hts221_id != __HTS221_MY_ID) {
        cur_ret = ret;
    } else {

        /* ��ȡʪ��У׼ֵ */
        ret = __hts221_get_hum_cal(p_dev);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /* ��ȡ�¶�У׼ֵ */
        ret = __hts221_get_tem_cal(p_dev);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }

    if (cur_ret != AM_OK) {
        am_kprintf("\r\nSensor HTS221 Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->hts221_dev);
}

/**
 * \brief ������ HTS221 ȥ��ʼ��
 */
am_err_t am_sensor_hts221_deinit (am_sensor_handle_t handle)
{
    am_sensor_hts221_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->hts221_dev.p_drv   = NULL;
    p_dev->hts221_dev.p_funcs = NULL;
    p_dev->dev_info           = NULL;

    return AM_OK;
}

/* end of file */

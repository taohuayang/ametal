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
 * \brief ������ AS621X �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-21  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_as621x.h"
#include "am_sensor.h"
#include "am_gpio.h"
#include "am_vdebug.h"

/**
 * \note 
 * 1.��/д���ȴ�����ֽ�(MSB),�ٴ�����ֽ�(LSB)
 * 2.�Ƚ�ģʽ���¶�ֵ���ڻ����THIGH�����������ɼ������ڵ�������������ʱ������
 *             ���������ֱ���¶��½���TLOW��������¶ȱ������
 *             (�Ƚ�ģʽ�£�Alert bit��Alert output������ͬ������)
 *   �ж�ģʽ�����¶�ֵ���ڻ����THIGH�����������ɼ������ڵ�������������ʱ������
 *             ���������ֱ�����κμĴ������ж���������SM=1����������������
 *             һ�����������������¶�ֵ�½���TLOW�����ٴμ�����������һֱ
 *             ���ּ���״ֱ̬������������
 *   
*/

/**< ������Ϣ��� */
#define __AS621X_DEBUG                  (0)

/********************************************************************************
 * �궨��
 ********************************************************************************/
#define  __AS621X_REG_TEMP              (0x00)    /**< \brief �¶����ݼĴ�����ַ    */
#define  __AS621X_REG_CONFIG            (0x01)    /**< \brief ���üĴ�����ַ        */
#define  __AS621X_REG_TLOW              (0x02)    /**< \brief ���¶���ֵ�Ĵ�����ַ  */
#define  __AS621X_REG_THIGH             (0x03)    /**< \brief ���¶���ֵ�Ĵ�����ַ  */

/** \brief ��ȡALλ */
#define __AS621X_AL_GET(data)           (((data) >> 5) & 0x1)

/** \brief ����ת������(Conversion Rate) */
#define __AS621X_CR_SET(data, mask)     (((data) & (~(0x3 << 6))) | (mask << 6))

/** \brief ����SMλ(Sleep Mode) */
#define __AS621X_SM_SET(data, mask)     (((data) & (~(0x1 << 0))) | (mask << 0))

/** \brief ��ȡSMλ */
#define __AS621X_SM_GET(data)           (((data) >> 0) & 0x1)

/** \brief ����IMλ(Interrupt Mode) */
#define __AS621X_IM_SET(data, mask)     (((data) & (~(0x1 << 1))) | (mask << 1))

/** \brief ����POLλ(Polarity) */
#define __AS621X_POL_SET(data, mask)    (((data) & (~(0x1 << 2))) | (mask << 2))

/** \brief ��������������(Consecutive Faults) */
#define __AS621X_CF_SET(data, mask)     (((data) & (~(0x3 << 3))) | (mask << 3))

/** \brief ���õ��δ���λ(Single Shot) */
#define __AS621X_SS_SET(data, mask)     (((data) & (~(0x1 << 7))) | (mask << 7))

/** \brief ��ȡSSλ */
#define __AS621X_SS_GET(data)           (((data) >> 7) & 0x1)

/** \brief ������int8ת��Ϊһ��int16���� */
#define __AS621X_UINT8_TO_UINT16(buff)  ((int16_t)((buff[0] << 8) | buff[1]))

/** \brief ����x���¶�ʵ��ֵ ������10^6�� */
#define __AS621X_GET_VALUE(x)           ((int32_t)(((x * 1000) >> 7) * 1000))

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
am_local am_const struct am_sensor_drv_funcs __g_sensor_as621x_funcs = {
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
 * \brief as621x д����
 */
am_local am_err_t __as621x_write (am_sensor_as621x_dev_t *p_this,
                                  uint32_t                subaddr,
                                  uint8_t                *p_buf,
                                  uint32_t                nbytes)
{
    return am_i2c_write(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief as621x ������
 */
am_local am_err_t __as621x_read (am_sensor_as621x_dev_t *p_this,
                                 uint32_t                subaddr,
                                 uint8_t                *p_buf,
                                 uint32_t                nbytes)
{
    return am_i2c_read(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/** \brief �¶�ת��Ϊ�Ĵ���ֵ */
am_local void __temp_to_value(float temperature, uint8_t *temp)
{
    int16_t temp_val;

    temp_val = (int16_t)(temperature * 128);

    temp[0] = (temp_val & 0xff00) >> 8;
    temp[1] = temp_val & 0xff;
}

/** \brief ������ֵ */
am_local am_err_t __as621x_temp_threshold_set (am_sensor_as621x_dev_t   *p_this,
                                               uint32_t                  subaddr,
                                               float                     temp)
{
    am_err_t ret = AM_OK;

    uint8_t temp_reg[2] = {0};

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    __temp_to_value(temp, temp_reg);

    ret = __as621x_write(p_this, subaddr, temp_reg, 2);

    return ret;
}

/** \brief ��ȡ��ֵ */
am_local am_err_t __as621x_temp_threshold_get (am_sensor_as621x_dev_t   *p_this,
                                               uint32_t                  subaddr,
                                               float                    *p_temp)
{
    am_err_t ret = AM_OK;

    uint8_t temp_reg[2] = {0};

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    ret = __as621x_read(p_this, subaddr, temp_reg, 2);

    *p_temp = (float)(__AS621X_UINT8_TO_UINT16(temp_reg) / 128);

    return ret;
}

/*******************************************************************************/

/** \brief ��ȡ����λ */
am_local am_err_t __as621x_alert_bit_get(am_sensor_as621x_dev_t  *p_this,
                                         uint8_t                 *p_alert_bit)
{
    am_err_t ret = AM_OK;

    uint8_t cfg_reg[2] = {0};

    ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);

    *p_alert_bit = __AS621X_AL_GET(cfg_reg[1]);

    return ret;
}

/** \brief ����ת������ */
am_local am_err_t __as621x_cr_set(am_sensor_as621x_dev_t    *p_this,
                                  uint8_t                    conversion_rate)
{
    uint8_t cfg_reg[2] = {0};

    am_err_t ret = AM_OK;

    ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    cfg_reg[1] = __AS621X_CR_SET(cfg_reg[1], conversion_rate);
    ret = __as621x_write(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ����SMλ(Sleep Mode) */
am_local am_err_t __as621x_sm_set(am_sensor_as621x_dev_t    *p_this,
                                  uint8_t                    sleep_mode)
{
    uint8_t cfg_reg[2] = {0};

    am_err_t ret = AM_OK;

    ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    cfg_reg[0] = __AS621X_SM_SET(cfg_reg[0], sleep_mode);
    ret = __as621x_write(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ��ȡSMλ(Sleep Mode) */
am_local am_err_t __as621x_sm_get(am_sensor_as621x_dev_t    *p_this,
                                    uint8_t                 *p_sm_bit)
{
    am_err_t ret = AM_OK;

    uint8_t cfg_reg[2] = {0};

    ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);

    *p_sm_bit = __AS621X_SM_GET(cfg_reg[0]);

    return ret;
}

/** \brief ����IMλ(Interrupt Mode) */
am_local am_err_t __as621x_im_set(am_sensor_as621x_dev_t    *p_this,
                                  uint8_t                    interrupt_mode)
{
    uint8_t cfg_reg[2] = {0};

    am_err_t ret = AM_OK;

    ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    cfg_reg[0] = __AS621X_IM_SET(cfg_reg[0], interrupt_mode);
    ret = __as621x_write(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ����POLλ(Polarity) */
am_local am_err_t __as621x_polarity_set(am_sensor_as621x_dev_t    *p_this,
                                        am_bool_t                  pol_high)
{
    uint8_t cfg_reg[2] = {0};

    am_err_t ret = AM_OK;

    ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    cfg_reg[0] = __AS621X_POL_SET(cfg_reg[0], pol_high);
    ret = __as621x_write(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ��������������(Consecutive Faults) */
am_local am_err_t __as621x_cf_set(am_sensor_as621x_dev_t    *p_this,
                                  uint8_t                    consecutive_fault)
{
    uint8_t cfg_reg[2] = {0};

    am_err_t ret = AM_OK;

    ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    cfg_reg[0] = __AS621X_CF_SET(cfg_reg[0], consecutive_fault);
    ret = __as621x_write(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ���õ��δ���λ(Single Shot) */
am_local am_err_t __as621x_single_shot(am_sensor_as621x_dev_t   *p_this,
                                       am_bool_t                 conv_enable)
{
    am_err_t ret = AM_OK;

    uint8_t cfg_reg[2] = {0};

    ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    /** \brief ����SSλ */
    cfg_reg[0] = __AS621X_SS_SET(cfg_reg[0], conv_enable);
    ret = __as621x_write(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ���õ��¶���ֵ */
am_local am_err_t __as621x_tlow_threshold_set (am_sensor_as621x_dev_t    *p_this,
                                               float                      tlow_temp)
{
    return __as621x_temp_threshold_set(p_this, __AS621X_REG_TLOW, tlow_temp);
}

/** \brief ���ø��¶���ֵ */
am_local am_err_t __as621x_thigh_threshold_set (am_sensor_as621x_dev_t   *p_this,
                                                float                     thigh_temp)
{
    return __as621x_temp_threshold_set(p_this, __AS621X_REG_THIGH, thigh_temp);
}

/** \brief ��ȡ���¶���ֵ */
am_local am_err_t __as621x_tlow_threshold_get (am_sensor_as621x_dev_t   *p_this,
                                               float                    *p_tlow_temp)
{
    return __as621x_temp_threshold_get(p_this, __AS621X_REG_TLOW, p_tlow_temp);
}

/** \brief ��ȡ���¶���ֵ */
am_local am_err_t __as621x_thigh_threshold_get (am_sensor_as621x_dev_t  *p_this,
                                                float                   *p_thigh_temp)
{
    return __as621x_temp_threshold_get(p_this, __AS621X_REG_THIGH, p_thigh_temp);
}

/*******************************************************************************/

/** \brief AS621X ������ʼ�� */
am_local am_err_t __as621x_param_init(am_sensor_as621x_dev_t    *p_this)
{
    as621x_param_config_t *p_param_config = (as621x_param_config_t *)p_this->dev_info->p_param_default;

    am_err_t ret = AM_OK;

    /* TLOW �Ĵ������� */

    /* ���õ��¶���ֵ */
    ret = __as621x_tlow_threshold_set(p_this, p_param_config->tlow_temp);
    if (ret != AM_OK) {
        return ret;
    }

    /* THIGH �Ĵ������� */

    /* ���ø��¶���ֵ */
    ret = __as621x_thigh_threshold_set(p_this, p_param_config->thigh_temp);
    if (ret != AM_OK) {
        return ret;
    }

    /* CONFIG �Ĵ������� */

    /* ����ת������ */
    ret = __as621x_cr_set(p_this, p_param_config->conversion_rate);
    if (ret != AM_OK) {
        return ret;
    }

    /* ����SMλ��Ĭ��˯��ģʽ */
    ret = __as621x_sm_set(p_this, p_param_config->sleep_mode);
    if (ret != AM_OK) {
        return ret;
    }

    /* ����IMλ���Ƚ�ģʽ */
    ret = __as621x_im_set(p_this, AM_AS621X_COMPARATOR_MODE);
    if (ret != AM_OK) {
        return ret;
    }

    /* ����POLλ��Ĭ�ϵ͵�ƽ���� */
    ret = __as621x_polarity_set(p_this, p_param_config->polarity_high);
    if (ret != AM_OK) {
        return ret;
    }

    /* �����������ϴ�����Ĭ��1�� */
    ret = __as621x_cf_set(p_this, p_param_config->consecutive_faults);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/**
 * \brief AS621X ��ȡ���
 */
am_local am_err_t __as621x_result_get(am_sensor_as621x_dev_t    *p_this,
                                      as621x_result_info_t      *p_result)
{
    am_err_t ret = AM_OK;

    uint8_t result_buf[2]  = {0};   /* ����Ĵ���ֵ */

    int16_t tem_data = 0;           /* ʵ���¶�ֵ */

    /* temperature */
    ret = __as621x_read(p_this, __AS621X_REG_TEMP, result_buf, 2);
    tem_data = __AS621X_UINT8_TO_UINT16(result_buf);    /* ʵ���¶�ֵ */
    p_result->as621x_temperature = __AS621X_GET_VALUE(tem_data);    /* ʵ���¶�ֵ����10^6�� */

    return ret;
}

#if __AS621X_DEBUG
#define __AS621X_UINT16_CONV(buff)  ((uint16_t)((buff[0] << 8) | buff[1]))

struct as621x_debug_info {
    const char  **reg_name_str;
    uint8_t     *reg;
};

const char *__as621x_reg_name_string[] = {
    "TEMP  ",
    "CONFIG",
    "TLOW  ",
    "THIGH ",
};

static uint8_t __as621x_reg_name[] = {
    __AS621X_REG_TEMP,
    __AS621X_REG_CONFIG,
    __AS621X_REG_TLOW,
    __AS621X_REG_THIGH,
};

struct as621x_debug_info __g_as621x_debug_info = {
    __as621x_reg_name_string,
    __as621x_reg_name,
};

/** \brief AS621X ����������мĴ���ֵ */
am_local void __as621x_regval_check(am_sensor_as621x_dev_t *p_this)
{
    uint8_t reg_buf[2] = {0};   /* �ȶ����ֽڣ��ٶ����ֽ� */
    uint16_t reg_val = 0;       /* �Ĵ���16λֵ */
    uint8_t counter = 0;

    for (counter = 0; counter < 4; counter++) {
        __as621x_read(p_this, __g_as621x_debug_info.reg[counter], reg_buf, 2);
        reg_val = __AS621X_UINT16_CONV(reg_buf);
        am_kprintf("%s : 0x%04x \r\n",__g_as621x_debug_info.reg_name_str[counter], reg_val);
    }
}
#endif

/*******************************************************************************/
/** \breif �жϻص����� */
am_local void __as621x_alarm_callback (void *p_arg)
{
    am_sensor_as621x_dev_t* p_this = (am_sensor_as621x_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /** < \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_as621x_dev_t* p_this = (am_sensor_as621x_dev_t*)p_arg;

    as621x_result_info_t result;

    /* ��ȡ���� */
    __as621x_result_get(p_this, &result);

    /* ��ȡ�¶� */
    p_this->data[0].val = result.as621x_temperature;
    p_this->data[0].unit = AM_SENSOR_UNIT_MICRO;

    if (p_this->pfn_trigger_cb[0] &&
            (p_this->flags[0] & AM_SENSOR_TRIGGER_THRESHOLD)) {
        p_this->pfn_trigger_cb[0](p_this->p_arg[0],
                                  AM_SENSOR_TRIGGER_THRESHOLD);
    }
}

/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (id == AM_AS621X_CHAN_1) {
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
    am_sensor_as621x_dev_t* p_this = (am_sensor_as621x_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    as621x_result_info_t result;

    uint8_t cfg_reg[2] = {0};

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

    /* ��Ϊ1������������޴����ص�������ʹ�� */
    if (num == 1) {
        cur_id = p_ids[0];
        /* �������޴�����ʽ����ֱ�Ӹ�ֵ */
        if ((AM_BIT_GET(p_this->trigger, 1)) &&
                (p_this->flags[0] & AM_SENSOR_TRIGGER_THRESHOLD)) {
            p_buf[0].val = p_this->data[cur_id].val;
            p_buf[0].unit= p_this->data[cur_id].unit;
            return AM_OK;
        }
    }

    /** \brief ��ȡSSλΪ1����ʾ����ת�� */
    do {
        ret = __as621x_read(p_this, __AS621X_REG_CONFIG, cfg_reg, 2);
        if (ret != AM_OK) {
            return ret;
        }
    } while (__AS621X_SS_GET(cfg_reg[0]) == 0x1);

    /** \brief ��ȡ������� */
    __as621x_result_get(p_this, &result);

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            p_buf[i].val = result.as621x_temperature;
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/

        } else {
            return -AM_ENODEV;  /*< \brief ���˴�ͨ�������ڸô�������ֱ�ӷ��� */
        }
    }

    return ret;
}

/** \brief ʹ�ܴ�����ͨ�� */
am_local am_err_t __pfn_enable (void            *p_drv,
                                const int       *p_ids,
                                int              num,
                                am_sensor_val_t *p_result)
{
    am_sensor_as621x_dev_t* p_this = (am_sensor_as621x_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    am_err_t ret = -AM_ENODEV;
    am_err_t curent_ret = AM_OK;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {
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

    if (ret != AM_OK) {     /*< \brief �������û�иô�������ͨ�����룬���˳� */
        return curent_ret;
    }

    /* �Ĵ���������ʼ�� */
    ret = __as621x_param_init(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* ����SSλ����������ת�� */
    ret = __as621x_single_shot(p_this, AM_TRUE);
    if (ret != AM_OK) {
        return ret;
    }

    if (ret == AM_OK) {
        AM_BIT_SET(p_this->trigger, 7);
        AM_BIT_SET(p_this->trigger, 6);
    }

#if __AS621X_DEBUG
    __as621x_regval_check(p_this);
#endif

    return curent_ret;
}

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result)
{
    am_sensor_as621x_dev_t* p_this = (am_sensor_as621x_dev_t*)p_drv;

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

        } else {
            ret = -AM_ENODEV;
        }

        if (p_result != NULL) {
            p_result[i].val = ret;
        }
    }

    if (AM_BIT_GET(p_this->trigger, 6) == 0) {

        /* SSλ���� */
        ret = __as621x_single_shot(p_this, AM_FALSE);
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
    return -AM_ENOTSUP;
}

/** \brief ��ȡ������ͨ������ */
am_local am_err_t __pfn_attr_get (void            *p_drv,
                                  int              id,
                                  int              attr,
                                  am_sensor_val_t *p_val)
{
    return -AM_ENOTSUP;
}

/** \brief ���ô�����һ��ͨ����������һ�������ص����� */
am_local am_err_t __pfn_trigger_cfg (void                   *p_drv,
                                     int                     id,
                                     uint32_t                flags,
                                     am_sensor_trigger_cb_t  pfn_cb,
                                     void                   *p_arg)
{
    am_sensor_as621x_dev_t* p_this = (am_sensor_as621x_dev_t*)p_drv;

    if (id != 0) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    switch (flags) {
    case AM_SENSOR_TRIGGER_THRESHOLD:       /* ���޴��� */
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
    am_sensor_as621x_dev_t* p_this = (am_sensor_as621x_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    if (id != 0) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (p_this->trigger & 0x2) {
        return AM_OK;
    }

    if (p_this->dev_info->trigger_pin != -1) {
        ret = am_gpio_trigger_on(p_this->dev_info->trigger_pin);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }

    /* ����SMλ������ת��ģʽ */
    ret = __as621x_sm_set(p_this, AM_AS621X_CONTINUOUS_CONVERSION_MODE);
    if (ret != AM_OK) {
        cur_ret = ret;
    }

    /* ����IMλ��ʹ���ж�ģʽ */
    ret = __as621x_im_set(p_this, AM_AS621X_INTERRUPT_MODE);
    if (ret != AM_OK) {
        cur_ret = ret;
    }

    if (cur_ret == AM_OK && id == 0) {
        AM_BIT_SET(p_this->trigger, 0);
        AM_BIT_SET(p_this->trigger, 1);
    }

    return cur_ret;
}

/** \brief �رմ��� */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id)
{
    am_sensor_as621x_dev_t* p_this = (am_sensor_as621x_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    if (id != 0) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    p_this->pfn_trigger_cb[id] = NULL;
    p_this->p_arg[id]          = NULL;
    p_this->flags[id]          = 0;

    AM_BIT_CLR(p_this->trigger, id);

    if ((p_this->trigger & 0x1) == 0) {

        if ((p_this->dev_info->trigger_pin != -1) && (cur_ret == AM_OK)) {
            ret = am_gpio_trigger_off(p_this->dev_info->trigger_pin);
            if (ret != AM_OK) {
                cur_ret = ret;
            }
        }

        if (cur_ret == AM_OK) {
            /* �����ж�ģʽ���ָ��Ƚ�ģʽ */
            __as621x_im_set(p_this, AM_AS621X_COMPARATOR_MODE);
            /* �ָ���ʼSMλ���� */
            __as621x_sm_set(p_this, p_this->dev_info->p_param_default->sleep_mode);
            AM_BIT_CLR(p_this->trigger, 1);
        }
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ AS621X ��ʼ��
 */
am_sensor_handle_t am_sensor_as621x_init (
        am_sensor_as621x_dev_t           *p_dev,
        const am_sensor_as621x_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle)
{

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->as621x_dev.p_drv   = p_dev;
    p_dev->as621x_dev.p_funcs = &__g_sensor_as621x_funcs;
    p_dev->dev_info           = p_devinfo;
    p_dev->pfn_trigger_cb[0]  = NULL;
    p_dev->p_arg[0]           = NULL;
    p_dev->flags[0]           = 0;
    p_dev->trigger            = 0;
    p_dev->data[0].val        = 0;
    p_dev->data[0].unit       = AM_SENSOR_UNIT_INVALID;

    if (p_devinfo->trigger_pin != -1) {
        if (p_devinfo->p_param_default->polarity_high == AM_TRUE) {
            am_gpio_pin_cfg(p_devinfo->trigger_pin, AM_GPIO_INPUT | AM_GPIO_PULLDOWN);
            am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                    __as621x_alarm_callback,
                                    (void*)p_dev);
            am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_RISE);
        } else {
            am_gpio_pin_cfg(p_devinfo->trigger_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);
            am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                    __as621x_alarm_callback,
                                    (void*)p_dev);
            am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_FALL);
        }
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    return &(p_dev->as621x_dev);
}

/**
 * \brief ������ AS621X ȥ��ʼ��
 */
am_err_t am_sensor_as621x_deinit (am_sensor_handle_t handle)
{
    am_sensor_as621x_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->as621x_dev.p_drv   = NULL;
    p_dev->as621x_dev.p_funcs = NULL;
    p_dev->dev_info           = NULL;

    return AM_OK;
}

am_err_t am_sensor_as621x_ioctl (am_sensor_handle_t  handle,
                                 int                 cmd,
                                 void               *p_arg)
{
    am_sensor_as621x_dev_t  *p_dev = (am_sensor_as621x_dev_t *)handle->p_drv;

    am_err_t ret = AM_OK;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    switch (cmd) {

    /* ��ȡ����λ */
    case AM_SENSOR_AS621X_ALERT_BIT_GET:
        ret = __as621x_alert_bit_get(p_dev, (uint8_t *)p_arg);
        break;

    /* ����ת������ */
    case AM_SENSOR_AS621X_CR_SET:
        ret = __as621x_cr_set(p_dev,
                             (uint8_t)(int)p_arg);
        break;

    /* ����SMλ(Sleep Mode) */
    case AM_SENSOR_AS621X_SM_SET:
        ret = __as621x_sm_set(p_dev,
                             (uint8_t)(int)p_arg);
        break;

    /* ��ȡSMλ */
    case AM_SENSOR_AS621X_SM_GET:
        ret = __as621x_sm_get(p_dev, (uint8_t *)p_arg);
        break;

    /* ����IMλ(Interrupt Mode) */
    case AM_SENSOR_AS621X_IM_SET:
        ret = __as621x_im_set(p_dev,
                             (uint8_t)(int)p_arg);
        break;

    /* ����POLλ(Polarity) */
    case AM_SENSOR_AS621X_POLARITY_SET:
        ret = __as621x_polarity_set(p_dev,
                                   (am_bool_t)(int)p_arg);
        break;

    /* ��������������(Consecutive Faults) */
    case AM_SENSOR_AS621X_CF_SET:
        ret = __as621x_cf_set(p_dev,
                             (uint8_t)(int)p_arg);
        break;

    /* ����SSλ */
    case AM_SENSOR_AS621X_SS_SET:
        ret = __as621x_single_shot(p_dev,
                                  (am_bool_t)(int)p_arg);
        break;

    /* ���õ��¶���ֵ */
    case AM_SENSOR_AS621X_TLOW_THRESHOLD_SET:
        ret = __as621x_tlow_threshold_set(p_dev,
                                          *(float *)p_arg);
        break;

    /* ���ø��¶���ֵ */
    case AM_SENSOR_AS621X_THIGH_THRESHOLD_SET:
        ret = __as621x_thigh_threshold_set(p_dev,
                                           *(float *)p_arg);
        break;

    /* ��ȡ���¶���ֵ */
    case AM_SENSOR_AS621X_TLOW_THRESHOLD_GET:
        ret = __as621x_tlow_threshold_get(p_dev,
                                         (float *)p_arg);
        break;

    /* ��ȡ���¶���ֵ */
    case AM_SENSOR_AS621X_THIGH_THRESHOLD_GET:
        ret = __as621x_thigh_threshold_get(p_dev,
                                          (float *)p_arg);
        break;

    default:
        ret = -AM_ENOTSUP;
        break;
    }

    return ret;
}

/* end of file */


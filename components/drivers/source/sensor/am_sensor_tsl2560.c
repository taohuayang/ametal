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
 * \brief ������ TSL2560 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tsl2560.h"
#include "am_sensor.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**< ������Ϣ��� */
#define __TSL2560_DEBUG             (1)

/**********************************************************************************************
 * �궨��
 **********************************************************************************************/

/**< ����Ĵ��� CMD */
#define __TSL2560_SEL_CMD                           (0x01 << 7)

/**< ����Ĵ��� TRANSACTION */
#define __TSL2560_NORMAL_OPERATION                  (0x01 << 5)
#define __TSL2560_SPECIAL_FUNCTION                  (0x03 << 5)

/**< ����Ĵ��� ADDR/SF */
#define __TSL2560_INTERRUPT_SET                     (0x04)
#define __TSL2560_CLEARS_ALS_INTERRUPT              (0x06)
#define __TSL2560_CLEARS_ALS_AND_NO_PERSIST_ALS_INTERRUPT   \
                                                    (0x07)
#define __TSL2560_CLEARS_NO_PERSIST_ALS_INTERRUPT           \
                                                    (0x0A)

#define __TSL2560_REG_ENABLE                        (0x00)
#define __TSL2560_REG_CONTROL                       (0x01)
#define __TSL2560_REG_AILTL                         (0x04)
#define __TSL2560_REG_AILTH                         (0x05)
#define __TSL2560_REG_AIHTL                         (0x06)
#define __TSL2560_REG_AIHTH                         (0x07)
#define __TSL2560_REG_NPAILTL                       (0x08)
#define __TSL2560_REG_NPAILTH                       (0x09)
#define __TSL2560_REG_NPAIHTL                       (0x0A)
#define __TSL2560_REG_NPAIHTH                       (0x0B)
#define __TSL2560_REG_PERSIST                       (0x0C)
#define __TSL2560_REG_PID                           (0x11)
#define __TSL2560_REG_ID                            (0x12)
#define __TSL2560_REG_STATUS                        (0x13)
#define __TSL2560_REG_C0DATAL                       (0x14)
#define __TSL2560_REG_C0DATAH                       (0x15)
#define __TSL2560_REG_C1DATAL                       (0x16)
#define __TSL2560_REG_C1DATAH                       (0x17)

/** \brief TSL2560�����λ */
#define __TSL2560_MASK_CONTROL_SW_RST               (0x1 << 7)
#define __TSL2560_SW_RST(val)                       ((val) << 7)
#define __TSL2560_SOFTWARE_RESET                    (0x1 << 7)

/** \brief ����AGAIN */
#define __TSL2560_MASK_CONTROL_AGAIN                (0x3 << 4)
#define __TSL2560_AGAIN_SET(val)                    ((val) << 4)

/** \brief ����ATIME */
#define __TSL2560_MASK_CONTROL_ATIME                (0x7 << 0)
#define __TSL2560_ATIME_SET(val)                    ((val) << 0)

/** \brief ����APERS */
#define __TSL2560_MASK_PERSIST_APERS                (0xf << 0)
#define __TSL2560_APERS_SET(val)                    ((val) << 0)

/** \brief TSL2560 ID */
#define __TSL2560_MASK_ID                           (0xf0)
#define __TSL2560_ID                                (0x50)

/** \brief ��ȡNPINTR */
#define __TSL2560_STATUS_NPINTR_GET(reg)            (((reg) >> 5) & 0x1)

/** \brief ��ȡAINT */
#define __TSL2560_STATUS_AINT_GET(reg)              (((reg) >> 4) & 0x1)

/** \brief ��ȡAVALID */
#define __TSL2560_STATUS_AVALID_GET(reg)            (((reg) >> 0) & 0x1)

/** \brief ������uint8ת��Ϊһ��uint16_t���� */
#define __TSL2560_UINT8_TO_UINT16(buff)             ((uint16_t)((*(buff + 1)) << 8 | (*buff)))

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
am_local am_const struct am_sensor_drv_funcs __g_sensor_tsl2560_funcs = {
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
 * \brief tsl2560 д����
 */
am_local am_err_t __tsl2560_write (am_sensor_tsl2560_dev_t  *p_this,
                                   uint32_t                  subaddr,
                                   uint8_t                  *p_buf,
                                   uint32_t                  nbytes)
{
    return am_i2c_write(&p_this->i2c_dev,
                        (__TSL2560_SEL_CMD | __TSL2560_NORMAL_OPERATION | subaddr),
                        p_buf,
                        1);
}

/*
 * \brief tsl2560 ������
 */
am_local am_err_t __tsl2560_read (am_sensor_tsl2560_dev_t   *p_this,
                                  uint32_t                   subaddr,
                                  uint8_t                   *p_buf,
                                  uint32_t                   nbytes)
{
    return am_i2c_read(&p_this->i2c_dev,
                        (__TSL2560_SEL_CMD | __TSL2560_NORMAL_OPERATION | subaddr),
                        p_buf,
                        1);
}

/*
 * \brief tsl2560 д���⹦������
 */
am_local am_err_t __tsl2560_special_function (am_sensor_tsl2560_dev_t  *p_this,
                                              uint8_t                   cmd_type,
                                              uint8_t                  *p_buf)
{
    return am_i2c_write(&p_this->i2c_dev,
                        (__TSL2560_SEL_CMD | __TSL2560_SPECIAL_FUNCTION | cmd_type),
                        p_buf,
                        1);
}

/*
 * \brief tsl2560 �޸ļĴ���ֵ
 */
am_local am_err_t __tsl2560_modify_reg_val(am_sensor_tsl2560_dev_t  *p_this,
                                           uint8_t                   reg,
                                           uint8_t                   mask,
                                           uint8_t                   val)
{
    uint8_t regval = 0;
    am_err_t ret = AM_OK;

    if (mask == 0xFF) {
        regval = val;
    } else {
        ret = __tsl2560_read(p_this, reg, &regval, 1);
        if (ret != AM_OK) {
            return ret;
        }

        regval &= ~mask;
        regval |= (val & mask);
    }

    ret = __tsl2560_write(p_this, reg, &regval, 1);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ������ֵ */
am_local am_err_t __tsl2560_threshold_set(am_sensor_tsl2560_dev_t   *p_this,
                                          uint32_t                   subaddr,
                                          uint16_t                   value)
{
    am_err_t ret = AM_OK;

    uint32_t i = 0;

    uint8_t reg[2] = {0};

    reg[0] = value & 0xff;
    reg[1] = (value & 0xff00) >> 8;

    for (i = 0; i < 2; i++) {
        ret = __tsl2560_write(p_this, (subaddr + i), &reg[i], 1);
        if (ret != AM_OK) {
            return ret;
        }
    }

    return ret;
}

/** \brief ��ȡ��ֵ */
am_local am_err_t __tsl2560_threshold_get(am_sensor_tsl2560_dev_t   *p_this,
                                          uint32_t                   subaddr,
                                          uint16_t                  *p_value)
{
    am_err_t ret = AM_OK;

    uint32_t i = 0;

    uint8_t reg[2] = {0};

    for (i = 0; i < 2; i++) {
        ret = __tsl2560_read(p_this, (subaddr + i), &reg[i], 1);
        if (ret != AM_OK) {
            return ret;
        }
    }

    *p_value = __TSL2560_UINT8_TO_UINT16(&reg[0]);

    return ret;
}

/*******************************************************************************/

am_local am_err_t __tsl2560_ioctl (am_sensor_tsl2560_dev_t  *p_dev,
                                   int                       cmd,
                                   void                     *p_arg)
{
    uint8_t reg = 0x00;
    uint8_t regmask = 0xFF;
    uint8_t regval = 0x00;

    am_err_t ret = AM_OK;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    switch (cmd) {

    /* ���ù���ʹ�� */
    case AM_SENSOR_TSL2560_FUNC_ENABLE:
        reg = __TSL2560_REG_ENABLE;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tsl2560_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ���ù��ܽ��� */
    case AM_SENSOR_TSL2560_FUNC_DISABLE:
        reg = __TSL2560_REG_ENABLE;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __tsl2560_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �����λ */
    case AM_SENSOR_TSL2560_SOFTRST:
        reg = __TSL2560_REG_CONTROL;
        regmask = __TSL2560_MASK_CONTROL_SW_RST;
        regval = AM_TRUE;
        regval = __TSL2560_SW_RST(regval);
        ret = __tsl2560_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ALS���� */
    case AM_SENSOR_TSL2560_AGAIN_SET:
        reg = __TSL2560_REG_CONTROL;
        regmask = __TSL2560_MASK_CONTROL_AGAIN;
        regval = (uint8_t)(int)p_arg;
        regval = __TSL2560_AGAIN_SET(regval);
        ret = __tsl2560_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ATIME */
    case AM_SENSOR_TSL2560_ATIME_SET:
        reg = __TSL2560_REG_CONTROL;
        regmask = __TSL2560_MASK_CONTROL_ATIME;
        regval = (uint8_t)(int)p_arg;
        regval = __TSL2560_ATIME_SET(regval);
        ret = __tsl2560_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ALS����ֵ */
    case AM_SENSOR_TSL2560_LOW_ALS_THRESHOLD_SET:
        ret = __tsl2560_threshold_set(p_dev, __TSL2560_REG_AILTL, (uint16_t)(int)p_arg);
        break;

    /* ����ALS����ֵ */
    case AM_SENSOR_TSL2560_HIGH_ALS_THRESHOLD_SET:
        ret = __tsl2560_threshold_set(p_dev, __TSL2560_REG_AIHTL, (uint16_t)(int)p_arg);
        break;

    /* ��ȡALS����ֵ */
    case AM_SENSOR_TSL2560_LOW_ALS_THRESHOLD_GET:
        ret = __tsl2560_threshold_get(p_dev, __TSL2560_REG_AILTL, (uint16_t *)p_arg);
        break;

    /* ��ȡALS����ֵ */
    case AM_SENSOR_TSL2560_HIGH_ALS_THRESHOLD_GET:
        ret = __tsl2560_threshold_get(p_dev, __TSL2560_REG_AIHTL, (uint16_t *)p_arg);
        break;

    /* ����No Persist ALS����ֵ */
    case AM_SENSOR_TSL2560_NO_PERSIST_LOW_ALS_THRESHOLD_SET:
        ret = __tsl2560_threshold_set(p_dev, __TSL2560_REG_NPAILTL, (uint16_t)(int)p_arg);
        break;

    /* ����No Persist ALS����ֵ */
    case AM_SENSOR_TSL2560_NO_PERSIST_HIGH_ALS_THRESHOLD_SET:
        ret = __tsl2560_threshold_set(p_dev, __TSL2560_REG_NPAIHTL, (uint16_t)(int)p_arg);
        break;

    /* ��ȡNo Persist ALS����ֵ */
    case AM_SENSOR_TSL2560_NO_PERSIST_LOW_ALS_THRESHOLD_GET:
        ret = __tsl2560_threshold_get(p_dev, __TSL2560_REG_NPAILTL, (uint16_t *)p_arg);
        break;

    /* ��ȡNo Persist ALS����ֵ */
    case AM_SENSOR_TSL2560_NO_PERSIST_HIGH_ALS_THRESHOLD_GET:
        ret = __tsl2560_threshold_get(p_dev, __TSL2560_REG_NPAIHTL, (uint16_t *)p_arg);
        break;

    /* ����APERS */
    case AM_SENSOR_TSL2560_APERS_SET:
        reg = __TSL2560_REG_PERSIST;
        regmask = __TSL2560_MASK_PERSIST_APERS;
        regval = (uint8_t)(int)p_arg;
        regval = __TSL2560_APERS_SET(regval);
        ret = __tsl2560_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ��ȡPID */
    case AM_SENSOR_TSL2560_PID_GET:
        ret = __tsl2560_read(p_dev, __TSL2560_REG_PID, (uint8_t *)p_arg, 1);
        break;

    /* ��ȡID */
    case AM_SENSOR_TSL2560_ID_GET:
        ret = __tsl2560_read(p_dev, __TSL2560_REG_ID, (uint8_t *)p_arg, 1);
        break;

    /* ��ȡNPINTR */
    case AM_SENSOR_TSL2560_NPINTR_GET:
        ret = __tsl2560_read(p_dev, __TSL2560_REG_STATUS, &regval, 1);
        regval = __TSL2560_STATUS_NPINTR_GET(regval);
        *(uint8_t *)p_arg = regval;
        break;

    /* ��ȡAINT */
    case AM_SENSOR_TSL2560_AINT_GET:
        ret = __tsl2560_read(p_dev, __TSL2560_REG_STATUS, &regval, 1);
        regval = __TSL2560_STATUS_AINT_GET(regval);
        *(uint8_t *)p_arg = regval;
        break;

    /* ��ȡAVALID */
    case AM_SENSOR_TSL2560_AVALID_GET:
        ret = __tsl2560_read(p_dev, __TSL2560_REG_STATUS, &regval, 1);
        regval = __TSL2560_STATUS_AVALID_GET(regval);
        *(uint8_t *)p_arg = regval;
        break;

    /* �����ж� */
    case AM_SENSOR_TSL2560_INTERRUPT_SET:
        ret = __tsl2560_special_function(p_dev, __TSL2560_INTERRUPT_SET, &regval);
        break;

    /* ���ALS�ж� */
    case AM_SENSOR_TSL2560_ALS_INTERRUPT_CLEAR:
        ret = __tsl2560_special_function(p_dev, __TSL2560_CLEARS_ALS_INTERRUPT, &regval);
        break;

    /* ���ALS�͵���ALS�ж� */
    case AM_SENSOR_TSL2560_ALS_AND_NO_PERSIST_ALS_INTERRUPT_CLEAR:
        ret = __tsl2560_special_function(p_dev, __TSL2560_CLEARS_ALS_AND_NO_PERSIST_ALS_INTERRUPT, &regval);
        break;

    /* �������ALS�ж� */
    case AM_SENSOR_TSL2560_NO_PERSIST_ALS_INTERRUPT_CLEAR:
        ret = __tsl2560_special_function(p_dev, __TSL2560_CLEARS_NO_PERSIST_ALS_INTERRUPT, &regval);
        break;

    default:
        ret = -AM_ENOTSUP;
        break;
    }

    return ret;
}

/*******************************************************************************/

/**
 * \brief TSL2560 ʹ��
 */
am_local void __tsl2560_enable(am_sensor_tsl2560_dev_t  *p_this)
{
    __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_FUNC_ENABLE,
                                (void *)(AM_TSL2560_AEN | \
                                         AM_TSL2560_PON ));
}

/**
 * \brief TSL2560 ����
 */
am_local void __tsl2560_disable(am_sensor_tsl2560_dev_t *p_this)
{
    __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_FUNC_DISABLE,
                                (void *)(AM_TSL2560_AEN | \
                                         AM_TSL2560_PON ));
}

/** \brief TSL2560 ���STATUS�Ĵ��� */
am_local void __tsl2560_status_clr_all(am_sensor_tsl2560_dev_t  *p_this)
{
    __tsl2560_ioctl(p_this,
                    AM_SENSOR_TSL2560_ALS_AND_NO_PERSIST_ALS_INTERRUPT_CLEAR,
                    NULL);
}

/**
 * \brief TSL2560 �ж�ʹ��
 */
am_local void __tsl2560_int_enable(am_sensor_tsl2560_dev_t  *p_this)
{
    __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_FUNC_ENABLE,
                            (void *)(uint32_t)(p_this->dev_info->p_param_default->interrupt_type));
}

/**
 * \brief TSL2560 �жϽ���
 */
am_local void __tsl2560_int_disable(am_sensor_tsl2560_dev_t *p_this)
{
    __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_FUNC_DISABLE,
                            (void *)(uint32_t)(p_this->dev_info->p_param_default->interrupt_type));
}

/** \brief TSL2560 ������ʼ�� */
am_local am_err_t __tsl2560_param_init(am_sensor_tsl2560_dev_t  *p_this)
{
    tsl2560_param_config_t *p_param_config = (tsl2560_param_config_t *)p_this->dev_info->p_param_default;

    am_err_t ret = AM_OK;

    /* AGAIN */
    ret = __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_AGAIN_SET, (void *)(uint32_t)(p_param_config->again_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* ATIME */
    ret = __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_ATIME_SET, (void *)(uint32_t)(p_param_config->atime_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* APERS */
    ret = __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_APERS_SET, (void *)(uint32_t)(p_param_config->apers_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* ���� ALS �͡�����ֵ */
    ret = __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_LOW_ALS_THRESHOLD_SET, (void *)(uint32_t)(p_param_config->als_low_threshold));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_HIGH_ALS_THRESHOLD_SET, (void *)(uint32_t)(p_param_config->als_high_threshold));
    if (ret != AM_OK) {
        return ret;
    }

    /* ���� ����ALS �͡�����ֵ */
    ret = __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_NO_PERSIST_LOW_ALS_THRESHOLD_SET, (void *)(uint32_t)(p_param_config->no_persist_als_low_threshold));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_NO_PERSIST_HIGH_ALS_THRESHOLD_SET, (void *)(uint32_t)(p_param_config->no_persist_als_high_threshold));
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/**
 * \brief TSL2560 ��ȡ���
 */
am_local am_err_t __tsl2560_result_get(am_sensor_tsl2560_dev_t  *p_this,
                                       tsl2560_result_info_t    *p_result)
{
    am_err_t ret = AM_OK;

    uint32_t i = 0;

    uint8_t result_buf[4]  = {0};         /* ����Ĵ���ֵ */

    for (i = 0; i < 4; i++) {
        ret = __tsl2560_read(p_this, (__TSL2560_REG_C0DATAL + i), &result_buf[i], 1);
        if (ret != AM_OK) {
            return ret;
        }
    }

    /* ALS_CH0 */
    p_result->als_ch0_data = __TSL2560_UINT8_TO_UINT16(&result_buf[0]);

    /* ALS_CH1 */
    p_result->als_ch1_data = __TSL2560_UINT8_TO_UINT16(&result_buf[2]);

    return ret;
}

/*******************************************************************************/

/** \breif �жϻص����� */
am_local void __tsl2560_alarm_callback (void *p_arg)
{
    am_sensor_tsl2560_dev_t* p_this = (am_sensor_tsl2560_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /*< \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_tsl2560_dev_t* p_this = (am_sensor_tsl2560_dev_t*)p_arg;

    uint8_t i = 0;

    tsl2560_result_info_t result;

    /* ��ȡ���� */
    __tsl2560_result_get(p_this, &result);

    /* ��ȡ���ݺ����жϱ�־λ */
    __tsl2560_status_clr_all(p_this);

    /* ��ȡALS_CH0 */
    p_this->data[0].val = result.als_ch0_data;
    p_this->data[0].unit = AM_SENSOR_UNIT_BASE;

    /* ��ȡALS_CH1 */
    p_this->data[1].val = result.als_ch1_data;
    p_this->data[1].unit = AM_SENSOR_UNIT_BASE;

    for (i = 0; i < 2; i++) {
        if (p_this->pfn_trigger_cb[i] &&
                (p_this->flags[i] & AM_SENSOR_TRIGGER_THRESHOLD)) {
            p_this->pfn_trigger_cb[i](p_this->p_arg[i],
                                      AM_SENSOR_TRIGGER_THRESHOLD);
        }
    }
}

/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if ((id == AM_TSL2560_CHAN_1) || (id == AM_TSL2560_CHAN_2)) {
        return AM_SENSOR_TYPE_ALS;
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
    am_sensor_tsl2560_dev_t* p_this = (am_sensor_tsl2560_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    tsl2560_result_info_t result;

    int cur_id = 0;
    int i = 0;

    uint8_t avalid = 0;

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
        if ((AM_BIT_GET(p_this->trigger, 2)) &&
                ((p_this->flags[0] & AM_SENSOR_TRIGGER_THRESHOLD) ||
                 (p_this->flags[1] & AM_SENSOR_TRIGGER_THRESHOLD))) {
            p_buf[0].val = p_this->data[cur_id].val;
            p_buf[0].unit= p_this->data[cur_id].unit;
            return AM_OK;
        }
    }

    /** \brief ��ȡ������� */
    do {

        __tsl2560_ioctl(p_this, AM_SENSOR_TSL2560_AVALID_GET, &avalid);

    } while (avalid != 0x1);
    
    ret = __tsl2560_result_get(p_this, &result);
    if (ret != AM_OK) {
        return ret;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            p_buf[i].val  = result.als_ch0_data;                /*< \brief ALS_CH0 */
            p_buf[i].unit = AM_SENSOR_UNIT_BASE;                /*< \brief ��λĬ��Ϊ0:10^(0)*/

        } else if (cur_id == 1) {

            p_buf[i].val  = result.als_ch1_data;                /*< \brief ALS_CH1 */
            p_buf[i].unit = AM_SENSOR_UNIT_BASE;                /*< \brief ��λĬ��Ϊ0:10^(0)*/

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
    am_sensor_tsl2560_dev_t* p_this = (am_sensor_tsl2560_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

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

    /* �Ĵ���������ʼ�� */
    ret = __tsl2560_param_init(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* enable �Ĵ�������ʹ�� */
    __tsl2560_enable(p_this);

    if (ret == AM_OK) {
        AM_BIT_SET(p_this->trigger, 7);
        AM_BIT_SET(p_this->trigger, 6);
        AM_BIT_SET(p_this->trigger, 5);
    }

    return curent_ret;
}

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result)
{
    am_sensor_tsl2560_dev_t* p_this = (am_sensor_tsl2560_dev_t*)p_drv;

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

        /* enable �Ĵ������ý��� */
        __tsl2560_disable(p_this);

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
    am_sensor_tsl2560_dev_t* p_this = (am_sensor_tsl2560_dev_t*)p_drv;

    if (id != 0 && id != 1) {
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
    am_sensor_tsl2560_dev_t* p_this = (am_sensor_tsl2560_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (p_this->trigger & 0x4) {
        return AM_OK;
    }

    if (p_this->dev_info->trigger_pin != -1) {
        ret = am_gpio_trigger_on(p_this->dev_info->trigger_pin);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }

    /* ���жϱ�־λ */
    __tsl2560_status_clr_all(p_this);

    /* ʹ���ж� */
    __tsl2560_int_enable(p_this);

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
    am_sensor_tsl2560_dev_t* p_this = (am_sensor_tsl2560_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

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

        if ((p_this->dev_info->trigger_pin != -1) && (cur_ret == AM_OK)) {
            ret = am_gpio_trigger_off(p_this->dev_info->trigger_pin);
            if (ret != AM_OK) {
                cur_ret = ret;
            }
        }

        if (cur_ret == AM_OK) {

            /* �����ж� */
            __tsl2560_int_disable(p_this);

            AM_BIT_CLR(p_this->trigger, 2);
        }
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ TSL2560 ��ʼ��
 */
am_sensor_handle_t am_sensor_tsl2560_init (
        am_sensor_tsl2560_dev_t             *p_dev,
        const am_sensor_tsl2560_devinfo_t   *p_devinfo,
        am_i2c_handle_t                      handle)
{
    am_err_t ret = AM_OK;

    uint8_t tsl2560_id = 0;
    uint8_t reg = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->tsl2560_dev.p_drv   = p_dev;
    p_dev->tsl2560_dev.p_funcs = &__g_sensor_tsl2560_funcs;
    p_dev->dev_info            = p_devinfo;
    p_dev->pfn_trigger_cb[0]   = NULL;
    p_dev->pfn_trigger_cb[1]   = NULL;
    p_dev->p_arg[0]            = NULL;
    p_dev->p_arg[1]            = NULL;
    p_dev->flags[0]            = 0;
    p_dev->flags[1]            = 0;
    p_dev->trigger             = 0;
    p_dev->data[0].val         = 0;
    p_dev->data[0].unit        = AM_SENSOR_UNIT_INVALID;
    p_dev->data[1].val         = 0;
    p_dev->data[1].unit        = AM_SENSOR_UNIT_INVALID;

    if (p_devinfo->trigger_pin != -1) {
        am_gpio_pin_cfg(p_devinfo->trigger_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);
        am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                __tsl2560_alarm_callback,
                                (void*)p_dev);
        am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_FALL);  /* �½��ش��� */
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    /* TSL2560�����λ */
    reg = __TSL2560_SOFTWARE_RESET;
    __tsl2560_write(p_dev, __TSL2560_REG_CONTROL, &reg, 1);
    am_mdelay(10);

    /* �ȴ���λ��� */
    do {
        __tsl2560_read(p_dev, __TSL2560_REG_CONTROL, &reg, 1);

    } while (reg & __TSL2560_SOFTWARE_RESET);

    /* ��ȡID */
    ret = __tsl2560_read(p_dev, __TSL2560_REG_ID, &tsl2560_id, 1);
    tsl2560_id &= __TSL2560_MASK_ID;
    if ((ret != AM_OK) || (tsl2560_id != __TSL2560_ID)) {
    #if __TSL2560_DEBUG
        am_kprintf("tsl2560_id = 0x%x \r\n", tsl2560_id);
    #endif
        am_kprintf("\r\nSensor TSL2560 Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->tsl2560_dev);
}

/**
 * \brief ������ TSL2560 ȥ��ʼ��
 */
am_err_t am_sensor_tsl2560_deinit (am_sensor_handle_t   handle)
{
    am_sensor_tsl2560_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->tsl2560_dev.p_drv   = NULL;
    p_dev->tsl2560_dev.p_funcs = NULL;
    p_dev->dev_info            = NULL;

    return AM_OK;
}

/**
 * \brief ������ TSL2560 ���ƺ���
 */
am_err_t am_sensor_tsl2560_ioctl (am_sensor_handle_t    handle,
                                  int                   cmd,
                                  void                 *p_arg)
{
    am_sensor_tsl2560_dev_t *p_dev = (am_sensor_tsl2560_dev_t *)handle->p_drv;

    am_err_t ret = AM_OK;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    ret = __tsl2560_ioctl(p_dev, cmd, p_arg);

    return ret;
}

/* end of file */


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
 * \brief ������ AS7421 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_as7421.h"
#include "am_sensor.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**< ������Ϣ��� */
#define __AS7421_DEBUG                          (0)

/************************************************************
 * �궨��
 ***********************************************************/
#define __AS7421_REG_CFG_MISC                   (0x38)
#define __AS7421_REG_CFG_LED_MULT               (0x39)
#define __AS7421_REG_LTF_CCOUNT_L               (0x3A)
#define __AS7421_REG_LTF_CCOUNT_H               (0x3B)
#define __AS7421_REG_TEMP_COMPDAC               (0x3C)
#define __AS7421_REG_LED_WAIT                   (0x3D)
#define __AS7421_REG_CFG_PINMAP                 (0x3E)
#define __AS7421_REG_CFG_RAM_0                  (0x40)
#define __AS7421_REG_CFG_RAM_1                  (0x41)
#define __AS7421_REG_CFG_RAM_2                  (0x42)
#define __AS7421_REG_CFG_RAM_3                  (0x43)
#define __AS7421_REG_CFG_RAM_4                  (0x44)
#define __AS7421_REG_CFG_RAM_5                  (0x45)
#define __AS7421_REG_CFG_RAM_6                  (0x46)
#define __AS7421_REG_CFG_RAM_7                  (0x47)
#define __AS7421_REG_CFG_RAM_8                  (0x48)
#define __AS7421_REG_CFG_RAM_9                  (0x49)
#define __AS7421_REG_CFG_RAM_10                 (0x4A)
#define __AS7421_REG_CFG_RAM_11                 (0x4B)
#define __AS7421_REG_CFG_RAM_12                 (0x4C)
#define __AS7421_REG_CFG_RAM_13                 (0x4D)
#define __AS7421_REG_CFG_RAM_14                 (0x4E)
#define __AS7421_REG_CFG_RAM_15                 (0x4F)
#define __AS7421_REG_CFG_RAM_16                 (0x50)
#define __AS7421_REG_CFG_RAM_17                 (0x51)
#define __AS7421_REG_CFG_RAM_18                 (0x52)
#define __AS7421_REG_CFG_RAM_19                 (0x53)
#define __AS7421_REG_CFG_RAM_20                 (0x54)
#define __AS7421_REG_CFG_RAM_21                 (0x55)
#define __AS7421_REG_CFG_RAM_22                 (0x56)
#define __AS7421_REG_CFG_RAM_23                 (0x57)
#define __AS7421_REG_CFG_RAM_24                 (0x58)
#define __AS7421_REG_CFG_RAM_25                 (0x59)
#define __AS7421_REG_CFG_RAM_26                 (0x5A)
#define __AS7421_REG_CFG_RAM_27                 (0x5B)
#define __AS7421_REG_CFG_RAM_28                 (0x5C)
#define __AS7421_REG_CFG_RAM_29                 (0x5D)
#define __AS7421_REG_CFG_RAM_30                 (0x5E)
#define __AS7421_REG_CFG_RAM_31                 (0x5F)
#define __AS7421_REG_ENABLE                     (0x60)
#define __AS7421_REG_LTF_ITIME_L                (0x61)
#define __AS7421_REG_LTF_ITIME_M                (0x62)
#define __AS7421_REG_LTF_ITIME_H                (0x63)
#define __AS7421_REG_LTF_WTIME_L                (0x64)
#define __AS7421_REG_LTF_WTIME_M                (0x65)
#define __AS7421_REG_LTF_WTIME_H                (0x66)
#define __AS7421_REG_CFG_LTF                    (0x67)
#define __AS7421_REG_CFG_LED                    (0x68)
#define __AS7421_REG_LTF_ICOUNT                 (0x69)
#define __AS7421_REG_CFG_RAM                    (0x6A)
#define __AS7421_REG_CFG_GPIO                   (0x6B)
#define __AS7421_REG_INT_EN                     (0x6C)
#define __AS7421_REG_CFG_AZ                     (0x6D)
#define __AS7421_REG_STATUS0                    (0x70)
#define __AS7421_REG_STATUS1                    (0x71)
#define __AS7421_REG_STATUS2                    (0x72)
#define __AS7421_REG_STATUS3                    (0x73)
#define __AS7421_REG_STATUS6                    (0x76)
#define __AS7421_REG_STATUS7                    (0x77)
#define __AS7421_REG_TEMP0_L                    (0x78)
#define __AS7421_REG_TEMP0_H                    (0x79)
#define __AS7421_REG_TEMP1_L                    (0x7A)
#define __AS7421_REG_TEMP1_H                    (0x7B)
#define __AS7421_REG_TEMP2_L                    (0x7C)
#define __AS7421_REG_TEMP2_H                    (0x7D)
#define __AS7421_REG_TEMP3_L                    (0x7E)
#define __AS7421_REG_TEMP3_H                    (0x7F)
#define __AS7421_REG_CH0_DATA_L                 (0x80)
#define __AS7421_REG_CH63_DATA_H                (0xFF)

/** \brief ����CFG_MISC�Ĵ��� */
#define __AS7421_MASK_CFG_MISC_LED_WAIT_OFF     (0x1 << 2)
#define __AS7421_LED_WAIT_OFF_SET(val)          ((val) << 2)

#define __AS7421_MASK_CFG_MISC_WAIT_CYCLE_ON    (0x1 << 1)
#define __AS7421_WAIT_CYCLE_ON_SET(val)         ((val) << 1)

#define __AS7421_MASK_CFG_MISC_SW_RST           (0x1 << 0)
#define __AS7421_SW_RST(val)                    ((val) << 0)
#define __AS7421_SOFTWARE_RESET                 (0x1 << 0)

/** \brief ����LED_MULT */
#define __AS7421_MASK_CFG_LED_MULT_LED_MULT     (0x1f << 0)
#define __AS7421_LED_MULT_SET(val)              ((val) << 0)

/** \brief ����INT_PINMAP */
#define __AS7421_MASK_CFG_PINMAP_INT_PINMAP     (0x7 << 4)
#define __AS7421_INT_PINMAP_SET(val)            ((val) << 4)

/** \brief ����INT_INVERT */
#define __AS7421_MASK_CFG_PINMAP_INT_INVERT     (0x1 << 3)
#define __AS7421_INT_INVERT_SET(val)            ((val) << 3)

/** \brief ����GPIO_PINMAP */
#define __AS7421_MASK_CFG_PINMAP_GPIO_PINMAP    (0x7 << 0)
#define __AS7421_GPIO_PINMAP_SET(val)           ((val) << 0)

/** \brief ����LED_AUTO */
#define __AS7421_MASK_ENABLE_LED_AUTO           (0x3 << 4)
#define __AS7421_LED_AUTO_SET(val)              ((val) << 4)

/** \brief ����LTF_CYCLE */
#define __AS7421_MASK_CFG_LTF_LTF_CYCLE         (0x3 << 3)
#define __AS7421_LTF_CYCLE_SET(val)             ((val) << 3)

/** \brief ����CLKMOD */
#define __AS7421_MASK_CFG_LTF_CLKMOD            (0x7 << 0)
#define __AS7421_CLKMOD_SET(val)                ((val) << 0)

/** \brief ����SET_LED_ON */
#define __AS7421_MASK_CFG_LED_SET_LED_ON        (0x1 << 7)
#define __AS7421_SET_LED_ON_SET(val)            ((val) << 7)

/** \brief ����LED_OFF_EN */
#define __AS7421_MASK_CFG_LED_LED_OFF_EN        (0x1 << 6)
#define __AS7421_LED_OFF_EN_SET(val)            ((val) << 6)

/** \brief ����LED_OFFSET */
#define __AS7421_MASK_CFG_LED_LED_OFFSET        (0x3 << 4)
#define __AS7421_LED_OFFSET_SET(val)            ((val) << 4)

/** \brief ����LED_CURRENT */
#define __AS7421_MASK_CFG_LED_LED_CURRENT       (0x7 << 0)
#define __AS7421_LED_CURRENT_SET(val)           ((val) << 0)

/** \brief ����REG_BANK */
#define __AS7421_MASK_CFG_RAM_REG_BANK          (0x1 << 7)
#define __AS7421_REG_BANK_SET(val)              ((val) << 7)

/** \brief ����RAM_OFFSET */
#define __AS7421_MASK_CFG_RAM_RAM_OFFSET        (0x1f << 0)
#define __AS7421_RAM_OFFSET_SET(val)            ((val) << 0)

/** \brief ����GPIO_INVERT */
#define __AS7421_MASK_CFG_GPIO_GPIO_INVERT      (0x1 << 3)
#define __AS7421_GPIO_INVERT_SET(val)           ((val) << 3)

/** \brief ����GPIO_OEN */
#define __AS7421_MASK_CFG_GPIO_GPIO_OEN         (0x1 << 2)
#define __AS7421_GPIO_OEN_SET(val)              ((val) << 2)

/** \brief ����GPIO_OUT */
#define __AS7421_MASK_CFG_GPIO_GPIO_OUT         (0x1 << 1)
#define __AS7421_GPIO_OUT_SET(val)              ((val) << 1)

/** \brief ����GPIO_IN */
#define __AS7421_MASK_CFG_GPIO_GPIO_IN          (0x1 << 0)
#define __AS7421_GPIO_IN_SET(val)               ((val) << 0)

/** \brief ����AZ_ON */
#define __AS7421_MASK_CFG_AZ_AZ_ON              (0x1 << 7)
#define __AS7421_AZ_ON_SET(val)                 ((val) << 7)

/** \brief ����AZ_WTIME */
#define __AS7421_MASK_CFG_AZ_AZ_WTIME           (0x3 << 5)
#define __AS7421_AZ_WTIME_SET(val)              ((val) << 5)

/** \brief ����AZ_EN */
#define __AS7421_MASK_CFG_AZ_AZ_EN              (0x1 << 4)
#define __AS7421_AZ_EN_SET(val)                 ((val) << 4)

/** \brief ����AZ_CYCLE */
#define __AS7421_MASK_CFG_AZ_AZ_CYCLE           (0x1 << 3)
#define __AS7421_AZ_CYCLE_SET(val)              ((val) << 3)

/** \brief ����AZ_ITERATION */
#define __AS7421_MASK_CFG_AZ_AZ_ITERATION       (0x7 << 0)
#define __AS7421_AZ_ITERATION_SET(val)          ((val) << 0)

/** \brief AS7421 ID */
#define __AS7421_MASK_ID                        (0x3f)
#define __AS7421_ID                             (0x0B)

/** \brief ��ȡTEMP_ASAT */
#define __AS7421_STATUS6_TEMP_ASAT_GET(reg)     (((reg) >> 6) & 0x1)

/** \brief ��ȡLTF_READY */
#define __AS7421_STATUS6_LTF_READY_GET(reg)     (((reg) >> 5) & 0x1)

/** \brief ��ȡLTF_BUSY */
#define __AS7421_STATUS6_LTF_BUSY_GET(reg)      (((reg) >> 4) & 0x1)

/** \brief ��ȡI2C_DATA_PTR */
#define __AS7421_STATUS7_I2C_DATA_PTR_GET(reg)  (((reg) >> 6) & 0x3)

/** \brief ��ȡDLOST */
#define __AS7421_STATUS7_DLOST_GET(reg)         (((reg) >> 5) & 0x1)

/** \brief ��ȡDSAT */
#define __AS7421_STATUS7_DSAT_GET(reg)          (((reg) >> 4) & 0x1)

/** \brief ��ȡASAT */
#define __AS7421_STATUS7_ASAT_GET(reg)          (((reg) >> 3) & 0x1)

/** \brief ��ȡTSD */
#define __AS7421_STATUS7_TSD_GET(reg)           (((reg) >> 2) & 0x1)

/** \brief ��ȡAZ */
#define __AS7421_STATUS7_AZ_GET(reg)            (((reg) >> 1) & 0x1)

/** \brief ��ȡADATA */
#define __AS7421_STATUS7_ADATA_GET(reg)         (((reg) >> 0) & 0x1)

/** \brief ������uint8ת��Ϊһ��uint16_t���� */
#define __AS7421_UINT8_TO_UINT16(buff)          ((uint16_t)((*(buff + 1)) << 8 | (*buff)))

/** \brief ÿ�β����¶ȵ����� */
#define __AS7421_TEMPERATURE_CNT                (4)

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
am_local am_const struct am_sensor_drv_funcs __g_sensor_as7421_funcs = {
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
 * \brief as7421 д����
 */
am_local am_err_t __as7421_write (am_sensor_as7421_dev_t    *p_this,
                                  uint32_t                   subaddr,
                                  uint8_t                   *p_buf,
                                  uint32_t                   nbytes)
{
    return am_i2c_write(&p_this->i2c_dev,
                        subaddr,
                        p_buf,
                        nbytes);
}

/*
 * \brief as7421 ������
 */
am_local am_err_t __as7421_read (am_sensor_as7421_dev_t *p_this,
                                 uint32_t                subaddr,
                                 uint8_t                *p_buf,
                                 uint32_t                nbytes)
{
    return am_i2c_read(&p_this->i2c_dev,
                       subaddr,
                       p_buf,
                       nbytes);
}

/*
 * \brief as7421 �޸ļĴ���ֵ
 */
am_local am_err_t __as7421_modify_reg_val(am_sensor_as7421_dev_t    *p_this,
                                          uint8_t                    reg,
                                          uint8_t                    mask,
                                          uint8_t                    val)
{
    uint8_t regval = 0;
    am_err_t ret = AM_OK;

    if (mask == 0xFF) {
        regval = val;
    } else {
        ret = __as7421_read(p_this, reg, &regval, 1);
        if (ret != AM_OK) {
            return ret;
        }

        regval &= ~mask;
        regval |= (val & mask);
    }

    ret = __as7421_write(p_this, reg, &regval, 1);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ������ֵ */
am_local am_err_t __as7421_threshold_set(am_sensor_as7421_dev_t *p_this,
                                         uint32_t                subaddr,
                                         uint16_t                value)
{
    am_err_t ret = AM_OK;

    uint8_t reg[2] = {0};

    reg[0] = value & 0xff;
    reg[1] = (value & 0xff00) >> 8;

    ret = __as7421_write(p_this, subaddr, reg, 2);

    return ret;
}

/** \brief ��ȡ��ֵ */
am_local am_err_t __as7421_threshold_get(am_sensor_as7421_dev_t *p_this,
                                         uint32_t                subaddr,
                                         uint16_t               *p_value)
{
    am_err_t ret = AM_OK;

    uint8_t reg[2] = {0};

    ret = __as7421_read(p_this, subaddr, reg, 2);

    *p_value = __AS7421_UINT8_TO_UINT16(&reg[0]);

    return ret;
}

/** \brief ����ITIME/WTIME�Ĵ���ֵ */
am_local am_err_t __as7421_time_set(am_sensor_as7421_dev_t  *p_this,
                                    uint32_t                 subaddr,
                                    uint32_t                 value)
{
    am_err_t ret = AM_OK;

    uint8_t reg[3] = {0};

    reg[0] = (value & 0x000000ff);
    reg[1] = (value & 0x0000ff00) >> 8;
    reg[2] = (value & 0x00ff0000) >> 16;

    ret = __as7421_write(p_this, subaddr, reg, 3);

    return ret;
}

/** \brief ��ȡITIME/WTIME�Ĵ���ֵ */
am_local am_err_t __as7421_time_get(am_sensor_as7421_dev_t  *p_this,
                                    uint32_t                 subaddr,
                                    uint32_t                *p_time)
{
    am_err_t ret = AM_OK;

    uint8_t reg[3] = {0};

    ret = __as7421_read(p_this, subaddr, reg, 3);

    *p_time = ((uint32_t)reg[2] << 16) |
              ((uint32_t)reg[1] << 8)  |
              ((uint32_t)reg[0] << 0);

    return ret;
}

/*******************************************************************************/

am_local am_err_t __as7421_ioctl (am_sensor_as7421_dev_t    *p_dev,
                                  int                        cmd,
                                  void                      *p_arg)
{
    uint8_t reg = 0x00;
    uint8_t regmask = 0xFF;
    uint8_t regval = 0x00;

    am_err_t ret = AM_OK;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    switch (cmd) {
    /* ����LED_WAIT_OFF */
    case AM_SENSOR_AS7421_LED_WAIT_OFF_SET:
        reg = __AS7421_REG_CFG_MISC;
        regmask = __AS7421_MASK_CFG_MISC_LED_WAIT_OFF;
        regval = (am_bool_t)(int)p_arg;
        regval = __AS7421_LED_WAIT_OFF_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����WAIT_CYCLE_ON */
    case AM_SENSOR_AS7421_WAIT_CYCLE_ON_SET:
        reg = __AS7421_REG_CFG_MISC;
        regmask = __AS7421_MASK_CFG_MISC_WAIT_CYCLE_ON;
        regval = (am_bool_t)(int)p_arg;
        regval = __AS7421_WAIT_CYCLE_ON_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �����λ */
    case AM_SENSOR_AS7421_SW_RST:
        reg = __AS7421_REG_CFG_MISC;
        regmask = __AS7421_MASK_CFG_MISC_SW_RST;
        regval = AM_TRUE;
        regval = __AS7421_SW_RST(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LED_MULT */
    case AM_SENSOR_AS7421_LED_MULT_SET:
        reg = __AS7421_REG_CFG_LED_MULT;
        regmask = __AS7421_MASK_CFG_LED_MULT_LED_MULT;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_LED_MULT_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LTF_CCOUNT */
    case AM_SENSOR_AS7421_LTF_CCOUNT_SET:
        ret = __as7421_threshold_set(p_dev, __AS7421_REG_LTF_CCOUNT_L, (uint16_t)(int)p_arg);
        break;

    /* ��ȡLTF_CCOUNT */
    case AM_SENSOR_AS7421_LTF_CCOUNT_GET:
        ret = __as7421_threshold_get(p_dev, __AS7421_REG_LTF_CCOUNT_L, (uint16_t *)p_arg);
        break;

    /* ����LED_WAIT */
    case AM_SENSOR_AS7421_LED_WAIT_SET:
        reg = __AS7421_REG_LED_WAIT;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����INT_PINMAP */
    case AM_SENSOR_AS7421_INT_PINMAP_SET:
        reg = __AS7421_REG_CFG_PINMAP;
        regmask = __AS7421_MASK_CFG_PINMAP_INT_PINMAP;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_INT_PINMAP_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����INT_INVERT */
    case AM_SENSOR_AS7421_INT_INVERT_SET:
        reg = __AS7421_REG_CFG_PINMAP;
        regmask = __AS7421_MASK_CFG_PINMAP_INT_INVERT;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_INT_INVERT_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GPIO_PINMAP */
    case AM_SENSOR_AS7421_GPIO_PINMAP_SET:
        reg = __AS7421_REG_CFG_PINMAP;
        regmask = __AS7421_MASK_CFG_PINMAP_GPIO_PINMAP;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_GPIO_PINMAP_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LED_AUTO */
    case AM_SENSOR_AS7421_LED_AUTO_SET:
        reg = __AS7421_REG_ENABLE;
        regmask = __AS7421_MASK_ENABLE_LED_AUTO;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_LED_AUTO_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ���ù���ʹ�� */
    case AM_SENSOR_AS7421_FUNC_ENABLE:
        reg = __AS7421_REG_ENABLE;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ���ù��ܽ��� */
    case AM_SENSOR_AS7421_FUNC_DISABLE:
        reg = __AS7421_REG_ENABLE;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ITIME */
    case AM_SENSOR_AS7421_ITIME_SET:
        ret = __as7421_time_set(p_dev, __AS7421_REG_LTF_ITIME_L, (uint32_t)p_arg);
        break;

    /* ��ȡITIME */
    case AM_SENSOR_AS7421_ITIME_GET:
        ret = __as7421_time_get(p_dev, __AS7421_REG_LTF_ITIME_L, (uint32_t *)p_arg);
        break;

    /* ����WTIME */
    case AM_SENSOR_AS7421_WTIME_SET:
        ret = __as7421_time_set(p_dev, __AS7421_REG_LTF_WTIME_L, (uint32_t)p_arg);
        break;

    /* ��ȡWTIME */
    case AM_SENSOR_AS7421_WTIME_GET:
        ret = __as7421_time_get(p_dev, __AS7421_REG_LTF_WTIME_L, (uint32_t *)p_arg);
        break;

    /* ����LTF_CYCLE */
    case AM_SENSOR_AS7421_LTF_CYCLE_SET:
        reg = __AS7421_REG_CFG_LTF;
        regmask = __AS7421_MASK_CFG_LTF_LTF_CYCLE;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_LTF_CYCLE_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����CLKMOD */
    case AM_SENSOR_AS7421_CLKMOD_SET:
        reg = __AS7421_REG_CFG_LTF;
        regmask = __AS7421_MASK_CFG_LTF_CLKMOD;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_CLKMOD_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����SET_LED_ON */
    case AM_SENSOR_AS7421_SET_LED_ON_SET:
        reg = __AS7421_REG_CFG_LED;
        regmask = __AS7421_MASK_CFG_LED_SET_LED_ON;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_SET_LED_ON_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LED_OFF_EN */
    case AM_SENSOR_AS7421_LED_OFF_EN_SET:
        reg = __AS7421_REG_CFG_LED;
        regmask = __AS7421_MASK_CFG_LED_LED_OFF_EN;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_LED_OFF_EN_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LED_OFFSET */
    case AM_SENSOR_AS7421_LED_OFFSET_SET:
        reg = __AS7421_REG_CFG_LED;
        regmask = __AS7421_MASK_CFG_LED_LED_OFFSET;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_LED_OFFSET_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LED_CURRENT */
    case AM_SENSOR_AS7421_LED_CURRENT_SET:
        reg = __AS7421_REG_CFG_LED;
        regmask = __AS7421_MASK_CFG_LED_LED_CURRENT;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_LED_CURRENT_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LTF_ICOUNT */
    case AM_SENSOR_AS7421_LTF_ICOUNT_SET:
        reg = __AS7421_REG_LTF_ICOUNT;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����REG_BANK */
    case AM_SENSOR_AS7421_REG_BANK_SET:
        reg = __AS7421_REG_CFG_RAM;
        regmask = __AS7421_MASK_CFG_RAM_REG_BANK;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_REG_BANK_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����RAM_OFFSET */
    case AM_SENSOR_AS7421_RAM_OFFSET_SET:
        reg = __AS7421_REG_CFG_RAM;
        regmask = __AS7421_MASK_CFG_RAM_RAM_OFFSET;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_RAM_OFFSET_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GPIO_INVERT */
    case AM_SENSOR_AS7421_GPIO_INVERT_SET:
        reg = __AS7421_REG_CFG_GPIO;
        regmask = __AS7421_MASK_CFG_GPIO_GPIO_INVERT;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_GPIO_INVERT_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GPIO_OEN */
    case AM_SENSOR_AS7421_GPIO_OEN_SET:
        reg = __AS7421_REG_CFG_GPIO;
        regmask = __AS7421_MASK_CFG_GPIO_GPIO_OEN;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_GPIO_OEN_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GPIO_OUT */
    case AM_SENSOR_AS7421_GPIO_OUT_SET:
        reg = __AS7421_REG_CFG_GPIO;
        regmask = __AS7421_MASK_CFG_GPIO_GPIO_OUT;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_GPIO_OUT_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GPIO_IN */
    case AM_SENSOR_AS7421_GPIO_IN_SET:
        reg = __AS7421_REG_CFG_GPIO;
        regmask = __AS7421_MASK_CFG_GPIO_GPIO_IN;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_GPIO_IN_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �ж�ʹ�� */
    case AM_SENSOR_AS7421_INT_ENABLE:
        reg = __AS7421_REG_INT_EN;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �жϽ��� */
    case AM_SENSOR_AS7421_INT_DISABLE:
        reg = __AS7421_REG_INT_EN;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����AZ_ON */
    case AM_SENSOR_AS7421_AZ_ON_SET:
        reg = __AS7421_REG_CFG_AZ;
        regmask = __AS7421_MASK_CFG_AZ_AZ_ON;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_AZ_ON_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����AZ_WTIME */
    case AM_SENSOR_AS7421_AZ_WTIME_SET:
        reg = __AS7421_REG_CFG_AZ;
        regmask = __AS7421_MASK_CFG_AZ_AZ_WTIME;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_AZ_WTIME_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����AZ_EN */
    case AM_SENSOR_AS7421_AZ_EN_SET:
        reg = __AS7421_REG_CFG_AZ;
        regmask = __AS7421_MASK_CFG_AZ_AZ_EN;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_AZ_EN_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����AZ_CYCLE */
    case AM_SENSOR_AS7421_AZ_CYCLE_SET:
        reg = __AS7421_REG_CFG_AZ;
        regmask = __AS7421_MASK_CFG_AZ_AZ_CYCLE;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_AZ_CYCLE_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����AZ_ITERATION */
    case AM_SENSOR_AS7421_AZ_ITERATION_SET:
        reg = __AS7421_REG_CFG_AZ;
        regmask = __AS7421_MASK_CFG_AZ_AZ_ITERATION;
        regval = (uint8_t)(int)p_arg;
        regval = __AS7421_AZ_ITERATION_SET(regval);
        ret = __as7421_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ��ȡID */
    case AM_SENSOR_AS7421_ID_GET:
        ret = __as7421_read(p_dev, __AS7421_REG_STATUS0, (uint8_t *)p_arg, 1);
        if (ret != AM_OK) {
        #if __AS7421_DEBUG
            am_kprintf("\r\nSensor AS7421 read ID failed! \r\n");
        #endif
        }
        break;

    /* ��ȡREVID */
    case AM_SENSOR_AS7421_REVID_GET:
        ret = __as7421_read(p_dev, __AS7421_REG_STATUS1, (uint8_t *)p_arg, 1);
        if (ret != AM_OK) {
        #if __AS7421_DEBUG
            am_kprintf("\r\nSensor AS7421 read REVID failed! \r\n");
        #endif
        }
        break;

    /* ��ȡSTATUS2�Ĵ��� */
    case AM_SENSOR_AS7421_STATUS2_GET:
        ret = __as7421_read(p_dev, __AS7421_REG_STATUS2, (uint8_t *)p_arg, 1);
        break;

    /* ��ȡSTATUS3�Ĵ��� */
    case AM_SENSOR_AS7421_STATUS3_GET:
        ret = __as7421_read(p_dev, __AS7421_REG_STATUS3, (uint8_t *)p_arg, 1);
        break;

    /* ��ȡSTATUS6�Ĵ��� */
    case AM_SENSOR_AS7421_STATUS6_GET:
        ret = __as7421_read(p_dev, __AS7421_REG_STATUS6, (uint8_t *)p_arg, 1);
        break;

    /* ��ȡSTATUS7�Ĵ��� */
    case AM_SENSOR_AS7421_STATUS7_GET:
        ret = __as7421_read(p_dev, __AS7421_REG_STATUS7, (uint8_t *)p_arg, 1);
        break;

    default:
        ret = -AM_ENOTSUP;
        break;
    }

    return ret;
}

/*******************************************************************************/

/** \brief AS7421 ��������жϱ�־ */
am_local am_err_t __as7421_status_clr_all(am_sensor_as7421_dev_t    *p_this)
{
    uint8_t status7_reg = 0x00;

    am_err_t ret = AM_OK;

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_STATUS7_GET, &status7_reg);

    return ret;
}

/** \brief AS7421 SMUX for integration cycle X */
am_local am_err_t __as7421_smux_cfg(am_sensor_as7421_dev_t  *p_this)
{
    am_err_t ret = AM_OK;

    /**\brief default SMUX configuration */
    uint8_t smux_cfg[8] = {0x21, 0x21, 0x21, 0x21,
                           0x43, 0x43, 0x43, 0x43};

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_RAM_OFFSET_SET, (void *)AM_AS7421_SMUX_FOR_INTEGRATION_CYCLE_A);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_write(p_this, __AS7421_REG_CFG_RAM_0, smux_cfg, 8);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_RAM_OFFSET_SET, (void *)AM_AS7421_SMUX_FOR_INTEGRATION_CYCLE_B);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_write(p_this, __AS7421_REG_CFG_RAM_8, smux_cfg, 8);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_RAM_OFFSET_SET, (void *)AM_AS7421_SMUX_FOR_INTEGRATION_CYCLE_C);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_write(p_this, __AS7421_REG_CFG_RAM_16, smux_cfg, 8);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_RAM_OFFSET_SET, (void *)AM_AS7421_SMUX_FOR_INTEGRATION_CYCLE_D);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_write(p_this, __AS7421_REG_CFG_RAM_24, smux_cfg, 8);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/* AS7421 �������� */
am_local am_err_t __as7421_set_gain(am_sensor_as7421_dev_t  *p_this)
{
    am_err_t ret = AM_OK;

    uint8_t ch_gain[64] = { 6, 6, 6, 6, 6, 6, 6, 6,
                            6, 6, 6, 6, 6, 6, 6, 6,
                            6, 6, 6, 6, 6, 6, 6, 6,
                            6, 6, 6, 6, 6, 6, 6, 6,
                            6, 6, 6, 6, 6, 6, 6, 6,
                            6, 6, 6, 6, 6, 6, 6, 6,
                            6, 6, 6, 6, 6, 6, 6, 6,
                            6, 6, 6, 6, 6, 6, 6, 6};

    /* power on in ENABLE register */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_FUNC_ENABLE,
                                (void *)(AM_AS7421_PON));

    /* һ�����д32���ֽڣ�������д��
       ��д cycle A/B����д cycle C/D */

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_RAM_OFFSET_SET, (void *)AM_AS7421_ASETUP_FOR_INTEGRATION_CYCLE_A_OR_B);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_write(p_this, __AS7421_REG_CFG_RAM_0, &ch_gain[0], 32);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_RAM_OFFSET_SET, (void *)AM_AS7421_ASETUP_FOR_INTEGRATION_CYCLE_C_OR_D);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_write(p_this, __AS7421_REG_CFG_RAM_0, &ch_gain[32], 32);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/* AS7421 set led mult */
am_local am_err_t __as7421_set_led_mult(am_sensor_as7421_dev_t  *p_this)
{
    am_err_t ret = AM_OK;

    uint8_t i = 0;

    for (i = 0; i < 4; i++) {
        /* select cycle */
        ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_OFFSET_SET, (void *)(uint32_t)(AM_AS7421_LED_MULT_0_FOR_INTEGRATION_CYCLE_A + i));
        if (ret != AM_OK) {
            return ret;
        }

        /* write LED_MULT register (select which LEDs to turn on) for selected cycle */
        /* CFG_LED_MULT �Ĵ������� */
        ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_MULT_SET, (void *)(uint32_t)(p_this->dev_info->p_param_default->led_mult));
        if (ret != AM_OK) {
            return ret;
        }
    }

    /* reset cycle */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_OFFSET_SET, (void *)(uint32_t)(AM_AS7421_LED_MULT_0_FOR_INTEGRATION_CYCLE_A));
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief AS7421 ������ʼ�� */
am_local am_err_t __as7421_param_init(am_sensor_as7421_dev_t    *p_this)
{
    as7421_param_config_t *p_param_config = (as7421_param_config_t *)p_this->dev_info->p_param_default;

    am_err_t ret = AM_OK;

    /* CFG_MISC �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_WAIT_OFF_SET, (void *)(uint32_t)(p_param_config->led_wait_off));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_WAIT_CYCLE_ON_SET, (void *)(uint32_t)(p_param_config->wait_cycle_on));
    if (ret != AM_OK) {
        return ret;
    }

    /* LED_WAIT �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_WAIT_SET, (void *)(uint32_t)(p_param_config->led_wait));
    if (ret != AM_OK) {
        return ret;
    }

    /* LTF_CCOUNT �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LTF_CCOUNT_SET, (void *)(uint32_t)(p_param_config->ltf_ccount));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG_PINMAP �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_INT_PINMAP_SET, (void *)(uint32_t)(p_param_config->int_pinmap));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_INT_INVERT_SET, (void *)(uint32_t)(p_param_config->int_invert));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_GPIO_PINMAP_SET, (void *)(uint32_t)(p_param_config->gpio_pinmap));
    if (ret != AM_OK) {
        return ret;
    }

    /* ENABLE �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_AUTO_SET, (void *)(uint32_t)(p_param_config->led_auto));
    if (ret != AM_OK) {
        return ret;
    }

    /* ENABLE �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_AUTO_SET, (void *)(uint32_t)(p_param_config->led_auto));
    if (ret != AM_OK) {
        return ret;
    }

    /* LTF_ITIME �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_ITIME_SET, (void *)(uint32_t)(p_param_config->ltf_itime));
    if (ret != AM_OK) {
        return ret;
    }

    /* LTF_WTIME �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_WTIME_SET, (void *)(uint32_t)(p_param_config->ltf_wtime));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG_LTF �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LTF_CYCLE_SET, (void *)(uint32_t)(p_param_config->ltf_cycle));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_CLKMOD_SET, (void *)(uint32_t)(p_param_config->clkmod));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG_LED �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_SET_LED_ON_SET, (void *)(uint32_t)(p_param_config->set_led_on));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_OFF_EN_SET, (void *)(uint32_t)(p_param_config->led_off_en));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LED_CURRENT_SET, (void *)(uint32_t)(p_param_config->led_current));
    if (ret != AM_OK) {
        return ret;
    }

    /* LTF_ICOUNT �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_LTF_ICOUNT_SET, (void *)(uint32_t)(p_param_config->ltf_icount));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG_RAM �Ĵ������� */

    /* CFG_GPIO �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_GPIO_INVERT_SET, (void *)(uint32_t)(p_param_config->gpio_invert));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_GPIO_OEN_SET, (void *)(uint32_t)(p_param_config->gpio_oen));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_GPIO_OUT_SET, (void *)(uint32_t)(p_param_config->gpio_out));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG_AZ �Ĵ������� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_AZ_WTIME_SET, (void *)(uint32_t)(p_param_config->az_wtime));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_AZ_ITERATION_SET, (void *)(uint32_t)(p_param_config->az_iteration));
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/**
 * \brief AS7421 �ж�ʹ��
 */
am_local void __as7421_int_enable(am_sensor_as7421_dev_t    *p_this)
{
    __as7421_ioctl(p_this, AM_SENSOR_AS7421_INT_ENABLE,
                                (void *)(AM_AS7421_EN_TSD |
                                         AM_AS7421_EN_ADATA));
}

/**
 * \brief AS7421 �жϽ���
 */
am_local void __as7421_int_disable(am_sensor_as7421_dev_t   *p_this)
{
    __as7421_ioctl(p_this, AM_SENSOR_AS7421_INT_DISABLE,
                                (void *)(AM_AS7421_EN_TSD |
                                         AM_AS7421_EN_ADATA));
}

/**
 * \brief AS7421 ��ȡ���
 */
am_local am_err_t __as7421_result_get(am_sensor_as7421_dev_t    *p_this,
                                      as7421_result_info_t      *p_result)
{
    am_err_t ret = AM_OK;

    uint16_t i = 0;

    uint8_t result_buf[136]  = {0};         /* ����Ĵ���ֵ */

    ret = __as7421_read(p_this, __AS7421_REG_TEMP0_L, &result_buf[0], 136);

    /* �������� x �¶�ADֵ */
    p_result->raw_temp_ic_a = __AS7421_UINT8_TO_UINT16(&result_buf[0]);
    p_result->raw_temp_ic_b = __AS7421_UINT8_TO_UINT16(&result_buf[2]);
    p_result->raw_temp_ic_c = __AS7421_UINT8_TO_UINT16(&result_buf[4]);
    p_result->raw_temp_ic_d = __AS7421_UINT8_TO_UINT16(&result_buf[6]);

    /* �������� x �¶� */
    p_result->temp_ic_a = p_result->raw_temp_ic_a;
    p_result->temp_ic_b = p_result->raw_temp_ic_b;
    p_result->temp_ic_c = p_result->raw_temp_ic_c;
    p_result->temp_ic_d = p_result->raw_temp_ic_d;

    /* CHx ADֵ */
    for (i = 0; i < 64; i++) {
        p_result->ch_data[i] = __AS7421_UINT8_TO_UINT16(&result_buf[(i << 1) + 8]);
    }

    return ret;
}

/*******************************************************************************/

/** \breif �жϻص����� */
am_local void __as7421_alarm_callback (void *p_arg)
{
    am_sensor_as7421_dev_t* p_this = (am_sensor_as7421_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /*< \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_as7421_dev_t* p_this = (am_sensor_as7421_dev_t*)p_arg;

    uint8_t i = 0;

    as7421_result_info_t result;

    /* ��ȡ���� */
    __as7421_result_get(p_this, &result);

    /* ��ȡ���ݺ����жϱ�־λ */
    __as7421_status_clr_all(p_this);

    /* ��ȡ�������� x �¶� */
    p_this->data[0].val = result.temp_ic_a;
    p_this->data[0].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[1].val = result.temp_ic_b;
    p_this->data[1].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[2].val = result.temp_ic_c;
    p_this->data[2].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[3].val = result.temp_ic_d;
    p_this->data[3].unit = AM_SENSOR_UNIT_BASE;

    /* ��ȡCHx */
    for (i = 0;i < 64; i++) {
        p_this->data[i+4].val = result.ch_data[i];
        p_this->data[i+4].unit = AM_SENSOR_UNIT_BASE;
    }

    for (i = 0; i < 2; i++) {
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

    if (id == AM_AS7421_CHAN_1) {
        return AM_SENSOR_TYPE_TEMPERATURE;
    } else if (id == AM_AS7421_CHAN_2) {
        return AM_SENSOR_TYPE_SPECTRAL;
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
    am_sensor_as7421_dev_t* p_this = (am_sensor_as7421_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    as7421_result_info_t result;

    int cur_id = 0;
    int i = 0;

    uint8_t j;
    uint8_t status7_reg = 0;

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
        if ((AM_BIT_GET(p_this->trigger, 1)) &&
                (p_this->flags[0] & AM_SENSOR_TRIGGER_DATA_READY)) {

            if (cur_id == 0) {

                for (j = 0; j < 4; j++) {
                    p_buf[j].val = p_this->data[j].val;
                    p_buf[j].unit= p_this->data[j].unit;
                }

            } else if (cur_id == 1) {

                for (j = 0; j < 64; j++) {
                    p_buf[j].val = p_this->data[j+4].val;
                    p_buf[j].unit= p_this->data[j+4].unit;
                }

            } else {
                return -AM_ENODEV;
            }
            return AM_OK;
        }
    }

    /** \brief ��ȡ������� */
    do {

        __as7421_ioctl(p_this, AM_SENSOR_AS7421_STATUS7_GET, &status7_reg);

    } while (__AS7421_STATUS7_ADATA_GET(status7_reg) != 0x1);

    ret = __as7421_result_get(p_this, &result);
    if (ret != AM_OK) {
        return ret;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            p_buf[0].val  = result.temp_ic_a;
            p_buf[0].unit = AM_SENSOR_UNIT_BASE;

            p_buf[1].val  = result.temp_ic_b;
            p_buf[1].unit = AM_SENSOR_UNIT_BASE;

            p_buf[2].val  = result.temp_ic_c;
            p_buf[2].unit = AM_SENSOR_UNIT_BASE;

            p_buf[3].val  = result.temp_ic_d;
            p_buf[3].unit = AM_SENSOR_UNIT_BASE;

        } else if (cur_id == 1) {

                for (j = 0; j < 64; j++) {
                    p_buf[j+4].val = result.ch_data[j];
                    p_buf[j+4].unit= AM_SENSOR_UNIT_BASE;
                }

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
    am_sensor_as7421_dev_t* p_this = (am_sensor_as7421_dev_t*)p_drv;
    

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

    /* AS7421 SMUX for integration cycle X���ο�������AMS�ṩ */
    ret = __as7421_smux_cfg(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* AS7421 �������ã��ο�������AMS�ṩ */
    ret = __as7421_set_gain(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* AS7421 set led mult */
    ret = __as7421_set_led_mult(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* �Ĵ���������ʼ�� */
    ret = __as7421_param_init(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* enable �Ĵ�������ʹ�� */
    ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_FUNC_ENABLE,
                                (void *)(AM_AS7421_TSD_EN   | \
                                         AM_AS7421_LTF_EN   | \
                                         AM_AS7421_PON ));
    if (ret != AM_OK) {
        return ret;
    }

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
    am_sensor_as7421_dev_t* p_this = (am_sensor_as7421_dev_t*)p_drv;

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
        ret = __as7421_ioctl(p_this, AM_SENSOR_AS7421_FUNC_DISABLE,
                                    (void *)(AM_AS7421_TSD_EN   | \
                                             AM_AS7421_LTF_EN   | \
                                             AM_AS7421_PON ));
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
    am_sensor_as7421_dev_t* p_this = (am_sensor_as7421_dev_t*)p_drv;

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    switch (flags) {
    case AM_SENSOR_TRIGGER_DATA_READY:       /* ����׼���������� */
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
    am_sensor_as7421_dev_t* p_this = (am_sensor_as7421_dev_t*)p_drv;

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
    __as7421_status_clr_all(p_this);

    /* ʹ���ж� */
    __as7421_int_enable(p_this);

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
    am_sensor_as7421_dev_t* p_this = (am_sensor_as7421_dev_t*)p_drv;

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
            __as7421_int_disable(p_this);

            AM_BIT_CLR(p_this->trigger, 2);
        }
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ AS7421 ��ʼ��
 */
am_sensor_handle_t am_sensor_as7421_init (
        am_sensor_as7421_dev_t           *p_dev,
        const am_sensor_as7421_devinfo_t *p_devinfo,
        am_i2c_handle_t                     handle)
{
    am_err_t ret = AM_OK;

    uint8_t as7421_id = 0;
    uint8_t i = 0;
    uint8_t reg = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->as7421_dev.p_drv   = p_dev;
    p_dev->as7421_dev.p_funcs = &__g_sensor_as7421_funcs;
    p_dev->dev_info           = p_devinfo;
    p_dev->pfn_trigger_cb[0]  = NULL;
    p_dev->pfn_trigger_cb[1]  = NULL;
    p_dev->p_arg[0]           = NULL;
    p_dev->p_arg[1]           = NULL;
    p_dev->flags[0]           = 0;
    p_dev->flags[1]           = 0;
    p_dev->trigger            = 0;
    for (i = 0; i < 68; i++) {
        p_dev->data[i].val        = 0;
        p_dev->data[i].unit       = AM_SENSOR_UNIT_INVALID;
    }

    if (p_devinfo->trigger_pin != -1) {
        am_gpio_pin_cfg(p_devinfo->trigger_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);
        am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                __as7421_alarm_callback,
                                (void*)p_dev);
        am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_FALL);  /* �½��ش��� */
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    /* AS7421Ӳ����λ */
    if (p_devinfo->rst_pin != -1) {
        am_gpio_set(p_devinfo->rst_pin, AM_GPIO_OUTPUT_INIT_HIGH);
        am_mdelay(10);
        am_gpio_set(p_devinfo->rst_pin, AM_GPIO_OUTPUT_INIT_LOW);
    }

    /* AS7421�����λ */
    reg = __AS7421_SOFTWARE_RESET;
    __as7421_write(p_dev, __AS7421_REG_CFG_MISC, &reg, 1);
    am_mdelay(10);

    /* �ȴ���λ��� */
    do {
        __as7421_read(p_dev, __AS7421_REG_CFG_MISC, &reg, 1);

    } while (reg & __AS7421_SOFTWARE_RESET);

    /* ��ȡID */
    ret = __as7421_read(p_dev, __AS7421_REG_STATUS0, &as7421_id, 1);
    as7421_id &= __AS7421_MASK_ID;
    if ((ret != AM_OK) || (as7421_id != __AS7421_ID)) {
    #if __AS7421_DEBUG
        am_kprintf("as7421_id = 0x%x \r\n", as7421_id);
    #endif
        am_kprintf("\r\nSensor AS7421 Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->as7421_dev);
}

/**
 * \brief ������ AS7421 ȥ��ʼ��
 */
am_err_t am_sensor_as7421_deinit (am_sensor_handle_t handle)
{
    am_sensor_as7421_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->as7421_dev.p_drv   = NULL;
    p_dev->as7421_dev.p_funcs = NULL;
    p_dev->dev_info           = NULL;

    return AM_OK;
}

/**
 * \brief ������ AS7421 ���ƺ���
 */
am_err_t am_sensor_as7421_ioctl (am_sensor_handle_t  handle,
                                 int                 cmd,
                                 void               *p_arg)
{
    am_sensor_as7421_dev_t   *p_dev = (am_sensor_as7421_dev_t *)handle->p_drv;

    am_err_t ret = AM_OK;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    ret = __as7421_ioctl(p_dev, cmd, p_arg);

    return ret;
}

/* end of file */


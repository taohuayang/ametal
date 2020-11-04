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
 * \brief PCF8551 LCD����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-02-25  yrz, first implementation.
 * \endinternal
 */

#include "am_pcf8551.h"

/* �Ĵ�����ַ */
#define __PCF8551_REG_SW_RST            ( 0x00 )   /* PCF8551A ��λ��ַ */
#define __PCF8551_REG_DEV_CTRL          ( 0x01 )   /* PCF8551A �豸���Ƶ�ַ */
#define __PCF8551_REG_DISP_CTRL_1       ( 0x02 )   /* PCF8551A ���ƼĴ���1��ַ */
#define __PCF8551_REG_DISP_CTRL_2       ( 0x03 )   /* PCF8551A ���ƼĴ���1��ַ */
#define __PCF8551_REG_DISP              ( 0x04 )   /* PCF8551A ��ʾ�Ĵ����׵�ַ */

/* �������� */
#define __PCF8551_DISP_ENABLE           (1 << 0)   /* PCF8551A ��ʾʹ�� */
#define __PCF8551_DISP_DISABLE          (~(1 << 0))/* PCF8551A ��ʾ���� */
#define __PCF8551_SW_RST_CMD            ( 0x2A )   /* PCF8551A �����λ���� */

#define __PCF8551_FRAME_FREQ_32Hz       (0 << 2)   /* PCF8551A ֡��32Hz */
#define __PCF8551_FRAME_FREQ_64Hz       (1 << 2)   /* PCF8551A ֡��64Hz */
#define __PCF8551_FRAME_FREQ_96Hz       (2 << 2)   /* PCF8551A ֡��96Hz */
#define __PCF8551_FRAME_FREQ_128Hz      (3 << 2)   /* PCF8551A ֡��128Hz */

#define __PCF8551_DRIVE_MODE_COM0_COM3  (0 << 2)   /* PCF8551A COM0-COM3ʹ�� */
#define __PCF8551_DRIVE_MODE_COM0_COM2  (1 << 2)   /* PCF8551A COM0-COM2ʹ�� */
#define __PCF8551_DRIVE_MODE_COM0_COM1  (2 << 2)   /* PCF8551A COM0-COM1ʹ�� */
#define __PCF8551_DRIVE_MODE_COM0       (3 << 2)   /* PCF8551A COM0ʹ�� */

#define __PCF8551_BLINK_OFF             (0 << 1)   /* PCF8551A ��˸�ر� */
#define __PCF8551_BLINK_HALF            (1 << 1)   /* PCF8551A ��˸Ƶ��0.5Hz */
#define __PCF8551_BLINK_1Hz             (2 << 1)   /* PCF8551A ��˸Ƶ��1Hz */
#define __PCF8551_BLINK_2Hz             (3 << 1)   /* PCF8551A ��˸Ƶ��2Hz */

/** \brief PCF8551 ����֡�� */
static int __pcf8551_frame_freq_set (am_pcf8551_dev_t *p_this, uint8_t freq)
{
    am_err_t ret = AM_OK;
    uint8_t  reg = 0x00;
    
    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    ret = am_i2c_read(&(p_this->i2c_dev), __PCF8551_REG_DEV_CTRL, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    /* ֡������ */
    reg &= __PCF8551_FRAME_FREQ_32Hz;

    switch(freq) {

    case  32:
        reg |= __PCF8551_FRAME_FREQ_32Hz;
        break;

    case  64:
        reg |= __PCF8551_FRAME_FREQ_64Hz;
        break;

    case  96:
        reg |= __PCF8551_FRAME_FREQ_96Hz;

    case  128:
        reg |= __PCF8551_FRAME_FREQ_128Hz;
        break;

    default:
        break;
    }

    ret = am_i2c_write(&(p_this->i2c_dev), __PCF8551_REG_DEV_CTRL, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    return AM_OK;
}

/** \brief PCF8551 ����ģʽ���� */
static int __pcf8551_drive_mode_set (am_pcf8551_dev_t *p_this, uint8_t mode)
{
    am_err_t ret = AM_OK;
    uint8_t  reg = 0x00;
    
    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    ret = am_i2c_read(&(p_this->i2c_dev), __PCF8551_REG_DISP_CTRL_1, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    /* ģʽ���� */
    reg &= __PCF8551_DRIVE_MODE_COM0_COM3;

    switch(mode) {

    case  4:
        reg |= __PCF8551_DRIVE_MODE_COM0_COM3;
        break;

    case  3:
        reg |= __PCF8551_DRIVE_MODE_COM0_COM2;
        break;

    case  2:
        reg |= __PCF8551_DRIVE_MODE_COM0_COM1;

    case  1:
        reg |= __PCF8551_DRIVE_MODE_COM0;
        break;

    default:
        break;
    }

    ret = am_i2c_write(&(p_this->i2c_dev), __PCF8551_REG_DISP_CTRL_1, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    return AM_OK;
}

/** \brief PCF8551 ��˸Ƶ������ */
static int __pcf8551_blink_freq_set (am_pcf8551_dev_t *p_this, uint8_t mode)
{
    am_err_t ret = AM_OK;
    uint8_t  reg = 0x00;
    
    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    ret = am_i2c_read(&(p_this->i2c_dev), __PCF8551_REG_DISP_CTRL_2, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    /* �ر���˸ */
    reg &= __PCF8551_BLINK_OFF;

    switch(mode) {

    case  0:
        reg |= __PCF8551_BLINK_OFF;
        break;

    case  1:
        reg |= __PCF8551_BLINK_HALF;
        break;

    case  2:
        reg |= __PCF8551_BLINK_1Hz;

    case  3:
        reg |= __PCF8551_BLINK_2Hz;
        break;

    default:
        break;
    }

    ret = am_i2c_write(&(p_this->i2c_dev), __PCF8551_REG_DISP_CTRL_2, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    return AM_OK;
}

/** \brief PCF8551 ���ƺ��� */
int am_pcf8551_ioctl (am_pcf8551_handle_t  handle,
                      int                  cmd,
                      void                *p_arg)
{
    am_err_t ret = AM_OK;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    switch(cmd) {

    case  AM_PCF8551_FRAME_FREQ_SET:

        ret = __pcf8551_frame_freq_set(handle, (uint32_t)p_arg);

        if (ret != AM_OK) {
            return ret;
        }

        break;

    case  AM_PCF8551_DRIVE_MODE_SET:

        ret = __pcf8551_drive_mode_set (handle, (uint32_t)p_arg);

        if (ret != AM_OK) {
            return ret;
        }

        break;

    case  AM_PCF8551_BLINK_FREQ_SET:

        ret = __pcf8551_blink_freq_set (handle, (uint32_t)p_arg);

        if (ret != AM_OK) {
            return ret;
        }

        break;

    default:
        break;
    }

    return ret;
}

/** \brief PCF8551��ʾ */
int am_pcf8551_display (am_pcf8551_handle_t handle,
                        uint8_t             ram_addr,
                        uint8_t            *p_data,
                        uint8_t             len)
{
    am_err_t ret = AM_OK;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    ret = am_i2c_write(&(handle->i2c_dev), ram_addr, p_data, len);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    return AM_OK;
}

/** \brief PCF8551 ����ʾ */
int am_pcf8551_display_on (am_pcf8551_handle_t handle)
{
    am_err_t ret = AM_OK;
    uint8_t  reg = 0x00;
    
    if (handle == NULL) {
        return -AM_EINVAL;
    }
    
    ret = am_i2c_read(&(handle->i2c_dev), __PCF8551_REG_DISP_CTRL_1, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    /* ��ʾʹ�� */
    reg |= __PCF8551_DISP_ENABLE;
    
    ret = am_i2c_write(&(handle->i2c_dev), __PCF8551_REG_DISP_CTRL_1, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    return AM_OK;
}

/** \brief PCF8551 ����ʾ */
int am_pcf8551_display_off (am_pcf8551_handle_t handle)
{
    am_err_t ret = AM_OK;
    uint8_t  reg = 0x00;
    
    if (handle == NULL) {
        return -AM_EINVAL;
    }
    
    ret = am_i2c_read(&(handle->i2c_dev), __PCF8551_REG_DISP_CTRL_1, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    /* ��ʾ���� */
    reg &= __PCF8551_DISP_DISABLE;
    
    ret = am_i2c_write(&(handle->i2c_dev), __PCF8551_REG_DISP_CTRL_1, &reg, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    return AM_OK;
}

/** \brief PCF8551 ��λ */
int am_pcf8551_software_rst (am_pcf8551_handle_t handle)
{
    am_err_t ret = AM_OK;
    uint8_t  cmd = __PCF8551_SW_RST_CMD;
    
    if (handle == NULL) {
        return -AM_EINVAL;
    }
    
    ret = am_i2c_write(&(handle->i2c_dev), __PCF8551_REG_SW_RST, &cmd, 1);
    
    if (ret != AM_OK) {
        return ret;
    }
    
    return AM_OK;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief PCF8551 ��ʼ��
 */
am_pcf8551_handle_t am_pcf8551_init (am_pcf8551_dev_t           *p_dev,
                                     const am_pcf8551_devinfo_t *p_devinfo,
                                     am_i2c_handle_t             handle)
{
    am_err_t ret = AM_OK;
    uint8_t  cmd = __PCF8551_SW_RST_CMD;

    if (p_dev == NULL || p_devinfo == NULL || handle == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&(p_dev->i2c_dev),
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->dev_info = p_devinfo;

    /* ��λ */
    ret = am_i2c_write(&(p_dev->i2c_dev), __PCF8551_REG_SW_RST, &cmd, 1);
    
    if (ret != AM_OK) {
        return NULL;
    }
    
    return p_dev;
}

/**
 * \brief PCF8551 ���ʼ��
 */
am_err_t am_pcf8551_deinit (am_pcf8551_handle_t handle)
{
    am_pcf8551_dev_t *p_dev = handle;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->dev_info = NULL;

    return AM_OK;
}

/* end of file */


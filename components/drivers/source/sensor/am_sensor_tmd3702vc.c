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
 * \brief ������ TMD3702VC �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tmd3702vc.h"
#include "am_sensor.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**< ������Ϣ��� */
#define __TMD3702VC_DEBUG           (0)

/*********************************************************************************************
 * �궨��
 ********************************************************************************************/
#define __TMD3702VC_REG_ENABLE      (0x80)  /**< \brief ʹ��״̬                            */
#define __TMD3702VC_REG_ATIME       (0x81)  /**< \brief ����ALS ADC�Ļ���ʱ��               */
#define __TMD3702VC_REG_PRATE       (0x82)  /**< \brief Prox��������ʱ��:(PRATE + 1) * 88us */
#define __TMD3702VC_REG_WTIME       (0x83)  /**< \brief ALS��Prox֮��ĵȴ�ʱ��             */
#define __TMD3702VC_REG_AILTL       (0x84)  /**< \brief ALS�жϵ���ֵ���ֽ� (Clear)         */
#define __TMD3702VC_REG_AILTH       (0x85)  /**< \brief ALS�жϵ���ֵ���ֽ� (Clear)         */
#define __TMD3702VC_REG_AIHTL       (0x86)  /**< \brief ALS�жϸ���ֵ���ֽ� (Clear)         */
#define __TMD3702VC_REG_AIHTH       (0x87)  /**< \brief ALS�жϸ���ֵ���ֽ� (Clear)         */
#define __TMD3702VC_REG_PILTL       (0x88)  /**< \brief Prox�жϵ���ֵ���ֽ�                */
#define __TMD3702VC_REG_PILTH       (0x89)  /**< \brief Prox�жϵ���ֵ���ֽ�                */
#define __TMD3702VC_REG_PIHTL       (0x8A)  /**< \brief Prox�жϸ���ֵ���ֽ�                */
#define __TMD3702VC_REG_PIHTH       (0x8B)  /**< \brief Prox�жϸ���ֵ���ֽ�                */
#define __TMD3702VC_REG_PERS        (0x8C)  /**< \brief ALS and prox�жϹ�����              */
#define __TMD3702VC_REG_CFG0        (0x8D)  /**< \brief ���üĴ���0                         */
#define __TMD3702VC_REG_PCFG0       (0x8E)  /**< \brief Prox���üĴ���0                     */
#define __TMD3702VC_REG_PCFG1       (0x8F)  /**< \brief Prox���üĴ���1                     */
#define __TMD3702VC_REG_CFG1        (0x90)  /**< \brief ���üĴ���1                         */
#define __TMD3702VC_REG_REVID       (0x91)  /**< \brief �޶�ID                              */
#define __TMD3702VC_REG_ID          (0x92)  /**< \brief �豸ID                              */
#define __TMD3702VC_REG_STATUS      (0x93)  /**< \brief �豸״̬                            */
#define __TMD3702VC_REG_CDATAL      (0x94)  /**< \brief Clear ͨ��ADC���ݵ��ֽ�             */
#define __TMD3702VC_REG_CDATAH      (0x95)  /**< \brief Clear ͨ��ADC���ݸ��ֽ�             */
#define __TMD3702VC_REG_RDATAL      (0x96)  /**< \brief Red ͨ��ADC���ݵ��ֽ�               */
#define __TMD3702VC_REG_RDATAH      (0x97)  /**< \brief Red ͨ��ADC���ݸ��ֽ�               */
#define __TMD3702VC_REG_GDATAL      (0x98)  /**< \brief Green/IR ͨ��ADC���ݵ��ֽ�          */
#define __TMD3702VC_REG_GDATAH      (0x99)  /**< \brief Green/IR ͨ��ADC���ݸ��ֽ�          */
#define __TMD3702VC_REG_BDATAL      (0x9A)  /**< \brief Blue ͨ��ADC���ݵ��ֽ�              */
#define __TMD3702VC_REG_BDATAH      (0x9B)  /**< \brief Blue ͨ��ADC���ݸ��ֽ�              */
#define __TMD3702VC_REG_PDATAL      (0x9C)  /**< \brief Prox ADC���ݵ��ֽ�                  */
#define __TMD3702VC_REG_PDATAH      (0x9D)  /**< \brief Prox ADC���ݸ��ֽ�                  */
#define __TMD3702VC_REG_REVID2      (0x9E)  /**< \brief �޶�ID 2                            */
#define __TMD3702VC_REG_CFG2        (0x9F)  /**< \brief ���üĴ���2                         */
#define __TMD3702VC_REG_SOFTRST     (0xA0)  /**< \brief ��λ                              */
#define __TMD3702VC_REG_CFG3        (0xAB)  /**< \brief ���üĴ���3                         */
#define __TMD3702VC_REG_CFG4        (0xAC)  /**< \brief ���üĴ���4 (must be set to 0x3D)   */
#define __TMD3702VC_REG_CFG6        (0xAE)  /**< \brief ���üĴ���6                         */
#define __TMD3702VC_REG_POFFSETL    (0xC0)  /**< \brief Proxƫ�Ƶ��ֽ�����                  */
#define __TMD3702VC_REG_POFFSETH    (0xC1)  /**< \brief Proxƫ�Ƹ��ֽ�����                  */
#define __TMD3702VC_REG_CALIB       (0xD7)  /**< \brief Proxƫ��У׼                        */
#define __TMD3702VC_REG_CALIBCFG    (0xD9)  /**< \brief Proxƫ��У׼����                    */
#define __TMD3702VC_REG_CALIBSTAT   (0xDC)  /**< \brief Proxƫ��У׼״̬                    */
#define __TMD3702VC_REG_INTENAB     (0xDD)  /**< \brief �ж�ʹ��                            */
#define __TMD3702VC_REG_FAC_L       (0xE6)  /**< \brief �������õ����� (lot code data)      */
#define __TMD3702VC_REG_FAC_H       (0xE7)  /**< \brief �������ø����� (lot code data)      */
#define __TMD3702VC_REG_TEST3       (0xF2)  /**< \brief ����3 (must be set to 0xC4)         */

/** \brief ����PPERS */
#define __TMD3702VC_MASK_PERS_PPERS                     (0xf << 4)
#define __TMD3702VC_PPERS_SET(val)                      ((val) << 4)

/** \brief ����APERS */
#define __TMD3702VC_MASK_PERS_APERS                     (0xf << 0)
#define __TMD3702VC_APERS_SET(val)                      ((val) << 0)

/** \brief ����WLONG(wait long) */
#define __TMD3702VC_MASK_CFG0_WLONG                     (0x1 << 2)
#define __TMD3702VC_WLONG_SET(val)                      ((val) << 2)

/** \brief ����PPULSE_LEN_16X */
#define __TMD3702VC_MASK_CFG0_PPULSE_LEN_16X            (0x1 << 0)
#define __TMD3702VC_PPULSE_LEN_16X_SET(val)             ((val) << 0)

/** \brief ����PPULSE_LEN */
#define __TMD3702VC_MASK_PCFG0_PPULSE_LEN               (0x3 << 6)
#define __TMD3702VC_PPULSE_LEN_SET(val)                 ((val) << 6)

/** \brief ����PPULSE */
#define __TMD3702VC_MASK_PCFG0_PPULSE                   (0x3f << 0)
#define __TMD3702VC_PPULSE_SET(val)                     ((val) << 0)

/** \brief ����PGAIN */
#define __TMD3702VC_MASK_PCFG1_PGAIN                    (0x3 << 6)
#define __TMD3702VC_PGAIN_SET(val)                      ((val) << 6)

/** \brief ����PLDRIVE */
#define __TMD3702VC_MASK_PCFG1_PLDRIVE                  (0xf << 0)
#define __TMD3702VC_PLDRIVE_SET(val)                    ((val) << 0)

/** \brief ����IR_MUX */
#define __TMD3702VC_MASK_CFG1_IR_MUX                    (0x1 << 6)
#define __TMD3702VC_IR_MUX_SET(val)                     ((val) << 6)

/** \brief ����AGAIN */
#define __TMD3702VC_MASK_CFG1_AGAIN                     (0x1f << 0)
#define __TMD3702VC_AGAIN_SET(val)                      ((val) << 0)

/** \brief TMD3702VC ID */
#define __TMD3702VC_ID                                  (0x10)

/** \brief ��ȡPINT״̬ */
#define __TMD3702VC_PINT_STATUS(reg)                    (((reg) >> 5) & 0x1)

/** \brief ��ȡAINT״̬ */
#define __TMD3702VC_AINT_STATUS(reg)                    (((reg) >> 4) & 0x1)

/** \brief ��ȡCINT״̬ */
#define __TMD3702VC_CINT_STATUS(reg)                    (((reg) >> 3) & 0x1)

/** \brief TMD3702VC�����λ */
#define __TMD3702VC_SW_RST                              (0x1 << 0)

/** \brief ����SAI */
#define __TMD3702VC_MASK_CFG3_SAI                       (0x1 << 4)
#define __TMD3702VC_SAI_SET(val)                        ((val) << 4)

/** \brief ����APC */
#define __TMD3702VC_MASK_CFG6_APC                       (0x1 << 6)
#define __TMD3702VC_APC_SET(val)                        ((val) << 6)

/** \brief ѡ��ProxУ׼���� */
#define __TMD3702VC_MASK_CALIB_ELECTRICAL_CALIBRATION   (0x1 << 5)
#define __TMD3702VC_PROX_CAL_TYPE_SEL(val)              ((val) << 5)

/** \brief ����ƫ��У׼���� */
#define __TMD3702VC_MASK_CALIB_START_OFFSET_CAL         (0x1 << 0)
#define __TMD3702VC_START_OFFSET_CAL(val)               ((val) << 0)

/** \brief ����BINSRCH_TARGET */
#define __TMD3702VC_MASK_CALIBCFG_BINSRCH_TARGET        (0x7 << 5)
#define __TMD3702VC_BINSRCH_TARGET_SET(val)             ((val) << 5)

/** \brief ����AUTO_OFFSET_ADJ */
#define __TMD3702VC_MASK_CALIBCFG_AUTO_OFFSET_ADJ       (0x1 << 3)
#define __TMD3702VC_AUTO_OFFSET_ADJ_SET(val)            ((val) << 3)

/** \brief ����PROX_AVG */
#define __TMD3702VC_MASK_CALIBCFG_PROX_AVG              (0x7 << 0)
#define __TMD3702VC_PROX_AVG_SET(val)                   ((val) << 0)

/** \brief ��ȡSOFTRSTλ */
#define __TMD3702VC_SOFTRST_GET(reg)                    (((reg) >> 0) & 0x1)

/** \brief ��ȡCALIB_FINISHEDλ */
#define __TMD3702VC_CALIB_FINISHED_GET(reg)             (((reg) >> 0) & 0x1)

/** \brief ������uint8ת��Ϊһ��uint16_t���� */
#define __TMD3702VC_UINT8_TO_UINT16(buff)               ((uint16_t)((*(buff + 1)) << 8 | (*buff)))

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
am_local am_const struct am_sensor_drv_funcs __g_sensor_tmd3702vc_funcs = {
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
 * \brief tmd3702vc д����
 */
am_local am_err_t __tmd3702vc_write (am_sensor_tmd3702vc_dev_t  *p_this,
                                     uint32_t                    subaddr,
                                     uint8_t                    *p_buf,
                                     uint32_t                    nbytes)
{
    return am_i2c_write(&p_this->i2c_dev,
                        subaddr,
                        p_buf,
                        nbytes);
}

/*
 * \brief tmd3702vc ������
 */
am_local am_err_t __tmd3702vc_read (am_sensor_tmd3702vc_dev_t   *p_this,
                                    uint32_t                     subaddr,
                                    uint8_t                     *p_buf,
                                    uint32_t                     nbytes)
{
    return am_i2c_read(&p_this->i2c_dev,
                       subaddr,
                       p_buf,
                       nbytes);
}

/*
 * \brief tmd3702vc �޸ļĴ���ֵ
 */
am_local am_err_t __tmd3702vc_modify_reg_val(am_sensor_tmd3702vc_dev_t  *p_this,
                                             uint8_t                     reg,
                                             uint8_t                     mask,
                                             uint8_t                     val)
{
    uint8_t regval = 0;
    am_err_t ret = AM_OK;

    if (mask == 0xFF) {
        regval = val;
    } else {
        ret = __tmd3702vc_read(p_this, reg, &regval, 1);
        if (ret != AM_OK) {
            return ret;
        }

        regval &= ~mask;
        regval |= (val & mask);
    }

    ret = __tmd3702vc_write(p_this, reg, &regval, 1);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ������ֵ */
am_local am_err_t __tmd3702vc_threshold_set(am_sensor_tmd3702vc_dev_t   *p_this,
                                            uint32_t                     subaddr,
                                            uint16_t                     value)
{
    am_err_t ret = AM_OK;

    uint8_t reg[2] = {0};

    reg[0] = value & 0xff;
    reg[1] = (value & 0xff00) >> 8;

    ret = __tmd3702vc_write(p_this, subaddr, reg, 2);

    return ret;
}

/** \brief ��ȡ��ֵ */
am_local am_err_t __tmd3702vc_threshold_get(am_sensor_tmd3702vc_dev_t   *p_this,
                                            uint32_t                     subaddr,
                                            uint16_t                    *p_value)
{
    am_err_t ret = AM_OK;

    uint8_t reg[2] = {0};

    ret = __tmd3702vc_read(p_this, subaddr, reg, 2);

    *p_value = __TMD3702VC_UINT8_TO_UINT16(&reg[0]);

    return ret;
}

/*******************************************************************************/

/** \brief STATUS�Ĵ���λ��� */
am_local am_err_t __tmd3702vc_status_flag_clr(am_sensor_tmd3702vc_dev_t *p_this,
                                              uint8_t                    flag)
{
    uint8_t status_reg = 0x00;

    am_err_t ret = AM_OK;

    ret = __tmd3702vc_read(p_this, __TMD3702VC_REG_STATUS, &status_reg, 1);
    if (ret != AM_OK) {
        return ret;
    }

    if (status_reg & flag) {
        status_reg = flag;
        ret = __tmd3702vc_write(p_this, __TMD3702VC_REG_STATUS, &status_reg, 1);
        if (ret != AM_OK) {
            return ret;
        }
    }

    return ret;
}

/** \brief �����λ */
am_local am_err_t __tmd3702vc_softrst(am_sensor_tmd3702vc_dev_t *p_this)
{
    uint8_t softrst_reg = 0x00;

    am_err_t ret = AM_OK;

    softrst_reg |= __TMD3702VC_SW_RST;
    ret = __tmd3702vc_write(p_this, __TMD3702VC_REG_SOFTRST, &softrst_reg, 1);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

am_local am_err_t __tmd3702vc_ioctl (am_sensor_tmd3702vc_dev_t  *p_dev,
                                     int                         cmd,
                                     void                       *p_arg)
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
    case AM_SENSOR_TMD3702VC_FUNC_ENABLE:
        reg = __TMD3702VC_REG_ENABLE;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ���ù��ܽ��� */
    case AM_SENSOR_TMD3702VC_FUNC_DISABLE:
        reg = __TMD3702VC_REG_ENABLE;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ATIME */
    case AM_SENSOR_TMD3702VC_ATIME_SET:
        reg = __TMD3702VC_REG_ATIME;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PRATE */
    case AM_SENSOR_TMD3702VC_PRATE_SET:
        reg = __TMD3702VC_REG_PRATE;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        regval = regval / 88 - 1;
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����WTIME */
    case AM_SENSOR_TMD3702VC_WTIME_SET:
        reg = __TMD3702VC_REG_WTIME;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ALS����ֵ */
    case AM_SENSOR_TMD3702VC_LOW_ALS_THRESHOLD_SET:
        ret = __tmd3702vc_threshold_set(p_dev, __TMD3702VC_REG_AILTL, (uint16_t)(int)p_arg);
        break;

    /* ����ALS����ֵ */
    case AM_SENSOR_TMD3702VC_HIGH_ALS_THRESHOLD_SET:
        ret = __tmd3702vc_threshold_set(p_dev, __TMD3702VC_REG_AIHTL, (uint16_t)(int)p_arg);
        break;

    /* ����Prox����ֵ */
    case AM_SENSOR_TMD3702VC_LOW_PROX_THRESHOLD_SET:
        if (p_dev->dev_info->p_param_default->apc_disable == AM_TMD3702VC_APC_ENABLE) {
            ret = __tmd3702vc_threshold_set(p_dev, __TMD3702VC_REG_PILTL, (uint16_t)(int)p_arg);
        } else {
            ret = __tmd3702vc_threshold_set(p_dev, __TMD3702VC_REG_PILTL, (uint16_t)(((int)p_arg) >> 2));
        }
        break;

    /* ����Prox����ֵ */
    case AM_SENSOR_TMD3702VC_HIGH_PROX_THRESHOLD_SET:
        if (p_dev->dev_info->p_param_default->apc_disable == AM_TMD3702VC_APC_ENABLE) {
            ret = __tmd3702vc_threshold_set(p_dev, __TMD3702VC_REG_PIHTL, (uint16_t)(int)p_arg);
        } else {
            ret = __tmd3702vc_threshold_set(p_dev, __TMD3702VC_REG_PIHTL, (uint16_t)(((int)p_arg) >> 2));
        }
        break;

    /* ��ȡALS����ֵ */
    case AM_SENSOR_TMD3702VC_LOW_ALS_THRESHOLD_GET:
        ret = __tmd3702vc_threshold_get(p_dev, __TMD3702VC_REG_AILTL, (uint16_t *)p_arg);
        break;

    /* ��ȡALS����ֵ */
    case AM_SENSOR_TMD3702VC_HIGH_ALS_THRESHOLD_GET:
        ret = __tmd3702vc_threshold_get(p_dev, __TMD3702VC_REG_AIHTL, (uint16_t *)p_arg);
        break;

    /* ��ȡProx����ֵ */
    case AM_SENSOR_TMD3702VC_LOW_PROX_THRESHOLD_GET:
        ret = __tmd3702vc_threshold_get(p_dev, __TMD3702VC_REG_PILTL, (uint16_t *)p_arg);
        break;

    /* ��ȡProx����ֵ */
    case AM_SENSOR_TMD3702VC_HIGH_PROX_THRESHOLD_GET:
        ret = __tmd3702vc_threshold_get(p_dev, __TMD3702VC_REG_PIHTL, (uint16_t *)p_arg);
        break;

    /* ����PPERS */
    case AM_SENSOR_TMD3702VC_PPERS_SET:
        reg = __TMD3702VC_REG_PERS;
        regmask = __TMD3702VC_MASK_PERS_PPERS;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_PPERS_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����APERS */
    case AM_SENSOR_TMD3702VC_APERS_SET:
        reg = __TMD3702VC_REG_PERS;
        regmask = __TMD3702VC_MASK_PERS_APERS;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_APERS_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����WLONG(wait long) */
    case AM_SENSOR_TMD3702VC_WLONG_SET:
        reg = __TMD3702VC_REG_CFG0;
        regmask = __TMD3702VC_MASK_CFG0_WLONG;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMD3702VC_WLONG_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PPULSE_LEN_16X */
    case AM_SENSOR_TMD3702VC_PPULSE_LEN_16X_SET:
        reg = __TMD3702VC_REG_CFG0;
        regmask = __TMD3702VC_MASK_CFG0_PPULSE_LEN_16X;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMD3702VC_PPULSE_LEN_16X_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PPULSE_LEN */
    case AM_SENSOR_TMD3702VC_PPULSE_LEN_SET:
        reg = __TMD3702VC_REG_PCFG0;
        regmask = __TMD3702VC_MASK_PCFG0_PPULSE_LEN;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_PPULSE_LEN_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����Prox���������������� */
    case AM_SENSOR_TMD3702VC_PPULSE_SET:
        reg = __TMD3702VC_REG_PCFG0;
        regmask = __TMD3702VC_MASK_PCFG0_PPULSE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_PPULSE_SET(regval - 1);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����Prox IR���������� */
    case AM_SENSOR_TMD3702VC_PGAIN_SET:
        reg = __TMD3702VC_REG_PCFG1;
        regmask = __TMD3702VC_MASK_PCFG1_PGAIN;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_PGAIN_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����Prox IR VCSEL������������ */
    case AM_SENSOR_TMD3702VC_PLDRIVE_SET:
        reg = __TMD3702VC_REG_PCFG1;
        regmask = __TMD3702VC_MASK_PCFG1_PLDRIVE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_PLDRIVE_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����IR_MUX */
    case AM_SENSOR_TMD3702VC_IR_MUX_SET:
        reg = __TMD3702VC_REG_CFG1;
        regmask = __TMD3702VC_MASK_CFG1_IR_MUX;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMD3702VC_IR_MUX_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ALS/Color���������� */
    case AM_SENSOR_TMD3702VC_AGAIN_SET:
        reg = __TMD3702VC_REG_CFG1;
        regmask = __TMD3702VC_MASK_CFG1_AGAIN;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_AGAIN_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ��ȡREVID */
    case AM_SENSOR_TMD3702VC_REVID_GET:
        ret = __tmd3702vc_read(p_dev, __TMD3702VC_REG_REVID, (uint8_t *)p_arg, 1);
        if (ret != AM_OK) {
        #if __TMD3702VC_DEBUG
            am_kprintf("\r\nSensor TMD3702VC read REVID failed! \r\n");
        #endif
        }
        break;

    /* ��ȡID */
    case AM_SENSOR_TMD3702VC_ID_GET:
        ret = __tmd3702vc_read(p_dev, __TMD3702VC_REG_ID, (uint8_t *)p_arg, 1);
        if (ret != AM_OK) {
        #if __TMD3702VC_DEBUG
            am_kprintf("\r\nSensor TMD3702VC read ID failed! \r\n");
        #endif
        }
        break;

    /* STATUS�Ĵ���λ��� */
    case AM_SENSOR_TMD3702VC_STATUS_FLAG_CLR:
        ret = __tmd3702vc_status_flag_clr(p_dev,
                                         (uint8_t)(int)p_arg);
        break;

    /* ��ȡREVID2 */
    case AM_SENSOR_TMD3702VC_REVID2_GET:
        ret = __tmd3702vc_read(p_dev, __TMD3702VC_REG_REVID2, (uint8_t *)p_arg, 1);
        if (ret != AM_OK) {
        #if __TMD3702VC_DEBUG
            am_kprintf("\r\nSensor TMD3702VC read REVID2 failed! \r\n");
        #endif
        }
        break;

    /* �����λ */
    case AM_SENSOR_TMD3702VC_SOFTRST:
        ret = __tmd3702vc_softrst(p_dev);
        break;

    /* ����APC */
    case AM_SENSOR_TMD3702VC_APC_SET:
        reg = __TMD3702VC_REG_CFG6;
        regmask = __TMD3702VC_MASK_CFG6_APC;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_APC_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ѡ��ProxУ׼���� */
    case AM_SENSOR_TMD3702VC_PROX_CAL_TYPE_SEL:
        reg = __TMD3702VC_REG_CALIB;
        regmask = __TMD3702VC_MASK_CALIB_ELECTRICAL_CALIBRATION;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_PROX_CAL_TYPE_SEL(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ƫ��У׼ */
    case AM_SENSOR_TMD3702VC_START_OFFSET_CAL_SET:
        reg = __TMD3702VC_REG_CALIB;
        regmask = __TMD3702VC_MASK_CALIB_START_OFFSET_CAL;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMD3702VC_START_OFFSET_CAL(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����BINSRCH_TARGET */
    case AM_SENSOR_TMD3702VC_BINSRCH_TARGET_SET:
        reg = __TMD3702VC_REG_CALIBCFG;
        regmask = __TMD3702VC_MASK_CALIBCFG_BINSRCH_TARGET;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_BINSRCH_TARGET_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����AUTO_OFFSET_ADJ */
    case AM_SENSOR_TMD3702VC_AUTO_OFFSET_ADJ_SET:
        reg = __TMD3702VC_REG_CALIBCFG;
        regmask = __TMD3702VC_MASK_CALIBCFG_AUTO_OFFSET_ADJ;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMD3702VC_AUTO_OFFSET_ADJ_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PROX_AVG */
    case AM_SENSOR_TMD3702VC_PROX_AVG_SET:
        reg = __TMD3702VC_REG_CALIBCFG;
        regmask = __TMD3702VC_MASK_CALIBCFG_PROX_AVG;
        regval = (uint8_t)(int)p_arg;
        regval = __TMD3702VC_PROX_AVG_SET(regval);
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �ж�ʹ�� */
    case AM_SENSOR_TMD3702VC_INT_ENABLE:
        reg = __TMD3702VC_REG_INTENAB;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �жϽ��� */
    case AM_SENSOR_TMD3702VC_INT_DISABLE:
        reg = __TMD3702VC_REG_INTENAB;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __tmd3702vc_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    default:
        ret = -AM_ENOTSUP;
        break;
    }

    return ret;
}

/*******************************************************************************/

/** \brief TMD3702VC ��ȡoffsetֵ */
am_local am_err_t __tmd3702vc_offset_cal(am_sensor_tmd3702vc_dev_t  *p_this,
                                         uint8_t                    *p_regval)
{
    am_err_t ret = AM_OK;

    if ((p_this == NULL) || (p_regval == NULL)) {
        return AM_ERROR;
    }

    if (p_regval[1] == 1) {
        /* offsetΪ���� */
        p_this->cal_val[0].prox_offset_adj = (int16_t)(0 - p_regval[0]);

    } else {
        /* offsetΪ���� */
        p_this->cal_val[0].prox_offset_adj = (int16_t)p_regval[0];
    }

    return ret;
}

/** \brief TMD3702VC ���STATUS�Ĵ��� */
am_local am_err_t __tmd3702vc_status_clr_all(am_sensor_tmd3702vc_dev_t *p_this)
{
    uint8_t status_reg = 0xFF;

    am_err_t ret = AM_OK;

    ret = __tmd3702vc_write(p_this, __TMD3702VC_REG_STATUS, &status_reg, 1);

    return ret;
}

/** \brief TMD3702VC ������ʼ�� */
am_local am_err_t __tmd3702vc_param_init(am_sensor_tmd3702vc_dev_t *p_this)
{
    tmd3702vc_param_config_t *p_param_config = (tmd3702vc_param_config_t *)p_this->dev_info->p_param_default;

    am_err_t ret = AM_OK;

    uint8_t reg = 0x00;     /* ����Ĵ���ֵ */

    /* ATIME �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_ATIME_SET, (void *)(uint32_t)(p_param_config->atime_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* PRATE �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PRATE_SET, (void *)(uint32_t)(p_param_config->prox_sample_time_us));
    if (ret != AM_OK) {
        return ret;
    }

    /* WTIME �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_WTIME_SET, (void *)(uint32_t)(p_param_config->wtime_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* PERS �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PPERS_SET, (void *)(uint32_t)(p_param_config->ppers_val));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_APERS_SET, (void *)(uint32_t)(p_param_config->apers_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG0 �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_WLONG_SET, (void *)(uint32_t)(p_param_config->wlong_en));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PPULSE_LEN_16X_SET, (void *)(uint32_t)(p_param_config->ppulse_len_16x_en));
    if (ret != AM_OK) {
        return ret;
    }

    /* PCFG0 �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PPULSE_LEN_SET, (void *)(uint32_t)(p_param_config->pulse_len));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PPULSE_SET, (void *)(uint32_t)(p_param_config->pulse));
    if (ret != AM_OK) {
        return ret;
    }

    /* PCFG1 �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PGAIN_SET, (void *)(uint32_t)(p_param_config->pgain_val));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PLDRIVE_SET, (void *)(uint32_t)(p_param_config->pldrive_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG1 �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_IR_MUX_SET, (void *)(uint32_t)(p_param_config->ir_mux));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_AGAIN_SET, (void *)(uint32_t)(p_param_config->again_val));
    if (ret != AM_OK) {
        return ret;
    }

    __tmd3702vc_read(p_this, __TMD3702VC_REG_CFG1, &reg, 1);
    reg |= (1 << 5);        /* CFG1�Ĵ�����bit5������1 */
    ret = __tmd3702vc_write(p_this, __TMD3702VC_REG_CFG1, &reg, 1);
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG3 �Ĵ������� */
    __tmd3702vc_status_clr_all(p_this);      /* ���STATUS�Ĵ��� */

    reg = 0x00;
    reg = __TMD3702VC_SAI_SET(p_param_config->sleep_after_interrupt);
    ret = __tmd3702vc_modify_reg_val(p_this, __TMD3702VC_REG_CFG3 , __TMD3702VC_MASK_CFG3_SAI, reg);
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG4 �Ĵ������� */
    reg = 0x3D;
    ret = __tmd3702vc_write(p_this, __TMD3702VC_REG_CFG4, &reg, 1);
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG6 �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_APC_SET, (void *)(uint32_t)(p_param_config->apc_disable));
    if (ret != AM_OK) {
        return ret;
    }

    /* CALIBCFG �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PROX_AVG_SET, (void *)(uint32_t)(p_param_config->prox_avg));
    if (ret != AM_OK) {
        return ret;
    }

    /* TEST3 �Ĵ������� */
    reg = 0xC4;
    ret = __tmd3702vc_write(p_this, __TMD3702VC_REG_TEST3, &reg, 1);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

#if __TMD3702VC_DEBUG
const char *__tmd3702vc_reg_name_string[] = {
"ENABLE   ",
"ATIME    ",
"PRATE    ",
"WTIME    ",
"AILTL    ",
"AILTH    ",
"AIHTL    ",
"AIHTH    ",
"PILTL    ",
"PILTH    ",
"PIHTL    ",
"PIHTH    ",
"PERS     ",
"CFG0     ",
"PCFG0    ",
"PCFG1    ",
"CFG1     ",
"REVID    ",
"ID       ",
"STATUS   ",
"CDATAL   ",
"CDATAH   ",
"RDATAL   ",
"RDATAH   ",
"GDATAL   ",
"GDATAH   ",
"BDATAL   ",
"BDATAH   ",
"PDATAL   ",
"PDATAH   ",
"REVID2   ",
"CFG2     ",
"SOFTRST  ",
"CFG3     ",
"CFG4     ",
"CFG6     ",
"POFFSETL ",
"POFFSETH ",
"CALIB    ",
"CALIBCFG ",
"CALIBSTAT",
"INTENAB  ",
"FAC_L    ",
"FAC_H    ",
"TEST3    ",
};

/* ���ڲ鿴�Ĵ���ֵ */
am_local void __tmd3702vc_regval_check(am_sensor_tmd3702vc_dev_t *p_this)
{
    uint8_t reg_val[45]         = {0};         /* ����Ĵ���ֵ */
    uint8_t counter = 0;

    __tmd3702vc_read(p_this, __TMD3702VC_REG_ENABLE, reg_val, 33);
    for (counter = 0; counter < 33;counter++) {
        am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);
    }

    __tmd3702vc_read(p_this, __TMD3702VC_REG_CFG3, &reg_val[33], 2);
    for (counter = 33; counter < 35;counter++) {
        am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);
    }

    __tmd3702vc_read(p_this, __TMD3702VC_REG_CFG6, &reg_val[35], 1);
    counter = 35;
    am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);

    __tmd3702vc_read(p_this, __TMD3702VC_REG_POFFSETL, &reg_val[36], 2);
    for (counter = 36; counter < 38;counter++) {
        am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);
    }

    __tmd3702vc_read(p_this, __TMD3702VC_REG_CALIB, &reg_val[38], 1);
    counter = 38;
    am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);

    __tmd3702vc_read(p_this, __TMD3702VC_REG_CALIBCFG, &reg_val[39], 1);
    counter = 39;
    am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);

    __tmd3702vc_read(p_this, __TMD3702VC_REG_CALIBSTAT, &reg_val[40], 2);
    for (counter = 40; counter < 42;counter++) {
        am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);
    }

    __tmd3702vc_read(p_this, __TMD3702VC_REG_FAC_L, &reg_val[42], 2);
    for (counter = 42; counter < 44;counter++) {
        am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);
    }

    __tmd3702vc_read(p_this, __TMD3702VC_REG_TEST3, &reg_val[44], 1);
    counter = 44;
    am_kprintf("%s : 0x%02x \r\n",__tmd3702vc_reg_name_string[counter], reg_val[counter]);
}
#endif

/** \brief TMD3702VC У׼ */
am_local am_err_t __tmd3702vc_open_cal(am_sensor_tmd3702vc_dev_t    *p_this)
{
    am_err_t ret    = AM_OK;

    tmd3702vc_param_config_t *p_param_config = (tmd3702vc_param_config_t *)p_this->dev_info->p_param_default;

    /* enable �Ĵ������ý��� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_FUNC_DISABLE,
                               (void *)(AM_TMD3702VC_WEN | \
                                        AM_TMD3702VC_PEN | \
                                        AM_TMD3702VC_AEN | \
                                        AM_TMD3702VC_PON ));
    if (ret != AM_OK) {
        return ret;
    }

    /* enable �Ĵ�������ʹ�� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_FUNC_ENABLE,
                                   (void *)AM_TMD3702VC_PON);
    if (ret != AM_OK) {
        return ret;
    }

    /* ���жϱ�־λ */
    __tmd3702vc_status_clr_all(p_this);

    /* INTENAB �Ĵ������� */

    /* У׼�ж�ʹ�� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_INT_ENABLE, (void *)AM_TMD3702VC_CIEN);
    if (ret != AM_OK) {
        return ret;
    }

    /* CALIBCFG �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_BINSRCH_TARGET_SET, (void *)(uint32_t)p_param_config->binsrch_target);
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_AUTO_OFFSET_ADJ_SET, (void *)(uint32_t)p_param_config->auto_offset_adj);
    if (ret != AM_OK) {
        return ret;
    }

    /* CALIB �Ĵ������� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_PROX_CAL_TYPE_SEL, (void *)(uint32_t)p_param_config->prox_cal_type);
    if (ret != AM_OK) {
        return ret;
    }

    /* ����ƫ��У׼ */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_START_OFFSET_CAL_SET, (void *)AM_TRUE);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

am_local am_err_t __tmd3702vc_close_cal(am_sensor_tmd3702vc_dev_t   *p_this)
{
    am_err_t ret    = AM_OK;

    /* ���STATUS */
    __tmd3702vc_status_clr_all(p_this);

    /* У׼�жϽ��� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_INT_DISABLE, (void *)AM_TMD3702VC_CIEN);
    if (ret != AM_OK) {
        return ret;
    }

    /* enable �Ĵ������ý��� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_FUNC_DISABLE,
                                                (void *)AM_TMD3702VC_PON);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

am_local am_err_t __tmd3702vc_calibration(am_sensor_tmd3702vc_dev_t *p_this)
{
    am_err_t ret    = AM_OK;

    uint8_t reg             = 0x00;         /* ����Ĵ���ֵ */
    uint8_t offset_data[2]  = {0};          /* ����ƫ�ƼĴ���ֵ */
    uint32_t cal_timeout    = 0xffff;       /* У׼��ʱ���� */

    /* ����У׼ */
    ret = __tmd3702vc_open_cal(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    while(1) {

        /* �ȴ�У׼����������� */
        __tmd3702vc_read(p_this, __TMD3702VC_REG_CALIBSTAT, &reg, 1);

        if (__TMD3702VC_CALIB_FINISHED_GET(reg) == 0x01) {     /* CALIB_FINISHED = 1 */

            am_kprintf("tmd3702vc_calibration finished!\r\n");

            break;
        }
        if (cal_timeout != 0) {
            cal_timeout--;
        }
        if (!cal_timeout) {

            am_kprintf("tmd3702vc_calibration timeout!\r\n");

            /* �ر�У׼ */
            __tmd3702vc_close_cal(p_this);

            return AM_ERROR;
        }
    }

    /* ��ȡPOFFSETL��POFFSETH */
    am_mdelay(100);
    __tmd3702vc_read(p_this, __TMD3702VC_REG_POFFSETL, offset_data, 2);
#if __TMD3702VC_DEBUG
    am_kprintf("offset_data[0] : 0x%02x \r\n", offset_data[0]);
    am_kprintf("offset_data[1] : 0x%02x \r\n", offset_data[1]);
#endif
    __tmd3702vc_offset_cal(p_this, offset_data);

    /* �ر�У׼ */
    ret = __tmd3702vc_close_cal(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/**
 * \brief TMD3702VC ��ȡ���
 */
am_local am_err_t __tmd3702vc_result_get(am_sensor_tmd3702vc_dev_t  *p_this,
                                         tmd3702vc_result_info_t    *p_result)
{
    am_err_t ret = AM_OK;

    uint8_t result_buf[10]  = {0};         /* ����Ĵ���ֵ */

    __tmd3702vc_read(p_this, __TMD3702VC_REG_CDATAL, result_buf, 10);

    /* clear */
    p_result->clear_channel_data = __TMD3702VC_UINT8_TO_UINT16(&result_buf[0]);

    /* red */
    p_result->red_channel_data = __TMD3702VC_UINT8_TO_UINT16(&result_buf[2]);

    /* green_or_ir */
    p_result->green_or_ir_channel_data = __TMD3702VC_UINT8_TO_UINT16(&result_buf[4]);

    /* blue */
    p_result->blue_channel_data = __TMD3702VC_UINT8_TO_UINT16(&result_buf[6]);

    /* Prox ADֵ */
    if (p_this->dev_info->p_param_default->apc_disable == AM_TMD3702VC_APC_ENABLE) {
        p_result->raw_prox_value = __TMD3702VC_UINT8_TO_UINT16(&result_buf[8]);
    } else {
        p_result->raw_prox_value = (uint16_t)((result_buf[8] << 2) | (result_buf[9] & 0x03));
    }

    /* prox ƫ��ֵ */
    p_result->prox_offset_adjust_value = p_this->cal_val[0].prox_offset_adj;

    /* Prox */
    p_result->prox_value = p_result->raw_prox_value;

    return ret;
}

/*******************************************************************************/

/** \breif �жϻص����� */
am_local void __tmd3702vc_alarm_callback (void *p_arg)
{
    am_sensor_tmd3702vc_dev_t* p_this = (am_sensor_tmd3702vc_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /*< \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_tmd3702vc_dev_t* p_this = (am_sensor_tmd3702vc_dev_t*)p_arg;

    tmd3702vc_result_info_t result;

    /* ��ȡ���� */
    __tmd3702vc_result_get(p_this, &result);

    /* ��ȡ���ݺ����жϱ�־λ */
    __tmd3702vc_status_clr_all(p_this);

    /* ��ȡProx */
    p_this->data[0].val = result.prox_value;
    p_this->data[0].unit = AM_SENSOR_UNIT_BASE;

    /* ��ȡALS */
    p_this->data[1].val = result.clear_channel_data;
    p_this->data[1].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[2].val = result.red_channel_data;
    p_this->data[2].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[3].val = result.green_or_ir_channel_data;
    p_this->data[3].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[4].val = result.blue_channel_data;
    p_this->data[4].unit = AM_SENSOR_UNIT_BASE;

    if (p_this->pfn_trigger_cb[0] &&
            (p_this->flags[0] & AM_SENSOR_TRIGGER_THRESHOLD)) {
        p_this->pfn_trigger_cb[0](p_this->p_arg[0],
                                  AM_SENSOR_TRIGGER_THRESHOLD);
    }

    if (p_this->pfn_trigger_cb[1] &&
            (p_this->flags[1] & AM_SENSOR_TRIGGER_THRESHOLD)) {
        p_this->pfn_trigger_cb[1](p_this->p_arg[1],
                                  AM_SENSOR_TRIGGER_THRESHOLD);
    }
}

/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (id == AM_TMD3702VC_CHAN_1) {
        return AM_SENSOR_TYPE_PROXIMITY;
    } else if (id == AM_TMD3702VC_CHAN_2) {
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
    am_sensor_tmd3702vc_dev_t* p_this = (am_sensor_tmd3702vc_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    tmd3702vc_result_info_t result;

    int cur_id = 0;
    int i = 0;

    uint8_t j;
    uint16_t times = 0xff;       /* ��ȡ����ʱ�� */

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

            if (cur_id == 0) {

                p_buf[0].val = p_this->data[cur_id].val;
                p_buf[0].unit= p_this->data[cur_id].unit;

            } else if (cur_id == 1) {

                for (j = 0; j < 4; j++) {
                    p_buf[j].val = p_this->data[cur_id + j].val;
                    p_buf[j].unit= p_this->data[cur_id + j].unit;
                }

            } else {
                return -AM_ENODEV;
            }
            return AM_OK;
        }
    }

    /** \brief ��ȡ������� */
    do {
        ret = __tmd3702vc_result_get(p_this, &result);
        if (times != 0) {
            times--;
        }
    } while ((ret != AM_OK) && (times != 0));

    if (ret != AM_OK) {
        return ret;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            p_buf[i].val  = result.prox_value;                  /*< \brief Prox */
            p_buf[i].unit = AM_SENSOR_UNIT_BASE;                /*< \brief ��λĬ��Ϊ0:10^(0)*/

        } else if (cur_id == 1) {       /*< \brief ALS */

            p_buf[i].val  = result.clear_channel_data;          /* clear */
            p_buf[i].unit = AM_SENSOR_UNIT_BASE;                /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+1].val  = result.red_channel_data;          /* red */
            p_buf[i+1].unit = AM_SENSOR_UNIT_BASE;              /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+2].val  = result.green_or_ir_channel_data;  /* green_or_ir */
            p_buf[i+2].unit = AM_SENSOR_UNIT_BASE;              /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+3].val  = result.blue_channel_data;         /* blue */
            p_buf[i+3].unit = AM_SENSOR_UNIT_BASE;              /*< \brief ��λĬ��Ϊ0:10^(0)*/

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
    am_sensor_tmd3702vc_dev_t* p_this = (am_sensor_tmd3702vc_dev_t*)p_drv;

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
    ret = __tmd3702vc_param_init(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* У׼ */
    ret = __tmd3702vc_calibration(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* enable �Ĵ�������ʹ�� */
    ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_FUNC_ENABLE,
                            (void *)(AM_TMD3702VC_WEN | \
                                     AM_TMD3702VC_PEN | \
                                     AM_TMD3702VC_AEN | \
                                     AM_TMD3702VC_PON ));
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
    am_sensor_tmd3702vc_dev_t* p_this = (am_sensor_tmd3702vc_dev_t*)p_drv;

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
        ret = __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_FUNC_DISABLE,
                                    (void *)(AM_TMD3702VC_WEN | \
                                             AM_TMD3702VC_PEN | \
                                             AM_TMD3702VC_AEN | \
                                             AM_TMD3702VC_PON ));
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
    am_sensor_tmd3702vc_dev_t* p_this = (am_sensor_tmd3702vc_dev_t*)p_drv;

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
    am_sensor_tmd3702vc_dev_t* p_this = (am_sensor_tmd3702vc_dev_t*)p_drv;

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
    __tmd3702vc_status_clr_all(p_this);

    /* ʹ���ж� */
    __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_INT_ENABLE,
                                (void *)(AM_TMD3702VC_PIEN |    /* Prox�ж� */
                                         AM_TMD3702VC_AIEN));   /* ALS�ж� */

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
    am_sensor_tmd3702vc_dev_t* p_this = (am_sensor_tmd3702vc_dev_t*)p_drv;

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
            __tmd3702vc_ioctl(p_this, AM_SENSOR_TMD3702VC_INT_DISABLE,
                                               (void *)(AM_TMD3702VC_PIEN |    /* Prox�ж� */
                                                        AM_TMD3702VC_AIEN));   /* ALS�ж� */
            AM_BIT_CLR(p_this->trigger, 2);
        }
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ TMD3702VC ��ʼ��
 */
am_sensor_handle_t am_sensor_tmd3702vc_init (
        am_sensor_tmd3702vc_dev_t           *p_dev,
        const am_sensor_tmd3702vc_devinfo_t *p_devinfo,
        am_i2c_handle_t                      handle)
{
    am_err_t ret = AM_OK;

    uint8_t tmd3702vc_id = 0;
    uint8_t reg = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->tmd3702vc_dev.p_drv   = p_dev;
    p_dev->tmd3702vc_dev.p_funcs = &__g_sensor_tmd3702vc_funcs;
    p_dev->dev_info           = p_devinfo;
    p_dev->pfn_trigger_cb[0]  = NULL;
    p_dev->pfn_trigger_cb[1]  = NULL;
    p_dev->p_arg[0]           = NULL;
    p_dev->p_arg[1]           = NULL;
    p_dev->flags[0]           = 0;
    p_dev->flags[1]           = 0;
    p_dev->trigger            = 0;
    p_dev->data[0].val        = 0;
    p_dev->data[0].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[1].val        = 0;
    p_dev->data[1].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[2].val        = 0;
    p_dev->data[2].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[3].val        = 0;
    p_dev->data[3].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[4].val        = 0;
    p_dev->data[4].unit       = AM_SENSOR_UNIT_INVALID;

    if (p_devinfo->trigger_pin != -1) {
        am_gpio_pin_cfg(p_devinfo->trigger_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);
        am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                __tmd3702vc_alarm_callback,
                                (void*)p_dev);
        am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_FALL);  /* �½��ش��� */
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    /* TMD3702VC�����λ */
    __tmd3702vc_softrst(p_dev);
    am_mdelay(10);

    /* �ȴ���λ��� */
    do {
        __tmd3702vc_read(p_dev, __TMD3702VC_REG_SOFTRST, &reg, 1);

    } while (__TMD3702VC_SOFTRST_GET(reg) == 0x1);

    ret = __tmd3702vc_read(p_dev, __TMD3702VC_REG_ID, &tmd3702vc_id, 1);
    if ((ret != AM_OK) || (tmd3702vc_id != __TMD3702VC_ID)) {
    #if __TMD3702VC_DEBUG
        am_kprintf("tmd3702vc_id = 0x%x \r\n", tmd3702vc_id);
    #endif
        am_kprintf("\r\nSensor TMD3702VC Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->tmd3702vc_dev);
}

/**
 * \brief ������ TMD3702VC ȥ��ʼ��
 */
am_err_t am_sensor_tmd3702vc_deinit (am_sensor_handle_t handle)
{
    am_sensor_tmd3702vc_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->tmd3702vc_dev.p_drv   = NULL;
    p_dev->tmd3702vc_dev.p_funcs = NULL;
    p_dev->dev_info           = NULL;

    return AM_OK;
}

/**
 * \brief ������ TMD3702VC ���ƺ���
 */
am_err_t am_sensor_tmd3702vc_ioctl (am_sensor_handle_t  handle,
                                    int                 cmd,
                                    void               *p_arg)
{
    am_sensor_tmd3702vc_dev_t   *p_dev = (am_sensor_tmd3702vc_dev_t *)handle->p_drv;

    am_err_t ret = AM_OK;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    ret = __tmd3702vc_ioctl(p_dev, cmd, p_arg);

    return ret;
}

/* end of file */


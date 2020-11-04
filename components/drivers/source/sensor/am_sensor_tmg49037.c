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
 * \brief ������ TMG49037 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation.
 * \endinternal
 */

#include "am_sensor_tmg49037.h"
#include "am_sensor.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**< ������Ϣ��� */
#define __TMG49037_DEBUG            (0)

/*********************************************************************************************
 * �궨��
 ********************************************************************************************/
#define __TMG49037_REG_ENABLE       (0x80)  /**< \brief ʹ��״̬                            */
#define __TMG49037_REG_ATIME        (0x81)  /**< \brief ����ALS ADC�Ļ���ʱ��               */
#define __TMG49037_REG_PTIME        (0x82)  /**< \brief Prox����ʱ��                        */
#define __TMG49037_REG_WTIME        (0x83)  /**< \brief ALS����֮��ĵȴ�ʱ��             */
#define __TMG49037_REG_AILTL        (0x84)  /**< \brief ALS�жϵ���ֵ���ֽ� (Clear)         */
#define __TMG49037_REG_AILTH        (0x85)  /**< \brief ALS�жϵ���ֵ���ֽ� (Clear)         */
#define __TMG49037_REG_AIHTL        (0x86)  /**< \brief ALS�жϸ���ֵ���ֽ� (Clear)         */
#define __TMG49037_REG_AIHTH        (0x87)  /**< \brief ALS�жϸ���ֵ���ֽ� (Clear)         */
#define __TMG49037_REG_PILTL        (0x88)  /**< \brief Prox�жϵ���ֵ���ֽ�                */
#define __TMG49037_REG_PILTH        (0x89)  /**< \brief Prox�жϵ���ֵ���ֽ�                */
#define __TMG49037_REG_PIHTL        (0x8A)  /**< \brief Prox�жϸ���ֵ���ֽ�                */
#define __TMG49037_REG_PIHTH        (0x8B)  /**< \brief Prox�жϸ���ֵ���ֽ�                */
#define __TMG49037_REG_PERS         (0x8C)  /**< \brief ALS and prox�жϹ�����              */
#define __TMG49037_REG_CFG0         (0x8D)  /**< \brief ���üĴ���0                         */
#define __TMG49037_REG_PGCFG0       (0x8E)  /**< \brief Prox/�������üĴ���0                */
#define __TMG49037_REG_PGCFG1       (0x8F)  /**< \brief Prox/�������üĴ���1                */
#define __TMG49037_REG_CFG1         (0x90)  /**< \brief ���üĴ���1                         */
#define __TMG49037_REG_REVID        (0x91)  /**< \brief �޶�ID                              */
#define __TMG49037_REG_ID           (0x92)  /**< \brief �豸ID                              */
#define __TMG49037_REG_STATUS       (0x93)  /**< \brief ״̬�Ĵ���                          */
#define __TMG49037_REG_CDATAL       (0x94)  /**< \brief Clear ͨ��ADC���ݵ��ֽ�             */
#define __TMG49037_REG_CDATAH       (0x95)  /**< \brief Clear ͨ��ADC���ݸ��ֽ�             */
#define __TMG49037_REG_RDATAL       (0x96)  /**< \brief Red ͨ��ADC���ݵ��ֽ�               */
#define __TMG49037_REG_RDATAH       (0x97)  /**< \brief Red ͨ��ADC���ݸ��ֽ�               */
#define __TMG49037_REG_GDATAL       (0x98)  /**< \brief Green ͨ��ADC���ݵ��ֽ�             */
#define __TMG49037_REG_GDATAH       (0x99)  /**< \brief Green ͨ��ADC���ݸ��ֽ�             */
#define __TMG49037_REG_BDATAL       (0x9A)  /**< \brief Blue ͨ��ADC���ݵ��ֽ�              */
#define __TMG49037_REG_BDATAH       (0x9B)  /**< \brief Blue ͨ��ADC���ݸ��ֽ�              */
#define __TMG49037_REG_PDATAL       (0x9C)  /**< \brief Prox ADC���ݵ��ֽ�                  */
#define __TMG49037_REG_PDATAH       (0x9D)  /**< \brief Prox ADC���ݸ��ֽ�                  */
#define __TMG49037_REG_STATUS2      (0x9E)  /**< \brief ״̬�Ĵ���2                         */
#define __TMG49037_REG_CFG2         (0x9F)  /**< \brief ���üĴ���2                         */
#define __TMG49037_REG_CFG3         (0xAB)  /**< \brief ���üĴ���3                         */
#define __TMG49037_REG_CFG4         (0xAC)  /**< \brief ���üĴ���4                         */
#define __TMG49037_REG_CFG5         (0xAD)  /**< \brief ���üĴ���5                         */
#define __TMG49037_REG_GCFG0        (0xB0)  /**< \brief �������üĴ���0                     */
#define __TMG49037_REG_GCFG1        (0xB1)  /**< \brief �������üĴ���1                     */
#define __TMG49037_REG_GCFG2        (0xB2)  /**< \brief �������üĴ���2                     */
#define __TMG49037_REG_STATUS3      (0xB3)  /**< \brief ״̬�Ĵ���3                         */
#define __TMG49037_REG_GTIME        (0xB4)  /**< \brief ���Ʋ���ʱ��Ĵ���                  */
#define __TMG49037_REG_GST_CTRL     (0xB5)  /**< \brief ���ƿ��ƼĴ���                      */
#define __TMG49037_REG_GTHR_INL     (0xB6)  /**< \brief ���ƽ�����ֵ���ֽ�                  */
#define __TMG49037_REG_GTHR_INH     (0xB7)  /**< \brief ���ƽ�����ֵ���ֽ�                  */
#define __TMG49037_REG_GTHR_OUTL    (0xB8)  /**< \brief �����˳���ֵ���ֽ�                  */
#define __TMG49037_REG_GTHR_OUTH    (0xB9)  /**< \brief �����˳���ֵ���ֽ�                  */
#define __TMG49037_REG_GFIFO_LVL    (0xBA)  /**< \brief ����FIFO���弶                      */
#define __TMG49037_REG_GSTATUS      (0xBB)  /**< \brief ����״̬�Ĵ���                      */
#define __TMG49037_REG_CONTROL      (0xBC)  /**< \brief ���ƼĴ���                          */
#define __TMG49037_REG_AUXID        (0xBD)  /**< \brief AUXID                               */
#define __TMG49037_REG_OFFSETNL     (0xC0)  /**< \brief ��ͨ��ƫ�Ƶ��ֽ�����                */
#define __TMG49037_REG_OFFSETNH     (0xC1)  /**< \brief ��ͨ��ƫ�Ƹ��ֽ�����                */
#define __TMG49037_REG_OFFSETSL     (0xC2)  /**< \brief ��ͨ��ƫ�Ƶ��ֽ�����                */
#define __TMG49037_REG_OFFSETSH     (0xC3)  /**< \brief ��ͨ��ƫ�Ƹ��ֽ�����                */
#define __TMG49037_REG_OFFSETWL     (0xC4)  /**< \brief ��ͨ��ƫ�Ƶ��ֽ�����                */
#define __TMG49037_REG_OFFSETWH     (0xC5)  /**< \brief ��ͨ��ƫ�Ƹ��ֽ�����                */
#define __TMG49037_REG_OFFSETEL     (0xC6)  /**< \brief ��ͨ��ƫ�Ƶ��ֽ�����                */
#define __TMG49037_REG_OFFSETEH     (0xC7)  /**< \brief ��ͨ��ƫ�Ƹ��ֽ�����                */
#define __TMG49037_REG_PBSLN_MEASL  (0xD0)  /**< \brief �������ߵ��ֽ�����                  */
#define __TMG49037_REG_PBSLN_MEASH  (0xD1)  /**< \brief �������߸��ֽ�����                  */
#define __TMG49037_REG_PBSLNL       (0xD2)  /**< \brief �洢���ߵ��ֽ�����                  */
#define __TMG49037_REG_PBSLNH       (0xD3)  /**< \brief �洢���߸��ֽ�����                  */
#define __TMG49037_REG_AZ_CONFIG    (0xD6)  /**< \brief �Զ�����                            */
#define __TMG49037_REG_CALIB        (0xD7)  /**< \brief У׼�Ĵ���                          */
#define __TMG49037_REG_CALIBCFG0    (0xD8)  /**< \brief У׼���üĴ���0                     */
#define __TMG49037_REG_CALIBCFG1    (0xD9)  /**< \brief У׼���üĴ���1                     */
#define __TMG49037_REG_CALIBCFG2    (0xDA)  /**< \brief У׼���üĴ���2                     */
#define __TMG49037_REG_CALIBCFG3    (0xDB)  /**< \brief У׼���üĴ���3                     */
#define __TMG49037_REG_CALIBSTAT    (0xDC)  /**< \brief У׼״̬�Ĵ���                      */
#define __TMG49037_REG_INTENAB      (0xDD)  /**< \brief �ж�ʹ��                            */
#define __TMG49037_REG_INTCLEAR     (0xDE)  /**< \brief �ж����                            */
#define __TMG49037_REG_GFIFO_NL     (0xF8)  /**< \brief ���Ʊ�ͨ��FIFO���ֽ�                */
#define __TMG49037_REG_GFIFO_NH     (0xF9)  /**< \brief ���Ʊ�ͨ��FIFO���ֽ�                */
#define __TMG49037_REG_GFIFO_SL     (0xFA)  /**< \brief ������ͨ��FIFO���ֽ�                */
#define __TMG49037_REG_GFIFO_SH     (0xFB)  /**< \brief ������ͨ��FIFO���ֽ�                */
#define __TMG49037_REG_GFIFO_WL     (0xFC)  /**< \brief ������ͨ��FIFO���ֽ�                */
#define __TMG49037_REG_GFIFO_WH     (0xFD)  /**< \brief ������ͨ��FIFO���ֽ�                */
#define __TMG49037_REG_GFIFO_EL     (0xFE)  /**< \brief ���ƶ�ͨ��FIFO���ֽ�                */
#define __TMG49037_REG_GFIFO_EH     (0xFF)  /**< \brief ���ƶ�ͨ��FIFO���ֽ�                */

/** \brief ����PPERS */
#define __TMG49037_MASK_PERS_PPERS                          (0xf << 4)
#define __TMG49037_PPERS_SET(val)                           ((val) << 4)

/** \brief ����APERS */
#define __TMG49037_MASK_PERS_APERS                          (0xf << 0)
#define __TMG49037_APERS_SET(val)                           ((val) << 0)

/** \brief ����LOWPOWER_IDLE */
#define __TMG49037_MASK_CFG0_LOWPOWER_IDLE                  (0x1 << 5)
#define __TMG49037_LOWPOWER_IDLE_SET(val)                   ((val) << 5)

/** \brief ����WLONG(wait long) */
#define __TMG49037_MASK_CFG0_WLONG                          (0x1 << 2)
#define __TMG49037_WLONG_SET(val)                           ((val) << 2)

/** \brief ����PGPULSE_LEN */
#define __TMG49037_MASK_PGCFG0_PGPULSE_LEN                  (0x3 << 6)
#define __TMG49037_PGPULSE_LEN_SET(val)                     ((val) << 6)

/** \brief ����PPULSE */
#define __TMG49037_MASK_PGCFG0_PPULSE                       (0x3f << 0)
#define __TMG49037_PPULSE_SET(val)                          ((val) << 0)

/** \brief ����PGGAIN */
#define __TMG49037_MASK_PGCFG1_PGGAIN                       (0x3 << 6)
#define __TMG49037_PGGAIN_SET(val)                          ((val) << 6)

/** \brief ����PGLDRIVE */
#define __TMG49037_MASK_PGCFG1_PGLDRIVE                     (0xf << 1)
#define __TMG49037_PGLDRIVE_SET(val)                        ((val) << 1)

/** \brief ����AGAIN */
#define __TMG49037_MASK_CFG1_AGAIN                          (0x3 << 0)
#define __TMG49037_AGAIN_SET(val)                           ((val) << 0)

/** \brief TMG49037 ID */
#define __TMG49037_ID                                       (0xB8)

/** \brief ��ȡPINT״̬ */
#define __TMG49037_PINT_STATUS(reg)                         (((reg) >> 5) & 0x1)

/** \brief ��ȡAINT״̬ */
#define __TMG49037_AINT_STATUS(reg)                         (((reg) >> 4) & 0x1)

/** \brief ��ȡGINT״̬ */
#define __TMG49037_GINT_STATUS(reg)                         (((reg) >> 2) & 0x1)

/** \brief ��ȡCINT״̬ */
#define __TMG49037_CINT_STATUS(reg)                         (((reg) >> 1) & 0x1)

/** \brief ��ȡPVALID״̬ */
#define __TMG49037_PVALID_STATUS2(reg)                      (((reg) >> 7) & 0x1)

/** \brief ��ȡAVALID״̬ */
#define __TMG49037_AVALID_STATUS2(reg)                      (((reg) >> 6) & 0x1)

/** \brief ����LTF_USEPROX */
#define __TMG49037_MASK_CFG3_LTF_USEPROX                    (0x1 << 6)
#define __TMG49037_LTF_USEPROX_SET(val)                     ((val) << 6)

/** \brief ����SAI */
#define __TMG49037_MASK_CFG3_SAI                            (0x1 << 4)
#define __TMG49037_SAI_SET(val)                             ((val) << 4)

/** \brief ����GTHR_OUT_NR */
#define __TMG49037_MASK_GCFG0_GTHR_OUT_NR                   (0x3 << 0)
#define __TMG49037_GTHR_OUT_NR_SET(val)                     ((val) << 0)

/** \brief ����GFIFOTHR */
#define __TMG49037_MASK_GCFG1_GFIFOTHR                      (0x3 << 6)
#define __TMG49037_GFIFOTHR_SET(val)                        ((val) << 6)

/** \brief ����GPULSE */
#define __TMG49037_MASK_GCFG1_GPULSE                        (0x3f << 0)
#define __TMG49037_GPULSE_SET(val)                          ((val) << 0)

/** \brief ����GEST_FILTER_SIZE */
#define __TMG49037_MASK_GCFG2_GEST_FILTER_SIZE              (0x1 << 5)
#define __TMG49037_GEST_FILTER_SIZE_SET(val)                ((val) << 5)

/** \brief ����GEST_FILTER */
#define __TMG49037_MASK_GCFG2_GEST_FILTER                   (0x1 << 4)
#define __TMG49037_GEST_FILTER_SET(val)                     ((val) << 4)

/** \brief ��ȡSAI_ACTIVEλ */
#define __TMG49037_SAI_ACTIVE_STATUS3(reg)                  (((reg) >> 1) & 0x1)

/** \brief ����GMODE */
#define __TMG49037_MASK_GST_CTRL_GMODE                      (0x1 << 0)
#define __TMG49037_GMODE_SET(val)                           ((val) << 0)

/** \brief ��ȡGFIFO_OVλ */
#define __TMG49037_GFIFO_OV_GET(reg)                        (((reg) >> 1) & 0x1)

/** \brief ��ȡGVALIDλ */
#define __TMG49037_GVALID_GET(reg)                          (((reg) >> 0) & 0x1)

/** \brief TMG49037���SAI_ACTIVEλ */
#define __TMD3702VC_SAI_ACTIVE_CLEAR                        (0x1 << 0)

/** \brief ����ƫ��У׼���� */
#define __TMG49037_MASK_CALIB_START_OFFSET_CAL              (0x1 << 0)
#define __TMG49037_START_OFFSET_CAL(val)                    ((val) << 0)

/** \brief ����DCAVG_AUTO_OFFSET_ADJUST */
#define __TMG49037_MASK_CALIBCFG0_DCAVG_AUTO_OFFSET_ADJUST  (0x1 << 6)
#define __TMG49037_DCAVG_AUTO_OFFSET_ADJUST_SET(val)        ((val) << 6)

/** \brief ѡ��ProxУ׼���� */
#define __TMG49037_MASK_CALIBCFG0_ELECTRICAL_CALIBRATION    (0x1 << 4)
#define __TMG49037_PROX_CAL_TYPE_SEL(val)                   ((val) << 4)

/** \brief ����BINSRCH_SKIP */
#define __TMG49037_MASK_CALIBCFG0_BINSRCH_SKIP              (0x1 << 3)
#define __TMG49037_BINSRCH_SKIP_SET(val)                    ((val) << 3)

/** \brief ����DCAVG_ITERATIONS */
#define __TMG49037_MASK_CALIBCFG0_DCAVG_ITERATIONS          (0x7 << 0)
#define __TMG49037_DCAVG_ITERATIONS_SET(val)                ((val) << 0)

/** \brief ����PXDCAVG_AUTO_GTHR */
#define __TMG49037_MASK_CALIBCFG1_PXDCAVG_AUTO_GTHR         (0x1 << 7)
#define __TMG49037_PXDCAVG_AUTO_GTHR_SET(val)               ((val) << 7)

/** \brief ����PROX_AUTO_OFFSET_ADJUST */
#define __TMG49037_MASK_CALIBCFG1_PROX_AUTO_OFFSET_ADJUST   (0x1 << 6)
#define __TMG49037_PROX_AUTO_OFFSET_ADJUST_SET(val)         ((val) << 6)

/** \brief ����PXDCAVG_AUTO_BASELINE */
#define __TMG49037_MASK_CALIBCFG1_PXDCAVG_AUTO_BASELINE     (0x1 << 3)
#define __TMG49037_PXDCAVG_AUTO_BASELINE_SET(val)           ((val) << 3)

/** \brief ����PXDCAVG_BASELINE_WINDOW */
#define __TMG49037_MASK_CALIBCFG1_PXDCAVG_BASELINE_WINDOW   (0x7 << 0)
#define __TMG49037_PXDCAVG_BASELINE_WINDOW_SET(val)         ((val) << 0)

/** \brief ����DCAVG_AUTO_GTHR */
#define __TMG49037_MASK_CALIBCFG2_DCAVG_AUTO_GTHR           (0x1 << 7)
#define __TMG49037_DCAVG_AUTO_GTHR_SET(val)                 ((val) << 7)

/** \brief ����BINSRCH_TARGET */
#define __TMG49037_MASK_CALIBCFG2_BINSRCH_TARGET            (0x7 << 4)
#define __TMG49037_BINSRCH_TARGET_SET(val)                  ((val) << 4)

/** \brief ����AUTO_GTHR_IN_MULT */
#define __TMG49037_MASK_CALIBCFG2_AUTO_GTHR_IN_MULT         (0xf << 0)
#define __TMG49037_AUTO_GTHR_IN_MULT_SET(val)               ((val) << 0)

/** \brief ����ZERO_WEIGHT */
#define __TMG49037_MASK_CALIBCFG3_ZERO_WEIGHT               (0xf << 0)
#define __TMG49037_ZERO_WEIGHT_SET(val)                     ((val) << 0)

/** \brief ��ȡZERO_DETECTEDλ */
#define __TMG49037_ZERO_DETECTED_GET(reg)                   (((reg) >> 3) & 0x1)

/** \brief ��ȡBASELINE_ADJUSTEDλ */
#define __TMG49037_BASELINE_ADJUSTED_GET(reg)               (((reg) >> 2) & 0x1)

/** \brief ��ȡOFFSET_ADJUSTEDλ */
#define __TMG49037_OFFSET_ADJUSTED_GET(reg)                 (((reg) >> 1) & 0x1)

/** \brief ��ȡCALIB_FINISHEDλ */
#define __TMG49037_CALIB_FINISHED_GET(reg)                  (((reg) >> 0) & 0x1)

/** \brief ������uint8ת��Ϊһ��uint16_t���� */
#define __TMG49037_UINT8_TO_UINT16(buff)                    ((uint16_t)((*(buff + 1)) << 8 | (*buff)))

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
am_local am_const struct am_sensor_drv_funcs __g_sensor_tmg49037_funcs = {
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
 * \brief tmg49037 д����
 */
am_local am_err_t __tmg49037_write (am_sensor_tmg49037_dev_t    *p_this,
                                    uint32_t                     subaddr,
                                    uint8_t                     *p_buf,
                                    uint32_t                     nbytes)
{
    return am_i2c_write(&p_this->i2c_dev,
                        subaddr,
                        p_buf,
                        nbytes);
}

/*
 * \brief tmg49037 ������
 */
am_local am_err_t __tmg49037_read (am_sensor_tmg49037_dev_t *p_this,
                                   uint32_t                  subaddr,
                                   uint8_t                  *p_buf,
                                   uint32_t                  nbytes)
{
    return am_i2c_read(&p_this->i2c_dev,
                       subaddr,
                       p_buf,
                       nbytes);
}

/*
 * \brief tmg49037 �޸ļĴ���ֵ
 */
am_local am_err_t __tmg49037_modify_reg_val(am_sensor_tmg49037_dev_t    *p_this,
                                            uint8_t                      reg,
                                            uint8_t                      mask,
                                            uint8_t                      val)
{
    uint8_t regval = 0;
    am_err_t ret = AM_OK;

    if (mask == 0xFF) {
        regval = val;
    } else {
        ret = __tmg49037_read(p_this, reg, &regval, 1);
        if (ret != AM_OK) {
            return ret;
        }

        regval &= ~mask;
        regval |= (val & mask);
    }

    ret = __tmg49037_write(p_this, reg, &regval, 1);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/** \brief ������ֵ */
am_local am_err_t __tmg49037_threshold_set(am_sensor_tmg49037_dev_t *p_this,
                                           uint32_t                  subaddr,
                                           uint16_t                  value)
{
    am_err_t ret = AM_OK;

    uint8_t reg[2] = {0};

    reg[0] = value & 0xff;
    reg[1] = (value & 0xff00) >> 8;

    ret = __tmg49037_write(p_this, subaddr, reg, 2);

    return ret;
}

/** \brief ��ȡ��ֵ */
am_local am_err_t __tmg49037_threshold_get(am_sensor_tmg49037_dev_t *p_this,
                                           uint32_t                  subaddr,
                                           uint16_t                 *p_value)
{
    am_err_t ret = AM_OK;

    uint8_t reg[2] = {0};

    ret = __tmg49037_read(p_this, subaddr, reg, 2);

    *p_value = __TMG49037_UINT8_TO_UINT16(&reg[0]);

    return ret;
}

/*******************************************************************************/

am_local am_err_t __tmg49037_ioctl (am_sensor_tmg49037_dev_t    *p_dev,
                                    int                          cmd,
                                    void                        *p_arg)
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
    case AM_SENSOR_TMG49037_FUNC_ENABLE:
        reg = __TMG49037_REG_ENABLE;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ���ù��ܽ��� */
    case AM_SENSOR_TMG49037_FUNC_DISABLE:
        reg = __TMG49037_REG_ENABLE;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ATIME */
    case AM_SENSOR_TMG49037_ATIME_SET:
        reg = __TMG49037_REG_ATIME;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PTIME */
    case AM_SENSOR_TMG49037_PTIME_SET:
        reg = __TMG49037_REG_PTIME;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����WTIME */
    case AM_SENSOR_TMG49037_WTIME_SET:
        reg = __TMG49037_REG_WTIME;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ALS����ֵ */
    case AM_SENSOR_TMG49037_LOW_ALS_THRESHOLD_SET:
        ret = __tmg49037_threshold_set(p_dev, __TMG49037_REG_AILTL, (uint16_t)(int)p_arg);
        break;

    /* ����ALS����ֵ */
    case AM_SENSOR_TMG49037_HIGH_ALS_THRESHOLD_SET:
        ret = __tmg49037_threshold_set(p_dev, __TMG49037_REG_AIHTL, (uint16_t)(int)p_arg);
        break;

    /* ����Prox����ֵ */
    case AM_SENSOR_TMG49037_LOW_PROX_THRESHOLD_SET:
        ret = __tmg49037_threshold_set(p_dev, __TMG49037_REG_PILTL, (uint16_t)(int)p_arg);
        break;

    /* ����Prox����ֵ */
    case AM_SENSOR_TMG49037_HIGH_PROX_THRESHOLD_SET:
        ret = __tmg49037_threshold_set(p_dev, __TMG49037_REG_PIHTL, (uint16_t)(int)p_arg);
        break;

    /* ��ȡALS����ֵ */
    case AM_SENSOR_TMG49037_LOW_ALS_THRESHOLD_GET:
        ret = __tmg49037_threshold_get(p_dev, __TMG49037_REG_AILTL, (uint16_t *)p_arg);
        break;

    /* ��ȡALS����ֵ */
    case AM_SENSOR_TMG49037_HIGH_ALS_THRESHOLD_GET:
        ret = __tmg49037_threshold_get(p_dev, __TMG49037_REG_AIHTL, (uint16_t *)p_arg);
        break;

    /* ��ȡProx����ֵ */
    case AM_SENSOR_TMG49037_LOW_PROX_THRESHOLD_GET:
        ret = __tmg49037_threshold_get(p_dev, __TMG49037_REG_PILTL, (uint16_t *)p_arg);
        break;

    /* ��ȡProx����ֵ */
    case AM_SENSOR_TMG49037_HIGH_PROX_THRESHOLD_GET:
        ret = __tmg49037_threshold_get(p_dev, __TMG49037_REG_PIHTL, (uint16_t *)p_arg);
        break;

    /* ����PPERS */
    case AM_SENSOR_TMG49037_PPERS_SET:
        reg = __TMG49037_REG_PERS;
        regmask = __TMG49037_MASK_PERS_PPERS;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PPERS_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����APERS */
    case AM_SENSOR_TMG49037_APERS_SET:
        reg = __TMG49037_REG_PERS;
        regmask = __TMG49037_MASK_PERS_APERS;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_APERS_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LOWPOWER_IDLE */
    case AM_SENSOR_TMG49037_LOWPOWER_IDLE_SET:
        reg = __TMG49037_REG_CFG0;
        regmask = __TMG49037_MASK_CFG0_LOWPOWER_IDLE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_LOWPOWER_IDLE_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����WLONG(wait long) */
    case AM_SENSOR_TMG49037_WLONG_SET:
        reg = __TMG49037_REG_CFG0;
        regmask = __TMG49037_MASK_CFG0_WLONG;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMG49037_WLONG_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PGPULSE_LEN */
    case AM_SENSOR_TMG49037_PGPULSE_LEN_SET:
        reg = __TMG49037_REG_PGCFG0;
        regmask = __TMG49037_MASK_PGCFG0_PGPULSE_LEN;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PGPULSE_LEN_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����Prox���������������� */
    case AM_SENSOR_TMG49037_PPULSE_SET:
        reg = __TMG49037_REG_PGCFG0;
        regmask = __TMG49037_MASK_PGCFG0_PPULSE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PPULSE_SET(regval - 1);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����Prox IR���������� */
    case AM_SENSOR_TMG49037_PGGAIN_SET:
        reg = __TMG49037_REG_PGCFG1;
        regmask = __TMG49037_MASK_PGCFG1_PGGAIN;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PGGAIN_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����Prox IR VCSEL������������ */
    case AM_SENSOR_TMG49037_PGLDRIVE_SET:
        reg = __TMG49037_REG_PGCFG1;
        regmask = __TMG49037_MASK_PGCFG1_PGLDRIVE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PGLDRIVE_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ALS/Color���������� */
    case AM_SENSOR_TMG49037_AGAIN_SET:
        reg = __TMG49037_REG_CFG1;
        regmask = __TMG49037_MASK_CFG1_AGAIN;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_AGAIN_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ��ȡREVID */
    case AM_SENSOR_TMG49037_REVID_GET:
        ret = __tmg49037_read(p_dev, __TMG49037_REG_REVID, (uint8_t *)p_arg, 1);
        if (ret != AM_OK) {
        #if __TMG49037_DEBUG
            am_kprintf("\r\nSensor TMG49037 read REVID failed! \r\n");
        #endif
        }
        break;

    /* ��ȡID */
    case AM_SENSOR_TMG49037_ID_GET:
        ret = __tmg49037_read(p_dev, __TMG49037_REG_ID, (uint8_t *)p_arg, 1);
        if (ret != AM_OK) {
        #if __TMG49037_DEBUG
            am_kprintf("\r\nSensor TMG49037 read ID failed! \r\n");
        #endif
        }
        break;

    /* CFG2�Ĵ���λʹ�� */
    case AM_SENSOR_TMG49037_CFG2_ENABLE:
        reg = __TMG49037_REG_CFG2;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* CFG2�Ĵ���λ���� */
    case AM_SENSOR_TMG49037_CFG2_DISABLE:
        reg = __TMG49037_REG_CFG2;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����LTF_USEPROX */
    case AM_SENSOR_TMG49037_LTF_USEPROX_SET:
        reg = __TMG49037_REG_CFG3;
        regmask = __TMG49037_MASK_CFG3_LTF_USEPROX;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_LTF_USEPROX_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����SAI */
    case AM_SENSOR_TMG49037_SAI_SET:
        reg = __TMG49037_REG_CFG3;
        regmask = __TMG49037_MASK_CFG3_SAI;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMG49037_SAI_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* CFG4�Ĵ���λ��λ */
    case AM_SENSOR_TMG49037_CFG4_SET_BIT:
        reg = __TMG49037_REG_CFG4;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* CFG4�Ĵ���λ��� */
    case AM_SENSOR_TMG49037_CFG4_RESET_BIT:
        reg = __TMG49037_REG_CFG4;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* CFG5�Ĵ���λ��λ */
    case AM_SENSOR_TMG49037_CFG5_SET_BIT:
        reg = __TMG49037_REG_CFG5;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* CFG5�Ĵ���λ��� */
    case AM_SENSOR_TMG49037_CFG5_RESET_BIT:
        reg = __TMG49037_REG_CFG5;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GTHR_MASK */
    case AM_SENSOR_TMG49037_GTHR_MASK_SET:
        reg = __TMG49037_REG_GCFG0;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GTHR_OUT_NR */
    case AM_SENSOR_TMG49037_GTHR_OUT_NR_SET:
        reg = __TMG49037_REG_GCFG0;
        regmask = __TMG49037_MASK_GCFG0_GTHR_OUT_NR;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_GTHR_OUT_NR_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GFIFOTHR */
    case AM_SENSOR_TMG49037_GFIFOTHR_SET:
        reg = __TMG49037_REG_GCFG1;
        regmask = __TMG49037_MASK_GCFG1_GFIFOTHR;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_GFIFOTHR_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GPULSE */
    case AM_SENSOR_TMG49037_GPULSE_SET:
        reg = __TMG49037_REG_GCFG1;
        regmask = __TMG49037_MASK_GCFG1_GPULSE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_GPULSE_SET(regval - 1);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GEST_FILTER_SIZE */
    case AM_SENSOR_TMG49037_GEST_FILTER_SIZE_SET:
        reg = __TMG49037_REG_GCFG2;
        regmask = __TMG49037_MASK_GCFG2_GEST_FILTER_SIZE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_GEST_FILTER_SIZE_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GEST_FILTER */
    case AM_SENSOR_TMG49037_GEST_FILTER_SET:
        reg = __TMG49037_REG_GCFG2;
        regmask = __TMG49037_MASK_GCFG2_GEST_FILTER;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_GEST_FILTER_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GTIME */
    case AM_SENSOR_TMG49037_GTIME_SET:
        reg = __TMG49037_REG_GTIME;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����GMODE */
    case AM_SENSOR_TMG49037_GMODE_SET:
        reg = __TMG49037_REG_GST_CTRL;
        regmask = __TMG49037_MASK_GST_CTRL_GMODE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_GMODE_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �������ƽ�����ֵ */
    case AM_SENSOR_TMG49037_GESTURE_ENTRY_THRESHOLD_SET:
        ret = __tmg49037_threshold_set(p_dev, __TMG49037_REG_GTHR_INL, (uint16_t)(int)p_arg);
        break;

    /* ���������˳���ֵ */
    case AM_SENSOR_TMG49037_GESTURE_EXIT_THRESHOLD_SET:
        ret = __tmg49037_threshold_set(p_dev, __TMG49037_REG_GTHR_OUTL, (uint16_t)(int)p_arg);
        break;

    /* SAI_ACTIVE_CLEAR */
    case AM_SENSOR_TMG49037_SAI_ACTIVE_CLEAR:
        reg = __TMG49037_REG_CONTROL;
        regmask = __TMD3702VC_SAI_ACTIVE_CLEAR;
        regval = __TMD3702VC_SAI_ACTIVE_CLEAR;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ��ȡAUXID */
    case AM_SENSOR_TMG49037_AUXID_GET:
        ret = __tmg49037_read(p_dev, __TMG49037_REG_AUXID, (uint8_t *)p_arg, 1);
        if (ret != AM_OK) {
        #if __TMG49037_DEBUG
            am_kprintf("\r\nSensor TMG49037 read AUXID failed! \r\n");
        #endif
        }
        break;

    /* ����AZ_NTH_ITERATION */
    case AM_SENSOR_TMG49037_AZ_NTH_ITERATION_SET:
        reg = __TMG49037_REG_AZ_CONFIG;
        regmask = 0xFF;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ƫ��У׼ */
    case AM_SENSOR_TMG49037_START_OFFSET_CAL_SET:
        reg = __TMG49037_REG_CALIB;
        regmask = __TMG49037_MASK_CALIB_START_OFFSET_CAL;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMG49037_START_OFFSET_CAL(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����DCAVG_AUTO_OFFSET_ADJUST */
    case AM_SENSOR_TMG49037_DCAVG_AUTO_OFFSET_ADJUST_SET:
        reg = __TMG49037_REG_CALIBCFG0;
        regmask = __TMG49037_MASK_CALIBCFG0_DCAVG_AUTO_OFFSET_ADJUST;
        regval = (am_bool_t)(int)p_arg;
        regval = __TMG49037_DCAVG_AUTO_OFFSET_ADJUST_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ѡ��ProxУ׼���� */
    case AM_SENSOR_TMG49037_PROX_CAL_TYPE_SEL:
        reg = __TMG49037_REG_CALIBCFG0;
        regmask = __TMG49037_MASK_CALIBCFG0_ELECTRICAL_CALIBRATION;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PROX_CAL_TYPE_SEL(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����BINSRCH_SKIP */
    case AM_SENSOR_TMG49037_BINSRCH_SKIP_SET:
        reg = __TMG49037_REG_CALIBCFG0;
        regmask = __TMG49037_MASK_CALIBCFG0_BINSRCH_SKIP;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_BINSRCH_SKIP_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����DCAVG_ITERATIONS */
    case AM_SENSOR_TMG49037_DCAVG_ITERATIONS_SET:
        reg = __TMG49037_REG_CALIBCFG0;
        regmask = __TMG49037_MASK_CALIBCFG0_DCAVG_ITERATIONS;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_DCAVG_ITERATIONS_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PXDCAVG_AUTO_GTHR */
    case AM_SENSOR_TMG49037_PXDCAVG_AUTO_GTHR_SET:
        reg = __TMG49037_REG_CALIBCFG1;
        regmask = __TMG49037_MASK_CALIBCFG1_PXDCAVG_AUTO_GTHR;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PXDCAVG_AUTO_GTHR_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PROX_AUTO_OFFSET_ADJUST */
    case AM_SENSOR_TMG49037_PROX_AUTO_OFFSET_ADJUST_SET:
        reg = __TMG49037_REG_CALIBCFG1;
        regmask = __TMG49037_MASK_CALIBCFG1_PROX_AUTO_OFFSET_ADJUST;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PROX_AUTO_OFFSET_ADJUST_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PXDCAVG_AUTO_BASELINE */
    case AM_SENSOR_TMG49037_PXDCAVG_AUTO_BASELINE_SET:
        reg = __TMG49037_REG_CALIBCFG1;
        regmask = __TMG49037_MASK_CALIBCFG1_PXDCAVG_AUTO_BASELINE;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PXDCAVG_AUTO_BASELINE_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����PXDCAVG_BASELINE_WINDOW */
    case AM_SENSOR_TMG49037_PXDCAVG_BASELINE_WINDOW_SET:
        reg = __TMG49037_REG_CALIBCFG1;
        regmask = __TMG49037_MASK_CALIBCFG1_PXDCAVG_BASELINE_WINDOW;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_PXDCAVG_BASELINE_WINDOW_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����DCAVG_AUTO_GTHR */
    case AM_SENSOR_TMG49037_DCAVG_AUTO_GTHR_SET:
        reg = __TMG49037_REG_CALIBCFG2;
        regmask = __TMG49037_MASK_CALIBCFG2_DCAVG_AUTO_GTHR;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_DCAVG_AUTO_GTHR_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����BINSRCH_TARGET */
    case AM_SENSOR_TMG49037_BINSRCH_TARGET_SET:
        reg = __TMG49037_REG_CALIBCFG2;
        regmask = __TMG49037_MASK_CALIBCFG2_BINSRCH_TARGET;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_BINSRCH_TARGET_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����AUTO_GTHR_IN_MULT */
    case AM_SENSOR_TMG49037_AUTO_GTHR_IN_MULT_SET:
        reg = __TMG49037_REG_CALIBCFG2;
        regmask = __TMG49037_MASK_CALIBCFG2_AUTO_GTHR_IN_MULT;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_AUTO_GTHR_IN_MULT_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* ����ZERO_WEIGHT */
    case AM_SENSOR_TMG49037_ZERO_WEIGHT_SET:
        reg = __TMG49037_REG_CALIBCFG3;
        regmask = __TMG49037_MASK_CALIBCFG3_ZERO_WEIGHT;
        regval = (uint8_t)(int)p_arg;
        regval = __TMG49037_ZERO_WEIGHT_SET(regval);
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �ж�ʹ�� */
    case AM_SENSOR_TMG49037_INT_ENABLE:
        reg = __TMG49037_REG_INTENAB;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �жϽ��� */
    case AM_SENSOR_TMG49037_INT_DISABLE:
        reg = __TMG49037_REG_INTENAB;
        regmask = (uint8_t)(int)p_arg;
        regval = 0x00;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    /* �ж���� */
    case AM_SENSOR_TMG49037_INT_CLEAR:
        reg = __TMG49037_REG_INTCLEAR;
        regmask = (uint8_t)(int)p_arg;
        regval = (uint8_t)(int)p_arg;
        ret = __tmg49037_modify_reg_val(p_dev, reg, regmask, regval);
        break;

    default:
        ret = -AM_ENOTSUP;
        break;
    }

    return ret;
}

/*******************************************************************************/

/** \brief TMG49037 ��ȡoffsetֵ */
am_local am_err_t __tmg49037_offset_cal(am_sensor_tmg49037_dev_t    *p_this,
                                        uint8_t                     *p_regval)
{
    am_err_t ret = AM_OK;

    if ((p_this == NULL) || (p_regval == NULL)) {
        return AM_ERROR;
    }

    if (p_regval[1] == 0xFF) {     //if (p_regval[1] == 1) {
        /* offsetΪ���� */
        p_this->cal_val[0].offset_n = (int16_t)(0 - p_regval[0]);

    } else {
        /* offsetΪ���� */
        p_this->cal_val[0].offset_n = (int16_t)p_regval[0];
    }

    if (p_regval[3] == 0xFF) {
        /* offsetΪ���� */
        p_this->cal_val[0].offset_s = (int16_t)(0 - p_regval[2]);

    } else {
        /* offsetΪ���� */
        p_this->cal_val[0].offset_s = (int16_t)p_regval[2];
    }

    if (p_regval[5] == 0xFF) {
        /* offsetΪ���� */
        p_this->cal_val[0].offset_w = (int16_t)(0 - p_regval[4]);

    } else {
        /* offsetΪ���� */
        p_this->cal_val[0].offset_w = (int16_t)p_regval[4];
    }

    if (p_regval[7] == 0xFF) {
        /* offsetΪ���� */
        p_this->cal_val[0].offset_e = (int16_t)(0 - p_regval[6]);

    } else {
        /* offsetΪ���� */
        p_this->cal_val[0].offset_e = (int16_t)p_regval[6];
    }

    return ret;
}

/** \brief TMG49037 ��������жϱ�־ */
am_local am_err_t __tmg49037_int_clear_all(am_sensor_tmg49037_dev_t *p_this)
{
    am_err_t ret = AM_OK;

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_INT_CLEAR,
                           (void *)(AM_TMG49037_INTCLEAR_ASAT  | \
                                    AM_TMG49037_INTCLEAR_PGSAT | \
                                    AM_TMG49037_INTCLEAR_PINT  | \
                                    AM_TMG49037_INTCLEAR_AINT  | \
                                    AM_TMG49037_INTCLEAR_GINT  | \
                                    AM_TMG49037_INTCLEAR_CINT ));

    return ret;
}

/** \brief TMG49037 ������ʼ�� */
am_local am_err_t __tmg49037_param_init(am_sensor_tmg49037_dev_t *p_this)
{
    tmg49037_param_config_t *p_param_config = (tmg49037_param_config_t *)p_this->dev_info->p_param_default;

    am_err_t ret = AM_OK;

    /* ATIME �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_ATIME_SET, (void *)(uint32_t)(p_param_config->atime_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* PTIME �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PTIME_SET, (void *)(uint32_t)(p_param_config->ptime_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* WTIME �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_WTIME_SET, (void *)(uint32_t)(p_param_config->wtime_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* PERS �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PPERS_SET, (void *)(uint32_t)(p_param_config->ppers_val));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_APERS_SET, (void *)(uint32_t)(p_param_config->apers_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG0 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_LOWPOWER_IDLE_SET, (void *)(uint32_t)(p_param_config->lowpower_idle));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_WLONG_SET, (void *)(uint32_t)(p_param_config->wlong_en));
    if (ret != AM_OK) {
        return ret;
    }

    /* PGCFG0 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PGPULSE_LEN_SET, (void *)(uint32_t)(p_param_config->pgpulse_len));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PPULSE_SET, (void *)(uint32_t)(p_param_config->pulse));
    if (ret != AM_OK) {
        return ret;
    }

    /* PGCFG1 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PGGAIN_SET, (void *)(uint32_t)(p_param_config->pggain_val));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PGLDRIVE_SET, (void *)(uint32_t)(p_param_config->pgldrive_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG1 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_AGAIN_SET, (void *)(uint32_t)(p_param_config->again_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG2 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_CFG2_ENABLE, 
                                    (void *)(AM_TMG49037_PMASK_E |\
                                             AM_TMG49037_PMASK_W |\
                                             AM_TMG49037_PMASK_S |\
                                             AM_TMG49037_PMASK_N |\
                                             AM_TMG49037_AMASK ));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG3 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_LTF_USEPROX_SET, (void *)(uint32_t)(p_param_config->ltf_useprox));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_SAI_SET, (void *)(uint32_t)(p_param_config->sleep_after_interrupt));
    if (ret != AM_OK) {
        return ret;
    }

    /* CFG5 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_CFG5_SET_BIT, (void *)(uint32_t)(p_param_config->cfg5_set_bit));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_CFG5_RESET_BIT, (void *)(uint32_t)(p_param_config->cfg5_reset_bit));
    if (ret != AM_OK) {
        return ret;
    }

    /* GCFG0 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_GTHR_MASK_SET, (void *)(uint32_t)(p_param_config->gthr_mask));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_GTHR_OUT_NR_SET, (void *)(uint32_t)(p_param_config->gthr_out_nr));
    if (ret != AM_OK) {
        return ret;
    }

    /* GCFG1 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_GFIFOTHR_SET, (void *)(uint32_t)(p_param_config->gfifothr));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_GPULSE_SET, (void *)(uint32_t)(p_param_config->gpulse));
    if (ret != AM_OK) {
        return ret;
    }

    /* GCFG2 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_GEST_FILTER_SIZE_SET, (void *)(uint32_t)(p_param_config->gest_filter_size));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_GEST_FILTER_SET, (void *)(uint32_t)(p_param_config->gest_filter));
    if (ret != AM_OK) {
        return ret;
    }

    /* GTIME �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_GTIME_SET, (void *)(uint32_t)(p_param_config->gtime_val));
    if (ret != AM_OK) {
        return ret;
    }

    /* CONTROL �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_SAI_ACTIVE_CLEAR, NULL);
    if (ret != AM_OK) {
        return ret;
    }

    /* AZ_CONFIG �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_AZ_NTH_ITERATION_SET, (void *)(uint32_t)(p_param_config->az_nth_iteration));
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

#if __TMG49037_DEBUG

struct tmg49037_debug_info {
    const char  **reg_name_str;
    uint8_t     *reg;
};

const char *__tmg49037_reg_name_string[] = {
"ENABLE     ",
"ATIME      ",
"PTIME      ",
"WTIME      ",
"AILTL      ",
"AILTH      ",
"AIHTL      ",
"AIHTH      ",
"PILTL      ",
"PILTH      ",
"PIHTL      ",
"PIHTH      ",
"PERS       ",
"CFG0       ",
"PGCFG0     ",
"PGCFG1     ",
"CFG1       ",
"REVID      ",
"ID         ",
"STATUS     ",
"CDATAL     ",
"CDATAH     ",
"RDATAL     ",
"RDATAH     ",
"GDATAL     ",
"GDATAH     ",
"BDATAL     ",
"BDATAH     ",
"PDATAL     ",
"PDATAH     ",
"STATUS2    ",
"CFG2       ",
"CFG3       ",
"CFG4       ",
"CFG5       ",
"GCFG0      ",
"GCFG1      ",
"GCFG2      ",
"STATUS3    ",
"GTIME      ",
"GST_CTRL   ",
"GTHR_INL   ",
"GTHR_INH   ",
"GTHR_OUTL  ",
"GTHR_OUTH  ",
"GFIFO_LVL  ",
"GSTATUS    ",
"CONTROL    ",
"AUXID      ",
"OFFSETNL   ",
"OFFSETNH   ",
"OFFSETSL   ",
"OFFSETSH   ",
"OFFSETWL   ",
"OFFSETWH   ",
"OFFSETEL   ",
"OFFSETEH   ",
"PBSLN_MEASL",
"PBSLN_MEASH",
"PBSLNL     ",
"PBSLNH     ",
"AZ_CONFIG  ",
"CALIB      ",
"CALIBCFG0  ",
"CALIBCFG1  ",
"CALIBCFG2  ",
"CALIBCFG3  ",
"CALIBSTAT  ",
"INTENAB    ",
"INTCLEAR   ",
"GFIFO_NL   ",
"GFIFO_NH   ",
"GFIFO_SL   ",
"GFIFO_SH   ",
"GFIFO_WL   ",
"GFIFO_WH   ",
"GFIFO_EL   ",
"GFIFO_EH   ",
};

static uint8_t __tmg49037_reg_name[] = {
__TMG49037_REG_ENABLE,
__TMG49037_REG_ATIME,
__TMG49037_REG_PTIME,
__TMG49037_REG_WTIME,
__TMG49037_REG_AILTL,
__TMG49037_REG_AILTH,
__TMG49037_REG_AIHTL,
__TMG49037_REG_AIHTH,
__TMG49037_REG_PILTL,
__TMG49037_REG_PILTH,
__TMG49037_REG_PIHTL,
__TMG49037_REG_PIHTH,
__TMG49037_REG_PERS,
__TMG49037_REG_CFG0,
__TMG49037_REG_PGCFG0,
__TMG49037_REG_PGCFG1,
__TMG49037_REG_CFG1,
__TMG49037_REG_REVID,
__TMG49037_REG_ID,
__TMG49037_REG_STATUS,
__TMG49037_REG_CDATAL,
__TMG49037_REG_CDATAH,
__TMG49037_REG_RDATAL,
__TMG49037_REG_RDATAH,
__TMG49037_REG_GDATAL,
__TMG49037_REG_GDATAH,
__TMG49037_REG_BDATAL,
__TMG49037_REG_BDATAH,
__TMG49037_REG_PDATAL,
__TMG49037_REG_PDATAH,
__TMG49037_REG_STATUS2,
__TMG49037_REG_CFG2,
__TMG49037_REG_CFG3,
__TMG49037_REG_CFG4,
__TMG49037_REG_CFG5,
__TMG49037_REG_GCFG0,
__TMG49037_REG_GCFG1,
__TMG49037_REG_GCFG2,
__TMG49037_REG_STATUS3,
__TMG49037_REG_GTIME,
__TMG49037_REG_GST_CTRL,
__TMG49037_REG_GTHR_INL,
__TMG49037_REG_GTHR_INH,
__TMG49037_REG_GTHR_OUTL,
__TMG49037_REG_GTHR_OUTH,
__TMG49037_REG_GFIFO_LVL,
__TMG49037_REG_GSTATUS,
__TMG49037_REG_CONTROL,
__TMG49037_REG_AUXID,
__TMG49037_REG_OFFSETNL,
__TMG49037_REG_OFFSETNH,
__TMG49037_REG_OFFSETSL,
__TMG49037_REG_OFFSETSH,
__TMG49037_REG_OFFSETWL,
__TMG49037_REG_OFFSETWH,
__TMG49037_REG_OFFSETEL,
__TMG49037_REG_OFFSETEH,
__TMG49037_REG_PBSLN_MEASL,
__TMG49037_REG_PBSLN_MEASH,
__TMG49037_REG_PBSLNL,
__TMG49037_REG_PBSLNH,
__TMG49037_REG_AZ_CONFIG,
__TMG49037_REG_CALIB,
__TMG49037_REG_CALIBCFG0,
__TMG49037_REG_CALIBCFG1,
__TMG49037_REG_CALIBCFG2,
__TMG49037_REG_CALIBCFG3,
__TMG49037_REG_CALIBSTAT,
__TMG49037_REG_INTENAB,
__TMG49037_REG_INTCLEAR,
__TMG49037_REG_GFIFO_NL,
__TMG49037_REG_GFIFO_NH,
__TMG49037_REG_GFIFO_SL,
__TMG49037_REG_GFIFO_SH,
__TMG49037_REG_GFIFO_WL,
__TMG49037_REG_GFIFO_WH,
__TMG49037_REG_GFIFO_EL,
__TMG49037_REG_GFIFO_EH,
};

struct tmg49037_debug_info __g_tmg49037_debug_info = {
    __tmg49037_reg_name_string,
    __tmg49037_reg_name,
};

/** \brief TMG49037 ����������мĴ���ֵ */
am_local void __tmg49037_regval_check(am_sensor_tmg49037_dev_t *p_this)
{
    uint8_t reg_buf[0xFF - 0x80 + 1]    = {0};         /* ����Ĵ���ֵ */
    uint8_t counter = 0;
    uint8_t reg_num = 0;

    __tmg49037_read(p_this, 0x80, reg_buf, (0xFF - 0x80 + 1));

    reg_num = AM_NELEMENTS(__tmg49037_reg_name);

    for (counter = 0; counter < reg_num; counter++) {
        am_kprintf("%s : 0x%02x \r\n",
                    __g_tmg49037_debug_info.reg_name_str[counter], 
                    reg_buf[__g_tmg49037_debug_info.reg[counter] - 0x80]);
    }
}
#endif

/** \brief TMG49037 У׼ */
am_local am_err_t __tmg49037_open_cal(am_sensor_tmg49037_dev_t  *p_this)
{
    am_err_t ret    = AM_OK;

    tmg49037_param_config_t *p_param_config = (tmg49037_param_config_t *)p_this->dev_info->p_param_default;

    /* enable �Ĵ������ý��� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_FUNC_DISABLE,
                                (void *)(AM_TMG49037_GEN | \
                                         AM_TMG49037_WEN | \
                                         AM_TMG49037_PEN | \
                                         AM_TMG49037_AEN | \
                                         AM_TMG49037_PON ));
    if (ret != AM_OK) {
        return ret;
    }

    /* enable �Ĵ�������ʹ�� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_FUNC_ENABLE,
                                    (void *)AM_TMG49037_PON);
    if (ret != AM_OK) {
        return ret;
    }

    /* ���жϱ�־λ */
    __tmg49037_int_clear_all(p_this);

    /* INTENAB �Ĵ������� */

    /* У׼�ж�ʹ�� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_INT_ENABLE,
                                    (void *)AM_TMG49037_CIEN);
    if (ret != AM_OK) {
        return ret;
    }

    /* CALIBCFG0 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_DCAVG_AUTO_OFFSET_ADJUST_SET, (void *)(uint32_t)(p_param_config->dcavg_auto_offset_adjust));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PROX_CAL_TYPE_SEL, (void *)(uint32_t)(p_param_config->prox_cal_type));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_BINSRCH_SKIP_SET, (void *)(uint32_t)(p_param_config->binsrch_skip));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_DCAVG_ITERATIONS_SET, (void *)(uint32_t)(p_param_config->dcavg_iterations));
    if (ret != AM_OK) {
        return ret;
    }

    /* CALIBCFG1 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PXDCAVG_AUTO_GTHR_SET, (void *)(uint32_t)(p_param_config->pxdcavg_auto_gthr));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PROX_AUTO_OFFSET_ADJUST_SET, (void *)(uint32_t)(p_param_config->prox_auto_offset_adjust));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PXDCAVG_AUTO_BASELINE_SET, (void *)(uint32_t)(p_param_config->pxdcavg_auto_baseline));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_PXDCAVG_BASELINE_WINDOW_SET, (void *)(uint32_t)(p_param_config->pxdcavg_baseline_window));
    if (ret != AM_OK) {
        return ret;
    }

    /* CALIBCFG2 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_DCAVG_AUTO_GTHR_SET, (void *)(uint32_t)(p_param_config->dcavg_auto_gthr));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_BINSRCH_TARGET_SET, (void *)(uint32_t)(p_param_config->binsrch_target));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_AUTO_GTHR_IN_MULT_SET, (void *)(uint32_t)(p_param_config->auto_gthr_in_mult));
    if (ret != AM_OK) {
        return ret;
    }

    /* CALIBCFG3 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_ZERO_WEIGHT_SET, (void *)(uint32_t)(p_param_config->zero_weight));
    if (ret != AM_OK) {
        return ret;
    }

    /* CALIB �Ĵ������� */

    /* ����ƫ��У׼ */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_START_OFFSET_CAL_SET, (void *)(AM_TRUE));
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

am_local am_err_t __tmg49037_close_cal(am_sensor_tmg49037_dev_t   *p_this)
{
    am_err_t ret    = AM_OK;

    /* ���жϱ�־λ */
    __tmg49037_int_clear_all(p_this);

    /* У׼�жϽ��� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_INT_DISABLE,
                                    (void *)AM_TMG49037_CIEN);
    if (ret != AM_OK) {
        return ret;
    }

    /* enable �Ĵ������ý��� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_FUNC_DISABLE,
                                    (void *)AM_TMG49037_PON);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

am_local am_err_t __tmg49037_calibration(am_sensor_tmg49037_dev_t *p_this)
{
    am_err_t ret    = AM_OK;

    uint8_t reg             = 0x00;         /* ����Ĵ���ֵ */
    uint8_t offset_data[8]  = {0};          /* ����ƫ�ƼĴ���ֵ */
    uint32_t cal_timeout    = 0xffff;       /* У׼��ʱ���� */

    /* ����У׼ */
    ret = __tmg49037_open_cal(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    while(1) {

        /* �ȴ�У׼����������� */
        __tmg49037_read(p_this, __TMG49037_REG_CALIBSTAT, &reg, 1);

        if (__TMG49037_CALIB_FINISHED_GET(reg) == 0x01) {     /* CALIB_FINISHED = 1 */

            am_kprintf("tmg49037_calibration finished!\r\n");

            break;
        }
        if (cal_timeout != 0) {
            cal_timeout--;
        }
        if (!cal_timeout) {

            am_kprintf("tmg49037_calibration timeout!\r\n");

            /* �ر�У׼ */
            __tmg49037_close_cal(p_this);

            return AM_ERROR;
        }
    }

    /* ��ȡ OFFSETxL��OFFSETxH */
    am_mdelay(100);
    __tmg49037_read(p_this, __TMG49037_REG_OFFSETNL, offset_data, 8);
#if __TMG49037_DEBUG
    am_kprintf("offset_data[0] : 0x%02x \r\n", offset_data[0]);
    am_kprintf("offset_data[1] : 0x%02x \r\n", offset_data[1]);
    am_kprintf("offset_data[2] : 0x%02x \r\n", offset_data[2]);
    am_kprintf("offset_data[3] : 0x%02x \r\n", offset_data[3]);
    am_kprintf("offset_data[4] : 0x%02x \r\n", offset_data[4]);
    am_kprintf("offset_data[5] : 0x%02x \r\n", offset_data[5]);
    am_kprintf("offset_data[6] : 0x%02x \r\n", offset_data[6]);
    am_kprintf("offset_data[7] : 0x%02x \r\n", offset_data[7]);
#endif
    __tmg49037_offset_cal(p_this, offset_data);

    /* �ر�У׼ */
    ret = __tmg49037_close_cal(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    return ret;
}

/**
 * \brief TMG49037 ��ȡ���
 */
am_local am_err_t __tmg49037_result_get(am_sensor_tmg49037_dev_t  *p_this,
                                         tmg49037_result_info_t    *p_result)
{
    am_err_t ret = AM_OK;

    uint8_t result_buf[18]  = {0};         /* ����Ĵ���ֵ */

    __tmg49037_read(p_this, __TMG49037_REG_CDATAL, &result_buf[0], 10);
    __tmg49037_read(p_this, __TMG49037_REG_GFIFO_NL, &result_buf[10], 8);

    /* clear */
    p_result->clear_channel_data = __TMG49037_UINT8_TO_UINT16(&result_buf[0]);

    /* red */
    p_result->red_channel_data = __TMG49037_UINT8_TO_UINT16(&result_buf[2]);

    /* green */
    p_result->green_channel_data = __TMG49037_UINT8_TO_UINT16(&result_buf[4]);

    /* blue */
    p_result->blue_channel_data = __TMG49037_UINT8_TO_UINT16(&result_buf[6]);

    /* Prox ADֵ */
    p_result->raw_prox_value = __TMG49037_UINT8_TO_UINT16(&result_buf[8]);

    /* GFIFON ADֵ */
    p_result->raw_gfifo_n = __TMG49037_UINT8_TO_UINT16(&result_buf[10]);

    /* GFIFOS ADֵ */
    p_result->raw_gfifo_s = __TMG49037_UINT8_TO_UINT16(&result_buf[12]);

    /* GFIFOW ADֵ */
    p_result->raw_gfifo_w = __TMG49037_UINT8_TO_UINT16(&result_buf[14]);

    /* GFIFOE ADֵ */
    p_result->raw_gfifo_e = __TMG49037_UINT8_TO_UINT16(&result_buf[16]);

    /* Prox У׼ֵ */
    p_result->prox_offset_adjust_value = 0;

    /* OFFSETN У׼ֵ */
    p_result->offset_n_adjust_value = 0;

    /* OFFSETS У׼ֵ */
    p_result->offset_s_adjust_value = 0;

    /* OFFSETW У׼ֵ */
    p_result->offset_w_adjust_value = 0;

    /* OFFSETE У׼ֵ */
    p_result->offset_e_adjust_value = 0;

    /* Prox */
    p_result->prox_value = p_result->raw_prox_value - p_result->prox_offset_adjust_value;

    /* GFIFON */
    p_result->gfifo_n = p_result->raw_gfifo_n - p_result->offset_n_adjust_value;

    /* GFIFOS */
    p_result->gfifo_s = p_result->raw_gfifo_s - p_result->offset_s_adjust_value;

    /* GFIFOW */
    p_result->gfifo_w = p_result->raw_gfifo_w - p_result->offset_w_adjust_value;

    /* GFIFOE */
    p_result->gfifo_e = p_result->raw_gfifo_e - p_result->offset_e_adjust_value;

    return ret;
}

/*******************************************************************************/

/** \breif �жϻص����� */
am_local void __tmg49037_alarm_callback (void *p_arg)
{
    am_sensor_tmg49037_dev_t* p_this = (am_sensor_tmg49037_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /*< \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_tmg49037_dev_t* p_this = (am_sensor_tmg49037_dev_t*)p_arg;

    uint8_t i = 0;
    
    tmg49037_result_info_t result;

    /* ��ȡ���� */
    __tmg49037_result_get(p_this, &result);

    /* ��ȡ���ݺ����жϱ�־λ */
    __tmg49037_int_clear_all(p_this);

    /* ��ȡProx */
    p_this->data[0].val = result.prox_value;
    p_this->data[0].unit = AM_SENSOR_UNIT_BASE;

    /* ��ȡALS */
    p_this->data[1].val = result.clear_channel_data;
    p_this->data[1].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[2].val = result.red_channel_data;
    p_this->data[2].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[3].val = result.green_channel_data;
    p_this->data[3].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[4].val = result.blue_channel_data;
    p_this->data[4].unit = AM_SENSOR_UNIT_BASE;

    /* ��ȡGESTURE */
    p_this->data[5].val = result.gfifo_n;
    p_this->data[5].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[6].val = result.gfifo_s;
    p_this->data[6].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[7].val = result.gfifo_w;
    p_this->data[7].unit = AM_SENSOR_UNIT_BASE;

    p_this->data[8].val = result.gfifo_e;
    p_this->data[8].unit = AM_SENSOR_UNIT_BASE;

    for (i = 0; i < 3; i++) {
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

    if (id == AM_TMG49037_CHAN_1) {
        return AM_SENSOR_TYPE_PROXIMITY;
    } else if (id == AM_TMG49037_CHAN_2) {
        return AM_SENSOR_TYPE_ALS;
    } else if (id == AM_TMG49037_CHAN_3) {
        return AM_SENSOR_TYPE_GESTURE;
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
    am_sensor_tmg49037_dev_t* p_this = (am_sensor_tmg49037_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    tmg49037_result_info_t result;

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
        if ((AM_BIT_GET(p_this->trigger, 3)) &&
                ((p_this->flags[0] & AM_SENSOR_TRIGGER_THRESHOLD) ||
                 (p_this->flags[1] & AM_SENSOR_TRIGGER_THRESHOLD) ||
                 (p_this->flags[2] & AM_SENSOR_TRIGGER_THRESHOLD))) {

            if (cur_id == 0) {

                p_buf[0].val = p_this->data[cur_id].val;
                p_buf[0].unit= p_this->data[cur_id].unit;

            } else if (cur_id == 1) {

                for (j = 0; j < 4; j++) {
                    p_buf[j].val = p_this->data[cur_id + j].val;
                    p_buf[j].unit= p_this->data[cur_id + j].unit;
                }

            } else if (cur_id == 2) {

                for (j = 0; j < 4; j++) {
                    p_buf[j].val = p_this->data[cur_id + 3 + j].val;
                    p_buf[j].unit= p_this->data[cur_id + 3 + j].unit;
                }

            } else {
                return -AM_ENODEV;
            }
            return AM_OK;
        }
    }

    /** \brief ��ȡ������� */
    do {
        ret = __tmg49037_result_get(p_this, &result);
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

            p_buf[i].val  = result.prox_value;              /*< \brief Prox */
            p_buf[i].unit = AM_SENSOR_UNIT_BASE;            /*< \brief ��λĬ��Ϊ0:10^(0)*/

        } else if (cur_id == 1) {       /*< \brief ALS */

            p_buf[i].val  = result.clear_channel_data;      /* clear */
            p_buf[i].unit = AM_SENSOR_UNIT_BASE;            /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+1].val  = result.red_channel_data;      /* red */
            p_buf[i+1].unit = AM_SENSOR_UNIT_BASE;          /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+2].val  = result.green_channel_data;    /* green */
            p_buf[i+2].unit = AM_SENSOR_UNIT_BASE;          /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+3].val  = result.blue_channel_data;     /* blue */
            p_buf[i+3].unit = AM_SENSOR_UNIT_BASE;          /*< \brief ��λĬ��Ϊ0:10^(0)*/

        } else if (cur_id == 2) {           /*< \brief GESTURE */

            p_buf[i+3].val  = result.gfifo_n;               /* gfifo_n */
            p_buf[i+3].unit = AM_SENSOR_UNIT_BASE;          /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+3+1].val  = result.gfifo_s;             /* gfifo_s */
            p_buf[i+3+1].unit = AM_SENSOR_UNIT_BASE;        /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+3+2].val  = result.gfifo_w;             /* gfifo_w */
            p_buf[i+3+2].unit = AM_SENSOR_UNIT_BASE;        /*< \brief ��λĬ��Ϊ0:10^(0)*/

            p_buf[i+3+3].val  = result.gfifo_e;             /* gfifo_e */
            p_buf[i+3+3].unit = AM_SENSOR_UNIT_BASE;        /*< \brief ��λĬ��Ϊ0:10^(0)*/

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
    am_sensor_tmg49037_dev_t* p_this = (am_sensor_tmg49037_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    am_err_t ret = -AM_ENODEV;
    am_err_t curent_ret = AM_OK;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0 || cur_id == 1 || cur_id == 2) {
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
    ret = __tmg49037_param_init(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* У׼ */
    ret = __tmg49037_calibration(p_this);
    if (ret != AM_OK) {
        return ret;
    }

    /* enable �Ĵ�������ʹ�� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_FUNC_ENABLE,
                                (void *)(AM_TMG49037_GEN | \
                                         AM_TMG49037_WEN | \
                                         AM_TMG49037_PEN | \
                                         AM_TMG49037_AEN | \
                                         AM_TMG49037_PON ));
    if (ret != AM_OK) {
        return ret;
    }

    if (ret == AM_OK) {
        AM_BIT_SET(p_this->trigger, 7);
        AM_BIT_SET(p_this->trigger, 6);
        AM_BIT_SET(p_this->trigger, 5);
        AM_BIT_SET(p_this->trigger, 4);
    }

    return curent_ret;
}

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result)
{
    am_sensor_tmg49037_dev_t* p_this = (am_sensor_tmg49037_dev_t*)p_drv;

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

        } else if (cur_id == 2) {

            AM_BIT_CLR(p_this->trigger, 4);
            ret = AM_OK;

        } else {
            ret = -AM_ENODEV;
        }

        if (p_result != NULL) {
            p_result[i].val = ret;
        }
    }

    if ((AM_BIT_GET(p_this->trigger, 6) == 0)
            && (AM_BIT_GET(p_this->trigger, 5) == 0)
            && (AM_BIT_GET(p_this->trigger, 4) == 0)) {

        /* enable �Ĵ������ý��� */
        ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_FUNC_DISABLE,
                                    (void *)(AM_TMG49037_GEN | \
                                             AM_TMG49037_WEN | \
                                             AM_TMG49037_PEN | \
                                             AM_TMG49037_AEN | \
                                             AM_TMG49037_PON ));
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
    am_sensor_tmg49037_dev_t* p_this = (am_sensor_tmg49037_dev_t*)p_drv;

    if (id != 0 && id != 1 && id != 2) {
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
    am_sensor_tmg49037_dev_t* p_this = (am_sensor_tmg49037_dev_t*)p_drv;
    tmg49037_param_config_t *p_param_config = (tmg49037_param_config_t *)p_this->dev_info->p_param_default;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    if (id != 0 && id != 1 && id != 2) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (p_this->trigger & 0x8) {
        return AM_OK;
    }

    if (p_this->dev_info->trigger_pin != -1) {
        ret = am_gpio_trigger_on(p_this->dev_info->trigger_pin);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }

    /* CFG4 �Ĵ������� */
    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_CFG4_SET_BIT, (void *)(uint32_t)(p_param_config->cfg4_set_bit));
    if (ret != AM_OK) {
        return ret;
    }

    ret = __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_CFG4_RESET_BIT, (void *)(uint32_t)(p_param_config->cfg4_reset_bit));
    if (ret != AM_OK) {
        return ret;
    }

    /* ���жϱ�־λ */
    __tmg49037_int_clear_all(p_this);

    /* ʹ���ж� */
    __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_INT_ENABLE,
                                        (void *)(AM_TMG49037_PIEN | \
                                                 AM_TMG49037_AIEN ));

    if (cur_ret == AM_OK && id == 0) {
        AM_BIT_SET(p_this->trigger, 0);
        AM_BIT_SET(p_this->trigger, 3);
    }
    if (cur_ret == AM_OK && id == 1) {
        AM_BIT_SET(p_this->trigger, 1);
        AM_BIT_SET(p_this->trigger, 3);
    }
    if (cur_ret == AM_OK && id == 2) {
        AM_BIT_SET(p_this->trigger, 2);
        AM_BIT_SET(p_this->trigger, 3);
    }

    return cur_ret;
}

/** \brief �رմ��� */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id)
{
    am_sensor_tmg49037_dev_t* p_this = (am_sensor_tmg49037_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    if (id != 0 && id != 1 && id != 2) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    p_this->pfn_trigger_cb[id] = NULL;
    p_this->p_arg[id]          = NULL;
    p_this->flags[id]          = 0;

    AM_BIT_CLR(p_this->trigger, id);

    if ((p_this->trigger & 0x7) == 0) {

        if ((p_this->dev_info->trigger_pin != -1) && (cur_ret == AM_OK)) {
            ret = am_gpio_trigger_off(p_this->dev_info->trigger_pin);
            if (ret != AM_OK) {
                cur_ret = ret;
            }
        }

        if (cur_ret == AM_OK) {

            /* �����ж� */
            __tmg49037_ioctl(p_this, AM_SENSOR_TMG49037_INT_DISABLE,
                                                (void *)(AM_TMG49037_PIEN | \
                                                         AM_TMG49037_AIEN ));
            AM_BIT_CLR(p_this->trigger, 3);
        }
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ TMG49037 ��ʼ��
 */
am_sensor_handle_t am_sensor_tmg49037_init (
        am_sensor_tmg49037_dev_t           *p_dev,
        const am_sensor_tmg49037_devinfo_t *p_devinfo,
        am_i2c_handle_t                     handle)
{
    am_err_t ret = AM_OK;

    uint8_t tmg49037_id = 0;

    uint8_t i = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->tmg49037_dev.p_drv   = p_dev;
    p_dev->tmg49037_dev.p_funcs = &__g_sensor_tmg49037_funcs;
    p_dev->dev_info           = p_devinfo;
    p_dev->pfn_trigger_cb[0]  = NULL;
    p_dev->pfn_trigger_cb[1]  = NULL;
    p_dev->pfn_trigger_cb[2]  = NULL;
    p_dev->p_arg[0]           = NULL;
    p_dev->p_arg[1]           = NULL;
    p_dev->p_arg[2]           = NULL;
    p_dev->flags[0]           = 0;
    p_dev->flags[1]           = 0;
    p_dev->flags[2]           = 0;
    p_dev->trigger            = 0;
    for (i = 0; i < 9; i++) {
        p_dev->data[i].val    = 0;
        p_dev->data[i].unit   = AM_SENSOR_UNIT_INVALID;
    }

    if (p_devinfo->trigger_pin != -1) {
        am_gpio_pin_cfg(p_devinfo->trigger_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);
        am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                __tmg49037_alarm_callback,
                                (void*)p_dev);
        am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_FALL);  /* �½��ش��� */
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    ret = __tmg49037_read(p_dev, __TMG49037_REG_ID, &tmg49037_id, 1);
    if ((ret != AM_OK) || (tmg49037_id != __TMG49037_ID)) {
    #if __TMG49037_DEBUG
        am_kprintf("tmg49037_id = 0x%x \r\n", tmg49037_id);
    #endif
        am_kprintf("\r\nSensor TMG49037 Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->tmg49037_dev);
}

/**
 * \brief ������ TMG49037 ȥ��ʼ��
 */
am_err_t am_sensor_tmg49037_deinit (am_sensor_handle_t handle)
{
    am_sensor_tmg49037_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->tmg49037_dev.p_drv   = NULL;
    p_dev->tmg49037_dev.p_funcs = NULL;
    p_dev->dev_info             = NULL;

    return AM_OK;
}

/**
 * \brief ������ TMG49037 ���ƺ���
 */
am_err_t am_sensor_tmg49037_ioctl (am_sensor_handle_t    handle,
                                   int                   cmd,
                                   void                 *p_arg)
{
    am_sensor_tmg49037_dev_t   *p_dev = (am_sensor_tmg49037_dev_t *)handle->p_drv;

    am_err_t ret = AM_OK;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    ret = __tmg49037_ioctl(p_dev, cmd, p_arg);

    return ret;
}

/* end of file */


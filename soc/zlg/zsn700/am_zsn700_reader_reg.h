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
 * \brief ZSN700_READER�Ĵ�������
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-01  htf, first implementation.
 * \endinternal
 */
 
#ifndef __ZSN700_READER_REG_H
#define __ZSN700_READER_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_zsn700_reader.h"
/** 
 * \addtogroup am_if_zsn700_reg
 * \copydoc am_zsn700_reg.h
 * @{
 */

/**
 * \name ZSN700_READER_REG ZSN700_READER�Ĵ�������
 * @{
 */
#define AM_ZSN700_READER_TXMODE_REG            0x12   /**< \brief �����������ʺ�֡��ʽ*/
#define AM_ZSN700_READER_RXMODE_REG            0x13   /**< \brief �����������ʺ�֡��ʽ */
#define AM_ZSN700_READER_TXCONTROL_REG         0x14   /**< \brief ������������TX1��TX2���� */
#define AM_ZSN700_READER_RXTHRESHOLD_REG       0x18   /**< \brief ������������ֵѡ�� */
#define AM_ZSN700_READER_MODWIDTH_REG          0x24   /**< \brief ���ƿ�ȿ��� */
#define AM_ZSN700_READER_RFCFG_REG             0x26   /**< \brief ���ý����������RF��ƽ */
#define AM_ZSN700_READER_GSN_REG               0x27   /**< \brief ѡ��������������TX1��TX2�ĵ絼�� */
#define AM_ZSN700_READER_CWGSP_REG             0x28   /**< \brief ѡ��������������TX1��TX2�ĵ絼�� */
#define AM_ZSN700_READER_MODGSP_REG            0x29   /**< \brief ѡ��������������TX1��TX2�ĵ絼�� */

/** @} */


/**
 * \name Command����Ĵ������� (0x01)
 * @{
 */

#define AM_ZSN700_READER_COMMAND_RCV_OFF         0x20        /**< \brief ��Ƶģ��������ر� */
#define AM_ZSN700_READER_COMMAND_POWER_DOWN      0x10        /**< \brief �����������ģʽ */
#define AM_ZSN700_READER_COMMAND_MASK            0x0F        /**< \brief ָ��Ĵ������� */

/** @} */


/**
 * \name CommIEN�ж�����ʹ�����ֹ���ƼĴ������� (0x02)
 * @{
 */

#define AM_ZSN700_READER_COMMIEN_IRQ_INV         0x80    /**< \brief IRQ�ź�ȡ�� ȱʡΪ1 */
#define AM_ZSN700_READER_COMMIEN_TX_IEN          0x40    /**< \brief ����TXIRQ�����ж����󴫵ݵ�IRQ */
#define AM_ZSN700_READER_COMMIEN_RX_IEN          0x20    /**< \brief ����RXIRQ�����ж����󴫵ݵ�IRQ */
#define AM_ZSN700_READER_COMMIEN_IDLE_IEN        0x10    /**< \brief ����IDLEIRQ�����ж����󴫵ݵ�IRQ */
#define AM_ZSN700_READER_COMMIEN_HIALERT_IEN     0x08    /**< \brief ����HIALERTIRQ�����ж����󴫵ݵ�IRQ */
#define AM_ZSN700_READER_COMMIEN_LOALERT_IEN     0x04    /**< \brief ����HIALERTIRQ�����ж����󴫵ݵ�IRQ */
#define AM_ZSN700_READER_COMMIEN_ERR_IEN         0x02    /**< \brief ����ERRIRQ�����ж����󴫵ݵ�IRQ */
#define AM_ZSN700_READER_COMMIEN_TIMER_IEN       0x01    /**< \brief ����TIMERIRQ��ʱ���ж����󴫵ݵ�IRQ */

/** @} */




/**
 * \name TxMode�Ĵ�������,���巢���������ʺ�֡��ʽ (0x12)
 * @{
 */
 
#define AM_ZSN700_READER_TXMODE_TXCRC_EN         0x80    /**< \brief ��1���ݷ���ʱʹ��CRCУ������(��106kbit������0) */
#define AM_ZSN700_READER_TXMODE_TXSPEED_MASK     0x70    /**< \brief ������������ */
#define AM_ZSN700_READER_TXMODE_TXSPEED_106KBIT  0x00    /**< \brief ��������106kbit */
#define AM_ZSN700_READER_TXMODE_TXSPEED_212KBIT  0x10    /**< \brief ��������212kbit */
#define AM_ZSN700_READER_TXMODE_TXSPEED_424KBIT  0x20    /**< \brief ��������424kbit */
#define AM_ZSN700_READER_TXMODE_TXSPEED_848KBIT  0x30    /**< \brief ��������848kbit */
#define AM_ZSN700_READER_TXMODE_INV_MOD          0x08    /**< \brief ��1,�������ݵĵ��Ʒ��� */

/** @} */


/**
 * \name RxMode�Ĵ�������,��������������ʺ�֡��ʽ (0x13)
 * @{
 */
 
#define AM_ZSN700_READER_RXMODE_RXCRC_EN         0x80    /**< \brief ��1���ݽ���ʱʹ��CRCУ������(��106kbit������0) */
#define AM_ZSN700_READER_RXMODE_RXSPEED_MASK     0x70    /**< \brief ������������ */
#define AM_ZSN700_READER_RXMODE_RXSPEED_106KBIT  0x00    /**< \brief ��������106kbit */
#define AM_ZSN700_READER_RXMODE_RXSPEED_212KBIT  0x10    /**< \brief ��������212kbit */
#define AM_ZSN700_READER_RXMODE_RXSPEED_424KBIT  0x20    /**< \brief ��������424kbit */
#define AM_ZSN700_READER_RXMODE_RXSPEED_848KBIT  0x30    /**< \brief ��������848kbit */
#define AM_ZSN700_READER_RXMODE_RXNOERR          0x08    /**< \brief ��1,������Ч������,���������ּ���.����14443B,����RxSOFReq��Ϊ1 */
#define AM_ZSN700_READER_RXMODE_RXMULTIPLE       0x04    /**< \brief ��0,���������յ�һ������֮֡���ٽ���.��1,������ն������֡ */

/** @} */


/**
 * \name TxControl�Ĵ�������,������������Tx1��Tx2���� (0x14)
 *
 * @{
 */
#define AM_ZSN700_READER_TXCONTROL_INV_TX2RF_ON  0x80    /**< \brief ��1,��TX2����ʹ��,������TX2������ź�ȡ�� */
#define AM_ZSN700_READER_TXCONTROL_INV_TX1RF_ON  0x40    /**< \brief ��1,��TX1����ʹ��,������TX2������ź�ȡ�� */
#define AM_ZSN700_READER_TXCONTROL_INV_TX2RF_OFF 0x20    /**< \brief ��1,��TX2�����ر�,������TX2������ź�ȡ�� */
#define AM_ZSN700_READER_TXCONTROL_INV_TX1RF_OFF 0x10    /**< \brief ��1,��TX1�����ر�,������TX2������ź�ȡ�� */
#define AM_ZSN700_READER_TXCONTROL_TX2_CW        0x08    /**< \brief ��1,TX2���������δ���Ƶ�13.56MHz�������ز�;��0,����� */
#define AM_ZSN700_READER_TXCONTROL_TX2RF_EN      0x02    /**< \brief ��1,TX2������ɷ������ݵ��Ƶ�13.56MHz�����ز� */
#define AM_ZSN700_READER_TXCONTROL_TX1RF_EN      0x01    /**< \brief ��1,TX1������ɷ������ݵ��Ƶ�13.56MHz�����ز� */

/** @} */

/**
 * \name RxThreshold�Ĵ�������,������������ֵѡ�� (0x18)
 * @{
 */

/** \brief �������ܽ��յ���С�ź�ǿ��(�������ˮƽ��������) */
#define AM_ZSN700_READER_RXTHRESHOLD_MINLEVEL   0xf0

/** \brief ���뵽������������˹�ر��������bit���ǿ��bit������ͻλ����С�ź�ǿ�� */
#define AM_ZSN700_READER_RXTHRESHOLD_COLLLEVEL  0x07

/** @} */


/**
 * \name RFCfg�Ĵ�������,���ý��������� (0x26)
 * @{
 */
 
#define AM_ZSN700_READER_RFCFG_RXGAIN_MASK       0x70    /**< \brief ��������ѹ����ָ������ */
#define AM_ZSN700_READER_RFCFG_RXGAIN_18DB       0x00    /**< \brief ��������ѹ����ָ��18dB */
#define AM_ZSN700_READER_RFCFG_RXGAIN_23DB       0x10    /**< \brief ��������ѹ����ָ��23dB */
#define AM_ZSN700_READER_RFCFG_RXGAIN_18DB_TOO   0x20    /**< \brief ��������ѹ����ָ��18dB */
#define AM_ZSN700_READER_RFCFG_RXGAIN_23DB_TOO   0x30    /**< \brief ��������ѹ����ָ��23dB */
#define AM_ZSN700_READER_RFCFG_RXGAIN_33DB       0x40    /**< \brief ��������ѹ����ָ��33dB */
#define AM_ZSN700_READER_RFCFG_RXGAIN_38DB       0x50    /**< \brief ��������ѹ����ָ��38dB */
#define AM_ZSN700_READER_RFCFG_RXGAIN_43DB       0x60    /**< \brief ��������ѹ����ָ��43dB */
#define AM_ZSN700_READER_RFCFG_RXGAIN_48DB       0x70    /**< \brief ��������ѹ����ָ��48dB */

/** @} */


/**
 * \name GsN�Ĵ�������,��������ʱ,ѡ��������������TX1��TX2��N�����ĵ絼 (0x27)
 * @{
 */

/**
 * \brief �޵���ʱ�����N�����ĵ絼,�������������,������������������:
 *        1.�絼ֵλ�����Ƽ�Ȩ
 *        2.soft Power-downģʽ�����λǿ����λ 
 *        3.�üĴ�����ֵֻ��TX1,TX2��������ʱʹ��
 */
#define AM_ZSN700_READER_CWGSN                   0xf0

/**
 * \brief ����ʱ�����N�����ĵ絼,�ɿ��Ƶ������:
 *        1.�絼ֵλ�����Ƽ�Ȩ
 *        2.soft Power-downģʽ�����λǿ����λ 
 *        3.�üĴ�����ֵֻ��TX1,TX2��������ʱʹ��
 */
#define AM_ZSN700_READER_MODGSN                  0x0f

/** @} */


/**
 * \name CWGsP�Ĵ�������,�������޵���ʱ��P�����ĵ絼 (0x28)
 * @{
 */

/**
 * \brief �޵���ʱ�����P�����ĵ絼,�������������,�������ļ���������:
 *        1.�絼ֵλ�����Ƽ�Ȩ
 *        2.soft Power-downģʽ�����λǿ����λ 
 */
#define AM_ZSN700_READER_CWGSP                   0x3f

/** @} */


/**
 * \name ModGsP�Ĵ������� (0x29)
 * @{
 */

/**
 * \brief ����ʱ�����P�����ĵ絼,�������������,�������ļ���������:
 *        1.�絼ֵλ�����Ƽ�Ȩ
 *        2.soft Power-downģʽ�����λǿ����λ 
 */
#define AM_ZSN700_READER_MODGSP                  0x3f

/** @} */


/**
 * @} am_if_zsn700_reg
 */

#ifdef __cplusplus
}
#endif
 
#endif /* __ZSN700_READER_REG_H */

/* end of file */

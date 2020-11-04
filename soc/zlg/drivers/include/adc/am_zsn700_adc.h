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
 * \brief ADC����������ADC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-18  yrz, first implementation
 * \endinternal
 */

#ifndef  __AM_ZSN700_ADC_H
#define  __AM_ZSN700_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_adc.h"

#include "hw/amhw_zsn700_adc.h"

/**
 * \addtogroup am_zsn700_if_adc
 * \copydoc am_zsn700_adc.h
 * @{
 */
/**
 * \brief ADC��Ӧͨ����GPIO��Ϣ
 */
typedef struct {
    amhw_zsn700_adc_chan_sel_t chan_sel;   /**< \brief ��Ӧ��ADCͨ����� */
    uint32_t gpio;                         /**< \brief ��Ӧ��GPIO�ܽź� */
    uint32_t func;                         /**< \brief ��Ӧ��GPIO�������� */
    uint32_t dfunc;                        /**< \brief ��Ӧ��GPIO����Ĭ������ */
} am_zsn700_adc_ioinfo_t;

/**
 * \brief ADC�豸��Ϣ
 */
typedef struct am_zsn700_adc_devinfo {

    /** \brief ADC�Ĵ�����Ļ���ַ */
    uint32_t   adc_reg_base;

    /** \brief ADC�жϺ� */
    int16_t    inum;

    /** \brief ʱ��ID */
    int        clk_num;

    /* �ο���ѹѡ�� */
    amhw_zsn700_adc_refvoltage_choice_t vref_choice;

    /**
     * \brief ADC�ο���ѹ����λ��mV
     *
     * �ο���ѹ Vref = (Vrefp - Vrefn)  Ϊ��������������ʱ
     * �ȶ�����ADC��ȷ����VREFP = VDDA Vrefn ����ֵΪ�� Vss �� Vssa ��
     *
     * \note �òο���ѹ�ɾ���ĵ�·����
     *
     */
    uint32_t   vref;

    /** \brief ADC�ڲ��¶ȴ���������ʹ��   1�������� 0���ر� */
    uint8_t    temp_enable;

    /** \brief ת������ */
    uint8_t    bits_mode;

    /** \brief ADC��Ӧͨ����������Ϣ  */
    am_zsn700_adc_ioinfo_t *p_ioinfo;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_zsn700_adc_devinfo_t;

/**
 * \brief ADC�豸ʵ��
 */
typedef struct am_zsn700_adc_dev {

    /** \brief ADC��׼���� */
    am_adc_serv_t                  adc_serve;

    /** \brief ָ��ADC�豸��Ϣ��ָ�� */
    const am_zsn700_adc_devinfo_t    *p_devinfo;

    /** \brief ����û�����ת����Ļص����� */
    am_adc_seq_cb_t                pfn_callback;

    /** \brief �û������ص������Ļص��������� */
    void                          *p_arg;

    /** \brief ��ǰת����ͨ�� */
    int                            chan;

    /** \brief ADCת������ģʽѡ��  */
    amhw_zsn700_adc_mode_t adc_mode;

    /** \brief ��ǰת�������������������׵�ַ */
    am_adc_buf_desc_t             *p_desc;

    /** \brief ��ǰת������������������ */
    uint32_t                       desc_num;

    /** \brief ת���Ĵ��� */
    uint32_t                       count;

    /** \brief ת����־ */
    uint32_t                       flags;

    /** \brief �Ե�ǰ�����������Ѿ������Ĵ��� */
    uint32_t                       conv_cnt;

    /** \brief ����ִ�е�ǰ���������������� */
    uint32_t                       desc_index;

    /** \brief ����������ת����ɵĴ��� */
    uint32_t                       seq_cnt;

    /** \brief ��������λ�� */
    uint16_t                       right_bit;

} am_zsn700_adc_dev_t;

/**
 * \brief ADC��ʼ��
 *
 * Ĭ�ϳ�ʼ������A
 *
 * \param[in] p_dev     : ָ��ADC�豸��ָ��
 * \param[in] p_devinfo : ָ��ADC�豸��Ϣ��ָ��
 *
 * \return ADC��׼���������� ���Ϊ NULL��������ʼ��ʧ��
 */
am_adc_handle_t am_zsn700_adc_init (am_zsn700_adc_dev_t           *p_dev,
                                    const am_zsn700_adc_devinfo_t *p_devinfo);

/**
 * \brief ADCȥ��ʼ��
 *
 * Ĭ��ȥ��ʼ������A
 *
 * \param[in] handle : am_zsn700_adc_init() ��ʼ��������õ�ADC������
 *
 * \return ��
 */
void am_zsn700_adc_deinit (am_adc_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_ADC_H */

/* end of file */

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
 * \brief  ZML165_ADC Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-9-15  lqy, first implementation.
 * \endinternal
 */

#ifndef __AM_ZML165_ADC_H
#define __AM_ZML165_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_zml165_adc
 * @copydoc am_zml165_adc.h
 * @{
 */

#include "ametal.h"
#include "am_adc.h"


/**
 * \name ZML165_ADC�ο���ѹѡ��
 * @{
 */
#define AM_ZML165_ADC_VOUT_ENABLE       0      /**< \brief ADC VOUTʹ�� */
#define AM_ZML165_ADC_VOUT_DISABLE      1      /**< \brief ADC VOUT����  */

/**
 * \name ZML165_ADCͨ��ѡ��
 * @{
 */

#define AM_ZML165_ADC_CHANNEL_A         0      /**< \brief ͨ�� A */
#define AM_ZML165_ADC_CHANNEL_B         1      /**< \brief ͨ�� B */
#define AM_ZML165_ADC_CHANNEL_TEMP      2      /**< \brief �¶� */
#define AM_ZML165_ADC_CHANNEL_SHORT     3      /**< \brief �ڶ� */

/** @} */

/**
 * \name ZML165_ADC PGAѡ��
 * @{
 */
#define AM_ZML165_ADC_PGA_1             0       /**< \brief ���汶�� 1*/
#define AM_ZML165_ADC_PGA_2             1       /**< \brief ���汶�� 2*/
#define AM_ZML165_ADC_PGA_64            2       /**< \brief ���汶�� 64*/
#define AM_ZML165_ADC_PGA_128           3       /**< \brief ���汶�� 128*/

/** @} */

/**
 * \name ZML165_ADC �������ѡ��
 * @{
 */
#define AM_ZML165_ADC_SPEED_10HZ        0       /**< \brief ADC�������10HZ */
#define AM_ZML165_ADC_SPEED_40HZ        1       /**< \brief ADC�������40HZ  */
#define AM_ZML165_ADC_SPEED_640HZ       2       /**< \brief ADC�������640HZ */
#define AM_ZML165_ADC_SPEED_1280HZ      3       /**< \brief ADC�������1280HZ*/

/** @} */


typedef struct am_zml165_adc_config{
    int8_t      pga;        /** \brief ������汶������,������Ĭ��ֵ������  -1 */
    int8_t      speed;      /** \brief �����������,������Ĭ��ֵ������  -1 */
    int8_t      channel;    /** \brief �������ͨ������,������Ĭ��ֵ������  -1 */
    int8_t      refo_off;   /** \brief REF��׼Դ״̬����,������Ĭ��ֵ������  -1 */
}am_zml165_adc_config_t;


/**
 * \brief ZML165_ADC �豸��Ϣ�ṹ��
 */
typedef struct am_zml165_adc_devinfo{

    /*\brief  ADC��ʼ������ */
    am_zml165_adc_config_t   config;

    /**
     * \brief ADC�ο���ѹ����λ��mV
     * \note �òο���ѹ�ɾ���ĵ�·����
     */
    uint32_t                 vref;

}am_zml165_adc_devinfo_t;

/** \brief �����ص����� */
typedef void (*am_zml165_adc_code_read_cb_t) (void *p_arg,uint32_t code);

/**
 * \brief ZML165_ADC �豸�ṹ��
 */
typedef struct am_zml165_adc_dev{

    /** \brief �Ŵ��� */
    uint8_t                        pga;
    /** \brief ������� */
    uint8_t                        out_speed;
    /** \brief ͨ�� */
    uint8_t                        ch;
    /** \brief REFʹ�� */
    uint8_t                        ref;
    /** \brief �Ƿ����ж�ģʽ */
    am_bool_t                      is_int;

    /** \brief INT���ŵĴ�����Ϣ���� */
    struct am_zml165_adc_trigger_info {

        /** \brief �����ص����� */
        am_zml165_adc_code_read_cb_t   pfn_callback;
        /** \brief �ص������Ĳ��� */
        void                      *p_arg;

    } triginfo;/**< \brief INT���ŵĴ�����Ϣ */

    /** \brief �豸��Ϣ */
    const am_zml165_adc_devinfo_t *p_devinfo;

    /** \brief ADC��׼���� */
    am_adc_serv_t                  adc_serve;

    /** \brief ����û�����ת����Ļص����� */
    am_adc_seq_cb_t                pfn_callback;

    /** \brief �û������ص������Ļص��������� */
    void                          *p_arg;

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

}am_zml165_adc_dev_t;

typedef am_zml165_adc_dev_t * am_zml165_adc_handle_t; /**< \brief ������� */

/** @} */

/**
 * \brief ZML165_ADC �豸��ʼ��
 *
 * \param[in] p_dev      :ָ��ZML165_ADC�豸�ṹ���ָ��
 * \param[in] p_devinfo  :ָ��ZML165_ADC�豸��Ϣ�ṹ���ָ��
 *
 * \return ZML165_ADC����������,���Ϊ NULL��������ʼ��ʧ��
 */
am_zml165_adc_handle_t am_zml165_adc_init(am_zml165_adc_dev_t            *p_dev,
                                          const am_zml165_adc_devinfo_t  *p_devinfo);

/**
 * \brief ZML165_ADC �豸���ʼ��
 *
 * \param[in] handle : ZML165_ADC�������
 *
 * \return ��
 */
void am_zml165_adc_deinit (am_zml165_adc_handle_t handle);

/**
 * \brief ZML165_ADC ���üĴ�����ȡ
 *
 * \param[in] p_dev : ZML165_ADC�������
 *
 * \return adc���üĴ���ֵ
 */
uint8_t am_zml165_adc_config_reg_read(am_zml165_adc_dev_t  *p_dev);

/**
 * \brief ZML165 ADC д������
 *
 * \param[in] p_dev : ZML165_ADC�������
 * \param[in] speed : p_config ָ�����ýṹ���ָ��
 *
 * \retval  AM_OK     : ���óɹ�
 *          AM_ERROR  : ����ʧ�ܣ�ADCδ׼����
 */
uint8_t am_zml165_adc_config_load(am_zml165_adc_dev_t     *p_dev,
                                  am_zml165_adc_config_t  *p_config);


/**
 * \brief ZML165_ADC pga�Ŵ�����ȡ
 *
 * \param[in] p_dev : ZML165_ADC�������
 *
 * \return pga�Ŵ���
 */
uint32_t am_zml165_adc_pga_get(am_zml165_adc_dev_t  *p_dev);

/**
 * \brief ZML165 ADC ͨ���Ż�ȡ
 *
 * \param[in] p_dev : ZML165_ADC�������
 *
 * \return chͨ����
 */
uint8_t am_zml165_adc_ch_get(am_zml165_adc_dev_t  *p_dev);

/**
 * \brief ZML165_ADC adc������ʶ�
 *
 * \param[in] p_dev : ZML165_ADC�������
 *
 * \return adc�������
 */
uint32_t am_zml165_adc_out_speed_get(am_zml165_adc_dev_t  *p_dev);

/**
 * \brief ZML165_ADC �����
 *
 * \param[in] p_dev   : ZML165_ADC�������
 *
 * \retval  AM_OK     : �����ɹ�
 */
int am_zml165_adc_read_int_enable(am_zml165_adc_dev_t  *p_dev);

/**
 * \brief ZML165_ADC ��ֹ��
 *
 * \param[in] p_dev   : ZML165_ADC�������
 *
 * \retval  AM_OK     : �����ɹ�
 */
int am_zml165_adc_read_int_disable(am_zml165_adc_dev_t  *p_dev);

/**
 * \brief ZML165_ADC ��ѭ��adc�ɼ�ֵ
 *
 * \param[in]  p_dev   : ZML165_ADC�������
 * \param[out] val     : ��������
 *
 * \retval  AM_OK �ɼ��ɹ�
 */
int am_zml165_adc_read_polling(am_zml165_adc_dev_t *p_dev, uint32_t *val);

/**
 * \brief ZML165_ADC ����͹���ģʽ
 *
 * \param[in] p_dev   : ZML165_ADC�������
 *
 * \retval  ��
 */
void am_zml165_adc_power_down_enter(am_zml165_adc_dev_t  *p_dev);

/**
 * \brief ZML165_ADC �˳��͹���ģʽ
 *
 * \param[in] p_dev   : ZML165_ADC�������
 *
 * \retval  ��
 */
void am_zml165_adc_power_down_out(am_zml165_adc_dev_t  *p_dev);

/**
 * \brief ZML165_ADC �����жϻص�����
 *
 * \param[in] p_dev   : ZML165_ADC�������
 * \param[in] p_fun   : ZML165_ADC�жϻص�����
 * \param[in] p_arg   : ZML165_ADC�жϻص���������
 *
 * \retval  ��
 */
void am_zml165_adc_int_connect(am_zml165_adc_dev_t      *p_dev ,
                               am_zml165_adc_code_read_cb_t  p_fun,
                               void                     *p_arg);

/**
 * \brief ZML165_ADC ɾ���жϻص�����
 *
 * \param[in] p_dev   : ZML165_ADC�������
 * \param[in] p_fun   : ZML165_ADC�жϻص�����
 * \param[in] p_arg   : ZML165_ADC�жϻص���������
 *
 * \retval  ��
 */
void am_zml165_adc_int_disconnect(am_zml165_adc_dev_t      *p_dev ,
                                  am_zml165_adc_code_read_cb_t  p_fun,
                                  void                         *p_arg);

/**
 * \brief ZML165_ADC ��ñ�׼adc���
 * \param[in] p_dev : ZML165_ADC�������
 *
 * \retval ��׼adc�������
 */
am_adc_handle_t am_zml165_adc_standard_adc_handle_get(am_zml165_adc_dev_t *p_dev);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SPI_H */

/*end of file */



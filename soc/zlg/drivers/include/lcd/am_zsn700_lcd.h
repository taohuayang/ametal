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
 * \brief LCD����������LCD��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-13
 * \endinternal
 */
#ifndef __AM_ZSN700_LCD_H
#define __AM_ZSN700_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

#define AM_ZSN700_LCD_MODE_0    0  /**< \brief LCD ģʽ0 */
#define AM_ZSN700_LCD_MODE_1    1  /**< \brief LCD ģʽ1 */

/**
 * \addtogroup am_zsn700_if_lcd
 * \copydoc am_zsn700_lcd.h
 * @{
 */

/**
 * \brief LCD COM-SEG�˿ڳ�ʼ��������Ϣ�ṹ��
 *
 * \note : �û���ʹ��LCD��ʱ����Ҫ�Լ�����һ���ṹ�岢���
 *         ���û��ڿ��ƶ˿�ʱ1��ʾ��0��ʾ�رգ�
 */
typedef struct am_zsn700_lcd_com_seg {
    uint32_t seg0_31;          /**< \brief seg0-31�˿� */
    uint8_t  seg32_35;         /**< \brief seg32-35�˿� */
    uint8_t  seg36com7_39com4; /**< \brief seg36-3 com4-7�ܽŹ���ѡ����CR0.DUTY����*/
    uint16_t seg40_51;         /**< \brief seg40-51�˿� */
    uint8_t  mux;              /**< \brief SEG32~SEG35�˿ڹ���ѡ�� */
    uint8_t  com0_3;           /**< \brief COM0-3�˿ڹ���ѡ�� */
}am_zsn700_lcd_com_seg_t;

/**
 * \brief LCD�豸��Ϣ�ṹ��
 */
typedef struct am_zsn700_lcd_info {

    uint32_t    reg_base;  /**< \brief LCD�Ĵ��������ַ */

    uint8_t     inum;      /**< \brief LCD�жϱ�� */

    uint8_t     bias_src;  /**< \brief LCDƫ��Դ */

    uint8_t     duty;      /**< \brief LCDռ�ձ� */

    uint8_t     bias;      /**< \brief LCDƫ�õ�ѹ */

    uint8_t     cpclk;     /**< \brief LCD��ѹ��ʱ��Ƶ��*/

    uint8_t     scanclk;   /**< \brief LCDɨ��Ƶ��*/

    uint8_t     clk_src;   /**< \brief LCDʱ��Դ*/

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

}am_zsn700_lcd_devinfo_t;

/**
 * \brief LCD�豸ʵ��
 */
typedef struct am_zsn700_lcd_dev {

    /** \brief ָ��LCD�豸��Ϣ��ָ�� */
    const am_zsn700_lcd_devinfo_t *p_devinfo;

    /** \brief �жϴ����ص� ����*/
    void (*pfn_trigger_cb)(void *);

    /** \brief �û��ص����� */
    void *p_arg;

    /** \brief LCD��ʾģʽ */
    uint8_t mode;

} am_zsn700_lcd_dev_t;

/** \brief LCD��׼�������������Ͷ��� */
typedef am_zsn700_lcd_dev_t *am_lcd_handle_t;

/**
 * \brief LCD ��ʼ��
 *
 * \param[in] p_dev     : LCD �豸ʵ��
 * \param[in] p_devinfo : LCD �豸��Ϣʵ��
 *
 * \retval : ��׼LCD������
 *
 */
am_lcd_handle_t  am_zsn700_lcd_init (am_zsn700_lcd_dev_t           *p_dev,
                                     const am_zsn700_lcd_devinfo_t *p_devinfo);

/**
 * \brief LCD ȥ��ʼ��
 *
 * \param[in] handle : ��׼LCD������
 *
 * \retval : ��
 *
 */
void am_zsn700_lcd_deinit (am_lcd_handle_t handle);


/**
 * \brief LCD ����
 *
 * \param[in] handle: ��׼LCD������
 *
 * \retval AM_OK    : �����ɹ�
 *         AM_ERROR : ����ʧ��
 *
 */
int am_zsn700_lcd_disp_clr (am_lcd_handle_t handle);

/**
 * \brief LCD ��������
 *
 * \param[in] handle: ��׼LCD������
 * \param[in] addr  : �Դ��ַ����
 * \param[in] data  : д�뵽�Դ������
 *
 * \retval AM_OK    : �����ɹ�
 *         AM_ERROR : ����ʧ��
 *
 */
int am_zsn700_lcd_disp_write (am_lcd_handle_t handle,
                              uint32_t addr,
                              uint32_t data);

/**
 * \brief LCD DMAģʽ���� ���жϴ�����
 *
 * \param[in] handle   : ��׼LCD������
 * \param[in] p_lcd_cb : �û��ص�����
 * \param[in] p_arg    : �û��ص�����
 *
 * \retval AM_OK    : �ɹ�
 *         AM_ERROR : ʧ��
 *
 */
int am_zsn700_lcd_dma_int_set (am_lcd_handle_t handle,
                               void (*p_lcd_cb) (void *),
                               void *p_arg);

/**
 * \brief LCD ʹ��
 *
 * \param[in] handle   : ��׼LCD������
 * \param[in] lcd_mode : LCD��ʾģʽ
 *
 * \retval AM_OK    : �ɹ�
 *         AM_ERROR : ʧ��
 *
 */
int am_zsn700_lcd_enable (am_lcd_handle_t handle, uint8_t lcd_mode);

/**
 * \brief LCD COM SEG �˿�����
 *
 * \param[in] handle : ��׼LCD������
 * \param[in] p_port : LCD COM-SEG�˿����ýṹ��ָ��
 *
 * \retval AM_OK    : �ɹ�
 *         AM_ERROR : ʧ��
 *
 */
int am_zsn700_lcd_com_seg_init (am_lcd_handle_t         handle,
                                am_zsn700_lcd_com_seg_t *p_port);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSN700_LCD_H */

/* end of file */

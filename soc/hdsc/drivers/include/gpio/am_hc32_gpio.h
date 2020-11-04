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
 * \brief GPIO����������GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.01 20-04-26 zcb, Fix the problem that only one pin can be
 *                      configured as external interrupt
 * - 1.00 19-09-06  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32_GPIO_H
#define __AM_HC32_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "hw/amhw_hc32_gpio.h"
#include "am_hc32_gpio_util.h"

/**
 * \addtogroup am_hc32_if_gpio
 * \copydoc am_hc32_gpio.h
 * @{
 */

/**
 * \brief ���ŵĴ�����Ϣ
 */
struct am_hc32_gpio_trigger_info {

    /** \brief �����ص����� */
    am_pfnvoid_t                        pfn_callback;

    /** \brief �ص������Ĳ��� */
    void                               *p_arg;
};

/**
 * \brief GPIO �豸��Ϣ
 */
typedef struct am_hc32_gpio_devinfo {

    /** \brief GPIO�Ĵ������ַ */
    uint32_t                            gpio_regbase;

    /** \brief �����жϺ��б� */
    const int8_t                        inum_pin[4];

    /** \brief ֧���ⲿ�жϵ� GPIO ������ű�� */
    const uint8_t                       exti_num_max;

    /** \brief ������ʽ */
    uint8_t                            *p_trigger;

    /** \brief ָ�����Ŵ�����Ϣ��ָ�� */
    struct am_hc32_gpio_trigger_info   *p_triginfo;

    /** \brief ƽ̨��ʼ������ */
    void                              (*pfn_plfm_init) (void);

    /** \brief ƽ̨ȥ��ʼ������ */
    void                              (*pfn_plfm_deinit) (void);

} am_hc32_gpio_devinfo_t;

/**
 * \brief GPIO�豸ʵ��
 */
typedef struct am_hc32_gpio_dev {

    /** \brief ָ��GPIO�豸��Ϣ��ָ�� */
    const am_hc32_gpio_devinfo_t       *p_devinfo;

    /** \brief ������Ч��־ */
    am_bool_t                           valid_flg;

} am_hc32_gpio_dev_t;

/**
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_hc32_gpio_init (am_hc32_gpio_dev_t           *p_dev,
                       const am_hc32_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIO���ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void am_hc32_gpio_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32_GPIO_H */

/* end of file */

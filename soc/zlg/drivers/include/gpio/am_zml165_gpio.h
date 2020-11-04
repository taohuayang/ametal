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
 * - 1.00 17-04-07  ari,first implementation
 * \endinternal
 */

#ifndef __AM_ZML165_GPIO_H
#define __AM_ZML165_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "hw/amhw_zlg_gpio.h"
#include "hw/amhw_zlg_syscfg.h"
#include "hw/amhw_zlg_exti.h"
#include "am_zml165_gpio_util.h"

/**
 * \addtogroup am_zml165_if_gpio
 * \copydoc am_zml165_gpio.h
 * @{
 */

/**
 * \brief ���ŵĴ�����Ϣ
 */
struct am_zml165_gpio_trigger_info {

    /** \brief �����ص����� */
    am_pfnvoid_t pfn_callback;

    /** \brief �ص������Ĳ��� */
    void        *p_arg;
};

/**
 * \brief GPIO �豸��Ϣ
 */
typedef struct am_zml165_gpio_devinfo {

    /** \brief GPIO�Ĵ������ַ */
    uint32_t     gpio_regbase;

    /** \brief ϵͳ����SYSCFG�Ĵ������ַ */
    uint32_t     syscfg_regbase;

    /** \brief �ⲿ�¼�EXTI���ƼĴ������ַ */
    uint32_t     exti_regbase;

    /** \brief GPIO�����жϺ��б� */
    const int8_t inum_pin[3];

    /** \brief GPIO֧�ֵ������жϺ����� */
    size_t       pint_count;

    /** \brief ������Ϣӳ�� */
    uint8_t     *p_infomap;

    /** \brief ָ�����Ŵ�����Ϣ��ָ�� */
    struct am_zml165_gpio_trigger_info *p_triginfo;

    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������ */

} am_zml165_gpio_devinfo_t;

/**
 * \brief GPIO�豸ʵ��
 */
typedef struct am_zml165_gpio_dev {

    /** \brief ָ��GPIO�豸��Ϣ��ָ�� */
    const am_zml165_gpio_devinfo_t *p_devinfo;

    /** \brief ������Ч��־ */
    am_bool_t                       valid_flg;

} am_zml165_gpio_dev_t;

/**
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zml165_gpio_init (am_zml165_gpio_dev_t           *p_dev,
                         const am_zml165_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIOȥ��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void am_zml165_gpio_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZML165_GPIO_H */

/* end of file */

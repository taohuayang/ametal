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
 * \brief SWDT������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-12
 * \endinternal
 */

#ifndef __AM_HC32F460_SWDT_H
#define __AM_HC32F460_SWDT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_wdt.h"
#include "hw/amhw_hc32f460_swdt.h"

/**
 * \addtogroup am_hc32f460_if_swdt
 * \copydoc am_hc32f460_swdt.h
 * @{
 */

/**
 * \name swdt״̬��־
 * \anchor am_hc32f460_swdt_statud_flags
 * @{
 */
#define AM_HC32F460_SWDT_STATUS_REFRESH_ERROR        (0)  /** \brief ˢ�´����־*/
#define AM_HC32F460_SWDT_STATUS_COUNT_UNDERFLOW      (1)  /** \brief ���������־ */

typedef enum {
    AM_HC32F460_SWDT_TRIGGER_EVENT_REQUEST_INT   = 0,
    AM_HC32F460_SWDT_TRIGGER_EVENT_REQUEST_RESET = 1,
}am_hc32f460_swdt_trigger_event_type_t;


/** \brief SWDT�жϻص��������� */
typedef void (*am_hc32f460_pfn_swdt_isr_t)(void *p_arg, uint32_t flag);



/**
 * \brief SWDT�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f460_swdt_devinfo {

    /** \brief SWDT�Ĵ��������ַ */
    uint32_t  swdt_regbase;

    /** \brief ʱ��ID */
    int       clk_num;

    /** \brief �жϺ� */
    int       inum;

    /** \brief �����¼����ͣ��ж�/��λ�� */
    uint16_t  event_type;

    /** \brief ƽ̨��ʼ������ */
    void    (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void    (*pfn_plfm_deinit)(void);

} am_hc32f460_swdt_devinfo_t;



/**
 * \brief WDT�豸�ṹ��
 */
typedef struct am_hc32f460_swdt_dev {

    /** \brief SWDT�ṩ�ı�׼���� */
    am_wdt_serv_t                   swdt_serv;

    /** \brief swdt�����ص����� */
    void (*pfn_isr)(void *p_arg, uint32_t flag);

    /** \brief �ص������ĵ�һ����ڲ��� */
    void                    *p_arg;

    /** \brief ָ��WDT�豸����Ϣָ�� */
    const am_hc32f460_swdt_devinfo_t  *p_devinfo;
} am_hc32f460_swdt_dev_t;

/**
 * \brief ����SWDT�жϷ�����
 *
 * \param[in] p_dev     : ָ��SWDT�豸
 * \param[in] p_devinfo : ָ������SWDT�жϷ�����
 * \param[in] p_arg     : �ص���������
 *
 * \return �ɹ��򷵻�AM_OK��������Ϊʧ��
 */
int am_hc32f460_swdt_isr_connect (am_hc32f460_swdt_dev_t     *p_dev,
                                  am_hc32f460_pfn_swdt_isr_t  pfn_isr,
                                  void                       *p_arg);

/**
 * \brief ɾ��SWDT�жϷ�����
 *
 * \param[in] p_dev     : ָ��SWDT�豸
 * \param[in] p_devinfo : ָ������SWDT�жϷ�����
 * \param[in] p_arg     : �ص���������
 *
 * \return �ɹ��򷵻�AM_OK��������Ϊʧ��
 */
int am_hc32f460_swdt_isr_disconnect (am_hc32f460_swdt_dev_t    *p_dev,
                                     am_hc32f460_pfn_swdt_isr_t pfn_isr,
                                     void                      *p_arg);


/**
 * \brief SWDT��ʼ��
 *
 * \param[in] p_dev     : ָ��SWDT�豸
 * \param[in] p_devinfo : ָ��SWDT�豸��Ϣ
 *
 * \return WDT��׼��������ʧ���򷵻�NULL
 */
am_wdt_handle_t am_hc32f460_swdt_init (am_hc32f460_swdt_dev_t            *p_dev,
                                       const am_hc32f460_swdt_devinfo_t  *p_devinfo);

/**
 * \brief ���SWDT�豸��ʼ��
 *
 * \param[in] handle : ʹ��WDT��ʼ������am_hc32f460_swdt_init()��ȡ����handle
 *
 * \return ��
 */
void am_hc32f460_swdt_deinit (am_wdt_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __AM_HC32F460_SWDT_H */

#endif

/* end of file */


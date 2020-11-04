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
 * \brief WDT������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-12
 * \endinternal
 */

#ifndef __AM_HC32F460_WDT_H
#define __AM_HC32F460_WDT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_wdt.h"
#include "hw/amhw_hc32f460_wdt.h"

/**
 * \addtogroup am_hc32f460_if_wdt
 * \copydoc am_hc32f460_wdt.h
 * @{
 */
/**
 * \name wdt״̬��־
 * \anchor am_hc32f460_wdt_status_flags
 * @{
 */
#define AM_HC32F460_WDT_STATUS_REFRESH_ERROR        (0)  /** \brief ˢ�´����־*/
#define AM_HC32F460_WDT_STATUS_COUNT_UNDERFLOW      (1)  /** \brief ���������־ */




/** \brief WDT�жϻص��������� */
typedef void (*am_hc32f460_pfn_wdt_isr_t)(void *p_arg, uint32_t flag);

typedef enum {
    AM_HC32F460_WDT_TRIGGER_EVENT_REQUEST_INT   = 0,
    AM_HC32F460_WDT_TRIGGER_EVENT_REQUEST_RESET = 1,
}am_hc32f460_wdt_trigger_event_type_t;

typedef enum {
    AM_HC32F460_WDT_SLEEPOFF   = 0,
    AM_HC32F460_WDT_SLEEPON    = 1,
}am_hc32f460_wdt_sleepoff_t;

typedef enum {
    AM_HC32F460_WDT_REFRESH_RANGE_100              = 0,  /* 100% */
    AM_HC32F460_WDT_REFRESH_RANGE_0_25             = 1,  /* 0%~25% */
    AM_HC32F460_WDT_REFRESH_RANGE_25_50            = 2,  /* 25%~50% */
    AM_HC32F460_WDT_REFRESH_RANGE_0_50             = 3,  /* 0%~50% */
    AM_HC32F460_WDT_REFRESH_RANGE_50_75            = 4,  /* 50%~75% */
    AM_HC32F460_WDT_REFRESH_RANGE_0_25_AND_50_75   = 5,  /* 0%~25% & 50%~75% */
    AM_HC32F460_WDT_REFRESH_RANGE_25_75            = 6,  /* 25%~75% */
    AM_HC32F460_WDT_REFRESH_RANGE_0_75             = 7,  /* 0%~75% */
    AM_HC32F460_WDT_REFRESH_RANGE_75_100           = 8,  /* 75%~100% */
    AM_HC32F460_WDT_REFRESH_RANGE_0_25_AND_75_100  = 9,  /* 0%~25% & 75%~100% */
    AM_HC32F460_WDT_REFRESH_RANGE_25_50_AND_75_100 = 10, /* 25%~50% & 75%~100% */
    AM_HC32F460_WDT_REFRESH_RANGE_0_50_AND_75_100  = 11, /* 0%~50% & 75%~100% */
    AM_HC32F460_WDT_REFRESH_RANGE_50_100           = 12, /* 50%~100% */
    AM_HC32F460_WDT_REFRESH_RANGE_0_25_AND_50_100  = 13, /* 0%~25% & 50%~100% */
    AM_HC32F460_WDT_REFRESH_RANGE_25_100           = 14, /* 25%~100% */
    AM_HC32F460_WDT_REFRESH_RANGE_0_100            = 15, /* 0%~100% */
}am_hc32f460_wdt_refresh_region_t;



/**
 * \brief WDT�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f460_wdt_devinfo {

    /** \brief WDT�Ĵ��������ַ */
    uint32_t  wdt_regbase;

    /** \brief ʱ��ID */
    int       clk_num;

    /** \brief �жϺ� */
    int       inum;

    /** \brief ˢ�´���/�����������¼����ͣ��ж�/��λ�� */
    am_hc32f460_wdt_trigger_event_type_t   EVENT_TYPE;

    /** \brief WDT��sleepģʽ�¼�����ֹ/��� */
    am_hc32f460_wdt_sleepoff_t             SLPOFF;

    /** \brief ˢ���������� */
    am_hc32f460_wdt_refresh_region_t       REFRESH_REGION;

    /** \brief ƽ̨��ʼ������ */
    void    (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void    (*pfn_plfm_deinit)(void);

} am_hc32f460_wdt_devinfo_t;



/**
 * \brief WDT�豸�ṹ��
 */
typedef struct am_hc32f460_wdt_dev {

    /** \brief WDT�ṩ�ı�׼���� */
    am_wdt_serv_t                   wdt_serv;

    /** \brief Ԥ��Ƶ���� */
    uint16_t                          div;

    /** \brief ˢ�´���/������������¼����ͣ��ж�/��λ��  */
    uint16_t                          trigger_type;

    /** \brief sleepģʽ���Ƿ�ʹ�ܼ���  */
    am_bool_t                         sleep_count;

    /** \brief wdt�����ص����� */
    void (*pfn_isr)(void *p_arg, uint32_t flag);

    /** \brief �ص������ĵ�һ����ڲ��� */
    void                    *p_arg;

    /** \brief ָ��WDT�豸����Ϣָ�� */
    const am_hc32f460_wdt_devinfo_t  *p_devinfo;
} am_hc32f460_wdt_dev_t;


/**
 * \brief ����WDT�жϷ�����
 *
 * \param[in] p_dev     : ָ��WDT�豸
 * \param[in] p_devinfo : ָ������WDT�жϷ�����
 * \param[in] p_arg     : �ص���������
 *
 * \return �ɹ��򷵻�AM_OK��������Ϊʧ��
 */
int am_hc32f460_wdt_isr_connect (am_hc32f460_wdt_dev_t     *p_dev,
                                 am_hc32f460_pfn_wdt_isr_t  pfn_isr,
                                 void                      *p_arg);

/**
 * \brief ɾ��WDT�жϷ�����
 *
 * \param[in] p_dev     : ָ��WDT�豸
 * \param[in] p_devinfo : ָ������WDT�жϷ�����
 * \param[in] p_arg     : �ص���������
 *
 * \return �ɹ��򷵻�AM_OK��������Ϊʧ��
 */
int am_hc32f460_wdt_isr_disconnect (am_hc32f460_wdt_dev_t     *p_dev,
                                    am_hc32f460_pfn_wdt_isr_t  pfn_isr,
                                    void                      *p_arg);

/**
 * \brief WDT��ʼ��
 *
 * \param[in] p_dev     : ָ��WDT�豸
 * \param[in] p_devinfo : ָ��WDT�豸��Ϣ
 *
 * \return WDT��׼��������ʧ���򷵻�NULL
 */
am_wdt_handle_t am_hc32f460_wdt_init (am_hc32f460_wdt_dev_t            *p_dev,
                                      const am_hc32f460_wdt_devinfo_t  *p_devinfo);

/**
 * \brief ���WDT�豸��ʼ��
 *
 * \param[in] handle : ʹ��WDT��ʼ������am_hc32f460_wdt_init()��ȡ����handle
 *
 * \return ��
 */
void am_hc32f460_wdt_deinit (am_wdt_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __AM_HC32F460_WDT_H */

#endif

/* end of file */


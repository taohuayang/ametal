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
 * \internal
 * \par Modification history
 * - 1.00 20-05-13
 * \endinternal
 */

#include "ametal.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_hc32f460_swdt.h"
#include "hc32f460_intctrl.h"
#include "hc32f460_inum.h"
#include "hc32f460_irq_handle.h"
#include "hc32f460_icg.h"

/****************************************************************************
 * Functions Declaration
 ***************************************************************************/

static int __wdt_feed (void     *p_drv);
static int __swdt_info_get (void *p_drv, am_wdt_info_t *p_info);

/** \brief ���Ź���׼�������ṹ�� */
static const struct am_wdt_drv_funcs __g_swdt_drv_funcs = {
    __swdt_info_get,
    NULL,
    __wdt_feed
};

#define AMHW_HC32F460_SWDT_COUNTER_MAX_CLK_DIV  (2048ULL)  /**< \brief ���Ź�����ʱ������Ƶ */
#define AMHW_HC32F460_SWDT_COUNTER_MIN_CLK_DIV  (1UL)      /**< \brief ���Ź�����ʱ����С��Ƶ */
#define AMHW_HC32F460_SWDT_COUNTER_MAX_PERIOD   (65536ULL) /**< \brief ���Ź����������� */
#define AMHW_HC32F460_SWDT_COUNTER_MIN_PERIOD   (256UL)    /**< \brief ���Ź���С�������� */

/** \brief ��ȡ���Ź���Ϣ */
static int __swdt_info_get (void *p_drv, am_wdt_info_t *p_info)
{
    am_hc32f460_swdt_dev_t *p_dev     = (am_hc32f460_swdt_dev_t *)p_drv;

    uint32_t clkrate = am_clk_rate_get(p_dev->p_devinfo->clk_num);

    p_info->min_timeout_ms = AMHW_HC32F460_SWDT_COUNTER_MIN_PERIOD *
                             (AMHW_HC32F460_SWDT_COUNTER_MIN_CLK_DIV / (float)clkrate) * 1000;
    p_info->max_timeout_ms = AMHW_HC32F460_SWDT_COUNTER_MAX_PERIOD *
                             (AMHW_HC32F460_SWDT_COUNTER_MAX_CLK_DIV / (float)clkrate) * 1000;

    return AM_OK;
}

/** \brief ι������ */
static int __wdt_feed (void *p_drv)
{
    am_hc32f460_swdt_dev_t *p_dev     = (am_hc32f460_swdt_dev_t *)p_drv;
    amhw_hc32f460_swdt_t   *p_hw_wdt =
                           (amhw_hc32f460_swdt_t *)p_dev->p_devinfo->swdt_regbase;

    /* ˢ�¼���ֵ */
    amhw_hc32f460_swdt_refresh_set(p_hw_wdt, AMHW_HC32F460_SWDT_REFRESH_START);
    amhw_hc32f460_swdt_refresh_set(p_hw_wdt, AMHW_HC32F460_SWDT_REFRESH_END);

    return AM_OK;
}

void hc32f460_swdt_irq_handler(void *p_arg)
{
    uint32_t flag = 0;

    am_hc32f460_swdt_dev_t *p_dev = (am_hc32f460_swdt_dev_t *)p_arg;

    amhw_hc32f460_swdt_t *p_hw_swdt =
        (amhw_hc32f460_swdt_t *) p_dev->p_devinfo->swdt_regbase;

    if (amhw_hc32f460_swdt_status_get(p_hw_swdt, AMHW_HC32F460_SWDT_STATUS_REF)) {
        flag = AM_HC32F460_SWDT_STATUS_REFRESH_ERROR;
        amhw_hc32f460_swdt_status_clr(p_hw_swdt, AMHW_HC32F460_SWDT_STATUS_REF);
    } else if (amhw_hc32f460_swdt_status_get(p_hw_swdt, AMHW_HC32F460_SWDT_STATUS_UDF)) {
        flag = AM_HC32F460_SWDT_STATUS_COUNT_UNDERFLOW;
        amhw_hc32f460_swdt_status_clr(p_hw_swdt, AMHW_HC32F460_SWDT_STATUS_UDF);
    }

    if (p_dev->pfn_isr) {
        p_dev->pfn_isr(p_arg , flag);
    }
}


/* ����SWDT�жϷ����� */
int am_hc32f460_swdt_isr_connect (am_hc32f460_swdt_dev_t     *p_dev,
                                  am_hc32f460_pfn_swdt_isr_t  pfn_isr,
                                  void                       *p_arg)
{
    if (p_dev-> pfn_isr == NULL) {
        p_dev-> pfn_isr = pfn_isr;
        p_dev-> p_arg   = p_arg;
    } else {
        return -AM_EPERM;
    }

    return AM_OK;
}

/* ɾ��WDT�жϷ��������� */
int am_hc32f460_swdt_isr_disconnect (am_hc32f460_swdt_dev_t    *p_dev,
                                     am_hc32f460_pfn_swdt_isr_t pfn_isr,
                                     void                     *p_arg)
{
    if (p_dev-> pfn_isr != NULL) {
        p_dev-> pfn_isr = NULL;
        p_dev-> p_arg   = NULL;
    } else {
        return -AM_EPERM;
    }

    return AM_OK;
}



#define  AMHW_HC32F460_SWDT_INT_VSSEL_BITS_MASK  (1 << 23)
/** \brief ��ʼ��WDT�豸ָ�� */
am_wdt_handle_t
am_hc32f460_swdt_init (am_hc32f460_swdt_dev_t           *p_dev,
                       const am_hc32f460_swdt_devinfo_t *p_devinfo)
{
    if (p_devinfo == NULL) {
        return NULL;
    }

    p_dev->p_devinfo = p_devinfo;
    p_dev->swdt_serv.p_funcs = (struct am_wdt_drv_funcs *)&__g_swdt_drv_funcs;
    p_dev->swdt_serv.p_drv   = p_dev;

    if (p_devinfo->event_type == HC32F460_ICG_SWDT_INTERRUPT_REQUEST) {
        /* ʹ�ܹ����ж�SWDT���λ */
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_SWDT_INT_VSSEL_BITS_MASK);

        am_int_connect(p_devinfo->inum, IRQ130_Handler, (void *)0);
    }


    /* SWDTƽ̨��ʼ�� */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    return &(p_dev->swdt_serv);
}

/** \brief SWDT���ʼ�� */
void am_hc32f460_swdt_deinit (am_wdt_handle_t handle)
{
    am_hc32f460_swdt_dev_t *p_dev = (am_hc32f460_swdt_dev_t *)handle;
    am_hc32f460_swdt_devinfo_t *p_devinfo = NULL;

    if (NULL == p_dev) {
        return ;
    }

    p_dev->p_devinfo        = NULL;
    p_dev->swdt_serv.p_funcs = NULL;
    p_dev->swdt_serv.p_drv   = NULL;
    p_devinfo = (am_hc32f460_swdt_devinfo_t *)p_dev->p_devinfo;

    if (p_devinfo->event_type == HC32F460_ICG_SWDT_INTERRUPT_REQUEST) {
        /* ���ܹ����ж�DMA���λ */
        amhw_hc32f460_intc_int_vssel_bits_clr(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_SWDT_INT_VSSEL_BITS_MASK);

        am_int_disconnect(p_devinfo->inum, IRQ130_Handler, (void *)0);

        /* �����жϺ���ص������ж�Դ�Ĺ����ж϶������ܣ��ر��ж� */
        if (amhw_hc32f460_intc_int_vssel_get(p_devinfo->inum) == 0) {
            am_int_disable(p_devinfo->inum);
        }
    }

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */

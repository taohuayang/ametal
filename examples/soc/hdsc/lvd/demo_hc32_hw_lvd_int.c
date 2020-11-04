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
 * \brief LVD �ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PIOB_7�����ѹ�Ӹ��ڻ�׼��ѹ��Ϊ���ڻ�׼��ѹ�������LVD�жϡ�
 *   ���ڴ�ӡ "LVD interrupt"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_hc32_hw_lvd_int.c src_hc32_hw_lvd_int
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-09  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_hw_lvd_int
 * \copydoc demo_hc32_hw_lvd_int.c
 */

/** [src_hc32_hw_lvd_int] */

#include "ametal.h"
#include "am_hc32.h"
#include "am_int.h"
#include "am_board.h"
#include "am_hc32_lvd.h"
#include "hw/amhw_hc32_lvd.h"
#include "hw/amhw_hc32_rcc_reset.h"

/** \brief LVD�������� */
#define __LVD_TRI_TYPE         AMHW_HC32_LVD_RTEN

/** \brief LVD�˲�ʱ�� */
#define __LVD_DEB_TIME         AMHW_HC32_LVD_DEB_TIME_7P2_MS

/** \brief LVD��������*/
#define __LVD_TRI_ACT          AMHW_HC32_LVD_TRI_ACT_NVIC_INT


/** \brief �û��ص�����*/
static am_pfnvoid_t            __gpfn_app_lvd_cb;
/** \brief �û��ص���������*/
static void                   *__gp_arg;


/**
 * \brief LVD�жϷ�����
 */
static void __lvd_irq_handler (void *p_arg)
{
    amhw_hc32_lvd_t *p_hw_base = (amhw_hc32_lvd_t *)p_arg;

    if (amhw_hc32_int_status_check (p_hw_base) == 0){
        return;
    }

    /* ����жϱ�־ */
    amhw_hc32_int_falg_clr (p_hw_base);

    /* �û��ص����� */
    if (__gpfn_app_lvd_cb) {
        __gpfn_app_lvd_cb(__gp_arg);
    }
}

/**
 * \brief LVD ��ʼ��
 */
static void __lvd_hw_init (amhw_hc32_lvd_t       *p_hw_base,
                           amhw_hc32_lvd_vids_t   lvd_vids,
                           uint32_t               lvd_src)
{
    /* CR �Ĵ������� */
    amhw_hc32_lvd_cr_clr(p_hw_base);

    /* ��������ʹ�� */
    amhw_hc32_lvd_tri_enable(p_hw_base, __LVD_TRI_TYPE);

    /* �����˲�ʱ��ѡ�� */
    amhw_hc32_lvd_deb_time_sel(p_hw_base, __LVD_DEB_TIME);

    /* ʹ�������˲� */
    amhw_hc32_lvd_deb_time_enable(p_hw_base);

    /* ��ֵ��ѹѡ�� */
    amhw_hc32_lvd_vids_sel(p_hw_base, lvd_vids);

    /* �����Դѡ�� */
    amhw_hc32_lvd_src_sel(p_hw_base, lvd_src);

    /* ������������ */
    amhw_hc32_lvd_tri_act_sel(p_hw_base, __LVD_TRI_ACT);
}

/**
 * \brief LVD�жϳ�ʼ��
 */
static void __lvd_int_init (amhw_hc32_lvd_t  *p_hw_base)
{
    /* �ж�״̬��־��� */
    amhw_hc32_int_falg_clr (p_hw_base);

    /* ʹ���ж� */
    amhw_hc32_lvd_int_enable (p_hw_base);

    /* �ж����� */
    am_int_connect(INUM_LVD, __lvd_irq_handler, p_hw_base);

    /* �����ж� */
    am_int_enable (INUM_LVD);
}

/**
 * \brief LVDϵͳ��λ���̣�hw�ӿڲ�ʵ��
 */
void demo_hc32_hw_lvd_int_entry (amhw_hc32_lvd_t      *p_hw_base,
                                 amhw_hc32_lvd_vids_t  lvd_vids,
                                 uint32_t              lvd_src,
                                 am_pfnvoid_t          pfn_lvd_cb,
                                 void                 *p_arg)
{
    if (p_hw_base == NULL) {
        return;
    }

    /* �����û��ص� */
    __gpfn_app_lvd_cb = pfn_lvd_cb;
    __gp_arg          = p_arg;

    /* LVD ��ʼ�� */
    __lvd_hw_init(p_hw_base, lvd_vids, lvd_src);

    /* �жϳ�ʼ�� */
    __lvd_int_init(p_hw_base);

    /* LVD ʹ�� */
    amhw_hc32_lvd_enable (p_hw_base);

    AM_FOREVER {
        ;
    }
}

/* end of file */

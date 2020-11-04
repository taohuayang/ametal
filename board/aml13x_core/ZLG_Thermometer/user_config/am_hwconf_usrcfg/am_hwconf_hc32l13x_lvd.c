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
 * \brief ZLG LVD �û������ļ�
 * \sa am_hwconf_hc32_lvd.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "am_hc32_lvd.h"
#include "hw/amhw_hc32_lvd.h"
#include "hc32x3x_pin.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_lvd
 * \copydoc am_hwconf_hc32_lvd.c
 * @{
 */

/**
 * \brief LVD ƽ̨��ʼ��
 */
void __hc32_plfm_lvd_init (void)
{
    /* ����LVDʱ�� */
    am_clk_enable (CLK_VC_LVD);
}

/**
 * \brief LVD ƽ̨ȥ��ʼ��
 */
void __hc32_plfm_lvd_deinit (void)
{
    /* �ر�DACʱ�� */
    am_clk_disable(CLK_VC_LVD);
}

/** \brief LVD �豸��Ϣ */
static const am_hc32_lvd_devinfo_t __g_lvd_devinfo =
{
    /**< \brief ָ��LVD�Ĵ������ָ�� */
    HC32_LVD_BASE,

    /**< \brief LVD�жϱ�� */
    INUM_LVD,

    /**
     * \brief LVD��������
     *
     * \note ���ִ�������������Ҫѡ��������������
     *       ����AMHW_HC32_LVD_FTEN | AMHW_HC32_LVD_RTEN��
     */
    AMHW_HC32_LVD_RTEN,

    /**
     * \brief LVD�����˲�ʱ��,�û�����ֵ�ο�ö�ٶ��壺LVD �����˲�ʱ��
     */
    AMHW_HC32_LVD_DEB_TIME_7P2_MS,

    /**
     * \brief LVD��ֵ��ѹ,�û�����ֵ�ο�ö�ٶ��壺LVD ��ֵ��ѹ
     */
    AMHW_HC32_LVD_VIDS_2P5_V,

    /**
     * \brief LVD�����Դ,�û�����ֵ�ο��궨�壺LVD �����Դѡ������
     */
    AMHW_HC32_LVD_SRC_AVCC,

    /**
     * \brief LVD��������,�û�����ֵ�ο��궨�壺LVD ��������ѡ������
     *
     * \note ������λֻ��ѡ��Ϊ�жϻ��߸�λ��������
     */
    AMHW_HC32_LVD_TRI_ACT_SYSTEM_RESET,

    /**< \brief LVDƽ̨��ʼ������ */
    __hc32_plfm_lvd_init,

    /**< \brief LVDƽ̨���ʼ������  */
    __hc32_plfm_lvd_deinit,
};

/** \brief LVD�豸ʵ�� */
static am_hc32_lvd_dev_t __g_lvd_dev;

/** \brief LVD ʵ����ʼ�������LVD��׼������ */
am_hc32_lvd_handle_t am_hc32_lvd_inst_init (void)
{
    return am_hc32_lvd_init(&__g_lvd_dev, &__g_lvd_devinfo);
}

/** \brief LVD ʵ�����ʼ�� */
void am_hc32_lvd_inst_deinit (am_hc32_lvd_handle_t handle)
{
    am_hc32_lvd_deinit(handle);
}

/**
 * @}
 */

/* end of file */

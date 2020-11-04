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
 * \brief PCA�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-19
 * \endinternal
 */

/*******************************************************************************
  ͷ�ļ�
*******************************************************************************/
#include "ametal.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_zlg118_pca.h"
#include "zlg118_clk.h"
#include "zlg118_inum.h"
#include "zlg118_periph_map.h"

/*******************************************************************************
  �궨��
*******************************************************************************/


/*******************************************************************************
  �ڲ�����
*******************************************************************************/

void __pca_irq_handler (void *parg)
{
    am_zlg118_pca_dev_t *p_dev = (am_zlg118_pca_dev_t *)parg;

    if(0 < amhw_zlg118_pca_int_get(p_dev->p_hw_pca, ZLG118_PCA_CF)) {
        amhw_zlg118_pca_int_clear(p_dev->p_hw_pca, ZLG118_PCA_CF);
    } else if (0 < amhw_zlg118_pca_int_get(p_dev->p_hw_pca, ZLG118_PCA_CCF4)) {
        amhw_zlg118_pca_int_clear(p_dev->p_hw_pca, ZLG118_PCA_CCF4);
    } else if (0 < amhw_zlg118_pca_int_get(p_dev->p_hw_pca, ZLG118_PCA_CCF3)) {
        amhw_zlg118_pca_int_clear(p_dev->p_hw_pca, ZLG118_PCA_CCF3);
    } else if (0 < amhw_zlg118_pca_int_get(p_dev->p_hw_pca, ZLG118_PCA_CCF2)) {
        amhw_zlg118_pca_int_clear(p_dev->p_hw_pca, ZLG118_PCA_CCF2);
    } else if (0 < amhw_zlg118_pca_int_get(p_dev->p_hw_pca, ZLG118_PCA_CCF1)) {
        amhw_zlg118_pca_int_clear(p_dev->p_hw_pca, ZLG118_PCA_CCF1);
    } else if (0 < amhw_zlg118_pca_int_get(p_dev->p_hw_pca, ZLG118_PCA_CCF0)) {
        amhw_zlg118_pca_int_clear(p_dev->p_hw_pca, ZLG118_PCA_CCF0);
    }
}

/*******************************************************************************
  �ⲿ����
*******************************************************************************/

/**
 * \brief PCA��ʼ��
 *
 * \return PCA����������
 */
am_zlg118_pca_handle_t am_zlg118_pca_init (
        am_zlg118_pca_dev_t             *p_dev,
        const am_zlg118_pca_devinfo_t   *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->p_devinfo = p_devinfo;
    p_dev->p_hw_pca = (amhw_zlg118_pca_t *)p_devinfo->pca_regbase;

    if(p_devinfo->pfn_plfm_init != NULL) {
        p_devinfo->pfn_plfm_init();
    }

    /* PCAʱ��Դѡ�� */
    amhw_zlg118_pca_cps_set(p_dev->p_hw_pca, p_devinfo->clk_src);

    return p_dev;
}

/**
 * \brief ���PCA��ʼ��
 *
 * \param[in] handle : ����豸������PCA��׼����������
 *
 * \return ��
 */
void am_zlg118_pca_deinit (am_zlg118_pca_handle_t handle)
{
    if(handle->p_devinfo->pfn_plfm_deinit != NULL) {
        handle->p_devinfo->pfn_plfm_deinit();
    }
    handle->p_devinfo = NULL;
    handle->p_hw_pca  = NULL;
}

/**
 * \brief PCA���ز���ģʽ����
 *
 * \param[in] handle : ����豸������PCA��׼����������
 * \param[in] num    : PCA ģ����
 * \param[in] chan   : ͨ����
 * \param[in] cap    : �������ѡ��
 *
 * \return AM_OK:�ɹ�
 *         ����:ʧ��
 */
int am_zlg118_pca_cap_set (am_zlg118_pca_handle_t handle,
                           uint8_t                num,
                           uint8_t                chan,
                           am_zlg118_pca_capn_t   cap)
{
    am_zlg118_pca_int_t int_clr;

    if(num > 4 || handle == NULL || handle->p_devinfo->ioinfo == NULL) {
        return -AM_EINVAL;
    }

    am_gpio_pin_cfg(handle->p_devinfo->ioinfo[chan].gpio,
                    handle->p_devinfo->ioinfo[chan].capfunc);

    /* ���ܱȽ��� */
    amhw_zlg118_pca_ecom_set(handle->p_hw_pca, num, 0);

    /* ����������� */
    amhw_zlg118_pca_capp_set(handle->p_hw_pca, num, (cap >> 1) & 0x1);
    amhw_zlg118_pca_capn_set(handle->p_hw_pca, num, cap & 0x1);

    /* ����ƥ�书�� */
    amhw_zlg118_pca_mat_set(handle->p_hw_pca, num, 0);

    /* �������ŷ�ת */
    amhw_zlg118_pca_tog_set(handle->p_hw_pca, num, ZLG118_PCA_TOG_DIS);

    /* ����PWM */
    amhw_zlg118_pca_pwm_set(handle->p_hw_pca, num, 0);
    amhw_zlg118_pca_epwm_disable(handle->p_hw_pca);

    switch(num) {
    case 0:
        int_clr = ZLG118_PCA_CCF0;
        break;
    case 1:
        int_clr = ZLG118_PCA_CCF1;
        break;
    case 2:
        int_clr = ZLG118_PCA_CCF2;
        break;
    case 3:
        int_clr = ZLG118_PCA_CCF3;
        break;
    case 4:
        int_clr = ZLG118_PCA_CCF4;
        break;

    default:
        break;
    }
    amhw_zlg118_pca_int_clear(handle->p_hw_pca, int_clr);

    /* ����Ƚ�/�����ж� */
    amhw_zlg118_pca_ccie_set(handle->p_hw_pca, num, 1);

    /* �����жϺ��� */
    am_int_connect(handle->p_devinfo->inum, __pca_irq_handler, (void *)handle);
    am_int_enable(handle->p_devinfo->inum);

    return AM_OK;
}

/**
 * \brief PCA�Ƚϼ���ģʽ����
 *
 * \param[in] handle : ����豸������PCA��׼����������
 * \param[in] num    : PCA ģ����
 * \param[in] carr   : ���ڼĴ���ֵ
 * \param[in] ccap   : �Ƚϲ���Ĵ���ֵ
 *
 * \return AM_OK:�ɹ�
 *         ����:ʧ��
 */
int am_zlg118_pca_cmp_cnt_set (am_zlg118_pca_handle_t handle,
                               uint8_t                num,
                               uint16_t               carr,
                               uint16_t               ccap)
{
    am_zlg118_pca_int_t int_clr;

    if(num > 4 || handle == NULL) {
        return -AM_EINVAL;
    }

    /* ʹ�ܱȽ��� */
    amhw_zlg118_pca_ecom_set(handle->p_hw_pca, num, 1);

    /* ����������� */
    amhw_zlg118_pca_capp_set(handle->p_hw_pca, num, ZLG118_PCA_CAPP_DIS >> 1);
    amhw_zlg118_pca_capn_set(handle->p_hw_pca, num, ZLG118_PCA_CAPN_DIS);

    /* ʹ��ƥ�书�� */
    amhw_zlg118_pca_mat_set(handle->p_hw_pca, num, 1);

    /* �������ŷ�ת */
    amhw_zlg118_pca_tog_set(handle->p_hw_pca, num, ZLG118_PCA_TOG_DIS);

    /* PWM���� */
    amhw_zlg118_pca_pwm_set(handle->p_hw_pca, num, 0);
    amhw_zlg118_pca_epwm_enable(handle->p_hw_pca);

    /* ���ڼĴ������� */
    amhw_zlg118_pca_carr_set(handle->p_hw_pca, carr);

    /* �Ƚϲ���Ĵ������� */
    amhw_zlg118_pca_ccap_set(handle->p_hw_pca, num, ccap);

    switch(num) {
    case 0:
        int_clr = ZLG118_PCA_CCF0;
        break;
    case 1:
        int_clr = ZLG118_PCA_CCF1;
        break;
    case 2:
        int_clr = ZLG118_PCA_CCF2;
        break;
    case 3:
        int_clr = ZLG118_PCA_CCF3;
        break;
    case 4:
        int_clr = ZLG118_PCA_CCF4;
        break;

    default:
        break;
    }
    amhw_zlg118_pca_int_clear(handle->p_hw_pca, int_clr);

    /* ����Ƚ�/�����ж� */
    amhw_zlg118_pca_ccie_set(handle->p_hw_pca, num, 1);
    amhw_zlg118_pca_cfie_set(handle->p_hw_pca, 1);

    /* �����жϺ��� */
    am_int_connect(handle->p_devinfo->inum, __pca_irq_handler, (void *)handle);
    am_int_enable(handle->p_devinfo->inum);

    return AM_OK;
}

/**
 * \brief PCA�������ģʽ����
 *
 * \param[in] handle  : ����豸������PCA��׼����������
 * \param[in] num     : PCA ģ����
 * \param[in] chan    : ͨ����
 * \param[in] pwm_sel : PWM����ѡ��
 * \param[in] carr    : ���ڼĴ���ֵ
 * \param[in] ccap    : �Ƚϲ���Ĵ���ֵ
 *
 * 8bitռ�ձ�  = (255 - ccap) / 100 * 100%
 * 16bitռ�ձ�= (carr - ccap) / carr * 100%
 *
 * \return AM_OK:�ɹ�
 *         ����:ʧ��
 */
int am_zlg118_pca_pwm_set (am_zlg118_pca_handle_t handle,
                           uint8_t                num,
                           uint8_t                chan,
                           am_zlg118_pca_pwm_t    pwm_sel,
                           uint16_t               carr,
                           uint16_t               ccap)
{
    if(num > 4 || handle == NULL || handle->p_devinfo->ioinfo == NULL) {
        return -AM_EINVAL;
    }

    am_gpio_pin_cfg(handle->p_devinfo->ioinfo[chan].gpio,
                    handle->p_devinfo->ioinfo[chan].pwmunc);

    /* ʹ�ܱȽ��� */
    amhw_zlg118_pca_ecom_set(handle->p_hw_pca, num, 1);

    /* ����������� */
    amhw_zlg118_pca_capp_set(handle->p_hw_pca, num, ZLG118_PCA_CAPP_DIS >> 1);
    amhw_zlg118_pca_capn_set(handle->p_hw_pca, num, ZLG118_PCA_CAPN_DIS);

    /* ʹ��ƥ�书�� */
    amhw_zlg118_pca_mat_set(handle->p_hw_pca, num, 1);

    /* ʹ�����ŷ�ת */
    amhw_zlg118_pca_tog_set(handle->p_hw_pca, num, ZLG118_PCA_TOG_EN);

    /* PWM���� */
    if(pwm_sel) {
        amhw_zlg118_pca_pwm_set(handle->p_hw_pca, num, 0);
        amhw_zlg118_pca_epwm_enable(handle->p_hw_pca);

        amhw_zlg118_pca_carr_set(handle->p_hw_pca, carr);
        amhw_zlg118_pca_ccap_set(handle->p_hw_pca, num, ccap);
    } else {
        amhw_zlg118_pca_pwm_set(handle->p_hw_pca, num, 1);
        amhw_zlg118_pca_epwm_disable(handle->p_hw_pca);

        amhw_zlg118_pca_ccapl_set(handle->p_hw_pca, num, 255 - ccap);
        amhw_zlg118_pca_ccaph_set(handle->p_hw_pca, num, 255 - ccap);
    }

    return AM_OK;
}

/* ����PCAģ�� */
void am_zlg118_pca_start(am_zlg118_pca_handle_t handle)
{
    amhw_zlg118_pca_start(handle->p_hw_pca);
}

/* ֹͣPCAģ�� */
void am_zlg118_pca_stop(am_zlg118_pca_handle_t handle)
{
    amhw_zlg118_pca_stop(handle->p_hw_pca);
}

/* end of file */

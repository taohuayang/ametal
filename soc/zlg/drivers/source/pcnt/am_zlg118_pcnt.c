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
 * \brief PCNT�����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-12
 * \endinternal
 */

/*******************************************************************************
  ͷ�ļ�
*******************************************************************************/
#include "ametal.h"
#include "am_int.h"
#include "am_zlg118_pcnt.h"

/*******************************************************************************
  �ڲ�����
*******************************************************************************/

void __pcnt_irq_handler (void *parg)
{
    am_zlg118_pcnt_dev_t *p_dev = (am_zlg118_pcnt_dev_t *)parg;
    if(amhw_zlg118_pcnt_int_get(p_dev->p_hw_pcnt, ZLG118_PCNT_INT_TO)) {
        amhw_zlg118_pcnt_int_clear(p_dev->p_hw_pcnt, ZLG118_PCNT_INT_TO);
    } else if (amhw_zlg118_pcnt_int_get(p_dev->p_hw_pcnt, ZLG118_PCNT_INT_OV)) {
        amhw_zlg118_pcnt_int_clear(p_dev->p_hw_pcnt, ZLG118_PCNT_INT_OV);
    } else if (amhw_zlg118_pcnt_int_get(p_dev->p_hw_pcnt, ZLG118_PCNT_INT_UF)) {
        amhw_zlg118_pcnt_int_clear(p_dev->p_hw_pcnt, ZLG118_PCNT_INT_UF);
    } else {
        ;
    }
}

/*******************************************************************************
  �ⲿ����
*******************************************************************************/

/**
 * \brief PCNT��ʼ��
 *
 * \param[in] p_dev     : ָ��PCNT�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��PCNT�豸��Ϣ�ṹ���ָ��
 *
 * \return PCNT����������
 */
am_zlg118_pcnt_handle_t am_zlg118_pcnt_init (
        am_zlg118_pcnt_dev_t     *p_dev,
        const am_zlg118_pcnt_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->p_devinfo = p_devinfo;
    p_dev->p_hw_pcnt = (amhw_zlg118_pcnt_t *)p_devinfo->pcnt_regbase;

    if(p_devinfo->pfn_plfm_init != NULL) {
        p_devinfo->pfn_plfm_init();
    }

    /* ����жϱ�ʶ */
    amhw_zlg118_pcnt_int_clear(p_dev->p_hw_pcnt,
                               ZLG118_PCNT_INT_TO |
                               ZLG118_PCNT_INT_OV |
                               ZLG118_PCNT_INT_UF);

    /* �����жϺ��� */
    am_int_connect(p_devinfo->inum, __pcnt_irq_handler, (void *)p_dev);

    return p_dev;
}

/**
 * \brief ���PCNT��ʼ��
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 *
 * \return ��
 */
void am_zlg118_pcnt_deinit (am_zlg118_pcnt_handle_t handle)
{
    if(handle->p_devinfo->pfn_plfm_deinit != NULL) {
        handle->p_devinfo->pfn_plfm_deinit();
    }
    handle->p_devinfo = NULL;
    handle->p_hw_pcnt = NULL;
}

/**
 * \brief ����ʱ������
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] clk    : ʱ��
 *
 * \return ��
 */
void am_zlg118_pcnt_clk_sel (am_zlg118_pcnt_handle_t handle,
                             am_zlg118_pcnt_clk_t    clk)
{
    if (handle == NULL) {
        return ;
    }
    amhw_zlg118_pcnt_clk_set(handle->p_hw_pcnt, clk);
}

/**
 * \brief ͨ����������
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] polar  : ͨ������ѡ��
 *
 * \return ��
 */
void am_zlg118_pcnt_polar_set (am_zlg118_pcnt_handle_t handle,
                               am_zlg118_pcnt_polar_t  polar)
{
    if (handle == NULL) {
        return ;
    }
    switch(polar) {
    case ZLG118_PCNT_S0PNOINVERT:
        amhw_zlg118_pcnt_s0p_set(handle->p_hw_pcnt, 0);
        break;

    case ZLG118_PCNT_S0PINVERT:
        amhw_zlg118_pcnt_s0p_set(handle->p_hw_pcnt, 1);
        break;

    case ZLG118_PCNT_S1PNOINVERT:
        amhw_zlg118_pcnt_s1p_set(handle->p_hw_pcnt, 0);
        break;

    case ZLG118_PCNT_S1PINVERT:
        amhw_zlg118_pcnt_s1p_set(handle->p_hw_pcnt, 1);
        break;

    default:
        break;
    }
}

/**
 * \brief �˲�ʹ��
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] debtop : �˲���������ֵ
 * \param[in] clkdiv : �˲�ʱ�ӷ�Ƶϵ��
 *
 * \return ��
 */
void am_zlg118_pcnt_flt_enable (am_zlg118_pcnt_handle_t handle,
                                uint8_t                 debtop,
                                uint16_t                clkdiv)
{
    if (handle == NULL) {
        return ;
    }
    amhw_zlg118_pcnt_debtop_set(handle->p_hw_pcnt, debtop);
    amhw_zlg118_pcnt_clkdiv_set(handle->p_hw_pcnt, clkdiv);
    amhw_zlg118_pcnt_flt_enable(handle->p_hw_pcnt);
}

/**
 * \brief �˲�����
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 *
 * \return ��
 */
void am_zlg118_pcnt_flt_disable (am_zlg118_pcnt_handle_t handle)
{
    if (handle == NULL) {
        return ;
    }
    amhw_zlg118_pcnt_flt_disable(handle->p_hw_pcnt);
}

/**
 * \brief ��ʱʹ��
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] th     : ��ʱ��ֵ
 *
 * \return ��
 */
void am_zlg118_pcnt_timeover_enable (am_zlg118_pcnt_handle_t handle,
                                     uint16_t                th)
{
    if (handle == NULL) {
        return ;
    }
    amhw_zlg118_pcnt_th_set(handle->p_hw_pcnt, th);
    amhw_zlg118_pcnt_timeover_enable(handle->p_hw_pcnt);
}

/**
 * \brief ��ʱ����
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 *
 * \return ��
 */
void am_zlg118_pcnt_timeover_disable (am_zlg118_pcnt_handle_t handle)
{
    if (handle == NULL) {
        return ;
    }
    amhw_zlg118_pcnt_timeover_disable(handle->p_hw_pcnt);
}

/**
 * \brief PCNTʹ��
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 * \param[in] mode   : ����ģʽ
 * \param[in] dir    : ��������
 * \param[in] value  : ���ֵ
 * \param[in] dgb    : ���ѡ��
 *
 * \return ��
 */
void am_zlg118_pcnt_start (am_zlg118_pcnt_handle_t handle,
                           am_zlg118_pcnt_mode_t   mode,
                           am_zlg118_pcnt_dir_t    dir,
                           uint16_t                value,
                           am_zlg118_pcnt_dgb_t    dgb)
{
    if (handle == NULL) {
        return ;
    }

    /* ������� */
    amhw_zlg118_pcnt_dbg_set(handle->p_hw_pcnt, dgb);

    /* ģʽ���� */
    amhw_zlg118_pcnt_mode_set(handle->p_hw_pcnt, mode);

    if(ZLG118_PCNT_DOUBLE != mode) {

        /* ������������ */
        amhw_zlg118_pcnt_dir_set(handle->p_hw_pcnt, dir);
    }

    /* ���ֵ���� */
    amhw_zlg118_pcnt_buf_set(handle->p_hw_pcnt, value);

    if(ZLG118_PCNT_UP == dir) {

        /* ����ͬ������ */
        amhw_zlg118_pcnt_cmd_set(handle->p_hw_pcnt,
                                 ZLG118_PCNT_B2T);

        /* ʹ����Ӧ�ж� */
        amhw_zlg118_pcnt_int_enable(handle->p_hw_pcnt,
                                    ZLG118_PCNT_INT_OV);
    } else {
        amhw_zlg118_pcnt_cmd_set(handle->p_hw_pcnt,
                                 ZLG118_PCNT_B2C);
        amhw_zlg118_pcnt_int_enable(handle->p_hw_pcnt,
                                    ZLG118_PCNT_INT_UF);
    }

    am_int_enable(handle->p_devinfo->inum);
    amhw_zlg118_pcnt_start(handle->p_hw_pcnt);
}

/**
 * \brief PCNT����
 *
 * \param[in] handle : ����豸������PCNT��׼����������
 *
 * \return ��
 */
void am_zlg118_pcnt_stop (am_zlg118_pcnt_handle_t handle)
{
    if (handle == NULL) {
        return ;
    }

    am_int_disable(handle->p_devinfo->inum);
    amhw_zlg118_pcnt_stop(handle->p_hw_pcnt);
}

/* end of file */

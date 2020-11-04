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
 * \par Modification history
 * - 1.00 19-10-11
 * \endinternal
 */

#ifndef __AMHW_ZLG118_PCNT_H
#define __AMHW_ZLG118_PCNT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__GNUC__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_zlg118_if_pcnt
 * \copydoc amhw_zlg118_pcnt.h
 * @{
 */

/**
 * \brief PCNT�Ĵ�����ṹ��
 */
typedef struct amhw_zlg118_pcnt {
    __IO uint32_t run;      /* �����Ĵ��� */
    __IO uint32_t ctrl;     /* ���ƼĴ��� */
    __IO uint32_t flt;      /* �˲����ƼĴ��� */
    __IO uint32_t tocr;     /* ��ʱ���ƼĴ��� */
    __O  uint32_t cmd;      /* ����Ĵ��� */
    __I  uint32_t sr1;      /* ״̬�Ĵ���1 */
    __I  uint32_t cnt;      /* �����Ĵ��� */
    __I  uint32_t top;      /* ��������Ĵ��� */
    __IO uint32_t buf;      /* �����������Ĵ��� */
    __I  uint32_t ifr;      /* �жϱ�ʶ�Ĵ��� */
    __O  uint32_t icr;      /* �ж�����Ĵ��� */
    __IO uint32_t ien;      /* �ж�ʹ�ܼĴ��� */
    __I  uint32_t sr2;      /* ״̬�Ĵ���2 */
    __IO uint32_t dbg;      /* ���ѡ��Ĵ��� */
} amhw_zlg118_pcnt_t;

/**
 * \brief PCNT����
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_start (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    p_hw_pcnt->run |= 0x1ul;
}

/**
 * \brief PCNTֹͣ
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_stop (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    p_hw_pcnt->run &= ~0x1ul;
}

/**
 * \brief PCNT����/ֹͣ״̬��ȡ
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return 0:ֹͣ, 1:����
 */
am_static_inline
uint8_t amhw_zlg118_pcnt_run_get (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    return p_hw_pcnt->run & 0x1ul;
}

/**
 * \brief S1ͨ������ѡ��
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  mode       : ����ѡ�� 1��ȡ���� 0����ȡ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_s1p_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t mode)
{
        p_hw_pcnt->ctrl = (p_hw_pcnt->ctrl & ~(0x1ul << 6)) | \
                          ((mode & 0x1) << 6);
}

/**
 * \brief S0ͨ������ѡ��
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  mode       : ����ѡ�� 1��ȡ���� 0����ȡ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_s0p_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t mode)
{
        p_hw_pcnt->ctrl = (p_hw_pcnt->ctrl & ~(0x1ul << 5)) | \
                          ((mode & 0x1) << 5);
}

/**
 * \brief ��������ѡ��(���Ե�ͨ��ģʽ��˫ͨ���ǽ�ģʽ��Ч)
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  dir        : �������� 1���������� 0���Ӽ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_dir_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t dir)
{
        p_hw_pcnt->ctrl = (p_hw_pcnt->ctrl & ~(0x1ul << 4)) | \
                          ((dir & 0x1) << 4);
}

/**
 * \brief ���������ȡ(���Ե�ͨ��ģʽ��˫ͨ���ǽ�ģʽ��Ч)
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return  1���������� 0���Ӽ���
 */
am_static_inline
uint8_t amhw_zlg118_pcnt_dir_get (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    return (p_hw_pcnt->ctrl >> 4) & 0x1ul;
}

/**
 * \brief ʱ��ѡ��
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  clksel     : ʱ��ѡ�� 0:PCLK
 *                                     1:PCLK
 *                                     2:XTL
 *                                     3:RCL
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_clk_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t clksel)
{
    p_hw_pcnt->ctrl = (p_hw_pcnt->ctrl & ~(0x3ul << 2)) | \
                      ((clksel & 0x3ul)<< 2);
}

/**
 * \brief ����ģʽѡ��
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  mode       : ʱ��ѡ�� 0:��ͨ���������ģʽ
 *                                     1:��ͨ���������ģʽ
 *                                     2:˫ͨ���ǽ��������ģʽ
 *                                     3:˫ͨ�������������ģʽ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_mode_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t mode)
{
    p_hw_pcnt->ctrl = (p_hw_pcnt->ctrl & ~0x3ul) | (mode & 0x3ul);
}

/**
 * \brief �������˲���ʹ��
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_flt_enable (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    p_hw_pcnt->flt |= (0x1ul << 16);
}

/**
 * \brief �������˲�������
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_flt_disable (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    p_hw_pcnt->flt &= ~(0x1ul << 16);
}

/**
 * \brief �˲���������ֵ����
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  top        : ��������ֵ,����Ϊ0
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_debtop_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t top)
{
    if(top > 0) {
        p_hw_pcnt->flt = (p_hw_pcnt->flt & ~(0x7ul << 13)) | \
                         ((top & 0x7ul) << 13);
    }
}

/**
 * \brief �˲�ʱ�ӷ�Ƶϵ������
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  div        : ��Ƶϵ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_clkdiv_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint16_t div)
{
    p_hw_pcnt->flt = (p_hw_pcnt->flt & ~0x1ffful) | (div & 0x1ffful);
}

/**
 * \brief ��ʱ����ʹ��
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_timeover_enable (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    p_hw_pcnt->tocr |= (0x1ul << 16);
}

/**
 * \brief ��ʱ���ܽ���
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_timeover_disable (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    p_hw_pcnt->tocr &= ~(0x1ul << 16);
}

/**
 * \brief ��ʱ��ֵ����
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  th         : ��ʱ��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_th_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint16_t th)
{
    p_hw_pcnt->tocr = (p_hw_pcnt->tocr & ~0xffful) | (th & 0xffful);
}

/**
 * \brief ����Ĵ�������
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  cmd        : ����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_cmd_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint32_t cmd)
{
    p_hw_pcnt->cmd |= cmd;
}

/**
 * \brief ˫ͨ������������������ȡ
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return 0:�Ӽ���, 1:������
 */
am_static_inline
uint8_t amhw_zlg118_pcnt_ddir_get (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    return p_hw_pcnt->sr1 & 0x1ul;
}

/**
 * \brief ����������ֵ��ȡ
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint16_t amhw_zlg118_pcnt_cnt_get (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    return p_hw_pcnt->cnt & 0xfffful;
}

/**
 * \brief �����������ֵ/���������ֵ��ȡ
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return ���ֵ
 */
am_static_inline
uint16_t amhw_zlg118_pcnt_top_get (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    return p_hw_pcnt->top & 0xfffful;
}

/**
 * \brief ������������ȡ
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 *
 * \return �����ֵ
 */
am_static_inline
uint16_t amhw_zlg118_pcnt_buf_get (amhw_zlg118_pcnt_t *p_hw_pcnt)
{
    return p_hw_pcnt->buf & 0xfffful;
}

/**
 * \brief ����ֵ����
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  buf        : ����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_buf_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint16_t buf)
{
    p_hw_pcnt->buf = buf;
}

/**
 * \brief �жϱ�ʶ��ȡ
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  ie         : �жϱ�ʶ
 *
 * \return 0:���жϱ�ʶ, ��0:���жϱ�ʶ
 */
am_static_inline
uint16_t amhw_zlg118_pcnt_int_get (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t ie)
{
    return p_hw_pcnt->buf & ie;
}

/**
 * \brief �жϱ�ʶ���
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  ie         : �жϱ�ʶ
 *
 * \return
 */
am_static_inline
void amhw_zlg118_pcnt_int_clear (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t ie)
{
    p_hw_pcnt->buf &= ~ie;
}

/**
 * \brief �ж�ʹ��
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  ie         : �жϱ�ʶ
 *
 * \return
 */
am_static_inline
void amhw_zlg118_pcnt_int_enable (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t ie)
{
    p_hw_pcnt->ien |= ie;
}

/**
 * \brief �жϽ���
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  ie         : �жϱ�ʶ
 *
 * \return
 */
am_static_inline
void amhw_zlg118_pcnt_int_disable (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t ie)
{
    p_hw_pcnt->ien &= ~ie;
}

/**
 * \brief ͬ��״̬��ȡ
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  cmd         : ͬ������
 *
 * \return 0:ͬ�����, ��0:ͬ��������
 */
am_static_inline
uint16_t amhw_zlg118_pcnt_stat_get (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t cmd)
{
    return p_hw_pcnt->sr2 & cmd;
}

/**
 * \brief ���ѡ��
 *
 * \papcnt[in]  p_hw_pcnt  : ָ��PCNT�Ĵ����ṹ���ָ��
 * \papcnt[in]  sel        : ���ѡ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_pcnt_dbg_set (amhw_zlg118_pcnt_t *p_hw_pcnt, uint8_t sel)
{
    p_hw_pcnt->buf = sel;
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__GNUC__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __AMHW_ZLG118_PCNT_H */

#endif

/* end of file */

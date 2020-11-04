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
 * \brief USB interfaces for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-27  yrh, first implementation
 * \endinternal
 */
#ifndef __AMHW_ZMF237_USBD_H
#define __AMHW_ZMF237_USBD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_types.h"
#include "../../../../zlg237/zlg237_periph_map.h"

/**
 * \addtogroup amhw_zmf237_if_usbd
 * \copydoc ZMF237_USBd.h
 * @{
 */

/**
 *  \brief USB �Ĵ����ṹ�嶨��
 */
typedef struct amhw_zmf237_usb{
    __IO  uint16_t top;              /* �ж�״̬�Ĵ�����ƫ�Ƶ�ַ0x00 */
          uint16_t reserve0;         /* ����λ */
    __IO  uint16_t int_state;        /* �ж�״̬�Ĵ�����ƫ�Ƶ�ַ0x04 */
          uint16_t reserve1;         /* ����λ */
    __IO  uint16_t ep_int_state;     /* �˵��ж�״̬�Ĵ�����ƫ�Ƶ�ַ0x08 */
          uint16_t reserve2;         /* ����λ */
    __IO  uint16_t ep0_int_state;    /* �˵�0�ж�״̬�Ĵ�����ƫ�Ƶ�ַ0xc0 */
          uint16_t reserve3;         /* ����λ */
    __IO  uint16_t int_en;           /* �ж�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x10 */
          uint16_t reserve4;         /* ����λ */
    __IO  uint16_t ep_int_en;        /* �˵��ж�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x14 */
          uint16_t reserve5;         /* ����λ */
    __IO  uint16_t ep0_int_en;       /* �˵�0�ж�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x18 */
          uint16_t reserve6[3];      /* ����λ */
    struct {
    __IO  uint16_t epx_int_state;
          uint16_t reserved6;
    }epx_int_state_arr[4];                 /* �˵�x�ж�״̬�Ĵ�����ƫ�Ƶ�ַ0x20-0x2c */
          uint16_t reserve7[8];            /* ����λ */
    struct {
    __IO  uint16_t epx_int_en;
          uint16_t reserved8;
    } epx_int_en_arr[4];                   /* �˵�x�ж�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x40-0x4c */
          uint16_t  reserve9[8];           /* ����λ */
    __IO  uint16_t addr;                   /* usb��ַ�Ĵ�����ƫ�Ƶ�ַ0x60 */
          uint16_t reserve10;              /* ����λ */
    __IO  uint16_t ep_en;                  /* usb�˵�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x64 */
          uint16_t reserve11[9];           /* ����λ */
    __IO  uint16_t tog_crl1_4;             /* ���ݷ�ת���ƼĴ�����ƫ�Ƶ�ַ0x78 */
          uint16_t  reserve12[3];          /* ����λ */
    struct {
    __IO  uint16_t stupx;
          uint16_t reserved13;
    }stupx_arr[8];                         /* ���ð����ݼĴ�����ƫ�Ƶ�ַ0x80-0x9c */
    __IO  uint16_t packet_size;            /* �������С�Ĵ�����ƫ�Ƶ�ַ0xa0 */
          uint16_t reserve14[47];          /* ����λ */
    struct {
    __IO  uint16_t epx_avai;
          uint16_t reserved15;
    }epx_avail_arr[5];                     /* �˵�x��Ч���ݼĴ�����ƫ�Ƶ�ַ0x100-0x110 */
          uint16_t  reserve16[22];         /* ����λ */
    struct {
    __IO  uint16_t epx_ctrl;
          uint16_t reserved17;
    }epx_ctrl_arr[5];                      /* �˵�x���ƼĴ�����ƫ�Ƶ�ַ0x140-0x150 */
          uint16_t reserve18[6];           /* ����λ */
    struct {
    __IO  uint16_t epx_fifo;
          uint16_t reserved19;
    }epx_fifo_arr[5];                      /* �˵�x fifo�Ĵ�����ƫ�Ƶ�ַ0x160-0x170 */
          uint16_t reserve20[8];           /* ����λ */
    __IO  uint16_t ep_dma;                 /* �˵�dmaʹ�ܼĴ�����ƫ�Ƶ�ַ0x184 */
          uint16_t reserve21;              /* ����λ */
    __IO  uint16_t ep_halt;                /* �˵��ݴ�Ĵ�����ƫ�Ƶ�ַ0x188 */
          uint16_t reserve22[27];          /* ����λ */
    __IO  uint16_t power;                  /* ���ļĴ�����ƫ�Ƶ�ַ0x1c0 */
}amhw_zmf237_usbd_t;

/*******************  Bit definition for USB_TOP register  *******************/
#define  AMHW_ZMF237_USB_TOP_SPEED        0
#define  AMHW_ZMF237_USB_TOP_CONNECT      1
#define  AMHW_ZMF237_USB_TOP_RESET        3
#define  AMHW_ZMF237_USB_TOP_SUSPEND      4
#define  AMHW_ZMF237_USB_TOP_DP_DM_STATE  5
#define  AMHW_ZMF237_USB_TOP_ACTIVE       7

/**************************  USB_TOP Configuration  ***************************/
#define  AMHW_USB_SPEED            (1UL << AMHW_ZMF237_USB_TOP_SPEED)
#define  AMHW_USB_CONNECT          (1UL << AMHW_ZMF237_USB_TOP_CONNECT)
#define  AMHW_USB_RESET            (1UL << AMHW_ZMF237_USB_TOP_RESET)
#define  AMHW_USB_SUSPEND          (1UL << AMHW_ZMF237_USB_TOP_SUSPEND)
#define  AMHW_USB_DP_DM_STATE      (3UL << AMHW_ZMF237_USB_TOP_DP_DM_STATE)
#define  AMHW_USB_ACTIVE           (1UL << AMHW_ZMF237_USB_TOP_ACTIVE)

/**
 * \brief USB����ö��
 */
typedef enum {
    ZMF237_USB_SPEED_FULL,   /* ȫ�ٴ��� */
    ZMF237_USB_SPEED_LOW     /* ���ٴ��� */
}zmf237_usb_speed_t;

/**
 *  \brief ����usb���ʺ���
 *
 *  \param[in] speed  usb����
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_speed_set (amhw_zmf237_usbd_t *p_usb, zmf237_usb_speed_t speed)
{
    if (speed == ZMF237_USB_SPEED_FULL)
        p_usb->top &= (~AMHW_USB_SPEED);
    else if (speed == ZMF237_USB_SPEED_LOW)
        p_usb->top |= (AMHW_USB_SPEED);
}

/**
 *  \brief ���usb���ʺ���
 *
 *  \return usb����
 */
am_static_inline
uint16_t amhw_zmf237_usbd_speed_get (amhw_zmf237_usbd_t *p_usb)
{
    return ((p_usb->top & AMHW_USB_SPEED) >> AMHW_ZMF237_USB_TOP_SPEED);
}

/**
 * \brief USB����״̬ö��
 */
typedef enum {
    ZMF237_USB_DISCONNECT,   /* �Ͽ����� */
    ZMF237_USB_CONNECT       /* ���� */
}zmf237_usb_connect_t;

/**
 *  \brief ����usb����״̬����
 *
 *  \param[in] connect  usb����״̬
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_connect_set (amhw_zmf237_usbd_t *p_usb, zmf237_usb_connect_t connect)
{
    if (connect == ZMF237_USB_DISCONNECT)
        p_usb->top &= (~AMHW_USB_CONNECT);
    else if (connect == ZMF237_USB_CONNECT)
        p_usb->top |= (AMHW_USB_CONNECT);
}

/**
 *  \brief ���usb����״̬����
 *
 *  \return usb����״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_connect_get (amhw_zmf237_usbd_t *p_usb)
{
    return ((p_usb->top & AMHW_USB_CONNECT) >> AMHW_ZMF237_USB_TOP_CONNECT);
}

/**
 * \brief USB��λ״̬ö��
 */
typedef enum {
    ZMF237_USB_NORESET,   /* ����λ */
    ZMF237_USB_RESET      /* ��λ */
}zmf237_usb_reset_t;

/**
 *  \brief ����usb��λ����
 *
 *  \param[in] reset  usb��λ״̬
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_reset_set (amhw_zmf237_usbd_t *p_usb, zmf237_usb_reset_t reset)
{
    if(reset == ZMF237_USB_NORESET)
        p_usb->top &= (~AMHW_USB_RESET);
    else if(reset == ZMF237_USB_RESET)
        p_usb->top |= (AMHW_USB_RESET);
}

/**
 *  \brief ���usb��λ����
 *
 *  \return usb��λ״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_reset_get (amhw_zmf237_usbd_t *p_usb)
{
    return ((p_usb->top & AMHW_USB_RESET) >> AMHW_ZMF237_USB_TOP_RESET);
}

/**
 * \brief USB suspend״̬ö��
 */
typedef enum {
    ZMF237_USB_SUSPEND_WORK,     /* ����״̬ */
    ZMF237_USB_SUSPEND_PENDING   /* ����״̬ */
}zmf237_usb_suspend_t;

/**
 *  \brief ���usb suspend״̬����
 *
 *  \return usb suspend״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_suspend_get (amhw_zmf237_usbd_t *p_usb)
{
    return ((p_usb->top & AMHW_USB_SUSPEND) >> AMHW_ZMF237_USB_TOP_SUSPEND);
}

/**
 *  \brief ���usb dp/dm��״̬����
 *
 *  \return usb dp/dm״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_dp_dm_get (amhw_zmf237_usbd_t *p_usb)
{
    return ((p_usb->top & AMHW_USB_DP_DM_STATE) >> AMHW_ZMF237_USB_TOP_DP_DM_STATE);
}

/**
 * \brief USB ���߻�Ծ״̬
 */
typedef enum {
    ZMF237_USB_INACTIVE,     /* ���߲���Ծ */
    ZMF237_USB_ACTIVE        /* ���߻�Ծ */
}zmf237_usb_active_t;

/**
 *  \brief ����usb���߻�Ծ״̬����
 *
 *  \param[in] active  usb ���߻�Ծ״̬
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_active_set(amhw_zmf237_usbd_t *p_usb, zmf237_usb_active_t active)
{
    if (active == ZMF237_USB_INACTIVE)
        p_usb->top &= (~AMHW_USB_ACTIVE);
    else if (active == ZMF237_USB_ACTIVE)
        p_usb->top |= (AMHW_USB_ACTIVE);
}

/**
 *  \brief ���usb���߻�Ծ״̬����
 *
 *  \return usb ���߻�Ծ״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_active_get (amhw_zmf237_usbd_t *p_usb)
{
    return ((p_usb->top & AMHW_USB_ACTIVE) >> AMHW_ZMF237_USB_TOP_ACTIVE);
}

/***********************  USB_INT_STATE Configuration  ************************/
#define  AMHW_ZMF237_USB_INT_STATE_RSTF      (1UL << 0)   /* ���߸�λ���� */
#define  AMHW_ZMF237_USB_INT_STATE_SUSPENDF  (1UL << 1)   /* ���߹��� */
#define  AMHW_ZMF237_USB_INT_STATE_RESUMF    (1UL << 2)   /* ���߻��� */
#define  AMHW_ZMF237_USB_INT_STATE_SOFF      (1UL << 3)   /* ��⵽SOF */
#define  AMHW_ZMF237_USB_INT_STATE_EPINTF    (1UL << 4)   /* �˵��ж� */
#define  AMHW_ZMF237_USB_INT_STATE_ALL        0X0F
/**
 *  \brief usb�ж�״̬�Ĵ����������
 *
 *  \param[in] state  usb �ж�״̬�Ĵ���״̬λö��
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_int_state_clear (amhw_zmf237_usbd_t *p_usb, uint16_t state)
{
    p_usb->int_state |= (state & AMHW_ZMF237_USB_INT_STATE_ALL);
}

/**
 *  \brief ���usb�ж�״̬�Ĵ���״̬����
 *
 *  \return usb �ж�״̬�Ĵ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_int_state_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->int_state;
}

/************************  EP_INT_STATE Configuration  ************************/
#define  AMHW_ZMF237_EP_INT_STATE_EP0F        (1UL << 0)
#define  AMHW_ZMF237_EP_INT_STATE_EP1F        (1UL << 1)
#define  AMHW_ZMF237_EP_INT_STATE_EP2F        (1UL << 2)
#define  AMHW_ZMF237_EP_INT_STATE_EP3F        (1UL << 3)
#define  AMHW_ZMF237_EP_INT_STATE_EP4F        (1UL << 4)
#define  AMHW_ZMF237_EP_INT_STATE_EP_ALL       0X1F

/**
 *  \brief ���usb�˵��ж�״̬�Ĵ���״̬����
 *
 *  \return usb �ж�״̬�Ĵ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_ep_int_state_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->ep_int_state;
}

/**
 *  \brief ���usb�˵��ж�״̬
 *
 *  \param[in] ep Ҫ����Ķ˵�
 */
am_static_inline
uint16_t amhw_zmf237_usbd_ep_int_state_clear (amhw_zmf237_usbd_t *p_usb, uint16_t ep)
{
    return p_usb->ep_int_state |= ep;
}

/************************  EP0_INT_STATE Configuration  ***********************/
#define  AMHW_ZMF237_EP0_INT_STATE_SETUP          (1UL << 0)  /* ���յ�SETUP�� */
#define  AMHW_ZMF237_EP0_INT_STATE_END            (1UL << 1)  /* �˵㴫����� */
#define  AMHW_ZMF237_EP0_INT_STATE_IN_NACK        (1UL << 2)
#define  AMHW_ZMF237_EP0_INT_STATE_IN_ACK         (1UL << 3)
#define  AMHW_ZMF237_EP0_INT_STATE_IN_STALL       (1UL << 4)
#define  AMHW_ZMF237_EP0_INT_STATE_OUT_NACK       (1UL << 5)
#define  AMHW_ZMF237_EP0_INT_STATE_OUT_ACK        (1UL << 6)
#define  AMHW_ZMF237_EP0_INT_STATE_OUT_STALL      (1UL << 7)
#define  AMHW_ZMF237_EP0_INT_STATE_ALL             0XFF

/**
 *  \brief ���usb�˵�0�ж�״̬�Ĵ���״̬����
 *
 *  \return usb �ж�״̬�Ĵ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_ep0_int_state_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->ep0_int_state;
}

/**
 *  \brief usb�˵�0�ж�״̬�Ĵ����������
 *
 *  \param[in] state  usb �ж�״̬�Ĵ���״̬λ
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_ep0_int_state_clear (amhw_zmf237_usbd_t *p_usb, uint16_t state)
{
    p_usb->ep0_int_state |= state;
}

/************************  USB_INT_EN Configuration  ***********************/
#define AMHW_ZMF237_USB_INT_EN_RSTIE       (1ul << 0)  /* USB ���߸�λ�ж�ʹ��λ */
#define AMHW_ZMF237_USB_INT_EN_SUSPENDIE   (1ul << 1)  /* USB ���߹����ж�ʹ��λ */
#define AMHW_ZMF237_USB_INT_EN_RESUMIE     (1ul << 2)  /* �����ж�ʹ��λ */
#define AMHW_ZMF237_USB_INT_EN_SOFIE       (1ul << 3)  /* SOF ����ж�ʹ��λ */
#define AMHW_ZMF237_USB_INT_EN_EPIE        (1ul << 4)  /* �˵��ж�ʹ��λ */
#define AMHW_ZMF237_USB_INT_EN_ALL          0X1F

/**
 *  \brief ʹ��USB�ж�
 *
 *  \param[in] int_en               Ҫʹ�ܵ�USB�ж�
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_int_enable (amhw_zmf237_usbd_t *p_usb, uint16_t int_en)
{
    p_usb->int_en |= int_en;
}

/**
 *  \brief ����USB�ж�
 *
 *  \param[in] int_dis              Ҫ���ܵ�USB�ж�
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_int_disable (amhw_zmf237_usbd_t *p_usb, uint16_t int_dis)
{
    p_usb->int_en &= ~int_dis;
}

/**
 *  \brief ���usb�˵�0�ж�״̬�Ĵ���״̬����
 *
 *  \return usb �ж�״̬�Ĵ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_int_en_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->int_en;
}

/**************************  EP_INT_EN Configuration  ************************/
#define  AMHW_ZMF237_EP_INT_EN_EP0IE          (1UL << 0)
#define  AMHW_ZMF237_EP_INT_EN_EP1IE          (1UL << 1)
#define  AMHW_ZMF237_EP_INT_EN_EP2IE          (1UL << 2)
#define  AMHW_ZMF237_EP_INT_EN_EP3IE          (1UL << 3)
#define  AMHW_ZMF237_EP_INT_EN_EP4IE          (1UL << 4)
#define  AMHW_ZMF237_EP_INT_EN_ALL             0X1F

/**
 *  \brief ���usb�˵��ж�ʹ�ܼĴ���״̬
 *
 *  \return usb �˵��ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_ep_int_en_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->ep_int_en;
}

/**
 *  \brief usb�˵��ж�ʹ��
 *
 *  \brief epx  Ҫʹ�ܵĶ˵�
 */
am_static_inline
void amhw_zmf237_usbd_ep_int_enable (amhw_zmf237_usbd_t *p_usb, uint16_t epx)
{
    p_usb->ep_int_en |= epx;
}

/**
 *  \brief usb�˵��жϽ���
 *
 *  \brief epx  Ҫ���ܵĶ˵�
 */
am_static_inline
void amhw_zmf237_usbd_ep_int_disable (amhw_zmf237_usbd_t *p_usb, uint16_t epx)
{
    p_usb->ep_int_en &= ~epx;
}

/**************************  EP0_INT_EN Configuration  ************************/
#define  AMHW_ZMF237_EP0_INT_EN_SETUPIE        (1UL << 0) /* ���յ� SETUP �� */
#define  AMHW_ZMF237_EP0_INT_EN_ENDIE          (1UL << 1) /* ������� */
#define  AMHW_ZMF237_EP0_INT_EN_IN_NACKIE      (1UL << 2) /* IN ��Ӧ�� NACK */
#define  AMHW_ZMF237_EP0_INT_EN_IN_ACKIE       (1UL << 3) /* IN ��Ӧ�� ACK */
#define  AMHW_ZMF237_EP0_INT_EN_IN_STALLIE     (1UL << 4) /* IN ��Ӧ�� STALL */
#define  AMHW_ZMF237_EP0_INT_EN_OUT_NACKIE     (1UL << 5) /* OUT ��Ӧ�� NACK */
#define  AMHW_ZMF237_EP0_INT_EN_OUT_ACKIE      (1UL << 6) /* OUT ��Ӧ�� ACK */
#define  AMHW_ZMF237_EP0_INT_EN_OUT_STALLIE    (1UL << 7) /* OUT ��Ӧ�� STALL */
#define  AMHW_ZMF237_EP0_INT_EN_ALL            0XFF

/**
 *  \brief ���usb�˵�0�ж�ʹ�ܼĴ���״̬
 *
 *  \return usb �˵�0�ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_ep0_int_en_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->ep0_int_en;
}

/**
 *  \brief ���usb�˵�0�ж�ʹ��
 *
 *  \param   enable  Ҫʹ�ܵ��ж�����
 */
am_static_inline
void amhw_zmf237_usbd_ep0_int_enable (amhw_zmf237_usbd_t *p_usb, uint16_t enable)
{
    p_usb->ep0_int_en |= enable;
}

/**
 *  \brief ���usb�˵�0�жϽ���
 *
 *  \param   disable  Ҫ���ܵ��ж�����
 */
am_static_inline
void amhw_zmf237_usbd_ep0_int_disable (amhw_zmf237_usbd_t *p_usb, uint16_t disable)
{
    p_usb->ep0_int_en &= ~disable;
}

/*************************  EPX_INT_STATE Configuration  **********************/
#define  AMHW_ZMF237_EPX_INT_STATE_ENDIE       (1UL << 1) /* ������� */
#define  AMHW_ZMF237_EPX_INT_STATE_IN_NACKIE   (1UL << 2) /* IN ��Ӧ�� NACK */
#define  AMHW_ZMF237_EPX_INT_STATE_IN_ACKIE    (1UL << 3) /* IN ��Ӧ�� ACK */
#define  AMHW_ZMF237_EPX_INT_STATE_IN_STALLIE  (1UL << 4) /* IN ��Ӧ�� STALL */
#define  AMHW_ZMF237_EPX_INT_STATE_OUT_NACKIE  (1UL << 5) /* OUT ��Ӧ�� NACK */
#define  AMHW_ZMF237_EPX_INT_STATE_OUT_ACKIE   (1UL << 6) /* OUT ��Ӧ�� ACK */
#define  AMHW_ZMF237_EPX_INT_STATE_OUT_STALLIE (1UL << 7) /* OUT ��Ӧ�� STALL */
#define  AMHW_ZMF237_EPX_INT_STATE_ALL          0XFE

/**
 * \brief USB �˵�
 */
typedef enum {
    ZMF237_USB_EP1,
    ZMF237_USB_EP2,
    ZMF237_USB_EP3,
    ZMF237_USB_EP4
}zmf237_usb_epx_t;

/**
 *  \brief ���usb�˵�X�ж�״̬
 *
 *  \param[in] epx                  Ҫ��ȡ�Ķ˵�
 *
 *  \return usb �˵�X�ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_epx_int_state_get (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx_t epx)
{
    return p_usb->epx_int_state_arr[epx].epx_int_state;
}

/**
 *  \brief usb�˵�X�ж�״̬���
 *
 *  \param[in] epx                  Ҫ����Ķ˵�
 *  \param[in] clear                Ҫ�����λ��״̬��
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_epx_int_state_clear (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx_t epx,
                                      uint16_t clear)
{
    p_usb->epx_int_state_arr[epx].epx_int_state |= clear;
}

/**************************  EPX_INT_EN Configuration  ************************/
#define  AMHW_ZMF237_EPX_INT_EN_ENDIE       (1UL << 1) /* ������� */
#define  AMHW_ZMF237_EPX_INT_EN_IN_NACKIE   (1UL << 2) /* IN ��Ӧ�� NACK */
#define  AMHW_ZMF237_EPX_INT_EN_IN_ACKIE    (1UL << 3) /* IN ��Ӧ�� ACK */
#define  AMHW_ZMF237_EPX_INT_EN_IN_STALLIE  (1UL << 4) /* IN ��Ӧ�� STALL */
#define  AMHW_ZMF237_EPX_INT_EN_OUT_NACKIE  (1UL << 5) /* OUT ��Ӧ�� NACK */
#define  AMHW_ZMF237_EPX_INT_EN_OUT_ACKIE   (1UL << 6) /* OUT ��Ӧ�� ACK */
#define  AMHW_ZMF237_EPX_INT_EN_OUT_STALLIE (1UL << 7) /* OUT ��Ӧ�� STALL */
#define  AMHW_ZMF237_EPX_INT_EN_ALL          0XFE

/**
 *  \brief ���usb�˵�X�ж�ʹ�ܼĴ���״̬
 *
 *  \param[in] epx                  Ҫ��ȡ�Ķ˵�
 *
 *  \return usb �˵�X�ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_epx_int_en_get (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx_t epx)
{
    return p_usb->epx_int_en_arr[epx].epx_int_en;
}

/**
 *  \brief usb�˵�X�ж�ʹ��
 *
 *  \param[in] epx                  �˵�
 *  \param[in] enable               Ҫʹ�ܵ�λ
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_epx_int_enable (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx_t epx,
                                 uint16_t enable)
{
    p_usb->epx_int_en_arr[epx].epx_int_en |= enable;
}

/**
 *  \brief usb�˵�X�жϽ���
 *
 *  \param[in] epx                  �˵�
 *  \param[in] disable              Ҫ���ܵ�λ
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_epx_int_disable (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx_t epx,
                                       uint16_t disable)
{
    p_usb->epx_int_en_arr[epx].epx_int_en &= ~disable;
}

/***************************  USB_ADDR Configuration  *************************/
#define AMHW_ZMF237_USBD_ADDR_MASK     0X7F
/**
 *  \brief ����USB�ĵ�ַ
 *
 *  \param[in] addr                 Ҫ���õĵ�ַ
 *
 *  \return usb �˵�X�ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_addr_set (amhw_zmf237_usbd_t *p_usb, uint8_t addr)
{
    return p_usb->addr = (addr & AMHW_ZMF237_USBD_ADDR_MASK);
}

/**
 *  \brief ���USB�ĵ�ַ
 *
 *  \return usb USB��ַ
 */
am_static_inline
uint16_t amhw_zmf237_usbd_addr_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->addr;
}

/******************************  EP_EN Configuration  *************************/
#define  AMHW_ZMF237_USB_EP0EN       (1UL << 0)
#define  AMHW_ZMF237_USB_EP1EN       (1UL << 1)
#define  AMHW_ZMF237_USB_EP2EN       (1UL << 2)
#define  AMHW_ZMF237_USB_EP3EN       (1UL << 3)
#define  AMHW_ZMF237_USB_EP4EN       (1UL << 4)
#define  AMHW_ZMF237_USB_EP_ALL       0X1F

/**
 *  \brief ���USB�˵�ʹ�ܼĴ���״̬
 *
 *  \return usb USB�˵�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_ep_en_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->ep_en;
}

/**
 *  \brief usb�˵�ʹ��
 *
 *  \param[in] enable               Ҫʹ�ܵĶ˵�
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_ep_enable (amhw_zmf237_usbd_t *p_usb, uint16_t enable)
{
    p_usb->ep_en |= enable;
}

/**
 *  \brief usb�˵����
 *
 *  \param[in] disable              Ҫ���ܵĶ˵�
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_ep_disable (amhw_zmf237_usbd_t *p_usb, uint16_t disable)
{
    p_usb->ep_en &= ~disable;
}

/****************************  TOG_CTRL Configuration  ************************/
/**< \brief �˵����ݷ�ת */
#define  AMHW_ZMF237_USB_DTOG_MASK    0X55
#define  AMHW_ZMF237_USB_DTOG1       (1UL << 0)
#define  AMHW_ZMF237_USB_DTOG2       (1UL << 2)
#define  AMHW_ZMF237_USB_DTOG3       (1UL << 4)
#define  AMHW_ZMF237_USB_DTOG4       (1UL << 6)

/**< \brief �˵����ݷ�תʹ��λ */
#define  AMHW_ZMF237_USB_DTOGEN_MASK  0XAA
#define  AMHW_ZMF237_USB_DTOG1EN     (1UL << 1)
#define  AMHW_ZMF237_USB_DTOG2EN     (1UL << 3)
#define  AMHW_ZMF237_USB_DTOG3EN     (1UL << 5)
#define  AMHW_ZMF237_USB_DTOG4EN     (1UL << 7)

/**
 *  \brief ����USB�˵�������ΪDATA0
 *
 *  \param[in] ep  Ҫ���õĶ˵��
 *
 *  \note �˵�Ų��ɰ�λ�򣬶˵�ŷ�ΧΪ1~4����˵�1~4
 */
am_static_inline
void amhw_zmf237_usbd_dtog_data0 (amhw_zmf237_usbd_t *p_usb, uint16_t ep)
{
    if (ep >= 1 && ep <= 4) {
        p_usb->tog_crl1_4 &=  ~(1 << ((ep - 1) * 2));
    }
}

/**
 *  \brief ����USB�˵�������ΪDATA1
 *
 *  \param[in] ep   Ҫ���õĶ˵�ţ����ɰ�λ��
 *
 *  \note �˵�Ų��ɰ�λ�򣬶˵�ŷ�ΧΪ1~4����˵�1~4
 */
am_static_inline
void amhw_zmf237_usbd_dtog_data1 (amhw_zmf237_usbd_t *p_usb, uint16_t ep)
{
    if (ep >= 1 && ep <= 4) {
        p_usb->tog_crl1_4 |=  (1 << ((ep - 1) * 2));
    }
}

/**
 *  \brief ���USB�˵����ݷ�ת״̬
 *
 *  \return usb USB�˵����ݷ�תʹ��״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_dtog_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->tog_crl1_4 & AMHW_ZMF237_USB_DTOG_MASK;
}

/**
 *  \brief usb�˵����ݷ�תʹ��
 *
 *  \param[in] ep     Ҫʹ�ܷ�ת�Ķ˵�
 *
 *  \note �˵�Ų��ɰ�λ�򣬶˵�ŷ�ΧΪ1~4����˵�1~4
 */
am_static_inline
void amhw_zmf237_usbd_dtog_enable (amhw_zmf237_usbd_t *p_usb, uint16_t ep)
{
    if (ep >= 1 && ep <= 4) {
        p_usb->tog_crl1_4 |=  (1 << ((ep - 1) * 2 + 1));
    }
}

/**
 *  \brief usb�˵����ݷ�ת����
 *
 *  \param[in] ep   Ҫ���ܷ�ת�Ķ˵�
 *
 *  \note �˵�Ų��ɰ�λ�򣬶˵�ŷ�ΧΪ1~4����˵�1~4
 */
am_static_inline
void amhw_zmf237_usbd_dtog_disable (amhw_zmf237_usbd_t *p_usb, uint16_t ep)
{
    if (ep >= 1 && ep <= 4) {
        p_usb->tog_crl1_4 &=  ~(1 << ((ep - 1) * 2 + 1));
    }
}

/*****************************  SETUPX Configuration  *************************/
/**
 *  \brief ��ȡUSB���ݰ����ݣ��������
 *
 *  \param[out] p_data              USB���ݰ��е�����
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_setupdata_get (amhw_zmf237_usbd_t *p_usb, uint8_t *p_data)
{
    int i = 0;

    for (i = 0; i < 8; i++) {
        p_data[i] = p_usb->stupx_arr[i].stupx;
    }
}

/**************************  PACKET_SIZE Configuration  ***********************/

/**
 *  \brief ����USB������Ĵ�С
 *
 *  \param[in] size                 USB������Ĵ�С
 *
 *  \return ��
 *
 *  \note ����������64�ֽ�
 */
am_static_inline
void amhw_zmf237_usbd_packet_size_set (amhw_zmf237_usbd_t *p_usb, uint8_t size)
{
    if (size > 64)
        size = 64;

    p_usb->packet_size = size;
}

/**
 *  \brief ��ȡUSB������Ĵ�С
 *
 *  \return USB������Ĵ�С
 */
am_static_inline
uint8_t amhw_zmf237_usbd_packet_size_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->packet_size;
}

/***************************  EPX_AVAIL Configuration  ************************/
/**
 * \brief USB �˵�
 */
typedef enum {
    ZMF237_USB_EPX0,
    ZMF237_USB_EPX1,
    ZMF237_USB_EPX2,
    ZMF237_USB_EPX3,
    ZMF237_USB_EPX4
}zmf237_usb_epx2_t;  /* ��ZMF237_USB_epx_t ���� */

/**
 *  \brief ���USB�˵�X FIFO��Ч���ݸ���
 *
 *  \return USB�˵�X FIFO��Ч���ݸ���
 */
am_static_inline
uint8_t amhw_zmf237_usbd_epx_avail_size_get (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx2_t epx)
{
    return p_usb->epx_avail_arr[epx].epx_avai;
}

/****************************  EPX_CTRL Configuration  ************************/
#define AMHW_ZMF237_USB_EPX_TRANCOUNT_MASK    0X7F

#define AMHW_ZMF237_USB_EPX_TRANEN    (1 << 7)    /* ʹ�ܴ��� */

/**
 *  \brief ���ö˵�X�����ݴ����������������
 *
 *  \param[in] epx                  Ҫ���д���Ķ˵�
 *  \param[in] count                Ҫ��������ݸ���
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_epx_transfer (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx2_t epx,
                                   uint8_t count)
{
    p_usb->epx_ctrl_arr[epx].epx_ctrl = AMHW_ZMF237_USB_EPX_TRANEN | count;
}

/**
 *  \brief �ж϶˵�X��USB�����Ƿ������
 *
 *  \param[in] epx                  Ҫ���д���Ķ˵�
 *
 *  \return ������ɷ���1��δ��ɷ���0
 */
am_static_inline
uint8_t amhw_zmf237_usbd_transfer_end(amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx2_t epx)
{
    if (p_usb->epx_ctrl_arr[epx].epx_ctrl & AMHW_ZMF237_USB_EPX_TRANEN)
        return 0;
    return 1;
}

/****************************  EPX_FIFO Configuration  ************************/
/**
 *  \brief ��USB�˵�X��fifo��д������
 *
 *  \param[in] epx                  Ҫ���õĶ˵�
 *  \param[in] data                 Ҫд�������
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_epx_fifo_write (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx2_t epx,
                                     uint8_t data)
{
    p_usb->epx_fifo_arr[epx].epx_fifo = data;
}

/**
 *  \brief ��USB�˵�X��fifo�ж�������
 *
 *  \param[in] epx                  Ҫ���õĶ˵�
 *
 *  \return fifo�е�����
 */
am_static_inline
uint8_t amhw_zmf237_usbd_epx_fifo_read (amhw_zmf237_usbd_t *p_usb, zmf237_usb_epx2_t epx)
{
    return p_usb->epx_fifo_arr[epx].epx_fifo;
}

/*****************************  EP_DMA Configuration  *************************/
/**< \brief �˵�DMAʹ��λ��ֻ֧�ֶ˵�1�Ͷ˵�2�� */
#define  AMHW_ZMF237_USB_DMA1EN     (1UL << 0)
#define  AMHW_ZMF237_USB_DMA2EN     (1UL << 1)

/**
 *  \brief ʹ�ܶ˵�DMA
 *
 *  \param[in] dma_epx              Ҫʹ��DMA�Ķ˵�
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_ep_dma_enable (amhw_zmf237_usbd_t *p_usb, uint16_t dma_epx)
{
    p_usb->ep_dma |= dma_epx;
}

/**
 *  \brief ���ܶ˵�DMA
 *
 *  \param[in] dma_epx              Ҫ����DMA�Ķ˵�
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_ep_dma_disable (amhw_zmf237_usbd_t *p_usb, uint16_t dma_epx)
{
    p_usb->ep_dma &= ~dma_epx;
}

/**
 *  \brief ��ȡ�˵�DMA��ʹ��״̬
 *
 *  \return ��
 */
am_static_inline
uint8_t amhw_zmf237_usbd_ep_dma_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->ep_dma;
}

/*****************************  EP_HALT Configuration  ************************/
/**< \brief �˵���ͣλ */
/**< \brief ����λ��Ϊ��1�����豸���� IN/OUT ������Զ���Ӧ STALL�������յ����ư�ʱ��λ�ᱻӲ���Զ����� */
#define  AMHW_ZMF237_USB_EP_HALT0     (1UL << 0)
#define  AMHW_ZMF237_USB_EP_HALT1     (1UL << 1)
#define  AMHW_ZMF237_USB_EP_HALT2     (1UL << 2)
#define  AMHW_ZMF237_USB_EP_HALT3     (1UL << 3)
#define  AMHW_ZMF237_USB_EP_HALT4     (1UL << 4)
#define  AMHW_ZMF237_USB_EP_HALT_ALL   0X1F

/**
 *  \brief ���ö˵���ͣ
 *
 *  \param[in] halt                 Ҫ��ͣ��λ
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_ep_halt_set (amhw_zmf237_usbd_t *p_usb, uint16_t halt)
{
    p_usb->ep_halt |= halt;
}

/**
 *  \brief ����˵���ͣ������ͣ��
 *
 *  \param[in] halt   Ҫ�������ͣλ
 *
 *  \return ��
 */
am_static_inline
void amhw_zmf237_usbd_ep_halt_reset (amhw_zmf237_usbd_t *p_usb, uint16_t halt)
{
    p_usb->ep_halt &= ~halt;
}

/**
 *  \brief ��ȡ�˵���ͣ״̬
 *
 *  \return �˵���ͣ״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_ep_halt_get (amhw_zmf237_usbd_t *p_usb)
{
    return p_usb->ep_halt;
}

/*****************************  USB_POWER Configuration  **********************/
#define  AMHW_ZMF237_USB_POWER_SUSPEN     (1UL << 0)
#define  AMHW_ZMF237_USB_POWER_SUSP       (1UL << 1)
#define  AMHW_ZMF237_USB_POWER_WKUP       (1UL << 3)

/**< \brief ������ƺ� */
/**< \brief ����ʹ�ܹ���� */
#define  AMHW_ZMF237_USB_SUSPDIS    0         /**< \brief �ɿ����������Ƿ���� */
#define  AMHW_ZMF237_USB_SUSPEN    (1 << 0)   /**< \brief ���ݹ���ģʽ��λ����꣩�����Ƿ���� */

/**< \brief λ����� */
#define  AMHW_ZMF237_USB_SUSP       0         /**< \brief ����ģʽ */
#define  AMHW_ZMF237_USB_NORMAL    (1 << 1)   /**< \brief ��������ģʽ */

/**
 *  \brief ����USB����״̬
 *
 *  \param[in] susp �����ֵӦ����һ�� λ����� �� һ������ʹ�ܹ�������
 *
 *  \retval ����1��ʾ������������������ģʽ������0��ʾ���������ڹ���ģʽ
 */
am_static_inline
void amhw_zmf237_usbd_susp_set (amhw_zmf237_usbd_t *p_usb, uint16_t susp)
{
    p_usb->power |= (susp & (~AMHW_ZMF237_USB_POWER_WKUP));
}

/**
 *  \brief ��ȡUSB����״̬
 *
 *  \retval ���ص����ݰ��������Ƿ�ʹ���Լ�����״̬
 */
am_static_inline
uint16_t amhw_zmf237_usbd_susp_get (amhw_zmf237_usbd_t *p_usb)
{
    return (p_usb->power & ~AMHW_ZMF237_USB_POWER_WKUP);
}

/**
 *  \brief ���������ӹ���״̬����
 */
am_static_inline
void amhw_zmf237_usbd_wakeup (amhw_zmf237_usbd_t *p_usb)
{
    p_usb->power |= AMHW_ZMF237_USB_POWER_WKUP;
}
/**
 * @}if_ZMF237_USBd
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZMF237_USBD_H */

/* end of file */

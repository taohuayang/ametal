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
 * \brief  XmodemЭ�� ����
 *
 * \internal
 * \par Modification History
 * - 1.00 18-8-31 , xgg, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "string.h"
#include "am_types.h"
#include "am_xmodem.h"

/*******************************************************************************
local defined
*******************************************************************************/
/* �ļ��������*/
#define __AM_XMODEM_DOC_EOT     0x51

/* �ļ������ź��ѷ��Ͳ�Ӧ��*/
#define __AM_XMODEM_EOT_ACK     0x52

/* ����λΪ128�ֽڹ���ģʽ�������ʼλ */
#define __AM_XMODEM_SOH         0x01

/* ����λΪ1K�ֽڹ���ģʽ�������ʼλ*/
#define __AM_XMODEM_STX         0x02

/* �ļ�������ϵĽ����ź� */
#define __AM_XMODEM_EOT         0x04

/* ������� */
#define __AM_XMODEM_CTRLZ       0x1A

/* ���ڻ�ȡ�����ַ��ر�״̬*/
#define __AM_XMODEM_CHAR_DOWN   0x00

/* ���ڻ�ȡ�����ַ���״̬*/
#define __AM_XMODEM_CHAR_UP     0x01

/* Xmodem�Ѿ���������*/
#define __AM_XMODEM_CON_UP      0x02

/* Xmodemδ��������*/
#define __AM_XMODEM_CON_DOWN    0x03

/* ���ڷ�������*/
#define __AM_XMODEM_DATA_TX     0x04

/* ���ڷ��ʹ����־*/
#define __AM_XMODEM_FLAG_TX     0x05

/* ��ֹ��ȡ�����ַ�*/
#define __AM_XMODEM_STOP_TX     0x06

/* Xmodem���;���*/
#define __AM_XMODEM_TX_READY    0x00

/* Xmodem��������*/
#define __AM_XMODEM_TX_START    0x01
/******************************************************************************/
/** \brief ֡ͷ���ܺ���*/
am_local am_bool_t am_xmodem_rec_frames (am_xmodem_rec_dev_t *p_dev,
                                         char                 inchar);

/** \brief ��ʼ���ܺ���*/
am_local void  __xmodem_rx_startup (am_xmodem_rec_dev_t  *p_dev);

/******************************************************************************/
/**
 * \brief ���ͷ�����ȡ�����ͺ���
 */
am_local void __xmodem_rec_can (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    p_dev->rx_bytes = -AM_DATA_CAN;
    /* �ص�֪ͨ�û� ���ͷ�����ȡ������*/
    p_dev->pfn_rx_callback(p_dev->p_arg,
                           p_dev->p_rec_devinfo->frames_info,
                           p_dev->rx_bytes);
}

/******************************************************************************/
/**
 * \brief ���շ������жϺ���
 */
am_local int __xmodem_data_check(am_xmodem_rec_dev_t *p_dev)
{
    int       i;
    char      cks = 0;
    uint32_t  crc;
    uint16_t  tcrc;
    if (p_dev->p_rec_devinfo->parity_mode == AM_XMODEM_CRC_MODE)
    {
        am_crc_cal(p_dev->crc_handle,
                   (uint8_t *)p_dev->p_rec_devinfo->frames_info,
                   p_dev->p_rec_devinfo->frames_bytes);
        am_crc_final(p_dev->crc_handle, &crc);
        tcrc = p_dev->fra_crc_pry;
        /* ���Լ������У����ʹ���õ���У������бȽ�*/
        if ((uint16_t)crc == tcrc) {
            return AM_TRUE;
        }
    }
    else
    {
        /* �������ۼ����*/
        for (i = 0; i < p_dev->p_rec_devinfo->frames_bytes; i++)
        {
            cks += p_dev->p_rec_devinfo->frames_info[i];
        }
        /* �����м�����ۼӺ��봫��������ۼӺͽ��бȽ�*/
        if (cks == p_dev->fra_sum_parity)
            return AM_TRUE;
    }
    return AM_FALSE;
}

/******************************************************************************/
/**
 * \brief ���յ�EOT��������
 */
am_local am_bool_t __xmodem_rec_eot (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    /* �����ַ���ȡ�ɹ�*/
    p_dev->char_get_state = __AM_XMODEM_CHAR_UP;

    /* ���ܵ������ַ����Ӧ���ͷ� */
    p_dev->p_rec_devinfo->frames_info[0] = AM_XMODEM_ACK;

    /* ʹ���ж�*/
    am_uart_tx_startup(p_dev->uart_handle);

    /* ���ͳɹ�*/
    p_dev->rx_bytes = -AM_DATA_SUC;

    /* �ص�֪ͨ�û� �������*/
    p_dev->pfn_rx_callback(p_dev->p_arg,
                           p_dev->p_rec_devinfo->frames_info,
                           p_dev->rx_bytes);

    return AM_TRUE;
}

/******************************************************************************/
/**
 * \brief SUMУ�麯��
 */
am_local am_bool_t __xmodem_rec_sum (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    p_dev->fra_sum_parity = inchar;
    if (AM_TRUE == __xmodem_data_check(p_dev))
       {
          if (p_dev->pfn_rx_callback != NULL) {
              p_dev->frames_num++;
              p_dev->pfn_rx_callback(p_dev->p_arg,
                                     p_dev->p_rec_devinfo->frames_info,
                                     p_dev->rx_bytes);
              p_dev->rx_bytes = 0;

              return AM_TRUE;
          }
       }
    return AM_FALSE;
}

/******************************************************************************/
/**
 * \brief CRCУ�麯��
 */
am_local am_bool_t __xmodem__rec_crc (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    uint8_t u_inchar = (uint8_t)inchar;

    if (p_dev->rx_bytes == p_dev->p_rec_devinfo->frames_bytes) {
        p_dev->fra_crc_pry |= (u_inchar << 8);
        p_dev->rx_bytes ++;
        return AM_TRUE;
    }

    if (p_dev->rx_bytes == p_dev->p_rec_devinfo->frames_bytes + 1) {
        p_dev->fra_crc_pry |= u_inchar;
        p_dev->rx_bytes--;
        if (AM_TRUE == __xmodem_data_check(p_dev)) {
            p_dev->pfn_rx_callback(p_dev->p_arg,
                                   p_dev->p_rec_devinfo->frames_info,
                                   p_dev->p_rec_devinfo->frames_bytes);
            p_dev->rx_bytes = 0;
            p_dev->frames_num++;
            p_dev->fra_crc_pry = 0;
            return AM_TRUE;
        }
    }

    return AM_FALSE;
}

/*******************************************************************************
      ״̬������
*******************************************************************************/
/**
 * \brief ���ݶα��溯��
 */
am_local am_bool_t __xmodem_rec_data_rec (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    /* ���ݽ���*/
    if (p_dev->rx_bytes < p_dev->p_rec_devinfo->frames_bytes) {
        p_dev->p_rec_devinfo->frames_info[p_dev->rx_bytes] = inchar;
        p_dev->rx_bytes++;
        return AM_TRUE;
    }
    /* ���ݽ�����ϣ�����sumУ����*/
    if (AM_XMODEM_SUM_MODE == p_dev->p_rec_devinfo->parity_mode) {
        return __xmodem_rec_sum(p_dev, inchar);

    }
    /* ���ݽ�����ϣ�����crcУ����*/
    if (AM_XMODEM_CRC_MODE == p_dev->p_rec_devinfo->parity_mode) {
        return __xmodem__rec_crc(p_dev, inchar);
    }
    return AM_FALSE;
}

/**
 * \brief ���кŷ����ж�
 */
am_local am_bool_t __xmodem_rec_rad (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    if (inchar == ~ (char)p_dev->frames_num) {
        /* ���ĵ���һ������״̬*/
        p_dev->p_rec_func = (pfn_xmodem_rx_t)__xmodem_rec_data_rec;
        return AM_TRUE;
    }

    return AM_FALSE;
}

/**
 * \brief ���кŽ��ܺ���
 */
am_local am_bool_t __xmodem_rec_pack (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    if (p_dev->frames_num != (uint8_t)inchar) {
        return AM_FALSE;
    }
    p_dev->p_rec_func = (pfn_xmodem_rx_t)__xmodem_rec_rad;

    return AM_TRUE;
}

/**
 * \brief ״̬����ʼ���亯��
 */
am_local am_bool_t am_xmodem_rec_frames (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    if ((uint8_t)inchar == __AM_XMODEM_SOH ||
        (uint8_t)inchar == __AM_XMODEM_STX) {

        p_dev->con_state = __AM_XMODEM_CON_UP;

        p_dev->p_rec_func = (pfn_xmodem_rx_t)__xmodem_rec_pack;

        return AM_TRUE;
    }
    return AM_FALSE;
}

/*****************************************************************************/
/**
 * \brief ���½�����һ֡����
 */
am_local void __xmodem_rx_nak_set (am_xmodem_rec_dev_t  *p_dev)
{
    /* �����ط����� */
    ++p_dev->nak_state;

    /* �ж��Ƿ�ﵽ����ط�����*/
    if (p_dev->nak_state == p_dev->p_rec_devinfo->nak_max_times) {
        /* Ҫ�����������ط���� */
        p_dev->nak_state = AM_OK;
        p_dev->rx_bytes  = -AM_EBADMSG;
        /* δ�ܽ��ܵ���ȷ�����ݣ������û��ص�����֪ͨ�û����ݴ��� */
        p_dev->pfn_rx_callback(p_dev->p_arg,
                               p_dev->p_rec_devinfo->frames_info,
                               p_dev->rx_bytes);
        return;
    }
    p_dev->p_rec_func     = (pfn_xmodem_rx_t)am_xmodem_rec_frames;
    p_dev->char_get_state = __AM_XMODEM_CHAR_UP;
    /* ���ͷ�����NAK�ط��ź�*/
    p_dev->p_rec_devinfo->frames_info[0] = AM_XMODEM_NAK;

    am_uart_tx_startup(p_dev->uart_handle);
}

/******************************************************************************/
/**
 * \brief ȡ�����ͺ���
 */
am_err_t am_xmodem_rec_can_set (am_xmodem_rec_handle_t handle)
{
   uint8_t i = 0;

   if (handle == NULL) {
      return -AM_EINVAL;
   }

   /* ����Xmodem����״̬������*/
   handle->p_rec_func = (pfn_xmodem_rx_t)am_xmodem_rec_frames;

   /* ȡ����������������η�ֹ���ͷ�δ�ܽӵ�*/
   for (i = 0; i < 3; i++) {
      /* ���淢�͵�ȡ����־*/
      handle->p_rec_devinfo->frames_info[0] = AM_XMODEM_CAN;
      handle->char_get_state = __AM_XMODEM_CHAR_UP;
      /* ���������ж� */
      am_uart_tx_startup(handle->uart_handle);
      while(handle->char_get_state == __AM_XMODEM_CHAR_UP);
   }

   return AM_OK;
}

/******************************************************************************/
/**
 * \brief �������պ���
 */
am_err_t am_xmodem_rec_ack_set (am_xmodem_rec_handle_t handle)
{
    if (handle == NULL) {
       return -AM_EINVAL;
    }

    /* �����ط�����*/
    handle->nak_state      = 0;

    /* ��ǰXmodem�����Ѿ�����*/
    handle->con_state      = __AM_XMODEM_CON_UP;

    /* ���ý���״̬������*/
    handle->p_rec_func     = (pfn_xmodem_rx_t)am_xmodem_rec_frames;

    /* ��ǰΪ����״̬̬*/
    handle->char_get_state = __AM_XMODEM_CHAR_UP;

    /* ����ACKȷ���źţ� ��Ӧ���ͷ�������һ֡���� */
    handle->p_rec_devinfo->frames_info[0] = AM_XMODEM_ACK;

    /* ���������ж� */
    am_uart_tx_startup(handle->uart_handle);

    /* ��ʱ�ȴ�Xmodem��λ���Ļ�Ӧ*/
    am_softimer_start(&handle->rx_softimer, \
                       handle->p_rec_devinfo->rx_timeout);

    return AM_OK;
}

/******************************************************************************/
/**
 * \brief xmodem���ջص�����ע��
 */
am_err_t am_xmodem_rec_cb_reg (am_xmodem_rec_handle_t handle,
                                am_xmodem_user_rx_t   pfn_rec_cb,
                                void                 *p_arg)
{
    if (pfn_rec_cb == NULL || pfn_rec_cb == NULL) {
       return -AM_EINVAL;
    }

    handle->p_arg = p_arg;

    handle->pfn_rx_callback = pfn_rec_cb;

    return AM_OK;
}

/******************************************************************************/
/**
 * \brief �����ʱ���ص�����
 *
 * \param[in] p_arg ָ��XMODEM �豸�ṹ���ָ��
 *
 * \return ��
 */
am_local void __xmodem_rec_softimer_callback (void *p_arg)
{
    am_xmodem_rec_dev_t *p_dev = (am_xmodem_rec_dev_t *)p_arg;
    /* �ر������ʱ�� */
    am_softimer_stop(&p_dev->rx_softimer);
    //���δ�ܳ�ʱû�������ӣ�����������
    if (p_dev->con_state == __AM_XMODEM_CON_DOWN) {
        ++p_dev->nak_state;
        if (p_dev->nak_state == p_dev->p_rec_devinfo->nak_max_times) {
            p_dev->nak_state = 0;
            p_dev->pfn_rx_callback(p_dev->p_arg,
                                   p_dev->p_rec_devinfo->frames_info,
                                   -AM_XMODEM_DOWN);
            return;
        }
        am_xmodem_rec_start(p_dev);
        return;
    }
    /*������־λ����ʱδ���յ�����*/
    p_dev->rx_bytes = -AM_ETIME;
    if (p_dev->pfn_rx_callback != NULL) {
        p_dev->pfn_rx_callback(p_dev->p_arg,
                               p_dev->p_rec_devinfo->frames_info,
                               p_dev->rx_bytes);
    }
}

/******************************************************************************/
/**
 * \brief �ַ���ȡ����
 */
am_local int __xmodem_rec_getchar (am_xmodem_rec_dev_t  *p_dev, char *p_data)
{
    /* ����״̬ʱ��ֻ��������ĵ�һ���ֽ��е����� */
    if (p_dev->char_get_state == __AM_XMODEM_CHAR_UP) {

        /* ��ȡ��Ҫ���͵ĵ�һ���ַ�*/
       *p_data = p_dev->p_rec_devinfo->frames_info[0];
        /* ����һ�κ󣬽����������ȡ�����ַ�*/
        p_dev->char_get_state = __AM_XMODEM_CHAR_DOWN;

        return AM_TRUE;
    }
    return AM_OK;
}

/******************************************************************************/
/**
 * \brief Xmodem��ȡһ���ַ����ͺ���
 */
am_local int __xmodem_rec_txchar_get (void *p_arg, char *p_outchar)
{
    am_xmodem_rec_dev_t *p_dev = (am_xmodem_rec_dev_t *)p_arg;
    if (__xmodem_rec_getchar(p_dev, p_outchar) != AM_TRUE) {
        return -AM_EEMPTY;
    }
    return AM_OK;
}

/******************************************************************************/
/**
 * \brief ���ݴ���״̬����
 */
am_local am_bool_t __xmodem_rec_data_err (am_xmodem_rec_dev_t *p_dev,
                                          char                 inchar)
{
    int ret = 0;
    /* �жϴ�����Ϣ�������ͷ�����ȡ�����ͣ���ص�֪ͨ�û�*/
    if (inchar == AM_XMODEM_CAN) {
        p_dev->rx_bytes++;
        if (p_dev->rx_bytes > 2) {
            __xmodem_rec_can(p_dev, inchar);
        }
        return AM_TRUE;
    }
    if (inchar == __AM_XMODEM_EOT &&
        p_dev->p_rec_func == (pfn_xmodem_rx_t)am_xmodem_rec_frames) {

        return __xmodem_rec_eot(p_dev, inchar);
    }
    if (inchar == AM_XMODEM_ACK) {
        return AM_TRUE;
    }
    if (p_dev->rx_bytes == p_dev->p_rec_devinfo->frames_bytes) {
        ret = -AM_XMODEM_CHECK_ERR;
        if (p_dev->pfn_rx_callback != NULL) {
            p_dev->pfn_rx_callback(p_dev->p_arg,
                                   p_dev->p_rec_devinfo->frames_info,
                                   ret);
        }
        return AM_TRUE;
    } else if (p_dev->p_rec_func == (pfn_xmodem_rx_t)__xmodem_rec_data_rec) {
        __xmodem_rx_nak_set(p_dev);
        return AM_TRUE;
    }
    //����������ϴ��������κδ���ֱ�ӷ���
    return AM_FALSE;
}

/******************************************************************************/
/**
 * \brief Xmodem���ݽ��պ���
 */
am_local void __xmodem_rx_char (void *p_arg, char inchar)
{
    am_xmodem_rec_dev_t *p_dev = (am_xmodem_rec_dev_t *)p_arg;

    //��ȡ��ǰ״̬����
    pfn_xmodem_rx_t pfn_rx_func = (pfn_xmodem_rx_t)p_dev->p_rec_func;

    //��ʧ�������ݴ��������ط���ȡ��
    if (AM_FALSE == pfn_rx_func(p_dev, inchar)) {
        if (AM_TRUE == __xmodem_rec_data_err(p_dev, inchar)) {
            am_softimer_stop (&p_dev->rx_softimer);
        }
    }else {
        am_softimer_stop (&p_dev->rx_softimer);
    }
}

/******************************************************************************/
/**
 * \brief Xmodem��ʼ���պ���
 */
am_local void  __xmodem_rx_startup (am_xmodem_rec_dev_t  *p_dev)
{
    /* ���ݹ���ģʽ��ѡ���͸����ͷ����ַ�*/
    switch (p_dev->p_rec_devinfo->parity_mode) {
       /* ����ģʽΪ����λΪ128�ֽ�ʱ�������ַ�NAK*/
       case AM_XMODEM_SUM_MODE:
                 p_dev->p_rec_devinfo->frames_info[0] = AM_XMODEM_NAK;
                 break;
       /* ����ģʽΪ����λΪ1K�ֽ�ʱ�������ַ�C*/
       case AM_XMODEM_CRC_MODE:
                 p_dev->p_rec_devinfo->frames_info[0] = 'C';
                 break;
    }
    /* ���������ַ�*/
    p_dev->char_get_state = __AM_XMODEM_CHAR_UP;
    /* �򿪷����ж�*/
    am_uart_tx_startup(p_dev->uart_handle);
    /* �򿪶�ʱ��*/
    am_softimer_start(&p_dev->rx_softimer, p_dev->p_rec_devinfo->start_time);
}

/******************************************************************************/
/**
 * \brief Xmodem�ļ����պ���
 */
am_err_t am_xmodem_rec_start (am_xmodem_rec_handle_t handle)
{
    /* ��ʼ���� */
    if (handle != NULL) {
        __xmodem_rx_startup(handle);
        return AM_OK;
    }
    return -AM_EINVAL;
}

/******************************************************************************/
/**
 * \brief ����CRC-16
 */
static void __crc_16_pattern_set(am_crc_handle_t   crc_handle,
                                 am_crc_pattern_t *p_crc_pattern)
{
    /* ���� CRC-16 ģ�� */
    p_crc_pattern->width     = 16;       /* CRC ���(�磺CRC5 �Ŀ��Ϊ 5) */
    p_crc_pattern->poly      = 0x1021;   /* CRC ���ɶ���ʽ */
    p_crc_pattern->initvalue = 0x0000;   /* CRC ��ʼֵ */
    p_crc_pattern->refin     = AM_FALSE; /* �������������Ҫλ��ת�����ֵΪ TRUE */
    p_crc_pattern->refout    = AM_FALSE; /* ���������ֵ��Ҫλ��ת�����ֵΪ TRUE */
    p_crc_pattern->xorout    = 0x0000;   /* ������ֵ */

    /* ��ʼ��CRC*/
    am_crc_init(crc_handle, p_crc_pattern);
}

/**
 * \brief �����豸��ʼ������
 */
am_xmodem_rec_handle_t  am_xmodem_rec_init (
                            am_xmodem_rec_dev_t            *p_dev,
                            const am_xmodem_rec_dev_info_t *p_rec_devinfo,
                            am_uart_handle_t                uart_handle,
                            am_crc_handle_t                 crc_handle)
{
    if ((NULL == p_dev) || (NULL == p_rec_devinfo) || (NULL == uart_handle)) {
        return NULL;
    }
    p_dev->p_rec_devinfo = (am_xmodem_rec_dev_info_t *)p_rec_devinfo;
    /* ֡���кų�ʼֵΪ1*/
    p_dev->frames_num      = 1;
    /* ��ʼ���ۻ���У��λΪ0 */
    p_dev->fra_sum_parity  = 0;
    /* ��ʼ��CRCУ�� */
    p_dev->fra_crc_pry     = 0;
    /* ��ʼ���ص�����ΪNULL*/
    p_dev->pfn_rx_callback = NULL;
    /* ��ʼ����ǰ�����ֽ��� */
    p_dev->rx_bytes        = 0;
    /* ��ʼ����ǰ�ط�״̬Ϊ0 */
    p_dev->nak_state       = 0;
    /* Xmodem��ǰ����״̬*/
    p_dev->con_state       = __AM_XMODEM_CON_DOWN;
    /* ����Xmodem��Ҫ�Ĵ��ھ��*/
    p_dev->uart_handle     = uart_handle;
    /* �����׼CRC���*/
    p_dev->crc_handle      = crc_handle;
    /* �����ַ���ȡĬ��Ϊ0 */
    p_dev->char_get_state  = __AM_XMODEM_CHAR_DOWN;
    /** ״̬���������*/
    p_dev->p_rec_func      = (pfn_xmodem_rx_t)am_xmodem_rec_frames;

    __crc_16_pattern_set(crc_handle, &p_dev->crc_pattern);

    /* ʹ�ܴ����ж�ģʽ */
    am_uart_ioctl(p_dev->uart_handle,
                  AM_UART_MODE_SET,
                  (void *)AM_UART_MODE_INT);
    /* ע�ᷢ�ͻص����� */
    am_uart_callback_set(p_dev->uart_handle,
                         AM_UART_CALLBACK_TXCHAR_GET,
                         __xmodem_rec_txchar_get,
                         (void *)(p_dev));
    /* ע����ջص����� */
    am_uart_callback_set(p_dev->uart_handle,
                         AM_UART_CALLBACK_RXCHAR_PUT,
                         __xmodem_rx_char,
                         (void *)(p_dev));

    if (p_rec_devinfo->rx_timeout != 0) {
        if (am_softimer_init(&p_dev->rx_softimer,
                              __xmodem_rec_softimer_callback,
                              p_dev) != AM_OK) {
            return NULL;
        }
    }
    return (am_xmodem_rec_handle_t)(p_dev);
}

/********************************************************************************
Xmodem��������
********************************************************************************/

/**
 * \brief ��ȡ�ļ����ͽ����ַ�
 */
am_local void __xmodem_tx_eot (am_xmodem_tx_dev_t *p_dev,
                               uint8_t            *p_outchar)
{
     p_dev->tx_state = __AM_XMODEM_FLAG_TX;
    *p_outchar = __AM_XMODEM_EOT;
     p_dev->state_flag  = __AM_XMODEM_DOC_EOT;
}

/******************************************************************************/
/**
 * \brief �ļ����ͽ�������
 */
am_err_t am_xmodem_tx_over (am_xmodem_tx_handle_t handle)
{
    if (handle == NULL) {
       return -AM_EINVAL;
    }
    /* ������ȡ�ַ����ͱ�־λ*/
    handle->tx_state = __AM_XMODEM_FLAG_TX;
    /* ������ʱ��*/
    am_softimer_start(&handle->tx_softimer,
                       handle->p_tx_devinfo->tx_timeout);
    /* �л����ļ����ͽ���״̬*/
    handle->p_tx_func = (pfn_xmodem_tx_t)__xmodem_tx_eot;
    /* ���������ж� */
    am_uart_tx_startup(handle->uart_handle);
    /* ������ʱ��*/
    am_softimer_start(&handle->tx_softimer,
                       handle->p_tx_devinfo->tx_timeout);
    return AM_OK;
}

/******************************************************************************/
/**
 * \brief ��ȡȡ�����ͺ����ַ�
 */
am_local am_bool_t __xmodem_tx_can_get (am_xmodem_tx_handle_t handle,
                                        char                 *p_outchar)
{
    if (handle->tx_bytes < 3) {
        *p_outchar = AM_XMODEM_CAN;
         handle->tx_bytes++;
         return AM_TRUE;
    }
    handle->tx_bytes = 0;
    handle->tx_state = __AM_XMODEM_STOP_TX;
    return AM_FALSE;
}

/******************************************************************************/
/**
 * \brief �û�ȡ�����ͺ���
 */
am_err_t am_xmodem_tx_can_set (am_xmodem_tx_handle_t handle)
{
    if (handle == NULL) {
        return -AM_EINVAL;
    }
    handle->tx_bytes = 0;
    handle->tx_state = __AM_XMODEM_DATA_TX;
    /* �л�������ȡ�������ļ�״̬���������������ν���ȡ���ź�*/
    handle->p_tx_func = (pfn_xmodem_tx_t)__xmodem_tx_can_get;
    am_uart_tx_startup(handle->uart_handle);
    handle->state_flag = __AM_XMODEM_EOT_ACK;

    return AM_OK;
}

/******************************************************************************/
/**
 * \brief �ַ���ȡ����
 */
am_local int __xmodem_tx_getchar (am_xmodem_tx_dev_t  *p_dev, char *p_data)
{
    pfn_xmodem_tx_t pfn_tx_func = (pfn_xmodem_tx_t)p_dev->p_tx_func;
    if (p_dev->tx_state != __AM_XMODEM_STOP_TX) {
        pfn_tx_func(p_dev, p_data);
        if (p_dev->tx_state == __AM_XMODEM_FLAG_TX) {
            p_dev->tx_state = __AM_XMODEM_STOP_TX;
        }
        return AM_TRUE;
    }
    return AM_OK;
}

/******************************************************************************/
/**
 * \brief Xmodem����ģʽ��ȡһ���ַ����ͺ���
 */
am_local int __xmodem_tx_char_get (void *p_arg, char *p_outchar)
{
    am_xmodem_tx_dev_t *p_dev = (am_xmodem_tx_dev_t *)p_arg;
    if (__xmodem_tx_getchar(p_dev, p_outchar) != AM_TRUE) {
        return -AM_EEMPTY;
    }
    return AM_OK;
}

/******************************************************************************/
/**
 * \brief xmodem���ͻص�����ע��
 */
am_err_t am_xmodem_tx_cb_reg (am_xmodem_tx_handle_t handle,
                              am_xmodem_user_tx_t   pfn_tx_cb,
                              void                 *p_arg)
{
    if (pfn_tx_cb == NULL || pfn_tx_cb == NULL) {
       return -AM_EINVAL;
    }

    handle->p_arg           = p_arg;
    handle->pfn_tx_callback = pfn_tx_cb;

    return AM_OK;
}

/**
 * \brief ����CRCУ���뺯��
 */
am_local uint16_t __xmodem_tx_crc_set (am_xmodem_tx_dev_t *p_dev,
                                       char               *ptr,
                                       uint32_t            count)
{
    uint8_t  i           = 0;
    uint8_t  data        = 0x1A;
    uint32_t crc         = 0;
    uint32_t ctrlz_count = 0;

    //��׼CRC����
    am_crc_cal(p_dev->crc_handle,
               (uint8_t *)ptr,
               p_dev->doc_bytes);

    if (p_dev->doc_bytes < p_dev->frame_tx_bytes) {
        ctrlz_count = p_dev->frame_tx_bytes - p_dev->doc_bytes;
        for (i = 0; i < ctrlz_count; i++) {
            am_crc_cal(p_dev->crc_handle,
                       &data,
                       1);
        }
    }

    am_crc_final(p_dev->crc_handle, &crc);

    return (uint16_t)(crc);
}

/*******************************************************************************
״̬������
*******************************************************************************/
/**
 * \brief ����У���뺯��
 */
am_local void __xmodem_tx_frames_parity (am_xmodem_tx_dev_t *p_dev,
                                         char               *p_outchar)
{
    uint16_t crc_high = 0;
    /* ������ģʽΪ1K���ȡCRCУ����*/
    if (p_dev->frame_tx_bytes == 1024) {
        crc_high = __xmodem_tx_crc_set(p_dev,
                                       (char *)p_dev->p_tx_buf,
                                        p_dev->doc_bytes);
        if (p_dev->fra_crc_pry == crc_high >> 8) {
            p_dev->fra_crc_pry = crc_high;
            p_dev->tx_state = __AM_XMODEM_STOP_TX;
        } else {
            p_dev->fra_crc_pry = crc_high >> 8;
        }
       *p_outchar = p_dev->fra_crc_pry;
    }
    /* ������ģʽΪ128���ȡSUMУ����*/
    if (p_dev->frame_tx_bytes == 128) {
        int i;
        char cks = 0;
        /* �������ۼ����*/
        for (i = 0; i < p_dev->doc_bytes; i++)
        {
            cks += p_dev->p_tx_buf[i];
        }
        if (p_dev->ctrlz_num != 0) {
            for (i = 0; i < p_dev->ctrlz_num; i++) {
                cks += __AM_XMODEM_CTRLZ;
            }
            p_dev->ctrlz_num = 0;
        }
        p_dev->fra_sum_parity = cks;
       *p_outchar = p_dev->fra_sum_parity;
        p_dev->tx_state = __AM_XMODEM_STOP_TX;
    }
}

/******************************************************************************/
/**
 * \brief ���ݲ���һ֡��亯��
 */
am_local am_bool_t __xmodem_tx_ctrlz_set (am_xmodem_tx_dev_t *p_dev,
                                          char               *p_outchar)
{
   *p_outchar = __AM_XMODEM_CTRLZ;
    p_dev->tx_bytes++;
    if (p_dev->tx_bytes == p_dev->frame_tx_bytes) {
        p_dev->tx_bytes   = 0;
        p_dev->state_flag = AM_XMODEM_MOU_SUC;
        p_dev->p_tx_func  = (pfn_xmodem_tx_t)__xmodem_tx_frames_parity;
        return AM_TRUE;
     }
    return AM_FALSE;
}

/******************************************************************************/
/**
 * \brief �������ݶκ���
 */
am_local am_bool_t __xmodem_tx_frames_data (am_xmodem_tx_dev_t *p_dev,
                                            char               *p_outchar)
{
    if (p_dev->doc_bytes == p_dev->frame_tx_bytes) {
       *p_outchar = p_dev->p_tx_buf[p_dev->tx_bytes];
        p_dev->tx_bytes++;
        if (p_dev->tx_bytes == p_dev->frame_tx_bytes) {
            p_dev->tx_bytes  = 0;
            p_dev->p_tx_func = (pfn_xmodem_tx_t)__xmodem_tx_frames_parity;
        }
        return AM_TRUE;
    }
    if (p_dev->doc_bytes < p_dev->frame_tx_bytes ) {
        if (p_dev->tx_bytes < p_dev->doc_bytes) {
           *p_outchar = p_dev->p_tx_buf[p_dev->tx_bytes];
            p_dev->tx_bytes++;
            if (p_dev->tx_bytes == p_dev->doc_bytes) {
                p_dev->p_tx_func  = (pfn_xmodem_tx_t)__xmodem_tx_ctrlz_set;
            }
            return AM_TRUE;
        }
    }
    return AM_FALSE;
}

/******************************************************************************/
/**
 * \brief �������кŷ��뺯��
 */
am_local am_bool_t __xmodem_tx_frames_pack_rmoc (am_xmodem_tx_dev_t *p_dev,
                                                 char               *p_outchar)
{
    /* �жϷ��ͺ�����ȡ���кŷ���*/
   *p_outchar = ~p_dev->frames_num;

    /* �л������ݷ���״̬*/
    p_dev->p_tx_func = (pfn_xmodem_tx_t)__xmodem_tx_frames_data;

    return AM_TRUE;
}

/******************************************************************************/
/**
 * \brief �������кź���
 */
am_local am_bool_t  __xomdem_tx_frames_packetno (am_xmodem_tx_dev_t *p_dev,
                                                 char               *p_outchar)
{
    /* ���кż�1*/
    p_dev->frames_num++;

    /* �жϷ��ͺ�����ȡ���к�*/
   *p_outchar = p_dev->frames_num;

    /* �л�����ȡ���кŷ���״̬*/
    p_dev->p_tx_func = (pfn_xmodem_tx_t)__xmodem_tx_frames_pack_rmoc;

    return AM_TRUE;
}

/******************************************************************************/
/**
 * \brief ����֡ͷ����
 */
am_local am_bool_t __xmodem_tx_frames_head (am_xmodem_tx_dev_t *p_dev,
                                            char               *p_outchar)
{
    if (p_dev->frame_tx_bytes == 1024) {
       /* 1K����ģʽ��֡ͷΪSTX*/
       *p_outchar = __AM_XMODEM_STX;
    }
    if (p_dev->frame_tx_bytes == 128) {
        /* 128����ģʽ��֡ͷΪSOH*/
       *p_outchar = __AM_XMODEM_SOH;
    }
    /* �л������кŷ���״̬*/
    p_dev->p_tx_func = (pfn_xmodem_tx_t)__xomdem_tx_frames_packetno;

    return AM_TRUE;
}

/******************************************************************************/
/**
 * \brief ��ʼ���ͺ���
 */
am_err_t am_xmodem_tx_pack (am_xmodem_tx_handle_t handle,
                            char                 *p_doc,
                            uint32_t              pack_size)
{
    if (handle == NULL || p_doc == NULL) {
        return -AM_EINVAL;
    }
    if (handle->state_flag != __AM_XMODEM_TX_START) {
        handle->state_flag = __AM_XMODEM_TX_START;
    }
    if (pack_size < handle->frame_tx_bytes) {
        handle->ctrlz_num = handle->frame_tx_bytes - pack_size;
    }
    /* ��ȡ�����ļ���ָ��*/
    handle->p_tx_buf  = p_doc;
    /* һ�η��͵�ģ���С*/
    handle->doc_bytes = pack_size;
    /* �����ȡ�����ַ�*/
    handle->tx_state  = __AM_XMODEM_DATA_TX;
    /* �л���֡ͷ����״̬*/
    handle->p_tx_func = (pfn_xmodem_tx_t)__xmodem_tx_frames_head;
    /* �򿪷����ж�*/
    am_uart_tx_startup(handle->uart_handle);
    /* ������ʱ��*/
    am_softimer_start(&handle->tx_softimer,
                       handle->p_tx_devinfo->tx_timeout);
    return AM_OK;
}

/******************************************************************************/
am_local void __xmodem_tx_eot_ack_char (am_xmodem_tx_dev_t *p_dev,
                                        char               *p_outchar)
{
     *p_outchar = AM_XMODEM_ACK;
}

/******************************************************************************/
am_local int __xmodem_tx_eot_ack (am_xmodem_tx_dev_t *p_dev)
{
    if (p_dev == NULL) {
        return -AM_EINVAL;
    }
    p_dev->tx_state   = __AM_XMODEM_FLAG_TX;
    p_dev->state_flag = __AM_XMODEM_EOT_ACK;
    p_dev->p_tx_func  = (pfn_xmodem_tx_t)__xmodem_tx_eot_ack_char;
    am_uart_tx_startup(p_dev->uart_handle);
    return AM_TRUE;
}

/******************************************************************************/
/**
 * \brief ���շ�Ҫ���ط�����
 */
am_local void __xmodem_tx_nak (am_xmodem_tx_dev_t *p_dev)
{
    if (p_dev->nake_state < p_dev->p_tx_devinfo->nak_times_max) {
        p_dev->tx_bytes   = 0;
        p_dev->tx_state   = __AM_XMODEM_FLAG_TX;
        p_dev->frames_num = p_dev->frames_num - 1;
        p_dev->p_tx_func  = (pfn_xmodem_tx_t)__xmodem_tx_frames_head;
        am_uart_tx_startup(p_dev->uart_handle);
    }
    if (p_dev->nake_state == p_dev->p_tx_devinfo->nak_times_max) {
        am_xmodem_tx_can_set(p_dev);
        p_dev->nake_state = 0;
        /* ֪ͨ�û���ǰ���ݰ��ط������ﵽ�涨������ط�����, ���Ѿ�ȡ���˷���*/
        p_dev->pfn_tx_callback(p_dev->p_arg, AM_XMODEM_NAK_TIME);
    }
    p_dev->nake_state++;
}

/******************************************************************************/
/**
 * \brief Ӧ���ź��жϺ���
 */
am_local int __xmodem_tx_result_mode (am_xmodem_tx_dev_t *p_dev,
                                      char                inchar)
{
    if (p_dev->state_flag == __AM_XMODEM_TX_READY) {
        p_dev->state_flag = __AM_XMODEM_TX_START;
        if (inchar == AM_XMODEM_1k) {
            p_dev->frame_tx_bytes = 1024;
        }
        if (inchar == AM_XMODEM_NAK) {
            p_dev->frame_tx_bytes = 128;
        }
        if (p_dev->frame_tx_bytes == 128 || p_dev->frame_tx_bytes == 1024) {
           p_dev->tx_state = __AM_XMODEM_FLAG_TX;
           p_dev->pfn_tx_callback(p_dev->p_arg, inchar);
           return AM_TRUE;
        }
    }
    if (p_dev->state_flag == __AM_XMODEM_TX_START) {
        if (inchar == AM_XMODEM_ACK) {
            p_dev->pfn_tx_callback(p_dev->p_arg, inchar);
        }
        if (inchar == AM_XMODEM_NAK) {
            __xmodem_tx_nak(p_dev);
        }
        if (inchar == AM_XMODEM_CAN) {
           p_dev->pfn_tx_callback(p_dev->p_arg, inchar);
        }
        return AM_TRUE;
    }
    if (p_dev->state_flag == AM_XMODEM_MOU_SUC) {
        p_dev->pfn_tx_callback(p_dev->p_arg, AM_XMODEM_MOU_SUC);
    }
    return AM_FALSE;
}

/******************************************************************************/
/**
 * \brief ģ�鷢������߽��շ�׼���÷���֪ͨ�û�
 */
am_local int __xmodem_tx_user_inform (am_xmodem_tx_dev_t *p_dev,
                                      char                inchar)
{
    /*��ǰ״̬Ϊ�ļ����ͽ���ʱ�����յ���Ӧ���źŽ��Զ��ظ�*/
    if (p_dev->state_flag == __AM_XMODEM_DOC_EOT) {
        return __xmodem_tx_eot_ack(p_dev);
    }
    if (p_dev->tx_bytes == 0 ) {
        p_dev->tx_state = __AM_XMODEM_FLAG_TX;
        return __xmodem_tx_result_mode(p_dev, inchar);
    }
    return AM_FALSE;
}

/******************************************************************************/
/**
 * \brief �жϽ����ַ�����
 */
am_local void __xmodem_tx_char (void *p_arg, uint8_t inchar)
{
    am_xmodem_tx_dev_t *p_dev = (am_xmodem_tx_dev_t *)p_arg;

    am_softimer_stop(&p_dev->tx_softimer);

    if (AM_FALSE == __xmodem_tx_user_inform(p_dev, inchar)) {
        return;
    }
}

/******************************************************************************/
/**
 * \brief Xmodem���ͳ�ʱ����
 */
am_local void __xmodem_tx_time_callback(void *p_arg)
{
    am_xmodem_tx_dev_t *p_dev = (am_xmodem_tx_dev_t *)p_arg;
    /* �ر������ʱ�� */
    am_softimer_stop(&p_dev->tx_softimer);
    if (p_dev->pfn_tx_callback != NULL) {
        am_xmodem_tx_can_set(p_dev);
        p_dev->pfn_tx_callback(p_dev->p_arg, -AM_ETIME);
     }
}

/******************************************************************************/
/**
 * \brief �����豸��ʼ������
 */
am_xmodem_tx_handle_t  am_xmodem_tx_init (
                           am_xmodem_tx_dev_t            *p_dev,
                           const am_xmodem_tx_dev_info_t *p_tx_devinfo,
                           am_uart_handle_t               uart_handle,
                           am_crc_handle_t                crc_handle)
{
    if ((NULL == p_dev) || (NULL == p_tx_devinfo) || (NULL == uart_handle)) {
        return NULL;
    }

    p_dev->ctrlz_num    = 0;    /**< \brief ��ʼ�������*/
    p_dev->tx_bytes     = 0;    /**< \brief ��ʼ�������ļ���С*/
    p_dev->p_tx_buf     = NULL; /**< \brief ��ʼ���ļ�ָ�� */
    p_dev->state_flag   = 0;    /**< \brief Ĭ�ϵ�һ�����յ����ַ�Ϊģʽ�ж��ַ� */
    p_dev->nake_state   = 0;    /**< \brief ��ʼ���ط�״̬Ϊ0*/
    p_dev->p_tx_func    = NULL; /**< \brief ��ʼ��״̬������ָ�� */
    p_dev->crc_handle   = crc_handle;   /**< \brief CRC���*/
    p_dev->uart_handle  = uart_handle;  /**< \brief ���ھ��*/
    p_dev->tx_state     = __AM_XMODEM_DATA_TX;
    p_dev->p_tx_devinfo = (am_xmodem_tx_dev_info_t *)p_tx_devinfo;

    /* ��ʼ��CRCģ��*/
    __crc_16_pattern_set(crc_handle, &p_dev->crc_pattern);

    /* ʹ�ܴ����ж�ģʽ */
    am_uart_ioctl(p_dev->uart_handle,
                  AM_UART_MODE_SET,
                  (void *)AM_UART_MODE_INT);

    am_uart_callback_set(p_dev->uart_handle,
                         AM_UART_CALLBACK_RXCHAR_PUT,
                         __xmodem_tx_char,
                         (void *)(p_dev));

    /* ע�ᷢ�ͻص����� */
    am_uart_callback_set(p_dev->uart_handle,
                         AM_UART_CALLBACK_TXCHAR_GET,
                         __xmodem_tx_char_get,
                         (void *)(p_dev));

    if (p_tx_devinfo->tx_timeout != 0) {
        if (am_softimer_init(&p_dev->tx_softimer,
                             __xmodem_tx_time_callback,
                             (void *)p_dev) != AM_OK) {
            return NULL;
        }
    }
    return (am_xmodem_tx_handle_t)(p_dev);
}


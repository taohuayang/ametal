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
 * \brief ��ȫоƬFMSE-A03 I2C�����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-07-02  yrz, first implementation.
 * \endinternal
 */
#include "am_fmse_i2c.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_wait.h"

/*******************************************************************************
 * �궨��
 ******************************************************************************/
#define I2C_CMD_IBLOCK			0x02
#define I2C_CMD_NAK				0xBA

#define I2C_MIN_LEN				3
#define I2C_MAX_LEN				1024

#define	FRAME_DELAY_I2C			5

/*******************************************************************************
 * ���غ�������
 ******************************************************************************/
static uint8_t __fmse_i2c_transceive (void     *p_drv,
                                      uint8_t  *sbuf,
                                      uint16_t  slen,
                                      uint8_t  *rbuf,
                                      uint16_t *rlen, 
                                      uint16_t  poll_inv,
                                      uint32_t  poll_timeout);
/*******************************************************************************
  Local functions
*******************************************************************************/
const struct am_fmse_drv_funcs __fmse_i2c_drv_funcs = {
	__fmse_i2c_transceive
};

/**
 * \brief I2C�ص�����
 */
static void __fmse_i2c_callback (void *p_arg)
{
    /* �����ȴ����� */
    am_wait_done((am_wait_t *)p_arg);
}

/**
 * \brief I2C֡����
 *
 * \param[in] p_drv : I2C������ FMSE�豸���
 * \param[in] cmd   : FMSE�豸����
 * \param[in] sbuf  : ���������ݻ�����
 * \param[in] slen  : ���͵����ݳ���
 *
 * \return ״ֵ̬
 */
static uint8_t __fmse_i2c_frame_send (void     *p_drv,
                                      uint8_t   cmd,
                                      uint8_t  *sbuf,
                                      uint16_t  slen)
{
    am_fmse_i2c_dev_t *p_this = (am_fmse_i2c_dev_t*)(p_drv);
    am_i2c_device_t   *p_dev  = (am_i2c_device_t*)(&p_this->i2c_dev);

    am_fmse_i2c_head_t fm_i2c_hd;
    uint16_t i;
    uint8_t bcc;

    am_i2c_transfer_t trans[3];
    am_wait_t         trans_wait;
    am_i2c_message_t  msg;
    int               ret;

    /* ֡ͷ */
    fm_i2c_hd.lenlo = slen + 3;
    fm_i2c_hd.lenhi = (slen + 3) >> 8;
    fm_i2c_hd.nad = 0;
    fm_i2c_hd.flag.cmd = cmd;

    /* calc bcc */
    bcc = fm_i2c_hd.lenlo ^ fm_i2c_hd.lenhi ^ fm_i2c_hd.nad ^ fm_i2c_hd.flag.cmd; 

    for(i = 0; i < slen; i++){
        bcc ^= sbuf[i];
    }

    am_wait_init(&trans_wait);

    /* �ӻ���ַ��֡ͷ */
    am_i2c_mktrans(&trans[0],
                    p_dev->dev_addr,
                    p_dev->dev_flags | AM_I2C_M_WR,
                   &(fm_i2c_hd.lenlo), 
                    4);
    /* ���͵����� */
    am_i2c_mktrans(&trans[1],
                    p_dev->dev_addr,
                    p_dev->dev_flags | 
                    AM_I2C_M_WR | AM_I2C_M_NOSTART,
                    sbuf,
                    slen);
    /* У�� */
    am_i2c_mktrans(&trans[2],
                    p_dev->dev_addr,
                    p_dev->dev_flags | 
                    AM_I2C_M_WR | AM_I2C_M_NOSTART,
                   &bcc,
                    1);

    am_i2c_mkmsg(&msg, &trans[0], 3, __fmse_i2c_callback, &trans_wait);

    ret = am_i2c_msg_start(p_dev->handle, &msg);

    if (ret != AM_OK) {
        return 12;
    }

    am_wait_on(&trans_wait);

    am_mdelay(FRAME_DELAY_I2C);

    return 0;
}

/**
 * \brief I2C֡����
 *
 * \param[in] p_drv : I2C������ FMSE�豸���
 * \param[in] rbuf  : �������ݻ�����
 * \param[in] rlen  : ���յ����ݳ���
 *
 * \return ״ֵ̬
 */
static uint8_t __fmse_i2c_frame_recv(void *p_drv, uint8_t *rbuf, uint16_t *rlen)
{
    am_fmse_i2c_dev_t *p_this = (am_fmse_i2c_dev_t*)(p_drv);
    am_i2c_device_t   *p_dev  = (am_i2c_device_t*)(&p_this->i2c_dev);
    
    uint16_t i;
    uint16_t recv_len;
    uint8_t bcc = 0;
    uint8_t ret;
    am_fmse_i2c_head_t fm_i2c_hd;
    uint8_t temp[1028];
    *rlen = 0;
    
    am_i2c_transfer_t trans[2];
    am_wait_t         trans_wait;
    am_i2c_message_t  msg;
    
    am_wait_init(&trans_wait);
    
    /* ��ȡ���� */
    am_i2c_mktrans(&trans[0],
                    p_dev->dev_addr,
                    p_dev->dev_flags | 
                    AM_I2C_M_RD,
                &(fm_i2c_hd.lenlo), 
                    2);
    
    am_i2c_mkmsg(&msg, &trans[0], 1, __fmse_i2c_callback, &trans_wait);
    
    ret = am_i2c_msg_start(p_dev->handle, &msg);
    
    if (ret != AM_OK) {
        return 12;
    }
    
    am_wait_on(&trans_wait);
    
    recv_len  = (fm_i2c_hd.lenhi << 8) + fm_i2c_hd.lenlo;
    
    if(recv_len < I2C_MIN_LEN || recv_len > I2C_MAX_LEN){
    
        *rlen = 0;
        return 13;
    }
    
    am_wait_init(&trans_wait);
    
    /* ��ȡ��󳤶� */
    am_i2c_mktrans(&trans[0],
                p_dev->dev_addr,
                p_dev->dev_flags | 
                AM_I2C_M_RD,
                temp, 
                recv_len + 2);
    
    am_i2c_mkmsg(&msg, &trans[0], 1, __fmse_i2c_callback, &trans_wait);
    
    ret = am_i2c_msg_start(p_dev->handle, &msg);
    
    if (ret != AM_OK) {
        return 12;
    }
    
    am_wait_on(&trans_wait);
    
    fm_i2c_hd.nad = temp[2];
    fm_i2c_hd.flag.sta = temp[3];
    
    bcc = fm_i2c_hd.lenlo ^ fm_i2c_hd.lenhi ^ fm_i2c_hd.nad ^ fm_i2c_hd.flag.sta;
    
    /* recv data length */
    *rlen = recv_len - 3;
    
    /* recv data */
    for(i = 0; i < *rlen; i++) {
        rbuf[i] = temp[i + 4];
        bcc ^= rbuf[i];
    }
    
    bcc ^= temp[recv_len + 1];
    
    if(bcc) {
        
        *rlen = 0;
        return 14;
    }
    
    am_mdelay(FRAME_DELAY_I2C);
    
    return fm_i2c_hd.flag.sta;
}

/**
 * \brief ��ȫоƬ���ͽ���֡
 *
 * \param[in] p_drv        : I2C������ FMSE�豸
 * \param[in] sbuf         : ���������ݻ�����
 * \param[in] slen         : ���������ݳ���
 * \param[in] rbuf         : �������ݻ�����
 * \param[in] rlen         : �������ݳ���
 * \param[in] poll_inv     : ֡����ʱ
 * \param[in] poll_timeout : ��ʱʱ��
 *
 * \return ״ֵ̬
 */
static uint8_t __fmse_i2c_transceive (void     *p_drv,
                                      uint8_t  *sbuf,
                                      uint16_t  slen,
                                      uint8_t  *rbuf,
                                      uint16_t *rlen, 
                                      uint16_t  poll_inv,
                                      uint32_t  poll_timeout)
{
    am_fmse_i2c_dev_t *p_dev = (am_fmse_i2c_dev_t*)(p_drv);
    uint8_t ret;
    uint32_t timeout;

    *rlen = 0;

    ret = __fmse_i2c_frame_send(p_dev, I2C_CMD_IBLOCK, sbuf, slen);

    if (ret != AM_OK) {
        return ret;
    }

    timeout = poll_timeout;

    /* ��ѯ���ǿ������1���룬���Ϊ10���� */
    poll_inv = ((poll_inv == 0) || (poll_inv > 9)) ? 1 : poll_inv;

    do {
        ret = __fmse_i2c_frame_recv(p_dev, rbuf, rlen);

        if(ret == 12) {              /* timeout */

            am_mdelay(poll_inv);
            timeout -= poll_inv;

        } else if(ret == 13 || ret == 14) {   /* ���Ȼ�bcc err */

            __fmse_i2c_frame_send(p_dev, I2C_CMD_NAK, 0, 0);
            timeout = poll_timeout;  /* �������ó�ʱʱ�� */

        } else if(ret == 0xF2) {       /* WTX */

            timeout = poll_timeout;  /* �������ó�ʱʱ�� */

        } else {
            break;                           
        }  
    } while (timeout > 10);
    
    return ret;
}

/**
 * \brief I2C����FMSE���豸��ʼ��
 *
 * \param[in] p_dev     : I2C������ FMSE�豸
 * \param[in] p_devinfo : FMSE�豸��Ϣ
 * \param[in] handle    : I2C��׼������
 *
 * \return FMSE��׼����������ΪNULL��������ʼ��ʧ��
 */
am_fmse_handle_t am_fmse_i2c_init (am_fmse_i2c_dev_t           *p_dev,
                                   const am_fmse_i2c_devinfo_t *p_devinfo,
                                   am_i2c_handle_t              handle)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                  handle,
                  p_devinfo->i2c_addr,
                  AM_I2C_ADDR_7BIT);

    p_dev->fmse_dev.p_drv   = p_dev;
    p_dev->fmse_dev.p_funcs = &__fmse_i2c_drv_funcs;
    p_dev->dev_info         = p_devinfo;

    return (&(p_dev->fmse_dev));
}

/**
 * \brief FMSE���豸ȥ��ʼ��
 *
 * \param[in] handle : FMSE��ʼ����ȡ�ı�׼������
 *
 * \return 
 */
am_err_t am_fmse_i2c_deinit (am_fmse_handle_t handle)
{
    am_fmse_i2c_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->fmse_dev.p_drv   = NULL;
    p_dev->fmse_dev.p_funcs = NULL;
    p_dev->dev_info         = NULL;

    return AM_OK;
}

/* end of file */

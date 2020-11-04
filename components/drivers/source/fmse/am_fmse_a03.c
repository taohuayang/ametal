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
 * \brief ��ȫоƬFMSE-A03 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-07-01  yrz, first implementation.
 * \endinternal
 */

#include "am_fmse_a03.h"
#include "am_vdebug.h"
#include "am_des.h"

/*******************************************************************************
 * �궨��
 ******************************************************************************/
#define FMSE_ERR_NULL_POINT     0xFFE1
#define FMSE_ERR_RECV_ACK       0xFFE2
#define FMSE_ERR_LENGTH         0xFFE3
#define FMSE_ERR_LRC            0xFFE4
#define FMSE_ERR_OTHER          0xFFE5
#define FMSE_ERR_CRC            0xFFE6
#define FMSE_ERR_INS            0xFFE7

/* ��ѯʱ��������λms */
#define FMSE_POLL_INTERVAL      5

/* ��ѯ��ʱʱ�䣬��λms */
#define FMSE_POLL_TIMEOUT       16000

/*******************************************************************************
 * ���غ�������
 ******************************************************************************/

/*******************************************************************************
  Local functions
*******************************************************************************/
/**
 * \brief �ڴ��ʼ��
 *
 * \param[in] p_dst  : ָ�����ʼ���ڴ��ָ��
 * \param[in] val    : ��ʼ����ֵ
 * \param[in] count  : ��ʼ�����ڴ泤��
 *
 * \return ��ʼ���ڴ��׵�ַ
 */
void* am_fmse_memset(void* p_dst, int val, size_t count)
{
    char* tmpdst = (char*)p_dst;
    char  tmpval = (char)val;
    
    if(p_dst == NULL || !count) {
        return NULL;
    }

    while(count--) {
        *tmpdst++ = tmpval;
    }
    
    return p_dst;
}

/**
 * \brief �ڴ����ݸ���
 *
 * \param[in] p_dst  : ָ��Ŀ�ĵ�ַ��ָ��
 * \param[in] p_src  : ָ��Դ��ַ��ָ��
 * \param[in] count  : ���Ƶ����ݳ���
 *
 * \return Ŀ�ĵ�ַ��ָ��
 */
void* am_fmse_memmove(void* p_dst, const void* p_src, size_t count)
{
    char* tmpdst = (char*)p_dst;
    char* tmpsrc = (char*)p_src;
    
    if(p_dst == NULL || p_src == NULL || !count) {
        return 0;
    }

    if (tmpdst <= tmpsrc || tmpdst >= tmpsrc + count) {
        while(count--) {
            *tmpdst++ = *tmpsrc++; 
        }
    } else {
        tmpdst = tmpdst + count - 1;
        tmpsrc = tmpsrc + count - 1;
        while(count--) {
            *tmpdst-- = *tmpsrc--;
        }
    }

    return p_dst; 
}

/**
 * \brief ���У��
 *
 * \param[in] result : ���ص�״ֵ̬
 *
 * \return У����������
 */
static uint16_t __fmse_result_check (uint8_t result)
{
    uint16_t ret;

    switch(result) {
        case 1:
            ret = FMSE_ERR_CRC;
            break;
        case 2:
            ret = FMSE_ERR_INS;
            break;
        case 11:
            ret = FMSE_ERR_NULL_POINT;
            break;
        case 12:
            ret = FMSE_ERR_RECV_ACK;
            break;
        case 13:
            ret = FMSE_ERR_LENGTH;
            break;
        case 14:
            ret = FMSE_ERR_LRC;
            break;
        default:
            ret = FMSE_ERR_OTHER;
            break;
    }

    return ret;
}

/**
 * \brief �ļ�����
 *
 * \param[in] handle : FMSE��׼������
 *
 * \return ״̬��
 */
uint16_t am_fmse_file_create (am_fmse_handle_t handle,
                              uint16_t         fid,
                              uint8_t          type,
                              uint16_t         space,
                              uint16_t         rank)
{
    uint8_t  result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint8_t  rbuf[2];
    uint16_t rlen;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout  = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0xE0;
    apdu_pack.p1 = fid >> 8;
    apdu_pack.p2 = fid;
    apdu_pack.p3.lc = 7;
    apdu_pack.capdu[0] = type;
    apdu_pack.capdu[1] = space >> 8;
    apdu_pack.capdu[2] = space;
    apdu_pack.capdu[3] = rank >> 8;
    apdu_pack.capdu[4] = rank;
    apdu_pack.capdu[5] = 0xFF;
    apdu_pack.capdu[6] = 0xFF;
    slen = 5 + 7;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                      &rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[rlen-2]<<8 | rbuf[rlen-1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief �������ȡ
 *
 * \param[in] handle : FMSE��׼������
 *
 * \return ״̬��
 */
uint16_t am_fmse_challenge_get (am_fmse_handle_t handle,
                                uint16_t         inlen,
                                uint8_t         *rbuf,
                                uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen  = 0;
    uint16_t ret   = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout  = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0;
    apdu_pack.ins = 0x84;
    apdu_pack.p1 = 0;
    apdu_pack.p2 = 0;
    apdu_pack.p3.le = inlen;
    slen = 5;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen-2]<<8 | rbuf[*rlen-1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief �ļ�ѡ��
 *
 * \param[in] handle : FMSE��׼������
 *
 * \return ״̬��
 */
uint16_t am_fmse_file_select (am_fmse_handle_t handle,
                              uint16_t         fid,
                              uint8_t         *rbuf,
                              uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0;
    apdu_pack.ins = 0xA4;
    apdu_pack.p1 = 0;
    apdu_pack.p2 = 0;
    apdu_pack.p3.lc = 2;
    apdu_pack.capdu[0] = fid >> 8;
    apdu_pack.capdu[1] = fid;
    slen = 5 + 2;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief У��
 *
 * \param[in] handle : FMSE��׼������
 *
 * \return ״̬��
 */
uint16_t am_fmse_pin_verify (am_fmse_handle_t  handle,
                             uint16_t          inlen,
                             uint8_t          *inbuf)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint8_t rbuf[2];
    uint16_t rlen;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0;
    apdu_pack.ins = 0x20;
    apdu_pack.p1 = 0;
    apdu_pack.p2 = 0;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                      &rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[rlen - 2] << 8 | rbuf[rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief �������ļ���ȡ
 *
 * \param[in] handle : FMSE��׼������
 * \param[in] sfi    : �ļ���ʼλ��
 * \param[in] inlen  : ��ȡ�ĳ���
 * \param[in] rbuf   : ���ջ�����
 * \param[in] rlen   : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_binary_read (am_fmse_handle_t handle,
                              uint16_t         sfi,
                              uint16_t         inlen,
                              uint8_t         *rbuf,
                              uint16_t         *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0;
    apdu_pack.ins = 0xB0;
    apdu_pack.p1 = sfi >> 8;
    apdu_pack.p2 = sfi;
    apdu_pack.p3.le = inlen;
    slen = 5;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief RSA ��Կ������
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] key_len : ��Կ�Գ���
 * \param[in] exp     : ��Կ��ָ��
 * \param[in] fid     : the Fid that save the dest RSA Key Pair
 *                      input 4Bytes Fid format: public key fid + private key fid
 *                      single 2Bytes Fid format:high byte + low byte
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_rsa_key_pair_gen(am_fmse_handle_t handle,
                                  uint8_t          key_len,
                                  uint8_t          exp,
                                  uint32_t         fid,
                                  uint8_t         *rbuf,
                                  uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x52;
    apdu_pack.p1 = key_len;
    apdu_pack.p2 = exp;
    apdu_pack.p3.lc = 8;
    apdu_pack.capdu[0] = 0xC0;
    apdu_pack.capdu[1] = 2;
    apdu_pack.capdu[2] = fid >> 24;
    apdu_pack.capdu[3] = fid >> 16;
    apdu_pack.capdu[4] = 0xC2;
    apdu_pack.capdu[5] = 2;
    apdu_pack.capdu[6] = fid >> 8;
    apdu_pack.capdu[7] = fid;
    slen = 5 + 8;

    if(handle)
    {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief SM2 ��Կ������
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] fid     : the Fid that save the dest RSA Key Pair
 *                      input 4Bytes Fid format: public key fid + private key fid
 *                      single 2Bytes Fid format:high byte + low byte
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_sm2_key_pair_gen (am_fmse_handle_t handle,
                                   uint32_t         fid,
                                   uint8_t         *rbuf,
                                   uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x50;
    apdu_pack.p1 = 0;
    apdu_pack.p2 = 0;
    apdu_pack.p3.lc = 8;
    apdu_pack.capdu[0] = 0xC0;
    apdu_pack.capdu[1] = 2;
    apdu_pack.capdu[2] = fid >> 24;
    apdu_pack.capdu[3] = fid >> 16;
    apdu_pack.capdu[4] = 0xC2;
    apdu_pack.capdu[5] = 2;
    apdu_pack.capdu[6] = fid >> 8;
    apdu_pack.capdu[7] = fid;
    slen = 5 + 8;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief ����Ự��Կ
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : key type and data block flag and RSA type
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input session key buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_session_key_import (am_fmse_handle_t handle,
                                     uint16_t         p1p2,
                                     uint16_t         inlen,
                                     uint8_t         *inbuf,
                                     uint8_t         *rbuf,
                                     uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x5A;
    apdu_pack.p1 = p1p2 >> 8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief data encrypt and decrypt
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : key type and data block flag and RSA type
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_data_encrypt_and_decrypt(am_fmse_handle_t handle,
                                          uint16_t         p1p2,
                                          uint16_t         inlen,
                                          uint8_t         *inbuf,
                                          uint8_t         *rbuf,
                                          uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0xDA;
    apdu_pack.p1 = p1p2 >> 8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief RSA public key calculate
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : key type and data block flag and RSA type
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_rsa_pub_key_cal(am_fmse_handle_t handle,
                                 uint16_t         p1p2,
                                 uint16_t         inlen,
                                 uint8_t         *inbuf,
                                 uint8_t         *rbuf,
                                 uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x76;
    apdu_pack.p1 = p1p2 >> 8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief RSA private key calculate
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : key type and data block flag and RSA type
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_rsa_pri_key_cal(am_fmse_handle_t handle,
                                 uint16_t         p1p2,
                                 uint16_t         inlen,
                                 uint8_t         *inbuf,
                                 uint8_t         *rbuf,
                                 uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x58;
    apdu_pack.p1 = p1p2 >> 8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief SM2 public key calculate
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : key type and data block flag and RSA type
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_sm2_pub_key_cal(am_fmse_handle_t handle,
                                 uint8_t          mode,
                                 uint16_t         inlen,
                                 uint8_t         *inbuf,
                                 uint8_t         *rbuf,
                                 uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x5C;
    apdu_pack.p1 = 0;
    apdu_pack.p2 = mode;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief SM2 private key calculate
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : key type and data block flag and RSA type
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_sm2_pri_key_cal(am_fmse_handle_t handle,
                                 uint8_t          mode,
                                 uint16_t         inlen,
                                 uint8_t         *inbuf,
                                 uint8_t         *rbuf,
                                 uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x6E;
    apdu_pack.p1 = 0;
    apdu_pack.p2 = mode;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief Install RSA key
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : key type and data block flag and RSA type
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_rsa_key_install (am_fmse_handle_t handle,
                                  uint16_t         p1p2,
                                  uint16_t         inlen,
                                  uint8_t         *inbuf,
                                  uint8_t         *rbuf,
                                  uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0xE6;
    apdu_pack.p1 = p1p2 >> 8;                      
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief WriteBinary
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] sfi     : file start position to write
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_binary_write (am_fmse_handle_t handle,
                               uint16_t         sfi,
                               uint16_t         inlen,
                               uint8_t         *inbuf,
                               uint8_t         *rbuf,
                               uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0;
    apdu_pack.ins = 0xD6;
    apdu_pack.p1 = sfi >> 8;
    apdu_pack.p2 = sfi;
    apdu_pack.p3.le = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }
    return ret;
}

/**
 * \brief Data_Compress
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : 
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_data_compress(am_fmse_handle_t handle,
                               uint16_t         p1p2,
                               uint16_t         inlen,
                               uint8_t         *inbuf,
                               uint8_t         *rbuf,
                               uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0xE4;
    apdu_pack.p1 = p1p2 >> 8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.le = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }
    return ret;
}

/**
 * \brief Export Public Key
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : 
 * \param[in] inlen   : file length to write
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_pub_key_export(am_fmse_handle_t handle,
                                uint16_t         p1p2,
                                uint16_t         inlen,
                                uint8_t         *inbuf,
                                uint8_t         *rbuf,
                                uint16_t         *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0xD9;
    apdu_pack.p1  = p1p2 >> 8;
    apdu_pack.p2  = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);    
    slen = 5 + inlen;

    if (handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }
    return ret;    
}

/**
 * \brief Gen ECC Key Pair
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : 
 * \param[in] Fid     : the Fid that save the dest Key Pair
 *                      input 4Bytes Fid format: public key fid + private key fid
 *                      single 2Bytes Fid format:high byte + low byte
 * \param[in] rbuf    : ���ջ�����
 * \param[in] rlen    : ���յĳ���
 *
 * \return ״̬��
 */
uint16_t am_fmse_ecc_key_pair_gen(am_fmse_handle_t handle,
                                  uint16_t         p1p2,
                                  uint32_t         fid,
                                  uint8_t         *rbuf,
                                  uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x30;
    apdu_pack.p1 = p1p2>>8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = 8;
    apdu_pack.capdu[0] = 0xC0;
    apdu_pack.capdu[1] = 2;
    apdu_pack.capdu[2] = fid >> 24;
    apdu_pack.capdu[3] = fid >> 16;
    apdu_pack.capdu[4] = 0xC2;
    apdu_pack.capdu[5] = 2;
    apdu_pack.capdu[6] = fid >> 8;
    apdu_pack.capdu[7] = fid;
    slen = 5 + 8;    

    if (handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief ECC public key calculate
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : 
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : the return data buffer
 * \param[in] rlen    : the return data length
 *
 * \return ret
 */
uint16_t am_fmse_ecc_pub_key_cal(am_fmse_handle_t handle,
                                 uint16_t         p1p2,
                                 uint16_t         inlen,
                                 uint8_t         *inbuf,
                                 uint8_t         *rbuf,
                                 uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x3C;
    apdu_pack.p1 = p1p2 >> 8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief ECC private key calculate
 *
 * \param[in] handle  : FMSE��׼������
 * \param[in] p1p2    : 
 * \param[in] inlen   : file length to read
 * \param[in] inbuf   : input data buffer
 * \param[in] rbuf    : the return data buffer
 * \param[in] rlen    : the return data length
 *
 * \return ret
 */
uint16_t am_fmse_ecc_pri_key_cal(am_fmse_handle_t handle,
                                 uint16_t         p1p2,
                                 uint16_t         inlen,
                                 uint8_t         *inbuf,
                                 uint8_t         *rbuf,
                                 uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x3E;
    apdu_pack.p1 = p1p2 >> 8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen-2]<<8 | rbuf[*rlen-1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief External Authentication
 *
 * \param[in]  handle      : FMSE��׼������
 * \param[in]  random_send : input lacal random data 
 * \param[in]  random_get  : input random data from SE
 * \param[in]  ea_key      : input External_Authentication Key
 * \param[out] None
 *
 * \return ret
 */
uint16_t am_fmse_external_authentication (am_fmse_handle_t  handle,
                                          uint8_t          *random_send,
                                          uint8_t          *random_get,
                                          uint8_t          *ea_key)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint8_t rbuf[2];
    uint16_t rlen;
    uint8_t tenp_buf[16] = {0};
    uint8_t auth_data[16] = {0};
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0;
    apdu_pack.ins = 0x82;
    apdu_pack.p1 = 0;
    apdu_pack.p2 = 0;
    apdu_pack.p3.lc = 0x10;

    am_tdes(0, random_get, ea_key, tenp_buf);
    am_des(0, random_send, tenp_buf, auth_data);

    am_fmse_memmove(&auth_data[8], random_send, 0x08);
    am_fmse_memmove(apdu_pack.capdu, auth_data, 0x10);
    slen = 5 + 0x10;

    if(handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                      &rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[rlen - 2] << 8 | rbuf[rlen - 1];
        else
            ret = __fmse_result_check(result);
    }

    return ret;
}

/**
 * \brief Change PIN
 *
 * \param[in]  handle      : FMSE��׼������
 * \param[in]  new_pin     : input pin 
 * \param[in]  new_pin_len : input new_pin_len
 * \param[in]  old_pin     : input old_pin
 * \param[in]  old_pin_len : input old_pin_len
 *
 * \return ret
 */
uint16_t am_fmse_pin_change (am_fmse_handle_t handle,
                             uint8_t         *new_pin,
                             uint8_t          new_pin_len,
                             uint8_t         *old_pin,
                             uint8_t          old_pin_len)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint8_t rbuf[2];
    uint16_t rlen;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0x5E;
    apdu_pack.p1  = 0x01;
    apdu_pack.p2  = 00;
    apdu_pack.p3.lc = new_pin_len + old_pin_len + 1;

    am_fmse_memmove(apdu_pack.capdu, old_pin, old_pin_len);
    apdu_pack.capdu[old_pin_len] = 0xFF;
    am_fmse_memmove(&apdu_pack.capdu[old_pin_len + 1], new_pin, new_pin_len);    

    slen = 5 + apdu_pack.p3.lc;

    if (handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                      &rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[rlen - 2] << 8 | rbuf[rlen - 1];
        else
            ret = __fmse_result_check(result);
    }
    return ret;
}

/**
 * \brief Write Key
 *
 * \param[in]  handle : FMSE��׼������
 * \param[in]  p1p2   : 
 * \param[in]  inlen  : data length to write
 * \param[in]  inbuf  : input data buffer
 * \param[in]  rbuf   : the return data buffer
 * \param[in]  rlen   : the return data length
 *            
 * \return ret
 */
uint16_t am_fmse_key_write (am_fmse_handle_t handle,
                            uint16_t         p1p2,
                            uint16_t         inlen,
                            uint8_t         *inbuf,
                            uint8_t         *rbuf,
                            uint16_t        *rlen)
{
    uint8_t result = 0;
    uint16_t slen = 0;
    uint16_t ret = FMSE_ERR_NULL_POINT;
    uint16_t interval = FMSE_POLL_INTERVAL;
    uint32_t timeout = FMSE_POLL_TIMEOUT;
    apdu_pack_t apdu_pack;

    apdu_pack.cla = 0x80;
    apdu_pack.ins = 0xD4;
    apdu_pack.p1 = p1p2>>8;
    apdu_pack.p2 = p1p2;
    apdu_pack.p3.lc = inlen;
    am_fmse_memmove(apdu_pack.capdu, inbuf, inlen);
    slen = 5 + inlen;

    if (handle) {
        result = handle->p_funcs->fmse_apdu_transceive(handle,
                                                       (uint8_t*)&apdu_pack,
                                                       slen,
                                                       rbuf,
                                                       rlen,
                                                       interval,
                                                       timeout);
        if(!result)
            ret = rbuf[*rlen - 2] << 8 | rbuf[*rlen - 1];
        else
            ret = __fmse_result_check(result);
    }
    return ret;
}

/* end of file */

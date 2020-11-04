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
 * \brief ��ȫоƬFMSE-A03 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *
 * \par Դ����
 * \snippet demo_fmse_data_encrypt_and_decrypt.c
 *          src_fmse_data_encrypt_and_decrypt
 * \internal
 * \par Modification history
 * - 1.00 20-07-01  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_fmse_data_encrypt_and_decrypt
 * \copydoc demo_fmse_data_encrypt_and_decrypt.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_fmse_a03.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_fmse_data_encrypt_and_decrypt_entry (am_fmse_handle_t handle)
{
    uint8_t i;
    uint8_t rbuf[1028];
    uint8_t inbuf[256];
    uint8_t pin[4];
    uint16_t rlen = 0;
    uint16_t ret  = 0;
    uint8_t det_key_index = 0;

    printf("\r\n");
    printf("data endecrypt test\r\n");  

    ret = am_fmse_file_select(handle, 0xDF01, rbuf, &rlen);
    if(ret != 0x9000) {
        printf("1. file selection failed\r\n");
    }

    pin[0] = 0x11;
    pin[1] = 0x22;
    pin[2] = 0x33;
    ret = am_fmse_pin_verify(handle, 3, pin);
    if(ret != 0x9000) {
        printf("2. pin verify failed\r\n");
    }

    am_fmse_memset(inbuf, 0, sizeof(inbuf));

    /* SM1�������� */
    am_fmse_memmove(inbuf, "\xc1\x10", 2);
    for(i = 0; i < 16; i++) {
        inbuf[i + 2] = i;
    }

    /* Import Session Key */
    /* 0110��SM1�㷨��������ݸ�ʽ */
    ret = am_fmse_session_key_import(handle, 0x0110, 0x12, inbuf, rbuf, &rlen);
    if(ret != 0x9000) {
        printf("3. session key import failed\r\n");
    }

    det_key_index = rbuf[0];

    printf("import session key: ret = %04x, rlen = %d\r\n",ret,rlen);

    /* ����ɹ������ص�ǰ��Կ������+9000���˴�����Ϊ00 */
    for(i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    /* pre data */
    am_fmse_memset(inbuf, 0, sizeof(inbuf));

    inbuf[3] = det_key_index;

    /* 00000000�����һ�ֽڱ�ʾ�Ự��Կ�������� */
    for(i = 0; i < 16; i++) {
        inbuf[i + 4] = 0x11;
    }

    /* Data Encrypt calc */
    /* 0040��Ψһ���ݿ飬���ܲ�����ʹ���Ե���ĻỰ��Կ,ECBģʽ��
     * ���ݳ���Ϊ4+16
     */
    ret = am_fmse_data_encrypt_and_decrypt(handle,
                                           0x0040,
                                           0x14,
                                           inbuf,
                                           rbuf,
                                          &rlen);
    if (ret != 0x9000) {
        printf("4. data encrypt failed\r\n");
    }

    /* ���ؼ����ļӽ������� */
    printf("data encrypt: ret = %04x, rlen = %d\r\n", ret, rlen);
    for(i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    /* pre data */
    am_fmse_memset(inbuf, 0, sizeof(inbuf));

    inbuf[3] = det_key_index;   

    /* 0x00000000����Կ����������ʮ���ֽ��Ǹո���ɼ��ܺ������ */
    for (i = 0; i < 16; i++) {
        inbuf[i + 4] = rbuf[i];
    }

    /* Data Decrypt calc
     * 00C0�����ܲ�����ʹ���ѵ���ĻỰ��Կ�������򳤶�Ϊ4+16
     */
    ret = am_fmse_data_encrypt_and_decrypt(handle,
                                           0x00C0,
                                           0x14,
                                           inbuf,
                                           rbuf,
                                          &rlen);
    if (ret != 0x9000) {
        printf("5. data decrypt failed\r\n");
    }
    printf("data decrypt: ret = %04x, rlen = %d\r\n",ret,rlen);
    for(i = 0; i < rlen; i++) {                                                                    
        printf("%02x,",rbuf[i]);                                        
    }                                                                    
    printf("\r\n");

    /* SM4��SM1һ�����ǶԳƼ����㷨�����ӽ�����ͬ������Կ */

    printf("\r\n");
    printf("SM4 TEST! \r\n");  
    am_fmse_memset(inbuf, 0, sizeof(inbuf));

    /* SM4�������� */
    am_fmse_memmove(inbuf, "\xc1\x10", 2);
    for(i = 0; i < 16; i++) {
        inbuf[i+2] = i;
    }

    /* Import Session Key */
    /* 0210��SM4�㷨��������ݸ�ʽ */
    ret = am_fmse_session_key_import(handle, 0x0210, 0x12, inbuf, rbuf, &rlen);
    if(ret != 0x9000) {
        printf("6. session key import failed\r\n");
    }
    printf("import session key SM4: ret = %04x, rlen = %d\r\n", ret, rlen); 

    /* ����ɹ������ص�ǰ��Կ������+9000���˴�����Ϊ00 */
    for(i = 0; i < rlen;  i++) {
        printf("%02x,",rbuf[i]);
    }

    /* ������Կ������ */
    det_key_index = rbuf[0];
    printf("\r\n");

    /* pre data */
    am_fmse_memset(inbuf, 0, sizeof(inbuf));

    /* 0x00000000��Ԥ����Կ����λ�� */
    for(i = 0; i < 16; i++) {
        inbuf[i + 4] = 0x44;
    }

    /* ���»Ự��Կ����0x00000000+zlg_key_num */
    inbuf[3] = det_key_index;

    /* Data Encrypt calc
     * 0040��Ψһ���ݿ飬���ܲ�����ʹ���Ե���ĻỰ��Կ,ECBģʽ��
     * ���ݳ���Ϊ4+16
     */
    ret = am_fmse_data_encrypt_and_decrypt(handle,
                                           0x0040,
                                           0x14,
                                           inbuf,
                                           rbuf,
                                          &rlen);
    if (ret != 0x9000) {
        printf("7. data encrypt failed\r\n");
    }

    /* ���ؼ����ļӽ������� */
    printf("data encrypt SM4: ret = %04x, rlen = %d\r\n", ret, rlen);
    for (i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    /* pre data */
    am_fmse_memset(inbuf, 0, sizeof(inbuf));

    /* 0x00000000��Ԥ����Կ����λ�ã�����ʮ���ֽ��Ǹո���ɼ��ܺ������ */
    for (i = 0; i < 16; i++) {
        inbuf[i + 4] = rbuf[i];
    }

    /* ���»Ự��Կ����0x00000000+zlg_key_num */
    inbuf[3] = det_key_index;

    /* Data Decrypt calc
     * 00C0�����ܲ�����ʹ���ѵ���ĻỰ��Կ�������򳤶�Ϊ4+16
     */
    ret = am_fmse_data_encrypt_and_decrypt(handle,
                                           0x00C0,
                                           0x14,
                                           inbuf,
                                           rbuf,
                                          &rlen);
    if (ret != 0x9000) {
        printf("8. data decrypt failed\r\n");
    }
    printf("data decrypt SM4: ret = %04x, rlen = %d\r\n", ret, rlen);
    for (i = 0; i < rlen; i++) {                                                                    
        printf("%02x,",rbuf[i]);                                        
    }                                                                    
    printf("\r\n");
}

/* end of file */

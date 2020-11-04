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
 * \snippet demo_fmse_rsa_load_test.c src_fmse_rsa_load_test
 *
 * \internal
 * \par Modification history
 * - 1.00 20-07-01  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_fmse_rsa_load_test
 * \copydoc demo_fmse_rsa_load_test.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_fmse_a03.h"
#include "am_delay.h"

#define FILE_ID_11			0x0A080A98
#define FILE_ID_22			0x0A010A91

#define ZLG_RSA_ECPT_LOAD_TEST  1

/**
 * \brief �������
 */
void demo_fmse_rsa_load_test_entry (am_fmse_handle_t  handle)
{
    uint8_t i;
    uint8_t  relt_n[150] = {0}; /* ��СҪ���ڵ���144�ֽ� */
    uint8_t  relt_e[16] = {0};  /* ��СҪ���ڵ���16�ֽ� */  
    uint8_t relt_rbuf[512];
    uint8_t relt_inbuf[256];   
    uint16_t relt_rlen = 0;
    uint16_t relt_sw = 0;    
    uint8_t relt_session_key_index = 0;   
    uint8_t pin[4];

    relt_sw = am_fmse_file_select(handle, 0xDF01, relt_rbuf, &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("1. file selection failed\r\n");
    }

    pin[0] = 0x11;
    pin[1] = 0x22;
    pin[2] = 0x33;
    relt_sw = am_fmse_pin_verify(handle, 3, pin);
    if(relt_sw != 0x9000) {
        printf("2. pin verify failed\r\n");
    }

    /* gen rsa1024 key pair */
    printf("gen 1024RSA key test!\r\n");
    relt_sw = am_fmse_rsa_key_pair_gen(handle,
                                       RSA1024,
                                       EXP65537,
                                       FILE_ID_11,
                                       relt_rbuf,
                                      &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("3. rsa key pair gen failed\r\n");
    }
    printf("gen RSA key pair: sw = %04x, rlen = %d\r\n", relt_sw, relt_rlen);
    for(i = 0; i < relt_rlen; i++) {
        printf("%02x,",relt_rbuf[i]);
    }
    printf("\r\n");

    /* key len: 2 + 128 + 4 = 134 ��0x86 */
    relt_sw = am_fmse_binary_read(handle, 0, 0x86, relt_rbuf, &relt_rlen);
    if(relt_sw != 0x9000) { 
        printf("4. binary reading failed\r\n");
    }
    printf("read binary: sw = %04x, rlen = %d\r\n", relt_sw, relt_rlen);          
    for(i = 0; i < relt_rlen; i++) {
        printf("%02x,",relt_rbuf[i]);
    }
    printf("\r\n");

/* ���ĵ������ */
#ifdef ZLG_RSA_ECPT_LOAD_TEST

    printf("\r\n");
    printf("RSA ECPT LOAD TEST ��\r\n");
    relt_n[0] = 128;           /* �����Ƕԡ�len(N)||N�����м��ܣ�Ԥ��д�볤�� */
    relt_e[0] = 4;             /* �����Ƕԡ�len(E)||E�����м��ܣ�Ԥ��д�볤�� */
    am_fmse_memmove(&relt_n[1], &relt_rbuf[2], 128);
    am_fmse_memmove(&relt_e[1], &relt_rbuf[2 + 128], 4);

    am_fmse_memmove(relt_inbuf, 0, sizeof(relt_inbuf));
    am_fmse_memmove(relt_inbuf, "\xc1\x10", 2);                                 
    for(i = 0; i < 16; i++) {
        relt_inbuf[i + 2] = i + 2;                                                         
    }

    /* Import Session Key */
    /* 0110��SM1�㷨��������ݸ�ʽ */
    relt_sw = am_fmse_session_key_import(handle,
                                         0x0110,
                                         0x12,
                                         relt_inbuf,
                                         relt_rbuf,
                                        &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("5. session key import failed\r\n");
    }
    relt_session_key_index = relt_rbuf[0];
    printf("import session key: relt_sw = %04x, relt_rlen = %d\r\n", relt_sw, relt_rlen);

    /* ����ɹ������ص�ǰ��Կ������+9000 */
    for(i = 0; i < relt_rlen; i++) {
        printf("%02x,",relt_rbuf[i]);
    }
    printf("\r\n");

    /* ����Ự��Կ���ûỰ��Կ����N������E���� */
    /* pre data N */
    am_fmse_memset(relt_inbuf, 0, sizeof(relt_inbuf));

    /* 0x000000xx�����һ�ֽڱ�ʾ�Ự��Կ�������� */
    relt_inbuf[3] = relt_session_key_index;
    for(i = 0; i < 144; i++) {
        relt_inbuf[i + 4] = relt_n[i];                                                
    }

    /* Data Encrypt calc
     * 0040��Ψһ���ݿ飬���ܲ�����ʹ���Ե���ĻỰ��Կ,ECBģʽ��
     * ���ݰ���4�ֽ���Կ�����ţ����������ݳ��ȣ���1�ֽڵ�N�������ȣ�
     * 128�ֽ�N������15���ֽڵ���䣨���Ϊ0��
     */
    relt_sw = am_fmse_data_encrypt_and_decrypt(handle,
                                               0x0040,
                                               4 + 1 + 128 + 15,
                                               relt_inbuf,
                                               relt_rbuf,
                                              &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("6. data encrypt failed\r\n");
    }

    /* ���ؼ����ļӽ������� */
    printf("data encrypt N: relt_sw = %04x, relt_rlen = %d\r\n", relt_sw, relt_rlen);
    for(i = 0; i < relt_rlen; i++) {
        printf("%02x,",relt_rbuf[i]);
    }
    printf("\r\n");

    /* ��N�����ļ������ݱ���,���ܺ�����ݳ�����ԭ��������ĳ��ȣ�
     * ��1+128+15 = 144
     */
    am_fmse_memmove(relt_n, relt_rbuf, 144);

    /* pre data E */
    am_fmse_memset(relt_inbuf, 0, sizeof(relt_inbuf));

    /* 0x000000xx�����һ�ֽڱ�ʾ�Ự��Կ�������� */   
    relt_inbuf[3] = relt_session_key_index;

    for(i = 0; i < 16; i++) {
        relt_inbuf[i + 4] = relt_e[i];                                            
    }

    /* Data Encrypt calc
    * 0040��Ψһ���ݿ飬���ܲ�����ʹ���Ե���ĻỰ��Կ,ECBģʽ��
    * 4�ֽ���Կ�����������������ܵ����ݳ��ȣ���1�ֽ�E�������ȣ�
    * 4�ֽ�E������11���ֽ���䣨���Ϊ0��
    */
    relt_sw = am_fmse_data_encrypt_and_decrypt(handle,
                                               0x0040,
                                               4 + 1 + 4 + 11,
                                               relt_inbuf,
                                               relt_rbuf,
                                              &relt_rlen);
    if(relt_sw != 0x9000){
        printf("7. data decrypt failed\r\n");
    }

    /* ���ؼ����ļӽ������� */
    printf("data encrypt E: relt_sw = %04x, relt_rlen = %d\r\n", relt_sw, relt_rlen);
    for(i = 0; i < relt_rlen; i++) {
        printf("%02x,",relt_rbuf[i]);
    }
    printf("\r\n");

    /* ��E�����ļ������ݱ���,���ܺ�����ݳ�����ԭ����
     * ����ĳ��ȣ���1+4+11= 16
     */
    am_fmse_memmove(relt_e, relt_rbuf, 16);

    /* ��������0A05��Կ�ļ��е���ԭ0A08���еĹ�Կ����N��E(�Ѽ���) */   
    am_fmse_memset(relt_inbuf, 0, sizeof(relt_inbuf)); 
    am_fmse_memmove(relt_inbuf, "\xc0\x02\x0A\x05\xc3\x81\x90", 7);

    /* װ�ص�0a05�ļ�,�����Ǽ��ܺ�Ĳ���N */
    for(i = 0; i < 144; i++) {                       
        relt_inbuf[i + 7] = relt_n[i]; 
    }

    /* 0x8001,���ܴ��룬RSA1024 */
    relt_sw = am_fmse_rsa_key_install(handle,
                                      0x8001,
                                      7 + 144,
                                      relt_inbuf,
                                      relt_rbuf,
                                     &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("8. rsa key install failed\r\n");
    }

    am_fmse_memset(relt_inbuf, 0, sizeof(relt_inbuf));
    am_fmse_memmove(relt_inbuf, "\xc0\x02\x0A\x05\xc9\x10", 6);

    /* װ�ص�0a05�ļ��������Ǽ��ܺ�Ĳ���E */
    for(i = 0; i < 16; i++) {
        relt_inbuf[i + 6] = relt_e[i];
    }

    /* 0x8001,���ܴ��룬RSA1024 */
    relt_sw = am_fmse_rsa_key_install(handle,
                                      0x8001,
                                      6 + 16,
                                      relt_inbuf,
                                      relt_rbuf,
                                     &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("9. rsa key install failed\r\n");
    }

#else  /* ���ĵ��빫Կ */
    printf("\r\n");
    printf("RSA LOAD TEST��\r\n");
    am_fmse_memmove(relt_n, &relt_rbuf[2], 128);
    am_fmse_memmove(relt_e, &relt_rbuf[2 + 128], 4);

    /* �����ε��빫Կ��N��E���� */     
    am_fmse_memset(relt_inbuf, 0, sizeof(relt_inbuf));

    /* װ�ص�0a05�ļ��������ǲ���N */
    am_fmse_memmove(relt_inbuf, "\xc0\x02\x0a\x05\xc3\x81\x80", 7);
    for(i = 0; i < 128; i++) {
        relt_inbuf[i + 7] = relt_n[i];
    }

    /* 0x0001,���Ĵ��룬RSA1024 */
    relt_sw = am_fmse_rsa_key_install(handle,
                                      0x0001,
                                      7 + 128,
                                      relt_inbuf,
                                      relt_rbuf,
                                     &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("10. rsa key install failed\r\n");
    }

    am_fmse_memset(relt_inbuf, 0, sizeof(relt_inbuf));

    /* ����0a05�ļ� */
    am_fmse_memmove(relt_inbuf, "\xc0\x02\x0A\x05\xc9\x04", 6);
    for(i = 0; i < 4; i++) {
        relt_inbuf[i + 6] = relt_e[i];
    }

    /* 0x0001,���Ĵ��룬RSA1024 */
    relt_sw = am_fmse_rsa_key_install(handle,
                                      0x0001,
                                      6+4,
                                      relt_inbuf,
                                      relt_rbuf,
                                     &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("11. rsa key install failed\r\n");
    }    

#endif /* ZLG_RSA_ECPT_LOAD_TEST */

    /* ������õ���õ�0A05��Կ���мӽ��ܲ��ԣ�����0A98��˽Կ���н��ܣ�
     * 0A05�Ĺ�Կ��ʵ�Ǵ�0A01��Կ�ļ��������������
     */
    am_fmse_memset(relt_inbuf, 0, sizeof(relt_inbuf));
    am_fmse_memmove(relt_inbuf, "\xc0\x02\x0a\x05\xc1\x81\x80", 7);

    /* ׼������Ĵ����ܵ����ݣ����ԭʼ������1~128 */
    for(i = 0; i < 128; i++) {
        relt_inbuf[i + 7] = i + 1;
    }

    /* RSA PUB key calc
     * ��Կ���㣬4000��ʾ�������ͻؽ������ΪRSA1024����
     */
    relt_sw = am_fmse_rsa_pub_key_cal(handle,
                                      0x4000,
                                      128 + 7,
                                      relt_inbuf,
                                      relt_rbuf,
                                     &relt_rlen);
    if(relt_sw != 0x9000){
        relt_sw = 8;
    }

    printf("RSA pub key cal: relt_sw = %04x, relt_rlen = %d\r\n", relt_sw, relt_rlen);
    for(i = 0; i < relt_rlen; i++) {
        printf("%02x,",relt_rbuf[i]);
    }
    printf("\r\n");

    am_fmse_memset(relt_inbuf, 0, sizeof(relt_inbuf));

    /* �л���˽Կ�ļ� */
    am_fmse_memmove(relt_inbuf, "\xc2\x02\x0a\x98\xc1\x81\x80", 7);

    relt_inbuf[2] = (FILE_ID_11 >> 8) & 0xff;
    relt_inbuf[3] = (FILE_ID_11 >> 0) & 0xff; 

    /* �ѹ�Կ�����ݼ����Ľ������Ϊ����˽Կ�Ĵ��������� */
    for(i = 0; i < 128; i++) {
        relt_inbuf[i + 7] = relt_rbuf[i];
    }

    /* RSA PRI key calc
     * ˽Կ���㣬4000��ʾ�������ͻؽ������ΪRSA1024���� ��0x87Ϊ����Ķ���
     */
    relt_sw = am_fmse_rsa_pri_key_cal(handle,
                                      0x4000,
                                      0x87,
                                      relt_inbuf,
                                      relt_rbuf,
                                     &relt_rlen);
    if(relt_sw != 0x9000) {
        printf("12. rsa pri key cal failed\r\n");
    }

    /* ��Կ��������ݾ�˽Կ����󣬱�Ϊ�ʼ��ԭʼ���� */
    printf("RSA pri key cal: relt_sw = %04x, relt_rlen = %d\r\n", relt_sw, relt_rlen);
    for(i = 0; i < relt_rlen; i++) {
        printf("%02x,",relt_rbuf[i]);
    }
    printf("\r\n");   
}

/* end of file */

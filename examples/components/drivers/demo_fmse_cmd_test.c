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
 * \snippet demo_fmse_cmd_test.c src_fmse_cmd_test
 *
 * \internal
 * \par Modification history
 * - 1.00 20-07-01  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_fmse_cmd_test
 * \copydoc demo_fmse_cmd_test.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_fmse_a03.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_fmse_cmd_test_entry (am_fmse_handle_t handle)
{
    uint8_t  i;
    uint8_t  rbuf[1028];
    uint8_t  pin[4];
    uint16_t rlen   = 0;
    uint16_t ret    = 0;

    /* ѡ��ȫĿ¼DF01�����Ŀ¼ID��Ĭ�ϵģ�оƬ���������õ� */
    ret = am_fmse_file_select(handle, 0xDF01, rbuf, &rlen);              
    if(ret != 0x9000) {
        printf("1. file selection failed\r\n");
    }
    printf("select file: ret = %04x, rlen = %d\r\n", ret, rlen);
    for(i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    /* ѡ����Ŀ¼ */    
    ret = am_fmse_file_select(handle, 0x3F00, rbuf, &rlen);
    if(ret != 0x9000) { 
        printf("2. file selection failed\r\n");
    }
    printf("select file: ret = %04x, rlen = %d\r\n",ret,rlen);
    for(i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    /* ��ȡ���ֽ������ */
    ret = am_fmse_challenge_get(handle, 8, rbuf, &rlen);
    if(ret != 0x9000) {
        printf("3. challenge get failed\r\n");
    }
    printf("get challenge: ret = %04x, rlen = %d\r\n",ret,rlen);
    for(i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    /* ����ѡ��DF01 */
    ret = am_fmse_file_select(handle, 0xDF01, rbuf, &rlen);
    if(ret != 0x9000) {
        printf("4. file selection failed\r\n");
    }
    printf("select file: ret = %04x, rlen = %d\r\n",ret,rlen);
    for(i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    /* ѡ��0A08��Կ�ļ�������ļ�Ҳ��Ĭ�ϴ��ڵģ��������� */
    ret = am_fmse_file_select(handle, 0x0A08, rbuf, &rlen); 
    if(ret != 0x9000) {
        printf("5. file selection failed\r\n");
    }
    printf("select file: ret = %04x, rlen = %d\r\n",ret,rlen);
    for(i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    /* ѡ��0A98˽Կ�ļ�������ļ�Ҳ��Ĭ�ϴ��ڵģ��������� */
    ret = am_fmse_file_select(handle, 0x0A98, rbuf, &rlen);
    if(ret != 0x9000) {
        printf("6. file selection failed\r\n");
    }
    printf("select file: ret = %04x, rlen = %d\r\n",ret,rlen);
    for(i = 0; i < rlen; i++) {
        printf("%02x,",rbuf[i]);
    }
    printf("\r\n");

    pin[0] = 0x11;
    pin[1] = 0x22;
    pin[2] = 0x33;

    /* У��Ĭ�Ͽ��� */
    ret = am_fmse_pin_verify(handle, 3, pin);
    if(ret != 0x9000) {
        printf("7. pin verify failed\r\n");
    }
    printf("verify pin: ret = %04x\r\n",ret);
}

/* end of file */

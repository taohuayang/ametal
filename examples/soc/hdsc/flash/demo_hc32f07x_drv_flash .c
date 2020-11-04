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
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. �����������ڴ�ӡ "erase error!"��
 *   2. д��������ڴ�ӡ "program error!"��
 *   3. д��ɹ������ڴ�ӡָ��������(512)�� 32bit ʮ���������ݡ�
 *
 * \par Դ����
 * \snippet demo_hc32_drv_flash.c src_hc32_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_drv_flash
 * \copydoc demo_hc32_drv_flash.c
 */

/** [src_hc32_drv_flash] */
#include "ametal.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_hc32f07x_flash.h"

/**
 * \brief �������
 */
void demo_hc32f07x_drv_flash_entry (void *p_hw_flash, uint16_t sector)
{
    amhw_hc32f07x_flash_t *p_flash = (amhw_hc32f07x_flash_t *)p_hw_flash;

    int             i;
    uint32_t        status;    /* FLASH ����ִ��״̬ */
    static uint32_t data[512/4]; /* Ҫд�� FLASH ������ */
    static uint32_t temp[512/4]; /* �� FLASH �ж��������� */

    /* ���ݳ�ʼ�� */
    for (i = 0; i < 512/4; i++) {
        data[i] = i;
    }

    /* ��ʼ��ΪHCLK=48Mʱ��Ӧ��ʱ�����*/
    status = am_hc32f07x_flash_init(12, 1);

    if(status==0){

        AM_DBG_INFO("flash init ok!\r\n");
    }

    /* �������� */
    status = am_hc32f07x_flash_sector_erase(p_flash, sector << 9);

    /* ������������ ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");

        AM_FOREVER;
    }

    /* ��������д������ */
    status = am_hc32f07x_flash_sector_program(p_flash,
                                          sector << 9,
                                          data,
                                          512/4);

    /* ����д���������ͣ�ڴ˴� */
    if ((512/4) != status) {
        AM_DBG_INFO("program error!\r\n");

        AM_FOREVER;
    }

    /* ��������ȡ���� */
    for (i = 0; i < (512/4); i++) {
        temp[i] = *(uint32_t *)((i * 4) + (sector << 9));

        /* У�����ݣ�У��ʧ�ܣ�����ͣ�ڴ˴� */
        if (temp[i] != data[i]) {
            AM_DBG_INFO("verify error!\r\n");
            AM_FOREVER;
        }
    }

    for (i = 0; i < (512/4); i++) {
        AM_DBG_INFO("%04d  ", temp[i]);
    }
    AM_DBG_INFO("\r\nflash test success!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32_drv_flash] */

/* end of file */

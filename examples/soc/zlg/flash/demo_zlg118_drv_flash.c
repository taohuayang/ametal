/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. �����������ڴ�ӡ "erase error!"��
 *   2. д��������ڴ�ӡ "program error!"��
 *   3. д��ɹ������ڴ�ӡָ��������(SECTOR_SIZE)�� 32bit ʮ���������ݡ�
 *
 * \par Դ����
 * \snippet demo_zlg118_drv_flash.c src_zlg118_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_drv_flash
 * \copydoc demo_zlg118_drv_flash.c
 */

/** [src_zlg118_drv_flash] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_zlg118_flash.h"

/**
 * \brief �������
 */
void demo_zlg118_drv_flash_entry (void *p_hw_flash, uint16_t sector)
{
    amhw_zlg118_flash_t *p_flash = (amhw_zlg118_flash_t *)p_hw_flash;

    int             i;
    uint32_t        status;         /* FLASH ����ִ��״̬ */
    static uint32_t data[SECTOR_SIZE]; /* Ҫд�� FLASH ������ */
    static uint32_t temp[SECTOR_SIZE]; /* �� FLASH �ж��������� */

    /* ���ݳ�ʼ�� */
    for (i = 0; i < SECTOR_SIZE; i++) {
        data[i] = i;
    }

    /* �������� */
    status = am_zlg118_flash_sector_erase(p_flash, sector << 9);

    /* ������������ ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");

        AM_FOREVER;
    }

    /* ��������д������ */
    status = am_zlg118_flash_sector_program(p_flash,
                                            sector << 9,
                                            data,
                                            SECTOR_SIZE);

    /* ����д���������ͣ�ڴ˴� */
    if ((SECTOR_SIZE) != status) {
        AM_DBG_INFO("program error!\r\n");

        AM_FOREVER;
    }

    /* ��������ȡ���� */
    for (i = 0; i < SECTOR_SIZE; i++) {
        temp[i] = *(uint32_t *)((i * 4) + (sector << 9));

        /* У�����ݣ�У��ʧ�ܣ�����ͣ�ڴ˴� */
        if (temp[i] != data[i]) {
            AM_DBG_INFO("verify error!\r\n");
            AM_FOREVER;
        }
    }

    for (i = 0; i < SECTOR_SIZE; i++) {
        AM_DBG_INFO("%04d  ", temp[i]);
    }
    AM_DBG_INFO("\r\nflash test success!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg118_drv_flash] */

/* end of file */

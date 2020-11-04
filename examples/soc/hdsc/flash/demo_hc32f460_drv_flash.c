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
 *   ��flash�����ֱ�̡�
 *   1. �����������ڴ�ӡ "erase error!"��
 *   2. д��������ڴ�ӡ "program error!"��
 *   3. д��ɹ������ڴ�ӡָ��ҳ��ʮ���������ݡ�
 *
 * \par Դ����
 * \snippet demo_hc32f460_drv_flash.c src_hc32f460_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_drv_flash
 * \copydoc demo_hc32f460_drv_flash.c
 */

/** [src_hc32f460_drv_flash] */
#include "ametal.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_hc32f460_flash.h"

/**< \brief ������С ���ֽ�(8bit)Ϊ��λ */
#define SECTOR_SIZE (8 * 1024)
#define __DATA_SIZE ((SECTOR_SIZE / 4))

/**
 * \brief �������
 */
void demo_hc32f460_drv_flash_entry (void *p_hw_flash, uint16_t sector)
{
    amhw_hc32f460_flash_t *p_flash = (amhw_hc32f460_flash_t *)p_hw_flash;

    int             i;
    uint32_t        status;    /* FLASH ����ִ��״̬ */

    /* Ҫд�� FLASH ������ */
    static uint32_t data1[__DATA_SIZE];

    /* �� FLASH �ж��������� */
    static uint32_t temp1[__DATA_SIZE];

    /* ���ݳ�ʼ�� */
    for (i = 0; i < __DATA_SIZE; i++) {
        data1[i] = i;
    }

/*******************************************************************************
���ֱ��
*******************************************************************************/

    am_hc32f460_flash_init(p_flash);

    /* ����ҳ */
    status = am_hc32f460_flash_sector_erase(p_flash, sector * SECTOR_SIZE);

    /* ҳ�������� ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��д������ */
    status = am_hc32f460_flash_sector_program(p_flash,
                                              sector * SECTOR_SIZE,
                                              data1,
                                              __DATA_SIZE);

    /* ҳд���������ͣ�ڴ˴� */
    if (__DATA_SIZE != status) {
        AM_DBG_INFO("word program error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��ȡ���� */
    for (i = 0; i < __DATA_SIZE; i++) {
        temp1[i] = *(uint32_t *)((i * 4) + (sector * SECTOR_SIZE));

        /* У�����ݣ�У��ʧ�ܣ�����ͣ�ڴ˴� */
        if (temp1[i] != data1[i]) {
            AM_DBG_INFO("word verify error!\r\n");
            AM_FOREVER;
        }
    }

    for (i = 0; i < __DATA_SIZE; i++) {
        AM_DBG_INFO("%04d  ", temp1[i]);
    }
    AM_DBG_INFO("\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f460_drv_flash] */

/* end of file */

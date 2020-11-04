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
 *   ��flash�����֡����֡��ֽڱ�̡�
 *   1. �����������ڴ�ӡ "erase error!"��
 *   2. д��������ڴ�ӡ "program error!"��
 *   3. д��ɹ������ڴ�ӡָ��ҳ��ʮ���������ݡ�
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
#include "am_hc32_flash.h"

#define __DATA_SIZE ((SECTOR_SIZE / 2) - 1)

/**
 * \brief �������
 */
void demo_hc32_drv_flash_entry (void *p_hw_flash, uint16_t sector)
{
    amhw_hc32_flash_t *p_flash = (amhw_hc32_flash_t *)p_hw_flash;

    int             i;
    uint32_t        status;    /* FLASH ����ִ��״̬ */

    /* Ҫд�� FLASH ������ */
    static uint32_t data1[__DATA_SIZE];
    static uint16_t data2[__DATA_SIZE];
    static uint8_t  data3[__DATA_SIZE];

    /* �� FLASH �ж��������� */
    static uint32_t temp1[__DATA_SIZE];
    static uint16_t temp2[__DATA_SIZE];
    static uint8_t  temp3[__DATA_SIZE];

    /* ���ݳ�ʼ�� */
    for (i = 0; i < __DATA_SIZE; i++) {
        data1[i] = i;
        data2[i] = i;
        data3[i] = i;
    }

/*******************************************************************************
���ֱ��
*******************************************************************************/

    /* ����ҳ */
    status = am_hc32_flash_sector_erase(p_flash, sector << 9);
    status = am_hc32_flash_sector_erase(p_flash, (sector + 1) << 9);    /* ������������һҳ */

    /* ҳ�������� ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��д������ */
    status = am_hc32_flash_sector_program(p_flash,
                                          sector << 9,
                                          data1,
                                          __DATA_SIZE);

    /* ҳд���������ͣ�ڴ˴� */
    if (__DATA_SIZE != status) {
        AM_DBG_INFO("word program error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��ȡ���� */
    for (i = 0; i < __DATA_SIZE; i++) {
        temp1[i] = *(uint32_t *)((i * 4) + (sector << 9));

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

/*******************************************************************************
�����ֱ��
*******************************************************************************/

    /* ����ҳ */
    status = am_hc32_flash_sector_erase(p_flash, sector << 9);

    /* ҳ�������� ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��д������ */
    status = am_hc32_flash_sector_halfword_program(p_flash,
                                                   sector << 9,
                                                   data2,
                                                   __DATA_SIZE);

    /* ҳд���������ͣ�ڴ˴� */
    if (__DATA_SIZE != status) {
        AM_DBG_INFO("half word program error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��ȡ���� */
    for (i = 0; i < __DATA_SIZE; i++) {
        temp2[i] = *(uint16_t *)((i * 2) + (sector << 9));

        /* У�����ݣ�У��ʧ�ܣ�����ͣ�ڴ˴� */
        if (temp2[i] != data2[i]) {
            AM_DBG_INFO("half word verify error!\r\n");
            AM_FOREVER;
        }
    }

    for (i = 0; i < __DATA_SIZE; i++) {
        AM_DBG_INFO("%04d  ", temp2[i]);
    }
    AM_DBG_INFO("\r\n");

/*******************************************************************************
���ֽڱ��
*******************************************************************************/

    /* ����ҳ */
    status = am_hc32_flash_sector_erase(p_flash, sector << 9);

    /* ҳ�������� ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��д������ */
    status = am_hc32_flash_sector_byte_program(p_flash,
                                              sector << 9,
                                              data3,
                                              __DATA_SIZE);

    /* ҳд���������ͣ�ڴ˴� */
    if (__DATA_SIZE != status) {
        AM_DBG_INFO("byte program error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��ȡ���� */
    for (i = 0; i < __DATA_SIZE; i++) {
        temp3[i] = *(uint8_t *)(i + (sector << 9));

        /* У�����ݣ�У��ʧ�ܣ�����ͣ�ڴ˴� */
        if (temp3[i] != data3[i]) {
            AM_DBG_INFO("byte verify error!\r\n");
            AM_FOREVER;
        }
    }

    for (i = 0; i < __DATA_SIZE; i++) {
        AM_DBG_INFO("%04d  ", temp3[i]);
    }
    AM_DBG_INFO("\r\n");

    AM_DBG_INFO("\r\nflash test success!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32_drv_flash] */

/* end of file */

/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www..cn/
*******************************************************************************/

/**
 * \file
 * \brief bootloader firmware store by flash drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-15  yrh, first implementation
 * \endinternal
 */
#include "am_boot_firmware_flash.h"
#include "am_boot_firmware.h"
#include "am_boot.h"
#include <string.h>

static int __firmware_flash_start(void *p_drv);
static int __firmware_flash_bytes(void *p_drv, uint8_t *p_data, uint32_t firmware_size);
static int __firmware_flash_final(void *p_drv);
static int __firmware_verify(void *p_drv, am_boot_firmware_verify_info_t *p_verify_info);

/**
 * \brief BootLoader �̼���ŵ�flash�ı�׼�ӿڵ�ʵ��
 */
static struct am_boot_firmware_drv_funcs __g_firmware_flash_drv_funcs = {
    __firmware_flash_start,
    __firmware_flash_bytes,
    __firmware_flash_final,
    __firmware_verify,
};

/**
 * \brief �̼���ŵ�flash�Ŀ�ʼ����
 */
static int __firmware_flash_start (void *p_drv)
{
    am_boot_firmware_flash_dev_t *p_dev = (am_boot_firmware_flash_dev_t *)p_drv;
    int ret;

    am_boot_flash_info_t *flash_info = NULL;
    p_dev->flash_handle->p_funcs->pfn_flash_info_get(p_dev->flash_handle->p_drv,
                                                    &flash_info);

    uint32_t flash_end_addr = flash_info->flash_start_addr + \
        flash_info->flash_size;

    if(p_dev->firmware_dst_addr < flash_info->flash_start_addr) {
        return AM_EFAULT;
    }

    if((p_dev->firmware_dst_addr + p_dev->p_devinfo->app_area_size) > flash_end_addr){
        return AM_ENOMEM;
    }

    p_dev->firmware_total_size     = 0;
    p_dev->erase_sector_start_addr = p_dev->firmware_dst_addr;
    p_dev->curr_program_flash_addr = p_dev->firmware_dst_addr;
    p_dev->curr_buf_data_size      = 0;


    ret = am_boot_flash_erase_region(p_dev->flash_handle,
                                     p_dev->erase_sector_start_addr,
                                     p_dev->p_devinfo->app_area_size);

    if(ret != AM_OK) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief �洢�̼�
 */
static int __firmware_flash_bytes (void *p_drv, uint8_t *p_data, uint32_t firmware_size)
{
    if(p_data == NULL) {
        return AM_EINVAL;
    }
    if(firmware_size == 0) {
        return AM_OK;
    }
    int      leave_size;   /* ʣ�� */
    int      ret, i;
    uint32_t program_size; /* ÿ��д��flash�ĵ����ݴ�С  */

    /* �����������滹������ʱ����Ҫ�����������´���Ĺ̼����������� data_program_start_index ָ�����껺������
     * �̼����ݵ���ʼ�±꣬Ҳ��û���뻺���������ݵ���ʼ�±�
     */
    uint32_t data_program_start_index = 0;

    /* ������ջ�������С��������д��flash�󣬹̼�ʣ������ݲ��㻺��Ĵ�С����Ҫ��ʱ���ڻ������У�
     * �ȴ��´����ݹ����������������С��������д��flash��leave_firmware_index����ָ��Ҫ��ʱ���뻺���������ݵ���ʼ�±�
     */
    uint32_t leave_firmware_index;
    am_boot_firmware_flash_dev_t *p_dev = (am_boot_firmware_flash_dev_t *)p_drv;

    p_dev->firmware_total_size += firmware_size;

    am_boot_flash_info_t *flash_info = NULL;
    p_dev->flash_handle->p_funcs->pfn_flash_info_get(p_dev->flash_handle->p_drv,
                                                    &flash_info);

    uint32_t flash_end_addr = flash_info->flash_start_addr + \
        flash_info->flash_size - 1;

    if((p_dev->firmware_dst_addr + p_dev->firmware_total_size) > flash_end_addr) {
        return AM_ENOMEM;
    }

    /* ����������ʣ������û��д��flash */
    if(p_dev->curr_buf_data_size != 0) {
        for(i = 0; (p_dev->curr_buf_data_size < p_dev->buf_data_size) && (i < firmware_size); i++) {
            p_dev->buf_data[p_dev->curr_buf_data_size++] = p_data[i];
        }

        if(p_dev->curr_buf_data_size == p_dev->buf_data_size) {
            ret = am_boot_flash_program(
                p_dev->flash_handle,
                p_dev->curr_program_flash_addr,
                p_dev->buf_data,
                p_dev->buf_data_size);
            if(ret != AM_OK) {
                return AM_ERROR;
            }
            p_dev->curr_program_flash_addr += p_dev->buf_data_size;
            p_dev->curr_buf_data_size = 0;
        }

        if(i < firmware_size) {
            data_program_start_index = i;
        } else {
            return AM_OK;
        }
    }

    firmware_size = firmware_size - data_program_start_index;
    leave_size    = firmware_size & (p_dev->buf_data_size - 1);
    program_size  = firmware_size - leave_size;
    leave_firmware_index = program_size + data_program_start_index;

    ret = am_boot_flash_program(
        p_dev->flash_handle,
        p_dev->curr_program_flash_addr,
       &p_data[data_program_start_index],
        program_size);
    if(ret != AM_OK) {
        return AM_ERROR;
    }
    p_dev->curr_program_flash_addr += program_size;

    for(i = 0; i < leave_size; i++) {
        p_dev->buf_data[p_dev->curr_buf_data_size++] = p_data[leave_firmware_index++];
    }

    return AM_OK;
}
/**
 * \brief �̼��洢����
 */
static int __firmware_flash_final(void *p_drv)
{
    am_boot_firmware_flash_dev_t *p_dev = (am_boot_firmware_flash_dev_t *)p_drv;
    int ret;
    if(p_dev->curr_buf_data_size != 0) {
        /* ��������̼����ʱ���������л������� ���Ҳ���ʱ��Ҫ��0�������������ٽ�ʣ�������д��flash*/
        while(p_dev->curr_buf_data_size < p_dev->buf_data_size) {
            p_dev->buf_data[p_dev->curr_buf_data_size++] = 0xff;
        }
        ret = am_boot_flash_program(
            p_dev->flash_handle,
            p_dev->curr_program_flash_addr,
            p_dev->buf_data,
            p_dev->buf_data_size);
        if(ret != AM_OK) {
            return AM_ERROR;
        }
    }
    p_dev->curr_buf_data_size      = 0;
    p_dev->firmware_total_size     = 0;
    p_dev->erase_sector_start_addr = p_dev->firmware_dst_addr;
    p_dev->curr_program_flash_addr = p_dev->firmware_dst_addr;

    return AM_OK;
}

/**
 * \brief �̼���У��
 */
static int __firmware_verify(void *p_drv, am_boot_firmware_verify_info_t *p_verify_info)
{
    am_boot_firmware_flash_dev_t *p_dev = (am_boot_firmware_flash_dev_t *)p_drv;
    uint8_t *p_flash = (uint8_t *)(p_dev->firmware_dst_addr );
    uint32_t cal_verify = 0, i = 0;

    for (i = 0 ; i < p_verify_info->len ; i++) {
        cal_verify += p_flash[i];
    }

    if (cal_verify == p_verify_info->verify_value) {
        //am_boot_update_flag_set(AM_BOOTLOADER_FLAG_APP);
        return AM_OK;
    } else {
        return -AM_ERROR;
    }
}

/**
 * \brief �̼�flash�洢��ʼ��
 */
am_boot_firmware_handle_t am_boot_firmware_flash_init (
    am_boot_firmware_flash_dev_t     *p_dev,
    am_boot_firmware_flash_devinfo_t *p_devinfo,
    am_boot_flash_handle_t            flash_handle)
{
    p_dev->firmware_flash_serv.pfn_funcs = &__g_firmware_flash_drv_funcs;
    p_dev->firmware_flash_serv.p_drv     = p_dev;
    p_dev->flash_handle                  = flash_handle;
    p_dev->firmware_dst_addr             = p_devinfo->firmware_dst_addr;
    p_dev->buf_data_size                 = p_devinfo->buf_size;
    p_dev->p_devinfo                     = p_devinfo;

    return &p_dev->firmware_flash_serv;
}

/**
 * \brief �̼�flash�洢���ʼ��
 */
void am_boot_firmware_flash_deint(void)
{

}
/* end of file */

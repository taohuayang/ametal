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
 * \brief bootloader drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-15  yrh, first implementation
 * \endinternal
 */
#include "am_zml165_boot.h"
#include "am_zml165.h"
#include "am_arm_nvic.h"
#include "am_int.h"
#include "am_zlg_flash.h"

static am_zml165_boot_dev_t *__gp_boot_dev = NULL;
static int __boot_source_release(void);
static int __boot_update_flag_get_and_dispose (void);
/**
 * \brief �ж�Ӧ�ô����Ƿ��ִ��
 */
am_bool_t am_boot_app_is_ready(void)
{
    if(__gp_boot_dev == NULL) {
        return AM_FALSE;
    }

    if(AM_OK != __boot_update_flag_get_and_dispose()) {
        return AM_FALSE;
    }

    uint32_t app_start_addr = __gp_boot_dev->p_devinfo->app_start_addr;
    if ((!app_start_addr) || (app_start_addr == 0xffffffff)) {
        return AM_FALSE;
    }
    uint32_t flash_start_addr = __gp_boot_dev->p_devinfo->flash_start_addr;
    uint32_t flash_end_adrr   = __gp_boot_dev->p_devinfo->flash_start_addr + \
        __gp_boot_dev->p_devinfo->flash_size - 1;
    uint32_t ram_start_addr = __gp_boot_dev->p_devinfo->ram_start_addr;
    uint32_t ram_size    = __gp_boot_dev->p_devinfo->ram_size;


    if(app_start_addr < flash_start_addr || app_start_addr > flash_end_adrr) {
        return AM_FALSE;
    } else {
        if((*(uint32_t *)app_start_addr) > (ram_start_addr + ram_size )||
           (*(uint32_t *)app_start_addr) < ram_start_addr) {
            return AM_FALSE;
        }
    }
    return AM_TRUE;
}
/**
 * \brief ��ת��Ӧ�ô���
 */
int am_boot_go_application(void)
{
    if(__gp_boot_dev == NULL) {
        return -AM_ERROR;
    }

    uint32_t app_start_addr = __gp_boot_dev->p_devinfo->app_start_addr;
    uint32_t stack_pointer = *(uint32_t *)app_start_addr;

    void (*farewell_bootloader)(void);

    farewell_bootloader = (void (*)(void))(*(uint32_t *)(app_start_addr + 4));

   __boot_source_release();

    /* ����ջָ�� */
    __set_MSP(stack_pointer);
    __set_PSP(stack_pointer);

    /* ��ת��Ӧ�ô��� */
    farewell_bootloader();
    /*���������ת�����벻��ִ�е�����*/
    return -AM_ERROR;
}

/**
 * \brief ϵͳ����
 */
void am_boot_reset(void)
{
    if(__gp_boot_dev == NULL) {
        return;
    }
    NVIC_SystemReset();
}

/**
 * \brief ˫��bootloader��־����
 *
 * \param[in] flags ��־
 * AM_BOOTLOADER_FLAG_APP    ˫���û�������Ч
 * AM_BOOTLOADER_FLAG_UPDATE ˫������������Ч
 * AM_BOOTLOADER_FLAG_NO     ˫���޴���
 *
 * \retval AM_OK �ɹ�
 */
int am_boot_update_flag_set(uint32_t flag)
{
    int ret = 0;
    if(__gp_boot_dev == NULL) {
        return -AM_ERROR;
    }

    ret = am_boot_flash_erase_region(__gp_boot_dev->flash_handle,
                                     __gp_boot_dev->p_devinfo->update_flag_addr,
                                     1024);
    if(ret != AM_OK) {
        return AM_ERROR;
    }

    ret = am_boot_flash_program(__gp_boot_dev->flash_handle,
                                __gp_boot_dev->p_devinfo->update_flag_addr,
                                (uint8_t *)&flag,
                                 4);
    if(ret != AM_OK) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief ˫��bootloader��־��ȡ������Ӧ����
 *
 */
static int __boot_update_flag_get_and_dispose ()
{
    uint32_t flags;
    uint16_t i = 0, ret;
    if(__gp_boot_dev == NULL) {
        return -AM_ERROR;
    }

   uint32_t addr = (uint32_t)__gp_boot_dev->p_devinfo->update_flag_addr;

   flags = *(uint32_t *)(addr);

   if (flags == AM_BOOTLOADER_FLAG_APP) {
       return AM_OK;
   } else if(flags == AM_BOOTLOADER_FLAG_UPDATE) {
       for(i = 0; i < __gp_boot_dev->p_devinfo->app_region_sector_count; i++) {
           am_boot_flash_erase_region(
               __gp_boot_dev->flash_handle,
               __gp_boot_dev->p_devinfo->app_start_addr + i * 1024,
               1024);
       }
       am_kprintf("bootloader : copying firmware from application backup...\r\n");
       for (i = 0 ; i < __gp_boot_dev->p_devinfo->app_region_sector_count ; i++) {

           ret = am_boot_flash_program(
               __gp_boot_dev->flash_handle,
               __gp_boot_dev->p_devinfo->app_start_addr + i * 1024,
               (uint8_t *)(i * 1024 + __gp_boot_dev->p_devinfo->update_start_addr) ,
               1024);

           if (ret != AM_OK) {
               am_kprintf("bootloader : firmware update error\r\n");
               return AM_ERROR;
           }
       }
       am_boot_update_flag_set(AM_BOOTLOADER_FLAG_APP);
   } else {
       return AM_ERROR;
   }

   return AM_OK;
}

/**
 * \brief �ͷ�ϵͳ��Դ
 *
 * \note bootloader����ת��Ӧ�ô���ǰ��������ô˽ӿڣ�
 *       ��bootloader���������Դ���߳�ʼ����ĳЩ���趼Ӧ�����ͷźͽ��ʼ���������Ӧ�ó������Ӱ�졣

 * \retval AM_OK : �ɹ�
 */
static int __boot_source_release(void)
{
    am_arm_nvic_deinit();
    __disable_irq();
    return AM_OK;
}

/**
 * \brief BootLoader��ʼ������
 */
int am_zml165_boot_init(am_zml165_boot_dev_t     *p_dev,
                        am_zml165_boot_devinfo_t *p_devinfo,
                        am_boot_flash_handle_t    flash_handle)
{
    if(p_devinfo == NULL || p_dev == NULL) {
        return -AM_ENXIO;
    }
    p_dev->flash_handle = flash_handle;
    p_dev->p_devinfo    = p_devinfo;

    __gp_boot_dev = p_dev;

    return AM_OK;
}

/* end of file */

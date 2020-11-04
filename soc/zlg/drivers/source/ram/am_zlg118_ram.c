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
 * \brief RAMģ���������ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-08
 * \endinternal
 */

#include "zlg118_inum.h"
#include "am_zlg118_ram.h"
#include "am_types.h"
#include "am_bitops.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "ametal.h"

/******************************************************************************
*   ��������
******************************************************************************/

/** \brief RAM �жϴ����� */
static void __ram_irq_handler (void *p_arg)
{
    amhw_zlg118_ram_err_clear((amhw_zlg118_ram_t *)p_arg);
    am_kprintf("RAM IRQ...\r\n");
}

/**
 * \brief RAMģ���ʼ��
 *
 * \param[in] p_hw_ram ָ��RAM�Ĵ������ָ��
 *
 * \return ��
 */
void am_zlg118_ram_init (amhw_zlg118_ram_t *p_hw_ram)
{
    /* ��������־ */
    amhw_zlg118_ram_err_clear(p_hw_ram);
    /* ʹ�ܳ������ж� */
    amhw_zlg118_ram_ie_enable(p_hw_ram);

    /* �����ж� */
    am_int_connect(INUM_FLASH_RAM, __ram_irq_handler, p_hw_ram);
    am_int_enable(INUM_FLASH_RAM);
}

/**
 * \brief ����RAM����
 *
 * \param[in] p_hw_ram    ָ��RAM�Ĵ������ָ��
 * \param[in] start_addr  ��ʼ��ַ
 * \param[in] size        ��С
 *
 * \return >0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_zlg118_ram_erase (amhw_zlg118_ram_t *p_hw_ram,
                             uint32_t           start_addr,
                             uint16_t           size)
{
    uint16_t i;

    if (start_addr < RAM_ADDRESS_BASE) {
        start_addr += RAM_ADDRESS_BASE;
    }
    if (RAM_ADDRESS_SIZE < start_addr) {
        return -AM_EINVAL;
    }

    for (i = 0; i < size; i++) {
        if(start_addr + i > RAM_ADDRESS_SIZE) {
            break;
        }
        *(uint8_t *)(start_addr + i) = 0;
    }

    return AM_OK;
}

/**
 * \brief ��������̻򲿷��������
 *
 * \param[in] p_hw_ram  ָ��RAM�Ĵ������ָ��
 * \param[in] dst_addr  д�뵽ram����ʼ��ַ
 * \param[in] p_src     Ҫд�뵽ram�е����ݵ���ʼ��ַ
 * \param[in] size      д����(32bit)�ĸ���
 *
 * \retval i ʵ�ʳɹ�д�������
 */
int32_t am_zlg118_ram_write (amhw_zlg118_ram_t *p_hw_ram,
                             uint32_t           dst_addr,
                             uint8_t           *p_src,
                             uint16_t           size)
{
    uint16_t i;

    if (dst_addr < RAM_ADDRESS_BASE) {
        dst_addr += RAM_ADDRESS_BASE;
    }

    /** size���ܴ��������Ĵ�С */
    if (size > RAM_SIZE || dst_addr >= RAM_ADDRESS_SIZE) {
        return -AM_EINVAL;
    }

    for (i = 0; i < size; i++) {
        if(dst_addr + i > RAM_ADDRESS_SIZE) {
            break;
        }
        *(uint8_t *)(dst_addr + i) = *(p_src + i);
    }

    return i;
}

/**
 * \brief ��RAM��ȡ����
 *
 * \param[in] p_hw_ram   ָ��RAM�Ĵ������ָ��
 * \param[in] dst_addr   ��ȡ��ram��ʼ��ַ
 * \param[in] p_src      Ҫ��ȡram�е����ݵ���ʼ��ַ
 * \param[in] size       ��ȡ�ֽڵĸ���
 *
 * \retval i ʵ�ʳɹ���ȡ������
 */
int32_t am_zlg118_ram_read (amhw_zlg118_ram_t *p_hw_ram,
                            uint32_t           dst_addr,
                            uint8_t           *p_src,
                            uint16_t           size)
{
    uint16_t i;

    if (dst_addr < RAM_ADDRESS_BASE) {
        dst_addr += RAM_ADDRESS_BASE;
    }

    /** size���ܴ��������Ĵ�С */
    if (size > RAM_SIZE || dst_addr >= RAM_ADDRESS_SIZE) {
        return -AM_EINVAL;
    }

    for (i = 0; i < size; i++) {
        if(dst_addr + i > RAM_ADDRESS_SIZE) {
            break;
        }
        *(p_src + i) = *(uint8_t *)(dst_addr + i);
    }

    return i;
}

/* end of file */

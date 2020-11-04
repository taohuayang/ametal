/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg237.cn/
*******************************************************************************/

/**
 * \file
 * \brief Flashģ���������ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  ari, first implementation
 * \endinternal
 */

#include "am_zlg237_flash.h"
#include "am_types.h"
#include "am_bitops.h"
#include "ametal.h"

/*******************************************************************************
  defines
*******************************************************************************/

#define UNLOCK_FALSH_KEY1   0x45670123  /**< \brief unlock key word */
#define UNLOCK_FALSH_KEY2   0xCDEF89AB  /**< \brief unlock key word */

#define FALSH_ADDRESS_BASE   0x08000000
#define FALSH_ADDRESS_SIZE   0x08000000 + FLASH_SIZE
/******************************************************************************
*   ��������
******************************************************************************/

/**
 * \brief Flashģ���ʼ��
 *
 * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
 *
 * \return ��
 */
void am_zlg237_flash_init (amhw_zlg237_flash_t *p_hw_flash)
{
    amhw_zlg237_flash_key_set(p_hw_flash, UNLOCK_FALSH_KEY1);
    amhw_zlg237_flash_key_set(p_hw_flash, UNLOCK_FALSH_KEY2);

    amhw_zlg237_flash_status_flag_clr(p_hw_flash,
                                      AMHW_ZLG237_FLASH_WRPRTERR_FLAG |
                                      AMHW_ZLG237_FLASH_PGERR_FLAG    |
                                      AMHW_ZLG237_FLASH_BUSY_FLAG);

    //amhw_zlg237_flash_set_prebuff_on(p_hw_flash, AM_FALSE);
    //amhw_zlg237_flash_half_cycle_enable(p_hw_flash, AM_FALSE);

    return;
}

/**
 * \brief ����ҳ��ҳ��СΪ1024��
 *
 * \param[in] p_hw_gpio  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr ҳ����ʼ��ַ
 *
 * \return > 0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_zlg237_flash_page_erase (amhw_zlg237_flash_t *p_hw_flash,
                                    uint32_t             start_addr)
{
    if (start_addr < FALSH_ADDRESS_BASE) {
        start_addr += FALSH_ADDRESS_BASE;
    }
    if (FALSH_ADDRESS_SIZE < start_addr) {
        return -AM_EINVAL;
    }
    while (amhw_zlg237_flash_status_check(p_hw_flash,
                                          AMHW_ZLG237_FLASH_BUSY_FLAG)) {
        ;
    }

    if (amhw_zlg237_flash_cs_reg_get(p_hw_flash) & AMHW_ZLG237_FLASH_LOCK_MASK) {
        amhw_zlg237_flash_key_set(p_hw_flash, UNLOCK_FALSH_KEY1);
        amhw_zlg237_flash_key_set(p_hw_flash, UNLOCK_FALSH_KEY2);
    }

    amhw_zlg237_flash_cs_reg_clr(p_hw_flash, AMHW_ZLG237_FLASH_PROGRAM_MASK |
                                             AMHW_ZLG237_FLASH_MASS_ERASE_MASK);

    amhw_zlg237_flash_cs_reg_set(p_hw_flash,
            AMHW_ZLG237_FLASH_PAGE_ERASE_MASK);

    amhw_zlg237_flash_ecr_haer_set(p_hw_flash,
                                   AMHW_ZLG237_FLASH_NO_HALF_PAGE_ERASE);

    amhw_zlg237_flash_address_set(p_hw_flash, start_addr);

    amhw_zlg237_flash_cs_reg_set(p_hw_flash,
                                 AMHW_ZLG237_FLASH_START_MASK);

    while (amhw_zlg237_flash_status_check(p_hw_flash,
                                          AMHW_ZLG237_FLASH_BUSY_FLAG)) {
        ;
    }

    return AM_OK;
}


/**
 * \brief ������ҳ��ҳ��СΪ1024��
 *
 * \param[in] p_hw_gpio  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr ��ҳ����ʼ��ַ
 *
 * \return > 0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_zlg237_flash_half_page_erase (amhw_zlg237_flash_t *p_hw_flash,
                                         uint32_t             start_addr)
{
    if (start_addr < FALSH_ADDRESS_BASE) {
        start_addr += FALSH_ADDRESS_BASE;
    }
    if (FALSH_ADDRESS_SIZE < start_addr) {
        return -AM_EINVAL;
    }
    while (amhw_zlg237_flash_status_check(p_hw_flash,
                                          AMHW_ZLG237_FLASH_BUSY_FLAG)) {
        ;
    }

    if (amhw_zlg237_flash_cs_reg_get(p_hw_flash) & AMHW_ZLG237_FLASH_LOCK_MASK) {
        amhw_zlg237_flash_key_set(p_hw_flash, UNLOCK_FALSH_KEY1);
        amhw_zlg237_flash_key_set(p_hw_flash, UNLOCK_FALSH_KEY2);
    }

    amhw_zlg237_flash_cs_reg_clr(p_hw_flash, AMHW_ZLG237_FLASH_PAGE_ERASE_MASK |
                                             AMHW_ZLG237_FLASH_PROGRAM_MASK);

    amhw_zlg237_flash_ecr_haer_set(p_hw_flash,
                                   AMHW_ZLG237_FLASH_HALF_PAGE_ERASE);

    amhw_zlg237_flash_address_set(p_hw_flash, start_addr);

    amhw_zlg237_flash_cs_reg_set(p_hw_flash,
                                 AMHW_ZLG237_FLASH_START_MASK);

    while (amhw_zlg237_flash_status_check(p_hw_flash,
                                          AMHW_ZLG237_FLASH_BUSY_FLAG)) {
        ;
    }
    amhw_zlg237_flash_ecr_haer_set(p_hw_flash, AMHW_ZLG237_FLASH_NO_HALF_PAGE_ERASE);

    return AM_OK;
}


/**
 * \brief ��������̻򲿷��������
 *
 * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
 * \param[in] dst_addr  д�뵽flash����ʼ��ַ
 * \param[in] p_src     Ҫд�뵽flash�е����ݵ���ʼ��ַ
 * \param[in] size      д����(32bit)�ĸ���
 *
 * \retval 0 ʵ�ʳɹ�д�������
 */
int32_t am_zlg237_flash_sector_program (amhw_zlg237_flash_t *p_hw_flash,
                                        uint32_t             dst_addr,
                                        uint32_t            *p_src,
                                        uint32_t             size)
{
    uint32_t i;

    if (dst_addr < FALSH_ADDRESS_BASE) {
        dst_addr += FALSH_ADDRESS_BASE;
    }

    /** size���ܴ��������Ĵ�С */
    if (size > SECTOR_SIZE || dst_addr >= FALSH_ADDRESS_SIZE) {
        return -AM_EINVAL;
    }

    if (amhw_zlg237_flash_cs_reg_get(p_hw_flash) & AMHW_ZLG237_FLASH_LOCK_MASK) {
        amhw_zlg237_flash_key_set(p_hw_flash, UNLOCK_FALSH_KEY1);
        amhw_zlg237_flash_key_set(p_hw_flash, UNLOCK_FALSH_KEY2);
    }

    amhw_zlg237_flash_cs_reg_clr(p_hw_flash, AMHW_ZLG237_FLASH_PROGRAM_MASK |
                                             AMHW_ZLG237_FLASH_PAGE_ERASE_MASK);

    amhw_zlg237_flash_ecr_wpg_set(p_hw_flash, AMHW_ZLG237_FLASH_WORD_PROGRAM);
    /** ��flash��� */
    for (i = 0; i < size; i++) {
        /** ��д�� */
        *(uint32_t *)(dst_addr + i * 4)     = (uint32_t)p_src[i];

        /** ����д�� */
//        *(uint16_t *)(dst_addr + i * 4)     = (uint16_t)p_src[i];
//        *(uint16_t *)(dst_addr + i * 4 + 2) = (uint16_t)(p_src[i] >> 16);
    }

    while (amhw_zlg237_flash_status_check(p_hw_flash,
                                          AMHW_ZLG237_FLASH_BUSY_FLAG)) {
       ;
    }

    amhw_zlg237_flash_ecr_wpg_set(p_hw_flash, AMHW_ZLG237_FLASH_NO_WORD_PROGRAM);

    for (i = 0; i < size; i++) {

      if (p_src[i] != *(uint32_t *)(dst_addr + i * 4)) {
          break;
      }
    }
    return i;
}

/**
 * \brief ������������
 *
 * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
 *
 * \return ִ�н��
 *
 */
uint32_t am_zlg237_flash_all_sector_erase (amhw_zlg237_flash_t *p_hw_flash)
{
    while (amhw_zlg237_flash_status_check(p_hw_flash,
                                          AMHW_ZLG237_FLASH_BUSY_FLAG)) {
        ;
    }

    amhw_zlg237_flash_cs_reg_clr(p_hw_flash, AMHW_ZLG237_FLASH_PROGRAM_MASK |
                                             AMHW_ZLG237_FLASH_PAGE_ERASE_MASK);

    amhw_zlg237_flash_cs_reg_set(p_hw_flash, AMHW_ZLG237_FLASH_MASS_ERASE_MASK);
    amhw_zlg237_flash_cs_reg_set(p_hw_flash, AMHW_ZLG237_FLASH_START_MASK);

    while (amhw_zlg237_flash_status_check(p_hw_flash,
                                          AMHW_ZLG237_FLASH_BUSY_FLAG)) {
         ;
    }
    return AM_OK;
}

/* end of file */

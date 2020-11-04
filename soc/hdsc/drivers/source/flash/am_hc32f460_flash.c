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
 * \brief Flashģ���������ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 20-06-17  cds, first implementation
 * \endinternal
 */

#include "hw/amhw_hc32f460_flash.h"
#include "am_types.h"
#include "am_bitops.h"
#include "am_int.h"
#include "ametal.h"

/*******************************************************************************
  defines
*******************************************************************************/
#define __AM_HC32F460_FLASH_START_ADDR   0x0
#define __AM_HC32F460_FLASH_END_ADDR     0x7FFDF

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
void am_hc32f460_flash_init (amhw_hc32f460_flash_t *p_hw_flash)
{
    /* ʹ��FLASH */
    amhw_hc32f460_flash_unlock(p_hw_flash);
    amhw_hc32f460_flash_enable(p_hw_flash, AM_TRUE);
    amhw_hc32f460_flash_lock(p_hw_flash);
}

/**
 * \brief ��������
 *
 * \param[in] p_hw_gpio  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr ��������ʼ��ַ
 *
 * \return > 0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_hc32f460_flash_sector_erase (amhw_hc32f460_flash_t *p_hw_flash,
                                        uint32_t               start_addr)
{
    amhw_hc32f460_flash_unlock(p_hw_flash);

    amhw_hc32f460_flash_fwmc_pemode_enable(p_hw_flash);

    amhw_hc32f460_flash_fwmc_pemod_set(p_hw_flash, AMHW_HC32F460_FLASH_ERASE_PGM_MD_SECTORERASE);

    *(volatile uint32_t *)start_addr = 0x12345678;

    while(!(amhw_hc32f460_flash_efm_status_get(p_hw_flash) & AMHW_HC32F460_EFM_STATUS_RDY));

    amhw_hc32f460_flash_efm_status_clr(p_hw_flash, AMHW_HC32F460_EFM_STATUS_OPTEND);

    amhw_hc32f460_flash_lock(p_hw_flash);

    return AM_OK;

}

/**
 * \brief ȫ����
 *
 * \param[in] p_hw_gpio  ָ��FLASH�Ĵ������ָ��
 *
 * \return ִ�н��
 */
int32_t am_hc32f460_flash_all_sector_erase (amhw_hc32f460_flash_t *p_hw_flash)
{
    amhw_hc32f460_flash_unlock(p_hw_flash);

    amhw_hc32f460_flash_fwmc_pemode_enable(p_hw_flash);

    amhw_hc32f460_flash_fwmc_pemod_set(p_hw_flash, AMHW_HC32F460_FLASH_ERASE_PGM_MD_MASSERASE);

    *(volatile uint32_t *)__AM_HC32F460_FLASH_START_ADDR = 0x12345678;

    while(!(amhw_hc32f460_flash_efm_status_get(p_hw_flash) & AMHW_HC32F460_EFM_STATUS_RDY));

    amhw_hc32f460_flash_efm_status_clr(p_hw_flash, AMHW_HC32F460_EFM_STATUS_OPTEND);

    amhw_hc32f460_flash_lock(p_hw_flash);

    return AM_OK;

}

/**
 * \brief ��flash���
 *
 * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
 * \param[in] dst_addr  д�뵽flash����ʼ��ַ
 * \param[in] p_src     Ҫд�뵽flash�е����ݵ���ʼ��ַ
 * \param[in] size      д����(32bit)�ĸ���
 *
 * \retval 0 ʵ�ʳɹ�д�������
 */
int32_t am_hc32f460_flash_sector_program (amhw_hc32f460_flash_t *p_hw_flash,
                                          uint32_t               dst_addr,
                                          uint32_t              *p_src,
                                          uint32_t               size)
{
    if ((dst_addr & 0x3) != 0) {
        return -AM_EINVAL;
    }

    if ((dst_addr + (size * 4)) > (__AM_HC32F460_FLASH_END_ADDR & 0xFFFFFFFC)) {
        return -AM_EINVAL;
    }

    uint32_t i = 0;

    amhw_hc32f460_flash_unlock(p_hw_flash);

    amhw_hc32f460_flash_fwmc_pemode_enable(p_hw_flash);

    amhw_hc32f460_flash_fwmc_pemod_set(p_hw_flash, AMHW_HC32F460_FLASH_ERASE_PGM_MD_SINGLEPROGRAM);

    /** ��flash��� */
    for (i = 0; i < size; i++) {

        /** д��һ���ֵ����� */
        *(uint32_t *)(dst_addr + i * 4)     = p_src[i];

        /** �ȴ�д����� */
        while (!(amhw_hc32f460_flash_efm_status_get(p_hw_flash) & AMHW_HC32F460_EFM_STATUS_RDY)) {
           ;
        }
    }

    amhw_hc32f460_flash_efm_status_clr(p_hw_flash, AMHW_HC32F460_EFM_STATUS_OPTEND);

    amhw_hc32f460_flash_lock(p_hw_flash);

    return i;
}

/**
 * \brief ����EFM�Ĵ���д����
 *
 * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
 *
 * \retval ��
 */
 void am_hc32f460_flash_lock(amhw_hc32f460_flash_t *p_hw_flash)
{
    amhw_hc32f460_flash_lock(p_hw_flash);
}

 /**
  * \brief �ر�EFM�Ĵ���д����
  *
  * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
  *
  * \retval ��
  */
 void am_hc32f460_flash_unlock(amhw_hc32f460_flash_t *p_hw_flash)
{
    amhw_hc32f460_flash_unlock(p_hw_flash);
}


 /**
  * \brief ����FLASH������ĵȴ�����
  *
  * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
  * \param[in] waitcycle FLASH������ĵȴ�����
  *
  * \retval ��
  */
void am_hc32f460_flash_waitcycle(amhw_hc32f460_flash_t *p_hw_flash,
                                 amhw_hc32f460_flash_read_waittime waitcycle)
{
    amhw_hc32f460_flash_waitcycle(p_hw_flash, waitcycle);
}



/* end of file */

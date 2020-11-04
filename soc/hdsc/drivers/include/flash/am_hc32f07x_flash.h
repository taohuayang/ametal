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
 * \brief Flash������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32_FLASH_H
#define __AM_HC32_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hw/amhw_hc32f07x_flash.h"
#include "am_types.h"
#include "am_bitops.h"
#include "hc32_soc_cfg.h"

/**
 * \addtogroup am_hc32_if_flash
 * \copydoc am_hc32_flash.h
 * @{
 */

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

typedef struct
{
    __IO uint32_t tnvs                      : 9;
    __IO uint32_t rsv                       :23;
} amhw_hc32f07x_flash_tnvs_field_t;

typedef struct
{
    __IO uint32_t tpgs                      : 8;
    __IO uint32_t rsv                       :24;
} amhw_hc32f07x_flash_tpgs_field_t;

typedef struct
{
    __IO uint32_t tprog                     : 9;
    __IO uint32_t rsv                       :23;
} amhw_hc32f07x_flash_tprog_field_t;

typedef struct
{
    __IO uint32_t tserase                   :18;
    __IO uint32_t rsv                       :14;
} amhw_hc32f07x_flash_tserase_field_t;

typedef struct
{
    __IO uint32_t tmerase                   :21;
    __IO uint32_t rsv                       :11;
} amhw_hc32f07x_flash_tmerase_field_t;

typedef struct
{
    __IO uint32_t tprcv                     :12;
    __IO uint32_t rsv                       :20;
} amhw_hc32f07x_flash_tprcv_field_t;

typedef struct
{
    __IO uint32_t tsrcv                     :12;
    __IO uint32_t rsv                       :20;
} amhw_hc32f07x_flash_tsrcv_field_t;

 typedef struct
{
    __IO uint32_t tmrcv                     :14;
    __IO uint32_t rsv                       :18;
} amhw_hc32f07x_flash_tmrcv_field_t;

typedef struct
{
    __IO uint32_t op                        : 2;
    __IO uint32_t wait                      : 2;
    __IO uint32_t busy                      : 1;
    __IO uint32_t ie                        : 2;
         uint32_t reserved7                 : 2;
    __IO uint32_t dpstb_en                  : 1;
    __IO uint32_t rsv                       :22;
} amhw_hc32f07x_flash_cr_field_t;

typedef struct
{
    __IO uint32_t if0                       : 1;
    __IO uint32_t if1                       : 1;
    __IO uint32_t rsv                       :30;
} amhw_hc32f07x_flash_ifr_field_t;

typedef struct
{
    __IO uint32_t iclr0                     : 1;
    __IO uint32_t iclr1                     : 1;
    __IO uint32_t rsv                       :30;
} amhw_hc32f07x_flash_iclr_field_t;

typedef struct
{
    __IO uint32_t byseq                     :16;
    __IO uint32_t rsv                       :16;
} amhw_hc32f07x_flash_bypass_field_t;

typedef struct
{
    __IO uint32_t slock                     :32;
} amhw_hc32f07x_flash_slock0_field_t;

typedef struct
{
    __IO uint32_t slock                     :32;
} amhw_hc32f07x_flash_slock1_field_t;

typedef struct
{
    __IO uint32_t slock                     :32;
} amhw_hc32f07x_flash_slock2_field_t;

typedef struct
{
    __IO uint32_t slock                     :32;
} amhw_hc32f07x_flash_slock3_field_t;

typedef struct
{
    union
    {
        __IO uint32_t tnvs;
        amhw_hc32f07x_flash_tnvs_field_t tnvs_f;
    };
    union
    {
        __IO uint32_t tpgs;
        amhw_hc32f07x_flash_tpgs_field_t tpgs_f;
    };
    union
    {
        __IO uint32_t tprog;
        amhw_hc32f07x_flash_tprog_field_t tprog_f;
    };
    union
    {
        __IO uint32_t tserase;
        amhw_hc32f07x_flash_tserase_field_t tserase_f;
    };
    union
    {
        __IO uint32_t tmerase;
        amhw_hc32f07x_flash_tmerase_field_t tmerase_f;
    };
    union
    {
        __IO uint32_t tprcv;
        amhw_hc32f07x_flash_tprcv_field_t tprcv_f;
    };
    union
    {
        __IO uint32_t tsrcv;
        amhw_hc32f07x_flash_tsrcv_field_t tsrcv_f;
    };
    union
    {
        __IO uint32_t tmrcv;
        amhw_hc32f07x_flash_tmrcv_field_t tmrcv_f;
    };
    union
    {
        __IO uint32_t cr;
        amhw_hc32f07x_flash_cr_field_t cr_f;
    };
    union
    {
        __IO uint32_t ifr;
        amhw_hc32f07x_flash_ifr_field_t ifr_f;
    };
    union
    {
        __IO uint32_t iclr;
        amhw_hc32f07x_flash_iclr_field_t iclr_f;
    };
    union
    {
        __IO uint32_t bypass;
        amhw_hc32f07x_flash_bypass_field_t bypass_f;
    };
    union
    {
        __IO uint32_t slock0;
        amhw_hc32f07x_flash_slock0_field_t slock0_f;
    };
    union
    {
        __IO uint32_t slock1;
        amhw_hc32f07x_flash_slock1_field_t slock1_f;
    };
}amhw_hc32_flash_typedef;

typedef enum en_flash_op
{
    Read        = 0u,           ///<������ֵ
    Program     = 1u,           ///<�������ֵ
    SectorErase = 2u,           ///<������������ֵ
    ChipErase   = 3u,           ///<ȫƬ��������ֵ
} en_flash_op_t;


uint32_t am_hc32f07x_flash_writebyte(uint32_t addr, uint8_t u8Data);
uint32_t am_hc32f07x_flash_writehalfword(uint32_t addr, uint16_t data);
uint32_t am_hc32f07x_flash_writeword(uint32_t addr, uint32_t data);
uint32_t am_hc32f07x_flash_sectorerase(uint32_t sectoraddr);
uint32_t am_hc32f07x_flash_chiperase(void);
void am_hc32f07x_flash_lockall(void);
void am_hc32f07x_flash_unlockall(void);

int32_t am_hc32f07x_flash_waitcycle(amhw_hc32f07x_flash_read_waittime waitcycle);

/**
 * \brief Flashģ���ʼ��
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 * \param[in] freqcfg    FLASH���ʱ��Ƶ�����ã�����HCLK��Ƶ��ѡ������ֵ��
 *                       1      - 4MHz;
 *                       2      - 8MHz;
 *                       4      - 16MHz;
 *                       6      - 24MHz;
 *                       8      - 32MHz;
 *                       12     - 48MHz;
 *                       other  - ��Чֵ
 * \param[in] able       AM_TRUE ��ϵͳ����DEEPSLEEPģʽ��FLASH����͹���ģʽ
 *                       AM_TRUE ��ϵͳ����DEEPSLEEPģʽ��FLASH������͹���ģʽ
 *
 * \return   AM_OK       �����ɹ�
 *           AM_EINVAL   ������Ч
 *           AM_ERROR    ��ʼ��ʧ��
 */
int32_t am_hc32f07x_flash_init(uint8_t freqcfg, am_bool_t able);

/**
 * \brief ��������
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr  ��������ʼ��ַ
 *
 * \return >0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_hc32f07x_flash_sector_erase (amhw_hc32f07x_flash_t *p_hw_flash,
                                    uint32_t           addr);

/**
 * \brief ��������̻򲿷��������
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 * \param[in] dst_addr   д�뵽flash����ʼ��ַ
 * \param[in] p_src      Ҫд�뵽flash�е����ݵ���ʼ��ַ
 * \param[in] size       д����(32bit)�ĸ���
 *
 * \retval 0 ʵ�ʳɹ�д�������
 */
int32_t am_hc32f07x_flash_sector_program (amhw_hc32f07x_flash_t *p_hw_flash,
                                      uint32_t             dst_addr,
                                      uint32_t            *p_src,
                                      uint32_t             size);

/**
 * \brief ������������(������������SRAM����Ч)
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 *
 * \return ִ�н��
 *
 */
uint32_t am_hc32f07x_flash_all_sector_erase (amhw_hc32f07x_flash_t *p_hw_flash);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AM_HC32_FLASH_H */

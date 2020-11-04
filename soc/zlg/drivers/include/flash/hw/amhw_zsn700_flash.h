/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief FTFC Peripheral Access Layer
 *
 *   The Miscellaneous System Control Module (FTFC) contains CPU configuration
 *   registers and on-chip memory controller registers.
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-17  YRZ, first implementation
 *
 * \endinternal
 */

#ifndef __AMHW_ZSN700_FLASH_H
#define __AMHW_ZSN700_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zsn700_if_flash
 * \copydoc amhw_zsn700_flash.h
 * @{
 */

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */

/*
 * \brief the structure of  FLASH register
 */
typedef struct amhw_zsn700_flash {
    __IO uint32_t tnvs;      /**< \brief Tnvsʱ������Ĵ���,          offset : 0x00 */
    __IO uint32_t tpgs;      /**< \brief Tpgsʱ������Ĵ���,          offset : 0x04 */
    __IO uint32_t tprog;     /**< \brief Tprogʱ������Ĵ���,         offset : 0x08 */
    __IO uint32_t tserase;   /**< \brief Tseraseʱ������Ĵ���,       offset : 0x0c */
    __IO uint32_t tmerase;   /**< \brief Tmeraseʱ������Ĵ���,       offset : 0x10 */
    __IO uint32_t tprcv;     /**< \brief Tprcvʱ������Ĵ���,         offset : 0x14 */
    __IO uint32_t tsrcv;     /**< \brief Tsrcvʱ������Ĵ���,         offset : 0x18 */
    __IO uint32_t tmrcv;     /**< \brief Tmrcvʱ������Ĵ���,         offset : 0x1c */
    __IO uint32_t cr;        /**< \brief ���ƼĴ���,                  offset : 0x20 */
    __IO uint32_t ifr;       /**< \brief �жϱ�־�Ĵ���,              offset : 0x24 */
    __IO uint32_t iclr;      /**< \brief �жϱ�־����Ĵ���,          offset : 0x28 */
    __IO uint32_t bypass;    /**< \brief Bypass���мĴ���,            offset : 0x2c */
    __IO uint32_t slock0;    /**< \brief Sector0-127��д�����Ĵ���,   offset : 0x30 */
    __IO uint32_t slock1;    /**< \brief Sector128-255��д�����Ĵ���, offset : 0x34 */
    __I  uint32_t reserve0;  /**< \brief ����λ                     , offset : 0x38 */
    __I  uint32_t reserve1;  /**< \brief ����λ                     , offset : 0x3c */
    __IO uint32_t slock2;    /**< \brief Sector256-383��д�����Ĵ���, offset : 0x40 */
    __IO uint32_t slock3;    /**< \brief Sector384-512��д�����Ĵ���, offset : 0x44 */
} amhw_zsn700_flash_t;

/**
 * \brief TNVS ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : HCLKƵ�ʣ���λMHz��
 *
 * \note ���㹫ʽ�� data = 8*HCLK�� HCLK�ĵ�λΪMHz
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_tnvs_set(amhw_zsn700_flash_t *p_hw_flash,
                                uint8_t              data)
{
    p_hw_flash->tnvs = (p_hw_flash->tnvs & (~0x1fful)) |
                       ((uint16_t)(data * 8) & (0x1fful));
}

/**
 * \brief TPGS ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : HCLKƵ�ʣ���λMHz��
 *
 * \note ���㹫ʽ�� data = 5.75*HCLK�� HCLK�ĵ�λΪMHz��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_tpgs_set(amhw_zsn700_flash_t *p_hw_flash,
                                uint8_t              data)
{
    p_hw_flash->tpgs = (p_hw_flash->tpgs & (~0x1fful)) |
                       ((uint16_t)(data * 5.75) & (0x1fful));
}

/**
 * \brief TPROG ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : HCLKƵ�ʣ���λMHz��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_tprog_set(amhw_zsn700_flash_t *p_hw_flash,
                                 uint8_t              data)
{
    p_hw_flash->tprog = (p_hw_flash->tprog & (~0x1fful)) |
                        ((uint16_t)(data * 6.75) & (0x1fful));
}

/**
 * \brief TSERASE ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : HCLKƵ�ʣ���λMHz��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_tserase_set(amhw_zsn700_flash_t *p_hw_flash,
                                   uint8_t              data)
{
    p_hw_flash->tserase = (p_hw_flash->tserase & (~0x3fffful)) |
                          ((uint32_t)(data * 4500) & (0x3fffful));
}

/**
 * \brief TMERASE ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : HCLKƵ�ʣ���λMHz��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_tmerase_set(amhw_zsn700_flash_t *p_hw_flash,
                                   uint8_t              data)
{
    p_hw_flash->tmerase = (p_hw_flash->tmerase & (~0x1ffffful)) |
                          ((uint32_t)(data * 35000) & (0x1ffffful));
}

/**
 * \brief TPRCV ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : HCLKƵ�ʣ���λMHz��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_tprcv_set(amhw_zsn700_flash_t *p_hw_flash,
                                 uint8_t              data)
{
    p_hw_flash->tprcv = (p_hw_flash->tprcv & (~0xffful)) |
                        ((uint16_t)(data * 6) & (0xffful));
}

/**
 * \brief TSRCV ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : HCLKƵ�ʣ���λMHz��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_tsrcv_set(amhw_zsn700_flash_t *p_hw_flash,
                                 uint8_t              data)
{
    p_hw_flash->tsrcv = (p_hw_flash->tsrcv & (~0xffful)) |
                        ((uint16_t)(data * 60) & (0xffful));
}

/**
 * \brief TMRCV ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : HCLKƵ�ʣ���λMHz��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_tmrcv_set(amhw_zsn700_flash_t *p_hw_flash,
                                 uint8_t              data)
{
    p_hw_flash->tmrcv = (p_hw_flash->tmrcv & (~0x3ffful)) |
                        ((uint16_t)(data * 250) & (0x3ffful));
}

/**
 * \brief DPSTB_EN ��ϵͳ����deepsleepģʽ�� FLASH�͹���ģʽ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_deepsleep_lp_disable(amhw_zsn700_flash_t *p_hw_flash)
{
    p_hw_flash->cr &= ~(0x1ul << 9) ;
}

/**
 * \brief DPSTB_EN ��ϵͳ����deepsleepģʽ�� FLASH�͹���ģʽʹ��
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_deepsleep_lp_enable(amhw_zsn700_flash_t *p_hw_flash)
{
    p_hw_flash->cr |= (0x1ul << 9) ;
}


/**
 * \brief BUSY ����/æ��־λ
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return AM_TRUE :  æ״̬
 *        AM_FALSE:  ����״̬
 *
 */
am_static_inline
am_bool_t amhw_zsn700_flash_busy_check(amhw_zsn700_flash_t *p_hw_flash)
{
    return (p_hw_flash->cr & (0x1ul << 4)) ? AM_TRUE : AM_FALSE;
}


/**
 * \brief ��FLASH����
 */
typedef enum {
    AMHW_ZSN700_FLASH_READ_WAITTIME_1 = 0,  /**< \brief  0~24MHz: 00/11: 1������ */
    AMHW_ZSN700_FLASH_READ_WAITTIME_2 = 1,  /**< \brief 24~48MHz:    01: 2������ */
    AMHW_ZSN700_FLASH_READ_WAITTIME_3 = 2,  /**< \brief 48~72MHz:    10: 3������ */
}amhw_zsn700_flash_read_waittime;

/**
 * \brief WAIT ��FLASH����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : ��д�����
 *                          amhw_zsn700_flash_read_waittimeö�������е�һ��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_read_waittime_set(
        amhw_zsn700_flash_t                *p_hw_flash,
        amhw_zsn700_flash_read_waittime     waittime)
{
    p_hw_flash->cr = (p_hw_flash->cr & (~(0x3ul << 2))) |
                     ((waittime & 0x3ul) << 2);
}

/**
 * \brief FLASH����ѡ��
 */
typedef enum {
    AMHW_ZSN700_FLASH_READ         = 0u,     /**< \brief �� */
    AMHW_ZSN700_FLASH_WRITE        = 1u ,    /**< \brief д */
    AMHW_ZSN700_FLASH_SECTOR_ERASE = 2u,     /**< \brief ҳ����  */
    AMHW_ZSN700_FLASH_CHIP_ERASE   = 3u,     /**< \brief ȫƬ����  */
}amhw_zsn700_flash_opt;

/**
 * \brief OP FLASH����ѡ��
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] data        : ��д�����
 *                          amhw_zsn700_flash_read_waittimeö�������е�һ��
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_opt_set(amhw_zsn700_flash_t   *p_hw_flash,
                               amhw_zsn700_flash_opt  opt)
{
    p_hw_flash->bypass = 0x5A5A;
    p_hw_flash->bypass = 0xA5A5;
    p_hw_flash->cr    &= ~0x3ul;

    p_hw_flash->bypass = 0x5A5A;
    p_hw_flash->bypass = 0xA5A5;
    p_hw_flash->cr    |= (opt & 0x3ul);
}

/**
 * \brief ��ȡOP FLASH����ѡ��
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return amhw_zsn700_flash_read_waittimeö�������е�һ��
 */
am_static_inline
uint8_t amhw_zsn700_flash_opt_get(amhw_zsn700_flash_t   *p_hw_flash)
{
    return (p_hw_flash->cr & 0x3ul);
}

/* ��д��������ַ�ж� */
#define AMHW_ZSN700_FLASH_INT_ERASE_P     (0x1ul << 6)

/* ��дPCֵ�ж� */
#define AMHW_ZSN700_FLASH_INT_ERASE_PC    (0x1ul << 5)

/* ��д�����ж� */
#define AMHW_ZSN700_FLASH_INT_ALL         (0x3ul << 5)

/**
 * \brief IE FLASH�жϽ���
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] type        : �ж����� AMHW_ZSN700_FLASH_INT_ERASE_P   ��
 *                                   AMHW_ZSN700_FLASH_INT_ERASE_PC  ��
 *                                   AMHW_ZSN700_FLASH_INT_ALL
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_int_disable(amhw_zsn700_flash_t *p_hw_flash,
                                   uint32_t             type)
{
    p_hw_flash->cr &= ~type;
}

/**
 * \brief IE FLASH�ж�ʹ��
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] type        : �ж����� AMHW_ZSN700_FLASH_INT_ERASE_P   ��
 *                                   AMHW_ZSN700_FLASH_INT_ERASE_PC  ��
 *                                   AMHW_ZSN700_FLASH_INT_ALL
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_int_enable(amhw_zsn700_flash_t *p_hw_flash,
                                  uint32_t             type)
{
    p_hw_flash->cr |= type;
}

/* ��д���������жϱ�־λ */
#define AMHW_ZSN700_FLASH_INT_ERASE_P_FLAG     (0x1ul << 1)

/* ��дPC��ַ�����жϱ�־λ */
#define AMHW_ZSN700_FLASH_INT_ERASE_PC_FLAG    (0x1ul << 0)

/* �����жϱ�־λ */
#define AMHW_ZSN700_FLASH_INT_ALL_FLAG         (0x3ul << 0)

/**
 * \brief IF FLASH�жϱ�־��ȡ
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] flag        : �жϱ�־ AMHW_ZSN700_FLASH_INT_ERASE_P_FLAG   ��
 *                                   AMHW_ZSN700_FLASH_INT_ERASE_PC_FLAG
 *
 * return AM_TRUE :  ��Ч
 *        AM_FALSE:  ��Ч
 */
am_static_inline
am_bool_t amhw_zsn700_flash_int_flag_check(amhw_zsn700_flash_t *p_hw_flash,
                                           uint32_t             flag)
{

    return (p_hw_flash->ifr & flag) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ICLR FLASH�жϱ�־���
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] flag        : �жϱ�־ AMHW_ZSN700_FLASH_INT_ERASE_P_FLAG   ��
 *                                   AMHW_ZSN700_FLASH_INT_ERASE_PC_FLAG
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_int_flag_clr(amhw_zsn700_flash_t *p_hw_flash,
                                    uint32_t             flag)
{
    p_hw_flash->iclr &= ~flag;
}

/**
 * \brief ICLR FLASH�жϱ�־���
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] value       : ��д������
 *
 * \note ���޸ı�ģ��Ĵ���֮ǰ������� BYSEQ[15:0]�Ĵ���д�� 0x5a5a-0xa5a5���С�
 *       ÿ��д���Bypass���к�ֻ�����޸�һ�μĴ�����
 *       �����ٴ��޸ļĴ����������ٴ����� 0x5a5a-0xa5a5���С�
 *
 * return none
 */
am_static_inline
void amhw_zsn700_flash_key_set (amhw_zsn700_flash_t *p_hw_flash,
                                uint16_t             value)
{
    p_hw_flash->bypass = value;
}

/**
 * \brief ʹ������������ν���
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

  /* ��������������ʹ�� */
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif
/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZSN700_FLASH_H */

/* end of file */

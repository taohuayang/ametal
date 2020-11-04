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
 * \brief EFM Peripheral Access Layer
 *
 *   The Miscellaneous System Control Module (FTFC) contains CPU configuration
 *   registers and on-chip memory controller registers.
 *
 * \internal
 * \par Modification history
 * - 1.00 20-06-17  cds, first implementation
 *
 * \endinternal
 */

#ifndef __AMHW_HC32F460_FLASH_H
#define __AMHW_HC32F460_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"
#include "hc32f460_regbase.h"

/**
 * \addtogroup amhw_hc32f460_if_flash
 * \copydoc amhw_hc32f460_flash.h
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

typedef struct amhw_hc32f460_flash {

    __IO uint32_t FAPRT;    /**< \brief FLASH���ʱ����Ĵ��� */

    __IO uint32_t FSTP;     /**< \brief FLASHֹͣ�Ĵ��� */

    __IO uint32_t FRMC;     /**< \brief FLASH��ģʽ�Ĵ��� */

    __IO uint32_t FWMC;     /**< \brief FLASH��дģʽ�Ĵ��� */

    __IO uint32_t FSR;      /**< \brief FLASH״̬�Ĵ��� */

    __IO uint32_t FSCLR;    /**< \brief FLASH״̬����Ĵ��� */

    __IO uint32_t FITE;     /**< \brief FLASH�ж���ɼĴ��� */

    __IO uint32_t FSWP;     /**< \brief FLASH��������״̬�Ĵ��� */

    __IO uint32_t FPMTSW;   /**< \brief FLASH��д����������ʼ��ַ�Ĵ��� */

    __IO uint32_t FPMTEW;   /**< \brief FLASH��д�������������ַ�Ĵ��� */

    uint8_t RESERVED10[40]; /**< \brief ���� */

    __IO uint32_t UQID1;    /**< \brief FLASH оƬID�Ĵ���1 */

    __IO uint32_t UQID2;    /**< \brief FLASH оƬID�Ĵ���2 */

    __IO uint32_t UQID3;    /**< \brief FLASH оƬID�Ĵ���3 */

    uint8_t RESERVED13[164];/**< \brief ���� */

    __IO uint32_t MMF_REMPRT;

    __IO uint32_t MMF_REMCR0;

    __IO uint32_t MMF_REMCR1;

} amhw_hc32f460_flash_t;

/**
 * \brief ��FLASH����
 */
typedef enum {
    AMHW_HC32F460_FLASH_READ_WAITTIME_0 = 0,  /**< \brief ������ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_1 ,     /**< \brief ����1���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_2 ,     /**< \brief ����2���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_3 ,     /**< \brief ����3���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_4 ,     /**< \brief ����4���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_5 ,     /**< \brief ����5���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_6 ,     /**< \brief ����6���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_7 ,     /**< \brief ����7���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_8 ,     /**< \brief ����8���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_9 ,     /**< \brief ����9���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_10 ,    /**< \brief ����10���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_11 ,    /**< \brief ����11���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_12 ,    /**< \brief ����12���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_13 ,    /**< \brief ����13���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_14 ,    /**< \brief ����14���ȴ����� */
    AMHW_HC32F460_FLASH_READ_WAITTIME_15 ,    /**< \brief ����15���ȴ����� */
} amhw_hc32f460_flash_read_waittime;

#define __AMHW_HC32F460_EFM_LOCK            (0x00000000u)
#define __AMHW_HC32F460_EFM_UNLOCK          (0x00000001u)
#define __AMHW_HC32F460_EFM_KEY1            (0x0123ul)
#define __AMHW_HC32F460_EFM_KEY2            (0x3210ul)

am_static_inline
void amhw_hc32f460_flash_lock(amhw_hc32f460_flash_t *p_hw_flash)
{
    if (__AMHW_HC32F460_EFM_UNLOCK== p_hw_flash->FAPRT)
    {
        p_hw_flash->FAPRT = __AMHW_HC32F460_EFM_KEY2;
        p_hw_flash->FAPRT = __AMHW_HC32F460_EFM_KEY2;
    }
}

am_static_inline
void amhw_hc32f460_flash_unlock(amhw_hc32f460_flash_t *p_hw_flash)
{
    if (__AMHW_HC32F460_EFM_LOCK == p_hw_flash->FAPRT)
    {
        p_hw_flash->FAPRT = __AMHW_HC32F460_EFM_KEY1;
        p_hw_flash->FAPRT = __AMHW_HC32F460_EFM_KEY2;
    }
}

/**
 * \brief ����FLASH������ĵȴ�����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] waitcycle   : FLASH������ĵȴ�����
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_waitcycle(amhw_hc32f460_flash_t            *p_hw_flash,
                                   amhw_hc32f460_flash_read_waittime waitcycle)
{
    uint32_t reg_value;

    reg_value = p_hw_flash->FRMC;
    p_hw_flash->FRMC = ((reg_value & (0xF << 4)) | (waitcycle << 4));
}

am_static_inline
void amhw_hc32f460_flash_enable(amhw_hc32f460_flash_t *p_hw_flash, am_bool_t flag)
{
    p_hw_flash->FSTP = (flag == AM_TRUE) ? 0 : 1;
}

/**
 * \brief FLASH�������ݸ�λ
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_readmode_crst_enable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FRMC |= (1 << 24);
}

/**
 * \brief FLASH�������ݲ���λ
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_readmode_crst_disable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FRMC &= ~(1 << 24);
}


/**
 * \brief FLASH���湦��ʹ��
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_readmode_cache_enable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FRMC |= (1 << 16);
}

/**
 * \brief FLASH���湦�ܽ���
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_readmode_cache_disable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FRMC &= ~(1 << 16);
}


/**
 * \brief FLASH����������ģʽʹ��
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_readmode_lvm_enable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FRMC |= (1 << 8);
}

/**
 * \brief FLASH����������ģʽ��ֹ
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_readmode_lvm_disable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FRMC &= ~(1 << 8);
}

/**
 * \brief FLASH���͹��Ķ�ʹ��
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_readmode_slpmd_enable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FRMC |= (1 << 0);
}

/**
 * \brief FLASH���͹��Ķ���ֹ
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_readmode_slpmd_disable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FRMC &= ~(1 << 0);
}

/**
 * \brief FLASH��̲����ڼ䣬�����ͷ�
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_fwmc_bushldctl_set(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FWMC |= (1 << 8);
}

/**
 * \brief FLASH��̲����ڼ䣬���߱�ռ��
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_fwmc_bushldctl_clr(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FWMC &= ~(1 << 8);
}

typedef enum {
    AMHW_HC32F460_FLASH_ERASE_PGM_MD_READONLY1       = 0, /**< \brief ֻ��ģʽ */
    AMHW_HC32F460_FLASH_ERASE_PGM_MD_SINGLEPROGRAM   = 1, /**< \brief �����ģʽ */
    AMHW_HC32F460_FLASH_ERASE_PGM_MD_SINGLEPROGRAMRB = 2, /**< \brief ����̻ض�ģʽ */
    AMHW_HC32F460_FLASH_ERASE_PGM_MD_SEQPROGRAM      = 3, /**< \brief �������ģʽ */
    AMHW_HC32F460_FLASH_ERASE_PGM_MD_SECTORERASE     = 4, /**< \brief ��������ģʽ */
    AMHW_HC32F460_FLASH_ERASE_PGM_MD_MASSERASE       = 5, /**< \brief ȫ����ģʽ */
    AMHW_HC32F460_FLASH_ERASE_PGM_MD_READONLY2       = 6, /**< \brief ֻ��ģʽ */
    AMHW_HC32F460_FLASH_ERASE_PGM_MD_READONLY3       = 7, /**< \brief ֻ��ģʽ */
}amhw_hc32f460_flash_mode_t;

/**
 * \brief FLASHģʽ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] mode        : ����ģʽ��־
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_fwmc_pemod_set(amhw_hc32f460_flash_t            *p_hw_flash,
                                        amhw_hc32f460_flash_mode_t        mode)
{
    uint32_t reg_val = p_hw_flash->FWMC;
    reg_val &= ~(0x7 << 4);
    reg_val |= (mode << 4);
    p_hw_flash->FWMC = reg_val;
}

/**
 * \brief FLASH �����дPEMOD
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_fwmc_pemode_enable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FWMC |= 1;
}

/**
 * \brief FLASH ��ֹ��дPEMOD
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return none
 */
am_static_inline
void amhw_hc32f460_flash_fwmc_pemode_disable(amhw_hc32f460_flash_t *p_hw_flash)
{
    p_hw_flash->FWMC &= ~1;
}

#define AMHW_HC32F460_EFM_STATUS_PEWERR       (1 << 0) /**< \brief ��дģʽ�����־ */
#define AMHW_HC32F460_EFM_STATUS_PEPRTERR     (1 << 1) /**< \brief �Ա�����ַ���/���������־λ */
#define AMHW_HC32F460_EFM_STATUS_PGSZERR      (1 << 2) /**< \brief ��̵�ַ�ʹ�С�������־λ */
#define AMHW_HC32F460_EFM_STATUS_PGMISMTCHERR (1 << 3) /**< \brief ����̻ض�ֵ��һ�±�־λ */
#define AMHW_HC32F460_EFM_STATUS_OPTEND       (1 << 4) /**< \brief ����������־λ */
#define AMHW_HC32F460_EFM_STATUS_COLERR       (1 << 5) /**< \brief FLASH��д���ʴ����־λ */
#define AMHW_HC32F460_EFM_STATUS_RDY          (1 << 8) /**< \brief FLASHæ/���б�־λ */

/**
 * \brief FLASH EFM״̬��־��ȡ
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return EFM״̬��־
 */
am_static_inline
uint32_t amhw_hc32f460_flash_efm_status_get(amhw_hc32f460_flash_t *p_hw_flash)
{
    return p_hw_flash->FSR;
}

/**
 * \brief FLASH EFM״̬��־���
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] flag        : ״̬��־λ
 *
 * return EFM״̬��־
 */
am_static_inline
void amhw_hc32f460_flash_efm_status_clr(amhw_hc32f460_flash_t *p_hw_flash,
                                        uint32_t               flag)
{
    p_hw_flash->FSCLR = flag;
}

typedef enum {
    AMHW_HC32F460_EFM_INTTYPE_PEERRITE    = 0, /**< \brief ���/���������ж���� */
    AMHW_HC32F460_EFM_INTTYPE_OPTENDITE   = 1, /**< \brief ���������ж���� */
    AMHW_HC32F460_EFM_INTTYPE_RDCOLERRITE = 2, /**< \brief ����ͻ�����ж���� */
} amhw_hc32f460_efm_int_type_t;

/**
 * \brief FLASH EFM�ж����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] flag        : �ж����ͱ�־λ
 *
 * return EFM״̬��־
 */
am_static_inline
void amhw_hc32f460_flash_efm_int_enable(amhw_hc32f460_flash_t       *p_hw_flash,
                                        amhw_hc32f460_efm_int_type_t flag)
{
    p_hw_flash->FITE |= (1 << flag);
}

/**
 * \brief FLASH EFM�жϽ�ֹ
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] flag        : �ж����ͱ�־λ
 *
 * return EFM״̬��־
 */
am_static_inline
void amhw_hc32f460_flash_efm_int_disable(amhw_hc32f460_flash_t       *p_hw_flash,
                                         amhw_hc32f460_efm_int_type_t flag)
{
    p_hw_flash->FITE &= ~(1 << flag);
}


/**
 * \brief FLASH ���ڱ�����ʼ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] addr        : ��ַ
 *
 * return
 */
am_static_inline
void amhw_hc32f460_flash_efm_fpmtsw_set(amhw_hc32f460_flash_t *p_hw_flash,
                                        uint32_t               addr)
{
    p_hw_flash->FPMTSW = addr;
}

/**
 * \brief FLASH ���ڱ���������ַ����
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 * \param[in] addr        : ��ַ
 *
 * return
 */
am_static_inline
void amhw_hc32f460_flash_efm_fpmtew_set(amhw_hc32f460_flash_t *p_hw_flash,
                                        uint32_t               addr)
{
    p_hw_flash->FPMTEW = addr;
}

/**
 * \brief FLASH ��ȡоƬΨһ��1
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return оƬΨһ��1
 */
am_static_inline
uint32_t amhw_hc32f460_flash_efm_uqid1_get(amhw_hc32f460_flash_t *p_hw_flash)
{
    return p_hw_flash->UQID1;
}

/**
 * \brief FLASH ��ȡоƬΨһ��2
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return оƬΨһ��1
 */
am_static_inline
uint32_t amhw_hc32f460_flash_efm_uqid2_get(amhw_hc32f460_flash_t *p_hw_flash)
{
    return p_hw_flash->UQID2;
}

/**
 * \brief FLASH ��ȡоƬΨһ��3
 *
 * \param[in] p_hw_flash  : ָ��FLASH�ṹ���ָ��
 *
 * return оƬΨһ��1
 */
am_static_inline
uint32_t amhw_hc32f460_flash_efm_uqid3_get(amhw_hc32f460_flash_t *p_hw_flash)
{
    return p_hw_flash->UQID3;
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

#endif /* __AMHW_HC32F460_FLASH_H */

/* end of file */

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
 * \brief CRC Peripheral Access Layer
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-18
 *
 * \endinternal
 */

#ifndef __AMHW_ZSN700_CRC_H
#define __AMHW_ZSN700_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zsn700_if_crc
 * \copydoc amhw_zsn700_crc.h
 * @{
 */

/**
 * \brief CRC - �Ĵ����ṹ��
 */
typedef struct amhw_zsn700_crc {
    __IO uint32_t crccr;      /**< \brief CRC ���ƼĴ��� */
    __IO uint32_t crcres;     /**< \brief CRC ����Ĵ��� */
         uint8_t  res[120];   /**< \brief ���� */
    __IO uint32_t crcdat;     /**< \brief CRC ���ݼĴ��� */
} amhw_zsn700_crc_t;

/**
 * \brief CRC 32λд����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] data     : ����У�������
 *
 * retval : none
 */
am_static_inline
void amhw_zsn700_crc_32bit_write_data (amhw_zsn700_crc_t    *p_hw_crc,
                                       uint32_t              data)
{
    p_hw_crc->crcdat = (p_hw_crc->crcdat & ~(0xffffffff)) | data;
}

/**
 * \brief CRC 16λд����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] data     : ����У�������
 *
 * retval : none
 *
 * \note this register can not  caculate data
 */
am_static_inline
void amhw_zsn700_crc_16bit_write_data (amhw_zsn700_crc_t  *p_hw_crc,
                                       uint16_t            data)
{
    p_hw_crc->crcdat = (p_hw_crc->crcdat & ~(0xffff)) | data;
}


/**
 * \brief CRC 8λд����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] data     : ����У�������
 *
 * retval : none
 *
 * \note this register can not  caculate data
 */
am_static_inline
void amhw_zsn700_crc_8bit_write_data (amhw_zsn700_crc_t *p_hw_crc, uint8_t data)
{
    p_hw_crc->crcdat = (p_hw_crc->crcdat & ~(0xff)) | data;
}

/**
 * \brief CRC 32λУ�鷽ʽ��ʼ������Ĵ���ֵ
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : none
 */
am_static_inline
void amhw_zsn700_crc_res_32data_init (amhw_zsn700_crc_t *p_hw_crc)
{
    p_hw_crc->crcres = 0xffffffff;
}

/**
 * \brief CRC 16λУ�鷽ʽ��ʼ������Ĵ���ֵ
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : none
 */
am_static_inline
void amhw_zsn700_crc_res_16data_init (amhw_zsn700_crc_t *p_hw_crc)
{
    p_hw_crc->crcres = 0xffff;
}

/**
 * \brief CRC 32λ������
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : CRC������ֵ
 */
am_static_inline
uint32_t amhw_zsn700_crc_32bit_read_data (amhw_zsn700_crc_t *p_hw_crc)
{
    return (p_hw_crc->crcres);
}

/**
 * \brief CRC 16λ������
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : CRC������ֵ
 */
am_static_inline
uint16_t amhw_zsn700_crc_16bit_read_data (amhw_zsn700_crc_t *p_hw_crc)
{
    return (uint16_t)(p_hw_crc->crcres);
}

/**
 * \brief CRC У���ж�
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : none
 */
am_static_inline
uint32_t amhw_zsn700_crc_judge (amhw_zsn700_crc_t *p_hw_crc)
{
    return (p_hw_crc->crccr & (0x2)) >> 1;
}

/**
 * \brief CRC У�鷽ʽѡ��
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : none
 */
am_static_inline
void amhw_zsn700_crc_cal_way (amhw_zsn700_crc_t *p_hw_crc, uint32_t flag)
{
    if (flag == 1){
        p_hw_crc->crccr |= (flag << 0);
    }else{
        p_hw_crc->crccr &= (flag << 0);
    }
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG_CRC_H */

/* end of file */

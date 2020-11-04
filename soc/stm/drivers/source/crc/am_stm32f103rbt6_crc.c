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
 * \brief CRC����ʵ��
 *
 * ֻ��֧��4�ֽڶ�������м���
 * ���� ���е��ֽ��� % 4 == 0
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-30  fra, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_stm32f103rbt6_crc.h"
#include "hw/amhw_stm32f103rbt6_crc.h"

/*******************************************************************************
* ģ���ں�������
*******************************************************************************/

/** \biref ��λ���� 10100->00101 */
static uint8_t __rev8bit(uint8_t data);

/*******************************************************************************
* CRC������������
*******************************************************************************/

/** \biref ����CRCģ�ͳ�ʼ��CRC��ΪCRC��������׼�� */
static int __crc_init (void *p_cookie, am_crc_pattern_t *p_pattern);

/** \brief CRC���� */
static int __crc_cal (void *p_cookie,const uint8_t *p_data, uint32_t nbytes);

/** \brief ��ȡCRC������ */
static int __crc_final (void *p_cookie, uint32_t *p_value);

/**
 * \brief CRC������
 */
static const struct am_crc_drv_funcs __g_crc_drvfuncs = {
    __crc_init,
    __crc_cal,
    __crc_final
};

/******************************************************************************/

/**
 * \brief ��λ���� 10100->00101
 */
static uint8_t __rev8bit (uint8_t data)
{
    uint8_t revdata = 0;
    uint8_t index = 0;

    revdata |= ((data >> index) & 0x01);

    for (index = 1; index < 8; index++) {
        revdata <<= 1;
        revdata |= ((data >> index) & 0x01);
    }
    return revdata;
}

/******************************************************************************/

/**
 * \brief ��ʼ��CRC
 */

static int __crc_init (void *p_cookie, am_crc_pattern_t *p_pattern)
{
    am_stm32f103rbt6_crc_dev_t *p_dev      = (am_stm32f103rbt6_crc_dev_t *)p_cookie;
    amhw_stm32f103rbt6_crc_t   *p_hw_crc   = NULL;

    if (p_dev == NULL || p_pattern == NULL) {
       return -AM_EINVAL;
    }

    if (p_pattern->poly  != 0x04C11DB7 || p_pattern->width != 32 ||
        p_pattern->initvalue != 0xFFFFFFFF ) {

        return -AM_ENOTSUP;
    }

    p_dev->p_pattern = p_pattern;

    p_hw_crc = (amhw_stm32f103rbt6_crc_t *)(p_dev->p_devinfo->crc_reg_base);

    /* ���üĴ���CRC_DATA Ϊ0xFFFF FFFF */
    amhw_stm32f103rbt6_crc_reset(p_hw_crc);

    return AM_OK;
}

/**
 * \brief CRC����
 */
static int __crc_cal (void *p_cookie, const uint8_t *p_data, uint32_t nbytes)
{
    uint32_t i;
    uint32_t tdata;
    am_stm32f103rbt6_crc_dev_t *p_dev    = (am_stm32f103rbt6_crc_dev_t *)p_cookie;
    amhw_stm32f103rbt6_crc_t   *p_hw_crc = (amhw_stm32f103rbt6_crc_t *)(p_dev->p_devinfo->crc_reg_base);

    if (p_dev->p_pattern == NULL || p_data == NULL) {
        return -AM_EINVAL;
    }

    if (nbytes % 4 != 0) {
        return -AM_ENOTSUP;
    }

    for (i = 0; i < nbytes; i+=4) {

        if (p_dev->p_pattern->refin == AM_TRUE) {

            /* �����ÿһ���ֽڶ�����λ���� */
            tdata = (__rev8bit(p_data[i]) << 24)  | (__rev8bit(p_data[i+1]) << 16) |
                    (__rev8bit(p_data[i+2]) << 8) |  __rev8bit(p_data[i+3]);
        } else {

            tdata = (p_data[i] << 24)  | (p_data[i+1] << 16) |
                    (p_data[i+2] << 8) | p_data[i+3];
        }

        amhw_stm32f103rbt6_crc_32bit_write_data(p_hw_crc, tdata);
    }

    return AM_OK;
}

/**
 * \brief ��ȡCRC������
 */
static int __crc_final (void *p_cookie, uint32_t *p_value)
{
    am_stm32f103rbt6_crc_dev_t *p_dev    = (am_stm32f103rbt6_crc_dev_t *)p_cookie;
    amhw_stm32f103rbt6_crc_t   *p_hw_crc = (amhw_stm32f103rbt6_crc_t   *)(p_dev->p_devinfo->crc_reg_base);

    if (p_dev->p_pattern == NULL) {
        return -AM_EINVAL;
    }

   *p_value = amhw_stm32f103rbt6_crc_32bit_read_data(p_hw_crc);

   if (p_dev->p_pattern->refout == AM_TRUE){

       /* ���������е��� */
       *p_value = (__rev8bit((uint8_t)(*p_value  & 0x000000ff)) << 24) |
                  (__rev8bit((uint8_t)((*p_value & 0x0000ff00)  >> 8 )) << 16) |
                  (__rev8bit((uint8_t)((*p_value & 0x00ff0000)  >> 16)) << 8 ) |
                   __rev8bit((uint8_t)((*p_value & 0xff000000)  >> 24));
   }

   /* ��������xorout��� */
   *p_value ^= p_dev->p_pattern->xorout;

    p_dev->p_pattern = NULL;

    return AM_OK;
}

/**
 * \brief CRC��ʼ��
 */
am_crc_handle_t am_stm32f103rbt6_crc_init (am_stm32f103rbt6_crc_dev_t           *p_dev,
                                 const am_stm32f103rbt6_crc_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->p_devinfo         = p_devinfo;
    p_dev->p_pattern         = NULL;

    p_dev->crc_serve.p_funcs = (struct am_crc_drv_funcs *)&__g_crc_drvfuncs;
    p_dev->crc_serve.p_drv   = p_dev;

    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    return &(p_dev->crc_serve);
}

/**
 * \brief CRC���ʼ��
 */
void am_stm32f103rbt6_crc_deinit (am_crc_handle_t handle)
{
    am_stm32f103rbt6_crc_dev_t *p_dev    = (am_stm32f103rbt6_crc_dev_t *)handle;

    if (NULL == handle) {
        return ;
    }

    p_dev->p_pattern = NULL;

    p_dev->crc_serve.p_funcs = NULL;
    p_dev->crc_serve.p_drv   = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */

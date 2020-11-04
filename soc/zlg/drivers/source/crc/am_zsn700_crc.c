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
 * - 1.00 20-03-18
 * \endinternal
 */

#include "ametal.h"
#include "am_zsn700_crc.h"
#include "hw/amhw_zsn700_crc.h"

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

/**
 * \brief ��ʼ��CRC
 */

static int __crc_init (void *p_cookie, am_crc_pattern_t *p_pattern)
{
    am_zsn700_crc_dev_t *p_dev      = (am_zsn700_crc_dev_t *)p_cookie;
    amhw_zsn700_crc_t   *p_hw_crc   = NULL;

    if (p_dev == NULL || p_pattern == NULL) {
       return -AM_EINVAL;
    }

    if ((p_pattern->poly  != 0x04C11DB7 || p_pattern->width != 32 ||
         p_pattern->initvalue != 0xFFFFFFFF) &&
        (p_pattern->poly  != 0x8005     || p_pattern->width != 16 ||
         p_pattern->initvalue != 0x0000)) {

        return -AM_ENOTSUP;
    }

    p_dev->p_pattern = p_pattern;

    p_hw_crc = (amhw_zsn700_crc_t *)(p_dev->p_devinfo->crc_reg_base);

    /* ����ģ��ѡ��У�鷽ʽ��crc-16 ��  crc-32�� */
    if (p_dev->p_pattern->width == 32){

        amhw_zsn700_crc_cal_way(p_hw_crc, AM_ZSN700_CRC_32);

        /* ��ʼ������Ĵ���ֵ */
        amhw_zsn700_crc_res_32data_init(p_hw_crc);
    }else{

        amhw_zsn700_crc_cal_way(p_hw_crc, AM_ZSN700_CRC_16);

        /* ��ʼ������Ĵ���ֵ */
        amhw_zsn700_crc_res_16data_init(p_hw_crc);
    }

    return AM_OK;
}

/**
 * \brief CRC����
 */
static int __crc_cal (void *p_cookie, const uint8_t *p_data, uint32_t nbytes)
{
    uint32_t i;
    uint32_t tdata;
    am_zsn700_crc_dev_t *p_dev    = (am_zsn700_crc_dev_t *)p_cookie;
    amhw_zsn700_crc_t   *p_hw_crc =
        (amhw_zsn700_crc_t *)(p_dev->p_devinfo->crc_reg_base);

    if (p_dev->p_pattern == NULL || p_data == NULL) {
        return -AM_EINVAL;
    }

    if (nbytes % 4 != 0) {
        return -AM_ENOTSUP;
    }

    for (i = 0; i < nbytes; i+=4) {

        tdata = (p_data[i] << 0)  | (p_data[i+1] << 8) |
                (p_data[i+2] << 16) | (p_data[i+3] << 24);

        amhw_zsn700_crc_32bit_write_data(p_hw_crc, tdata);
    }

    return AM_OK;
}

/**
 * \brief ��ȡCRC������
 */
static int __crc_final (void *p_cookie, uint32_t *p_value)
{
    am_zsn700_crc_dev_t *p_dev    = (am_zsn700_crc_dev_t *)p_cookie;
    amhw_zsn700_crc_t   *p_hw_crc =
        (amhw_zsn700_crc_t   *)(p_dev->p_devinfo->crc_reg_base);

    if (p_dev->p_pattern == NULL) {
        return -AM_EINVAL;
    }

    if (p_dev->p_pattern->width == 32){

        *p_value = amhw_zsn700_crc_32bit_read_data(p_hw_crc);
    }else {

        *p_value = amhw_zsn700_crc_16bit_read_data(p_hw_crc);
    }

    p_dev->p_pattern = NULL;

    return AM_OK;
}

/**
 * \brief CRC��ʼ��
 */
am_crc_handle_t am_zsn700_crc_init (am_zsn700_crc_dev_t           *p_dev,
                                    const am_zsn700_crc_devinfo_t *p_devinfo)
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
void am_zsn700_crc_deinit (am_crc_handle_t handle)
{
    am_zsn700_crc_dev_t *p_dev    = (am_zsn700_crc_dev_t *)handle;

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

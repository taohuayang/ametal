/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg116.cn/
*******************************************************************************/

/**
 * \file
 * \brief device�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 20-09-22
 * \endinternal
 */

#ifndef __AMHW_ZLG116_DEVICE_H
#define __AMHW_ZLG116_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"



/**
 * \brief device - �Ĵ�����
 */
typedef struct amhw_zlg116_device {
    uint16_t f_size;        /**< \brief ���������Ĵ��� */
    uint16_t reset[3];
    uint16_t uid[6];        /**< \brief ��ƷΨһ��ʶ�Ĵ��� (96 λ) */     
} amhw_zlg116_device_t;



/**
 * \brief ��ȡUID
 *
 * \param[in] p_hw_dac : ָ��device�Ĵ��������ַָ��
 * \param[in] p_uid : ָ��UID���洢��λ�ã��ɶ�������Ϊuint16_t [6];
 * \retval : ��
 */
am_static_inline
void amhw_zlg116_get_uid (amhw_zlg116_device_t *p_hw_device, uint16_t *p_uid)
{
    p_uid[0] = (uint16_t)(p_hw_device->uid[0]);
    p_uid[1] = (uint16_t)(p_hw_device->uid[1]);
    p_uid[2] = (uint16_t)(p_hw_device->uid[2]);
    p_uid[3] = (uint16_t)(p_hw_device->uid[3]);
    p_uid[4] = (uint16_t)(p_hw_device->uid[4]);
    p_uid[5] = (uint16_t)(p_hw_device->uid[5]);
}




#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG116_DEVICE_H */

/* end of file */

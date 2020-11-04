/*******************************************************************************
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* @file       cd_include.h
* @author     sky
* @date       2015/12/23
* @version    V1.00
* @brief      (cd,coupling device, ����豸)����ͷ�ļ������ļ���оƬ���
*                    - V1.00    2015/12/23 sky �����ĵ�(����FM17550S�Ĵ���)
*******************************************************************************/

/**
 * \file
 * \brief coupling device ����豸ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-23  sky, first implementation.
 * \endinternal
 */

#ifndef __AM_CD_INCLUDE_H
#define __AM_CD_INCLUDE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup if_cd_include
 * \copydoc cd_include.h
 * @{
 */
    
/**
 * \brief ��������Ԫ�ظ����ĺ�
 * \param[in] array : ����
 * \return ����Ԫ�ظ���
 */
#ifndef count_of
#define count_of(array) (sizeof(array) / sizeof(array[0]))
#endif

/**
 * \brief ����豸ѡ��
 */
#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"

/**
 * @} if_cd_include
 */

#ifdef __cplusplus
}
#endif

#endif /* __CD_INCLUDE_H */

/* end of file */

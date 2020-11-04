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
 * \brief ͨ�÷����� NVRAM����������ȣ���ʼ��
 *
 * \internal
 * \par modification history
 * - 1.00 18-10-16  tee, first implementation
 * \endinternal
 */

#ifndef __AM_SERVICE_INST_INIT_H
#define __AM_SERVICE_INST_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief NVRAM ��׼�����ʼ��
 *
 * \note ʹ�� NVRAM ǰ��������øú�������ͨ���� am_prj_config.h �ļ��е�
 *       #AM_CFG_NVRAM_ENABLE ��ֵ�޸�Ϊ 1 ʵ�֣�ʹϵͳ����ʱ�Զ����øú���
 */
void am_nvram_inst_init (void);

/**
 * \brief �¼�����������������������룩�����ʼ��
 */
void am_event_input_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SERVICE_INST_INIT_H */

/* end of file */

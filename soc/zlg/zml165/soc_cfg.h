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
 * \brief оƬƬ��ϵͳӲ�����ã� �������ļ���Ӱ�� ����Ĵ����б�Ķ���
 *
 * ����Ӳ��������Ҫ���ã����磬ͨ����Ŀ�ȣ� ��ͬоƬ���ܴ��ڲ��졣 ���ļ�������ָ��
 * оƬ��Ӧ��Ӳ�����á�ÿ��оƬĿ¼�¾�Ӧ����һ�����ļ���
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  tee, first implementation
 * \endinternal
 */

#ifndef __SOC_CFG_H
#define __SOC_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name ZML165 Ӳ�����ã�������������ʹ�õ��ĸ�������
 * @{
 */

/** \brief DMA ͨ����Ŀ���ã������������  hw/amhw_zlg_dma.h �ļ��� */
#define SOC_CFG_ZLG_DMA_CHAN_CNT          5

/**< \brief flash�Ĵ�С ���ֽ�(8bit)Ϊ��λ */
#define FLASH_SIZE  (1024 * 64UL)

/**< \brief ������С ����(32bit)Ϊ��λ */
#define SECTOR_SIZE (4096UL / 4)

/**@} */

#ifdef __cplusplus
}
#endif

#endif /* __SOC_CFG_H */

/* end of file */

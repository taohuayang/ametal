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
 * - 1.00 19-06-26  yrh, first implementation
 * \endinternal
 */

#ifndef __SOC_CFG_H
#define __SOC_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name STM32F103RBT6 Ӳ�����ã�������������ʹ�õ��ĸ�������
 * @{
 */

/** \brief DMA ͨ����Ŀ���ã������������  hw/amhw_stm32f103rbt6_dma.h �ļ��� */
#define SOC_CFG_STM32F103RBT6_DMA_CHAN_CNT          7

/**< \brief flash�Ĵ�С ���ֽ�(8bit)Ϊ��λ */
#define FLASH_SIZE  (128 * 1024UL)

/**< \brief ������С ����(32bit)Ϊ��λ */
#define SECTOR_SIZE (4096UL / 4)

/**@} */

#ifdef __cplusplus
}
#endif

#endif /* __SOC_CFG_H */

/* end of file */

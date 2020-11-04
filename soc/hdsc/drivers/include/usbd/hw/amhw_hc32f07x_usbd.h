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
 * \brief USBFS�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-15
 * \endinternal
 */

#ifndef __AMHW_HC32_USBFS_H
#define __AMHW_HC32_USBFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <am_types.h>

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__GNUC__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_hc32_if_usbfs
 * \copydoc amhw_hc32_usbfs.h
 * @{
 */

/**
 * \brief USBFS�Ĵ�����ṹ��
 */
typedef struct amhw_hc32_usbfs {
    __IO uint32_t reserve0[2];     /**< \brief ���� */
    __IO uint32_t gahbcfg;         /**< \brief 0x08 AHB���ƼĴ��� */
    __IO uint32_t gusbcfg;         /**< \brief 0x0c USB���üĴ��� */
    __IO uint32_t grstctl;         /**< \brief 0x10 ��λ�Ĵ��� */
    __IO uint32_t gintsts;         /**< \brief 0x14 �жϼĴ��� */
    __IO uint32_t gintmsk;         /**< \brief 0x18 �ж����μĴ��� */
    __IO uint32_t grxstsr;         /**< \brief 0x1c ����״̬���Զ�ȡ�Ĵ��� */
    __IO uint32_t grxstsp;         /**< \brief 0x20 ����״̬��ȡ�ͳ�ջ�Ĵ��� */
    __IO uint32_t grxfsiz;         /**< \brief 0x24 ����FIFO��С�Ĵ��� */
    __IO uint32_t gnptxfsiz;       /**< \brief 0x28 �����ڷ���FIFO��С�Ĵ��� */
    __I  uint32_t gnptxsts;        /**< \brief 0x2c �����ڷ���FIFO״̬�Ĵ��� */
    __IO uint32_t reserve1[3];     /**< \brief ���� */
    __IO uint32_t cid;             /**< \brief 0x3c ID�Ĵ��� */
    __IO uint32_t reserve2[49];    /**< \brief ���� */	
    __IO uint32_t dptxfsiz1;       /**< \brief 0x104 �豸����IN�˵㷢��FIFO��С�Ĵ���*/
    __IO uint32_t dptxfsiz2;       /**< \brief 0x108 �豸����IN�˵㷢��FIFO��С�Ĵ���*/
    __IO uint32_t dptxfsiz3;       /**< \brief 0x10c �豸����IN�˵㷢��FIFO��С�Ĵ���*/
    __IO uint32_t dptxfsiz4;       /**< \brief 0x110 �豸����IN�˵㷢��FIFO��С�Ĵ���*/
    __IO uint32_t reserve3[443];   /**< \brief ���� */	
    __IO uint32_t dcfg;            /**< \brief 0x800 �豸���üĴ��� */
    __IO uint32_t dctl;            /**< \brief 0x804 �豸���ƼĴ��� */
    __I  uint32_t dsts;            /**< \brief 0x808 �豸״̬�Ĵ��� */
    __IO uint32_t reserve4;        /**< \brief ���� */
    __IO uint32_t diepmsk;         /**< \brief 0x810 �豸IN�˵�ͨ���ж����μĴ��� */
    __IO uint32_t doepmsk;         /**< \brief 0x814 �豸OUT�˵�ͨ���ж����μĴ��� */
    __IO  uint32_t daint;           /**< \brief 0x818 �豸ȫ��˵��жϼĴ��� */	
    __IO uint32_t daintmsk;        /**< \brief 0x81c �豸ȫ��˵��ж����μĴ��� */
    __IO uint32_t reserve5[5];     /**< \brief ���� */
    __IO uint32_t diepempmsk;      /**< \brief 0x834 �豸IN�˵�FIFO���ж����μĴ��� */	
    __IO uint32_t reserve6[50];    /**< \brief ���� */
    __IO uint32_t diepctl0;        /**< \brief 0x900 �豸IN�˵�0���ƼĴ��� */
    __IO uint32_t reserve7;        /**< \brief ���� */
    __IO uint32_t diepint0;        /**< \brief 0x908 �豸IN�˵�0�жϼĴ��� */
    __IO uint32_t reserve8;        /**< \brief ���� */
    __IO uint32_t diepsiz0;        /**< \brief 0x910 �豸IN�˵�0�����С�Ĵ��� */

    __IO uint32_t diepdma0;        /**< \brief 0x914 �豸IN�˵�0DMA��ַ�Ĵ��� */
    __IO uint32_t dtxfsts0;        /**< \brief 0x920 �豸IN�˵�0���ƼĴ��� */
    __IO uint32_t reserve9;        /**< \brief ���� */

    __IO uint32_t diepctl1;        /**< \brief 0x920 �豸IN�˵�1���ƼĴ��� */
    __IO uint32_t reserve10;        /**< \brief ���� */
    __IO uint32_t diepint1;        /**< \brief 0x928 �豸IN�˵�1�жϼĴ��� */
    __IO uint32_t reserve11;       /**< \brief ���� */
    __IO uint32_t diepsiz1;        /**< \brief 0x930 �豸IN�˵�1�����С�Ĵ��� */
    __IO uint32_t diepdma1;        /**< \brief 0x934 �豸IN�˵�1DMA��ַ�Ĵ��� */
    __IO uint32_t dtxfsts1;        /**< \brief 0x938 �豸IN�˵�1���ƼĴ��� */
    __IO uint32_t reserve12[9];    /**< \brief 0x93c���� */

    __IO uint32_t diepctl2;        /**< \brief 0x960 �豸IN�˵�2���ƼĴ��� */
    __IO uint32_t reserve13;       /**< \brief ���� */		
    __IO uint32_t diepint2;        /**< \brief 0x968 �豸IN�˵�2�жϼĴ��� */	
    __IO uint32_t reserve14;       /**< \brief ���� */
    __IO uint32_t diepsiz2;        /**< \brief 0x970 �豸IN�˵�2�����С�Ĵ��� */
    __IO uint32_t diepdma2;        /**< \brief 0x974 �豸IN�˵�2DMA��ַ�Ĵ��� */
    __IO uint32_t dtxfsts2;        /**< \brief 0x920 �豸IN�˵�2���ƼĴ��� */
    __IO uint32_t reserve15[9];   /**< \brief ���� */

    __IO uint32_t diepctl3;        /**< \brief 0x960 �豸IN�˵�3���ƼĴ��� */
    __IO uint32_t reserve16;       /**< \brief ���� */		
    __IO uint32_t diepint3;        /**< \brief 0x968 �豸IN�˵�3�жϼĴ��� */	
    __IO uint32_t reserve17;       /**< \brief ���� */
    __IO uint32_t diepsiz3;        /**< \brief 0x970 �豸IN�˵�3�����С�Ĵ��� */
    __IO uint32_t diepdma3;        /**< \brief 0x974 �豸IN�˵�3DMA��ַ�Ĵ��� */
    __IO uint32_t dtxfsts3;        /**< \brief 0x920 �豸IN�˵�3���ƼĴ��� */
    __IO uint32_t reserve18[9];   /**< \brief ���� */

    __IO uint32_t diepctl4;        /**< \brief 0x9e0 �豸IN�˵�4���ƼĴ��� */
    __IO uint32_t reserve19;       /**< \brief ���� */		
    __IO uint32_t diepint4;        /**< \brief 0x9e8 �豸IN�˵�4�жϼĴ��� */	
    __IO uint32_t reserve20;       /**< \brief ���� */
    __IO uint32_t diepsiz4;        /**< \brief 0x9f0 �豸IN�˵�4�����С�Ĵ��� */
    __IO uint32_t diepdma4;        /**< \brief 0x9f4 �豸IN�˵�4DMA��ַ�Ĵ��� */
    __IO uint32_t dtxfsts4;        /**< \brief 0x9f8 �豸IN�˵�4���ƼĴ��� */
    __IO uint32_t reserve21[65];   /**< \brief 0x9fc���� */

    __IO uint32_t doepctl0;        /**< \brief 0xb00 �豸OUT�˵�0���ƼĴ��� */
    __IO uint32_t reserve22;       /**< \brief ���� */		
    __IO uint32_t doepint0;        /**< \brief 0xb08 �豸OUT�˵�0�жϼĴ��� */
    __IO uint32_t reserve23;       /**< \brief ���� */
    __IO uint32_t doepsiz0;        /**< \brief 0xb10 �豸OUT�˵�0�����С�Ĵ��� */
    __IO uint32_t doepdma0;        /**< \brief 0xb14 �豸OUT�˵�0DMA��ַ�Ĵ��� */
    __IO uint32_t reserve24[10];   /**< \brief 0xb18���� */

    __IO uint32_t doepctl1;        /**< \brief 0xb40 �豸OUT�˵�1���ƼĴ��� */
    __IO uint32_t reserve25;       /**< \brief ���� */		
    __IO uint32_t doepint1;        /**< \brief 0xb08 �豸OUT�˵�1�жϼĴ��� */
    __IO uint32_t reserve26;       /**< \brief ���� */
    __IO uint32_t doepsiz1;        /**< \brief 0xb10 �豸OUT�˵�1�����С�Ĵ��� */
    __IO uint32_t doepdma1;        /**< \brief 0x974 �豸OUT�˵�1DMA��ַ�Ĵ��� */
    __IO uint32_t reserve27[10];   /**< \brief ���� */	

    __IO uint32_t doepctl2;        /**< \brief 0xb40 �豸OUT�˵�2���ƼĴ��� */
    __IO uint32_t reserve28;       /**< \brief ���� */
    __IO uint32_t doepint2;        /**< \brief 0xb48 �豸OUT�˵�2�жϼĴ��� */
    __IO uint32_t reserve29;       /**< \brief ���� */
    __IO uint32_t doepsiz2;        /**< \brief 0xb50 �豸OUT�˵�2�����С�Ĵ��� */
    __IO uint32_t doepdma2;        /**< \brief 0xb54 �豸OUT�˵�2DMA��ַ�Ĵ��� */
    __IO uint32_t reserve30[10];   /**< \brief ���� */

    __IO uint32_t doepctl3;        /**< \brief 0xb80 �豸OUT�˵�3���ƼĴ��� */
    __IO uint32_t reserve31;       /**< \brief ���� */
    __IO uint32_t doepint3;        /**< \brief 0xb88 �豸OUT�˵�3�жϼĴ��� */
    __IO uint32_t reserve32;       /**< \brief ���� */
    __IO uint32_t doepsiz3;        /**< \brief 0xb90 �豸OUT�˵�3�����С�Ĵ��� */
    __IO uint32_t doepdma3;        /**< \brief 0xb94 �豸OUT�˵�3DMA��ַ�Ĵ��� */
    __IO uint32_t reserve33[10];   /**< \brief ���� */

    __IO uint32_t doepctl4;        /**< \brief 0xC00 �豸OUT�˵�4���ƼĴ��� */
    __IO uint32_t reserve34;       /**< \brief ���� */
    __IO uint32_t doepint4;        /**< \brief 0xc08 �豸OUT�˵�4�жϼĴ��� */
    __IO uint32_t reserve35;       /**< \brief ���� */
    __IO uint32_t doepsiz4;        /**< \brief 0xb10 �豸OUT�˵�4�����С�Ĵ��� */
    __IO uint32_t doepdma4;        /**< \brief 0xc14 �豸OUT�˵�4DMA��ַ�Ĵ��� */
    __IO uint32_t reserve36[122];   /**< \brief ���� */

    __IO uint32_t pcgcctl;         /**< \brief 0xe00 ��Դ���ſ�ʱ�ӿ��Ƽ����� */		
} amhw_hc32_usbfs_t;
 
typedef enum {
    AMHW_HC32_USBFS_SINGLE = 0u,                // ����
    AMHW_HC32_USBFS_INCR   = 1u,                // INCR
    AMHW_HC32_USBFS_INCR4  = 3u,                // INCR4
    AMHW_HC32_USBFS_INCR8  = 5u,                // INCR8
    AMHW_HC32_USBFS_INCR16 = 7u,                // INCR16
}amhw_hc32_usbfs_hbstlen_type_t;

typedef enum {
    AMHW_HC32_USBFS_TXFIFO0   = 0u,                // TXFIFO0���
    AMHW_HC32_USBFS_TXFIFO1   = 1u,                // TXFIFO1���
    AMHW_HC32_USBFS_TXFIFO2   = 2u,                // TXFIFO2���
    AMHW_HC32_USBFS_TXFIFO3   = 3u,                // TXFIFO3���
    AMHW_HC32_USBFS_TXFIFO4   = 4u,                // TXFIFO4���
    AMHW_HC32_USBFS_TXFIFO5   = 5u,                // TXFIFO5���
    AMHW_HC32_USBFS_TXFIFO6   = 6u,                // TXFIFO6���
    AMHW_HC32_USBFS_TXFIFO7   = 7u,                // TXFIFO7���
    AMHW_HC32_USBFS_TXFIFO8   = 8u,                // TXFIFO8���
    AMHW_HC32_USBFS_TXFIFO9   = 9u,                // TXFIFO9���
    AMHW_HC32_USBFS_TXFIFO10  = 10u,               // TXFIFO10���
    AMHW_HC32_USBFS_TXFIFO11  = 11u,               // TXFIFO11���
    AMHW_HC32_USBFS_TXFIFO12  = 12u,               // TXFIFO12���
    AMHW_HC32_USBFS_TXFIFO13  = 13u,               // TXFIFO13���
    AMHW_HC32_USBFS_TXFIFO14  = 14u,               // TXFIFO14���
    AMHW_HC32_USBFS_TXFIFO15  = 15u,               // TXFIFO15���
    AMHW_HC32_USBFS_TXFIFOALL = 16U,               // ˢ�����еķ���FIFO
}amhw_hc32_usbfs_txfifonum_type_t;

/**
 * \brief  DMAʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_dma_enable (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->gahbcfg |= (0x1ul << 5);
}

/**
 * \brief  DMA����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_dma_disable (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->gahbcfg &= ~(0x1ul << 5);
} 

/**
 * \brief  HBSTLEN ��������/��������
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] hbstlen    :��������/����(amhw_hc32_usbfs_hbstlen_type_tö����)
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_hbstlen_set (amhw_hc32_usbfs_t *p_hw_usbfs,
                                  amhw_hc32_usbfs_hbstlen_type_t hbstlen)
{
    p_hw_usbfs->gahbcfg |= ((hbstlen & 0xful) << 1);
} 

/**
 * \brief  GINTMSK ȫ���ж�ʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_gintmsk_enable (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->gahbcfg |= (0x1ul << 0);
}

/**
 * \brief  GINTMSK ȫ���жϽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_gintmsk_disable (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->gahbcfg &= ~(0x1ul << 0);
} 

/**
 * \brief  USB��תʱ������
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_trdt_set (amhw_hc32_usbfs_t *p_hw_usbfs, uint8_t tim)
{
    p_hw_usbfs->gusbcfg = (p_hw_usbfs->gusbcfg & (~(0xf << 10))) | 
                          ((tim & 0xf) << 10);
}

/**
 * \brief  PHYSEL ȫ��ϵ���շ���ѡ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_physel_set (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->gusbcfg |= (0x1ul << 6);
}

/**
 * \brief  AHBIDL AHB����������ָʾ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return AM_TRUE  :  ���������ڿ���
 *         AM_FALSE :  �����������ڿ���
 */
am_static_inline
am_bool_t amhw_hc32_usbfs_ahbidl_read (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return ((p_hw_usbfs->grstctl >> 31) & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief  DMAREQ DMA�������ָʾ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return AM_TRUE  :  ��DMA�������ڽ���
 *         AM_FALSE :  �����ڽ��е�DMA����
 */
am_static_inline
am_bool_t amhw_hc32_usbfs_dmareq_read(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return ((p_hw_usbfs->grstctl >> 30) & 0x1ul) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief  TXFNUM TxFIFO�������
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] txfifo     : ����ˢ�µ�FIFO���(amhw_hc32_usbfs_txfifonum_type_tö����)
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_txfnum_write (amhw_hc32_usbfs_t *p_hw_usbfs, 
                                   amhw_hc32_usbfs_txfifonum_type_t txfifo)
{
    p_hw_usbfs->grstctl |= ((txfifo & 0x1ful) << 6);
}

/**
 * \brief  TXFFLSH TxFIFOˢ��ʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_txfflsh_enable (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->grstctl |= (0x1ul << 5);
}

/**
 * \brief  TXFFLSH TxFIFOˢ�½���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_txfflsh_disable (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->grstctl &= ~(0x1ul << 5);
}

/**
 * \brief  RXFFLSH RxFIFOˢ��ʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_rxfflsh_enable (amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->grstctl |=(0x1ul << 4);
}

/**
 * \brief  RXFFLSH RxFIFOˢ�½���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_rxfflsh_disable(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->grstctl &= ~(0x1ul << 4);
}

/**
 * \brief  HSRST HCLK���߼���λ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_hsrst_set(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->grstctl |= (0x1ul << 1);
}

///**
// * \brief  HSRST HCLK���߼���λ
// *
// * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
// *
// * \return none
// */
//am_static_inline
//void amhw_hc32_usbfs_hsrst_clr(amhw_hc32_usbfs_t *p_hw_usbfs)
//{
//    p_hw_usbfs->grstctl &= ~(0x1ul << 1);
//}

/**
 * \brief  CSRST ģ����λ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_csrst_enable(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->grstctl |=(0x1ul << 0);
}

/**
 * \brief  CSRST ģ����λֵ��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return AM_TRUE  :  ��λ״̬
 *         AM_FALSE :  δ���и�λ
 */
am_static_inline
am_bool_t amhw_hc32_usbfs_csrst_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return ((p_hw_usbfs->grstctl & (0x1ul << 0)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ȫ���ж�״̬����
 *  @{
 */
#define AMHW_HC32F07X_USBFS_INT_WKUOINT   (1U << 31) /* �ָ���Զ�̻����ж� */
#define AMHW_HC32F07X_USBFS_INT_VBUS      (1U << 30) /* VBUSy�ж� */
#define AMHW_HC32F07X_USBFS_INT_DATAFSUSP (1U << 22) /* ���ݻ�ȡ���� */
#define AMHW_HC32F07X_USBFS_INT_INISOOUT  (1U << 21) /* δ���OUTͬ������ */
#define AMHW_HC32F07X_USBFS_INT_IISOIXFR  (1U << 20) /* δ���INͬ������ */
#define AMHW_HC32F07X_USBFS_INT_OEPINT    (1U << 19) /* OUT�˵��ж� */
#define AMHW_HC32F07X_USBFS_INT_IEPINT    (1U << 18) /* IN�˵��ж� */
#define AMHW_HC32F07X_USBFS_INT_EOPF      (1U << 15) /* ������֡�����ж� */
#define AMHW_HC32F07X_USBFS_INT_ISOODRP   (1U << 14) /* ����ͬ�����ݰ��ж� */
#define AMHW_HC32F07X_USBFS_INT_ENUMDNE   (1U << 13) /* ö������ж� */
#define AMHW_HC32F07X_USBFS_INT_USBRST    (1U << 12) /* USB��λ�ж� */
#define AMHW_HC32F07X_USBFS_INT_USBSUSP   (1U << 11) /* USB�����ж� */
#define AMHW_HC32F07X_USBFS_INT_ESUSP     (1U << 10) /* USB���ڹ����ж� */
#define AMHW_HC32F07X_USBFS_INT_GONAKEFF  (1U << 7) /* ȫ��OUTNAK��Ч�ж� */
#define AMHW_HC32F07X_USBFS_INT_GINAKEFF  (1U << 6) /* ȫ�ַ�������INNAK��Ч�ж� */
#define AMHW_HC32F07X_USBFS_INT_RXFNE     (1U << 4) /* RXFIFO�ǿ��ж� */
#define AMHW_HC32F07X_USBFS_INT_SOF       (1U << 3) /* ֡��ʼ�ж� */
#define AMHW_HC32F07X_USBFS_INT_ALL       (0XFFFFFFFF) /* ����ȫ���ж�*/
/**
 * \brief  ȫ���ж�״̬��ȡ
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return  �ο��궨��AMHW_HC32F07X_USBFS_INT_
 */
am_static_inline
uint32_t amhw_hc32_usbfs_gintsts_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
  return  (uint32_t)(p_hw_usbfs->gintsts );
}

/**
 * \brief  ȫ���ж�״̬���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �жϱ�־���ο��궨��AMHW_HC32F07X_USBFS_INT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_gintsts_clr(amhw_hc32_usbfs_t *p_hw_usbfs,
                                 uint32_t           flag)
{
    p_hw_usbfs->gintsts |= flag;
}

/**
 * \brief  ȫ���ж�ʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �жϱ�־���ο��궨��AMHW_HC32F07X_USBFS_INT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_int_enable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                    uint32_t           flag)
{
    p_hw_usbfs->gintmsk |= flag;
}

/**
 * \brief  ��Ӧȫ���жϽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �жϱ�־���ο��궨��AMHW_HC32F07X_USBFS_INT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_int_disable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                    uint32_t           flag)
{
    p_hw_usbfs->gintmsk &= ~flag;
}

/**
 * \brief USBFS���ݰ�״̬
 */
typedef enum {
    AMHW_HC32F07X_USBFS_STS_GOUT_NAK    = 1, /* ȫ��OUTNAK�������жϣ� */
    AMHW_HC32F07X_USBFS_STS_DATA_UPDT   = 2, /* ���յ�OUT���ݰ� */
    AMHW_HC32F07X_USBFS_STS_XFER_COMP   = 3, /* OUT������ɣ������жϣ� */
    AMHW_HC32F07X_USBFS_STS_SETUP_COMP  = 4, /* SETUP������ɣ������жϣ� */
    AMHW_HC32F07X_USBFS_STS_SETUP_UPDT  = 6, /* ���յ�SETUP���ݰ� */
}amhw_hc32f07x_usbfs_sts_t;

/**
 * \brief  ��ȡ���ݰ�״̬
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return �ο�ö����amhw_hc32f07x_usbfs_sts_t
 */
am_static_inline
amhw_hc32f07x_usbfs_sts_t 
amhw_hc32_usbfs_pktsts_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return (amhw_hc32f07x_usbfs_sts_t)((p_hw_usbfs->grxstsr >> 17) & 0x0f);
}

/**
 * \brief USBFS����PID
 */
typedef enum {
    AMHW_HC32F07X_USBFS_PID_DATA0   = 0, /* DATA0 */
    AMHW_HC32F07X_USBFS_PID_DATA1   = 2, /* DATA1 */
    AMHW_HC32F07X_USBFS_PID_DATA2   = 1, /* DATA2 */
    AMHW_HC32F07X_USBFS_PID_SETUP   = 3, /* MDATA */
}amhw_hc32f07x_usbfs_pid_t;

/**
 * \brief  ��ȡ����PID
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return �ο�ö����amhw_hc32f07x_usbfs_pid_t
 */
am_static_inline
amhw_hc32f07x_usbfs_pid_t 
amhw_hc32_usbfs_pid_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return (amhw_hc32f07x_usbfs_pid_t)((p_hw_usbfs->grxstsr >> 15) & 0x03);
}

/**
 * \brief  ��ȡ���յ����ݰ����ֽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return �ֽ���
 */
am_static_inline
uint16_t amhw_hc32_usbfs_bcnt_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return (uint16_t)((p_hw_usbfs->grxstsr >> 4) & 0x3ff);
}

/**
 * \brief  ��ȡ���յ����ݰ��Ķ˵���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return �˵���
 */
am_static_inline
uint8_t amhw_hc32_usbfs_epnum_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return (uint8_t)(p_hw_usbfs->grxstsr & 0x0f);
}

/**
 * \brief  ����RxFIFO���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_rxfd_set(amhw_hc32_usbfs_t *p_hw_usbfs,uint16_t depth)
{
    p_hw_usbfs->grxfsiz = depth;
}

/**
 * \brief  ��ȡRxFIFO���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return RxFIFO���
 */
am_static_inline
uint16_t amhw_hc32_usbfs_rxfd_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return (uint16_t)(p_hw_usbfs->grxfsiz & 0x3ff);
}

/**
 * \brief  ���÷����ڷ���FIFO��С
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_nptfd_set(amhw_hc32_usbfs_t *p_hw_usbfs,uint16_t depth)
{
    p_hw_usbfs->gnptxfsiz = (depth << 16);
}

/**
 * \brief  ��ȡ�����ڷ���FIFO��С
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return �����ڷ���FIFO��С
 */
am_static_inline
uint16_t amhw_hc32_usbfs_nptfd_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return (uint16_t)((p_hw_usbfs->gnptxfsiz >> 16) & 0x3ff);
}

/**
 * \brief  ���ò�ƷID
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_cid_set(amhw_hc32_usbfs_t *p_hw_usbfs,uint32_t id)
{
    p_hw_usbfs->cid = id;
}

/**
 * \brief  ����IN�˵�TxFIFO���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] depth      : FIFO���ֵ
 * \param[in] n          : ��ӦFIFO�Ĵ������
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_ineptxfd_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                  uint16_t           depth,
                                  uint8_t            n)
{
    switch(n)
    {
        case 1: 
            p_hw_usbfs->dptxfsiz1 =(p_hw_usbfs->dptxfsiz1 &(~(0xfffful<<16))) |
                                   (depth << 16);
            break;
        case 3:
            p_hw_usbfs->dptxfsiz2 =(p_hw_usbfs->dptxfsiz2 &(~(0xfffful<<16))) |
                                   (depth << 16);
            break;
        case 5:
            p_hw_usbfs->dptxfsiz3 =(p_hw_usbfs->dptxfsiz3 &(~(0xfffful<<16))) |
                                   (depth << 16);
            break;
        case 7:
            p_hw_usbfs->dptxfsiz4 =(p_hw_usbfs->dptxfsiz4 &(~(0xfffful<<16))) |
                                   (depth << 16);
            break;
        default: break;
    }
}

/**
 * \brief  ����IN�˵�TxFIFORAM��ʼ��ַ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] address    : IN�˵�TxFIFORAM��ʼ��ַ
 * \param[in] n          : ��ӦFIFO�Ĵ������
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_ineptxsa_set(amhw_hc32_usbfs_t *p_hw_usbfs,
	                                uint16_t           address,
                                  uint8_t            n)
{
    switch(n)
    {
        case 1: p_hw_usbfs->dptxfsiz1 =(p_hw_usbfs->dptxfsiz1 &(~0xffff)) | 
                                       address;
                break;
        case 3: p_hw_usbfs->dptxfsiz2 =(p_hw_usbfs->dptxfsiz2 &(~0xffff)) |
                                       address;
                break;
        case 5: p_hw_usbfs->dptxfsiz3 =(p_hw_usbfs->dptxfsiz3 &(~0xffff)) |
                                       address;
                break;
        case 7: p_hw_usbfs->dptxfsiz4 =(p_hw_usbfs->dptxfsiz4 &(~0xffff)) |
                                       address;
                break;
        default: break;
    }
}

/**
 * \brief USBFS֡�������
 */
typedef enum {
    AMHW_HC32F07X_USBFS_PFIVL80   = 0, /* 80%֡��� */
    AMHW_HC32F07X_USBFS_PFIVL85   = 2, /* 85%֡��� */
    AMHW_HC32F07X_USBFS_PFIVL90   = 1, /* 90%֡��� */
    AMHW_HC32F07X_USBFS_PFIVL95   = 3, /* 95%֡��� */
}amhw_hc32f07x_usbfs_pfivl_t;

/**
 * \brief  ����������֡���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο�ö����amhw_hc32f07x_usbfs_pfivl_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_dfivl_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                               amhw_hc32f07x_usbfs_pfivl_t flag)
{
    p_hw_usbfs->dcfg =(p_hw_usbfs->dcfg & (~(0x03 << 11))) | (flag << 11);
}

/**
 * \brief  �����豸��ַ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] address    : �豸��ַ
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_dad_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                             uint8_t            address)
{
    p_hw_usbfs->dcfg =(p_hw_usbfs->dcfg & (~(0x7f << 4))) | (address << 4);
}

/**
 * \brief  ���㳤��״̬OUT�����ź�
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : 0,�յ����ݷ���Ӧ�ó��򣬸���NAK��STALL�ظ������ź�
 *                         1,�������ݷ���Ӧ�ó��򣬻ָ�STALL�����ź�
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_nzlsohsk_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                  uint8_t            flag)
{
    p_hw_usbfs->dcfg =(p_hw_usbfs->dcfg & (~(0x01 << 2))) | (flag << 2);
}

/**
 * \brief  �豸�ٶ�����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_dspd_set(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    p_hw_usbfs->dcfg |= 0x03;
}



/**
 * \brief �豸���ƶ���
 *  @{
 */
#define AMHW_HC32F07X_USBFS_WRITE_POPRGDNE  (1U << 11) /* �ϵ������ */
#define AMHW_HC32F07X_USBFS_WRITE_CGONAK    (1U << 10) /* ����ȫ��OUT NAK */
#define AMHW_HC32F07X_USBFS_WRITE_SGONAK    (1U << 9)  /* ��λȫ��OUT NAK */
#define AMHW_HC32F07X_USBFS_WRITE_CGINAK    (1U << 8)  /* ����ȫ��IN NAK */
#define AMHW_HC32F07X_USBFS_WRITE_SGINAK    (1U << 7)  /* ��λȫ��IN NAK */

/**
 * \brief  �豸����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_WRITE_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_dctl_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                              uint16_t           flag)
{
    p_hw_usbfs->dctl |= flag;
}

/**
 * \brief �豸���ƶ���
 *  @{
 */
#define AMHW_HC32F07X_USBFS_DCTL_SDIS      (1U << 1)  /* ����� */
#define AMHW_HC32F07X_USBFS_DCTL_RWUSIG    (1U << 0)  /* Զ�̻��� */

/**
 * \brief  �豸����ʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_CTL_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_dctl_enable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                 uint16_t           flag)
{
    p_hw_usbfs->dctl |= flag;
}

/**
 * \brief  �豸���ƽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_CTL_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_dctl_disable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                  uint16_t           flag)
{
    p_hw_usbfs->dctl &= ~flag;
}

/**
 * \brief �豸����״̬����
 *  @{
 */
#define AMHW_HC32F07X_USBFS_READ_POPRGDNE  (1U << 11) /* �ϵ������ */
#define AMHW_HC32F07X_USBFS_READ_GONSTS    (1U << 3)  /* ȫ��OUT NAK״̬ */
#define AMHW_HC32F07X_USBFS_READ_GINSTS    (1U << 2)  /* ȫ��IN NAK״̬ */

/**
 * \brief  �豸����״̬��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_READ_
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32_usbfs_dctl_get(amhw_hc32_usbfs_t *p_hw_usbfs,
                                   uint16_t           flag)
{
    return ((p_hw_usbfs->dctl & flag) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief  ����SOF��֡���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return SOF֡���
 */
am_static_inline
uint16_t amhw_hc32_usbfs_fnsof_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return (uint16_t)((p_hw_usbfs->dsts >> 8) & 0x3fff);
}

/**
 * \brief  ��ȡ���������־
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32_usbfs_eerr_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return  (((p_hw_usbfs->dsts >> 3) & 0x01) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief  ��ȡö���ٶ�
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return SOF֡���
 */
am_static_inline
uint8_t amhw_hc32_usbfs_enumspd_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return (uint8_t)((p_hw_usbfs->dsts >> 1) & 0x3);
}

/**
 * \brief  ��ȡ����״̬
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32_usbfs_suspsts_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{
    return  (((p_hw_usbfs->dsts >> 0) & 0x01) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �豸IN�˵�ͨ���ж϶���
 *  @{
 */
#define AMHW_HC32F07X_USBFS_EP_IN_INEPNEM    (1U << 6) /* IN�˵�NAK��Ч�ж� */
#define AMHW_HC32F07X_USBFS_EP_IN_INEPNNM    (1U << 5) /* EP��ƥ��ʱ���յ�IN�����ж� */
#define AMHW_HC32F07X_USBFS_EP_IN_ITTXFEMSK  (1U << 4) /* TxFIFOΪ�ս��յ�IN�����ж� */
#define AMHW_HC32F07X_USBFS_EP_IN_TOM        (1U << 3) /* ��ʱ�ж�*/
#define AMHW_HC32F07X_USBFS_EP_IN_EPDM       (1U << 1) /* �˵��ֹ�ж� */
#define AMHW_HC32F07X_USBFS_EP_IN_XFRCM      (1U << 0) /* ��������ж� */
#define AMHW_HC32F07X_USBFS_EP_IN_ALL        (0x0b) /* ����IN�˵��ж� */

/**
 * \brief  �豸IN�˵�ͨ���ж�ʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_IN_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_diepmsk_enable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                    uint16_t           flag)
{
    p_hw_usbfs->diepmsk |= flag;
}

/**
 * \brief  �豸IN�˵�ͨ���жϽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_IN_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_diepmsk_disable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                     uint16_t           flag)
{
    p_hw_usbfs->diepmsk &= ~flag;
}

/**
 * \brief �豸OUT�˵�ͨ���ж϶���
 *  @{
 */
#define AMHW_HC32F07X_USBFS_EP_OUT_OTEPDM (1U << 4) /* �˵��ֹʱ���յ�OUT�����ж� */
#define AMHW_HC32F07X_USBFS_EP_OUT_STUPM  (1U << 3) /* SETUP�׶�����ж� */
#define AMHW_HC32F07X_USBFS_EP_OUT_EPDM   (1U << 1) /* �˵��ֹ�ж� */
#define AMHW_HC32F07X_USBFS_EP_OUT_XFRCM  (1U << 0) /* ��������ж� */
#define AMHW_HC32F07X_USBFS_EP_OUT_ALL    (0X2b)    /* ����OUT�˵��ж� */

/**
 * \brief  �豸OUT�˵�ͨ���ж�ʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_OUT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_doepmsk_enable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                    uint16_t           flag)
{
    p_hw_usbfs->doepmsk |= flag;
}

/**
 * \brief  �豸OUT�˵�ͨ���жϽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_IN_
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_doepmsk_disable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                     uint16_t           flag)
{
    p_hw_usbfs->doepmsk &= ~flag;
}

/**
 * \brief ����OUT�˵��ж�λ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦOUT�˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_oepint_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                uint16_t           num)
{       
    p_hw_usbfs->daint |= (0x1 << (16+num)); 
} 

/**
 * \brief ����IN�˵��ж�λ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦIN�˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_iepint_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                uint16_t           num)
{       
    p_hw_usbfs->daint |= (0x1 << num); 
}


/**
 * \brief ��ȡOUT�˵��ж�λ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦOUT�˵���
 *
 * \return none
 */
am_static_inline
uint16_t amhw_hc32_usbfs_oepint_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{       
    return (uint16_t)(p_hw_usbfs->daint >> 16);
}

/**
 * \brief ��ȡIN�˵��ж�λ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦIN�˵���
 *
 * \return none
 */
am_static_inline
uint16_t amhw_hc32_usbfs_iepint_get(amhw_hc32_usbfs_t *p_hw_usbfs)
{       
    return (uint16_t)(p_hw_usbfs->daint);
}

/**
 * \brief  ����OUT�˵��ж�ʹ��λ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦOUT�˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_oepintm_enable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                      uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->daintmsk |= (1u << 16); 
                break;
        case 2: p_hw_usbfs->daintmsk |= (1u << 18); 
                break;
        case 4: p_hw_usbfs->daintmsk |= (1u << 20);
                break;
        case 6: p_hw_usbfs->daintmsk |= (1u << 22);
                break;
        case 8: p_hw_usbfs->daintmsk |= (1u << 24);
                break;
        default: break;
    }
}

/**
 * \brief  ����OUT�˵��жϽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦOUT�˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_oepintm_disable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                      uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->daintmsk &= ~(1u << 16); 
                break;
        case 2: p_hw_usbfs->daintmsk &= ~(1u << 17); 
                break;
        case 4: p_hw_usbfs->daintmsk &= ~(1u << 18);
                break;
        case 6: p_hw_usbfs->daintmsk &= ~(1u << 19);
                break;
        case 8: p_hw_usbfs->daintmsk &= ~(1u << 20);
                break;
        default: break;
    }
}

/**
 * \brief  ����IN�˵��ж�ʹ��λ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦIN�˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_iepintm_enable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                      uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->daintmsk |= (1u << 0); 
                break;
        case 1: p_hw_usbfs->daintmsk |= (1u << 1); 
                break;
        case 3: p_hw_usbfs->daintmsk |= (1u << 3);
                break;
        case 5: p_hw_usbfs->daintmsk |= (1u << 5);
                break;
        case 7: p_hw_usbfs->daintmsk |= (1u << 7);
                break;
        default: break;
    }
}

/**
 * \brief  ����IN�˵��жϽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦIN�˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_iepintm_disable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                      uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->daintmsk &= ~(1u << 0); 
                break;
        case 1: p_hw_usbfs->daintmsk &= ~(1u << 1); 
                break;
        case 3: p_hw_usbfs->daintmsk &= ~(1u << 2);
                break;
        case 5: p_hw_usbfs->daintmsk &= ~(1u << 3);
                break;
        case 7: p_hw_usbfs->daintmsk &= ~(1u << 4);
                break;
        default: break;
    }
}

/**
 * \brief  ����IN�˵�FIFO���ж�ʹ��
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦIN�˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_neptxfem_enable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                      uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepempmsk |= (1u << 0); 
                break;
        case 1: p_hw_usbfs->diepempmsk |= (1u << 1); 
                break;
        case 3: p_hw_usbfs->diepempmsk |= (1u << 2);
                break;
        case 5: p_hw_usbfs->diepempmsk |= (1u << 3);
                break;
        case 7: p_hw_usbfs->diepempmsk |= (1u << 4);
                break;
        default: break;
    }
}

/**
 * \brief  ����IN�˵�FIFO���жϽ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : ��ӦIN�˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_neptxfem_disable(amhw_hc32_usbfs_t *p_hw_usbfs,
                                      uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepempmsk &= ~(1u << 0); 
                break;
        case 1: p_hw_usbfs->diepempmsk &= ~(1u << 1); 
                break;
        case 3: p_hw_usbfs->diepempmsk &= ~(1u << 2);
                break;
        case 5: p_hw_usbfs->diepempmsk &= ~(1u << 3);
                break;
        case 7: p_hw_usbfs->diepempmsk &= ~(1u << 4);
                break;
        default: break;
    }
}

/**
 * \brief �豸�˵����λ����
 *  @{
 */

#define AMHW_HC32F07X_USBFS_CTL_EPENA  (1U << 31) /* �˵�ʹ�� */
#define AMHW_HC32F07X_USBFS_CTL_EPDIS  (1U << 30) /* �˵��ֹ (OUT�˵�0����)*/
#define AMHW_HC32F07X_USBFS_CTL_SNAK   (1U << 27) /* ��λNAK */
#define AMHW_HC32F07X_USBFS_CTL_CNAK   (1U << 26) /* ����NAK */
#define AMHW_HC32F07X_USBFS_CTL_STALL  (1U << 21) /* STALL���� */

/* �˵�0���ɶ�����λ���� */
#define AMHW_HC32F07X_USBFS_CTL_SODDFRM (1U << 29) /* ��������֡ */
#define AMHW_HC32F07X_USBFS_CTL_SD0PID  (1U << 28) /* ���˵�����PID��ΪDATA0 */
#define AMHW_HC32F07X_USBFS_CTL_SEVNFRM (1U << 28) /* ����ż��֡*/

/* ֻ�ɶ�OUT�˵��������λ���� */
#define AMHW_HC32F07X_USBFS_CTL_SNPM    (1U << 20) /* ����ģʽ */
#define AMHW_HC32F07X_USBFS_CTL_SNPMCLR (~(1U << 20)) /* ����ģʽ��� */

/**
 * \brief  �豸IN�˵����λ����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_CTL_
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_diepctl_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                  uint32_t           flag,
                                  uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepctl0 |= flag;
                break;
        case 1: p_hw_usbfs->diepctl1 |= flag; 
                break;
        case 3: p_hw_usbfs->diepctl2 |= flag;
                break;
        case 5: p_hw_usbfs->diepctl3 |= flag;
                break;
        case 7: p_hw_usbfs->diepctl4 |= flag;
                break;
        default: break;
    }
}

/**
 * \brief  �豸IN�˵����λ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_CTL_
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_diepctl_clr(amhw_hc32_usbfs_t *p_hw_usbfs,
                                  uint32_t           flag,
                                  uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepctl0 &= ~flag;
                break;
        case 1: p_hw_usbfs->diepctl1 &= ~flag; 
                break;
        case 3: p_hw_usbfs->diepctl2 &= ~flag;
                break;
        case 5: p_hw_usbfs->diepctl3 &= ~flag;
                break;
        case 7: p_hw_usbfs->diepctl4 &= ~flag;
                break;
        default: break;
    }
}

/**
 * \brief  
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_nextep_set(amhw_hc32_usbfs_t *p_hw_usbfs,
	                               uint8_t           ep_num,
                                  uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepctl0 = (p_hw_usbfs->diepctl0 & ~(0xf << 11)) | 
					                              (ep_num <<11);
                break;
        case 1: p_hw_usbfs->diepctl1 = (p_hw_usbfs->diepctl1 & ~(0xf << 11)) | 
					                              (ep_num <<11); 
                break;
        case 3: p_hw_usbfs->diepctl2 = (p_hw_usbfs->diepctl2 & ~(0xf << 11)) | 
					                              (ep_num <<11);
                break;
        case 5: p_hw_usbfs->diepctl3 = (p_hw_usbfs->diepctl3 & ~(0xf << 11)) | 
					                              (ep_num <<11);
                break;
        case 7: p_hw_usbfs->diepctl4 = (p_hw_usbfs->diepctl4 & ~(0xf << 11)) | 
					                              (ep_num <<11);
                break;
        default: break;
    }
}

/**
 * \brief  �豸OUT�˵����λ����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_CTL_
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_doepctl_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                  uint32_t           flag,
                                  uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->doepctl0 |= flag;
                break;
        case 2: p_hw_usbfs->doepctl1 |= flag; 
                break;
        case 4: p_hw_usbfs->doepctl2 |= flag;
                break;
        case 6: p_hw_usbfs->doepctl3 |= flag;
                break;
        case 8: p_hw_usbfs->doepctl4 |= flag;
                break;
        default: break;
    }
}

/**
 * \brief  �豸OUT�˵����λ���
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_CTL_
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_doepctl_clr(amhw_hc32_usbfs_t *p_hw_usbfs,
	                                uint32_t           flag,
                                  uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->doepctl0 &= ~flag;		
                break;
        case 2: p_hw_usbfs->doepctl1 &= ~flag;	
                break;
        case 4: p_hw_usbfs->doepctl2 &= ~flag;
                break;
        case 6: p_hw_usbfs->doepctl3 &= ~flag;
                break;
        case 8: p_hw_usbfs->doepctl4 &= ~flag;
                break;
        default: break;
    }
}

/**
 * \brief  TxFIFO�������
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] tfifo_num  : TxFIFO���
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_in_txfnum_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                  uint8_t           tfifo_num,
                                  uint8_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepctl0 = (p_hw_usbfs->diepctl0 & (~(0xf<<22))) | 
                                       ((tfifo_num & 0xf) << 22);
                break;
        case 1: p_hw_usbfs->diepctl1 = (p_hw_usbfs->diepctl1 & (~(0xf<<22))) | 
                                       ((tfifo_num & 0xf) << 22);
                break;
        case 3: p_hw_usbfs->diepctl2 = (p_hw_usbfs->diepctl2 & (~(0xf<<22))) |
                                       ((tfifo_num & 0xf) << 22);
                break;
        case 5: p_hw_usbfs->diepctl3 = (p_hw_usbfs->diepctl3 & (~(0xf<<22))) |
                                       ((tfifo_num & 0xf) << 22);
                break;
        case 7: p_hw_usbfs->diepctl4 = (p_hw_usbfs->diepctl4 & (~(0xf<<22))) |
                                        ((tfifo_num & 0xf) << 22);
                break;
        default: break;
    }    
}

/**
 * \brief USBFS�˵����Ͷ���
 */
typedef enum {
    AMHW_HC32F07X_USBFS_EPTYPE_CTRL  = 0, /* ���� */
    AMHW_HC32F07X_USBFS_EPTYPE_ISOC  = 1, /* ͬ�� */
    AMHW_HC32F07X_USBFS_EPTYPE_BULK  = 2, /* ���� */
    AMHW_HC32F07X_USBFS_EPTYPE_INTR  = 3, /* �ж� */
}amhw_hc32f07x_usbfs_eptype_t;

/**
 * \brief  �豸IN�˵����ͻ�ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return �豸�˵�����
 */
am_static_inline
void amhw_hc32_usbfs_in_eptyp_set(amhw_hc32_usbfs_t *p_hw_usbfs, 
                                  amhw_hc32f07x_usbfs_eptype_t type,
                                  uint8_t num)
{

    switch(num)
    {
       case 0: p_hw_usbfs->diepctl0 = 
                               ((p_hw_usbfs->diepctl0 & (~(0x03 << 18))) |
                               type << 18);
               break;
        case 1: p_hw_usbfs->diepctl1 = 
                               ((p_hw_usbfs->diepctl1 & (~(0x03 << 18))) |
                                type << 18);
                break;
        case 3: p_hw_usbfs->diepctl2 =
                               ((p_hw_usbfs->diepctl2 & (~(0x03 << 18))) |
                               type << 18);
                break;
        case 5: p_hw_usbfs->diepctl3 =
                               ((p_hw_usbfs->diepctl3 & (~(0x03 << 18))) |
                               type << 18);
                break;
        case 7: p_hw_usbfs->diepctl4 =
                               ((p_hw_usbfs->diepctl4 & (~(0x03 << 18))) |
                               type << 18);
                break;
        default: break;
    }
}

/**
 * \brief  �豸OUT�˵����ͻ�ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return �豸�˵�����
 */
am_static_inline
void amhw_hc32_usbfs_out_eptyp_set(amhw_hc32_usbfs_t *p_hw_usbfs, 
                                   amhw_hc32f07x_usbfs_eptype_t type,
                                   uint8_t num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->doepctl0 = 
                                ((p_hw_usbfs->doepctl0 & (~(0x03 << 18))) |
                                type << 18);
                break;
        case 2: p_hw_usbfs->doepctl1 = 
                                ((p_hw_usbfs->doepctl1 & (~(0x03 << 18))) |
                                type << 18);
                break;
        case 4: p_hw_usbfs->doepctl2 =
                                ((p_hw_usbfs->doepctl2 & (~(0x03 << 18))) |
                                type << 18);
                break;
        case 6: p_hw_usbfs->doepctl3 =
                                ((p_hw_usbfs->doepctl3 & (~(0x03 << 18))) |
                                type << 18);
                break;
        case 8: p_hw_usbfs->doepctl4 =
                                ((p_hw_usbfs->doepctl4 & (~(0x03 << 18))) |
                                type << 18);
                break;
        default: break;
    }
}

/**
 * \brief  �豸IN�˵�NAK״̬��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return AM_TRUE :�ظ�NAK����
 *         AM_FALSE:����FIFO״̬�ظ���NAK����
 */
am_static_inline
am_bool_t amhw_hc32_usbfs_in_naksts_get(amhw_hc32_usbfs_t *p_hw_usbfs,
                                        uint8_t            num)
{
    am_bool_t naksts = AM_FALSE;
    switch(num)
    {
        case 0: naksts = (((p_hw_usbfs->diepctl0 >> 17) & 
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        case 1: naksts = (((p_hw_usbfs->diepctl1 >> 17) & 
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        case 3: naksts = (((p_hw_usbfs->diepctl2 >> 17) &
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        case 5: naksts = (((p_hw_usbfs->diepctl3 >> 17) &
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        case 7: naksts = (((p_hw_usbfs->diepctl4 >> 17) &
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        default: break;
    }
    return naksts;
}

/**
 * \brief  �豸OUT�˵�NAK״̬��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 *
 * \return AM_TRUE :�ظ�NAK����
 *         AM_FALSE:����FIFO״̬�ظ���NAK����
 */
am_static_inline
am_bool_t amhw_hc32_usbfs_out_naksts_get(amhw_hc32_usbfs_t *p_hw_usbfs, uint8_t num)
{
	  am_bool_t naksts = AM_FALSE;
    switch(num)
    {
        case 0: naksts = (((p_hw_usbfs->doepctl0 >> 17) & 
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        case 2: naksts = (((p_hw_usbfs->doepctl1 >> 17) & 
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        case 4: naksts = (((p_hw_usbfs->doepctl2 >> 17) &
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        case 6: naksts = (((p_hw_usbfs->doepctl3 >> 17) &
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        case 8: naksts = (((p_hw_usbfs->doepctl4 >> 17) &
                         0x01) ? AM_TRUE : AM_FALSE);
                break;
        default: break;
    }
    return naksts;
}

/**
 * \brief  �豸IN��˵�����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_in_usbaep_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                   uint16_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepctl0 |= 1u << 15;
                break;
        case 1: p_hw_usbfs->diepctl1 |= 1u << 15;
                break;
        case 3: p_hw_usbfs->diepctl2 |= 1u << 15;
                break;
        case 5: p_hw_usbfs->diepctl3 |= 1u << 15;
                break;
        case 7: p_hw_usbfs->diepctl4 |= 1u << 15;
                break;
        default: break;
    }
}

/**
 * \brief  �豸OUT��˵�����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_out_usbaep_set(amhw_hc32_usbfs_t *p_hw_usbfs,
	                                   uint16_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->doepctl0 |= 1u << 15;
                break;
        case 2: p_hw_usbfs->doepctl1 |= 1u << 15;
                break;
        case 4: p_hw_usbfs->doepctl2 |= 1u << 15;
                break;
        case 6: p_hw_usbfs->doepctl3 |= 1u << 15;
                break;
        case 8: p_hw_usbfs->doepctl4 |= 1u << 15;
                break;
        default: break;
    }
}


/**
 * \brief  IN�˵�������ݰ���С����
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] size       : �ο�ö����amhw_hc32f07x_usbfs_mpsiz_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_in_mpsiz_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                  uint8_t            size,
                                  uint8_t            num)
{
    if(num==0){
        if(size >= 64){
            size = 0;
        }
        else if(size >= 32){
            size = 1;
        }
        else if(size >= 16){
            size = 2;
        }
        else {
            size = 3;
        }
    }
    switch(num)
    {
        case 0: p_hw_usbfs->diepctl0 = (p_hw_usbfs->diepctl0 & (~0x03)) | 
                                       (size & 0x03);
                break;
        case 1: p_hw_usbfs->diepctl1 = (p_hw_usbfs->diepctl1 & (~0x7ff)) |
                                       (size & 0x7ff);
                break;
        case 3: p_hw_usbfs->diepctl2 = (p_hw_usbfs->diepctl2 & (~0x7ff)) |
                                       (size & 0x7ff);
                break;
        case 5: p_hw_usbfs->diepctl3 = (p_hw_usbfs->diepctl3 & (~0x7ff)) |
                                       (size & 0x7ff);
                break;
        case 7: p_hw_usbfs->diepctl4 = (p_hw_usbfs->diepctl4 & (~0x7ff)) |
                                       (size & 0x7ff);
                break;
        default: break;
    }
}

/**
 * \brief  OUT�˵�������ݰ���С����
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] size       : �ο�ö����amhw_hc32f07x_usbfs_mpsiz_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_out_mpsiz_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                   uint8_t            size,
                                   uint8_t            num)
{
    if(num==0){
        if(size >= 64){
            size = 0;
        }
        else if(size >= 32){
            size = 1;
        }
        else if(size >= 16){
            size = 2;
        }
        else {
            size = 3;
        }
    }
    switch(num)
    {
        case 0: p_hw_usbfs->doepctl0 = (p_hw_usbfs->doepctl0 & (~0x03)) | 
                                       (size & 0x03);
                break;
        case 2: p_hw_usbfs->doepctl1 = (p_hw_usbfs->doepctl1 & (~0x7ff)) |
                                       (size & 0x7ff);
                break;
        case 4: p_hw_usbfs->doepctl2 = (p_hw_usbfs->doepctl2 & (~0x7ff)) |
                                       (size & 0x7ff);
                break;
        case 6: p_hw_usbfs->doepctl3 = (p_hw_usbfs->doepctl3 & (~0x7ff)) |
                                       (size & 0x7ff);
                break;
        case 8: p_hw_usbfs->doepctl4 = (p_hw_usbfs->doepctl4 & (~0x7ff)) |
                                       (size & 0x7ff);
                break;
        default: break;
    }
}

/**
 * \brief  IN�˵��ж����ͻ�ȡ
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : IN�˵���
 *
 * \return IN�˵��ж�ֵ
 */
am_static_inline
uint8_t amhw_hc32_usbfs_int_instat_get(amhw_hc32_usbfs_t *p_hw_usbfs, uint8_t num)
{
	  uint8_t stat = 0;
    switch(num)
    {
        case 0: stat = (p_hw_usbfs->diepint0);
                break;
        case 1: stat = (p_hw_usbfs->diepint1);
                break;
        case 3: stat = (p_hw_usbfs->diepint2);
                break;
        case 5: stat = (p_hw_usbfs->diepint3);
                break;
        case 7: stat = (p_hw_usbfs->diepint4);
                break;
        default: break;
    }
    return stat;
}

/**
 * \brief �豸IN�˵��ж϶���
 *  @{
 */
#define AMHW_HC32F07X_USBFS_IN_INEPNE (1U << 6) /* IN�˵�NAK��Ч */
#define AMHW_HC32F07X_USBFS_IN_ITTXFE (1U << 4) /* TxFIFOΪ�ս��յ�IN���� */
#define AMHW_HC32F07X_USBFS_IN_TO     (1U << 3) /* ��ʱ */
#define AMHW_HC32F07X_USBFS_IN_EPDISD (1U << 1) /* �˵��ֹ�ж� */
#define AMHW_HC32F07X_USBFS_IN_XFRC   (1U << 0) /* ��������ж� */
#define AMHW_HC32F07X_USBFS_IN_ALL    (0XFF) /* ��������ж� */

/**
 * \brief  �豸IN�˵��ж�����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_IN
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_diepint_clr(amhw_hc32_usbfs_t *p_hw_usbfs,
	                               uint8_t           flag,
	                               uint8_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepint0 |= flag;
                break;
        case 1: p_hw_usbfs->diepint1 |= flag;
                break;
        case 3: p_hw_usbfs->diepint2 |= flag;
                break;
        case 5: p_hw_usbfs->diepint3 |= flag;
                break;
        case 7: p_hw_usbfs->diepint4 |= flag;
                break;
        default: break;
    }
}

/**
 * \brief  �豸IN�˵����ݰ�����ֵ����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] cnt        : ����ֵ
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_in_pktcnt_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                   uint16_t          cnt,
                                   uint8_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepsiz0 = (p_hw_usbfs->diepsiz0 & (~(0x03 << 19))) |
                                       ((cnt & 0x03)<< 19);
                break;
        case 1: p_hw_usbfs->diepsiz1 = (p_hw_usbfs->diepsiz1 & (~(0x3ff << 19))) |
                                       ((cnt & 0x3ff)<< 19);
                break;
        case 3: p_hw_usbfs->diepsiz2 = (p_hw_usbfs->diepsiz2 & (~(0x3ff << 19))) |
                                       ((cnt & 0x3ff)<< 19);
                break;
        case 5: p_hw_usbfs->diepsiz3 = (p_hw_usbfs->diepsiz3 & (~(0x3ff << 19))) |
                                       ((cnt & 0x3ff)<< 19);
                break;
        case 7: p_hw_usbfs->diepsiz4 = (p_hw_usbfs->diepsiz4 & (~(0x3ff << 19))) |
                                       ((cnt & 0x3ff)<< 19);
                break;
        default: break;
    }
}

/**
 * \brief  �豸IN�˵����ݰ�����ֵ��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return ����ֵ
 */
am_static_inline
uint16_t amhw_hc32_usbfs_in_pktcnt_get(amhw_hc32_usbfs_t *p_hw_usbfs,
                                     uint8_t           num)
{
    uint16_t cnt = 0;
    switch(num)
    {
        case 0: cnt = ((p_hw_usbfs->diepsiz0 >> 19) & 0x03);
                break;
        case 1: cnt = ((p_hw_usbfs->diepsiz1 >> 19) & 0x3ff);
                break;
        case 3: cnt = ((p_hw_usbfs->diepsiz2 >> 19) & 0x3ff);
                break;
        case 5: cnt = ((p_hw_usbfs->diepsiz3 >> 19) & 0x3ff);
                break;
        case 7: cnt = ((p_hw_usbfs->diepsiz4 >> 19) & 0x3ff);
                break;
        default: break;
    }
    return cnt;
}

/**
 * \brief  �豸IN�˵㴫���С����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] size       : �����С
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_in_xfrsiz_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                   uint32_t          size,
                                   uint8_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepsiz0 = (p_hw_usbfs->diepsiz0 & (~0x7f)) |
                                       ((size & 0x7f)<< 0);
                break;
        case 1: p_hw_usbfs->diepsiz1 = (p_hw_usbfs->diepsiz1 & (~0x7ffff)) |
                                       ((size & 0x7ffff)<< 0);
                break;
        case 3: p_hw_usbfs->diepsiz2 = (p_hw_usbfs->diepsiz2 & (~0x7ffff)) |
                                       ((size & 0x7ffff)<< 0);
                break;
        case 5: p_hw_usbfs->diepsiz3 = (p_hw_usbfs->diepsiz3 & (~0x7ffff)) |
                                       ((size & 0x7ffff)<< 0);
                break;
        case 7: p_hw_usbfs->diepsiz4 = (p_hw_usbfs->diepsiz4 & (~0x7ffff)) |
                                       ((size & 0x7ffff)<< 0);
                break;
        default: break;
    }
}

/**
 * \brief  �豸IN�˵㴫���С��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return �����Сֵ
 */
am_static_inline
uint32_t amhw_hc32_usbfs_in_xfrsiz_get(amhw_hc32_usbfs_t *p_hw_usbfs,
                                       uint8_t           num)
{
    uint32_t size = 0;
    switch(num)
    {
        case 0: size = (p_hw_usbfs->diepsiz0  & 0x7f);
                break;
        case 1: size = (p_hw_usbfs->diepsiz1  & 0x7ffff);
                break;
        case 3: size = (p_hw_usbfs->diepsiz2  & 0x7ffff);
                break;
        case 5: size = (p_hw_usbfs->diepsiz3  & 0x7ffff);
                break;
        case 7: size = (p_hw_usbfs->diepsiz4  & 0x7ffff);
                break;
        default: break;
    }
    return size;
}

/**
 * \brief  �豸IN�˵�DMA��ַ����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] adderess   : DMA��ַ
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_in_dmaaddr_set(amhw_hc32_usbfs_t *p_hw_usbfs,
	                               uint32_t           adderess,
	                               uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->diepdma0 = adderess;
                break;
        case 1: p_hw_usbfs->diepdma1 = adderess;
                break;
        case 3: p_hw_usbfs->diepdma2 = adderess;
                break;
        case 5: p_hw_usbfs->diepdma3 = adderess;
                break;
        case 7: p_hw_usbfs->diepdma4 = adderess;
                break;
        default: break;
    }
}

/**
 * \brief  �豸IN�˵�FIFO���ÿռ��С��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return 32λ��Ϊ��λ�Ŀ��ÿռ�
 */
am_static_inline
uint16_t amhw_hc32_usbfs_ineptfsize_set(amhw_hc32_usbfs_t *p_hw_usbfs,
	                                 uint8_t            num)
{
    uint16_t size = 0;
    switch(num)
    {
        case 0: size = p_hw_usbfs->dtxfsts0 & 0xffff;
                break;
        case 1: size = p_hw_usbfs->dtxfsts1 & 0xffff;
                break;
        case 3: size = p_hw_usbfs->dtxfsts2 & 0xffff;
                break;
        case 5: size = p_hw_usbfs->dtxfsts3 & 0xffff;
                break;
        case 7: size = p_hw_usbfs->dtxfsts4 & 0xffff;
                break;
        default: break;
    }
    return size;
}

/**
 * \brief �豸OUT�˵��ж϶���
 *  @{
 */
#define AMHW_HC32F07X_USBFS_OUT_RECSTUP (1U << 6) /* �յ�������setup���ݰ�*/
#define AMHW_HC32F07X_USBFS_OUT_OTEPDIS (1U << 4) /* �˵��ֹʱ���յ�IN���� */
#define AMHW_HC32F07X_USBFS_OUT_STUP    (1U << 3) /* STUP�׶���� */
#define AMHW_HC32F07X_USBFS_OUT_EPDISD  (1U << 1) /* �˵��ֹ�ж� */
#define AMHW_HC32F07X_USBFS_OUT_XFRC    (1U << 0) /* ��������ж� */

/**
 * \brief  �豸IN�˵��ж�����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] flag       : �ο��궨��AMHW_HC32F07X_USBFS_OUT
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_doepint_clr(amhw_hc32_usbfs_t *p_hw_usbfs,
	                               uint8_t           flag,
	                               uint8_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->doepint0 |= flag;
                break;
        case 2: p_hw_usbfs->doepint1 |= flag;
                break;
        case 4: p_hw_usbfs->doepint2 |= flag;
                break;
        case 6: p_hw_usbfs->doepint3 |= flag;
                break;
        case 8: p_hw_usbfs->doepint4 |= flag;
                break;
        default: break;
    }
}

/**
 * \brief  OUT�˵��ж����ͻ�ȡ
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : OUT�˵���
 *
 * \return OUT�˵��ж�ֵ
 */
am_static_inline
uint8_t amhw_hc32_usbfs_int_outstat_get(amhw_hc32_usbfs_t *p_hw_usbfs,
		                                uint8_t num)
{
    uint8_t stat = 0;
    switch(num)
    {
        case 0: stat = (p_hw_usbfs->doepint0);
                break;
        case 2: stat = (p_hw_usbfs->doepint1);
                break;
        case 4: stat = (p_hw_usbfs->doepint2);
                break;
        case 6: stat = (p_hw_usbfs->doepint3);
                break;
        case 8: stat = (p_hw_usbfs->doepint4);
                break;
        default: break;
    }
    return stat;
}

/**
 * \brief  �豸OUT�˵����ݰ�����ֵ����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] cnt        : ����ֵ
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_out_pktcnt_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                    uint16_t          cnt,
                                    uint8_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->doepsiz0 = (p_hw_usbfs->doepsiz0 &
                                       (~(0x01 << 19))) |
                                       ((cnt & 0x01)<< 19);
                break;
        case 2: p_hw_usbfs->doepsiz1 = (p_hw_usbfs->doepsiz1 &
                                       (~(0x3ff << 19))) |
                                       ((cnt & 0x3ff)<< 19);
                break;
        case 4: p_hw_usbfs->doepsiz2 = (p_hw_usbfs->doepsiz2 &
                                       (~(0x3ff << 19))) |
                                       ((cnt & 0x3ff)<< 19);
                break;
        case 6: p_hw_usbfs->doepsiz3 = (p_hw_usbfs->doepsiz3 &
                                       (~(0x3ff << 19))) |
                                       ((cnt & 0x3ff)<< 19);
                break;
        case 8: p_hw_usbfs->doepsiz4 = (p_hw_usbfs->doepsiz4 &
                                       (~(0x3ff << 19))) |
                                       ((cnt & 0x3ff)<< 19);
                break;
        default: break;
    }
}

/**
 * \brief  �豸OUT�˵����ݰ�����ֵ��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return ����ֵ
 */
am_static_inline
uint16_t amhw_hc32_usbfs_out_pktcnt_get(amhw_hc32_usbfs_t *p_hw_usbfs,
                                        uint8_t           num)
{
    uint16_t cnt = 0;
    switch(num)
    {
        case 0: cnt = ((p_hw_usbfs->doepsiz0 >> 19) & 0x01);
                break;
        case 2: cnt = ((p_hw_usbfs->doepsiz1 >> 19) & 0x3ff);
                break;
        case 4: cnt = ((p_hw_usbfs->doepsiz2 >> 19) & 0x3ff);
                break;
        case 6: cnt = ((p_hw_usbfs->doepsiz3 >> 19) & 0x3ff);
                break;
        case 8: cnt = ((p_hw_usbfs->doepsiz4 >> 19) & 0x3ff);
                break;
        default: break;
    }
    return cnt;
}

/**
 * \brief  �豸OUT�˵㴫���С����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] size       : �����С
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
uint32_t amhw_hc32_usbfs_out_xfrsiz_get(amhw_hc32_usbfs_t *p_hw_usbfs,
                                    uint8_t           num)
{
	  uint32_t cnt = 0;
    switch(num)
    {
        case 0: cnt = (p_hw_usbfs->doepsiz0 & (0x7f));
                break;
        case 2: cnt = (p_hw_usbfs->doepsiz1 & (0x7ffff));
                break;
        case 4: cnt = (p_hw_usbfs->doepsiz2 & (0x7ffff));
                break;
        case 6: cnt = (p_hw_usbfs->doepsiz3 & (0x7ffff));
                break;
        case 8: cnt = (p_hw_usbfs->doepsiz4 & (0x7ffff));
                break;
        default: break;
    }
		return cnt;
}

/**
 * \brief  �豸OUT�˵㴫���С����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] size       : �����С
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_out_xfrsiz_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                    uint32_t          size,
                                    uint8_t           num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->doepsiz0 = (p_hw_usbfs->doepsiz0 & (~0x7f)) |
                                       ((size & 0x7f)<< 0);
                break;
        case 2: p_hw_usbfs->doepsiz1 = (p_hw_usbfs->doepsiz1 & (~0x7ffff)) |
                                       ((size & 0x7ffff)<< 0);
                break;
        case 4: p_hw_usbfs->doepsiz2 = (p_hw_usbfs->doepsiz2 & (~0x7ffff)) |
                                       ((size & 0x7ffff)<< 0);
                break;
        case 6: p_hw_usbfs->doepsiz3 = (p_hw_usbfs->doepsiz3 & (~0x7ffff)) |
                                       ((size & 0x7ffff)<< 0);
                break;
        case 8: p_hw_usbfs->doepsiz4 = (p_hw_usbfs->doepsiz4 & (~0x7ffff)) |
                                       ((size & 0x7ffff)<< 0);
                break;
        default: break;
    }
}

/**
 * \brief  �豸IN�˵㴫���С��ȡ
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return �����Сֵ
 */
am_static_inline
uint32_t amhw_hc32_usbfs_xfrsiz_get(amhw_hc32_usbfs_t *p_hw_usbfs,
                                    uint8_t           num)
{
    uint32_t size = 0;
    switch(num)
    {
        case 0: size = (p_hw_usbfs->diepsiz0  & 0x7f);
                break;
        case 1: size = (p_hw_usbfs->diepsiz1  & 0x7ffff);
                break;
        case 3: size = (p_hw_usbfs->diepsiz2  & 0x7ffff);
                break;
        case 5: size = (p_hw_usbfs->diepsiz3  & 0x7ffff);
                break;
        case 7: size = (p_hw_usbfs->diepsiz4  & 0x7ffff);
                break;
        default: break;
    }
    return size;
}

/**
 * \brief USBFS SETUP���ݰ�����
 */
typedef enum {
    AMHW_HC32F07X_USBFS_SETUP_CNT1  = 1, /* 1�����ݰ� */
    AMHW_HC32F07X_USBFS_SETUP_CNT2  = 2, /* 1�����ݰ� */
    AMHW_HC32F07X_USBFS_SETUP_CNT3  = 3, /* 1�����ݰ� */
}amhw_hc32f07x_usbfs_setup_t;

/**
 * \brief  �豸OUT�˵�0SETUP����������
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_out0_stuocnt_get(amhw_hc32_usbfs_t *p_hw_usbfs,
                                      amhw_hc32f07x_usbfs_setup_t cnt)
{
    p_hw_usbfs->doepsiz0 = (p_hw_usbfs->doepsiz0 & (~(0x03 << 29))) |
                           ((cnt & 0x03)<< 29);
}

/**
 * \brief  �豸OUT�˵�DMA��ַ����
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] adderess   : DMA��ַ
 * \param[in] num        : �˵���
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_out_dmaaddr_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                     uint32_t           adderess,
                                     uint8_t            num)
{
    switch(num)
    {
        case 0: p_hw_usbfs->doepdma0 = adderess;
                break;
        case 2: p_hw_usbfs->doepdma1 = adderess;
                break;
        case 4: p_hw_usbfs->doepdma2 = adderess;
                break;
        case 6: p_hw_usbfs->doepdma3 = adderess;
                break;
        case 8: p_hw_usbfs->doepdma4 = adderess;
                break;
        default: break;
    }
}

/**
 * \brief  �豸�ſ�ʱ������
 *
 * \param[in] p_hw_usbfs : ָ��usbfs�Ĵ�����ָ��
 * \param[in] en         : AM_TRUE :����HCLK��PHYʱ��
 *                         AM_FALSE:ֹͣHCLK��PHYʱ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32_usbfs_gatclk_set(amhw_hc32_usbfs_t *p_hw_usbfs,
                                am_bool_t          en)
{
    if(en == AM_TRUE){
        p_hw_usbfs->pcgcctl &= ~0x03;
    }else {
        p_hw_usbfs->pcgcctl |= 0x03;
    }
}


 /**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__GNUC__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __AMHW_HC32_USBFS_H */

#endif

/* end of file */

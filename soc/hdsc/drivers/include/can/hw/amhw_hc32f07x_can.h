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
 * \brief CAN Ӳ�������ӿ�
 */

#ifndef __AMHW_HC32F07X_CAN_H
#define __AMHW_HC32F07X_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#pragma anon_unions
/**
 * \addtogroup amhw_hc32f07x_if_can
 * \copydoc amhw_hc32f07x_can.h
 * @{
 */

/**
 * \brief can structure of register
 */
/**
 * \brief can structure of register
 */
/**< \brief ����buf����λ */	
typedef struct amhw_hc32f07x_can_cst {
    uint8_t dlc          : 4;    /**< \brief �������ݳ��� */   
    uint8_t reserved0    : 2;    /**< \brief ���� */   
    uint8_t rtr          : 1;    /**< \brief ֡���� */   
    uint8_t ide          : 1;    /**< \brief ֡��ʽ */   
    uint8_t reserved1    : 4;    /**< \brief ���� */  
    uint8_t tx           : 1;    /**< \brief �ػ�ģʽ�Խ��ձ�־ */   
    uint8_t koer         : 3;    /**< \brief ������� */   
    uint16_t    cycletime;          
}amhw_hc32f07x_can_cst_t;

/**< \brief ����buf����λ */
typedef struct amhw_hc32f07x_can_txctrl {
    uint32_t dlc          : 4;        /**< \brief �������ݳ��� */
    uint32_t reserved0    : 2;        /**< \brief ���� */
    uint32_t rtr          : 1;        /**< \brief ֡���� */
    uint32_t ide          : 1;        /**< \brief ֡��ʽ */
    uint32_t reserved1    : 24;       /**< \brief ���� */
}amhw_hc32f07x_can_txctrl_t;

/**< \brief ����buf */
typedef struct amhw_hc32f07x_can_tbuf {
    __IO uint32_t tbuf0;

    union{
        __IO uint32_t tbuf1;
        __IO  amhw_hc32f07x_can_txctrl_t    txctrl;
    };

    __IO uint32_t tbuf2;
    __IO uint32_t tbuf3;
}amhw_hc32f07x_can_tbuf_t;

/**< \brief ����buf */
typedef struct amhw_hc32f07x_can_rbuf {
    __IO uint32_t rbuf0;

    union{
        __IO uint32_t rbuf1;
        __IO amhw_hc32f07x_can_cst_t cst;
    };

    __IO uint32_t rbuf2;
    __IO uint32_t rbuf3;
}amhw_hc32f07x_can_rbuf_t;

/**
 * \brief HC32F07X CAN�Ĵ����ṹ��
 */	
typedef struct amhw_hc32f07x_can {

    __IO amhw_hc32f07x_can_rbuf_t    rbuf;
    __IO uint8_t   reserve0[64];           /**< \brief ���� */
    __IO amhw_hc32f07x_can_tbuf_t    tbuf;
    __IO uint8_t   reserve1[64];           /**< \brief ���� */
    __IO uint8_t   cfgstat;    /**< \brief ���ú�״̬�Ĵ��� */ 
    __IO uint8_t   tcmd;       /**< \brief ����Ĵ��� */
    __IO uint8_t   tctrl;      /**< \brief ���Ϳ��ƼĴ��� */
    __IO uint8_t   rctrl;      /**< \brief ���տ��ƼĴ��� */
    __IO uint8_t   rtie;       /**< \brief ���պͷ����ж�ʹ�ܼĴ��� */
    __IO uint8_t   rtif;       /**< \brief ���պͷ����жϱ�־�Ĵ��� */
    __IO uint8_t   errint;     /**< \brief �����ж�ʹ�ܺͱ�־�Ĵ��� */
    __IO uint8_t   limit;      /**< \brief �����޶��Ĵ���*/
    __IO uint32_t  bt;         /**< \brief λʱ��Ĵ��� */
    __IO uint8_t  reserve2[4]; /**< \brief ���� */	
    __IO uint8_t  ealcap;      /**< \brief ������ٲ�ʧ�ܲ�׽�Ĵ��� */	
    __IO uint8_t  reserve3[1]; /**< \brief ���� */
    __IO uint8_t  recnt;       /**< \brief ���մ�������Ĵ��� */
    __IO uint8_t  tecnt;       /**< \brief ���ʹ���������Ĵ��� */	
    __IO uint8_t  acfctrl;     /**< \brief ɸѡ������ƼĴ���*/
    __IO uint8_t  reserve4[1]; /**< \brief ���� */
    __IO uint8_t  acfen;       /**< \brief ɸѡ����ʹ�ܼĴ��� */	
    __IO uint8_t  reserve5[1]; /**< \brief ���� */	
    __IO uint32_t acf;         /**< \brief ɸѡ����code��mask�Ĵ��� */	
    __IO uint8_t  reserve6[2]; /**< \brief ���� */
    __IO uint8_t  tbslot;      /**< \brief tb slotָ��Ĵ��� */
    __IO uint8_t  ttcfg;       /**< \brief ʱ�䴥�����üĴ��� */	
    __IO uint32_t  refmsg;     /**< \brief �ο���Ϣ�Ĵ��� */	
    __IO uint16_t  trgcfg;     /**< \brief �������üĴ��� */	
    __IO uint16_t  trgtrig;    /**< \brief ����ʱ��Ĵ��� */
    __IO uint16_t  trgwtrig;   /**< \brief ��������ʱ��Ĵ��� */			
} amhw_hc32f07x_can_t;

/**
 * \brief CAN IDE��ʽ����
 */
typedef enum {
    AMHW_HC32F07X_CAN_IDE_STANDARD = 0, /* ��׼��ʽ */
    AMHW_HC32F07X_CAN_IDE_EXTENDED = 1, /* ��չ��ʽ */
}amhw_hc32f07x_can_ide_t;

/**
 * \brief CAN RTR֡����
 */
typedef enum {
    AMHW_HC32F07X_CAN_RTR_DATA   = 0, /* ����֡ */
    AMHW_HC32F07X_CAN_RTR_REMOTE = 1, /* Զ��֡ */
}amhw_hc32f07x_can_rtr_t;

/**
 * \brief CAN ����BUFѡ����
 */
typedef enum {
    AMHW_HC32F07X_CAN_TXBUF_PTB = 0, /* PTB*/
    AMHW_HC32F07X_CAN_TXBUF_STB = 1, /* STB */
}amhw_hc32f07x_can_txbuf_t;

/**
 * \brief CAN ���ݳ��ȶ���
 */
typedef enum {
    AMHW_HC32F07X_CAN_DATA_LEN0 = 0, /* 0BYTE */
    AMHW_HC32F07X_CAN_DATA_LEN1 = 1, /* 1BYTE */
    AMHW_HC32F07X_CAN_DATA_LEN2 = 2, /* 2BYTE */
    AMHW_HC32F07X_CAN_DATA_LEN3 = 3, /* 3BYTE */
    AMHW_HC32F07X_CAN_DATA_LEN4 = 4, /* 4BYTE */
    AMHW_HC32F07X_CAN_DATA_LEN5 = 5, /* 5BYTE */
    AMHW_HC32F07X_CAN_DATA_LEN6 = 6, /* 6BYTE */
    AMHW_HC32F07X_CAN_DATA_LEN7 = 7, /* 7BYTE */
    AMHW_HC32F07X_CAN_DATA_LEN8 = 8, /* 8BYTE */	
}amhw_hc32f07x_can_data_t;

/**
 * \brief CAN ģʽ
 */
typedef enum {
    AMHW_HC32F07X_CAN_EXT_LOOPBACK_MODE   = 0X40, /* �ⲿ�ػ�ģʽ */
    AMHW_HC32F07X_CAN_INT_LOOPBACK_MODE   = 0X20, /* �ڲ��ػ�ģʽ */
    AMHW_HC32F07X_CAN_SIG_PRIARY_MODE     = 0X10, /* PTB���δ���ģʽ */
    AMHW_HC32F07X_CAN_SIG_SECONDARY_MODE  = 0X08, /* STB���δ���ģʽ */
    AMHW_HC32F07X_CAN_LISTEN_ONLY_MODE    = 0XFF, /* ��Ĭģʽ */
}amhw_hc32f07x_can_mode_t;

/**
 * \brief CAN ģʽ
 */
typedef enum amhw_zmf159_can_type {
    AMHW_HC32F07X_CAN_PTB = 0,        /**< \brief ptb can */
    AMHW_HC32F07X_CAN_STB,             /**< \brief stb can */
}amhw_hc32f07x_can_type_t;

/**
 * \brief CAN ��λ����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_reset_set (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->cfgstat |= (1u<<7);
}

/**
 * \brief CAN ��λ�������
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_reset_clr (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->cfgstat &= ~(1u<<7);
}

/**
 * \brief CAN ģʽ����ʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_mode_enable (amhw_hc32f07x_can_t *p_hw_can,
                                    amhw_hc32f07x_can_mode_t mode )
{
    if(mode == AMHW_HC32F07X_CAN_LISTEN_ONLY_MODE){
        p_hw_can->tcmd |= (1u<<6);
    }else {
	      p_hw_can->cfgstat |= mode;
	}
}

/**
 * \brief CAN ģʽ����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_mode_disable (amhw_hc32f07x_can_t *p_hw_can,
                                    amhw_hc32f07x_can_mode_t mode )
{
    if(mode == AMHW_HC32F07X_CAN_LISTEN_ONLY_MODE){
        p_hw_can->tcmd &= ~(1u<<6);
    }else {
        p_hw_can->cfgstat &= ~mode;
    }
}

/**
 * \brief CAN״̬��־
 *  @{
 */
#define AMHW_HC32F07X_CAN_FLAG_RX_ACTIVE        (1U << 2) /* ������״̬�ź� */
#define AMHW_HC32F07X_CAN_FLAG_TX_ACTIVE        (1U << 1) /* ������״̬�ź� */
#define AMHW_HC32F07X_CAN_FLAG_BUSOFF_ACTIVE    (1U << 0) /* ���߹ر�״̬�ź� */

/**
 * \brief CAN ״̬��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f07x_can_status_get (amhw_hc32f07x_can_t *p_hw_can, uint8_t flag)
{
  return  ((p_hw_can->cfgstat  & flag) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief CAN TECNT��RECNT�Ĵ�������
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_cnt_clr (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->cfgstat |= (1u<<0);
}

/**
 * \brief CAN ����BUFѡ��λ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_txbuf_sel (amhw_hc32f07x_can_t       *p_hw_can,
                                  amhw_hc32f07x_can_txbuf_t  flag)
{
    p_hw_can->tcmd  = (p_hw_can->tcmd & (~(1u << 7)))|(flag << 7);
}



/**
 * \brief CAN STBY�趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stby_sel (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd |= (1u<<5);
}

/**
 * \brief CAN STBY���
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stby_clr (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd &= ~(1u<<5);
}

/**
 * \brief CAN PTB����ʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_ptb_send_enable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd |= (1u<<4);
}

/**
 * \brief CAN PTB���ͽ���
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_ptb_send_disable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd &= ~(1u<<4);
}

/**
 * \brief CAN PTB����ȡ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_ptb_abort_enable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd |= (1u<<3);
}

/**
 * \brief CAN STB����һ֡����ʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stb_sendone_enable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd |= (1u<<2);
}

/**
 * \brief CAN STB����һ֡���ݽ�ֹ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stb_sendone_disable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd &= ~(1u<<2);
}

/**
 * \brief CAN STB������������ʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stb_sendall_enable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd |= (1u<<1);
}

/**
 * \brief CAN STB�����������ݽ�ֹ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stb_sendall_disable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd &= ~(1u<<1);
}

/**
 * \brief CAN STB����ȡ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stb_abort_enable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tcmd |= (1u<<0);
}

/**
 * \brief CAN ��һ��STB SLOT
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stb_slot_next (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tctrl &= (1u<<6);
}

/**
 * \brief CAN STB����ģʽ����
 */
typedef enum {
    AMHW_HC32F07X_CAN_STB_MODE_FIFO = 0, /* FIFOģʽ */
    AMHW_HC32F07X_CAN_STB_MODE_PRIM = 1, /* ���ȼ�ģʽ */
}amhw_hc32f07x_can_stb_mode_t;

/**
 * \brief CAN STB����ģʽ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_stb_mode_set (amhw_hc32f07x_can_t *p_hw_can,
	                                 amhw_hc32f07x_can_stb_mode_t flag)
{
    p_hw_can->tctrl = (p_hw_can->tctrl & (~(1u << 5)))|(flag << 5);
}

/**
 * \brief CAN TTCAN BUFģʽ����
 */
typedef enum {
    AMHW_HC32F07X_CAN_TT_BUF_TS   = 0, /* TSMODE�趨 */
    AMHW_HC32F07X_CAN_TT_BUF_TR = 1, /* ͨ��TBPTR��TTPTR�趨 */
}amhw_hc32f07x_can_tt_buf_t;

/**
 * \brief CAN TTCAN BUFģʽ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_ttcan_buf_set (amhw_hc32f07x_can_t *p_hw_can,
	                                   amhw_hc32f07x_can_tt_buf_t flag)
{
    p_hw_can->tctrl = (p_hw_can->tctrl & (~(1u << 4)))|(flag << 4);
}

/**
 * \brief CAN STB״̬����
 */
typedef enum {
    AMHW_HC32F07X_CAN_TB_EMPTY        = 0, /* �� */
    AMHW_HC32F07X_CAN_TB_NOT_HALFFULL = 1, /* С�ڵ��ڰ���*/
    AMHW_HC32F07X_CAN_TB_HALFFULL     = 2, /* ���ڰ��� */
    AMHW_HC32F07X_CAN_TB_FULL         = 3, /* �� */
}amhw_hc32f07x_can_tb_status_t;

/**
 * \brief CAN TTCAN BUFģʽ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
amhw_hc32f07x_can_tb_status_t amhw_hc32f07x_can_get_tb_status (amhw_hc32f07x_can_t *p_hw_can)
{
   return (amhw_hc32f07x_can_tb_status_t) (p_hw_can->tctrl & 0x03 );
}

/**
 * \brief CAN ��Ӧ��ʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_sack_enable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->rctrl |= 0x80 ;
}

/**
 * \brief CAN ��Ӧ���ֹ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_sack_disable (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->rctrl &= ~(1u << 7) ;
}

/**
 * \brief CAN ����BUF����ģʽ����
 */
typedef enum {
    AMHW_HC32F07X_CAN_RXBUF_OVERWRITTEN = 0, /* ������յ������ݱ����� */
    AMHW_HC32F07X_CAN_RXBUF_NOTSTORED   = 1, /* ���½��յ������ݲ����洢*/
}amhw_hc32f07x_can_rxbuf_mode_t;

/**
 * \brief CAN ����BUF����ģʽ�趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_rxbuf_over_mode_set (amhw_hc32f07x_can_t *p_hw_can,
	                                        amhw_hc32f07x_can_rxbuf_mode_t flag)
{
    p_hw_can->rctrl = (p_hw_can->rctrl & (~(1u << 6)))|(flag << 6);
}

/**
 * \brief CAN ����BUF�����־
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f07x_can_rxbuf_over_get (amhw_hc32f07x_can_t *p_hw_can)
{
      return ((p_hw_can->cfgstat & (1u << 5)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief CAN ����BUF�ͷ�
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_rxbuf_release (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->rctrl |= (1u << 4);
}

/**
 * \brief CAN ����BUF���ݴ洢ģʽ����
 */
typedef enum {
    AMHW_HC32F07X_CAN_RXBUF_NORMAL = 0, /* ����ģʽ */
    AMHW_HC32F07X_CAN_RXBUF_ALL    = 1, /* �洢����(�洢����)����*/
}amhw_hc32f07x_can_rxbuf_all_t;

/**
 * \brief CAN ����BUF���ݴ洢�趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_rxbuf_stores_all_set (amhw_hc32f07x_can_t *p_hw_can,
                                             amhw_hc32f07x_can_rxbuf_all_t flag)
{
    p_hw_can->rctrl = (p_hw_can->rctrl & (~(1u << 3)))|(flag << 3);
}

/**
 * \brief CAN ����BUF״̬
 */
typedef enum {
    AMHW_HC32F07X_CAN_RXBUF_EMPTY        = 0, /* �� */
    AMHW_HC32F07X_CAN_RXBUF_NOT_ALMOSTFULL = 1, /* �ǿյ�С���޶�ֵ */
    AMHW_HC32F07X_CAN_RXBUF_ALMOSTFULL     = 2, /* �����޶�ֵ��δ�� */
    AMHW_HC32F07X_CAN_RXBUF_FULL         = 3, /* �� */
}amhw_hc32f07x_can_rxbuf_status_t;

/**
 * \brief CAN TTCAN BUFģʽ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
amhw_hc32f07x_can_rxbuf_status_t 
amhw_hc32f07x_can_get_rxbuf_status (amhw_hc32f07x_can_t *p_hw_can)
{
   return (amhw_hc32f07x_can_rxbuf_status_t) (p_hw_can->rctrl & 0x03 );
}

/**
 * \brief CAN �շ��ж�
 * @{
 */
#define AMHW_HC32F07X_CAN_INT_RECV          (0x1 << 7ul)  /**< \brief �����ж� */
#define AMHW_HC32F07X_CAN_INT_RX_OVER       (0x1 << 6ul)  /**< \brief ���������ж� */
#define AMHW_HC32F07X_CAN_INT_RX_FULL       (0x1 << 5ul)  /**< \brief �������ж� */
#define AMHW_HC32F07X_CAN_INT_RX_ALMOSTFULL (0x1 << 4ul)  /**< \brief ���ս����ж� */
#define AMHW_HC32F07X_CAN_INT_TX_PTB        (0x1 << 3ul)  /**< \brief PTB�����ж� */
#define AMHW_HC32F07X_CAN_INT_TX_STB        (0x1 << 2ul)  /**< \brief STB�����ж� */
#define AMHW_HC32F07X_CAN_INT_ERROR         (0x1 << 1ul)  /**< \brief �����ж� */
#define AMHW_HC32F07X_CAN_INT_PASSIVE       (0x1 << 5ul)  /**< \brief ���󱻶��ж� */
#define AMHW_HC32F07X_CAN_INT_ARBILOST      (0x1 << 3ul)  /**< \brief �ٲ�ʧ���ж� */
#define AMHW_HC32F07X_CAN_INT_BUS_ERR       (0x1 << 1ul)  /**< \brief ���ߴ����ж� */
/**
 * @}
 */

/**
 * \brief CAN �շ��ж�ʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �жϱ�־���ο��궨��AMHW_HC32F07X_CAN_INT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_int_enable (amhw_hc32f07x_can_t *p_hw_can,
                                   uint8_t              flag)
{
    if(flag == AMHW_HC32F07X_CAN_INT_PASSIVE ||
       flag == AMHW_HC32F07X_CAN_INT_ARBILOST||
       flag == AMHW_HC32F07X_CAN_INT_BUS_ERR) {

        p_hw_can->errint |= (flag);
    }else {
        p_hw_can->rtie |= (flag);
    }
}

/**
 * \brief CAN �շ��жϽ���
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �ж�Դ���ο��궨��AMHW_HC32F07X_CAN_INT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_int_disable (amhw_hc32f07x_can_t *p_hw_can,
                                    uint8_t              flag)
{
    if(flag == AMHW_HC32F07X_CAN_INT_PASSIVE ||
       flag == AMHW_HC32F07X_CAN_INT_ARBILOST||
       flag == AMHW_HC32F07X_CAN_INT_BUS_ERR) {

        p_hw_can->errint &= ~(flag);
    }else {
        p_hw_can->rtie &= ~(flag);
    }
}

/**
 * \brief CAN ���������շ��ж�
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �ж�Դ���ο��궨��AMHW_HC32F07X_CAN_INT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_int_all_disable (amhw_hc32f07x_can_t *p_hw_can)
{
        p_hw_can->rtie = 0x00;
}

/**
 * \brief CAN �շ��жϱ�־
 * @{
 */
#define AMHW_HC32F07X_CAN_FLAG_RECV          (0x1 << 7ul)  /**< \brief �����жϱ�־ */
#define AMHW_HC32F07X_CAN_FLAG_RX_OVER       (0x1 << 6ul)  /**< \brief ���������жϱ�־ */
#define AMHW_HC32F07X_CAN_FLAG_RX_FULL       (0x1 << 5ul)  /**< \brief �������жϱ�־ */
#define AMHW_HC32F07X_CAN_FLAG_RX_ALMOSTFULL (0x1 << 4ul)  /**< \brief ���ս����жϱ�־ */
#define AMHW_HC32F07X_CAN_FLAG_TX_PTB        (0x1 << 3ul)  /**< \brief PTB�����жϱ�־ */
#define AMHW_HC32F07X_CAN_FLAG_TX_STB        (0x1 << 2ul)  /**< \brief STB�����жϱ�־*/
#define AMHW_HC32F07X_CAN_FLAG_ERROR         (0x1 << 1ul)  /**< \brief �����жϱ�־ */
#define AMHW_HC32F07X_CAN_FLAG_TX_ABORT      (0x1 << 0ul)  /**< \brief ȡ�������жϱ�־ */
/**
 * @}
 */

/**
 * \brief CAN �շ��жϱ�־��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �жϱ�־���ο��궨��AMHW_HC32F07X_CAN_FLAG_
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f07x_can_get_irq_status (amhw_hc32f07x_can_t *p_hw_can,
                                            uint8_t              flag)
{
   return (uint8_t) ((p_hw_can->rtif & flag ) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief CAN �շ��жϱ�־���
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �жϱ�־���ο��궨��AMHW_HC32F07X_CAN_FLAG_
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_irq_status_clr (amhw_hc32f07x_can_t *p_hw_can,
                                       uint8_t              flag)
{
     p_hw_can->rtif |= (flag);
}

/**
 * \brief CAN �����жϱ�־
 * @{
 */
#define AMHW_HC32F07X_CAN_ERR_FLAG_EWARN     (0x1 << 7ul)  /**< \brief ���󾯸��жϱ�־ */
#define AMHW_HC32F07X_CAN_ERR_FLAG_PASSIVE   (0x1 << 4ul)  /**< \brief ���󱻶��жϱ�־ */
#define AMHW_HC32F07X_CAN_ERR_FLAG_ARBILOST  (0x1 << 2ul)  /**< \brief �ٲ�ʧ���жϱ�־ */
#define AMHW_HC32F07X_CAN_ERR_FLAG_BUS_ERR   (0x1 << 0ul)  /**< \brief ���ߴ����жϱ�־ */
/**
 * @}
 */

/**
 * \brief CAN �����жϱ�־��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �жϱ�־���ο��궨��AMHW_HC32F07X_CAN_ERR_FLAG_
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f07x_can_get_err_status (amhw_hc32f07x_can_t *p_hw_can,
                                              uint8_t            flag)
{
   return (uint8_t) ((p_hw_can->errint  & flag ) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief CAN �����жϱ�־���
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �жϱ�־���ο��궨��AMHW_HC32F07X_CAN_FLAG_
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_err_status_clr (amhw_hc32f07x_can_t *p_hw_can,
                                       uint8_t              flag)
{
     p_hw_can->errint |= (flag);
}

/**
 * \brief CAN ���������־��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �жϱ�־���ο��궨��AMHW_HC32F07X_CAN_FLAG_
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f07x_can_err_active_get (amhw_hc32f07x_can_t *p_hw_can)
{
    return (uint8_t) ((p_hw_can->errint  & (1 << 6) ) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief CAN ������Ԥ��Ƶ�趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] presc     : ������Ԥ��Ƶֵ��8bit
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_brp_set (amhw_hc32f07x_can_t *p_hw_can,
                                uint8_t              presc)
{
     p_hw_can->bt = (p_hw_can->bt & (~(0xfful << 24))) | ((presc & 0xfful) << 24);
}

/**
 * \brief CAN ������Ԥ��Ƶ��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return ������Ԥ��Ƶֵ��8bit
 */
am_static_inline
uint8_t amhw_hc32f07x_can_brp_get (amhw_hc32f07x_can_t *p_hw_can)
{
     return (uint8_t)((p_hw_can->bt >> 24) & 0xfful);
}

/**
 * \brief CAN ͬ���������ʱ���趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] sjw       : ͬ���������ʱ�䣬7bit
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_sjw_set (amhw_hc32f07x_can_t *p_hw_can,
                                uint8_t              sjw)
{
     p_hw_can->bt = (p_hw_can->bt & (~(0x7f << 16))) | ((sjw & 0x7f) << 16);
}

/**
 * \brief CAN ͬ���������ʱ���ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return ͬ���������ʱ�䣬7bit
 */
am_static_inline
uint8_t amhw_hc32f07x_can_sjw_get (amhw_hc32f07x_can_t *p_hw_can)
{
     return (uint8_t)((p_hw_can->bt >> 16) & 0x7f);
}

/**
 * \brief CAN λ��2ʱ���趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] seg2     : λ��2ʱ�䣬7bit
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tseg2_set (amhw_hc32f07x_can_t *p_hw_can,
                                  uint8_t              seg2  )
{
     p_hw_can->bt = (p_hw_can->bt & (~(0x7f << 8))) | ((seg2 & 0x7f) << 8);
}

/**
 * \brief CAN λ��2ʱ���趨��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return λ��2ʱ�䣬7bit
 */
am_static_inline
uint8_t amhw_hc32f07x_can_tseg2_get (amhw_hc32f07x_can_t *p_hw_can )
{
     return (uint8_t)((p_hw_can->bt >> 8) & 0x7f);
}

/**
 * \brief CAN λ��1ʱ���趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] seg2     : λ��1ʱ�䣬8bit
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tseg1_set (amhw_hc32f07x_can_t *p_hw_can,
                                  uint8_t              seg1  )
{
     p_hw_can->bt = (p_hw_can->bt & (~0xff )) | (seg1 & 0xff);
}

/**
 * \brief CAN λ��1ʱ���趨��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return λ��1ʱ�䣬8bit
 */
am_static_inline
uint8_t amhw_hc32f07x_can_tseg1_get (amhw_hc32f07x_can_t *p_hw_can )
{
     return (uint8_t)(p_hw_can->bt & 0xff);
}

/**
 * \brief CAN ����״̬����
 */
typedef enum {
    AMHW_HC32F07X_CAN_ERROR_NO     = 0u, /* �޴��� */
    AMHW_HC32F07X_CAN_ERROR_BIT    = 1u, /* λ���� */
    AMHW_HC32F07X_CAN_ERROR_FORM   = 2u, /* ��ʽ���� */
    AMHW_HC32F07X_CAN_ERROR_STUFF  = 3u, /* ������ */
    AMHW_HC32F07X_CAN_ERROR_ACK    = 4u, /* Ӧ����� */
    AMHW_HC32F07X_CAN_ERROR_CRC    = 5u, /* CRC���� */
    AMHW_HC32F07X_CAN_ERROR_UNKOWN = 6u, /* δ֪���� */
}amhw_hc32f07x_can_error_t;

/**
 * \brief CAN ����״̬��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return ����״̬���ο�amhw_hc32f07x_can_error_t
 */
am_static_inline
amhw_hc32f07x_can_error_t 
amhw_hc32f07x_can_error_status_get (amhw_hc32f07x_can_t *p_hw_can )
{
     return (amhw_hc32f07x_can_error_t)((p_hw_can->ealcap >> 5) & 0x07);
}

/**
 * \brief CAN �ٲ�ʧ�ܲ���
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return �ٲ�ʧ��λ��
 */
am_static_inline
uint8_t amhw_hc32f07x_can_arbitration_lost_get (amhw_hc32f07x_can_t *p_hw_can)
{
     return (uint8_t)(p_hw_can->ealcap & 0x1f);
}

/**
 * \brief CAN ����BUF�����޶�����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] val       : ����BUF�����޶�ֵ
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_rxbuf_warning_set (amhw_hc32f07x_can_t *p_hw_can,
                                          uint8_t              val  )
{
     p_hw_can->limit = (p_hw_can->limit & (~(0x0f << 4))) | ((val & 0x0f) << 4);
}

/**
 * \brief CAN ���󾯸��޶�����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] val       : ���󾯸��޶�ֵ
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_err_warning_set (amhw_hc32f07x_can_t *p_hw_can,
                                        uint8_t              val  )
{
     p_hw_can->limit = (p_hw_can->limit & (~0x0f)) | (val & 0x0f);
}

/**
 * \brief CAN ���ʹ��������
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return �������ֵ
 */
am_static_inline
uint8_t amhw_hc32f07x_can_get_transerrorcount (amhw_hc32f07x_can_t *p_hw_can)
{
     return (uint8_t)(p_hw_can->tecnt);
}

/**
 * \brief CAN ���մ��������
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return �������ֵ
 */
am_static_inline
uint8_t amhw_hc32f07x_can_get_recverrorcount (amhw_hc32f07x_can_t *p_hw_can)
{
     return (uint8_t)(p_hw_can->recnt);
}

/**
 * \brief CAN ѡ��ɸѡ������
 */
typedef enum {
    AMHW_HC32F07X_CAN_ACF_ID     = 0u, /* ACFָ��ɸѡ��ID�Ĵ��� */
    AMHW_HC32F07X_CAN_ACF_MASK   = 1u, /* ACFָ��ɸѡ��MASK�Ĵ��� */
}amhw_hc32f07x_can_acf_t;

/**
 * \brief CAN ѡ��ɸѡ���趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �ο�ö�ٶ���amhw_hc32f07x_can_acf_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_acf_select_set (amhw_hc32f07x_can_t      *p_hw_can,
                                       amhw_hc32f07x_can_acf_t   flag)
{
     p_hw_can->acfctrl = (p_hw_can->acfctrl & (~(0x01 << 5))) | (flag << 5);
}

/**
 * \brief CAN ɸѡ����ʹ��
 */
typedef enum {
    AMHW_HC32F07X_CAN_FILTER1     = 0u, /* ɸѡ����1ʹ�� */
    AMHW_HC32F07X_CAN_FILTER2     = 1u, /* ɸѡ����2ʹ�� */
    AMHW_HC32F07X_CAN_FILTER3     = 2u, /* ɸѡ����3ʹ�� */
    AMHW_HC32F07X_CAN_FILTER4     = 3u, /* ɸѡ����4ʹ�� */
    AMHW_HC32F07X_CAN_FILTER5     = 4u, /* ɸѡ����5ʹ�� */
    AMHW_HC32F07X_CAN_FILTER6     = 5u, /* ɸѡ����6ʹ�� */
    AMHW_HC32F07X_CAN_FILTER7     = 6u, /* ɸѡ����7ʹ�� */
    AMHW_HC32F07X_CAN_FILTER8     = 7u, /* ɸѡ����8ʹ�� */
}amhw_hc32f07x_can_filter_t;

/**
 * \brief CAN ɸѡ����ַ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] filter    : �ο�ö�ٶ���amhw_hc32f07x_can_filter_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_filter_addr (amhw_hc32f07x_can_t        *p_hw_can,
                                    amhw_hc32f07x_can_filter_t  filter)
{
     p_hw_can->acfctrl = (filter & 0x0f);
}

/**
 * \brief CAN ɸѡ����ʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] filter    : �ο�ö�ٶ���amhw_hc32f07x_can_filter_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_filter_enable (amhw_hc32f07x_can_t        *p_hw_can,
                                      amhw_hc32f07x_can_filter_t  filter)
{
     p_hw_can->acfen |= (1u << filter);
}

/**
 * \brief CAN ɸѡ�������
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] filter    : �ο�ö�ٶ���amhw_hc32f07x_can_filter_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_filter_disable (amhw_hc32f07x_can_t        *p_hw_can,
                                       amhw_hc32f07x_can_filter_t  filter)
{
    p_hw_can->acfen &= ~(1u << filter);
}

/**
 * \brief CAN ɸѡ����ʹ��
 */
typedef enum {
    AMHW_HC32F07X_CAN_AIDE_STD  = 2u, /* �����ձ�׼֡ */
    AMHW_HC32F07X_CAN_AIDE_EXT  = 3u, /* ��������չ֡ */
    AMHW_HC32F07X_CAN_AIDE_ALL  = 0U, /* ���ձ�׼֡����չ֡ */
}amhw_hc32f07x_can_aide_t;

/**
 * \brief CAN ɸѡ�����������趨
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_ide_set (amhw_hc32f07x_can_t     *p_hw_can,
                                amhw_hc32f07x_can_aide_t flag)
{
     p_hw_can->acf = (p_hw_can->acf & (~(0x03 << 29))) | (flag << 29);
}

/**
 * \brief CAN ɸѡ��CODE/MASK����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] val       : ����ֵ
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_filter_code_set (amhw_hc32f07x_can_t *p_hw_can,
                                        uint32_t             val)
{
     p_hw_can->acf = (p_hw_can->acf & (~(0x1fffffff << 0))) | (val & 0x1fffffff);
}

/**
 * \brief CAN TTCAN����TBΪ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_tbslot_empty_set (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tbslot |= (1u << 7);
}

/**
 * \brief CAN TTCAN����TBΪ���
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_tbslot_filled_set (amhw_hc32f07x_can_t *p_hw_can)
{
    p_hw_can->tbslot |= (1u << 6);
}

/**
 * \brief CAN ɸѡ����ʹ��
 */
typedef enum {
    AMHW_HC32F07X_CAN_TBPTR_PTB   = 0u, /* ָ��PTB */
    AMHW_HC32F07X_CAN_TBPTR_STB1  = 1u, /* ָ��STB SLOT1 */
    AMHW_HC32F07X_CAN_TBPTR_STB2  = 2u, /* ָ��STB SLOT2 */
    AMHW_HC32F07X_CAN_TBPTR_STB3  = 3u, /* ָ��STB SLOT1 */
    AMHW_HC32F07X_CAN_TBPTR_STB4  = 4u, /* ָ��STB SLOT2 */
}amhw_hc32f07x_can_tbptr_t;

/**
 * \brief CAN ɸѡ��CODE/MASK����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �ο�ö����amhw_hc32f07x_can_tbptr_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tbptr_set (amhw_hc32f07x_can_t       *p_hw_can,
                                  amhw_hc32f07x_can_tbptr_t  flag)
{
     p_hw_can->tbslot = (p_hw_can->tbslot & (~(0x07<< 0))) | (flag & 0x07);
}

/**
 * \brief CAN TTCAN�ж�
 * @{
 */
#define AMHW_HC32F07X_CAN_TT_INT_WT  (0x1 << 7ul)    /**< \brief �����ж� */
#define AMHW_HC32F07X_CAN_TT_INT_IF  (0x1 << 4ul)    /**< \brief ʱ�䴥���ж� */
/**
 * @}
 */

/**
 * \brief CAN TTCAN�ж�ʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �ο�ö����AMHW_HC32F07X_CAN_TT_INT_	
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_int_enable (amhw_hc32f07x_can_t *p_hw_can,
                                      uint8_t              flag)
{
     p_hw_can->ttcfg |= flag;
}

/**
 * \brief CAN TTCAN�жϽ���
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �ο�ö����AMHW_HC32F07X_CAN_TT_INT_
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_int_disable (amhw_hc32f07x_can_t *p_hw_can,
                                       uint8_t              flag)
{
     p_hw_can->ttcfg &= ~flag;
}

/**
 * \brief CAN TTCAN�жϱ�־
 * @{
 */
#define AMHW_HC32F07X_CAN_TT_FLAG_WT  (0x1 << 6ul)    /**< \brief �����жϱ�־ */
#define AMHW_HC32F07X_CAN_TT_FLAG_ERR (0x1 << 5ul)   /**< \brief �����жϱ�־ */
#define AMHW_HC32F07X_CAN_TT_FLAG_IF  (0x1 << 3ul)    /**< \brief ʱ�䴥���жϱ�־ */
/**
 * @}
 */

/**
 * \brief CAN TTCAN�жϱ�־��ȡ
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �жϱ�־���ο��궨��AMHW_HC32F07X_CAN_TT_FLAG_
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
am_bool_t amhw_hc32f07x_can_tt_status_get (amhw_hc32f07x_can_t *p_hw_can,
                                           uint8_t              flag)
{
    return (uint8_t) ((p_hw_can->ttcfg & flag ) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief CAN TTCAN�жϱ�־����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �жϱ�־���ο��궨��AMHW_HC32F07X_CAN_TT_FLAG_
 *
 * \return AM_TRUE :��־��Ч
 *         AM_FALSE:��־��Ч
 */
am_static_inline
void amhw_hc32f07x_can_tt_status_clr (amhw_hc32f07x_can_t *p_hw_can,
                                      uint8_t              flag)
{
    p_hw_can->ttcfg |= flag;
}

/**
 * \brief CAN TTCAN������Ԥ��Ƶ
 */
typedef enum {
    AMHW_HC32F07X_CAN_TT_PRESC_DIV1  = 0u, /* DIV1 */
    AMHW_HC32F07X_CAN_TT_PRESC_DIV2  = 1u, /* DIV2 */
    AMHW_HC32F07X_CAN_TT_PRESC_DIV3  = 2u, /* DIV3 */
    AMHW_HC32F07X_CAN_TT_PRESC_DIV4  = 3u, /* DIV4 */
}amhw_hc32f07x_can_tt_presc_t;

/**
 * \brief CAN TTCAN������Ԥ��Ƶ����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : TTCAN������Ԥ��Ƶֵ���ο�ö����amhw_hc32f07x_can_tt_presc_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_prescdiv_set (amhw_hc32f07x_can_t *p_hw_can,
                                        uint8_t              flag)
{
    p_hw_can->ttcfg = (p_hw_can->ttcfg & (~(0x03<< 1))) | ((flag & 0x03) << 1);
}

/**
 * \brief CAN TTCANʹ��
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_enable (amhw_hc32f07x_can_t *p_hw_can)
{
     p_hw_can->ttcfg |= 0x01;
}

/**
 * \brief CAN TTCAN����
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_disable (amhw_hc32f07x_can_t *p_hw_can)
{
     p_hw_can->ttcfg &= ~(0x01);
}

/**
 * \brief CAN TTCAN�ο���ϢIDE����
 */
typedef enum {
    AMHW_HC32F07X_CAN_TT_IDE_STD  = 0u, /* ��׼��ʽ */
    AMHW_HC32F07X_CAN_TT_IDE_EXT  = 1u, /* ��չ��ʽ */
}amhw_hc32f07x_can_tt_ide_t;

/**
 * \brief CAN TTCAN�ο���ϢIDE����
 * \param[in] p_hw_can : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag     : IDE����ֵ���ο�ö����amhw_hc32f07x_can_tt_ide_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_refide_format_set (amhw_hc32f07x_can_t *p_hw_can,
                                             uint8_t              flag)
{
    p_hw_can->refmsg = (p_hw_can->refmsg & (~(1U << 31))) | ((flag & 0x01) << 31);;
}

/**
 * \brief CAN TTCAN�ο���ϢIDE����
 * \param[in] p_hw_can : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] val      : IDE����ֵ���ο�ö����amhw_hc32f07x_can_tt_ide_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_refid_set (amhw_hc32f07x_can_t *p_hw_can,
                                     uint32_t             val)
{
    p_hw_can->refmsg = (p_hw_can->refmsg & (1U << 31)) | (val & (~(1U << 31)));
}

/**
 * \brief CAN TTCAN��������
 */
typedef enum {
    AMHW_HC32F07X_CAN_TT_IMMEDIATE = 0u, /* �������� */
    AMHW_HC32F07X_CAN_TT_TIME      = 1u, /* ʱ�䴥�� */
    AMHW_HC32F07X_CAN_TT_SINGLE    = 2u, /* ���η��ʹ��� */
    AMHW_HC32F07X_CAN_TT_START     = 3u, /* ���Ϳ�ʼ���� */
    AMHW_HC32F07X_CAN_TT_STOP      = 4u, /* ����ֹͣ���� */
}amhw_hc32f07x_can_tt_trigger_type_t;

/**
 * \brief CAN TTCAN�ο���ϢIDE����
 * \param[in] p_hw_can : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag     : �������ͣ��ο�ö����amhw_hc32f07x_can_tt_trigger_type_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_trigger_type_set (amhw_hc32f07x_can_t                 *p_hw_can,
                                            amhw_hc32f07x_can_tt_trigger_type_t  flag)
{
    p_hw_can->refmsg  = (p_hw_can->refmsg & (~(0x03 << 8))) | 
                       ((flag & 0x03) << 8);
}

/**
 * \brief CAN TTCAN����ʹ�ܴ�������
 * \param[in] p_hw_can : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag     : ����ʹ�ܴ�������Ϊflag+1
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_tt_tew_set (amhw_hc32f07x_can_t *p_hw_can,
                                   uint8_t              flag)
{
    p_hw_can->trgcfg = (p_hw_can->trgcfg & (~(0x0f << 12))) | 
                       ((flag & 0x0f) << 12   );
}

/**
 * \brief CAN TTCAN���ʹ�����ָ��
 */
typedef enum {
    AMHW_HC32F07X_CAN_TTPTR_PTB   = 0u, /* ָ��PTB */
    AMHW_HC32F07X_CAN_TTPTR_STB1  = 1u, /* ָ��STB SLOT1 */
    AMHW_HC32F07X_CAN_TTPTR_STB2  = 2u, /* ָ��STB SLOT2 */
    AMHW_HC32F07X_CAN_TTPTR_STB3  = 3u, /* ָ��STB SLOT1 */
    AMHW_HC32F07X_CAN_TTPTR_STB4  = 4u, /* ָ��STB SLOT2 */
}amhw_hc32f07x_can_ttptr_t;

/**
 * \brief CAN ���ʹ�����TB slotָ������
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : �ο�ö����amhw_hc32f07x_can_ttptr_t
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_ttcan_ttptr_set (amhw_hc32f07x_can_t       *p_hw_can,
                                        amhw_hc32f07x_can_ttptr_t  flag)
{
     p_hw_can->trgcfg = (p_hw_can->trgcfg & (~(0x07<< 0))) | (flag & 0x07);
}

/**
 * \brief CAN ����ʱ������
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : ����ʱ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_ttcan_trig_set (amhw_hc32f07x_can_t *p_hw_can,
                                       uint16_t             flag)
{
     p_hw_can->trgtrig  = (p_hw_can->trgtrig & (~0xffff)) | flag;
}

/**
 * \brief CAN ��������ʱ������
 * \param[in] p_hw_can  : ָ��CAN�Ĵ����ṹ���ָ��
 * \param[in] flag      : ����ʱ��
 *
 * \return none
 */
am_static_inline
void amhw_hc32f07x_can_ttcan_wtrig_set (amhw_hc32f07x_can_t *p_hw_can,
                                        uint16_t             flag)
{
     p_hw_can->trgwtrig = (p_hw_can->trgwtrig & (~0xffff)) | flag;
}


/**
 * @} amhw_hc32f07x_if_can
 */
#pragma no_anon_unions
#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F07X_CAN_H */

/* end of file */

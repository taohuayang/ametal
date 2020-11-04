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
 * \brief USB interfaces for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-18  sdq, first implementation
 * \endinternal
 */
#ifndef __AMHW_HC32F460_USBD_H
#define __AMHW_HC32F460_USBD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_types.h"
#include "hc32f460_periph_map.h"
/**
 * \addtogroup amhw_hc32f460_if_usbd
 * \copydoc HC32F460_USBd.h
 * @{
 */

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

/* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

/* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */

/**
 * \brief USBFS AHB ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t GINTMSK                   : 1;  /**< \brief ȫ���ж�����*/
    __IO uint32_t HBSTLEN                   : 4;  /**< \brief ��������/����*/
    __IO uint32_t DMAEN                     : 1;  /**< \brief DMAʹ��*/
    uint32_t RESERVED6                      : 1;  /**< \brief ����*/
    __IO uint32_t TXFELVL                   : 1;  /**< \brief �豸TxFIFO������*/
    __IO uint32_t PTXFELVL                  : 1;  /**< \brief ������TxFIFO������*/
    uint32_t RESERVED9                      :23;  /**< \brief ����*/
} stc_usbfs_gahbcfg_field_t;

/**
 * \brief USBFS USB ���üĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t TOCAL                     : 3;  /**< \brief */
    uint32_t RESERVED3                      : 3;  /**< \brief ���� */
    __IO uint32_t PHYSEL                    : 1;  /**< \brief ȫ��ϵ���շ���ѡ�� */
    uint32_t RESERVED7                      : 3;  /**< \brief ���� */
    __IO uint32_t TRDT                      : 4;  /**< \brief USB��תʱ�� */
    uint32_t RESERVED14                     :15;  /**< \brief ���� */
    __IO uint32_t FHMOD                     : 1;  /**< \brief ǿ������ģʽ */
    __IO uint32_t FDMOD                     : 1;  /**< \brief ǿ���豸ģʽ */
    uint32_t RESERVED31                     : 1;  /**< \brief ���� */
} stc_usbfs_gusbcfg_field_t;

/**
 * \brief USBFS ��λ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CSRST                     : 1;  /**< \brief ģ����λ */
    __IO uint32_t HSRST                     : 1;  /**< \brief HCLK���߼���λ */
    __IO uint32_t FCRST                     : 1;  /**< \brief ����֡��������λ */
    uint32_t RESERVED3                      : 1;  /**< \brief ���� */
    __IO uint32_t RXFFLSH                   : 1;  /**< \brief RxFIFOˢ�� */
    __IO uint32_t TXFFLSH                   : 1;  /**< \brief TxFIFOˢ�� */
    __IO uint32_t TXFNUM                    : 5;  /**< \brief TxFIFO��� */
    uint32_t RESERVED11                     :19;  /**< \brief ���� */
    __IO uint32_t DMAREQ                    : 1;  /**< \brief DMA�����ź� */
    __IO uint32_t AHBIDL                    : 1;  /**< \brief AHB���������� */
} stc_usbfs_grstctl_field_t;

/**
 * \brief USBFS ȫ���ж�״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CMOD                      : 1;  /**< \brief ��ǰ����ģʽ */
    __IO uint32_t MMIS                      : 1;  /**< \brief ģʽ��ƥ���ж� */
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t SOF                       : 1;  /**< \brief ֡��ʼ�ж� */
    __IO uint32_t RXFLNE                    : 1;  /**< \brief RxFIFO�ǿ��ж� */
    __IO uint32_t NPTXFE                    : 1;  /**< \brief ��������TxFIFO���ж� */
    __IO uint32_t GINAKEFF                  : 1;  /**< \brief ȫ�ַ�������INNAK��Ч�ж� */
    __IO uint32_t GOUTNAKEFF                : 1;  /**< \brief ȫ��OUT NAK��Ч�ж� */
    uint32_t RESERVED8                      : 2;  /**< \brief ���� */
    __IO uint32_t ESUSP                     : 1;  /**< \brief ���ڹ����ж� */
    __IO uint32_t USBSUSP                   : 1;  /**< \brief USB�����ж� */
    __IO uint32_t USBRST                    : 1;  /**< \brief USB��λ�ж� */
    __IO uint32_t ENUMDNE                   : 1;  /**< \brief ö������ж� */
    __IO uint32_t ISOODRP                   : 1;  /**< \brief ����ͬ��OUT���ݰ��ж� */
    __IO uint32_t EOPF                      : 1;  /**< \brief ������֡�����ж� */
    uint32_t RESERVED16                     : 2;  /**< \brief ���� */
    __IO uint32_t IEPINT                    : 1;  /**< \brief IN�˵��ж� */
    __IO uint32_t OEPINT                    : 1;  /**< \brief OUT�˵��ж� */
    __IO uint32_t IISOIXFR                  : 1;  /**< \brief δ���INͬ������ */
    __IO uint32_t IPXFR_INCOMPISO           : 1;  /**< \brief δ��������Դ���/δ���OUTͬ������ */
    __IO uint32_t DATAFSUSP                 : 1;  /**< \brief ���ݻ�ȡ���� */
    uint32_t RESERVED23                     : 1;  /**< \brief ���� */
    __IO uint32_t HPRTINT                   : 1;  /**< \brief �����˿��ж� */
    __IO uint32_t HCINT                     : 1;  /**< \brief ����ͨ���ж�*/
    __IO uint32_t PTXFE                     : 1;  /**< \brief ������TxFIFO���ж� */
    uint32_t RESERVED27                     : 1;  /**< \brief ���� */
    __IO uint32_t CIDSCHG                   : 1;  /**< \brief ������ID��״̬�仯�ж� */
    __IO uint32_t DISCINT                   : 1;  /**< \brief ��⵽�Ͽ������ж� */
    __IO uint32_t VBUSVINT                  : 1;  /**< \brief VBUS��Ч�ж� */
    __IO uint32_t WKUINT                    : 1;  /**< \brief ��⵽�ָ�/Զ�̻����ж� */
} stc_usbfs_gintsts_field_t;

/**
 * \brief USBFS ȫ���ж����μĴ���λ��ṹ��
 */
typedef struct
{
    uint32_t RESERVED0                      : 1;  /**< \brief ���� */
    __IO uint32_t MMISM                     : 1;  /**< \brief ģʽ��ƥ���ж����� */
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t SOFM                      : 1;  /**< \brief ���� */
    __IO uint32_t RXFNEM                    : 1;  /**< \brief RxFIFO�ǿ��ж����� */
    __IO uint32_t NPTXFEM                   : 1;  /**< \brief ��������TxFIFO���ж����� */
    __IO uint32_t GINAKEFFM                 : 1;  /**< \brief ȫ�ַ�������IN NAK��Ч�ж����� */
    __IO uint32_t GOUTNAKEFFM               : 1;  /**< \brief ȫ��OUT NAK��Ч�ж����� */
    uint32_t RESERVED8                      : 2;  /**< \brief ���� */
    __IO uint32_t ESUSPM                    : 1;  /**< \brief ���ڹ����ж����� */
    __IO uint32_t USBSUSPM                  : 1;  /**< \brief USB�����ж����� */
    __IO uint32_t USBRSTM                   : 1;  /**< \brief USB��λ�ж����� */
    __IO uint32_t ENUMDNEM                  : 1;  /**< \brief ö������ж����� */
    __IO uint32_t ISOODRPM                  : 1;  /**< \brief ����ͬ��OUT���ݰ��ж����� */
    __IO uint32_t EOPFM                     : 1;  /**< \brief ������֡�����ж����� */
    uint32_t RESERVED16                     : 2;  /**< \brief ���� */
    __IO uint32_t IEPIM                     : 1;  /**< \brief IN�˵��ж����� */
    __IO uint32_t OEPIM                     : 1;  /**< \brief OUT�˵��ж����� */
    __IO uint32_t IISOIXFRM                 : 1;  /**< \brief δ���INͬ�������ж����� */
    __IO uint32_t IPXFRM_INCOMPISOOUTM      : 1;  /**< \brief δ��������Դ����ж�����/δ���OUTͬ�������ж����� */
    __IO uint32_t DATAFSUSPM                : 1;  /**< \brief ���ݻ�ȡ�����ж����� */
    uint32_t RESERVED23                     : 1;  /**< \brief ���� */
    __IO uint32_t HPRTIM                    : 1;  /**< \brief �����˿��ж����� */
    __IO uint32_t HCIM                      : 1;  /**< \brief ����ͨ���ж����� */
    __IO uint32_t PTXFEM                    : 1;  /**< \brief ������TxFIFO���ж����� */
    uint32_t RESERVED27                     : 1;  /**< \brief ���� */
    __IO uint32_t CIDSCHGM                  : 1;  /**< \brief �ж�������ID��״̬�仯�ж����� */
    __IO uint32_t DISCIM                    : 1;  /**< \brief ��⵽�Ͽ������ж����� */
    __IO uint32_t VBUSVIM                   : 1;  /**< \brief VBUS��Ч�ж����� */
    __IO uint32_t WKUIM                     : 1;  /**< \brief ��⵽�ָ�/Զ�̻����ж����� */
} stc_usbfs_gintmsk_field_t;

/**
 * \brief USBFS ����״̬���Զ�ȡ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CHNUM_EPNUM               : 4;  /**< \brief ͨ����� */
    __IO uint32_t BCNT                      :11;  /**< \brief �ֽڼ��� */
    __IO uint32_t DPID                      : 2;  /**< \brief ����PID */
    __IO uint32_t PKTSTS                    : 4;  /**< \brief ���ݰ�״̬ */
    uint32_t RESERVED21                     :11;  /**< \brief ���� */
} stc_usbfs_grxstsr_field_t;

/**
 * \brief USBFS ״̬��ȡ�ͳ�ջ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CHNUM_EPNUM               : 4;  /**< \brief ͨ����� */
    __IO uint32_t BCNT                      :11;  /**< \brief �ֽڼ��� */
    __IO uint32_t DPID                      : 2;  /**< \brief ����PID */
    __IO uint32_t PKTSTS                    : 4;  /**< \brief ���ݰ�״̬ */
    uint32_t RESERVED21                     :11;  /**< \brief ���� */
} stc_usbfs_grxstsp_field_t;

/**
 * \brief USBFS ����FIFO��С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t RXFD                      :11;  /**< \brief RxFIFO��� */
    uint32_t RESERVED11                     :21;  /**< \brief ���� */
} stc_usbfs_grxfsiz_field_t;

/**
 * \brief USBFS �����������Է���FIFO��С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t NPTXFSA                   :16;  /**< \brief �������Է���RAM��ʼ��ַ/�˵�0����RAM��ʼ��ַ */
    __IO uint32_t NPTXFD                    :16;  /**< \brief ��������TxFIFO���/�˵�0 TxFIFO��� */
} stc_usbfs_hnptxfsiz_field_t;

/**
 * \brief USBFS �����������Է���FIFO/����״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t NPTXFSAV                  :16;  /**< \brief �������Է���������ж��� */
    __IO uint32_t NPTQXSAV                  : 8;  /**< \brief �������Է���������п��ÿռ� */
    __IO uint32_t NPTXQTOP                  : 7;  /**< \brief �������Է���������ж��� */
    uint32_t RESERVED31                     : 1;  /**< \brief ���� */
} stc_usbfs_hnptxsts_field_t;

/**
 * \brief USBFS ���������Է���FIFO��С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t PTXSA                     :12;  /**< \brief ����������TxFIFO��ʼ��ַ */
    uint32_t RESERVED12                     : 4;  /**< \brief ���� */
    __IO uint32_t PTXFD                     :11;  /**< \brief ����������TxFIFO��� */
    uint32_t RESERVED27                     : 5;  /**< \brief ���� */
} stc_usbfs_hptxfsiz_field_t;

/**
 * \brief USBFS �豸IN�˵㷢��FIFO��С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t INEPTXSA                  :12;  /**< \brief IN�˵�TxFIFOx RAM��ʼ��ַ */
    uint32_t RESERVED12                     : 4;  /**< \brief ���� */
    __IO uint32_t INEPTXFD                  :10;  /**< \brief IN�˵�TxFIFO��� */
    uint32_t RESERVED26                     : 6;  /**< \brief ���� */
} stc_usbfs_dieptxf_field_t;

/**
 * \brief USBFS �������üĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t FSLSPCS                   : 2;  /**< \brief FS/LS PHYʱ��ѡ�� */
    __IO uint32_t FSLSS                     : 1;  /**< \brief ��֧��FS��LS */
    uint32_t RESERVED3                      :29;  /**< \brief ���� */
} stc_usbfs_hcfg_field_t;

/**
 * \brief USBFS ����֡ʱ�����Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t FRIVL                     :16;  /**< \brief ֡��� */
    uint32_t RESERVED16                     :16;  /**< \brief ���� */
} stc_usbfs_hfir_field_t;

/**
 * \brief USBFS ����֡���/֡ʣ��ʱ��Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t FRNUM                     :16;  /**< \brief ֡��� */
    __IO uint32_t FTREM                     :16;  /**< \brief ֡ʣ��ʱ�� */
} stc_usbfs_hfnum_field_t;

/**
 * \brief USBFS ���������Է���FIFO/����״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t PTXFSAVL                  :16;  /**< \brief �����Է�������FIFO���ÿռ� */
    __IO uint32_t PTXQSAV                   : 8;  /**< \brief �����Է���������п��ÿռ� */
    __IO uint32_t PTXQTOP                   : 8;  /**< \brief �����Է���������ж��� */
} stc_usbfs_hptxsts_field_t;

/**
 * \brief USBFS ����ȫ��ͨ���жϼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t HAINT                     :12;  /**< \brief ͨ���ж� */
    uint32_t RESERVED12                     :20;  /**< \brief ���� */
} stc_usbfs_haint_field_t;

/**
 * \brief USBFS ����ȫ��ͨ���ж����μĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t HAINTM                    :12;  /**< \brief ͨ���ж����� */
    uint32_t RESERVED12                     :20;  /**< \brief ���� */
} stc_usbfs_haintmsk_field_t;

/**
 * \brief USBFS �����˿ڿ��ƺ�״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t PCSTS                     : 1;  /**< \brief �˿�����״̬ */
    __IO uint32_t PCDET                     : 1;  /**< \brief ��⵽�˿����� */
    __IO uint32_t PENA                      : 1;  /**< \brief �˿�ʹ�� */
    __IO uint32_t PENCHNG                   : 1;  /**< \brief �˿�ʹ��/��ֹ�仯 */
    uint32_t RESERVED4                      : 2;  /**< \brief ���� */
    __IO uint32_t PRES                      : 1;  /**< \brief �˿ڻָ� */
    __IO uint32_t PSUSP                     : 1;  /**< \brief �˿ڹ��� */
    __IO uint32_t PRST                      : 1;  /**< \brief �˿ڸ�λ */
    uint32_t RESERVED9                      : 1;  /**< \brief ���� */
    __IO uint32_t PLSTS                     : 2;  /**< \brief �˿���״̬ */
    __IO uint32_t PWPR                      : 1;  /**< \brief �˿ڵ�Դ */
    uint32_t RESERVED13                     : 4;  /**< \brief ���� */
    __IO uint32_t PSPD                      : 2;  /**< \brief �˿��ٶ� */
    uint32_t RESERVED19                     :13;  /**< \brief ���� */
} stc_usbfs_hprt_field_t;

/**
 * \brief USBFS ����ͨ��x���ԼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t MPSIZ                     :11;  /**< \brief ������ݰ���С*/
    __IO uint32_t EPNUM                     : 4;  /**< \brief �˵��� */
    __IO uint32_t EPDIR                     : 1;  /**< \brief �˵㷽�� */
    uint32_t RESERVED16                     : 1;  /**< \brief ���� */
    __IO uint32_t LSDEV                     : 1;  /**< \brief �����豸 */
    __IO uint32_t EPTYP                     : 2;  /**< \brief �˵����� */
    uint32_t RESERVED20                     : 2;  /**< \brief ���� */
    __IO uint32_t DAD                       : 7;  /**< \brief �豸��ַ */
    __IO uint32_t ODDFRM                    : 1;  /**< \brief ����֡ */
    __IO uint32_t CHDIS                     : 1;  /**< \brief ͨ����ֹ */
    __IO uint32_t CHENA                     : 1;  /**< \brief ͨ��ʹ�� */
} stc_usbfs_hcchar_field_t;

/**
 * \brief USBFS ����ͨ��x�жϼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRC                      : 1;  /**< \brief ������� */
    __IO uint32_t CHH                       : 1;  /**< \brief ͨ��ֹͣ */
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t STALL                     : 1;  /**< \brief �յ�STALL��Ӧ */
    __IO uint32_t NAK                       : 1;  /**< \brief �յ�NAK��Ӧ */
    __IO uint32_t ACK                       : 1;  /**< \brief �յ�/����ACK��Ӧ */
    uint32_t RESERVED6                      : 1;  /**< \brief ���� */
    __IO uint32_t TXERR                     : 1;  /**< \brief ͨ��������� */
    __IO uint32_t BBERR                     : 1;  /**< \brief ���Ŵ��� */
    __IO uint32_t FRMOR                     : 1;  /**< \brief ֡������� */
    __IO uint32_t DTERR                     : 1;  /**< \brief �����л����� */
    uint32_t RESERVED11                     :21;  /**< \brief ���� */
} stc_usbfs_hcint_field_t;

/**
 * \brief USBFS ����ͨ��x�ж����μĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRCM                     : 1;  /**< \brief ��������ж����� */
    __IO uint32_t CHHM                      : 1;  /**< \brief ͨ��ֹͣ�ж����� */
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t STALLM                    : 1;  /**< \brief �յ�STALL��Ӧ�ж����� */
    __IO uint32_t NAKM                      : 1;  /**< \brief �յ�NAK��Ӧ�ж����� */
    __IO uint32_t ACKM                      : 1;  /**< \brief �յ�/����ACK��Ӧ�ж����� */
    uint32_t RESERVED6                      : 1;  /**< \brief ���� */
    __IO uint32_t TXERRM                    : 1;  /**< \brief ͨ����������ж����� */
    __IO uint32_t BBERRM                    : 1;  /**< \brief ���Ŵ����ж����� */
    __IO uint32_t FRMORM                    : 1;  /**< \brief ֡��������ж����� */
    __IO uint32_t DTERRM                    : 1;  /**< \brief �����л������ж����� */
    uint32_t RESERVED11                     :21;  /**< \brief ���� */
} stc_usbfs_hcintmsk_field_t;

/**
 * \brief USBFS ����ͨ��x�����С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRSIZ                    :19;  /**< \brief �����С */
    __IO uint32_t PKTCNT                    :10;  /**< \brief ���ݰ����� */
    __IO uint32_t DPID                      : 2;  /**< \brief ����PID */
    uint32_t RESERVED31                     : 1;  /**< \brief ���� */
} stc_usbfs_hctsiz_field_t;

/**
 * \brief USBFS �豸���üĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DSPD                      : 2;  /**< \brief �豸�ٶ� */
    __IO uint32_t NZLSOHSK                  : 1;  /**< \brief ���㳤��״̬OUT�����ź� */
    uint32_t RESERVED3                      : 1;  /**< \brief ���� */
    __IO uint32_t DAD                       : 7;  /**< \brief �豸��ַ */
    __IO uint32_t PFIVL                     : 2;  /**< \brief ������֡��� */
    uint32_t RESERVED13                     :19;  /**< \brief ���� */
} stc_usbfs_dcfg_field_t;

/**
 * \brief USBFS �豸���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t RWUSIG                    : 1;  /**< \brief ����Զ�̻����ź� */
    __IO uint32_t SDIS                      : 1;  /**< \brief ����� */
    __IO uint32_t GINSTS                    : 1;  /**< \brief ȫ��IN NAK״̬ */
    __IO uint32_t GONSTS                    : 1;  /**< \brief ȫ��OUT NAK״̬ */
    __IO uint32_t TCTL                      : 3;
    __IO uint32_t SGINAK                    : 1;  /**< \brief ��λȫ��IN NAK */
    __IO uint32_t CGINAK                    : 1;  /**< \brief ����ȫ��IN NAK */
    __IO uint32_t SGONAK                    : 1;  /**< \brief ��λȫ��OUT NAK */
    __IO uint32_t CGONAK                    : 1;  /**< \brief ����ȫ��OUT NAK */
    __IO uint32_t POPRGDNE                  : 1;  /**< \brief �ϵ������ */
    uint32_t RESERVED12                     :20;  /**< \brief ���� */
} stc_usbfs_dctl_field_t;

/**
 * \brief USBFS �豸״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SUSPSTS                   : 1;  /**< \brief ����״̬ */
    __IO uint32_t ENUMSPD                   : 2;  /**< \brief ö���ٶ� */
    __IO uint32_t EERR                      : 1;  /**< \brief �������� */
    uint32_t RESERVED4                      : 4;  /**< \brief ���� */
    __IO uint32_t FNSOF                     :14;  /**< \brief ����SOF��֡��� */
    uint32_t RESERVED22                     :10;  /**< \brief ���� */
} stc_usbfs_dsts_field_t;

/**
 * \brief USBFS �豸IN�˵�ͨ���ж����μĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRCM                     : 1;  /**< \brief ��������ж����� */
    __IO uint32_t EPDM                      : 1;  /**< \brief �˵��ֹ�ж����� */
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t TOM                       : 1;  /**< \brief ��ʱ�ж����� */
    __IO uint32_t ITTXFEMSK                 : 1;  /**< \brief TxFIFOΪ��ʱ���յ�IN�����ж����� */
    __IO uint32_t INEPNMM                   : 1;  /**< \brief EP��ƥ��ʱ���յ�IN�����ж����� */
    __IO uint32_t IINEPNEM                  : 1;  /**< \brief IN�˵�NAK��Ч�ж����� */
    uint32_t RESERVED7                      :25;  /**< \brief ���� */
} stc_usbfs_diepmsk_field_t;

/**
 * \brief USBFS �豸OUT�˵�ͨ���ж����μĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRCM                     : 1;  /**< \brief ��������ж����� */
    __IO uint32_t EPDM                      : 1;  /**< \brief �˵��ֹ�ж�����*/
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t STUPM                     : 1;  /**< \brief SETUP�׶�����ж����� */
    __IO uint32_t OTEPDM                    : 1;  /**< \brief �˵��ֹʱ���յ�OUT�����ж����� */
    uint32_t RESERVED5                      :27;  /**< \brief ���� */
} stc_usbfs_doepmsk_field_t;

/**
 * \brief USBFS �豸ȫ��˵��жϼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t IEPINT                    : 6;  /**< \brief IN�˵��ж�λ */
    uint32_t RESERVED6                      :10;  /**< \brief ���� */
    __IO uint32_t OEPINT                    : 6;  /**< \brief OUT�˵��ж�λ */
    uint32_t RESERVED22                     :10;  /**< \brief ���� */
} stc_usbfs_daint_field_t;

/**
 * \brief USBFS �豸ȫ��˵��ж����μĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t IEPINTM                   : 6;  /**< \brief IN�˵��ж�����λ */
    uint32_t RESERVED6                      :10;  /**< \brief ���� */
    __IO uint32_t OEPINTM                   : 6;  /**< \brief OUT�˵��ж�����λ */
    uint32_t RESERVED22                     :10;  /**< \brief ���� */
} stc_usbfs_daintmsk_field_t;

/**
 * \brief USBFS �豸IN�˵�FIFO���ж����μĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t INEPTXFEM                 : 6;  /**< \brief IN EP TxFIFO���ж�����λ */
    uint32_t RESERVED6                      :26;  /**< \brief ���� */
} stc_usbfs_diepempmsk_field_t;

/**
 * \brief USBFS �豸IN�˵�0���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t MPSIZ                     : 2;  /**< \brief ������ݰ���С */
    uint32_t RESERVED2                      :13;  /**< \brief ���� */
    __IO uint32_t USBAEP                    : 1;  /**< \brief USB��˵� */
    uint32_t RESERVED16                     : 1;  /**< \brief ���� */
    __IO uint32_t NAKSTS                    : 1;  /**< \brief NAK״̬ */
    __IO uint32_t EPTYP                     : 2;  /**< \brief �˵����� */
    uint32_t RESERVED20                     : 1;  /**< \brief ���� */
    __IO uint32_t STALL                     : 1;  /**< \brief STALL���� */
    __IO uint32_t TXFNUM                    : 4;  /**< \brief TxFIFO��� */
    __IO uint32_t CNAK                      : 1;  /**< \brief ����NAKλ */
    __IO uint32_t SNAK                      : 1;  /**< \brief ��ΪNAKλ */
    uint32_t RESERVED28                     : 2;  /**< \brief ���� */
    __IO uint32_t EPDIS                     : 1;  /**< \brief �˵��ֹ */
    __IO uint32_t EPENA                     : 1;  /**< \brief �˵�ʹ�� */
} stc_usbfs_diepctl0_field_t;

/**
 * \brief USBFS �豸IN�˵�x�жϼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRC                      : 1;  /**< \brief ��������ж� */
    __IO uint32_t EPDISD                    : 1;  /**< \brief �˵��ֹ�ж� */
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t TOC                       : 1;  /**< \brief ��ʱ */
    __IO uint32_t TTXFE                     : 1;  /**< \brief TxFIFOΪ��ʱ���յ�IN���� */
    uint32_t RESERVED5                      : 1;  /**< \brief ���� */
    __IO uint32_t NEPNE                     : 1;  /**< \brief IN�˵�NAK��Ч */
    __IO uint32_t TXFE                      : 1;  /**< \brief ����FIFOΪ�� */
    uint32_t RESERVED8                      :24;  /**< \brief ���� */
} stc_usbfs_diepint0_field_t;

/**
 * \brief USBFS �豸IN�˵�0�����С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRSIZ                    : 7;  /**< \brief �����С */
    uint32_t RESERVED7                      :12;  /**< \brief ���� */
    __IO uint32_t PKTCNT                    : 2;  /**< \brief ���ݰ����� */
    uint32_t RESERVED21                     :11;  /**< \brief ���� */
} stc_usbfs_dieptsiz0_field_t;

/**
 * \brief USBFS �豸IN�˵㷢��FIFO״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t INEPTFSAV                 :16;  /**< \brief IN�˵�TxFIFO���ÿռ� */
    uint32_t RESERVED16                     :16;  /**< \brief ���� */
} stc_usbfs_dtxfsts0_field_t;

/**
 * \brief USBFS �豸IN�˵�x���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t MPSIZ                     :11;  /**< \brief ������ݰ���С */
    uint32_t RESERVED11                     : 4;  /**< \brief ���� */
    __IO uint32_t USBAEP                    : 1;  /**< \brief USB��˵� */
    __IO uint32_t EONUM_DPID                : 1;  /**< \brief ż��/����֡�˵�����PID */
    __IO uint32_t NAKSTS                    : 1;  /**< \brief NAK״̬ */
    __IO uint32_t EPTYP                     : 2;  /**< \brief �˵����� */
    uint32_t RESERVED20                     : 1;  /**< \brief ���� */
    __IO uint32_t STALL                     : 1;  /**< \brief STALL���� */
    __IO uint32_t TXFNUM                    : 4;  /**< \brief TxFIFO��� */
    __IO uint32_t CNAK                      : 1;  /**< \brief ����NAKλ */
    __IO uint32_t SNAK                      : 1;  /**< \brief ��ΪNAKλ */
    __IO uint32_t SD0PID_SEVNFRM            : 1;  /**< \brief ����DATA0 PID/SEVNFRM */
    __IO uint32_t SODDFRM                   : 1;  /**< \brief ��������֡ */
    __IO uint32_t EPDIS                     : 1;  /**< \brief �˵��ֹ */
    __IO uint32_t EPENA                     : 1;  /**< \brief �˵�ʹ�� */
} stc_usbfs_diepctl_field_t;

/**
 * \brief USBFS �豸IN�˵�x�жϼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRC                      : 1;  /**< \brief ��������ж� */
    __IO uint32_t EPDISD                    : 1;  /**< \brief �˵��ֹ�ж� */
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t TOC                       : 1;  /**< \brief ��ʱ */
    __IO uint32_t TTXFE                     : 1;  /**< \brief TxFIFOΪ��ʱ���յ���IN���� */
    uint32_t RESERVED5                      : 1;  /**< \brief ���� */
    __IO uint32_t NEPNE                     : 1;  /**< \brief IN�˵�NAK��Ч */
    __IO uint32_t TXFE                      : 1;  /**< \brief ����FIFOΪ�� */
    uint32_t RESERVED8                      :24;  /**< \brief ���� */
} stc_usbfs_diepint_field_t;

/**
 * \brief USBFS �豸IN�˵�x�����С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRSIZ                    :19;  /**< \brief �����С */
    __IO uint32_t PKTCNT                    :10;  /**< \brief ���ݰ����� */
    __IO uint32_t MC                        : 2;
    uint32_t RESERVED31                     : 1;  /**< \brief ���� */
} stc_usbfs_dieptsiz_field_t;

/**
 * \brief USBFS �豸IN�˵㷢��FIFO״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t INEPTFSAV                 :16;  /**< \brief IN�˵�TxFIFO���ÿռ� */
    uint32_t RESERVED16                     :16;  /**< \brief ���� */
} stc_usbfs_dtxfsts_field_t;

/**
 * \brief USBFS �豸����OUT�˵�0���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t MPSIZ                     : 2;  /**< \brief ������ݰ���С */
    uint32_t RESERVED2                      :13;  /**< \brief ���� */
    __IO uint32_t USBAEP                    : 1;  /**< \brief USB��˵� */
    uint32_t RESERVED16                     : 1;  /**< \brief ���� */
    __IO uint32_t NAKSTS                    : 1;  /**< \brief NAK״̬ */
    __IO uint32_t EPTYP                     : 2;  /**< \brief �˵����� */
    __IO uint32_t SNPM                      : 1;  /**< \brief ����ģʽ */
    __IO uint32_t STALL                     : 1;  /**< \brief STALL���� */
    uint32_t RESERVED22                     : 4;  /**< \brief ���� */
    __IO uint32_t CNAK                      : 1;  /**< \brief ����NAKλ */
    __IO uint32_t SNAK                      : 1;  /**< \brief ��ΪNAKλ */
    uint32_t RESERVED28                     : 2;  /**< \brief ���� */
    __IO uint32_t EPDIS                     : 1;  /**< \brief �˵��ֹ */
    __IO uint32_t EPENA                     : 1;  /**< \brief �˵�ʹ�� */
} stc_usbfs_doepctl0_field_t;

/**
 * \brief USBFS �豸OUT�˵�x�жϼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRC                      : 1;  /**< \brief ��������ж� */
    __IO uint32_t EPDISD                    : 1;  /**< \brief �˵��ֹ�ж� */
    uint32_t RESERVED2                      : 1;  /**< \brief ���� */
    __IO uint32_t STUP                      : 1;  /**< \brief SETUP�׶���� */
    __IO uint32_t OTEPDIS                   : 1;  /**< \brief �˵��ֹʱ���յ�OUT���� */
    uint32_t RESERVED5                      : 1;  /**< \brief ���� */
    __IO uint32_t B2BSTUP                   : 1;  /**< \brief ���ӵ�������SETUP���ݰ� */
    uint32_t RESERVED7                      :25;  /**< \brief ���� */
} stc_usbfs_doepint_field_t;

/**
 * \brief USBFS �豸OUT�˵�0�����С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRSIZ                    : 7;  /**< \brief �����С */
    uint32_t RESERVED7                      :12;  /**< \brief ���� */
    __IO uint32_t PKTCNT                    : 1;  /**< \brief ���ݰ����� */
    uint32_t RESERVED20                     : 9;  /**< \brief ���� */
    __IO uint32_t STUPCNT                   : 2;  /**< \brief SETUP���ݰ����� */
    uint32_t RESERVED31                     : 1;  /**< \brief ���� */
} stc_usbfs_doeptsiz0_field_t;

/**
 * \brief USBFS �豸OUT�˵�x���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t MPSIZ                     :11;  /**< \brief ������ݰ���С */
    uint32_t RESERVED11                     : 4;  /**< \brief ���� */
    __IO uint32_t USBAEP                    : 1;  /**< \brief USB��˵� */
    __IO uint32_t DPID                      : 1;  /**< \brief ż��/����֡/�˵�����PID */
    __IO uint32_t NAKSTS                    : 1;  /**< \brief NAK״̬ */
    __IO uint32_t EPTYP                     : 2;  /**< \brief �˵����� */
    __IO uint32_t SNPM                      : 1;  /**< \brief ����ģʽ */
    __IO uint32_t STALL                     : 1;  /**< \brief STALL���� */
    uint32_t RESERVED22                     : 4;  /**< \brief ���� */
    __IO uint32_t CNAK                      : 1;  /**< \brief ����NAKλ */
    __IO uint32_t SNAK                      : 1;  /**< \brief ��ΪNAKλ */
    __IO uint32_t SD0PID                    : 1;  /**< \brief ����DATA0 PID/SEVNFRM */
    __IO uint32_t SD1PID                    : 1;  /**< \brief ����DATA1 PID/SEVNFRM */
    __IO uint32_t EPDIS                     : 1;  /**< \brief �˵��ֹ */
    __IO uint32_t EPENA                     : 1;  /**< \brief �˵�ʹ�� */
} stc_usbfs_doepctl_field_t;

/**
 * \brief USBFS �豸OUT�˵�x�����С�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t XFRSIZ                    :19;  /**< \brief �����С */
    __IO uint32_t PKTCNT                    :10;  /**< \brief ���ݰ����� */
    uint32_t RESERVED29                     : 3;  /**< \brief ���� */
} stc_usbfs_doeptsiz_field_t;

/**
 * \brief USBFS ʱ���ſؿ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t STPPCLK                   : 1;  /**< \brief ֹͣPHYʱ�� */
    __IO uint32_t GATEHCLK                  : 1;  /**< \brief �ſ�HCLK */
    uint32_t RESERVED2                      :30;  /**< \brief ���� */
} stc_usbfs_pcgcctl_field_t;

/**
 *  \brief USB �Ĵ����ṹ�嶨��
 */
typedef struct
{
    uint8_t RESERVED0[8];                   /**< \brief ����*/
    union
    {
        __IO uint32_t GAHBCFG;              /**< \brief AHB���ƼĴ���*/
        stc_usbfs_gahbcfg_field_t GAHBCFG_f;
    };
    union
    {
        __IO uint32_t GUSBCFG;              /**< \brief USB���üĴ���*/
        stc_usbfs_gusbcfg_field_t GUSBCFG_f;
    };
    union
    {
        __IO uint32_t GRSTCTL;              /**< \brief ��λ�Ĵ���*/
        stc_usbfs_grstctl_field_t GRSTCTL_f;
    };
    union
    {
        __IO uint32_t GINTSTS;              /**< \brief ȫ���ж�״̬�Ĵ���*/
        stc_usbfs_gintsts_field_t GINTSTS_f;
    };
    union
    {
        __IO uint32_t GINTMSK;              /**< \brief ȫ���ж����μĴ���*/
        stc_usbfs_gintmsk_field_t GINTMSK_f;
    };
    union
    {
        __IO uint32_t GRXSTSR;              /**< \brief ����״̬���Զ�ȡ�Ĵ���*/
        stc_usbfs_grxstsr_field_t GRXSTSR_f;
    };
    union
    {
        __IO uint32_t GRXSTSP;              /**< \brief ����״̬��ȡ�ͳ�ջ�Ĵ���*/
        stc_usbfs_grxstsp_field_t GRXSTSP_f;
    };
    union
    {
        __IO uint32_t GRXFSIZ;              /**< \brief USBFS����FIFO��С�Ĵ���*/
        stc_usbfs_grxfsiz_field_t GRXFSIZ_f;
    };
    union
    {
        __IO uint32_t HNPTXFSIZ;            /**< \brief USBFS�����������Է���FIFO��С�Ĵ���*/
        stc_usbfs_hnptxfsiz_field_t HNPTXFSIZ_f;
    };
    union
    {
        __IO uint32_t HNPTXSTS;             /**< \brief USBFS�������Է���״̬�Ĵ���*/
        stc_usbfs_hnptxsts_field_t HNPTXSTS_f;
    };
    uint8_t RESERVED10[12];                 /**< \brief ����*/
    __IO uint32_t CID;                      /**< \brief USBFSģ��ID�Ĵ���*/
    uint8_t RESERVED11[192];                /**< \brief ����*/
    union
    {
        __IO uint32_t HPTXFSIZ;             /**< \brief USBFS�����Է���FIFO��С�Ĵ���*/
        stc_usbfs_hptxfsiz_field_t HPTXFSIZ_f;
    };
    union
    {
        __IO uint32_t DIEPTXF1;             /**< \brief USBFS�豸IN�˵�1����FIFO��С�Ĵ���*/
        stc_usbfs_dieptxf_field_t DIEPTXF1_f;
    };
    union
    {
        __IO uint32_t DIEPTXF2;             /**< \brief USBFS�豸IN�˵�2����FIFO��С�Ĵ���*/
        stc_usbfs_dieptxf_field_t DIEPTXF2_f;
    };
    union
    {
        __IO uint32_t DIEPTXF3;             /**< \brief USBFS�豸IN�˵�3����FIFO��С�Ĵ���*/
        stc_usbfs_dieptxf_field_t DIEPTXF3_f;
    };
    union
    {
        __IO uint32_t DIEPTXF4;             /**< \brief USBFS�豸IN�˵�4����FIFO��С�Ĵ���*/
        stc_usbfs_dieptxf_field_t DIEPTXF4_f;
    };
    union
    {
        __IO uint32_t DIEPTXF5;             /**< \brief USBFS�豸IN�˵�5����FIFO��С�Ĵ���*/
        stc_usbfs_dieptxf_field_t DIEPTXF5_f;
    };
    uint8_t RESERVED17[744];                /**< \brief ����*/
    union
    {
        __IO uint32_t HCFG;                 /**< \brief USBFS�������üĴ���*/
        stc_usbfs_hcfg_field_t HCFG_f;
    };
    union
    {
        __IO uint32_t HFIR;                 /**< \brief USBFS����֡ʱ�����Ĵ���*/
        stc_usbfs_hfir_field_t HFIR_f;
    };
    union
    {
        __IO uint32_t HFNUM;                /**< \brief USBFS����֡���/ʣ��ʱ�����Ĵ���*/
        stc_usbfs_hfnum_field_t HFNUM_f;
    };
    uint8_t RESERVED20[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HPTXSTS;              /**< \brief USBFS���������Է���FIFO/����״̬�Ĵ���*/
        stc_usbfs_hptxsts_field_t HPTXSTS_f;
    };
    union
    {
        __IO uint32_t HAINT;                /**< \brief USBFS����ȫ��ͨ���жϼĴ���*/
        stc_usbfs_haint_field_t HAINT_f;
    };
    union
    {
        __IO uint32_t HAINTMSK;             /**< \brief USBFS����ȫ��ͨ���ж����μĴ���*/
        stc_usbfs_haintmsk_field_t HAINTMSK_f;
    };
    uint8_t RESERVED23[36];                 /**< \brief ����*/
    union
    {
        __IO uint32_t HPRT;                 /**< \brief �����˿ڿ��ƺ�״̬�Ĵ���*/
        stc_usbfs_hprt_field_t HPRT_f;
    };
    uint8_t RESERVED24[188];                /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR0;              /**< \brief ����ͨ��0���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR0_f;
    };
    uint8_t RESERVED25[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT0;               /**< \brief ����ͨ��0�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT0_f;
    };
    union
    {
        __IO uint32_t HCINTMSK0;            /**< \brief ����ͨ��0�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK0_f;
    };
    union
    {
        __IO uint32_t HCTSIZ0;              /**< \brief ����ͨ��0�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ0_f;
    };
    __IO uint32_t HCDMA0;                   /**< \brief ����ͨ��0DMA��ַ�Ĵ���*/
    uint8_t RESERVED29[8];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR1;              /**< \brief ����ͨ��1���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR1_f;
    };
    uint8_t RESERVED30[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT1;               /**< \brief ����ͨ��1�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT1_f;
    };
    union
    {
        __IO uint32_t HCINTMSK1;            /**< \brief ����ͨ��1�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK1_f;
    };
    union
    {
        __IO uint32_t HCTSIZ1;              /**< \brief ����ͨ��1�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ1_f;
    };
    __IO uint32_t HCDMA1;                   /**< \brief ����ͨ��1DMA��ַ�Ĵ���*/
    uint8_t RESERVED34[8];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR2;              /**< \brief ����ͨ��2���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR2_f;
    };
    uint8_t RESERVED35[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT2;               /**< \brief ����ͨ��2�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT2_f;
    };
    union
    {
        __IO uint32_t HCINTMSK2;            /**< \brief ����ͨ��2�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK2_f;
    };
    union
    {
        __IO uint32_t HCTSIZ2;              /**< \brief ����ͨ��2�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ2_f;
    };
    __IO uint32_t HCDMA2;                   /**< \brief ����ͨ��2DMA��ַ�Ĵ���*/
    uint8_t RESERVED39[8];
    union
    {
        __IO uint32_t HCCHAR3;              /**< \brief ����ͨ��3���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR3_f;
    };
    uint8_t RESERVED40[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT3;               /**< \brief ����ͨ��3�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT3_f;
    };
    union
    {
        __IO uint32_t HCINTMSK3;            /**< \brief ����ͨ��3�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK3_f;
    };
    union
    {
        __IO uint32_t HCTSIZ3;              /**< \brief ����ͨ��3�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ3_f;
    };
    __IO uint32_t HCDMA3;                   /**< \brief ����ͨ��3DMA��ַ�Ĵ���*/
    uint8_t RESERVED44[8];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR4;              /**< \brief ����ͨ��4���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR4_f;
    };
    uint8_t RESERVED45[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT4;               /**< \brief ����ͨ��4�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT4_f;
    };
    union
    {
        __IO uint32_t HCINTMSK4;            /**< \brief ����ͨ��4�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK4_f;
    };
    union
    {
        __IO uint32_t HCTSIZ4;              /**< \brief ����ͨ��4�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ4_f;
    };
    __IO uint32_t HCDMA4;                   /**< \brief ����ͨ��4DMA��ַ�Ĵ���*/
    uint8_t RESERVED49[8];
    union
    {
        __IO uint32_t HCCHAR5;              /**< \brief ����ͨ��5���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR5_f;
    };
    uint8_t RESERVED50[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT5;               /**< \brief ����ͨ��5�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT5_f;
    };
    union
    {
        __IO uint32_t HCINTMSK5;            /**< \brief ����ͨ��5�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK5_f;
    };
    union
    {
        __IO uint32_t HCTSIZ5;              /**< \brief ����ͨ��5�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ5_f;
    };
    __IO uint32_t HCDMA5;                   /**< \brief ����ͨ��5DMA��ַ�Ĵ���*/
    uint8_t RESERVED54[8];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR6;              /**< \brief ����ͨ��6���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR6_f;
    };
    uint8_t RESERVED55[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT6;               /**< \brief ����ͨ��6�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT6_f;
    };
    union
    {
        __IO uint32_t HCINTMSK6;            /**< \brief ����ͨ��6�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK6_f;
    };
    union
    {
        __IO uint32_t HCTSIZ6;              /**< \brief ����ͨ��6�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ6_f;
    };
    __IO uint32_t HCDMA6;                   /**< \brief ����ͨ��6DMA��ַ�Ĵ���*/
    uint8_t RESERVED59[8];
    union
    {
        __IO uint32_t HCCHAR7;              /**< \brief ����ͨ��7���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR7_f;
    };
    uint8_t RESERVED60[4];
    union
    {
        __IO uint32_t HCINT7;               /**< \brief ����ͨ��7�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT7_f;
    };
    union
    {
        __IO uint32_t HCINTMSK7;            /**< \brief ����ͨ��7�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK7_f;
    };
    union
    {
        __IO uint32_t HCTSIZ7;              /**< \brief ����ͨ��7�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ7_f;
    };
    __IO uint32_t HCDMA7;                   /**< \brief ����ͨ��7DMA��ַ�Ĵ���*/
    uint8_t RESERVED64[8];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR8;              /**< \brief ����ͨ��8���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR8_f;
    };
    uint8_t RESERVED65[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT8;               /**< \brief ����ͨ��8�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT8_f;
    };
    union
    {
        __IO uint32_t HCINTMSK8;            /**< \brief ����ͨ��8�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK8_f;
    };
    union
    {
        __IO uint32_t HCTSIZ8;              /**< \brief ����ͨ��8�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ8_f;
    };
    __IO uint32_t HCDMA8;                   /**< \brief ����ͨ��8DMA��ַ�Ĵ���*/
    uint8_t RESERVED69[8];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR9;              /**< \brief ����ͨ��9���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR9_f;
    };
    uint8_t RESERVED70[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT9;               /**< \brief ����ͨ��9�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT9_f;
    };
    union
    {
        __IO uint32_t HCINTMSK9;            /**< \brief ����ͨ��9�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK9_f;
    };
    union
    {
        __IO uint32_t HCTSIZ9;              /**< \brief ����ͨ��9�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ9_f;
    };
    __IO uint32_t HCDMA9;                   /**< \brief ����ͨ��9DMA��ַ�Ĵ���*/
    uint8_t RESERVED74[8];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR10;             /**< \brief ����ͨ��10���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR10_f;
    };
    uint8_t RESERVED75[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT10;              /**< \brief ����ͨ��10�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT10_f;
    };
    union
    {
        __IO uint32_t HCINTMSK10;           /**< \brief ����ͨ��10�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK10_f;
    };
    union
    {
        __IO uint32_t HCTSIZ10;             /**< \brief ����ͨ��10�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ10_f;
    };
    __IO uint32_t HCDMA10;                  /**< \brief ����ͨ��10DMA��ַ�Ĵ���*/
    uint8_t RESERVED79[8];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCCHAR11;             /**< \brief ����ͨ��11���ԼĴ���*/
        stc_usbfs_hcchar_field_t HCCHAR11_f;
    };
    uint8_t RESERVED80[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t HCINT11;              /**< \brief ����ͨ��11�жϼĴ���*/
        stc_usbfs_hcint_field_t HCINT11_f;
    };
    union
    {
        __IO uint32_t HCINTMSK11;           /**< \brief ����ͨ��11�ж����μĴ���*/
        stc_usbfs_hcintmsk_field_t HCINTMSK11_f;
    };
    union
    {
        __IO uint32_t HCTSIZ11;             /**< \brief ����ͨ��11�����С�Ĵ���*/
        stc_usbfs_hctsiz_field_t HCTSIZ11_f;
    };
    __IO uint32_t HCDMA11;                  /**< \brief ����ͨ��11DMA��ַ�Ĵ���*/
    uint8_t RESERVED84[392];                /**< \brief ����*/
    union
    {
        __IO uint32_t DCFG;                 /**< \brief USBFS�豸���üĴ���*/
        stc_usbfs_dcfg_field_t DCFG_f;
    };
    union
    {
        __IO uint32_t DCTL;                 /**< \brief USBFS�豸���ƼĴ���*/
        stc_usbfs_dctl_field_t DCTL_f;
    };
    union
    {
        __IO uint32_t DSTS;                 /**< \brief USBFS�豸״̬�Ĵ���*/
        stc_usbfs_dsts_field_t DSTS_f;
    };
    uint8_t RESERVED87[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPMSK;              /**< \brief USBFS�豸IN�˵�ͨ���ж����μĴ���*/
        stc_usbfs_diepmsk_field_t DIEPMSK_f;
    };
    union
    {
        __IO uint32_t DOEPMSK;              /**< \brief USBFS�豸OUT�˵�ͨ���ж����μĴ���*/
        stc_usbfs_doepmsk_field_t DOEPMSK_f;
    };
    union
    {
        __IO uint32_t DAINT;                /**< \brief USBFS�豸ȫ��˵��жϼĴ���*/
        stc_usbfs_daint_field_t DAINT_f;
    };
    union
    {
        __IO uint32_t DAINTMSK;             /**< \brief USBFS�豸ȫ��˵��ж����μĴ���*/
        stc_usbfs_daintmsk_field_t DAINTMSK_f;
    };
    uint8_t RESERVED91[20];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPEMPMSK;           /**< \brief USBFS�豸IN�˵�FIFO���ж����μĴ���*/
        stc_usbfs_diepempmsk_field_t DIEPEMPMSK_f;
    };
    uint8_t RESERVED92[200];                /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPCTL0;             /**< \brief USBFS�豸IN�˵�0���ƼĴ���*/
        stc_usbfs_diepctl0_field_t DIEPCTL0_f;
    };
    uint8_t RESERVED93[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPINT0;             /**< \brief USBFS�豸IN�˵�0�жϼĴ���*/
        stc_usbfs_diepint0_field_t DIEPINT0_f;
    };
    uint8_t RESERVED94[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPTSIZ0;            /**< \brief USBFS�豸IN�˵�0�����С�Ĵ���*/
        stc_usbfs_dieptsiz0_field_t DIEPTSIZ0_f;
    };
    __IO uint32_t DIEPDMA0;                 /**< \brief USBFS�豸IN�˵�0DMA��ַ�Ĵ���*/
    union
    {
        __IO uint32_t DTXFSTS0;             /**< \brief USBFS�豸IN�˵�0����FIFO״̬�Ĵ���*/
        stc_usbfs_dtxfsts0_field_t DTXFSTS0_f;
    };
    uint8_t RESERVED97[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPCTL1;             /**< \brief USBFS�豸IN�˵�1���ƼĴ���*/
        stc_usbfs_diepctl_field_t DIEPCTL1_f;
    };
    uint8_t RESERVED98[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPINT1;             /**< \brief USBFS�豸IN�˵�1�жϼĴ���*/
        stc_usbfs_diepint_field_t DIEPINT1_f;
    };
    uint8_t RESERVED99[4];                  /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPTSIZ1;            /**< \brief USBFS�豸IN�˵�1�����С�Ĵ���*/
        stc_usbfs_dieptsiz_field_t DIEPTSIZ1_f;
    };
    __IO uint32_t DIEPDMA1;                 /**< \brief USBFS�豸IN�˵�1DMA��ַ�Ĵ���*/
    union
    {
        __IO uint32_t DTXFSTS1;             /**< \brief USBFS�豸IN�˵�1����FIFO״̬�Ĵ���*/
        stc_usbfs_dtxfsts_field_t DTXFSTS1_f;
    };
    uint8_t RESERVED102[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPCTL2;             /**< \brief USBFS�豸IN�˵�1���ƼĴ���*/
        stc_usbfs_diepctl_field_t DIEPCTL2_f;
    };
    uint8_t RESERVED103[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPINT2;             /**< \brief USBFS�豸IN�˵�2�жϼĴ���*/
        stc_usbfs_diepint_field_t DIEPINT2_f;
    };
    uint8_t RESERVED104[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPTSIZ2;            /**< \brief USBFS�豸IN�˵�2�����С�Ĵ���*/
        stc_usbfs_dieptsiz_field_t DIEPTSIZ2_f;
    };
    __IO uint32_t DIEPDMA2;                 /**< \brief USBFS�豸IN�˵�2DMA��ַ�Ĵ���*/
    union
    {
        __IO uint32_t DTXFSTS2;             /**< \brief USBFS�豸IN�˵�2����FIFO״̬�Ĵ���*/
        stc_usbfs_dtxfsts_field_t DTXFSTS2_f;
    };
    uint8_t RESERVED107[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPCTL3;             /**< \brief USBFS�豸IN�˵�3���ƼĴ���*/
        stc_usbfs_diepctl_field_t DIEPCTL3_f;
    };
    uint8_t RESERVED108[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPINT3;             /**< \brief USBFS�豸IN�˵�3�жϼĴ���*/
        stc_usbfs_diepint_field_t DIEPINT3_f;
    };
    uint8_t RESERVED109[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPTSIZ3;            /**< \brief USBFS�豸IN�˵�3�����С�Ĵ���*/
        stc_usbfs_dieptsiz_field_t DIEPTSIZ3_f;
    };
    __IO uint32_t DIEPDMA3;                 /**< \brief USBFS�豸IN�˵�3DMA��ַ�Ĵ���*/
    union
    {
        __IO uint32_t DTXFSTS3;             /**< \brief USBFS�豸IN�˵�3����FIFO״̬�Ĵ���*/
        stc_usbfs_dtxfsts_field_t DTXFSTS3_f;
    };
    uint8_t RESERVED112[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPCTL4;             /**< \brief USBFS�豸IN�˵�4���ƼĴ���*/
        stc_usbfs_diepctl_field_t DIEPCTL4_f;
    };
    uint8_t RESERVED113[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPINT4;             /**< \brief USBFS�豸IN�˵�4�жϼĴ���*/
        stc_usbfs_diepint_field_t DIEPINT4_f;
    };
    uint8_t RESERVED114[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPTSIZ4;            /**< \brief USBFS�豸IN�˵�4�����С�Ĵ���*/
        stc_usbfs_dieptsiz_field_t DIEPTSIZ4_f;
    };
    __IO uint32_t DIEPDMA4;                 /**< \brief USBFS�豸IN�˵�4DMA��ַ�Ĵ���*/
    union
    {
        __IO uint32_t DTXFSTS4;             /**< \brief USBFS�豸IN�˵�4����FIFO״̬�Ĵ���*/
        stc_usbfs_dtxfsts_field_t DTXFSTS4_f;
    };
    uint8_t RESERVED117[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPCTL5;             /**< \brief USBFS�豸IN�˵�5���ƼĴ���*/
        stc_usbfs_diepctl_field_t DIEPCTL5_f;
    };
    uint8_t RESERVED118[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPINT5;             /**< \brief USBFS�豸IN�˵�5�жϼĴ���*/
        stc_usbfs_diepint_field_t DIEPINT5_f;
    };
    uint8_t RESERVED119[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DIEPTSIZ5;            /**< \brief USBFS�豸IN�˵�5�����С�Ĵ���*/
        stc_usbfs_dieptsiz_field_t DIEPTSIZ5_f;
    };
    __IO uint32_t DIEPDMA5;                 /**< \brief USBFS�豸IN�˵�5DMA��ַ�Ĵ���*/
    union
    {
        __IO uint32_t DTXFSTS5;             /**< \brief USBFS�豸IN�˵�5����FIFO״̬�Ĵ���*/
        stc_usbfs_dtxfsts_field_t DTXFSTS5_f;
    };
    uint8_t RESERVED122[324];               /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPCTL0;             /**< \brief �豸OUT�˵�0���ƼĴ���*/
        stc_usbfs_doepctl0_field_t DOEPCTL0_f;
    };
    uint8_t RESERVED123[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPINT0;             /**< \brief �豸OUT�˵�0�жϼĴ���*/
        stc_usbfs_doepint_field_t DOEPINT0_f;
    };
    uint8_t RESERVED124[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPTSIZ0;            /**< \brief �豸OUT�˵�0�����С�Ĵ���*/
        stc_usbfs_doeptsiz0_field_t DOEPTSIZ0_f;
    };
    __IO uint32_t DOEPDMA0;                 /**< \brief �豸OUT�˵�0DMA��ַ�Ĵ���*/
    uint8_t RESERVED126[8];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPCTL1;             /**< \brief �豸OUT�˵�1���ƼĴ���*/
        stc_usbfs_doepctl_field_t DOEPCTL1_f;
    };
    uint8_t RESERVED127[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPINT1;             /**< \brief �豸OUT�˵�1�жϼĴ���*/
        stc_usbfs_doepint_field_t DOEPINT1_f;
    };
    uint8_t RESERVED128[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPTSIZ1;            /**< \brief �豸OUT�˵�1�����С�Ĵ���*/
        stc_usbfs_doeptsiz_field_t DOEPTSIZ1_f;
    };
    __IO uint32_t DOEPDMA1;                 /**< \brief �豸OUT�˵�1DMA��ַ�Ĵ���*/
    uint8_t RESERVED130[8];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPCTL2;             /**< \brief �豸OUT�˵�2���ƼĴ���*/
        stc_usbfs_doepctl_field_t DOEPCTL2_f;
    };
    uint8_t RESERVED131[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPINT2;             /**< \brief �豸OUT�˵�2�жϼĴ���*/
        stc_usbfs_doepint_field_t DOEPINT2_f;
    };
    uint8_t RESERVED132[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPTSIZ2;            /**< \brief �豸OUT�˵�2�����С�Ĵ���*/
        stc_usbfs_doeptsiz_field_t DOEPTSIZ2_f;
    };
    __IO uint32_t DOEPDMA2;                 /**< \brief �豸OUT�˵�2DMA��ַ�Ĵ���*/
    uint8_t RESERVED134[8];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPCTL3;             /**< \brief �豸OUT�˵�2���ƼĴ���*/
        stc_usbfs_doepctl_field_t DOEPCTL3_f;
    };
    uint8_t RESERVED135[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPINT3;             /**< \brief �豸OUT�˵�3�жϼĴ���*/
        stc_usbfs_doepint_field_t DOEPINT3_f;
    };
    uint8_t RESERVED136[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPTSIZ3;            /**< \brief �豸OUT�˵�3�����С�Ĵ���*/
        stc_usbfs_doeptsiz_field_t DOEPTSIZ3_f;
    };
    __IO uint32_t DOEPDMA3;                 /**< \brief �豸OUT�˵�3DMA��ַ�Ĵ���*/
    uint8_t RESERVED138[8];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPCTL4;             /**< \brief �豸OUT�˵�2���ƼĴ���*/
        stc_usbfs_doepctl_field_t DOEPCTL4_f;
    };
    uint8_t RESERVED139[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPINT4;             /**< \brief �豸OUT�˵�4�жϼĴ���*/
        stc_usbfs_doepint_field_t DOEPINT4_f;
    };
    uint8_t RESERVED140[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPTSIZ4;            /**< \brief �豸OUT�˵�4�����С�Ĵ���*/
        stc_usbfs_doeptsiz_field_t DOEPTSIZ4_f;
    };
    __IO uint32_t DOEPDMA4;                 /**< \brief �豸OUT�˵�4DMA��ַ�Ĵ���*/
    uint8_t RESERVED142[8];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPCTL5;             /**< \brief �豸OUT�˵�2���ƼĴ���*/
        stc_usbfs_doepctl_field_t DOEPCTL5_f;
    };
    uint8_t RESERVED143[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPINT5;             /**< \brief �豸OUT�˵�5�жϼĴ���*/
        stc_usbfs_doepint_field_t DOEPINT5_f;
    };
    uint8_t RESERVED144[4];                 /**< \brief ����*/
    union
    {
        __IO uint32_t DOEPTSIZ5;            /**< \brief �豸OUT�˵�5�����С�Ĵ���*/
        stc_usbfs_doeptsiz_field_t DOEPTSIZ5_f;
    };
    __IO uint32_t DOEPDMA5;                 /**< \brief �豸OUT�˵�5DMA��ַ�Ĵ���*/
    uint8_t RESERVED146[584];               /**< \brief ����*/
    union
    {
        __IO uint32_t PCGCCTL;              /**< \brief USBFS��Դ���ſ�ʱ�ӿ��Ƽ�����*/
        stc_usbfs_pcgcctl_field_t PCGCCTL_f;
    };
} amhw_hc32f460_usbd_t;


/**
 * \brief ʹ������������ν���
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

/* ��������������ʹ�� */
#elif defined(__GNUC__)

/* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

/* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif
/** @} */

/**
 * @}if_HC32F460_USBd
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_USBD_H */

/* end of file */

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
 * \brief OPA �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 19-10-10
 * \endinternal
 */

#ifndef __AMHW_HC32_OPA_H
#define __AMHW_HC32_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_hc32f07x_if_opa
 * \copydoc amhw_hc32f07x_opa.h
 * @{
 */

/**
 * \brief OPA - �Ĵ�����
 */
typedef struct amhw_hc32f27x_opa {
         uint32_t  res1[12];     /**< \brief  ���� */
    __IO uint32_t  opacr0;       /**< \brief  OPA ���üĴ���0 */
    __IO uint32_t  opacr1;       /**< \brief  OPA ���üĴ���1 */
	  __IO uint32_t  opacr2;       /**< \brief  OPA ���üĴ���2 */
	  __IO uint32_t  opacr;        /**< \brief  OPA ���ƼĴ��� */ 
} amhw_hc32f07x_opa_t;

/**
 * \brief OPA ���ñ��
 */
#define  AMHW_HC32F07X_OP0   0
#define  AMHW_HC32F07X_OP1   1
#define  AMHW_HC32F07X_OP2   2
#define  AMHW_HC32F07X_OP3   3
#define  AMHW_HC32F07X_OP4   4

/**
 * \brief OPA ���ʹ������
 */
#define  AMHW_HC32F07X_OPA0_2_OEN0   (0U << 0U)
#define  AMHW_HC32F07X_OPA0_2_OEN1   (1U << 0U)
#define  AMHW_HC32F07X_OPA0_2_OEN2   (1U << 1U)
#define  AMHW_HC32F07X_OPA0_2_OEN3   (1U << 2U)
#define  AMHW_HC32F07X_OPA0_2_OEN4   (1U << 3U)
#define  AMHW_HC32F07X_OPA3_4_OEN    (0)

/**
 * \brief OPA0 ���ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in] flag     : ���xʹ�����룬�ο��궨�壺OPA ���ʹ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa0_out_en (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr0 |= flag;
}

/**
 * \brief OPA1 ���ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in] flag     : ���xʹ�����룬�ο��궨�壺OPA ���ʹ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa1_out_en (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr0 |= (flag << 4);
}

/**
 * \brief OPA2 ���ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in] flag     : ���xʹ�����룬�ο��궨�壺OPA ���ʹ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa2_out_en (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr0 |= (flag<<8);
}




/**
 * \brief OPA �����������
 */
#define  AMHW_HC32F07X_OPA_ODIS1   ~(1U << 0U)
#define  AMHW_HC32F07X_OPA_ODIS2   ~(1U << 1U)
#define  AMHW_HC32F07X_OPA_ODIS3   ~(1U << 2U)
#define  AMHW_HC32F07X_OPA_ODIS4   ~(1U << 3U)

/**
 * \brief OPA �������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in] flag     : ���x�������룬�ο��궨�壺OPA �����������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa0_out_dis (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr0 &= flag;
}

/**
 * \brief OPA �������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in] flag     : ���x�������룬�ο��궨�壺OPA �����������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa1_out_dis (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr0 &= (flag << 4);
}

/**
 * \brief OPA �������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in] flag     : ���x�������룬�ο��궨�壺OPA �����������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa2_out_dis (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr0 &= (flag << 8);
}

/**
 * \brief OPA DACʹ��OP3��λ���ӻ���ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \note : ��OPAʹ�ܲ���ͬʱʹ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa3buf_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 10);
    p_hw_opa->opacr1 &= ~(1 << 8);
}

/**
 * \brief OPA DACʹ��OP4��λ���ӻ���ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \note : ��OPAʹ�ܲ���ͬʱʹ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa4buf_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 11);
    p_hw_opa->opacr1 &= ~(1 << 9);
}

/**
 * \brief OPA DACʹ��OP3��λ���ӻ������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa3buf_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr0 &= ~(1 << 10);
}

/**
 * \brief OPA DACʹ��OP4��λ���ӻ������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa4buf_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr0 &= ~(1 << 11);
}

/**
 * \brief OPA0 �Զ�У��ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa0_az_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 0);
}

/**
 * \brief OPA1 �Զ�У��ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa1_az_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 1);
}

/**
 * \brief OPA2 �Զ�У��ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa2_az_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 2);
}

/**
 * \brief OPA3 �Զ�У��ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa3_az_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 3);
}

/**
 * \brief OPA4 �Զ�У��ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa4_az_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 4);
}

/**
 * \brief OPA1 �Զ�У�����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa0_az_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 0);
}

/**
 * \brief OPA0 �Զ�У�����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa1_az_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 1);
}

/**
 * \brief OPA2 �Զ�У�����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa2_az_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 2);
}

/**
 * \brief OPA3 �Զ�У�����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa3_az_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 3);
}

/**
 * \brief OPA4 �Զ�У�����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa4_az_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 4);
}

/**
 * \brief OPA0 ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \note : ��OPABUFʹ�ܲ���ͬʱʹ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa0_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 5);
}

/**
 * \brief OPA1 ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \note : ��OPABUFʹ�ܲ���ͬʱʹ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa1_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 6);
}

/**
 * \brief OPA2 ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \note : ��OPABUFʹ�ܲ���ͬʱʹ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa2_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 7);
}

/**
 * \brief OPA3 ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \note : ��OPABUFʹ�ܲ���ͬʱʹ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa3_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 8);
    p_hw_opa->opacr1 &= ~(1 << 10);
}

/**
 * \brief OPA4 ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \note : ��OPABUFʹ�ܲ���ͬʱʹ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa4_en (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 |= (1 << 9);
    p_hw_opa->opacr1 &= ~(1 << 11);
}

/**
 * \brief OPA0 ����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa0_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 5);
}

/**
 * \brief OPA1 ����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa1_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 6);
}

/**
 * \brief OPA2 ����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa2_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 7);
}

/**
 * \brief OPA3 ����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa3_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 8);
}

/**
 * \brief OPA4 ����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa4_dis (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 9);
}

/**
 * \brief �Զ�У׼����������
 */
typedef enum amhw_hc32f07x_opa_clk_sel {
    AMHW_HC32F07X_OPA_CLK_1 = 0,
    AMHW_HC32F07X_OPA_CLK_2,
    AMHW_HC32F07X_OPA_CLK_4,
    AMHW_HC32F07X_OPA_CLK_8,
    AMHW_HC32F07X_OPA_CLK_16,
    AMHW_HC32F07X_OPA_CLK_32,
    AMHW_HC32F07X_OPA_CLK_64,
    AMHW_HC32F07X_OPA_CLK_128,
    AMHW_HC32F07X_OPA_CLK_256,
    AMHW_HC32F07X_OPA_CLK_512,
    AMHW_HC32F07X_OPA_CLK_1024,
    AMHW_HC32F07X_OPA_CLK_2048,
    AMHW_HC32F07X_OPA_CLK_4096,
}amhw_hc32f07x_opa_clk_sel_t;

/**
 * \brief OPA �Զ�У׼����������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in]  flag    : У׼ʱ�����ڣ��ο�ö�ٶ��壺�Զ�У׼����������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa_clk_sel (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr = (p_hw_opa->opacr & (~(0xf << 4))) | (flag << 4);
}

/**
 * \brief OPA �Զ�У��ѡ������
 */
#define  AMHW_HC32F07X_OPA_AZ_SW      1U /**< \brief ���У׼ */
#define  AMHW_HC32F07X_OPA_AZ_SW_TRI  2U /**< \brief �������У׼ */
#define  AMHW_HC32F07X_OPA_AZ_ADC     3U /**< \brief ADC����У׼ */

/**
 * \brief OPA �Զ�У��ѡ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in]  flag    : �Զ�У�㷽ʽ���ο��궨�壺OPA �Զ�У��ѡ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_opa_az_way_sel (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    if (flag == AMHW_HC32F07X_OPA_AZ_ADC){
        p_hw_opa->opacr |= (1 << 0);
    }else if (flag == AMHW_HC32F07X_OPA_AZ_SW){
        p_hw_opa->opacr |= (1 << 3);
    }else {
        p_hw_opa->opacr &= ~(1 << 3);
    }
}

/**
 * \brief OPA У׼��������
 */
#define AMHW_HC32F07X_AZ_SW_START        (1U << 2U)  /**< \brief ���У׼���� */
#define AMHW_HC32F07X_AZ_SW_TRI_START    (1U << 1U)  /**< \brief �������У׼���� */

/**
 * \brief OPA ������������У׼����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in]  flag    : �Զ�У�㷽ʽ���ο��궨�壺OPA У׼��������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_az_start (amhw_hc32f07x_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr |= flag;
}

/**
 * \brief OPA �������У׼ֹͣ
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f07x_az_stop (amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr &= ~(1 << 1);
}

/**
 * \brief OPA ADC��������OPA�Զ�У׼ֹͣ
 * 
 * \param[in] p_hw_opa :ָ��OPA�Ĵ��������ַָ��
 *
* \retval : ��
 */

am_static_inline
void amhw_hc32f07x_az_sw_adc_stop(amhw_hc32f07x_opa_t *p_hw_opa)
{
    p_hw_opa->opacr &= ~(1 << 0);
}


/**
 * @} amhw_if_hc32f07x_opa
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F07X_OPA_H */

/* end of file */

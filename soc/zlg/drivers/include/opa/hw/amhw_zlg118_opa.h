/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief OPA �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 19-10-10
 * \endinternal
 */

#ifndef __AMHW_ZLG118_OPA_H
#define __AMHW_ZLG118_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zlg118_if_opa
 * \copydoc amhw_zlg118_opa.h
 * @{
 */

/**
 * \brief OPA - �Ĵ�����
 */
typedef struct amhw_zlg118_opa {
         uint32_t  res1[12];     /**< \brief  ���� */
    __IO uint32_t  opacr0;       /**< \brief  OPA ���üĴ���0 */
         uint32_t  res2[2];      /**< \brief  ���� */
    __IO uint32_t  opacr1;       /**< \brief  OPA ���üĴ���1 */
} amhw_zlg118_opa_t;

/**
 * \brief OPA ���ʹ������
 */
#define  AMHW_ZLG118_OPA_OEN1   (1U << 3U)
#define  AMHW_ZLG118_OPA_OEN2   (1U << 4U)
#define  AMHW_ZLG118_OPA_OEN3   (1U << 5U)
#define  AMHW_ZLG118_OPA_OEN4   (1U << 6U)

/**
 * \brief OPA ���ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in] flag     : ���xʹ�����룬�ο��궨�壺OPA ���ʹ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opa_out_en (amhw_zlg118_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr0 |= flag;
}

/**
 * \brief OPA �����������
 */
#define  AMHW_ZLG118_OPA_ODIS1   ~(1U << 3U)
#define  AMHW_ZLG118_OPA_ODIS2   ~(1U << 4U)
#define  AMHW_ZLG118_OPA_ODIS3   ~(1U << 5U)
#define  AMHW_ZLG118_OPA_ODIS4   ~(1U << 6U)

/**
 * \brief OPA �������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in] flag     : ���x�������룬�ο��궨�壺OPA �����������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opa_out_dis (amhw_zlg118_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr0 &= flag;
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
void amhw_zlg118_opabuf_en (amhw_zlg118_opa_t *p_hw_opa)
{
    p_hw_opa->opacr0 |= (1 << 2);
    p_hw_opa->opacr0 &= ~(1 << 0);
}

/**
 * \brief OPA DACʹ��OP3��λ���ӻ������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opabuf_dis (amhw_zlg118_opa_t *p_hw_opa)
{
    p_hw_opa->opacr0 &= ~(1 << 2);
}

/**
 * \brief OPA �Զ�У��ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opa_az_en (amhw_zlg118_opa_t *p_hw_opa)
{
    p_hw_opa->opacr0 |= (1 << 1);
}

/**
 * \brief OPA �Զ�У�����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opa_az_dis (amhw_zlg118_opa_t *p_hw_opa)
{
    p_hw_opa->opacr0 &= ~(1 << 1);
}

/**
 * \brief OPA ʹ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \note : ��OPABUFʹ�ܲ���ͬʱʹ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opa_en (amhw_zlg118_opa_t *p_hw_opa)
{
    p_hw_opa->opacr0 |= (1 << 0);
    p_hw_opa->opacr0 &= ~(1 << 2);
}

/**
 * \brief OPA ����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opa_dis (amhw_zlg118_opa_t *p_hw_opa)
{
    p_hw_opa->opacr0 &= ~(1 << 0);
}

/**
 * \brief �Զ�У׼����������
 */
typedef enum amhw_zlg118_opa_clk_sel {
    AMHW_ZLG118_OPA_CLK_1 = 0,
    AMHW_ZLG118_OPA_CLK_2,
    AMHW_ZLG118_OPA_CLK_4,
    AMHW_ZLG118_OPA_CLK_8,
    AMHW_ZLG118_OPA_CLK_16,
    AMHW_ZLG118_OPA_CLK_32,
    AMHW_ZLG118_OPA_CLK_64,
    AMHW_ZLG118_OPA_CLK_128,
    AMHW_ZLG118_OPA_CLK_256,
    AMHW_ZLG118_OPA_CLK_512,
    AMHW_ZLG118_OPA_CLK_1024,
    AMHW_ZLG118_OPA_CLK_2048,
    AMHW_ZLG118_OPA_CLK_4096,
}amhw_zlg118_opa_clk_sel_t;

/**
 * \brief OPA �Զ�У׼����������
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in]  flag    : У׼ʱ�����ڣ��ο�ö�ٶ��壺�Զ�У׼����������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opa_clk_sel (amhw_zlg118_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr1 = (p_hw_opa->opacr1 & (~(0xf << 4))) | (flag << 4);
}

/**
 * \brief OPA �Զ�У��ѡ������
 */
#define  AMHW_ZLG118_OPA_AZ_SW      1U /**< \brief ���У׼ */
#define  AMHW_ZLG118_OPA_AZ_SW_TRI  2U /**< \brief �������У׼ */
#define  AMHW_ZLG118_OPA_AZ_ADC     3U /**< \brief ADC����У׼ */

/**
 * \brief OPA �Զ�У��ѡ��
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in]  flag    : �Զ�У�㷽ʽ���ο��궨�壺OPA �Զ�У��ѡ������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_opa_az_way_sel (amhw_zlg118_opa_t *p_hw_opa, uint32_t flag)
{
    if (flag == AMHW_ZLG118_OPA_AZ_ADC){
        p_hw_opa->opacr1 |= (1 << 0);
    }else if (flag == AMHW_ZLG118_OPA_AZ_SW){
        p_hw_opa->opacr1 |= (1 << 3);
    }else {
        p_hw_opa->opacr1 &= ~(1 << 3);
    }
}

/**
 * \brief OPA У׼��������
 */
#define AMHW_ZLG118_AZ_SW_START        (1U << 2U)  /**< \brief ���У׼���� */
#define AMHW_ZLG118_AZ_SW_TRI_START    (1U << 1U)  /**< \brief �������У׼���� */

/**
 * \brief OPA ������������У׼����
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 * \param[in]  flag    : �Զ�У�㷽ʽ���ο��궨�壺OPA У׼��������
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_az_start (amhw_zlg118_opa_t *p_hw_opa, uint32_t flag)
{
    p_hw_opa->opacr1 |= flag;
}

/**
 * \brief OPA �������У׼ֹͣ
 *
 * \param[in] p_hw_opa : ָ��OPA�Ĵ��������ַָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zlg118_az_stop (amhw_zlg118_opa_t *p_hw_opa)
{
    p_hw_opa->opacr1 &= ~(1 << 1);
}


/**
 * @} amhw_if_zlg118_opa
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG118_OPA_H */

/* end of file */

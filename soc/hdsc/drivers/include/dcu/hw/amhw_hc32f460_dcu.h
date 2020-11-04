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
 * \brief DCU �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 20-05-26
 * \endinternal
 */

#ifndef __AMHW_HC32F460_DCU_H
#define __AMHW_HC32F460_DCU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_hc32f460_if_dcu
 * \copydoc amhw_hc32f460_dcu.h
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
 * \brief DCU���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t MODE                      : 3;  /** <brief ����ģʽ */
    __IO uint32_t DATASIZE                  : 2;  /** <brief ���ݴ�С */
    uint32_t RESERVED5                      : 3;  /** <brief ���� */
    __IO uint32_t COMP_TRG                  : 1;  /** <brief �Ƚ�ģʽ�����Ƚϵ�ʱ�� */
    uint32_t RESERVED9                      :22;  /** <brief ���� */
    __IO uint32_t INTEN                     : 1;  /** <brief �ж�ʹ�� */
} stc_dcu_ctl_field_t;

/**
 * \brief DCU��־�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t FLAG_OP                   : 1;  /** <brief �����־λ */
    __IO uint32_t FLAG_LS2                  : 1;  /** <brief С�ڱ�־λ2 */
    __IO uint32_t FLAG_EQ2                  : 1;  /** <brief ���ڱ�־λ2 */
    __IO uint32_t FLAG_GT2                  : 1;  /** <brief ���ڱ�־λ2 */
    __IO uint32_t FLAG_LS1                  : 1;  /** <brief С�ڱ�־λ1 */
    __IO uint32_t FLAG_EQ1                  : 1;  /** <brief ���ڱ�־λ1 */
    __IO uint32_t FLAG_GT1                  : 1;  /** <brief ���ڱ�־λ1 */
    uint32_t RESERVED7                      :25;  /** <brief ���� */
} stc_dcu_flag_field_t;

/**
 * \brief DCU��־��λ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t CLR_OP                    : 1;  /** <brief ��������־λ */
    __IO uint32_t CLR_LS2                   : 1;  /** <brief ���С�ڱ�־λ2 */
    __IO uint32_t CLR_EQ2                   : 1;  /** <brief ������ڱ�־λ2 */
    __IO uint32_t CLR_GT2                   : 1;  /** <brief ������ڱ�־λ2 */
    __IO uint32_t CLR_LS1                   : 1;  /** <brief ���С�ڱ�־λ1 */
    __IO uint32_t CLR_EQ1                   : 1;  /** <brief ������ڱ�־λ1 */
    __IO uint32_t CLR_GT1                   : 1;  /** <brief ������ڱ�־λ1 */
    uint32_t RESERVED7                      :25;  /** <brief ���� */
} stc_dcu_flagclr_field_t;

/**
 * \brief DCU��־��λ�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t INT_OP                    : 1;  /** <brief �����־λ */
    __IO uint32_t INT_LS2                   : 1;  /** <brief С���ж�����ѡ��2 */
    __IO uint32_t INT_EQ2                   : 1;  /** <brief �����ж�����ѡ��2 */
    __IO uint32_t INT_GT2                   : 1;  /** <brief �����ж�����ѡ��2 */
    __IO uint32_t INT_LS1                   : 1;  /** <brief С���ж�����ѡ��1 */
    __IO uint32_t INT_EQ1                   : 1;  /** <brief �����ж�����ѡ��1 */
    __IO uint32_t INT_GT1                   : 1;  /** <brief �����ж�����ѡ��1 */
    __IO uint32_t INT_WIN                   : 2;  /** <brief ���ڱȽ��ж�����ѡ�� */
    uint32_t RESERVED9                      :23;  /** <brief ���� */
} stc_dcu_intsel_field_t;

/**
 * \brief DCU - �Ĵ�����
 */
typedef struct amhw_hc32f460_dcu {
    union
    {
        __IO uint32_t CTL;          /**< \brief DCU0���ƼĴ��� */
        stc_dcu_ctl_field_t CTL_f;  /**< \brief DCU0��־�Ĵ��� */
    };
    union
    {
        __IO uint32_t FLAG;         /**< \brief DCU0��־�Ĵ��� */
        stc_dcu_flag_field_t FLAG_f;
    };
    __IO uint32_t DATA0;            /**< \brief DCU0���ݼĴ���0 */
    __IO uint32_t DATA1;            /**< \brief DCU0���ݼĴ���1 */
    __IO uint32_t DATA2;            /**< \brief DCU0���ݼĴ���2 */
    union
    {
        __IO uint32_t FLAGCLR;      /**< \brief DCU0��־��λ�Ĵ��� */
        stc_dcu_flagclr_field_t FLAGCLR_f;
    };
    union
    {
        __IO uint32_t INTSEL;       /**< \brief DCU0�ж�����ѡ��Ĵ��� */
        stc_dcu_intsel_field_t INTSEL_f;
    };
} amhw_hc32f460_dcu_t;


/**
 * \brief DCU ʹ���ж�
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_int_enable (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    p_hw_dcu->CTL_f.INTEN = 1;
}

/**
 * \brief DCU �����ж�
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_int_disable (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    p_hw_dcu->CTL_f.INTEN = 0;
}

/**
 * \brief DCU �Ƚ�ģʽ�����Ƚϵ�ʱ��
 */
typedef enum {
    AMHW_HC32F460_DCU_COMPTRG_BY_DATA0   = 0,  /**< \brief д��data0�󴥷��Ƚ� */
    AMHW_HC32F460_DCU_COMPTRG_BY_DATA012 = 1   /**< \brief д��data0/data1/data2�󴥷��Ƚ� */
} amhw_hc32f460_dcu_comptrg_t;

/**
 * \brief DCU ���ñȽ�ģʽ������ʱ��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] flag     : �Ƚ�ģʽ�����Ƚϵ�ʱ����amhw_hc32f460_dcu_comptrg_t��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_comptrg_set (amhw_hc32f460_dcu_t *p_hw_dcu, amhw_hc32f460_dcu_comptrg_t flag)
{
    p_hw_dcu->CTL_f.COMP_TRG = flag;
}


/**
 * \brief DCU ���ݴ�С
 */
typedef enum {
    AMHW_HC32F460_DCU_DATASIZE_8BIT  = 0,  /**< \brief 8bit */
    AMHW_HC32F460_DCU_DATASIZE_16BIT = 1,  /**< \brief 16bit */
    AMHW_HC32F460_DCU_DATASIZE_32BIT = 2   /**< \brief 32bit */
} amhw_hc32f460_dcu_datasize_t;

/**
 * \brief DCU �������ݴ�С
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] datasize : ���ݴ�С��־��amhw_hc32f460_dcu_datasize_t��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_datasize_set (amhw_hc32f460_dcu_t         *p_hw_dcu,
                                     amhw_hc32f460_dcu_datasize_t datasize)
{
    p_hw_dcu->CTL_f.DATASIZE = datasize;
}


/**
 * \brief DCU ����ģʽ
 */
typedef enum {
    AMHW_HC32F460_DCU_OPERATION_MODE_INVALID   = 0,  /**< \brief DCU��Ч */
    AMHW_HC32F460_DCU_OPERATION_MODE_ADD       = 1,  /**< \brief �ӷ�ģʽ */
    AMHW_HC32F460_DCU_OPERATION_MODE_SUB       = 2,  /**< \brief ����ģʽ */
    AMHW_HC32F460_DCU_OPERATION_MODE_HWTRG_ADD = 3,  /**< \brief Ӳ�������ӷ�ģʽ */
    AMHW_HC32F460_DCU_OPERATION_MODE_HWTRG_SUB = 4,  /**< \brief Ӳ����������ģʽ */
    AMHW_HC32F460_DCU_OPERATION_MODE_COMP      = 5   /**< \brief �Ƚ�ģʽ */
} amhw_hc32f460_dcu_operation_mode_t;


/**
 * \brief DCU ����ģʽ����
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] mode     : DCU����ģʽ��amhw_hc32f460_dcu_operation_mode_t��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_mode_set (amhw_hc32f460_dcu_t *p_hw_dcu, amhw_hc32f460_dcu_operation_mode_t mode)
{
    p_hw_dcu->CTL_f.MODE = mode;
}

/**
 * \brief DCU �����־
 */
typedef enum {
    AMHW_HC32F460_DCU_RESULT_FLAG_OP   = 1 << 0,  /**< \brief ������� */
    AMHW_HC32F460_DCU_RESULT_FLAG_lS2  = 1 << 1,  /**< \brief DATA0 < DATA2 */
    AMHW_HC32F460_DCU_RESULT_FLAG_EQ2  = 1 << 2,  /**< \brief DATA0 = DATA2 */
    AMHW_HC32F460_DCU_RESULT_FLAG_GT2  = 1 << 3,  /**< \brief DATA0 > DATA2 */
    AMHW_HC32F460_DCU_RESULT_FLAG_LS1  = 1 << 4,  /**< \brief DATA0 < DATA1 */
    AMHW_HC32F460_DCU_RESULT_FLAG_EQ1  = 1 << 5,  /**< \brief DATA0 = DATA1 */
    AMHW_HC32F460_DCU_RESULT_FLAG_GT1  = 1 << 6,  /**< \brief DATA0 > DATA1 */
} amhw_hc32f460_dcu_result_flag_t;

/**
 * \brief DCU ��־λ���
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] flag     : DCU��־��amhw_hc32f460_dcu_result_flag_t��
 *
 * \retval : ��
 */
am_static_inline
am_bool_t amhw_hc32f460_dcu_result_flag_check (amhw_hc32f460_dcu_t            *p_hw_dcu,
                                               amhw_hc32f460_dcu_result_flag_t flag)
{
    return (p_hw_dcu->FLAG & flag) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief DCU ��־��ȡ
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��־�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_hc32f460_dcu_result_flag_get (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->FLAG;
}

/**
 * \brief DCU ��־λ���
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] flag     : DCU��־��amhw_hc32f460_dcu_result_flag_t��
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_result_flag_clr (amhw_hc32f460_dcu_t *p_hw_dcu, uint32_t flag)
{
    p_hw_dcu->FLAGCLR = flag;
}

/**
 * \brief DCU д���ݼĴ���data0��8bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data0_write_8bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint8_t data)
{
    p_hw_dcu->DATA0 = data;
}

/**
 * \brief DCU д���ݼĴ���data0��16bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data0_write_16bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint16_t data)
{
    p_hw_dcu->DATA0 = data;
}

/**
 * \brief DCU д���ݼĴ���data0��32bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data0_write_32bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint32_t data)
{
    p_hw_dcu->DATA0 = data;
}

/**
 * \brief DCU д���ݼĴ���data1��8bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data1_write_8bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint8_t data)
{
    p_hw_dcu->DATA1 = data;
}

/**
 * \brief DCU д���ݼĴ���data1��16bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data1_write_16bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint16_t data)
{
    p_hw_dcu->DATA1 = data;
}

/**
 * \brief DCU д���ݼĴ���data1��32bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data1_write_32bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint32_t data)
{
    p_hw_dcu->DATA1 = data;
}

/**
 * \brief DCU д���ݼĴ���data2��8bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data2_write_8bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint8_t data)
{
    p_hw_dcu->DATA2 = data;
}

/**
 * \brief DCU д���ݼĴ���data2��16bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data2_write_16bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint16_t data)
{
    p_hw_dcu->DATA2 = data;
}

/**
 * \brief DCU д���ݼĴ���data2��32bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 * \param[in] data     : Ҫд�������
 *
 * \retval : ��
 */
am_static_inline
void amhw_hc32f460_dcu_data2_write_32bit (amhw_hc32f460_dcu_t *p_hw_dcu, uint32_t data)
{
    p_hw_dcu->DATA2 = data;
}


/**
 * \brief DCU ��ȡ���ݼĴ���data0��8bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint8_t amhw_hc32f460_dcu_data0_read_8bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA0;
}

/**
 * \brief DCU д���ݼĴ���data0��16bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint16_t amhw_hc32f460_dcu_data0_read_16bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA0;
}

/**
 * \brief DCU д���ݼĴ���data0��32bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint32_t amhw_hc32f460_dcu_data0_read_32bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA0;
}

/**
 * \brief DCU ��ȡ���ݼĴ���data1��8bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint8_t amhw_hc32f460_dcu_data1_read_8bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA1;
}

/**
 * \brief DCU д���ݼĴ���data1��16bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint16_t amhw_hc32f460_dcu_data1_read_16bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA1;
}

/**
 * \brief DCU д���ݼĴ���data1��32bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint32_t amhw_hc32f460_dcu_data1_read_32bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA1;
}

/**
 * \brief DCU ��ȡ���ݼĴ���data2��8bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint8_t amhw_hc32f460_dcu_data2_read_8bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA2;
}

/**
 * \brief DCU д���ݼĴ���data2��16bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint16_t amhw_hc32f460_dcu_data2_read_16bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA2;
}

/**
 * \brief DCU д���ݼĴ���data2��32bit��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
uint32_t amhw_hc32f460_dcu_data2_read_32bit (amhw_hc32f460_dcu_t *p_hw_dcu)
{
    return p_hw_dcu->DATA2;
}

/**
 * \brief DCU �ж�����
 */
typedef enum {
    AMHW_HC32F460_DCU_INT_OP          = 1 << 0,  /**< \brief ������� */
    AMHW_HC32F460_DCU_INT_lS2         = 1 << 1,  /**< \brief �Ƚ�ģʽ�£��Ҵ����жϽ���ʱ��DATA0 < DATA2 */
    AMHW_HC32F460_DCU_INT_EQ2         = 1 << 2,  /**< \brief �Ƚ�ģʽ�£��Ҵ����жϽ���ʱ��DATA0 = DATA2 */
    AMHW_HC32F460_DCU_INT_GT2         = 1 << 3,  /**< \brief �Ƚ�ģʽ�£��Ҵ����жϽ���ʱ��DATA0 > DATA2 */
    AMHW_HC32F460_DCU_INT_LS1         = 1 << 4,  /**< \brief �Ƚ�ģʽ�£��Ҵ����жϽ���ʱ��DATA0 < DATA1 */
    AMHW_HC32F460_DCU_INT_EQ1         = 1 << 5,  /**< \brief �Ƚ�ģʽ�£��Ҵ����жϽ���ʱ��DATA0 = DATA1 */
    AMHW_HC32F460_DCU_INT_GT1         = 1 << 6,  /**< \brief �Ƚ�ģʽ�£��Ҵ����жϽ���ʱ��DATA0 > DATA1 */
	AMHW_HC32F460_DCU_INT_WIN_INSIDE  = 1 << 7,  /**< \brief DATA2 <= DATA0 <= DATA1 */
	AMHW_HC32F460_DCU_INT_WIN_OUTSIDE = 2 << 7,  /**< \brief DATA0 > DATA1 ��  DATA0 < DATA2*/
	AMHW_HC32F460_DCU_INT_CMP_INVALID = 3 << 7,  /**< \brief DATA0 > DATA1 */
} amhw_hc32f460_dcu_int_condition_t;

/**
 * \brief DCU �ж�����ѡ��
 *
 * \param[in] p_hw_dcu : ָ��DCU�Ĵ�����ָ��
 *
 * \retval : ��ȡ��������
 */
am_static_inline
void amhw_hc32f460_dcu_int_condition_set (amhw_hc32f460_dcu_t              *p_hw_dcu,
                                          amhw_hc32f460_dcu_int_condition_t flag)
{
    p_hw_dcu->INTSEL = flag;
}


#define HC32F460_DCU0_TRIGGER_SEL_REG_ADDR  (0x40010844)
#define HC32F460_DCU1_TRIGGER_SEL_REG_ADDR  (0x40010848)
#define HC32F460_DCU2_TRIGGER_SEL_REG_ADDR  (0x4001084c)
#define HC32F460_DCU3_TRIGGER_SEL_REG_ADDR  (0x40010850)

/**
 * \brief DCU ����Դѡ��
 *
 * \param[in] p_hw_dcu    : ָ��DCU�Ĵ�����ָ��
 * \param[in] trigger_src : ����Դ�¼����
 *
 */
am_static_inline
void amhw_hc32f460_dcu_trigger_src_set (uint8_t dev_id, int trigger_src)
{
    switch (dev_id) {

    case 0: *(uint32_t *)HC32F460_DCU0_TRIGGER_SEL_REG_ADDR = trigger_src; break;
    case 1: *(uint32_t *)HC32F460_DCU1_TRIGGER_SEL_REG_ADDR = trigger_src; break;
    case 2: *(uint32_t *)HC32F460_DCU2_TRIGGER_SEL_REG_ADDR = trigger_src; break;
    case 3: *(uint32_t *)HC32F460_DCU3_TRIGGER_SEL_REG_ADDR = trigger_src; break;
    }
}

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
 * @} amhw_if_hc32f460_dcu
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_DCU_H */

/* end of file */

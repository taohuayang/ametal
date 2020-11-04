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
 * \brief OPA DAC��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   DAC������Ҳ���ѹ����ӦOPA�������PA04��С��ȵ����Ҳ���ѹ��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zlg118_core_opa_dac.c src_zlg118_core_opa_dac
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-10  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_core_opa_dac
 * \copydoc demo_zlg118_core_opa_dac.c
 */

/** [src_zlg118_core_opa_dac] */
#include "ametal.h"
#include "am_zlg118.h"
#include "am_gpio.h"
#include "zlg118_pin.h"
#include "am_zlg118_opa.h"
#include "demo_zlg_entries.h"
#include "math.h"

#define PI          3.14159265358979     /**< \briefԲ���� */
#define OPA_MODE    AM_ZLG118_OPA_DAC    /**< \brief OPA DAC��ѹ����ģʽ*/

/**< \brief DAC���õ�ѹֵ������  */
static uint16_t vol_val[128] = {0};

/*******************************************************************************
** \brief  �������Ҳ��Ĳ�����
** \param  buf:���ڴ�����Ҳ�������Ļ���
** \return ��
******************************************************************************/
static void _BufProduce(uint16_t* vol_val)
{
   uint8_t tmp;
   double tmp1;
   tmp1=PI/64;
   for(tmp=0; tmp<128; tmp++)
   {
       vol_val[tmp] =(uint16_t)(((sin(tmp1*tmp))*2047)+2048);
   }
}

/**
 * \brief �������
 */
void demo_zlg118_core_hw_opa_dac_entry (void)
{

    AM_DBG_INFO("demo am118_core hw opa dac test!\r\n");

    /* ����DACʱ�� */
    am_clk_enable(CLK_DAC);

    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    _BufProduce(vol_val);

    demo_zlg118_hw_opa_dac_entry(ZLG118_OPA,
                                 ZLG118_DAC,
                                 OPA_MODE,
                                 vol_val);
}

/* end of file */

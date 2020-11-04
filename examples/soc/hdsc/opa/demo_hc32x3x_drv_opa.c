/**
 * \file
 * \brief OPA��ͬģʽ�����������ϵ���̣�ͨ�� std ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *    OPA_UintMode_Test
 *    ��ʱͨ��ʾ�����۲�PC06��PC07�źţ�PC07����ź���PC06�ź�ͨ�ŷ�ֵ��һ�µġ�
 *    OPA_ForWardMode_Test
 *    ��ʱͨ��ʾ�����۲�PC06��PC07�źţ�PC07����ź���PC06�ź�ͨ�ŷ�ֵ����������
 *    OPA_GpMode_Test
 *    PC06����VCOR1.5V��PB15��PC07�ӵ���22K��PB15�ӵ���10K�Եأ�
 *    ��ʱͨ��ʾ�����۲�PC06��PC07�źţ�PC07����ź���PC06�ź�ͨ�ŷ�ֵ����������
 *
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 * * \par Դ����
 * \snippet demo_hc32_std_opa.c src_hc32_std_opa
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-17  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32_std_opa
 * \copydoc demo_hc32_std_opa.c
 */

/** [src_hc32_std_opa] */
#include "ametal.h"
#include "am_hc32.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_hc32x3x_opa.h"

/**
 * \brief OPA���̣�ͨ���첽��׼�ӿ�ʵ��
 */
void demo_hc32x3x_drv_opa_entry (void *p_handle, uint8_t ch)
{

   if (p_handle ==NULL){
       return ;
   }

    /* ����ģʽ   ��Ҫ�ײ�����IO�˿����ڲ�����ΪAWHW_HC32_OPA_PO_EN */
    am_hc32_opa_mode_set(p_handle, ch);

    /* ʹ�� */
    am_hc32_opa_enable(p_handle);

    while(1){
      ;
    }
}

/* end of file */

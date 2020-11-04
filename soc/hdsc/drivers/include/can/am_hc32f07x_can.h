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
 * \brief LVD����������LVD��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-26
 * \endinternal
 */
 
#ifndef __AM_HC32F07X_CAN_H
#define __AM_HC32F07X_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_can.h"
#include "hw/amhw_hc32f07x_can.h"

/**
 * \addtogroup am_hc32_if_lvd
 * \copydoc am_hc32_lvd.h
 * @{
 */

/**
 * \brief can ��ʼ��������Ϣ
 */
typedef struct am_hc32f07x_can_init_info {

        /** \brief ʱ�䴥��ͨ�ŷ�ʽ
     *   0 ����
     *   1 ʹ��
     */
    am_bool_t   can_ttcm;

    /** \brief ���ջ��������ݴ洢ģʽ
     *   0 ����ģʽ
     *   1 �洢���� 
     */
    amhw_hc32f07x_can_rxbuf_all_t  rx_all;

    /** \brief ���ջ���������ģʽ
     *   0 ������յ����ݱ�����
     *   1 ���½��յ������ݲ����洢
     */
    amhw_hc32f07x_can_rxbuf_mode_t  over_mode;

    /** \brief ����������ģʽѡ��
     *   0 FIFOģʽ
     *   1 ���ȼ�ģʽ
     */
    amhw_hc32f07x_can_stb_mode_t    can_stb_mode;

    /** \brief ���ջ����������趨ֵ */
    uint8_t warning_limitval;

    /** \brief ���󾯸��޶�ֵ */
    uint8_t error_warning_limitval;    

}am_hc32f07x_can_init_info_t;

/**
 * \brief �жϻص���Ϣ
 */
typedef struct am_hc32f07x_can_intcb_info{

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
} am_hc32f07x_can_intcb_info_t;

/**
 * \brief CAN�豸��Ϣ�ṹ��
 */
typedef struct am_hc32f07x_can_info {

    /** \brief �Ĵ�������ַ */
    uint32_t                       regbase;

    /** \brief �жϺ� */	
    uint32_t                       int_num; 

    amhw_hc32f07x_can_type_t        type;

    /** \brief �ص���Ϣ */
    am_hc32f07x_can_intcb_info_t  *p_intcb_info;

    /** \brief �ص���Ϣ�ڴ��С */
    uint8_t                        p_intcb_num;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

    am_hc32f07x_can_init_info_t    *init_info;

}am_hc32f07x_can_devinfo_t;

/**
 * \brief �豸
 */
typedef struct am_hc32f07x_can_dev {
    am_can_serv_t                   handle;

    const am_hc32f07x_can_devinfo_t  *p_devinfo;

} am_hc32f07x_can_dev_t;

/**
 * \brief CAN��ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 * \param[in] p_devinfo : �豸��Ϣ
 *
 * \return handle
 */
am_can_handle_t am_hc32f07x_can_init (am_hc32f07x_can_dev_t           *p_dev,
                                      const am_hc32f07x_can_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 *
 * \return ��
 */
void am_hc32f07x_can_deinit (am_can_handle_t handle);

/**
 * @} am_hc32f07x_if_can
 */


#ifdef __cplusplus
}
#endif

#endif /* __AM_S32K14X_CAN_H */

/* end of file */

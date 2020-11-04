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
 * \brief CAN�����豸��Ϣ
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-31  zc, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG237_CAN_H
#define __AM_ZLG237_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_can.h"
#include "amhw_zlg237_can.h"

/**
 * \addtogroup am_zlg237_if_can
 * \copydoc am_zlg237_can.h
 * @{
 */


/**
 * \brief can ��ʼ��������Ϣ
 */
typedef struct am_zlg237_can_init_info {

    /** \brief 0 ��ͨģʽ   1 �ػ�ģʽ */
    amhw_zlg237_can_test_mode_t     can_mode;

    /** \brief ʱ�䴥��ͨ��ģʽ  0 �Ǵ���  1 ���� */
    am_bool_t   can_ttcm;

    /** \brief ����Զ����߹���
     *   0 �����MCR��INRQλ�����á�1�� �� �塮0�� һ��Ӳ����⵽128��11λ��������λ���˳�����ģʽ
     *   1 һ��Ӳ����⵽128��11λ��������λ���˳�����ģʽ
     */
    am_bool_t   can_abom;

    /** \brief �Զ�����ģʽ
     *   0 ˯��ģʽͨ�����CAN_MCR��SLEEPλ  ���������
     *   1 ˯��ģʽͨ�����CAN���ģ���Ӳ���Զ����ѡ����ѵ�ͬʱ��Ӳ���Զ���CAN_MSR ��SLEEP��SLAK�塮0��
     */
    am_bool_t   can_awum;

    /** \brief ��ֹ�����Զ��ش�
     *   0 Ӳ���ڷ��ͱ���ʧ��ʱ��һֱ�ش������ͳɹ�
     *   1 CAN����ֻ����һ��
     */
    am_bool_t   can_nart;

    /** \brief ����FIFO����ģʽ
     *   0 �ڽ������ʱFIFOδ��������������FIFO�ı���δ����������һ���յ��ı��ĻḲ��ԭ�еı���
     *   1 �ڽ������ʱFIFO��������������FIFO�ı���δ����������һ���յ��ı��Ļᱻ����
     */
    am_bool_t   can_rflm;

    /** \brief ����FIFO���ȼ�
     *   0 ���ȼ��ɱ��ĵı�ʶ��������
     *   1 ���ȼ��ɷ��������˳��������
     */
    am_bool_t   can_txfp;

}am_zlg237_can_init_info_t;

/**<brief �˲�������������Ϣ  */
typedef struct {
    uint8_t  can_fliter_fifo;        /** <brief ����FIFO 0 FIFO0 1 FIFO1*/
    uint8_t  can_filter_mode;        /** <brief �˲���ģʽ 0 ��ʶ������λ  1 ��ʶ���б�λ  */
    uint8_t  can_filter_scale;       /** <brief �˲���λ�� 0 2��16λ   1 ����32λ*/
    uint8_t  filter_state;           /** <brief �˲�������״̬  0 ������������ 1 ������������ */

}amhw_zlg237_can_filter_t;

/**
 * \brief �жϻص���Ϣ
 */
typedef struct am_zlg237_can_intcb_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
} am_zlg237_can_intcb_info_t;

/**
 * \brief CAN �豸��Ϣ
 */
typedef struct am_zlg237_can_devinfo {

    /** \brief �Ĵ�������ַ */
    uint32_t                         regbase;

    /** \brief �жϺ� */
    uint32_t                         int_num;

    /** \brief �ص���Ϣ */
    am_zlg237_can_intcb_info_t      *p_intcb_info;

    /** \brief �ص���Ϣ�ڴ��С */
    uint8_t                          p_intcb_num;

    /** \brief ƽ̨��ʼ������ */
    void                           (*pfn_plfm_init)(void);

    /** \brief ƽ̨ȥ��ʼ������ */
    void                           (*pfn_plfm_deinit)(void);

    amhw_zlg237_can_filter_t       *filter;

    am_zlg237_can_init_info_t      *init_info;

} am_zlg237_can_devinfo_t;

/**
 * \brief �豸
 */
typedef struct am_zlg237_can_dev {
    am_can_serv_t                   handle;

    /** \brief ����ģʽ */
    amhw_zlg237_can_mode_t          mode;

    /** \brief ������ƥ�����*/
    uint8_t                         fmi;


    const am_zlg237_can_devinfo_t  *p_devinfo;
} am_zlg237_can_dev_t;

/**
 * \brief CAN��ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 * \param[in] p_devinfo : �豸��Ϣ
 *
 * \return handle
 */
am_can_handle_t am_zlg237_can_init (am_zlg237_can_dev_t           *p_dev,
                                    const am_zlg237_can_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 *
 * \return ��
 */
void am_zlg237_can_deinit (am_can_handle_t handle);

/**
 * @} am_s32k14x_if_can
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_S32K14X_CAN_H */

/* end of file */


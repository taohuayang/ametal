/*******************************************************************************
*                                 AMetal
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief CAN
 *
 * \internal
 * \par Modification History
 * - 1.00 19-07-31  zc, first implementation
 * \endinternal
 */
#include "hw/amhw_zlg237_can.h"



/**
 * \brief CAN ����ģʽ����
 *
 * \param[in] p_hw_can          : ָ��CAN�Ĵ������ָ��
 * \param[in] operating_mode    : ָ��amhw_zlg237_can_operating_type_t ����
 *
 * \return  CAN��ģʽ����״̬�Ƿ�ɹ�  0  1
 */
uint8_t amhw_zlg237_can_operating_mode_request (amhw_zlg237_can_t     *p_hw_can,
                                                amhw_zlg237_can_mode_t mode)
{
    uint8_t  status  = CAN_DISABLE;
    uint32_t timeout = 0x0000ffff;

    if (mode == AMHW_ZLG237_CAN_OPERATING_MODE_INIT) {

        /* �����ʼ��  */
        p_hw_can->mcr = (uint32_t)((p_hw_can->mcr &(uint32_t)
                                     (~(uint32_t)AMHW_ZLG237_CAN_MCR_SLEEP)) |
                        AMHW_ZLG237_CAN_MCR_INRQ);
        /* �ȴ�Ӧ���ź� */
        while ( ((p_hw_can->msr & (uint32_t)0x3) != AMHW_ZLG237_CAN_MSR_INAK) &&
                (timeout != 0)) {
            timeout--;
        }

        /* ��ʱ��ACK��ȷ��״̬ */
        if ((p_hw_can->msr & (uint32_t)0x3) != AMHW_ZLG237_CAN_MSR_INAK) {
            status = CAN_DISABLE;
        } else {
            status = CAN_ENABLE;
        }
    } else if (mode == AMHW_ZLG237_CAN_OPERATING_NORMAL) {

        /* �����뿪��ʼ��ģʽ��˯��ģʽ ��������ģʽ */
        p_hw_can->mcr &= (uint32_t) (~(AMHW_ZLG237_CAN_MCR_SLEEP |
                                       AMHW_ZLG237_CAN_MCR_INRQ));

        /* �ȴ�Ӧ�� */
        while ( ((p_hw_can->msr & (uint32_t)0x3) != 0) && (timeout != 0)) {
            timeout--;
        }

        if ((p_hw_can->msr & (uint32_t)0x3) != 0) {
            status = CAN_DISABLE;
        } else {
            status = CAN_ENABLE;
        }
    } else if (mode == AMHW_ZLG237_CAN_OPERATING_SLEEP) {
        /* ����˯��ģʽ  */
        p_hw_can->mcr = (uint32_t)((p_hw_can->mcr &(uint32_t)
                                     (~(uint32_t)AMHW_ZLG237_CAN_MCR_INRQ)) |
                        AMHW_ZLG237_CAN_MCR_SLEEP);
        /* �ȴ�Ӧ���ź� */
        while ( ((p_hw_can->msr & (uint32_t)0x3) != AMHW_ZLG237_CAN_MSR_SLAK) &&
                (timeout != 0)) {
            timeout--;
        }

        /* ��ʱ��ACK��ȷ��״̬ */
        if ((p_hw_can->msr & (uint32_t)0x3) != AMHW_ZLG237_CAN_MSR_SLAK) {
            status = CAN_DISABLE;
        } else {
            status = CAN_ENABLE;
        }
        /* ����ģʽ */
    } else {
        status = CAN_DISABLE;
    }

    return (uint8_t) status;
}


/**
 * \brief CAN �����Ӧ��־λ�Ƿ�����
 *
 * \param[in] p_hw_can        : ָ��CAN�Ĵ������ָ��
 * \param[in] can_it          : ָ������ amhw_zlg237_can_flag_t
 * \param[in] state           : ״̬   0  1
 * \return  ��
 */
uint8_t amhw_zlg237_can_get_flagstatus(amhw_zlg237_can_t        *p_hw_can,
                                       amhw_zlg237_can_flag_t    can_flag)
{
    uint8_t bitstatus = CAN_DISABLE;

    if ( (can_flag &  AMHW_ZLG237_CAN_FLAG_ESR) != (uint32_t)CAN_DISABLE) {
        if ((p_hw_can->esr & (can_flag & 0x000fffff)) !=
                (uint32_t)CAN_DISABLE ) {
            bitstatus = CAN_ENABLE;
        } else {
            bitstatus = CAN_DISABLE;
        }
    } else if ( (can_flag &  AMHW_ZLG237_CAN_FLAG_MSR) !=
            (uint32_t)CAN_DISABLE) {
        if ((p_hw_can->msr & (can_flag & 0x000fffff)) !=
                (uint32_t)CAN_DISABLE ) {
            bitstatus = CAN_ENABLE;
        } else {
            bitstatus = CAN_DISABLE;
        }
    } else if ( (can_flag &  AMHW_ZLG237_CAN_FLAG_TSR) !=
            (uint32_t)CAN_DISABLE) {
        if ((p_hw_can->tsr & (can_flag & 0x000fffff)) !=
                (uint32_t)CAN_DISABLE) {
            bitstatus = CAN_ENABLE;
        } else {
            bitstatus = CAN_DISABLE;
        }
    } else if ( (can_flag &  AMHW_ZLG237_CAN_FLAG_RF0R) !=
            (uint32_t)CAN_DISABLE) {
        if ((p_hw_can->rf_0r & (can_flag & 0x000fffff)) !=
                (uint32_t)CAN_DISABLE) {
            bitstatus = CAN_ENABLE;
        } else {
            bitstatus = CAN_DISABLE;
        }
    } else {
        if ((p_hw_can->rf_1r & (can_flag & 0x000fffff)) !=
                (uint32_t)CAN_DISABLE) {
            bitstatus = CAN_ENABLE;
        } else {
            bitstatus = CAN_DISABLE;
        }
    }

    return bitstatus ;
}


/**
 * \brief ��ȡָ���жϵ�״̬
 *
 * \param[in] p_hw_can ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
uint8_t amhw_zlg237_can_get_itstatus (amhw_zlg237_can_t *p_hw_can,
                                      uint32_t           can_it)
{
    uint8_t it_status = CAN_DISABLE;

        switch (can_it) {

        case (AMHW_ZLG237_CAN_INT_TMEIE):
            if (p_hw_can->ier & 0x01) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->tsr,
                                AMHW_ZLG237_CAN_TSR_RQCP0 |
                                AMHW_ZLG237_CAN_TSR_RQCP1 |
                                AMHW_ZLG237_CAN_TSR_RQCP2 );
            }

            break;

        case ( AMHW_ZLG237_CAN_INT_FMPIE0):
            if (p_hw_can->ier &0x02) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->rf_0r, AMHW_ZLG237_CAN_RF0R_FMP0);
            }

            break;

        case ( AMHW_ZLG237_CAN_INT_FFIE0):
            if (p_hw_can->ier & 0x04) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->rf_0r, AMHW_ZLG237_CAN_RF0R_FULL0);
            }

            break;

        case (  AMHW_ZLG237_CAN_INT_FOVIE0):
            if (p_hw_can->ier & 0x08) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->rf_0r, AMHW_ZLG237_CAN_RF0R_FOVR0);
            }

            break;

        case ( AMHW_ZLG237_CAN_INT_FMPIE1):
            if (p_hw_can->ier & 0x10) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->rf_1r, AMHW_ZLG237_CAN_RF0R_FMP1);
            }

            break;

        case (  AMHW_ZLG237_CAN_INT_FFIE1):
            if (p_hw_can->ier & 0x20) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->rf_1r, AMHW_ZLG237_CAN_RF0R_FULL1);
            }

            break;

        case (  AMHW_ZLG237_CAN_INT_FOVIE1):
            if (p_hw_can->ier & 0x40) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->rf_1r, AMHW_ZLG237_CAN_RF0R_FOVR1);
            }

            break;

        case (  AMHW_ZLG237_CAN_INT_EWGIE):
            if (p_hw_can->ier & 0x100) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->esr, AMHW_ZLG237_CAN_ESR_EWGF);
            }

            break;

        case ( AMHW_ZLG237_CAN_INT_EPVIE):
            if (p_hw_can->ier & 0x200) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->esr, AMHW_ZLG237_CAN_ESR_EPVF);
            }

            break;

        case ( AMHW_ZLG237_CAN_INT_BOFIE):
             if (p_hw_can->ier & 0x400) {
                 it_status = amhw_zlg237_can_check_itstatus(
                                 p_hw_can->esr, AMHW_ZLG237_CAN_ESR_BOFF);
             }

           break;

        case (  AMHW_ZLG237_CAN_INT_LECIE):
            if (p_hw_can->ier & 0x800) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->esr, AMHW_ZLG237_CAN_ESR_LEC);
            }

            break;

        case (  AMHW_ZLG237_CAN_INT_ERRIE):
            if (p_hw_can->ier & 0x8000) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->msr, AMHW_ZLG237_CAN_MSR_ERRI);
            }

            break;

        case ( AMHW_ZLG237_CAN_INT_WKUIE):
            if (p_hw_can->ier & 0x10000) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->msr, AMHW_ZLG237_CAN_MSR_WKUI);
            }

            break;

        case ( AMHW_ZLG237_CAN_INT_SLKIE):
            if (p_hw_can->ier & 0x20000) {
                it_status = amhw_zlg237_can_check_itstatus(
                                p_hw_can->msr, AMHW_ZLG237_CAN_MSR_SLAKI);
            }

            break;

        default:
            it_status = 0;
            break;

        }

    return (uint8_t)it_status;
}


/**
 * \brief  ���ָ���жϵı�־λ
 *
 * \param[in] p_hw_can ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
void amhw_zlg237_can_clear_itstatus (amhw_zlg237_can_t *p_hw_can,
                                      uint32_t           can_it)
{
    switch (can_it ) {

    case (AMHW_ZLG237_CAN_INT_TMEIE):
        p_hw_can->tsr |= (AMHW_ZLG237_CAN_TSR_RQCP0 |
                          AMHW_ZLG237_CAN_TSR_RQCP1 |
                          AMHW_ZLG237_CAN_TSR_RQCP2  );
        break;

    case ( AMHW_ZLG237_CAN_INT_FMPIE0):

        /* ͨ����RFOM λ ��1 ���ͷ�FIFO���� */
        p_hw_can->rf_0r |= (uint32_t)AMHW_ZLG237_CAN_RF0R_RFOM0;
        break;

    case (  AMHW_ZLG237_CAN_INT_FFIE0):

        /* ͨ��д 1 �������λ */
        p_hw_can->rf_0r |= (uint32_t)AMHW_ZLG237_CAN_RF0R_FULL0;
        break;

    case (  AMHW_ZLG237_CAN_INT_FOVIE0):

        /* ͨ��д 1 �������λ */
        p_hw_can->rf_0r |= (uint32_t)AMHW_ZLG237_CAN_RF0R_FOVR0;
        break;

    case ( AMHW_ZLG237_CAN_INT_FMPIE1):

        /* ͨ����RFOM λ ��1 ���ͷ�FIFO���� */
        p_hw_can->rf_1r |= (uint32_t)AMHW_ZLG237_CAN_RF1R_RFOM1;
        break;

    case (  AMHW_ZLG237_CAN_INT_FFIE1):

        /* ͨ��д 1 �������λ */
        p_hw_can->rf_1r |= (uint32_t)AMHW_ZLG237_CAN_RF0R_FULL1;
        break;

    case ( AMHW_ZLG237_CAN_INT_FOVIE1):

        /* ͨ��д 1 �������λ */
        p_hw_can->rf_1r |= (uint32_t)AMHW_ZLG237_CAN_RF0R_FOVR1;
        break;

    case ( AMHW_ZLG237_CAN_INT_WKUIE):

        /* ͨ��д 1 �������λ */
        p_hw_can->msr |= (uint32_t)AMHW_ZLG237_CAN_MSR_WKUI;
        break;

    case (AMHW_ZLG237_CAN_INT_SLKIE):

        /* ͨ��д 1 �������λ */
        p_hw_can->msr |= (uint32_t)AMHW_ZLG237_CAN_MSR_SLAKI;
        break;

//    case ( 1ul << AMHW_ZLG237_CAN_INT_EWGIE):
//        p_hw_can->esr &= ~(uint32_t)AMHW_ZLG237_CAN_ESR_EWGF;
//        break;
//
//    case ( 1ul << AMHW_ZLG237_CAN_INT_EPVIE):
//        p_hw_can->esr &= ~(uint32_t)AMHW_ZLG237_CAN_ESR_EPVF;
//        break;
//
//    case ( 1ul << AMHW_ZLG237_CAN_INT_BOFIE):
//        p_hw_can->esr &= ~(uint32_t)AMHW_ZLG237_CAN_ESR_BOFF;
//           break;

    case (  AMHW_ZLG237_CAN_INT_LECIE):
       p_hw_can->esr &= ~(uint32_t)AMHW_ZLG237_CAN_ESR_LEC;
       break;

    case ( AMHW_ZLG237_CAN_INT_ERRIE):

       /* ͨ��д 1 �������λ */
       p_hw_can->msr |= (uint32_t)AMHW_ZLG237_CAN_MSR_ERRI;
       break;

    default:
        break;

    }
}


/* end of file */

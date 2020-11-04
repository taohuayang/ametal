#ifndef __AM_UARTCMD_CD4051_H
#define __AM_UARTCMD_CD4051_H

#include "ametal.h"

#define  AM_FM175XX_ANTENNA_ONE       1  /**< \brief 1�ɿ������豸 FM17510 */
#define  AM_FM175XX_ANTENNA_TWO       2  /**< \brief 2�ɿ������豸 FM17550 */
#define  AM_FM175XX_ANTENNA_EIGHT     8  /**< \brief 8�ɿ������豸 FM175xx + CD4051*/

typedef struct am_cd4051_device_info{
    int pin_en;
    int pin_s0;
    int pin_s1;
    int pin_s2;
}am_cd4051_device_info_t;

typedef struct am_antenna_info{
    am_cd4051_device_info_t  cd4051_dev_inf;
    int                      antenna_num;
}am_antenna_info_t;

/**
 * \brief cd4051���ų�ʼ��
 */
void uartcmd_cd4051_pin_init (am_antenna_info_t *p_dev);

/**
 * \brief cd4051ʹ��
 */
void uartcmd_cd4051_chip_en (am_antenna_info_t *p_dev);

/**
 * \brief cd4051ͨ��ѡ��
 *
 * \param[in] channel_num : ѡ���ͨ����(0~7)
 */
void uartcmd_cd4051_channel_selected (am_antenna_info_t *p_dev, uint8_t channel_num);


#endif

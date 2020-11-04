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
 * \brief GPIO hardware operation interface
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-06  zp, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG118_GPIO_H
#define __AMHW_ZLG118_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"

/**
 * \addtogroup amhw_zlg118_if_gpio
 * \copydoc amhw_zlg118_gpio.h
 * @{
 */

#define AMHW_ZLG118_GPIO_PORT_MAX 6  /**< \brief GPIO ����GPIO�˿����� */

/**
 * \brief GPIO ���żĴ�����ṹ��
 */
typedef struct {

    /**
     * \brief �˿ڹ���������(64����ÿ����Ӧһ������)
     *        PA0~PA15 ��
     *        PB0~PB15 ��
     *        PC0~PC15 ��
     *        PD0~PD15
     */
    __IO  uint32_t pin_x_sel_I[64];

} amhw_zlg118_gpio_pin_t;

/**
 * \brief GPIO �˿ڼĴ����ṹ��
 */
typedef struct {
    __IO  uint32_t dir;         /**< \brief ����������üĴ��� */
    __IO  uint32_t in;          /**< \brief ����ֵ�Ĵ���*/
    __IO  uint32_t out;         /**< \brief ���ֵ���üĴ���*/
    __IO  uint32_t ads;         /**< \brief ��ģ���üĴ���*/
    __IO  uint32_t bset;        /**< \brief λ��λ�Ĵ���*/
    __IO  uint32_t bclr;        /**< \brief λ����Ĵ���*/
    __IO  uint32_t bsetclr;     /**< \brief λ��λ����Ĵ���*/
    __IO  uint32_t dr;          /**< \brief �����������üĴ���*/
    __IO  uint32_t pu;          /**< \brief ����ʹ�����üĴ���*/
    __IO  uint32_t pd;          /**< \brief ����ʹ�����üĴ���*/
    __IO  uint32_t reserve;     /**< \brief ����λ */
    __IO  uint32_t od;          /**< \brief ��©������üĴ���*/
    __IO  uint32_t hie;         /**< \brief �ߵ�ƽ�ж�ʹ�����üĴ���*/
    __IO  uint32_t lie;         /**< \brief �͵�ƽ�ж�ʹ�����üĴ���*/
    __IO  uint32_t rie;         /**< \brief �������ж�ʹ�����üĴ���*/
    __IO  uint32_t fie;         /**< \brief �½����ж�ʹ�����üĴ���*/

}amhw_zlg118_gpio_port_t;

/**
 * \brief GPIO �˿��жϼĴ����ṹ��
 */
typedef struct {
    __IO  uint32_t stat;          /**< \brief �ж�״̬�Ĵ���*/
          uint32_t reserve0[3];   /**< \brief ����λ */
    __IO  uint32_t iclr;          /**< \brief �ж�����Ĵ���*/
          uint32_t reserve1[11];  /**< \brief ����λ */
}amhw_zlg118_gpio_port_int_t;

/**
 * \brief GPIO �˿ڸ����Ĵ����ṹ��
 */
typedef struct {
    __IO  uint32_t ctrl0;         /**< \brief �˿ڸ����������üĴ���0 */
    __IO  uint32_t ctrl1;         /**< \brief �˿ڸ����������üĴ���1 */
    __IO  uint32_t ctrl2;         /**< \brief �˿ڸ����������üĴ���2 */
    __IO  uint32_t timgs;         /**< \brief �˿ڸ������ܶ�ʱ���ſ�ѡ�� */
    __IO  uint32_t times;         /**< \brief �˿ڸ������ܶ�ʱ��ETRѡ�� */
    __IO  uint32_t timcps;        /**< \brief �˿ڸ������ܶ�ʱ����������ѡ�� */
    __IO  uint32_t pcas;          /**< \brief �˿ڸ�������PCA����ѡ�� */
    __IO  uint32_t pcnt;          /**< \brief �˿ڸ�������PCNT����ѡ�� */
    __I   uint32_t reserve[824];  /**< \brief ����λ */
}amhw_zlg118_gpio_port_support_t;

/**
 * \brief һ��ṹ�壨�ĸ��˿�Ϊһ�飬����PA-PD��
 */
typedef struct {
    amhw_zlg118_gpio_pin_t          gpio_pin_x;
    amhw_zlg118_gpio_port_t         gpio_port[4];
    amhw_zlg118_gpio_port_int_t     gpio_int_reg[4];
    amhw_zlg118_gpio_port_support_t gpio_sup_reg;
} amhw_zlg118_gpio_group_t;

/**
 * \brief GPIO�Ĵ�����ṹ��
 */
typedef struct amhw_zlg118_gpio {
    amhw_zlg118_gpio_group_t    gpio[(AMHW_ZLG118_GPIO_PORT_MAX/4) + 1];
} amhw_zlg118_gpio_t;


/**
 * \brief GPIO���Ÿ�������
 * \note ÿ�����Ų�һ����Ψһ����ȷ��������ͨGPIO�������ã���Ӧ��ֵΪ0
 */
typedef enum {
    AMHW_ZLG118_AFIO_NO = 0,
    AMHW_ZLG118_AFIO_1,
    AMHW_ZLG118_AFIO_2,
    AMHW_ZLG118_AFIO_3,
    AMHW_ZLG118_AFIO_4,
    AMHW_ZLG118_AFIO_5,
    AMHW_ZLG118_AFIO_6,
    AMHW_ZLG118_AFIO_7,
}amhw_zlg118_gpio_afio_t;

/**
 * \brief ���Ÿ�������
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] afio_choice: ���Ÿ���ѡ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_afio_set (amhw_zlg118_gpio_t      *p_hw_gpio,
                                amhw_zlg118_gpio_afio_t  afio_choice,
                                int                      pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_pin_x.pin_x_sel_I[pin % 64] = afio_choice;
}

/**
 * \brief ���Ÿ��������ȡ
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ���ŵ�ǰ�������õľ�����ֵ
 */
am_static_inline
amhw_zlg118_gpio_afio_t amhw_zlg118_gpio_afio_get (amhw_zlg118_gpio_t *p_hw_gpio,
                                                   int                 pin)
{
    return (amhw_zlg118_gpio_afio_t)p_hw_gpio->gpio[pin / 64].gpio_pin_x.pin_x_sel_I[pin % 64];
}

/**
 * \brief ����GPIO���ŷ���Ϊ���
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_dir_output (amhw_zlg118_gpio_t *p_hw_gpio,
                                      int                 pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].dir &= ~(0x1ul << (pin % 16));
}

/**
 * \brief ����GPIO���ŷ���Ϊ����
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_dir_input (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].dir |= (0x1ul << (pin % 16));
}

/**
 * \brief ��ȡGPIO���������������
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return 1 �� ����
 *         0 �� ���
 */
am_static_inline
int amhw_zlg118_gpio_pin_dir_get (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    return (p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].dir & (0x1ul << (pin % 16))) ? 1 : 0;
}

/**
 * \brief ��GPIO���������ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : �͵�ƽ
 * \retval 1 : �ߵ�ƽ
 */
am_static_inline
int amhw_zlg118_gpio_pin_input_get(amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    return (p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].in & (0x1ul << (pin % 16))) ? 1 : 0;
}

/**
 * \brief ����GPIO���ŵ�ƽΪ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 * \note ������óɿ�©����������ⲿ�������������ߡ�
 */
am_static_inline
void amhw_zlg118_gpio_pin_out_high (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].out |= (0x1ul << (pin % 16));
}

/**
 * \brief ����GPIO���ŵ�ƽΪ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 */
am_static_inline
void amhw_zlg118_gpio_pin_out_low (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].out &= ~(0x1ul << (pin % 16));
}

/**
 * \brief ��GPIO���������ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : �͵�ƽ
 * \retval 1 : �ߵ�ƽ
 */
am_static_inline
int amhw_zlg118_gpio_pin_output_get (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    return (p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].out & (0x1ul << (pin % 16))) ? 1 : 0;
}

/**
 * \brief ����GPIO����Ϊģ��˿�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_analog_set (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].ads |= (0x1ul << (pin % 16));
}

/**
 * \brief ����GPIO����Ϊ���ֶ˿�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_digital_set (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].ads &= ~(0x1ul << (pin % 16));
}

/**
 * \brief ��ȡ��ǰ�˿����ֶ˿�/ģ��˿�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : ���ֶ˿�
 * \retval 1 : ģ��˿�
 */
am_static_inline
int amhw_zlg118_gpio_pin_analog_digital_get (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    return (p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].ads & (0x1ul << (pin % 16))) ? 1 : 0;
}

/**
 * \brief λ��λ�Ĵ���     ��λ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_bit_set (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].bset |= (0x1ul << (pin % 16));
}

/**
 * \brief λ����Ĵ���    ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_bit_clr (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].bclr |= (0x1ul << (pin % 16));
}

/**
 * \brief λ����Ĵ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_bit_hold (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].bset &= ~(0x1ul << (pin % 16));
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].bclr &= ~(0x1ul << (pin % 16));
}


/**
 * \brief λ��λ����Ĵ���   ��λ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 *
 * \note �üĴ���    ��16bit -- ��λ  ����Ӧλд1��
 *              ��16bit -- ����  ����Ӧλд1��
 *
 *       ��16bit�͵�16bit ��ͬλͬʱд1ʱ��
 *       ������и����ȼ������ö˿ڱ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_bitsetclr_set (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].bsetclr |= (0x1ul << ((pin % 16) + 16));
}

/**
 * \brief λ��λ����Ĵ���    ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \note �üĴ���    ��16bit -- ��λ  ����Ӧλд1��
 *              ��16bit -- ����  ����Ӧλд1��
 *
 *       ��16bit�͵�16bit ��ͬλͬʱд1ʱ��
 *       ������и����ȼ������ö˿ڱ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_bitsetclr_clr (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].bsetclr |= (0x1ul << (pin % 16));
}


/**
 * \brief λ��λ����Ĵ���    ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_bitsetclr_hold (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].bsetclr &= ~(0x1ul << (pin % 16));
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].bsetclr &= ~(0x1ul << ((pin % 16) + 16));
}

/**
 * \brief ����ʹ�����üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_pu_enable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].pu |= (0x1ul << (pin % 16));
}

/**
 * \brief ����ʹ�����üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_pu_disable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].pu &= ~(0x1ul << (pin % 16));
}

/**
 * \brief ����ʹ�����üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_pd_enable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].pd |= (0x1ul << (pin % 16));
}

/**
 * \brief ����ʹ�����üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_pd_disable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].pd &= ~(0x1ul << (pin % 16));
}

/**
 * \brief ��©������üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_od_enable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].od |= (0x1ul << (pin % 16));
}

/**
 * \brief ��©������üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_od_disable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].od &= ~(0x1ul << (pin % 16));
}

/**
 * \brief �����������üĴ���    ����������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_driver_low (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].dr |= (0x1ul << (pin % 16));
}

/**
 * \brief �����������üĴ���  ����������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_driver_high (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].dr &= ~(0x1ul << (pin % 16));
}

/**
 * \brief �ߵ�ƽ�ж�ʹ�����üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_high_int_enable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].hie |= (0x1ul << (pin % 16));
}

/**
 * \brief �ߵ�ƽ�ж�ʹ�����üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_high_int_disable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].hie &= ~(0x1ul << (pin % 16));
}

/**
 * \brief �͵�ƽ�ж�ʹ�����üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_low_int_enable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].lie |= (0x1ul << (pin % 16));
}

/**
 * \brief �͵�ƽ�ж�ʹ�����üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_low_int_disable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].lie &= ~(0x1ul << (pin % 16));
}

/**
 * \brief �������ж�ʹ�����üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_raising_int_enable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].rie |= (0x1ul << (pin % 16));
}

/**
 * \brief �������ж�ʹ�����üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_raising_int_disable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].rie &= ~(0x1ul << (pin % 16));
}

/**
 * \brief �½����ж�ʹ�����üĴ���    ʹ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_falling_int_enable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].fie |= (0x1ul << (pin % 16));
}

/**
 * \brief �½����ж�ʹ�����üĴ���   ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_pin_falling_int_disable (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_port[(pin % 64) / 16].fie &= ~(0x1ul << (pin % 16));
}

/**
 * \brief �ж�״̬�Ĵ���  ��ȡ�Ƿ����жϴ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 1 : ���жϴ���
 * \retval 0 : ���жϴ���
 */
am_static_inline
int amhw_zlg118_gpio_pin_int_flag_get (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    return (p_hw_gpio->gpio[pin / 64].gpio_int_reg[(pin % 64) / 16].stat & (0x1ul << (pin % 16))) ? 1 : 0;
}

/**
 * \brief �ж�����Ĵ���  �����־
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval none
 */
am_static_inline
void amhw_zlg118_gpio_pin_int_flag_clr (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_int_reg[(pin % 64) / 16].iclr |= (0x1ul << (pin % 16));
    p_hw_gpio->gpio[pin / 64].gpio_int_reg[(pin % 64) / 16].iclr &= ~(0x1ul << (pin % 16));
    p_hw_gpio->gpio[pin / 64].gpio_int_reg[(pin % 64) / 16].iclr |= (0x1ul << (pin % 16));
}

/**
 * \brief �ж�����Ĵ���  �������ı�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval none
 */
am_static_inline
void amhw_zlg118_gpio_pin_int_flag_hold (amhw_zlg118_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin / 64].gpio_int_reg[(pin % 64) / 16].iclr |= (0x1ul << (pin % 16));
}

/**
 * \brief �˿ڸ����������üĴ���0  DEEPSLEEPģʽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ��ϵͳ���� ACTIVE/SLEEPģʽ��ʱ��ϵͳʱ�Ӳ��ᱻ�رգ����Խ� IESEL����Ϊ 0��
 *       ��ʱ�����˿��жϵ��ⲿ�ź�Դ������ϵͳʱ��ͬ��֮������ж��źţ������˳��ⲿ�ź�Դ
 *       ��ë�̡�
 *       ��ϵͳ�������� DEEPSLEEPģʽ��ʱ��ϵͳʱ�ӽ����رգ����Խ� IESEL����Ϊ 1����
 *       ʱ�����˿��жϵ��ⲿ�ź�Դֱ�Ӳ����ж��źţ������˳��ⲿ�ź�Դ��ë�̡�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_int_mode_deepsleep (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl0 |= (0x1ul);
}

/**
 * \brief �˿ڸ����������üĴ���0  ACTIVE/SLEEPģʽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ��ϵͳ���� ACTIVE/SLEEPģʽ��ʱ��ϵͳʱ�Ӳ��ᱻ�رգ����Խ� IESEL����Ϊ 0��
 *       ��ʱ�����˿��жϵ��ⲿ�ź�Դ������ϵͳʱ��ͬ��֮������ж��źţ������˳��ⲿ�ź�Դ
 *       ��ë�̡�
 *       ��ϵͳ�������� DEEPSLEEPģʽ��ʱ��ϵͳʱ�ӽ����رգ����Խ� IESEL����Ϊ 1����
 *       ʱ�����˿��жϵ��ⲿ�ź�Դֱ�Ӳ����ж��źţ������˳��ⲿ�ź�Դ��ë�̡�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_int_mode_active_or_sleep (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl0 &= ~(0x1ul);
}

/**
 * \brief IR�������ѡ��  �������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_irout_polarity_forward (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 &= ~((0x1ul << 14));
}

/**
 * \brief IR�������ѡ��  �������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_irout_polarity_reverse (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 |= ((0x1ul << 14));
}

/**
 * \brief IR������Ի�ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \retval 0 : �������
 * \retval 1 : �������
 */
am_static_inline
int amhw_zlg118_gpio_sup_irout_polarity_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 & (0x1ul << 14)) ? 1 : 0;
}

/**
 * \brief hclk����ſ�   �ſ�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_hclk_gate (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 &= ~((0x1ul << 13));
}

/**
 * \brief hclk����ſ�    ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_hclk_output (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 |= ((0x1ul << 13));
}

/**
 * \brief pclk����ſ�   �ſ�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_pclk_gate (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 &= ~((0x1ul << 12));
}

/**
 * \brief pclk����ſ�    ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_pclk_output (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 |= ((0x1ul << 12));
}

/**
 * \brief hclk�����Ƶѡ�� ��
 *        pclk�����Ƶѡ�� ��
 *        tclk�����Ƶѡ��
 *        ö����
 */
typedef enum {
    AMHW_ZLG118_GPIO_SUP_CLK_DIV_NO = 0ul,
    AMHW_ZLG118_GPIO_SUP_CLK_DIV_2,
    AMHW_ZLG118_GPIO_SUP_CLK_DIV_4,
    AMHW_ZLG118_GPIO_SUP_CLK_DIV_8,
}amhw_zlg118_gpio_sup_clk_div_t;

/**
 * \brief hclk�����Ƶѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] div_value : ��Ƶϵ��    amhw_zlg118_gpio_sup_clk_div_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_hclk_div_set (amhw_zlg118_gpio_t             *p_hw_gpio,
                                        amhw_zlg118_gpio_sup_clk_div_t  div_value)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 = (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 & (~(0x3ul << 10))) |
                                            ((div_value & 0x3ul) << 10);
}

/**
 * \brief hclk�����Ƶϵ����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��ǰ��Ƶϵ�� amhw_zlg118_gpio_sup_clk_div_tö�����е�һ��
 */
am_static_inline
amhw_zlg118_gpio_sup_clk_div_t amhw_zlg118_gpio_sup_hclk_div_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_clk_div_t)((p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 >> 10) & 0x3ul);
}

/**
 * \brief pclk�����Ƶѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] div_value : ��Ƶϵ��    amhw_zlg118_gpio_sup_clk_div_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_pclk_div_set (amhw_zlg118_gpio_t             *p_hw_gpio,
                                        amhw_zlg118_gpio_sup_clk_div_t  div_value)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 = (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 & (~(0x3ul << 8))) |
                                            ((div_value & 0x3ul) << 8);
}

/**
 * \brief pclk�����Ƶϵ����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��ǰ��Ƶϵ�� amhw_zlg118_gpio_sup_clk_div_tö�����е�һ��
 */
am_static_inline
amhw_zlg118_gpio_sup_clk_div_t amhw_zlg118_gpio_sup_pclk_div_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_clk_div_t)((p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 >> 8) & 0x3ul);
}

/**
 * \brief �ⲿʱ���ź���Դѡ��  ��
 *        SPI0��SSN�ź���Դѡ�� ��
 *        SPI1��SSN�ź���Դѡ��
 *        ö����
 */
typedef enum {
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_HIGH = 0,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PA3,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PA4,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PA6,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PA8,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PA9,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PA12,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PA15,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PB1,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PB2,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PB5,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PB6,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PB9,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PB10,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PB12,
    AMHW_ZLG118_GPIO_SUP_EXTCLK_SSN01_PB14,
}amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t;

/**
 * \brief SPI0 SSN�ź���Դѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] ssn0_src  : �ź���Դ    amhw_zlg118_gpio_sup_extclk_or_ssn01_src_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_spi0_ssn_set (amhw_zlg118_gpio_t                         *p_hw_gpio,
                                        amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t  ssn0_src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 = (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 & (~(0xful << 4))) |
                                            ((ssn0_src & 0xful) << 4);
}

/**
 * \brief SPI0 SSN�ź���Դ��ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��ǰ��Ƶϵ�� amhw_zlg118_gpio_sup_extclk_or_ssn01_src_tö�����е�һ��
 */
am_static_inline
amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t amhw_zlg118_gpio_sup_spi0_ssn_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t)((p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 >> 4) & 0xful);
}

/**
 * \brief SPI1 SSN�ź���Դѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] ssn1_src  : �ź���Դ    amhw_zlg118_gpio_sup_extclk_or_ssn01_src_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_spi1_ssn_set (amhw_zlg118_gpio_t                         *p_hw_gpio,
                                        amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t  ssn1_src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 = (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 & (~(0xful << 0))) |
                                            ((ssn1_src & 0xful) << 0);
}

/**
 * \brief SPI1 SSN�ź���Դ��ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��ǰ��Ƶϵ�� amhw_zlg118_gpio_sup_extclk_or_ssn01_src_tö�����е�һ��
 */
am_static_inline
amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t amhw_zlg118_gpio_sup_spi1_ssn_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t)((p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 >> 0) & 0xful);
}

/**
 * \brief �ⲿʱ���ź���Դѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] ssn1_src  : �ź���Դ    amhw_zlg118_gpio_sup_extclk_or_ssn01_src_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_ext_clk_set (amhw_zlg118_gpio_t                         *p_hw_gpio,
                                       amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t  extclk_src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 = (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 & (~(0xful << 0))) |
                                            ((extclk_src & 0xful) << 0);
}

/**
 * \brief �ⲿʱ���ź���Դ��ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��ǰ��Ƶϵ�� amhw_zlg118_gpio_sup_extclk_or_ssn01_src_tö�����е�һ��
 */
am_static_inline
amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t amhw_zlg118_gpio_sup_ext_clk_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_extclk_or_ssn01_src_t)((p_hw_gpio->gpio[0].gpio_sup_reg.ctrl1 >> 0) & 0xful);
}

/**
 * \brief AHB���߷���ģʽ   ʹ��FASTIO���߷���PxIN,PxOUT�Ĵ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_inout_fastio_bus_mode (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 &= ~(0x3ul << 15);
}

/**
 * \brief AHB���߷���ģʽ   ʹ��AHB���߷���PxIN,PxOUT�Ĵ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_inout_ahb_bus_mode (amhw_zlg118_gpio_t *p_hw_gpio)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 |= (0x3ul << 15);
}

/**
 * \brief AHB���߷���ģʽ��ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return   0   ʹ��FASTIO���߷���PxIN,PxOUT�Ĵ���
 *           1   ʹ��AHB���߷���PxIN,PxOUT�Ĵ���
 */
am_static_inline
int amhw_zlg118_gpio_sup_inout_bus_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 & (0x3ul << 15)) ? 1 : 0;
}

/**
 * \brief tclk����ź�Դѡ��
 *        ö����
 */
typedef enum {
    AMHW_ZLG118_GPIO_SUP_TCLK_NO = 0,
    AMHW_ZLG118_GPIO_SUP_TCLK_RCH,
    AMHW_ZLG118_GPIO_SUP_TCLK_XTH,
    AMHW_ZLG118_GPIO_SUP_TCLK_PLL,
}amhw_zlg118_gpio_sup_tclk_src_t;

/**
 * \brief tclk�����Ƶѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] div_value : ��Ƶϵ��    amhw_zlg118_gpio_sup_clk_div_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tclk_div_set (amhw_zlg118_gpio_t             *p_hw_gpio,
                                        amhw_zlg118_gpio_sup_clk_div_t  div_value)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 = (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 & (~(0x3ul << 6))) |
                                            ((div_value & 0x3ul) << 6);
}

/**
 * \brief tclk�����Ƶϵ����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��ǰ��Ƶϵ�� amhw_zlg118_gpio_sup_clk_div_tö�����е�һ��
 */
am_static_inline
amhw_zlg118_gpio_sup_clk_div_t amhw_zlg118_gpio_sup_tclk_div_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_clk_div_t)((p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 >> 6) & 0x3ul);
}

/**
 * \brief tclk����ź�Դѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] tclk_src  : ��Ƶϵ��    amhw_zlg118_gpio_sup_tclk_src_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tclk_src_set (amhw_zlg118_gpio_t             *p_hw_gpio,
                                        amhw_zlg118_gpio_sup_clk_div_t  tclk_src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 = (p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 & (~(0x3ul << 4))) |
                                            ((tclk_src & 0x3ul) << 4);
}

/**
 * \brief ttclk����ź�Դ��ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ��ǰ��Ƶϵ�� amhw_zlg118_gpio_sup_tclk_src_tö�����е�һ��
 */
am_static_inline
amhw_zlg118_gpio_sup_tclk_src_t amhw_zlg118_gpio_sup_tclk_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_tclk_src_t)((p_hw_gpio->gpio[0].gpio_sup_reg.ctrl2 >> 4) & 0x3ul);
}

/**
 * \brief LPTimer1��ʱ��GATE����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������� PCA ����ѡ��(GPIO_PCAS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_lptim1_gate_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                               uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.pcas = (p_hw_gpio->gpio[0].gpio_sup_reg.pcas & (~(0x7ul << 6))) |
                                           ((src & 0x7ul) << 6);
}

/**
 * \brief LPTimer1��ʱ��GATE�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������� PCA ����ѡ��(GPIO_PCAS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_lptim1_gate_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.pcas >> 6) & 0x7ul);
}

/**
 * \brief LPTimer0��ʱ��GATE����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_lptim0_gate_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                               uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timgs = (p_hw_gpio->gpio[0].gpio_sup_reg.timgs & (~(0x7ul << 12))) |
                                            ((src & 0x7ul) << 12);
}

/**
 * \brief LPTimer0��ʱ��GATE�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_lptim0_gate_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timgs >> 12) & 0x7ul);
}

/**
 * \brief Timer3��ʱ��GATE����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim3_gate_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timgs = (p_hw_gpio->gpio[0].gpio_sup_reg.timgs & (~(0x7ul << 9))) |
                                            ((src & 0x7ul) << 9);
}

/**
 * \brief Timer3��ʱ��GATE�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim3_gate_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timgs >> 9) & 0x7ul);
}

/**
 * \brief Timer2��ʱ��GATE����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim2_gate_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timgs = (p_hw_gpio->gpio[0].gpio_sup_reg.timgs & (~(0x7ul << 6))) |
                                            ((src & 0x7ul) << 6);
}

/**
 * \brief Timer3��ʱ��GATE�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim2_gate_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timgs >> 6) & 0x7ul);
}

/**
 * \brief Timer1��ʱ��GATE����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim1_gate_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timgs = (p_hw_gpio->gpio[0].gpio_sup_reg.timgs & (~(0x7ul << 3))) |
                                            ((src & 0x7ul) << 3);
}

/**
 * \brief Timer1��ʱ��GATE�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim1_gate_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timgs >> 3) & 0x7ul);
}

/**
 * \brief Timer0��ʱ��GATE����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim0_gate_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timgs = (p_hw_gpio->gpio[0].gpio_sup_reg.timgs & (~(0x7ul))) |
                                            (src & 0x7ul);
}

/**
 * \brief Timer0��ʱ��GATE�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim0_gate_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (p_hw_gpio->gpio[0].gpio_sup_reg.timgs & 0x7ul);
}

/**
 * \brief LPTimer1��ʱ��ETR����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������� PCA ����ѡ��(GPIO_PCAS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_lptim1_etr_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                              uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.pcas = (p_hw_gpio->gpio[0].gpio_sup_reg.pcas & (~(0x7ul << 9))) |
                                            ((src & 0x7ul) << 9);
}

/**
 * \brief LPTimer1��ʱ��ETR�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������� PCA ����ѡ��(GPIO_PCAS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_lptim1_etr_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.pcas >> 9) & 0x7ul);
}

/**
 * \brief LPTimer0��ʱ��ETR����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_lptim0_etr_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                              uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.times = (p_hw_gpio->gpio[0].gpio_sup_reg.times & (~(0x7ul << 12))) |
                                            ((src & 0x7ul) << 12);
}

/**
 * \brief LPTimer0��ʱ��ETR�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ�� ETRѡ��(GPIO_TIMES)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_lptim0_etr_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.times >> 12) & 0x7ul);
}

/**
 * \brief Timer3��ʱ��ETR����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim3_etr_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                            uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.times = (p_hw_gpio->gpio[0].gpio_sup_reg.times & (~(0x7ul << 9))) |
                                            ((src & 0x7ul) << 9);
}

/**
 * \brief Timer3��ʱ��ETR�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ�� ETRѡ��(GPIO_TIMES)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim3_etr_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.times >> 9) & 0x7ul);
}

/**
 * \brief Timer2��ʱ��ETR����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim2_etr_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                            uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.times = (p_hw_gpio->gpio[0].gpio_sup_reg.times & (~(0x7ul << 6))) |
                                            ((src & 0x7ul) << 6);
}

/**
 * \brief Timer2��ʱ��ETR�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ�� ETRѡ��(GPIO_TIMES)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim2_etr_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.times >> 6) & 0x7ul);
}

/**
 * \brief Timer1��ʱ��ETR����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim1_etr_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                            uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.times = (p_hw_gpio->gpio[0].gpio_sup_reg.times & (~(0x7ul << 3))) |
                                            ((src & 0x7ul) << 3);
}

/**
 * \brief Timer1��ʱ��ETR�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ�� ETRѡ��(GPIO_TIMES)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim1_etr_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.times >> 3) & 0x7ul);
}

/**
 * \brief Timer0��ʱ��ETR����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ���ſ�ѡ��(GPIO_TIMGS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim0_etr_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                            uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.times = (p_hw_gpio->gpio[0].gpio_sup_reg.times & (~(0x7ul << 0))) |
                                            ((src & 0x7ul) << 0);
}

/**
 * \brief Timer0��ʱ��ETR�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ�� ETRѡ��(GPIO_TIMES)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim0_etr_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.times >> 0) & 0x7ul);
}

/**
 * \brief Timer3��ʱ��CH0B����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim3_ch0b_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timcps = (p_hw_gpio->gpio[0].gpio_sup_reg.timcps & (~(0x7ul << 12))) |
                                             ((src & 0x7ul) << 12);
}

/**
 * \brief Timer3��ʱ��CH0B�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim3_ch0b_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timcps >> 12) & 0x7ul);
}

/**
 * \brief Timer3��ʱ��CH0A����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim3_ch0a_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timcps = (p_hw_gpio->gpio[0].gpio_sup_reg.timcps & (~(0x7ul << 9))) |
                                             ((src & 0x7ul) << 9);
}

/**
 * \brief Timer3��ʱ��CH0A�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim3_ch0a_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timcps >> 9) & 0x7ul);
}

/**
 * \brief Timer2��ʱ��CHA����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim2_cha_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timcps = (p_hw_gpio->gpio[0].gpio_sup_reg.timcps & (~(0x7ul << 6))) |
                                             ((src & 0x7ul) << 6);
}

/**
 * \brief Timer2��ʱ��CHA�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim2_cha_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timcps >> 6) & 0x7ul);
}

/**
 * \brief Timer1��ʱ��CHA����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim1_cha_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timcps = (p_hw_gpio->gpio[0].gpio_sup_reg.timcps & (~(0x7ul << 3))) |
                                             ((src & 0x7ul) << 3);
}

/**
 * \brief Timer1��ʱ��CHA�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim1_cha_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timcps >> 3) & 0x7ul);
}

/**
 * \brief Timer0��ʱ��CHA����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_tim0_cha_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                             uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.timcps = (p_hw_gpio->gpio[0].gpio_sup_reg.timcps & (~(0x7ul << 0))) |
                                             ((src & 0x7ul) << 0);
}

/**
 * \brief Timer0��ʱ��CHA�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������ܶ�ʱ����������ѡ��(GPIO_TIMCPS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_tim0_cha_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.timcps >> 0) & 0x7ul);
}

/**
 * \brief PCA ECIʱ������ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������� PCA ����ѡ��(GPIO_PCAS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_pca_eci_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                           uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.pcas = (p_hw_gpio->gpio[0].gpio_sup_reg.pcas & (~(0x7ul << 3))) |
                                           ((src & 0x7ul) << 3);
}

/**
 * \brief PCA ECIʱ�������ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������� PCA ����ѡ��(GPIO_PCAS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_pca_eci_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.pcas >> 3) & 0x7ul);
}

/**
 * \brief PCA CH0 ���������ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *         --�˿ڸ������� PCA ����ѡ��(GPIO_PCAS)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_pca_ch0_src_set (amhw_zlg118_gpio_t *p_hw_gpio,
                                           uint8_t             src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.pcas = (p_hw_gpio->gpio[0].gpio_sup_reg.pcas & (~(0x7ul << 0))) |
                                           ((src & 0x7ul) << 0);
}

/**
 * \brief PCA CH0 ����������ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \note ����ѡ����ֵ����ο��û��ֲ�GPIO�½ڵ�
 *       --�˿ڸ������� PCA ����ѡ��(GPIO_PCAS)
 *
 * \return ��
 */
am_static_inline
uint8_t amhw_zlg118_gpio_sup_pca_ch0_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return ((p_hw_gpio->gpio[0].gpio_sup_reg.pcas >> 0) & 0x7ul);
}

/**
 * \brief PCNT��������ѡ��
 *        ö����
 */
typedef enum {
    AMHW_ZLG118_GPIO_SUP_PCNT_NO = 0,
    AMHW_ZLG118_GPIO_SUP_PCNT_VC0_OUT,
    AMHW_ZLG118_GPIO_SUP_PCNT_VC1_OUT,
    AMHW_ZLG118_GPIO_SUP_PCNT_VC2_OUT,
}amhw_zlg118_gpio_sup_pcnt_in_src_t;

/**
 * \brief PCNT_S1����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ   amhw_zlg118_gpio_sup_pcnt_in_src_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_pcnt_s1_src_set (amhw_zlg118_gpio_t                *p_hw_gpio,
                                           amhw_zlg118_gpio_sup_pcnt_in_src_t src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.pcnt = (p_hw_gpio->gpio[0].gpio_sup_reg.pcnt & (~(0x3ul << 2))) |
                                           ((src & 0x3ul) << 2);
}

/**
 * \brief PCNT_S1�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return amhw_zlg118_gpio_sup_pcnt_in_src_tö����
 */
am_static_inline
amhw_zlg118_gpio_sup_pcnt_in_src_t amhw_zlg118_gpio_sup_pcnt_s1_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_pcnt_in_src_t)((p_hw_gpio->gpio[0].gpio_sup_reg.pcnt >> 2) & 0x3ul);
}

/**
 * \brief PCNT_S0����ѡ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] src       : �趨��ֵ   amhw_zlg118_gpio_sup_pcnt_in_src_tö����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg118_gpio_sup_pcnt_s0_src_set (amhw_zlg118_gpio_t                *p_hw_gpio,
                                           amhw_zlg118_gpio_sup_pcnt_in_src_t src)
{
    p_hw_gpio->gpio[0].gpio_sup_reg.pcnt = (p_hw_gpio->gpio[0].gpio_sup_reg.pcnt & (~(0x3ul << 0))) |
                                           ((src & 0x3ul) << 0);
}

/**
 * \brief PCNT_S0�����ȡ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return amhw_zlg118_gpio_sup_pcnt_in_src_tö����
 */
am_static_inline
amhw_zlg118_gpio_sup_pcnt_in_src_t amhw_zlg118_gpio_sup_pcnt_s0_src_get (amhw_zlg118_gpio_t *p_hw_gpio)
{
    return (amhw_zlg118_gpio_sup_pcnt_in_src_t)((p_hw_gpio->gpio[0].gpio_sup_reg.pcnt >> 0) & 0x3ul);
}

typedef enum amhw_zlg118_gpiomode
{
    AMHW_ZLG118_GPIO_MODE_IPU = 0,         /**< \brief ��������ģʽ  */
    AMHW_ZLG118_GPIO_MODE_IPD = 1,         /**< \brief ��������ģʽ */
    AMHW_ZLG118_GPIO_MODE_AIN = 2,         /**< \brief ģ������ģʽ */
    AMHW_ZLG118_GPIO_MODE_IN_FLOATING = 3, /**< \brief ��������ģʽ */
    AMHW_ZLG118_GPIO_MODE_OUT_PP = 4,      /**< \brief �������ģʽ */
    AMHW_ZLG118_GPIO_MODE_OUT_OD = 5,      /**< \brief ��©���ģʽ */
    AMHW_ZLG118_GPIO_MODE_AOUT = 6         /**< \brief ģ�����ģʽ */
}amhw_zlg118_gpiomode_t;

/**
 * \brief ����GPIO���ŵ�ģʽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] gpio_mode : ���ŵ�ģʽ��ֵΪ amhw_zlg217_gpiomode_t ���ö������
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
void amhw_zlg118_gpio_pin_mode_set (amhw_zlg118_gpio_t     *p_hw_gpio,
                                    amhw_zlg118_gpiomode_t  gpio_mode,
                                    int                     pin);


/**
 * @} amhw_zlg118_if_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG118_GPIO_H */

/* end of file */

#include "zsn603_platform.h"
#include "am_i2c.h"
#include "am_gpio.h"
#include "am_uart_rngbuf.h"
#include "am_delay.h"

/** \brief  ���ڴ��亯�� */
int zsn603_platform_uart_tx(zsn603_platform_uart_t *p_dev,
                            uint8_t                *p_data,
                            uint32_t                nbytes)
{
    if(am_uart_poll_send(p_dev->handle, p_data, nbytes) == nbytes){
        return 0;
    }else{
        return 1;
    }
}

/** \brief  ZSN603 �豸UART��ʽƽ̨��س�ʼ�� */
uint8_t  zsn603_platform_uart_init(zsn603_platform_uart_t                *p_dev,
                                   const zsn603_platform_uart_devinfo_t  *p_info,
                                   zsn603_uart_funcs_t                   *p_funcs,
                                   void                                  *p_arg)
{
    if(p_dev == NULL || p_info == NULL){
        return 1;
    }

    p_dev->p_devinfo = p_info;
    p_dev->handle    = p_info->pfn_handle_get();

    if(p_info->rst_pin != -1){
        //�����ڸ�λ����  ���ZSN603����Ӳ����λ
        am_gpio_pin_cfg(p_info->rst_pin, AM_GPIO_OUTPUT_INIT_HIGH);
        am_mdelay(10);
        am_gpio_pin_cfg(p_info->rst_pin, AM_GPIO_OUTPUT_INIT_LOW);
        am_mdelay(50);
    }

    am_uart_ioctl(p_dev->handle, AM_UART_MODE_SET, (void *)AM_UART_MODE_INT);
    am_uart_callback_set(p_dev->handle, AM_UART_CALLBACK_RXCHAR_PUT, p_funcs->zsn603_uart_rx, p_arg);
    am_uart_ioctl(p_dev->handle, AM_UART_BAUD_SET, (void *)p_info->baud_rate);

    /* ���������жϷ����� */
    am_gpio_trigger_connect(p_info->int_pin, p_funcs->zsn603_int_pin_cb, (void *)p_arg);
    /* ���������жϴ�����ʽ */
    am_gpio_trigger_cfg(p_info->int_pin, AM_GPIO_TRIGGER_FALL);
    /* ʹ�����Ŵ����ж� */
    am_gpio_trigger_on(p_info->int_pin);

    return 0;
}

/** \brief ZSN603ƽ̨����豸(UARTģʽ)���ʼ�� */
uint8_t  zsn603_platform_uart_deinit(zsn603_platform_uart_t    *p_dev)
{
    if(p_dev == NULL){
        return 1;
    }else{
        p_dev->p_devinfo->pfn_handle_deinit(p_dev->handle);
        return 0;
    }
}


/** \brief  I2Cд���� */
int zsn603_platform_i2c_write(zsn603_platform_i2c_t  *p_dev,
                              uint8_t                 slv_addr,
                              uint16_t                sub_addr,
                              uint8_t                *p_data,
                              uint32_t                nbytes)
{
    am_i2c_device_t i2c_dev;

    am_i2c_mkdev(&i2c_dev,
                  p_dev->handle,
                  slv_addr,
                  AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_2BYTE);

    return am_i2c_write(&i2c_dev,
                         sub_addr,
                        (const uint8_t *)p_data,
                         nbytes);

}
/** \brief I2C������ */
int zsn603_platform_i2c_read(zsn603_platform_i2c_t     *p_dev,
                             uint8_t                    slv_addr,
                             uint16_t                   sub_addr,
                             uint8_t                   *p_data,
                             uint32_t                   nbytes)
{
    am_i2c_device_t i2c_dev;
    am_i2c_mkdev(&i2c_dev,
                  p_dev->handle,
                  slv_addr,
                  AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_2BYTE);

    return am_i2c_read(&i2c_dev,
                       sub_addr,
                       p_data,
                       nbytes);
}

/** \brief  ZSN603 �豸I2C��ʽƽ̨��س�ʼ�� */
uint8_t  zsn603_platform_i2c_init(zsn603_platform_i2c_t                *p_dev,
                                  const zsn603_platform_i2c_devinfo_t  *p_info,
                                  void(*int_pin_callback_function)     (void *),
                                  void                                 *p_arg)
{
    if(p_dev == NULL || p_info == NULL){
        return 1;
    }

    p_dev->p_devinfo = p_info;

    p_dev->handle = p_info->pfn_handle_get();

    if(p_info->rst_pin != -1){
        //�����ڸ�λ����  ���ZSN603����Ӳ����λ
        am_gpio_pin_cfg(p_info->rst_pin, AM_GPIO_OUTPUT_INIT_HIGH);
        am_mdelay(10);
        am_gpio_pin_cfg(p_info->rst_pin, AM_GPIO_OUTPUT_INIT_LOW);
        am_mdelay(50);
    }

    /* ���������жϷ����� */
    am_gpio_trigger_connect(p_info->int_pin, int_pin_callback_function, (void *)p_arg);
    /* ���������жϴ�����ʽ */
    am_gpio_trigger_cfg(p_info->int_pin, AM_GPIO_TRIGGER_FALL);
    /* ʹ�����Ŵ����ж� */
    am_gpio_trigger_on(p_info->int_pin);

    return 0;
}

/** \brief ZSN603ƽ̨����豸(I2Cģʽ)���ʼ�� */
uint8_t  zsn603_platform_i2c_deinit(zsn603_platform_i2c_t    *p_dev)
{
    if(p_dev == NULL){
        return 1;
    }else{
        p_dev->p_devinfo->pfn_handle_deinit(p_dev->handle);
        return 0;
    }
}

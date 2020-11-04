
#include "ametal.h"
#include "am_stm32f103rbt6.h"
#include "stm32f103rbt6_pin.h"
#include "stm32f103rbt6_clk.h"
#include "am_clk.h"
#include "am_stm32f103rbt6_inst_init.h"
#include "am_baudrate_detect.h"
/**
 * \name �Զ������ʼ��궨��
 * @{
 */

/** \brief ��Ҫ�õ��Ķ�ʱ��λ�� */
#define     TIMER_WIDTH           16
static am_cap_handle_t            cap_handle;
/** @} */

/*******************************************************************************
 * �Զ������ʼ������
 ******************************************************************************/


/** \brief �Զ������ʵ�ƽ̨��ʼ�� */
void __stm32f103rbt6_plfm_autobaud_init (void)
{
    amhw_stm32f103rbt6_tim_prescale_set((amhw_stm32f103rbt6_tim_t *)STM32F103RBT6_TIM2_BASE, (uint16_t)8);
}

/** \brief �Զ������ʵ�ƽ̨���ʼ��  */
void __stm32f103rbt6_plfm_autobaud_deinit (void)
{
    am_stm32f103rbt6_tim1_cap_inst_deinit (cap_handle);
}

/** \brief �Զ������ʵ��豸��Ϣʵ�� */
static am_baudrate_detect_devinfo_t __g_stm32f103rbt6_baudrate_detect_devinfo = {
    PIOA_10,                           /**< \brief ���������� */
    2,                                 /**< \brief CAP����ͨ���� */
    TIMER_WIDTH,                       /**< \brief TIMER��ʱ��λ�� */
    10,                                /**< \brief ����һ�����ݵĳ�ʱʱ��(ms)*/
    AM_CAP_TRIGGER_FALL,          /**< \brief CAP���񴥷���ʽ */
    __stm32f103rbt6_plfm_autobaud_init,  /**< \brief ƽ̨��ʼ������ */
    __stm32f103rbt6_plfm_autobaud_deinit,/**< \brief ƽ̨���ʼ������ */
};

/** \brief �Զ������ʹ��ܵ��豸ʵ�� */
am_baudrate_detect_dev_t  __g_stm32f103rbt6_baudrate_detect_dev;

/** \brief ʵ����ʼ��������Զ������ʷ����� */
am_baudrate_detect_handle_t am_stm32f103rbt6_baudrate_detect_inst_init (void)
{
    cap_handle = am_stm32f103rbt6_tim1_cap_inst_init();

    return am_baudrate_detect_init(&__g_stm32f103rbt6_baudrate_detect_dev,
                                   &__g_stm32f103rbt6_baudrate_detect_devinfo,
                                    cap_handle);
}

/** \brief ʵ�����ʼ��*/
void am_stm32f103rbt6_baudrate_detect_inst_deinit(am_baudrate_detect_handle_t handle)
{
    am_baudrate_detect_deinit(handle);
}

/* end of file */

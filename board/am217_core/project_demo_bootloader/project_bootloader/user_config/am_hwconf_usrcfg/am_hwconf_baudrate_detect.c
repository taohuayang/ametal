#include "ametal.h"
#include "am_zlg217.h"
#include "zlg217_pin.h"
#include "zlg217_clk.h"
#include "am_clk.h"
#include "am_zlg217_inst_init.h"
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
void __zlg217_plfm_baudrate_detect_init (void)
{
    /* Ԥ��ƵֵԽ�ͣ������׼����͵Ĳ����ʣ��෴Ԥ��Ƶֵ�ߣ��ܹ������ߵĲ����� */
    amhw_zlg_tim_prescale_set((amhw_zlg_tim_t *)ZLG217_TIM2_BASE, (uint16_t)8);
}

/** \brief �Զ������ʵ�ƽ̨���ʼ��  */
void __zlg217_plfm_baudrate_detect_deinit (void)
{
    am_zlg217_tim1_cap_inst_deinit (cap_handle);
}

/** \brief �Զ������ʵ��豸��Ϣʵ�� */
static am_baudrate_detect_devinfo_t __g_zlg217_baudrate_detect_devinfo = {
    PIOA_10,                            /**< \brief ���������� */
    2,                                 /**< \brief CAP����ͨ���� */
    TIMER_WIDTH,                       /**< \brief TIMER��ʱ��λ�� */
    10,                                /**< \brief ����һ�����ݵĳ�ʱʱ��(ms)*/
    AM_CAP_TRIGGER_BOTH_EDGES,               /**< \brief CAP���񴥷���ʽ */
    __zlg217_plfm_baudrate_detect_init,  /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_baudrate_detect_deinit,/**< \brief ƽ̨���ʼ������ */
};

/** \brief �Զ������ʹ��ܵ��豸ʵ�� */
am_baudrate_detect_dev_t  __g_zlg217_baudrate_detect_dev;

/** \brief ʵ����ʼ��������Զ������ʷ����� */
am_baudrate_detect_handle_t am_zlg217_baudrate_detect_inst_init (void)
{
    cap_handle = am_zlg217_tim1_cap_inst_init();

    return am_baudrate_detect_init(&__g_zlg217_baudrate_detect_dev,
                                   &__g_zlg217_baudrate_detect_devinfo,
                                    cap_handle);
}

/** \brief ʵ�����ʼ��*/
void am_zlg217_baudrate_detect_inst_deinit(am_baudrate_detect_handle_t handle)
{
    am_baudrate_detect_deinit(handle);
}

/* end of file */

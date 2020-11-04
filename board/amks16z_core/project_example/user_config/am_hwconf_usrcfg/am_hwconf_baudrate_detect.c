#include "ametal.h"
#include "am_kl26.h"
#include "kl26_pin.h"
#include "kl26_clk.h"
#include "am_clk.h"
#include "am_kl26_inst_init.h"
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
void __kl26_plfm_baudrate_detect_init (void)
{
    /* Ԥ��ƵֵԽ�ͣ������׼����͵Ĳ����ʣ��෴Ԥ��Ƶֵ�ߣ��ܹ������ߵĲ����� */
    amhw_fsl_tpm_prescale_set(KL26_TPM0, AMHW_FSL_TPM_DIVIDED_BY_4);
}

/** \brief �Զ������ʵ�ƽ̨���ʼ��  */
void __kl26_plfm_baudrate_detect_deinit (void)
{
    am_kl26_tpm0_cap_inst_deinit (cap_handle);
}

/** \brief �Զ������ʵ��豸��Ϣʵ�� */
static am_baudrate_detect_devinfo_t __g_kl26_baudrate_detect_devinfo = {
    PIOD_4,                            /**< \brief ���������� */
    4,                                 /**< \brief CAP����ͨ���� */
    TIMER_WIDTH,                       /**< \brief TIMER��ʱ��λ�� */
    10,                                /**< \brief ����һ�����ݵĳ�ʱʱ��(ms)*/
    AM_CAP_TRIGGER_BOTH_EDGES,               /**< \brief CAP���񴥷���ʽ */
    __kl26_plfm_baudrate_detect_init,  /**< \brief ƽ̨��ʼ������ */
    __kl26_plfm_baudrate_detect_deinit,/**< \brief ƽ̨���ʼ������ */
};

/** \brief �Զ������ʹ��ܵ��豸ʵ�� */
am_baudrate_detect_dev_t  __g_kl26_baudrate_detect_dev;

/** \brief ʵ����ʼ��������Զ������ʷ����� */
am_baudrate_detect_handle_t am_kl26_baudrate_detect_inst_init (void)
{
    cap_handle = am_kl26_tpm0_cap_inst_init();

    return am_baudrate_detect_init(&__g_kl26_baudrate_detect_dev,
                                   &__g_kl26_baudrate_detect_devinfo,
                                    cap_handle);
}

/** \brief ʵ�����ʼ��*/
void am_kl26_baudrate_detect_inst_deinit(am_baudrate_detect_handle_t handle)
{
    am_baudrate_detect_deinit(handle);
}

/* end of file */

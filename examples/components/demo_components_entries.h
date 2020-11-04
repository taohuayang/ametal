/*******************************************************************************
                             AMetal
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
 * \brief components �������̺����������
 * \sa    demo_components_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 18-07-30  pea, first implementation
 * \endinternal
 */

#ifndef __DEMO_COMPONENTS_ENTRIES_H
#define __DEMO_COMPONENTS_ENTRIES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_ftl.h"
#include "am_mtd.h"
#include "am_mx25xx.h"
#include "am_ep24cxx.h"
#include "am_fm175xx.h"
#include "am_fm25clxx.h"
#include "am_zm516x.h"
#include "am_zlg9021.h"
#include "am_zlg52810.h"
#include "am_mk100.h"
#include "am_gs200.h"
#include "am_rs200.h"
#include "zsn603.h"
#include "am_xmodem.h"
#include "am_baudrate_detect.h"
#include "am_iso7816.h"
#include "am_fmse_a03.h"
/**
 * \brief EP24CXX ��������
 *
 * \param[in] ep24cxx_handle EP24CXX ��׼������
 * \param[in] test_lenth     �����ֽ���
 *
 * \return ��
 */
void demo_ep24cxx_entry (am_ep24cxx_handle_t ep24cxx_handle, int32_t test_lenth);

/**
 * \brief  MX25XX���� ����
 *
 * \param[in] mx25xx_handle  MX25XX ��׼������
 * \param[in] test_lenth     �����ֽ���
 *
 * \return ��
 */
void demo_mx25xx_entry (am_mx25xx_handle_t mx25xx_handle, int32_t test_lenth);

/**
 * \brief FTL ����
 *
 * \param[in] ftl_handle     FTL ��׼������
 * \param[in] test_lenth     �����ֽ���
 *
 * \return ��
 */
void demo_ftl_entry (am_ftl_handle_t ftl_handle, int32_t test_lenth);

/**
 * \brief MTD ����
 *
 * \param[in] mtd_handle  MTD ��׼������
 * \param[in] test_lenth  �����ֽ���
 *
 * \return ��
 */
void demo_mtd_entry (am_mtd_handle_t mtd_handle, int32_t test_lenth);

/**
 * \brief FM175XX ��CPU������
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_cpu_card (am_fm175xx_handle_t handle);

/**
 * \brief FM175XX ��A���Ϳ�����
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_picca_read_id (am_fm175xx_handle_t handle);

/**
 * \brief A�࿨�����߿�����
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_picca_halt (am_fm175xx_handle_t handle);

/**
 * \brief A�࿨��������
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_picca_read_block (am_fm175xx_handle_t handle);

/**
 * \brief A�࿨ֵ��������
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_picca_val_operate (am_fm175xx_handle_t handle);

/**
 * \brief A��д������
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_picca_write_block (am_fm175xx_handle_t handle);

/**
 * \brief B�࿨����������
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_piccb_read_id (am_fm175xx_handle_t handle);

/**
 * \brief FM175XX LPCDģʽ����
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_picca_lpcd_mode (am_fm175xx_handle_t handle);
/**
 * \brief FM175XX FM11RF005M����������
 * \param[in] handle  FM175XX ������
 * \return ��
 */
void demo_fm175xx_fm11rf005m_operate (am_fm175xx_handle_t handle);

/**
 * \brief zm516x ģ���Զ�����������
 * \param[in] handle  zm516x ������
 * \return ��
 */
void demo_zm516x_baudrate_entry (am_zm516x_handle_t handle);

/**
 * \brief zm516x ģ�� GPIO ����
 * \param[in] handle  zm516x ������
 * \return ��
 */
void demo_zm516x_gpio_entry (am_zm516x_handle_t handle);

/**
 * \brief zm516x ģ�� KEY LED ����
 * \param[in] handle  zm516x ������
 * \return ��
 */
void demo_zm516x_key_led_entry (am_zm516x_handle_t handle);

/**
 * \brief zm516x ģ����������
 * \param[in] handle  zm516x ������
 * \return ��
 */
void demo_zm516x_network_entry (am_zm516x_handle_t handle);

/**
 * \brief zm516x ģ����������
 * \param[in] handle  zm516x ������
 * \return ��
 */
void demo_zm516x_search_entry (am_zm516x_handle_t handle);

/**
 * \brief zm516x ģ����ʾ����
 * \param[in] handle  zm516x ������
 * \return ��
 */
void demo_zm516x_entry (am_zm516x_handle_t handle);

/**
 * \brief zlg9021 ����ģ���Զ�����������
 * \param[in] handle  zlg9021 ������
 * \return ��
 */
void demo_zlg9021_baudrate_entry (am_zlg9021_handle_t zlg9021_handle);

/**
 * \brief zlg9021 ����ģ�� LED ����
 * \param[in] handle  zlg9021 ������
 * \return ��
 */
void demo_zlg9021_led_entry (am_zlg9021_handle_t zlg9021_handle);

/**
 * \brief zlg52810 ����ģ���Զ�����������
 * \param[in] handle  zlg52810 ������
 * \return ��
 */
void demo_zlg52810_baudrate_entry (am_zlg52810_handle_t zlg52810_handle);
/**
 * \brief EEPROM����
 * \param[in] ��
 * \return ��
 */
void demo_am845_core_eeprom_entry (void);

/**
 * \brief FM25CLxx����
 * \param[in] handle  FM25CLxx ������
 * \return ��
 */
void demo_fm25clxx_entry(am_fm25clxx_handle_t fm25clxx_handle, int32_t test_lenth);

/**
 * \brief  ZSN603  LED����ʵ������
 *
 * \param[in] handle      : ZSN603�豸������
 * \retval  no : �޷���ֵ
 */
void demo_zsn603_led_test_entry (zsn603_handle_t handle);

/**
 * \brief  ZSN603  A�࿨��������
 *
 * \param[in] handle      : ZSN603�豸������
 * \retval  no : �޷���ֵ
 */
void demo_zsn603_picca_active_test_entry (zsn603_handle_t handle);

/**
 * \brief  ZSN603  B�࿨��������
 *
 * \param[in] handle      : ZSN603�豸������
 * \retval  no : �޷���ֵ
 */
void demo_zsn603_piccb_active_test_entry (zsn603_handle_t handle);

/**
 * \brief  ZSN603  �Զ����ģʽ����
 *
 * \param[in] handle      : ZSN603�豸������
 * \retval  no : �޷���ֵ
 */
void demo_zsn603_auto_detect_test_entry(zsn603_handle_t handle);

/**
 * \brief xmodem��������
 * \param[in] handle  xmodem���շ�����
 * \return ��
 */
void demo_xmodem_rec_entry (am_xmodem_rec_handle_t  handle);

/**
 * \brief xmodem��������
 * \param[in] handle  xmodem���ͷ�����
 * \return ��
 */
void  demo_xmodem_tx_entry (am_xmodem_tx_handle_t  handle);

/**
 * \brief ���ڲ����ʼ������
 *
 * \param[in] baudrate_handle  �����ʼ�������
 * \param[in] uart_handle      ���ڷ�����
 *
 * \return ��
 */
void demo_uart_auto_baudrate_entry (am_baudrate_detect_handle_t baudrate_handle,
                                    am_uart_handle_t            uart_handle);

/**
 * \brief MK100����
 * \param[in] handle  MK100 ������
 * \return ��
 */
void demo_mk100_entry(am_mk100_handle_t handle);

/**
 * \brief GS200 ģ�����ò���������
 * \param[in] handle  GS200�豸������
 * \return ��
 */
void demo_gs200_baudrate_entry (am_gs200_handle_t gs200_handle,uint32_t gs200_baudrate);

/**
 * \brief RS200 ģ������
 * \param[in] handle  RS200�豸������
 * \return ��
 */
void demo_rs200_entry (am_rs200_handle_t handle);

/**
 * \brief ISO7816 �Ӵ�ʽ������
 * \param[in] iso7816_handle  ISO7816�豸������
 * \return ��
 */
void demo_iso7816_entry(am_iso7816_handle_t iso7816_handle);

/**
 * \brief FMSE-A03 �����ƶ�д��������
 * \param[in] handle�� FMSE��׼������
 * \return ��
 */
void demo_fmse_binary_rw_test_entry (am_fmse_handle_t handle);

/**
 * \brief FMSE-A03 �����������
 * \param[in] handle�� FMSE��׼������
 * \return ��
 */
void demo_fmse_cmd_test_entry (am_fmse_handle_t handle);

/**
 * \brief FMSE-A03 ����ѹ������
 * \param[in] handle�� FMSE��׼������
 * \return ��
 */
void demo_fmse_data_compress_test_entry (am_fmse_handle_t handle);

/**
 * \brief FMSE-A03 �ӽ��ܲ�������
 * \param[in] handle�� FMSE��׼������
 * \return ��
 */
void demo_fmse_data_encrypt_and_decrypt_entry (am_fmse_handle_t handle);

/**
 * \brief FMSE-A03 ECC��������
 * \param[in] handle�� FMSE��׼������
 * \return ��
 */
void demo_fmse_ecc_calc_test_entry (am_fmse_handle_t handle);

/**
 * \brief FMSE-A03 ��Կ����������
 * \param[in] handle�� FMSE��׼������
 * \param[in] mode  �� ����ģʽ  0��1024RSA   1��2048RSA   2��SM2
 * \return ��
 */
void demo_fmse_gen_key_pair_entry (am_fmse_handle_t handle, uint8_t mode);

/**
 * \brief FMSE-A03 RSA��������
 * \param[in] handle�� FMSE��׼������
 * \return ��
 */
void demo_fmse_rsa_load_test_entry (am_fmse_handle_t  handle);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_COMPONENTS_ENTRIES_H */

/* end of file */

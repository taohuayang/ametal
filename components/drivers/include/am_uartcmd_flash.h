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
 * \brief 
 *
 * \internal
 * \par Modification History
 * - 1.00 15-09-  win, first implementation.
 * \endinternal
 */
#ifndef __AM_UARTCMD_FLASH_H
#define __AM_UARTCMD_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_uartcmd_comm.h"
#include "am_uartcmd_flash_define.h"

#pragma pack(1)
typedef struct uartcmd_auto_detest_info {

    /**
     * \brief ��Ƭ����
     *        - RC_CARD_TYPE_MF1       -- Mifare S50/70��
     *        - RC_CARD_TYPE_PLUS      -- PLUS CPU��
     *        - RC_CARD_TYPE_FM1208    -- FM1208 CPU��
     *        - RC_CARD_TYPE_FM12AG08  -- FM12AG08 ����CPU��
     *        - RC_CARD_TYPE_ISO14443A -- ISO14443 TypeA
     *        - RC_CARD_TYPE_ISO14443B -- ISO14443 TypeB
     *        - RC_CARD_TYPE_ISO115693 -- ISO115693
     *        - RC_CARD_TYPE_ISO7816_3 -- ISO7816_3
     */
    uint8_t card_type;

    /**
     * \brief �Զ����ģʽ
     *        - nMode.4:7    -- ����������д1
     *        - nMode.3      -- �Ƿ�ִ��Halt()����
     *        - 0            -- �޶���
     *        - 1            -- ִ��Halt()
     *        - nMode.2      -- ������Ƿ�������
     *        - 0            -- ���������
     *        - 1            -- �������
     *        - nMode.1      -- ��⵽��ʱ���Ƿ�����ж��ź�
     *        - 0            -- �������ж�
     *        - 1            -- �����ж�(���ݷ��ͽ�������ʧ;I2C�յ�������ַ����ʧ)
     *        - nMode.0      -- ���ݷ���ģʽ
     *        - 0            -- ���ڲ�����
     *        - 1            -- ������������
     */
    uint8_t mode;

    /**
     * \brief ����ģʽ
     *        - nTxMode.2:7   -- ����������д1
     *        - nTxMode.0:1   -- ��������ģʽ
     *        - 00            -- TX1��TX2 ��������
     *        - 01            -- ��TX1 ����
     *        - 10            -- ��TX2 ����
     *        - 11            -- TX1��TX2 ͬʱ����
     * */
    uint8_t tx_mode;

    /**
     * \brief �������
     *         - 0x26      -- IDLE(TypeA)
     *         - 0x52      -- ALL(TypeA)
     *         - 0x00      -- IDLE(TypeB)
     *         - 0x08      -- ALL(TypeB)
     */
    uint8_t req_code;

    /**
     * \brief �ⲿ��֤����Ƭ��ȡ����Ȩ�ޣ�ģʽ
     *        - AuthMode.7              -- ��Կ��Դ
     *        - 0                       -- �ⲿ������Կ
     *        - 1                       -- �ڲ���Կ
     *        - AuthMode.0:6            -- ��Կ���ͻ��㷨��ʶ
     *        - RC_ALGORITHM_CRYPTO1_A  -- Mifaer Crypto1 ��ԿA
     *        - RC_ALGORITHM_CRYPTO1_B  -- Mifaer Crypto1 ��ԿB
     *        - RC_ALGORITHM_3_DES      -- 3-DES
     *        - RC_ALGORITHM_1_DES      -- 1-DES
     *        - RC_ALGORITHM_SM1        -- SM1
     *        - RC_ALGORITHM_NO         -- ����֤
     *        - ����                                         -- ��������ʹ��
     * */
    uint8_t auth_mode;

    /**
     * \brief �ⲿ��֤ʱ��Ӧ��Ƭ��KID��������CPU����
     */
    uint8_t ext_auth_kid;

    /**
     * \brief �ڲ���֤����֤�Ƿ��Ǳ�ϵͳ�Ŀ���ģʽ����nExAuthMode
     */
    uint8_t inter_auth_mode;

    /**
     * \brief �ⲿ��֤ʱ��Ӧ��Ƭ��KID��������CPU����
     */
    uint8_t inter_auth_kid;

    /**
     * \brief �ⲿ��֤��Կ(�ڲ�E2/PSAM��Կ����1�ֽ�Ϊ��Կ�������)
     */
    uint8_t ext_auth_key[16];

    /**
     * \brief �ڲ���֤��Կ(�ڲ�E2/PSAM��Կ����1�ֽ�Ϊ��Կ�������)
     */
    uint8_t inter_auth_key[16];

    /** \brief Ӧ�õ�FID��������CPU����*/
    uint16_t app_fid;

    /** \brief ����ģʽ��������*/
    uint8_t ctrl_mode;

    /** \brief �û��������ļ���SFI��������CPU���� */
    uint8_t sfi_cfg_file;

    /** \brief Ӧ�����ݴ���ļ���SFI ���������ݿ�Ŀ�� */
    uint8_t app_sfi;

    /** \brief Ӧ�����ݴ�ŵ�ƫ���� */
    uint8_t app_offset;

    /** \brief Ӧ�����ݵĳ��� */
    uint8_t app_bytes;

    /**
     * \brief �������ģʽ
     *        - nDataOutMode.7                   -- ��С��ģʽ
     *           - RC_LITTLE_ENDIAN              -- С��ģʽ
     *           - RC_BIG_ENDIAN                 -- ���ģʽ
     *        - nDataOutMode.4:6                 -- ���ݴ���ģʽ
     *           - DATA_OUTPUT_PROCESS_NO        -- ������
     *           - DATA_OUTPUT_PROCESS_SEGMENT   -- �ֶ�
     *           - DATA_OUTPUT_PROCESS_CROSS     -- ����
     *        - nDataOutMode.0:3                 -- ���ݼ���ģʽ
     *           - DATA_OUTPUT_ENCRYPT_NO        -- ������
     *           - DATA_OUTPUT_ENCRYPT_1_DES     -- 1-DES
     *           - DATA_OUTPUT_ENCRYPT_3_DES     -- 3-DES
     *           - DATA_OUTPUT_ENCRYPT_SM1       -- SM1
     *           - DATA_OUTPUT_ENCRYPT_ROLLCODE  -- ����
     *           - DATA_OUTPUT_ENCRYPT_RC5       -- RC5
     *           - DATA_OUTPUT_ENCRYPT_AES       -- AES ����
     */
    uint8_t data_output_mode;

} uartcmd_auto_detest_info_t;

typedef struct uartcmd_config_info {

    /** \brief ������ϢУ��� */
    uint16_t    check_sum;

    /** \brief ��¼����ʼ��ַ */
    uint16_t    record_addr;

    /** \brief ��Ʒ�̼��汾 */
    char        version[UARTCMD_FLASH_VERSION_SIZE];

    /** \brief ���к� */
    char        serial_num[UARTCMD_FLASH_SN_SIZE];

    /** \brief ģ���ַ����I2C��ַ��ͬ��*/
    uint8_t     module_addr;

    /**
     * \brief �����ʱ��
     *        - RC_BAUD_230400    -- 230400bps
     *        - RC_BAUD_172800    -- 172800bps
     *        - RC_BAUD_115200    -- 115200bps
     *        - RC_BAUD_57600     -- 57600bps
     *        - RC_BAUD_38400     -- 38400bps
     *        - RC_BAUD_28800     -- 28800bps
     *        - RC_BAUD_19200     -- 19200bps
     *        - RC_BAUD_9600      -- 9600bps
     */
    uint8_t     baud_num;

    /**
     * \brief ����ģʽ
     *        - workMode.4:7                    -- ����ģʽ
     *          - WORK_MODE_SLAVE               -- �ӻ�ģʽ
     *          - WORK_MODE_AUTO_DETEST         -- �Զ����ģʽ
     *        - workMode.0:3                    -- ͨ��ģʽ
     *          - COMM_AUTO_DETEST              -- �Զ����ģʽ
     *          - COMM_IIC                      -- IICͨ��
     *          - COMM_UART                     -- UARTͨ��
     *          - COMM_UART_DEFAULT_BAUD_RATE   -- UARTͨ��(�����ʹ̶�Ϊ19200)
     *          - COMM_UART_LAST_BAUD_RATE      -- UARTͨ��(�����ʹ̶�Ϊ�ϴ����õĲ�����)
     *          - COMM_WG                       -- WGͨ��
     */
    uint8_t     work_mode;

    /**
     * \brief ֡��ʽ
     *        - RC_FRAME_FORMAT_OLD       -- ��֡��ʽ
     *        - RC_FRAME_FORMAT_NEW       -- ��֡��ʽ
     */
    uint8_t     frame_format;

    /** \brief Τ��λ�� */
    uint16_t    wiegang_bits;

    /** \brief Τ������ */
    uint8_t     wiegang_period;

    /** \brief Τ�������� */
    uint8_t     wiegang_pulse_width;

    /** \brief �Զ����������Ϣ */
    uartcmd_auto_detest_info_t auto_cfg;

    /** \brief ���Լ�¼ */
    uint8_t     test_record[UARTCMD_RECORD_SIZE];

    /** \brief �û���Կ */
    uint8_t     user_key[2][16];

} uartcmd_config_info_t;

/**
 * \brief UARTCMD �̼���Ϣ
 */
typedef struct uartcmd_flash_devinfo {
    uartcmd_config_info_t info;
    uint8_t               user_data[UARTCMD_FLASH_USER_MEM_SIZE];
    uint8_t               ic_card_key[16][32];
} uartcmd_flash_devinfo_t;

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif /* __UARTCMD_FLASH_H */

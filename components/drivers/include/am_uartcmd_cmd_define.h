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
 * - 1.00 15-11-17  win, first implementation.
 * \endinternal
 */
#ifndef __AM_UARTCMD_CMD_DEFINE_H
#define __AM_UARTCMD_CMD_DEFINE_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief 0 -- �ӻ�ģʽ�� ���� -- ����ģʽ */
#define UARTCMD_CMD_MST_MODE            0

/** \brief 0 -- ����֡�а�ȫ����������Ч�� ���� -- ��Ч */
#define UARTCMD_CMD_SM_ENABLE           0

#define UARTCMD_CMD_GENERAL_ADDR        0x00     /**< \brief ͨ�õ�ַ(ͬI2C��ַ) */
#define UARTCMD_CMD_DEFAULT_ADDR        0xB2     /**< \brief Ĭ�ϵ�ַ0xB2 */
#define UARTCMD_CMD_ADDR_MASK           0xFE     /**< \brief ��ַ����(ͬI2C��ַ) */

/**
 * \brief ��д��������
 */
typedef enum uartcmd_cmd_class {
    UARTCMD_CMD_CLASS_MANUFACTURER    = 0x00,  /**< \brief �������������������û����ţ� */
    UARTCMD_CMD_CLASS_DEVICE          = 0x01,  /**< \brief �豸���������� */
    UARTCMD_CMD_CLASS_MIFARE          = 0x02,  /**< \brief MIFARE ��������(����USI14443-3A) */
    UARTCMD_CMD_CLASS_ISO7816_3       = 0x05,  /**< \brief ISO7816-3 */
    UARTCMD_CMD_CLASS_ISO14443        = 0x06,  /**< \brief ISO14443��PICC�������� */
    UARTCMD_CMD_CLASS_PLUS_CPU        = 0x07,  /**< \brief PLUS CPU �������� */
    UARTCMD_CMD_CLASS_ISO15693        = 0x08,  /**< \brief ISO15693��VICC�������� */
    UARTCMD_CMD_CLASS_ISO18K6C        = 0x09,  /**< \brief ISO18000-6C */
    UARTCMD_CMD_CLASS_ISO18092        = 0x0A,  /**< \biref ISO18092(NFCIP-1) */
    UARTCMD_CMD_CLASS_SGIDC           = 0x0B,  /**< \brief �������֤������ */

    UARTCMD_CMD_CLASS_COMM            = 0xFF   /**< \brief ģ��ͨ���� */
} uartcmd_cmd_class_t;

/**
 * \brief ���������������
 */
typedef enum uartcmd_cmd_manu {
    UARTCMD_CMD_CODE_GET_DEVICE_BASIC_INFO   = ' ',  /**< \brief  0x20 ���豸������Ϣ */
    UARTCMD_CMD_CODE_GET_PRODUCTION_INFO     = '!',  /**< \brief 0x21 ��������Ϣ */
    UARTCMD_CMD_CODE_GET_TEST_RECORD         = '"',  /**< \brief 0x22 �����Լ�¼ */
    UARTCMD_CMD_CODE_WRITE_PRODUCTION_INFO   = '#',  /**< \brief 0x23 д������Ϣ */
    UARTCMD_CMD_CODE_WRITE_TEST_RECORD       = '$',  /**< \brief 0x24 д���Լ�¼ */
    UARTCMD_CMD_CODE_ERASE_TEST_RECORD       = '%',  /**< \brief 0x25 �������Լ�¼ */
    UARTCMD_CMD_CODE_MANUFACTURER_AUTH       = '*',  /**< \brief 0x2A ��֤������Կ */
    UARTCMD_CMD_CODE_UPDTAE                  = '+'   /**< \brief 0x2B ���� */
} uartcmd_cmd_manu_t;

/**
 * \brief �豸�������������
 */
typedef enum uartcmd_cmd_code_dev_ctrl {

    /** \brief 0x41 ��ȡ�豸��Ϣ */
    UARTCMD_CMD_CODE_GET_DEVICE_INFO            = 'A',

    /** \brief 0x42 ����IC ���ӿ� */
    UARTCMD_CMD_CODE_CONFIG_ICC_INTERFACE       = 'B',

    /** \brief 0x43 �ر�IC ���ӿ� */
    UARTCMD_CMD_CODE_CLOSE_ICC_INTERFACE        = 'C',

    /** \brief 0x44 ����IC ���ӿ�Э�飨����ģʽ�� */
    UARTCMD_CMD_CODE_SET_ICC_INTERFACE_PROTOCOL = 'D',

    /** \brief 0x45 װ��IC ����Կ */
    UARTCMD_CMD_CODE_LOAD_ICC_KEY               = 'E',

    /** \brief 0x46 ����IC ���ӿڵļĴ���ֵ */
    UARTCMD_CMD_CODE_SET_ICC_INTERFACE_REG      = 'F',

    /** \brief 0x47 ��ȡIC ���ӿڵļĴ���ֵ */
    UARTCMD_CMD_CODE_GET_ICC_INTERFACE_REG      = 'G',

    /** \brief 0x48 ���ò����� */
    UARTCMD_CMD_CODE_SET_BAUD_RATE              = 'H',

    /** \brief 0x49 ����IC ���ӿڵ�������ʽ����T(X1��Tx2��������ʽ) */
    UARTCMD_CMD_CODE_SET_ICC_INTERFACE_OUTPUT   = 'I',

    /** \brief 0x4A ����I/O */
    UARTCMD_CMD_CODE_SET_IO                     = 'J',

    /** \brief 0x4B �����¾�֡��ʽ */
    //UARTCMD_CMD_CODE_SET_FRAME_FORMAT           = 'K',

    /** \brief 0x4D ��ȡI/O ״̬ */
    UARTCMD_CMD_CODE_GET_IO                     = 'M',

    /** \brief 0x4F ���õ�ǰ������IC���ӿ� */
    UARTCMD_CMD_CODE_SET_CUR_ICC_INTERFACE      = 'O',

    /** \brief 0x50 ��ȡ��ǰ������IC���ӿ� */
    UARTCMD_CMD_CODE_GET_CUR_ICC_INTERFACE      = 'P',

    /** \brief 0x52 IC ���ӿڸ�λ */
    UARTCMD_CMD_CODE_ICC_INTERFACE_RESET        = 'R',

    /** \brief 0x53 ���ݿ齻�� �뿨��������ǩ�������ݽ��� */
    UARTCMD_CMD_CODE_EXCHANGE_BLOCK             = 'S',

    /** \brief 0x55 �����豸����ģʽ */
    //UARTCMD_CMD_CODE_SET_DEVICE_MODE            = 'U',

    /** \brief 0x56 ��ȡ�豸����ģʽ */
    //UARTCMD_CMD_CODE_GET_DEVICE_MODE            = 'V',

    /** \brief 0x56 ��ȡ�Զ����Ļ�Ӧ(��Ҫ������) */
    UARTCMD_CMD_CODE_GET_AUTO_DECTECT_RESPONSE  = 'W',

    /** \brief 0x58 �û���֤������(��Ϊ������֤��������֤) */
    UARTCMD_CMD_CODE_USER_AUTH                  = 'Y',

    /** \brief 0x61 װ���û���Կ    ��֤ģ����Կ��ͨѶ������Կ */
    UARTCMD_CMD_CODE_LOAD_USER_KEY              = 'a',

    /** \brief 0x62 ��EEPROM */
    UARTCMD_CMD_CODE_READ_E2                    = 'b',

    /** \brief 0x63 дEEPROM */
    UARTCMD_CMD_CODE_WRITE_E2                   = 'c',

    /** \brief ��ȡ����оƬ��λ���� */
    //UARTCMD_CMD_CODE_GET_RESET_COUNT            = 'd',
    
    /** \brief ѡ������ */
    UARTCMD_CMD_CODE_ANTE_SELECT                = 'e',

} uartcmd_cmd_code_dev_ctrl_t;

/**
 * \brief Mifare����MF0/1�����������
 */
typedef enum uartcmd_cmd_code_mifare {
    UARTCMD_CMD_CODE_MF_REQUEST           = 'A', /**< \brief 0x41 ���� */
    UARTCMD_CMD_CODE_MF_ANTICOLL          = 'B', /**< \brief 0x42 ����ײ */
    UARTCMD_CMD_CODE_MF_SELECT            = 'C', /**< \brief 0x43 ѡ�� */
    UARTCMD_CMD_CODE_MF_HALT              = 'D', /**< \brief 0x44 ������ */
    UARTCMD_CMD_CODE_MF_AUTH_E2           = 'E', /**< \brief 0x45 ֤ʵE2��Կ��֤ */
    UARTCMD_CMD_CODE_MF_AUTH_KEY          = 'F', /**< \brief 0x46 ֤ʵֱ����Կ��֤ */
    UARTCMD_CMD_CODE_MF_READ              = 'G', /**< \brief 0x47 �� */
    UARTCMD_CMD_CODE_MF_WRITE             = 'H', /**< \brief 0x48 д */
    UARTCMD_CMD_CODE_MF0_WRITE            = 'I', /**< \brief 0x49 дUltraLight */
    UARTCMD_CMD_CODE_MF_VALUE             = 'J', /**< \brief 0x4A ֵ���� */
    UARTCMD_CMD_CODE_MF_RESET             = 'L', /**< \brief 0x4C ����λ */
    UARTCMD_CMD_CODE_MF_ACTIVE            = 'M', /**< \brief 0x4D ������ */
    UARTCMD_CMD_CODE_MF_AUTO_DETECT       = 'N', /**< \brief 0x4E �Զ���� */
    UARTCMD_CMD_CODE_MF_GET_AUTO_DETECT   = 'O', /**< \brief 0x4F ���Զ�������� */
    UARTCMD_CMD_CODE_MF_SET_VALUE         = 'P', /**< \brief 0x50 ����ֵ���ֵ */
    UARTCMD_CMD_CODE_MF_GET_VALUE         = 'Q', /**< \brief 0x51 ��ȡֵ���ֵ */
    UARTCMD_CMD_CODE_EXCHANGE_BLOCK1      = 'X', /**< \brief 0x58 ���ݽ������� */
    UARTCMD_CMD_CODE_MF0_EXTEND           = 'S'  /**< \brief MF0��Ƭ��PCD֮�����ݽ�����չ���� */
} uartcmd_cmd_code_mifare_t;

/**
 * \brief ISO7816-3 Э�����������
 */
typedef enum uartcmd_cmd_code_iso7816_3 {
    UARTCMD_CMD_CODE_CICC_RESET         = 'A', /**< \brief 0x41 �Ӵ�ʽIC����λ(�Զ�����PPS) */
    UARTCMD_CMD_CODE_CICC_TPDU          = 'B', /**< \brief 0x42 �Ӵ�ʽIC������Э�飨�Զ�����T=0��T=1Э�飩*/
    UARTCMD_CMD_CODE_CICC_COLD_RESET    = 'C', /**< \brief 0x43 �Ӵ�ʽIC���临λ */
    UARTCMD_CMD_CODE_CICC_WARM_RESET    = 'D', /**< \brief 0x44 �Ӵ�ʽIC���ȸ�λ */
    UARTCMD_CMD_CODE_CICC_DEACTIVATION  = 'E', /**< \brief 0x45 �Ӵ�ʽIC��ͣ��رյ�Դ��ʱ�ӣ�*/
    UARTCMD_CMD_CODE_CICC_PPS           = 'F', /**< \brief 0x46 �Ӵ�ʽIC��PPS(����Э��Э��) */
    UARTCMD_CMD_CODE_CICC_TP0           = 'G', /**< \brief 0x47 �Ӵ�ʽIC��T=0����Э�� */
    UARTCMD_CMD_CODE_CICC_TP1           = 'H', /**< \brief 0x48 �Ӵ�ʽIC��T=1����Э�� */
} uartcmd_cmd_code_iso7816_3_t;


/**
 * \brief ISO14443Э�����������
 */
typedef enum uartcmd_cmd_code_iso14443 {
    UARTCMD_CMD_CODE_PICCA_REQUEST          = 'A',  /**< \brief 0x41 A�Ϳ����� */
    UARTCMD_CMD_CODE_PICCA_ANTICOLL         = 'B',  /**< \brief 0x42 A�Ϳ�����ײ */
    UARTCMD_CMD_CODE_PICCA_SELECT           = 'C',  /**< \brief 0x43 A�Ϳ�ѡ�� */
    UARTCMD_CMD_CODE_PICCA_HALT             = 'D',  /**< \brief 0x44 A�Ϳ����� */
    UARTCMD_CMD_CODE_PICCA_RATS             = 'E',  /**< \brief 0x45 A�Ϳ�RATS */
    UARTCMD_CMD_CODE_PICCA_PPS              = 'F',  /**< \brief 0x46 A�Ϳ�PPS */
    UARTCMD_CMD_CODE_PICC_DESELECT          = 'G',  /**< \brief 0x47 DESELECT */
    UARTCMD_CMD_CODE_PICC_TPCL              = 'H',  /**< \brief 0x48 T=CL */
    UARTCMD_CMD_CODE_PICC_EXCHANGE_BLOCK2   = 'J',  /**< \brief 0x4B ���ݽ��� */

    /** \brief 0x4C A�Ϳ���λ����֧��ISO14443-4, ���Զ�ִ��RATS��*/
    UARTCMD_CMD_CODE_PICCA_RESET            = 'L',

    UARTCMD_CMD_CODE_PICCA_ACTIVE           = 'M',  /**< \brief 0x4D A�Ϳ����� */
    UARTCMD_CMD_CODE_PICCB_ACTIVE           = 'N',  /**< \brief 0x4E B�Ϳ����� */
    UARTCMD_CMD_CODE_PICCB_RESET            = 'O',  /**< \brief 0x4F B�Ϳ���λ��ִ��ATTRIB�� */
    UARTCMD_CMD_CODE_PICCB_REQUEST          = 'P',  /**< \brief 0x50 B�Ϳ����� */
    UARTCMD_CMD_CODE_PICCB_SLOT_MARKER      = 'Q',  /**< \brief 0x51 B�Ϳ�����ײ */
    UARTCMD_CMD_CODE_PICCB_ATTRIB           = 'R',  /**< \brief 0x52 B�Ϳ��޸Ĵ������ԣ�ѡ�񿨣� */
    UARTCMD_CMD_CODE_PICCB_HALT             = 'S',  /**< \brief 0x53 B�Ϳ����� */
    UARTCMD_CMD_CODE_PICCB_GETUID           = 'T'   /**< \brief 0x54 ��ȡ����֤UID */
} uartcmd_cmd_code_iso14443_t;

/**
 * \brief ISO15693Э�����������
 */
typedef enum uartcmd_cmd_code_iso15693 {
    UARTCMD_CMD_CODE_VICC_INVENTORY             = 'A', /**< \brief 0x41 Ŀ¼ */
    UARTCMD_CMD_CODE_VICC_STAY_QUIET            = 'B', /**< \brief 0x42 ���־�Ĭ */
    UARTCMD_CMD_CODE_VICC_READ_BLOCK            = 'C', /**< \brief 0x43 �����ݿ� */
    UARTCMD_CMD_CODE_VICC_WRITE_BLOCK           = 'D', /**< \brief 0x44 д���ݿ� */
    UARTCMD_CMD_CODE_VICC_LOCK_BLOCK            = 'E', /**< \brief 0x45 ������ */
    UARTCMD_CMD_CODE_VICC_SELECT                = 'F', /**< \brief 0x46 ѡ�� */
    UARTCMD_CMD_CODE_VICC_RESET_READY           = 'H', /**< \brief 0x48 ��λ��׼����״̬ */
    UARTCMD_CMD_CODE_VICC_WRITE_AFI             = 'I', /**< \brief 0x49 дAFI */
    UARTCMD_CMD_CODE_VICC_WRITE_DSFID           = 'K', /**< \brief 0x4B дDSFID */
    UARTCMD_CMD_CODE_VICC_LOCK_DSFID            = 'L', /**< \brief 0x4C ����DSFID */
    UARTCMD_CMD_CODE_VICC_GET_SYS_INFO          = 'M', /**< \brief 0x4D ��ȡϵͳ��Ϣ */
    UARTCMD_CMD_CODE_VICC_GET_SECURITY_STATUS   = 'N'  /**< \brief 0x4E ��ȡ��ȫ״̬ */
} uartcmd_cmd_code_iso15693_t;

/**
 * \brief �������֤���������
 */
typedef enum uartcmd_cmd_code_2g_id_card {
    UARTCMD_CMD_CODE_SGIDC_RESET     = 'A',  /**< \brief 0x41   �������֤��λ */
    UARTCMD_CMD_CODE_SGIDC_GET_UID   = 'B'   /**< \brief 0x42   ���������֤ID�� */
} uartcmd_cmd_code_2g_id_card_t;

/**
 * \brief PLUS CPU ����������루��������MF1���ֵ�����Լ���������
 */
typedef enum uartcmd_cmd_code_plus_cpu {

    /** \brief 0x42 SL0 ���˻��������� */
    UARTCMD_CMD_CODE_SL0_WRITE_PERSO        = 'B',

    /** \brief 0x43 SL0 �ύ���˻� */
    UARTCMD_CMD_CODE_SL0_COMMIT_PERSO       = 'C',

    /** \brief 0x44 SL2 AES��֤��ֱ����Կ��֤�� */
    UARTCMD_CMD_CODE_SL2_AES_AUTH           = 'D',

    /** \brief 0x45 SL2 AES��֤��E2��Կ��֤�� */
    UARTCMD_CMD_CODE_SL2_AES_AUTH_E2        = 'E',

    /** \brief 0x46 SL2 CRYPTO 1��֤��ֱ����Կ��֤�� */
    UARTCMD_CMD_CODE_SL2_CRYPTO1_AUTH       = 'F',

    /** \brief 0x47 SL2 CRYPTO 1��֤��E2��Կ��֤�� */
    UARTCMD_CMD_CODE_SL2_CRYPTO1_AUTH_E2    = 'G',

    /** \brief 0x48 SL2 ���� */
    UARTCMD_CMD_CODE_SL2_READ               = 'H',

    /** \brief 0x49 SL2 ���д */
    UARTCMD_CMD_CODE_SL2_WRITE              = 'I',

    /** \brief 0x4A SL3 �״���֤��ֱ����Կ��֤�� */
    UARTCMD_CMD_CODE_SL3_FIRST_AUTH         = 'J',

    /** \brief 0x4B SL3 �״���֤��E2��Կ��֤�� */
    UARTCMD_CMD_CODE_SL3_FIRST_AUTH_E2      = 'K',

    /** \brief 0x4C SL3 ������֤��ֱ����Կ��֤�� */
    UARTCMD_CMD_CODE_SL3_FOLLOWING_AUTH     = 'L',

    /** \brief 0x4D SL3 ������֤��E2��Կ��֤�� */
    UARTCMD_CMD_CODE_SL3_FOLLOWING_AUTH_E2  = 'M',

    /** \brief 0x4E SL3 ��λ��֤ */
    UARTCMD_CMD_CODE_SL3_RESET_AUTH         = 'N',

    /** \brief 0x4F SL3 �����ݿ� */
    UARTCMD_CMD_CODE_SL3_READ               = 'O',

    /** \brief 0x50 SL3 д���ݿ� */
    UARTCMD_CMD_CODE_SL3_WRITE              = 'P',

    /** \brief 0x51 SL3 д���ݿ� */
    UARTCMD_CMD_CODE_SL3_SET_VALUE          = 'Q',

    /** \brief 0x52 SL3 �����ݿ� */
    UARTCMD_CMD_CODE_SL3_GET_VALUE          = 'R',

    /** \brief 0x53 SL3 ֵ����� */
    UARTCMD_CMD_CODE_SL3_VALUE              = 'S',

    /** \brief 0x54 SL3 �м̹������ */
    UARTCMD_CMD_CODE_SL3_PROX_CHECK         = 'T',

    /** \brief 0x55 SL3 ���⿨֧�� */
    UARTCMD_CMD_CODE_SL3_VCS                = 'U',

    /** \brief 0x56 SL3 ���⿨֧��(�ɻ�ȡUID) */
    UARTCMD_CMD_CODE_SL3_VCSL               = 'V',

    /** \brief 0x57 SL3 ���⿨ѡ�� */
    UARTCMD_CMD_CODE_SL3_SVC                = 'W',

    /** \brief 0x58 SL3 ���⿨ȡ��ѡ�� */
    UARTCMD_CMD_CODE_SL3_DESVC              = 'X'

} uartcmd_cmd_code_plus_cpu_t;

/**
 * \brief ISO18000-6C���������
 */
typedef enum uartcmd_cmd_code_iso18000_6c {

    /** \brief 0x41   ���ò�ѯ��Query������ */
    UARTCMD_CMD_CODE_SET_QUERY_PARAMETER            = 'A',

    /** \brief 0x42   ��ȡ��ѯ��Query������ */
    UARTCMD_CMD_CODE_GET_QUERY_PARAMETER            = 'B',

    /** \brief 0x43   �����̴棨Inventory��ʱ��Singulation�㷨 */
    UARTCMD_CMD_CODE_SET_SINGULATION_ALGORITHM      = 'C',

    /** \brief 0x44   ��ȡ�̴棨Inventory��ʱ��Singulation�㷨 */
    UARTCMD_CMD_CODE_GET_SINGULATION_ALGORITHM      = 'D',

    /** \brief 0x45   ����Singulation�㷨���� */
    UARTCMD_CMD_CODE_SET_SINGULATION_PARAMETER      = 'E',

    /** \brief 0x46   ��ȡSingulation�㷨���� */
    UARTCMD_CMD_CODE_GET_SINGULATION_PARAMETER      = 'F',

    /** \brief 0x48   ��ȡ�̴������� */
    UARTCMD_CMD_CODE_RFID18K6C_GET_INVENTORY        = 'H',

    /** \brief 0x49   ��ȡ���ʵĻ�Ӧ */
    UARTCMD_CMD_CODE_RFID18K6C_GET_ACCESS_RESPONSE  = 'I',

    /** \brief 0x4A   �����̴���� */
    UARTCMD_CMD_CODE_RFID18K6C_START_INVENTORY      = 'J',

    /** \brief 0x4B   ���������� */
    UARTCMD_CMD_CODE_RFID18K6C_START_READ           = 'K',

    /** \brief 0x4C   ����д���� */
    UARTCMD_CMD_CODE_RFID18K6C_START_WRITE          = 'L',

    /** \brief 0x4D   ���������� */
    UARTCMD_CMD_CODE_RFID18K6C_START_KILL           = 'M',

    /** \brief 0x4E   ���������� */
    UARTCMD_CMD_CODE_RFID18K6C_START_LOCK           = 'N',

    /** \brief 0x4F   �������� */
    UARTCMD_CMD_CODE_RFID18K6C_START_ERASE          = 'O',

    /** \brief 0x50   ��ֹ��ǰ�Ĳ��� */
    UARTCMD_CMD_CODE_RFID18K6C_ABORT                = 'P'

} uartcmd_cmd_code_iso18000_6c_t;

#ifdef __cplusplus
}
#endif

#endif /* __UARTCMD_CMD_DEFINE_H */

/* end of file */

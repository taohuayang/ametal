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
#ifndef __AM_UARTCMD_FLASH_DEFINE_H
#define __AM_UARTCMD_FLASH_DEFINE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name ����ģʽ
 * @{
 */

#define UARTCMD_FLASH_WORK_MODE_MASK      0xF0    /**< \brief ����ģʽ���� */
#define UARTCMD_FLASH_WORK_MODE_SLAVE     0x00    /**< \brief �ӻ�ģʽ */
#define UARTCMD_FLASH_WORK_MODE_AUTO      0x10    /**< \brief �Զ����ģʽ */

#define UARTCMD_FLASH_COMM_MODE_MASK      0x0F    /**< \brief ͨ��ģʽ���� */
#define UARTCMD_FLASH_COMM_AUTO           0x00    /**< \brief ͨ���Զ����ģʽ */
#define UARTCMD_FLASH_COMM_I2C            0x01    /**< \brief I2Cͨ�� */
#define UARTCMD_FLASH_COMM_UART           0x02    /**< \brief UARTͨ�� */
#define UARTCMD_FLASH_COMM_WG             0x08    /**< \brief WGͨ�� */

/** \brief Ĭ�Ϲ���ģʽ */
#define UARTCMD_FLASH_MODE_DEFAULT       (UARTCMD_FLASH_WORK_MODE_SLAVE | \
                                          UARTCMD_FLASH_COMM_AUTO)

/** @} */

/**
 * \name �汾��Ϣ
 * @
 */

/** \brief �汾��Ϣ���� */
#define UARTCMD_FLASH_VERSION_SIZE        20

/** \brief ���кų��� */
#define UARTCMD_FLASH_SN_SIZE             16

/** @} */

/***
 * \name ֡��ʽ
 * @{
 */

#define UARTCMD_FLASH_FRAME_FORMAT_OLD       0x00    /**< \brief ��֡��ʽ */
#define UARTCMD_FLASH_FRAME_FORMAT_NEW       0x01    /**< \brief ��֡��ʽ */

/** @} */

/**
 * \name ������
 * @{
 */

#define UARTCMD_FLASH_BAUD_230400            7       /**< \brief 230400 */
#define UARTCMD_FLASH_BAUD_172800            6       /**< \brief 172800 */
#define UARTCMD_FLASH_BAUD_115200            5       /**< \brief 115200 */
#define UARTCMD_FLASH_BAUD_57600             4       /**< \brief 57600 */
#define UARTCMD_FLASH_BAUD_38400             3       /**< \brief 38400 */
#define UARTCMD_FLASH_BAUD_28800             2       /**< \brief 28800 */
#define UARTCMD_FLASH_BAUD_19200             1       /**< \brief 19200 */
#define UARTCMD_FLASH_BAUD_9600              0       /**< \brief 9600 */

/** @} */

//#define AUTO_DETEST_EN_MASK             0x80        //!< �Զ����ʹ������
//#define AUTO_DETEST_NOT_SENT_MASK       0x40        //!< ����δ��������
//#define AUTO_DETEST_EXECUTIVE_HALT_MASK 0x08        //!< ���ִ��Halt()����
//#define AUTO_DETEST_CONTINUE_MASK       0x04        //!< ��������ִ������
//#define AUTO_DETEST_INTERRUPT_MASK      0x02        //!< �����ж����루UART��
//#define AUTO_DETEST_INITIATIVE_SEND_MASK    0x01    //!< ������������(UART)

/**
 * \name ��Կ����
 * @{
 */

#define UARTCMD_FLASH_KEY_TYPE_A        0x60  /**< \brief ��Կ����A */
#define UARTCMD_FLASH_KEY_A_LEN         0x06  /**< \brief ����A����Ϊ8 */
#define UARTCMD_FLASH_KEY_TYPE_B        0x61  /**< \brief ��Կ����B */
#define UARTCMD_FLASH_KEY_B_LEN         0x10  /**< \brief ��Կ����Ϊ16 */

/**
 *  \brief ��ŵ�FLASH�е���Կ���ȡ�����������A��������B����ŵ�FLASH�ж���16�ֽڡ�
 *         �轫����A��䵽16�ֽ�
 */
#define UARTCMD_FLASH_KEY_LEN           0x10

/** \brief �û���Կ���� */
#define UARTCMD_FLASH_USER_KEY_LEN      0x10

/** @} */

/**
 * \name �û�����
 * @{
 */

#define UARTCMD_FLASH_USER_MEM_SIZE     256  /**< \brief �û����ݴ�С */

/** @} */

/**
 * \name I2C��ַ
 * @{
 */

#define UARTCMD_FLASH_MAX_I2C_ADDR         0xBF  /**< \brief �豸���I2C��ַ */
#define UARTCMD_FLASH_MIN_I2C_ADDR         0xB0  /**< \brief �豸��СI2C��ַ */
#define UARTCMD_FLASH_DEFAULT_ADDR         0xB2  /**< \brief �豸Ĭ�ϵ�ַ 0xB2 */

/** @} */

/**
 * \name Э������
 * @{
 */

#define UARTCMD_FLASH_CRAD_TPYE_ISO14443A   0x3F  /**< \brief ISO14443A */
#define UARTCMD_FLASH_CARD_TYPE_ISO14443B   0x5F  /**< \brief ISO14443B */
#define UARTCMD_FLASH_CARD_TYPE_7816        0x9F  /**< \brief ISO7816_3 */

/** @} */

/**
 * \name ��֤ʱ�㷨��ʶ
 * @{
 */

#define UARTCMD_FLASH_AUTH_ALGORITHM_ID_MASK   0x7F   /**< \brief �㷨��ʶ���� */
#define UARTCMD_FLASH_AUTH_ALGORITHM_3_DES     0x00   /**< \brief 3-DES */
#define UARTCMD_FLASH_AUTH_ALGORITHM_1_DES     0x01   /**< \brief 1-DES */
#define UARTCMD_FLASH_AUTH_ALGORITHM_SM1       0x03   /**< \brief SM1 */

/** \brief Mifaer Crypto1/PLUS CPU AES ��ԿA */
#define UARTCMD_FLASH_AUTH_ALGORITHM_KEY_A     0x60

/** \brief Mifaer Crypto1/PLUS CPU AES ��ԿB */
#define UARTCMD_FLASH_AUTH_ALGORITHM_KEY_B     0x61

#define UARTCMD_FLASH_AUTH_ALGORITHM_NO        0x7F   /**< \brief ����֤ */

/** @} */

/**
 * \name �Զ����ģʽ
 * @{
 */

#define UARTCMD_FLASH_AUTO_DETEST_EN_MASK               0x80    /**< \brief �Զ����ʹ������ */
#define UARTCMD_FLASH_AUTO_DETEST_NO_SEND_MASK          0x40    /**< \brief ����δ�������� */
#define UARTCMD_FLASH_AUTO_DETEST_EXECUTE_HALT_MASK     0x08    /**< \brief ���ִ��Halt()���� */
#define UARTCMD_FLASH_AUTO_DETEST_CONTINUE_MASK         0x04    /**< \brief ��������ִ������ */
#define UARTCMD_FLASH_AUTO_DETEST_INTERRUPT_MASK        0x02    /**< \brief �����ж����루UART�� */
#define UARTCMD_FLASH_AUTO_DETEST_SEND_MASK             0x01    /**< \brief ������������(UART) */

/** \brief UARTCMD�Զ����ģʽ���� */
#define UARTCMD_FLASH_AUTO_DETEST_MODE_MASK            (UARTCMD_FLASH_AUTO_DETEST_EXECUTE_HALT_MASK | \
                                                        UARTCMD_FLASH_AUTO_DETEST_CONTINUE_MASK     | \
                                                        UARTCMD_FLASH_AUTO_DETEST_INTERRUPT_MASK    | \
                                                        UARTCMD_FLASH_AUTO_DETEST_SEND_MASK)

#define UARTCMD_FLASH_AUTO_DETEST_EN                    0x80     /**< \brief �Զ����ʹ�� */
#define UARTCMD_FLASH_AUTO_DETEST_NO_SEND               0x40     /**< \brief ����δ���� */
#define UARTCMD_FLASH_AUTO_DETEST_EXECUTE_HALT          0x08     /**< \brief ���ִ��Halt() */
#define UARTCMD_FLASH_AUTO_DETEST_CONTINUE              0x04     /**< \brief ��������ִ�� */
#define UARTCMD_FLASH_AUTO_DETEST_INTERRUPT             0x02     /**< \brief �����ж� */
#define UARTCMD_FLASH_AUTO_DETEST_SEND                  0x01     /**< \brief �������� */

/** @} */

/**
 * \name ����ģʽ
 * @{
 */

#define UARTCMD_FLASH_CONTROL_BY_PSAM          0xAA  /**< \brief PSAM �����ļ�����ģʽ */
#define UARTCMD_FLASH_CONTROL_BY_USER_CARD     0x55  /**< \brief �û��������ļ�����ģʽ */
#define UARTCMD_FLASH_CONTROL_BY_READER        0x00  /**< \brief ����������ģʽ */

/** @} */

/**
 * \name �������ģʽ
 * @{
 */

/** \brief ���������С��ģʽ���� */
#define UARTCMD_FLASH_DATA_ENDIAN_MASK       0x80

#define UARTCMD_FLASH_DATA_ENDIAN_LITTLE     0x00  /**< \brief С��ģʽ(Ĭ��) */
#define UARTCMD_FLASH_DATA_ENDIAN_BIG        0x80  /**< \brief ���ģʽ */

/** \brief �����������ģʽ���� */
#define UARTCMD_FLASH_DATA_OUTPUT_MASK       0x70

#define UARTCMD_FLASH_DATA_OUTPUT_NO         0x00  /**< \brief ���ݲ����� */
#define UARTCMD_FLASH_DATA_OUTPUT_SEGMENT    0x10  /**< \brief ���ݷֶ� */
#define UARTCMD_FLASH_DATA_OUTPUT_CROSS      0x20  /**< \brief ���ݽ��� */

/** \brief �����������ģʽ���� */
#define UARTCMD_FLASH_DATA_ENCRYPT_MASK      0x0F

#define UARTCMD_DATA_ENCRYPT_NO              0x00  /**< \brief ������ */
#define UARTCMD_DATA_ENCRYPT_1_DES           0x01  /**< \brief 1-DES */
#define UARTCMD_DATA_ENCRYPT_3_DES           0x02  /**< \brief 3-DES */
#define UARTCMD_DATA_ENCRYPT_SM1             0x03  /**< \brief SM1 */
#define UARTCMD_DATA_ENCRYPT_ROLLCODE        0x08  /**< \brief ������� */
#define UARTCMD_DATA_ENCRYPT_RC5             0x09  /**< \brief RC5 ���� */
#define UARTCMD_DATA_ENCRYPT_AES             0x0A  /**< \brief AES ���� */

/** @} */

/**
 * \name ��������
 * @{
 */

#define UARTCMD_FLASH_CARD_TYPE_ISO14443A     0x3F  /**< \brief ISO14443A */
#define UARTCMD_FLASH_CARD_TYPE_ISO14443B     0x5F  /**< \brief ISO14443B */
#define UARTCMD_FLASH_CARD_TYPE_ISO115693     0x7F  /**< \brief ISO115693 */
#define UARTCMD_FLASH_CARD_TYPE_ISO7816_3     0x9F  /**< \brief ISO7816_3 */
#define UARTCMD_FLASH_CARD_TYPE_INVALID       0xFF  /**< \brief ��Ч��/��Ч��SAK */

#define UARTCMD_FLASH_CARD_TYPE_MF0           0x00  /**< \brief MF0ϵ�п� */
#define UARTCMD_FLASH_CARD_TYPE_UL            0x01  /**< \brief MF0 ULϵ�п� */
#define UARTCMD_FLASH_CARD_TYPE_ULC           0x02  /**< \brief MF0 ULCϵ�п� */

#define UARTCMD_FLASH_CARD_TYPE_MF1           0x08  /**< \brief MF1ϵ�п� */
#define UARTCMD_FLASH_CARD_TYPE_MINI          0x09  /**< \brief MF1 miniϵ�п� */
#define UARTCMD_FLASH_CARD_TYPE_S50           0x0A  /**< \brief MF1 s50ϵ�п� */
#define UARTCMD_FLASH_CARD_TYPE_S70           0x0B  /**< \brief MF1 s70ϵ�п� */

#define UARTCMD_FLASH_CARD_TYPE_MF3           0x10  /**< \brief MF3ϵ�п� */
#define UARTCMD_FLASH_CARD_TYPE_D20           0x11  /**< \brief MF3 D20�� */
#define UARTCMD_FLASH_CARD_TYPE_D21           0x12  /**< \brief MF3 D21�� */
#define UARTCMD_FLASH_CARD_TYPE_D40           0x13  /**< \brief MF3 D40�� */
#define UARTCMD_FLASH_CARD_TYPE_D41           0x14  /**< \brief MF3 D41�� */
#define UARTCMD_FLASH_CARD_TYPE_D80           0x15  /**< \brief MF3 D80�� */
#define UARTCMD_FLASH_CARD_TYPE_D81           0x16  /**< \brief MF3 D81�� */

#define UARTCMD_FLASH_CARD_TYPE_MFP           0x18  /**< \brief PLUS CPU ϵ�п� */
#define UARTCMD_FLASH_CARD_TYPE_MFP2_SL2      0x19  /**< \brief PLUS CPU 2K(SL2) */
#define UARTCMD_FLASH_CARD_TYPE_MFP4_SL2      0x1A  /**< \brief PLUS CPU 4K(SL2) */
#define UARTCMD_FLASH_CARD_TYPE_MFPS_SL3      0x1B  /**< \brief PLUS S 2/4K(SL3) */
#define UARTCMD_FLASH_CARD_TYPE_MFPX_SL3      0x1C  /**< \brief PLUS X 2/4K(SL3) */

#define UARTCMD_FLASH_CARD_TYPE_ISO14443A_4   0x20  /**< \brief ISO14443-4 TypeA ϵ�п� */
#define UARTCMD_FLASH_CARD_TYPE_FM1208        0x21  /**< \brief ����΢����FM1208CPU�� */
#define UARTCMD_FLASH_CARD_TYPE_FM12AG08      0x22  /**< \brief ����΢����FM12AG08 ����CPU�� */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __UARTCMD_FLASH_DEFINE_H */

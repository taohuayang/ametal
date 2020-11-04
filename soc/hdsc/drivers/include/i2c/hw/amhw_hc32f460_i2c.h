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
 * \brief I2C�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-19
 * \endinternal
 */

#ifndef __AMHW_HC32F460_I2C_H
#define __AMHW_HC32F460_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */

typedef enum en_address_bit
{
    Adr7bit = 0u,       /**< \brief I2C address length is 7 bits */
    Adr10bit = 1u,      /**< \brief I2C address length is 10 bits */
}en_address_bit_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**< \brief define interrupt enable bit for I2C_CR2 register */
#define I2C_CR2_STARTIE         (0x00000001ul)
#define I2C_CR2_SLADDR0EN       (0x00000002ul)
#define I2C_CR2_SLADDR1EN       (0x00000004ul)
#define I2C_CR2_TENDIE          (0x00000008ul)
#define I2C_CR2_STOPIE          (0x00000010ul)
#define I2C_CR2_RFULLIE         (0x00000040ul)
#define I2C_CR2_TEMPTYIE        (0x00000080ul)
#define I2C_CR2_ARLOIE          (0x00000200ul)
#define I2C_CR2_NACKIE          (0x00001000ul)
#define I2C_CR2_TMOURIE         (0x00004000ul)
#define I2C_CR2_GENCALLIE       (0x00100000ul)
#define I2C_CR2_SMBDEFAULTIE    (0x00200000ul)
#define I2C_CR2_SMBHOSTIE       (0x00400000ul)
#define I2C_CR2_SMBALRTIE       (0x00800000ul)

/**< \brief define status bit for I2C_SR register */
#define I2C_SR_STARTF           (0x00000001ul)
#define I2C_SR_SLADDR0F         (0x00000002ul)
#define I2C_SR_SLADDR1F         (0x00000004ul)
#define I2C_SR_TENDF            (0x00000008ul)
#define I2C_SR_STOPF            (0x00000010ul)
#define I2C_SR_RFULLF           (0x00000040ul)
#define I2C_SR_TEMPTYF          (0x00000080ul)
#define I2C_SR_ARLOF            (0x00000200ul)
#define I2C_SR_NACKDETECTF      (0x00000400ul)
#define I2C_SR_NACKSENDF        (0x00001000ul)
#define I2C_SR_TMOUTF           (0x00004000ul)
#define I2C_SR_MSL              (0x00010000ul)
#define I2C_SR_BUSY             (0x00020000ul)
#define I2C_SR_TRA              (0x00040000ul)
#define I2C_SR_GENCALLF         (0x00100000ul)
#define I2C_SR_SMBDEFAULTF      (0x00200000ul)
#define I2C_SR_SMBHOSTF         (0x00400000ul)
#define I2C_SR_SMBALRTF         (0x00800000ul)

/**< \brief define status clear bit for I2C_CLR register*/
#define I2C_CLR_STARTFCLR           (0x00000001ul)
#define I2C_CLR_SLADDR0FCLR         (0x00000002ul)
#define I2C_CLR_SLADDR1FCLR         (0x00000004ul)
#define I2C_CLR_TENDFCLR            (0x00000008ul)
#define I2C_CLR_STOPFCLR            (0x00000010ul)
#define I2C_CLR_RFULLFCLR           (0x00000040ul)
#define I2C_CLR_TEMPTYFCLR          (0x00000080ul)
#define I2C_CLR_ARLOFCLR            (0x00000200ul)
#define I2C_CLR_NACKFCLR            (0x00001000ul)
#define I2C_CLR_TMOUTFCLR           (0x00004000ul)
#define I2C_CLR_GENCALLFCLR         (0x00100000ul)
#define I2C_CLR_SMBDEFAULTFCLR      (0x00200000ul)
#define I2C_CLR_SMBHOSTFCLR         (0x00400000ul)
#define I2C_CLR_SMBALRTFCLR         (0x00800000ul)
#define I2C_CLR_MASK                (0x00F056DFul)


typedef enum en_i2c_functional_state
{
    I2C_DISABLE = 0u,
    I2C_ENABLE  = 1u,
} en_i2c_functional_state_t;

typedef enum en_i2c_flag_status
{
    I2C_RESET = 0u,
    I2C_SET   = 1u,
} en_i2c_flag_status_t;

/**
 * \addtogroup amhw_hc32f460_if_i2c
 * \copydoc amhw_hc32f460_i2c.h
 * @{
 */

/**
 * \brief I2C���ƼĴ���1λ��ṹ��
 */
typedef struct
{
    __IO uint32_t PE                        : 1;  /**< \brief PC����ʹ��*/
    __IO uint32_t SMBUS                     : 1;  /**< \brief SMBUS/I2C����ģʽѡ��λ*/
    __IO uint32_t SMBALRTEN                 : 1;  /**< \brief ����ƥ��SMBUS������Ӧ��ַλ*/
    __IO uint32_t SMBDEFAULTEN              : 1;  /**< \brief ����ƥ��SMBUSĬ�ϵ�ַλ*/
    __IO uint32_t SMBHOSTEN                 : 1;  /**< \brief ����ƥ��SMBUS������ַλ*/
    uint32_t RESERVED5                      : 1;  /**< \brief ���� */
    __IO uint32_t ENGC                      : 1;  /**< \brief �㲥����ʹ��*/
    __IO uint32_t RESTART                   : 1;  /**< \brief �ظ���ʼ��������λ*/
    __IO uint32_t START                     : 1;  /**< \brief ��ʼ��������λ*/
    __IO uint32_t STOP                      : 1;  /**< \brief ֹͣ��������λ*/
    __IO uint32_t ACK                       : 1;  /**< \brief ����Ӧ��*/
    uint32_t RESERVED11                     : 4;  /**< \brief ���� */
    __IO uint32_t SWRST                     : 1;  /**< \brief �����λ */
    uint32_t RESERVED16                     :16;  /**< \brief ���� */
} stc_i2c_cr1_field_t;

/**
 * \brief I2C���ƼĴ���2λ��ṹ��
 */
typedef struct
{
    __IO uint32_t STARTIE                   : 1;  /**< \brief ��ʼ����/���¿�ʼ�����ж����� */
    __IO uint32_t SLADDR0IE                 : 1;  /**< \brief �ӻ���ַ0ƥ��һ���ж����� */
    __IO uint32_t SLADDR1IE                 : 1;  /**< \brief �ӻ���ַ1ƥ��һ���ж����� */
    __IO uint32_t TENDIE                    : 1;  /**< \brief ����һ֡���ݽ����ж�����λ */
    __IO uint32_t STOPIE                    : 1;  /**< \brief ֹͣ�����ж����� */
    uint32_t RESERVED5                      : 1;  /**< \brief ���� */
    __IO uint32_t RFULLIE                   : 1;  /**< \brief �����������ж�����λ */
    __IO uint32_t TEMPTYIE                  : 1;  /**< \brief �������ݿ��ж�����λ */
    uint32_t RESERVED8                      : 1;  /**< \brief ���� */
    __IO uint32_t ARLOIE                    : 1;  /**< \brief �ٲ�ʧ���ж����� */
    uint32_t RESERVED10                     : 2;  /**< \brief ���� */
    __IO uint32_t NACKIE                    : 1;  /**< \brief NACK�ж����� */
    uint32_t RESERVED13                     : 1;  /**< \brief ���� */
    __IO uint32_t TMOUTIE                   : 1;  /**< \brief ��ʱ�ж����� */
    uint32_t RESERVED15                     : 5;  /**< \brief ���� */
    __IO uint32_t GENCALLIE                 : 1;  /**< \brief �㲥���е�ַƥ��һ���ж����� */
    __IO uint32_t SMBDEFAULTIE              : 1;  /**< \brief SMBUSĬ�ϵ�ַƥ��һ���ж����� */
    __IO uint32_t SMHOSTIE                  : 1;  /**< \brief SMBUS������ַƥ��һ���ж����� */
    __IO uint32_t SMBALRTIE                 : 1;  /**< \brief SMBUS������Ӧ��ַƥ��һ���ж����� */
    uint32_t RESERVED24                     : 8;  /**< \brief ���� */
} stc_i2c_cr2_field_t;

/**
 * \brief I2C���ƼĴ���3λ��ṹ��
 */
typedef struct
{
    __IO uint32_t TMOUTEN                   : 1;  /**< \brief ��ʱ��������λ */
    __IO uint32_t LTMOUT                    : 1;  /**< \brief �͵�ƽ��ʱ������� */
    __IO uint32_t HTMOUT                    : 1;  /**< \brief �ߵ�ƽ��ʱ������� */
    uint32_t RESERVED3                      : 4;  /**< \brief ���� */
    __IO uint32_t FACKEN                    : 1;  /**< \brief RFULL��־λ��Ϊʱ���ѡ�� */
    uint32_t RESERVED8                      :24;  /**< \brief ���� */
} stc_i2c_cr3_field_t;

/**
 * \brief I2C�ӻ���ַ�Ĵ���0λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SLADDR0                   :10;  /**< \brief �ӻ���ַ */
    uint32_t RESERVED10                     : 2;  /**< \brief ���� */
    __IO uint32_t SLADDR0EN                 : 1;  /**< \brief �ӻ���ַ0��Чλ */
    uint32_t RESERVED13                     : 2;  /**< \brief ���� */
    __IO uint32_t ADDRMOD0                  : 1;  /**< \brief 7λ/10λ��ַ��ʽѡ��λ */
    uint32_t RESERVED16                     :16;  /**< \brief ���� */
} stc_i2c_slr0_field_t;

/**
 * \brief I2C�ӻ���ַ�Ĵ���1λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SLADDR1                   :10;  /**< \brief �ӻ���ַ */
    uint32_t RESERVED10                     : 2;  /**< \brief ���� */
    __IO uint32_t SLADDR1EN                 : 1;  /**< \brief �ӻ���ַ1��Чλ */
    uint32_t RESERVED13                     : 2;  /**< \brief ���� */
    __IO uint32_t ADDRMOD1                  : 1;  /**< \brief 7λ/10λ��ַ��ʽѡ��λ */
    uint32_t RESERVED16                     :16;  /**< \brief ���� */
} stc_i2c_slr1_field_t;

/**
 * \brief I2C SCL��ƽ��ʱ���ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t TOUTLOW                   :16;  /**< \brief SCL�͵�ƽ��ʱ���� */
    __IO uint32_t TOUTHIGH                  :16;  /**< \brief SCL�ߵ�ƽ��ʱ���� */
} stc_i2c_sltr_field_t;

/**
 * \brief I2C ״̬�Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t STARTF                    : 1;  /**< \brief ��ʼ����/���¿�ʼ������־λ */
    __IO uint32_t SLADDR0F                  : 1;  /**< \brief �ӻ���ַ�Ĵ���0ƥ��һ�±�־ */
    __IO uint32_t SLADDR1F                  : 1;  /**< \brief �ӻ���ַ�Ĵ���1ƥ��һ�±�־ */
    __IO uint32_t TENDF                     : 1;  /**< \brief �������ݽ�����־λ */
    __IO uint32_t STOPF                     : 1;  /**< \brief ֹͣ������־λ */
    uint32_t RESERVED5                      : 1;  /**< \brief ���� */
    __IO uint32_t RFULLF                    : 1;  /**< \brief ������������־λ */
    __IO uint32_t TEMPTYF                   : 1;  /**< \brief �������ݿձ�־λ */
    uint32_t RESERVED8                      : 1;  /**< \brief ���� */
    __IO uint32_t ARLOF                     : 1;  /**< \brief �ٲ�ʧ�ܱ�־λ */
    __IO uint32_t ACKRF                     : 1;  /**< \brief ����Ӧ��λ */
    uint32_t RESERVED11                     : 1;  /**< \brief ���� */
    __IO uint32_t NACKF                     : 1;  /**< \brief NACK��־λ */
    uint32_t RESERVED13                     : 1;  /**< \brief ���� */
    __IO uint32_t TMOUTF                    : 1;  /**< \brief ��ʱ��־λ */
    uint32_t RESERVED15                     : 1;  /**< \brief ���� */
    __IO uint32_t MSL                       : 1;  /**< \brief ���ӻ�ѡ��λ */
    __IO uint32_t BUSY                      : 1;  /**< \brief ����æ��־λ */
    __IO uint32_t TRA                       : 1;  /**< \brief ���ͽ���ѡ��λ */
    uint32_t RESERVED19                     : 1;  /**< \brief ���� */
    __IO uint32_t GENCALLF                  : 1;  /**< \brief �㲥���е�ַƥ��һ�±�־ */
    __IO uint32_t SMBDEFAULTF               : 1;  /**< \brief SMBUSĬ�ϵ�ַƥ��һ�±�־λ */
    __IO uint32_t SMBHOSTF                  : 1;  /**< \brief SMBUS������ַƥ��һ�±�־λ */
    __IO uint32_t SMBALRTF                  : 1;  /**< \brief SMBUS������Ӧ��ַƥ��һ�±�־λ */
    uint32_t RESERVED24                     : 8;  /**< \brief ���� */
} stc_i2c_sr_field_t;

/**
 * \brief I2C ״̬����Ĵ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t STARTFCLR                 : 1;  /**< \brief ��ʼ����/���¿�ʼ������־����λ */
    __IO uint32_t SLADDR0FCLR               : 1;  /**< \brief �ӻ���ַ�Ĵ���0ƥ��һ�±�־����λ */
    __IO uint32_t SLADDR1FCLR               : 1;  /**< \brief �ӻ���ַ�Ĵ���1ƥ��һ�±�־����λ */
    __IO uint32_t TENDFCLR                  : 1;  /**< \brief �������ݽ�����־λ����λ */
    __IO uint32_t STOPFCLR                  : 1;  /**< \brief ֹͣ������־λ����λ */
    uint32_t RESERVED5                      : 1;  /**< \brief ���� */
    __IO uint32_t RFULLFCLR                 : 1;  /**< \brief ������������־λ����λ */
    __IO uint32_t TEMPTYFCLR                : 1;  /**< \brief �������ݿձ�־λ����λ */
    uint32_t RESERVED8                      : 1;  /**< \brief ���� */
    __IO uint32_t ARLOFCLR                  : 1;  /**< \brief �ٲ�ʧ�ܱ�־λ����λ */
    uint32_t RESERVED10                     : 2;  /**< \brief ���� */
    __IO uint32_t NACKFCLR                  : 1;  /**< \brief NACK��־λ����λ */
    uint32_t RESERVED13                     : 1;  /**< \brief ���� */
    __IO uint32_t TMOUTFCLR                 : 1;  /**< \brief ��ʱ��־λ����λ */
    uint32_t RESERVED15                     : 5;  /**< \brief ���� */
    __IO uint32_t GENCALLFCLR               : 1;  /**< \brief �㲥���е�ַƥ��һ�±�־����λ */
    __IO uint32_t SMBDEFAULTFCLR            : 1;  /**< \brief SMBUSĬ�ϵ�ַƥ��һ�±�־����λ */
    __IO uint32_t SMBHOSTFCLR               : 1;  /**< \brief SMBUS������ַƥ��һ�±�־����λ */
    __IO uint32_t SMBALRTFCLR               : 1;  /**< \brief SMBUS������Ӧ��ַƥ��һ�±�־����λ */
    uint32_t RESERVED24                     : 8;  /**< \brief ���� */
} stc_i2c_clr_field_t;

/**
 * \brief I2C ���ݷ��ͼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DT                        : 8;  /**< \brief ���� */
    uint32_t RESERVED8                      :24;  /**< \brief ���� */
} stc_i2c_dtr_field_t;

/**
 * \brief I2C ���ݽ��ռĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DR                        : 8;  /**< \brief ���� */
    uint32_t RESERVED8                      :24;  /**< \brief ���� */
} stc_i2c_drr_field_t;

/**
 * \brief I2C ʱ�ӿ��ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t SLOWW                     : 5;  /**< \brief �趨SCLʱ�ӵĵ͵�ƽ��� */
    uint32_t RESERVED5                      : 3;  /**< \brief ���� */
    __IO uint32_t SHIGHW                    : 5;  /**< \brief �趨SCL�ߵ�ƽ���λ */
    uint32_t RESERVED13                     : 3;  /**< \brief ���� */
    __IO uint32_t FREQ                      : 3;  /**< \brief I2C��׼ʱ��Ƶ���趨λ */
    uint32_t RESERVED19                     :13;  /**< \brief ���� */
} stc_i2c_ccr_field_t;

/**
 * \brief I2C �˲����ƼĴ���λ��ṹ��
 */
typedef struct
{
    __IO uint32_t DNF                       : 2;  /**< \brief �����˲����˲�����ѡ�� */
    uint32_t RESERVED2                      : 2;  /**< \brief ���� */
    __IO uint32_t DNFEN                     : 1;  /**< \brief �����˲���������λ */
    __IO uint32_t ANFEN                     : 1;  /**< \brief ģ���˲���������λ */
    uint32_t RESERVED6                      :26;  /**< \brief ���� */
} stc_i2c_fltr_field_t;


/**
 * \brief I2C�Ĵ�����ṹ��
 */
typedef struct amhw_hc32f460_i2c {
    union
    {
        __IO uint32_t CR1;        /**< \brief I2C���ƼĴ���1 */
        stc_i2c_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;        /**< \brief I2C���ƼĴ���2 */
        stc_i2c_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t CR3;        /**< \brief I2C���ƼĴ���3 */
        stc_i2c_cr3_field_t CR3_f;
    };
    uint8_t RESERVED3[4];         /**< \brief ���� */
    union
    {
        __IO uint32_t SLR0;       /**< \brief I2C�ӻ���ַ�Ĵ���0 */
        stc_i2c_slr0_field_t SLR0_f;
    };
    union
    {
        __IO uint32_t SLR1;        /**< \brief I2C�ӻ���ַ�Ĵ���1 */
        stc_i2c_slr1_field_t SLR1_f;
    };
    union
    {
        __IO uint32_t SLTR;        /**< \brief I2C״̬�Ĵ��� */
        stc_i2c_sltr_field_t SLTR_f;
    };
    union
    {
        __IO uint32_t SR;          /**< \brief I2C״̬�Ĵ��� */
        stc_i2c_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t CLR;         /**< \brief I2C״̬�Ĵ��� */
        stc_i2c_clr_field_t CLR_f;
    };
    union
    {
        __IO uint32_t DTR;         /**< \brief I2C���ݷ��ͼĴ��� */
        stc_i2c_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t DRR;         /**< \brief I2C���ݽ��ռĴ��� */
        stc_i2c_drr_field_t DRR_f;
    };
    union
    {
        __IO uint32_t CCR;         /**< \brief I2C�����ʿ��ƼĴ��� */
        stc_i2c_ccr_field_t CCR_f;
    };
    union
    {
        __IO uint32_t FLTR;        /**< \brief I2C�����ʿ��ƼĴ��� */
        stc_i2c_fltr_field_t FLTR_f;
    };
} amhw_hc32f460_i2c_t;

#define I2C1_RXI   (1 << 4)
#define I2C1_TXI   (1 << 5)
#define I2C1_TEI   (1 << 6)
#define I2C1_EEI   (1 << 7)

#define I2C2_RXI   (1 << 8)
#define I2C2_TXI   (1 << 9)
#define I2C2_TEI   (1 << 10)
#define I2C2_EEI   (1 << 11)

#define I2C3_RXI   (1 << 12)
#define I2C3_TXI   (1 << 13)
#define I2C3_TEI   (1 << 14)
#define I2C3_EEI   (1 << 15)


#define GENERATE_START                  0x00u
#define GENERATE_RESTART                0x01u
#define ADDRESS_W                       0x00u
#define ADDRESS_R                       0x01u
#define TIMEOUT                         ((uint32_t)0x10000)

/**
 * \brief i2c���ñ�־
 */

/** \brief ����ģʽ(1Mbps)ʹ��(i2c_tm < 9ʱ����ʹ��) */
#define AMHW_HC32F460_I2C_HIGH_SPEED          (1ul)

/** \brief Ӧ���־ʹ�� */
#define AMHW_HC32F460_I2C_REPLY_ENABLE        (1ul << 2)

/** \brief �жϱ�־λ */
#define AMHW_HC32F460_I2C_INT_FLAG            (1ul << 3)

/** \brief ֹͣ��־ʹ�� */
#define AMHW_HC32F460_I2C_STOP_ENABLE         (1ul << 4)

/** \brief ��ʼ��־ʹ�� */
#define AMHW_HC32F460_I2C_START_ENABLE        (1ul << 5)

typedef enum en_i2c_mode
{
    I2cMaster = 0u,        /**< \brief I2C master mode */
    I2cSlave,              /**< \brief I2C slave mode */
}en_i2c_mode_t;

typedef struct stc_i2c_init
{
    en_i2c_mode_t enI2cMode; /**< \brief I2C mode config, master or slave */
    uint32_t u32Pclk3;       /**< \brief Plck3 frequency */
    uint32_t u32Baudrate;    /**< \brief I2C baudrate config */
    uint32_t u32SclTime;     /**< \brief The SCL rising and falling time, count of T(pclk3) */
}stc_i2c_init_t;
/**
 * \brief I2C״̬��־
 */
typedef enum amhw_hc32f460_status_flag{

	/** \brief ��ָ��ģʽ״̬ */
    AMHW_HC32F460_STATUS_FLAG_0   = (0x00),   /**< \brief �������ߴ����I2C����δ�����״̬ */
    AMHW_HC32F460_STATUS_FLAG_1   = (0x08),   /**< \brief �ѷ�����ʼ���� */
    AMHW_HC32F460_STATUS_FLAG_2   = (0x10),   /**< \brief �ѷ����ظ���ʼ���� */

	/** \brief ��������״̬ */
    AMHW_HC32F460_STATUS_FLAG_3   = (0x18),   /**< \brief �ѷ���SLA+W���ѽ���ACK */
    AMHW_HC32F460_STATUS_FLAG_4   = (0x20),   /**< \brief �ѷ���SLA+W���ѽ��շ�ACK */
    AMHW_HC32F460_STATUS_FLAG_5   = (0x28),   /**< \brief �ѷ������ݣ��ѽ���ACK */
    AMHW_HC32F460_STATUS_FLAG_6   = (0x30),   /**< \brief �ѷ������� */
    AMHW_HC32F460_STATUS_FLAG_7   = (0x38),   /**< \brief ��SLA+ ��д��д�����ֽ�ʱ��ʧ�ٲ� */

    /** \brief ��������״̬ */
    AMHW_HC32F460_STATUS_FLAG_8   = (0x40),   /**< \brief �ѷ���SLA +R,�ѽ���ACK */
    AMHW_HC32F460_STATUS_FLAG_9   = (0x48),   /**< \brief �ѷ���SLA +R,�ѽ��շ�ACK */
    AMHW_HC32F460_STATUS_FLAG_10  = (0x50),   /**< \brief �ѽ��������ֽڣ�ACK�ѷ��� */
    AMHW_HC32F460_STATUS_FLAG_11  = (0x58),   /**< \brief �ѽ��������ֽڣ���ACK�ѷ��� */

    /** \brief �ӽ�����״̬ */
    AMHW_HC32F460_STATUS_FLAG_12  = (0x60),   /**< \brief �ѽ��������SLA+W���ѽ���ACK */
    AMHW_HC32F460_STATUS_FLAG_13  = (0x68),   /**< \brief ����ʱ��SLA+��д��ʧ�ٲã��ѽ��������SLA+W���ѷ���ACK�� */
    AMHW_HC32F460_STATUS_FLAG_14  = (0x70),   /**< \brief �ѽ���ͨ�õ��õ�ַ��0x00�����ѷ���ACK */
    AMHW_HC32F460_STATUS_FLAG_15  = (0x78),   /**< \brief ����ʱ��SLA+��д�ж�ʧ�ٲã��ѽ���ͨ�õ��õ�ַ���ѷ���ACK�� */
    AMHW_HC32F460_STATUS_FLAG_16  = (0x80),   /**< \brief ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ���ACK�� */
    AMHW_HC32F460_STATUS_FLAG_17  = (0x88),   /**< \brief ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ��ط�ACK�� */
    AMHW_HC32F460_STATUS_FLAG_18  = (0x90),   /**< \brief ǰһ��Ѱַʹ��ͨ�õ��õ�ַ���ѽ������ݣ��ѷ���ACK�� */
    AMHW_HC32F460_STATUS_FLAG_19  = (0x98),   /**< \brief ǰһ��Ѱַʹ��ͨ�õ��õ�ַ���ѽ������ݣ��ѷ��ط�ACK�� */
    AMHW_HC32F460_STATUS_FLAG_20  = (0xa0),   /**< \brief ��ʹ�ôӽ���/�ӷ���ģʽ�о�̬Ѱַʱ�����յ�ֹͣ�������ظ���ʼ���� */

    /** \brief �ӷ�����״̬ */
    AMHW_HC32F460_STATUS_FLAG_22  = (0xa8),   /**< \brief �ѽ��������SLA+R���ѷ���ACK */
    AMHW_HC32F460_STATUS_FLAG_23  = (0xb0),   /**< \brief ������ʱ��SLA+ ��д�ж�ʧ�ٲã��ѽ�������SLA+R���ѷ���ACK�� */
    AMHW_HC32F460_STATUS_FLAG_24  = (0xb8),   /**< \brief �ѷ������ݣ��ѽ���ACK�� */
    AMHW_HC32F460_STATUS_FLAG_25  = (0xc0),   /**< \brief �ѷ��������ֽڣ��ѽ��շ�ACK; */
    AMHW_HC32F460_STATUS_FLAG_26  = (0xc8),   /**< \brief װ��������ֽ��ѱ����ͣ��ѽ���ACK�� */

    /** \brief ����״̬ */
    AMHW_HC32F460_STATUS_FLAG_27  = (0xf8)    /**< \brief �޿��õ����״̬��Ϣ��si=0�� */
}amhw_hc32f460_status_flag_t;

typedef enum en_clock_timeout_switch
{
    TimeoutFunOff = 0u,  /**< \brief I2C SCL pin time out function off */
    LowTimerOutOn = 3u,  /**< \brief I2C SCL pin high level time out function on */
    HighTimeOutOn = 5u,  /**< \brief I2C SCL pin low level time out function on */
    BothTimeOutOn = 7u,  /**< \brief I2C SCL pin both(low and high) level time out function on */
}en_clock_timeout_switch_t;

typedef struct stc_clock_timeout_init
{
    en_clock_timeout_switch_t   enClkTimeOutSwitch;   /**< \brief I2C clock timeout function switch */
    uint16_t                    u16TimeOutHigh;       /**< \brief I2C clock timeout period for High level */
    uint16_t                    u16TimeOutLow;        /**< \brief I2C clock timeout period for Low level */
}stc_clock_timeout_init_t;


static uint8_t freq_div[8] = {1,2,4,8,16,32,64,128};

static uint8_t amhw_hc32f460_i2c_get_freq_reg(float fDiv)
{
    uint8_t u8Reg = 0u;

    for(uint8_t i=7u; i>0u; i--)
    {
        if(fDiv >= (float)freq_div[i-1u])
        {
            u8Reg = i;
            break;
        }
    }

    return u8Reg;
}

am_static_inline
void amhw_hc32f460_i2c_baud_config (amhw_hc32f460_i2c_t * p_hw_i2c, 
                   uint32_t u32Baudrate, uint32_t u32SclTime, uint32_t u32Pclk3)
{
    float fDivIndex = 0.0f;
    uint8_t u8DivIndex;
    uint32_t width = 0ul;
    uint32_t dnfsum = 0ul, divsum = 0ul;
    uint32_t tmp = 0ul;

    if (u32Baudrate > 400000ul)
    {
        u32Baudrate = 400000ul;
    }

    /** \brief Judge digitial filter status */
    if(1u == p_hw_i2c->FLTR_f.DNFEN)
    {
        dnfsum = p_hw_i2c->FLTR_f.DNF+1ul;
    }
    else
    {
        dnfsum = 0ul;
    }
    divsum = 2ul;  /**< \brief default */

    if (0ul != u32Baudrate)
    {
        tmp = u32Pclk3/u32Baudrate - u32SclTime;
    }

    /** \brief Calculate the pclk3 div */
    fDivIndex = (float)tmp / ((32.0f + (float)dnfsum + (float)divsum) * 2.0f);

    if (fDivIndex > 128.0f)
    {
        while(1);
    }
    
    u8DivIndex = amhw_hc32f460_i2c_get_freq_reg(fDivIndex);

    /** \brief Judge if clock divider on*/
    if(0u == u8DivIndex)
    {
        divsum = 3ul;
    }
    else
    {
        divsum = 2ul;
    }
    
    width =  tmp / freq_div[u8DivIndex];

    if ((width/2ul) < (dnfsum + divsum))
    {
        while(1);
    }

    /* Write register */
    p_hw_i2c->CCR_f.FREQ = u8DivIndex;
    p_hw_i2c->CCR_f.SLOWW = width / 2ul - dnfsum - divsum;
    p_hw_i2c->CCR_f.SHIGHW = width - width / 2ul - dnfsum - divsum;
}


/**
 * \brief ʹ�� I2C ģ��
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_i2c_enable (amhw_hc32f460_i2c_t *p_hw_i2c)
{
    p_hw_i2c->CR1_f.PE = 1;
}

/**
 * \brief ���� I2C ģ�飨���ͺͽ��ջ��屣�ֲ���״̬��
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_i2c_disable (amhw_hc32f460_i2c_t *p_hw_i2c)
{
    p_hw_i2c->CR1_f.PE = 0;
}

/**
 * \brief I2C�㲥����ʹ��
 *
 */
am_static_inline
void amhw_hc32f460_i2c_gen_call_ack (amhw_hc32f460_i2c_t *p_hw_i2c)
{
    p_hw_i2c->CR1_f.ENGC = 1;
}

/**
 * \brief I2C���ܹ㲥���в�ʹ��
 *
 */
am_static_inline
void amhw_hc32f460_i2c_gen_call_nack (amhw_hc32f460_i2c_t *p_hw_i2c)
{
    p_hw_i2c->CR1_f.ENGC = 0;
}

am_static_inline
void amhw_hc32f460_i2c_slave_addr0_config(amhw_hc32f460_i2c_t      *pstcI2Cx,
                                          en_i2c_functional_state_t enNewState,
                                          en_address_bit_t          enAdrMode,
                                          uint8_t                   u8Adr)
{
    pstcI2Cx->SLR0_f.SLADDR0EN = enNewState;
    pstcI2Cx->SLR0_f.ADDRMOD0 = enAdrMode;
    if(Adr7bit == enAdrMode)
    {
        pstcI2Cx->SLR0_f.SLADDR0 = ((uint32_t)u8Adr & 0x7Ful) << 1ul;
    }
    else
    {
        pstcI2Cx->SLR0_f.SLADDR0 = (uint32_t)u8Adr;
    }
}

/**
 * \brief д����.
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 * \param[in]  dat       : ����
 *
 * \return ��
 */
am_static_inline
void amhw_hc32f460_i2c_dat_write (amhw_hc32f460_i2c_t  *p_hw_i2c,
                                  uint8_t               dat)
{
    p_hw_i2c->DTR = dat;
}

/**
 * \brief ������.
 *
 * \param[in]  p_hw_i2c  : ָ��I2C�Ĵ����ṹ���ָ��
 *
 * \return ����
 */
am_static_inline
uint8_t amhw_hc32f460_i2c_dat_read (amhw_hc32f460_i2c_t *p_hw_i2c)
{
    return (uint8_t)(p_hw_i2c->DRR);
}

am_static_inline
void amhw_hc32f460_i2c_status_clr (amhw_hc32f460_i2c_t *p_hw_i2c,
                                   uint32_t             u32StatusBit)
{
    p_hw_i2c->CLR |= (u32StatusBit & I2C_CLR_MASK);
}

am_static_inline
void amhw_hc32f460_i2c_intr_enable (amhw_hc32f460_i2c_t *p_hw_i2c,
                                    uint32_t             u32IntEn)
{
    p_hw_i2c->CR2 |= u32IntEn;
}

am_static_inline
void amhw_hc32f460_i2c_intr_disable (amhw_hc32f460_i2c_t *p_hw_i2c,
                                     uint32_t             u32IntEn)
{
    p_hw_i2c->CR2 &= ~u32IntEn;
}


am_static_inline
en_i2c_flag_status_t amhw_hc32f460_i2c_get_status(amhw_hc32f460_i2c_t *p_hw_i2c,
                                                  uint32_t             u32StatusBit)
{
    en_i2c_flag_status_t enRet = I2C_RESET;

    if(0ul != (p_hw_i2c->SR & u32StatusBit))
    {
        enRet = I2C_SET;
    }
    else
    {
        enRet = I2C_RESET;
    }

    return enRet;
}

am_static_inline
void amhw_hc32f460_i2c_generate_start(amhw_hc32f460_i2c_t      *p_hw_i2c,
                                      en_i2c_functional_state_t enNewState)
{
    p_hw_i2c->CR1_f.START = enNewState;
}

am_static_inline
void amhw_hc32f460_i2c_clear_status(amhw_hc32f460_i2c_t *p_hw_i2c,
                                    uint32_t             u32StatusBit)
{
    p_hw_i2c->CLR |= (u32StatusBit & I2C_CLR_MASK);
}

am_static_inline
void amhw_hc32f460_i2c_generate_restart(amhw_hc32f460_i2c_t      *p_hw_i2c,
                                        en_i2c_functional_state_t enNewState)
{
    p_hw_i2c->CR1_f.RESTART = enNewState;
}

am_static_inline
void amhw_hc32f460_i2c_generate_stop(amhw_hc32f460_i2c_t       *p_hw_i2c,
                                     en_i2c_functional_state_t  enNewState)
{
    p_hw_i2c->CR1_f.STOP = enNewState;
}

am_static_inline
void amhw_hc32f460_i2c_send_data(amhw_hc32f460_i2c_t *p_hw_i2c, uint8_t u8Data)
{
    p_hw_i2c->DTR = u8Data;
}

am_static_inline
void amhw_hc32f460_i2c_nack_config(amhw_hc32f460_i2c_t      *p_hw_i2c,
                                   en_i2c_functional_state_t enNewState)
{
    p_hw_i2c->CR1_f.ACK = enNewState;
}

am_static_inline
am_bool_t amhw_hc32f460_i2c_deinit(amhw_hc32f460_i2c_t *p_hw_i2c)
{
    /* Reset peripheral register and internal status*/
    p_hw_i2c->CR1_f.PE = 0u;
    p_hw_i2c->CR1_f.SWRST = 1u;
    return AM_OK;
}

am_static_inline
am_bool_t amhw_hc32f460_i2c_init(amhw_hc32f460_i2c_t  *p_hw_i2c,
                                 const stc_i2c_init_t *pstcI2C_InitStruct)
{
    am_bool_t enRes = AM_OK;
    if((NULL == pstcI2C_InitStruct) || (NULL == p_hw_i2c))
    {
        enRes = AM_FALSE;
    }
    else
    {
        /* Register and internal status reset */
        p_hw_i2c->CR1_f.PE = 0u;
        p_hw_i2c->CR1_f.SWRST = 1u;

        p_hw_i2c->CR1_f.PE = 1u;

        amhw_hc32f460_i2c_baud_config(p_hw_i2c,
                           pstcI2C_InitStruct->u32Baudrate,
                           pstcI2C_InitStruct->u32SclTime,
                           pstcI2C_InitStruct->u32Pclk3);

        p_hw_i2c->CR1_f.ENGC = 0u;
        p_hw_i2c->CR1_f.SWRST = 0u;
        p_hw_i2c->CR1_f.PE = 0u;
    }
    return enRes;
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __AMHW_HC32F460_I2C_H */

#endif

/* end of file */

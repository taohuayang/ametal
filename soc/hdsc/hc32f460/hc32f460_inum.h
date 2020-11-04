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
 * \brief HC32F460 �жϺŶ���
 *
 * \internal
 * \par Modification history
 * - 1.00 20-01-13  cds, first implementation
 * \endinternal
 */

#ifndef __HC32F460_INUM_H
#define __HC32F460_INUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \addtogroup hc32f460_if_inum
 * \copydoc hc32f460_inum.h
 * @{
 */


/**
 * \name HC32F460 CPU �ж�������
 * @{
 */

/**
 * \name HC32F460 CPU �ж���������һ
 */
#define INT_VECTOR_0    (0)
#define INT_VECTOR_1    (1)
#define INT_VECTOR_2    (2)
#define INT_VECTOR_3    (3)
#define INT_VECTOR_4    (4)
#define INT_VECTOR_5    (5)
#define INT_VECTOR_6    (6)
#define INT_VECTOR_7    (7)
#define INT_VECTOR_8    (8)
#define INT_VECTOR_9    (9)
#define INT_VECTOR_10   (10)
#define INT_VECTOR_11   (11)
#define INT_VECTOR_12   (12)
#define INT_VECTOR_13   (13)
#define INT_VECTOR_14   (14)
#define INT_VECTOR_15   (15)
#define INT_VECTOR_16   (16)
#define INT_VECTOR_17   (17)
#define INT_VECTOR_18   (18)
#define INT_VECTOR_19   (19)
#define INT_VECTOR_20   (20)
#define INT_VECTOR_21   (21)
#define INT_VECTOR_22   (22)
#define INT_VECTOR_23   (23)
#define INT_VECTOR_24   (24)
#define INT_VECTOR_25   (25)
#define INT_VECTOR_26   (26)
#define INT_VECTOR_27   (27)
#define INT_VECTOR_28   (28)
#define INT_VECTOR_29   (29)
#define INT_VECTOR_30   (30)
#define INT_VECTOR_31   (31)

/**
 * \name HC32F460 CPU �ж��������Ͷ�
 */
#define INT_VECTOR_32   (32)
#define INT_VECTOR_33   (33)
#define INT_VECTOR_34   (34)
#define INT_VECTOR_35   (35)
#define INT_VECTOR_36   (36)
#define INT_VECTOR_37   (37)
#define INT_VECTOR_38   (38)
#define INT_VECTOR_39   (39)
#define INT_VECTOR_40   (40)
#define INT_VECTOR_41   (41)
#define INT_VECTOR_42   (42)
#define INT_VECTOR_43   (43)
#define INT_VECTOR_44   (44)
#define INT_VECTOR_45   (45)
#define INT_VECTOR_46   (46)
#define INT_VECTOR_47   (47)
#define INT_VECTOR_48   (48)
#define INT_VECTOR_49   (49)
#define INT_VECTOR_50   (50)
#define INT_VECTOR_51   (51)
#define INT_VECTOR_52   (52)
#define INT_VECTOR_53   (53)
#define INT_VECTOR_54   (54)
#define INT_VECTOR_55   (55)
#define INT_VECTOR_56   (56)
#define INT_VECTOR_57   (57)
#define INT_VECTOR_58   (58)
#define INT_VECTOR_59   (59)
#define INT_VECTOR_60   (60)
#define INT_VECTOR_61   (61)
#define INT_VECTOR_62   (62)
#define INT_VECTOR_63   (63)
#define INT_VECTOR_64   (64)
#define INT_VECTOR_65   (65)
#define INT_VECTOR_66   (66)
#define INT_VECTOR_67   (67)
#define INT_VECTOR_68   (68)
#define INT_VECTOR_69   (69)
#define INT_VECTOR_70   (70)
#define INT_VECTOR_71   (71)
#define INT_VECTOR_72   (72)
#define INT_VECTOR_73   (73)
#define INT_VECTOR_74   (74)
#define INT_VECTOR_75   (75)
#define INT_VECTOR_76   (76)
#define INT_VECTOR_77   (77)
#define INT_VECTOR_78   (78)
#define INT_VECTOR_79   (79)
#define INT_VECTOR_80   (80)
#define INT_VECTOR_81   (81)
#define INT_VECTOR_82   (82)
#define INT_VECTOR_83   (83)
#define INT_VECTOR_84   (84)
#define INT_VECTOR_85   (85)
#define INT_VECTOR_86   (86)
#define INT_VECTOR_87   (87)
#define INT_VECTOR_88   (88)
#define INT_VECTOR_89   (89)
#define INT_VECTOR_90   (90)
#define INT_VECTOR_91   (91)
#define INT_VECTOR_92   (92)
#define INT_VECTOR_93   (93)
#define INT_VECTOR_94   (94)
#define INT_VECTOR_95   (95)
#define INT_VECTOR_96   (96)
#define INT_VECTOR_97   (97)
#define INT_VECTOR_98   (98)
#define INT_VECTOR_99   (99)
#define INT_VECTOR_100  (100)
#define INT_VECTOR_101  (101)
#define INT_VECTOR_102  (102)
#define INT_VECTOR_103  (103)
#define INT_VECTOR_104  (104)
#define INT_VECTOR_105  (105)
#define INT_VECTOR_106  (106)
#define INT_VECTOR_107  (107)
#define INT_VECTOR_108  (108)
#define INT_VECTOR_109  (109)
#define INT_VECTOR_110  (110)
#define INT_VECTOR_111  (111)
#define INT_VECTOR_112  (112)
#define INT_VECTOR_113  (113)
#define INT_VECTOR_114  (114)
#define INT_VECTOR_115  (115)
#define INT_VECTOR_116  (116)
#define INT_VECTOR_117  (117)
#define INT_VECTOR_118  (118)
#define INT_VECTOR_119  (119)
#define INT_VECTOR_120  (120)
#define INT_VECTOR_121  (121)
#define INT_VECTOR_122  (122)
#define INT_VECTOR_123  (123)
#define INT_VECTOR_124  (124)
#define INT_VECTOR_125  (125)
#define INT_VECTOR_126  (126)
#define INT_VECTOR_127  (127)

/**
 * \name HC32F460 CPU �ж�����������
 */
#define INT_VECTOR_128  (128)
#define INT_VECTOR_129  (129)
#define INT_VECTOR_130  (130)
#define INT_VECTOR_131  (131)
#define INT_VECTOR_132  (132)
#define INT_VECTOR_133  (133)
#define INT_VECTOR_134  (134)
#define INT_VECTOR_135  (135)
#define INT_VECTOR_136  (136)
#define INT_VECTOR_137  (137)
#define INT_VECTOR_138  (138)
#define INT_VECTOR_139  (139)
#define INT_VECTOR_140  (140)
#define INT_VECTOR_141  (141)
#define INT_VECTOR_142  (142)
#define INT_VECTOR_143  (143)

/**
 * \name HC32F460 CPU �жϺ�
 * @{
 */

#define INUM_PORT_EIRQ0      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ1      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ2      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ3      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ4      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ5      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ6      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ7      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ8      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ9      INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ10     INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ11     INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ12     INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ13     INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ14     INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_PORT_EIRQ15     INT_VECTOR_128    /**< \brief �ⲿ�ж� */
#define INUM_DMA1            INT_VECTOR_129    /**< \brief DMA1�ж� */
#define INUM_DMA2            INT_VECTOR_129    /**< \brief DMA2�ж� */
#define INUM_EFM             INT_VECTOR_129    /**< \brief EFM�ж� */
#define INUM_USBFS_SOF       INT_VECTOR_129    /**< \brief INUM_SOF�ж� */
#define INUM_QSPI            INT_VECTOR_129    /**< \brief INUM_QSPI�ж� */
#define INUM_DCU             INT_VECTOR_129    /**< \brief INUM_DCU�ж� */
#define INUM_TIMER0_1        INT_VECTOR_130    /**< \brief TIMER0_1�ж� */
#define INUM_TIMER0_2        INT_VECTOR_130    /**< \brief TIMER0_2�ж� */
#define INUM_RTC             INT_VECTOR_130    /**< \brief RTC�ж� */
#define INUM_XTAL32          INT_VECTOR_130    /**< \brief XTAL32�ж� */
#define INUM_XTAL            INT_VECTOR_130    /**< \brief XTAL�ж� */
#define INUM_WKTM            INT_VECTOR_130    /**< \brief WKTM�ж� */
#define INUM_SWDT            INT_VECTOR_130    /**< \brief SWDT�ж� */
#define INUM_TIMER6_1        INT_VECTOR_131    /**< \brief TIMER6_1�ж� */
#define INUM_TIMER6_2        INT_VECTOR_131    /**< \brief TIMER6_2�ж� */
#define INUM_TIMER6_3        INT_VECTOR_132    /**< \brief TIMER6_3�ж� */
#define INUM_TIMERA_1        INT_VECTOR_136    /**< \brief TIMERA_1�ж� */
#define INUM_TIMERA_2        INT_VECTOR_136    /**< \brief TIMERA_2�ж� */
#define INUM_TIMERA_3        INT_VECTOR_136    /**< \brief TIMERA_3�ж� */
#define INUM_TIMERA_4        INT_VECTOR_136    /**< \brief TIMERA_4�ж� */
#define INUM_TIMERA_5        INT_VECTOR_136    /**< \brief TIMERA_5�ж� */
#define INUM_TIMERA_6        INT_VECTOR_136    /**< \brief TIMERA_6�ж� */
#define INUM_USBFS_GLB       INT_VECTOR_136    /**< \brief USBFS_GLB�ж� */
#define INUM_USART1          INT_VECTOR_136    /**< \brief USART1�ж� */
#define INUM_USART2          INT_VECTOR_136    /**< \brief USART2�ж� */
#define INUM_USART3          INT_VECTOR_137    /**< \brief USART3�ж� */
#define INUM_USART4          INT_VECTOR_137    /**< \brief USART4�ж� */
#define INUM_SPI1            INT_VECTOR_137    /**< \brief SPI1�ж� */
#define INUM_SPI2            INT_VECTOR_137    /**< \brief SPI2�ж� */
#define INUM_SPI3            INT_VECTOR_137    /**< \brief SPI3�ж� */
#define INUM_SPI4            INT_VECTOR_137    /**< \brief SPI4�ж� */
#define INUM_AOS_STRG        INT_VECTOR_137    /**< \brief AOS_STRG�ж� */
#define INUM_TIMER4_1        INT_VECTOR_138    /**< \brief TIMER4_1�ж� */
#define INUM_TIMER4_2        INT_VECTOR_138    /**< \brief TIMER4_2�ж� */
#define INUM_TIMER4_3        INT_VECTOR_139    /**< \brief TIMER4_3�ж� */
#define INUM_TIMER4_1EVT     INT_VECTOR_139    /**< \brief TIMER4_1EVT�ж� */
#define INUM_TIMER4_2EVT     INT_VECTOR_139    /**< \brief TIMER4_2EVT�ж� */
#define INUM_TIMER4_3EVT     INT_VECTOR_140    /**< \brief TIMER4_2EVT�ж� */
#define INUM_TIMER4_EMB      INT_VECTOR_140    /**< \brief TIMER4_EMB�ж� */
#define INUM_EVENT_PORT1     INT_VECTOR_0      /**< \brief EVENT_PORT1�ж� */
#define INUM_EVENT_PORT2     INT_VECTOR_1      /**< \brief EVENT_PORT2�ж� */
#define INUM_EVENT_PORT3     INT_VECTOR_2      /**< \brief EVENT_PORT3�ж� */
#define INUM_EVENT_PORT4     INT_VECTOR_3      /**< \brief EVENT_PORT4�ж� */
#define INUM_I2S1            INT_VECTOR_140    /**< \brief I2S1�ж� */
#define INUM_I2S2            INT_VECTOR_140    /**< \brief I2S2�ж� */
#define INUM_I2S3            INT_VECTOR_140    /**< \brief I2S3�ж� */
#define INUM_I2S4            INT_VECTOR_140    /**< \brief I2S4�ж� */
#define INUM_ACMP1           INT_VECTOR_4      /**< \brief ACMP1�ж� */
#define INUM_ACMP2           INT_VECTOR_5      /**< \brief ACMP2�ж� */
#define INUM_ACMP3           INT_VECTOR_6      /**< \brief ACMP3�ж� */
#define INUM_USART1_WUPI     INT_VECTOR_7      /**< \brief USART1_WUPI�ж� */
#define INUM_PVD             INT_VECTOR_141    /**< \brief PVD�ж� */
#define INUM_OTS             INT_VECTOR_8      /**< \brief OTS�ж� */
#define INUM_FCM             INT_VECTOR_141    /**< \brief FCM�ж� */
#define INUM_WDT             INT_VECTOR_141    /**< \brief WDT�ж� */
#define INUM_I2C1            INT_VECTOR_141    /**< \brief I2C1�ж� */
#define INUM_I2C2            INT_VECTOR_141    /**< \brief I2C2�ж� */
#define INUM_I2C3            INT_VECTOR_141    /**< \brief I2C3�ж� */
#define INUM_ADC1            INT_VECTOR_142    /**< \brief ADC1�ж� */
#define INUM_ADC2            INT_VECTOR_142    /**< \brief ADC2�ж� */
#define INUM_TRNG            INT_VECTOR_142    /**< \brief TRNG�ж� */
#define INUM_SDIOC1          INT_VECTOR_143    /**< \brief SDIOC1�ж� */
#define INUM_SDIOC2          INT_VECTOR_143    /**< \brief SDIOC2�ж� */
#define INUM_CAN             INT_VECTOR_143    /**< \brief CAN�ж� */


/**
 * \name ������Ӧͨ�����д�����¼����
 * \anchor dma_request_src
 * @{
 */
/**
 *******************************************************************************
 ** \brief Event number enumeration
 ******************************************************************************/
typedef enum en_event_src
{
    EVT_SWI_IRQ0            = 0u,
    EVT_SWI_IRQ1            = 1u,
    EVT_SWI_IRQ2            = 2u,
    EVT_SWI_IRQ3            = 3u,
    EVT_SWI_IRQ4            = 4u,
    EVT_SWI_IRQ5            = 5u,
    EVT_SWI_IRQ6            = 6u,
    EVT_SWI_IRQ7            = 7u,
    EVT_SWI_IRQ8            = 8u,
    EVT_SWI_IRQ9            = 9u,
    EVT_SWI_IRQ10           = 10u,
    EVT_SWI_IRQ11           = 11u,
    EVT_SWI_IRQ12           = 12u,
    EVT_SWI_IRQ13           = 13u,
    EVT_SWI_IRQ14           = 14u,
    EVT_SWI_IRQ15           = 15u,
    EVT_SWI_IRQ16           = 16u,
    EVT_SWI_IRQ17           = 17u,
    EVT_SWI_IRQ18           = 18u,
    EVT_SWI_IRQ19           = 19u,
    EVT_SWI_IRQ20           = 20u,
    EVT_SWI_IRQ21           = 21u,
    EVT_SWI_IRQ22           = 22u,
    EVT_SWI_IRQ23           = 23u,
    EVT_SWI_IRQ24           = 24u,
    EVT_SWI_IRQ25           = 25u,
    EVT_SWI_IRQ26           = 26u,
    EVT_SWI_IRQ27           = 27u,
    EVT_SWI_IRQ28           = 28u,
    EVT_SWI_IRQ29           = 29u,
    EVT_SWI_IRQ30           = 30u,
    EVT_SWI_IRQ31           = 31u,

    /* External Interrupt. */
    EVT_PORT_EIRQ0          = 0u,
    EVT_PORT_EIRQ1          = 1u,
    EVT_PORT_EIRQ2          = 2u,
    EVT_PORT_EIRQ3          = 3u,
    EVT_PORT_EIRQ4          = 4u,
    EVT_PORT_EIRQ5          = 5u,
    EVT_PORT_EIRQ6          = 6u,
    EVT_PORT_EIRQ7          = 7u,
    EVT_PORT_EIRQ8          = 8u,
    EVT_PORT_EIRQ9          = 9u,
    EVT_PORT_EIRQ10         = 10u,
    EVT_PORT_EIRQ11         = 11u,
    EVT_PORT_EIRQ12         = 12u,
    EVT_PORT_EIRQ13         = 13u,
    EVT_PORT_EIRQ14         = 14u,
    EVT_PORT_EIRQ15         = 15u,

    /* DMAC */
    EVT_DMA1_TC0            = 32u,
    EVT_DMA1_TC1            = 33u,
    EVT_DMA1_TC2            = 34u,
    EVT_DMA1_TC3            = 35u,
    EVT_DMA2_TC0            = 36u,
    EVT_DMA2_TC1            = 37u,
    EVT_DMA2_TC2            = 38u,
    EVT_DMA2_TC3            = 39u,
    EVT_DMA1_BTC0           = 40u,
    EVT_DMA1_BTC1           = 41u,
    EVT_DMA1_BTC2           = 42u,
    EVT_DMA1_BTC3           = 43u,
    EVT_DMA2_BTC0           = 44u,
    EVT_DMA2_BTC1           = 45u,
    EVT_DMA2_BTC2           = 46u,
    EVT_DMA2_BTC3           = 47u,

    /* EFM */
    EVT_EFM_OPTEND          = 52u,

    /* USB SOF */
    EVT_USBFS_SOF           = 53u,

    /* DCU */
    EVT_DCU1                = 55u,
    EVT_DCU2                = 56u,
    EVT_DCU3                = 57u,
    EVT_DCU4                = 58u,

    /* TIMER 0 */
    EVT_TMR01_GCMA          = 64u,
    EVT_TMR01_GCMB          = 65u,
    EVT_TMR02_GCMA          = 66u,
    EVT_TMR02_GCMB          = 67u,

    /* RTC */
    EVT_RTC_ALM             = 81u,
    EVT_RTC_PRD             = 82u,

    /* TIMER 6 */
    EVT_TMR61_GCMA          = 96u,
    EVT_TMR61_GCMB          = 97u,
    EVT_TMR61_GCMC          = 98u,
    EVT_TMR61_GCMD          = 99u,
    EVT_TMR61_GCME          = 100u,
    EVT_TMR61_GCMF          = 101u,
    EVT_TMR61_GOVF          = 102u,
    EVT_TMR61_GUDF          = 103u,
    EVT_TMR61_SCMA          = 107u,
    EVT_TMR61_SCMB          = 108u,
    EVT_TMR62_GCMA          = 112u,
    EVT_TMR62_GCMB          = 113u,
    EVT_TMR62_GCMC          = 114u,
    EVT_TMR62_GCMD          = 115u,
    EVT_TMR62_GCME          = 116u,
    EVT_TMR62_GCMF          = 117u,
    EVT_TMR62_GOVF          = 118u,
    EVT_TMR62_GUDF          = 119u,
    EVT_TMR62_SCMA          = 123u,
    EVT_TMR62_SCMB          = 124u,
    EVT_TMR63_GCMA          = 128u,
    EVT_TMR63_GCMB          = 129u,
    EVT_TMR63_GCMC          = 130u,
    EVT_TMR63_GCMD          = 131u,
    EVT_TMR63_GCME          = 132u,
    EVT_TMR63_GCMF          = 133u,
    EVT_TMR63_GOVF          = 134u,
    EVT_TMR63_GUDF          = 135u,
    EVT_TMR63_SCMA          = 139u,
    EVT_TMR63_SCMB          = 140u,

    /* TIMER A */
    EVT_TMRA1_OVF           = 256u,
    EVT_TMRA1_UDF           = 257u,
    EVT_TMRA1_CMP           = 258u,
    EVT_TMRA2_OVF           = 259u,
    EVT_TMRA2_UDF           = 260u,
    EVT_TMRA2_CMP           = 261u,
    EVT_TMRA3_OVF           = 262u,
    EVT_TMRA3_UDF           = 263u,
    EVT_TMRA3_CMP           = 264u,
    EVT_TMRA4_OVF           = 265u,
    EVT_TMRA4_UDF           = 266u,
    EVT_TMRA4_CMP           = 267u,
    EVT_TMRA5_OVF           = 268u,
    EVT_TMRA5_UDF           = 269u,
    EVT_TMRA5_CMP           = 270u,
    EVT_TMRA6_OVF           = 272u,
    EVT_TMRA6_UDF           = 273u,
    EVT_TMRA6_CMP           = 274u,

    /* USART */
    EVT_USART1_EI           = 278u,
    EVT_USART1_RI           = 279u,
    EVT_USART1_TI           = 280u,
    EVT_USART1_TCI          = 281u,
    EVT_USART1_RTO          = 282u,
    EVT_USART2_EI           = 283u,
    EVT_USART2_RI           = 284u,
    EVT_USART2_TI           = 285u,
    EVT_USART2_TCI          = 286u,
    EVT_USART2_RTO          = 287u,
    EVT_USART3_EI           = 288u,
    EVT_USART3_RI           = 289u,
    EVT_USART3_TI           = 290u,
    EVT_USART3_TCI          = 291u,
    EVT_USART3_RTO          = 292u,
    EVT_USART4_EI           = 293u,
    EVT_USART4_RI           = 294u,
    EVT_USART4_TI           = 295u,
    EVT_USART4_TCI          = 296u,
    EVT_USART4_RTO          = 297u,

    /* SPI */
    EVT_SPI1_SRRI           = 299u,
    EVT_SPI1_SRTI           = 300u,
    EVT_SPI1_SPII           = 301u,
    EVT_SPI1_SPEI           = 302u,
    EVT_SPI1_SPTEND         = 303u,
    EVT_SPI2_SRRI           = 304u,
    EVT_SPI2_SRTI           = 305u,
    EVT_SPI2_SPII           = 306u,
    EVT_SPI2_SPEI           = 307u,
    EVT_SPI2_SPTEND         = 308u,
    EVT_SPI3_SRRI           = 309u,
    EVT_SPI3_SRTI           = 310u,
    EVT_SPI3_SPII           = 311u,
    EVT_SPI3_SPEI           = 312u,
    EVT_SPI3_SPTEND         = 313u,
    EVT_SPI4_SRRI           = 314u,
    EVT_SPI4_SRTI           = 315u,
    EVT_SPI4_SPII           = 316u,
    EVT_SPI4_SPEI           = 317u,
    EVT_SPI4_SPTEND         = 318u,

    /* AOS */
    EVT_AOS_STRG            = 319u,

    /* TIMER 4 */
    EVT_TMR41_SCMUH         = 368u,
    EVT_TMR41_SCMUL         = 369u,
    EVT_TMR41_SCMVH         = 370u,
    EVT_TMR41_SCMVL         = 371u,
    EVT_TMR41_SCMWH         = 372u,
    EVT_TMR41_SCMWL         = 373u,
    EVT_TMR42_SCMUH         = 374u,
    EVT_TMR42_SCMUL         = 375u,
    EVT_TMR42_SCMVH         = 376u,
    EVT_TMR42_SCMVL         = 377u,
    EVT_TMR42_SCMWH         = 378u,
    EVT_TMR42_SCMWL         = 379u,
    EVT_TMR43_SCMUH         = 384u,
    EVT_TMR43_SCMUL         = 385u,
    EVT_TMR43_SCMVH         = 386u,
    EVT_TMR43_SCMVL         = 387u,
    EVT_TMR43_SCMWH         = 388u,
    EVT_TMR43_SCMWL         = 389u,

    /* EVENT PORT */
    EVT_EVENT_PORT1         = 394u,
    EVT_EVENT_PORT2         = 395u,
    EVT_EVENT_PORT3         = 396u,
    EVT_EVENT_PORT4         = 397u,

    /* I2S */
    EVT_I2S1_TXIRQOUT       = 400u,
    EVT_I2S1_RXIRQOUT       = 401u,
    EVT_I2S2_TXIRQOUT       = 403u,
    EVT_I2S2_RXIRQOUT       = 404u,
    EVT_I2S3_TXIRQOUT       = 406u,
    EVT_I2S3_RXIRQOUT       = 407u,
    EVT_I2S4_TXIRQOUT       = 409u,
    EVT_I2S4_RXIRQOUT       = 410u,

    /* COMPARATOR */
    EVT_ACMP1               = 416u,
    EVT_ACMP2               = 417u,
    EVT_ACMP3               = 418u,

    /* I2C */
    EVT_I2C1_RXI            = 420u,
    EVT_I2C1_TXI            = 421u,
    EVT_I2C1_TEI            = 422u,
    EVT_I2C1_EE1            = 423u,
    EVT_I2C2_RXI            = 424u,
    EVT_I2C2_TXI            = 425u,
    EVT_I2C2_TEI            = 426u,
    EVT_I2C2_EE1            = 427u,
    EVT_I2C3_RXI            = 428u,
    EVT_I2C3_TXI            = 429u,
    EVT_I2C3_TEI            = 430u,
    EVT_I2C3_EE1            = 431u,

    /* PVD */
    EVT_PVD_PVD1            = 433u,
    EVT_PVD_PVD2            = 434u,

    /* OTS */
    EVT_OTS                 = 435u,

    /* WDT */
    EVT_WDT_REFUDF          = 439u,

    /* ADC */
    EVT_ADC1_EOCA           = 448u,
    EVT_ADC1_EOCB           = 449u,
    EVT_ADC1_CHCMP          = 450u,
    EVT_ADC1_SEQCMP         = 451u,
    EVT_ADC2_EOCA           = 452u,
    EVT_ADC2_EOCB           = 453u,
    EVT_ADC2_CHCMP          = 454u,
    EVT_ADC2_SEQCMP         = 455u,

    /* TRNG */
    EVT_TRNG_END            = 456u,

    /* SDIO */
    EVT_SDIOC1_DMAR         = 480u,
    EVT_SDIOC1_DMAW         = 481u,
    EVT_SDIOC2_DMAR         = 483u,
    EVT_SDIOC2_DMAW         = 484u,
    EVT_MAX                 = 511u,
}en_event_src_t;


/** @} */

/**
 * \brief ���ж���Ϊ��(INUM_USB - INUM_WWDT + 1),
 *
 */
#define INUM_INTERNAL_COUNT     (144)

/**
 * \brief ����жϺ�Ϊ�� INUM_USB
 */
#define INUM_INTERNAL_MAX        INUM_CAN

/** \brief ��С�жϺ�: INUM_WWDT */
#define INUM_INTERNAL_MIN        0

/**
 * \cond
 * �жϺŶ��壬Ϊ core_cm4.h�ļ�����
 */
typedef enum {

    /* ----------------------  Cortex-M4���쳣��  ------------------- */

    /** \brief 2  ���������ж�, ���ܱ�ֹͣ����ռ */
    NonMaskableInt_IRQn      = -14,

    /** \brief 3  Ӳ�������ж� */
    HardFault_IRQn           = -13,

    /** \brief 4  �ڴ�����ж� */
    MemManage                = -12,

    /** \brief 5  ���ߴ����ж� */
    BusFault                 = -11,

    /** \brief 6  �û������ж� */
    UsageFault               = -10,

    /** \brief 11  ϵͳ�������ͨ��SVCָ�� */
    SVCall_IRQn              =  -5,

    /** \brief 14  ϵͳ�Ĺ������� */
    PendSV_IRQn              =  -2,

    /** \brief 15  ϵͳ�δ�ʱ�� */
    SysTick_IRQn             =  -1,

    /******  ZLG217 Specific Interrupt Numbers *******************************************************/
//    WWDG_IRQn                 = 0,         /**< \brief ���ڶ�ʱ���ж� */
//    PVD_IRQn                  =1,         /**< \brief ��Դ��ѹ����ж� */
//    TAMPER_IRQn               =2,         /**< \brief �������ж� */
//    RTC_IRQn                  =3,         /**< \brief ʵʱʱ�ӣ�RTC��ȫ���ж� */
//    FLASH_IRQn                =4,         /**< \brief ����ȫ���ж� */
//    RCC_IRQn                  =5,         /**< \brief ��λ��ʱ�ӿ��ƣ�RCC���ж� */
//    EXTI0_IRQn                =6,         /**< \brief EXTI��0�ж� */
//    EXTI1_IRQn                =7,         /**< \brief EXTI��1�ж� */
//    EXTI2_IRQn                =8,         /**< \brief EXTI��2�ж� */
//    EXTI3_IRQn                =9,         /**< \brief EXTI��3�ж� */
//    EXTI4_IRQn                =10,        /**< \brief EXTI��4�ж� */
//    DMA1_1_IRQn               =11,        /**< \brief DMA1ͨ��1ȫ���ж� */
//    DMA1_2_IRQn               =12,        /**< \brief DMA1ͨ��2ȫ���ж� */
//    DMA1_3_IRQn               =13,        /**< \brief DMA1ͨ��3ȫ���ж� */
//    DMA1_4_IRQn               =14,        /**< \brief DMA1ͨ��4ȫ���ж� */
//    DMA1_5_IRQn               =15,        /**< \brief DMA1ͨ��5ȫ���ж� */
//    DMA1_6_IRQn               =16,        /**< \brief DMA1ͨ��6ȫ���ж� */
//    DMA1_7_IRQn               =17,        /**< \brief DMA1ͨ��7ȫ���ж� */
//    ADC1_2_IRQn               =18,        /**< \brief ADC1��ADC2��ȫ���ж� */
//    USB_IRQn                  =19,        /**< \brief USB�ж� */
//    Reserved0                 =20,        /**< \brief RESERVED */
//    CAN_RX1_IRQn              =21,        /**< \brief CAN����1�ж� */
//    Reserved1                 =22,        /**< \brief RESERVED */
//    EXTI9_5_IRQn              =23,        /**< \brief EXTI��[9��5]�ж� */
//    TIM1_BRK_IRQn             =24,        /**< \brief TIM1�Ͽ��ж� */
//    TIM1_UP_IRQn              =25,        /**< \brief TIM1�����ж� */
//    TIM1_TRG_COM_IRQn         =26,        /**< \brief TIM1������ͨ���ж� */
//    TIM1_CC_IRQn              =27,        /**< \brief TIM1����Ƚ��ж� */
//    TIM2_IRQn                 =28,        /**< \brief TIM2ȫ���ж� */
//    TIM3_IRQn                 =29,        /**< \brief TIM3ȫ���ж� */
//    TIM4_IRQn                 =30,        /**< \brief TIM14ȫ���ж� */
//    I2C1_EV_IRQn              =31,        /**< \brief I2C1�¼��ж� */
//    Reserved2                 =32,        /**< \brief RESERVED */
//    I2C2_EV_IRQn              =33,        /**< \brief I2C1�¼��ж� */
//    Reserved3                 =34,        /**< \brief RESERVED */
//    SPI1_IRQn                 =35,        /**< \brief SPI1ȫ���ж� */
//    SPI2_IRQn                 =36,        /**< \brief SPI2ȫ���ж� */
//    UART1_IRQn                =37,        /**< \brief UART1ȫ���ж� */
//    UART2_IRQn                =38,        /**< \brief UART2ȫ���ж� */
//    UART3_IRQn                =39,        /**< \brief UART3ȫ���ж� */
//    EXTI15_10_IRQn            =40,        /**< \brief EXTI��[15��10]�ж� */
//    RTCAlarm_IRQn             =41,        /**< \brief ����EXTI17��RTC�����ж� */
//    USB_WK_IRQn               =42,        /**< \brief ����EXTI18�Ĵ�USB���������ж� */
//    Reserved4                 =43,        /**< \brief RESERVED */
//    Reserved5                 =44,        /**< \brief RESERVED */
//    AES_IRQn                  =45,        /**< \brief AESȫ���ж� */
} IRQn_Type;

/**
 * \endcond
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F460_INUM_H */

/* end of file */

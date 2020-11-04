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
 * \brief �����������ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� am_sensor.h
 *
 * \internal
 * \par modification history
 * - 1.00 18-11-20  wan, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_H
#define __AM_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup grp_am_if_sensor
 * \copydoc am_sensor.h
 * @{
 */

/**
 * \name ���������Ͷ���
 * @{
 */
#define AM_SENSOR_TYPE_VOLTAGE     (1)  /**< \brief ��ѹ����λ: V             */
#define AM_SENSOR_TYPE_CURRENT     (2)  /**< \brief ��������λ: A             */
#define AM_SENSOR_TYPE_TEMPERATURE (3)  /**< \brief �¶ȣ���λ: ���϶�        */
#define AM_SENSOR_TYPE_PRESS       (4)  /**< \brief ѹǿ����λ: ��˹��        */
#define AM_SENSOR_TYPE_LIGHT       (5)  /**< \brief ���նȣ���λ: �տ�˹      */
#define AM_SENSOR_TYPE_ALTITUDE    (6)  /**< \brief ���Σ���λ: ��            */
#define AM_SENSOR_TYPE_DISTANCE    (7)  /**< \brief ���룬��λ: ��            */

/** \brief ֱ��<=1um��΢��Ũ�ȣ���λ: ug/m^3 */
#define AM_SENSOR_TYPE_PM_1             (100)

/** \brief ֱ��<=2.5um��΢��Ũ�ȣ���λ: ug/m^3 */
#define AM_SENSOR_TYPE_PM_2_5           (101)

/** \brief ֱ��<=10um��΢��Ũ�ȣ���λ: ug/m^3 */
#define AM_SENSOR_TYPE_PM_10            (102)

/** \brief ���ʪ�ȣ�ֵΪ�ٷֱȣ�1��ʾ 1% */
#define AM_SENSOR_TYPE_HUMIDITY         (103)

/** \brief �ӽ�ʽ����������ֵ�źţ�1 ��ʾ�нӽ��� */
#define AM_SENSOR_TYPE_PROXIMITY        (104)

/** \brief ���򣬽Ƕ��� 0/90/180/270 �ֱ��ʾ����/����/����/���� */
#define AM_SENSOR_TYPE_ORIENT           (105)

/** \brief ������ */
#define AM_SENSOR_TYPE_ALS              (106)

/** \brief �����⣬�ɼ��� */
#define AM_SENSOR_TYPE_ALS_VISIBLE      (107)

/** \brief �����⣬����� */
#define AM_SENSOR_TYPE_ALS_IR           (108)

/** \brief ���� */
#define AM_SENSOR_TYPE_GESTURE          (109)

/** \brief ���� */
#define AM_SENSOR_TYPE_SPECTRAL         (110)

/**
 * \brief ���ٶȣ���λ: m/s^2
 *
 * ���ִ��������Լ��������ļ��ٶȣ����磺x,y,z �ᣬ��������£���ʹ��ͨ����
 * ���ֲ�ͬ����ļ��ٶȣ�x��y��z ��ʾ�˲�ͬ��ͨ����
 */
#define AM_SENSOR_TYPE_ACCELEROMETER    (200)

/**
 * \brief ���ٶȣ������ǲ���������λ: rad/s
 *
 * ���ִ��������Լ��������Ľ��ٶȣ����磺x,y,z �ᣬ��������£���ʹ��ͨ����
 * ���ֲ�ͬ����Ľ��ٶȣ�x��y��z ��ʾ�˲�ͬ��ͨ����
 */
#define AM_SENSOR_TYPE_GYROSCOPE        (201)

/**
 * \brief �Ÿ�Ӧǿ�ȣ���λ: ��˹
 *
 * ���ִ��������Լ��������ĴŸ�Ӧǿ�ȣ����磺x,y,z �ᣬ��������£���ʹ��ͨ
 * �������ֲ�ͬ����ĴŸ�Ӧǿ�ȣ�x��y��z ��ʾ�˲�ͬ��ͨ����
 */
#define AM_SENSOR_TYPE_MAGNETIC         (202)

/**
 * \brief ��תʸ��(Rotation Vector)���Ƕ��ơ�
 *
 * ��תʸ��ͨ����Ϊ����������������ת�Ƕȣ� x,y,z �ᣬ��������£���ʹ��ͨ
 * �������ֲ�ͬ�ķ���
 */
#define AM_SENSOR_TYPE_ROTATION_VECTOR  (203)

/** @} */

/**
 * \name ����������ģʽ����
 * @{
 */

/**
 * \brief ����׼����������
 */
#define AM_SENSOR_TRIGGER_DATA_READY   (1ul << 0)

/**
 * \brief ���޴���
 *
 * ��������Σ������ﵽ #AM_SENSOR_ATTR_DURATION_DATA ����ֵ���������ݾ���������
 *�� #AM_SENSOR_ATTR_THRESHOLD_UPPER ����ֵ�����������
 *�� #AM_SENSOR_ATTR_THRESHOLD_LOWER ����ֵ��ʱ������
 */
#define AM_SENSOR_TRIGGER_THRESHOLD    (1ul << 1)

/**
 * \brief ������б�ʣ�����
 *
 * ��������Σ������ﵽ #AM_SENSOR_ATTR_DURATION_SLOPE ����ֵ������������
 * ������һ�β������ݵ������������������ޣ� #AM_SENSOR_ATTR_THRESHOLD_SLOPE ��ʱ
 * ������
 */
#define AM_SENSOR_TRIGGER_SLOPE        (1ul << 2)

/**
 * \brief �������͵Ĵ���
 *
 * ��ӽ�ʽ���������������⴫���������ഫ�����������ź��Ƕ�ֵ�źţ���ֵΪ��ʱ
 *����0��������
 */
#define AM_SENSOR_TRIGGER_BOOL         (1ul << 3)

/** @} */

/**
 * \name ������ͨ�����Զ���
 * @{
 */

/** \brief ����Ƶ�ʣ�ÿ������Ĵ��� */
#define AM_SENSOR_ATTR_SAMPLING_RATE          (1)

/** \brief ������ֵ */
#define AM_SENSOR_ATTR_FULL_SCALE             (2)

/** \brief ƫ��ֵ�����ھ�̬У׼���������ݣ����������� = ʵ�ʲ���ֵ + offset */
#define AM_SENSOR_ATTR_OFFSET                 (3)

/** \brief �����ޣ��������޴���ģʽ�����ݵ��ڸ�ֵʱ���� */
#define AM_SENSOR_ATTR_THRESHOLD_LOWER        (4)

/** \brief �����ޣ��������޴���ģʽ�����ݸ��ڸ�ֵʱ���� */
#define AM_SENSOR_ATTR_THRESHOLD_UPPER        (5)

/** \brief �������ޣ������������������ݱ仯���죨б�ʹ��󣩣�������ֵʱ���� */
#define AM_SENSOR_ATTR_THRESHOLD_SLOPE        (6)

/**
 * \brief �������ݳ����������������޴���ģʽ
 *
 * ����ֵ��Чʱ�����ʾ������Σ������ﵽ������ֵ���������ݾ��������޻��������
 * ʱ�Ŵ�����
 */
#define AM_SENSOR_ATTR_DURATION_DATA          (7)

/**
 * \brief ��������������������������ģʽ
 *
 * ����ֵ��Чʱ�����ʾ������Σ������ﵽ������ֵ�����������������һ�β�������
 * ��������������������ʱ�Ŵ�����
 */
#define AM_SENSOR_ATTR_DURATION_SLOPE         (8)

/** @} */

/**
 * \name ��λ���壬���ڴ��������ݵ� unit ����
 *
 * \anchor table_unit
 *
 * \par ������λǰ׺��
 *
 * | ָ����10���ݣ� | ���ţ�Symbol�� | Ӣ��ǰ׺ |  ���Ķ���  |
 * | :------------: | :----------- : | :------: |:---------: |
 * |       24       |        Y       |   Yotta  |  Ң������  |
 * |       21       |        Z       |   Zetta  |  ������  |
 * |       18       |        E       |    Exa   | ���������� |
 * |       15       |        P       |   Peta   |  �ģ�����  |
 * |       12       |        T       |   Tera   |  ̫������  |
 * |        9       |        G       |   Giga   |  ��������  |
 * |        6       |        M       |   Mega   |     ��     |
 * |        3       |        k       |   kilo   |     ǧ     |
 * |        2       |        h       |   hecto  |     ��     |
 * |        1       |        da      |   deca   |     ʮ     |
 * |        0       |        -       |     -    |     -      |
 * |       -1       |        d       |   deci   |     ��     |
 * |       -2       |        c       |   centi  |     ��     |
 * |       -3       |        m       |   milli  |     ��     |
 * |       -6       |        ��       |   micro  |     ΢     |
 * |       -9       |        n       |   nano   |  �ɣ�ŵ��  |
 * |       -12      |        p       |   pico   |  Ƥ���ɣ�  |
 * |       -15      |        f       |   femto  | �ɣ�ĸ�У� |
 * |       -18      |        a       |   atto   |  �����У�  |
 * |       -21      |        z       |   zepto  | �ƣ����У� |
 * |       -24      |        y       |   yocto  | �ۣ����У� |
 *
 * \note
 *
 *  - ָ������ 10���ݣ����磬24��ʾ 10^24��ָ��ͨ����3Ϊ���������1000��Ϊ�����
 *  - ����Symbol�����ִ�Сд����ָ����ǰ׺�����У���������Ϊ��д��Ψ���� kilo
 * �ķ��� "k" ��Сд���������ڴ����¶ȵķ��ţ���д�� "K"��
 *  - ǰ׺������Ӣ�ĵ����У�ͨ�����Ӹ�ǰ׺��ʾ�����������磬���ȵ�λ�׵�Ӣ�ĵ���
 * Ϊ��meter����ǧ�׶�Ӧ�ĵ���Ϊ��kilometer��
 *  - ���Ķ������У������ڵ����ڲ��»���������¿���ʡ�ԡ�
 *  - �٣�10^2����ʮ��10^1�����֣�10 ^-1�����壨10^-2������ʹ�á�
 * @{
 */

#define AM_SENSOR_UNIT_YOTTA      (24)       /**< \brief Ң��������10^(24)    */
#define AM_SENSOR_UNIT_ZETTA      (21)       /**< \brief ��������10^(21)    */
#define AM_SENSOR_UNIT_EXA        (18)       /**< \brief ������������10^(18)  */
#define AM_SENSOR_UNIT_PETA       (15)       /**< \brief �ģ�������10^(15)    */
#define AM_SENSOR_UNIT_TERA       (12)       /**< \brief ̫��������10^(12)    */
#define AM_SENSOR_UNIT_GIGA       (9)        /**< \brief ����������10^(9)     */
#define AM_SENSOR_UNIT_MEGA       (6)        /**< \brief �ף�10^(6)           */
#define AM_SENSOR_UNIT_KILO       (3)        /**< \brief ǧ��10^(3)           */
#define AM_SENSOR_UNIT_HECTO      (2)        /**< \brief �٣�10^(2)           */
#define AM_SENSOR_UNIT_DECA       (1)        /**< \brief ʮ��10^(1)           */
#define AM_SENSOR_UNIT_BASE       (0)        /**< \brief ����10^(0)������Ϊ1  */
#define AM_SENSOR_UNIT_DECI       (-1)       /**< \brief �֣�10^(-1)          */
#define AM_SENSOR_UNIT_CENTI      (-2)       /**< \brief �壬10^(-2)          */
#define AM_SENSOR_UNIT_MILLI      (-3)       /**< \brief ����10^(-3)          */
#define AM_SENSOR_UNIT_MICRO      (-6)       /**< \brief ΢��10^(-6)          */
#define AM_SENSOR_UNIT_NANO       (-9)       /**< \brief �ɣ�ŵ����10^(-9)    */
#define AM_SENSOR_UNIT_PICO       (-12)      /**< \brief Ƥ���ɣ���10^(-12)   */
#define AM_SENSOR_UNIT_FEMTO      (-15)      /**< \brief �ɣ�ĸ�У���10^(-15) */
#define AM_SENSOR_UNIT_ATTO       (-18)      /**< \brief �����У���10^(-18)   */
#define AM_SENSOR_UNIT_ZEPTO      (-21)      /**< \brief �ƣ����У���10^(-21) */
#define AM_SENSOR_UNIT_YOCTO      (-24)      /**< \brief �ۣ����У���10^(-24) */

#define AM_SENSOR_UNIT_INVALID    (-32768)   /**< \brief ��Чֵ������       */

/** @} */

/** \brief �������жϴ�����ĳһͨ���������Ƿ���Ч����ֵΪ��ʱ��Ч��������Ч */
#define AM_SENSOR_VAL_IS_VALID(data)    \
             ((data).unit != (int32_t)(AM_SENSOR_UNIT_INVALID))

/**
 * \brief �����꣬��ȡһ����λ��Ӧ��ǰ׺���ţ���"M"���ף���"k"��ǧ��
 *
 * \param[in] unit : ��λ��AM_SENSOR_UNIT_* (eg: #AM_SENSOR_UNIT_MILLI)
 *
 * \return �����ַ���������λ��Ч���򷵻�NULL����unitΪ0(#AM_SENSOR_UNIT_BASE)
 * �򷵻ؿ��ַ���: ""���ر�ע�⣬�������ص���һ���ַ�����������һ���ַ�����Ϊ
 * ���ֵ�λ�ķ��ſ�����������ĸ���磺"da"��ʮ����
 */
#define AM_SENSOR_UNIT_SYMBOL_GET(unit) am_sensor_unit_symbol_get(unit)

/**
 * \name �ص��������Ͷ���
 * @{
 */

/**
 * \brief �������ص���������
 *
 * \param[in] p_arg       : �û����ûص�����ʱָ�����û�����
 * \param[in] trigger_src : ����Դ��AM_SENSOR_TRIGGER_*�������Ƕ����Ļ�ֵ��
 *
 * \return ��
 */
typedef void (*am_sensor_trigger_cb_t) (void *p_arg, uint32_t trigger_src);

/** @} */

/**
 * \brief ��������������
 *
 * ʵ���У����������ݿ���ΪС����Ϊ�˱���Ӱ��ϵͳ���ܣ�AMetal������ֱ��ʹ�ø���
 * ��������ʹ�á������� + ����λ������ʾһ�����������ݡ���ʵ�ʴ���������ΪС��ʱ��ֻ
 * ��ʹ�ø�С�ĵ�λ����ʾ���ݣ����ɽ�ʹ����������ȫ����С����
 *
 * ���磬һ����ѹ�������ɼ����ĵ�ѹΪ1.234V����ѹ�Ļ�����λΪV������ÿ�ִ�������
 * �Ͷ�Ӧ�Ļ�����λ�ڶ��崫�������ͺ�ʱ������˵������Ϊ�˱���С�������䵥λ��С
 * Ϊ mV����Ϊ��1234 mV��
 *
 * ����ʹ���� val �� unit �����з������ֱ��ʾ���������ݵ�ֵ�ĵ�λ��
 *
 * - val  : ����������ֵ���з���32λ����
 * - unit ����λ����"M"���ף���"k"��ǧ����"m"��������"��"��΢���� "p"��Ƥ���ȵȡ�
 * ��λʹ��10���ݽ��б�ʾ����"M"��ʾ10^6����unit��ֵΪ6��ͨ������£�unitΪ������
 * �Ա�ʾ��ȷ��С�����λ��
 *
 * ���轫����������ͳһΪ������λ���罫��ѹ����ȫ��ͳһΪ��λV�������ͨ�����¹�
 * ʽ��ɣ�data = val * (10 ^ unit)�����͵ļ����������±�:
 *
 * |   data����ʵֵ����ѹ: V�� |    val    |   unit   |
 * | :-----------------------: | :-------: | :------: |
 * |           2.854           |  2854     |  -3(mV)  |
 * |           1.7             |  1700     |  -3(mV)  |
 * |           2.3433          |  2343300  |  -6(��V)  |
 * |           2888000         |  2888     |   3(kV)  |
 * |           0               |     0     |     0    |
 * |          -2888000         |  -2888    |   3(kV)  |
 * |          -2.3433          |  -2343300 |  -6(��V)  |
 * |          -2.854           |  -2854    |  -3(mV)  |
 * |          -1.7             |  -1700    |  -3(mV)  |
 *
 * \attention �� unit ��ֵΪ -32768 ʱ�����ʾ��ֵΪ��Ч�Ĵ��������ݡ���ʹ����
 * ��group����ؽӿڲ������������ͨ��ʱ��������ֵ��ΪAM_OK�����ʾĳЩͨ������
 * ʧ�ܣ�ʧ�ܵ�ͨ����Ӧ�Ĵ�����ֵ�������Ϊ��Чֵ��ʹ�� AM_SENSOR_VAL_IS_VALID()
 * ����Կ����ж�ֵ�Ƿ���Ч������ʱ��val��ԱΪ��׼�����룬���Ծݴ��ж�ʧ�ܵ�ԭ��
 */
typedef struct am_sensor_val {

    /**
     * \brief ��������ֵ����Ч��Χ��-2147483648 ~ 2147483647
     *
     * �ر�أ��� unit ��ֵΪ (#AM_SENSOR_UNIT_INVALID) ʱ����ʾ��ֵΪ��Ч�Ĵ���
     * ����ֵ����ʱ��val��Ա��ֵ��ʾ��׼�����룬�Ը����û��жϲ���ʧ�ܵ�ԭ��
     * ���磬-AM_ENODEV ��ʾ������ͨ��id�����ڣ��޶�Ӧ�������豸��
     */
    int32_t   val;

    /**
     * \brief ��λ
     *
     * ʹ��ָ����10���ݣ���ʾ�����磺6��ʾ10^6������"M"���ף���3��ʾ10^3��
     * ����"k"��ǧ����-3��ʾ10^-3������"m"��������
     *
     * ������ֱ��ʹ�����֣�����ʹ���Ѿ�����õĵ�λ�꣺AM_SENSOR_UNIT_*
     * (eg: #AM_SENSOR_UNIT_MILLI)
     *
     * �ر�ע�⣬��ֵΪ (#AM_SENSOR_UNIT_INVALID) ʱ����ʾ��ֵΪ��Ч�Ĵ�������ֵ��
     * ��ʱ��val��Ա��ֵ��ʾ��׼�����룬�Ը����û��жϲ���ʧ�ܵ�ԭ��
     *
     * ͨ������£���λ�Ӳ��淴ӳ��һ���������ľ��ȣ���ˣ���һ�������������̲�
     * �䣬��ô��������ݵĵĵ�λһ��Ҳ����ı䡣
     */
    int32_t   unit;

} am_sensor_val_t;

/**
 * \brief ���������������ṹ��
 */
struct am_sensor_drv_funcs {

    /** \brief ��ȡ�ô�����ĳһͨ�������� */
    am_err_t (*pfn_type_get)(void *p_drv, int id);

    /** \brief ��ȡ������ͨ���������� */
    am_err_t (*pfn_data_get)(void            *p_drv,
                             const int       *p_ids,
                             int              num,
                             am_sensor_val_t *p_buf);

    /** \brief ʹ�ܴ�����ͨ�� */
    am_err_t (*pfn_enable)(void            *p_drv,
                           const int       *p_ids,
                           int              num,
                           am_sensor_val_t *p_result);

    /** \brief ���ܴ�����ͨ�� */
    am_err_t (*pfn_disable)(void            *p_drv,
                            const int       *p_ids,
                            int              num,
                            am_sensor_val_t *p_result);

    /** \brief ���ô�����ͨ������ */
    am_err_t (*pfn_attr_set)(void                  *p_drv,
                             int                    id,
                             int                    attr,
                             const am_sensor_val_t *p_val);

    /** \brief ��ȡ������ͨ������ */
    am_err_t (*pfn_attr_get)(void            *p_drv,
                             int              id,
                             int              attr,
                             am_sensor_val_t *p_val);

    /** \brief ���ô�����һ��ͨ����������һ�������ص����� */
    am_err_t (*pfn_trigger_cfg)(void                   *p_drv,
                                int                     id,
                                uint32_t                flags,
                                am_sensor_trigger_cb_t  pfn_cb,
                                void                   *p_arg);

    /** \brief �򿪴��� */
    am_err_t (*pfn_trigger_on)(void *p_drv, int id);

    /** \brief �رմ��� */
    am_err_t (*pfn_trigger_off)(void *p_drv, int id);

};

/**
 * \brief sensor����
 */
typedef struct am_sensor_serv {

    /** \brief sensor���������ṹ��ָ��    */
    const struct am_sensor_drv_funcs *p_funcs;

    /** \brief �������������ĵ�һ������  */
    void                             *p_drv;
    
} am_sensor_serv_t;

/** \brief sensor��׼�������������Ͷ���  */
typedef am_sensor_serv_t *am_sensor_handle_t;

/**
 * \brief ��ȡ������ĳһͨ�������ͣ����磺�¶ȡ�ʪ�ȡ�ѹǿ��
 *
 * һ�������������ṩ��·���ݲɼ�ͨ������ÿ��ͨ�������Ϳ��ܲ�ͬ�����磺�¶ȡ�
 * ʪ�ȡ�ѹǿ��֮�֣���ʹ�øýӿڿ��Կ��ٻ�ȡ�ô�����ĳһͨ��������(��ÿ��������
 * ��ID����0��ʼ���α��)��
 *
 * \param[in] handle : ��������׼������
 * \param[in] id     : ������ͨ�� id
 *
 * \retval  >=0       ���������ͣ�AM_SENSOR_TYPE_*(eg: #AM_SENSOR_TYPE_VOLTAGE)
 * \retval -AM_ENODEV ͨ��������
 * \retval -AM_EINVAL ��Ч����
 */
am_static_inline
am_err_t am_sensor_type_get (am_sensor_handle_t handle, int id)
{
    return handle->p_funcs->pfn_type_get(handle->p_drv, id);
}

/**
 * \brief �Ӵ�����ָ��ͨ����ȡ��������
 *
 * \param[in]  handle   ����������׼������
 * \param[in]  p_ids    ��������ͨ�� id�б�
 * \param[in]  num      ��ͨ����Ŀ
 * \param[out] p_buf    ����������������������������� num һ��
 *
 * \retval  AM_OK     �ɹ���һ������ͨ�����ݶ�ȡ�ɹ�
 * \retval -AM_ENODEV ���ֻ�����ͨ��������
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EPERM  ����������
 * \retval   <0       ���ֻ�����ͨ����ȡʧ��
 *
 * \note p_ids�б���ܰ������ͨ����p_buf�л�ȡ�����ݻᰴ�մ����ͨ��IDһһ��Ӧ
 * ���ڶ�Ӧ�Ļ������С����ú�������ֵ<0�����ʾ���ֻ�������ͨ�����ݶ�ȡʧ�ܣ���
 * ���ø�����AM_SENSOR_VAL_IS_VALID ���ж�ÿ��ͨ�������ݣ���Ϊ�棬���ʾ��ͨ��ֵ
 * ��Ч����Ϊ�٣����ʾ��ͨ�����ݻ�ȡʧ�ܡ�
 *
 * \attention ������ĳһͨ��������׼����������ģʽ����ֻ���ڸ�ͨ���Ĵ����ص���
 * ������øú�����ȡ��ͨ����ֵ���мǲ�Ҫ�ڸ�ͨ���Ļص��������ȡ����ͨ���Ĳ���
 * ����
 */
am_static_inline
am_err_t am_sensor_data_get (am_sensor_handle_t  handle,
                             const int          *p_ids,
                             int                 num,
                             am_sensor_val_t    *p_buf)
{
    return handle->p_funcs->pfn_data_get(handle->p_drv, p_ids, num, p_buf);
}

/**
 * \brief ʹ�ܴ�������һ������ͨ��
 *
 * ʹ�ܺ󣬴�����ͨ���������������ʼ�ɼ��ⲿ�źš��������˴������Ĳ���Ƶ����
 * ��ֵ��#AM_SENSOR_ATTR_SAMPLING_RATE������ֵ��Ϊ0����ϵͳ���Զ���������ֵָ��
 * �Ĳ���Ƶ�ʻ�ȡ�������еĲ���ֵ�����û���������׼��������������ÿ�����ݲ���
 * �����󣬶��������û��ص��������ر�أ�������Ƶ��Ϊ0��Ĭ�ϣ������Զ�������
 * ÿ�ε���am_sensor_data_get()����ʱ�ŴӴ������л�ȡ�������ݡ�
 *
 * \param[in]  handle   ����������׼������
 * \param[in]  p_ids    ��������ͨ�� id�б�
 * \param[in]  num      ��ͨ����Ŀ
 * \param[out] p_result ��ÿ��ͨ��ʹ�ܵĽ������valֵ�У����׼�����뺬��һ��
 *
 * \retval  AW_OK     ����ͨ��ʹ�ܳɹ�
 * \retval -AM_ENODEV ���ֻ�����ͨ��������
 * \retval -AM_EINVAL ��Ч����
 * \retval   <0       ���ֻ�����ͨ��ʹ��ʧ�ܣ�ÿһ��ͨ��ʹ�ܵĽ������ val ֵ��
 *
 * \attention p_result ָ��Ļ������ڴ洢ÿ��ͨ��ʹ�ܵĽ�������Ǳ�ʾ״̬������
 * ��Ч�Ĵ��������ݣ����ú�������ֵ<0�������ͨ�� valֵ�����ж϶�Ӧͨ����ʹ����
 * �����ɣ�valֵ�ĺ������׼������Ķ�Ӧ��ϵһ�¡��ر�أ������� p_result Ϊ 
 * NULL�������������ÿ��ͨ��ʹ�ܵĽ����
 */
am_static_inline
am_err_t am_sensor_enable (am_sensor_handle_t  handle,
                           const int          *p_ids,
                           int                 num,
                           am_sensor_val_t    *p_result)
{
    return handle->p_funcs->pfn_enable(handle->p_drv, p_ids, num, p_result);
}

/**
 * \brief ���ܴ�������һ������ͨ��
 *
 * ���ܺ󣬴��������رգ���������ֹͣ�ɼ��ⲿ�źţ�ͬʱ��ϵͳҲ���ٴӴ������л�
 * ȡ����ֵ�����۲���Ƶ���Ƿ�Ϊ0����
 *
 * \param[in]  handle   ����������׼������
 * \param[in]  p_ids    ��������ͨ�� id�б�
 * \param[in]  num      ��ͨ����Ŀ
 * \param[out] p_result ��ÿ��ͨ�����ܵĽ������valֵ�У����׼�����뺬��һ��
 *
 * \retval  AM_OK     ����ͨ�����ܳɹ�
 * \retval -AM_ENODEV ���ֻ�����ͨ��������
 * \retval -AM_EINVAL ��Ч����
 * \retval   < 0      ��׼�����룬���ֻ�����ͨ������ʧ��
 *
 * \attention p_result ָ��Ļ������ڴ洢ÿ��ͨ�����ܵĽ�������Ǳ�ʾ״̬������
 * ��Ч�Ĵ��������ݣ����ú�������ֵ<0�������ͨ�� valֵ�����ж϶�Ӧͨ���Ľ�����
 * �����ɣ�valֵ�ĺ������׼������Ķ�Ӧ��ϵһ�¡��ر�أ������� p_result Ϊ
 *  NULL�������������ÿ��ͨ�����ܵĽ����
 */
am_static_inline
am_err_t am_sensor_disable (am_sensor_handle_t  handle,
                            const int          *p_ids,
                            int                 num,
                            am_sensor_val_t    *p_result)
{
    return handle->p_funcs->pfn_disable(handle->p_drv, p_ids, num, p_result);
}

/**
 * \brief ���ô�����ͨ��������
 *
 * \param[in] handle : ��������׼������
 * \param[in] id     : ������ͨ�� id
 * \param[in] attr   : ���ԣ�AM_SENSOR_ATTR_*(eg:#AM_SENSOR_ATTR_SAMPLING_RATE)
 * \param[in] p_val  : ����ֵ
 *
 * \retval   AM_OK       �ɹ�
 * \retval  -AM_EINVAL   ��Ч����
 * \retval  -AM_ENOTSUP  ��֧��
 * \retval  -AM_ENODEV   ͨ��������
 *
 * \note ֧�ֵ���������崫������أ����ִ��������ܲ�֧���κ����ԡ�
 */
am_static_inline
am_err_t am_sensor_attr_set (am_sensor_handle_t     handle,
                             int                    id,
                             int                    attr,
                             const am_sensor_val_t *p_val)
{
    return handle->p_funcs->pfn_attr_set(handle->p_drv, id, attr, p_val);
}

/**
 * \brief ��ȡ������ͨ��������
 *
 * \param[in]  handle : ��������׼������
 * \param[in]  id     : ������ͨ�� id
 * \param[in]  attr   : ���ԣ�AM_SENSOR_ATTR_*(eg:#AM_SENSOR_ATTR_SAMPLING_RATE)
 * \param[out] p_val  : ���ڻ�ȡ����ֵ�Ļ���
 *
 * \retval   AM_OK       �ɹ�
 * \retval  -AM_EINVAL   ��Ч����
 * \retval  -AM_ENOTSUP  ��֧��
 * \retval  -AM_ENODEV   ͨ��������
 *
 * \note ֧�ֵ���������崫������أ����ִ��������ܲ�֧���κ����ԡ�
 */
am_static_inline
am_err_t am_sensor_attr_get (am_sensor_handle_t handle,
                             int                id,
                             int                attr,
                             am_sensor_val_t   *p_val)
{
    return handle->p_funcs->pfn_attr_get(handle->p_drv, id, attr, p_val);
}

/**
 * \brief ���ô�����һ��ͨ����������һ�������ص�����
 *
 * \param[in] handle : ��������׼������
 * \param[in] id     : ������ͨ�� id
 * \param[in] flags  : ָ�����������ͣ�����AM_SENSOR_TRIGGER_DATA_READY
 *                     (�Ҷ���������Ϳ��������)
 * \param[in] pfn_cb : ����ʱִ�еĻص�������ָ��
 * \param[in] p_arg  : �û�����
 *
 * \retval  AM_OK      �ɹ�
 * \retval -AM_EINVAL  ��Ч����
 * \retval -AM_ENOTSUP ��֧�ֵĴ���ģʽ
 * \retval -AM_ENODEV  ͨ��������
 *
 * \note ֧�ֵĴ���ģʽ����崫������أ����ִ�������֧���κδ���ģʽ������ģʽ
 * ʱ������Ҫͨ��I2C��SPI��ͨ�Žӿ��봫����ͨ�ţ��ȽϺ�ʱ���ú����������жϻ���
 * ��ʹ�á�
 */
am_static_inline
am_err_t am_sensor_trigger_cfg (am_sensor_handle_t      handle,
                                int                     id,
                                uint32_t                flags,
                                am_sensor_trigger_cb_t  pfn_cb,
                                void                   *p_arg)
{
    return handle->p_funcs->pfn_trigger_cfg(handle->p_drv,
                                            id,
                                            flags,
                                            pfn_cb,
                                            p_arg);
}

/**
 * \brief �򿪴���(�򿪸�ͨ�� am_sensor_trigger_cfg �������ù������д�������)
 *
 * \param[in] handle : ��������׼������
 * \param[in] id     : ������ͨ�� id
 *
 * \retval  AM_OK     �򿪳ɹ�
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_ENODEV ͨ��������
 * \retval   < 0      ʧ��
 */
am_static_inline
am_err_t am_sensor_trigger_on (am_sensor_handle_t handle,
                               int                id)
{
    return handle->p_funcs->pfn_trigger_on(handle->p_drv, id);
}

/**
 * \brief �رմ���(�رո�ͨ�������д���ģʽ)
 *
 * \param[in] handle : ��������׼������
 * \param[in] id     : ������ͨ�� id
 *
 * \retval  AM_OK     �رճɹ�
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_ENODEV ͨ��������
 * \retval   < 0      ʧ��
 */
am_static_inline
am_err_t am_sensor_trigger_off (am_sensor_handle_t handle,
                                int                id)
{
    return handle->p_funcs->pfn_trigger_off(handle->p_drv, id);
}

/**
 * \brief ������������ȡһ����λ��Ӧ��ǰ׺���ţ���"M"���ף���"k"��ǧ��
 *
 * \param[in] unit : ��λ��AM_SENSOR_UNIT_* (eg: #AM_SENSOR_UNIT_MILLI)
 *
 * \return �����ַ���������λ��Ч���򷵻�NULL����unitΪ0(#AM_SENSOR_UNIT_BASE)
 * �򷵻ؿ��ַ���: ""���ر�ע�⣬�������ص���һ���ַ�����������һ���ַ�����Ϊ
 * ���ֵ�λ�ķ��ſ�����������ĸ���磺"da"��ʮ����
 */
const char *am_sensor_unit_symbol_get (int32_t unit);

/**
 * \brief �������������ڴ��������ݵ�λ��ת��
 *
 * \param[in] p_buf   : ���������ݻ���
 * \param[in] num     : ���������ݸ���
 * \param[in] to_unit : Ŀ�굥λ��AM_SENSOR_UNIT_* (eg: #AM_SENSOR_UNIT_MILLI)
 *
 * \retval AM_OK      ת���ɹ�
 * \retval -AM_EINVAL ת��ʧ�ܣ���������
 * \retval -AM_ERANGE ĳһ����ת��ʧ�ܣ���ת������ᳬ����Χ��������С��λʱ����
 *                    ���֣�,ת��ʧ�ܵ����ݽ�����ԭֵ��ԭ��λ���䣬�û���ͨ����
 *                    λ�Ƿ�ΪĿ�굥λ���ж��Ƿ�ת���ɹ���
 *
 * \note ��λת����ԭ��
 *
 * - ��������λ������unit��ֵ�����ٶ�unit���ӵ�ֵΪn����Ὣval��ֵ����10^n��
 * ���ڴ�������������ʹԭvalֵ�ľ��ȼ�С�����ȼ�Сʱ����ѭ�������뷨�����磺
 * ԭ����Ϊ1860mV��������λת��ΪV����ת���Ľ��Ϊ2V��ԭ����Ϊ1245mV��������λ
 * ת��ΪV����ת���Ľ��Ϊ1V�����ڴ��ھ��ȵ���ʧ����λ������Ӧ�ý���ʹ�á�
 *
 * - ������С��λ����Сunit��ֵ�����ٶ�unit��С��ֵΪn����Ὣval��ֵ����10^n��
 * ��Ӧ�ر�ע�⣬valֵ������Ϊ32λ�з����������ʾ�����ݷ�ΧΪ��-2147483648 ~
 * 2147483647����Ӧʹvalֵ����10^n������ݳ����÷�Χ����С��λ�����ھ��ȵ���ʧ��
 * ��Ӧע�����ݵ��������Ӧ��һ��������С��̫С�ĵ�λ��
 *
 * - �ر�أ���ת��ǰ��ĵ�λû�з����仯����������������ֵ���ֲ��䡣
 */
am_err_t am_sensor_val_unit_convert (am_sensor_val_t *p_buf,
                                     int              num,
                                     int32_t          to_unit);

/** @} grp_am_if_sensor */

 #ifdef __cplusplus
 }
 #endif

 #endif /* __AM_SENSOR_H */

 /* end of file */

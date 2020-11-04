/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ZLG72128ͨ��������
 *
 * \note
 * ����ZLG72128�����ԣ������I2C�Ĵ�������������zlg72128_platform.h
 * ���Ѿ���I2C��صĴ��亯�������˶��壬�û���ʹ�����ʱ����Ҫ���������ƽ̨����
 * ��������䣬��������ZLG72128ģ����Ӧ�ã���ֻ��Ҫע������ڵĽӿں������ɡ�
 * zlg72128_platform.h�в�����������I2C���亯����������ƽ̨��صĳ�ʼ��
 * ��������ʱ�������û�Ҳ��Ҫ��������ƽ̨���������䣬�����zlg72128_platform.h
 * �ļ���
 *
 * \internal
 * \par Modification History
 * - 1.00 18-11-13  xgg�� first implementation.
 * \endinternal
 */

#ifndef __ZLG72128_H
#define __ZLG72128_H

#include "zlg72128_platform.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup if_zlg72128
 * @copydoc zlg72128.h
 * @{
 */

/**
 * \name ��ͨ��������1�� ~ ��3�����а�������ֵ�궨��
 *
 *  �оٳ��� zlg72128_key_cb_t �ص������е� key_val ���ܵ�һϵ��ֵ������
 *  ʹ��key_valֵ����һϵ�к�ֵ����Ӧ�Աȣ����ж�����һ�������¡����������
 *  ����ZLG72128_KEY_x_y �����У�x������һ�У�1 ~ 3����y��ʾ��һ�У�1 ~ 8)
 *
 * @{
 */

#define  ZLG72128_KEY_1_1     1     /**< \brief ��1�ŵ�1������  */
#define  ZLG72128_KEY_1_2     2     /**< \brief ��1�ŵ�2������  */
#define  ZLG72128_KEY_1_3     3     /**< \brief ��1�ŵ�3������  */
#define  ZLG72128_KEY_1_4     4     /**< \brief ��1�ŵ�4������  */
#define  ZLG72128_KEY_1_5     5     /**< \brief ��1�ŵ�5������  */
#define  ZLG72128_KEY_1_6     6     /**< \brief ��1�ŵ�6������  */
#define  ZLG72128_KEY_1_7     7     /**< \brief ��1�ŵ�7������  */
#define  ZLG72128_KEY_1_8     8     /**< \brief ��1�ŵ�8������  */

#define  ZLG72128_KEY_2_1     9     /**< \brief ��2�ŵ�1������  */
#define  ZLG72128_KEY_2_2     10    /**< \brief ��2�ŵ�2������  */
#define  ZLG72128_KEY_2_3     11    /**< \brief ��2�ŵ�3������  */
#define  ZLG72128_KEY_2_4     12    /**< \brief ��2�ŵ�4������  */
#define  ZLG72128_KEY_2_5     13    /**< \brief ��2�ŵ�5������  */
#define  ZLG72128_KEY_2_6     14    /**< \brief ��2�ŵ�6������  */
#define  ZLG72128_KEY_2_7     15    /**< \brief ��2�ŵ�7������  */
#define  ZLG72128_KEY_2_8     16    /**< \brief ��2�ŵ�8������  */


#define  ZLG72128_KEY_3_1     17    /**< \brief ��3�ŵ�1������  */
#define  ZLG72128_KEY_3_2     18    /**< \brief ��3�ŵ�2������  */
#define  ZLG72128_KEY_3_3     19    /**< \brief ��3�ŵ�3������  */
#define  ZLG72128_KEY_3_4     20    /**< \brief ��3�ŵ�4������  */
#define  ZLG72128_KEY_3_5     21    /**< \brief ��3�ŵ�5������  */
#define  ZLG72128_KEY_3_6     22    /**< \brief ��3�ŵ�6������  */
#define  ZLG72128_KEY_3_7     23    /**< \brief ��3�ŵ�7������  */
#define  ZLG72128_KEY_3_8     24    /**< \brief ��3�ŵ�8������  */

/** @} */

/**
 * \name ���ܰ�������4�����а�������ź궨��
 *
 *   ���ܰ����ӵ�4�п�ʼ���������ң����ζ���Ϊ F0 ~ F7����״̬�ֱ��밴����
 * �������е� funkey_val ֵ�� bit0 ~ bit7 ��Ӧ��0λ���£�1Ϊ�ͷš�
 * ����funkey_val��8�����ܼ������ֵ������ֱ��ʹ�����8λ��ֵʵ�ֽ�Ϊ����
 * �İ������ơ���ֻ��Ҫ�򵥵ļ������ĳ�����ܼ���״̬������ʹ��
 * #ZLG72128_FUNKEY_CHECK()����ĳһ���ܼ���״̬��
 * #ZLG72128_FUNKEY_CHECK()���funkey_num����Ϊ0 ~ 7������ʹ
 * �� �˴�����ĺ�ֵ��#ZLG72128_FUNKEY_0 ~ #ZLG72128_FUNKEY_7
 *
 * @{
 */

#define  ZLG72128_FUNKEY_0     0     /**< \brief ���ܼ�1  */
#define  ZLG72128_FUNKEY_1     1     /**< \brief ���ܼ�2  */
#define  ZLG72128_FUNKEY_2     2     /**< \brief ���ܼ�3  */
#define  ZLG72128_FUNKEY_3     3     /**< \brief ���ܼ�4  */
#define  ZLG72128_FUNKEY_4     4     /**< \brief ���ܼ�4  */
#define  ZLG72128_FUNKEY_5     5     /**< \brief ���ܼ�5  */
#define  ZLG72128_FUNKEY_6     6     /**< \brief ���ܼ�6  */
#define  ZLG72128_FUNKEY_7     7     /**< \brief ���ܼ�7  */

/** @} */

/**
 * \name �������ʾ��λ�ķ���
 * ���� \sa zlg72128_digitron_shift() ������ \a dir ������
 * @{
 */
#define  ZLG72128_DIGITRON_SHIFT_RIGHT  0   /**< \brief ����  */
#define  ZLG72128_DIGITRON_SHIFT_LEFT   1   /**< \brief ����  */

/** @} */

/**
 * \name ���ܰ�������4�����а�����״̬����
 *
 *   ���ܰ����ӵ�4�п�ʼ���������ң����ζ���Ϊ F0 ~ F7����״̬�ֱ��밴���ص�����
 * �е� funkey_val ֵ�� bit0 ~ bit7 ��Ӧ��0λ���£�1Ϊ�ͷš�����funkey_val��8��
 * ���ܼ������ֵ������ֱ��ʹ�����8λ��ֵʵ�ֽ�Ϊ���ӵİ������ơ���ֻ��Ҫ��
 * �ļ������ĳ�����ܼ���״̬������ʹ�øú���ĳһ���ܼ���״̬��
 *
 * \param[in] funkey_val : �����ص������л�ȡ���Ĺ��ܼ���ֵ
 * \param[in] funkey_num : ���ܼ���ţ���Чֵ��0 ~ 7���ֱ��Ӧ F0 ~ F7������ʹ��
 *                         ��ֵ#ZLG72128_FUNKEY_0 ~ #ZLG72128_FUNKEY_7
 *
 * \retval 1 : ��Ӧ���ܼ���ǰ�ǰ���״̬
 * \retval 0 : ��Ӧ���ܼ���ǰ���ͷ�״̬
 * @{
 */

#define  ZLG72128_FUNKEY_CHECK(funkey_val, funkey_num)  \
               (((funkey_val) & (1 << ((funkey_num) & 0x07))) ? 0 : 1)

/** @} */

/**
 * \name ����ܶ�
 * ���� \sa zlg72128_digitron_seg_ctrl() �ο��ƺ����� \a seg ������
 * @{
 */

#define  ZLG72128_DIGITRON_SEG_A    0        /**< \brief a  ��  */
#define  ZLG72128_DIGITRON_SEG_B    1        /**< \brief b  ��  */
#define  ZLG72128_DIGITRON_SEG_C    2        /**< \brief c  ��  */
#define  ZLG72128_DIGITRON_SEG_D    3        /**< \brief d  ��  */
#define  ZLG72128_DIGITRON_SEG_E    4        /**< \brief e  ��  */
#define  ZLG72128_DIGITRON_SEG_F    5        /**< \brief f  ��  */
#define  ZLG72128_DIGITRON_SEG_G    6        /**< \brief g  ��  */
#define  ZLG72128_DIGITRON_SEG_DP   7        /**< \brief dp ��  */

/** @} */

/** \brief ���ֽӿڵ���ZLG72128_TRUE��ZLG72128_FLASE������������� */
#define  ZLG72128_TRUE              1
#define  ZLG72128_FALSE             0

/**
 * \brief ZLG72128�ӻ���ַ���û��ɼ��A4�ĵ�ƽ��ȷ����ǰZLG72128ģ��Ĵӻ���ַ��
 *        ������A4Ϊ���ջ��߸ߵ�ƽ����ӻ���ַΪ0x30
 *        ������A4Ϊ�͵�ƽ����ӻ���ַΪ0x20
 */
#define  ZLG72128_PIN_HIGH_SLV_ADDR  0x30
#define  ZLG72128_PIN_LOW_SLV_ADDR   0x20

/**
 * \brief ������ͨ��������1�� ~ ��3�У��ص���������
 *
 *    ����ʹ�� zlg72128_key_cb_set() �������øûص�������ϵͳ֮�У����а���
 * �¼�����ʱ�����ûص�������
 *
 * \param[in] p_arg      : ���ûص�����ʱ�趨���û��Զ������
 *
 * \param[in] key_val    : ��ֵ���ӵ�1�п�ʼ����������˳���š���1�е�1������
 *                         ��ֵΪ1����1�е�2��������ֵΪ2���Դ����ơ�����ʹ��
 *                         ��ֱֵ���� ZLG72128_KEY_*_*(#ZLG72128_KEY_1_1)
 *                         �Ƚϣ����ж�����һ�������¡�����أ�0��ʾ���κ���ͨ
 *                         �������¡�
 *
 * \param[in] repeat_cnt : ����������������ͨ����֧����������ֵ�����ڸ�������
 *                         key_val0��Ӧ����ͨ������������������funkey_val����
 *                         �Ĺ��ܼ�û�й�ϵ��0 ��ʾ�״ΰ�����δ����������ֵ��
 *                         ʾʶ�𵽵�������������������סʱ�䳬��2s�󣬿�ʼ��
 *                         ����Ч��������Ч��ʱ����Լ200ms����ÿ��200ms��
 *                         repeat_cnt��1��������һ�θú�����ֱ�������ͷš���ֵ
 *                         ���Ϊ255����������������255���򽫽�����������׶Σ�
 *                         ����û��ʱ���������ûص�������
 *
 * \param[in] funkey_val : ���ܼ���ֵ������8λ���ֱ����4�и���������Ӧ�����λ
 *                         ���4�е�1��������Ӧ���θ�λ���4�е�2��������Ӧ����
 *                         ��λ���4�е�8��������Ӧ��λֵΪ0������Ӧ�����£�λ
 *                         ֵΪ1������Ӧ��δ���¡�ֻҪ��ֵ�����ı䣬�ͻ��������
 *                         �Ļص�������
 *
 * \note ���ڹ��ܼ�����ͨ����������ʵ����ϼ�Ӧ�ã�����PC���ϵ�Alt��Shift�Ȱ�����
 *
 *     �羭���õ���һ�����ܣ��༭����ʱ��TAB�������ƣ������סShift������TAB��
 * ��Ϊ���ơ����Ժ�����ʵ�����ƵĹ��ܣ��繦�ܼ�0������Shift������ͨ����0����TA
 * B����
 */
typedef void (*zlg72128_key_cb_t) (void       *p_arg,
                                   uint8_t     key_val,
                                   uint8_t     repeat_cnt,
                                   uint8_t     funkey_val);

/**
 * \brief ZLG72128�豸��Ϣ�ṹ�嶨��
 */
typedef struct zlg72128_devinfo {

    /** \brief ƽ̨��Ϣ�ṹ��*/
    zlg72128_plfm_init_info_t  plfm_info;

}zlg72128_devinfo_t;

/**
 * \brief ZLG72128�豸�ṹ�嶨��
 *
 * \note ��Ϊ���ǵ����ƽ̨�����û������ŵĶ��岻ͬ�����������˵��
 * λ���ź��ж����ŵ���������Լ򵥵ģ�������ZLG72128������в�û��
 * ���ŵ����ú�����ZLG72128�ĸ�λ�ź��ǵ͵�ƽ��Ч���û�����λ������
 * ��5-10ms����Դﵽ��λЧ����ͬ�������ж�������˵Ҳ�ǵ͵�ƽ��Ч
 * �û����Խ��жϴ�����ʽ����Ϊ�½��ػ�͵�ƽ�������û���������ص�
 * ����������zlg72128_platform.h�ж��������zlg72128_plfm_init������
 * ���С�
 *
 */
typedef struct zlg72128_dev {

    /** \brief ����ƽ̨��ص��豸*/
    zlg72128_plfm_t     plfm;

    /** \brief ������ͨ���ص����� */
    zlg72128_key_cb_t   pfn_key_cb;

    /** \brief ���水���ص��������� */
    void               *pfn_key_arg;

} zlg72128_dev_t;


/** \brief ����ZLG72128�������  */
typedef zlg72128_dev_t   *zlg72128_handle_t;

/**
 * \brief ZLG72128��ʼ������
 *  ����ZLG72128�����ӿ�ǰ��Ӧ�����ȵ��øó�ʼ���������Ի�ȡ����
 *  ZLG72128��handle����ȡ���ľ���ڵ��ô󲿷ֽӿ�ʱ���贫�뵽��
 *  �ڵĵ�һ������handle�С���ʼ�������ڲ�������zlg72128_platform.h
 *  �ж����zlg72128_plfm_init��������ƽ̨��ص���Ϣ���г�ʼ��
 *
 * \param[in] p_dev     : ָ��ZLG72128�豸��ָ��
 * \param[in] p_devinfo : �豸��Ϣ�ṹ�壬��Ϣ�ṹ���б�����zlg72128_platform.h
 *                        �ж����zlg72128_plfm_init_info_t�ṹ�壬�ڲ�����
 *                        zlg72128_plfm_initʱ�ᴫ���ڶ�������p_plfm_init_info�С�
 *
 * \return ��ִ�гɹ����ز���ZLG72128��handle��
 *         ������NULL���������Ч��ƽ̨��ʼ������ִ��ʧ�ܡ�
 *
 * \note �豸ָ��p_devָ����豸ֻ��Ҫ���壬����Ҫ�ڵ��ñ�����ǰ��ʼ����
 */
zlg72128_handle_t zlg72128_init (zlg72128_dev_t           *p_dev,
                                 const zlg72128_devinfo_t *p_devinfo);

/**
 * \brief ��ͨ��������1�� ~ ��3�����а������ص�����ע��
 *
 * ���а����¼�����ʱ�������ô˴����õĻص������������¼���������3�������
 *  1. ����ͨ��������
 *  2. ��ͨ����һֱ���£���������״̬
 *  3. ��һ���ܰ���״̬�����仯���ͷ�->���� �� ����->�ͷ�
 *
 * \param[in] handle      : ZLG72128�Ĳ������
 * \param[in] pfn_key_cb  : �����ص�����
 * \param[in] p_arg       : �ص������Ĳ���
 *
 * \retval -2 : ��������
 * \retval  0 : ִ�гɹ�
 */
int zlg72128_key_cb_set (zlg72128_handle_t   handle,
                         zlg72128_key_cb_t   pfn_key_cb,
                         void               *p_arg);

/**
 * \brief �����������˸ʱ�䣬�����趨ĳλ��˸ʱ����������ʱ���Ϩ�������ʱ��
 *
 *     ��������Ϊ���������ʱ���Ϊ500ms��ʱ�䵥λΪms����Ч��ʱ��Ϊ��
 *  150��200��250��������800��850��900���� 150ms ~ 900ms������50msΪ��ࡣ
 *  ��ʱ�䲻��ǡ��Ϊ��Щֵ���������һ����ӽ���ֵ��
 *
 * \param[in] handle : ZLG72128�Ĳ������
 * \param[in] on_ms  : ����������ʱ�䣬��ЧֵΪ 150ms ~ 900ms������50msΪ���
 * \param[in] off_ms : Ϩ�������ʱ�䣬��ЧֵΪ 150ms ~ 900ms������50msΪ���
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 *
 * \note ��������˸ʱ�䲢��������������˸���������ĳλ����˸���غ��ܿ���
 * ��˸���� \sa zlg72128_digitron_flash_ctrl()
 */
int zlg72128_digitron_flash_time_cfg (zlg72128_handle_t  handle,
                                      uint16_t           on_ms,
                                      uint16_t           off_ms);

/**
 * \brief ���ƣ��򿪻�رգ��������˸��Ĭ�Ͼ�����˸
 *
 * \param[in] handle   : ZLG72128�Ĳ������
 * \param[in] ctrl_val : ����ֵ��λ0 ~ 11�ֱ��Ӧ�������ҵ�����ܡ�ֵΪ1ʱ��˸��
 *                       ֵΪ0ʱ����˸��
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 */
int zlg72128_digitron_flash_ctrl (zlg72128_handle_t  handle,
                                  uint16_t           ctrl_val);

/**
 * \brief ��������ܵ���ʾ���ԣ�����ʾ��ر���ʾ��
 *
 *    Ĭ������£���������ܾ����ڴ���ʾ״̬���򽫰���12λ�����ɨ�裬ʵ���У�
 * ������Ҫ��ʾ��λ��������12λ����ʱ������ʹ�øú����ر�ĳЩλ����ʾ��
 *
 * \param[in] handle   : ZLG72128�Ĳ������
 * \param[in] ctrl_val : ����ֵ��λ0 ~ λ11�ֱ��Ӧ�������ҵ�����ܡ�
 *                       ֵΪ1�ر���ʾ��ֵΪ0����ʾ
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 *
 * \note �������ö���ΪϨ����벻ͬ�����ö���ΪϨ�����ʱ�������ͬ����ɨ�裬ͬ
 * ����Ҫ��ÿ��ɨ��ʱ�����Ӧ�Ķ��롣ʹ�øú����ر�ĳЩλ����ʾ���ǴӸ����ϲ�
 * ��ɨ���λ��
 */
int zlg72128_digitron_disp_ctrl (zlg72128_handle_t  handle,
                                 uint16_t           ctrl_val);

/**
 * \brief �����������ʾ���ַ�
 *
 *      ZLG72128�Ѿ��ṩ�˳�����10�����ֺ�21����ĸ��ֱ����ʾ������Ҫ��ʾ��֧�ֵ�
 *  ͼ�Σ�����ֱ��ʹ�� \sa zlg72128_digitron_dispbuf_set() ����ֱ�����ö��롣
 *
 * \param[in] handle     : ZLG72128�Ĳ������
 * \param[in] pos        : ������ʾ��λ�ã���Чֵ 0 ~ 11
 * \param[in] ch         : ��ʾ���ַ���֧���ַ� 0123456789AbCdEFGHiJLopqrtUychT
 *                         �Լ��ո�(����ʾ)
 * \param[in] is_dp_disp : �Ƿ���ʾС����
 *                        - ZLG72128_TRUE :��ʾ
 *                        - ZLG72128_FALSE:����ʾ
 * \param[in] is_flash   : ��λ�Ƿ���˸
 *                        - ZLG72128_TRUE :��˸
 *                        - ZLG72128_FALSE:����˸
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 */
int zlg72128_digitron_disp_char (zlg72128_handle_t  handle,
                                 uint8_t            pos,
                                 char               ch,
                                 bool_t             is_dp_disp,
                                 bool_t             is_flash);

/**
 * \brief ��ָ��λ�ÿ�ʼ��ʾһ���ַ���
 *
 * \param[in] handle    : ZLG72128�Ĳ������
 * \param[in] start_pos : �ַ�����ʼλ��
 * \param[in] p_str     : ��ʾ���ַ���
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 *
 * \note ��������֧�ֵ��ַ������ַ�λ������ʾ
 */
int zlg72128_digitron_disp_str (zlg72128_handle_t  handle,
                                uint8_t            start_pos,
                                const char        *p_str);

/**
 * \brief �����������ʾ�����֣�0 ~ 9��
 *
 * \param[in] handle     : ZLG72128�Ĳ������
 * \param[in] pos        : ������ʾ��λ�ã���Чֵ 0 ~ 11
 * \param[in] num        : ��ʾ�����֣�0 ~ 9
 * \param[in] is_dp_disp : �Ƿ���ʾС����
 *                        - ZLG72128_TRUE :��ʾ
 *                        - ZLG72128_FALSE:����ʾ
 * \param[in] is_flash   : ��λ�Ƿ���˸
 *                        - ZLG72128_TRUE :��˸
 *                        - ZLG72128_FALSE:����˸
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 */
int zlg72128_digitron_disp_num (zlg72128_handle_t  handle,
                                uint8_t            pos,
                                uint8_t            num,
                                bool_t             is_dp_disp,
                                bool_t             is_flash);

/**
 * \brief ֱ�������������ʾ�����ݣ����룩
 *
 *      ���û���Ҫ��ʾһЩ�Զ��������ͼ��ʱ������ʹ�øú�����ֱ�����ö��롣һ
 *  ��������ZLG72128�Ѿ��ṩ�˳�����10�����ֺ�21����ĸ��ֱ����ʾ���û�����ʹ��
 *  �˺���ֱ�����ö��룬����ֱ��ʹ�� \sa ������ʾ���ֻ���ĸ
 *      Ϊ����������ö�������λ��ʾ�Ķ��룬����������һ������д���������
 *  ��ʾ�Ķ��롣
 *
 * \param[in] handle    : ZLG72128�Ĳ������
 * \param[in] start_pos : �������ö�����ʼλ�ã���Чֵ 0 ~ 11
 * \param[in] p_buf     : �����ŵĻ�����
 * \param[in] num       : �������õ�����ܶ���ĸ���
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 *
 * \note �� start_pos + num ��ֵ���� 12 �������Ļ��������ݱ�������
 */
int zlg72128_digitron_dispbuf_set (zlg72128_handle_t  handle,
                                   uint8_t            start_pos,
                                   uint8_t           *p_buf,
                                   uint8_t            num);

/**
 * \brief ֱ�ӿ��ƶεĵ�����Ϩ��
 *
 *   Ϊ�˸������Ŀ����������ʾ���ṩ��ֱ�ӿ���ĳһ�ε����ԣ������𣩡�
 *
 * \param[in] handle : ZLG72128�Ĳ������
 * \param[in] pos    : ���ƶ�������λ����Чֵ 0 ~ 11
 * \param[in] seg    : �Σ���Чֵ 0 ~ 7���ֱ��Ӧ��a,b,c,d,e,f,g,dp
 *                     ����ʹ�����к꣺
 *                       - ZLG72128_DIGITRON_SEG_A
 *                       - ZLG72128_DIGITRON_SEG_B
 *                       - ZLG72128_DIGITRON_SEG_C
 *                       - ZLG72128_DIGITRON_SEG_D
 *                       - ZLG72128_DIGITRON_SEG_E
 *                       - ZLG72128_DIGITRON_SEG_F
 *                       - ZLG72128_DIGITRON_SEG_G
 *                       - ZLG72128_DIGITRON_SEG_DP
 *
 * \param[in] is_on  : �Ƿ�����ö�
 *                    - ZLG72128_TRUE :����
 *                    - ZLG72128_FALSE:Ϩ��
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 */
int zlg72128_digitron_seg_ctrl (zlg72128_handle_t  handle,
                                uint8_t            pos,
                                char               seg,
                                bool_t             is_on);

/**
 * \brief ��ʾ��λ����
 *
 *      ʹ��ǰ��������ܵ���ʾ���ƻ����ƣ�����ָ���Ƿ���ѭ���ƶ����������ѭ��
 *   ��λ������λ���ұ߿ճ���λ�����ƣ�����߿ճ���λ�����ƣ�������ʾ�κ����ݡ�
 *   ����ѭ���ƶ�����ճ���λ������ʾ���Ƴ�λ�����ݡ�
 *
 * \param[in] handle    : ZLG72128�Ĳ������
 * \param[in] dir       : ��λ����
 *                       - ZLG72128_DIGITRON_SHIFT_LEFT   ����
 *                       - ZLG72128_DIGITRON_SHIFT_RIGHT  ����
 * \param[in] is_cyclic : �Ƿ�ѭ����λ
 *                       - ZLG72128_TRUE :ѭ����λ
 *                       - ZLG72128_FALSE:��ѭ����λ
 * \param[in] num       : ������λ��λ������Чֵ 0�����ƶ��� ~ 11������ֵ��Ч
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 *
 * \note ������λ��˵��
 *
 *   ʵ���У����ܻᷢ����λ�����෴���������ڿ��ܴ�������Ӳ����ƣ�
 *   1�� ���ұ�Ϊ0������ܣ���������Ϊ��11��10��9��8��7��6��5��4��3��2�� 1�� 0
 *   2�� �����Ϊ0������ܣ���������Ϊ�� 0�� 1��2��3��4��5��6��7��8��9��10��11
 *   ����Ҫȡ����Ӳ�����ʱ COM0 ~ COM11 ��������Ӧ���������������λ�á�
 *
 *       �˴����ƺ����Ƶĸ������ԡ������ֲᡷ�е���Ӧ�õ�·Ϊ�ο��ģ������ұ�
 *   Ϊ0������ܡ���ô���ƺ����Ƶĸ���ֱ�Ϊ��
 *   ���ƣ������0��ʾ�л���1�������1��ʾ�л���2�������������10��ʾ�л���11
 *   ���ƣ������11��ʾ�л���10�������1��ʾ�л���2�������������10��ʾ�л���11
 *
 *   �ɼ�����Ӳ����·��������λ�����෴�ģ�����λЧ������Ҳǡǡ���෴�ģ��˴�
 * ֻ��Ҫ��΢ע�⼴�ɡ�
 */
int zlg72128_digitron_shift (zlg72128_handle_t  handle,
                             uint8_t            dir,
                             bool_t             is_cyclic,
                             uint8_t            num);

/**
 * \brief �����ɨ��λ������������������ɨ��λ��
 *
 * \param[in] handle : ZLG72128�Ĳ������
 * \param[in] num    : �������ʾλ��(��ЧֵΪ0~12)
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 */
int zlg72128_digitron_scan_set (zlg72128_handle_t  handle,
                                uint8_t            num);
/**
 * \brief ��λ���������ܵ�����LED��Ϩ��
 *
 * \param[in] handle : ZLG72128�Ĳ������
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 */
int zlg72128_digitron_disp_reset (zlg72128_handle_t handle);

/**
 * \brief �����������LED����0.5S��������˸�����ڲ����������ʾ�Ƿ�����
 *
 * \param[in] handle : ZLG72128�Ĳ������
 *
 * \retval -2     : ��������
 * \retval  0     : ִ�гɹ�
 * \retval ����ֵ : I2Cд����ʧ��
 */
int zlg72128_digitron_disp_test (zlg72128_handle_t handle);

/**
 * \brief ZLG72128���ʼ������
 *
 *  ������ʹ��ָ����ZLG72128�豸ʱ������ʹ�øú������ʼ�����豸�����ͷ������Դ
 *
 * \param[in] handle : ZLG72128�Ĳ������
 *
 * \retval -2     : ��������
 * \retval ����ֵ : ƽ̨���ʼ��ʧ��
 */
int zlg72128_deinit(zlg72128_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZLG72128_H */

/* end of file */

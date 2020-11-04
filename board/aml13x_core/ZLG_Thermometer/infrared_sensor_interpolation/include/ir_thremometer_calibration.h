/***************************Copyright(c)***********************************
**                Guangzhou ZHIYUAN electronics Co.,LTD.                   
**                                                                         
**                      http://www.zlg.cn                         
**                                                                         
**-------------File Info---------------------------------------------------
**File Name:            zal_infrared_sensor_interpolation.h
**Latest modified Date: 
**Latest Version:       
**Description:          
**                      
**-------------------------------------------------------------------------
**Created By:            moxinyu
**Created Date:         2020-3-18
**Version:              v1.0.0
**Description:          
**                      
**-------------------------------------------------------------------------
**Modified By:         
**Modified Date:      
**Version:              
**Description:          
**                      
**************************************************************************/
#ifndef _IR_THREMOMETER_CALIBRATION_H_
#define _IR_THREMOMETER_CALIBRATION_H_

/**
 * \brief У׼��ʼ��
 */
void ir_thremometer_calib_init(void);

/**
 * \brief ����У׼�¶ȵ㣬һ��ֻ����������У׼�㣬���������������ir_thremometer_calib_run��֮������ٴ�У׼
 *
 * \param[in] obj_temp : У׼�¶ȵ�
 *
 * \return��AM_OK���ɹ���AM_ERROR��ʧ��
 */
int ir_thremometer_set_calib_point(float obj_temp);

/**
 * \brief ����У׼�㷨
 *
 * \return��AM_OK���ɹ���AM_ERROR��ʧ��
 */
int ir_thremometer_calib_run(void);

/**
 * \brief ����ģʽ�в���ģʽ
 *
 * \param[in] temp : ����ģʽ�¶�
 *
 * \return������ģʽ�¶�
 */
float ir_thremometer_mode_btot(float temp);

/**
 * \brief ����ģʽ������ģʽ
 *
 * \param[in] temp : ����ģʽ�¶�
 *
 * \return������ģʽ�¶�
 */
float ir_thremometer_mode_ttob(float temp);

/**
 * \brief У׼��ѹֵ
 *
 * \param[in] vol : ��ҪУ׼�ĵ�ѹֵ
 *
 * \return��У׼��ĵ�ѹֵ
 */
float ir_thremometer_calib_vol(float vol);

/**
 * \brief ����Ƿ�У׼��
 *
 * \return��AM_TRUE: �Ѿ�У׼����AM_FALSE��û��У׼��
 */
am_bool_t ir_thremometer_if_already_calib(void);

#endif

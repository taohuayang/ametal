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
**Created By:            yanjianxiong
**Created Date:         2020-2-27
**Version:              v1.0.0
**Description:          
**                      
**-------------------------------------------------------------------------
**Modified By:          yanjianxiong
**Modified Date:        2020-3-12
**Version:              
**Description:          ����25���µ�VT�����㷨
**                      
**************************************************************************/

#ifndef __ZAL_INFRARED_SENSOR_INTERPOLATION_H__
#define __ZAL_INFRARED_SENSOR_INTERPOLATION_H__

#include <math.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif
/******RT �����**************/
	/**
	* @brief	    ͨ������ֵ��ȡ�����¶�
	*
	* @param[in]	rInput		  �������ֵ rInput
	* @return		���ص�ǰ�Ļ����¶ȣ�
	*/
	__declspec(dllimport) float
		zal_environment_tem_value_get(float rInput);
	/**
	* @brief	    ͨ����ѹֵ��ȡ�¶�ֵ����׼25���϶��£�
	*
	* @param[in]	vInput		  �����ѹֵvInput
	* @return		���ص�ǰ�Ļ����¶ȣ�
	*/
	__declspec(dllimport) float
		zal_environment_tem25_value_get(float vInput);
	/**
	* @brief	    ͨ�������¶Ⱥ͵�ѹֵ����ȡ�����¶�ֵ
	*
	* @param[in]	env_value	���뻷���¶�ֵ env_value
	* @param[in]	vInput		�����ѹֵ vInput
	* @return		���ص�ǰ�Ĳ����¶ȣ�(���鴫����ֻ��25���׼��ϸ��Ĵ�����ʹ��)
	*/
	__declspec(dllimport) float
		zal_temperature_get(float env_value, float vInput);

	/**
	* @brief	    ͨ�������¶ȺͲ����¶ȣ���ȡ��ѹֵ
	*
	* @param[in]	rInput	    ���뻷���¶�ֵ env_v
	* @param[in]	vInput		��������¶�ֵ obj_v
	* @return		���ص�ǰ��ѹֵ��
	*/
	__declspec(dllimport) float
		zal_voltage_value_get(float env_v, float obj_v);

		/**
	* @brief	    ͨ�������¶ȣ���ȡ����ֵ
	*
	* @param[in]	env_v	    ���뻷���¶�env_v
	* @return		���ص�ǰ����ֵ;
	*/
	__declspec(dllimport) float
		zal_resistance_value_get(float env_v);

				/**
	* @brief	    ͨ�������¶Ⱥ͵�ǰ��ѹֵ����ȡ���25���϶����¶�ֵ
	*
	* @param[in]	tInput	    ���뻷���¶�tInput
	* @param[in]	vInput	    ���������ѹvInput
	* @return		����Ŀ���¶�ֵ (������ֻ��25���׼��ϸ��Ĵ�����ʹ��)
	*/
	__declspec(dllimport) float
		zal_temperature25_value_get(float tInput,float vInput);
	
#ifdef __cplusplus
}
#endif
#endif

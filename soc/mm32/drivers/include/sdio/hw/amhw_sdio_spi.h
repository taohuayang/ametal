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
 * \brief SDIO Ӳ�������ӿ�
 * \internal
 * \par Modification history
 * - 1.00 17-04-13  ari, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG_SDIO_H
#define __AMHW_ZLG_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_zlg_sdio
 * \copydoc amhw_zlg_sdio.h
 * @{
 */

/**
 * \brief sdio structure of register
 */
typedef struct amhw_zlg_sdio {
    __IO uint32_t  mmc_ctrl;        /**< \brief sdio mmc_ctrl register */
    __IO uint32_t  mmc_io;          /**< \brief sdio mmc_io register */
    __IO uint32_t  mmc_bytecntl;    /**< \brief sdio mmc_bytecntl register */
    __IO uint32_t  mmc_tr_blockcnt; /**< \brief sdio interrupt enable register */
    __IO uint32_t  mmc_crcctl;      /**< \brief sdio mmc_crcctl register */
    __IO uint32_t  cmd_crc;         /**< \brief sdio cmd_crc register*/
    __IO uint32_t  dat_crcl;        /**< \brief sdio dat_crcl control */
    __IO uint32_t  dat_crch;        /**< \brief sdio dat_crch register */
    __IO uint32_t  mmc_int_mask;    /**< \brief sdio mmc_int_mask number */
    __IO uint32_t  clr_mmc_int;     /**< \brief sdio clr_mmc_int register */
    __IO uint32_t  mmc_cardsel;     /**< \brief sdio mmc_cardsel control */
    __I  uint32_t  mmc_siq;         /**< \brief sdio mmc_siq control */
    __IO uint32_t  mmc_io_mbctl;    /**< \brief sdio mmc_io_mbctl control */
    __IO uint32_t  mmc_blockcnt;    /**< \brief sdio mmc_blockcnt control */
    __IO uint32_t  mmc_timeoutcnt;  /**< \brief sdio mmc_timeoutcnt control */
    __IO uint32_t  cmd_bufx[16];    /**< \brief sdio cmd_bufx control */
    __IO uint32_t  buf_ctll;        /**< \brief sdio buf_ctll control */
    __IO uint32_t  resiver[31];     /**< \brief sdio cmd_bufx control */
    __IO uint32_t  data_buf[128];   /**< \brief sdio data_buf control */
} amhw_zlg_sdio_t;

/**
 * \brief sdio��DAT��λ��
 */
typedef enum amhw_zlg_sdio_width {
    AMHW_ZLG_ADIO_WIDTH_1BIT      = 0x0,   /**< \brief 1λ */
	AMHW_ZLG_ADIO_WIDTH_4BIT      = 0x1,   /**< \brief 4λ */
} amhw_zlg_sdio_width_t;

/**
 * \brief sdio�ٶ�ģʽ����
 */
typedef enum amhw_zlg_sdio_speed_mode {
    AMHW_ZLG_ADIO_SPEED_MODE_LOW      = 0x0,   /**< \brief ����ģʽ */
	AMHW_ZLG_ADIO_SPEED_MODE_HIGH     = 0x1,   /**< \brief ����ģʽ */
} amhw_zlg_sdio_speed_mode_t;

/**
 * \brief sdio�˿�ʱ������
 */
typedef enum amhw_zlg_port_clk_mode {
    AMHW_ZLG_ADIO_PORT_CLK_MODE_1_2BASECLK      = 0x0,   /**< \brief 1/2������ʱ����ģʽ */
    AMHW_ZLG_ADIO_PORT_CLK_MODE_1_4BASECLK      = 0x1,   /**< \brief 1/4������ʱ����ģʽ */
    AMHW_ZLG_ADIO_PORT_CLK_MODE_1_6BASECLK      = 0x2,   /**< \brief 1/6������ʱ����ģʽ */
    AMHW_ZLG_ADIO_PORT_CLK_MODE_1_8BASECLK      = 0x3,   /**< \brief 1/8������ʱ����ģʽ */
	AMHW_ZLG_ADIO_PORT_CLK_MODE_1_10BASECLK     = 0x4,   /**< \brief 1/10������ʱ����ģʽ */
    AMHW_ZLG_ADIO_PORT_CLK_MODE_1_12BASECLK     = 0x5,   /**< \brief 1/12������ʱ����ģʽ */
    AMHW_ZLG_ADIO_PORT_CLK_MODE_1_14BASECLK     = 0x6,   /**< \brief 1/14������ʱ����ģʽ */
    AMHW_ZLG_ADIO_PORT_CLK_MODE_1_16BASECLK     = 0x7,   /**< \brief 1/16������ʱ����ģʽ */
} amhw_zlg_port_clk_mode_t;

/**
 * \brief sdio�˿�ʱ������
 */
typedef enum amhw_zlg_output_selection_mode {
    AMHW_ZLG_SDIO_OUTPUT_SELECTION_OD_MODE    = 0x1,   /**< \brief ���ʹ��*/
	AMHW_ZLG_SDIO_OUTPUT_SELECTION_PP_MODE    = 0x0,   /**< \brief ʹ��mmc_portģʽ */
} amhw_zlg_output_selection_mode_t;

/**
 * \brief sdio�˿�ʱ������
 */
typedef enum amhw_zlg_signal_mode {
	AMHW_ZLG_SDIO_SIGNAL_MMC_PORT_MODE    = 0x0,   /**< \brief ʹ��mmc_portģʽ */
    AMHW_ZLG_SDIO_SIGNAL_AUTO_MODE        = 0x1,   /**< \brief �Զ�����ģʽ*/
} amhw_zlg_signal_mode_t;

/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_sdio_port_operation_mode {
	AMHW_ZLG_SDIO_PORT_OPER_SPI_MODE    = 0x0,   /**< \brief ʹ��SPI_ģʽ */
	AMHW_ZLG_SDIO_PORT_OPER_SDIO_MODE   = 0x1,   /**< \brief SDIO/SD/MMCģʽ*/
} amhw_zlg_sdio_port_operation_mode_t;

/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_sdio_pclkg_mode {
	AMHW_ZLG_SDIO_PCLKG_SEL_REORSEND    = 0x0,   /**< \brief �˿ڲ���8����ʱ�� */
	AMHW_ZLG_SDIO_PCLKG_8FREE_CLK       = 0x1,   /**< \brief ѡ�������Ӧ/��������*/
} amhw_zlg_sdio_pclkg_t;

/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_resive_or_send_mode {
	AMHW_ZLG_SDIO_RESIVE_MODE     = 0x0,   /**< \brief ʹ�ý���ģʽ */
	AMHW_ZLG_SDIO_SEND_MODE       = 0x1,   /**< \brief ʹ�÷���ģʽ*/
} amhw_zlg_resive_or_send_mode_t;


/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_transfer_mode {
	AMHW_ZLG_SDIO_WRITE_MODE      = 0x0,   /**< \brief дģʽ */
	AMHW_ZLG_SDIO_READ_MODE       = 0x1,   /**< \brief ��ģʽ*/
} amhw_zlg_transfer_mode_t;

/**
 * \brief ���ȴ�ʹ�ܺ���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_read_wait_enable (amhw_zlg_sdio_t              *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl |= ( 1<<10 );
}

/**
* \brief ���ȴ����ܺ���
*
* \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
*
* \return ��
*/
am_static_inline
void amhw_zlg_sdio_read_wait_disable (amhw_zlg_sdio_t             *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl &= ~(1 << 10);
}

/**
 * \brief �ж�ʹ�ܺ���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_int_enable (amhw_zlg_sdio_t              *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl |= (1 << 9);
}

/**
* \brief �жϽ��ܺ���
*
* \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
*
* \return ��
*/
am_static_inline
void amhw_zlg_sdio_int_disable (amhw_zlg_sdio_t             *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl &= ~(1 << 9);
}

/**
 * \brief SDIOʹ�ܺ���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_mode_enable (amhw_zlg_sdio_t              *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl |= (1 << 8);
}

/**
* \brief SDIO���ܺ���
*
* \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
*
* \return ��
*/
am_static_inline
void amhw_zlg_sdio_mode_disable (amhw_zlg_sdio_t             *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl &= ~(1 << 8);
}

/**
 * \brief ����λ�������ܺ���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] width    p_hw_sdio ���ƼĴ���λ��ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_bus_width_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_sdio_width_t width)
{

	if (width) {
		p_hw_sdio->mmc_ctrl |= (1 << 7);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 7);
	}
}

/**
 * \brief ����ѡ���亯��
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƴ�������ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_speed_mode_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_sdio_speed_mode_t mode)
{

	if (mode) {
		p_hw_sdio->mmc_ctrl |= (1 << 6);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 6);
	}
}

/**
 * \brief ����ѡ�����ú���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƼĴ���CLK����ѡ��ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_prot_clk_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_port_clk_mode_t speed)
{
	p_hw_sdio->mmc_ctrl |= (speed << 3);
}

/**
 * \brief ������ú���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] mode   SDIO ���ƼĴ����������ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_output_mode_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_output_selection_mode_t mode)
{
	if (mode) {
	    p_hw_sdio->mmc_ctrl |= (1 << 2);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 2);
	}
}


/**
 * \brief �ź�ѡ����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƼĴ�����λ�ж�����ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_signal_mode_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_signal_mode_t mode)
{
	if (mode) {
	    p_hw_sdio->mmc_ctrl |= (1 << 1);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 1);
	}
}

/**
 * \brief �˿�ģʽѡ��λ���ú���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƼĴ�����λ�˿�ģʽö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_port_operation_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_sdio_port_operation_mode_t mode)
{
	if (mode) {
	    p_hw_sdio->mmc_ctrl |= (1 << 0);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 0);
	}
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƼĴ�����λcmd��ֹ��־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_cmd12_io_flag_set (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t cmd_stop)
{
	if (cmd_stop) {
	    p_hw_sdio->mmc_io |= (1 << 9);
	} else {
		p_hw_sdio->mmc_io &= ~(1 << 9);
	}
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return AM_TRUE  ��cmd12/IO��ֹ����
 *         AM_FALSE ����cmd12/IO��ֹ����
 */
am_static_inline
am_bool_t amhw_zlg_sdio_cmd12_io_flag_get (amhw_zlg_sdio_t *p_hw_sdio)
{
    if ((p_hw_sdio->mmc_io) & (1 << 9)) {
    	return AM_TRUE;
    } else {
    	return AM_FALSE;
    }
}

/**
 * \brief ����sdio������λ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   ��ǰָ����Ƿ�����ݿ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_cmdch_flag_set (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t cmd_stop)
{
	if (cmd_stop) {
	    p_hw_sdio->mmc_io |= (1 << 8);
	} else {
		p_hw_sdio->mmc_io &= ~(1 << 8);
	}
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return AM_TRUE  ��ǰָ�������ݿ�
 *         AM_FALSE ��ǰָ��󲻸����ݿ�
 */
am_static_inline
am_bool_t amhw_zlg_sdio_cmdch_flag_get (amhw_zlg_sdio_t *p_hw_sdio)
{
    if ((p_hw_sdio->mmc_io) & (1 << 8)) {
    	return AM_TRUE;
    } else {
    	return AM_FALSE;
    }
}

/**
 * \brief ʹ�ܵ������ݿ�
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_attoclkg_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io |= (1 << 7);
}

/**
 * \brief ���ܵ������ݿ�
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_attoclkg_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io &= ~(1 << 7);
}

/**
 * \brief ����������Զ�������Ӧ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_enrresp_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io |= (1 << 6);
}

/**
 * \brief ����������Զ�������Ӧ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_enrresp_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io &= ~(1 << 6);
}

/**
 * \brief ���ö˿�ʱ����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] mode   SDIO ���ƼĴ����˿�ʱ��ѡ��ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_pclkg_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_resive_or_send_mode_t mode)
{
	if (mode == AMHW_ZLG_SDIO_SEND_MODE) {
	    p_hw_sdio->mmc_io |= (1 << 3);
	} else {
		p_hw_sdio->mmc_io &= ~(1 << 3);
	}
}

/**
 * \brief ʹ���Զ���Ӧ����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_autotr_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	    p_hw_sdio->mmc_io |= (1 << 2);
}

/**
 * \brief �����Զ���Ӧ����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_autotr_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
		p_hw_sdio->mmc_io &= ~(1 << 2);
}

/**
 * \brief ���ö�дģʽ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] mode   SDIO ���ƼĴ�����дö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_transfdir_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_transfer_mode_t mode)
{
	if (mode == AMHW_ZLG_SDIO_READ_MODE) {
	    p_hw_sdio->mmc_io |= (1 << 1);
	} else {
		p_hw_sdio->mmc_io &= ~(1 << 1);
	}
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_autodattr_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	    p_hw_sdio->mmc_io |= (1 << 0);
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_autodattr_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
		p_hw_sdio->mmc_io &= ~(1 << 0);
}

/* δ����� ������ */




/* end of file */

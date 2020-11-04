/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Modbus ��վ����demo
 *
 * - ʹ��ע�⣺
 *
 *   1. Modbus ��������Ĭ��ʹ�������ʱ����ʹ�������ʱ����ΪModbus�Ķ�ʱʱ��
 *      �뿪�������ʱ�������ú� am_prj_config.h �ļ��� AM_CFG_SOFTIMER_ENABLE ��
 *
 *   2. ʹ��Ӳ����ʱ��ʱ������Ӳ����ʱ�����û������ļ�ѡ��32λ��ʱ������ģʽ
 *
 * \par Դ����
 * \snippet am_mb_slave_modbus_demo.c src_mb_slave_modbus_demo
 *
 * \internal
 * \par Modification history
 * - 1.00 17-03-31  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup grp_am_if_mb_slv
 * \copydoc am_mb_slave_modbus_demo.c
 */

/** [src_mb_slave_modbus_demo] */
#include "am_system.h"
#include "am_mb_slave.h"
#include "am_mb_ascii_comm.h"
#include "am_mb_utils.h"
#include "am_aml165_inst_init.h"
#include "demo_aml165_core_entries.h"
/*******************************************************************************
 * Macro Definition
 ******************************************************************************/
#define _AM_MB_MASK_WR_REG_FUNCODE   (22)  /* д�Ĵ������빦���� */

#define _AM_MB_COIL_START_ADDR       (1000) /**< \brief ��Ȧ��ʼ��ַΪ0   */
#define _AM_MB_COIL_END_ADDR         (1160) /**< \brief ��Ȧ������ַΪ160 */
#define _AM_MB_COIL_NUM              (20)   /**< \brief ֧�ֵ���Ȧ��Ϊ20 * 8�� */

#define _AM_MB_HOLD_REGS_START_ADDR  (1000) /**< \brief ���ּĴ�����ʼ��ַΪ0   */
#define _AM_MB_HOLD_REGS_END_ADDR    (1010) /**< \brief ���ּĴ���������ַΪ10 */
#define _AM_MB_HODL_REGS_NUM         (10)  /**< \brief ֧�ֵı��ּĴ���Ϊ10�� */

#define _AM_MB_INPUT_REGS_START_ADDR (1000)   /**< \brief ����Ĵ�����ʼ��ַΪ0   */
#define _AM_MB_INPUT_REGS_END_ADDR   (1010)  /**< \brief ����Ĵ���������ַΪ10 */
#define _AM_MB_INPUT_REGS_NUM        (10)  /**< \brief ֧�ֵı��ּĴ���Ϊ10�� */

/*******************************************************************************
 * Static variables
 ******************************************************************************/
/* ������Ȧ�ڴ沢���ó�ֵ */
am_local uint8_t  _g_coils_buf[_AM_MB_COIL_NUM] = {
    0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
};

/* ���䱣�ּĴ���������Ĵ����ڴ沢���ó�ֵ */
am_local uint16_t _g_hold_regs[_AM_MB_HODL_REGS_NUM]   = {0,1,2,3,4,5,6,7,8,9};
am_local uint16_t _g_input_regs[_AM_MB_INPUT_REGS_NUM] = {10,11,12,13,14,15,16,17,18,19};

/******************************************************************************/
/** \brief �ڴ���ȡ16λ�޷�����(���ģʽ) */
am_static_inline uint16_t _mb_to_u16 (const uint8_t *buf)
{
    return ((uint16_t)buf[0] << 8) + buf[1];
}

/******************************************************************************/
/** \brief ����Ȧ�ص����� */
am_local
am_mb_exception_t _mb_slv_read_coils_callback (am_mb_slave_handle slave,
                                               uint8_t           *p_buf,
                                               uint16_t           addr,
                                               uint16_t           num)
{
    if ((addr < _AM_MB_COIL_START_ADDR) || (addr > _AM_MB_COIL_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_ADDRESS;
    }

    if (addr + num > _AM_MB_COIL_END_ADDR) {
        return AM_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    /* ����Ȧֵ��buf��*/
    am_mb_bits_cp_to_buf(p_buf, _g_coils_buf, addr - _AM_MB_COIL_START_ADDR, num);

    return AM_MB_EXP_NONE;
}
/******************************************************************************/
/** \brief д��Ȧ�ص����� */
am_local
am_mb_exception_t _mb_slv_write_coils_callback (am_mb_slave_handle slave,
                                                uint8_t           *p_buf,
                                                uint16_t           addr,
                                                uint16_t           num)
{
    if ((addr < _AM_MB_COIL_START_ADDR) || (addr > _AM_MB_COIL_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_ADDRESS;
    }

    if (addr + num > _AM_MB_COIL_END_ADDR) {
        return AM_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    /* ��buf������ֵд��ָ����Ȧ*/
    am_mb_bits_set_from_buf(_g_coils_buf, p_buf, addr - _AM_MB_COIL_START_ADDR, num);

    return AM_MB_EXP_NONE;
}

/******************************************************************************/
/** \brief ����ɢ������ص����� */
am_local
am_mb_exception_t _mb_slv_read_discrete_inputs_callback (am_mb_slave_handle slave,
                                                         uint8_t           *p_buf,
                                                         uint16_t           addr,
                                                         uint16_t           num)
{
    return _mb_slv_read_coils_callback(slave, p_buf, addr, num);
}
/******************************************************************************/
/** \brief �����ּĴ����ص����� */
am_local
am_mb_exception_t _mb_slv_read_hold_regs_callback (am_mb_slave_handle slave,
                                                   uint8_t           *p_buf,
                                                   uint16_t           addr,
                                                   uint16_t           num)
{
    uint16_t index;

    if ((addr < _AM_MB_HOLD_REGS_START_ADDR) || (addr > _AM_MB_HOLD_REGS_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_ADDRESS;
    }

    if ((addr + num > _AM_MB_HOLD_REGS_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    index = addr - _AM_MB_HOLD_REGS_START_ADDR;

    /* ��ȡ���ּĴ������ݵ�p_buf��*/
    am_mb_regcpy(p_buf, &_g_hold_regs[index], num);

    return AM_MB_EXP_NONE;
}

/******************************************************************************/
/** \brief д�Ĵ����ص����� */
am_local
am_mb_exception_t _mb_slv_write_hold_regs_callback (am_mb_slave_handle slave,
                                                    uint8_t           *p_buf,
                                                    uint16_t           addr,
                                                    uint16_t           num)
{
    uint16_t index;

    if ((addr < _AM_MB_HOLD_REGS_START_ADDR) ||
        (addr > _AM_MB_HOLD_REGS_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_ADDRESS;
    }

    if ((addr + num > _AM_MB_HOLD_REGS_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    index = addr - _AM_MB_HOLD_REGS_START_ADDR;

    /* ��p_buf����д�����ּĴ������� */
    am_mb_regcpy(&_g_hold_regs[index], p_buf, num);

    return AM_MB_EXP_NONE;
}
/******************************************************************************/
/** \brief ������Ĵ����ص����� */
am_local
am_mb_exception_t _mb_slv_read_input_regs_callback (am_mb_slave_handle slave,
                                                    uint8_t           *p_buf,
                                                    uint16_t           addr,
                                                    uint16_t           num)
{
    uint16_t index;

    if ((addr < _AM_MB_INPUT_REGS_START_ADDR) ||
        (addr > _AM_MB_INPUT_REGS_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_ADDRESS;
    }

    if ((addr + num > _AM_MB_INPUT_REGS_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    index = addr - _AM_MB_INPUT_REGS_START_ADDR;

    /* ��ȡ����Ĵ������ݵ�p_buf��*/
    am_mb_regcpy(p_buf, &_g_input_regs[index], num);

    return AM_MB_EXP_NONE;
}

/** \brief ��չд�Ĵ�������ص����� */
am_local
am_mb_exception_t _mb_slv_reg_wr_mask_callback (am_mb_slave_handle slave,
                                                uint8_t           *p_pdu,
                                                uint16_t          *p_len)
{
    uint16_t addr, and, or;

    if (*p_len != 7) {
        return AM_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    addr = _mb_to_u16(p_pdu + 1);
    and  = _mb_to_u16(p_pdu + 3);
    or   = _mb_to_u16(p_pdu + 5);

    if ((addr < _AM_MB_HOLD_REGS_START_ADDR) ||
        (addr > _AM_MB_HOLD_REGS_END_ADDR)) {
        return AM_MB_EXP_ILLEGAL_DATA_ADDRESS;
    }

    _g_hold_regs[addr - _AM_MB_HOLD_REGS_START_ADDR] &= and;
    _g_hold_regs[addr - _AM_MB_HOLD_REGS_START_ADDR] |= or;

    return AM_MB_EXP_NONE;

}

/******************************************************************************/
/* ͨ�ù�����ص�����ע�� */
am_local
am_mb_err_t app_mb_slave_comm_callback_register (am_mb_slave_handle slave)
{
    /* ע�����Ȧ�ص����� */
    am_mb_slave_register_callback(slave,
                                  AM_MB_FUNC_COILS_CALLBACK,
                                  AM_MB_FUNC_CALLBACK_READ,
                                  _mb_slv_read_coils_callback);

    /* ע��д��Ȧ�ص����� */
    am_mb_slave_register_callback(slave,
                                  AM_MB_FUNC_COILS_CALLBACK,
                                  AM_MB_FUNC_CALLBACK_WRITE,
                                  _mb_slv_write_coils_callback);

    /* ע�����ɢ������ص����� */
    am_mb_slave_register_callback(slave,
                                  AM_MB_FUNC_DISCRETEINPUTS_CALLBACK,
                                  AM_MB_FUNC_CALLBACK_READ,
                                  _mb_slv_read_discrete_inputs_callback);

    /* ע������ּĴ����ص����� */
    am_mb_slave_register_callback(slave,
                                  AM_MB_FUNC_HOLDREGISTERS_CALLBACK,
                                  AM_MB_FUNC_CALLBACK_READ,
                                  _mb_slv_read_hold_regs_callback);

    /* ע��д���ּĴ����ص����� */
    am_mb_slave_register_callback(slave,
                                  AM_MB_FUNC_HOLDREGISTERS_CALLBACK,
                                  AM_MB_FUNC_CALLBACK_WRITE,
                                  _mb_slv_write_hold_regs_callback);

    /* ע�������Ĵ����ص����� */
    am_mb_slave_register_callback(slave,
                                  AM_MB_FUNC_INPUTREGISTERS_CALLBACK,
                                  AM_MB_FUNC_CALLBACK_READ,
                                  _mb_slv_read_input_regs_callback);

    /* ע����չд�Ĵ�������ص����� */
    am_mb_slave_register_handler(slave,
                                 _AM_MB_MASK_WR_REG_FUNCODE,
                                 _mb_slv_reg_wr_mask_callback);

    return AM_MB_ERR_NOERR;
}

/******************************************************************************/
/** \brief Modbus ��վ����ʾ�� */
void demo_aml165_core_mb_slave_test_entry (void)
{
    uint8_t     i       = 0;
    uint32_t    cur_ms;
    uint32_t    pre_ms;
    am_mb_err_t err;

    am_mb_slave_dev_t   mb_slave_dev;    /* ��վ�豸 */
    am_mb_slave_handle  mb_slave_handle; /* ��վ��� */

    am_funcode_handle_t funcode_buf[4];  /* �����û�ע�Ṧ�����ڴ� */
    am_mb_slave_info_t  mb_slave_info;   /* ��վ�豸��Ϣ */


    /* ��վ������ʼ�� */
    mb_slave_info.mode                  = AM_MB_ASCII;    /* RTUģʽ */
    mb_slave_info.slave_addr            = 0x08;           /* ��վ��ַ-0x08  */
    /* �����豸��Ϣ��ʼ�� */
    mb_slave_info.serial_info.uart      = am_zml165_uart1_inst_init();
    mb_slave_info.serial_info.baudrate  = 115200;         /* ��վ������-115200 */
    mb_slave_info.serial_info.parity    = AM_MB_PAR_NONE; /* ����-żУ��            */
    /* Ӳ����ʱ���豸��Ϣ��ʼ�� */
    mb_slave_info.timer_info.timer      = am_zml165_tim2_timing_inst_init ();
    mb_slave_info.timer_info.chan       = 0;

    /* ��ʼ����վ�豸����ȡ��վ��� */
    mb_slave_handle = am_mb_slave_init(&mb_slave_dev, &mb_slave_info, &err);
    if (err != AM_MB_ERR_NOERR) {
        return;
    }

    /* �����û�ע�Ṧ�����ڴ� */
    am_mbs_user_funcode_alloc(mb_slave_handle, funcode_buf,
                              AM_NELEMENTS(funcode_buf));

    /* ע��ͨ�ù�����ص����� */
    app_mb_slave_comm_callback_register(mb_slave_handle);

    am_mb_slave_start(mb_slave_handle);

    pre_ms = am_ticks_to_ms(am_sys_tick_get());
    AM_FOREVER {
        am_mb_slave_poll(mb_slave_handle);

        cur_ms = am_ticks_to_ms(am_sys_tick_get());
        if (cur_ms - pre_ms > 1000) {
            pre_ms = cur_ms;
            i++;
            if (i == 20) {
                i = 0;
                break;
            }
        }
    }

    /* �޸Ĵ�վ��ַ */
    am_mb_slave_stop(mb_slave_handle);
    am_mb_slave_set_addr(mb_slave_handle, 0x01);
    am_mb_slave_start(mb_slave_handle);

    pre_ms = am_ticks_to_ms(am_sys_tick_get());
    AM_FOREVER {
        am_mb_slave_poll(mb_slave_handle);

        cur_ms = am_ticks_to_ms(am_sys_tick_get());
        if (cur_ms - pre_ms > 1000) {
            pre_ms = cur_ms;
            i++;
            if (i == 10) {
                i = 0;
                break;
            }
        }
    }

    /* �޸�ΪӲ����ʱ�� */
    am_mb_slave_stop(mb_slave_handle);
    am_mb_slave_ioctl(mb_slave_handle, AM_MBS_TYPE_USED_HW_TMR, (void *)AM_TRUE);
    am_mb_slave_start(mb_slave_handle);

    AM_FOREVER {
        am_mb_slave_poll(mb_slave_handle);

        cur_ms = am_ticks_to_ms(am_sys_tick_get());
        if (cur_ms - pre_ms > 1000) {
            pre_ms = cur_ms;
            i++;
            if (i == 20) {
                i = 0;
                break;
            }
        }
    }

    /* �޸������ʱ�� */
    am_mb_slave_stop(mb_slave_handle);
    am_mb_slave_ioctl(mb_slave_handle, AM_MBS_TYPE_USED_HW_TMR, (void *)AM_FALSE);
    am_mb_slave_start(mb_slave_handle);

    pre_ms = am_ticks_to_ms(am_sys_tick_get());
    AM_FOREVER {
        am_mb_slave_poll(mb_slave_handle);
    }
}

/** [src_mb_slave_modbus_demo] */

/* end of file */


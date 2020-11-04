/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ƽ̨���亯����ʵ��
 *
 *  zlg72128_platform.h �ļ��������ĸ�������ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 19-4-22  xgg, first implementation.
 * \endinternal
 */
#include "zlg72128_platform.h"

/* ϵͳ�Ĵ�����ַ*/
static const uint8_t __g_sys_addr = 0x00;
/* ��ֵ�Ĵ�����ַ*/
static const uint8_t __g_key_addr = 0x01;

/* ��ֵ�ϱ�����*/
static void __zlg72128_key_report(zlg72128_plfm_t *p_plfm);
/* ����ֵ�Ƿ���Ч����*/
static void __zlg72128_key_vaild(zlg72128_plfm_t *p_plfm);

/* ms ������ʱ����ʵ�� */
void zlg72128_plfm_delay_ms (uint32_t ms)
{
    am_mdelay(ms);

}

/* ���ϵͳ�Ĵ����Ƿ���Ч����*/
static void __zlg72128_key_vaild(zlg72128_plfm_t *p_plfm)
{
    /* ���ϵͳ�Ĵ�����Ϊ0�������ζ�ȡ�����Ĵ���*/
    if (p_plfm->r_buff[0]) {

        am_i2c_mktrans(&p_plfm->trans[2],
                        p_plfm->p_devinfo->slv_addr,
                        AM_I2C_ADDR_7BIT | AM_I2C_M_WR,
                        (uint8_t *)&__g_key_addr,
                        1);

        /* ��ȡ��Ч��ֵ�Ĵ��� */
        am_i2c_mktrans(&p_plfm->trans[3],
                        p_plfm->p_devinfo->slv_addr,
                        AM_I2C_M_RD,
                        &p_plfm->r_buff[1],
                        3);
        /*������Ϣ*/
        am_i2c_mkmsg(&(p_plfm->msg),
                     &(p_plfm->trans[2]),
                     2,
                     (am_pfnvoid_t)__zlg72128_key_report,
                     (void *)p_plfm);

        /* ��ѯ��ֵ�Ĵ���ֵ*/
        am_i2c_msg_start(p_plfm->i2c_handle, &p_plfm->msg);
    } else {

        if (p_plfm->p_devinfo->use_int_pin) {
            /* ���´򿪴����ж�*/
            am_gpio_trigger_on(p_plfm->p_devinfo->int_pin);
        } else {
            /* ���������ʱ��*/
            am_softimer_start(&(p_plfm->timer),
                               p_plfm->p_devinfo->interval_ms);
        }
    }
}

/* �ϱ���Ч��ֵ����*/
static void __zlg72128_key_report(zlg72128_plfm_t *p_plfm)
{
    /* �ϱ���Ч��ֵ*/
    p_plfm->pfn_keyval_report(p_plfm->p_key_arg, &p_plfm->r_buff[1]);

    if (p_plfm->p_devinfo->use_int_pin) {
        /* ���´򿪴����ж�*/
        am_gpio_trigger_on(p_plfm->p_devinfo->int_pin);
    } else {
        /* ���������ʱ��*/
        am_softimer_start(&(p_plfm->timer),
                           p_plfm->p_devinfo->interval_ms);
    }
}

/* �����жϴ�����*/
static void __int_keyval_i2c_read(zlg72128_plfm_t *p_plfm)
{
    /* �ر������ж�*/
    if (am_gpio_trigger_off(p_plfm->p_devinfo->int_pin)) {
         return;
    }

    am_i2c_mktrans(&p_plfm->trans[0],
                    p_plfm->p_devinfo->slv_addr,
                    AM_I2C_ADDR_7BIT | AM_I2C_M_WR,
                    (uint8_t *)&__g_sys_addr,
                    1);

    /* ��ȡϵͳ�Ĵ��� */
    am_i2c_mktrans(&p_plfm->trans[1],
                    p_plfm->p_devinfo->slv_addr,
                    AM_I2C_M_RD,
                    p_plfm->r_buff,
                    1);

    /*������Ϣ*/
    am_i2c_mkmsg(&(p_plfm->msg),
                 &(p_plfm->trans[0]),
                 2,
                 (am_pfnvoid_t)__zlg72128_key_vaild,
                 (void *)p_plfm);

    /* ��ѯϵͳ�Ĵ���������ֵ�Ƿ���Ч*/
    am_i2c_msg_start(p_plfm->i2c_handle, &p_plfm->msg);
}

/* ��ʱ����ѯ������*/
static void __timer_keyval_i2c_read(zlg72128_plfm_t *p_plfm)
{
    if (!p_plfm->p_devinfo->use_int_pin) {
        /* �ر������ʱ��*/
        am_softimer_stop(&(p_plfm->timer));
    }

    am_i2c_mktrans(&p_plfm->trans[0],
                    p_plfm->p_devinfo->slv_addr,
                    AM_I2C_ADDR_7BIT | AM_I2C_M_WR,
                    (uint8_t *)&__g_sys_addr,
                    1);

    /* ��ȡϵͳ�Ĵ��� */
    am_i2c_mktrans(&p_plfm->trans[1],
                    p_plfm->p_devinfo->slv_addr,
                    AM_I2C_M_RD,
                    p_plfm->r_buff,
                    1);

    /*������Ϣ*/
    am_i2c_mkmsg(&(p_plfm->msg),
                 &(p_plfm->trans[0]),
                 2,
                 (am_pfnvoid_t)__zlg72128_key_vaild,
                 (void *)p_plfm);

    /* ��ѯϵͳ�Ĵ���������ֵ�Ƿ���Ч*/
    am_i2c_msg_start(p_plfm->i2c_handle, &p_plfm->msg);
}

/**
 * \brief ƽ̨��ʼ�����ú��������� zlg72128_init()�����У������ȵ���
 *
 * ��ƽ̨��صĳ�ʼ�������磬��ʼ��GPIO��I2C�ȡ��������жϵ�
 */
int zlg72128_plfm_init (zlg72128_plfm_t                  *p_plfm,
                        const zlg72128_plfm_init_info_t  *p_plfm_init_info,
                        void  (*pfn_keyval_report) (void *, uint8_t reg1_3[3]),
                        void                             *p_key_arg)
{
    int ret = 0;

    if (p_plfm == NULL || p_plfm_init_info == NULL) {

        return -AM_EINVAL;
    }

    p_plfm->p_devinfo         = p_plfm_init_info;
    p_plfm->p_key_arg         = p_key_arg;
    p_plfm->i2c_handle        = p_plfm_init_info->pfn_i2c_handle_get();
    p_plfm->pfn_keyval_report = pfn_keyval_report;

    /* �����ӻ��豸����I2C��д����*/
    am_i2c_mkdev(&p_plfm->i2c_dev,
                  p_plfm->i2c_handle,
                  p_plfm->p_devinfo->slv_addr,
                  AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    /* ��λ��������*/
    if (p_plfm->p_devinfo->rst_pin != -1) {
        /* ���ø�λ�������״̬Ϊ�͵�ƽ*/
        if (am_gpio_pin_cfg(p_plfm->p_devinfo->rst_pin,
                            AM_GPIO_OUTPUT_INIT_LOW)) {

            return -AM_ENOTSUP;
        }

        am_mdelay(1);
        /* ���߸�λ����*/
        if (am_gpio_set(p_plfm->p_devinfo->rst_pin, 1)) {

            return -AM_ENXIO;
        }
        am_mdelay(5);
    }

    /* �ж���������*/
    if (p_plfm->p_devinfo->use_int_pin) {

        if (am_gpio_pin_cfg(p_plfm->p_devinfo->int_pin,
                            AM_GPIO_INPUT | AM_GPIO_PULLUP)) {
            return -AM_ENOTSUP;
        }

        /* ����GPIO�����ж� */
        if (am_gpio_trigger_connect(p_plfm_init_info->int_pin,
                                    (am_pfnvoid_t)__int_keyval_i2c_read,
                                    (void *)p_plfm)) {
            return -AM_EPERM;
        }

        /* ����Ϊ�͵�ƽ��������ʧ��������Ϊ�½��ش���*/
        if(am_gpio_trigger_cfg(p_plfm_init_info->int_pin,
                               AM_GPIO_TRIGGER_LOW)) {

            if(am_gpio_trigger_cfg(p_plfm_init_info->int_pin,
                                   AM_GPIO_TRIGGER_FALL)) {
                /* ��֧�ֵ�ǰ������ʽ*/
                return -AM_EPERM;
            }

        }
        if (am_gpio_trigger_on(p_plfm_init_info->int_pin)) {

            /* ʹ�������ж�ʧ��*/
            return -AM_EPERM;
        }
    } else {
        /* ʹ�������ʱ����һ����ʱ����ɨ�� */
        ret = am_softimer_init(&(p_plfm->timer),
                               (am_pfnvoid_t)__timer_keyval_i2c_read,
                               (void *)p_plfm);

        if (ret) {
            return ret;
        }

        am_softimer_start(&(p_plfm->timer),
                          p_plfm->p_devinfo->interval_ms);
    }

    return AM_OK;
}

/**
 * \brief ƽ̨���ʼ��
 *
 * �ͷ�һЩ��ƽ̨��ص���Դ�����粿��ƽ̨��Ҫ�ر������жϡ��ͷ�����
 */
int zlg72128_plfm_deinit(zlg72128_plfm_t *p_plfm)
{
    int ret = 0;

    if(p_plfm == NULL) {
        return -AM_EINVAL;
    }

    p_plfm->p_devinfo->pfn_i2c_deinit(p_plfm->i2c_handle);

    if (p_plfm->p_devinfo->use_int_pin) {
        /* �ر������ж�*/
        if (am_gpio_trigger_off(p_plfm->p_devinfo->int_pin)) {
            return -AM_EPERM;
        }
        /* ɾ�����Żص�����*/
        ret = am_gpio_trigger_disconnect(p_plfm->p_devinfo->int_pin,
                                         (am_pfnvoid_t)__int_keyval_i2c_read,
                                         (void *)p_plfm);
        if (ret) {
            return ret;
        }
    } else {

        am_softimer_stop(&(p_plfm->timer));
    }

    return AM_OK;
}

/* I2Cд��������ʵ��*/
int zlg72128_plfm_i2c_write (zlg72128_plfm_t *p_plfm,
                             uint8_t          sub_addr,
                             uint8_t         *p_buf,
                             uint8_t          nbytes)
{
    if (p_plfm == NULL) {

        return -AM_EINVAL;
    }

    return am_i2c_write(&p_plfm->i2c_dev,
                         sub_addr,
                         p_buf,
                         nbytes);
}


/* end of file */

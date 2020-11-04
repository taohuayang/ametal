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
 * \brief SDIO����������SDIO��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 20-04-29  cds, first implementation
 * \endinternal
 */

/*******************************************************************************
  ͷ�ļ�
*******************************************************************************/
#include "am_hc32f460_sdioc.h"
#include "hw/amhw_hc32f460_sdioc.h"
#include "ametal.h"
#include "am_clk.h"
#include "hc32f460_clk.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_sdio.h"
#include "am_byteops.h"
#include "hc32f460_irq_handle.h"
#include "hc32f460_intctrl.h"


/** \brief SDIO �жϴ����� */
void hc32f460_sdioc_irq_handle (void *p_arg);

static int __sdio_setup (void *p_drv, struct am_sdio_device *p_device);
static int __sdio_msg_start (void                  *p_drv,
                             struct am_sdio_device *p_dev,
                             struct am_sdio_msg    *p_msg);

/**
 * \brief SDIO ������������
 */
static am_const struct am_sdio_drv_funcs __g_sdio_drv_funcs = {
     __sdio_setup,
     __sdio_msg_start
};

/** \brief SDIO �жϴ����� */
void hc32f460_sdioc_irq_handle (void *p_arg)
{
    am_hc32f460_sdioc_dev_t *p_dev     = (am_hc32f460_sdioc_dev_t *)p_arg;
    amhw_hc32f460_sdioc_t   *p_hw_sdioc = (amhw_hc32f460_sdioc_t *)p_dev->p_devinfo->regbase;
    uint16_t                 status_normal    = 0;

    status_normal = amhw_hc32f460_sdioc_normal_intstat_all_get(p_hw_sdioc);

    if (AMHW_HC32F460_SDIOC_NORMAL_INT_CC & status_normal) {
        if (p_dev->int_normal_status == AMHW_HC32F460_SDIOC_NORMAL_INT_CC) {
            p_dev->int_normal_status = 0;
            am_wait_done(&p_dev->wait);
        }
        amhw_hc32f460_sdioc_normal_intstat_clr(p_hw_sdioc,
                                               AMHW_HC32F460_SDIOC_NORMAL_INT_CC);
    }

    if (AMHW_HC32F460_SDIOC_NORMAL_INT_TC & status_normal) {
        if (p_dev->int_normal_status == AMHW_HC32F460_SDIOC_NORMAL_INT_TC) {
            p_dev->int_normal_status = 0;
            am_wait_done(&p_dev->wait);
        }
        amhw_hc32f460_sdioc_normal_intstat_clr(p_hw_sdioc,
                                               AMHW_HC32F460_SDIOC_NORMAL_INT_TC);
    }
}

static int __sdio_cmd_send (am_hc32f460_sdioc_dev_t *p_dev,
                            am_sdio_trans_t         *p_trans)
{
    int              ret;
    amhw_hc32f460_sdioc_t *p_hw_sdioc = (amhw_hc32f460_sdioc_t *)p_dev->p_devinfo->regbase;
    uint16_t reg_temp = 0;
    uint16_t transmode = 0;


    /* ������������ĵ�16λ */
    amhw_hc32f460_sdioc_arg0_set (p_hw_sdioc, (p_trans->arg & 0xFFFF));
    /* ������������ĸ�16λ */
    amhw_hc32f460_sdioc_arg1_set (p_hw_sdioc, (p_trans->arg & 0xFFFF0000) >> 16);

    reg_temp |= (p_trans->cmd & 0x3F) << 8;

    /* ��ʱĬ����ͨ����������ݣ������Ӧ���е������ź�CRCУ���룬û�д�busy��Ӧ�� */
    switch (p_trans->rsp_type) {
    case AM_SDIO_RESPONSE_NO :
        reg_temp |= AMHW_HC32F460_SDIOC_CMD_NO_RESPONSE;
        break;
    case AM_SDIO_RESPONSE_SHORT :
        reg_temp |= AMHW_HC32F460_SDIOC_CMD_48BIT_RESPONSE;
        break;
    case AM_SDIO_RESPONSE_LONG :
        reg_temp |= AMHW_HC32F460_SDIOC_CMD_136BIT_RESPONSE;
        break;
    }

    if (p_trans->cmd == 25 || p_trans->cmd == 24) {
        p_hw_sdioc->BLKCNT = p_trans->nblock;
        p_hw_sdioc->BLKSIZE = p_trans->blk_size;
        if (p_trans->nblock > 1) {
            transmode |= (1 << 5);
        }

        transmode |= (1 << 1);
        p_hw_sdioc->TRANSMODE = transmode;
    }

    if (p_trans->cmd == 18 || p_trans->cmd == 17) {
        p_hw_sdioc->BLKCNT = p_trans->nblock;
        p_hw_sdioc->BLKSIZE = p_trans->blk_size;
        if (p_trans->nblock > 1) {
            transmode |= (1 << 5);
        }

        transmode |= (1 << 4);
        transmode |= (1 << 1);
        p_hw_sdioc->TRANSMODE = transmode;
    }

    /* ���ֿ�Ƭ��֧�ָ����� */
    if (p_trans->cmd == 4) {
        return AM_OK;
    }

    /* ������ɺ������Զ����� */
    amhw_hc32f460_sdioc_cmd_set(p_hw_sdioc, reg_temp);

    p_dev->int_normal_status = AMHW_HC32F460_SDIOC_NORMAL_INT_CC;

    /* �ȴ�������ɣ���Ӧ���������ɺ���Ӧ�������Ӧ�������ɣ� */
    if ((ret = am_wait_on_timeout(&p_dev->wait, 10)) != AM_OK) {
        return ret;
    }

    /* ��ȡ�������Ӧ */
    if (p_trans->rsp_type == AM_SDIO_RESPONSE_SHORT) {

        if (p_trans->p_rsp) {
            p_trans->p_rsp[0] = (uint32_t)amhw_hc32f460_sdioc_resp0_15b_read(p_hw_sdioc) |
                                ((uint32_t)amhw_hc32f460_sdioc_resp16_31b_read(p_hw_sdioc) << 16);
            p_trans->p_rsp[1] =  (uint32_t)amhw_hc32f460_sdioc_resp32_47b_read(p_hw_sdioc);
        }

    } else if (p_trans->rsp_type == AM_SDIO_RESPONSE_LONG) {

        if (p_trans->p_rsp) {
            p_trans->p_rsp[0] =  (uint32_t)amhw_hc32f460_sdioc_resp0_15b_read(p_hw_sdioc) |
                                 ((uint32_t)amhw_hc32f460_sdioc_resp16_31b_read(p_hw_sdioc) << 16);
            p_trans->p_rsp[1] =  (uint32_t)amhw_hc32f460_sdioc_resp32_47b_read(p_hw_sdioc) |
                                 ((uint32_t)amhw_hc32f460_sdioc_resp48_63b_read(p_hw_sdioc) << 16);
            p_trans->p_rsp[2] =  (uint32_t)amhw_hc32f460_sdioc_resp64_79b_read(p_hw_sdioc) |
                                 ((uint32_t)amhw_hc32f460_sdioc_resp80_95b_read(p_hw_sdioc) << 16);
            p_trans->p_rsp[3] =  (uint32_t)amhw_hc32f460_sdioc_resp96_111b_read(p_hw_sdioc) |
                                 ((uint32_t)amhw_hc32f460_sdioc_resp112_127b_read(p_hw_sdioc) << 16);
        }
    }

    return AM_OK;
}

static int __sdio_data_send (am_hc32f460_sdioc_dev_t *p_dev,
                             am_sdio_trans_t         *p_trans)
{
    int                    ret;
    uint32_t               i           = 0;
    uint32_t              *p_data      = (uint32_t *)p_trans->p_data;
    amhw_hc32f460_sdioc_t *p_hw_sdioc   = (amhw_hc32f460_sdioc_t *)p_dev->p_devinfo->regbase;

    am_sdio_timeout_obj_t timeout;

    amhw_hc32f460_sdioc_blksize_set(p_hw_sdioc, p_trans->blk_size);

    amhw_hc32f460_sdioc_transmode_dir_set (p_hw_sdioc,
                                           AMHW_HC32F460_SDIOC_TRANSMODE_DIR_WRITE);

    p_dev->int_normal_status = AMHW_HC32F460_SDIOC_NORMAL_INT_TC;

    am_sdio_timeout_set(&timeout, 10);
    do {
        if (am_sdio_timeout(&timeout)) {
            return -AM_ETIME;
        }
    } while(!amhw_hc32f460_sdioc_normal_intstat_get(p_hw_sdioc,
                                                    AMHW_HC32F460_SDIOC_NORMAL_INT_BWR));

    uint32_t blk_num = p_trans->nblock;

    while(blk_num) {
        if (amhw_hc32f460_sdioc_normal_intstat_get(p_hw_sdioc, AMHW_HC32F460_SDIOC_NORMAL_INT_BWR) &&
            amhw_hc32f460_sdioc_pstat_get(p_hw_sdioc, AMHW_HC32F460_SDIOC_PSTAT_BWE)){
            for(i = 0; i < p_trans->blk_size; i += 4) {
                amhw_hc32f460_sdioc_data_write(p_hw_sdioc, *p_data++);
            }
            blk_num--;
        }
    }

    ret = am_wait_on_timeout(&p_dev->wait, 1000);

    return ret;
}

static int __sdio_data_recv(am_hc32f460_sdioc_dev_t *p_dev,
                            am_sdio_trans_t   *p_trans)
{
    uint32_t               i            = 0;
    uint32_t              *p_buf        = (uint32_t *)p_trans->p_data;
    amhw_hc32f460_sdioc_t *p_hw_sdioc   = (amhw_hc32f460_sdioc_t *)p_dev->p_devinfo->regbase;

    amhw_hc32f460_sdioc_blksize_set(p_hw_sdioc, p_trans->blk_size);

    amhw_hc32f460_sdioc_transmode_dir_set (p_hw_sdioc,
                                           AMHW_HC32F460_SDIOC_TRANSMODE_DIR_READ);

    p_dev->int_normal_status = AMHW_HC32F460_SDIOC_NORMAL_INT_TC;

    uint32_t blk_num = p_trans->nblock;

    while(blk_num) {
        if (amhw_hc32f460_sdioc_normal_intstat_get(p_hw_sdioc, AMHW_HC32F460_SDIOC_NORMAL_INT_BRR) &&
           amhw_hc32f460_sdioc_pstat_get(p_hw_sdioc, AMHW_HC32F460_SDIOC_PSTAT_BRE)){
            for(i = 0; i < p_trans->blk_size; i += 4) {
                *p_buf++ = amhw_hc32f460_sdioc_data_read(p_hw_sdioc);
            }
            blk_num--;
        }
    }

    return AM_OK;
}

static int __sdio_transfer (void *p_drv, am_sdio_trans_t *p_trans)
{
    int                      ret   = AM_ERROR;
    am_hc32f460_sdioc_dev_t *p_dev = (am_hc32f460_sdioc_dev_t *)p_drv;

    ret = __sdio_cmd_send(p_dev, p_trans);

    if (ret != AM_OK) {
        return ret;
    }

    if (p_trans->p_data) {
        if (p_trans->opt == AM_SDIO_OW) {
            ret = __sdio_data_send(p_dev, p_trans);
        } else {
            ret = __sdio_data_recv(p_dev, p_trans);
        }
    }

    return ret;
}

static void __clk_div_set(amhw_hc32f460_sdioc_t   *p_hw_sdioc,
                             uint32_t                 sdio_speed)
{
    uint32_t clk_exclk = am_clk_rate_get(CLK_EXCLK);
    uint32_t clk_div_temp = 1;
    uint32_t clk_rate_temp = 0;
    uint32_t err_min = 0;
    uint32_t err_now  = 0;
    uint8_t i = 0;
    uint8_t temp = 0;

    for (i = 0; i < 9; i++) {
        if (i == 0) {
            clk_div_temp = 1;
        } else {
            clk_div_temp = 2 * clk_div_temp;
        }

        clk_rate_temp = clk_exclk / clk_div_temp;
        err_now = (sdio_speed > clk_rate_temp) ?
                  (sdio_speed - clk_rate_temp) : (clk_rate_temp - sdio_speed);

        if (i == 0) {
            err_min = err_now;
            temp = 0;
        } else if (err_now < err_min) {
            err_min = err_now;
            temp = i;
        }
    }

    switch (temp) {

        case 0: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_1);
            break;
        case 1: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_2);
            break;
        case 2: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_4);
            break;
        case 3: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_8);
            break;
        case 4: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_16);
            break;
        case 5: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_32);
            break;
        case 6: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_64);
            break;
        case 7: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_128);
            break;
        case 8: amhw_hc32f460_sdioc_clkcon_clkdiv_set(p_hw_sdioc,
                                                      AMHW_HC32F460_SDIOC_CK_DIV_256);
            break;
    }
}


static int __sdio_setup (void *p_drv, struct am_sdio_device *p_device)
{
    am_hc32f460_sdioc_dev_t *p_hc32f460_sdio_dev = (am_hc32f460_sdioc_dev_t *)p_drv;
    amhw_hc32f460_sdioc_t   *p_hw_sdioc          = (amhw_hc32f460_sdioc_t *)p_hc32f460_sdio_dev->p_devinfo->regbase;

    amhw_hc32f460_sdioc_all_rst(p_hw_sdioc, AM_TRUE);

    while(p_hw_sdioc->SFTRST_f.RSTA == 1);

    /* ʱ�ӷ�Ƶ���� */
    __clk_div_set (p_hw_sdioc, p_device->speed);

    /* ʹ��ʱ�� */
    amhw_hc32f460_sdioc_clkcon_ck_enable(p_hw_sdioc);

    /* ʹ��SDIOx_CK��� */
    amhw_hc32f460_sdioc_clkcon_ck_output(p_hw_sdioc);

    amhw_hc32f460_sdioc_enable(p_hw_sdioc);

    if (p_device->mode == AM_SDIO_SD_1B_M) {
        amhw_hc32f460_sdioc_hostcon_datawide_set(p_hw_sdioc,
                                                 AMHW_HC32F460_HOSTCON_DATA_WIDE_1BIT);
    } else if(p_device->mode == AM_SDIO_SD_4B_M) {
        amhw_hc32f460_sdioc_hostcon_datawide_set(p_hw_sdioc,
                                                 AMHW_HC32F460_HOSTCON_DATA_WIDE_4BIT);
    } else if(p_device->mode == AM_SDIO_SD_8B_M) {
        amhw_hc32f460_sdioc_hostcon_exdw_enable(p_hw_sdioc);
    } else {
        return -AM_EINVAL;
    }

    /* ����ж�״̬ */
    amhw_hc32f460_sdioc_normal_intstat_clr(p_hw_sdioc, AMHW_HC32F460_SDIOC_NORMAL_INT_ALL);
    amhw_hc32f460_sdioc_err_intstat_clr(p_hw_sdioc, AMHW_HC32F460_SDIOC_ERR_INT_ALL);


    /* ʹ���ж�״̬ */
    amhw_hc32f460_sdioc_normal_intstat_enable(p_hw_sdioc,
                                              AMHW_HC32F460_SDIOC_NORMAL_INT_ALL |
                                              AMHW_HC32F460_SDIOC_NORMAL_INT_CINT);
    amhw_hc32f460_sdioc_err_intstat_enable(p_hw_sdioc, AMHW_HC32F460_SDIOC_ERR_INT_ALL);

    /* ʹ���ж��ź� */
    amhw_hc32f460_sdioc_normal_int_signal_enable(p_hw_sdioc,
                                                 AMHW_HC32F460_SDIOC_NORMAL_INT_TC |
                                                 AMHW_HC32F460_SDIOC_NORMAL_INT_CC);


    return AM_OK;
}

static int __sdio_msg_start (void                  *p_drv,
                             struct am_sdio_device *p_dev,
                             struct am_sdio_msg    *p_msg)
{
    am_sdio_trans_t   *p_trans = NULL;
    int                ret     = AM_ERROR;

    while(!(am_list_empty(&p_msg->trans_list))) {
        p_trans = am_sdio_msg_out(p_msg);
        do {
            ret = __sdio_transfer(p_drv, p_trans);

            if (ret != AM_OK) {
                p_msg->status = ret;

                return p_msg->status;
            }

        } while ((ret != AM_OK) && (p_trans->retries--));

    }

    if (ret == AM_OK) {
        p_msg->status = AM_OK;
    }

    if (p_msg->pfn_complete) {
        p_msg->pfn_complete(p_msg->p_arg);
    }

    return p_msg->status;
}




am_sdio_handle_t am_hc32f460_sdioc_init (am_hc32f460_sdioc_dev_t           *p_dev,
                                         const am_hc32f460_sdioc_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->sdio_serv.p_funcs = (struct am_sdio_drv_funcs *)&__g_sdio_drv_funcs;
    p_dev->sdio_serv.p_drv   = p_dev;

    p_dev->p_devinfo         = p_devinfo;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    am_wait_init(&p_dev->wait);

    /* �����жϺ��� */
    if (p_dev->p_devinfo->dev_id == 1) {
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_SDIOC1_INT_VSSEL_BITS_MASK);
    } else if (p_dev->p_devinfo->dev_id == 2){
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_SDIOC2_INT_VSSEL_BITS_MASK);
    }

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, IRQ143_Handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->sdio_serv);
}

void am_hc32f460_sdioc_deinit (am_sdio_handle_t handle)
{
    am_hc32f460_sdioc_dev_t *p_dev = (am_hc32f460_sdioc_dev_t *)handle;

    if (p_dev->p_devinfo->pfn_plfm_init) {
        p_dev->p_devinfo->pfn_plfm_init();
    }

    /* �����ж����λ���� */
    if (p_dev->p_devinfo->dev_id == 1) {
        amhw_hc32f460_intc_int_vssel_bits_clr(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_SDIOC1_INT_VSSEL_BITS_MASK);
    } else if (p_dev->p_devinfo->dev_id == 2){
        amhw_hc32f460_intc_int_vssel_bits_clr(p_dev->p_devinfo->inum,
                                              AMHW_HC32F460_SDIOC2_INT_VSSEL_BITS_MASK);
    }

    /* �����жϺ���û�й����жϱ�ʹ�ܣ���ɾ�����ӣ��ر��ж� */
    if (amhw_hc32f460_intc_int_vssel_get(p_dev->p_devinfo->inum) == 0) {
        am_int_disconnect(p_dev->p_devinfo->inum, IRQ143_Handler, (void *)p_dev);
        am_int_disable(p_dev->p_devinfo->inum);
    }
}

/* end of file */

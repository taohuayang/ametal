#include "am_boot_flash.h"
#include "am_xmodem.h"
#include "am_boot_firmware_recv.h"
#include "am_boot_enter_check.h"
#include "am_boot_firmware.h"
#include "am_boot_msg.h"


int am_zlg116_clk_inst_deinit (void);

/** \brief ����BootLoader��׼�ӿ�ʵ����ʼ��*/
int am_zlg116_boot_single_inst_init(void);

/** \brief �����̼����ʵ����ʼ�� */
am_boot_firmware_handle_t am_zlg116_boot_single_firmware_flash_inst_init(void);

/* end of file */

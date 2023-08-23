#include "bsp_iwdt.h"
#include "bsp_led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "R7FA6M5BH.h"


void IWDT_Init(void)
{
    /*如果是J-Link调试器的话需要加上这句话*/
    R_DEBUG->DBGSTOPCR_b.DBGSTOP_IWDT = 0;

    /*独立看门狗初始化*/  //RSTSR0
		
		R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_14, BSP_IO_LEVEL_HIGH);
    R_IWDT_Open(&g_iwdt0_ctrl, &g_iwdt0_cfg);
	
		
		(void) R_IWDT_Refresh(&g_iwdt0_ctrl);
	
		
		
}


void IWDT_Feed(void)
{
    /*刷新看门狗计数器*/
    (void) R_IWDT_Refresh(&g_iwdt0_ctrl);
}

void sysReset(void)
{
    vTaskSuspendAll();
    __set_FAULTMASK(1);
    NVIC_SystemReset();
    xTaskResumeAll();
}

/* 当看门狗NMI发生时中断回调 */
void iwdt_callback(wdt_callback_args_t * p_args)
{
      /*防止编译器产生关于函数中没有使用形参的警告*/
      (void) p_args;
			
      /* 通过软件复位MCU*/
      sysReset();
}



#include "bsp_iwdt.h"
#include "bsp_led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "R7FA6M5BH.h"


void IWDT_Init(void)
{
    /*�����J-Link�������Ļ���Ҫ������仰*/
    R_DEBUG->DBGSTOPCR_b.DBGSTOP_IWDT = 0;

    /*�������Ź���ʼ��*/  //RSTSR0
		
		R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_14, BSP_IO_LEVEL_HIGH);
    R_IWDT_Open(&g_iwdt0_ctrl, &g_iwdt0_cfg);
	
		
		(void) R_IWDT_Refresh(&g_iwdt0_ctrl);
	
		
		
}


void IWDT_Feed(void)
{
    /*ˢ�¿��Ź�������*/
    (void) R_IWDT_Refresh(&g_iwdt0_ctrl);
}

void sysReset(void)
{
    vTaskSuspendAll();
    __set_FAULTMASK(1);
    NVIC_SystemReset();
    xTaskResumeAll();
}

/* �����Ź�NMI����ʱ�жϻص� */
void iwdt_callback(wdt_callback_args_t * p_args)
{
      /*��ֹ�������������ں�����û��ʹ���βεľ���*/
      (void) p_args;
			
      /* ͨ�������λMCU*/
      sysReset();
}



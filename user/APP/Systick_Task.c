#include "Systick_Task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "qe_touch_config.h"

void vSystick_Task( void *pvParameters )
{
	FSP_PARAMETER_NOT_USED(pvParameters);
	TickType_t tick;
	tick = xTaskGetTickCount();
	
	while(1)
	{
		/* ��Ҫ�����Դ���ĳ��򣬶�Ӧ������̵��õ�SysTick_ISR */
		xTaskDelayUntil(&tick,pdMS_TO_TICKS(1));
	

		
	}
	
}
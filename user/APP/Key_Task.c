#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_api.h"
#include "Key_Task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Wdt_Task.h"

void vKey_Task( void *pvParameters )
{
	FSP_PARAMETER_NOT_USED(pvParameters);
	while(1)
	{
		vTaskDelay(100);
		if( Key_Scan(KEY_SW2_PIN) == KEY_ON ) //ɨ���жϰ���
		{
			vTaskDelay(pdMS_TO_TICKS( 9000UL ));
			LED1_ON; //�궨�� LED ��
			LED2_ON;
			LED3_ON;
		}
		if( Key_Scan(KEY_SW3_PIN) == KEY_ON )
		{
			vTaskDelay(pdMS_TO_TICKS( 9000UL ));
			LED1_OFF; //�궨�� LED ��
			LED2_OFF;
			LED3_OFF;
		}
		xEventGroupSetBits(xEventGroup, TASK1);
	}
	
	
}

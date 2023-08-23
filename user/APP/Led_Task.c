#include "bsp_led.h"
#include "bsp_api.h"
#include "Led_Task.h"
#include "FreeRTOS.h"
#include "task.h"

void vLed_Task( void *pvParameters )
{
	FSP_PARAMETER_NOT_USED(pvParameters);
	uint16_t count = 0;
		while(1)
		{
			switch(count)
			{
				case 0:
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_LOW); //LED1 ¡¡
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_03, BSP_IO_LEVEL_HIGH); //LED2 ¡¡
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_04, BSP_IO_LEVEL_HIGH); //LED3 ¡¡
					LED1_ON;
					LED2_OFF;
					LED3_OFF;
					vTaskDelay(pdMS_TO_TICKS(1000));//œµÕ≥ ±÷”
					//R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_SECONDS);
					count++;
				break;
				case 1:
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_HIGH); //LED1 ¡¡
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_03, BSP_IO_LEVEL_LOW); //LED2 ¡¡
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_04, BSP_IO_LEVEL_HIGH); //LED3 ¡¡
					LED1_OFF;
					LED2_ON;
					LED3_OFF;
					vTaskDelay(pdMS_TO_TICKS(1000));
					//R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_SECONDS);
					count++;
					break;
				case 2:
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_HIGH); //LED1 ¡¡
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_03, BSP_IO_LEVEL_HIGH); //LED2 ¡¡
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_04, BSP_IO_LEVEL_LOW); //LED3 ¡¡
					LED1_OFF;
					LED2_OFF;
					LED3_ON;
					vTaskDelay(pdMS_TO_TICKS(1000));
					//R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_SECONDS);
					count++;
					break;
				default:
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_HIGH); //LED1 ¡¡
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_03, BSP_IO_LEVEL_HIGH); //LED2 ¡¡
//					R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_04, BSP_IO_LEVEL_HIGH); //LED3 ¡¡
					LED1_OFF;
					LED2_OFF;
					LED3_OFF;
					count = 0;
					break;
			}
		}
	
}
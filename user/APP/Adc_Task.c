#include "FreeRTOS.h"
#include "task.h"
#include "Adc_Task.h"
#include "bsp_adc.h"
#include "semphr.h"
#include "stdio.h"
#include "Wdt_Task.h"
#include "bsp_gpt_timing.h"
extern SemaphoreHandle_t xSemaphore;

QueueHandle_t xQueue;

void vAdc_Task( void *pvParameters )
{
	FSP_PARAMETER_NOT_USED(pvParameters);
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 100UL );
	BaseType_t xStatus;
	double lReceivedValue;
	adc_Init();
	GPT_Timing_Init();
	/* 创建队列: 长度为5，数据大小为4字节(存放一个整数) */
	xQueue = xQueueCreate( 10, sizeof( double ) );
	if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
	{
		printf("开始读取 ADC 的数值\r\n");
		xSemaphoreGive(xSemaphore);
	}
	//double adc_data = 0.0;
	while(1)
	{
		xEventGroupSetBits(xEventGroup, TASK4);
		xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );
		if( xStatus == pdPASS )
		{
			if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
			{
				printf("a0=%f\r\n",lReceivedValue);
				xSemaphoreGive(xSemaphore);
			}
			//adc_data = adc_read();
		}
		//vTaskDelay(pdMS_TO_TICKS(100));
	}
	
}

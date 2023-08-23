#include "bsp_uart4.h"
#include "bsp_api.h"
#include "Debug_Task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"
#include "Wdt_Task.h"
extern SemaphoreHandle_t xSemaphore;


void vDebug_Task( void *pvParameters )
{
		FSP_PARAMETER_NOT_USED(pvParameters);
		uint8_t Read_Buffer[DATA_LEN];
		uint16_t Read_Length;
		Debug_UART4_Init();
		Queue_Init((Circular_queue_t*)&Circular_queue); //环形队列初始化
		if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)//判断队列中的数据不为空
		{
			printf("这是一个串口环形队列例程\r\n");
			printf("打开串口助手发送数据 5 个及以上的数据，接收窗口会打印所发送的数据\r\n");
			xSemaphoreGive(xSemaphore);
		}
		while(1)
		{
			xEventGroupSetBits(xEventGroup, TASK2);
			if (Queue_isEmpty(&Circular_queue) == false) //判断队列中的数据不为空
			{
				Read_Length = Queue_HadUse(&Circular_queue);
				if( (Read_Length >= 5) && (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)) // 如果队列中的数据大于等于 5 个，开始打印队列中的所有数据
				{
					printf("Read_Length=%d: ", Read_Length);
					memset(Read_Buffer, 0, DATA_LEN);
					/* 读出 Read_Length 个数据 */
					Queue_Read(&Circular_queue, Read_Buffer, Read_Length);
					printf("%s\r\n", Read_Buffer);
					xSemaphoreGive(xSemaphore);
				}
			}
			vTaskDelay(pdMS_TO_TICKS(100));
		}
	
}

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
		Queue_Init((Circular_queue_t*)&Circular_queue); //���ζ��г�ʼ��
		if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)//�ж϶����е����ݲ�Ϊ��
		{
			printf("����һ�����ڻ��ζ�������\r\n");
			printf("�򿪴������ַ������� 5 �������ϵ����ݣ����մ��ڻ��ӡ�����͵�����\r\n");
			xSemaphoreGive(xSemaphore);
		}
		while(1)
		{
			xEventGroupSetBits(xEventGroup, TASK2);
			if (Queue_isEmpty(&Circular_queue) == false) //�ж϶����е����ݲ�Ϊ��
			{
				Read_Length = Queue_HadUse(&Circular_queue);
				if( (Read_Length >= 5) && (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)) // ��������е����ݴ��ڵ��� 5 ������ʼ��ӡ�����е���������
				{
					printf("Read_Length=%d: ", Read_Length);
					memset(Read_Buffer, 0, DATA_LEN);
					/* ���� Read_Length ������ */
					Queue_Read(&Circular_queue, Read_Buffer, Read_Length);
					printf("%s\r\n", Read_Buffer);
					xSemaphoreGive(xSemaphore);
				}
			}
			vTaskDelay(pdMS_TO_TICKS(100));
		}
	
}

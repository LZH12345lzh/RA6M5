#include "Wdt_Task.h"

#include "bsp_iwdt.h" 
#include "stdio.h"
extern SemaphoreHandle_t xSemaphore;


void vWdt_Task( void *pvParameters )
{
	FSP_PARAMETER_NOT_USED(pvParameters);
	EventBits_t uxBits;
	uint32_t iwdt_counter;	fsp_err_t err;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 1000UL ); /* ����ӳ�1000ms */;
	if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) //�ж϶����е����ݲ�Ϊ��
	{
		printf("���Ź�����ʼ BSP_CFG_ROM_REG_OFS0 = 0x%x\r\n",BSP_CFG_ROM_REG_OFS0);
		xSemaphoreGive(xSemaphore);
	}
	IWDT_Init();
	while(1)
	{
		/* �ȴ������������¼���־ */
		uxBits = xEventGroupWaitBits(xEventGroup, 			 /* �¼���־���� */
																 TASK1|TASK2|TASK3|TASK4|TASK5,        /* �ȴ�TASK_BIT_ALL������ */
																 pdTRUE,             /* �˳�ǰTASK_BIT_ALL�������������TASK_BIT_ALL�������òű�ʾ���˳���*/
																 pdTRUE,             /* ����ΪpdTRUE��ʾ�ȴ�TASK_BIT_ALL��������*/
																 xTicksToWait);      /* �ȴ��ӳ�ʱ�� */
		if((uxBits & (TASK1|TASK2|TASK3|TASK4|TASK5)) == (TASK1|TASK2|TASK3|TASK4|TASK5))
		{
				if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
				{
					err = R_IWDT_CounterGet(&g_iwdt0_ctrl,&iwdt_counter);
					printf("����û������������� iwdt_counter=%d  err=%d\r\n",iwdt_counter,err);
					xSemaphoreGive(xSemaphore);
				}
				IWDT_Feed();
		}
		else
		{
				if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) //�ж϶����е����ݲ�Ϊ��
				{
					err = R_IWDT_CounterGet(&g_iwdt0_ctrl,&iwdt_counter);
					printf("����û����񲢷Ƕ��������� iwdt_counter=%d  err=%d\r\n",iwdt_counter,err);
					xSemaphoreGive(xSemaphore);
				}
				IWDT_Feed();
				/* ������ÿxTicksToWait����һ�� */
				/* ͨ������uxBits�򵥵Ŀ����ڴ˴�����Ǹ�������û�з������б�־ */
		}
		
	}
	
}





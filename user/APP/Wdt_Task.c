#include "Wdt_Task.h"

#include "bsp_iwdt.h" 
#include "stdio.h"
extern SemaphoreHandle_t xSemaphore;


void vWdt_Task( void *pvParameters )
{
	FSP_PARAMETER_NOT_USED(pvParameters);
	EventBits_t uxBits;
	uint32_t iwdt_counter;	fsp_err_t err;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 1000UL ); /* 最大延迟1000ms */;
	if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) //判断队列中的数据不为空
	{
		printf("看门狗任务开始 BSP_CFG_ROM_REG_OFS0 = 0x%x\r\n",BSP_CFG_ROM_REG_OFS0);
		xSemaphoreGive(xSemaphore);
	}
	IWDT_Init();
	while(1)
	{
		/* 等待所有任务发来事件标志 */
		uxBits = xEventGroupWaitBits(xEventGroup, 			 /* 事件标志组句柄 */
																 TASK1|TASK2|TASK3|TASK4|TASK5,        /* 等待TASK_BIT_ALL被设置 */
																 pdTRUE,             /* 退出前TASK_BIT_ALL被清除，这里是TASK_BIT_ALL都被设置才表示“退出”*/
																 pdTRUE,             /* 设置为pdTRUE表示等待TASK_BIT_ALL都被设置*/
																 xTicksToWait);      /* 等待延迟时间 */
		if((uxBits & (TASK1|TASK2|TASK3|TASK4|TASK5)) == (TASK1|TASK2|TASK3|TASK4|TASK5))
		{
				if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
				{
					err = R_IWDT_CounterGet(&g_iwdt0_ctrl,&iwdt_counter);
					printf("五个用户任务都正常运行 iwdt_counter=%d  err=%d\r\n",iwdt_counter,err);
					xSemaphoreGive(xSemaphore);
				}
				IWDT_Feed();
		}
		else
		{
				if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) //判断队列中的数据不为空
				{
					err = R_IWDT_CounterGet(&g_iwdt0_ctrl,&iwdt_counter);
					printf("五个用户任务并非都正常运行 iwdt_counter=%d  err=%d\r\n",iwdt_counter,err);
					xSemaphoreGive(xSemaphore);
				}
				IWDT_Feed();
				/* 基本是每xTicksToWait进来一次 */
				/* 通过变量uxBits简单的可以在此处检测那个任务长期没有发来运行标志 */
		}
		
	}
	
}





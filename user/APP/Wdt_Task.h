#ifndef __WTDTASK_H
#define __WDTTASK_H
#include "FreeRTOS.h"
#include "task.h"
#include "hal_data.h"
#include "event_groups.h"
#include "semphr.h"
extern EventGroupHandle_t xEventGroup;
//typedef enum
//{
//	TASK1 = (uint8_t)0X00,
//	TASK2 ,
//	TASK3 ,
//	TASK4 ,
//	TASK5 ,
//	TASK6 ,
//	TASK7 ,
//	TASK8 ,
//	TASK9 ,
//	TASK10,
//	TASK_NUM
//}TASK_t;

//#define TaskSetFlag(num)  (1<<num)

#define TASK1  (1<<0)
#define TASK2  (1<<1)
#define TASK3  (1<<2)
#define TASK4  (1<<3)
#define TASK5  (1<<4)

//#define TASK_BIT_ALL      TaskSetFlag(TASK1) | TaskSetFlag(TASK2)| TaskSetFlag(TASK3)| TaskSetFlag(TASK4)| TaskSetFlag(TASK5)
void vWdt_Task( void *pvParameters );

#endif

/*
 * FreeRTOS Kernel V10.4.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */
 //.\Objects\EBF_RA6M5.axf: Error: L6218E: Undefined symbol MPU_xTaskCreate (referred from hal_entry.o).

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "bsp_api.h"
#define configENABLE_FPU    										0
#define configENABLE_MPU												0
#define configENABLE_TRUSTZONE 									0
#define configRUN_FREERTOS_SECURE_ONLY 					1
#define INCLUDE_vTaskDelayUntil                 1

#define configMAX_PRIORITIES                  ( 5 )
#define configUSE_PREEMPTION                    1
#define configMINIMAL_STACK_SIZE      			 ( 128 ) 
#define configUSE_IDLE_HOOK               		 	0
#ifndef configUSE_TICK_HOOK
		#define configUSE_TICK_HOOK           			0
#endif
 #define configMAX_TASK_NAME_LEN               (16)
#define configUSE_16_BIT_TICKS                  0
#define configTICK_RATE_HZ                   ( 1000 )       
#define configCPU_CLOCK_HZ                 SystemCoreClock  //200 000 000  / 1000 = 200 000 / 200 000 000 = 1/1000 = 1ms
#ifndef configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
	#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY ((1))
#endif
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - __NVIC_PRIO_BITS))
#define configTOTAL_HEAP_SIZE                 ( 0x4000 )
#define INCLUDE_xTaskGetCurrentTaskHandle 				1
#define INCLUDE_vTaskDelayUntil 									1
#define INCLUDE_vTaskDelay                        1
#define configUSE_MALLOC_FAILED_HOOK 							1


#define xPortSysTickHandler 	SysTick_Handler
#define xPortPendSVHandler    PendSV_Handler
#define vPortSVCHandler 			SVC_Handler



/*SVC_Handler,                                              
    DebugMon_Handler,                                         
    0,                                                        
    PendSV_Handler,                                          
    SysTick_Handler,*/

#endif /* FREERTOS_CONFIG_H */
#include "bsp_gpt_timing.h"
#include "bsp_adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
extern QueueHandle_t xQueue;
/* GPT初始化函数 */
void GPT_Timing_Init(void)
{
    /* 初始化 GPT0 模块 */
    R_GPT_Open(&g_timer_gpt0_ctrl, &g_timer_gpt0_cfg);
    
    /* 启动 GPT0 定时器 */
    R_GPT_Start(&g_timer_gpt0_ctrl);
}


/* 定时器溢出 中断回调函数 */
void gpt0_timing_callback(timer_callback_args_t * p_args)
{
		double tmp ;
    if (TIMER_EVENT_CYCLE_END == p_args->event)
    {
			tmp = adc_read();
			xQueueSendToBack( xQueue, &tmp, 0 );
    }
}
 


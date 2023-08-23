#include "Pwm_Task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_gpt_pwm_output.h"
#include "bsp_gpt_input_capture.h"
#include "semphr.h"
#include "stdio.h"
#include "bsp_led.h"
#include "Wdt_Task.h"
extern SemaphoreHandle_t xSemaphore;
// 外部变量声明
extern timer_info_t info; //用于获取定时器参数信息
extern uint32_t pwm_period; //PWM 周期
extern uint32_t pwm_high_level_time; //PWM 高电平的时间
extern uint32_t pwm_freq; //PWM 频率
extern uint32_t pwm_duty; //PWM 占空比

void vPwm_Task( void *pvParameters )
{
	FSP_PARAMETER_NOT_USED(pvParameters);
	TickType_t tick;
	GPT_PWM_Init(); // GPT PWM 输出初始化
	GPT_InputCapture_Init(); // GPT 输入捕获初始化
	tick = xTaskGetTickCount();
	while(1)
	{
		xTaskDelayUntil(&tick,pdMS_TO_TICKS(1000));
		xEventGroupSetBits(xEventGroup, TASK5);
		if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
		{
			/* 计算 PWM 的频率 */
			pwm_freq = info.clock_frequency / pwm_period;
			/* 计算 PWM 的占空比 */
			pwm_duty = pwm_high_level_time * 100 / pwm_period;
			// 打印
			printf("High=%d, Period=%d, ", pwm_high_level_time, pwm_period);
			printf("Friquency = %dHz, Duty_Cycle = %d%%\r\n", pwm_freq, pwm_duty);
			pwm_period = pwm_high_level_time = pwm_freq = 0; //打印完后旧数据清零
			LED1_TOGGLE;
			// 间隔 1s
			xSemaphoreGive(xSemaphore);
		}
		
		
	}
	
}
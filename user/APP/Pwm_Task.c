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
// �ⲿ��������
extern timer_info_t info; //���ڻ�ȡ��ʱ��������Ϣ
extern uint32_t pwm_period; //PWM ����
extern uint32_t pwm_high_level_time; //PWM �ߵ�ƽ��ʱ��
extern uint32_t pwm_freq; //PWM Ƶ��
extern uint32_t pwm_duty; //PWM ռ�ձ�

void vPwm_Task( void *pvParameters )
{
	FSP_PARAMETER_NOT_USED(pvParameters);
	TickType_t tick;
	GPT_PWM_Init(); // GPT PWM �����ʼ��
	GPT_InputCapture_Init(); // GPT ���벶���ʼ��
	tick = xTaskGetTickCount();
	while(1)
	{
		xTaskDelayUntil(&tick,pdMS_TO_TICKS(1000));
		xEventGroupSetBits(xEventGroup, TASK5);
		if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
		{
			/* ���� PWM ��Ƶ�� */
			pwm_freq = info.clock_frequency / pwm_period;
			/* ���� PWM ��ռ�ձ� */
			pwm_duty = pwm_high_level_time * 100 / pwm_period;
			// ��ӡ
			printf("High=%d, Period=%d, ", pwm_high_level_time, pwm_period);
			printf("Friquency = %dHz, Duty_Cycle = %d%%\r\n", pwm_freq, pwm_duty);
			pwm_period = pwm_high_level_time = pwm_freq = 0; //��ӡ������������
			LED1_TOGGLE;
			// ��� 1s
			xSemaphoreGive(xSemaphore);
		}
		
		
	}
	
}
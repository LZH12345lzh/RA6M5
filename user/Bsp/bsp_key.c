#include "bsp_key.h"
#include "bsp_led.h"

/* 读键值 */
uint32_t R_key_read(bsp_io_port_pin_t key)
{
	bsp_io_level_t state;
	R_IOPORT_PinRead(&g_ioport_ctrl, key, &state);
	return state;
}
/*
* 按键扫描函数判断你的手是否松开
*/
uint32_t Key_Scan(bsp_io_port_pin_t key)
{
	if(R_key_read(key) == BSP_IO_LEVEL_HIGH)
	{
		return KEY_OFF;
	}
	else
	{
		do //等待按键释放
		{
			R_key_read(key);
		} while (BSP_IO_LEVEL_LOW == R_key_read(key));
		return KEY_ON;
	}
	return KEY_ON;
}

//void sw2_callback(external_irq_callback_args_t *p_args)
//{
//	(void) p_args;
//	LED1_ON; //宏定义 LED 开
//	LED2_ON;
//	LED3_ON;
//}

//void sw3_callback(external_irq_callback_args_t *p_args)
//{
//	(void) p_args;
//	LED1_OFF; //宏定义 LED 开
//	LED2_OFF;
//	LED3_OFF;
//}

/* IRQ 初始化函数 */
//void IRQ_Init(void)
//{
//	/* 初始化外部中断 */
//	R_ICU_ExternalIrqOpen(sw2.p_ctrl,sw2.p_cfg);
//	R_ICU_ExternalIrqEnable(sw2.p_ctrl);
//	R_ICU_ExternalIrqOpen(sw3.p_ctrl, sw3.p_cfg);
//	R_ICU_ExternalIrqEnable(sw3.p_ctrl);
//}





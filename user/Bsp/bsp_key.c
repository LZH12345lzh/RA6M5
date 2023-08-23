#include "bsp_key.h"
#include "bsp_led.h"

/* ����ֵ */
uint32_t R_key_read(bsp_io_port_pin_t key)
{
	bsp_io_level_t state;
	R_IOPORT_PinRead(&g_ioport_ctrl, key, &state);
	return state;
}
/*
* ����ɨ�躯���ж�������Ƿ��ɿ�
*/
uint32_t Key_Scan(bsp_io_port_pin_t key)
{
	if(R_key_read(key) == BSP_IO_LEVEL_HIGH)
	{
		return KEY_OFF;
	}
	else
	{
		do //�ȴ������ͷ�
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
//	LED1_ON; //�궨�� LED ��
//	LED2_ON;
//	LED3_ON;
//}

//void sw3_callback(external_irq_callback_args_t *p_args)
//{
//	(void) p_args;
//	LED1_OFF; //�궨�� LED ��
//	LED2_OFF;
//	LED3_OFF;
//}

/* IRQ ��ʼ������ */
//void IRQ_Init(void)
//{
//	/* ��ʼ���ⲿ�ж� */
//	R_ICU_ExternalIrqOpen(sw2.p_ctrl,sw2.p_cfg);
//	R_ICU_ExternalIrqEnable(sw2.p_ctrl);
//	R_ICU_ExternalIrqOpen(sw3.p_ctrl, sw3.p_cfg);
//	R_ICU_ExternalIrqEnable(sw3.p_ctrl);
//}





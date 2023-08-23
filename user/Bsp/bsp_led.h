#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "hal_data.h"

#define LED1_ON 	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_LOW); //LED1 ��				
#define LED2_ON 	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_03, BSP_IO_LEVEL_LOW); //LED2 ��
#define LED3_ON 	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_04, BSP_IO_LEVEL_LOW); //LED3 ��

#define LED1_OFF 	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_HIGH); //LED1 ��				
#define LED2_OFF	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_03, BSP_IO_LEVEL_HIGH); //LED2 ��
#define LED3_OFF	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_04, BSP_IO_LEVEL_HIGH); //LED3 ��

#define LED1_TOGGLE R_PORT4->PODR ^= 1<<(BSP_IO_PORT_04_PIN_00 & 0xFF)
#define LED2_TOGGLE R_PORT4->PODR ^= 1<<(BSP_IO_PORT_04_PIN_03 & 0xFF)
#define LED3_TOGGLE R_PORT4->PODR ^= 1<<(BSP_IO_PORT_04_PIN_04 & 0xFF)

/* LED ��ʼ������ */
void LED_Init(void);


#endif


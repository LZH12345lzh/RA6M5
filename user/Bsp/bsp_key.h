#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "hal_data.h"

#define KEY_ON  	           1				
#define KEY_OFF 	           0
#define KEY_SW2_PIN     		 BSP_IO_PORT_00_PIN_04   
#define KEY_SW3_PIN					 BSP_IO_PORT_00_PIN_05


uint32_t R_key_read(bsp_io_port_pin_t key);
uint32_t Key_Scan(bsp_io_port_pin_t key);

//void sw2_callback(external_irq_callback_args_t *p_args);
//void sw3_callback(external_irq_callback_args_t *p_args);
//void IRQ_Init(void);
#endif


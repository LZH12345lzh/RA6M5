#ifndef __FATFSTASK_H
#define __FATFSTASK_H
#include "hal_data.h"
#include "ff.h"



#define LED_RED_IO_PIN    BSP_IO_PORT_04_PIN_00
#define LED_GREEN_IO_PIN  BSP_IO_PORT_04_PIN_03
#define LED_BLUE_IO_PIN   BSP_IO_PORT_04_PIN_04

#define LED_RED_ON()      R_IOPORT_PinWrite(&g_ioport_ctrl, LED_RED_IO_PIN, BSP_IO_LEVEL_LOW)
#define LED_GREEN_ON()    R_IOPORT_PinWrite(&g_ioport_ctrl, LED_GREEN_IO_PIN, BSP_IO_LEVEL_LOW)
#define LED_BLUE_ON()     R_IOPORT_PinWrite(&g_ioport_ctrl, LED_BLUE_IO_PIN, BSP_IO_LEVEL_LOW)

#define LED_RED_OFF()     R_IOPORT_PinWrite(&g_ioport_ctrl, LED_RED_IO_PIN, BSP_IO_LEVEL_HIGH)
#define LED_GREEN_OFF()   R_IOPORT_PinWrite(&g_ioport_ctrl, LED_GREEN_IO_PIN, BSP_IO_LEVEL_HIGH)
#define LED_BLUE_OFF()    R_IOPORT_PinWrite(&g_ioport_ctrl, LED_BLUE_IO_PIN, BSP_IO_LEVEL_HIGH)




void vFatfs_Task( void *pvParameters );


#endif
#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H
#include "hal_data.h"

typedef enum
{
    SYS_DELAY_UNITS_SECONDS      = 200000000, ///< Requested delay amount is in seconds
    SYS_DELAY_UNITS_MILLISECONDS = 200000,    ///< Requested delay amount is in milliseconds
    SYS_DELAY_UNITS_MICROSECONDS = 200        ///< Requested delay amount is in microseconds
} sys_delay_units_t;

void SysTick_Init(uint32_t IT_frequency);
void SysTick_Delay(uint32_t delay, sys_delay_units_t unit);

#endif
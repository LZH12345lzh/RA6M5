#include "bsp_SysTick.h"



static __IO uint32_t IT_nums;  //延时需要触发中断的次数
static uint32_t IT_Period;  //中断周期(单位为时钟节拍数)
/**
 * @brief  启动系统滴答计时器 SysTick
 * @param  IT_frequency: 滴答计时器每秒的中断次数
 * @retval 无
 */
void SysTick_Init(uint32_t IT_frequency)
{
    /* SystemFrequency在这里默认为200M
     * SystemFrequency / 1000    1ms中断一次
     * SystemFrequency / 100000  10us中断一次
     * SystemFrequency / 1000000 1us中断一次
     */
    IT_Period = SystemCoreClock / IT_frequency;
    uint32_t err = SysTick_Config (IT_Period);
    assert(err==0); //capture error
}

/**
 * @brief  延时程序
 * @param  delay: 延时的单位时间
 * @param  unit: 延时的单位
 * @retval 无
 */

void SysTick_Delay(uint32_t delay, sys_delay_units_t unit)  //用FreeRTOS的延时函数代替，该延时函数就是依据系统时钟来配置的 根据arm-cm33内核函数计算的
{
    uint32_t SumTime = delay * unit; //计算总延时时间(单位为时钟节拍数)
    IT_nums = SumTime/IT_Period;     //计算进入中断的次数
    while (IT_nums != 0);
}

/**
  * @brief  SysTick的中断服务函数
  * @param  无
  * @retval 无
  * @attention 用e2 studio编译会出现警告，但是没有影响，不需要管
  */

//裸机情况下使用该文件函数
//在有FreeRTOS下，即使配置了系统定时器的中断时间也不会触发，因为会被任务调度器里面重新赋值，在FreeRTOSConfig中有配置频率了
//void SysTick_Handler(void)
//{
//    if (IT_nums != 0x00)
//    {
//        IT_nums--;
//    }
//}



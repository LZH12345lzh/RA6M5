#include "bsp_SysTick.h"



static __IO uint32_t IT_nums;  //��ʱ��Ҫ�����жϵĴ���
static uint32_t IT_Period;  //�ж�����(��λΪʱ�ӽ�����)
/**
 * @brief  ����ϵͳ�δ��ʱ�� SysTick
 * @param  IT_frequency: �δ��ʱ��ÿ����жϴ���
 * @retval ��
 */
void SysTick_Init(uint32_t IT_frequency)
{
    /* SystemFrequency������Ĭ��Ϊ200M
     * SystemFrequency / 1000    1ms�ж�һ��
     * SystemFrequency / 100000  10us�ж�һ��
     * SystemFrequency / 1000000 1us�ж�һ��
     */
    IT_Period = SystemCoreClock / IT_frequency;
    uint32_t err = SysTick_Config (IT_Period);
    assert(err==0); //capture error
}

/**
 * @brief  ��ʱ����
 * @param  delay: ��ʱ�ĵ�λʱ��
 * @param  unit: ��ʱ�ĵ�λ
 * @retval ��
 */

void SysTick_Delay(uint32_t delay, sys_delay_units_t unit)  //��FreeRTOS����ʱ�������棬����ʱ������������ϵͳʱ�������õ� ����arm-cm33�ں˺��������
{
    uint32_t SumTime = delay * unit; //��������ʱʱ��(��λΪʱ�ӽ�����)
    IT_nums = SumTime/IT_Period;     //��������жϵĴ���
    while (IT_nums != 0);
}

/**
  * @brief  SysTick���жϷ�����
  * @param  ��
  * @retval ��
  * @attention ��e2 studio�������־��棬����û��Ӱ�죬����Ҫ��
  */

//��������ʹ�ø��ļ�����
//����FreeRTOS�£���ʹ������ϵͳ��ʱ�����ж�ʱ��Ҳ���ᴥ������Ϊ�ᱻ����������������¸�ֵ����FreeRTOSConfig��������Ƶ����
//void SysTick_Handler(void)
//{
//    if (IT_nums != 0x00)
//    {
//        IT_nums--;
//    }
//}



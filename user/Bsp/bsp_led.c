#include "bsp_led.h"


/* LED ��ʼ������ */
void LED_Init(void)
{
	/* ��ʼ���������ţ������ظ���ʼ���ˣ�����ע�͵��� */
	R_IOPORT_Open (&g_ioport_ctrl, g_ioport.p_cfg);
}

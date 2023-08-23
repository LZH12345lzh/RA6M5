/***********************************************************************
*
* FILE : qe_sample_main.c
* DATE : 2022-02-14
* DESCRIPTION : Main Program for RA
*
* NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "qe_touch_config.h"
#include "qe_touch_sample.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"
#define TOUCH_SCAN_INTERVAL_EXAMPLE (20)    /* milliseconds */

void qe_touch_main(void *pvParameters);


uint64_t button_status;
#if (TOUCH_CFG_NUM_SLIDERS != 0)
    uint16_t slider_position[TOUCH_CFG_NUM_SLIDERS];
#endif
#if (TOUCH_CFG_NUM_WHEELS != 0)
    uint16_t wheel_position[TOUCH_CFG_NUM_WHEELS];
#endif






void qe_touch_main(void *pvParameters)
{
    fsp_err_t err;
    //touch_button_cfg_t
    err = R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    /* Open Touch middleware */
    err = RM_TOUCH_Open(g_qe_touch_instance_config01.p_ctrl, g_qe_touch_instance_config01.p_cfg);
		
		uint8_t flag;
		BaseType_t xResult = pdFAIL;
    if (FSP_SUCCESS != err)
    {
        while (true) {}
    }

    /* Main loop */
    while (1)
    {
        /* for [CONFIG01] configuration */
				RM_TOUCH_ScanStart(g_qe_touch_instance_config01.p_ctrl);
				xResult = xTaskNotifyWait(0,0,&flag,portMAX_DELAY);
				if(xResult == pdPASS)
				{
					if ( 1 == flag )
					{
						err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &button_status, NULL, NULL);        // scan the key data,save to button_status
						if (FSP_SUCCESS == err)
						{
								if (button_status == 1)
								{
									LED1_TOGGLE;
									LED2_TOGGLE;
									LED3_TOGGLE;
								}
						}
					}
				}

    }
}

/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_iwdt.h"
            #include "r_wdt_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_dac.h"
#include "r_dac_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
#include "r_dmac.h"
#include "r_transfer_api.h"
#include "r_sdhi.h"
#include "r_sdmmc_api.h"
#include "r_qspi.h"
            #include "r_spi_flash_api.h"
#include "r_iic_master.h"
#include "r_i2c_master_api.h"
#include "r_sci_uart.h"
            #include "r_uart_api.h"
FSP_HEADER
/** WDT on IWDT Instance. */
extern const wdt_instance_t g_iwdt0;


/** Access the IWDT instance using these structures when calling API functions directly (::p_api is not used). */
extern iwdt_instance_ctrl_t g_iwdt0_ctrl;
extern const wdt_cfg_t g_iwdt0_cfg;

#ifndef iwdt_callback
void iwdt_callback(wdt_callback_args_t * p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_gpt7;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer_gpt7_ctrl;
extern const timer_cfg_t g_timer_gpt7_cfg;

#ifndef gpt7_input_capture_callback
void gpt7_input_capture_callback(timer_callback_args_t * p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_gpt6;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer_gpt6_ctrl;
extern const timer_cfg_t g_timer_gpt6_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_gpt0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer_gpt0_ctrl;
extern const timer_cfg_t g_timer_gpt0_cfg;

#ifndef gpt0_timing_callback
void gpt0_timing_callback(timer_callback_args_t * p_args);
#endif
/** DAC on DAC Instance. */
extern const dac_instance_t DAC;

/** Access the DAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dac_instance_ctrl_t DAC_ctrl;
extern const dac_cfg_t DAC_cfg;
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;

/** Access the ADC instance using these structures when calling API functions directly (::p_api is not used). */
extern adc_instance_ctrl_t g_adc0_ctrl;
extern const adc_cfg_t g_adc0_cfg;
extern const adc_channel_cfg_t g_adc0_channel_cfg;

#ifndef adc_callback
void adc_callback(adc_callback_args_t * p_args);
#endif

#ifndef NULL
#define ADC_DMAC_CHANNELS_PER_BLOCK_NULL  1
#endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_transfer0;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_transfer0_ctrl;
extern const transfer_cfg_t g_transfer0_cfg;

#ifndef g_sdmmc0_dmac_callback
void g_sdmmc0_dmac_callback(dmac_callback_args_t * p_args);
#endif
/** SDMMC on SDMMC Instance. */
extern const sdmmc_instance_t g_sdmmc0;


/** Access the SDMMC instance using these structures when calling API functions directly (::p_api is not used). */
extern sdhi_instance_ctrl_t g_sdmmc0_ctrl;
extern sdmmc_cfg_t g_sdmmc0_cfg;

#ifndef g_sdmmc0_callback
void g_sdmmc0_callback(sdmmc_callback_args_t * p_args);
#endif
extern const spi_flash_instance_t Flash;
            extern qspi_instance_ctrl_t Flash_ctrl;
            extern const spi_flash_cfg_t Flash_cfg;
/* I2C Master on IIC Instance. */
extern const i2c_master_instance_t EEPROM;

/** Access the I2C Master instance using these structures when calling API functions directly (::p_api is not used). */
extern iic_master_instance_ctrl_t EEPROM_ctrl;
extern const i2c_master_cfg_t EEPROM_cfg;

#ifndef i2c_callback
void i2c_callback(i2c_master_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      debug_uart4;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     debug_uart4_ctrl;
            extern const uart_cfg_t debug_uart4_cfg;
            extern const sci_uart_extended_cfg_t debug_uart4_cfg_extend;

            #ifndef debug_uart4_callback
            void debug_uart4_callback(uart_callback_args_t * p_args);
            #endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */

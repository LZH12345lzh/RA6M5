/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_uart_rxi_isr, /* SCI4 RXI (Received data full) */
            [1] = sci_uart_txi_isr, /* SCI4 TXI (Transmit data empty) */
            [2] = sci_uart_tei_isr, /* SCI4 TEI (Transmit end) */
            [3] = sci_uart_eri_isr, /* SCI4 ERI (Receive error) */
            [4] = iic_master_rxi_isr, /* IIC2 RXI (Receive data full) */
            [5] = iic_master_txi_isr, /* IIC2 TXI (Transmit data empty) */
            [6] = iic_master_tei_isr, /* IIC2 TEI (Transmit end) */
            [7] = iic_master_eri_isr, /* IIC2 ERI (Transfer error) */
            [8] = sdhimmc_accs_isr, /* SDHIMMC0 ACCS (Card access) */
            [9] = sdhimmc_card_isr, /* SDHIMMC0 CARD (Card detect) */
            [10] = dmac_int_isr, /* DMAC0 INT (DMAC transfer end 0) */
            [11] = adc_scan_end_isr, /* ADC0 SCAN END (A/D scan end interrupt) */
            [12] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [13] = gpt_counter_overflow_isr, /* GPT7 COUNTER OVERFLOW (Overflow) */
            [14] = gpt_capture_a_isr, /* GPT7 CAPTURE COMPARE A (Compare match A) */
            [15] = gpt_capture_b_isr, /* GPT7 CAPTURE COMPARE B (Compare match B) */
            [16] = ctsu_write_isr, /* CTSU WRITE (Write request interrupt) */
            [17] = ctsu_read_isr, /* CTSU READ (Measurement data transfer request interrupt) */
            [18] = ctsu_end_isr, /* CTSU END (Measurement end interrupt) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_SCI4_RXI), /* SCI4 RXI (Received data full) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_SCI4_TXI), /* SCI4 TXI (Transmit data empty) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_SCI4_TEI), /* SCI4 TEI (Transmit end) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_SCI4_ERI), /* SCI4 ERI (Receive error) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_IIC2_RXI), /* IIC2 RXI (Receive data full) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_IIC2_TXI), /* IIC2 TXI (Transmit data empty) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_IIC2_TEI), /* IIC2 TEI (Transmit end) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_IIC2_ERI), /* IIC2 ERI (Transfer error) */
            [8] = BSP_PRV_IELS_ENUM(EVENT_SDHIMMC0_ACCS), /* SDHIMMC0 ACCS (Card access) */
            [9] = BSP_PRV_IELS_ENUM(EVENT_SDHIMMC0_CARD), /* SDHIMMC0 CARD (Card detect) */
            [10] = BSP_PRV_IELS_ENUM(EVENT_DMAC0_INT), /* DMAC0 INT (DMAC transfer end 0) */
            [11] = BSP_PRV_IELS_ENUM(EVENT_ADC0_SCAN_END), /* ADC0 SCAN END (A/D scan end interrupt) */
            [12] = BSP_PRV_IELS_ENUM(EVENT_GPT0_COUNTER_OVERFLOW), /* GPT0 COUNTER OVERFLOW (Overflow) */
            [13] = BSP_PRV_IELS_ENUM(EVENT_GPT7_COUNTER_OVERFLOW), /* GPT7 COUNTER OVERFLOW (Overflow) */
            [14] = BSP_PRV_IELS_ENUM(EVENT_GPT7_CAPTURE_COMPARE_A), /* GPT7 CAPTURE COMPARE A (Compare match A) */
            [15] = BSP_PRV_IELS_ENUM(EVENT_GPT7_CAPTURE_COMPARE_B), /* GPT7 CAPTURE COMPARE B (Compare match B) */
            [16] = BSP_PRV_IELS_ENUM(EVENT_CTSU_WRITE), /* CTSU WRITE (Write request interrupt) */
            [17] = BSP_PRV_IELS_ENUM(EVENT_CTSU_READ), /* CTSU READ (Measurement data transfer request interrupt) */
            [18] = BSP_PRV_IELS_ENUM(EVENT_CTSU_END), /* CTSU END (Measurement end interrupt) */
        };
        #endif
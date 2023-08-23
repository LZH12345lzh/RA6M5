/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
        #ifdef __cplusplus
        extern "C" {
        #endif
                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (19)
        #endif
        /* ISR prototypes */
        void sci_uart_rxi_isr(void);
        void sci_uart_txi_isr(void);
        void sci_uart_tei_isr(void);
        void sci_uart_eri_isr(void);
        void iic_master_rxi_isr(void);
        void iic_master_txi_isr(void);
        void iic_master_tei_isr(void);
        void iic_master_eri_isr(void);
        void sdhimmc_accs_isr(void);
        void sdhimmc_card_isr(void);
        void dmac_int_isr(void);
        void adc_scan_end_isr(void);
        void gpt_counter_overflow_isr(void);
        void gpt_capture_a_isr(void);
        void gpt_capture_b_isr(void);
        void ctsu_write_isr(void);
        void ctsu_read_isr(void);
        void ctsu_end_isr(void);

        /* Vector table allocations */
        #define VECTOR_NUMBER_SCI4_RXI ((IRQn_Type) 0) /* SCI4 RXI (Received data full) */
        #define SCI4_RXI_IRQn          ((IRQn_Type) 0) /* SCI4 RXI (Received data full) */
        #define VECTOR_NUMBER_SCI4_TXI ((IRQn_Type) 1) /* SCI4 TXI (Transmit data empty) */
        #define SCI4_TXI_IRQn          ((IRQn_Type) 1) /* SCI4 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI4_TEI ((IRQn_Type) 2) /* SCI4 TEI (Transmit end) */
        #define SCI4_TEI_IRQn          ((IRQn_Type) 2) /* SCI4 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI4_ERI ((IRQn_Type) 3) /* SCI4 ERI (Receive error) */
        #define SCI4_ERI_IRQn          ((IRQn_Type) 3) /* SCI4 ERI (Receive error) */
        #define VECTOR_NUMBER_IIC2_RXI ((IRQn_Type) 4) /* IIC2 RXI (Receive data full) */
        #define IIC2_RXI_IRQn          ((IRQn_Type) 4) /* IIC2 RXI (Receive data full) */
        #define VECTOR_NUMBER_IIC2_TXI ((IRQn_Type) 5) /* IIC2 TXI (Transmit data empty) */
        #define IIC2_TXI_IRQn          ((IRQn_Type) 5) /* IIC2 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_IIC2_TEI ((IRQn_Type) 6) /* IIC2 TEI (Transmit end) */
        #define IIC2_TEI_IRQn          ((IRQn_Type) 6) /* IIC2 TEI (Transmit end) */
        #define VECTOR_NUMBER_IIC2_ERI ((IRQn_Type) 7) /* IIC2 ERI (Transfer error) */
        #define IIC2_ERI_IRQn          ((IRQn_Type) 7) /* IIC2 ERI (Transfer error) */
        #define VECTOR_NUMBER_SDHIMMC0_ACCS ((IRQn_Type) 8) /* SDHIMMC0 ACCS (Card access) */
        #define SDHIMMC0_ACCS_IRQn          ((IRQn_Type) 8) /* SDHIMMC0 ACCS (Card access) */
        #define VECTOR_NUMBER_SDHIMMC0_CARD ((IRQn_Type) 9) /* SDHIMMC0 CARD (Card detect) */
        #define SDHIMMC0_CARD_IRQn          ((IRQn_Type) 9) /* SDHIMMC0 CARD (Card detect) */
        #define VECTOR_NUMBER_DMAC0_INT ((IRQn_Type) 10) /* DMAC0 INT (DMAC transfer end 0) */
        #define DMAC0_INT_IRQn          ((IRQn_Type) 10) /* DMAC0 INT (DMAC transfer end 0) */
        #define VECTOR_NUMBER_ADC0_SCAN_END ((IRQn_Type) 11) /* ADC0 SCAN END (A/D scan end interrupt) */
        #define ADC0_SCAN_END_IRQn          ((IRQn_Type) 11) /* ADC0 SCAN END (A/D scan end interrupt) */
        #define VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW ((IRQn_Type) 12) /* GPT0 COUNTER OVERFLOW (Overflow) */
        #define GPT0_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 12) /* GPT0 COUNTER OVERFLOW (Overflow) */
        #define VECTOR_NUMBER_GPT7_COUNTER_OVERFLOW ((IRQn_Type) 13) /* GPT7 COUNTER OVERFLOW (Overflow) */
        #define GPT7_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 13) /* GPT7 COUNTER OVERFLOW (Overflow) */
        #define VECTOR_NUMBER_GPT7_CAPTURE_COMPARE_A ((IRQn_Type) 14) /* GPT7 CAPTURE COMPARE A (Compare match A) */
        #define GPT7_CAPTURE_COMPARE_A_IRQn          ((IRQn_Type) 14) /* GPT7 CAPTURE COMPARE A (Compare match A) */
        #define VECTOR_NUMBER_GPT7_CAPTURE_COMPARE_B ((IRQn_Type) 15) /* GPT7 CAPTURE COMPARE B (Compare match B) */
        #define GPT7_CAPTURE_COMPARE_B_IRQn          ((IRQn_Type) 15) /* GPT7 CAPTURE COMPARE B (Compare match B) */
        #define VECTOR_NUMBER_CTSU_WRITE ((IRQn_Type) 16) /* CTSU WRITE (Write request interrupt) */
        #define CTSU_WRITE_IRQn          ((IRQn_Type) 16) /* CTSU WRITE (Write request interrupt) */
        #define VECTOR_NUMBER_CTSU_READ ((IRQn_Type) 17) /* CTSU READ (Measurement data transfer request interrupt) */
        #define CTSU_READ_IRQn          ((IRQn_Type) 17) /* CTSU READ (Measurement data transfer request interrupt) */
        #define VECTOR_NUMBER_CTSU_END ((IRQn_Type) 18) /* CTSU END (Measurement end interrupt) */
        #define CTSU_END_IRQn          ((IRQn_Type) 18) /* CTSU END (Measurement end interrupt) */
        #ifdef __cplusplus
        }
        #endif
        #endif /* VECTOR_DATA_H */
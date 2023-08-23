#include "hal_data.h"
#include "bsp_uart4.h"
#include "i2c_ee.h"

unsigned int timeout_ms = 500;

i2c_master_event_t g_i2c_callback_event;
static volatile bool iic_complete = false;



void i2c_callback (i2c_master_callback_args_t * p_args)
{
    g_i2c_callback_event = p_args->event;
}


/**
* @brief I2C EEPROM��ʼ��
* @param   ��
* @retval  ��
*/
void I2C_EE_Init()
{
    R_IIC_MASTER_Open(EEPROM.p_ctrl, &EEPROM_cfg);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
}


/**
* @brief �Ե��ֽڵķ�ʽ��I2C EEPROM��
* @param
*   @arg address:д��ַ
*   @arg byte:д������
* @retval  ��
*/
void I2C_EE_ByteWrite(unsigned char address, unsigned char byte)
{
    iic_complete = false;
    unsigned char send_buffer[2] = {};

    send_buffer[0] = address;
    send_buffer[1] = byte;
    R_IIC_MASTER_Write(&EEPROM_ctrl, &send_buffer[0], 2, false); //ÿ��д������ false ��������

    while ((I2C_MASTER_EVENT_TX_COMPLETE != g_i2c_callback_event) && timeout_ms)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MILLISECONDS);
        timeout_ms--;
    }
    timeout_ms = 500;
}


/**
* @brief   ���������е�������ҳд��ķ�ʽд��I2C EEPROM��
* @param
*   @arg ptr_write:������ָ��
*   @arg WriteAddr:д��ַ
*     @arg len:д�ĳ���
* @retval  ��
*/
void I2C_EE_Writepage(unsigned char* ptr_write , unsigned char WriteAddr,unsigned char len)      //ҳд��   page 0~31
{

    unsigned char send_buffer[9] = {};
    send_buffer[0] = WriteAddr;

    for(unsigned char i = 0;i<len;i++)
    {
        send_buffer[1+i] = *(ptr_write+i);
    }

    R_IIC_MASTER_Write(&EEPROM_ctrl, &send_buffer[0], len+1 , false);

    while ((I2C_MASTER_EVENT_TX_COMPLETE != g_i2c_callback_event) && timeout_ms)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MILLISECONDS);
        timeout_ms--;
    }
    timeout_ms = 500;

    I2C_EE_WaitState();
}


/**
* @brief   ���������е�����д��I2C EEPROM��
* @param
*   @arg pBuffer:������ָ��
*   @arg WriteAddr:д��ַ
*     @arg NumByteToWrite:д���ֽ���
* @retval  ��
*/
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint8_t WriteAddr,uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

    Addr = WriteAddr % EEPROM_PAGESIZE;
    count = EEPROM_PAGESIZE - Addr;
    NumOfPage =  (uint8_t)NumByteToWrite / EEPROM_PAGESIZE;
    NumOfSingle = (uint8_t)NumByteToWrite % EEPROM_PAGESIZE;

    /* If WriteAddr is I2C_PageSize aligned  */
    if (Addr == 0) {
        /* If NumByteToWrite < I2C_PageSize */
        if (NumOfPage == 0) {
            I2C_EE_Writepage(pBuffer, WriteAddr, NumOfSingle);
        }
        /* If NumByteToWrite > I2C_PageSize */
        else {
            while (NumOfPage--) {
                I2C_EE_Writepage(pBuffer, WriteAddr, EEPROM_PAGESIZE);
                WriteAddr +=  EEPROM_PAGESIZE;
                pBuffer += EEPROM_PAGESIZE;
            }

            if (NumOfSingle!=0) {
                I2C_EE_Writepage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
    /* If WriteAddr is not I2C_PageSize aligned  */
    else {
        /* If NumByteToWrite < I2C_PageSize */
        if (NumOfPage== 0) {
            I2C_EE_Writepage(pBuffer, WriteAddr, NumOfSingle);
        }
        /* If NumByteToWrite > I2C_PageSize */
        else {
            NumByteToWrite -= count;
            NumOfPage =  (uint8_t)NumByteToWrite / EEPROM_PAGESIZE;
            NumOfSingle = (uint8_t)NumByteToWrite % EEPROM_PAGESIZE;

            if (count != 0) {
                I2C_EE_Writepage(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;
            }

            while (NumOfPage--) {
                I2C_EE_Writepage(pBuffer, WriteAddr, EEPROM_PAGESIZE);
                WriteAddr +=  EEPROM_PAGESIZE;
                pBuffer += EEPROM_PAGESIZE;
            }
            if (NumOfSingle != 0) {
                I2C_EE_Writepage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}



/**
* @brief ��ȡI2C EEPROM����
* @param
*   @arg ptr_read:��ȡ������ָ��
*   @arg address:��ַ
*     @arg byte:��ȡ���ֽ���
* @retval  ��
*/
void I2C_EE_BufferRead(unsigned char* ptr_read,unsigned char address,unsigned char byte)
{

    unsigned char send_buffer[2] = {};
    unsigned char read_buffer[1] = {};

    send_buffer[0] = address;
    R_IIC_MASTER_Write(&EEPROM_ctrl, &send_buffer[0], 1, true);
    while ((I2C_MASTER_EVENT_TX_COMPLETE != g_i2c_callback_event) && timeout_ms)
    {
        R_BSP_SoftwareDelay(400U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
    }
    timeout_ms = 500;

    R_BSP_SoftwareDelay(250U, BSP_DELAY_UNITS_MICROSECONDS);

    R_IIC_MASTER_Read(&EEPROM_ctrl, ptr_read, byte, false);

}

/**
* @brief I2C EEPROM�������
*/
void I2C_EE_Writedrase()
{
    unsigned char I2c_Buf_Write[256] = {};
    for(int i = 0 ; i<256 ; i++)
    {
        I2c_Buf_Write[i] = 0xff;
    }
    I2C_EE_BufferWrite(I2c_Buf_Write, 0x00 , 256);
}


/**
* @brief EEPROM�ȴ�����д��ɹ�
*/
void I2C_EE_WaitState(void)
{
    while (timeout_ms)
    {
        R_BSP_SoftwareDelay(9U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
    }
    timeout_ms = 500;
}



/**
* @brief  I2C(AT24C02)��д����
* @param  ��
* @retval ��������1 ������������0
*/
uint8_t I2C_Test(void)
{
    uint16_t i;
    unsigned char DATA_Size = 30;
    unsigned char I2c_Buf_Write[33] = {};
    unsigned char I2c_Buf_Read[33] = {};

    //��I2c_Buf_Write��˳�����������д��EERPOM��
    printf("д������\r\n");
    for ( i=0; i<DATA_Size; i++ ) { //��仺��
        I2c_Buf_Write[i] =( unsigned char )i;
        printf("0x%02X ", I2c_Buf_Write[i]);
        if (i%16 == 15)
            printf("\n");
    }
    I2C_EE_BufferWrite( I2c_Buf_Write, 0x00 , DATA_Size);



    //��EEPROM��������˳�򱣳ֵ�I2c_Buf_Read��
    printf("\r\n����������\n");
    R_BSP_SoftwareDelay(10U, BSP_DELAY_UNITS_MILLISECONDS);
    I2C_EE_BufferRead(I2c_Buf_Read, 0x00 , DATA_Size);



    //��I2c_Buf_Read�е�����ͨ�����ڴ�ӡ
    R_BSP_SoftwareDelay(10U, BSP_DELAY_UNITS_MILLISECONDS);
    for (i=0; i<DATA_Size; i++) {
        if (I2c_Buf_Read[i] != I2c_Buf_Write[i]) {
            printf("0x%02X \n", I2c_Buf_Read[i]);
            printf("����:I2C EEPROMд������������ݲ�һ��\n");
            printf("%d\n",i);
            return 0;
        }
        printf("0x%02X ", I2c_Buf_Read[i]);
        if (i%16 == 15)
            printf("\n");

    }
    printf("\r\nI2C(AT24C02)��д���Գɹ�\n");
    return 1;
}

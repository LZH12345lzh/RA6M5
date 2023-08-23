#include "Fatfs_Task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"
#include "Wdt_Task.h"
extern SemaphoreHandle_t xSemaphore;

/*
    BYTE fmt;           * Format option (FM_FAT, FM_FAT32, FM_EXFAT and FM_SFD) *
    BYTE n_fat;         * Number of FATs *
    UINT align;         * Data area alignment (sector) *
    UINT n_root;        * Number of root directory entries *
    DWORD au_size;      * Cluster size (byte) *
 */
MKFS_PARM f_opt =
{
    .fmt = FM_FAT32,       //格式选项
    .n_fat = 0,     //FATs大小
    .align = 0,     //数据区域对齐（扇区）
    .n_root = 0,    //根目录条目数
    .au_size = 0,   //群集大小（字节）
};
FATFS fs;                         /* FatFs文件系统对象 */
FIL fnew;                         /* 文件对象 */
FRESULT res_sd;                   /* 文件操作结果 */
UINT fnum;                        /* 文件成功读写数量 */
BYTE ReadBuffer[1024] = {0};      /* 读缓冲区 */
BYTE WriteBuffer[] =              /* 写缓冲区*/
											"新建文件系统测试文件\r\n";
BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
void vFatfs_Task( void *pvParameters )
{
	
	FSP_PARAMETER_NOT_USED(pvParameters);
	LED_RED_OFF();
	LED_GREEN_OFF();
	LED_BLUE_OFF();
	uint8_t flag = 0;
	if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
	{
		printf("\r\n****** 这是一个FLASH 文件系统实验 ******\r\n");
		res_sd = f_mount(&fs, "1:", 1);
		/*----------------------- 格式化测试 ---------------------------*/
			/* 如果没有文件系统就格式化创建创建文件系统 */
			if (res_sd == FR_NO_FILESYSTEM)
			{
					printf("》FLASH还没有文件系统，即将进行格式化...\r\n");
					/* 格式化 */
					res_sd = f_mkfs("1:", NULL, work, sizeof(work));

					if (res_sd == FR_OK)
					{
							printf("》FLASH已成功格式化文件系统。\r\n");
							/* 格式化后，先取消挂载 */
							res_sd = f_mount(NULL, "1:", 1);
							/* 重新挂载   */
							res_sd = f_mount(&fs, "1:", 1);
							flag = 1;
					}
					else
					{
							LED_RED_ON();  //红灯亮
							printf("《《格式化失败。》》\r\n");
							flag = 0 ;
					}
					if(flag)
					{
						res_sd = f_setlabel("1:FATFS TEST");  //设置盘符的名称为“FATFS TEST”
						if (res_sd == FR_OK)
						{
								printf("》设置盘符的名称为“FATFS TEST”。\r\n");
						}
						else
						{
								LED_RED_ON();  //红灯亮
								printf("《《设置盘符的名称失败。》》\r\n");
								while (1);
						}
					}
			}
			else if (res_sd != FR_OK)
			{
					LED_RED_ON();  //红灯亮
					printf("！！FLASH挂载文件系统失败。(%d)\r\n", res_sd);
					printf("！！可能原因：FLASH初始化不成功。\r\n");
					flag = 0;
			}
			else
			{
					printf("》文件系统挂载成功，可以进行读写测试\r\n");
				 flag = 1;
			}

			/*----------------------- 文件系统测试：写测试 -----------------------------*/
			/* 打开文件，如果文件不存在则创建它 */
			if( flag )
			{
				flag = 0;
				printf("\r\n****** 即将进行文件写入测试... ******\r\n");
				// 创建新文件。如果该文件存在，则覆盖。  |
				// 可以写文件
				res_sd = f_open(&fnew, "1:FatFs读写测试文件.txt", FA_CREATE_ALWAYS | FA_WRITE);  //FatFs读写测试文件 FatFs_files
				if (res_sd == FR_OK)
				{
						printf("》打开/创建FatFs读写测试文件.txt文件成功，向文件写入数据。\r\n");
						/* 将指定存储区内容写入到文件内 */
						res_sd = f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);
						if (res_sd == FR_OK)
						{
								LED_GREEN_ON();  //绿灯亮
								printf("》文件写入成功，写入字节数据：%d\n", fnum);
								printf("》向文件写入的数据为：\r\n%s\r\n", WriteBuffer);
								flag = 1;
						}
						else
						{
								LED_RED_ON();  //红灯亮
								printf("！！文件写入失败：(%d)\n", res_sd);
								flag = 0;
						}
						/* 不再写，关闭文件 */
						f_close(&fnew);
				}
				else
				{
						LED_RED_ON();  //红灯亮
						printf("！！打开/创建文件失败。\r\n");
						flag = 0;
				}

				/*------------------- 文件系统测试：读测试 ------------------------------------*/
				if(flag)
				{
					printf("****** 即将进行文件读取测试... ******\r\n");
					res_sd = f_open(&fnew, "1:FatFs读写测试文件.txt", FA_OPEN_EXISTING | FA_READ);
					if (res_sd == FR_OK)
					{
							printf("》打开文件成功。\r\n");
							res_sd = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
							if (res_sd == FR_OK)
							{
									LED_BLUE_ON();  //蓝灯亮
									printf("》文件读取成功,读到字节数据：%d\r\n", fnum);
									printf("》读取得的文件数据为：\r\n%s \r\n", ReadBuffer);
									flag = 1;
							}
							else
							{
									LED_RED_ON();  //红灯亮
									printf("！！文件读取失败：(%d)\n", res_sd);
									flag = 0;
							}
					}
					else
					{
							LED_RED_ON();  //红灯亮
							printf("！！打开文件失败。\r\n");
							flag = 0;
					}
				}
				if( flag )
				{
					/* 不再读，关闭文件 */
					f_close(&fnew);

					/* 不再使用文件系统，取消挂载文件系统 */
					f_mount(NULL, "1:", 1);
				}

				/* 操作完成，停机 */
			}
			xSemaphoreGive(xSemaphore);
	}
    while (1)
    {
			xEventGroupSetBits(xEventGroup, TASK3);
			vTaskDelay(pdMS_TO_TICKS(1000));
    }
	
}






/*
	该文件用来debug使用，通过type-c连接电脑与开发板的usb转串口相连接
	用于调试
	重定向printf函数由该串口输出
*/
#include "bsp_uart4.h"
Circular_queue_t Circular_queue;

bool Queue_Init(Circular_queue_t *circular_queue)																  //初始化队列
{
	if( !circular_queue )
	{
		return false;
	}
	memset(circular_queue->data,0,DATA_LEN);
	circular_queue->head = 0;
	circular_queue->tail = 0;
	return true;
	
}
bool Queue_isEmpty(Circular_queue_t *circular_queue) 															//判断队列是否为空
{
	if( !circular_queue )
	{
		return false;
	}
	if((circular_queue->head) == (circular_queue->tail))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Queue_isFull(Circular_queue_t *circular_queue) 																//判断队列是否已满  当判断为满的时候tail指针指向的地址是没有数据的
{
	if( !circular_queue )
	{
		return false;
	}
	if((circular_queue->tail + 1) % DATA_LEN == circular_queue->head)
	{
		return true;
	}
	else
	{
		return false;
	}
}

uint16_t Queue_HadUse(Circular_queue_t *circular_queue)														//返回队列中数据的长度
{
	if( !circular_queue )
	{
		return false;
	}
	return (uint16_t)(circular_queue->tail - circular_queue->head + DATA_LEN) % DATA_LEN;  //向队列插入一个数据后，尾指针往下一格移动，代表再有数据的话填充在这里
	
}
uint16_t Queue_NoUse(Circular_queue_t *circular_queue) 														//返回未使用数据的长度
{
	if( !circular_queue )
	{
		return false;
	}
	 return (uint16_t)(DATA_LEN - ((circular_queue->tail - circular_queue->head + DATA_LEN) % DATA_LEN) -1); //保留一个Byte数据用来区分队列的满状态
}
bool Queue_Wirte(Circular_queue_t *circular_queue, uint8_t *string, uint16_t len)  //写数据
{
	if( !circular_queue )
	{
		return false;
	}
	if(Queue_NoUse(circular_queue)<len)
		return false;
	for(int i=0;i<len;i++)
	{
			circular_queue->data[circular_queue->tail]=string[i];
			circular_queue->tail = (uint16_t)(circular_queue->tail+1)%DATA_LEN; //防止越界
	}
	return true;
}
bool Queue_Read(Circular_queue_t *circular_queue, uint8_t *string, uint16_t len) 	//读数据
{
	if( !circular_queue )
	{
		return false;
	}
	if(Queue_HadUse(circular_queue)<len)
			return false;
	for(int i=0;i<len;i++)
	{
			string[i]=circular_queue->data[circular_queue->head];
			circular_queue->head = (uint16_t)(circular_queue->head+1)%DATA_LEN; //防止越界
	}
	return true;
}




/* 调试串口 UART4 初始化 */
void Debug_UART4_Init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    
    err = R_SCI_UART_Open (&debug_uart4_ctrl, &debug_uart4_cfg);
    assert(FSP_SUCCESS == err);
}

/* 发送完成标志 */
volatile bool uart_send_complete_flag = false;


/* 串口中断回调 */
void debug_uart4_callback (uart_callback_args_t * p_args)
{
		bool is_full = false;
    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
//            /* 把串口接收到的数据发送回去 */
//            R_SCI_UART_Write(&debug_uart4_ctrl, (uint8_t *)&(p_args->data), 1);
						/* 接收到数据后马上写入队列中 */
						is_full = Queue_Wirte(&Circular_queue, (uint8_t*) &p_args->data, 1);
						if( !is_full )
						{
							
						}
            break;
        }
        case UART_EVENT_TX_COMPLETE:
        {
            uart_send_complete_flag = true;
            break;
        }
        default:
            break;
    }
}


/* 重定向 printf 输出 */
#if defined __GNUC__ && !defined __clang__
int _write(int fd, char *pBuffer, int size); //防止编译警告
int _write(int fd, char *pBuffer, int size)
{
    (void)fd;
    R_SCI_UART_Write(&g_uart4_ctrl, (uint8_t *)pBuffer, (uint32_t)size);
    while(uart_send_complete_flag == false);
    uart_send_complete_flag = false;

    return size;
}
#else
int fputc(int ch, FILE *f)
{
    (void)f;
    R_SCI_UART_Write(&debug_uart4_ctrl, (uint8_t *)&ch, 1);
    while(uart_send_complete_flag == false);
    uart_send_complete_flag = false;

    return ch;
}
#endif
/*
	���ļ�����debugʹ�ã�ͨ��type-c���ӵ����뿪�����usbת����������
	���ڵ���
	�ض���printf�����ɸô������
*/
#include "bsp_uart4.h"
Circular_queue_t Circular_queue;

bool Queue_Init(Circular_queue_t *circular_queue)																  //��ʼ������
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
bool Queue_isEmpty(Circular_queue_t *circular_queue) 															//�ж϶����Ƿ�Ϊ��
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
bool Queue_isFull(Circular_queue_t *circular_queue) 																//�ж϶����Ƿ�����  ���ж�Ϊ����ʱ��tailָ��ָ��ĵ�ַ��û�����ݵ�
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

uint16_t Queue_HadUse(Circular_queue_t *circular_queue)														//���ض��������ݵĳ���
{
	if( !circular_queue )
	{
		return false;
	}
	return (uint16_t)(circular_queue->tail - circular_queue->head + DATA_LEN) % DATA_LEN;  //����в���һ�����ݺ�βָ������һ���ƶ��������������ݵĻ����������
	
}
uint16_t Queue_NoUse(Circular_queue_t *circular_queue) 														//����δʹ�����ݵĳ���
{
	if( !circular_queue )
	{
		return false;
	}
	 return (uint16_t)(DATA_LEN - ((circular_queue->tail - circular_queue->head + DATA_LEN) % DATA_LEN) -1); //����һ��Byte�����������ֶ��е���״̬
}
bool Queue_Wirte(Circular_queue_t *circular_queue, uint8_t *string, uint16_t len)  //д����
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
			circular_queue->tail = (uint16_t)(circular_queue->tail+1)%DATA_LEN; //��ֹԽ��
	}
	return true;
}
bool Queue_Read(Circular_queue_t *circular_queue, uint8_t *string, uint16_t len) 	//������
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
			circular_queue->head = (uint16_t)(circular_queue->head+1)%DATA_LEN; //��ֹԽ��
	}
	return true;
}




/* ���Դ��� UART4 ��ʼ�� */
void Debug_UART4_Init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    
    err = R_SCI_UART_Open (&debug_uart4_ctrl, &debug_uart4_cfg);
    assert(FSP_SUCCESS == err);
}

/* ������ɱ�־ */
volatile bool uart_send_complete_flag = false;


/* �����жϻص� */
void debug_uart4_callback (uart_callback_args_t * p_args)
{
		bool is_full = false;
    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
//            /* �Ѵ��ڽ��յ������ݷ��ͻ�ȥ */
//            R_SCI_UART_Write(&debug_uart4_ctrl, (uint8_t *)&(p_args->data), 1);
						/* ���յ����ݺ�����д������� */
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


/* �ض��� printf ��� */
#if defined __GNUC__ && !defined __clang__
int _write(int fd, char *pBuffer, int size); //��ֹ���뾯��
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
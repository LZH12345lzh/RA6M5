#ifndef __BSP_DEBUG_UART_H
#define	__BSP_DEBUG_UART_H
#include "hal_data.h"
#include "stdio.h"

#define DATA_LEN  300//���л��泤��
typedef struct{
	uint16_t head;						//ͷָ��   ����Ҫ�����λ��ȡ������
	uint16_t tail;						//βָ��   ����Ҫ�����λ�ò�������
	uint8_t data[DATA_LEN];   //��������
}Circular_queue_t;


extern Circular_queue_t Circular_queue;


bool Queue_Init(Circular_queue_t *circular_queue);																  //��ʼ������
bool Queue_isEmpty(Circular_queue_t *circular_queue); 															//�ж϶����Ƿ�Ϊ��
bool Queue_isFull(Circular_queue_t *circular_queue); 																//�ж϶����Ƿ�����
bool Queue_Wirte(Circular_queue_t *circular_queue, uint8_t *string, uint16_t len);  //д����
bool Queue_Read(Circular_queue_t *circular_queue, uint8_t *string, uint16_t len); 	//������
uint16_t Queue_HadUse(Circular_queue_t *circular_queue);														//���ض��������ݵĳ���
uint16_t Queue_NoUse(Circular_queue_t *circular_queue); 														//����δʹ�����ݵĳ���
void Debug_UART4_Init(void);


#endif

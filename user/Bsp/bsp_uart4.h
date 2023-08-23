#ifndef __BSP_DEBUG_UART_H
#define	__BSP_DEBUG_UART_H
#include "hal_data.h"
#include "stdio.h"

#define DATA_LEN  300//队列缓存长度
typedef struct{
	uint16_t head;						//头指针   代表要从这个位置取出数据
	uint16_t tail;						//尾指针   代表要从这个位置插入数据
	uint8_t data[DATA_LEN];   //队列数据
}Circular_queue_t;


extern Circular_queue_t Circular_queue;


bool Queue_Init(Circular_queue_t *circular_queue);																  //初始化队列
bool Queue_isEmpty(Circular_queue_t *circular_queue); 															//判断队列是否为空
bool Queue_isFull(Circular_queue_t *circular_queue); 																//判断队列是否已满
bool Queue_Wirte(Circular_queue_t *circular_queue, uint8_t *string, uint16_t len);  //写数据
bool Queue_Read(Circular_queue_t *circular_queue, uint8_t *string, uint16_t len); 	//读数据
uint16_t Queue_HadUse(Circular_queue_t *circular_queue);														//返回队列中数据的长度
uint16_t Queue_NoUse(Circular_queue_t *circular_queue); 														//返回未使用数据的长度
void Debug_UART4_Init(void);


#endif

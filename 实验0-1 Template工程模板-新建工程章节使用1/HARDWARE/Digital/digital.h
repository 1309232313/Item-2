#ifndef __Digital_H
#define __Digital_H	 
#include "sys.h"



#define DI1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//��ȡ����0
#define DI2	 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//��ȡ����2 


void DI_Init(void);//IO��ʼ��



#endif

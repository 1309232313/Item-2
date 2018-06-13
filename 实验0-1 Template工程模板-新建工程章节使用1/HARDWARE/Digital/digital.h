#ifndef __Digital_H
#define __Digital_H	 
#include "sys.h"



#define DI1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//读取按键0
#define DI2	 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//读取按键2 


void DI_Init(void);//IO初始化



#endif

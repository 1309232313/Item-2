#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY1 PBin(5)   	//PB5
//#define KEY2 PBin(10)	//PB10
//#define KEY3 PBin(11)	//PB11



#define OK  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define UP  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
#define SET  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2 
#define DOWN  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 

//#define SET		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键0
//#define UP		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//读取按键2 
//#define DOWN	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//读取按键1
//#define OK		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//读取按键1


 

#define UP_PRES 1	//KEY1按下
#define DOWN_PRES	2	//KEY2按下
#define SET_PRES	3	//KEY3按下
#define OK_PRES  4//读取按键1



void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif

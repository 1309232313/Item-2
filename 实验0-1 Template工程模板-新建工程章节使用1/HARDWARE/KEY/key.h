#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

/**
 * ��������
 * ������Ӧ����
 */
extern u8 SET_Sign;//SET����������Ӧ��־; 0,�ް���; 1,����.
extern u16 SET_LongPress; //SET���������ȴ�,����������
extern u8 UP_Sign;//UP����������Ӧ��־; 0,�ް���; 1,����.
extern u16 UP_LongPress;//UP���������ȴ�,�����������ټ�.
extern u8 DOWN_Sign;	//DOWN����������Ӧ��־; 0,�ް���; 1,����.
extern u16 DOWN_LongPress;//DOWN���������ȴ�,����������ֵ���ټ�.
extern u8 OK_Sign;//OK����������Ӧ��־�� 0���ް�����1�����¡�
extern u16 OK_LongPress;//OK���������ȴ�.


//#define KEY1 PBin(5)   	//PB5
//#define KEY2 PBin(10)	//PB10
//#define KEY3 PBin(11)	//PB11



#define OK  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0
#define UP  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����1
#define SET  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����2 
#define DOWN  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3(WK_UP) 

//#define SET		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����0
//#define UP		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ����2 
//#define DOWN	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ����1
//#define OK		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//��ȡ����1


 
#define SET_PRES	1	//KEY3����
#define UP_PRES 2	//KEY1����
#define DOWN_PRES	3	//KEY2����
#define OK_PRES  4//��ȡ����1



void KEY_Init(void);//IO��ʼ��
void KeyScan(void);//����ɨ�����,ÿ2msɨ��һ�ΰ���


u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif

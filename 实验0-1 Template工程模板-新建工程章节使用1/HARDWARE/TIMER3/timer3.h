#ifndef __TIMER3_H
#define __TIMER3_H
#include "sys.h"   


/**
 * ʱ�����
 */
extern u16 Timer_segment;//��ʱ������
extern u16 ExitTimed;//����ҳ���Զ��˳���ʱ��
extern u16 Err_time;//������ʱ��

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void); //TIM3�ж�
void ExitMenuTiming(void);//ҳ���Զ��˳���ʱ��


#endif

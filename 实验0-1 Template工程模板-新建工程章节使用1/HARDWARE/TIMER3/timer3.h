#ifndef __TIMER3_H
#define __TIMER3_H
#include "sys.h"   


/**
 * 时间变量
 */
extern u16 Timer_segment;//定时器计数
extern u16 ExitTimed;//各级页面自动退出的时间
extern u16 Err_time;//错误检测时间

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void); //TIM3中断
void ExitMenuTiming(void);//页面自动退出计时器


#endif

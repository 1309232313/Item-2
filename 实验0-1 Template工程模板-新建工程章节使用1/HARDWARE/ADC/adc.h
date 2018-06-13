#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"

#define ADC_samples 	1						//每通道采样50次
#define ADC_chs 		4						//2个通道


extern vu16 After_Filter[ADC_chs];		//用来存放求平均值之后的结果

void Adc_Init(void);
void Filter(void);
#endif

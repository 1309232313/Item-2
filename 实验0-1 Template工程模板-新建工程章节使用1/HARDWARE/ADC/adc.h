#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"

#define ADC_samples 	1						//ÿͨ������50��
#define ADC_chs 		4						//2��ͨ��


extern vu16 After_Filter[ADC_chs];		//���������ƽ��ֵ֮��Ľ��

void Adc_Init(void);
void Filter(void);
#endif

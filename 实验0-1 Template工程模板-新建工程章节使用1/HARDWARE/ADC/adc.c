#include "adc.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "delay.h"
#include "dma.h"

vu16 AD_Value[ADC_samples][ADC_chs];//用来存放ADC转换结果，也是DMA的目标地址
vu16 After_Filter[ADC_chs];		//用来存放求平均值之后的结果
float Value[ADC_chs];					//用来存放最终电压结果

//初始化ADC
void Adc_Init(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO,ENABLE);//使能ADC1通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置ADC分频因子6，72M/6=12，ADC最大时钟不能超过14M
	
	//PB0(ch=8),PB1(ch=9)配置为模拟量输入
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	//AD工作模式设置
	ADC_DeInit(ADC1);														//将外设ADC1的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode					= ADC_Mode_Independent;		//ADC工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode			= ENABLE;					//开启扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode	= ENABLE;					//开启连续转换模式
	ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;		//右对齐
	ADC_InitStructure.ADC_ExternalTrigConv 	 	= ADC_ExternalTrigConv_None;//不用外部触发。用软件触发
	ADC_InitStructure.ADC_NbrOfChannel 			= ADC_chs;					//顺序进行规则转换的ADC通道数目
	ADC_Init(ADC1, &ADC_InitStructure);										//初始化外设ADCx
//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
//ADC1，ADC通道X，规则采样顺序值为y,采样时间为239.5周期	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_71Cycles5);//通道8，规则采样顺序值为1，采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,2,ADC_SampleTime_71Cycles5);//通道9，规则采样顺序值为2，采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,3,ADC_SampleTime_71Cycles5);//通道14，规则采样顺序值为2，采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15,4,ADC_SampleTime_71Cycles5);//通道15，规则采样顺序值为2，采样时间为239.5周期
	
//开启ADC的DMA支持(要实现DMA功能，还需要独立配置DMA通道等参数)	***注意：如果今后还需要开启别的DMA，那么可以将此部分代码专门写在DMA.c中
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);						//使能ADC1
	
	ADC_ResetCalibration(ADC1);			//复位指定的ADC1的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));//获取ADC1复位校准寄存器的状态，若为设置状态，则等待
	
	ADC_StartCalibration(ADC1);			//开始指定的ADC1的校准
	while(ADC_GetCalibrationStatus(ADC1));//获取指定ADC1的校准程序，设置状态则等待
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//开启AD转换
}

///*求平均值*/
//void Filter(void)
//{
//	int i;
//	int sum = 0;
//	u8  count;
//	for (i=0;i<ADC_chs;i++)
//	{
//		for(count=0;count<ADC_samples;count++)
//		{
//			sum+=AD_Value[count][i];
//		}
//		After_Filter[i] = sum/ADC_samples;
//		sum = 0;
//	//将AD平均值变为电压并立即转换为对应的压力
//		for(i=0;i<ADC_chs;i++)
//		{
//			
//			Value[i]=22.5*((After_Filter[i]*3.3/4096)-1)+5;//将求到的结果电压扩大100倍方便求出小数
//			
//		}
//	}
//}

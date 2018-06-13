#include "dma.h"
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "adc.h"

DMA_InitTypeDef DMA_InitStructure;
u16 DMA1_MEM_LEN;//保存DMA每次数据传送的长度
/*DMA1的各通道配置
这里的传输形式是固定的，这点要根据不同情况来修改
从存储器->外设模式/8位数据宽度/存储器增量模式
DMA_CHx:DMA通道CHx
cpar:外设地址
cmar:数据传输量
*/
extern vu16 AD_Value[ADC_samples][ADC_chs];//用来存放ADC转换结果，也是DMA的目标地址
void DMA_Config(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//使能时钟
	DMA_DeInit(DMA1_Channel1);											//将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr	= (u32)&ADC1->DR;//DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr		= (u32)&AD_Value;//DMA内存基地址 
	
	DMA_InitStructure.DMA_DIR					= DMA_DIR_PeripheralSRC;//数据传输方向外设到内存
	DMA_InitStructure.DMA_BufferSize			= ADC_samples*ADC_chs; //DMA通道的缓存大小 
	
	DMA_InitStructure.DMA_PeripheralInc			= DMA_PeripheralInc_Disable;//外设地址不变
	DMA_InitStructure.DMA_MemoryInc				= DMA_MemoryInc_Enable;//内存地址递增
	
	DMA_InitStructure.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_HalfWord;//数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize		= DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	
	DMA_InitStructure.DMA_Mode					= DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority				= DMA_Priority_Medium; //DMA通道拥有中优先级
	DMA_InitStructure.DMA_M2M					= DMA_M2M_Disable;//非内存到内存传输
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);	//初始化DMA的通道
	DMA_Cmd(DMA1_Channel1,ENABLE);//启动DMA通道
}

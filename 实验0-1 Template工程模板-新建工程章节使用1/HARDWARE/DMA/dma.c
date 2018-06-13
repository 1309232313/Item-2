#include "dma.h"
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "adc.h"

DMA_InitTypeDef DMA_InitStructure;
u16 DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ���
/*DMA1�ĸ�ͨ������
����Ĵ�����ʽ�ǹ̶��ģ����Ҫ���ݲ�ͬ������޸�
�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
DMA_CHx:DMAͨ��CHx
cpar:�����ַ
cmar:���ݴ�����
*/
extern vu16 AD_Value[ADC_samples][ADC_chs];//�������ADCת�������Ҳ��DMA��Ŀ���ַ
void DMA_Config(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//ʹ��ʱ��
	DMA_DeInit(DMA1_Channel1);											//��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr	= (u32)&ADC1->DR;//DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr		= (u32)&AD_Value;//DMA�ڴ����ַ 
	
	DMA_InitStructure.DMA_DIR					= DMA_DIR_PeripheralSRC;//���ݴ��䷽�����赽�ڴ�
	DMA_InitStructure.DMA_BufferSize			= ADC_samples*ADC_chs; //DMAͨ���Ļ����С 
	
	DMA_InitStructure.DMA_PeripheralInc			= DMA_PeripheralInc_Disable;//�����ַ����
	DMA_InitStructure.DMA_MemoryInc				= DMA_MemoryInc_Enable;//�ڴ��ַ����
	
	DMA_InitStructure.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_HalfWord;//���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize		= DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	
	DMA_InitStructure.DMA_Mode					= DMA_Mode_Circular; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority				= DMA_Priority_Medium; //DMAͨ��ӵ�������ȼ�
	DMA_InitStructure.DMA_M2M					= DMA_M2M_Disable;//���ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);	//��ʼ��DMA��ͨ��
	DMA_Cmd(DMA1_Channel1,ENABLE);//����DMAͨ��
}

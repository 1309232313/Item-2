#include "stm32f10x.h"
#include "LCD_ZK.H"
#include "zk.h"
#include "delay.h"
#include "key.h"
#include "menu.h"
#include "timer3.h"
#include "usart.h"
#include "dma.h"
#include "adc.h"
#include "timer4.h"
void Rcc_FRE72_init(void);
void rcc_hsi_init(void);
void mco_init(void);

int main(void)
{	
	u16 i=0;
	rcc_hsi_init();
	delay_init();//��ʱ��ʼ��
	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
	KEY_Init();//������ʼ��
	TIM3_Int_Init(10-1,640-1);//��ʱ����ʼ��,1/[64M/(640*10)]=0.0001s => 0.1ms
	initial_lcd();//LCD��ʼ��
	DMA_Config();  
	Adc_Init();		  		//ADC��ʼ��
	TIM4_Time_Init();
	clear_screen();//����
	
//	display_GB2312_string(0,0,"�˵�:");
//	display_GB2312_string(2,2,"|");
//	display_GB2312_string(2,114,"|");
//	display_GB2312_string(2,6,"--------------");
//	display_GB2312_string(4,60,"100");
//	display_string_5x7(8,1,"������<!@#$%^&*()_");
//	display_string_5x7(6,110,"mA");
	while(1)
	{
//	
//		display_graphic_12x16(6,10,Triangle_Increase_White);
//		display_graphic_12x16(6,30,Triangle_Increase_Black);
//		display_graphic_12x16(6,50,Triangle_Decrease_White);
//		display_graphic_12x16(6,70,Triangle_Decrease_Black);
		LOGODisplay();
	}
}
void Rcc_FRE72_init(void)
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	while(!RCC_WaitForHSEStartUp());
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_PLLConfig(RCC_CFGR_PLLSRC_HSE,RCC_PLLMul_9);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); 
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08); 
}

void mco_init(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOA����ʱ��ʹ��
	
  //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM1_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���ù������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIO
   RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);

}
void rcc_hsi_init(void)
{
	

	RCC_DeInit();
 
  RCC_HSICmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
 
	  RCC_HCLKConfig(RCC_SYSCLK_Div1);   
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
	
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);     //     4*16 =64MHZ     
		FLASH->ACR |= 0x32;                           //FLASH 2delay ��ϵͳʱ�ӵ���48MHZʹ��
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  
	 while(RCC_GetSYSCLKSource() != 0x08);	//0X00 HSI 0X04HSE 0X08PLL

}

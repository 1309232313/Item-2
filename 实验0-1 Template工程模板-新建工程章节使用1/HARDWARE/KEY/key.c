#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "timer3.h"
#include "usart.h"
			
/**
 * 按键变量
 * 按键响应变量
 */
u8 SET_Sign=0;//SET按键立即响应标志; 0,无按键; 1,按下.
u16 SET_LongPress=0; //SET按键长按等待,用作解锁等
u8 UP_Sign=0;//UP按键立即响应标志; 0,无按键; 1,按下.
u16 UP_LongPress=0;//UP按键长按等待,用作长按快速加.
u8 DOWN_Sign=0;	//DOWN按键立即响应标志; 0,无按键; 1,按下.
u16 DOWN_LongPress=0;//DOWN按键长按等待,用作长按数值快速减.
u8 OK_Sign=0;//OK按键立即响应标志； 0，无按键；1，按下。
u16 OK_LongPress=0;//OK按键长按等待.
			
			
			
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}			
//按键初始化函数
//void KEY_Init(void) //IO初始化
//{ 
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTB

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4

//}

/**
 * 按键扫描变量有:
 * 响应标志位:SET_Sign、UP_Sign、DOWN_Sign、OK_Sign	//0,无按键; 1,按下
 * 长按等待位:SET_LongPress、UP_LongPress、DOWN_LongPress、OK_LongPress	//长按自加
 * SET和OK键位响应时间为4ms
 * UP和DOWN键响应时间为2ms
*/
void KeyScan(void)//按键扫描程序,每2ms扫描一次按键
{
	if((Timer_segment%20)==0)	//每2ms扫描一次按键,查询按键是否有被按下,并消抖.
	{
		if(SET==0)	//SET键位是否被按下,按键低电平有效.
		{
			if(Timer_segment%40==0)	//再次消抖,Timer_segment=40因为SET键有时需要反应迅速
			{
				if(SET==0)
				{
					SET_Sign=1;	//按键按下立即响应标志为1,用作快速的响应
					ExitTimed=0;//当有按键响应时页面退出计时器归零
					Err_time=1;
					SET_LongPress++;//按键长按等待时间,用作解锁等
				}else
				{
					SET_Sign=0;//关闭响应.
					SET_LongPress=0;//长按时间归零等待下次计时.
				}
			}
		}else//按键被松开是,重置所有标志量
		{
			SET_Sign=0;//关闭响应.
			SET_LongPress=0;//长按时间归零等待下次计时.
		}
		if(UP==0)	//UP键位是否被按下,按键为向上加.
		{
			if(Timer_segment%10==0)	//当进入手动控制压力时长按UP键时反应要迅速
			{
				if(UP==0)
				{
					UP_Sign=1;//按键按下立即响应标志位1.
					ExitTimed=0;//当有按键响应时页面退出计时器归零
					Err_time=1;
					UP_LongPress++;//按键长按时一直加,可用作长按响应前的等待时间
				}else//按键被松开是,重置所有标志量
				{
					UP_Sign=0;//关闭响应.
					UP_LongPress=0;//长按时间归零等待下次计时.
				}
			}
		}else//按键被松开是,重置所有标志量
		{
			UP_Sign=0;//关闭响应.
			UP_LongPress=0;//长按时间归零等待下次计时.
		}
		if(DOWN==1)//DOWN键位是否被按下,按键为向下减
		{
			if(Timer_segment%10==0)//长按时快速减
			{
				if(DOWN==1)
				{
					DOWN_Sign=1;//按键按下立即响应标志为1
					ExitTimed=0;//当有按键响应时页面退出计时器归零
					Err_time=1;
					DOWN_LongPress++;//按键长按时一直减,可用作长按响应前的等待时间
				}else//按键被松开是,重置所有标志量
				{
					DOWN_Sign=0;//关闭响应.
					DOWN_LongPress=0;//长按时间归零等待下次计时.
				}
			}
		}else//按键被松开是,重置所有标志量
		{
			DOWN_Sign=0;//关闭响应.
			DOWN_LongPress=0;//长按时间归零等待下次计时.
		}
		if(OK==0)//OK键位是否被按下,该键为确认键
		{
			if(Timer_segment%40==0)//消抖
			{
				if(OK==0)
				{
					OK_Sign=1;//按键按下立即响应标志为1
					ExitTimed=0;//当有按键响应时页面退出计时器归零
					Err_time=1;
					OK_LongPress++;//按键长按时间
				}else
				{
					OK_Sign=0;//关闭响应
					OK_LongPress=0;//长按时间归零等待下次计时
				}
			}
		}else
		{
			OK_Sign=0;//关闭响应
			OK_LongPress=0;//长按时间归零等待下次计时
		}
		Timer_segment+=1;//避免程序在0.1ms的时间内多次进入扫描
	}
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY1按下
//2，KEY2按下
//3，KEY3按下 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		
	if(key_up&&(SET_Sign==1||UP_Sign==1||DOWN_Sign==1||OK_Sign==1))
	{
		if(SET_LongPress==20||UP_LongPress==20||DOWN_LongPress==20||OK_LongPress==20)
			key_up=mode;
		if(SET_LongPress>=20){SET_LongPress=0;	return SET_PRES;}
		else if(UP_LongPress>=20){UP_LongPress=0;	return UP_PRES;}
		else if(DOWN_LongPress>=20){DOWN_LongPress=0;	return DOWN_PRES;}
		else if(OK_LongPress>=20){OK_LongPress=0;	return OK_PRES;}
	}else if(SET_Sign==0 && UP_Sign==0 && DOWN_Sign==0 && OK_Sign==0)key_up=1; 	    
 	return 0;// 无按键按下	
}

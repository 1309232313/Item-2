#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "timer3.h"
#include "usart.h"
			
/**
 * ��������
 * ������Ӧ����
 */
u8 SET_Sign=0;//SET����������Ӧ��־; 0,�ް���; 1,����.
u16 SET_LongPress=0; //SET���������ȴ�,����������
u8 UP_Sign=0;//UP����������Ӧ��־; 0,�ް���; 1,����.
u16 UP_LongPress=0;//UP���������ȴ�,�����������ټ�.
u8 DOWN_Sign=0;	//DOWN����������Ӧ��־; 0,�ް���; 1,����.
u16 DOWN_LongPress=0;//DOWN���������ȴ�,����������ֵ���ټ�.
u8 OK_Sign=0;//OK����������Ӧ��־�� 0���ް�����1�����¡�
u16 OK_LongPress=0;//OK���������ȴ�.
			
			
			
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}			
//������ʼ������
//void KEY_Init(void) //IO��ʼ��
//{ 
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTB

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

//}

/**
 * ����ɨ�������:
 * ��Ӧ��־λ:SET_Sign��UP_Sign��DOWN_Sign��OK_Sign	//0,�ް���; 1,����
 * �����ȴ�λ:SET_LongPress��UP_LongPress��DOWN_LongPress��OK_LongPress	//�����Լ�
 * SET��OK��λ��Ӧʱ��Ϊ4ms
 * UP��DOWN����Ӧʱ��Ϊ2ms
*/
void KeyScan(void)//����ɨ�����,ÿ2msɨ��һ�ΰ���
{
	if((Timer_segment%20)==0)	//ÿ2msɨ��һ�ΰ���,��ѯ�����Ƿ��б�����,������.
	{
		if(SET==0)	//SET��λ�Ƿ񱻰���,�����͵�ƽ��Ч.
		{
			if(Timer_segment%40==0)	//�ٴ�����,Timer_segment=40��ΪSET����ʱ��Ҫ��ӦѸ��
			{
				if(SET==0)
				{
					SET_Sign=1;	//��������������Ӧ��־Ϊ1,�������ٵ���Ӧ
					ExitTimed=0;//���а�����Ӧʱҳ���˳���ʱ������
					Err_time=1;
					SET_LongPress++;//���������ȴ�ʱ��,����������
				}else
				{
					SET_Sign=0;//�ر���Ӧ.
					SET_LongPress=0;//����ʱ�����ȴ��´μ�ʱ.
				}
			}
		}else//�������ɿ���,�������б�־��
		{
			SET_Sign=0;//�ر���Ӧ.
			SET_LongPress=0;//����ʱ�����ȴ��´μ�ʱ.
		}
		if(UP==0)	//UP��λ�Ƿ񱻰���,����Ϊ���ϼ�.
		{
			if(Timer_segment%10==0)	//�������ֶ�����ѹ��ʱ����UP��ʱ��ӦҪѸ��
			{
				if(UP==0)
				{
					UP_Sign=1;//��������������Ӧ��־λ1.
					ExitTimed=0;//���а�����Ӧʱҳ���˳���ʱ������
					Err_time=1;
					UP_LongPress++;//��������ʱһֱ��,������������Ӧǰ�ĵȴ�ʱ��
				}else//�������ɿ���,�������б�־��
				{
					UP_Sign=0;//�ر���Ӧ.
					UP_LongPress=0;//����ʱ�����ȴ��´μ�ʱ.
				}
			}
		}else//�������ɿ���,�������б�־��
		{
			UP_Sign=0;//�ر���Ӧ.
			UP_LongPress=0;//����ʱ�����ȴ��´μ�ʱ.
		}
		if(DOWN==1)//DOWN��λ�Ƿ񱻰���,����Ϊ���¼�
		{
			if(Timer_segment%10==0)//����ʱ���ټ�
			{
				if(DOWN==1)
				{
					DOWN_Sign=1;//��������������Ӧ��־Ϊ1
					ExitTimed=0;//���а�����Ӧʱҳ���˳���ʱ������
					Err_time=1;
					DOWN_LongPress++;//��������ʱһֱ��,������������Ӧǰ�ĵȴ�ʱ��
				}else//�������ɿ���,�������б�־��
				{
					DOWN_Sign=0;//�ر���Ӧ.
					DOWN_LongPress=0;//����ʱ�����ȴ��´μ�ʱ.
				}
			}
		}else//�������ɿ���,�������б�־��
		{
			DOWN_Sign=0;//�ر���Ӧ.
			DOWN_LongPress=0;//����ʱ�����ȴ��´μ�ʱ.
		}
		if(OK==0)//OK��λ�Ƿ񱻰���,�ü�Ϊȷ�ϼ�
		{
			if(Timer_segment%40==0)//����
			{
				if(OK==0)
				{
					OK_Sign=1;//��������������Ӧ��־Ϊ1
					ExitTimed=0;//���а�����Ӧʱҳ���˳���ʱ������
					Err_time=1;
					OK_LongPress++;//��������ʱ��
				}else
				{
					OK_Sign=0;//�ر���Ӧ
					OK_LongPress=0;//����ʱ�����ȴ��´μ�ʱ
				}
			}
		}else
		{
			OK_Sign=0;//�ر���Ӧ
			OK_LongPress=0;//����ʱ�����ȴ��´μ�ʱ
		}
		Timer_segment+=1;//���������0.1ms��ʱ���ڶ�ν���ɨ��
	}
}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY1����
//2��KEY2����
//3��KEY3���� 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		
	if(key_up&&(SET_Sign==1||UP_Sign==1||DOWN_Sign==1||OK_Sign==1))
	{
		if(SET_LongPress==20||UP_LongPress==20||DOWN_LongPress==20||OK_LongPress==20)
			key_up=mode;
		if(SET_LongPress>=20){SET_LongPress=0;	return SET_PRES;}
		else if(UP_LongPress>=20){UP_LongPress=0;	return UP_PRES;}
		else if(DOWN_LongPress>=20){DOWN_LongPress=0;	return DOWN_PRES;}
		else if(OK_LongPress>=20){OK_LongPress=0;	return OK_PRES;}
	}else if(SET_Sign==0 && UP_Sign==0 && DOWN_Sign==0 && OK_Sign==0)key_up=1; 	    
 	return 0;// �ް�������	
}

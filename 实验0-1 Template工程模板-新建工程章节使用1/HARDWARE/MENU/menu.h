#ifndef __MENU_H
#define __MENU_H	 
#include "sys.h"

#define NULL 0

#define MENU_MAX_ROW 3 // �˵������ʾ���� 

//����˵������� 
#define MENU_SUBMENU	101 // �����Ӳ˵��Ĳ˵��� 
#define MENU_PARAM		102 // ���������ִ�в������ã�   

#define Yes		1 // ���������ִ�в������ã�  
#define No		0 // ���������ִ�в������ã�  
//����˵�������Ҫ��ȫ�ֱ���
extern u8 item_index;//��ǰ�˵�������




/**
 * ʱ�����
 */
extern u16 Timer_segment;//��ʱ������
extern u16 ExitTimed;//����ҳ���Զ��˳���ʱ��
extern u16 Err_time;//������ʱ��
/**
 * ��������
 * ������Ӧ����
 */
extern u8 SET_Sign;//SET����������Ӧ��־; 0,�ް���; 1,����.
extern u16 SET_LongPress; //SET���������ȴ�,����������
extern u8 UP_Sign;//UP����������Ӧ��־; 0,�ް���; 1,����.
extern u16 UP_LongPress;//UP���������ȴ�,�����������ټ�.
extern u8 DOWN_Sign;	//DOWN����������Ӧ��־; 0,�ް���; 1,����.
extern u16 DOWN_LongPress;//DOWN���������ȴ�,����������ֵ���ټ�.
extern u8 OK_Sign;//OK����������Ӧ��־�� 0���ް�����1�����¡�
extern u16 OK_LongPress;//OK���������ȴ�.



typedef void (*MENU_FUN)(const char *);
/*************** 
 * �˵��ṹ 
 * һ������ȴ���һ���˵��������е�һ��Ԫ�ؾ���һ���˵������һ�������Ľṹ�壬 
 * �����еĵ�һ��Ԫ���е�numֵ����Ҫ����ʾ�����˵����ж��ٸ��˵�� 
 * 
 * uint8_t num �����˵������������ڵ�һ����������ȷ�Ĳ˵������� 
 * char* label �˵��ı� 
 * uint8_t type �������ͣ��ο��궨�� 
 * MENU_CALLBACK CallBack;  ָ�����ĺ���ָ�룬����Ҫִ�еľ��嶯������ 
 * mymenu* next ��һ���˵���ֻ���ڲ˵��ĵ�һ�����ã��������ÿգ�NULL������ 
 * mymenu* prev ��һ���˵���ͬ�� 
 **************/ 
struct MenuItem//�ṹ�����Ͷ���//����һ���˵� 
{ 
	uint8_t num;			//�����˵�����
	u8 Higher_Menu_Level;//�ϼ��˵���
	u8 Current_Menu_Level;//��ǰ�˵���
	char *title;			//���˵�����
	char *label;			//�˵����ı�
	uint8_t type;			//�ο��궨��
	MENU_FUN Fun;	//ָ�����ĺ���ָ��
	struct MenuItem *next;	//��һ���˵�
	struct MenuItem *prev;	//��һ���˵�
};

void DispCurrentMenu(void);//���Ƶ�ǰ�˵���
void DropOut(const char * Text);//����


void TIM3_IRQHandler(void); //TIM3�ж�
void ExitMenuTiming(void);//ҳ���Զ��˳���ʱ��
void KeyScan(void);//����ɨ�����,ÿ2msɨ��һ�ΰ���
u8 MenuOption(void);
void Initial(void);
void LOGODisplay(void);

#endif


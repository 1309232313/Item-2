#ifndef __MENU_H
#define __MENU_H	 
#include "sys.h"

#define NULL 0

#define MENU_MAX_ROW 3 // �˵������ʾ���� 

//����˵������� 
#define MENU_SUBMENU	11 // �����Ӳ˵��Ĳ˵��� 
#define MENU_PARAM		12 // ���������ִ�в������ã�   

#define	START					13 //	����	
#define	CLOSE					14 //	�ر�

//������Ӧ�Ķ�������
//p1
	#define	Form1			201	//P1.0���嶨λ����װ��ʽ:1,Form1
	#define	Form2			202	//P1.0���嶨λ����װ��ʽ:2,Form2
	#define	Form3			203	//P1.0���嶨λ����װ��ʽ:3,Form3
//P2
	#define CURRENT		201	//P2.01�ź���ʽ:1,������ʽ
	#define	VOLTAGE		202	//P2.02�ź���ʽ:2,��ѹ��ʽ
	#define	SWITCH		203	//P2.03�ź���ʽ:3,������
	#define	MIN_RGE		211	//P2.1 MIN_RGE �趨�����źŵ���Сֵ(Ԥ��Ϊ4mA)
	#define	MAX_PRG		221	//P2.2 MAX_PRG �趨�����źŵ����ֵ(Ԥ��Ϊ20mA)
	#define	POSITIVE	241	//P2.41 ACTION:�趨���������÷�ʽ
	#define	NEGATIVE	242	//P2.42 ACTION:�趨���ŷ����÷�ʽ
	#define	RAMP1			261	//P2.61 RAMP? ���Ϳ����ٶ�
	#define	RAMP2			271	//P2.71 RAMP? ���͹����ٶ�
//P6
	#define	MIN_VR		601	//P6.0 MIN_VR �ֶ����÷���ȫ��λ��
	#define	MAX_VR		611	//P6.1 MAX_VR �ֶ����÷���ȫ��λ��
	#define	ACTAUTOR	621	//P6.2 ACTAUTOR ѡ��ִ������ʽ
//P8
	#define	MIN_RGE8	801	//P8.0 MIN_RGE ��λ��ʼ�����ֵ��Ĭ��Ϊ4mA)
	#define	MAX_RGE8	811	//P8.1 MAX_RGE 100%��λ����ֵ��Ĭ��Ϊ20mA)
	#define	ACTION		821	//P8.2 ACTION ��λ��������ѡ��Ĭ��4mA ��Ӧ��λ 0%��

#define Yes		1 // ���������ִ�в������ã�  
#define No		0 // ���������ִ�в������ã�  
//����˵�������Ҫ��ȫ�ֱ���
extern u8 item_index;//��ǰ�˵�������






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
	u8 action;//�����������ݵĶ�������
	struct MenuItem *next;	//��һ���˵�
	struct MenuItem *prev;	//��һ���˵�
};

void DispCurrentMenu(void);//���Ƶ�ǰ�˵���
void DropOut(const char * Text);//����
void P2_SETPOINT_SignalSetting(u8 parameter);


u8 MenuOption(void);
void Initial(void);
void LOGODisplay(void);

#endif


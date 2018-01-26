#include "menu.h"
#include "LCD_ZK.H"
#include "zk.h"
#include "delay.h"
#include "key.h"
#include "timer3.h"
#include "usart.h"
/**
 * ʱ�����
 */
u16 Timer_segment=1;//��ʱ������
u16 ExitTimed=0;//����ҳ���Զ��˳���ʱ��
u16 Err_time=1;//������ʱ��
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



u8 Level=0;
/**
 * NULL		0
 * �˵������ʾ����: MENU_MAX_ROW	5
 * ����˵�������
 * 		MENU_SUBMENU	101		�����Ӳ˵��Ĳ˵��� 
 *   	MENU_PARAM		102		���������ִ�в������ã�
 */
/**
 * �˵��ṹ 
 * һ������ȴ���һ���˵��������е�һ��Ԫ�ؾ���һ���˵������һ�������Ľṹ�壬 
 * �����еĵ�һ��Ԫ���е�numֵ����Ҫ����ʾ�����˵����ж��ٸ��˵�� 
 * 
 * 		uint8_t num �����˵������������ڵ�һ����������ȷ�Ĳ˵������� 
 * 		char *title	���˵�����
 *   	char* label �˵��ı� 
 *    	uint8_t type �������ͣ��ο��궨�� 
 *     	MENU_CALLBACK CallBack;  ָ�����ĺ���ָ�룬����Ҫִ�еľ��嶯������ 
 *     	mymenu* next ��һ���˵���ֻ���ڲ˵��ĵ�һ�����ã��������ÿգ�NULL������ 
 *      mymenu* prev ��һ���˵���ͬ�� 
*/ 
//�ṹ������ 
struct MenuItem menu_main[9];//1���˵�,���˵�
//��2���˵�
struct MenuItem menu_P1_STANDARD[5];//����������
struct MenuItem menu_P2_SETPOINT[9];//�����ź���
struct MenuItem menu_P3_ACTUATOR[4];//ִ����������
struct MenuItem menu_P4_MESSAGES[6];//
struct MenuItem menu_P5_ALARMS[8];//����������
struct MenuItem menu_P6_MAN_ADJ[6];//�ֶ����� 
struct MenuItem menu_P7_PAR[12];//���Ʋ���
struct MenuItem menu_P8_ANLG_OUT[6];//ģ���ź����
//��3���˵�
//P1�˵�
	struct MenuItem menu_P1_0ACTUATOR[2];//P1.0 ACTUATOR,���嶨λ����װ��ʽ
//	struct MenuItem menu_P1_1AUTO_ADJ[2];//P1.1 AUTO_ADJ �����Զ���������
	struct MenuItem menu_P1_2TOL_BAND[2];//P1.2 TOL_BAND �趨ƫ���������
	struct MenuItem menu_P1_3TEST[2];//P1.3 TEST �����޸Ľ��
//	struct MenuItem menu_P1_4EXIT[2];//P1.4 EXIT �˳������в�����
//P2�˵�
	struct MenuItem menu_P2_0SignalSystem[3];//P2.0 �ź���ʽ 1.���� 2.��ѹ 3.������
	struct MenuItem menu_P2_1MIN_RGE[3];//P2.1 MIN_RGE �趨�����źŵ���Сֵ(Ԥ��Ϊ4mA)	,****��ȷ��
	struct MenuItem menu_P2_2MAX_PRG[3];//P2.2 MAX_PRG �趨�����źŵ����ֵ(Ԥ��Ϊ20mA)	,****��ȷ��
	struct MenuItem menu_P2_3CHARACT[3];//P2.3 CHARACT ѡ�������������	,****��ȷ��
	struct MenuItem menu_P2_4ACTION[3];//P2.4 ACTION �趨�����������÷�ʽ	,****��ȷ��
	struct MenuItem menu_P2_5SHUT_OFF[3];//P2.5 SHUT-OFF �趨���ſ�����ֵ	,****��ȷ��
	struct MenuItem menu_P2_6RAMP1[3];//P2.6 RAMP? ���Ϳ����ٶ�	,****��ȷ��
	struct MenuItem menu_P2_7RAMP2[3];//P2.7 RAMP? ���͹����ٶ�	,****��ȷ��
//	struct MenuItem menu_P2_8EXIT[3];//P2.8 EXIT �˳������в�����
//P3�˵�
	struct MenuItem menu_P3_0MIN_RGE[4];//P3.0 MIN_RGE ����������ʼ����(Ԥ��Ϊ0%)	,****��ȷ��
	struct MenuItem menu_P3_1MAX_RGE[4];//P3.1 MAX_RGE ����������ֹ����(Ԥ��Ϊ100%)	,****��ȷ��
	struct MenuItem menu_P3_2ZERO_POS[4];//P3.2 ZERO_POS ��ʼ�㷽������(Ԥ��Ϊȫ�ؼ���������ʱ�뷽��)	,****��ȷ��
//	struct MenuItem menu_P3_3EXIT[4];//P3.3 EXIT �˳������в�����
//P4�˵�
	struct MenuItem menu_P4_0TIME_OUT[6];//P4.0 TIME _OUT ��λ��ʱ	,****��ȷ��
	struct MenuItem menu_P4_1POS_SW1[6];//P4.1 POS_SW1 ��һλ���ź����õ�	,****��ȷ��
	struct MenuItem menu_P4_2POS_SW2[6];//P4.2 POS_SW2 �ڶ�λ���ź����õ�	,****��ȷ��
	struct MenuItem menu_P4_3SW1_ACTV[6];//P4.3 SW1_ACTV ���ڻ���ڵ�һλ���ź�ʱ��Ч
	struct MenuItem menu_P4_4SW2_ACTV[6];//P4.4 SW2_ACTV ���ڻ���ڵڶ�λ���ź�ʱ��Ч
//	struct MenuItem menu_P4_5EXIT[6];//P4.5 EXIT �˳������в�����
//P5�˵�
	struct MenuItem menu_P5_0LEACKAGE[2];//P5.0 LEACKAGE ����ִ��������й©����  	,1.ȷ��;2.ȡ��
	struct MenuItem menu_P5_1SP_RGE[2];//P5.1 SP_RGE ���������źų��ޱ���  	,1.ȷ��;2.ȡ��
	struct MenuItem menu_P5_2SENS_RGE[2];//P5.2 SENS_RGE �������Ư�Ʊ���  	,1.ȷ��;2.ȡ��
	struct MenuItem menu_P5_3CTRLER[2];//P5.3 CTRLER ����Զ�����Ʊ��л�����  	,1.ȷ��;2.ȡ��
	struct MenuItem menu_P5_4TIME_OUT[2];//P5.4 TIME-OUT ������λ��ʱ����  	,1.ȷ��;2.ȡ��
	struct MenuItem menu_P5_5STRK_CTR[2];//P5.5 STRK_CTR ���������г̳��ޱ���  	,1.ȷ��;2.ȡ��
	struct MenuItem menu_P5_6TRAVEL[2];//P5.6 TRAVEL �������г̳��ޱ���  	,1.ȷ��;2.ȡ��
	struct MenuItem menu_P5_7EXIT[2];//P5.7 EXIT �˳������в�����  	,1.ȷ��;2.ȡ��
//P6�˵�
	struct MenuItem menu_P6_0MIN_VR[2];//P6.0 MIN_VR �ֶ����÷���ȫ��λ��				,****��ȷ��
	struct MenuItem menu_P6_1MAX_VR[2];//P6.1 MAX_VR �ֶ����÷���ȫ��λ��				,****��ȷ��
	struct MenuItem menu_P6_2ACTAUTOR[6];//P6.2 ACTAUTOR ѡ��ִ������ʽ				,****��ȷ��
	struct MenuItem menu_P6_3SPRNG_Y2[6];//P6.3 SPRNG_Y2 �趨ִ���������쳤ʱ��λ����������ת����				,****��ȷ��
	struct MenuItem menu_P6_4ADJ_MODE[6];//P6.4 ADJ_MODE ѡ���Զ��������������Ŀ				,****��ȷ��
	struct MenuItem menu_P6_5EXIT[2];//P6.5 EXIT �˳������в�����
//P7�˵�
	struct MenuItem menu_P7_0KP1[2];//P7.0 KP�� �������ϵ������				,****��ȷ��
	struct MenuItem menu_P7_1KP2[2];//P7.1 KP�� �������ϵ������				,****��ȷ��
	struct MenuItem menu_P7_2TV1[2];//P7.2 TV�� �������ʱ�����				,****��ȷ��
	struct MenuItem menu_P7_3TV2[2];//P7.3 TV�� �������ʱ�����				,****��ȷ��
	struct MenuItem menu_P7_11EXIT[2];//P7.11 EXIT �˳������в�����
//P8�˵�
	struct MenuItem menu_P8_0MIN_RGE[2];//P8.0 MIN_RGE ��λ��ʼ�����ֵ��Ĭ��Ϊ4mA)				,****��ȷ��
	struct MenuItem menu_P8_1MAX_RGE[2];//P8.1 MAX_RGE 100%��λ����ֵ��Ĭ��Ϊ20mA)				,****��ȷ��
	struct MenuItem menu_P8_2ACTION[2];//P8.2 ACTION ��λ��������ѡ��Ĭ��4mA ��Ӧ��λ 0%��				,****��ȷ��
	struct MenuItem menu_P8_3ALARM[2];//				,****��ȷ��
	struct MenuItem menu_P8_4TEST[2];//				,****��ȷ��
	struct MenuItem menu_P8_5EXIT[2];//P8.5 EXIT �˳������в�����				,****��ȷ��

struct MenuItem ConfirmOrCancel[2];
//�ṹ���ʼ��//�˵�����,�����ｫÿһ���˵��Ĺ������ú�
struct MenuItem menu_main[9] = // ��1���˵�,���˵�
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�					�ο��궨��	 		����			��һ���˵�						��һ���˵�
			{9, 		0,				1,					"",				"1.STANDARD  ",	MENU_SUBMENU, NULL, 		menu_P1_STANDARD, 	NULL},//����������,
			{9, 		0,				2,					"",				"2.SETPOINT  ",	MENU_SUBMENU, NULL, 		menu_P2_SETPOINT, 	NULL},//�����ź���,
			{9, 		0,				3,					"",				"3.ACTUATOR  ",	MENU_SUBMENU, NULL, 		menu_P3_ACTUATOR,		NULL},//ִ����������,
			{9, 		0,				4,					"",				"4.MESSAGES  ",	MENU_SUBMENU, NULL, 		menu_P4_MESSAGES,		NULL},//P4._,
			{9, 		0,				5,					"",				"5.ALARMS    ", MENU_SUBMENU, NULL, 		menu_P5_ALARMS,			NULL},//����������
			{9, 		0,				6,					"",				"6.MAN_ADJ   ", MENU_SUBMENU, NULL, 		menu_P6_MAN_ADJ,		NULL},//�ֶ�����, 
			{9,			0,				7, 					"",				"7.CTRL_PAR  ", MENU_SUBMENU, NULL, 		menu_P7_PAR,				NULL},//���Ʋ���,
			{9, 		0,				8,					"",				"8.ANLG_OUT  ", MENU_SUBMENU,	NULL, 		menu_P8_ANLG_OUT,		NULL},//ģ���ź����, 
			{9, 		0,				8,					"",				"9.EXIT      ", NULL,					NULL, 		menu_P8_ANLG_OUT,		NULL},//ģ���ź����,  
}; 
struct MenuItem menu_P1_STANDARD[5] = // ��2���˵�,����������
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�					�ο��궨��	  	����			��һ���˵�							��һ���˵�
			{5,			1,			 	1,					"",				"1.ACTUATOR  ",	MENU_SUBMENU, NULL, 		NULL, 								menu_main},//��ȷ�� �� ���˵���ʲô
			{5,			1, 				2,					"",				"2.AUTO_ADJ  ",	MENU_SUBMENU, NULL, 		ConfirmOrCancel, 			menu_main},
			{5,			1,	 			3,					"",				"3.TOL_BAND  ",	MENU_SUBMENU, NULL, 		NULL, 								menu_main},//��ȷ�� �� ���˵���ʲô
			{5,			1,				4,					"",				"4.TEST      ",	MENU_SUBMENU, NULL, 		NULL, 								menu_main},//��ȷ�� �� ���˵���ʲô
			{5,			1, 				5,					"",				"5.EXIT      ",	MENU_PARAM,		DropOut,	NULL, 								menu_main},
};
struct MenuItem menu_P2_SETPOINT[9] = // ��2���˵�,�����ź���
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�						�ο��궨��	 		����			��һ���˵�					��һ���˵�
			{9,			2, 				1,					"",				"1.SignalSyste",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			2, 				2,					"",				"2.MIN_RGE    ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			2, 				3,					"",				"3.MAX_PRG    ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			2, 				4,					"",				"4.CHARACT    ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			2, 				5,					"",				"5.ACTION     ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			2, 				6,					"",				"6.SHUT-OFF   ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			2, 				7,					"",				"7.RAMP��     ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			2, 				8,					"",				"8.RAMP��     ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			2, 				9,					"",				"9.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL, 						menu_main},
};
struct MenuItem menu_P3_ACTUATOR[4] = // ��2���˵�,�����ź���
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�						�ο��궨��	 		����			��һ���˵�					��һ���˵�
			{4,				3, 			1,					"",				"1.MIN_RGE    ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{4,				3,			2,					"",				"2.MAX_RGE    ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{4,				3, 			3,					"",				"3.ZERO_POS   ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{4,				3, 			4,					"",				"4.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô	
};
struct MenuItem menu_P4_MESSAGES[6] = // ��2���˵�,�����ź���
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�						�ο��궨��	 		����			��һ���˵�					��һ���˵�
			{6,				4, 			1,					"",				"1.TIME_OUT   ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				4, 			2,					"",				"2.POS_SW1    ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
			{6,				4, 			3,					"",				"3.POS_SW2    ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
			{6,				4, 			4,					"",				"4.SW1_ACTV   ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
			{6,				4, 			5,					"",				"5.SW2_ACTV   ",	MENU_SUBMENU, NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
			{6,				4, 			6,					"",				"6.EXIT       ",	MENU_PARAM, 	DropOut,	NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
};
struct MenuItem menu_P5_ALARMS[8] =
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�						�ο��궨��	 		����			��һ���˵�					��һ���˵�
			{8,				5, 			1,					"",				"1.LEACKAGE   ",	MENU_SUBMENU, NULL,  		ConfirmOrCancel,	menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				5, 			2,					"",				"2.SP_RGE     ",	MENU_SUBMENU, NULL,  		ConfirmOrCancel,	menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				5, 			3,					"",				"3.SENS_RGE   ",	MENU_SUBMENU, NULL,  		ConfirmOrCancel,	menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				5, 			4,					"",				"4.CTRLER     ",	MENU_SUBMENU, NULL,  		ConfirmOrCancel,	menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				5, 			5,					"",				"5.TIME_OUT   ",	MENU_SUBMENU, NULL,  		ConfirmOrCancel,	menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				5, 			6,					"",				"6.STRK_CTR   ",	MENU_SUBMENU, NULL,  		ConfirmOrCancel,	menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				5, 			7,					"",				"7.TRAVEL     ",	MENU_SUBMENU, NULL,  		ConfirmOrCancel,	menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				5, 			8,					"",				"8.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
};
struct MenuItem menu_P6_MAN_ADJ[6] =
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�						�ο��궨��	 		����			��һ���˵�					��һ���˵�
			{6,				6, 			1,					"",				"1.MIN_VR     ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				6, 			2,					"",				"2.MAX_VR     ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				6, 			3,					"",				"3.ACTAUTOR   ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				6, 			4,					"",				"4.SPRNG_Y2   ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				6, 			5,					"",				"5.ADJ_MODE   ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				6, 			6,					"",				"6.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
};
struct MenuItem menu_P7_PAR[12] = 
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�						�ο��궨��	 		����			��һ���˵�					��һ���˵�
			{12,			7, 			1,					"",				"1.KP1        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			2,					"",				"2.KP2        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			3,					"",				"3.TV1        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			4,					"",				"4.TV2        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			5,					"",				"5.Air        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			6,					"",				"6.Air        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7,			7,					"",				"7.Air        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			8,					"",				"8.Air        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			9,					"",				"9.Air        ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			10,					"",				"10.Air       ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			11,					"",				"11.Air       ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			7, 			12,					"",				"12.EXIT      ",	MENU_PARAM, 	DropOut, 	NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
};
struct MenuItem menu_P8_ANLG_OUT[6] =
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�						�ο��궨��	 		����			��һ���˵�					��һ���˵�
			{6,			8,			 	1,					"",				"1.MIN_RGE    ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			8, 				2,					"",				"2.MAX_RGE    ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			8, 				3,					"",				"3.ACTION     ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			8, 				4,					"",				"4.ALARM      ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			8, 				5,					"",				"5.TEST       ",	MENU_SUBMENU, NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			8, 				6,					"",				"6.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
};
struct MenuItem ConfirmOrCancel[2] = // ��3���˵�,ȷ�ϻ�ȡ��
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����	�˵��ı�						�ο��궨��	 		����			��һ���˵�					��һ���˵�
			{2,				2, 			1,					"",				"Cancel      ",		NULL,					DropOut, 	NULL, 						menu_main},//ȡ��
			{2,				2, 			2,					"",				"Confirm     ",		MENU_PARAM, 	DropOut, 	NULL, 						menu_main},//ȷ��
};	
//����˵�������Ҫ��ȫ�ֱ���
struct MenuItem *cur_item = menu_main;//��ʼ����ǰ�˵�Ϊ��һ��(main_menu)
struct MenuItem *prev_item = NULL;	//��ʼ����һ���˵�Ϊ��
u8 item_index = 0;//��ǰ�˵�������

void DispCurrentMenu(void)//���Ƶ�ǰ�˵���
{
	
	u8 menu_num = cur_item[0].num;//��ȡ��ǰ�˵�����Ŀ����
	u8 i, num = menu_num>MENU_MAX_ROW ? MENU_MAX_ROW : menu_num;//�����������ܳ���ÿһ��������������
	
	if(item_index>=menu_num)//�˵�������ѡ���Ƿ�Խ�� 
	{ 
		if(item_index==0XFF) 
		{
			item_index = 0; 
		}
		if(item_index>=menu_num) 
		{
			item_index = 0; 
		}else if(item_index<=0)
		{
			item_index = menu_num-1;
		}
	}
	printf("item_index:%d\r\n",item_index);
//	printf("�ϼ��˵�:%s\r\n",prev_item[item_index].label);
	
	if(item_index>=MENU_MAX_ROW)
	{
		for (i=0; i<num; i++)//����ĳһ���˵� 
		{
			display_GB2312_string((i+1)*2,25,(u8 *)cur_item[i+1+(item_index-MENU_MAX_ROW)].label);
			display_GB2312_string((i+1)*2,1,"��");
		}
		display_GB2312_string(6,1,"��");
	}else
	{
		for (i=0; i<num; i++)//����ĳһ���˵� 
		{
			display_GB2312_string((i+1)*2,25,(u8 *)cur_item[i].label);
			display_GB2312_string((i+1)*2,1,"��");
		}
		display_GB2312_string((item_index+1)*2,1,"��");
	}
}

/**.
*��������
*/
void DropOut(const char *Text)
{
		item_index=cur_item[item_index].Higher_Menu_Level-1;//���ò˵�������
		cur_item = prev_item;//������һ���˵�Ϊ��ǰ�˵� 
		prev_item = cur_item[0].prev;//���õ�ǰ�˵�����һ���˵� 
		clear_screen();//����
		if(cur_item[item_index].Higher_Menu_Level==0)	display_GB2312_string(0,0,"�˵�:");
		else	display_GB2312_string(0,1,(u8 *)prev_item[cur_item[item_index].Higher_Menu_Level-1].label);
//							display_GB2312_string(0,0,"��");
		display_GB2312_string(0,110,">>");
		DispCurrentMenu();
}
/**
 * ��������ɨ��
 * LCD��ʾ
 * �˵���ʱ����
 */
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	KeyScan();
	ExitMenuTiming();
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//���TIM3�����жϷ������
	{
		if(Timer_segment>=1000)	Timer_segment=1;
		else Timer_segment++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);//���TIMx�����жϱ�־ 
	}
}
void ExitMenuTiming(void)//ҳ���Զ��˳���ʱ��
{
	if(Timer_segment==999)
	{
		ExitTimed++;
		Err_time++;
	}
	if(ExitTimed==600)
	{
		ExitTimed=0;
		Err_time=1;
	}
}
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
u8 MenuOption(void)
{
	while(1)
	{
		if(SET_Sign==1)//�������һֱ��Ӧ,�����˵���
		{
			if(SET_LongPress==750)//��Ӧʱ��Ϊ2s
			{
				SET_Sign=0;
				clear_screen();//����
				display_GB2312_string(0,1,"�˵�:");
//				display_GB2312_string(0,0,"��");
				display_GB2312_string(0,110,">>");
				DispCurrentMenu();
				while(1)//����˵�������дμ�����ѡ��
				{
					if(UP_LongPress==20)//���Ϸ�ҳ
					{
						UP_LongPress=22;//��ֹ��һ�ζ�ν���
						item_index++; 
						DispCurrentMenu();
					}
					else if(DOWN_LongPress==20)//���·�ҳ
					{
						DOWN_LongPress=22;//��ֹ��һ�ζ�ν���
						item_index--; 
						DispCurrentMenu();
					}
					if(OK_LongPress==20)//����μ�ҳ��
					{
						OK_Sign=22;
						switch(cur_item[item_index].type)//������ͣ�������Ӧ����
						{
							case MENU_SUBMENU:
								if(cur_item[item_index].next != NULL)
								{ 
									prev_item = cur_item;//�˼��˵��������һ���˵� 
									cur_item = cur_item[item_index].next;//��ָ�����һ���˵�����Ϊ��ǰ�˵�
									item_index = 0;//���ò˵�������
									clear_screen();//����
									if(cur_item[item_index].Higher_Menu_Level==0)	display_GB2312_string(0,0,"�˵�:");
									else	display_GB2312_string(0,1,(u8 *)prev_item[cur_item[item_index].Higher_Menu_Level-1].label);
//									display_GB2312_string(0,0,"��");
									display_GB2312_string(0,110,">>");
									DispCurrentMenu();
									
								}else
								{
//									display_GB2312_string(2,25,"NO           ");
								}
								break; 
							case MENU_PARAM: 
								if(cur_item[item_index].Fun != NULL)
								{ 
									//������Ӧ�Ķ�������,�����ݲ���
									cur_item[item_index].Fun((const char *)cur_item[item_index].label);
								}
								else
								{
//									display_GB2312_string(2,25,"NO           ");
								}				
								break; 
							default: 
								break;												
						}
					}
					if(SET_LongPress==20)
					{
						SET_Sign=2;
						SET_LongPress=752;
						if (prev_item != NULL)//������һ���˵��Ĳ��� 
						{
							item_index=cur_item[item_index].Higher_Menu_Level-1;//���ò˵�������
							cur_item = prev_item;//������һ���˵�Ϊ��ǰ�˵� 
							prev_item = cur_item[0].prev;//���õ�ǰ�˵�����һ���˵� 
							clear_screen();//����
							if(cur_item[item_index].Higher_Menu_Level==0)	display_GB2312_string(0,0,"�˵�:");
							else	display_GB2312_string(0,1,(u8 *)prev_item[cur_item[item_index].Higher_Menu_Level-1].label);
//							display_GB2312_string(0,0,"��");
							display_GB2312_string(0,110,">>");
							DispCurrentMenu();
						} 
						else
						{
							Initial();//�ص���ʼҳ��
						}						
					}
					if(ExitTimed==(600-1))	Initial();//�ص���ʼҳ��
				}
			}
		}
		else	Initial();//�ص���ʼҳ��
	}
}
void Initial(void)
{
	u8 i=0;
	clear_screen();//����
	display_128x64(UI_1);
	while(1)
	{
		if(SET_Sign==1)	MenuOption();//���ڳ�ʼ����ʱ��SET������˵���,�ɹ�����˵�����Ҫ����SET 3S
		Decoding_16x32(ExitTimed);
		Decoding_12x16(ExitTimed);
	}
}
void LOGODisplay(void)
{
		
		display_128x64(LOGO);
		delay_ms(1000);
		Initial();
}










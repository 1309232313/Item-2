#include "menu.h"
#include "LCD_ZK.H"
#include "zk.h"
#include "delay.h"
#include "key.h"
#include "timer3.h"
#include "usart.h"

/**************************************************************************************************
*�����洢����,ȫ�ֱ���
*/
//P1
	u8	STANDARD_P10_ACTUATOR=0;	//Form1=1,Form2=2,Form3=3
	u8	STANDARD_P11_AUTO_ADJ=0;	//�����Զ���������
	u8	STANDARD_P12_TOL_BAND=0;	//�趨ƫ���������
	u8	STANDARD_P13_TEST=0;	//�����޸Ľ��
//p2
	u8	SETPOINT_P20_Signal=0;	//SETPOINT_P20_Signal=1.����, 2.��ѹ, 3.������
	float SETPOINT_P21_MIN_RGE=4.0;//ȫ�ֱ���,�趨�����źŵ���Сֵ(Ԥ��Ϊ4mA)
	float SETPOINT_P22_MAX_PRG=20.0;//ȫ�ֱ���,�趨�����źŵ����ֵ(Ԥ��Ϊ20mA)
	u8	SETPOINT_P23_CHARACT=0;	//ѡ�������������
	u8	SETPOINT_P24_ACTION=0;	//1,����;2,����;�趨�����������÷�ʽ
	u8	SETPOINT_P25_SHUT_OFF=0;	//�趨���ſ�����ֵ
	u8	SETPOINT_P26_RAMP1=0;	//���Ϳ����ٶ�
	u8	SETPOINT_P27_RAMP2=0;	//���͹����ٶ�
//P3
	u8	ACTUATOR_P30_MIN_RGE=0;	//����������ʼ����(Ԥ��Ϊ0%)
	u8	ACTUATOR_P31_MAX_RGE=0;	//����������ֹ����(Ԥ��Ϊ100%)
	u8	ACTUATOR_P32_ZERO_POS=2; //1,����;2,����;��ʼ�㷽������(Ԥ��Ϊȫ�ؼ���������ʱ�뷽��)
//P4
	u8	MESSAGES_P40_TIME_OUT=0; //��λ��ʱ
	u8	MESSAGES_P41_POS_SW1=0; //��һλ���ź����õ�
	u8	MESSAGES_P42_POS_SW2=0; //�ڶ�λ���ź����õ�
	u8	MESSAGES_P43_SW1_ACTV=0; //���ڻ���ڵ�һλ���ź�ʱ��Ч
	u8	MESSAGES_P44_SW2_ACTV=0; //���ڻ���ڵڶ�λ���ź�ʱ��Ч
//P5
	u8	ALARMS_P50_LEACKAGE=0; //����ִ��������й©����
	u8	ALARMS_P51_SP_RGE=0; //���������źų��ޱ���
	u8	ALARMS_P52_SENS_RGE=0; //�������Ư�Ʊ���
	u8	ALARMS_P53_CTRLER=0; //����Զ�����Ʊ��л�����
	u8	ALARMS_P54_TIME_OUT=0; //������λ��ʱ����
	u8	ALARMS_P55_STRK_CTR=0; //���������г̳��ޱ���
	u8	ALARMS_P56_TRAVEL=0; //�������г̳��ޱ���
//P6
	u8	MAN_ADJ_P60_MIN_VR=0; //�ֶ����÷���ȫ��λ��
	u8	MAN_ADJ_P61_MAX_VR=0; //�ֶ����÷���ȫ��λ��
	u8	MAN_ADJ_P62_ACTAUTOR=0; //ѡ��ִ������ʽ
	u8	MAN_ADJ_P63_SPRNG_Y2=0; //1,����;2,����;�趨ִ���������쳤ʱ��λ����������ת����
	u8	MAN_ADJ_P64_ADJ_MODE=0; //ѡ���Զ��������������Ŀ
//P7
	u8	CTRL_PAR_P70_KP1=0; //�������ϵ������
	u8	CTRL_PAR_P71_KP2=0; //�������ϵ������
	u8	CTRL_PAR_P72_TV1=0; //�������ʱ�����
	u8	CTRL_PAR_P73_TV2=0; //�������ʱ�����
//P8
	float	ANLGOUT_P80_MIN_RGE=4.0;//��λ��ʼ�����ֵ��Ĭ��Ϊ4mA)
	float	ANLGOUT_P81_MAX_RGE=20.0;//100%��λ����ֵ��Ĭ��Ϊ20mA)
	u8	ANLG_OUT_P82_ACTION=0; //1,����;2,����;��λ��������ѡ��Ĭ��4mA ��Ӧ��λ 0%��
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
struct MenuItem menu_main[8];//1���˵�,���˵�
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
	struct MenuItem menu_P1_0ACTUATOR[3];//P1.0 ACTUATOR,���嶨λ����װ��ʽ
//	struct MenuItem menu_P1_1AUTO_ADJ[2];//P1.1 AUTO_ADJ �����Զ���������
	struct MenuItem menu_P1_2TOL_BAND[2];//P1.2 TOL_BAND �趨ƫ���������
	struct MenuItem menu_P1_3TEST[2];//P1.3 TEST �����޸Ľ��
//	struct MenuItem menu_P1_4EXIT[2];//P1.4 EXIT �˳������в�����
//P2�˵�
	struct MenuItem menu_P2_0SignalSystem[3];//P2.0 �ź���ʽ 1.���� 2.��ѹ 3.������
	struct MenuItem menu_P2_1MIN_RGE[3];//P2.1 MIN_RGE �趨�����źŵ���Сֵ(Ԥ��Ϊ4mA)	,****��ȷ��
	struct MenuItem menu_P2_2MAX_PRG[3];//P2.2 MAX_PRG �趨�����źŵ����ֵ(Ԥ��Ϊ20mA)	,****��ȷ��
	struct MenuItem menu_P2_3CHARACT[3];//P2.3 CHARACT ѡ�������������	,****��ȷ��
	struct MenuItem menu_P2_4ACTION[2];//P2.4 ACTION �趨�����������÷�ʽ	,****��ȷ��
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
	struct MenuItem menu_P6_2ACTAUTOR[2];//P6.2 ACTAUTOR ѡ��ִ������ʽ				,****��ȷ��
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


//����˵�������Ҫ��ȫ�ֱ���
struct MenuItem *cur_item = menu_main;//��ʼ����ǰ�˵�Ϊ��һ��(main_menu)
struct MenuItem *prev_item = NULL;	//��ʼ����һ���˵�Ϊ��
u8 item_index = 0;//��ǰ�˵�������

/*****************************************************************************************************************************************************************************************************/
//�ṹ���ʼ��//�˵�����,�����ｫÿһ���˵��Ĺ������ú�
/**
*һ���˵�
*/
struct MenuItem menu_main[8] = // ��1���˵�,���˵�
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�					�ο��궨��	 		����					��������			��һ���˵�						��һ���˵�
			{8, 		0,				0,					"�˵���        >>",		"1.STANDARD  ",	MENU_SUBMENU, NULL,		 			NULL,			menu_P1_STANDARD, 	NULL},//����������,
			{8, 		0,				1,					"",										"2.SETPOINT  ",	MENU_SUBMENU, NULL,		 			NULL,			menu_P2_SETPOINT, 	NULL},//�����ź���,
			{8, 		0,				2,					"",										"3.ACTUATOR  ",	MENU_SUBMENU, NULL,		 			NULL,			menu_P3_ACTUATOR,		NULL},//ִ����������,
			{8, 		0,				3,					"",										"4.MESSAGES  ",	MENU_SUBMENU, NULL,		 			NULL,			menu_P4_MESSAGES,		NULL},//P4._,
			{8, 		0,				4,					"",										"5.ALARMS    ", MENU_SUBMENU, NULL,		 			NULL,			menu_P5_ALARMS,			NULL},//����������
			{8, 		0,				5,					"",										"6.MAN_ADJ   ", MENU_SUBMENU, NULL,		 			NULL,			menu_P6_MAN_ADJ,		NULL},//�ֶ�����, 
			{8,			0,				6, 					"",										"7.CTRL_PAR  ", MENU_SUBMENU, NULL,					NULL,			menu_P7_PAR,				NULL},//���Ʋ���,
			{8, 		0,				7,					"",										"8.ANLG_OUT  ", MENU_SUBMENU,	NULL,		 			NULL,			menu_P8_ANLG_OUT,		NULL},//ģ���ź����, 
}; 
/****
***	2���˵�
***/
struct MenuItem menu_P1_STANDARD[5] = // ��2���˵�,P1	����������
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�					�ο��궨��	 		����			��������			��һ���˵�							��һ���˵�
			{5,			0,			 	0,					"1.STANDARD    >>",		"1.ACTUATOR  ",	MENU_SUBMENU, NULL, 			NULL,			menu_P1_0ACTUATOR, 		menu_main},//��ȷ�� �� ���˵���ʲô
			{5,			0, 				1,					"",										"2.AUTO_ADJ  ",	MENU_PARAM, 	CancelOROK,	NULL,			NULL, 								menu_main},
			{5,			0,	 			2,					"",										"3.TOL_BAND  ",	MENU_PARAM, 	CancelOROK, NULL,			NULL, 								menu_main},//��ȷ�� �� ���˵���ʲô
			{5,			0,				3,					"",										"4.TEST      ",	MENU_PARAM, 	CancelOROK,	NULL,			NULL, 								menu_main},//��ȷ�� �� ���˵���ʲô
			{5,			0, 				4,					"",										"5.EXIT      ",	MENU_PARAM,		UpOneLevel,	NULL,			NULL, 								menu_main},
};
struct MenuItem menu_P2_SETPOINT[9] = // ��2���˵�,P2	�����ź���
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�						�ο��궨��	 		����												��������			��һ���˵�								��һ���˵�
			{9,			1, 				0,					"2.SETPOINT    >>",		"1.SignalSyste",	MENU_SUBMENU, NULL, 											NULL, 			menu_P2_0SignalSystem,	menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			1, 				1,					"",										"2.MIN_RGE    ",	MENU_PARAM, 	CurrentValue, 							MIN_RGE2, 		NULL, 									menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			1, 				2,					"",										"3.MAX_PRG    ",	MENU_PARAM, 	CurrentValue, 							MAX_PRG2, 		NULL, 									menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			1, 				3,					"",										"4.CHARACT    ",	MENU_SUBMENU, NULL, 											NULL, 			NULL, 									menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			1, 				4,					"",										"5.ACTION     ",	MENU_SUBMENU, NULL, 											NULL, 			menu_P2_4ACTION, 				menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			1, 				5,					"",										"6.SHUT-OFF   ",	MENU_SUBMENU, NULL, 											NULL, 			NULL, 									menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			1, 				6,					"",										"7.RAMP��     ",	MENU_SUBMENU, NULL, 											NULL, 			NULL, 									menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			1, 				7,					"",										"8.RAMP��     ",	MENU_SUBMENU, NULL, 											NULL, 			NULL, 									menu_main},//��ȷ�� �� ���˵���ʲô
			{9,			1, 				8,					"",										"9.EXIT       ",	MENU_PARAM, 	UpOneLevel, 								NULL, 			NULL, 									menu_main},
};
struct MenuItem menu_P3_ACTUATOR[4] = // ��2���˵�,P3	ִ����������
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�						�ο��궨��	 		����			��������			��һ���˵�						��һ���˵�
			{4,				2, 			0,					"3.ACTUATOR    >>",		"1.MIN_RGE    ",	MENU_SUBMENU, NULL, 			NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{4,				2,			1,					"",										"2.MAX_RGE    ",	MENU_SUBMENU, NULL, 			NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{4,				2, 			2,					"",										"3.ZERO_POS   ",	MENU_SUBMENU, NULL,		 		NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{4,				2, 			3,					"",										"4.EXIT       ",	MENU_PARAM, 	UpOneLevel,	NULL,			NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô	
};
struct MenuItem menu_P4_MESSAGES[6] = // ��2���˵�,P4	MESSAGES
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�						�ο��궨��	 		����			��������			��һ���˵�						��һ���˵�
			{6,				3, 			0,					"4.MESSAGES    >>",		"1.TIME_OUT   ",	MENU_SUBMENU, NULL, 			NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				3, 			1,					"",										"2.POS_SW1    ",	MENU_SUBMENU, NULL, 			NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
			{6,				3, 			2,					"",										"3.POS_SW2    ",	MENU_SUBMENU, NULL, 			NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
			{6,				3, 			3,					"",										"4.SW1_ACTV   ",	MENU_SUBMENU, NULL, 			NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
			{6,				3, 			4,					"",										"5.SW2_ACTV   ",	MENU_SUBMENU, NULL,		 		NULL,  		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
			{6,				3, 			5,					"",										"6.EXIT       ",	MENU_PARAM, 	UpOneLevel,	NULL, 		NULL, 						menu_main},//��ȷ�� �� ���˵���ʲô			
};
struct MenuItem menu_P5_ALARMS[8] = // ��2���˵�,P5	����������
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�						�ο��궨��	 		����					��������		��һ���˵�		��һ���˵�
			{8,				4, 			0,					"5.ALARMS      >>",		"1.LEACKAGE   ",	MENU_PARAM, 	CancelOROK, 	NULL,  		NULL,					menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				4, 			1,					"",										"2.SP_RGE     ",	MENU_PARAM, 	CancelOROK, 	NULL,  		NULL,					menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				4, 			2,					"",										"3.SENS_RGE   ",	MENU_PARAM, 	CancelOROK, 	NULL,  		NULL,					menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				4, 			3,					"",										"4.CTRLER     ",	MENU_PARAM, 	CancelOROK, 	NULL,  		NULL,					menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				4, 			4,					"",										"5.TIME_OUT   ",	MENU_PARAM, 	CancelOROK, 	NULL,  		NULL,					menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				4, 			5,					"",										"6.STRK_CTR   ",	MENU_PARAM, 	CancelOROK, 	NULL,  		NULL,					menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				4, 			6,					"",										"7.TRAVEL     ",	MENU_PARAM, 	CancelOROK, 	NULL,  		NULL,					menu_main},//��ȷ�� �� ���˵���ʲô
			{8,				4, 			7,					"",										"8.EXIT       ",	MENU_PARAM, 	UpOneLevel,		NULL,			NULL, 				menu_main},//��ȷ�� �� ���˵���ʲô
};
struct MenuItem menu_P6_MAN_ADJ[6] = // ��2���˵�,P6	�ֶ�����
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�						�ο��궨��	 		����			��������			��һ���˵�						��һ���˵�
			{6,				5, 			0,					"6.MAN_ADJ     >>",		"1.MIN_VR     ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,								menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				5, 			1,					"",										"2.MAX_VR     ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,								menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				5, 			2,					"",										"3.ACTAUTOR   ",	MENU_SUBMENU, NULL, 			NULL,  		menu_P6_2ACTAUTOR,	menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				5, 			3,					"",										"4.SPRNG_Y2   ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,								menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				5, 			4,					"",										"5.ADJ_MODE   ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,								menu_main},//��ȷ�� �� ���˵���ʲô
			{6,				5, 			5,					"",										"6.EXIT       ",	MENU_PARAM, 	UpOneLevel,	NULL,			NULL,								menu_main},//��ȷ�� �� ���˵���ʲô
};
struct MenuItem menu_P7_PAR[12] = // ��2���˵�,P7	���Ʋ���
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�						�ο��궨��	 		����			��������			��һ���˵�						��һ���˵�
			{12,			6, 			0,					"7.PAR         >>",		"1.KP1        ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			1,					"",										"2.KP2        ",	MENU_SUBMENU, NULL,				NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			2,					"",										"3.TV1        ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			3,					"",										"4.TV2        ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			4,					"",										"5.Air        ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			5,					"",										"6.Air        ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6,			6,					"",										"7.Air        ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			7,					"",										"8.Air        ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			8,					"",										"9.Air        ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			9,					"",										"10.Air       ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			10,					"",										"11.Air       ",	MENU_SUBMENU, NULL, 			NULL,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{12,			6, 			11,					"",										"12.EXIT      ",	MENU_PARAM, 	UpOneLevel, NULL,			NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
};
struct MenuItem menu_P8_ANLG_OUT[6] = // ��2���˵�,P8	ģ���ź����
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����							�˵��ı�						�ο��궨��	 		����							��������			��һ���˵�						��һ���˵�
			{6,			7,			 	0,					"8.ANLG_OUT    >>",		"1.MIN_RGE    ",	MENU_PARAM,	 	CurrentValue, 		MIN_RGE8,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			7, 				1,					"",										"2.MAX_RGE    ",	MENU_PARAM,		CurrentValue, 		MAX_RGE8,  		NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			7, 				2,					"",										"3.ACTION     ",	MENU_SUBMENU, NULL, 						NULL,  				menu_P8_2ACTION,	menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			7, 				3,					"",										"4.ALARM      ",	MENU_SUBMENU, NULL, 						NULL,  				NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			7, 				4,					"",										"5.TEST       ",	MENU_SUBMENU, NULL, 						NULL,  				NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
			{6,			7, 				5,					"",										"6.EXIT       ",	MENU_PARAM, 	UpOneLevel, 			NULL,					NULL,							menu_main},//��ȷ�� �� ���˵���ʲô
};
/********
*****	3���˵�
*****/
////p1
	struct MenuItem menu_P1_0ACTUATOR[3] = // ��	3 ���˵�,P1_0	���嶨λ����װ��ʽ
	{
	//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����						�˵��ı�						�ο��궨��	 		����					��������			��һ���˵�						��һ���˵�
				{3,				0, 			0,					"1_1.ACTUATOR  >>",	"1.Form 1     ",	MENU_PARAM, 	CancelOROK, 	Form1, 	 		NULL,								menu_P1_STANDARD},//��ʽ1
				{3,				0, 			1,					"",									"2.Form 2     ",	MENU_PARAM, 	CancelOROK, 	Form2,  		NULL,								menu_P1_STANDARD},//��ʽ2
				{3,				0, 			2,					"",									"3.Form 3     ",	MENU_PARAM, 	CancelOROK, 	Form3,  		NULL,								menu_P1_STANDARD},//��ʽ3
	};

////p2
	struct MenuItem menu_P2_0SignalSystem[3] = // ��	3 ���˵�,P2_0	�ź���ʽ
	{		
	//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����						�˵��ı�						�ο��궨��	 		����					��������			��һ���˵�						��һ���˵�
				{3,				0, 			0,					"2_1.Signal    >>",	"1.Current    ",	MENU_PARAM, 	CancelOROK, 	CURRENT, 	 	NULL,								menu_P2_SETPOINT},//����
				{3,				0, 			1,					"",									"2.Voltage    ",	MENU_PARAM, 	CancelOROK, 	VOLTAGE,  	NULL,								menu_P2_SETPOINT},//��ѹ
				{3,				0, 			2,					"",									"3.Switch     ",	MENU_PARAM, 	CancelOROK, 	SWITCH,  		NULL,								menu_P2_SETPOINT},//������
	};
	struct MenuItem menu_P2_4ACTION[2] = // ��	3 ���˵�,P2_4	�趨�����������÷�ʽ
	{	
	//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����						�˵��ı�						�ο��궨��	 		����					��������			��һ���˵�						��һ���˵�
				{2,				4, 			0,					"2_4.ACTION   >>",	"1.Positive   ",	MENU_PARAM, 	CancelOROK, 	POSITIVE,  	NULL,								menu_P2_SETPOINT},//����
				{2,				4, 			1,					"",									"2.Reverse    ",	MENU_PARAM, 	CancelOROK, 	REVERSE,  	NULL,								menu_P2_SETPOINT},//����
	};	
////p6
	struct MenuItem menu_P6_2ACTAUTOR[2] = // ��	3 ���˵�,P6_2	ѡ��ִ������ʽ
	{
	//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����						�˵��ı�						�ο��궨��	 		����					��������			��һ���˵�						��һ���˵�
				{2,				4, 			0,					"6_2.ACTAUTOR >>",	"1.Form 1      ",	MENU_PARAM, 	CancelOROK, 	ACTAUTOR1, 	NULL,								menu_P6_MAN_ADJ},//��ʽ1	
				{2,				4, 			0,					"",									"2.Form 2      ",	MENU_PARAM, 	CancelOROK, 	ACTAUTOR2,	NULL,								menu_P6_MAN_ADJ},//��ʽ2
	};
////p8
	struct MenuItem menu_P8_2ACTION[2] = // ��	3 ���˵�,P6_2	ѡ��ִ������ʽ	
	{
	//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����						�˵��ı�						�ο��궨��	 		����					��������			��һ���˵�						��һ���˵�
				{2,				4, 			0,					"8_2.ACTION   >>",	"1.Positive    ",	MENU_PARAM, 	CancelOROK, 	ACTION1,			NULL,								menu_P8_ANLG_OUT},//����	
				{2,				4, 			0,					"",									"2.Reverse     ",	MENU_PARAM, 	CancelOROK, 	ACTION2,			NULL,								menu_P8_ANLG_OUT},//����
	};
	
	
struct MenuItem ConfirmOrCancel[2] = // ��3���˵�,ȷ�ϻ�ȡ��
{
//�����˵�����	�ϼ��˵���	��ǰ�˵���  ���˵�����						�˵��ı�						�ο��궨��	 		����			��������			��һ���˵�						��һ���˵�
			{2,				2, 			0,					"",									"Cancel      ",		NULL,					UpOneLevel, 	NULL,				NULL, 						menu_main},//ȡ��
			{2,				2, 			1,					"",									"Confirm     ",		MENU_PARAM, 	UpOneLevel, 	NULL,				NULL, 						menu_main},//ȷ��
};	









/******************************************************************************************************************************************************************************************************
*��������
*/
/**
*������һ���˵�
*@Text	�ϼ��˵��ı�
*@parameter	��������
*/
void	UpOneLevel(const char *Text, u16 parameter)
{
	item_index=cur_item[item_index].Higher_Menu_Level;//���ò˵�������
	cur_item = prev_item;//������һ���˵�Ϊ��ǰ�˵� 
	prev_item = cur_item[0].prev;//���õ�ǰ�˵�����һ���˵� 
	DispCurrentMenu();
}

/**
*����ȫ�ֲ���
*@parameter	��������ҳ��Ķ�������,
*@value	ȡ����ȷ��
*/
void	ParameterAssignment(u16 parameter,u16 value)
{
	switch(parameter)
	{
//P1
		case	Form1:	STANDARD_P10_ACTUATOR=1;	break;
		case	Form2:	STANDARD_P10_ACTUATOR=2;	break;
		case	Form3:	STANDARD_P10_ACTUATOR=3;	break;
		case	AUTO_ADJ:	STANDARD_P11_AUTO_ADJ=(u8)value;	break;
		case	TOL_BAND:	STANDARD_P12_TOL_BAND=(u8)value;	break;
		case	TEST:	STANDARD_P13_TEST=0;	break;
//P2
		case	CURRENT:	SETPOINT_P20_Signal=1;	break;
		case	VOLTAGE:	SETPOINT_P20_Signal=2;	break;
		case	SWITCH:		SETPOINT_P20_Signal=3;	break;
		case	MIN_RGE2:	break;
		case	MAX_PRG2:	break;
		case	CHARACT:	break;                                                                               
		case	POSITIVE:	SETPOINT_P24_ACTION=1;	break;
		case	REVERSE:	SETPOINT_P24_ACTION=2;	break;
		case	SHUT_OFF:	SETPOINT_P25_SHUT_OFF=(u8)value;	break;
		case	RAMP1:	break;
		case	RAMP2:	break;
//P3
		case	MIN_RGE:	break;
		case	MAX_RGE:	break;
		case	ZERO_POS1:	break;
		case	ZERO_POS2:	break;
//P4
		case	TIME_OUT4:	break;
		case	POS_SW1:	break;
		case	POS_SW2:	break;
		case	SW1_ACTV:	break;
		case	SW2_ACTV:	break;
//P5
		case	LEACKAGE:	break;
		case	SP_RGE:	break;
		case	SENS_RGE:	break;
		case	CTRLER:	break;
		case	TIME_OUT5:	break;
		case	STRK_CTR:	break;
		case	TRAVEL:	break;
//P6
		case	MIN_VR:	break;
		case	MAX_VR:	break;
		case	ACTAUTOR1:	MAN_ADJ_P62_ACTAUTOR=1;	break;
		case	ACTAUTOR2:	MAN_ADJ_P62_ACTAUTOR=2;	break;
		case	SPRNG_Y2:	break;
		case	ADJ_MODE:	break;
//P7
		case	KP1:	break;
		case	KP2:	break;
		case	TV1:	break;
		case	TV2:	break;
//P8
		case	MIN_RGE8:	break;
		case	MAX_RGE8:	break;
		case	ACTION1:	ANLG_OUT_P82_ACTION=1;	break;
		case	ACTION2:	ANLG_OUT_P82_ACTION=2;	break;
		default:	break;
	}
	
	
	
}
/**
*����ȷ������,��ֹ��
*@Text	[] ,�ϼ��˵��ı�
*@parameter [] ,��������,ȫ�ֱ���
*{ParameterAssignment(parameter,value)},����ȫ�ֲ��� 
*/
void CancelOROK(const char *Text, u16 parameter)
{
	u8 key=0;
	u16 value=0;
	clear_screen();//����
	display_GB2312_string(0,1,(u8*)Text);
	display_GB2312_string(2,25,"Cancel      ");
	display_GB2312_string(4,25,"Confirm     ");
	display_GB2312_string(2,1,"��");//	��	��
	display_GB2312_string(4,1,"��");
	while(1)
	{
		key=KEY_Scan(0);//ɨ�谴��
		switch(key)
		{
			case	UP_PRES:
						display_GB2312_string(2,1,"��");
						display_GB2312_string(4,1,"��");
						value=CLOSE;
						break;
			case	DOWN_PRES:
						display_GB2312_string(2,1,"��");
						display_GB2312_string(4,1,"��");
						value=START;
						break;
			case	OK_PRES:
						if(value==START)	ParameterAssignment(parameter,value);	
						SET_Sign=1;
						SET_LongPress=750;
						MenuOption();
						break;
			case	SET_PRES:
						SET_Sign=1;
						SET_LongPress=750;
						MenuOption();
						break;
			default:
						break;
		}
	}
}
/**
*�趨�ź������Сֵ����λmA��ÿ���趨��С����Ϊ0.1mA
*@Text	[],��ʾ�����˵��ı�,�������ʾ
*@parameter	[MIN_RGE],�趨�����źŵ���Сֵ(Ԥ��Ϊ4mA)
*@parameter	[MAX_PRG],�趨�����źŵ����ֵ(Ԥ��Ϊ20mA)
*/
void CurrentValue(const char *Text,u16 parameter)
{
	u16 value=0;
	u8 key=0;
	switch(parameter)
	{
		case	MIN_RGE2:
					value=SETPOINT_P21_MIN_RGE*10;//���趨�����źŵ���Сֵ��ֵ��	parameter		(Ԥ��Ϊ4mA)
					break;
		case	MAX_PRG2:
					value=SETPOINT_P22_MAX_PRG*10;//���趨�����źŵ����ֵ��ֵ��	parameter		(Ԥ��Ϊ20mA)
					break;
		case	MIN_RGE8:
					value=ANLGOUT_P80_MIN_RGE*10;//����λ��ʼ�����ֵ��ֵ��	parameter		��Ĭ��Ϊ4mA)
					break;
		case	MAX_RGE8:
					value=ANLGOUT_P81_MAX_RGE*10;//��100%��λ����ֵ��ֵ��	parameter		��Ĭ��Ϊ20mA)
					break;
		default:
					break;
	}
	clear_screen();//����
	display_GB2312_string(0,1,(u8*)Text);
	display_string_5x7(6,110,"mA");
	while(1)
	{
		key=KEY_Scan(3);//ɨ�谴��
		switch(key)
		{
			case	UP_PRES:
						switch(parameter)
						{
							case	MIN_RGE2:
										if(value>=SETPOINT_P22_MAX_PRG*10)	value=value;
										else	value++;
										break;
							case	MAX_PRG2:
										if(value>=25*10)	value=value;
										else	value++;
										break;
							case	MIN_RGE8:
										if(value>=ANLGOUT_P81_MAX_RGE*10)	value=value;
										else	value++;
										break;
							case	MAX_RGE8:
										if(value>=25*10)	value=value;
										else	value++;
										break;
							default:
										break;
						}
						break;
			case	DOWN_PRES:
						switch(parameter)
						{
							case	MIN_RGE2:
										if(value<=2*10)	value=value;
										else	value--;
										break;
							case	MAX_PRG2:
										if(value<=SETPOINT_P21_MIN_RGE*10)	value=value;
										else	value--;
										break;
							case	MIN_RGE8:
										if(value<=2*10)	value=value;
										else	value--;
										break;
							case	MAX_RGE8:
										if(value<=ANLGOUT_P80_MIN_RGE*10)	value=value;
										else	value--;
										break;
							default:
										break;
						}
						break;
			case	OK_PRES:
						switch(parameter)
						{
							case	MIN_RGE2:
										SETPOINT_P21_MIN_RGE=value;//���趨�����źŵ���Сֵ��ֵ��	parameter		(Ԥ��Ϊ4mA)
										SETPOINT_P21_MIN_RGE=SETPOINT_P21_MIN_RGE/10;
										break;
							case	MAX_PRG2:
										SETPOINT_P22_MAX_PRG=value;//���趨�����źŵ����ֵ��ֵ��	parameter		(Ԥ��Ϊ20mA)
										SETPOINT_P22_MAX_PRG=SETPOINT_P22_MAX_PRG/10;
										break;
							case	MIN_RGE8:
										ANLGOUT_P80_MIN_RGE=value;
										ANLGOUT_P80_MIN_RGE=ANLGOUT_P80_MIN_RGE/10;//
										break;
							case	MAX_RGE8:
										ANLGOUT_P81_MAX_RGE=value;
										ANLGOUT_P81_MAX_RGE=ANLGOUT_P81_MAX_RGE/10;//
										break;
							default:
										break;
						}
						SET_Sign=1;
						SET_LongPress=750;
						MenuOption();
						break;
			case	SET_PRES:
						SET_LongPress=750;
						MenuOption();
						break;
			default:
				break;
		}
		key=0;
		Decoding_16x32(value);
		if(ExitTimed==(600-1))	Initial();//�ص���ʼҳ��
	}
}

/**
*���Ʋ˵��ı���
*/
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
	clear_screen();//����
	display_GB2312_string(0,1,(u8*)cur_item[0].title);
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
/**
*ѡ��˵�,��������˵�ѡ��
*/
u8 MenuOption(void)
{
	u8 key=0;
	while(1)
	{
		if(SET_Sign==1)//�������һֱ��Ӧ,�����˵���
		{
			if(SET_LongPress==750)//��Ӧʱ��Ϊ2s
			{
				SET_Sign=0;
				DispCurrentMenu();
				while(1)//����˵�������дμ�����ѡ��
				{
					key=KEY_Scan(0);//ɨ�谴��
					switch(key)
					{
						case	UP_PRES:
									item_index--; 
									DispCurrentMenu();
									break;
						case	DOWN_PRES:
									item_index++; 
									DispCurrentMenu();
									break;
						case	OK_PRES:
									switch(cur_item[item_index].type)//������ͣ�������Ӧ����
									{
										case MENU_SUBMENU:
											if(cur_item[item_index].next != NULL)
											{ 
												prev_item = cur_item;//�˼��˵��������һ���˵� 
												cur_item = cur_item[item_index].next;//��ָ�����һ���˵�����Ϊ��ǰ�˵�
												item_index = 0;//���ò˵�������
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
												cur_item[item_index].Fun((const char *)cur_item[item_index].label,cur_item[item_index].action);
											}
											else
											{
			//									display_GB2312_string(2,25,"NO           ");
											}				
											break; 
										default: 
											break;												
									}
									break;
							case	SET_PRES:
										if (prev_item != NULL)//������һ���˵��Ĳ��� 
										{
											item_index=cur_item[item_index].Higher_Menu_Level;//���ò˵�������
											cur_item = prev_item;//������һ���˵�Ϊ��ǰ�˵� 
											prev_item = cur_item[0].prev;//���õ�ǰ�˵�����һ���˵� 
											DispCurrentMenu();
										} 
										else
										{
											Initial();//�ص���ʼҳ��
										}
										break;
							default: 
								break;
					}
					if(ExitTimed==(600-1))	Initial();//�ص���ʼҳ��
				}
			}
		}
		else	Initial();//�ص���ʼҳ��
	}
}
/**
*��̬��ʾ����
*/
void Initial(void)
{
//	u8 i=0;
	clear_screen();//����
	display_128x64(UI_1);
	printf("SETPOINT_P20_Signal:%d\r\n",SETPOINT_P20_Signal);
	while(1)
	{
		
		if(SET_Sign==1)	MenuOption();//���ڳ�ʼ����ʱ��SET������˵���,�ɹ�����˵�����Ҫ����SET 3S
		Decoding_16x32(ExitTimed);
		Decoding_12x16(ExitTimed);
	}
}
/**
*����LOGO����
*/
void LOGODisplay(void)
{
		display_128x64(LOGO);
		delay_ms(1000);
		Initial();
}










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
//������Ӧ�Ķ�����������
#define ACTION_ASSOCIATION	5//������������
//������Ӧ�Ķ�������
//p1
	#define	Form1				101	//P1.0���嶨λ����װ��ʽ:1,Form1
	#define	Form2				102	//P1.0���嶨λ����װ��ʽ:2,Form2
	#define	Form3				103	//P1.0���嶨λ����װ��ʽ:3,Form3
	#define	AUTO_ADJ		111	//P1.1 AUTO_ADJ �����Զ���������
	#define	TOL_BAND		121	//P1.2 TOL_BAND �趨ƫ���������
	#define	TEST				131	//P1.3 TEST �����޸Ľ��
//P2
	#define CURRENT			201	//P2.01�ź���ʽ:1,������ʽ
	#define	VOLTAGE			202	//P2.02�ź���ʽ:2,��ѹ��ʽ
	#define	SWITCH			203	//P2.03�ź���ʽ:3,������
	#define	MIN_RGE2		211	//P2.1 MIN_RGE �趨�����źŵ���Сֵ(Ԥ��Ϊ4mA)
	#define	MAX_PRG2		221	//P2.2 MAX_PRG �趨�����źŵ����ֵ(Ԥ��Ϊ20mA)
	#define	CHARACT			231	//P2.3 CHARACT ѡ�������������
	#define	POSITIVE		241	//P2.41 ACTION:�趨���������÷�ʽ
	#define	REVERSE			242	//P2.42 ACTION:�趨���ŷ����÷�ʽ
	#define	SHUT_OFF		251	//P2.5 SHUT-OFF �趨���ſ�����ֵ
	#define	RAMP1				261	//P2.61 RAMP? ���Ϳ����ٶ�
	#define	RAMP2				271	//P2.71 RAMP? ���͹����ٶ�
//P3
	#define	MIN_RGE			301	//P3.0 MIN_RGE ����������ʼ����(Ԥ��Ϊ0%)
	#define	MAX_RGE			311	//P3.1 MAX_RGE ����������ֹ����(Ԥ��Ϊ100%)
	#define	ZERO_POS1 	321	//P3.2 ZERO_POS ��ʼ�㷽������(Ԥ��Ϊȫ�ؼ���������ʱ�뷽��)
	#define	ZERO_POS2		322	//P3.2 ZERO_POS ��ʼ�㷽������(Ԥ��Ϊȫ�ؼ���������ʱ�뷽��)
//P4
	#define	TIME_OUT4		401	//P4.0 TIME_OUT ��λ��ʱ
	#define	POS_SW1			411	//P4.1 POS_SW1 ��һλ���ź����õ�
	#define	POS_SW2			421	//P4.2 POS_SW2 �ڶ�λ���ź����õ�
	#define	SW1_ACTV		431	//P4.3 SW1_ACTV ���ڻ���ڵ�һλ���ź�ʱ��Ч
	#define	SW2_ACTV		441	//P4.4 SW2_ACTV ���ڻ���ڵڶ�λ���ź�ʱ��Ч
//P5
	#define	LEACKAGE		501	//P5.0 LEACKAGE ����ִ��������й©����
	#define	SP_RGE			511	//P5.1 SP_RGE ���������źų��ޱ���
	#define	SENS_RGE		521	//P5.2 SENS_RGE �������Ư�Ʊ���
	#define	CTRLER			531	//P5.3 CTRLER ����Զ�����Ʊ��л�����
	#define	TIME_OUT5		541	//P5.4 TIME_OUT ������λ��ʱ����
	#define	STRK_CTR		551	//P5.5 STRK_CTR ���������г̳��ޱ���
	#define	TRAVEL			561	//P5.6 TRAVEL �������г̳��ޱ���
//P6
	#define	MIN_VR			601	//P6.0 MIN_VR �ֶ����÷���ȫ��λ��
	#define	MAX_VR			611	//P6.1 MAX_VR �ֶ����÷���ȫ��λ��
	#define	ACTAUTOR1		621	//P6.2 ACTAUTOR ѡ��ִ������ʽ
	#define	ACTAUTOR2		622	//P6.2 ACTAUTOR ѡ��ִ������ʽ
	#define	SPRNG_Y2		631	//P6.3 SPRNG_Y2 �趨ִ���������쳤ʱ��λ����������ת����
	#define	ADJ_MODE		641	//P6.4 ADJ_MODE ѡ���Զ��������������Ŀ
//P7
	#define	KP1					701	//P7.0 KP ? �������ϵ������	
	#define	KP2 				711	//P7.1 KP ? �������ϵ������
	#define	TV1 				721	//P7.2 TV ? �������ʱ�����
	#define	TV2 				731	//P7.3 TV ? �������ʱ�����
//P8
	#define	MIN_RGE8		801	//P8.0 MIN_RGE ��λ��ʼ�����ֵ��Ĭ��Ϊ4mA)
	#define	MAX_RGE8		811	//P8.1 MAX_RGE 100%��λ����ֵ��Ĭ��Ϊ20mA)
	#define	ACTION1			821	//P8.2 ACTION ��λ��������ѡ��Ĭ��4mA ��Ӧ��λ 0%,����
	#define	ACTION2			822	//P8.2 ACTION ��λ��������ѡ��Ĭ��4mA ��Ӧ��λ 0%,����

#define Yes		1 // ���������ִ�в������ã�  
#define No		0 // ���������ִ�в������ã�  
//����˵�������Ҫ��ȫ�ֱ���
extern u8 item_index;//��ǰ�˵�������


/**************************************************************************************************
*�����洢����,ȫ�ֱ���
*/
//P1
extern u8	STANDARD_P10_ACTUATOR;	//Form1=1,Form2=2,Form3=3
extern u8	STANDARD_P11_AUTO_ADJ;	//�����Զ���������
extern u8	STANDARD_P12_TOL_BAND;	//�趨ƫ���������
extern u8	STANDARD_P13_TEST;	//�����޸Ľ��
//p2
extern u8	SETPOINT_P20_Signal;	//SETPOINT_P20_Signal=1.����, 2.��ѹ, 3.������
extern float SETPOINT_P21_MIN_RG;//ȫ�ֱ���,�趨�����źŵ���Сֵ(Ԥ��Ϊ4mA)
extern float SETPOINT_P22_MAX_PRG;//ȫ�ֱ���,�趨�����źŵ����ֵ(Ԥ��Ϊ20mA)
extern u8	SETPOINT_P23_CHARACT;	//ѡ�������������
extern u8	SETPOINT_P24_ACTION;	//1,����;2,����;�趨�����������÷�ʽ
extern u8	SETPOINT_P25_SHUT_OFF;	//�趨���ſ�����ֵ
extern u8	SETPOINT_P26_RAMP1;	//���Ϳ����ٶ�
extern u8	SETPOINT_P27_RAMP2;	//���͹����ٶ�
//P3
extern u8	ACTUATOR_P30_MIN_RGE;	//����������ʼ����(Ԥ��Ϊ0%)
extern u8	ACTUATOR_P31_MAX_RGE;	//����������ֹ����(Ԥ��Ϊ100%)
extern u8	ACTUATOR_P32_ZERO_POS; //1,����;2,����;��ʼ�㷽������(Ԥ��Ϊȫ�ؼ���������ʱ�뷽��)
//P4
extern u8	MESSAGES_P40_TIME_OUT; //��λ��ʱ
extern u8	MESSAGES_P41_POS_SW1; //��һλ���ź����õ�
extern u8	MESSAGES_P42_POS_SW2; //�ڶ�λ���ź����õ�
extern u8	MESSAGES_P43_SW1_ACTV; //���ڻ���ڵ�һλ���ź�ʱ��Ч
extern u8	MESSAGES_P44_SW2_ACTV; //���ڻ���ڵڶ�λ���ź�ʱ��Ч
//P5
extern u8	ALARMS_P50_LEACKAGE; //����ִ��������й©����
extern u8	ALARMS_P51_SP_RGE; //���������źų��ޱ���
extern u8	ALARMS_P52_SENS_RGE; //�������Ư�Ʊ���
extern u8	ALARMS_P53_CTRLER; //����Զ�����Ʊ��л�����
extern u8	ALARMS_P54_TIME_OUT; //������λ��ʱ����
extern u8	ALARMS_P55_STRK_CTR; //���������г̳��ޱ���
extern u8	ALARMS_P56_TRAVEL; //�������г̳��ޱ���
//P6
extern float	MAN_ADJ_P60_MIN_VR; //�ֶ����÷���ȫ��λ��
extern float	MAN_ADJ_P61_MAX_VR; //�ֶ����÷���ȫ��λ��
extern u8	MAN_ADJ_P62_ACTAUTOR; //ѡ��ִ������ʽ
extern u8	MAN_ADJ_P63_SPRNG_Y2; //1,����;2,����;�趨ִ���������쳤ʱ��λ����������ת����
extern u8	MAN_ADJ_P64_ADJ_MODE; //ѡ���Զ��������������Ŀ
//P7
extern u8	CTRL_PAR_P70_KP1; //�������ϵ������
extern u8	CTRL_PAR_P71_KP2; //�������ϵ������
extern u8	CTRL_PAR_P72_TV1; //�������ʱ�����
extern u8	CTRL_PAR_P73_TV2; //�������ʱ�����
//P8
extern float	ANLGOUT_P80_MIN_RGE;//��λ��ʼ�����ֵ��Ĭ��Ϊ4mA)
extern float	ANLGOUT_P81_MAX_RGE;//100%��λ����ֵ��Ĭ��Ϊ20mA)
extern u8	ANLG_OUT_P82_ACTION; //1,����;2,����;��λ��������ѡ��Ĭ��4mA ��Ӧ��λ 0%��
extern u8 Level;

extern vu16 AD_Value[];//�������ADCת�������Ҳ��DMA��Ŀ���ַ











typedef void (*MENU_FUN)(const char *,u16 *);
/*************** 
 * �˵��ṹ 
 * һ������ȴ���һ���˵��������е�һ��Ԫ�ؾ���һ���˵������һ�������Ľṹ�壬 
 * �����еĵ�һ��Ԫ���е�numֵ����Ҫ����ʾ�����˵����ж��ٸ��˵�� 
 * 
 * uint8_t num �����˵������������ڵ�һ����������ȷ�Ĳ˵������� 
 * u8 Higher_Menu_Level;�ϼ��˵���
 * u8 Current_Menu_Level;��ǰ�˵���
 * char* label �˵��ı� 
 * uint8_t type �������ͣ��ο��궨�� 
 * MENU_CALLBACK CallBack;  ָ�����ĺ���ָ�룬����Ҫִ�еľ��嶯������ 
 * u16 action �����������ݵĶ�������
 * u16 ActionAssociation  ����������ָ��༶���п�������ʱֻ������һ��ָ��ʱ
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
	u16 action;//�����������ݵĶ�������
	u16 ActionAssociation;//����������ָ��༶���п�������ʱֻ������һ��ָ��ʱ
	struct MenuItem *next;	//��һ���˵�
	struct MenuItem *prev;	//��һ���˵�
};

void	UpOneLevel(const char *Text, u16 *parameter);//������һ��
void DispCurrentMenu(void);//���Ƶ�ǰ�˵���
void Associated_Action(void);//������������,�����ر�����������
void CancelOROK(const char *Text, u16 *parameter);//����
void CurrentValue(const char *Text,u16 *parameter);
void	ParameterAssignment(u16 parameter,u16 value);
void ValvePosition_P6(const char *Text,u16 *parameter);//����λ��
u8 MenuOption(void);
void Initial(void);
void LOGODisplay(void);

#endif


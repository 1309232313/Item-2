#ifndef __MENU_H
#define __MENU_H	 
#include "sys.h"

#define NULL 0

#define MENU_MAX_ROW 3 // 菜单最大显示行数 

//定义菜单项类型 
#define MENU_SUBMENU	11 // 具有子菜单的菜单项 
#define MENU_PARAM		12 // 参数项（用于执行参数设置）   

#define	START					13 //	启动	
#define	CLOSE					14 //	关闭
//定义相应的动作关联参数
#define ACTION_ASSOCIATION	5//动作关联参数
//定义相应的动作参数
//p1
	#define	Form1				101	//P1.0定义定位器安装形式:1,Form1
	#define	Form2				102	//P1.0定义定位器安装形式:2,Form2
	#define	Form3				103	//P1.0定义定位器安装形式:3,Form3
	#define	AUTO_ADJ		111	//P1.1 AUTO_ADJ 启动自动整定程序
	#define	TOL_BAND		121	//P1.2 TOL_BAND 设定偏差带或死区
	#define	TEST				131	//P1.3 TEST 试验修改结果
//P2
	#define CURRENT			201	//P2.01信号制式:1,电流形式
	#define	VOLTAGE			202	//P2.02信号制式:2,电压形式
	#define	SWITCH			203	//P2.03信号制式:3,开关量
	#define	MIN_RGE2		211	//P2.1 MIN_RGE 设定给定信号的最小值(预设为4mA)
	#define	MAX_PRG2		221	//P2.2 MAX_PRG 设定给定信号的最大值(预设为20mA)
	#define	CHARACT			231	//P2.3 CHARACT 选择调节特性曲线
	#define	POSITIVE		241	//P2.41 ACTION:设定阀门正作用方式
	#define	REVERSE			242	//P2.42 ACTION:设定阀门反作用方式
	#define	SHUT_OFF		251	//P2.5 SHUT-OFF 设定阀门开度阈值
	#define	RAMP1				261	//P2.61 RAMP? 降低开向速度
	#define	RAMP2				271	//P2.71 RAMP? 降低关向速度
//P3
	#define	MIN_RGE			301	//P3.0 MIN_RGE 调节曲线起始开度(预设为0%)
	#define	MAX_RGE			311	//P3.1 MAX_RGE 调节曲线终止开度(预设为100%)
	#define	ZERO_POS1 	321	//P3.2 ZERO_POS 起始点方向设置(预设为全关即返馈杆逆时针方向)
	#define	ZERO_POS2		322	//P3.2 ZERO_POS 起始点方向设置(预设为全关即返馈杆逆时针方向)
//P4
	#define	TIME_OUT4		401	//P4.0 TIME_OUT 定位超时
	#define	POS_SW1			411	//P4.1 POS_SW1 第一位置信号设置点
	#define	POS_SW2			421	//P4.2 POS_SW2 第二位置信号设置点
	#define	SW1_ACTV		431	//P4.3 SW1_ACTV 高于或低于第一位置信号时有效
	#define	SW2_ACTV		441	//P4.4 SW2_ACTV 高于或低于第二位置信号时有效
//P5
	#define	LEACKAGE		501	//P5.0 LEACKAGE 启动执行器气缸泄漏报警
	#define	SP_RGE			511	//P5.1 SP_RGE 启动给定信号超限报警
	#define	SENS_RGE		521	//P5.2 SENS_RGE 启动零点漂移报警
	#define	CTRLER			531	//P5.3 CTRLER 启动远方控制被切换报警
	#define	TIME_OUT5		541	//P5.4 TIME_OUT 启动定位超时报警
	#define	STRK_CTR		551	//P5.5 STRK_CTR 启动调节行程超限报警
	#define	TRAVEL			561	//P5.6 TRAVEL 启动总行程超限报警
//P6
	#define	MIN_VR			601	//P6.0 MIN_VR 手动设置阀门全关位置
	#define	MAX_VR			611	//P6.1 MAX_VR 手动设置阀门全开位置
	#define	ACTAUTOR1		621	//P6.2 ACTAUTOR 选择执行器型式
	#define	ACTAUTOR2		622	//P6.2 ACTAUTOR 选择执行器型式
	#define	SPRNG_Y2		631	//P6.3 SPRNG_Y2 设定执行器弹簧伸长时定位器返馈杆旋转方向
	#define	ADJ_MODE		641	//P6.4 ADJ_MODE 选择自动调整所需检测的项目
//P7
	#define	KP1					701	//P7.0 KP ? 开向比例系数调整	
	#define	KP2 				711	//P7.1 KP ? 关向比例系数调整
	#define	TV1 				721	//P7.2 TV ? 开向积分时间调整
	#define	TV2 				731	//P7.3 TV ? 关向积分时间调整
//P8
	#define	MIN_RGE8		801	//P8.0 MIN_RGE 阀位起始点电流值（默认为4mA)
	#define	MAX_RGE8		811	//P8.1 MAX_RGE 100%阀位电流值（默认为20mA)
	#define	ACTION1			821	//P8.2 ACTION 阀位正反方向选择（默认4mA 对应阀位 0%,正向
	#define	ACTION2			822	//P8.2 ACTION 阀位正反方向选择（默认4mA 对应阀位 0%,反向

#define Yes		1 // 参数项（用于执行参数设置）  
#define No		0 // 参数项（用于执行参数设置）  
//定义菜单操作需要的全局变量
extern u8 item_index;//当前菜单项索引


/**************************************************************************************************
*参数存储变量,全局变量
*/
//P1
extern u8	STANDARD_P10_ACTUATOR;	//Form1=1,Form2=2,Form3=3
extern u8	STANDARD_P11_AUTO_ADJ;	//启动自动整定程序
extern u8	STANDARD_P12_TOL_BAND;	//设定偏差带或死区
extern u8	STANDARD_P13_TEST;	//试验修改结果
//p2
extern u8	SETPOINT_P20_Signal;	//SETPOINT_P20_Signal=1.电流, 2.电压, 3.开关量
extern float SETPOINT_P21_MIN_RG;//全局变量,设定给定信号的最小值(预设为4mA)
extern float SETPOINT_P22_MAX_PRG;//全局变量,设定给定信号的最大值(预设为20mA)
extern u8	SETPOINT_P23_CHARACT;	//选择调节特性曲线
extern u8	SETPOINT_P24_ACTION;	//1,正向;2,反向;设定阀门正反作用方式
extern u8	SETPOINT_P25_SHUT_OFF;	//设定阀门开度阈值
extern u8	SETPOINT_P26_RAMP1;	//降低开向速度
extern u8	SETPOINT_P27_RAMP2;	//降低关向速度
//P3
extern u8	ACTUATOR_P30_MIN_RGE;	//调节曲线起始开度(预设为0%)
extern u8	ACTUATOR_P31_MAX_RGE;	//调节曲线终止开度(预设为100%)
extern u8	ACTUATOR_P32_ZERO_POS; //1,正向;2,逆向;起始点方向设置(预设为全关即返馈杆逆时针方向)
//P4
extern u8	MESSAGES_P40_TIME_OUT; //定位超时
extern u8	MESSAGES_P41_POS_SW1; //第一位置信号设置点
extern u8	MESSAGES_P42_POS_SW2; //第二位置信号设置点
extern u8	MESSAGES_P43_SW1_ACTV; //高于或低于第一位置信号时有效
extern u8	MESSAGES_P44_SW2_ACTV; //高于或低于第二位置信号时有效
//P5
extern u8	ALARMS_P50_LEACKAGE; //启动执行器气缸泄漏报警
extern u8	ALARMS_P51_SP_RGE; //启动给定信号超限报警
extern u8	ALARMS_P52_SENS_RGE; //启动零点漂移报警
extern u8	ALARMS_P53_CTRLER; //启动远方控制被切换报警
extern u8	ALARMS_P54_TIME_OUT; //启动定位超时报警
extern u8	ALARMS_P55_STRK_CTR; //启动调节行程超限报警
extern u8	ALARMS_P56_TRAVEL; //启动总行程超限报警
//P6
extern float	MAN_ADJ_P60_MIN_VR; //手动设置阀门全关位置
extern float	MAN_ADJ_P61_MAX_VR; //手动设置阀门全开位置
extern u8	MAN_ADJ_P62_ACTAUTOR; //选择执行器型式
extern u8	MAN_ADJ_P63_SPRNG_Y2; //1,正向;2,反向;设定执行器弹簧伸长时定位器返馈杆旋转方向
extern u8	MAN_ADJ_P64_ADJ_MODE; //选择自动调整所需检测的项目
//P7
extern u8	CTRL_PAR_P70_KP1; //开向比例系数调整
extern u8	CTRL_PAR_P71_KP2; //关向比例系数调整
extern u8	CTRL_PAR_P72_TV1; //开向积分时间调整
extern u8	CTRL_PAR_P73_TV2; //关向积分时间调整
//P8
extern float	ANLGOUT_P80_MIN_RGE;//阀位起始点电流值（默认为4mA)
extern float	ANLGOUT_P81_MAX_RGE;//100%阀位电流值（默认为20mA)
extern u8	ANLG_OUT_P82_ACTION; //1,正向;2,反向;阀位正反方向选择（默认4mA 对应阀位 0%）
extern u8 Level;

extern vu16 AD_Value[];//用来存放ADC转换结果，也是DMA的目标地址











typedef void (*MENU_FUN)(const char *,u16 *);
/*************** 
 * 菜单结构 
 * 一个数组既代表一级菜单，数组中的一个元素就是一个菜单项，就是一个单独的结构体， 
 * 数组中的第一个元素中的num值很重要，表示本级菜单具有多少个菜单项。 
 * 
 * uint8_t num 本级菜单数量，必须在第一项中设置正确的菜单项数量 
 * u8 Higher_Menu_Level;上级菜单级
 * u8 Current_Menu_Level;当前菜单级
 * char* label 菜单文本 
 * uint8_t type 此项类型，参考宏定义 
 * MENU_CALLBACK CallBack;  指向动作的函数指针，此项要执行的具体动作函数 
 * u16 action 向动作函数传递的动作参数
 * u16 ActionAssociation  动作关联，指向多级并行控制命令时只能是有一个指令时
 * mymenu* next 下一级菜单，只需在菜单的第一项设置，其他项置空（NULL）即可 
 * mymenu* prev 上一级菜单，同上 
 **************/ 
struct MenuItem//结构体类型定义//定义一个菜单 
{ 
	uint8_t num;			//本级菜单数量
	u8 Higher_Menu_Level;//上级菜单级
	u8 Current_Menu_Level;//当前菜单级
	char *title;			//级菜单标题
	char *label;			//菜单项文本
	uint8_t type;			//参考宏定义
	MENU_FUN Fun;	//指向动作的函数指针
	u16 action;//向动作函数传递的动作参数
	u16 ActionAssociation;//动作关联，指向多级并行控制命令时只能是有一个指令时
	struct MenuItem *next;	//下一级菜单
	struct MenuItem *prev;	//上一级菜单
};

void	UpOneLevel(const char *Text, u16 *parameter);//返回上一级
void DispCurrentMenu(void);//绘制当前菜单项
void Associated_Action(void);//动作关联函数,用来关闭其他启动项
void CancelOROK(const char *Text, u16 *parameter);//动作
void CurrentValue(const char *Text,u16 *parameter);
void	ParameterAssignment(u16 parameter,u16 value);
void ValvePosition_P6(const char *Text,u16 *parameter);//阀门位置
u8 MenuOption(void);
void Initial(void);
void LOGODisplay(void);

#endif


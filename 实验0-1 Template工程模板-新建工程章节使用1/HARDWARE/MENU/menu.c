#include "menu.h"
#include "LCD_ZK.H"
#include "zk.h"
#include "delay.h"
#include "key.h"
#include "timer3.h"
#include "usart.h"

/**************************************************************************************************
*参数存储变量,全局变量
*/
//P1
	u8	STANDARD_P10_ACTUATOR=0;	//Form1=1,Form2=2,Form3=3
	u8	STANDARD_P11_AUTO_ADJ=0;	//启动自动整定程序
	u8	STANDARD_P12_TOL_BAND=0;	//设定偏差带或死区
	u8	STANDARD_P13_TEST=0;	//试验修改结果
//p2
	u8	SETPOINT_P20_Signal=0;	//SETPOINT_P20_Signal=1.电流, 2.电压, 3.开关量
	float SETPOINT_P21_MIN_RGE=4.0;//全局变量,设定给定信号的最小值(预设为4mA)
	float SETPOINT_P22_MAX_PRG=20.0;//全局变量,设定给定信号的最大值(预设为20mA)
	u8	SETPOINT_P23_CHARACT=0;	//选择调节特性曲线
	u8	SETPOINT_P24_ACTION=0;	//1,正向;2,反向;设定阀门正反作用方式
	u8	SETPOINT_P25_SHUT_OFF=0;	//设定阀门开度阈值
	u8	SETPOINT_P26_RAMP1=0;	//降低开向速度
	u8	SETPOINT_P27_RAMP2=0;	//降低关向速度
//P3
	u8	ACTUATOR_P30_MIN_RGE=0;	//调节曲线起始开度(预设为0%)
	u8	ACTUATOR_P31_MAX_RGE=0;	//调节曲线终止开度(预设为100%)
	u8	ACTUATOR_P32_ZERO_POS=2; //1,正向;2,逆向;起始点方向设置(预设为全关即返馈杆逆时针方向)
//P4
	u8	MESSAGES_P40_TIME_OUT=0; //定位超时
	u8	MESSAGES_P41_POS_SW1=0; //第一位置信号设置点
	u8	MESSAGES_P42_POS_SW2=0; //第二位置信号设置点
	u8	MESSAGES_P43_SW1_ACTV=0; //高于或低于第一位置信号时有效
	u8	MESSAGES_P44_SW2_ACTV=0; //高于或低于第二位置信号时有效
//P5
	u8	ALARMS_P50_LEACKAGE=0; //启动执行器气缸泄漏报警
	u8	ALARMS_P51_SP_RGE=0; //启动给定信号超限报警
	u8	ALARMS_P52_SENS_RGE=0; //启动零点漂移报警
	u8	ALARMS_P53_CTRLER=0; //启动远方控制被切换报警
	u8	ALARMS_P54_TIME_OUT=0; //启动定位超时报警
	u8	ALARMS_P55_STRK_CTR=0; //启动调节行程超限报警
	u8	ALARMS_P56_TRAVEL=0; //启动总行程超限报警
//P6
	float	MAN_ADJ_P60_MIN_VR=100.0; //手动设置阀门全关位置
	float	MAN_ADJ_P61_MAX_VR=100.0; //手动设置阀门全开位置
	u8	MAN_ADJ_P62_ACTAUTOR=0; //选择执行器型式
	u8	MAN_ADJ_P63_SPRNG_Y2=0; //1,正向;2,反向;设定执行器弹簧伸长时定位器返馈杆旋转方向
	u8	MAN_ADJ_P64_ADJ_MODE=0; //选择自动调整所需检测的项目
//P7
	u8	CTRL_PAR_P70_KP1=0; //开向比例系数调整
	u8	CTRL_PAR_P71_KP2=0; //关向比例系数调整
	u8	CTRL_PAR_P72_TV1=0; //开向积分时间调整
	u8	CTRL_PAR_P73_TV2=0; //关向积分时间调整
//P8
	float	ANLGOUT_P80_MIN_RGE=4.0;//阀位起始点电流值（默认为4mA)
	float	ANLGOUT_P81_MAX_RGE=20.0;//100%阀位电流值（默认为20mA)
	u8	ANLG_OUT_P82_ACTION=0; //1,正向;2,反向;阀位正反方向选择（默认4mA 对应阀位 0%）
u8 Level=0;
/**
 * NULL		0
 * 菜单最大显示行数: MENU_MAX_ROW	5
 * 定义菜单项类型
 * 		MENU_SUBMENU	101		具有子菜单的菜单项 
 *   	MENU_PARAM		102		参数项（用于执行参数设置）
 */
/**
 * 菜单结构 
 * 一个数组既代表一级菜单，数组中的一个元素就是一个菜单项，就是一个单独的结构体， 
 * 数组中的第一个元素中的num值很重要，表示本级菜单具有多少个菜单项。 
 * 
 * 		uint8_t num 本级菜单数量，必须在第一项中设置正确的菜单项数量 
 * 		char *title	级菜单标题
 *   	char* label 菜单文本 
 *    	uint8_t type 此项类型，参考宏定义 
 *     	MENU_CALLBACK CallBack;  指向动作的函数指针，此项要执行的具体动作函数 
 *     	mymenu* next 下一级菜单，只需在菜单的第一项设置，其他项置空（NULL）即可 
 *      mymenu* prev 上一级菜单，同上 
*/ 
//结构体声明 
struct MenuItem menu_main[12];//1级菜单,主菜单
//第2级菜单
struct MenuItem menu_P1_Display_Mode[5];//显示模式Display Mode
struct MenuItem menu_P2_Input_Signal[9];//输入信号Input Signal
struct MenuItem menu_P3_Outout_Signal[7];//输出信号Outout Signal
struct MenuItem menu_P4_Action_Mode[6];//作用形式Action Mode
struct MenuItem menu_P5_Action_Manner[8];//作用方式Action Manner
struct MenuItem menu_P6_Adjust_Mode[6];//整定模式Adjust Mode 
struct MenuItem menu_P7_Opening_Mode[12];//开度模式Opening mode
struct MenuItem menu_P8_IQ[8];//信息查询Information Query
struct MenuItem menu_P9_Restore_Factory_Value[3];//恢复出厂值Restore_Factory_Value
struct MenuItem menu_P10_Error_Message[5];//错误信息Error_Message
struct MenuItem menu_P11_Calibration[3];//压力标定,温度标定
struct MenuItem menu_P12_Reserved[3];//预留菜单
//第3级菜单
//P1菜单
	struct MenuItem menu_P1_0ACTUATOR[3];//P1.0 ACTUATOR,定义定位器安装形式
//	struct MenuItem menu_P1_1AUTO_ADJ[2];//P1.1 AUTO_ADJ 启动自动整定程序
	struct MenuItem menu_P1_2TOL_BAND[2];//P1.2 TOL_BAND 设定偏差带或死区
	struct MenuItem menu_P1_3TEST[2];//P1.3 TEST 试验修改结果
//	struct MenuItem menu_P1_4EXIT[2];//P1.4 EXIT 退出到运行操作级
//P2菜单
	struct MenuItem menu_P2_0SignalSystem[3];//P2.0 信号制式 1.电流 2.电压 3.开关量
	struct MenuItem menu_P2_1MIN_RGE[3];//P2.1 MIN_RGE 设定给定信号的最小值(预设为4mA)	,****不确定
	struct MenuItem menu_P2_2MAX_PRG[3];//P2.2 MAX_PRG 设定给定信号的最大值(预设为20mA)	,****不确定
	struct MenuItem menu_P2_3CHARACT[3];//P2.3 CHARACT 选择调节特性曲线	,****不确定
	struct MenuItem menu_P2_4ACTION[2];//P2.4 ACTION 设定阀门正反作用方式	,****不确定
	struct MenuItem menu_P2_5SHUT_OFF[3];//P2.5 SHUT-OFF 设定阀门开度阈值	,****不确定
	struct MenuItem menu_P2_6RAMP1[3];//P2.6 RAMP? 降低开向速度	,****不确定
	struct MenuItem menu_P2_7RAMP2[3];//P2.7 RAMP? 降低关向速度	,****不确定
//	struct MenuItem menu_P2_8EXIT[3];//P2.8 EXIT 退出到运行操作级
//P3菜单
	struct MenuItem menu_P3_0MIN_RGE[4];//P3.0 MIN_RGE 调节曲线起始开度(预设为0%)	,****不确定
	struct MenuItem menu_P3_1MAX_RGE[4];//P3.1 MAX_RGE 调节曲线终止开度(预设为100%)	,****不确定
	struct MenuItem menu_P3_2ZERO_POS[4];//P3.2 ZERO_POS 起始点方向设置(预设为全关即返馈杆逆时针方向)	,****不确定
//	struct MenuItem menu_P3_3EXIT[4];//P3.3 EXIT 退出到运行操作级
//P4菜单
	struct MenuItem menu_P4_0TIME_OUT[6];//P4.0 TIME _OUT 定位超时	,****不确定
	struct MenuItem menu_P4_1POS_SW1[6];//P4.1 POS_SW1 第一位置信号设置点	,****不确定
	struct MenuItem menu_P4_2POS_SW2[6];//P4.2 POS_SW2 第二位置信号设置点	,****不确定
	struct MenuItem menu_P4_3SW1_ACTV[6];//P4.3 SW1_ACTV 高于或低于第一位置信号时有效
	struct MenuItem menu_P4_4SW2_ACTV[6];//P4.4 SW2_ACTV 高于或低于第二位置信号时有效
//	struct MenuItem menu_P4_5EXIT[6];//P4.5 EXIT 退出到运行操作级
//P5菜单
	struct MenuItem menu_P5_0LEACKAGE[2];//P5.0 LEACKAGE 启动执行器气缸泄漏报警  	,1.确认;2.取消
	struct MenuItem menu_P5_1SP_RGE[2];//P5.1 SP_RGE 启动给定信号超限报警  	,1.确认;2.取消
	struct MenuItem menu_P5_2SENS_RGE[2];//P5.2 SENS_RGE 启动零点漂移报警  	,1.确认;2.取消
	struct MenuItem menu_P5_3CTRLER[2];//P5.3 CTRLER 启动远方控制被切换报警  	,1.确认;2.取消
	struct MenuItem menu_P5_4TIME_OUT[2];//P5.4 TIME-OUT 启动定位超时报警  	,1.确认;2.取消
	struct MenuItem menu_P5_5STRK_CTR[2];//P5.5 STRK_CTR 启动调节行程超限报警  	,1.确认;2.取消
	struct MenuItem menu_P5_6TRAVEL[2];//P5.6 TRAVEL 启动总行程超限报警  	,1.确认;2.取消
	struct MenuItem menu_P5_7EXIT[2];//P5.7 EXIT 退出到运行操作级  	,1.确认;2.取消
//P6菜单
	struct MenuItem menu_P6_0MIN_VR[2];//P6.0 MIN_VR 手动设置阀门全关位置				,****不确定
	struct MenuItem menu_P6_1MAX_VR[2];//P6.1 MAX_VR 手动设置阀门全开位置				,****不确定
	struct MenuItem menu_P6_2ACTAUTOR[2];//P6.2 ACTAUTOR 选择执行器型式				,****不确定
	struct MenuItem menu_P6_3SPRNG_Y2[6];//P6.3 SPRNG_Y2 设定执行器弹簧伸长时定位器返馈杆旋转方向				,****不确定
	struct MenuItem menu_P6_4ADJ_MODE[6];//P6.4 ADJ_MODE 选择自动调整所需检测的项目				,****不确定
	struct MenuItem menu_P6_5EXIT[2];//P6.5 EXIT 退出到运行操作级
//P7菜单
	struct MenuItem menu_P7_0KP1[2];//P7.0 KP∧ 开向比例系数调整				,****不确定
	struct MenuItem menu_P7_1KP2[2];//P7.1 KP∨ 关向比例系数调整				,****不确定
	struct MenuItem menu_P7_2TV1[2];//P7.2 TV∧ 开向积分时间调整				,****不确定
	struct MenuItem menu_P7_3TV2[2];//P7.3 TV∨ 关向积分时间调整				,****不确定
	struct MenuItem menu_P7_11EXIT[2];//P7.11 EXIT 退出到运行操作级
//P8菜单
	struct MenuItem menu_P8_0MIN_RGE[2];//P8.0 MIN_RGE 阀位起始点电流值（默认为4mA)				,****不确定
	struct MenuItem menu_P8_1MAX_RGE[2];//P8.1 MAX_RGE 100%阀位电流值（默认为20mA)				,****不确定
	struct MenuItem menu_P8_2ACTION[2];//P8.2 ACTION 阀位正反方向选择（默认4mA 对应阀位 0%）				,****不确定
	struct MenuItem menu_P8_3ALARM[2];//				,****不确定
	struct MenuItem menu_P8_4TEST[2];//				,****不确定
	struct MenuItem menu_P8_5EXIT[2];//P8.5 EXIT 退出到运行操作级				,****不确定

struct MenuItem ConfirmOrCancel[2];


//定义菜单操作需要的全局变量
struct MenuItem *cur_item = menu_main;//初始化当前菜单为第一级(main_menu)
struct MenuItem *prev_item = NULL;	//初始化上一级菜单为空
u8 item_index = 0;//当前菜单项索引

/*****************************************************************************************************************************************************************************************************/
//结构体初始化//菜单定义,在这里将每一个菜单的关联设置好
/**
*一级菜单
*/
struct MenuItem menu_main[12] = // 第1级菜单,主菜单
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本					参考宏定义	 		动作函数				动作参数		动作关联常数		下一级菜单											上一级菜单
			{12, 		0,				0,					"菜单：        >>",		"1.F_01      ",	MENU_SUBMENU, NULL,		 			NULL,			NULL,					menu_P1_Display_Mode, 				NULL},//显示模式
			{12, 		0,				1,					"",										"2.F_02      ",	MENU_SUBMENU, NULL,		 			NULL,			NULL,					menu_P2_Input_Signal, 				NULL},//输入信号
			{12, 		0,				2,					"",										"3.F_03      ",	MENU_SUBMENU, NULL,		 			NULL,			NULL,					menu_P3_Outout_Signal,				NULL},//输出信号
			{12, 		0,				3,					"",										"4.F_04      ",	MENU_SUBMENU, NULL,		 			NULL,			NULL,					menu_P4_Action_Mode,					NULL},//作用形式
			{12, 		0,				4,					"",										"5.F_05      ", MENU_SUBMENU, NULL,		 			NULL,			NULL,					menu_P5_Action_Manner,				NULL},//作用方式
			{12, 		0,				5,					"",										"6.F_06      ", MENU_SUBMENU, NULL,		 			NULL,			NULL,					menu_P6_Adjust_Mode,					NULL},//整定模式 
			{12,		0,				6, 					"",										"7.F_07      ", MENU_SUBMENU, NULL,					NULL,			NULL,					menu_P7_Opening_Mode,					NULL},//开度模式
			{12, 		0,				7,					"",										"8.F_08      ", MENU_SUBMENU,	NULL,		 			NULL,			NULL,					menu_P8_IQ,										NULL},//信息查询
			{12, 		0,				8,					"",										"9.F_09      ", MENU_SUBMENU,	NULL,		 			NULL,			NULL,					menu_P9_Restore_Factory_Value,NULL},//恢复出厂值
			{12, 		0,				9,					"",										"10.F_10     ", MENU_SUBMENU,	NULL,		 			NULL,			NULL,					menu_P10_Error_Message,				NULL},//错误信息
			{12, 		0,				10,					"",										"11.F_11     ", MENU_SUBMENU,	NULL,		 			NULL,			NULL,					menu_P11_Calibration,					NULL},//预留菜单
			{12, 		0,				11,					"",										"12.F_12     ", MENU_SUBMENU,	NULL,		 			NULL,			NULL,					menu_P12_Reserved,						NULL},//预留菜单
}; 
/****
***	2级菜单
***/
struct MenuItem menu_P1_Display_Mode[5] = // 第2级菜单,P1	显示模式Display Mode
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本		   			参考宏定义	 		动作函数			动作参数		动作关联常数		  				下一级菜单		上一级菜单
			{4,			0,			 	0,					"1.Display Mode  ",		"1.百分比%    ",		MENU_PARAM,		CancelOROK, START,			ACTION_ASSOCIATION,			NULL, 		menu_main},//不确定 子 级菜单是什么
			{4,			0, 				1,					"",										"2.电流mA     ",	MENU_PARAM, 	CancelOROK,	CLOSE,			ACTION_ASSOCIATION,			NULL, 		menu_main},
			{4,			0,	 			2,					"",										"3.电压V      ",	MENU_PARAM, 	CancelOROK, CLOSE,			ACTION_ASSOCIATION,			NULL, 		menu_main},//不确定 子 级菜单是什么
			{4,			0, 				3,					"",										"4.EXIT      ",		MENU_PARAM,		UpOneLevel,	NULL,				NULL,										NULL, 		menu_main},
};
struct MenuItem menu_P2_Input_Signal[9] = // 第2级菜单,P2	输入信号Input Signal
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数			动作参数			动作关联常数	  				下一级菜单		上一级菜单
			{5,			1, 				0,					"2.Input Signal  ",		"1.0-20mA     ",	MENU_PARAM,		CancelOROK, START, 			ACTION_ASSOCIATION, 	NULL,				menu_main},//不确定 子 级菜单是什么
			{5,			1, 				1,					"",										"2.4-20mA     ",	MENU_PARAM, 	CancelOROK,	CLOSE, 			ACTION_ASSOCIATION, 	NULL, 			menu_main},//不确定 子 级菜单是什么
			{5,			1, 				2,					"",										"3.0-5V       ",	MENU_PARAM, 	CancelOROK,	CLOSE, 			ACTION_ASSOCIATION, 	NULL, 			menu_main},//不确定 子 级菜单是什么
			{5,			1, 				3,					"",										"4.0-10V      ",	MENU_PARAM, 	CancelOROK,	CLOSE, 			ACTION_ASSOCIATION,		NULL, 			menu_main},//不确定 子 级菜单是什么
			{5,			1, 				4,					"",										"5.EXIT       ",	MENU_PARAM, 	UpOneLevel,	NULL, 			NULL, 								NULL, 			menu_main},
};
struct MenuItem menu_P3_Outout_Signal[7] = // 第2级菜单,P3	输出信号Outout Signal
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数			动作参数		动作关联常数							下一级菜单		上一级菜单
			{7,				2, 			0,					"3.Outout Signal ",		"1.0-20mA     ",	MENU_PARAM, 	CancelOROK, START,  		ACTION_ASSOCIATION,  	NULL, 			menu_main},//不确定 子 级菜单是什么
			{7,				2,			1,					"",										"2.4-20mA     ",	MENU_PARAM, 	CancelOROK, CLOSE,  		ACTION_ASSOCIATION,  	NULL, 			menu_main},//不确定 子 级菜单是什么
			{7,				2, 			2,					"",										"3.0-5V       ",	MENU_PARAM, 	CancelOROK,	CLOSE,  		ACTION_ASSOCIATION,  	NULL, 			menu_main},//不确定 子 级菜单是什么
			{7,				2, 			3,					"",										"4.0-5V       ",	MENU_PARAM, 	CancelOROK,	CLOSE,  		ACTION_ASSOCIATION,  	NULL, 			menu_main},//不确定 子 级菜单是什么
			{7,				2, 			4,					"",										"5.PNP        ",	MENU_PARAM, 	CancelOROK,	CLOSE,  		ACTION_ASSOCIATION, 	NULL, 			menu_main},//不确定 子 级菜单是什么
			{7,				2, 			5,					"",										"6.NPN        ",	MENU_PARAM, 	CancelOROK,	CLOSE,  		ACTION_ASSOCIATION, 	NULL, 			menu_main},//不确定 子 级菜单是什么
			{7,				2, 			6,					"",										"7.EXIT       ",	MENU_PARAM, 	UpOneLevel,	NULL,				NULL,  								NULL, 			menu_main},//不确定 子 级菜单是什么	
};
struct MenuItem menu_P4_Action_Mode[6] = // 第2级菜单,P4	作用形式Action Mode
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数			动作参数		动作关联常数							下一级菜单		上一级菜单
			{2,				3, 			0,					"4.Action Mode   ",		"1.单作用     ",		MENU_PARAM, 	CancelOROK,	START,  		ACTION_ASSOCIATION,  	NULL, 			menu_main},//不确定 子 级菜单是什么
			{2,				3, 			1,					"",										"2.双作用     ",		MENU_PARAM,	 	CancelOROK, CLOSE,  		ACTION_ASSOCIATION,  	NULL, 			menu_main},//不确定 子 级菜单是什么					
			{2,				3, 			2,					"",										"3.EXIT       ",	MENU_PARAM, 	UpOneLevel,	NULL, 			NULL,  								NULL, 			menu_main},//不确定 子 级菜单是什么			
};
struct MenuItem menu_P5_Action_Manner[8] = // 第2级菜单,P5	作用方式Action Manner
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数						下一级菜单		上一级菜单
			{2,				4, 			0,					"5.Action Manner ",		"1.正作用     ",		MENU_PARAM, 	CancelOROK, 	START,  	ACTION_ASSOCIATION,  	NULL,				menu_main},//不确定 子 级菜单是什么
			{2,				4, 			1,					"",										"2.反作用     ",		MENU_PARAM, 	CancelOROK, 	CLOSE,  	ACTION_ASSOCIATION,  	NULL,				menu_main},//不确定 子 级菜单是什么
			{2,				4, 			2,					"",										"3.EXIT       ",	MENU_PARAM, 	UpOneLevel,		NULL,			NULL,  								NULL, 			menu_main},//不确定 子 级菜单是什么
};
struct MenuItem menu_P6_Adjust_Mode[6] = // 第2级菜单,P6	 整定模式Adjust Mode
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数						下一级菜单		上一级菜单
			{2,				5, 			0,					"6.Adjust Mode   ",		"1.自动       ",	MENU_PARAM, 	CancelOROK, 	START,  	ACTION_ASSOCIATION,		NULL,				menu_main},//不确定 子 级菜单是什么
			{2,				5, 			1,					"",										"2.手动       ",	MENU_PARAM, 	CancelOROK, 	CLOSE,  	ACTION_ASSOCIATION,		NULL,				menu_main},//不确定 子 级菜单是什么
			{2,				5, 			2,					"",										"3.EXIT       ",	MENU_PARAM, 	UpOneLevel,		NULL,			NULL,									NULL,				menu_main},//不确定 子 级菜单是什么
};
struct MenuItem menu_P7_Opening_Mode[12] = // 第2级菜单,P7	控制参数
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数						下一级菜单		上一级菜单
			{7,				6, 			0,					"7.Opening mode  ",		"1.线性       ",	MENU_PARAM, 	CancelOROK, 	START,  	ACTION_ASSOCIATION,  	NULL,				menu_main},//不确定 子 级菜单是什么
			{7,				6, 			1,					"",										"2.1:25       ",	MENU_PARAM, 	CancelOROK,		CLOSE,  	ACTION_ASSOCIATION,  	NULL,				menu_main},//不确定 子 级菜单是什么
			{7,				6, 			2,					"",										"3.1:30       ",	MENU_PARAM, 	CancelOROK, 	CLOSE,  	ACTION_ASSOCIATION, 	NULL,				menu_main},//不确定 子 级菜单是什么
			{7,				6, 			3,					"",										"4.1:40       ",	MENU_PARAM, 	CancelOROK, 	CLOSE,  	ACTION_ASSOCIATION,  	NULL,				menu_main},//不确定 子 级菜单是什么
			{7,				6, 			4,					"",										"5.1:50       ",	MENU_PARAM, 	CancelOROK, 	CLOSE,  	ACTION_ASSOCIATION,  	NULL,				menu_main},//不确定 子 级菜单是什么
			{7,				6, 			5,					"",										"6.自定义     ",		MENU_PARAM, 	CancelOROK, 	CLOSE,  	ACTION_ASSOCIATION,		NULL,				menu_main},//不确定 子 级菜单是什么
			{7,				6, 			6,					"",										"7.EXIT      ",		MENU_PARAM, 	UpOneLevel, 	NULL,			NULL,									NULL,				menu_main},//不确定 子 级菜单是什么
};
struct MenuItem menu_P8_IQ[8] = // 第2级菜单,P8	模拟信号输出
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数			下一级菜单		上一级菜单
			{8,			7,			 	0,					"8.IQ            ",		"1.产品型号    ",	MENU_SUBMENU,	NULL, 				NULL,			NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{8,			7, 				1,					"",										"2.S/N号      ",	MENU_SUBMENU,	NULL, 				NULL, 		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{8,			7, 				2,					"",										"3.程序版本号  ",	MENU_SUBMENU, NULL, 				NULL,  		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{8,			7, 				3,					"",										"4.使用时间    ",	MENU_SUBMENU, NULL, 				NULL,  		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{8,			7, 				4,					"",										"5.全开时间    ",	MENU_SUBMENU, NULL, 				NULL,  		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{8,			7, 				5,					"",										"6.全关时间    ",	MENU_SUBMENU, NULL, 				NULL,  		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{8,			7, 				6,					"",										"7.错误警告    ",	MENU_SUBMENU, NULL, 				NULL,  		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{8,			7, 				7,					"",										"8.EXIT       ",	MENU_PARAM, 	UpOneLevel, 	NULL,			NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
};
struct MenuItem menu_P9_Restore_Factory_Value[3] = // 第2级菜单,P9		恢复出厂值Restore_Factory_Value
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数			下一级菜单		上一级菜单
			{3,			8,			 	0,					"9.Restore       ",		"1.NRESET     ",	MENU_PARAM,		CancelOROK, 	CLOSE,		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{3,			8, 				1,					"",										"2.RESET      ",	MENU_PARAM,		CancelOROK, 	CLOSE, 		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{3,			8,			 	2,					"",										"3.EXIT       ",	MENU_PARAM,		UpOneLevel, 	NULL,			NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
};
struct MenuItem menu_P10_Error_Message[5] = // 第2级菜单,P10		错误信息Error_Message
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数			下一级菜单		上一级菜单
			{5,			9,			 	0,					"10.Error Message",		"1.ER1        ",	MENU_SUBMENU,	NULL, 				NULL,			NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{5,			9, 				1,					"",										"2.ER2        ",	MENU_SUBMENU,	NULL, 				NULL, 		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{5,			9,			 	2,					"",										"3.ER3        ",	MENU_SUBMENU,	NULL, 				NULL,			NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{5,			9, 				3,					"",										"4.ER4        ",	MENU_SUBMENU,	NULL, 				NULL, 		NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
			{5,			9,			 	4,					"",										"5.EXIT       ",	MENU_PARAM,		UpOneLevel, 	NULL,			NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
	
};
struct MenuItem menu_P11_Calibration[3] = // 第2级菜单,P11		压力标定,温度标定
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数			下一级菜单		上一级菜单
			{1,			10,			 	0,					"11.Reserved menu",		"1.EXIT       ",	MENU_PARAM,		UpOneLevel, 	NULL,			NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
	
};
struct MenuItem menu_P12_Reserved[3] = // 第2级菜单,P12		预留菜单
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数			下一级菜单		上一级菜单
			{1,			11,			 	0,					"12.Reserved menu",		"1.EXIT       ",	MENU_PARAM,		UpOneLevel, 	NULL,			NULL,  					NULL,				menu_main},//不确定 子 级菜单是什么
};
/********
*****	3级菜单
*****/
////p1
	struct MenuItem menu_P1_0ACTUATOR[3] = // 第	3 级菜单,P1_0	定义定位器安装形式
	{
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数			下一级菜单						上一级菜单
				{3,				0, 			0,					"1_1.ACTUATOR  >>",	"1.Form 1     ",	MENU_PARAM, 	CancelOROK, 	Form1, 	 		NULL,  				NULL,								menu_P1_Display_Mode},//型式1
				{3,				0, 			1,					"",									"2.Form 2     ",	MENU_PARAM, 	CancelOROK, 	Form2,  		NULL,  				NULL,								menu_P1_Display_Mode},//型式2
				{3,				0, 			2,					"",									"3.Form 3     ",	MENU_PARAM, 	CancelOROK, 	Form3,  		NULL,  				NULL,								menu_P1_Display_Mode},//型式3
	};

////p2
	struct MenuItem menu_P2_0SignalSystem[3] = // 第	3 级菜单,P2_0	信号制式
	{		
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数			下一级菜单						上一级菜单
				{3,				0, 			0,					"2_1.Signal    >>",	"1.Current    ",	MENU_PARAM, 	CancelOROK, 	CURRENT, 	 	NULL,  				NULL,								menu_P2_Input_Signal},//电流
				{3,				0, 			1,					"",									"2.Voltage    ",	MENU_PARAM, 	CancelOROK, 	VOLTAGE,  	NULL,  				NULL,								menu_P2_Input_Signal},//电压
				{3,				0, 			2,					"",									"3.Switch     ",	MENU_PARAM, 	CancelOROK, 	SWITCH,  		NULL,  				NULL,								menu_P2_Input_Signal},//开关量
	};
	struct MenuItem menu_P2_4ACTION[2] = // 第	3 级菜单,P2_4	设定阀门正反作用方式
	{	
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数				下一级菜单						上一级菜单
				{2,				4, 			0,					"2_4.ACTION   >>",	"1.Positive   ",	MENU_PARAM, 	CancelOROK, 	POSITIVE,  	NULL,  					NULL,								menu_P2_Input_Signal},//正向
				{2,				4, 			1,					"",									"2.Reverse    ",	MENU_PARAM, 	CancelOROK, 	REVERSE,  	NULL,  					NULL,								menu_P2_Input_Signal},//反向
	};	
////p6
	struct MenuItem menu_P6_2ACTAUTOR[2] = // 第	3 级菜单,P6_2	选择执行器型式
	{
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数				下一级菜单						上一级菜单
				{2,				4, 			0,					"6_2.ACTAUTOR >>",	"1.Form 1      ",	MENU_PARAM, 	CancelOROK, 	ACTAUTOR1, 	NULL,  					NULL,								menu_P6_Adjust_Mode},//型式1	
				{2,				4, 			0,					"",									"2.Form 2      ",	MENU_PARAM, 	CancelOROK, 	ACTAUTOR2,	NULL,  					NULL,								menu_P6_Adjust_Mode},//型式2
	};
////p8
	struct MenuItem menu_P8_2ACTION[2] = // 第	3 级菜单,P8_2	选择执行器型式	
	{
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作函数				动作参数			动作关联常数			下一级菜单						上一级菜单
				{2,				4, 			0,					"8_2.ACTION   >>",	"1.Positive    ",	MENU_PARAM, 	CancelOROK, 	ACTION1,			NULL,  					NULL,								menu_P8_IQ},//正向	
				{2,				4, 			0,					"",									"2.Reverse     ",	MENU_PARAM, 	CancelOROK, 	ACTION2,			NULL,  					NULL,								menu_P8_IQ},//反向
	};

struct MenuItem ConfirmOrCancel[2] = // 第3级菜单,确认或取消
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作函数				动作参数		动作关联常数			下一级菜单						上一级菜单
			{2,				2, 			0,					"",									"Cancel      ",		NULL,					UpOneLevel, 	NULL,				NULL,					NULL, 						menu_main},//取消
			{2,				2, 			1,					"",									"Confirm     ",		MENU_PARAM, 	UpOneLevel, 	NULL,				NULL,					NULL, 						menu_main},//确认
};	
/******************************************************************************************************************************************************************************************************
*动作函数
*/
/**
*返回上一级菜单
*@Text	上级菜单文本
*@parameter	动作参数
*/
void	UpOneLevel(const char *Text, u16 *parameter)
{
	item_index=cur_item[item_index].Higher_Menu_Level;//重置菜单项索引
	cur_item = prev_item;//设置上一级菜单为当前菜单 
	prev_item = cur_item[0].prev;//设置当前菜单的上一级菜单 
	DispCurrentMenu();
}

/**
*更新全局参数
*@parameter	各级控制页面的动作参数,
*@value	取消或确认
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
*动作关联函数
*因为有些动作指令是并行触发,只有一个有效,所以当触发一个后需要将其他的一些关闭
*/
void Associated_Action(void)
{
	u8 i;
	for(i=0; i<cur_item[item_index].num; i++)
	{
		if(cur_item[i].ActionAssociation==ACTION_ASSOCIATION)
		{
			if(cur_item[item_index].Current_Menu_Level==cur_item[i].Current_Menu_Level)
			{
				cur_item[i].action=START;
				
			}else 
			{
				cur_item[i].action=CLOSE;
			}
		}
	}
}
/**
*二次确定界面,防止误触
*@Text	[] ,上级菜单文本
*@parameter [] ,动作参数,全局变量
*{ParameterAssignment(parameter,value)},更改全局参数 
*/
void CancelOROK(const char *Text, u16 *parameter)
{
	u8 key=0;
	u16 value=*parameter;
	clear_screen();//清屏
	display_GB2312_string(0,1,(u8*)Text);
	display_GB2312_string(2,25,"Cancel      ");
	display_GB2312_string(4,25,"Confirm     ");
	display_GB2312_string(2,1,"□");//	□	■
	display_GB2312_string(4,1,"□");
	if(value==START)	display_GB2312_string(4,1,"■");
	else if(value==CLOSE)display_GB2312_string(2,1,"■");
	while(1)
	{
		key=KEY_Scan(0);//扫描按建
		switch(key)
		{
			case	UP_PRES:
						display_GB2312_string(2,1,"■");
						display_GB2312_string(4,1,"□");
						value=CLOSE;//关闭									
						break;
			case	DOWN_PRES:
						display_GB2312_string(2,1,"□");
						display_GB2312_string(4,1,"■");
						value=START;//开启
						break;
			case	OK_PRES:
//						if(value==START)	ParameterAssignment(*parameter,value);	
						SET_Sign=1;
						SET_LongPress=750;
						*parameter=value;
						Associated_Action();
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
*使用页面:P2.1,P2.2,P8.0,P8.1
*设定信号最大最小值，单位mA，每次设定最小变量为0.1mA
*@Text	[],显示本级菜单文本,在最顶行显示
*@parameter	[MIN_RGE],设定给定信号的最小值(预设为4mA)
*@parameter	[MAX_PRG],设定给定信号的最大值(预设为20mA)
*/
void CurrentValue(const char *Text,u16 *parameter)
{
	u16 value=0;
	u8 key=0;
	switch(*parameter)
	{
		case	MIN_RGE2:
					value=SETPOINT_P21_MIN_RGE*10;//将设定给定信号的最小值赋值给	parameter		(预设为4mA)
					break;
		case	MAX_PRG2:
					value=SETPOINT_P22_MAX_PRG*10;//将设定给定信号的最大值赋值给	parameter		(预设为20mA)
					break;
		case	MIN_RGE8:
					value=ANLGOUT_P80_MIN_RGE*10;//将阀位起始点电流值赋值给	parameter		（默认为4mA)
					break;
		case	MAX_RGE8:
					value=ANLGOUT_P81_MAX_RGE*10;//将100%阀位电流值赋值给	parameter		（默认为20mA)
					break;
		default:
					break;
	}
	clear_screen();//清屏
	display_GB2312_string(0,1,(u8*)Text);
	display_string_5x7(6,110,"mA");
	while(1)
	{
		key=KEY_Scan(3);//扫描按建
		switch(key)
		{
			case	UP_PRES:
						switch(*parameter)
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
						switch(*parameter)
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
						switch(*parameter)
						{
							case	MIN_RGE2:
										SETPOINT_P21_MIN_RGE=value;//将设定给定信号的最小值赋值给	parameter		(预设为4mA)
										SETPOINT_P21_MIN_RGE=SETPOINT_P21_MIN_RGE/10;
										break;
							case	MAX_PRG2:
										SETPOINT_P22_MAX_PRG=value;//将设定给定信号的最大值赋值给	parameter		(预设为20mA)
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
		if(ExitTimed==(600-1))	Initial();//回到初始页面
	}
}
/**
*使用页面P6.1,P6.2
*
*/
void ValvePosition_P6(const char *Text,u16 *parameter)
{
	u16 value=0;
	u8 key=0;
	switch(*parameter)
	{
		case	MIN_VR:
					value=MAN_ADJ_P60_MIN_VR*10;//将设定给定信号的最小值赋值给	parameter		(预设为4mA)
					break;
		case	MAX_VR:
					value=MAN_ADJ_P61_MAX_VR*10;//将设定给定信号的最大值赋值给	parameter		(预设为20mA)
					break;
		default:
					break;
	}
	clear_screen();//清屏
	display_GB2312_string(0,1,(u8*)Text);
	display_string_5x7(6,110,"%");
	while(1)
	{
		key=KEY_Scan(3);//扫描按建
		switch(key)
		{
			case	UP_PRES:
						switch(*parameter)
						{
							case	MIN_VR:
										if(value>=MAN_ADJ_P61_MAX_VR*10)	value=value;
										else	value++;
										break;
							case	MAX_VR:
										if(value>=100*10)	value=value;
										else	value++;
										break;
							case ADJ_MODE:
										
										break;
							default:
										break;
						}
						break;
			case	DOWN_PRES:
						switch(*parameter)
						{
							case	MIN_VR:
										if(value<=0*10)	value=value;
										else	value--;
										break;
							case	MAX_VR:
										if(value<=MAN_ADJ_P60_MIN_VR*10)	value=value;
										else	value--;
										break;
							default:
										break;
						}
						break;
			case	OK_PRES:
						switch(*parameter)
						{
							case	MIN_RGE2:
										MAN_ADJ_P60_MIN_VR=value;//将设定给定信号的最小值赋值给	parameter		(预设为4mA)
										MAN_ADJ_P60_MIN_VR=MAN_ADJ_P60_MIN_VR/10;
										break;
							case	MAX_PRG2:
										MAN_ADJ_P61_MAX_VR=value;//将设定给定信号的最大值赋值给	parameter		(预设为20mA)
										MAN_ADJ_P61_MAX_VR=MAN_ADJ_P61_MAX_VR/10;
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
		if(ExitTimed==(600-1))	Initial();//回到初始页面
	}
}
/// <summary>
/// 阀门自调整程序
/// </summary>
void ValvePosition_P6_ADJ_MODE()
{
    u16 ValvePositionAcquisition = 0;//采集阀门转动角度模拟量
    u16 delay = 100;//阀门开启延时
    u8 i = 0;
    u32 num = 0;//循环采集传感器数据集合
    u16 before = 0;//动作前采集的值
    u16 rear = 0;//动作后采集的值
    u8 difference = 0;//前后只差,如果大于设定值则记录
    u8 flag = 0;//零位/最大位标志

    while (1)
    {
        if (flag == 0)
        {
            for (i = 0; i < 10; i++)
            {
                num = num + AD_Value[0];
            }
            before = num / 10;
            TIM_CCxCmd(TIM4, TIM_Channel_3, TIM_CCx_Enable);
            TIM_CCxCmd(TIM4, TIM_Channel_4, TIM_CCx_Disable);
            TIM_SetCompare4(TIM3, 100);
            delay_ms(delay);
            TIM_CCxCmd(TIM4, TIM_Channel_3, TIM_CCx_Disable);
            TIM_CCxCmd(TIM4, TIM_Channel_4, TIM_CCx_Disable);
            for (i = 0; i < 10; i++)
            {
                num = num + AD_Value[0];
            }
            rear = num / 10;
            difference = before - rear;
            if (difference < 0) difference = -difference;
            if (difference < 10)
            {
                flag = flag;
            }
            else flag = 1;
        }
        TIM_CCxCmd(TIM4, TIM_Channel_3, TIM_CCx_Enable);
        TIM_CCxCmd(TIM4, TIM_Channel_4, TIM_CCx_Disable);
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);

        if (flag == 1)
        {
            for (i = 0; i < 10; i++)
            {
                num = num + AD_Value[0];
            }
            before = num / 10;
            TIM_CCxCmd(TIM4, TIM_Channel_3, TIM_CCx_Disable);
            TIM_CCxCmd(TIM4, TIM_Channel_4, TIM_CCx_Enable);
            TIM_SetCompare4(TIM4, 100);
            delay_ms(delay);
            TIM_CCxCmd(TIM4, TIM_Channel_3, TIM_CCx_Disable);
            TIM_CCxCmd(TIM4, TIM_Channel_4, TIM_CCx_Disable);
            for (i = 0; i < 10; i++)
            {
                num = num + AD_Value[0];
            }
            rear = num / 10;
            difference = before - rear;
            if (difference < 0) difference = -difference;
            if (difference < 10)
            {
                flag = flag;
            }
            else break;
        }

    }
}


/**
*绘制菜单文本项
*/
void DispCurrentMenu(void)//绘制当前菜单项
{
	
	u8 menu_num = cur_item[0].num;//获取当前菜单的项目数量
	u8 i, num = menu_num>MENU_MAX_ROW ? MENU_MAX_ROW : menu_num;//绘制数量不能超过每一屏的最大绘制数量
	
	if(item_index>=menu_num)//菜单项上下选择是否越界 
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
	clear_screen();//清屏
	display_GB2312_string(0,1,(u8*)cur_item[0].title);
	if(item_index>=MENU_MAX_ROW)
	{
		for (i=0; i<num; i++)//绘制某一级菜单 
		{
			display_GB2312_string((i+1)*2,25,(u8 *)cur_item[i+1+(item_index-MENU_MAX_ROW)].label);
			display_GB2312_string((i+1)*2,1,"□");
		}
		display_GB2312_string(6,1,"■");
	}else
	{
		for (i=0; i<num; i++)//绘制某一级菜单 
		{
			display_GB2312_string((i+1)*2,25,(u8 *)cur_item[i].label);
			display_GB2312_string((i+1)*2,1,"□");
		}
		display_GB2312_string((item_index+1)*2,1,"■");
	}
}
/**
*选择菜单,进入各级菜单选项
*/
u8 MenuOption(void)
{
	u8 key=0;
	while(1)
	{
		if(SET_Sign==1)//如果按键一直响应,则进入菜单栏
		{
			if(SET_LongPress==750)//响应时间为2s
			{
				SET_Sign=0;
				DispCurrentMenu();
				while(1)//进入菜单栏后进行次级界面选择
				{
					key=KEY_Scan(0);//扫描按建
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
									switch(cur_item[item_index].type)//检测类型，进入相应动作
									{
										case MENU_SUBMENU://拥有子菜单项.
											if(cur_item[item_index].next != NULL)
											{ 
												prev_item = cur_item;//此级菜单变成了上一级菜单 
												cur_item = cur_item[item_index].next;//将指向的下一级菜单设置为当前菜单
												item_index = 0;//重置菜单项索引
												DispCurrentMenu();
											}else
											{
			//									display_GB2312_string(2,25,"NO           ");
											}
											break; 
										case MENU_PARAM: //参数项（用于执行参数设置） 
											if(cur_item[item_index].Fun != NULL)
											{ 
												//调用相应的动作函数,并传递参数
												cur_item[item_index].Fun((const char *)cur_item[item_index].label,&cur_item[item_index].action);
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
										if (prev_item != NULL)//返回上一级菜单的操作 
										{
											item_index=cur_item[item_index].Higher_Menu_Level;//重置菜单项索引
											cur_item = prev_item;//设置上一级菜单为当前菜单 
											prev_item = cur_item[0].prev;//设置当前菜单的上一级菜单 
											DispCurrentMenu();
										} 
										else
										{
											Initial();//回到初始页面
										}
										break;
							default: 
								break;
					}
					if(ExitTimed==(600-1))	Initial();//回到初始页面
				}
			}
		}
		else	Initial();//回到初始页面
	}
}
/**
*动态显示界面
*/
void Initial(void)
{
//	u8 i=0;
	clear_screen();//清屏
	display_128x64(UI_1);
	while(1)
	{
		
		if(SET_Sign==1)	MenuOption();//当在初始界面时按SET键进入菜单栏,成功进入菜单栏需要长按SET 3S
		
		
		
		Decoding_16x32(ExitTimed);//字体:Agency FB	大小:16*32,	
		Decoding_12x16(ExitTimed);//字体:Agency FB	大小:12*16,
		delay_ms(20);
		if(ExitTimed==30)	
		{
			printf("%s-- %s:%d\r\n",menu_P1_Display_Mode[0].title,menu_P1_Display_Mode[0].label,menu_P1_Display_Mode[0].action);
			printf("%s-- %s:%d\r\n",menu_P1_Display_Mode[0].title,menu_P1_Display_Mode[1].label,menu_P1_Display_Mode[1].action);
			printf("%s-- %s:%d\r\n",menu_P1_Display_Mode[0].title,menu_P1_Display_Mode[2].label,menu_P1_Display_Mode[2].action);
			printf("\r\n\r");
			printf("%s-- %s:%d\r\n",menu_P2_Input_Signal[0].title,menu_P2_Input_Signal[0].label,menu_P2_Input_Signal[0].action);
			printf("%s-- %s:%d\r\n",menu_P2_Input_Signal[0].title,menu_P2_Input_Signal[1].label,menu_P2_Input_Signal[1].action);
			printf("%s-- %s:%d\r\n",menu_P2_Input_Signal[0].title,menu_P2_Input_Signal[2].label,menu_P2_Input_Signal[2].action);
			printf("%s-- %s:%d\r\n",menu_P2_Input_Signal[0].title,menu_P2_Input_Signal[3].label,menu_P2_Input_Signal[3].action);
			printf("\r\n\r");
			printf("%s-- %s:%d\r\n",menu_P3_Outout_Signal[0].title,menu_P3_Outout_Signal[0].label,menu_P3_Outout_Signal[0].action);
			printf("%s-- %s:%d\r\n",menu_P3_Outout_Signal[0].title,menu_P3_Outout_Signal[1].label,menu_P3_Outout_Signal[1].action);
			printf("%s-- %s:%d\r\n",menu_P3_Outout_Signal[0].title,menu_P3_Outout_Signal[2].label,menu_P3_Outout_Signal[2].action);
			printf("%s-- %s:%d\r\n",menu_P3_Outout_Signal[0].title,menu_P3_Outout_Signal[3].label,menu_P3_Outout_Signal[3].action);
			printf("%s-- %s:%d\r\n",menu_P3_Outout_Signal[0].title,menu_P3_Outout_Signal[4].label,menu_P3_Outout_Signal[4].action);
			printf("%s-- %s:%d\r\n",menu_P3_Outout_Signal[0].title,menu_P3_Outout_Signal[5].label,menu_P3_Outout_Signal[5].action);
			printf("\r\n\r");
			printf("%s-- %s:%d\r\n",menu_P4_Action_Mode[0].title,menu_P4_Action_Mode[0].label,menu_P4_Action_Mode[0].action);
			printf("%s-- %s:%d\r\n",menu_P4_Action_Mode[0].title,menu_P4_Action_Mode[1].label,menu_P4_Action_Mode[1].action);
			printf("\r\n\r");
			printf("%s-- %s:%d\r\n",menu_P5_Action_Manner[0].title,menu_P5_Action_Manner[0].label,menu_P5_Action_Manner[0].action);
			printf("%s-- %s:%d\r\n",menu_P5_Action_Manner[0].title,menu_P5_Action_Manner[1].label,menu_P5_Action_Manner[1].action);
			printf("\r\n\r");
			printf("%s-- %s:%d\r\n",menu_P6_Adjust_Mode[0].title,menu_P6_Adjust_Mode[0].label,menu_P6_Adjust_Mode[0].action);
			printf("%s-- %s:%d\r\n",menu_P6_Adjust_Mode[0].title,menu_P6_Adjust_Mode[1].label,menu_P6_Adjust_Mode[1].action);
			printf("\r\n\r");
			printf("%s-- %s:%d\r\n",menu_P7_Opening_Mode[0].title,menu_P7_Opening_Mode[0].label,menu_P7_Opening_Mode[0].action);
			printf("%s-- %s:%d\r\n",menu_P7_Opening_Mode[0].title,menu_P7_Opening_Mode[1].label,menu_P7_Opening_Mode[1].action);
			printf("%s-- %s:%d\r\n",menu_P7_Opening_Mode[0].title,menu_P7_Opening_Mode[2].label,menu_P7_Opening_Mode[2].action);
			printf("%s-- %s:%d\r\n",menu_P7_Opening_Mode[0].title,menu_P7_Opening_Mode[3].label,menu_P7_Opening_Mode[3].action);
			printf("%s-- %s:%d\r\n",menu_P7_Opening_Mode[0].title,menu_P7_Opening_Mode[4].label,menu_P7_Opening_Mode[4].action);
			printf("%s-- %s:%d\r\n",menu_P7_Opening_Mode[0].title,menu_P7_Opening_Mode[5].label,menu_P7_Opening_Mode[5].action);
			printf("\r\n\r");
		}
	}
}
/**
*开机LOGO界面
*/
void LOGODisplay(void)
{
		display_128x64(LOGO);
		delay_ms(1000);
		Initial();
}










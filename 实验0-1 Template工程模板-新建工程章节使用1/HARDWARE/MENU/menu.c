#include "menu.h"
#include "LCD_ZK.H"
#include "zk.h"
#include "delay.h"
#include "key.h"
#include "timer3.h"
#include "usart.h"

/**************************************************************************************************
*参数存储变量
*/
//p2
	float SETPOINT_P21_MIN_RGE=4.0;//全局变量,设定给定信号的最小值(预设为4mA)
	float SETPOINT_P22_MAX_PRG=20.0;//全局变量,设定给定信号的最大值(预设为20mA)


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
struct MenuItem menu_main[9];//1级菜单,主菜单
//第2级菜单
struct MenuItem menu_P1_STANDARD[5];//基本参数组
struct MenuItem menu_P2_SETPOINT[9];//给定信号组
struct MenuItem menu_P3_ACTUATOR[4];//执行器特性组
struct MenuItem menu_P4_MESSAGES[6];//
struct MenuItem menu_P5_ALARMS[8];//报警功能组
struct MenuItem menu_P6_MAN_ADJ[6];//手动调整 
struct MenuItem menu_P7_PAR[12];//控制参数
struct MenuItem menu_P8_ANLG_OUT[6];//模拟信号输出
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
struct MenuItem menu_main[9] = // 第1级菜单,主菜单
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本					参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
			{9, 		0,				0,					"菜单：        >>",		"1.STANDARD  ",	MENU_SUBMENU, NULL,		 NULL,			menu_P1_STANDARD, 	NULL},//基本参数组,
			{9, 		0,				1,					"",										"2.SETPOINT  ",	MENU_SUBMENU, NULL,		 NULL,			menu_P2_SETPOINT, 	NULL},//给定信号组,
			{9, 		0,				2,					"",										"3.ACTUATOR  ",	MENU_SUBMENU, NULL,		 NULL,			menu_P3_ACTUATOR,		NULL},//执行器特性组,
			{9, 		0,				3,					"",										"4.MESSAGES  ",	MENU_SUBMENU, NULL,		 NULL,			menu_P4_MESSAGES,		NULL},//P4._,
			{9, 		0,				4,					"",										"5.ALARMS    ", MENU_SUBMENU, NULL,		 NULL,			menu_P5_ALARMS,			NULL},//报警功能组
			{9, 		0,				5,					"",										"6.MAN_ADJ   ", MENU_SUBMENU, NULL,		 NULL,			menu_P6_MAN_ADJ,		NULL},//手动调整, 
			{9,			0,				6, 					"",										"7.CTRL_PAR  ", MENU_SUBMENU, NULL,		 NULL,			menu_P7_PAR,				NULL},//控制参数,
			{9, 		0,				7,					"",										"8.ANLG_OUT  ", MENU_SUBMENU,	NULL,		 NULL,			menu_P8_ANLG_OUT,		NULL},//模拟信号输出, 
			{9, 		0,				8,					"",										"9.EXIT      ", NULL,					NULL,		 NULL,			menu_P8_ANLG_OUT,		NULL},//模拟信号输出,  
}; 
/****
***	2级菜单
***/
struct MenuItem menu_P1_STANDARD[5] = // 第2级菜单,P1	基本参数组
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本					参考宏定义	 		动作		动作参数			下一级菜单							上一级菜单
			{5,			0,			 	0,					"1.STANDARD    >>",		"1.ACTUATOR  ",	MENU_SUBMENU, NULL, 		NULL,			menu_P1_0ACTUATOR, 		menu_main},//不确定 子 级菜单是什么
			{5,			0, 				1,					"",										"2.AUTO_ADJ  ",	MENU_SUBMENU, NULL, 		NULL,			ConfirmOrCancel, 			menu_main},
			{5,			0,	 			2,					"",										"3.TOL_BAND  ",	MENU_SUBMENU, NULL, 		NULL,			NULL, 								menu_main},//不确定 子 级菜单是什么
			{5,			0,				3,					"",										"4.TEST      ",	MENU_SUBMENU, NULL, 		NULL,			NULL, 								menu_main},//不确定 子 级菜单是什么
			{5,			0, 				4,					"",										"5.EXIT      ",	MENU_PARAM,		DropOut,	NULL,			NULL, 								menu_main},
};
struct MenuItem menu_P2_SETPOINT[9] = // 第2级菜单,P2	给定信号组
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作		动作参数			下一级菜单								上一级菜单
			{9,			1, 				0,					"2.SETPOINT    >>",		"1.SignalSyste",	MENU_SUBMENU, NULL, 		NULL, 		menu_P2_0SignalSystem,	menu_main},//不确定 子 级菜单是什么
			{9,			1, 				1,					"",										"2.MIN_RGE    ",	MENU_PARAM, P2_SETPOINT_SignalSetting, 		NULL, 		NULL, 									menu_main},//不确定 子 级菜单是什么
			{9,			1, 				2,					"",										"3.MAX_PRG    ",	MENU_PARAM, P2_SETPOINT_SignalSetting, 		NULL, 		NULL, 									menu_main},//不确定 子 级菜单是什么
			{9,			1, 				3,					"",										"4.CHARACT    ",	MENU_SUBMENU, NULL, 		NULL, 		NULL, 									menu_main},//不确定 子 级菜单是什么
			{9,			1, 				4,					"",										"5.ACTION     ",	MENU_SUBMENU, NULL, 		NULL, 		menu_P2_4ACTION, 				menu_main},//不确定 子 级菜单是什么
			{9,			1, 				5,					"",										"6.SHUT-OFF   ",	MENU_SUBMENU, NULL, 		NULL, 		NULL, 									menu_main},//不确定 子 级菜单是什么
			{9,			1, 				6,					"",										"7.RAMP∧     ",	MENU_SUBMENU, NULL, 		NULL, 		NULL, 									menu_main},//不确定 子 级菜单是什么
			{9,			1, 				7,					"",										"8.RAMP∨     ",	MENU_SUBMENU, NULL, 		NULL, 		NULL, 									menu_main},//不确定 子 级菜单是什么
			{9,			1, 				8,					"",										"9.EXIT       ",	MENU_PARAM, 	DropOut,	NULL, 		NULL, 									menu_main},
};
struct MenuItem menu_P3_ACTUATOR[4] = // 第2级菜单,P3	执行器特性组
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
			{4,				2, 			0,					"3.ACTUATOR    >>",		"1.MIN_RGE    ",	MENU_SUBMENU, NULL, 		NULL,  		NULL, 						menu_main},//不确定 子 级菜单是什么
			{4,				2,			1,					"",										"2.MAX_RGE    ",	MENU_SUBMENU, NULL, 		NULL,  		NULL, 						menu_main},//不确定 子 级菜单是什么
			{4,				2, 			2,					"",										"3.ZERO_POS   ",	MENU_SUBMENU, NULL,		 	NULL,  		NULL, 						menu_main},//不确定 子 级菜单是什么
			{4,				2, 			3,					"",										"4.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL,			NULL, 						menu_main},//不确定 子 级菜单是什么	
};
struct MenuItem menu_P4_MESSAGES[6] = // 第2级菜单,P4	MESSAGES
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
			{6,				3, 			0,					"4.MESSAGES    >>",		"1.TIME_OUT   ",	MENU_SUBMENU, NULL, 		NULL,  		NULL, 						menu_main},//不确定 子 级菜单是什么
			{6,				3, 			1,					"",										"2.POS_SW1    ",	MENU_SUBMENU, NULL, 		NULL,  		NULL, 						menu_main},//不确定 子 级菜单是什么			
			{6,				3, 			2,					"",										"3.POS_SW2    ",	MENU_SUBMENU, NULL, 		NULL,  		NULL, 						menu_main},//不确定 子 级菜单是什么			
			{6,				3, 			3,					"",										"4.SW1_ACTV   ",	MENU_SUBMENU, NULL, 		NULL,  		NULL, 						menu_main},//不确定 子 级菜单是什么			
			{6,				3, 			4,					"",										"5.SW2_ACTV   ",	MENU_SUBMENU, NULL,		 	NULL,  		NULL, 						menu_main},//不确定 子 级菜单是什么			
			{6,				3, 			5,					"",										"6.EXIT       ",	MENU_PARAM, 	DropOut,	NULL, 		NULL, 						menu_main},//不确定 子 级菜单是什么			
};
struct MenuItem menu_P5_ALARMS[8] = // 第2级菜单,P5	报警功能组
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
			{8,				4, 			0,					"5.ALARMS      >>",		"1.LEACKAGE   ",	MENU_SUBMENU, NULL, 		NULL,  		ConfirmOrCancel,	menu_main},//不确定 子 级菜单是什么
			{8,				4, 			1,					"",										"2.SP_RGE     ",	MENU_SUBMENU, NULL, 		NULL,  		ConfirmOrCancel,	menu_main},//不确定 子 级菜单是什么
			{8,				4, 			2,					"",										"3.SENS_RGE   ",	MENU_SUBMENU, NULL, 		NULL,  		ConfirmOrCancel,	menu_main},//不确定 子 级菜单是什么
			{8,				4, 			3,					"",										"4.CTRLER     ",	MENU_SUBMENU, NULL, 		NULL,  		ConfirmOrCancel,	menu_main},//不确定 子 级菜单是什么
			{8,				4, 			4,					"",										"5.TIME_OUT   ",	MENU_SUBMENU, NULL, 		NULL,  		ConfirmOrCancel,	menu_main},//不确定 子 级菜单是什么
			{8,				4, 			5,					"",										"6.STRK_CTR   ",	MENU_SUBMENU, NULL, 		NULL,  		ConfirmOrCancel,	menu_main},//不确定 子 级菜单是什么
			{8,				4, 			6,					"",										"7.TRAVEL     ",	MENU_SUBMENU, NULL, 		NULL,  		ConfirmOrCancel,	menu_main},//不确定 子 级菜单是什么
			{8,				4, 			7,					"",										"8.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL,			NULL, 						menu_main},//不确定 子 级菜单是什么
};
struct MenuItem menu_P6_MAN_ADJ[6] = // 第2级菜单,P6	手动调整
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
			{6,				5, 			0,					"6.MAN_ADJ     >>",		"1.MIN_VR     ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,								menu_main},//不确定 子 级菜单是什么
			{6,				5, 			1,					"",										"2.MAX_VR     ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,								menu_main},//不确定 子 级菜单是什么
			{6,				5, 			2,					"",										"3.ACTAUTOR   ",	MENU_SUBMENU, NULL, 		NULL,  		menu_P6_2ACTAUTOR,	menu_main},//不确定 子 级菜单是什么
			{6,				5, 			3,					"",										"4.SPRNG_Y2   ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,								menu_main},//不确定 子 级菜单是什么
			{6,				5, 			4,					"",										"5.ADJ_MODE   ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,								menu_main},//不确定 子 级菜单是什么
			{6,				5, 			5,					"",										"6.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL,			NULL,								menu_main},//不确定 子 级菜单是什么
};
struct MenuItem menu_P7_PAR[12] = // 第2级菜单,P7	控制参数
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
			{12,			6, 			0,					"7.PAR         >>",		"1.KP1        ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			1,					"",										"2.KP2        ",	MENU_SUBMENU, NULL,			NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			2,					"",										"3.TV1        ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			3,					"",										"4.TV2        ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			4,					"",										"5.Air        ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			5,					"",										"6.Air        ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6,			6,					"",										"7.Air        ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			7,					"",										"8.Air        ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			8,					"",										"9.Air        ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			9,					"",										"10.Air       ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			10,					"",										"11.Air       ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{12,			6, 			11,					"",										"12.EXIT      ",	MENU_PARAM, 	DropOut, 	NULL,			NULL,							menu_main},//不确定 子 级菜单是什么
};
struct MenuItem menu_P8_ANLG_OUT[6] = // 第2级菜单,P8	模拟信号输出
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题							菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
			{6,			7,			 	0,					"8.ANLG_OUT    >>",		"1.MIN_RGE    ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{6,			7, 				1,					"",										"2.MAX_RGE    ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{6,			7, 				2,					"",										"3.ACTION     ",	MENU_SUBMENU, NULL, 		NULL,  		menu_P8_2ACTION,	menu_main},//不确定 子 级菜单是什么
			{6,			7, 				3,					"",										"4.ALARM      ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{6,			7, 				4,					"",										"5.TEST       ",	MENU_SUBMENU, NULL, 		NULL,  		NULL,							menu_main},//不确定 子 级菜单是什么
			{6,			7, 				5,					"",										"6.EXIT       ",	MENU_PARAM, 	DropOut, 	NULL,			NULL,							menu_main},//不确定 子 级菜单是什么
};
/********
*****	3级菜单
*****/
////p1
	struct MenuItem menu_P1_0ACTUATOR[3] = // 第	3 级菜单,P1_0	定义定位器安装形式
	{
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
				{3,				0, 			0,					"1_1.ACTUATOR  >>",	"1.Form 1     ",	MENU_SUBMENU, NULL, 	Form1, 	 		NULL,								menu_P1_STANDARD},//型式1
				{3,				0, 			1,					"",									"2.Form 2     ",	MENU_SUBMENU, NULL, 	Form2,  		NULL,								menu_P1_STANDARD},//型式2
				{3,				0, 			2,					"",									"3.Form 3     ",	MENU_SUBMENU, NULL, 	Form3,  		NULL,								menu_P1_STANDARD},//型式3
	};

////p2
	struct MenuItem menu_P2_0SignalSystem[3] = // 第	3 级菜单,P2_0	信号制式
	{
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
				{3,				0, 			0,					"2_1.Signal    >>",	"1.Current    ",	MENU_SUBMENU, NULL, 	CURRENT, 	 	NULL,								menu_P2_SETPOINT},//电流
				{3,				0, 			1,					"",									"2.Voltage    ",	MENU_SUBMENU, NULL, 	VOLTAGE,  	NULL,								menu_P2_SETPOINT},//电压
				{3,				0, 			2,					"",									"3.Switch     ",	MENU_SUBMENU, NULL, 	SWITCH,  		NULL,								menu_P2_SETPOINT},//开关量
	};
	struct MenuItem menu_P2_4ACTION[2] = // 第	3 级菜单,P2_4	设定阀门正反作用方式
	{	
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
				{2,				4, 			0,					"2_4.ACTION   >>",	"1.Positive   ",	MENU_SUBMENU, NULL, 	NULL, 		 	NULL,								menu_P2_SETPOINT},//正向
				{2,				4, 			1,					"",									"2.Reverse    ",	MENU_SUBMENU, NULL, 	NULL, 		 	NULL,								menu_P2_SETPOINT},//反向
	};	
////p6
	struct MenuItem menu_P6_2ACTAUTOR[2] = // 第	3 级菜单,P6_2	选择执行器型式
	{
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
				{2,				4, 			0,					"6_2.ACTAUTOR >>",	"1.Form 1      ",	MENU_SUBMENU, NULL, 	NULL, 		 	NULL,								menu_P6_MAN_ADJ},//型式1	
				{2,				4, 			0,					"",									"2.Form 1      ",	MENU_SUBMENU, NULL, 	NULL, 		 	NULL,								menu_P6_MAN_ADJ},//型式2
	};
////p8
	struct MenuItem menu_P8_2ACTION[2] = // 第	3 级菜单,P6_2	选择执行器型式	
	{
	//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作		动作参数			下一级菜单						上一级菜单
				{2,				4, 			0,					"8_2.ACTION   >>",	"1.Positive    ",	MENU_SUBMENU, NULL, 	NULL, 		 	NULL,								menu_P8_ANLG_OUT},//正向	
				{2,				4, 			0,					"",									"2.Reverse     ",	MENU_SUBMENU, NULL, 	NULL, 		 	NULL,								menu_P8_ANLG_OUT},//反向
	};
	
	
struct MenuItem ConfirmOrCancel[2] = // 第3级菜单,确认或取消
{
//本级菜单数量	上级菜单级	当前菜单级  级菜单标题						菜单文本						参考宏定义	 		动作			动作参数			下一级菜单						上一级菜单
			{2,				2, 			0,					"",									"Cancel      ",		NULL,					DropOut, 	NULL,				NULL, 						menu_main},//取消
			{2,				2, 			1,					"",									"Confirm     ",		MENU_PARAM, 	DropOut, 	NULL,				NULL, 						menu_main},//确认
};	









/******************************************************************************************************************************************************************************************************
*动作函数
*/
void DropOut(const char *Text)
{
		item_index=cur_item[item_index].Higher_Menu_Level-1;//重置菜单项索引
		cur_item = prev_item;//设置上一级菜单为当前菜单 
		prev_item = cur_item[0].prev;//设置当前菜单的上一级菜单 
		DispCurrentMenu();
}
/**
*设定信号最大最小值，单位mA，每次设定最小变量为0.1mA
*@parameter	[MIN_RGE],设定给定信号的最小值(预设为4mA)
*@parameter	[MAX_PRG],设定给定信号的最大值(预设为20mA)
*/
void P2_SETPOINT_SignalSetting(u8 parameter)
{
	u16 value=0;
	u8 key=0;
	if(parameter==MIN_RGE)	value=SETPOINT_P21_MIN_RGE*10;//将设定给定信号的最小值赋值给	parameter		(预设为4mA)
	else	value=SETPOINT_P22_MAX_PRG*10;//将设定给定信号的最大值赋值给	parameter		(预设为20mA)
	clear_screen();//清屏
	while(1)
	{
		key=KEY_Scan(0);//扫描按建
		switch(key)
		{
			case	UP_PRES:
						if(value<SETPOINT_P22_MAX_PRG*10)	value++;
						else	value=value;
						display_graphic_32x16(6,42,Triangle_Decrease_Black);
						break;
			case	DOWN_PRES:
						if(value>SETPOINT_P21_MIN_RGE*10)	value--;
						else value=value;
						display_graphic_32x16(6,60,Triangle_Increase_Black);
						break;
			case	OK_PRES:
						if(parameter==MIN_RGE)	{
							SETPOINT_P21_MIN_RGE=value;//将设定给定信号的最小值赋值给	parameter		(预设为4mA)
							SETPOINT_P21_MIN_RGE=SETPOINT_P21_MIN_RGE/10;
						}
						else	{
							SETPOINT_P22_MAX_PRG=value;//将设定给定信号的最大值赋值给	parameter		(预设为20mA)
							SETPOINT_P22_MAX_PRG=SETPOINT_P22_MAX_PRG/10;
						}
						break;
			case	SET_PRES:
						SET_LongPress=750;
						MenuOption();
						break;
			default:
				break;
		}
		display_graphic_32x16(6,42,Triangle_Decrease_White);
		display_graphic_32x16(6,60,Triangle_Increase_White);
		Decoding_16x32(value);
		display_string_5x7(6,110,"mA");
		
	}
}


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
	printf("item_index:%d\r\n",item_index);
//	printf("上级菜单:%s\r\n",prev_item[item_index].label);
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
									item_index++; 
									DispCurrentMenu();
									break;
						case	DOWN_PRES:
									item_index--; 
									DispCurrentMenu();
									break;
						case	OK_PRES:
									switch(cur_item[item_index].type)//检测类型，进入相应动作
									{
										case MENU_SUBMENU:
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
										case MENU_PARAM: 
											if(cur_item[item_index].Fun != NULL)
											{ 
												//调用相应的动作函数,并传递参数
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
void Initial(void)
{
//	u8 i=0;
	clear_screen();//清屏
	display_128x64(UI_1);
	while(1)
	{
		
		if(SET_Sign==1)	MenuOption();//当在初始界面时按SET键进入菜单栏,成功进入菜单栏需要长按SET 3S
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










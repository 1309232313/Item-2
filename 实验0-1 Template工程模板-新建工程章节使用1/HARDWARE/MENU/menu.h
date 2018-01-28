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

//定义相应的动作参数
//p1
	#define	Form1			201	//P1.0定义定位器安装形式:1,Form1
	#define	Form2			202	//P1.0定义定位器安装形式:2,Form2
	#define	Form3			203	//P1.0定义定位器安装形式:3,Form3
//P2
	#define CURRENT		201	//P2.01信号制式:1,电流形式
	#define	VOLTAGE		202	//P2.02信号制式:2,电压形式
	#define	SWITCH		203	//P2.03信号制式:3,开关量
	#define	MIN_RGE		211	//P2.1 MIN_RGE 设定给定信号的最小值(预设为4mA)
	#define	MAX_PRG		221	//P2.2 MAX_PRG 设定给定信号的最大值(预设为20mA)
	#define	POSITIVE	241	//P2.41 ACTION:设定阀门正作用方式
	#define	NEGATIVE	242	//P2.42 ACTION:设定阀门反作用方式
	#define	RAMP1			261	//P2.61 RAMP? 降低开向速度
	#define	RAMP2			271	//P2.71 RAMP? 降低关向速度
//P6
	#define	MIN_VR		601	//P6.0 MIN_VR 手动设置阀门全关位置
	#define	MAX_VR		611	//P6.1 MAX_VR 手动设置阀门全开位置
	#define	ACTAUTOR	621	//P6.2 ACTAUTOR 选择执行器型式
//P8
	#define	MIN_RGE8	801	//P8.0 MIN_RGE 阀位起始点电流值（默认为4mA)
	#define	MAX_RGE8	811	//P8.1 MAX_RGE 100%阀位电流值（默认为20mA)
	#define	ACTION		821	//P8.2 ACTION 阀位正反方向选择（默认4mA 对应阀位 0%）

#define Yes		1 // 参数项（用于执行参数设置）  
#define No		0 // 参数项（用于执行参数设置）  
//定义菜单操作需要的全局变量
extern u8 item_index;//当前菜单项索引






typedef void (*MENU_FUN)(const char *);
/*************** 
 * 菜单结构 
 * 一个数组既代表一级菜单，数组中的一个元素就是一个菜单项，就是一个单独的结构体， 
 * 数组中的第一个元素中的num值很重要，表示本级菜单具有多少个菜单项。 
 * 
 * uint8_t num 本级菜单数量，必须在第一项中设置正确的菜单项数量 
 * char* label 菜单文本 
 * uint8_t type 此项类型，参考宏定义 
 * MENU_CALLBACK CallBack;  指向动作的函数指针，此项要执行的具体动作函数 
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
	u8 action;//向动作函数传递的动作参数
	struct MenuItem *next;	//下一级菜单
	struct MenuItem *prev;	//上一级菜单
};

void DispCurrentMenu(void);//绘制当前菜单项
void DropOut(const char * Text);//动作
void P2_SETPOINT_SignalSetting(u8 parameter);


u8 MenuOption(void);
void Initial(void);
void LOGODisplay(void);

#endif


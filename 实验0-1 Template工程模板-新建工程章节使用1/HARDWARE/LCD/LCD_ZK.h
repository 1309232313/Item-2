#define _LCD_ZK_H_
#ifdef _LCD_ZK_H_



/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

//带参宏，可以像内联函数一样使用
#define lcd_cs1(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_13)

#define lcd_rs(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_12)


#define lcd_sid(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_10)

#define lcd_sclk(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_9);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_9)
#define Rom_CS(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_15)

#define Rom_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_14)

					
#define lcd_RES(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_11)

#define ROM_OUT    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)

extern unsigned char const bmp1[];
extern unsigned char const jiong1[];
extern unsigned char const lei1[];

void GBZK_GPIO_Config(void);
/*写指令到LCD模块*/
void transfer_command_lcd(int data1);   
/*写数据到LCD模块*/
void transfer_data_lcd(int data1);
/*延时*/
void delay(int n_ms);               
/*LCD模块初始化*/
void initial_lcd(void);
void lcd_address(unsigned char page,unsigned char column);
/*全屏清屏*/
void clear_screen(void);
/*显示128x64点阵图像*/
void display_128x64(const unsigned char *dp);

/*显示16x40点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void display_graphic_16x32(unsigned int page,unsigned int column,const unsigned char *dp);
/*显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp);
/*显示12x16点阵图像、ASCII, 或12x16点阵的自造字符、其他图标*/
void display_graphic_12x16(unsigned int page,unsigned char column,const unsigned char *dp);
/*显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标*/
void display_graphic_8x16(unsigned int page,unsigned char column,const unsigned char *dp);
/*显示5*7点阵图像、ASCII, 或5x7点阵的自造字符、其他图标*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp);
/****送指令到晶联讯字库IC***/
void send_command_to_ROM( unsigned char datu );
/****从晶联讯字库IC中取汉字或字符数据（1个字节）***/
static unsigned char get_data_from_ROM(void);
/*从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出DataLen个字节的数据到 pBuff的地址*/
/*连续读取*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen );
/******************************************************************/
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text);
void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text);

#endif

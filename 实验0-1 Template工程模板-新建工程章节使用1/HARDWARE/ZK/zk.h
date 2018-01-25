#ifndef __ZK_H
#define	__ZK_H
#include "sys.h"
//#define _0 shuzi0
//#define _1 shuzi1
//#define _2 shuzi2
//#define _3 shuzi3
//#define _4 shuzi4
//#define _5 shuzi5
//#define _6 shuzi6
//#define _7 shuzi7


extern unsigned char const LOGO[];
extern unsigned char const UI_1[];
extern unsigned char const UI_2[];

extern unsigned char const shuzi0_32[];
extern unsigned char const shuzi1_32[];
extern unsigned char const shuzi2_32[];
extern unsigned char const shuzi3_32[];
extern unsigned char const shuzi4_32[];
extern unsigned char const shuzi5_32[];
extern unsigned char const shuzi6_32[];
extern unsigned char const shuzi7_32[];
extern unsigned char const shuzi8_32[];
extern unsigned char const shuzi9_32[];
extern unsigned char const Point_32[];
extern unsigned char const Empty_32[];

extern unsigned char  shuzi0_16[];
extern unsigned char shuzi1_16[];
extern unsigned char shuzi2_16[];
extern unsigned char shuzi3_16[];
extern unsigned char shuzi4_16[];
extern unsigned char shuzi5_16[];
extern unsigned char shuzi6_16[];
extern unsigned char shuzi7_16[];
extern unsigned char shuzi8_16[];
extern unsigned char shuzi9_16[];
extern unsigned char Point_16[];
extern unsigned char Empty_16[];
void Decoding_16x32(u16 Digital);
void Decoding_12x16(u16 Digital);

#endif

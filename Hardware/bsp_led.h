//记得ifndef和endif的条件编译
#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "stm32f10x.h"
//GPIO输出有关LED的宏定义（对于led引脚和寄存器端口,以及时钟进行重定义）

//绿色LED灯
#define LED_G_GPIO_PIN				GPIO_Pin_0
#define LED_G_GPIO_PORT				GPIOB
#define LED_G_GPIO_CLK				RCC_APB2Periph_GPIOB
//蓝色LED灯
#define LED_B_GPIO_PIN				GPIO_Pin_1
#define LED_B_GPIO_PORT				GPIOB
#define LED_B_GPIO_CLK				RCC_APB2Periph_GPIOB
//红色LED灯
#define LED_R_GPIO_PIN				GPIO_Pin_5
#define LED_R_GPIO_PORT				GPIOB
#define LED_R_GPIO_CLK				RCC_APB2Periph_GPIOB

////对于灯的开关状态进行宏定义
//#define ON		1
//#define OFF		0

////绿色LED灯开关状态的宏
//#define	LED_G(LED_State)	if(LED_State)\
//							{GPIO_SetBits(LED_G_GPIO_PORT,  LED_G_GPIO_PIN);}\
//							else\
//							{GPIO_ResetBits(LED_G_GPIO_PORT,  LED_G_GPIO_PIN);}
//							
////蓝色LED灯开关状态的宏
//#define	LED_B(LED_State)	if(LED_State)\
//							{GPIO_SetBits(LED_B_GPIO_PORT,  LED_B_GPIO_PIN);}\
//							else\
//							{GPIO_ResetBits(LED_B_GPIO_PORT,  LED_B_GPIO_PIN)};
//							
////红色LED灯开关状态的宏
//#define	LED_R(LED_State)	if(LED_State)\
//							{GPIO_SetBits(LED_R_GPIO_PORT,  LED_R_GPIO_PIN);}\
//							else\
//							{GPIO_ResetBits(LED_R_GPIO_PORT,  LED_R_GPIO_PIN);}

/*直接操作寄存器的方法控制IO*/
#define digitalHi(p,i) {p->BSRR=i;} //输出为高电平
#define digitalLo(p,i) {p->BRR=i;} //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态	

//控制LED状态的宏

//红色LED
#define LED_R_ON			digitalLo(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_R_OFF			digitalHi(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_R_TOGGLE		digitalToggle(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
//绿色LED
#define LED_G_ON			digitalLo(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_G_OFF			digitalHi(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_G_TOGGLE		digitalToggle(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
//蓝色LED
#define LED_B_ON			digitalLo(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_B_OFF			digitalHi(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_B_TOGGLE		digitalToggle(LED_B_GPIO_PORT,LED_B_GPIO_PIN)


//流水灯颜色的宏

//红色
#define LED_RED			LED_R_ON;\
						LED_B_OFF;\
						LED_G_OFF
//绿色
#define LED_GREEN		LED_R_OFF;\
						LED_B_OFF;\
						LED_G_ON
							
//蓝色
#define LED_BLUE		LED_R_OFF;\
						LED_B_ON;\
						LED_G_OFF

//黄色
#define LED_YELLOW		LED_R_ON;\
						LED_B_OFF;\
						LED_G_ON

//紫色
#define LED_PURPLE		LED_R_ON;\
						LED_B_ON;\
						LED_G_OFF

//青色
#define LED_CYAN		LED_R_OFF;\
						LED_B_ON;\
						LED_G_ON
//白色
#define LED_WHITE		LED_R_ON;\
						LED_B_ON;\
						LED_G_ON
//关掉所有灯光
#define LED_BLACK		LED_R_OFF;\
						LED_B_OFF;\
						LED_G_OFF


////LED灯反转的宏定义
//#define LED_GREEN_TOGGLE		{LED_G_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}
//#define LED_RED_TOGGLE			{LED_R_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}
//#define LED_BLUE_TOGGLE			{LED_B_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}


//调用LED的GPIO的配置函数
void LED_GPIO_Config(void);

#endif /*_BSP_LED_H*/

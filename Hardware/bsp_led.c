//bsp:board support package 板级支持包（stm32f103VE6T）
#include "bsp_led.h"

void LED_GPIO_Config(void){
	

	//初始化一个结构体(每一个引脚都对应一个结构体)
	GPIO_InitTypeDef GPIO_InitStructure_GREEN;
	GPIO_InitTypeDef GPIO_InitStructure_BLUE;
	GPIO_InitTypeDef GPIO_InitStructure_RED;
	//时钟的使能
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(LED_B_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(LED_R_GPIO_CLK,ENABLE);
	
	//对LED灯的引脚，引脚输出模式，速度进行配置
	//绿色LED的GPIO配置
	GPIO_InitStructure_GREEN.GPIO_Pin = LED_G_GPIO_PIN;
	GPIO_InitStructure_GREEN.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure_GREEN.GPIO_Speed = GPIO_Speed_50MHz;
	
	//蓝色LED的GPIO配置
	GPIO_InitStructure_BLUE.GPIO_Pin = LED_B_GPIO_PIN;
	GPIO_InitStructure_BLUE.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure_BLUE.GPIO_Speed = GPIO_Speed_50MHz;
	
	//红色LED的GPIO配置
	GPIO_InitStructure_RED.GPIO_Pin = LED_R_GPIO_PIN;
	GPIO_InitStructure_RED.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure_RED.GPIO_Speed = GPIO_Speed_50MHz;
	
	//调用库函数，初始化GPIO
	GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStructure_GREEN);
	GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStructure_BLUE);
	GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStructure_RED);
	
	//默认LED全部灭掉
	GPIO_SetBits(LED_G_GPIO_PORT,  LED_G_GPIO_PIN);
	GPIO_SetBits(LED_R_GPIO_PORT,  LED_R_GPIO_PIN);
	GPIO_SetBits(LED_B_GPIO_PORT,  LED_B_GPIO_PIN);

}

void assert_failed(uint8_t* file, uint32_t line)
{
	// 断言错误时执行的代码
	LED_R_ON;
}

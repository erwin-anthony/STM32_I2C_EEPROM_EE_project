#ifndef	_BSP_USART_H
#define	_BSP_USART_H

#include "stm32f10x.h"                  // Device header
#include "stdio.h"
/** 
  * 串口宏定义，不同的串口挂载的总线和IO不一样，移植时需要修改这几个宏
	* 1-修改总线时钟的宏，uart1挂载到apb2总线，其他uart挂载到apb1总线
	* 2-修改GPIO的宏
  */
  
#define USARTx_1		1
#define USARTx_2		0
#define USARTx_3		0
#define UARTx_4		 	0
#define UARTx_5		 	0



#if USARTx_1	
//USART1串口的宏
//USART1 串口1GPIO引脚宏定义
#define	USART_GPIO_APBxClkCmd			RCC_APB2PeriphClockCmd					/*GPIO引脚时钟使能*/
#define	USART_GPIO_CLK					RCC_APB2Periph_GPIOA					/*GPIO引脚时钟配置寄存器*/
#define	USART_GPIO_TX_PIN				GPIO_Pin_9			/*GPIO发送引脚的PIN*/
#define	USART_GPIO_TX_PORT				GPIOA				/*GPIO发送引脚的端口*/
#define	USART_GPIO_RX_PIN				GPIO_Pin_10			/*GPIO接收引脚的PIN*/
#define	USART_GPIO_RX_PORT				GPIOA				/*GPIO接收引脚的端口*/
//USART1-串口1相关的宏
#define	USARTx						USART1										/*USART串口1*/
#define	USART_APBxClkCmd			RCC_APB2PeriphClockCmd						/*USART时钟使能*/
#define	USART_CLK					RCC_APB2Periph_USART1						/*USART时钟配置寄存器*/
//中断相关宏定义
#define  USART_IRQ                	USART1_IRQn
#define  USART_IRQHandler           USART1_IRQHandler



#elif USARTx_2
//USART2串口的宏
//USART2 串口2GPIO引脚宏定义
#define	USART_GPIO_APBxClkCmd			RCC_APB2PeriphClockCmd					/*GPIO引脚时钟使能*/
#define	USART_GPIO_CLK					RCC_APB2Periph_GPIOA					/*GPIO引脚时钟配置寄存器*/
#define	USART_GPIO_TX_PIN				GPIO_Pin_2			/*GPIO发送引脚的PIN*/
#define	USART_GPIO_TX_PORT				GPIOA				/*GPIO发送引脚的端口*/
#define	USART_GPIO_RX_PIN				GPIO_Pin_3		/*GPIO接收引脚的PIN*/
#define	USART_GPIO_RX_PORT				GPIOA				/*GPIO接收引脚的端口*/
//USART2-串口2相关的宏
#define	USARTx						USART2										/*USART串口2*/
#define	USART_APBxClkCmd			RCC_APB1PeriphClockCmd						/*USART时钟使能*/
#define	USART_CLK					RCC_APB1Periph_USART2						/*USART时钟配置寄存器*/
//中断相关宏定义
#define  USART_IRQ                	USART2_IRQn
#define  USART_IRQHandler           	USART2_IRQHandler


#elif USARTx_3
//USART3串口的宏
//USART3 串口3GPIO引脚宏定义
#define	USART_GPIO_APBxClkCmd			RCC_APB2PeriphClockCmd					/*GPIO引脚时钟使能*/
#define	USART_GPIO_CLK					RCC_APB2Periph_GPIOB					/*GPIO引脚时钟配置寄存器*/
#define	USART_GPIO_TX_PIN				GPIO_Pin_10			/*GPIO发送引脚的PIN*/
#define	USART_GPIO_TX_PORT				GPIOB				/*GPIO发送引脚的端口*/
#define	USART_GPIO_RX_PIN				GPIO_Pin_11		/*GPIO接收引脚的PIN*/
#define	USART_GPIO_RX_PORT				GPIOB				/*GPIO接收引脚的端口*/
//USART3-串口3相关的宏
#define	USARTx						USART3										/*USART串口3*/
#define	USART_APBxClkCmd			RCC_APB1PeriphClockCmd						/*USART时钟使能*/
#define	USART_CLK					RCC_APB1Periph_USART3						/*USART时钟配置寄存器*/
//中断相关宏定义
#define  USART_IRQ                	USART3_IRQn
#define  USART_IRQHandler           USART3_IRQHandler


#elif UARTx_4
//UART4串口的宏
//UART4 串口4GPIO引脚宏定义
#define	USART_GPIO_APBxClkCmd			RCC_APB2PeriphClockCmd					/*GPIO引脚时钟使能*/
#define	USART_GPIO_CLK					RCC_APB2Periph_GPIOC					/*GPIO引脚时钟配置寄存器*/
#define	USART_GPIO_TX_PIN				GPIO_Pin_10			/*GPIO发送引脚的PIN*/
#define	USART_GPIO_TX_PORT				GPIOC				/*GPIO发送引脚的端口*/
#define	USART_GPIO_RX_PIN				GPIO_Pin_11		/*GPIO接收引脚的PIN*/
#define	USART_GPIO_RX_PORT				GPIOC				/*GPIO接收引脚的端口*/
//UART4-串口4相关的宏
#define	USARTx						UART4										/*UART4串口*/
#define	USART_APBxClkCmd			RCC_APB1PeriphClockCmd						/*USART时钟使能*/
#define	USART_CLK					RCC_APB1Periph_UART4						/*USART时钟配置寄存器*/
//中断相关宏定义
#define  USART_IRQ                	UART4_IRQn
#define  USART_IRQHandler           UART4_IRQHandler



#elif UARTx_5
//UART5串口的宏
//UART5 串口5GPIO引脚宏定义
#define	USART_GPIO_APBxClkCmd			RCC_APB2PeriphClockCmd					/*GPIO引脚时钟使能*/
#define	USART_GPIO_CLK					(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)				/*GPIO引脚时钟配置寄存器*/
#define	USART_GPIO_TX_PIN				GPIO_Pin_12			/*GPIO发送引脚的PIN*/
#define	USART_GPIO_TX_PORT				GPIOC				/*GPIO发送引脚的端口*/
#define	USART_GPIO_RX_PIN				GPIO_Pin_2		/*GPIO接收引脚的PIN*/
#define	USART_GPIO_RX_PORT				GPIOD				/*GPIO接收引脚的端口*/
//UART5-串口5相关的宏
#define	USARTx						UART5										/*UART5串口*/
#define	USART_APBxClkCmd			RCC_APB1PeriphClockCmd						/*USART时钟使能*/
#define	USART_CLK					RCC_APB1Periph_UART5						/*USART时钟配置寄存器*/
//中断相关宏定义
#define  USART_IRQ                	UART5_IRQn
#define  USART_IRQHandler           UART5_IRQHandler

#endif





void USART_Config(void);


#endif	/*_BSP_USART_H*/

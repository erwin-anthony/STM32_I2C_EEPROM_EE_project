#include "bsp_usart.h"



void USART_Config(void){
	
	//结构体的声明
	GPIO_InitTypeDef GPIO_InitStructure_USART_TX;
	GPIO_InitTypeDef GPIO_InitStructure_USART_RX;
	USART_InitTypeDef USART_InitStructure;
	
	//打开串口GPIO的时钟
	USART_GPIO_APBxClkCmd(USART_GPIO_CLK,ENABLE);
	//打开串口外设的时钟
	USART_APBxClkCmd(USART_CLK,ENABLE);
	
	//串口的GPIO配置
	//发送(TX)串口GPIO配置
	GPIO_InitStructure_USART_TX.GPIO_Pin = USART_GPIO_TX_PIN;
	GPIO_InitStructure_USART_TX.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure_USART_TX.GPIO_Speed = GPIO_Speed_50MHz;
	//接收(RX)串口GPIO配置
	GPIO_InitStructure_USART_RX.GPIO_Pin = USART_GPIO_RX_PIN;
	GPIO_InitStructure_USART_RX.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure_USART_RX.GPIO_Speed = GPIO_Speed_50MHz;

	//GPIO初始化
	GPIO_Init(USART_GPIO_TX_PORT, &GPIO_InitStructure_USART_TX);
	GPIO_Init(USART_GPIO_RX_PORT, &GPIO_InitStructure_USART_RX);


	//配置串口的工作参数
	/*配置波特率*/
	USART_InitStructure.USART_BaudRate =115200;				
	/*配置硬件流控制*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 				
	/*配置工作模式，收发一起*/	
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;				
	/*配置校验位*/	
	USART_InitStructure.USART_Parity = USART_Parity_No;				
	/*配置停止位*/	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				
	/*配置帧数据字长	*/	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;				
	
	//串口配置初始化	
	USART_Init(USARTx, &USART_InitStructure);
	

	//使能串口
	USART_Cmd(USARTx, ENABLE);
	
}


/***************** 串口发送函数  **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t data)
{
	/*使用USART串口函数完成数据发送 */
	USART_SendData(pUSARTx,data);
		
	/* 判断发送数据是否完成 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t data)
{
	/*使用USART串口函数完成数据发送 */
	USART_SendData(pUSARTx,data);	
	/* 判断发送数据是否完成 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	
	

}


//重定向C库函数printf到串口，重定向后可以使用
int fputc(int ch, FILE *f)
{
		/*发送一个字节数据到串口*/
		USART_SendData(USARTx, (uint8_t) ch);
		
		/*判断是否发送完成*/
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
			/*重定向到C库函数getchar到串口*/
int fgetc(FILE *f)
{
		while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USARTx);
}

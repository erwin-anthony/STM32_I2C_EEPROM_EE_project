#include "stm32f10x.h"                  // Device header
#include "bsp_led.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "string.h"
#include "bsp_i2c.h"

#define  EEP_Firstpage      0x00


uint8_t I2c_Buf_Write[256];
uint8_t I2c_Buf_Read[256];
uint8_t readData[10] = {1,2,3,4,5,6,7,8,9,10};


int main(void){


	USART_Config();
	LED_GPIO_Config();

	
	
	EEPROM_Byte_Write(9,0x55);

	EEPROM_Random_Read(9,readData,1);

	printf("\r\n接收到的数据是0x%x\r\n",readData[9]);
	
	while(1){
		

	}

}

////I2C读写测试
//uint8_t I2C_Test(void){
//	
//	uint16_t i;
//	printf("写入数据\n\r");
//	
//	for ( i=0; i<=255; i++ ) //填充缓冲
//	{   
//		I2c_Buf_Write[i] = i;

//		printf("0x%02X ", I2c_Buf_Write[i]);
//		if(i%16 == 15){
//			printf("\n\r");
//		}		
//   }

//  //将I2c_Buf_Write中顺序递增的数据写入EERPOM中 
//	I2C_EE_BufferWrite( I2c_Buf_Write, EEP_Firstpage, 256);
//  
//  EEPROM_INFO("\n\r写成功\n\r");
//   
//   EEPROM_INFO("\n\r读出的数据\n\r");
//  //将EEPROM读出数据顺序保持到I2c_Buf_Read中
//	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256); 
//   
//  //将I2c_Buf_Read中的数据通过串口打印
//	for (i=0; i<256; i++)
//	{	
//		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
//		{
//			EEPROM_ERROR("0x%02X ", I2c_Buf_Read[i]);
//			EEPROM_ERROR("错误:I2C EEPROM写入与读出的数据不一致\n\r");
//			return 0;
//		}
//    printf("0x%02X ", I2c_Buf_Read[i]);
//    if(i%16 == 15)    
//        printf("\n\r");
//    
//	}
//  EEPROM_INFO("I2C(AT24C02)读写测试成功\n\r");
//  
//  return 1;

//}

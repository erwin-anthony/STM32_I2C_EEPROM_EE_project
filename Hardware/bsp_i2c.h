#ifndef _BSP_I2C_H
#define _BSP_I2C_H
#include "stm32f10x.h"                  // Device header
#include "bsp_usart.h"


//定义I2C自身地址(不跟外设冲突的7位地址)
#define STM32_I2C_OWN_ADDR			0x0A




/*I2C_EEPROM相关定义*/
#define I2C_EEPROM					I2C1
#define I2C_EEPROM_CLK				RCC_APB1Periph_I2C1
#define I2C_EEPROM_APBxClkCmd		RCC_APB1PeriphClockCmd
#define I2C_EEPROM_BAUDRATE			400000
#define I2Cx_OWN_ADDRESS7      		0X0A  

#define EEPROM_Block0_ADDRESS 		0xA0


//EEPROM相关引脚
//SCL引脚
#define EEPROM_SCL_GPIO_CLK					RCC_APB2Periph_GPIOB
#define EEPROM_SCL_GPIO_APBxClkCmd			RCC_APB2PeriphClockCmd
#define EEPROM_SCL_GPIO_PIN					GPIO_Pin_6
#define EEPROM_SCL_GPIO_PORT				GPIOB
//SDA引脚
#define EEPROM_SDA_GPIO_CLK					RCC_APB2Periph_GPIOB
#define EEPROM_SDA_GPIO_APBxClkCmd			RCC_APB2PeriphClockCmd
#define EEPROM_SDA_GPIO_PIN					GPIO_Pin_7
#define EEPROM_SDA_GPIO_PORT				GPIOB


/*等待超时时间*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/*信息输出*/
#define EEPROM_DEBUG_ON         0

#define EEPROM_INFO(fmt,arg...)           printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define EEPROM_ERROR(fmt,arg...)          printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define EEPROM_DEBUG(fmt,arg...)          do{\
                                          if(EEPROM_DEBUG_ON)\
                                          printf("<<-EEPROM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)


void I2C_EE_Init(void);
uint32_t EEPROM_Byte_Write(uint8_t addr,uint8_t data);
uint32_t EEPROM_Random_Read(uint8_t addr,uint8_t *data,uint8_t numByteToRead);
void I2C_EE_WaitEepromStandbyState(void);

#endif /*_BSP_I2C_H*/

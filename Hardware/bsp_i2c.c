#include "bsp_i2c.h"

uint16_t EEPROM_ADDRESS;

static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;   

static uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);



//初始化EPROM的GPIO引脚
static void EEPROM_GPIO_Config(void){
	//初始化结构体

	GPIO_InitTypeDef GPIO_InitStructure_EE_SCL;
	GPIO_InitTypeDef GPIO_InitStructure_EE_SDA;
	
	//打开串口GPIO的时钟
	EEPROM_SCL_GPIO_APBxClkCmd(EEPROM_SCL_GPIO_CLK,ENABLE);
	EEPROM_SDA_GPIO_APBxClkCmd(EEPROM_SDA_GPIO_CLK,ENABLE);	
	
	//EEPROM的串口配置
	//SCL引脚配置
	GPIO_InitStructure_EE_SCL.GPIO_Pin = EEPROM_SCL_GPIO_PIN;
	GPIO_InitStructure_EE_SCL.GPIO_Mode = GPIO_Mode_AF_OD;//开漏输出
	GPIO_InitStructure_EE_SCL.GPIO_Speed = GPIO_Speed_50MHz;
	//SDA引脚配置
	GPIO_InitStructure_EE_SDA.GPIO_Pin = EEPROM_SDA_GPIO_PIN;
	GPIO_InitStructure_EE_SDA.GPIO_Mode = GPIO_Mode_AF_OD;//开漏输出
	GPIO_InitStructure_EE_SDA.GPIO_Speed = GPIO_Speed_50MHz;
	
	//初始化(SCL和SDA)结构体
	GPIO_Init(EEPROM_SCL_GPIO_PORT,&GPIO_InitStructure_EE_SCL);
	GPIO_Init(EEPROM_SDA_GPIO_PORT,&GPIO_InitStructure_EE_SDA);

}

//初始化I2C工作模式
static void I2C_MODE_Config(void){

	//初始化结构体
	I2C_InitTypeDef I2C_InitStructure_EE;	
	
	//配置I2C结构体
	I2C_InitStructure_EE.I2C_Ack = I2C_Ack_Enable ;//使能应答
	I2C_InitStructure_EE.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//使用7位地址模式
	I2C_InitStructure_EE.I2C_ClockSpeed = I2C_EEPROM_BAUDRATE;//配置SCL时钟频率
	I2C_InitStructure_EE.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure_EE.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure_EE.I2C_OwnAddress1 = I2Cx_OWN_ADDRESS7;//只要与外挂的I2C地址不一样即可
	//初始化I2C
	I2C_Init(I2C_EEPROM,&I2C_InitStructure_EE);
	//使能I2C
	I2C_EEPROM_APBxClkCmd(I2C_EEPROM_CLK,ENABLE);		
}

/*I2C外设EEPROM初始化*/
void I2C_EE_Init(void){
	
	EEPROM_GPIO_Config();
	
	I2C_MODE_Config();
	
#ifdef EEPROM_Block0_ADDRESS
	
  EEPROM_ADDRESS = EEPROM_Block0_ADDRESS;

#endif

}




/*EEPROM的写入函数*/
uint32_t EEPROM_Byte_Write(uint8_t addr,uint8_t data){
	

	
	//产生起始信号
	I2C_GenerateSTART(I2C_EEPROM,ENABLE);
	
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	/*检测EV5事件是否完成,以及清除*/
	while(!I2C_CheckEvent(I2C_EEPROM, I2C_EVENT_MASTER_MODE_SELECT))  
	{
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
	} 

	
	I2CTimeout = I2CT_FLAG_TIMEOUT;	
	//EV5事检测到后发送设备地址
	I2C_Send7bitAddress(I2C_EEPROM,EEPROM_ADDRESS,I2C_Direction_Transmitter);
	/*检测EV6事件是否完成,以及清除*/
	while(!I2C_CheckEvent(I2C_EEPROM, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))  
	{
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
	}

	
	I2CTimeout = I2CT_FLAG_TIMEOUT;	
	//检测后发送要操作的存储单元地址addr
	I2C_SendData(I2C_EEPROM, addr);
	/*检测EV8事件是否完成,以及清除*/
	while(!I2C_CheckEvent(I2C_EEPROM,I2C_EVENT_MASTER_BYTE_TRANSMITTED))  
	{
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
	}	
	
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	//检测正常发送要存储的数据data
	I2C_SendData(I2C_EEPROM, data);
	/*检测EV8事件是否完成,以及清除*/
	while(!I2C_CheckEvent(I2C_EEPROM,I2C_EVENT_MASTER_BYTE_TRANSMITTED))  
	{
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
	}	
	//数据传输完成
	I2C_GenerateSTOP(I2C_EEPROM,ENABLE);

}






/*EEPROM的读取函数*/
uint32_t EEPROM_Random_Read(uint8_t addr,uint8_t *data,uint8_t numByteToRead){
	
	
							/*写入要读取数据的存储单元地址*/
	//产生起始信号
	I2C_GenerateSTART(I2C_EEPROM,ENABLE);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	/*检测EV5事件是否完成,以及清除*/
	while(!I2C_CheckEvent(I2C_EEPROM, I2C_EVENT_MASTER_MODE_SELECT))  
	{
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
	} 

	
	
	//EV5事件被检测到后发送设备地址
	I2C_Send7bitAddress(I2C_EEPROM,EEPROM_ADDRESS,I2C_Direction_Transmitter);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	/*检测EV6事件是否完成,以及清除*/
	while(!I2C_CheckEvent(I2C_EEPROM,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))  
	{
		if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(11);
	} 	

	
	//检测后发送要操作的存储单元地址addr
	I2C_SendData(I2C_EEPROM, addr);
	while(I2C_CheckEvent(I2C_EEPROM,I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR);
	
	
	
	
	
							/*发送读取数据的存储单元地址*/
	//产生第二次起始信号
	I2C_GenerateSTART(I2C_EEPROM,ENABLE);
	
	//检测写入(检测EV5事件)
	while(I2C_CheckEvent(I2C_EEPROM,I2C_EVENT_MASTER_MODE_SELECT) == ERROR);
	//EV5事件被检测到后发送存储地址
	I2C_Send7bitAddress(I2C_EEPROM,EEPROM_ADDRESS,I2C_Direction_Receiver);
	//检测EV6事件
	while(I2C_CheckEvent(I2C_EEPROM,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR);	
	
	
	

							/*读取具体的数据*/

	while(numByteToRead){
	
		if(1 == numByteToRead){
			
			//当处理最后一个字节
			I2C_AcknowledgeConfig(I2C_EEPROM,DISABLE);
			
			//检测EV7事件
			while(I2C_CheckEvent(I2C_EEPROM,I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR);
			*data = I2C_ReceiveData(I2C_EEPROM);
		}


		//检测EV7事件
		while(I2C_CheckEvent(I2C_EEPROM,I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR);
		//检测EV7事件后，即数据寄存器有新的数据，可以继续接收
		*data = I2C_ReceiveData(I2C_EEPROM);
		
		data++;
		numByteToRead--;
	
	}


	
	//数据传输完成
	I2C_GenerateSTOP(I2C_EEPROM,ENABLE);
	
	//重新配置ACK使能，以便下次响应应答
	I2C_AcknowledgeConfig(I2C_EEPROM,ENABLE);

}


//等待EEPROM内部时序完成
void I2C_EE_WaitEepromStandbyState(void)      
{
  vu16 SR1_Tmp = 0;

  do
  {
    /* 发送起始信号 */
    I2C_GenerateSTART(I2C_EEPROM, ENABLE);
    /* 读取I2C1的SR1寄存器 */
    SR1_Tmp = I2C_ReadRegister(I2C_EEPROM, I2C_Register_SR1);
    /* 发送EEPROM的地址为了写入*/
    I2C_Send7bitAddress(I2C_EEPROM, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(I2C_EEPROM, I2C_Register_SR1) & 0x0002));
  
  /* 清除AF标志 */
  I2C_ClearFlag(I2C_EEPROM, I2C_FLAG_AF);
    /* 停止信号 */    
    I2C_GenerateSTOP(I2C_EEPROM, ENABLE); 
}



/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：错误代码，可以用来定位是哪个环节出错.
  * @retval 返回0，表示IIC读取失败.
  */
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  EEPROM_ERROR("I2C 等待超时!errorCode = %d",errorCode);
  
  return 0;
}


/* 
 * 初始化通讯使用的目标引脚及端口时钟
 * 使能SPI外设的时钟
 * 配置SPI外设的模式、地址、速率等参数并使使能SPI外设
 * 编写基本SPI按字节收发的函数
 * 编写对FLASH擦除及读写操作的函数
 * 编写测试程序，对读写数据进行校验
 */
 #include "bsp_spi_flash.h"
 
 static __IO uint32_t SPITimeout = SPI_FLAG_TIMEOUT;
 static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);
 
 /**
  ** @brief  SPI_FLASH 初始化
  ** @param  无
  ** @retval 无
  */
void SPI_FLASH_Init(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 使能 SPI 时钟 */
	FLASH_SPI_APBxClock_Fun(FLASH_SPI_CLK, ENABLE);
	
	/* 使能 SPI 相关引脚时钟  */
	FLASH_SPI_CS_APBxClock_Fun(FLASH_SPI_CS_CLK, ENABLE);
	FLASH_SPI_SCK_APBxClock_Fun(FLASH_SPI_SCK_CLK, ENABLE);
	FLASH_SPI_MISO_APBxClock_Fun(FLASH_SPI_MISO_CLK, ENABLE);
	FLASH_SPI_MOSI_APBxClock_Fun(FLASH_SPI_MOSI_CLK, ENABLE);
	
	/* 配置 SPI 相关引脚 */
	/* SCK */
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(FLASH_SPI_CS_PORT, &GPIO_InitStructure);
	
	/* SCK */
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(FLASH_SPI_SCK_PORT, &GPIO_InitStructure);
	
	/* MOSI */
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(FLASH_SPI_MOSI_PORT, &GPIO_InitStructure);
	
	/* MISO */
	GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(FLASH_SPI_MISO_PORT, &GPIO_InitStructure);
	
	/* SPI 模式配置 */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7; /* 无效的 */
	SPI_Init(FLASH_SPIx, &SPI_InitStructure);
	
	/* 使能 SPI */
	SPI_Cmd(FLASH_SPIx, ENABLE);
	
}

/** 
 * @brief   使用 SPI 发送一个字节
 * @param   byte: 要发送的字节
 * @retval  返回接收到的数据
 */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
	SPITimeout = SPI_FLAG_TIMEOUT;
	/* 等待发动缓存区为空， TXE事件 */
	while(SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE))
	{
		if((--SPITimeout) == 0) return SPI_TIMEOUT_UserCallback(0);
	}
	
	/* 写入数据寄存器，把要写入的数据写入发送缓存器 */
	SPI_I2S_SendData(FLASH_SPIx, byte);
	
	SPITimeout = SPI_FLAG_TIMEOUT;
	/* 等待接收缓存器非空，RXNE事件 */
	while(SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE))
	{
		if((--SPITimeout) == 0) return SPI_TIMEOUT_UserCallback(0);
	}
	
	/* 读取数据寄存器，获取接收缓冲区数据 */
	return SPI_I2S_ReceiveData(FLASH_SPIx);
}

/**
 * @brief   等待超时回调函数
 * @param   None
 * @retval  None
 */
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
	 /* 等待超时后的处理，输出错误信息 */
	FLASH_INFO("SPI 等待超时!errorCode = %d", errorCode);
	return 0;
}


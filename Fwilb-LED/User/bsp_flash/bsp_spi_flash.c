/* 
 * ��ʼ��ͨѶʹ�õ�Ŀ�����ż��˿�ʱ��
 * ʹ��SPI�����ʱ��
 * ����SPI�����ģʽ����ַ�����ʵȲ�����ʹʹ��SPI����
 * ��д����SPI���ֽ��շ��ĺ���
 * ��д��FLASH��������д�����ĺ���
 * ��д���Գ��򣬶Զ�д���ݽ���У��
 */
 #include "bsp_spi_flash.h"
 
 static __IO uint32_t SPITimeout = SPI_FLAG_TIMEOUT;
 static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);
 
 /**
  ** @brief  SPI_FLASH ��ʼ��
  ** @param  ��
  ** @retval ��
  */
void SPI_FLASH_Init(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ʹ�� SPI ʱ�� */
	FLASH_SPI_APBxClock_Fun(FLASH_SPI_CLK, ENABLE);
	
	/* ʹ�� SPI �������ʱ��  */
	FLASH_SPI_CS_APBxClock_Fun(FLASH_SPI_CS_CLK, ENABLE);
	FLASH_SPI_SCK_APBxClock_Fun(FLASH_SPI_SCK_CLK, ENABLE);
	FLASH_SPI_MISO_APBxClock_Fun(FLASH_SPI_MISO_CLK, ENABLE);
	FLASH_SPI_MOSI_APBxClock_Fun(FLASH_SPI_MOSI_CLK, ENABLE);
	
	/* ���� SPI ������� */
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
	
	/* SPI ģʽ���� */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7; /* ��Ч�� */
	SPI_Init(FLASH_SPIx, &SPI_InitStructure);
	
	/* ʹ�� SPI */
	SPI_Cmd(FLASH_SPIx, ENABLE);
	
}

/** 
 * @brief   ʹ�� SPI ����һ���ֽ�
 * @param   byte: Ҫ���͵��ֽ�
 * @retval  ���ؽ��յ�������
 */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
	SPITimeout = SPI_FLAG_TIMEOUT;
	/* �ȴ�����������Ϊ�գ� TXE�¼� */
	while(SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE))
	{
		if((--SPITimeout) == 0) return SPI_TIMEOUT_UserCallback(0);
	}
	
	/* д�����ݼĴ�������Ҫд�������д�뷢�ͻ����� */
	SPI_I2S_SendData(FLASH_SPIx, byte);
	
	SPITimeout = SPI_FLAG_TIMEOUT;
	/* �ȴ����ջ������ǿգ�RXNE�¼� */
	while(SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE))
	{
		if((--SPITimeout) == 0) return SPI_TIMEOUT_UserCallback(0);
	}
	
	/* ��ȡ���ݼĴ�������ȡ���ջ��������� */
	return SPI_I2S_ReceiveData(FLASH_SPIx);
}

/**
 * @brief   �ȴ���ʱ�ص�����
 * @param   None
 * @retval  None
 */
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
	 /* �ȴ���ʱ��Ĵ������������Ϣ */
	FLASH_INFO("SPI �ȴ���ʱ!errorCode = %d", errorCode);
	return 0;
}


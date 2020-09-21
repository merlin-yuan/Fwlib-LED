/*
 * 使能 RX 和 TX 引脚 GPIO 时钟和 USART 时钟
 * 初始化 GPIO, 并将 GPIO 复用到 USART 上
 * 配置 USART 参数
 * 配置中断控制器并使能 USART 接收中断
 * 在 USART 接收中断服务函数实现数据接收和发送
 */
#include "bsp_usart.h"
#include "stdio.h"


static void MVIC_Configration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* 开启 时钟 */
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
	
	/* 配置 GPIO */
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 配置 USART */
	/* 配置为 收发模式 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 配置硬件控制流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* 配置波特率 115200 */
	USART_InitStructure.USART_BaudRate = 115200;
	/* 无校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 停止位为1 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 数据字长 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	/* 串口优先级配置 */
	MVIC_Configration();
	
	/* 使能接收中断 */
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(DEBUG_USARTx, ENABLE);
}

/* 发送一个字节 */
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx, ch);
	
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/* 发送一个字符串 */
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
	uint16_t k = 0;
	do
	{
		Usart_SendByte(pUSARTx, *(str+k));
		k++;
	} while (*(str+k) != '\0');
	
	/* 等待发从完成 */
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

/* 中断服务函数 */
void DEBUG_USART_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)
	{
		USART_SendData(DEBUG_USARTx, USART_ReceiveData(DEBUG_USARTx));
	}
}
	
/* 重指向输出位置 */
int fputc(int ch, FILE *F)
{
	Usart_SendByte(DEBUG_USARTx, ch);
	return ch;
}

/* 重指向输入位置 */
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);
	
	return USART_ReceiveData(DEBUG_USARTx);
}
	


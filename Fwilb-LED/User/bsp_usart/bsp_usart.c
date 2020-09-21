/*
 * ʹ�� RX �� TX ���� GPIO ʱ�Ӻ� USART ʱ��
 * ��ʼ�� GPIO, ���� GPIO ���õ� USART ��
 * ���� USART ����
 * �����жϿ�������ʹ�� USART �����ж�
 * �� USART �����жϷ�����ʵ�����ݽ��պͷ���
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
	
	/* ���� ʱ�� */
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
	
	/* ���� GPIO */
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� USART */
	/* ����Ϊ �շ�ģʽ */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ����Ӳ�������� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* ���ò����� 115200 */
	USART_InitStructure.USART_BaudRate = 115200;
	/* ��У�� */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* ֹͣλΪ1 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* �����ֳ� */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	/* �������ȼ����� */
	MVIC_Configration();
	
	/* ʹ�ܽ����ж� */
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);
	
	/* ʹ�ܴ��� */
	USART_Cmd(DEBUG_USARTx, ENABLE);
}

/* ����һ���ֽ� */
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx, ch);
	
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/* ����һ���ַ��� */
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
	uint16_t k = 0;
	do
	{
		Usart_SendByte(pUSARTx, *(str+k));
		k++;
	} while (*(str+k) != '\0');
	
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

/* �жϷ����� */
void DEBUG_USART_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)
	{
		USART_SendData(DEBUG_USARTx, USART_ReceiveData(DEBUG_USARTx));
	}
}
	
/* ��ָ�����λ�� */
int fputc(int ch, FILE *F)
{
	Usart_SendByte(DEBUG_USARTx, ch);
	return ch;
}

/* ��ָ������λ�� */
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);
	
	return USART_ReceiveData(DEBUG_USARTx);
}
	


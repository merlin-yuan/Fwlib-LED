/*
 * ʹ��GPIO�˿�ʱ��
 * ��ʼ��GPIOĿ������Ϊ����ģʽ���������룩
 * 
 * ��ʼ�����������жϵ�GPIO
 * ��ʼ�� EXTI
 * ���� NVIC
 * ��д�жϷ�����
 */
#include "bsp_key.h"

/* ���� NVIC �ж�Դ�����ȼ���ʹ�� */
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* �������ȼ� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* �����ж�Դ������ 1 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	/* ������ռ���ȼ� */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* ���������ȼ� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* ʹ���ж�ͨ�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* �����ж�Դ������ 2 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_KEY_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	NVIC_Configuration();
	
	/* ��ʼ�����������жϵ�GPIO */
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK | KEY2_INT_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/* KEY1 */
	GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
	/* KEY2 */
	GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
	
	/* ��ʼ�� EXTI */
	/*  EXTI GPIOԴ */
	GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	/* KEY1 */	
	EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* KEY2 */
	GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;
	EXTI_Init(&EXTI_InitStructure);
}
/* �жϷ������ */
uint8_t key_1 = 1, key_2 = 0;
void KEY1_IRQHandler(void)
{
	if (EXTI_GetFlagStatus(KEY1_INT_EXTI_LINE) != RESET)
	{
		key_1 ^= 0x01;
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);
	}
}

void KEY2_IRQHandler(void)
{
	if (EXTI_GetFlagStatus(KEY2_INT_EXTI_LINE) != RESET)
	{
		key_2 += 0x01;
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);
	}
}


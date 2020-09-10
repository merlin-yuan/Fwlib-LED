/*
 * 使能GPIO端口时钟
 * 初始化GPIO目标引脚为输入模式（浮空输入）
 * 
 * 初始化用来产生中断的GPIO
 * 初始化 EXTI
 * 配置 NVIC
 * 编写中断服务函数
 */
#include "bsp_key.h"

/* 配置 NVIC 中断源，优先级，使能 */
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 设置优先级 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* 配置中断源：按键 1 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	/* 设置抢占优先级 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 设置子优先级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断通道 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* 配置中断源：按键 2 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_KEY_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	NVIC_Configuration();
	
	/* 初始化用来产生中断的GPIO */
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK | KEY2_INT_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/* KEY1 */
	GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
	/* KEY2 */
	GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
	
	/* 初始化 EXTI */
	/*  EXTI GPIO源 */
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
/* 中断服务程序 */
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


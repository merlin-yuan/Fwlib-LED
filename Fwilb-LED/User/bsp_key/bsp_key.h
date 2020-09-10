#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"


/* KEY1 SW1 PA0 */
#define KEY1_INT_GPIO_PORT			GPIOA
#define KEY1_INT_GPIO_CLK			(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN			GPIO_Pin_0
#define KEY1_INT_EXTI_PORTSOURCE	GPIO_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE		GPIO_PinSource0
#define KEY1_INT_EXTI_LINE			EXTI_Line0
#define KEY1_INT_EXTI_IRQ			EXTI0_IRQn
#define KEY1_IRQHandler				EXTI0_IRQHandler

/* KEY2 SW3 PC13 */
#define KEY2_INT_GPIO_PORT			GPIOC
#define KEY2_INT_GPIO_CLK			(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO)
#define KEY2_INT_GPIO_PIN			GPIO_Pin_13
#define KEY2_INT_EXTI_PORTSOURCE	GPIO_PortSourceGPIOC
#define KEY2_INT_EXTI_PINSOURCE		GPIO_PinSource13
#define KEY2_INT_EXTI_LINE			EXTI_Line13
#define KEY2_INT_EXTI_IRQ			EXTI15_10_IRQn
#define KEY2_IRQHandler				EXTI15_10_IRQHandler
/* RESET SW2 */

extern uint8_t key_1;
extern uint8_t key_2;
void EXTI_KEY_Config(void);
#endif /* __BSP_KEY_H */

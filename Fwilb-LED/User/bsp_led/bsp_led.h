#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

/* LED Green */
#define LED_G_GPIO_CLK			RCC_APB2Periph_GPIOB
#define LED_G_GPIO_PORT			GPIOB
#define LED_G_GPIO_PIN			GPIO_Pin_0

/* LED Blue */
#define LED_B_GPIO_CLK			RCC_APB2Periph_GPIOB
#define LED_B_GPIO_PORT			GPIOB
#define LED_B_GPIO_PIN			GPIO_Pin_1

/* LED Red */
#define LED_R_GPIO_CLK			RCC_APB2Periph_GPIOB
#define LED_R_GPIO_PORT			GPIOB
#define LED_R_GPIO_PIN			GPIO_Pin_5


/* Toggle */
#define GPIO_ToggleBits(p,i)		{p->ODT ^= i;}


/* LED ON/OF */
#define LED_G_OFF		GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN)
#define LED_G_ON		GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN)
#define LED_G_TOGGLE	GPIO_ToggleBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN)

#define LED_B_OFF		GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN)
#define LED_B_ON		GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN)
#define LED_B_TOGGLE	GPIO_ToggleBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN)

#define LED_R_OFF		GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN)
#define LED_R_ON		GPIO_ResetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN)
#define LED_R_TOGGLE	GPIO_ToggleBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN)

/* Red */
#define LED_RED			{LED_G_OFF; LED_B_OFF; LED_R_ON;}
/* Green */
#define LED_GREEN		{LED_G_ON; LED_B_OFF; LED_R_OFF;}
/* Blue */
#define LED_BLUE		{LED_G_OFF; LED_B_ON; LED_R_OFF;}
/* Yellow (Red + Green) */
#define LED_YELLOW		{LED_G_ON; LED_B_OFF; LED_R_ON;}
/* Purple (Red + Blue) */
#define LED_PURPLE		{LED_G_OFF; LED_B_ON; LED_R_ON;}
/* Cyan (Green + Blue) */
#define LED_CYAN		{LED_G_ON; LED_B_ON; LED_R_OFF;}
/* White (Red + Green + Blue) */
#define LED_WHITE		{LED_G_ON; LED_B_ON; LED_R_ON;}
/* Black (All OFF)*/
#define LED_BLACK		{LED_G_OFF; LED_B_OFF; LED_R_OFF;}


void LED_GPIO_Config(void);

#endif /* __BSP_LED_H */

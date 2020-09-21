#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_clkconfig.h"
#include "bsp_systick.h"
#include "bsp_debug.h"
#include "bsp_usart.h"

#define SOFT_DELAY		Delay_ms(1000)


int main(void)
{
	// 来到这里的时候，系统的时钟已经被配置成72M。
	// 修改系统时钟配置 8 * 9 = 72MHz
	HSE_SetSysClock(RCC_PLLMul_8);
//	HSE_SetSysClock(RCC_PLLMul_8);
	/* 初始化 滴答定时器 */
	SysTick_Init(); 
	/* 初始化 USART1 */
	USART_Config();
	/* 初始化 LED GPIO */
	LED_GPIO_Config();
	/* 初始化 KEY1/KEY2 */
	EXTI_KEY_Config();
	
	
	Usart_SendString(DEBUG_USARTx, "Light up the led light \r\n");
	while(1)
	{
		/* 验证 按键中断是否起作用 */
		if (key_1)
		{
			/*轮流显示 红绿蓝黄紫青白 颜色*/
			LED_RED;
			SOFT_DELAY;
			
			LED_GREEN;
			SOFT_DELAY;
			
			LED_BLUE;
			SOFT_DELAY;
			
			LED_YELLOW;
			SOFT_DELAY;
			
			LED_PURPLE;
			SOFT_DELAY;
			
			LED_CYAN;
			SOFT_DELAY;
			
			LED_WHITE;
			SOFT_DELAY;
			
			LED_BLACK;
			SOFT_DELAY;
		}
		else
		{
			/*单色呼吸显示 红绿蓝黄紫青白 颜色*/
			switch(key_2)
			{
				case 1:
					LED_RED;
					break;
				case 2:
					LED_GREEN;
					break;
				case 3:
					LED_BLUE;
					break;
				case 4:
					LED_YELLOW;
					break;
				case 5:
					LED_PURPLE;
					break;
				case 6:
					LED_CYAN;
					break;
				case 7:
					LED_WHITE;
					break;
				default:
					key_2 = 1;
					break;
				
			}
			SOFT_DELAY;			
			LED_BLACK;
			SOFT_DELAY;
		}
	//	DEBUG("Test \r\n");
	}
}


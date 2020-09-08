#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"

#define SOFT_DELAY		Delay(0x8FFFFF)

void Delay(uint32_t nCount);

int main(void)
{
	// 来到这里的时候，系统的时钟已经被配置成72M。
	/* 初始化 LED GPIO */
	LED_GPIO_Config();
	
	while(1)
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
}

void Delay(uint32_t nCount)
{
	while(--nCount > 0);
}

#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"

#define SOFT_DELAY		Delay(0x8FFFFF)

void Delay(uint32_t nCount);

int main(void)
{
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	/* ��ʼ�� LED GPIO */
	LED_GPIO_Config();
	
	while(1)
	{
		/*������ʾ ������������� ��ɫ*/
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

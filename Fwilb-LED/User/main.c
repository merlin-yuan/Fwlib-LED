#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_clkconfig.h"
#include "bsp_systick.h"
#include "bsp_debug.h"
#include "bsp_usart.h"

#define SOFT_DELAY		Delay_ms(1000)


int main(void)
{
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	// �޸�ϵͳʱ������ 8 * 9 = 72MHz
	HSE_SetSysClock(RCC_PLLMul_8);
//	HSE_SetSysClock(RCC_PLLMul_8);
	/* ��ʼ�� �δ�ʱ�� */
	SysTick_Init(); 
	/* ��ʼ�� USART1 */
	USART_Config();
	/* ��ʼ�� LED GPIO */
	LED_GPIO_Config();
	/* ��ʼ�� KEY1/KEY2 */
	EXTI_KEY_Config();
	
	
	Usart_SendString(DEBUG_USARTx, "Light up the led light \r\n");
	while(1)
	{
		/* ��֤ �����ж��Ƿ������� */
		if (key_1)
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
		else
		{
			/*��ɫ������ʾ ������������� ��ɫ*/
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


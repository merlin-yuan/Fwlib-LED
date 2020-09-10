/* 
 * ʹ��GPIO�˿�ʱ��
 * ��ʼ��Ŀ������Ϊ�������ģʽ
 */
#include "bsp_led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK | LED_B_GPIO_CLK | LED_R_GPIO_CLK, ENABLE);
	
	/* ���ö˿����ģʽ */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/* Green */
	GPIO_InitStruct.GPIO_Pin = LED_G_GPIO_PIN;
	GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);
	/* Blue */
	GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN;
	GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);
	/* Red */
	GPIO_InitStruct.GPIO_Pin = LED_R_GPIO_PIN;
	GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);
	
	/* �ر����� LED���ơ�*/
	LED_BLACK;


}

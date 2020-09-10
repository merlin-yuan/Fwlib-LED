/* 
 * 使能GPIO端口时钟
 * 初始化目标引脚为推挽输出模式
 */
#include "bsp_led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK | LED_B_GPIO_CLK | LED_R_GPIO_CLK, ENABLE);
	
	/* 配置端口输出模式 */
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
	
	/* 关闭所有 LED　灯　*/
	LED_BLACK;


}

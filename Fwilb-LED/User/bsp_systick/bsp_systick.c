/*
 * 设置重装在寄存器的值
 * 清除当前数值寄存器的值
 * 配置控制与状态寄存器
 */
 #include "bsp_systick.h"
 
static __IO uint32_t TimingDelay;
 
void SysTick_Init(void)
{
	/* SystemCoreClock / 100000		10us
	 * SystemCoreClock / 1000		1ms
	 */
	if (SysTick_Config(SystemCoreClock / 100000))
	{
		while(1);
	}
}
void Delay_us(__IO uint32_t nTime)
{
	TimingDelay = nTime;
	
	/* 开启滴答定时器 */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(TimingDelay);
	
}
 
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}


/*
 * ������װ�ڼĴ�����ֵ
 * �����ǰ��ֵ�Ĵ�����ֵ
 * ���ÿ�����״̬�Ĵ���
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
	
	/* �����δ�ʱ�� */
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


/*
 * 开启 HSE/HSI 等待 HSE/HSI 稳定
 * 设置 AHB、APB2、APB1 的预分频因子
 * 设置 PLL 的时钟来源，和 PLL 的倍频因子，设置各种频率主要在这里设置
 * 开启 PLL 等待 PLL稳定
 * 把 PLLCK 切换为系统时钟 SYSCLK
 * 读取系统切换状态，确保 PLLCLK被选为系统时钟
 */
#include "bsp_clkconfig.h"

/* 
 * @param  pllmull: specifies the PLL multiplication factor.
 * this parameter can be RCC_PLLMul_x where x:[2,16] 
 */
void HSE_SetSysClock(uint32_t pllmull)
{
    __IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;
    /* 复位为上电默认 HSI 时钟 */
    RCC_DeInit();

    /* 开启 HSE 时钟 */
    RCC_HSEConfig(CR_HSEON_Set);

    /* 等待 HSE 时钟稳定 */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS)
    {
        /*-------------------- 使能 FLASH 预缓存 -----------------*/
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        /* 配置等待周期 */
        /* 
         * 0 等待周期  当0 < SYSCLK < 24MHz
         * 1 等待周期  当24MHz < SYSCLK < 48MHz
         * 2 等待周期  当48MHz < SYSCLK < 72MHz
         */
        FLASH_SetLatency(FLASH_Latency_2);
        /*------------------------------------------------------*/

        /* 设置 AHB、APB2、APB1 预分频因子 */
        /* SYSCLK=HCLK=APB2CLK=2APB1CLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* 设置 PLL 时钟倍频因子，时钟来源 */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmull);

        /* 开启 PLL 时钟，等待稳定 */
        RCC_PLLCmd(ENABLE);
        /* Wait till HSE is ready and if Time out is reached exit */
        while((StartUpCounter++ != HSE_STARTUP_TIMEOUT) && (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET));

        if (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET)
        {
            /* 把 PLLCK 切换为系统时钟 SYSCLK */
            RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

            /* 读取系统切换状态，确保 PLLCLK被选为系统时钟 */
            while (RCC_GetSYSCLKSource() != 0x08);
        }
    } 
    else 
    {
        /* HSE 启动失败 */
    }

    /* 读取系统切换状态，确保 PLLCLK被选为系统时钟 */
    if (RCC_GetSYSCLKSource() != 0x08)
    {
        /* 未设置成功 */
    }
}

/* 
 * @param  pllmull: specifies the PLL multiplication factor.
 * this parameter can be RCC_PLLMul_x where x:[2,16] 
 */
void HSI_SetSysClock(uint32_t pllmull)
{
    __IO uint32_t StartUpCounter = 0, HSIStartUpStatus = 0;
    /* 复位为上电默认 HSI 时钟 */
    RCC_DeInit();

    /* 开启 HSI 时钟 */
    RCC_HSICmd(ENABLE);

    /* 等待 HSI 时钟稳定 */
    while((StartUpCounter++ != HSE_STARTUP_TIMEOUT) && (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET));
    if (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != RESET)
    {
        /*-------------------- 使能 FLASH 预缓存 -----------------*/
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        /* 配置等待周期 */
        /* 
         * 0 等待周期  当0 < SYSCLK < 24MHz
         * 1 等待周期  当24MHz < SYSCLK < 48MHz
         * 2 等待周期  当48MHz < SYSCLK < 72MHz
         */
        FLASH_SetLatency(FLASH_Latency_2);
        /*------------------------------------------------------*/

        /* 设置 AHB、APB2、APB1 预分频因子 */
        /* SYSCLK=HCLK=APB2CLK=2APB1CLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* 设置 PLL 时钟倍频因子，时钟来源 */
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pllmull);

        /* 开启 PLL 时钟，等待稳定 */
        RCC_PLLCmd(ENABLE);
        /* Wait till HSE is ready and if Time out is reached exit */
        StartUpCounter = 0;
        while((StartUpCounter++ != HSE_STARTUP_TIMEOUT) && (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET));

        if (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET)
        {
            /* 把 PLLCK 切换为系统时钟 SYSCLK */
            RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

            /* 读取系统切换状态，确保 PLLCLK被选为系统时钟 */
            while (RCC_GetSYSCLKSource() != 0x08);
        }
    } 
    else
    {
        /* 开启 HSI 失败 */
    }

    /* 读取系统切换状态，确保 PLLCLK被选为系统时钟 */
    if (RCC_GetSYSCLKSource() != 0x08)
    {
        /* 未设置成功 */
    }
}

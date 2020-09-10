#ifndef __BSP_CLKCONFIG_H
#define __BSP_CLKCONFIG_H

#include "stm32f10x.h"

void HSE_SetSysClock(uint32_t pllmull);
void HSI_SetSysClock(uint32_t pllmull);

#endif /* __BSP_CLKCONFIG_H */

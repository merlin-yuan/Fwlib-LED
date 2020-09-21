#ifndef __BSP_SPI_FLASH_H
#define __BSP_SPI_FLASH_H

#include "stm32f10x.h"
#include <stdio.h>

/* �����-��ͷ ****************************/

/* WIP(busy)��־��FLASH�ڲ�����д�� */
#define WIP_Flag				0x01
#define Dummy_Byte				0xFF
/* �����-���� ****************************/

/* SPI�ӿڶ���-��ͷ **********************/
#define FLASH_SPIx						SPI1
#define FLASH_SPI_APBxClock_Fun			RCC_APB2PeriphClockCmd
#define FLASH_SPI_CLK					RCC_APB2Periph_SPI1

/* CS(NSS)���ţ�Ƭѡѡ��ͨGPIO���� */
#define FLASH_SPI_CS_APBxClock_Fun		RCC_APB2PeriphClockCmd
#define FLASH_SPI_CS_CLK				RCC_APB2Periph_GPIOA
#define FLASH_SPI_CS_PIN				GPIO_Pin_4
#define FLASH_SPI_CS_PORT				GPIOA

/* SCK ʱ������*/
#define FLASH_SPI_SCK_APBxClock_Fun		RCC_APB2PeriphClockCmd
#define FLASH_SPI_SCK_CLK				RCC_APB2Periph_GPIOA
#define FLASH_SPI_SCK_PIN				GPIO_Pin_5
#define FLASH_SPI_SCK_PORT				GPIOA

/* MISO ����*/
#define FLASH_SPI_MISO_APBxClock_Fun	RCC_APB2PeriphClockCmd
#define FLASH_SPI_MISO_CLK				RCC_APB2Periph_GPIOA
#define FLASH_SPI_MISO_PIN				GPIO_Pin_6
#define FLASH_SPI_MISO_PORT				GPIOA

/* MOSI ����*/
#define FLASH_SPI_MOSI_APBxClock_Fun	RCC_APB2PeriphClockCmd
#define FLASH_SPI_MOSI_CLK				RCC_APB2Periph_GPIOA
#define FLASH_SPI_MOSI_PIN				GPIO_Pin_7
#define FLASH_SPI_MOSI_PORT				GPIOA

#define FLASH_SPI_CS_LOW()		GPIO_ResetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN)
#define FLASH_SPI_CS_HIGH()		GPIO_SetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN)
/* SPI �ӿڶ���-��β *************************/

/* �ȴ���ʱʱ�� */
#define SPI_FLAG_TIMEOUT			((uint32_t)0x1000)
#define SPI_LONG_TIMEOUT			((uint32_t)(10 * SPI_FLAG_TIMEOUT))

/* ��Ϣ��� */
#define FLASH_DEBUG_ON			1
#define FLASH_INFO(fmt,arg...)			printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)			printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)			do{\
											if(FLASH_DEBUG_ON)\
											printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__,##arg);\
										}while(0)


#endif /* __BSP_SPI_FLASH_H */

#ifndef __BSP_DEBUG_H
#define __BSP_DEBUG_H

#include "stdio.h"
#define __DEBUG__

#ifdef __DEBUG__
#define DEBUG(fmt,arg...)	printf("File: "__FILE__", Line: %05d: "fmt, __LINE__, ##arg)
#else
#define DEBUG(fmt,arg...)
#endif

#endif /* __BSP_DEBUG_H */

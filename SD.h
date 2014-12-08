#ifndef SD_HEADER
#define SD_HEADER

// Includes
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"+
#include "stm32f4xx_rcc.h"
#include "misc.h"

#include "attributes.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_fatfs.h"
#include <stdio.h>
#include <string.h>


// Defines
#define _MAX_FILES 20


// Functions
FRESULT SDInit(void);
FRESULT SDGetNames(const TCHAR* path);
uint16_t SDGet16(TCHAR* fname);
void SDPut16(TCHAR* fname, uint16_t data);

#endif /* SD_HEADER */

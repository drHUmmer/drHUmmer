#ifndef SD_HEADER
#define SD_HEADER

// Includes
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

#include "attributes.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_fatfs.h"
#include <stdio.h>
#include <string.h>

#include "interrupt.h"
// Defines
#define _MAX_FILES 20
#define WAV_BUF_SIZE 512


// Globals
TCHAR	fnames[_MAX_FILES][13];
uint8_t	nfiles;

uint16_t wavBufA[WAV_BUF_SIZE];
uint16_t wavBufB[WAV_BUF_SIZE];
//uint32_t bufCnt = 0;


// Functions
FRESULT SDInit(void);
FRESULT SDGetNames(const TCHAR* path);
uint16_t SDGet16(TCHAR* fname, uint16_t clusterIdx);
FRESULT SDGet512(uint16_t* buf16, TCHAR* fname, uint32_t clusterIdx);
void SDPut16(TCHAR* fname, uint16_t data);


#endif /* SD_HEADER */

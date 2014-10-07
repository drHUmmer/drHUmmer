# ifndef DAC_HEADER
# define DAC_HEADER

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_rcc.h"

// structure used for GPIO setting
GPIO_InitTypeDef GPIO_InitStructure;

//structure used for DAC settings
DAC_InitTypeDef dacSettings;

void dacInit(void);
void dacPut(uint16_t data);

# endif /*DAC_HEADER*/

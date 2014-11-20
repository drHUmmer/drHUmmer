//#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define PIC_NSS		GPIO_Pin_8
#define LED_SS 		GPIO_Pin_9

#define DUMMY_BYTE	0x00

void SPI3_Init(void);
void SPI_PIC_Send(uint8_t data);
void SPI_LED_Send(uint8_t data);
uint8_t SPI_PIC_Receive(void);

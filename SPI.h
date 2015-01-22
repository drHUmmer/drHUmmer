//#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "ui.h"

//#define DEBUG
//#define LEDDEBUG

#define PIC_NSS		GPIO_Pin_9		// 8
#define LED_SS 		GPIO_Pin_8		// 9

#define DUMMY_BYTE	0x00

/*PIC command defines*/
#define PIC_RESET				0xF0
#define PIC_GET_BUTTON			0x20
#define PIC_GET_ROTARY			0x40
#define PIC_BUTTON_EDGE			0x80
#define	PIC_BUTTON_MODE			0xA0

#define PIC_EDGE_RISING			0x00
#define PIC_EDGE_FALLING		0x10
#define	PIC_MODE_MOMENT			0x00
#define PIC_MODE_TOGGLE			0x10

#define	PIC_BUTTONS_ALL			0x00
#define PIC_BUTTONS_1			0x01
#define PIC_BUTTONS_2			0x02
#define PIC_BUTTONS_3			0x03
#define PIC_BUTTONS_4			0x04

#define PIC_ROTARY_ALL			0x00
#define PIC_ROTARY_1			0x01
#define PIC_ROTARY_2			0x02
#define PIC_ROTARY_3			0x03
#define PIC_ROTARY_4			0x04
#define PIC_ROTARY_5			0x05
#define PIC_ROTARY_6			0x06
#define PIC_ROTARY_7			0x07
#define PIC_ROTARY_8			0x08
#define PIC_ROTARY_9			0x09
#define PIC_ROTARY_10			0x0A
#define PIC_ROTARY_11			0x0B

#define PIC_B_E_SEQ_ALL			0x01
#define PIC_B_E_DRUM_ALL		0x02
#define PIC_B_E_PLAY			0x03
#define PIC_B_E_CLEAR			0x04
#define PIC_B_E_FX				0x05
#define PIC_B_E_PATT_LEN		0x06
#define PIC_B_E_PATT_SEL		0x07
#define PIC_B_E_ALT				0x08
#define PIC_B_E_MENU1			0x09
#define PIC_B_E_MENU2			0x0A
#define PIC_B_E_EXTRA1			0x0B
#define PIC_B_E_EXTRA2			0x0C

#define PIC_B_M_SEQ_ALL			0x01
#define PIC_B_M_DRUM_ALL		0x02
#define PIC_B_M_PLAY			0x03
#define PIC_B_M_CLEAR			0x04
#define PIC_B_M_FX				0x05
#define PIC_B_M_PATT_LEN		0x06
#define PIC_B_M_PATT_SEL		0x07
#define PIC_B_M_ALT				0x08
#define PIC_B_M_MENU1			0x09
#define PIC_B_M_MENU2			0x0A
#define PIC_B_M_EXTRA1			0x0B
#define PIC_B_M_EXTRA2			0x0C

#define PIC_NO_SETTING			0x00

void SPI3_Init(void);
void SPI_PIC_Send(uint8_t command,uint8_t setting,uint8_t address);
int8_t SPI_PIC_Receive(void);

//#ifdef DEBUG	/*	Debug mode	*/
//void SPI_LED_Send(void);
//#else

#ifdef LEDDEBUG
void SPI_LED_Send(uint16_t data);
#else
void SPI_LED_Send(void);
#endif
//#endif


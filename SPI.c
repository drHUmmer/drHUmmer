#include "SPI.h"

void SPI3_Init(void)
{
	/*****************
	 * 	SPI config & init
	 * 	PC8  = PIC NSS
	 * 	PC9  = LED NSS
	 * 	PC10 = SCLK
	 * 	PC11 = MISO
	 * 	PC12 = MOSI
	 *****************/

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);				//enable APB clock for SPI3
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);				//enable AHB peripheral clock for GPIO bank C

	GPIO_InitTypeDef GPIO_InitStruct;

	//NSS pins configured as GPIO outputs; software managed
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10;	//MOSI | MISO | CLK
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			//DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SPI3);		//connect alt functions to pins
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SPI3);
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	SPI_InitTypeDef SPI3_InitStruct;
	SPI3_InitStruct.SPI_CPOL = SPI_CPOL_Low;							//clock idle low
	SPI3_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;							//capture on 1st edge
	SPI3_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;					//Shift MSB first
	SPI3_InitStruct.SPI_DataSize = SPI_DataSize_8b;						//8 bits per transfer
	SPI3_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;	//BaudRate = APB1 / Prescaler = 42MHz / 8 = 5.25MHz
	SPI3_InitStruct.SPI_Mode = SPI_Mode_Master;							//Master mode
	SPI3_InitStruct.SPI_NSS = SPI_NSS_Soft;								//Software managed Slave Select to leave pin available
	SPI3_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//Full duplex over 2 data lines
	SPI3_InitStruct.SPI_CRCPolynomial = 0x1;							//Not using this, but needs to be >= 0x1
	SPI_Init(SPI3, &SPI3_InitStruct);

	SPI_CalculateCRC(SPI3, DISABLE);									//Don't calculate CRC
	SPI_Cmd(SPI3, ENABLE);												//Enable SPI3
}


void SPI_PIC_Send(uint8_t command,uint8_t setting,uint8_t address)
{
	uint16_t dummy;
	uint8_t data = (command | setting | address);

	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until SPI3 is available
	while(SPI3->SR & SPI_I2S_FLAG_BSY);

	if(!(SPI3->CR1 & SPI_CPHA_2Edge))
	{
		SPI3->CR1 &= ~((uint16_t)SPI_CR1_SPE);
		SPI3->CR1 |= (uint16_t)SPI_CPHA_2Edge;
		SPI3->CR1 |= SPI_CR1_SPE;
	}

	GPIO_ResetBits(GPIOC, PIC_NSS);										//select PIC
	SPI3->DR = data;													//send data
	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until finished sending data
	while(SPI3->SR & SPI_I2S_FLAG_BSY);									//
	GPIO_SetBits(GPIOC, PIC_NSS);										//deselect PIC
	dummy = SPI3->DR;													//access data register to avoid overrun error flag
}

#ifdef DEBUG	/*	debug mode	*/
void SPI_LED_Send(uint16_t data)
{
	uint8_t dummy;
	uint8_t dataMSB = ((data & 0xFF00)>>8);
	uint8_t dataLSB = (data & 0x00FF);

	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until SPI3 is available
	while(SPI3->SR & SPI_I2S_FLAG_BSY);

	if(SPI3->CR1 & SPI_CPHA_2Edge)
	{
		SPI3->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_SPE);
		SPI3->CR1 &= (uint16_t)~((uint16_t)SPI_CPHA_2Edge);
		SPI3->CR1 |= SPI_CR1_SPE;
	}

	GPIO_ResetBits(GPIOC, LED_SS);										//select LEDs
	SPI3->DR = dataMSB;													//send MSByte
	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until finished sending data
	while(SPI3->SR & SPI_I2S_FLAG_BSY);									//
	SPI3->DR = dataLSB;													//send LSByte
	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until finished sending data
	while(SPI3->SR & SPI_I2S_FLAG_BSY);									//
	GPIO_SetBits(GPIOC, LED_SS);										//deselect LEDs
	dummy = SPI3->DR;													//access data register to avoid overrun error flag
}
#else	/*	LED drivers use different settings from shift registers	*/
void SPI_LED_Send(uint16_t data)
{
	uint16_t dummy;
	uint8_t dataMSB = ((data & 0xFF00)>>8);
	uint8_t dataLSB = (data & 0x00FF);

	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until SPI3 is available
	while(SPI3->SR & SPI_I2S_FLAG_BSY);

	if(SPI3->CR1 & SPI_CPHA_2Edge)
	{
		SPI3->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_SPE);
		SPI3->CR1 &= (uint16_t)~((uint16_t)SPI_CPHA_2Edge);
		SPI3->CR1 |= SPI_CR1_SPE;
	}

	GPIO_SetBits(GPIOC, LED_SS);										//select LEDs
	SPI3->DR = ~data;													//send data (
	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until finished sending data
	while(SPI3->SR & SPI_I2S_FLAG_BSY);									//
	SPI3->DR = dataLSB;													//send LSByte
	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until finished sending data
	while(SPI3->SR & SPI_I2S_FLAG_BSY);									//
	GPIO_ResetBits(GPIOC, LED_SS);										//deselect LEDs
	dummy = SPI3->DR;													//access data register to avoid overrun error flag
}
#endif		/*	DEBUG	*/

int8_t SPI_PIC_Receive(void)
{
	int8_t data;

	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until SPI3 is available
	while(SPI3->SR & SPI_I2S_FLAG_BSY);

	if(!(SPI3->CR1 & SPI_CPHA_2Edge))
	{
		SPI3->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_SPE);
		SPI3->CR1 |= (uint16_t)SPI_CPHA_2Edge;
		SPI3->CR1 |= SPI_CR1_SPE;
	}

	GPIO_ResetBits(GPIOC, PIC_NSS);										//select PIC
	SPI3->DR = DUMMY_BYTE;												//send dummy
	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until finished sending (receiving)
	while(SPI3->SR & SPI_I2S_FLAG_BSY);									//
	GPIO_SetBits(GPIOC, PIC_NSS);										//deselect PIC

	data = SPI3->DR;													//retrieve received data

	return data;
}
#ifndef __RINGBUFF_H
#define __RINGBUFF_H

#include "stm32f4xx.h"

#define BUFFER_SIZE 64

// type definition for FIFO circular buffer
typedef struct ringbuffer
{
	uint16_t buffer[BUFFER_SIZE];		// Array to hold the buffer data
	volatile uint32_t head;				// Position to write data to next
	volatile uint32_t tail;				// Position to read data from next
} RingBuffer_TypeDef;

void RingBufferInit(void);
//RingBuffer_TypeDef* Create_Rbuffer(void);
uint8_t Write_Rbuffer(RingBuffer_TypeDef *buffer, uint16_t data);
uint16_t Read_Rbuffer(RingBuffer_TypeDef *buffer);

RingBuffer_TypeDef bass_buff;			// Bass drum ADC input buffer
RingBuffer_TypeDef snare_buff;			// Snare drum ADC input buffer
RingBuffer_TypeDef dac_buff;			// DAC output buffer
RingBuffer_TypeDef debug_buff;			// debug buffer

RingBuffer_TypeDef *bass_buff_p;		// buffer pointers
RingBuffer_TypeDef *snare_buff_p;
RingBuffer_TypeDef *dac_buff_p;
RingBuffer_TypeDef *debug_buff_p;

#endif	/* __RINGBUFF_H */

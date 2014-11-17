#include "ringbuff.h"


/***************************************************************
 * 						RingBufferInit
 * 	Description: Initialises ring buffers with 0 for
 * 				 all values. ADD NEW BUFFERS AS NEEDED
 ***************************************************************/
void RingBufferInit(void)
{
	uint8_t i;
	for(i=0;i<BUFFER_SIZE;i++)
	{
		bass_buff.buffer[i] = 0;
		snare_buff.buffer[i] = 0;
		dac_buff.buffer[i] = 0;
		debug_buff.buffer[i] = 0;
	}
	bass_buff.head = 0;
	snare_buff.head = 0;
	dac_buff.head = 0;
	debug_buff.head = 0;
	
	bass_buff.tail = 0;
	snare_buff.tail = 0;
	dac_buff.tail = 0;
	debug_buff.tail = 0;

	bass_buff_p = &bass_buff;
	snare_buff_p = &snare_buff;
	dac_buff_p = &dac_buff;
	debug_buff_p = &debug_buff;
}

/***************************************************************
 * 						Write_Rbuffer
 * 	Description: Writes data to the appropriate location
 * 				 in a ring buffer. Returns -1 if tail
 * 				 would be overwritten.
 * 	Variables  : *buffer ; pointer to ring buffer struct
 * 				 data	 ; 16 bit unsigned data
 ***************************************************************/
uint8_t Write_Rbuffer(RingBuffer_TypeDef *buffer, uint16_t data)
{
	uint32_t next = (uint32_t)(buffer->head + 1) % BUFFER_SIZE;

	if(next != buffer->tail)
	{
		buffer->buffer[buffer->head] = data;
		buffer->head = next;
		return 0;
	}
	else
	{
		return -1;
	}
}

/***************************************************************
 * 						Read_Rbuffer
 * 	Description: Returns data at the oldest location in
 * 				 a ring buffer.
 * 				 Returns -1 if there's no (unread) data.
 * 	Variables  : *buffer ; pointer to ring buffer struct
 ***************************************************************/
uint16_t Read_Rbuffer(RingBuffer_TypeDef *buffer)
{
	if(buffer->head == buffer->tail)
	{
		return -1;
	}
	else
	{
		uint16_t data = buffer->buffer[buffer->tail];
		buffer->tail = (uint32_t)(buffer->tail + 1) % BUFFER_SIZE;
		return data;
	}
}

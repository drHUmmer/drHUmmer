/*All MIDI in and MIDI out related stuffz*/

/*INCLUDES*/
#include "midi.h"

/*VARIABLES*/
uint16_t midiStatus = 0;
MIDImsg_t midiTest;

/*FUNCTIONS*/

/* MidiInit()
 * Initializes MIDI UART and sets to either input or output
 *
 * Usage:
 * MidiInit(MIDI_MODE);
 */
uint8_t MidiInit(uint8_t mode)
{
	UART2_init(MIDI_BAUD_RATE);	//initialize UART for MIDI

	if(mode)					//set mode to either input or output
	{
		midiStatus |= MIDI_MODE;
	}
	else
	{
		midiStatus &= ~(MIDI_MODE);
	}

	midiStatus |= MIDI_ENABLE;	//set enable bit

	return mode;
}

/* MidiSend()
 * Sends a midi command
 *
 * Usage:
 * MidiSend(&msg, channel);
 */
uint8_t MidiSend(MIDImsg_t *msg, uint8_t ch)
{
	uint8_t temp = (msg->head|ch);

	UART_sendData(MIDI_UART, temp);

	if(msg->head < 0xF0)
	{
		UART_sendData(MIDI_UART, msg->msg1);
		UART_sendData(MIDI_UART, msg->msg2);
	}

	return 0;
}

/* MidiNoteOn()
 *
 */
uint8_t MidiNoteOn()
{

}


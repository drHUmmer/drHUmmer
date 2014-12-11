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
 * Sends a MIDI note on message
 *
 * Usage:
 * MidiNoteOn(note, channel, velocity);
 */
uint8_t MidiNoteOn(notes note, uint8_t ch, uint8_t vel)
{
	MIDImsg_t midiMsg;

	midiMsg.head = (NOTE_ON|ch);
	midiMsg.msg1 = note;
	midiMsg.msg2 = vel;

	MidiSend(&midiMsg, ch);

	return 0;
}

/* MidiNoteOff()
 * Sends a MIDI note off message
 *
 * Usage:
 * MidiNoteOff(note, channel, velocity);
 */
uint8_t MidiNoteOff(notes note, uint8_t ch, uint8_t vel)
{
	MIDImsg_t midiMsg;

	midiMsg.head = (NOTE_OFF|ch);
	midiMsg.msg1 = note;
	midiMsg.msg2 = vel;

	MidiSend(&midiMsg, ch);

	return 0;
}

/* MidiClock()
 * Sends a MIDI clock message
 *
 * Usage:
 * MidiClock();
 */
uint8_t MidiClock(void)
{
	MIDImsg_t midiMsg;

	midiMsg.head = MIDI_CLOCK;
	midiMsg.msg1 = 0;
	midiMsg.msg2 = 0;

	MidiSend(&midiMsg, MIDI_ALL_CH);

	return 0;
}

/* MidiStart()
 * Sends a MIDI start message
 *
 * Usage:
 * MidiStart();
 */
uint8_t MidiStart(void)
{
	MIDImsg_t midiMsg;

	midiMsg.head = MIDI_START;
	midiMsg.msg1 = 0;
	midiMsg.msg2 = 0;

	MidiSend(&midiMsg, MIDI_ALL_CH);

	return 0;
}

/* MidiStop()
 * Sends a MIDI stop message
 *
 * Usage:
 * MidiStop();
 */
uint8_t MidiStop(void)
{
	MIDImsg_t midiMsg;

	midiMsg.head = MIDI_STOP;
	midiMsg.msg1 = 0;
	midiMsg.msg2 = 0;

	MidiSend(&midiMsg, MIDI_ALL_CH);

	return 0;
}

/* MidiContinue()
 * Sends a MIDI continue message
 *
 * Usage:
 * MidiContinue();
 */
uint8_t MidiContinue(void)
{
	MIDImsg_t midiMsg;

	midiMsg.head = MIDI_CONT;
	midiMsg.msg1 = 0;
	midiMsg.msg2 = 0;

	MidiSend(&midiMsg, MIDI_ALL_CH);

	return 0;
}


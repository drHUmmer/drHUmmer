#ifndef MIDI_H
#define MIDI_H

/*INCLUDES*/
#include "UART.h"

/*DEFINES*/
#define MIDI_BAUD_RATE 31250
#define MIDI_UART 2

//midi channel commands, OR these with the channels
#define MIDI_NOTE_ON	0x90
#define MIDI_NOTE_OFF	0x80
#define MIDI_PITCH_BEND	0xE0

//midi system commands
#define MIDI_CLOCK	0xF8
#define MIDI_START	0xFA
#define MIDI_STOP	0xFC
#define MIDI_CONT	0xFB

//midi channels, mind the offset, channel 1 = 0x0
#define MIDI_CH1 	0x00
#define MIDI_CH2 	0x01
#define MIDI_CH3 	0x02
#define MIDI_CH4 	0x03
#define MIDI_CH5 	0x04
#define MIDI_CH6 	0x05
#define MIDI_CH7 	0x06
#define MIDI_CH8 	0x07
#define MIDI_CH9 	0x08
#define MIDI_CH10 	0x09
#define MIDI_CH11 	0x0A
#define MIDI_CH12 	0x0B
#define MIDI_CH13 	0x0C
#define MIDI_CH14 	0x0D
#define MIDI_CH15 	0x0E
#define MIDI_CH16 	0x0F

//defines for MIDI status register
#define MIDI_INS1_TRIG	(1<<0)
#define MIDI_INS2_TRIG	(1<<1)
#define MIDI_INS3_TRIG	(1<<2)
#define MIDI_INS4_TRIG	(1<<3)
#define MIDI_INS5_TRIG	(1<<4)
#define MIDI_INS6_TRIG	(1<<5)
#define MIDI_MODE		(1<<6)
#define MIDI_ENABLE		(1<<7)
#define MIDI_CHAN		(0xF<<8)
#define MIDI_CONT_FLAG	(1<<12)
#define MIDI_STOP_FLAG	(1<<13)
#define MIDI_START_FLAG	(1<<14)
#define MIDI_PB_FLAG	(1<<15)

typedef struct
{
	uint8_t head;
	uint8_t msg1;
	uint8_t msg2;
}MIDImsg_t;

/*VARIABLES*/
extern uint16_t midiStatus;
extern MIDImsg_t midiTest;

/*FUNCTION PROTOTYPES*/
uint8_t MidiInit(uint8_t mode);

#endif

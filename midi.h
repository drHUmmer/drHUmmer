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
#define MIDI_ALL_CH	0x00
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

enum notes
{
	C0, C_0, D0, D_0, E0, F0, F_0, G0, G_0, A0, A_0, B0,
	C1, C_1, D1, D_1, E1, F1, F_1, G1, G_1, A1, A_1, B1,
	C2, C_2, D2, D_2, E2, F2, F_2, G2, G_2, A2, A_2, B2,
	C3, C_3, D3, D_3, E3, F3, F_3, G3, G_3, A3, A_3, B3,
	C4, C_4, D4, D_4, E4, F4, F_4, G4, G_4, A4, A_4, B4,
	C5, C_5, D5, D_5, E5, F5, F_5, G5, G_5, A5, A_5, B5,
	C6, C_6, D6, D_6, E6, F6, F_6, G6, G_6, A6, A_6, B6,
	C7, C_7, D7, D_7, E7, F7, F_7, G7, G_7, A7, A_7, B7,
	C8, C_8, D8, D_8, E8, F8, F_8, G8, G_8, A8, A_8, B8,
	C9, C_9, D9, D_9, E9, F9, F_9, G9, G_9, A9, A_9, B9
};

/*VARIABLES*/
extern uint16_t midiStatus;
extern MIDImsg_t midiTest;

/*FUNCTION PROTOTYPES*/
uint8_t MidiInit(uint8_t mode);
uint8_t MidiSend(MIDImsg_t *msg, uint8_t ch);
uint8_t MidiNoteOn(notes note, uint8_t ch, uint8_t vel);
uint8_t MidiNoteOff(notes note, uint8_t ch, uint8_t vel);
uint8_t MidiClock(void);
uint8_t MidiStart(void);
uint8_t MidiStop(void);
uint8_t MidiContinue(void);




#endif

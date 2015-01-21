#ifndef __SEQUENCER_H
#define __SEQUENCER_H

#include "stm32f4xx.h"

#define SEQ_LIVE_MODE 		0
#define SEQ_PATTERN_MODE 	1

void sequencerInit(void);

typedef struct
{
	uint16_t id;			// Specifies which instrument this is
	uint16_t sequence;		// Trigger sequence, 1 bit per quarter note
	uint8_t  substeps[16];	// Up to 8 substeps per quarter note
	uint8_t level;			// Level (volume) setting of instrument
	uint8_t tone;			// Tone setting of instrument
	uint32_t file_addr;		// Physical address of file on storage medium
	uint32_t file_length; 	// Length of file (number of samples?)
	uint32_t buffer_loc;	// Pointer to current location in sample buffer
	uint16_t sample;		// Current sample from buffer
	uint8_t  triggerflag;	// Tell DAC to play sample

}Instrument_TypeDef;

typedef struct
{
	uint8_t  playing;		// Self explanatory
	uint8_t	 patt_live_mode;// Pattern mode or live mode selected
	uint32_t BPM;			// Current sequencer BPM
	uint16_t beatclk;		// counter, 24/beat, 6/step
	uint16_t beatmask;		// the current beat (mask, not a counter)
	uint8_t  stepcnt;		// the current beat (counter, not a mask)
	uint8_t	 submask;		// the current substep (mask)
	uint8_t  timerflag;		// Flag for analogue trigger timing
	uint8_t	 instrID;		// Currently selected instrument

/* Structs containing information about active instruments */
	Instrument_TypeDef bassdrum;
	Instrument_TypeDef snaredrum;
	Instrument_TypeDef instr0;
	Instrument_TypeDef instr1;
	Instrument_TypeDef instr2;
	Instrument_TypeDef instr3;

}Sequencer_TypeDef;

Sequencer_TypeDef sequencer;

#endif	/* __SEQUENCER_H */

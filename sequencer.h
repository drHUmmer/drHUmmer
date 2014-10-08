#ifndef __SEQUENCER_H
#define __SEQUENCER_H


typedef struct
{
  uint16_t id;			// Specifies which instrument this is
  uint16_t sequence;	// Trigger sequence, 1 bit per quarter note
  uint16_t level;		// Level (volume) setting of instrument
  uint16_t tone;		// Tone setting of instrument
  uint32_t file_addr;	// Physical address of file on storage medium
  uint32_t file_length; // Length of file (number of samples?)
  uint32_t buffer_loc;	// Pointer to current location in sample buffer
  uint16_t sample;		// Current sample from buffer
  uint8_t  triggerflag;	// Tell DAC to play sample

}Instrument_TypeDef;

typedef struct
{
	uint32_t BPM;		// Current sequencer BPM
	uint16_t beatclk;	// counter, 24/beat
	uint16_t beatmask;	// the current beat (mask, not a counter)
	uint8_t  timerflag;	// tells trigger interrupt whether or not to wait until the next beat (to actually reach 5ms)

	Instrument_TypeDef bassdrum;
	Instrument_TypeDef snaredrum;
	Instrument_TypeDef instr0;
	Instrument_TypeDef instr1;
	Instrument_TypeDef instr2;
	Instrument_TypeDef instr3;

}Sequencer_TypeDef;

Sequencer_TypeDef sequencer;

#endif	/* __SEQUENCER_H */

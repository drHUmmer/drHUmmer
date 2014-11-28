#include "sequencer.h"

void sequencerInit(void)
{
	uint16_t i;

	sequencer.BPM = 125;
	sequencer.beatclk = 0;
	sequencer.stepcnt = 0;
	sequencer.beatmask = 0x8000;				// MSB, first beat
	sequencer.submask = 0x20;					// MSB, first substep

	sequencer.snaredrum.sequence 	= 0x0000;	// 0000 0000 0000 0000			//(a)snare
	sequencer.bassdrum.sequence 	= 0x0000;	// 0000 0000 0000 0000			//(a)bass
	sequencer.instr0.sequence 		= 0x2222;	// 0010 0010 0010 0010			//hihat
	sequencer.instr1.sequence 		= 0x0808;	// 0000 1000 0000 1000			//snare
	sequencer.instr2.sequence 		= 0x8080;	// 1000 1000 1000 1000			//basskick
	sequencer.instr3.sequence 		= 0x0000;	// 0000 0000 0000 0000			//cymbal

	for(i=0;i<16;i++)
	{
		sequencer.snaredrum.substeps[i] = 0x20;	// 0010 0000					//(a)snare
		sequencer.bassdrum.substeps[i] 	= 0x20;	// 0010 0000					//(a)bass
		sequencer.instr0.substeps[i]	= 0x20;	// 0010 0000					//hihat
		sequencer.instr1.substeps[i] 	= 0x20;	// 0010 0000					//snare
		sequencer.instr2.substeps[i] 	= 0x20;	// 0010 0000					//basskick
		sequencer.instr3.substeps[i] 	= 0x20;	// 0010 0000					//cymbal
	}

	sequencer.instr0.tone = 1;
	sequencer.instr0.file_length = 16060;
	sequencer.instr1.tone = 1;
	sequencer.instr1.file_length = 22051;
	sequencer.instr2.tone = 1;
	sequencer.instr2.file_length = 18387;
	sequencer.instr3.tone = 1;
	sequencer.instr3.file_length = 65135;
}

#include "sequencer.h"

void sequencerInit(void)
{
	uint16_t i;

	sequencer.BPM = 100;
	sequencer.beatclk = 0;
	sequencer.stepcnt = 0;
	sequencer.beatmask = 0x8000;				// MSB, first beat
	sequencer.submask = 0x20;					// MSB, first substep

	sequencer.instr0.file_nr 		= 4;
	sequencer.instr1.file_nr 		= 4;
	sequencer.instr2.file_nr 		= 4;
	sequencer.instr3.file_nr 		= 4;

	sequencer.instr0.i 		= 44;
	sequencer.instr1.i 		= 44;
	sequencer.instr2.i 		= 44;
	sequencer.instr3.i 		= 44;

	sequencer.instr0.buffer_loc		= 0;
	sequencer.instr1.buffer_loc		= 0;
	sequencer.instr2.buffer_loc		= 0;
	sequencer.instr3.buffer_loc		= 0;

	sequencer.instr0.level 		= 100;
	sequencer.instr1.level 		= 100;
	sequencer.instr2.level 		= 100;
	sequencer.instr3.level 		= 100;

	sequencer.snaredrum.sequence 	= 0x0000;	// 0000 0000 0000 0000			//(a)snare
	sequencer.bassdrum.sequence 	= 0xFFFF;	// 0000 0000 0000 0000			//(a)bass
	sequencer.instr0.sequence 		= 0x2222;	// 0010 0010 0010 0010			//hihat
	sequencer.instr1.sequence 		= 0x0808;	// 0000 1000 0000 1000			//snare
	sequencer.instr2.sequence 		= 0x8080;	// 1000 1000 1000 1000			//basskick
	sequencer.instr3.sequence 		= 0x0001;	// 0000 0000 0000 0001			//cymbal

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
	sequencer.instr0.file_length = FS_INST0;
	sequencer.instr1.tone = 1;
	sequencer.instr1.file_length = FS_INST1;
	sequencer.instr2.tone = 1;
	sequencer.instr2.file_length = FS_INST2;
	sequencer.instr3.tone = 1;
	sequencer.instr3.file_length = FS_INST3;

	sequencer.bassdrum.sample = 2048;
	sequencer.snaredrum.sample = 2048;
}

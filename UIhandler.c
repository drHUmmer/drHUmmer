#include "UIhandler.h"

//////////////////
// Main Handler //
//////////////////
void UIhandler() {
	// Sequencer
	UIhandler_Sequencer();

	// FX
	UIhandler_FX_IO();
	UIhandler_FX_ROT();
	UIhandler_FX_SWTICH();

	// Menu
	// Functions called in menu.c

	// Drums
	UIhandler_Drum_Levels();
	UIhandler_SelectDrums();

	// Pattern buttons
	// todo: pattern length
	// todo: pattern select

	// Play Button
	UIhandler_PlayButton();

	// Update LEDS
#ifndef LEDDEBUG
	SPI_LED_Send();
#endif
}

///////////////
// Sequencer //
///////////////
void UIhandler_Sequencer (void) {
	uint32_t sequencerButtons = uiInput.buttons & 0xFFFF;

	switch (sequencer.instrID) {
	case 0: sequencer.bassdrum.sequence 	^= sequencerButtons; 	break;	// A1
	case 1: sequencer.snaredrum.sequence 	^= sequencerButtons;	break;	// A2
	case 2: sequencer.instr0.sequence 		^= sequencerButtons;	break;	// D1
	case 3: sequencer.instr1.sequence 		^= sequencerButtons;	break;	// D2
	case 4: sequencer.instr2.sequence 		^= sequencerButtons;	break;	// D3
	case 5: sequencer.instr3.sequence 		^= sequencerButtons;	break;	// D4
	}

	/*
	switch (sequencer.instrID) {
	case 0: SPI_LED_Send(sequencer.bassdrum.sequence);				break;	// A1
	case 1: SPI_LED_Send(sequencer.snaredrum.sequence);				break;	// A2
	case 2: SPI_LED_Send(sequencer.instr0.sequence);				break;	// D1
	case 3: SPI_LED_Send(sequencer.instr1.sequence);				break;	// D2
	case 4: SPI_LED_Send(sequencer.instr2.sequence);				break;	// D3
	case 5: SPI_LED_Send(sequencer.instr3.sequence);				break;	// D4
	}
	*/

	// Reset sequencer button values
	uiInput.buttons &= ~0xFFFF;
}

//////////
// MENU //
//////////
uint8_t UIhandler_Menu_Ok (uint8_t reset) {
	uint8_t returnValue = 0;
	if (BUTTON_MENU_OK) {
		returnValue = 1;

		if (reset)
			uiInput.buttons &= ~BUTTON_MENU_OK;
	}

	return returnValue;
}

uint8_t UIhandler_Menu_Back (uint8_t reset) {
	uint8_t returnValue = 0;
	if (BUTTON_MENU_BACK) {
		returnValue = 1;

		if (reset)
			uiInput.buttons &= ~BUTTON_MENU_BACK;
	}

	return returnValue;
}

int8_t UIhandler_Menu_Rotary (uint8_t reset) {
	int8_t returnValue = 0;
	returnValue = ROTARY_MENU;

	if (reset)
		ROTARY_MENU = 0;

	return returnValue;
}

////////
// FX //
////////
void UIhandler_FX_IO (void) {
	if (BUTTON_FX_ONOFF) {
		if (FXsettings.fxEnable)
			FXsettings.fxEnable = 0;
		else
			FXsettings.fxEnable = 1;

		uiInput.buttons &= ~BUTTON_FX_ONOFF;
	}
}

void UIhandler_FX_SWTICH (void) {
	if (BUTTON_SHIFT) {
		int8_t tempValue;

		// FX 1
		if (ROTARY_FX_1) {
			tempValue = FXsettings.fx1;
			tempValue += ROTARY_FX_1;
			while (tempValue > 4) {			// Effects are 0 till 4
				tempValue -= 5;
			}
			while (tempValue < 0) {
				tempValue += 5;
			}
			FXsettings.fx1 = tempValue;
		}

		// FX 2
		if (ROTARY_FX_2) {
			tempValue = FXsettings.fx2;
			tempValue += ROTARY_FX_2;
			while (tempValue > 4) {			// Effects are 0 till 4
				tempValue -= 5;
			}
			while (tempValue < 0) {
				tempValue += 5;
			}
			FXsettings.fx2 = tempValue;
		}
		uiInput.buttons &= ~BUTTON_SHIFT;
	}
}

static void UIhandler_FX_ROT_single (int8_t inRotary, uint8_t inFX) {
	int8_t rotaryValue = inRotary;		// REFACTOR

	if (!BUTTON_SHIFT && rotaryValue) {
		int32_t tempValue;

		switch (inFX) {
		case LPF:
			tempValue = FXsettings.lpfFreq;
			tempValue += rotaryValue * LPF_STEP;
			tempValue = (tempValue > LPF_HIGH	? LPF_HIGH 	: tempValue);	// Upper range check
			tempValue = (tempValue < LPF_LOW 	? LPF_LOW 	: tempValue);	// Lower range check
			FXsettings.lpfFreq = tempValue;
			break;
		case HPF:
			tempValue = FXsettings.hpfFreq;
			tempValue += rotaryValue * HPF_STEP;
			tempValue = (tempValue > HPF_HIGH	? HPF_HIGH 	: tempValue);	// Upper range check
			tempValue = (tempValue < HPF_LOW 	? HPF_LOW 	: tempValue);	// Lower range check
			FXsettings.hpfFreq = tempValue;
			break;
		case DS:
			tempValue = FXsettings.dsFreq;
			tempValue += rotaryValue * DS_STEP;
			tempValue = (tempValue > DS_HIGH	? DS_HIGH 	: tempValue);	// Upper range check
			tempValue = (tempValue < DS_LOW 	? DS_LOW 	: tempValue);	// Lower range check
			FXsettings.dsFreq = tempValue;
			break;
		case BC:
			tempValue = FXsettings.bcBits;
			tempValue += rotaryValue * BC_STEP;
			tempValue = (tempValue > BC_HIGH	? BC_HIGH 	: tempValue);	// Upper range check
			tempValue = (tempValue < BC_LOW 	? BC_LOW 	: tempValue);	// Lower range check
			FXsettings.bcBits = tempValue;
			break;
		}
	}
}

void UIhandler_FX_ROT (void) {
	UIhandler_FX_ROT_single(ROTARY_FX_1, FXsettings.fx1);
	UIhandler_FX_ROT_single(ROTARY_FX_2, FXsettings.fx2);
}

///////////
// DRUMS //
///////////
static void UIhandler_Drum_Levels_Single (Instrument_TypeDef* instr, int8_t* rotaryLevel, int8_t* rotaryTone) {
	// Level
	int8_t temp;

	temp = instr->level;
	temp += *rotaryLevel * 5;
	temp = (temp > 100 	? 100 	: temp);
	temp = (temp < 0	? 0		: temp);
	instr->level = temp;

	// Tone
	temp = instr->tone;
	temp += *rotaryTone;
	temp = (temp > 100 	? 100 	: temp);
	temp = (temp < 0	? 0		: temp);
	instr->tone = temp;

	// Reset drums
	*rotaryLevel 	= 0;
	*rotaryTone		= 0;
}

void UIhandler_Drum_Levels (void) {
	UIhandler_Drum_Levels_Single (&sequencer.instr0, &ROTARY_DRUM_LEVEL_1, &ROTARY_DRUM_TONE_1);
	UIhandler_Drum_Levels_Single (&sequencer.instr1, &ROTARY_DRUM_LEVEL_2, &ROTARY_DRUM_TONE_2);
	UIhandler_Drum_Levels_Single (&sequencer.instr2, &ROTARY_DRUM_LEVEL_3, &ROTARY_DRUM_TONE_3);
	UIhandler_Drum_Levels_Single (&sequencer.instr3, &ROTARY_DRUM_LEVEL_4, &ROTARY_DRUM_TONE_4);
}

void UIhandler_SelectDrums (void) {
	if (BUTTON_DRUM_1)
		sequencer.instrID = 0;

	if (BUTTON_DRUM_2)
		sequencer.instrID = 1;

	if (BUTTON_DRUM_3)
		sequencer.instrID = 2;

	if (BUTTON_DRUM_4)
		sequencer.instrID = 3;

	if (BUTTON_DRUM_5)
		sequencer.instrID = 4;

	if (BUTTON_DRUM_6)
		sequencer.instrID = 5;

	// Clear drum inputs
	uiInput.buttons &= ~(BUTTON_DRUM_1 | BUTTON_DRUM_2 | BUTTON_DRUM_3 | BUTTON_DRUM_4  | BUTTON_DRUM_5  | BUTTON_DRUM_6);
}

/////////////////
// Play Button //
/////////////////
void UIhandler_PlayButton (void) {
	if (BUTTON_PLAY) {
		sequencer.playing = (sequencer.playing == 1 ? 0 : 1);

		uiInput.buttons &= ~BUTTON_PLAY;		// Reset input value
	}
}

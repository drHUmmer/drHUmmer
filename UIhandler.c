#include "UIhandler.h"

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
			tempValue += ROTARY_FX_1;
			while (tempValue > 4) {			// Effects are 0 till 4
				tempValue -= 5;
			}
			while (tempValue < 0) {
				tempValue += 5;
			}
			FXsettings.fx2 = tempValue;
		}
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
static void UIhandler_Drums_Levels_Single (Instrument_TypeDef* instr, int8_t* rotaryLevel, int8_t* rotaryTone) {
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

#include "menu.h"

/*
 * Menu hierarchy
 *
 * Info
 * 	\ Main
 * 	 	\ Colours
 * 	 	|	\ Background colour
 * 	 	|	\ Text colour
 * 	 	|	\ Level bar
 * 	 	|	\ Tone positive bar
 * 	 	|	\ Tone negative bar
 * 	 	\ Fx
 * 	 	|	\ Fx 1
 * 	 	|	\ Fx 2
 *		\ Settings Fx
 *		|	\ lp freq
 *		|	\ hp freq
 *		|	\ ds freq
 *		|	\ bc bits
 *		\ Set BPM
 *
 */

void MenuSetup() {
	LCD_Clear(ColourConverterDec(Black));

	// Set default values
	gui.colours.background 	= Black;
	gui.colours.text 		= Green;
	gui.colours.levelBar	= Red;
	gui.colours.tonePosBar	= Blue2;
	gui.colours.toneNegBar	= Yellow;
	gui.menus.current		= &gui.menus.info;

	// Clear menu options
	MenuClearStringMemory(&gui.menus.info);
	MenuClearStringMemory(&gui.menus.main);
	MenuClearStringMemory(&gui.menus.backcolour);
	MenuClearStringMemory(&gui.menus.textcolour);
	MenuClearStringMemory(&gui.menus.fx);
	MenuClearStringMemory(&gui.menus.fx1);
	MenuClearStringMemory(&gui.menus.fx2);
	MenuClearStringMemory(&gui.menus.levelBarcolour);
	MenuClearStringMemory(&gui.menus.tonePosBarcolour);
	MenuClearStringMemory(&gui.menus.toneNegBarcolour);

	// Main screen //
	gui.menus.info.selectedOption							= 0;
	gui.menus.info.nrOfOptions								= 0;
	gui.menus.info.handler									= Menu_InfoHandler;
	strcpy(gui.menus.info.menuTitle							, TITLE_INFOSCREEN);
	
	// Settings Menu //
	gui.menus.main.selectedOption							= 1;
	gui.menus.main.nrOfOptions								= 8;
	gui.menus.main.handler									= Menu_MainHandler;
	gui.menus.main.parent									= Menu_Info;
	strcpy(gui.menus.main.menuTitle							, TITLE_MAINSMENU);
	strcpy(gui.menus.main.menuOptions [0]					, BACKSTRING);
	strcpy(gui.menus.main.menuOptions [1]					, "Set fx");
	strcpy(gui.menus.main.menuOptions [2]					, "Set colours");
	strcpy(gui.menus.main.menuOptions [3]					, "Set BPM");
	strcpy(gui.menus.main.menuOptions [4]					, "Set lpf freq");
	strcpy(gui.menus.main.menuOptions [5]					, "Set hpf freq");
	strcpy(gui.menus.main.menuOptions [6]					, "Set ds freq");
	strcpy(gui.menus.main.menuOptions [7]					, "Set bc bits");

	// Colours //
	gui.menus.colours.selectedOption						= 1;
	gui.menus.colours.nrOfOptions							= 7;
	gui.menus.colours.handler								= Menu_ColourHandler;
	gui.menus.colours.parent								= Menu_Main;
	strcpy(gui.menus.colours.menuTitle						, TITLE_COLOURMENU);
	strcpy(gui.menus.colours.menuOptions	[0]				, BACKSTRING);
	strcpy(gui.menus.colours.menuOptions	[1]				, "Invert");
	strcpy(gui.menus.colours.menuOptions	[2]				, "Back colour");
	strcpy(gui.menus.colours.menuOptions	[3]				, "Text colour");
	strcpy(gui.menus.colours.menuOptions	[4]				, "Level colour");
	strcpy(gui.menus.colours.menuOptions	[5]				, "Tone + colour");
	strcpy(gui.menus.colours.menuOptions	[6]				, "Tone - colour");

	// Background colour //
	gui.menus.backcolour.selectedOption						= 1;
	gui.menus.backcolour.nrOfOptions						= 11;
	gui.menus.backcolour.handler							= Menu_BackcolourHandler;
	gui.menus.backcolour.parent								= Menu_Colours;
	strcpy(gui.menus.backcolour.menuTitle					, TITLE_BACKCOLOURMENU);
	strcpy(gui.menus.backcolour.menuOptions	[0]				, BACKSTRING);
	strcpy(gui.menus.backcolour.menuOptions	[1]				, "White");
	strcpy(gui.menus.backcolour.menuOptions	[2]				, "Black");
	strcpy(gui.menus.backcolour.menuOptions	[3]				, "Red");
	strcpy(gui.menus.backcolour.menuOptions	[4]				, "Green");
	strcpy(gui.menus.backcolour.menuOptions	[5]				, "Blue");
	strcpy(gui.menus.backcolour.menuOptions	[6]				, "Yellow");
	strcpy(gui.menus.backcolour.menuOptions	[7]				, "Cyan");
	strcpy(gui.menus.backcolour.menuOptions	[8]				, "Magenta");
	strcpy(gui.menus.backcolour.menuOptions	[9]				, "Grey");
	strcpy(gui.menus.backcolour.menuOptions	[10]			, "Blue - 2");

	// Text colour //
	gui.menus.textcolour.selectedOption						= 1;
	gui.menus.textcolour.nrOfOptions						= 11;
	gui.menus.textcolour.handler							= Menu_TextcolourHandler;
	gui.menus.textcolour.parent								= Menu_Colours;
	strcpy(gui.menus.textcolour.menuTitle	  				, TITLE_TEXTCOLOURMENU);
	strcpy(gui.menus.textcolour.menuOptions [0]				, BACKSTRING);
	strcpy(gui.menus.textcolour.menuOptions [1]				, "White");
	strcpy(gui.menus.textcolour.menuOptions [2]				, "Black");
	strcpy(gui.menus.textcolour.menuOptions [3]				, "Red");
	strcpy(gui.menus.textcolour.menuOptions [4]				, "Green");
	strcpy(gui.menus.textcolour.menuOptions [5]				, "Blue");
	strcpy(gui.menus.textcolour.menuOptions [6]				, "Yellow");
	strcpy(gui.menus.textcolour.menuOptions [7]				, "Cyan");
	strcpy(gui.menus.textcolour.menuOptions [8]				, "Magenta");
	strcpy(gui.menus.textcolour.menuOptions [9]				, "Grey");
	strcpy(gui.menus.textcolour.menuOptions [10]			, "Blue - 2");

	// Level colour //
	gui.menus.levelBarcolour.selectedOption					= 1;
	gui.menus.levelBarcolour.nrOfOptions					= 11;
	gui.menus.levelBarcolour.handler						= Menu_LevelBarHandler;
	gui.menus.levelBarcolour.parent							= Menu_Colours;
	strcpy(gui.menus.levelBarcolour.menuTitle	  			, TITLE_LEVELBAR);
	strcpy(gui.menus.levelBarcolour.menuOptions [0]			, BACKSTRING);
	strcpy(gui.menus.levelBarcolour.menuOptions [1]			, "White");
	strcpy(gui.menus.levelBarcolour.menuOptions [2]			, "Black");
	strcpy(gui.menus.levelBarcolour.menuOptions [3]			, "Red");
	strcpy(gui.menus.levelBarcolour.menuOptions [4]			, "Green");
	strcpy(gui.menus.levelBarcolour.menuOptions [5]			, "Blue");
	strcpy(gui.menus.levelBarcolour.menuOptions [6]			, "Yellow");
	strcpy(gui.menus.levelBarcolour.menuOptions [7]			, "Cyan");
	strcpy(gui.menus.levelBarcolour.menuOptions [8]			, "Magenta");
	strcpy(gui.menus.levelBarcolour.menuOptions [9]			, "Grey");
	strcpy(gui.menus.levelBarcolour.menuOptions [10]		, "Blue - 2");

	// Tone + colour //
	gui.menus.tonePosBarcolour.selectedOption				= 1;
	gui.menus.tonePosBarcolour.nrOfOptions					= 11;
	gui.menus.tonePosBarcolour.handler						= Menu_TonePosBarHandler;
	gui.menus.tonePosBarcolour.parent						= Menu_Colours;
	strcpy(gui.menus.tonePosBarcolour.menuTitle	  			, TITLE_TONEPOSBAR);
	strcpy(gui.menus.tonePosBarcolour.menuOptions [0]		, BACKSTRING);
	strcpy(gui.menus.tonePosBarcolour.menuOptions [1]		, "White");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [2]		, "Black");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [3]		, "Red");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [4]		, "Green");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [5]		, "Blue");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [6]		, "Yellow");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [7]		, "Cyan");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [8]		, "Magenta");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [9]		, "Grey");
	strcpy(gui.menus.tonePosBarcolour.menuOptions [10]		, "Blue - 2");

	// Tone - colour //
	gui.menus.toneNegBarcolour.selectedOption				= 1;
	gui.menus.toneNegBarcolour.nrOfOptions					= 11;
	gui.menus.toneNegBarcolour.handler						= Menu_ToneNegBarHandler;
	gui.menus.toneNegBarcolour.parent						= Menu_Colours;
	strcpy(gui.menus.toneNegBarcolour.menuTitle	  			, TITLE_TONENEGBAR);
	strcpy(gui.menus.toneNegBarcolour.menuOptions [0]		, BACKSTRING);
	strcpy(gui.menus.toneNegBarcolour.menuOptions [1]		, "White");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [2]		, "Black");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [3]		, "Red");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [4]		, "Green");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [5]		, "Blue");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [6]		, "Yellow");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [7]		, "Cyan");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [8]		, "Magenta");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [9]		, "Grey");
	strcpy(gui.menus.toneNegBarcolour.menuOptions [10]		, "Blue - 2");

	// Set FX //
	gui.menus.fx.selectedOption								= 1;
	gui.menus.fx.nrOfOptions								= 3;
	gui.menus.fx.handler									= Menu_SetFxHandler;
	gui.menus.fx.parent										= Menu_Main;
	strcpy(gui.menus.fx.menuTitle							, TITLE_SETFX);
	strcpy(gui.menus.fx.menuOptions	[0]						, BACKSTRING);
	strcpy(gui.menus.fx.menuOptions	[1]						, "Fx 1");
	strcpy(gui.menus.fx.menuOptions	[2]						, "Fx 2");

	// Set FX 1 //
	gui.menus.fx1.selectedOption								= 1;
	gui.menus.fx1.nrOfOptions								= 6;
	gui.menus.fx1.handler									= Menu_SetFx1Handler;
	gui.menus.fx1.parent									= Menu_SetFx;
	strcpy(gui.menus.fx1.menuTitle							, TITLE_SETFX1);
	strcpy(gui.menus.fx1.menuOptions	[0]					, BACKSTRING);
	strcpy(gui.menus.fx1.menuOptions	[1]					, "None");
	strcpy(gui.menus.fx1.menuOptions	[2]					, "Low-pass");
	strcpy(gui.menus.fx1.menuOptions	[3]					, "High-pass");
	strcpy(gui.menus.fx1.menuOptions	[4]					, "Bitcrusher");
	strcpy(gui.menus.fx1.menuOptions	[5]					, "Down-sampler");

	// Set FX 2 //
	gui.menus.fx2.selectedOption							= 1;
	gui.menus.fx2.nrOfOptions								= 6;
	gui.menus.fx2.handler									= Menu_SetFx2Handler;
	gui.menus.fx2.parent									= Menu_SetFx;
	strcpy(gui.menus.fx2.menuTitle							, TITLE_SETFX2);
	strcpy(gui.menus.fx2.menuOptions	[0]					, BACKSTRING);
	strcpy(gui.menus.fx2.menuOptions	[1]					, "None");
	strcpy(gui.menus.fx2.menuOptions	[2]					, "Low-pass");
	strcpy(gui.menus.fx2.menuOptions	[3]					, "High-pass");
	strcpy(gui.menus.fx2.menuOptions	[4]					, "Bitcrusher");
	strcpy(gui.menus.fx2.menuOptions	[5]					, "Down-sampler");

	// Set BPM //
	gui.menus.bpm.selectedOption							= 1;
	gui.menus.bpm.nrOfOptions								= 1;
	gui.menus.bpm.handler									= Menu_SetBPMHandler;
	gui.menus.bpm.parent									= Menu_Main;
	strcpy(gui.menus.bpm.menuTitle							, TITLE_SETBPM);
	strcpy(gui.menus.bpm.menuOptions	[0]					, "");

	// Set LPF freq //
	gui.menus.lpFreq.selectedOption							= 1;
	gui.menus.lpFreq.nrOfOptions							= 1;
	gui.menus.lpFreq.handler								= Menu_SetLPFfreqHandler;
	gui.menus.lpFreq.parent									= Menu_Main;
	strcpy(gui.menus.lpFreq.menuTitle						, TITLE_SETLPFFREQ);
	strcpy(gui.menus.lpFreq.menuOptions	[0]					, "");

	// Set HPF freq //
	gui.menus.hpFreq.selectedOption							= 1;
	gui.menus.hpFreq.nrOfOptions							= 1;
	gui.menus.hpFreq.handler								= Menu_SetHPFfreqHandler;
	gui.menus.hpFreq.parent									= Menu_Main;
	strcpy(gui.menus.hpFreq.menuTitle						, TITLE_SETHPFFREQ);
	strcpy(gui.menus.hpFreq.menuOptions	[0]					, "");

	// Set DS freq //
	gui.menus.dsFreq.selectedOption							= 1;
	gui.menus.dsFreq.nrOfOptions							= 1;
	gui.menus.dsFreq.handler								= Menu_SetDSfreqHandler;
	gui.menus.dsFreq.parent									= Menu_Main;
	strcpy(gui.menus.dsFreq.menuTitle						, TITLE_SETDSFREQ);
	strcpy(gui.menus.dsFreq.menuOptions	[0]					, "");

	// Set BC bits //
	gui.menus.bcBits.selectedOption							= 1;
	gui.menus.bcBits.nrOfOptions							= 1;
	gui.menus.bcBits.handler								= Menu_SetBCbitsHandler;
	gui.menus.bcBits.parent									= Menu_Main;
	strcpy(gui.menus.bcBits.menuTitle						, TITLE_SETBCBITS);
	strcpy(gui.menus.bcBits.menuOptions	[0]					, "");

// Progressbars
	// Analog drum 1
	gui.bars.analogDrum1Level.value							= sequencer.bassdrum.level;
	gui.bars.analogDrum1Level.xPos							= 0;
	gui.bars.analogDrum1Level.yPos							= 0;
	gui.bars.analogDrum1Level.xSize							= 180;
	gui.bars.analogDrum1Level.ySize							= 25;

	gui.bars.analogDrum1Tone.value							= sequencer.bassdrum.tone;
	gui.bars.analogDrum1Tone.xPos							= 0;
	gui.bars.analogDrum1Tone.yPos							= 25;
	gui.bars.analogDrum1Tone.xSize							= 180;
	gui.bars.analogDrum1Tone.ySize							= 25;

	// Analog drum 2
	gui.bars.analogDrum2Level.value							= sequencer.snaredrum.level;
	gui.bars.analogDrum2Level.xPos							= 0;
	gui.bars.analogDrum2Level.yPos							= 54;
	gui.bars.analogDrum2Level.xSize							= 180;
	gui.bars.analogDrum2Level.ySize							= 25;

	gui.bars.analogDrum2Tone.value							= sequencer.snaredrum.tone;
	gui.bars.analogDrum2Tone.xPos							= 0;
	gui.bars.analogDrum2Tone.yPos							= 79;
	gui.bars.analogDrum2Tone.xSize							= 180;
	gui.bars.analogDrum2Tone.ySize							= 25;

	// Digital drum 1
	gui.bars.digitalDrum1Level.value						= sequencer.instr0.level;
	gui.bars.digitalDrum1Level.xPos							= 0;
	gui.bars.digitalDrum1Level.yPos							= 108;
	gui.bars.digitalDrum1Level.xSize						= 180;
	gui.bars.digitalDrum1Level.ySize						= 25;

	gui.bars.digitalDrum1Tone.value							= sequencer.instr0.tone;
	gui.bars.digitalDrum1Tone.xPos							= 0;
	gui.bars.digitalDrum1Tone.yPos							= 133;
	gui.bars.digitalDrum1Tone.xSize							= 180;
	gui.bars.digitalDrum1Tone.ySize							= 25;

	// Digital drum 2
	gui.bars.digitalDrum2Level.value						= sequencer.instr1.level;
	gui.bars.digitalDrum2Level.xPos							= 0;
	gui.bars.digitalDrum2Level.yPos							= 162;
	gui.bars.digitalDrum2Level.xSize						= 180;
	gui.bars.digitalDrum2Level.ySize						= 25;

	gui.bars.digitalDrum2Tone.value							= sequencer.instr1.tone;
	gui.bars.digitalDrum2Tone.xPos							= 0;
	gui.bars.digitalDrum2Tone.yPos							= 187;
	gui.bars.digitalDrum2Tone.xSize							= 180;
	gui.bars.digitalDrum2Tone.ySize							= 25;

	// Digital drum 3
	gui.bars.digitalDrum3Level.value						= sequencer.instr2.level;
	gui.bars.digitalDrum3Level.xPos							= 0;
	gui.bars.digitalDrum3Level.yPos							= 216;
	gui.bars.digitalDrum3Level.xSize						= 180;
	gui.bars.digitalDrum3Level.ySize						= 25;

	gui.bars.digitalDrum3Tone.value							= sequencer.instr2.tone;
	gui.bars.digitalDrum3Tone.xPos							= 0;
	gui.bars.digitalDrum3Tone.yPos							= 241;
	gui.bars.digitalDrum3Tone.xSize							= 180;
	gui.bars.digitalDrum3Tone.ySize							= 25;

	// Digital drum 4
	gui.bars.digitalDrum4Level.value						= sequencer.instr3.level;
	gui.bars.digitalDrum4Level.xPos							= 0;
	gui.bars.digitalDrum4Level.yPos							= 270;
	gui.bars.digitalDrum4Level.xSize						= 180;
	gui.bars.digitalDrum4Level.ySize						= 25;

	gui.bars.digitalDrum4Tone.value							= sequencer.instr3.tone;
	gui.bars.digitalDrum4Tone.xPos							= 0;
	gui.bars.digitalDrum4Tone.yPos							= 295;
	gui.bars.digitalDrum4Tone.xSize							= 180;
	gui.bars.digitalDrum4Tone.ySize							= 25;

	// Start mainscreen
	Menu_Info();
}

////////////////////
// Menu Functions //
////////////////////
void MenuClearStringMemory (Menu_Typedef* menu) {
	uint8_t count 		= 0;
	uint8_t charcount	= 0;

	for (count = 0; count < MAXOPTIONS; count ++) {
		for (charcount = 0; charcount < MAXSTRINGLENGTH; charcount ++) {
			menu->menuOptions[count][charcount] = '\0';
		}
	}

	MenuClearTitle(menu);
}

void MenuClearTitle (Menu_Typedef* menu) {
	uint8_t count		= 0;

	for (count = 0; count < MAXSTRINGLENGTH; count ++) {
		menu->menuTitle[count] = '\0';
	}
}

uint8_t MenuCompareTitle(char* toCompare) {
	// Return 1 if equals
	// Return 0 if not equal
	return !(!!(strcmp(gui.menus.current->menuTitle, toCompare)));
}

uint8_t MenuCompareSelected(char* toCompare) {
	// Return 1 if equals
	// Return 0 if not equal
	uint8_t currentSelectedOption = gui.menus.current->selectedOption;
	return !(!!(strcmp(gui.menus.current->menuOptions[currentSelectedOption], toCompare)));
}

void MenuDrawCurrentlySelected () {
	if (!MenuCompareTitle(TITLE_INFOSCREEN)) {
		LCD_SetTextColor(ColourConverterDec(gui.colours.background));
		LCD_DrawFullRect(10, 3, 176, 19);
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
		LCD_PutChar(160 - ((gui.menus.current->selectedOption % OPTIONSPERMENU) * 30), 5, CURRENTLYSELECTEDCHAR);
	}
}

void MenuDrawOptions(uint8_t clearBack) {
	if (clearBack) {
		LCD_SetTextColor(ColourConverterDec(gui.colours.background));
		LCD_DrawFullRect(10, 30, 176, 280);						// Redraw options //
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
	}

	if (gui.menus.current->nrOfOptions) {
		uint8_t optionCounter 	= 0;
		uint8_t optionOffset 	= OPTIONSPERMENU * (gui.menus.current->selectedOption / OPTIONSPERMENU);

		for (optionCounter = optionOffset; optionCounter < (optionOffset + OPTIONSPERMENU); optionCounter ++) {
			if (optionCounter < MAXOPTIONS && optionCounter < gui.menus.current->nrOfOptions) {
				if (gui.menus.current->menuOptions[optionCounter][0] != '\0') {
					LCD_StringLine(160 - ((optionCounter - optionOffset) * 30), 30, gui.menus.current->menuOptions[optionCounter]);
				}
			}
		}
	}
}

void MenuDrawTitle(uint8_t clearBack) {
	if (clearBack) {
		LCD_SetTextColor(ColourConverterDec(gui.colours.background));
		LCD_DrawFullRect(210, 20, 27, 290);
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
	}

	LCD_StringLine(210, 30, gui.menus.current->menuTitle);
}

void MenuRedrawScreen () {
	LCD_Clear(ColourConverterDec(gui.colours.background));
	LCD_SetBackColor(ColourConverterDec(gui.colours.background));
	LCD_SetTextColor(ColourConverterDec(gui.colours.text));

	// Title
	MenuDrawTitle(0);

	// Horizontal line, separating menu and title
	LCD_DrawFullRect(198, 10, 5, 300);

	// Draw options
	MenuDrawOptions(0);

	// Draw cursor
	MenuDrawCurrentlySelected();
}

void MenuUpdateSelectedItem() {
	uint8_t oldValue 		= gui.menus.current->selectedOption;
	uint8_t nrOfOptions		= gui.menus.current->nrOfOptions;
	int8_t newValue 		= oldValue;
	int8_t rotaryValue		= MenuRotaryRead(1);

	if (rotaryValue == 0) {
		return;									// RETURN //
	}

	newValue += rotaryValue;
	if (newValue < 0) {							// If negative
		newValue += nrOfOptions;				// Turn around
	}
	newValue %= nrOfOptions;					// If too high, turn around as well

	gui.menus.current->selectedOption = newValue;

	if (newValue / OPTIONSPERMENU != oldValue / OPTIONSPERMENU) {	// Only redraw everything when necessary
		MenuRedrawScreen();//					// More efficient than MenuDrawOptions
//		MenuDrawOptions(1);						// Redraw the options
	}

	MenuDrawCurrentlySelected();				// Redraw cursor

	return;
}

////////////////////
// User Interface //
////////////////////
uint8_t MenuBackpressed(uint8_t reset) {
	uint8_t returnValue = 0;
	if (buttonz.buttonBack) {					// BUTTONZ //
		returnValue = 1;

		if (reset)
			buttonz.buttonBack = 0;
	}

	return returnValue;
}

uint8_t MenuOKpressed(uint8_t reset) {
	uint8_t returnValue = 0;
	if (buttonz.buttonOK) {						// BUTTONZ //
		returnValue = 1;

		if (reset)
			buttonz.buttonOK = 0;
	}

	return returnValue;
}

int8_t MenuRotaryRead(uint8_t reset) {
	int8_t returnValue = 0;
	returnValue = buttonz.rotaryValue;

	if (reset)
		buttonz.rotaryValue = 0;				// BUTTONZ //

	return returnValue;
}

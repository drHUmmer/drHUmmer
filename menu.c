#include "menu.h"

/*
 * Menu hierarchy
 *
 * Info
 * \ Main
 * 		\ MIDI
 * 		|	\ Channel
 * 		|	\ Master / Slave
 * 		|	\ Sync
 * 		\ Seq
 * 		|	\ BPM
 * 		|	\ Patt / live mode
 * 		\ File
 * 		|	\ Sample select
 * 		|	\ Save pattern
 * 		|	\ Load pattern
 * 		\ Filter bookmark
 * 		|	\ Filter book. 1
 * 		|	\ Filter book. 2
 * 		\ UI
 * 			\ Colours
 * 			|	\ background
 * 			|	\ text
 * 			|	\ level
 * 			|	\ tone pos
 * 			|	\ tone neg
 * 			\ Infobars
 * 				\ Infobar 1
 * 				\ Infobar 2
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
	gui.menus.info.showCursor								= 0;
	gui.menus.info.handler									= Menu_InfoHandler;
	strcpy(gui.menus.info.menuTitle							, TITLE_INFOSCREEN);
	
	// Settings Menu //
	gui.menus.main.selectedOption							= 0;
	gui.menus.main.nrOfOptions								= 6;
	gui.menus.main.showCursor								= 1;
	gui.menus.main.handler									= Menu_MainHandler;
	gui.menus.main.parent									= Menu_Info;
	strcpy(gui.menus.main.menuTitle							, TITLE_MAINSMENU);
	strcpy(gui.menus.main.menuOptions [0]					, BACKSTRING);
	strcpy(gui.menus.main.menuOptions [1]					, "MIDI");
	strcpy(gui.menus.main.menuOptions [2]					, "Sequencer");
	strcpy(gui.menus.main.menuOptions [3]					, "File");
	strcpy(gui.menus.main.menuOptions [4]					, "Filter");
	strcpy(gui.menus.main.menuOptions [5]					, "UI");

//////////
// MIDI //
//////////
	gui.menus.midi.selectedOption							= 0;
	gui.menus.midi.nrOfOptions								= 4;
	gui.menus.midi.showCursor								= 1;
	gui.menus.midi.handler									= 
	gui.menus.midi.parent									= Menu_Main;
	strcpy(gui.menus.midi.menuTitle							, TITLE_MIDI);
	strcpy(gui.menus.midi.menuOptions[0]					, BACKSTRING);
	strcpy(gui.menus.midi.menuOptions[1]					, "Channel");
	strcpy(gui.menus.midi.menuOptions[2]					, "Master / slave");
	strcpy(gui.menus.midi.menuOptions[3]					, "Sync");

	gui.menus.midi_channel.selectedOption					= 0;
	gui.menus.midi_channel.nrOfOptions						= 0;
	gui.menus.midi_channel.showCursor						= 0;
	gui.menus.midi_channel.handler							= 
	gui.menus.midi_channel.parent							= Menu_MIDI;
	strcpy(gui.menus.midi_channel.menuTitle					, TITLE_MIDI_CHANNEL);

	gui.menus.midi_master_slave.selectedOption				= 0;
	gui.menus.midi_master_slave.nrOfOptions					= 0;
	gui.menus.midi_master_slave.showCursor					= 0;
	gui.menus.midi_master_slave.handler						= 
	gui.menus.midi_master_slave.parent						= Menu_MIDI;
	strcpy(gui.menus.midi_master_slave.menuTitle			, TITLE_MIDI_MASTER_SLAVE);

	gui.menus.midi_sync.selectedOption						= 0;
	gui.menus.midi_sync.nrOfOptions							= 0;
	gui.menus.midi_sync.showCursor							= 0;
	gui.menus.midi_sync.handler								= 
	gui.menus.midi_sync.parent								= Menu_MIDI;
	strcpy(gui.menus.midi_sync.menuTitle					, TITLE_MIDI_SYNC);

/////////
// SEQ //
/////////
	gui.menus.seq.selectedOption							= 0;
	gui.menus.seq.nrOfOptions								= 3;
	gui.menus.seq.showCursor								= 0;
	gui.menus.seq.handler									= 
	gui.menus.seq.parent									= Menu_Main;
	strcpy(gui.menus.seq.menuTitle							, TITLE_SEQ);
	strcpy(gui.menus.seq.menuOptions[0]						, BACKSTRING);
	strcpy(gui.menus.seq.menuOptions[1]						, "BPM");
	strcpy(gui.menus.seq.menuOptions[2]						, "Pattern / live");

	gui.menus.seq_bpm.selectedOption						= 0;
	gui.menus.seq_bpm.nrOfOptions							= 0;
	gui.menus.seq_bpm.showCursor							= 0;
	gui.menus.seq_bpm.handler								= 
	gui.menus.seq_bpm.parent								= Menu_Main;
	strcpy(gui.menus.seq_bpm.menuTitle						, TITLE_SEQ_BPM);

	gui.menus.seq_patt_live_mode.selectedOption				= 0;
	gui.menus.seq_patt_live_mode.nrOfOptions				= 3;
	gui.menus.seq_patt_live_mode.showCursor					= 0;
	gui.menus.seq_patt_live_mode.handler					= 
	gui.menus.seq_patt_live_mode.parent						= Menu_Main;
	strcpy(gui.menus.seq_patt_live_mode.menuTitle			, TITLE_SEQ_PATT_LIVE);
	strcpy(gui.menus.seq_patt_live_mode.menuOptions[0]		, BACKSTRING);
	strcpy(gui.menus.seq_patt_live_mode.menuOptions[1]		, "Pattern");
	strcpy(gui.menus.seq_patt_live_mode.menuOptions[2]		, "Live");

//////////
// FILE //
//////////

////////
// UI //
////////
	gui.menus.ui.selectedOption								= 1;
	gui.menus.ui.nrOfOptions								= 3;
	gui.menus.ui.showCursor									= 1;
	gui.menus.ui.handler									= 
	gui.menus.ui.parent										= Menu_Main;
	strcpy(gui.menus.ui.menuTitle							, TITLE_UI_COLOURS);
	strcpy(gui.menus.ui.menuOptions	[0]						, BACKSTRING);
	strcpy(gui.menus.ui.menuOptions	[1]						, "Colours");
	strcpy(gui.menus.ui.menuOptions	[2]						, "Info");

	gui.menus.ui_colours.selectedOption						= 1;
	gui.menus.ui_colours.nrOfOptions						= 6;
	gui.menus.ui_colours.showCursor							= 1;
	gui.menus.ui_colours.handler							= 
	gui.menus.ui_colours.parent								= Menu_UI;
	strcpy(gui.menus.ui_colours.menuTitle					, TITLE_UI_COLOURS);
	strcpy(gui.menus.ui_colours.menuOptions	[0]				, BACKSTRING);
	strcpy(gui.menus.ui_colours.menuOptions	[1]				, "Background");
	strcpy(gui.menus.ui_colours.menuOptions	[2]				, "Text");
	strcpy(gui.menus.ui_colours.menuOptions	[3]				, "Level bar");
	strcpy(gui.menus.ui_colours.menuOptions	[4]				, "Tone bar +");
	strcpy(gui.menus.ui_colours.menuOptions	[5]				, "Tone bar -");

	// Background colour //
	gui.menus.ui_backcolour.selectedOption					= 1;
	gui.menus.ui_backcolour.nrOfOptions						= 11;
	gui.menus.ui_backcolour.showCursor						= 1;
	gui.menus.ui_backcolour.handler							= 
	gui.menus.ui_backcolour.parent							= Menu_UI_Colours;
	strcpy(gui.menus.ui_backcolour.menuTitle				, TITLE_UI_COLOURS_BACK);
	strcpy(gui.menus.ui_backcolour.menuOptions	[0]			, BACKSTRING);
	strcpy(gui.menus.ui_backcolour.menuOptions	[1]			, "White");
	strcpy(gui.menus.ui_backcolour.menuOptions	[2]			, "Black");
	strcpy(gui.menus.ui_backcolour.menuOptions	[3]			, "Red");
	strcpy(gui.menus.ui_backcolour.menuOptions	[4]			, "Green");
	strcpy(gui.menus.ui_backcolour.menuOptions	[5]			, "Blue");
	strcpy(gui.menus.ui_backcolour.menuOptions	[6]			, "Yellow");
	strcpy(gui.menus.ui_backcolour.menuOptions	[7]			, "Cyan");
	strcpy(gui.menus.ui_backcolour.menuOptions	[8]			, "Magenta");
	strcpy(gui.menus.ui_backcolour.menuOptions	[9]			, "Grey");
	strcpy(gui.menus.ui_backcolour.menuOptions	[10]		, "Blue - 2");

	// Text colour //
	gui.menus.ui_textcolour.selectedOption					= 1;
	gui.menus.ui_textcolour.nrOfOptions						= 11;
	gui.menus.ui_textcolour.showCursor						= 1;
	gui.menus.ui_textcolour.handler							= 
	gui.menus.ui_textcolour.parent							= Menu_UI_Colours;
	strcpy(gui.menus.ui_textcolour.menuTitle	  			, TITLE_UI_COLOURS_TEXT);
	strcpy(gui.menus.ui_textcolour.menuOptions [0]			, BACKSTRING);
	strcpy(gui.menus.ui_textcolour.menuOptions [1]			, "White");
	strcpy(gui.menus.ui_textcolour.menuOptions [2]			, "Black");
	strcpy(gui.menus.ui_textcolour.menuOptions [3]			, "Red");
	strcpy(gui.menus.ui_textcolour.menuOptions [4]			, "Green");
	strcpy(gui.menus.ui_textcolour.menuOptions [5]			, "Blue");
	strcpy(gui.menus.ui_textcolour.menuOptions [6]			, "Yellow");
	strcpy(gui.menus.ui_textcolour.menuOptions [7]			, "Cyan");
	strcpy(gui.menus.ui_textcolour.menuOptions [8]			, "Magenta");
	strcpy(gui.menus.ui_textcolour.menuOptions [9]			, "Grey");
	strcpy(gui.menus.ui_textcolour.menuOptions [10]			, "Blue - 2");

	// Level colour //
	gui.menus.levelBarcolour.selectedOption					= 1;
	gui.menus.levelBarcolour.nrOfOptions					= 11;
	gui.menus.levelBarcolour.showCursor						= 1;
	gui.menus.levelBarcolour.handler						= TITLE_UI_COLOURS_LEVEL;
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
	gui.menus.tonePosBarcolour.showCursor							= 1;
	gui.menus.tonePosBarcolour.handler						= ;
	gui.menus.tonePosBarcolour.parent						= Menu_UI_Colours;
	strcpy(gui.menus.tonePosBarcolour.menuTitle	  			, TITLE_UI_COLOURS_TONEPOS);
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
	gui.menus.toneNegBarcolour.showCursor					= 1;
	gui.menus.toneNegBarcolour.handler						= ;
	gui.menus.toneNegBarcolour.parent						= Menu_UI_Colours;
	strcpy(gui.menus.toneNegBarcolour.menuTitle	  			, TITLE_UI_COLOURS_TONENEG);
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

	gui.menus.ui_info.selectedOption						= 1;
	gui.menus.ui_info.nrOfOptions							= 3;
	gui.menus.ui_info.showCursor							= 1;
	gui.menus.ui_info.handler								= 
	gui.menus.ui_info.parent								= Menu_UI;
	strcpy(gui.menus.ui_info.menuTitle						, TITLE_UI_INFO);
	strcpy(gui.menus.ui_info.menuOptions	[0]				, BACKSTRING);
	strcpy(gui.menus.ui_info.menuOptions	[1]				, "Info bar left");
	strcpy(gui.menus.ui_info.menuOptions	[2]				, "Info bar right");

	gui.menus.ui_info_1.selectedOption						= 1;
	gui.menus.ui_info_1.nrOfOptions							= 3;
	gui.menus.ui_info_1.showCursor							= 1;
	gui.menus.ui_info_1.handler								= 
	gui.menus.ui_info_1.parent								= Menu_UI;
	strcpy(gui.menus.ui_info_1.menuTitle					, TITLE_UI_INFO_1);
	strcpy(gui.menus.ui_info_1.menuOptions	[0]				, BACKSTRING);
	strcpy(gui.menus.ui_info_1.menuOptions	[1]				, "BPM");
	strcpy(gui.menus.ui_info_1.menuOptions	[2]				, "Instrument");
	strcpy(gui.menus.ui_info_1.menuOptions	[3]				, "Pattern");
	strcpy(gui.menus.ui_info_1.menuOptions	[4]				, "Patt/Live mode");
	strcpy(gui.menus.ui_info_1.menuOptions	[5]				, "Play status");

	gui.menus.ui_info_2.selectedOption						= 1;
	gui.menus.ui_info_2.nrOfOptions							= 3;
	gui.menus.ui_info_2.showCursor							= 1;
	gui.menus.ui_info_2.handler								= 
	gui.menus.ui_info_2.parent								= Menu_UI;
	strcpy(gui.menus.ui_info_2.menuTitle					, TITLE_UI_INFO_2);
	strcpy(gui.menus.ui_info_2.menuOptions	[0]				, BACKSTRING);
	strcpy(gui.menus.ui_info_2.menuOptions	[1]				, "BPM");
	strcpy(gui.menus.ui_info_2.menuOptions	[2]				, "Instrument");
	strcpy(gui.menus.ui_info_2.menuOptions	[3]				, "Pattern");
	strcpy(gui.menus.ui_info_2.menuOptions	[4]				, "Patt/Live mode");
	strcpy(gui.menus.ui_info_2.menuOptions	[5]				, "Play status");

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
	if (gui.menus.current->showCursor) {
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

void MenuDrawEffect1 (uint8_t redraw) {
	if (redraw) {
		LCD_SetTextColor(ColourConverterDec(gui.colours.background));
		LCD_DrawFullRect(182, 0, 25, 155);
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
	}

	switch (FXsettings.fx1) {
	case LPF: 	LCD_StringLine(182,10, "LP"); LCD_StringInt(182, 60, FXsettings.lpfFreq, 1);	break;
	case HPF: 	LCD_StringLine(182,10, "HP"); LCD_StringInt(182, 60, FXsettings.hpfFreq, 1);	break;
	case BC: 	LCD_StringLine(182,10, "BC"); LCD_StringInt(182, 60, FXsettings.bcBits, 1);		break;
	case DS: 	LCD_StringLine(182,10, "DS"); LCD_StringInt(182, 60, FXsettings.dsFreq, 1); 	break;
	case NONE:	LCD_StringLine(182,10, "fx 1 off"); break;
	}
}

void MenuDrawEffect2 (uint8_t redraw) {
	if (redraw) {
		LCD_SetTextColor(ColourConverterDec(gui.colours.background));
		LCD_DrawFullRect(182, 165, 25, 155);
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
	}

	switch (FXsettings.fx2) {
	case LPF: 	LCD_StringLine(182,170, "LP"); LCD_StringInt(182, 220, FXsettings.lpfFreq, 1); 	break;
	case HPF: 	LCD_StringLine(182,170, "HP"); LCD_StringInt(182, 220, FXsettings.hpfFreq, 1);	break;
	case BC: 	LCD_StringLine(182,170, "BC"); LCD_StringInt(182, 220, FXsettings.bcBits, 1);	break;
	case DS: 	LCD_StringLine(182,170, "DS"); LCD_StringInt(182, 220, FXsettings.dsFreq, 1);	break;
	case NONE:	LCD_StringLine(182,170, "fx 2 off"); break;
	}
}

void MenuDrawInfo1 (uint8_t redraw) {
	if (redraw) {
		LCD_SetTextColor(ColourConverterDec(Red));				// DEBUG COLOUR //
		LCD_DrawFullRect(160, 165, 25, 155);					// !! TEST !! ALIGNMENT //
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
	}
}

void MenuDrawInfo2 (uint8_t redraw) {
	if (redraw) {
		LCD_SetTextColor(ColourConverterDec(Red));				// DEBUG COLOUR //
		LCD_DrawFullRect(160, 165, 25, 155);					// !! TEST !! ALIGNMENT //
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
	}
}
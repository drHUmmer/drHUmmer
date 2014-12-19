#include "menuHandlers.h"

static void Menu_GotoParent(void) {
	if (!MenuCompareTitle(TITLE_INFOSCREEN)) {
		gui.menus.current->parent();
	}
}

void Menu_Update_handler(void) {
	if (MenuOKpressed(0)) {
		if (MenuCompareSelected(BACKSTRING)) {
			Menu_GotoParent();
			MenuOKpressed(1);		// Reset OK button
			GPIO_SetBits(GPIOD, GPIO_Pin_14);					// GPIO //
			return;												// RETURN //
		}
	}

	if (MenuBackpressed(1)) {
		Menu_GotoParent();
		GPIO_SetBits(GPIOD, GPIO_Pin_15);						// GPIO //
		return;													// RETURN //
	}

	// Run current menu handler
	gui.menus.current->handler();

	// Always reset the buttons, to prevent weird things to happen
	MenuOKpressed(1);
	MenuBackpressed(1);
}

void Menu_Info_handler(void) {
	if (MenuOKpressed(1)) {
		Menu_Main();
		return;
	}

	LCD_Levelbar(&gui.bars.analogDrum1Level	, sequencer.bassdrum.level);
	LCD_Levelbar(&gui.bars.analogDrum2Level	, sequencer.snaredrum.level);
	LCD_Levelbar(&gui.bars.digitalDrum1Level	, sequencer.instr0.level);
	LCD_Levelbar(&gui.bars.digitalDrum2Level	, sequencer.instr1.level);
	LCD_Levelbar(&gui.bars.digitalDrum3Level	, sequencer.instr2.level);
	LCD_Levelbar(&gui.bars.digitalDrum4Level	, sequencer.instr3.level);

	LCD_Tonebar(&gui.bars.analogDrum1Tone		, sequencer.bassdrum.tone);
	LCD_Tonebar(&gui.bars.analogDrum2Tone		, sequencer.snaredrum.tone);
	LCD_Tonebar(&gui.bars.digitalDrum1Tone		, sequencer.instr0.tone);
	LCD_Tonebar(&gui.bars.digitalDrum2Tone		, sequencer.instr1.tone);
	LCD_Tonebar(&gui.bars.digitalDrum3Tone		, sequencer.instr2.tone);
	LCD_Tonebar(&gui.bars.digitalDrum4Tone		, sequencer.instr3.tone);

	// Update filter setting values
	switch (FXsettings.fx1) {
		case LPF:	gui.infobars.fx1.setting = LPF;	gui.infobars.fx1.value = FXsettings.lpfFreq;	break;
		case HPF:	gui.infobars.fx1.setting = HPF;	gui.infobars.fx1.value = FXsettings.hpfFreq;	break;
		case BC:	gui.infobars.fx1.setting = BC;	gui.infobars.fx1.value = FXsettings.bcBits;		break;
		case DS:	gui.infobars.fx1.setting = DS;	gui.infobars.fx1.value = FXsettings.dsFreq;		break;
	}
	switch (FXsettings.fx2) {
		case LPF:	gui.infobars.fx2.setting = LPF;	gui.infobars.fx2.value = FXsettings.lpfFreq;	break;
		case HPF:	gui.infobars.fx2.setting = HPF;	gui.infobars.fx2.value = FXsettings.hpfFreq;	break;
		case BC:	gui.infobars.fx2.setting = BC;	gui.infobars.fx2.value = FXsettings.bcBits;		break;
		case DS:	gui.infobars.fx2.setting = DS;	gui.infobars.fx2.value = FXsettings.dsFreq;		break;
	}

	 // Update info setting values
	switch (gui.infobars.info1.setting) {
		case INFO_NONE:					gui.infobars.info1.value = 0; 							break;
		case INFO_BPM:					gui.infobars.info1.value = sequencer.BPM; 				break;
		case INFO_PLAY_STATUS:			gui.infobars.info1.value = sequencer.playing;			break;
		case INFO_INSTRUMENT:			gui.infobars.info1.value = sequencer.instrID;			break;
		case INFO_PATT_LIVE_MODE:		gui.infobars.info1.value = sequencer.patt_live_mode;	break;
		case INFO_MIDI_CHANNEL:			gui.infobars.info1.value = settings.midi.channel;		break;
		case INFO_MIDI_MASTER_SLAVE:	gui.infobars.info1.value = settings.midi.master_slave;	break;
		case INFO_MIDI_SYNC:			gui.infobars.info1.value = settings.midi.sync;			break;
	}
	switch (gui.infobars.info2.setting) {
		case INFO_NONE:					gui.infobars.info2.value = 0; 							break;
		case INFO_BPM:					gui.infobars.info2.value = sequencer.BPM; 				break;
		case INFO_PLAY_STATUS:			gui.infobars.info2.value = sequencer.playing;			break;
		case INFO_INSTRUMENT:			gui.infobars.info2.value = sequencer.instrID;			break;
		case INFO_PATT_LIVE_MODE:		gui.infobars.info2.value = sequencer.patt_live_mode;	break;
		case INFO_MIDI_CHANNEL:			gui.infobars.info2.value = settings.midi.channel;		break;
		case INFO_MIDI_MASTER_SLAVE:	gui.infobars.info2.value = settings.midi.master_slave;	break;
		case INFO_MIDI_SYNC:			gui.infobars.info2.value = settings.midi.sync;			break;
	}

	// Draw updates, if needed
	MenuDrawInfo1	(0);
	MenuDrawInfo2	(0);
	MenuDrawEffect1	(0);
	MenuDrawEffect2	(0);
}

void Menu_Main_handler(void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected(TITLE_MIDI))
			Menu_MIDI();

		else if (MenuCompareSelected(TITLE_SEQ))
			Menu_SEQ();

		else if (MenuCompareSelected(TITLE_FILE))
			Menu_File();

		else if (MenuCompareSelected(TITLE_FILTERBOOKMARK))
			Menu_Filter_Bookmark();

		else if (MenuCompareSelected(TITLE_UI))
			Menu_UI();
	}
}

//////////
// MIDI //
//////////
void Menu_MIDI_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Channel"))
			Menu_MIDI_Channel();

		else if (MenuCompareSelected("Master / slave"))
			Menu_MIDI_Master_Slave();

		else if (MenuCompareSelected("Sync"))
			Menu_MIDI_Sync();
	}
}

void Menu_MIDI_Channel_handler (void) {
	if (MenuOKpressed(1)) {
		Menu_GotoParent();
	}

	// Change value with rotary
	int8_t rotaryValue = MenuRotaryRead(1);
	int8_t channelValue = settings.midi.channel;
	
	if (rotaryValue) {
		channelValue += rotaryValue;

		if (channelValue < 0)
			channelValue = channelValue + 16;
		
		if (channelValue >= 16)
			channelValue -= 16;

		settings.midi.channel = channelValue;


		LCD_StringInt(SCREENLINE2, 167, channelValue, 1);
	}
}

void Menu_MIDI_Master_Slave_handler(void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Master")) {
			settings.midi.master_slave = MIDI_MASTER;
			LCD_StringLine(SCREENLINE6, SCREENINFOSTART, "MIDI MASTER");
		}


		else if (MenuCompareSelected("Slave")) {
			settings.midi.master_slave = MIDI_SLAVE;
			LCD_StringLine(SCREENLINE6, SCREENINFOSTART, "MIDI SLAVE ");
		}
	}
}

void Menu_MIDI_Sync_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Sync on")) {
			settings.midi.sync = MIDI_SYNC_ON;

			LCD_StringLine(SCREENLINE6, SCREENINFOSTART, "Sync is ON ");
		}

		else if (MenuCompareSelected("Sync off")) {
			settings.midi.sync = MIDI_SYNC_OFF;

			LCD_StringLine(SCREENLINE6, SCREENINFOSTART, "Sync is OFF");
		}
	}
}

/////////
// SEQ //
/////////
void Menu_SEQ_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("BPM"))
			Menu_SEQ_BPM();

		else if (MenuCompareSelected("Pattern / live"))
			Menu_SEQ_Patt_Live_Mode();
	}
}

void Menu_SEQ_BPM_handler (void) {
	if (MenuOKpressed(1))
		Menu_GotoParent();

	int8_t rotary 	= MenuRotaryRead(1);
	int16_t BPM		= sequencer.BPM;

	if (rotary) {
		BPM += (rotary * 5);
		if (BPM < 50)
			BPM = 50;

		if (BPM > 400)
			BPM = 400;

		sequencer.BPM = BPM;
		BPMUpdate(BPM);

		LCD_StringInt(SCREENLINE2, SCREENSTART + (18*5), sequencer.BPM, 1);
	}
}

void Menu_SEQ_Patt_Live_Mode_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Pattern")) {
			sequencer.patt_live_mode = SEQ_PATTERN_MODE;
			LCD_StringLine(SCREENLINE6, SCREENINFOSTART, "Patt. selected");
		}

		else if (MenuCompareSelected("Live")) {
			sequencer.patt_live_mode = SEQ_LIVE_MODE;
			LCD_StringLine(SCREENLINE6, SCREENINFOSTART, "Live selected ");
		}
	}
}

//////////
// FILE //
//////////
void Menu_File_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Select pattern"))
			Menu_File_Sample_Select();

		else if (MenuCompareSelected("Save pattern"))
			Menu_File_Save_Pattern();

		else if (MenuCompareSelected("Load pattern"))
			Menu_File_Save_Pattern();
	}
}

void Menu_File_Sample_Select_handler (void) { // ToDo

}

void Menu_File_Save_Pattern_handler (void) { // ToDo

}

void Menu_File_Load_Pattern_handler (void) { // ToDo

}

//////////////////////
// FILTER BOOKMARKS //
//////////////////////
void Menu_Filter_Bookmark_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Bookmark 1"))
			Menu_Filter_Bookmark_1();

		else if (MenuCompareSelected("Bookmark 2"))
			Menu_Filter_Bookmark_2();
	}
}

void Menu_Filter_Bookmark_1_handler (void) {
	MenuUpdateSelectedItem();
}

void Menu_Filter_Bookmark_2_handler (void) {
	MenuUpdateSelectedItem();
}

////////
// UI //
////////
void Menu_UI_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Colours"))
			Menu_UI_colours();

		else if (MenuCompareSelected("Info"))
			Menu_UI_info();
	}
}

void Menu_UI_colours_handler(void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Back colour"))
			Menu_UI_backcolour();

		else if (MenuCompareSelected("Text colour"))
			Menu_UI_textcolour();

		else if (MenuCompareSelected("Level colour"))
			Menu_UI_levelbarcolour();

		else if (MenuCompareSelected("Tone + colour"))
			Menu_UI_toneposbarcolour();

		else if (MenuCompareSelected("Tone - colour"))
			Menu_UI_tonenegbarcolour();
	}
}

void Menu_UI_backcolour_handler(void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.background = White;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Black")) {
			gui.colours.background = Black;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Red")) {
			gui.colours.background = Red;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Green")) {
			gui.colours.background = Green;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue")) {
			gui.colours.background = Blue;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Yellow")) {
			gui.colours.background = Yellow;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Cyan")) {
			gui.colours.background = Cyan;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Magenta")) {
			gui.colours.background = Magenta;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Grey")) {
			gui.colours.background = Grey;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue - 2")) {
			gui.colours.background = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_UI_textcolour_handler(void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.text = White;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Black")) {
			gui.colours.text = Black;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Red")) {
			gui.colours.text = Red;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Green")) {
			gui.colours.text = Green;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue")) {
			gui.colours.text = Blue;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Yellow")) {
			gui.colours.text = Yellow;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Cyan")) {
			gui.colours.text = Cyan;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Magenta")) {
			gui.colours.text = Magenta;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Grey")) {
			gui.colours.text = Grey;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue - 2")) {
			gui.colours.text = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_UI_levelbarcolour_handler(void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.levelBar = White;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Black")) {
			gui.colours.levelBar = Black;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Red")) {
			gui.colours.levelBar = Red;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Green")) {
			gui.colours.levelBar = Green;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue")) {
			gui.colours.levelBar = Blue;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Yellow")) {
			gui.colours.levelBar = Yellow;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Cyan")) {
			gui.colours.levelBar = Cyan;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Magenta")) {
			gui.colours.levelBar = Magenta;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Grey")) {
			gui.colours.levelBar = Grey;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue - 2")) {
			gui.colours.levelBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_UI_toneposbarcolour_handler(void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.tonePosBar = White;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Black")) {
			gui.colours.tonePosBar = Black;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Red")) {
			gui.colours.tonePosBar = Red;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Green")) {
			gui.colours.tonePosBar = Green;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue")) {
			gui.colours.tonePosBar = Blue;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Yellow")) {
			gui.colours.tonePosBar = Yellow;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Cyan")) {
			gui.colours.tonePosBar = Cyan;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Magenta")) {
			gui.colours.tonePosBar = Magenta;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Grey")) {
			gui.colours.tonePosBar = Grey;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue - 2")) {
			gui.colours.tonePosBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_UI_tonenegbarcolour_handler(void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.toneNegBar = White;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Black")) {
			gui.colours.toneNegBar = Black;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Red")) {
			gui.colours.toneNegBar = Red;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Green")) {
			gui.colours.toneNegBar = Green;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue")) {
			gui.colours.toneNegBar = Blue;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Yellow")) {
			gui.colours.toneNegBar = Yellow;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Cyan")) {
			gui.colours.toneNegBar = Cyan;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Magenta")) {
			gui.colours.toneNegBar = Magenta;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Grey")) {
			gui.colours.toneNegBar = Grey;
			MenuRedrawScreen();
		}
		else if(MenuCompareSelected("Blue - 2")) {
			gui.colours.toneNegBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_UI_info_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Infobar 1"))
			Menu_UI_info_1();

		else if (MenuCompareSelected("Infobar 2"))
			Menu_UI_info_2();
	}
}

void Menu_UI_info_1_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("NONE"))
			gui.infobars.info1.setting = INFO_NONE;

		else if (MenuCompareSelected("BPM"))
			gui.infobars.info1.setting = INFO_BPM;

		else if (MenuCompareSelected("Instrument"))
			gui.infobars.info1.setting = INFO_INSTRUMENT;

		else if (MenuCompareSelected("Patt/Live mode"))
			gui.infobars.info1.setting = INFO_PATT_LIVE_MODE;

		else if (MenuCompareSelected("Pattern ID"))
			gui.infobars.info1.setting = INFO_PATTERN_ID;

		else if (MenuCompareSelected("MIDI Channel"))
			gui.infobars.info1.setting = INFO_MIDI_CHANNEL;

		else if (MenuCompareSelected("MIDI M/S"))
			gui.infobars.info1.setting = INFO_MIDI_MASTER_SLAVE;

		else if (MenuCompareSelected("MIDI Sync"))
			gui.infobars.info1.setting = INFO_MIDI_SYNC;

		else if (MenuCompareSelected("Play status"))
			gui.infobars.info1.setting = INFO_PLAY_STATUS;

//		Menu_GotoParent();
	}
}

void Menu_UI_info_2_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("NONE"))
			gui.infobars.info2.setting = INFO_NONE;

		else if (MenuCompareSelected("BPM"))
			gui.infobars.info2.setting = INFO_BPM;

		else if (MenuCompareSelected("Instrument"))
			gui.infobars.info2.setting = INFO_INSTRUMENT;

		else if (MenuCompareSelected("Patt/Live mode"))
			gui.infobars.info2.setting = INFO_PATT_LIVE_MODE;

		else if (MenuCompareSelected("Pattern ID"))
			gui.infobars.info2.setting = INFO_PATTERN_ID;

		else if (MenuCompareSelected("MIDI Channel"))
			gui.infobars.info2.setting = INFO_MIDI_CHANNEL;

		else if (MenuCompareSelected("MIDI M/S"))
			gui.infobars.info2.setting = INFO_MIDI_MASTER_SLAVE;

		else if (MenuCompareSelected("MIDI Sync"))
			gui.infobars.info2.setting = INFO_MIDI_SYNC;

		else if (MenuCompareSelected("Play status"))
			gui.infobars.info2.setting = INFO_PLAY_STATUS;

//		Menu_GotoParent();
	}
}

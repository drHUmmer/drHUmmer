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
//			GPIO_SetBits(GPIOD, GPIO_Pin_14);					// GPIO //
			return;												// RETURN //
		}
	}

	if (MenuBackpressed(1)) {
		Menu_GotoParent();
//		GPIO_SetBits(GPIOD, GPIO_Pin_15);						// GPIO //
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
		case NONE:	gui.infobars.fx1.setting = NONE;gui.infobars.fx1.value = -1;					break;
	}
	switch (FXsettings.fx2) {
		case LPF:	gui.infobars.fx2.setting = LPF;	gui.infobars.fx2.value = FXsettings.lpfFreq;	break;
		case HPF:	gui.infobars.fx2.setting = HPF;	gui.infobars.fx2.value = FXsettings.hpfFreq;	break;
		case BC:	gui.infobars.fx2.setting = BC;	gui.infobars.fx2.value = FXsettings.bcBits;		break;
		case DS:	gui.infobars.fx2.setting = DS;	gui.infobars.fx2.value = FXsettings.dsFreq;		break;
		case NONE:	gui.infobars.fx2.setting = NONE;gui.infobars.fx2.value = -1;					break;
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

		LCD_StringInt(SCREENLINE2, SCREENSTART + (CHARWIDTH*5), sequencer.BPM, 1);
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

void Menu_File_Save_Pattern_handler (void) {
	int8_t rotary = MenuRotaryRead(1);
	static int8_t saveNr = 1;

	if (rotary) {
		saveNr += rotary;
		if (saveNr > 4)
			saveNr = 4;
		if (saveNr < 1)
			saveNr = 1;

		// Display update
		LCD_StringInt(SCREENLINE2, SCREENSTART + (CHARWIDTH*6), saveNr, 0);
	} else {
		if (MenuOKpressed(1)) {
			LCD_StringLine(SCREENLINE6, SCREENSTART, "Pattern saved");

			// todo: SAVE PATTERN

//			Menu_GotoParent();
		}
	}
}

void Menu_File_Load_Pattern_handler (void) {
	int8_t rotary = MenuRotaryRead(1);
	static int8_t loadNr = 1;

	if (rotary) {
		loadNr += rotary;
		if (loadNr > 4)
			loadNr = 4;
		if (loadNr < 1)
			loadNr = 1;

		// Display update
		LCD_StringInt(SCREENLINE2, SCREENSTART + (CHARWIDTH*6), loadNr, 0);
	} else {
		if (MenuOKpressed(1)) {
			LCD_StringLine(SCREENLINE6, SCREENSTART, "Pattern loaded");

			// todo: LOAD PATTERN

//			Menu_GotoParent();
		}
	}
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

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Set fx 1"))
			Menu_Filter_Bookmark_1_Set_Filter_1();

		else if (MenuCompareSelected("Set fx 2"))
			Menu_Filter_Bookmark_1_Set_Filter_2();
	}
}

void Menu_Filter_Bookmark_2_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Set fx 1"))
			Menu_Filter_Bookmark_2_Set_Filter_1();

		else if (MenuCompareSelected("Set fx 2"))
			Menu_Filter_Bookmark_2_Set_Filter_2();
	}
}

void Menu_Filter_Bookmark_1_Set_Filter_1_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("NONE")) {
			settings.filterbookmarks.bookmark1.fx1_filter 	= NONE;
			settings.filterbookmarks.bookmark1.fx1_value	= 0;
			Menu_GotoParent();
		}
		else if (MenuCompareSelected("LPF")) {
			settings.filterbookmarks.bookmark1.fx1_filter 	= LPF;
			settings.filterbookmarks.bookmark1.fx1_value	= LPF_HIGH / 2;
			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("HPF")) {
			settings.filterbookmarks.bookmark1.fx1_filter 	= HPF;
			settings.filterbookmarks.bookmark1.fx1_value	= HPF_HIGH / 2;
			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("BC")) {
			settings.filterbookmarks.bookmark1.fx1_filter 	= BC;
			settings.filterbookmarks.bookmark1.fx1_value	= BC_HIGH / 2;

			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("DS")) {
			settings.filterbookmarks.bookmark1.fx1_filter 	= DS;
			settings.filterbookmarks.bookmark1.fx1_value	= DS_HIGH / 2;

			Menu_Filter_Bookmark_1_Set_Value_1();
		}
	}
}

void Menu_Filter_Bookmark_1_Set_Filter_2_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("NONE")) {
			settings.filterbookmarks.bookmark1.fx2_filter 	= NONE;
			settings.filterbookmarks.bookmark1.fx2_value	= 0;
			Menu_GotoParent();
		}
		else if (MenuCompareSelected("LPF")) {
			settings.filterbookmarks.bookmark1.fx2_filter 	= LPF;
			settings.filterbookmarks.bookmark1.fx2_value	= LPF_HIGH / 2;
			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("HPF")) {
			settings.filterbookmarks.bookmark1.fx2_filter 	= HPF;
			settings.filterbookmarks.bookmark1.fx2_value	= HPF_HIGH / 2;
			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("BC")) {
			settings.filterbookmarks.bookmark1.fx2_filter 	= BC;
			settings.filterbookmarks.bookmark1.fx2_value	= BC_HIGH / 2;

			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("DS")) {
			settings.filterbookmarks.bookmark1.fx2_filter 	= DS;
			settings.filterbookmarks.bookmark1.fx2_value	= DS_HIGH / 2;

			Menu_Filter_Bookmark_1_Set_Value_1();
		}
	}
}

void Menu_Filter_Bookmark_1_Set_Value_1_handler (void) {
	int8_t rotaryValue = MenuRotaryRead(1);
	uint8_t fxFilter	= settings.filterbookmarks.bookmark1.fx1_filter;
	int16_t fxValue 	= settings.filterbookmarks.bookmark1.fx1_value;

	if (MenuOKpressed(1)) {
		Menu_GotoParent();
	}

	if (rotaryValue) {
		switch (fxFilter) {
			case LPF:
				fxValue += (rotaryValue * LPF_STEP);
				if (fxValue < LPF_LOW)
					fxValue = LPF_LOW;
				if (fxValue > LPF_HIGH)
					fxValue = LPF_HIGH;
				break;
			case HPF:
				fxValue += (rotaryValue * HPF_STEP);
				if (fxValue < HPF_LOW)
					fxValue = HPF_LOW;
				if (fxValue > HPF_HIGH)
					fxValue = HPF_HIGH;
				break;
			case DS:
				fxValue += (rotaryValue * DS_STEP);
				if (fxValue < DS_LOW)
					fxValue = DS_LOW;
				if (fxValue > DS_HIGH)
					fxValue = DS_HIGH;
				break;
			case BC:
				fxValue += (rotaryValue * BC_STEP);
				if (fxValue < BC_LOW)
					fxValue = BC_LOW;
				if (fxValue > BC_HIGH)
					fxValue = BC_HIGH;
				break;
		}

		LCD_StringInt (SCREENLINE3, SCREENSTART + (CHARWIDTH * 10), fxValue, 1);
		settings.filterbookmarks.bookmark1.fx1_value = fxValue;
	}
}

void Menu_Filter_Bookmark_1_Set_Value_2_handler (void) {
int8_t rotaryValue = MenuRotaryRead(1);
	uint8_t fxFilter	= settings.filterbookmarks.bookmark1.fx2_filter;
	int16_t fxValue 	= settings.filterbookmarks.bookmark1.fx2_value;

	if (MenuOKpressed(1)) {
		Menu_GotoParent();
	}

	if (rotaryValue) {
		switch (fxFilter) {
			case LPF:
				fxValue += (rotaryValue * LPF_STEP);
				if (fxValue < LPF_LOW)
					fxValue = LPF_LOW;
				if (fxValue > LPF_HIGH)
					fxValue = LPF_HIGH;
				break;
			case HPF:
				fxValue += (rotaryValue * HPF_STEP);
				if (fxValue < HPF_LOW)
					fxValue = HPF_LOW;
				if (fxValue > HPF_HIGH)
					fxValue = HPF_HIGH;
				break;
			case DS:
				fxValue += (rotaryValue * DS_STEP);
				if (fxValue < DS_LOW)
					fxValue = DS_LOW;
				if (fxValue > DS_HIGH)
					fxValue = DS_HIGH;
				break;
			case BC:
				fxValue += (rotaryValue * BC_STEP);
				if (fxValue < BC_LOW)
					fxValue = BC_LOW;
				if (fxValue > BC_HIGH)
					fxValue = BC_HIGH;
				break;
		}

		LCD_StringInt (SCREENLINE3, SCREENSTART + (CHARWIDTH * 10), fxValue, 1);
		settings.filterbookmarks.bookmark1.fx2_value = fxValue;
	}
}

void Menu_Filter_Bookmark_2_Set_Filter_1_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("NONE")) {
			settings.filterbookmarks.bookmark2.fx1_filter 	= NONE;
			settings.filterbookmarks.bookmark2.fx1_value	= 0;
			Menu_GotoParent();
		}
		else if (MenuCompareSelected("LPF")) {
			settings.filterbookmarks.bookmark2.fx1_filter 	= LPF;
			settings.filterbookmarks.bookmark2.fx1_value	= LPF_HIGH / 2;
			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("HPF")) {
			settings.filterbookmarks.bookmark2.fx1_filter 	= HPF;
			settings.filterbookmarks.bookmark2.fx1_value	= HPF_HIGH / 2;
			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("BC")) {
			settings.filterbookmarks.bookmark2.fx1_filter 	= BC;
			settings.filterbookmarks.bookmark2.fx1_value	= BC_HIGH / 2;

			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("DS")) {
			settings.filterbookmarks.bookmark2.fx1_filter 	= DS;
			settings.filterbookmarks.bookmark2.fx1_value	= DS_HIGH / 2;

			Menu_Filter_Bookmark_1_Set_Value_1();
		}
	}
}

void Menu_Filter_Bookmark_2_Set_Filter_2_handler (void) {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("NONE")) {
			settings.filterbookmarks.bookmark2.fx2_filter 	= NONE;
			settings.filterbookmarks.bookmark2.fx2_value	= 0;
			Menu_GotoParent();
		}
		else if (MenuCompareSelected("LPF")) {
			settings.filterbookmarks.bookmark2.fx2_filter 	= LPF;
			settings.filterbookmarks.bookmark2.fx2_value	= LPF_HIGH / 2;
			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("HPF")) {
			settings.filterbookmarks.bookmark2.fx2_filter 	= HPF;
			settings.filterbookmarks.bookmark2.fx2_value	= HPF_HIGH / 2;
			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("BC")) {
			settings.filterbookmarks.bookmark2.fx2_filter 	= BC;
			settings.filterbookmarks.bookmark2.fx2_value	= BC_HIGH / 2;

			Menu_Filter_Bookmark_1_Set_Value_1();
		}
		else if (MenuCompareSelected("DS")) {
			settings.filterbookmarks.bookmark2.fx2_filter 	= DS;
			settings.filterbookmarks.bookmark2.fx2_value	= DS_HIGH / 2;

			Menu_Filter_Bookmark_1_Set_Value_1();
		}
	}
}

void Menu_Filter_Bookmark_2_Set_Value_1_handler (void) {
int8_t rotaryValue = MenuRotaryRead(1);
	uint8_t fxFilter	= settings.filterbookmarks.bookmark2.fx1_filter;
	int16_t fxValue 	= settings.filterbookmarks.bookmark2.fx1_value;

	if (MenuOKpressed(1)) {
		Menu_GotoParent();
	}

	if (rotaryValue) {
		switch (fxFilter) {
			case LPF:
				fxValue += (rotaryValue * LPF_STEP);
				if (fxValue < LPF_LOW)
					fxValue = LPF_LOW;
				if (fxValue > LPF_HIGH)
					fxValue = LPF_HIGH;
				break;
			case HPF:
				fxValue += (rotaryValue * HPF_STEP);
				if (fxValue < HPF_LOW)
					fxValue = HPF_LOW;
				if (fxValue > HPF_HIGH)
					fxValue = HPF_HIGH;
				break;
			case DS:
				fxValue += (rotaryValue * DS_STEP);
				if (fxValue < DS_LOW)
					fxValue = DS_LOW;
				if (fxValue > DS_HIGH)
					fxValue = DS_HIGH;
				break;
			case BC:
				fxValue += (rotaryValue * BC_STEP);
				if (fxValue < BC_LOW)
					fxValue = BC_LOW;
				if (fxValue > BC_HIGH)
					fxValue = BC_HIGH;
				break;
		}

		LCD_StringInt (SCREENLINE3, SCREENSTART + (CHARWIDTH * 10), fxValue, 1);
		settings.filterbookmarks.bookmark2.fx1_value = fxValue;
	}
}

void Menu_Filter_Bookmark_2_Set_Value_2_handler (void) {
	int8_t rotaryValue = MenuRotaryRead(1);
	uint8_t fxFilter	= settings.filterbookmarks.bookmark2.fx2_filter;
	int16_t fxValue 	= settings.filterbookmarks.bookmark2.fx2_value;

	if (MenuOKpressed(1)) {
		Menu_GotoParent();
	}

	if (rotaryValue) {
		switch (fxFilter) {
			case LPF:
				fxValue += (rotaryValue * LPF_STEP);
				if (fxValue < LPF_LOW)
					fxValue = LPF_LOW;
				if (fxValue > LPF_HIGH)
					fxValue = LPF_HIGH;
				break;
			case HPF:
				fxValue += (rotaryValue * HPF_STEP);
				if (fxValue < HPF_LOW)
					fxValue = HPF_LOW;
				if (fxValue > HPF_HIGH)
					fxValue = HPF_HIGH;
				break;
			case DS:
				fxValue += (rotaryValue * DS_STEP);
				if (fxValue < DS_LOW)
					fxValue = DS_LOW;
				if (fxValue > DS_HIGH)
					fxValue = DS_HIGH;
				break;
			case BC:
				fxValue += (rotaryValue * BC_STEP);
				if (fxValue < BC_LOW)
					fxValue = BC_LOW;
				if (fxValue > BC_HIGH)
					fxValue = BC_HIGH;
				break;
		}

		LCD_StringInt (SCREENLINE3, SCREENSTART + (CHARWIDTH * 10), fxValue, 1);
		settings.filterbookmarks.bookmark2.fx2_value = fxValue;
	}
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
		if (MenuCompareSelected("Background"))
			Menu_UI_backcolour();

		else if (MenuCompareSelected("Text"))
			Menu_UI_textcolour();

		else if (MenuCompareSelected("Level bar"))
			Menu_UI_levelbarcolour();

		else if (MenuCompareSelected("Tone bar +"))
			Menu_UI_toneposbarcolour();

		else if (MenuCompareSelected("Tone bar -"))
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

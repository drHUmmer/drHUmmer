#include "menuScreens.h"

void Menu_Info() {
	gui.menus.current = &gui.menus.info;

	// Clear screen
	LCD_Clear(ColourConverterDec(gui.colours.background));
	delay_nms(100);

// Lines //
	LCD_SetTextColor(ColourConverterDec(gui.colours.text));
	// Fx
	LCD_DrawFullRect(210, 0, 3, 320);			// Horizontal line 		(1st row line)
	LCD_DrawFullRect(BARHEIGHT, 0, 3, 320);		// Horizontal line 		(2nd row line)
	LCD_DrawFullRect(BARHEIGHT, 158, 59, 4);	// Top veritcal line 	(split into coloums)

	// Verical lines (seperating instruments)
	LCD_DrawFullRect(0, 50,  BARHEIGHT, 4);
	LCD_DrawFullRect(0, 104, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 158, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 212, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 266, BARHEIGHT, 4);

// Texts
	MenuDrawInfo1(1);
	MenuDrawInfo2(1);
	MenuDrawEffect1(1);
	MenuDrawEffect2(1);

// Progressbars
	// D1
	LCD_Levelbar(&gui.bars.digitalDrum1Level, 	BAR_REDRAW);
	LCD_Tonebar(&gui.bars.digitalDrum1Tone, 	BAR_REDRAW);

	// D2
	LCD_Levelbar(&gui.bars.digitalDrum2Level, 	BAR_REDRAW);
	LCD_Tonebar(&gui.bars.digitalDrum2Tone, 	BAR_REDRAW);

	// D3
	LCD_Levelbar(&gui.bars.digitalDrum3Level, 	BAR_REDRAW);
	LCD_Tonebar(&gui.bars.digitalDrum3Tone, 	BAR_REDRAW);

	// D4
	LCD_Levelbar(&gui.bars.digitalDrum4Level, 	BAR_REDRAW);
	LCD_Tonebar(&gui.bars.digitalDrum4Tone, 	BAR_REDRAW);
}

void Menu_Main (void) {
	gui.menus.current = &gui.menus.main;
	MenuRedrawScreen();
}

// MIDI
void Menu_MIDI (void) {
	gui.menus.current = &gui.menus.midi;
	MenuRedrawScreen();
}

void Menu_MIDI_Channel (void) {
	gui.menus.current = &gui.menus.midi_channel;
	MenuRedrawScreen();

	LCD_StringLine(SCREENLINE2, SCREENSTART, "MIDI ch:");
	LCD_StringInt(SCREENLINE2, 167, settings.midi.channel, 1);
	LCD_StringLine(SCREENLINE4, SCREENSTART, "Min ch: 0");
	LCD_StringLine(SCREENLINE5, SCREENSTART, "Max ch: 15");
}

void Menu_MIDI_Master_Slave (void) {
	gui.menus.current = &gui.menus.midi_master_slave;
	MenuRedrawScreen();
}

void Menu_MIDI_Sync (void) {
	gui.menus.current = &gui.menus.midi_sync;
	MenuRedrawScreen();
}

// SEQ
void Menu_SEQ (void) {
	gui.menus.current = &gui.menus.seq;
	MenuRedrawScreen();
}

void Menu_SEQ_BPM (void) {
	gui.menus.current = &gui.menus.seq_bpm;
	MenuRedrawScreen();

	LCD_StringLine(SCREENLINE2, SCREENSTART, "BPM:");
	LCD_StringInt(SCREENLINE2, SCREENSTART + (18*5), sequencer.BPM, 1);

	LCD_StringLine(SCREENLINE4, SCREENSTART, "Min:   50");
	LCD_StringLine(SCREENLINE5, SCREENSTART, "Max:   300");
}

void Menu_SEQ_Patt_Live_Mode (void) {
	gui.menus.current = &gui.menus.seq_patt_live_mode;
	MenuRedrawScreen();
}

// FILE
void Menu_File (void) {
	gui.menus.current = &gui.menus.file;
	MenuRedrawScreen();
}

void Menu_File_Sample_Select (void) {
	gui.menus.current = &gui.menus.file_sample_select;
	MenuRedrawScreen();
}

void Menu_File_Save_Pattern (void) {
	gui.menus.current = &gui.menus.file_save_pattern;
	MenuRedrawScreen();
}

void Menu_File_Load_Pattern (void) {
	gui.menus.current = &gui.menus.file_load_pattern;
	MenuRedrawScreen();
}

// Filter bookmarks
void Menu_Filter_Bookmark (void) {
	gui.menus.current = &gui.menus.filter_bookmark;
	MenuRedrawScreen();
}

void Menu_Filter_Bookmark_1 (void) {
	gui.menus.current = &gui.menus.filter_bookmark_1;
	MenuRedrawScreen();

	// ToDo: Draw current settings

}

void Menu_Filter_Bookmark_2 (void) {
	gui.menus.current = &gui.menus.filter_bookmark_2;
	MenuRedrawScreen();

	// ToDo: Draw current settings
	uint8_t filter1 = settings.filter_bookmark_2.fx1_filter;
	uint16_t value1 = settings.filter_bookmark_2.fx1_value;

	uint8_t filter2 = settings.filter_bookmark_2.fx2_filter;
	uint16_t value2 = settings.filter_bookmark_2.fx2_value;

	uint8_t textFilterOffset	= SCREENSTART + (CHARWIDTH * 5);
	uint8_t textValueOffset		= SCREENSTART + (CHARWIDTH * 11);


	LCD_StringLine(SCREENLINE5, SCREENSTART, "Fx1:");
	LCD_StringLine(SCREENLINE6, SCREENSTART, "Fx2:");

	switch (filter) {
		case INFO_NONE:	
			LCD_StringLine(SCREENLINE5, textFilterOffset, "NONE");
			break;

		case INFO_BPM:	
			LCD_StringLine(SCREENLINE5, textFilterOffset, "BPM ");
			LCD_StringInt(SCREENLINE5, textValueOffset, value1, 0);
			break;
	}
}

// UI
void Menu_UI (void) {
	gui.menus.current = &gui.menus.ui;
	MenuRedrawScreen();
}

void Menu_UI_colours (void) {
	gui.menus.current = &gui.menus.ui_colours;
	MenuRedrawScreen();
}

void Menu_UI_info (void) {
	gui.menus.current = &gui.menus.ui_info;
	MenuRedrawScreen();
}

void Menu_UI_backcolour (void) {
	gui.menus.current = &gui.menus.ui_backcolour;
	MenuRedrawScreen();
}

void Menu_UI_textcolour (void) {
	gui.menus.current = &gui.menus.ui_textcolour;
	MenuRedrawScreen();
}

void Menu_UI_levelbarcolour (void) {
	gui.menus.current = &gui.menus.ui_levelbarcolour;
	MenuRedrawScreen();
}

void Menu_UI_toneposbarcolour (void) {
	gui.menus.current = &gui.menus.ui_toneposbarcolour;
	MenuRedrawScreen();
}

void Menu_UI_tonenegbarcolour (void) {
	gui.menus.current = &gui.menus.ui_tonenegbarcolour;
	MenuRedrawScreen();
}

void Menu_UI_info_1 (void) {
	gui.menus.current = &gui.menus.ui_info_1;
	MenuRedrawScreen();
}

void Menu_UI_info_2 (void) {
	gui.menus.current = &gui.menus.ui_info_2;
	MenuRedrawScreen();
}

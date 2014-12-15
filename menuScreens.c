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

	// Verical lines (seperating drums)
	LCD_DrawFullRect(0, 50,  BARHEIGHT, 4);
	LCD_DrawFullRect(0, 104, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 158, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 212, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 266, BARHEIGHT, 4);

// Texts
	MenuDrawInfo1();
	MenuDrawInfo2();
	MenuDrawEffect1();
	MenuDrawEffect2();

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

void Menu_Colours() {
	gui.menus.current = &gui.menus.colours;
	MenuRedrawScreen();
}

void Menu_Main() {
	gui.menus.current = &gui.menus.main;
	MenuRedrawScreen();
}

void Menu_SetBackcolour() {
	gui.menus.current = &gui.menus.backcolour;
	MenuRedrawScreen();
}

void Menu_SetTextcolour() {
	gui.menus.current = &gui.menus.textcolour;
	MenuRedrawScreen();
}

void Menu_SetLevelBarcolour() {
	gui.menus.current = &gui.menus.levelBarcolour;
	MenuRedrawScreen();
}

void Menu_SetTonePosBarcolour() {
	gui.menus.current = &gui.menus.tonePosBarcolour;
	MenuRedrawScreen();
}

void Menu_SetToneNegBarcolour() {
	gui.menus.current = &gui.menus.toneNegBarcolour;
	MenuRedrawScreen();
}

void Menu_SetBPM() {
	gui.menus.current = &gui.menus.bpm;
	MenuRedrawScreen();

	LCD_StringLine(150, 50, "BPM:");
	LCD_StringInt(120, 50, sequencer.BPM, 1);
}

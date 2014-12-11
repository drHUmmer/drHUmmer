#include "menuScreens.h"

void Menu_Info() {
	gui.menus.current = &gui.menus.info;

	// Clear screen
	LCD_Clear(ColourConverterDec(gui.colours.background));

// Lines //
	LCD_SetTextColor(ColourConverterDec(gui.colours.text));
	// Fx
	LCD_DrawFullRect(210, 0, 3, 320);			// Horizontal line [BPM]
	LCD_DrawFullRect(BARHEIGHT, 0, 3, 320);		// Horizontal line [filters]
	LCD_DrawFullRect(BARHEIGHT, 158, 59, 4);	// Top veritcal line


	// Verical lines (seperating drums)
	LCD_DrawFullRect(0, 50, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 104, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 158, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 212, BARHEIGHT, 4);
	LCD_DrawFullRect(0, 266, BARHEIGHT, 4);

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

// Texts
	LCD_SetTextColor(ColourConverterDec(gui.colours.text));

	// BPM
	LCD_StringLine(212, 10, "BPM:");
	LCD_StringInt (212, 60, sequencer.BPM, 0);

	// Instrument
	LCD_StringLine(212, 170, "Instr");
	if (sequencer.instrID == 0)								// DEMO
		 LCD_StringLine(212, 270, "0");						// CODE
	 else													// !!
		 LCD_StringInt (212, 200, sequencer.instrID, 0);	// !!

	// Effect 1
	switch (FXsettings.fx1) {
	case LPF: 	LCD_StringLine(182,10, "LP"); LCD_StringInt(182, 60, FXsettings.lpfFreq, 1);	break;
	case HPF: 	LCD_StringLine(182,10, "HP"); LCD_StringInt(182, 60, FXsettings.hpfFreq, 1);	break;
	case BC: 	LCD_StringLine(182,10, "BC"); LCD_StringInt(182, 60, FXsettings.bcBits, 1);		break;
	case DS: 	LCD_StringLine(182,10, "DS"); LCD_StringInt(182, 60, FXsettings.dsFreq, 1); 	break;
	case NONE:	LCD_StringLine(182,10, "fx 1 off"); break;
	}

	// Effect 2
	switch (FXsettings.fx2) {
	case LPF: 	LCD_StringLine(182,170, "LP"); LCD_StringInt(182, 220, FXsettings.lpfFreq, 1); 	break;
	case HPF: 	LCD_StringLine(182,170, "HP"); LCD_StringInt(182, 220, FXsettings.hpfFreq, 1);	break;
	case BC: 	LCD_StringLine(182,170, "BC"); LCD_StringInt(182, 220, FXsettings.bcBits, 1);	break;
	case DS: 	LCD_StringLine(182,170, "DS"); LCD_StringInt(182, 220, FXsettings.dsFreq, 1);	break;
	case NONE:	LCD_StringLine(182,170, "fx 2 off"); break;
	}
}

void Menu_Colours() {
	gui.menus.current = &gui.menus.colours;
	MenuRedrawScreen();
}

void Menu_Main() {
	gui.menus.current = &gui.menus.main;
//	gui.menus.main.selectedOption = 1;		// Always set the menu to "Set FX"
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

void Menu_SetFx() {
	gui.menus.current = &gui.menus.fx;

	switch(FXsettings.fx1) {
	case LPF: 	strcpy(gui.menus.fx.menuOptions[1], "Fx 1 - LPF "); break;
	case HPF: 	strcpy(gui.menus.fx.menuOptions[1], "Fx 1 - HPF "); break;
	case BC: 	strcpy(gui.menus.fx.menuOptions[1], "Fx 1 - BC  "); break;
	case DS: 	strcpy(gui.menus.fx.menuOptions[1], "Fx 1 - DS  "); break;
	default: 	strcpy(gui.menus.fx.menuOptions[1], "Fx 1 - NONE"); break;
	}

	switch(FXsettings.fx2) {
	case LPF: 	strcpy(gui.menus.fx.menuOptions[2], "Fx 2 - LPF "); break;
	case HPF: 	strcpy(gui.menus.fx.menuOptions[2], "Fx 2 - HPF "); break;
	case BC: 	strcpy(gui.menus.fx.menuOptions[2], "Fx 2 - BC  "); break;
	case DS: 	strcpy(gui.menus.fx.menuOptions[2], "Fx 2 - DS  "); break;
	default: 	strcpy(gui.menus.fx.menuOptions[2], "Fx 2 - NONE"); break;
	}

	MenuRedrawScreen();
}

void Menu_SetFx1() {
	gui.menus.current = &gui.menus.fx1;

	MenuClearTitle(&gui.menus.fx1);

	switch(FXsettings.fx1) {
	case LPF: 	strcpy(gui.menus.fx1.menuTitle,	"Set fx 1 - LPF "); 	break;
	case HPF: 	strcpy(gui.menus.fx1.menuTitle,	"Set fx 1 - HPF "); 	break;
	case BC: 	strcpy(gui.menus.fx1.menuTitle,	"Set fx 1 - BC  "); 	break;
	case DS: 	strcpy(gui.menus.fx1.menuTitle,	"Set fx 1 - DS  "); 	break;
	default: 	strcpy(gui.menus.fx1.menuTitle,	"Set fx 1 - NONE"); 	break;
	}

	MenuRedrawScreen();
}

void Menu_SetFx2() {
	gui.menus.current = &gui.menus.fx2;

	MenuClearTitle(&gui.menus.fx2);

	switch(FXsettings.fx2) {
	case LPF: 	strcpy(gui.menus.fx2.menuTitle,	"Set fx 2 - LPF "); 	break;
	case HPF: 	strcpy(gui.menus.fx2.menuTitle,	"Set fx 2 - HPF "); 	break;
	case BC: 	strcpy(gui.menus.fx2.menuTitle,	"Set fx 2 - BC  "); 	break;
	case DS: 	strcpy(gui.menus.fx2.menuTitle,	"Set fx 2 - DS  "); 	break;
	default: 	strcpy(gui.menus.fx2.menuTitle,	"Set fx 2 - NONE"); 	break;
	}

	MenuRedrawScreen();
}

void Menu_SetBPM() {
	gui.menus.current = &gui.menus.bpm;
	MenuRedrawScreen();

	LCD_StringLine(150, 50, "BPM:");
	LCD_StringInt(120, 50, sequencer.BPM, 1);
}

void Menu_SetlpfFreq() {
	gui.menus.current = &gui.menus.lpFreq;
	MenuRedrawScreen();

	LCD_StringLine(150, 50, "LPF freq:");
	LCD_StringInt(120, 50, FXsettings.lpfFreq, 1);
}

void Menu_SethpfFreq() {
	gui.menus.current = &gui.menus.hpFreq;
	MenuRedrawScreen();

	LCD_StringLine(150, 50, "HPF freq:");
	LCD_StringInt(120, 50, FXsettings.hpfFreq, 1);
}

void Menu_SetDSFreq() {
	gui.menus.current = &gui.menus.dsFreq;
	MenuRedrawScreen();

	LCD_StringLine(150, 50, "DS freq:");
	LCD_StringInt(120, 50, FXsettings.dsFreq, 1);
}

void Menu_SetBCbits() {
	gui.menus.current = &gui.menus.bcBits;
	MenuRedrawScreen();

	LCD_StringLine(150, 50, "BC bits:");
	LCD_StringInt(120, 50, FXsettings.bcBits, 1);
}

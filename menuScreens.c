#include "menuScreens.h"

void Menu_Info() {
	gui.menus.current = &gui.menus.info;

	int8_t 	value = 0;
	uint8_t level = 0;

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
	value = sequencer.instr0.tone;
	level = sequencer.instr0.level;

//	LCD_CreateVertProgressbar(0, 108, BARHEIGHT, 25, backgroundColour, colourLevel, level);
	if (value > 0) {
//		LCD_CreateVertProgressbar(BARHEIGHT / 2, 133, BARHEIGHT / 2, 25, backgroundColour, colourTonePos, value);	// Tone positive
	}
	else if (value < 0) {
//		LCD_CreateVertProgressbar(0, 133, BARHEIGHT / 2, 25, colourToneNeg, backgroundColour, 100 + value);// Tone negative
	}
	else {
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
		LCD_DrawFullRect(BARHEIGHT / 2 - 2, 133, 4, 25);
	}

	// D2
	value = sequencer.instr1.tone;
	level = sequencer.instr1.level;

//	LCD_CreateVertProgressbar(0, 162, BARHEIGHT, 25, backgroundColour, colourLevel, level);		// Level
	if (value > 0) {
//		LCD_CreateVertProgressbar(BARHEIGHT / 2, 187, BARHEIGHT / 2, 25, backgroundColour, colourTonePos, value);	// Tone positive
	}
	else if (value < 0) {
//		LCD_CreateVertProgressbar(0, 187, BARHEIGHT / 2, 25, colourToneNeg, backgroundColour, 100 + value);// Tone negative
	}
	else {
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
		LCD_DrawFullRect(BARHEIGHT / 2 - 2, 187, 4, 25);
	}

	// D3
	value = sequencer.instr2.tone;
	level = sequencer.instr2.level;

//	LCD_CreateVertProgressbar(0, 216, BARHEIGHT, 25, backgroundColour, colourLevel, level);
	if (value > 0) {
//		LCD_CreateVertProgressbar(BARHEIGHT / 2, 241, BARHEIGHT / 2, 25, backgroundColour, colourTonePos, value);	// Tone positive
	}
	else if (value < 0) {
//		LCD_CreateVertProgressbar(0, 241, BARHEIGHT / 2, 25, colourToneNeg, backgroundColour, 100 + value);// Tone negative
	}
	else {
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
		LCD_DrawFullRect(BARHEIGHT / 2 - 2, 241, 4, 25);
	}

	// D4
	value = sequencer.instr3.tone;
	level = sequencer.instr3.level;

//	LCD_CreateVertProgressbar(0, 270, BARHEIGHT, 25, backgroundColour, colourLevel, level);
	if (value > 0) {
//		LCD_CreateVertProgressbar(BARHEIGHT / 2, 295, BARHEIGHT / 2, 25, backgroundColour, colourTonePos, value);	// Tone positive
	}
	else if (value < 0) {
//		LCD_CreateVertProgressbar(0, 295, BARHEIGHT / 2, 25, colourToneNeg, backgroundColour, 100 + value);// Tone negative
	}
	else {
		LCD_SetTextColor(ColourConverterDec(gui.colours.text));
		LCD_DrawFullRect(BARHEIGHT / 2 - 2, 295, 4, 25);
	}

// Texts
	LCD_SetTextColor(ColourConverterDec(gui.colours.text));

	// BPM
	LCD_StringLine(212, 10, "BPM:");
	LCD_StringInt (212, 60, sequencer.BPM, 0);

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
	gui.menus.main.selectedOption = 1;		// Always set the menu to "Set FX"
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

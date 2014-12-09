#include "menuHandlers.h"

static uint8_t 	volumeAnalogDrum1	= 0;
static uint8_t 	volumeAnalogDrum2	= 0;
static uint8_t 	volumeDigitalDrum1	= 0;
static uint8_t 	volumeDigitalDrum2	= 0;
static uint8_t 	volumeDigitalDrum3	= 0;
static uint8_t 	volumeDigitalDrum4	= 0;

static int8_t	toneDigitalDrum1	= 0;
static int8_t	toneDigitalDrum2	= 0;
static int8_t	toneDigitalDrum3	= 0;
static int8_t	toneDigitalDrum4	= 0;

static uint8_t	mh_effect1			= 0;
static uint8_t	mh_effect2			= 0;
static uint16_t	mh_bcBits			= 0;
static uint16_t mh_dsFreq			= 0;
static uint16_t	mh_lpfFreq			= 0;
static uint16_t	mh_hpfFreq			= 0;

static void Menu_GotoParent() {
	if (!MenuCompareTitle(TITLE_MAINSCREEN)) {
		mainmenu.menuCurrent->parent();
	}
}

void Menu_UpdateHandler() {
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
	mainmenu.menuCurrent->handler();

	// Always reset the buttons, to prevent weird things to happen
	MenuOKpressed(1);
	MenuBackpressed(1);
}

void Menu_MainHandler() {
	 if (MenuOKpressed(1)) {
	 	Menu_Settings();
	 	return;
	 }

	uint16_t colourLevel 		= mainmenu.levelbarcolour;
	uint16_t colourTonePos		= mainmenu.toneposbarcolour;
	uint16_t colourToneNeg		= mainmenu.tonenegbarcolour;
	uint16_t backgroundColour	= mainmenu.backgroundcolour;

	 if (volumeDigitalDrum1 != sequencer.instr0.level) {
		 volumeDigitalDrum1 = sequencer.instr0.level;

		 LCD_CreateVertProgressbar(0, 108, BARHEIGHT, 25, backgroundColour, colourLevel, volumeDigitalDrum1);
	 }

	 if (volumeDigitalDrum2 != sequencer.instr1.level) {

	 }

	 if (volumeDigitalDrum3 != sequencer.instr2.level) {

	 }

	 if (volumeDigitalDrum4 != sequencer.instr3.level) {

	 }

//	 volumeAnalogDrum1	= sequencer.bassdrum.level;
//	 volumeAnalogDrum2	= sequencer.snaredrum.level;
//	 volumeDigitalDrum1	= sequencer.instr0.level;
//	 volumeDigitalDrum2	= sequencer.instr1.level;
//	 volumeDigitalDrum3	= sequencer.instr2.level;
//	 volumeDigitalDrum4	= sequencer.instr3.level;
//
//	 toneDigitalDrum1	= sequencer.instr0.tone;
//	 toneDigitalDrum2	= sequencer.instr1.tone;
//	 toneDigitalDrum3	= sequencer.instr2.tone;
//	 toneDigitalDrum4	= sequencer.instr3.tone;

}

void Menu_SettingsHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Set colours"))
			Menu_Colours();

		if (MenuCompareSelected("Set fx"))
			Menu_SetFx();
	}
}

void Menu_ColourHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Invert")) {
			uint16_t temp = mainmenu.backgroundcolour;
			mainmenu.backgroundcolour = mainmenu.foregroundcolour;
			mainmenu.foregroundcolour = temp;
			MenuRedrawScreen();
		}

		if (MenuCompareSelected("Back colour"))
			Menu_SetBackcolour();

		if (MenuCompareSelected("Text colour"))
			Menu_SetTextcolour();

		if (MenuCompareSelected("Level colour"))
			Menu_SetLevelBarcolour();

		if (MenuCompareSelected("Tone + colour"))
			Menu_SetTonePosBarcolour();

		if (MenuCompareSelected("Tone - colour"))
			Menu_SetToneNegBarcolour();
	}
}

void Menu_BackcolourHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			mainmenu.backgroundcolour = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			mainmenu.backgroundcolour = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			mainmenu.backgroundcolour = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			mainmenu.backgroundcolour = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			mainmenu.backgroundcolour = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			mainmenu.backgroundcolour = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			mainmenu.backgroundcolour = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			mainmenu.backgroundcolour = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			mainmenu.backgroundcolour = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			mainmenu.backgroundcolour = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_TextcolourHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			mainmenu.foregroundcolour = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			mainmenu.foregroundcolour = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			mainmenu.foregroundcolour = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			mainmenu.foregroundcolour = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			mainmenu.foregroundcolour = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			mainmenu.foregroundcolour = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			mainmenu.foregroundcolour = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			mainmenu.foregroundcolour = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			mainmenu.foregroundcolour = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			mainmenu.foregroundcolour = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_LevelBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			mainmenu.levelbarcolour = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			mainmenu.levelbarcolour = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			mainmenu.levelbarcolour = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			mainmenu.levelbarcolour = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			mainmenu.levelbarcolour = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			mainmenu.levelbarcolour = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			mainmenu.levelbarcolour = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			mainmenu.levelbarcolour = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			mainmenu.levelbarcolour = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			mainmenu.levelbarcolour = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_TonePosBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			mainmenu.toneposbarcolour = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			mainmenu.toneposbarcolour = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			mainmenu.toneposbarcolour = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			mainmenu.toneposbarcolour = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			mainmenu.toneposbarcolour = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			mainmenu.toneposbarcolour = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			mainmenu.toneposbarcolour = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			mainmenu.toneposbarcolour = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			mainmenu.toneposbarcolour = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			mainmenu.toneposbarcolour = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_ToneNegBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			mainmenu.tonenegbarcolour = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			mainmenu.tonenegbarcolour = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			mainmenu.tonenegbarcolour = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			mainmenu.tonenegbarcolour = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			mainmenu.tonenegbarcolour = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			mainmenu.tonenegbarcolour = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			mainmenu.tonenegbarcolour = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			mainmenu.tonenegbarcolour = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			mainmenu.tonenegbarcolour = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			mainmenu.tonenegbarcolour = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_SetFxHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		uint8_t currentSelectedOption = mainmenu.menuCurrent->currentOption;

		if (strstr(mainmenu.menuCurrent->menuOptions[currentSelectedOption], "Fx 1") != NULL) {
			Menu_SetFx1();
		}
		if (strstr(mainmenu.menuCurrent->menuOptions[currentSelectedOption], "Fx 2") != NULL) {
			Menu_SetFx2();
		}
	}
}

void Menu_SetFx1Handler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("None"))
			FXsettings.fx1 = NONE;

		if (MenuCompareSelected("Low-pass"))
			FXsettings.fx1 = LPF;

		if (MenuCompareSelected("High-pass"))
			FXsettings.fx1 = HPF;

		if (MenuCompareSelected("Bitcrusher"))
			FXsettings.fx1 = BC;

		if (MenuCompareSelected("Down-sampler"))
			FXsettings.fx1 = DS;

		MenuClearTitle(mainmenu.menuCurrent);

		switch(FXsettings.fx1) {
		case LPF: 	strcpy(mainmenu.menuCurrent->menuTitle, "Set fx 1 - LPF "); 	break;
		case HPF: 	strcpy(mainmenu.menuCurrent->menuTitle,	"Set fx 1 - HPF "); 	break;
		case BC: 	strcpy(mainmenu.menuCurrent->menuTitle,	"Set fx 1 - BC  "); 	break;
		case DS: 	strcpy(mainmenu.menuCurrent->menuTitle,	"Set fx 1 - DS  "); 	break;
		default: 	strcpy(mainmenu.menuCurrent->menuTitle,	"Set fx 1 - NONE"); 	break;
		}

		MenuDrawTitle(1);
	}
}

void Menu_SetFx2Handler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("None"))
			FXsettings.fx2 = NONE;

		if (MenuCompareSelected("Low-pass"))
			FXsettings.fx2 = LPF;

		if (MenuCompareSelected("High-pass"))
			FXsettings.fx2 = HPF;

		if (MenuCompareSelected("Bitcrusher"))
			FXsettings.fx2 = BC;

		if (MenuCompareSelected("Down-sampler"))
			FXsettings.fx2 = DS;

		MenuClearTitle(mainmenu.menuCurrent);

		switch(FXsettings.fx2) {
		case LPF: 	strcpy(mainmenu.menuCurrent->menuTitle, "Set fx 2 - LPF "); 	break;
		case HPF: 	strcpy(mainmenu.menuCurrent->menuTitle,	"Set fx 2 - HPF "); 	break;
		case BC: 	strcpy(mainmenu.menuCurrent->menuTitle,	"Set fx 2 - BC  "); 	break;
		case DS: 	strcpy(mainmenu.menuCurrent->menuTitle,	"Set fx 2 - DS  "); 	break;
		default: 	strcpy(mainmenu.menuCurrent->menuTitle,	"Set fx 2 - NONE"); 	break;
		}

		MenuDrawTitle(1);
	}
}


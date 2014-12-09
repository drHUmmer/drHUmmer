#include "menuHandlers.h"

static void Menu_GotoParent() {
	if (!MenuCompareTitle(TITLE_INFOSCREEN)) {
		gui.menus.current->parent();
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
	gui.menus.current->handler();

	// Always reset the buttons, to prevent weird things to happen
	MenuOKpressed(1);
	MenuBackpressed(1);
}

void Menu_InfoHandler() {
	 if (MenuOKpressed(1)) {
	 	Menu_Main();
	 	return;
	 }

	 if (gui.bars.digitalDrum1Level.value != sequencer.instr0.level) {
		 gui.bars.digitalDrum1Level.value = sequencer.instr0.level;
		 LCD_Levelbar(&gui.bars.digitalDrum1Level, gui.bars.digitalDrum1Level.value);
	 }
}

void Menu_MainHandler() {
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
			uint16_t temp 				= gui.colours.background;
			gui.colours.background 		= gui.colours.text;
			gui.colours.text 			= temp;
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
			gui.colours.background = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.background = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.background = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.background = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.background = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.background = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.background = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.background = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.background = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.background = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_TextcolourHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.text = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.text = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.text = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.text = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.text = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.text = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.text = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.text = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.text = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.text = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_LevelBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.levelBar = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.levelBar = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.levelBar = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.levelBar = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.levelBar = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.levelBar = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.levelBar = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.levelBar = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.levelBar = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.levelBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_TonePosBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.tonePosBar = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.tonePosBar = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.tonePosBar = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.tonePosBar = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.tonePosBar = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.tonePosBar = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.tonePosBar = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.tonePosBar = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.tonePosBar = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.tonePosBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_ToneNegBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.toneNegBar = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.toneNegBar = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.toneNegBar = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.toneNegBar = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.toneNegBar = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.toneNegBar = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.toneNegBar = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.toneNegBar = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.toneNegBar = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.toneNegBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_SetFxHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		uint8_t currentSelectedOption = gui.menus.current->selectedOption;

		if (strstr(gui.menus.current->menuOptions[currentSelectedOption], "Fx 1") != NULL) {
			Menu_SetFx1();
		}
		if (strstr(gui.menus.current->menuOptions[currentSelectedOption], "Fx 2") != NULL) {
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

		MenuClearTitle(gui.menus.current);

		switch(FXsettings.fx1) {
		case LPF: 	strcpy(gui.menus.current->menuTitle,	"Set fx 1 - LPF "); 	break;
		case HPF: 	strcpy(gui.menus.current->menuTitle,	"Set fx 1 - HPF "); 	break;
		case BC: 	strcpy(gui.menus.current->menuTitle,	"Set fx 1 - BC  "); 	break;
		case DS: 	strcpy(gui.menus.current->menuTitle, 	"Set fx 1 - DS  "); 	break;
		default: 	strcpy(gui.menus.current->menuTitle,	"Set fx 1 - NONE"); 	break;
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

		MenuClearTitle(gui.menus.current);

		switch(FXsettings.fx2) {
		case LPF: 	strcpy(gui.menus.current->menuTitle, 	"Set fx 2 - LPF "); 	break;
		case HPF: 	strcpy(gui.menus.current->menuTitle,	"Set fx 2 - HPF "); 	break;
		case BC: 	strcpy(gui.menus.current->menuTitle,	"Set fx 2 - BC  "); 	break;
		case DS: 	strcpy(gui.menus.current->menuTitle,	"Set fx 2 - DS  "); 	break;
		default: 	strcpy(gui.menus.current->menuTitle,	"Set fx 2 - NONE"); 	break;
		}

		MenuDrawTitle(1);
	}
}

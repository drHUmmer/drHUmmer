#include "menuHandlers.h"

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
	 }

	 // ToDo: Progress bars
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

		if (MenuCompareSelected("Set back colour"))
			Menu_SetBackcolour();

		if (MenuCompareSelected("Set text colour"))
			Menu_SetTextcolour();
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


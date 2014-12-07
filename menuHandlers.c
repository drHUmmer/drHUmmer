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
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			return;												// RETURN //
		}
	}

	if (MenuBackpressed(1)) {
		Menu_GotoParent();
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
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
		if (MenuCompareSelected(TITLE_COLOURMENU))
			Menu_Colours();
	}
}

void Menu_ColourHandler() {
	MenuUpdateSelectedItem();

	if (MenuCompareSelected("Invert")) {
		uint16_t temp = mainmenu.backgroundcolour;
		mainmenu.backgroundcolour = mainmenu.foregroundcolour;
		mainmenu.foregroundcolour = temp;
	}

	if (MenuCompareSelected("Set back colour"))
		Menu_SetBackcolour();

	if (MenuCompareSelected("Set text colour"))
		Menu_SetTextcolour();
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


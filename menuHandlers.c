#include "menuHandlers.h"

static void Menu_GotoParent() {
	if (mainmenu.menuCurrent->hasParent) {
		mainmenu.menuCurrent->parent();
	}
}

void Menu_UpdateHandler() {
	if (MenuOKpressed(0)) {
		uint8_t currentSelectedOption = mainmenu.menuCurrent->currentOption;
		if (!(strcmp(mainmenu.menuCurrent->menuOptions[currentSelectedOption], "Back"))) {
			Menu_GotoParent();
			MenuOKpressed(1);		// Reset OK button
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			return;
		}
	}

	if (MenuBackpressed(1)) {
		Menu_GotoParent();
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		return;
	}

	// Run current menu handler
	mainmenu.menuCurrent->handler();

	// Otherwise the buttons would be "pressed" even when it isn't
	MenuOKpressed(1);
	MenuBackpressed(1);
}

void Menu_MainHandler() {
	 if (MenuOKpressed(1)) {
	 	Menu_Settings();
	 }
}

void Menu_SettingsHandler() {
	MenuUpdateSelectedItem();

	if (mainmenu.menuCurrent->currentOption == 1 && MenuOKpressed(1)) {
		mainmenu.menuCurrent = &mainmenu.menuBackcolour;
		MenuRedrawScreen();
	}

	if (mainmenu.menuCurrent->currentOption == 2 && MenuOKpressed(1)) {
		mainmenu.menuCurrent = &mainmenu.menuTextcolour;
		MenuRedrawScreen();
	}
}

void Menu_BackcolourHandler() {
	MenuUpdateSelectedItem();

	uint8_t currentOption = mainmenu.menuCurrent->currentOption;

	if (MenuOKpressed(1)) {
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "White"))) {
			mainmenu.backgroundcolour = White;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Black"))) {
			mainmenu.backgroundcolour = Black;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Red"))) {
			mainmenu.backgroundcolour = Red;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Green"))) {
			mainmenu.backgroundcolour = Green;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Blue"))) {
			mainmenu.backgroundcolour = Blue;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Yellow"))) {
			mainmenu.backgroundcolour = Yellow;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Cyan"))) {
			mainmenu.backgroundcolour = Cyan;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Magenta"))) {
			mainmenu.backgroundcolour = Magenta;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Grey"))) {
			mainmenu.backgroundcolour = Grey;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Blue - 2"))) {
			mainmenu.backgroundcolour = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_TextcolourHandler() {
	MenuUpdateSelectedItem();

	uint8_t currentOption = mainmenu.menuCurrent->currentOption;

	if (MenuOKpressed(1)) {
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "White"))) {
			mainmenu.foregroundcolour = White;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Black"))) {
			mainmenu.foregroundcolour = Black;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Red"))) {
			mainmenu.foregroundcolour = Red;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Green"))) {
			mainmenu.foregroundcolour = Green;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Blue"))) {
			mainmenu.foregroundcolour = Blue;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Yellow"))) {
			mainmenu.foregroundcolour = Yellow;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Cyan"))) {
			mainmenu.foregroundcolour = Cyan;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Magenta"))) {
			mainmenu.foregroundcolour = Magenta;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Grey"))) {
			mainmenu.foregroundcolour = Grey;
			MenuRedrawScreen();
		}
		if(!(strcmp(mainmenu.menuCurrent->menuOptions[currentOption], "Blue - 2"))) {
			mainmenu.foregroundcolour = Blue2;
			MenuRedrawScreen();
		}
	}
}


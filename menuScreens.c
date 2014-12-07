#include "menuScreens.h"

void Menu_Main() {
	mainmenu.menuCurrent = &mainmenu.menuMain;
	MenuRedrawScreen();

	LCD_CreateVertProgressbar(5, 5, 150, 25, ColourConverterEnc(50,10,10), Yellow, 33);
}

void Menu_Colours() {
	mainmenu.menuCurrent = &mainmenu.menuColours;
	MenuRedrawScreen();
}

void Menu_Settings() {
	mainmenu.menuCurrent = &mainmenu.menuSettings;
	mainmenu.menuSettings.currentOption = 1;		// Always set the menu to "Set FX"
	MenuRedrawScreen();
}

void Menu_SetBackcolour() {
	mainmenu.menuCurrent = &mainmenu.menuBackcolour;
	MenuRedrawScreen();
}

void Menu_SetTextcolour() {
	mainmenu.menuCurrent = &mainmenu.menuTextcolour;
	MenuRedrawScreen();
}

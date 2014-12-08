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

void Menu_SetFx() {
	mainmenu.menuCurrent = &mainmenu.menuFx;

	switch(FXsettings.fx1) {
	case LPF: 	strcpy(mainmenu.menuFx.menuOptions[1], "Fx 1 - LPF "); break;
	case HPF: 	strcpy(mainmenu.menuFx.menuOptions[1], "Fx 1 - HPF "); break;
	case BC: 	strcpy(mainmenu.menuFx.menuOptions[1], "Fx 1 - BC  "); break;
	case DS: 	strcpy(mainmenu.menuFx.menuOptions[1], "Fx 1 - DS  "); break;
	default: 	strcpy(mainmenu.menuFx.menuOptions[1], "Fx 1 - NONE"); break;
	}

	switch(FXsettings.fx2) {
	case LPF: 	strcpy(mainmenu.menuFx.menuOptions[2], "Fx 2 - LPF "); break;
	case HPF: 	strcpy(mainmenu.menuFx.menuOptions[2], "Fx 2 - HPF "); break;
	case BC: 	strcpy(mainmenu.menuFx.menuOptions[2], "Fx 2 - BC  "); break;
	case DS: 	strcpy(mainmenu.menuFx.menuOptions[2], "Fx 2 - DS  "); break;
	default: 	strcpy(mainmenu.menuFx.menuOptions[2], "Fx 2 - NONE"); break;
	}

	MenuRedrawScreen();
}

void Menu_SetFx1() {
	mainmenu.menuCurrent = &mainmenu.menuFx1;

	MenuClearTitle(&mainmenu.menuFx1);

	switch(FXsettings.fx1) {
	case LPF: 	strcpy(mainmenu.menuFx1.menuTitle,	"Set fx 1 - LPF "); 	break;
	case HPF: 	strcpy(mainmenu.menuFx1.menuTitle,	"Set fx 1 - HPF "); 	break;
	case BC: 	strcpy(mainmenu.menuFx1.menuTitle,	"Set fx 1 - BC  "); 	break;
	case DS: 	strcpy(mainmenu.menuFx1.menuTitle,	"Set fx 1 - DS  "); 	break;
	default: 	strcpy(mainmenu.menuFx1.menuTitle,	"Set fx 1 - NONE"); 	break;
	}

	MenuRedrawScreen();
}

void Menu_SetFx2() {
	mainmenu.menuCurrent = &mainmenu.menuFx2;

	MenuClearTitle(&mainmenu.menuFx2);

	switch(FXsettings.fx2) {
	case LPF: 	strcpy(mainmenu.menuFx2.menuTitle,	"Set fx 2 - LPF "); 	break;
	case HPF: 	strcpy(mainmenu.menuFx2.menuTitle,	"Set fx 2 - HPF "); 	break;
	case BC: 	strcpy(mainmenu.menuFx2.menuTitle,	"Set fx 2 - BC  "); 	break;
	case DS: 	strcpy(mainmenu.menuFx2.menuTitle,	"Set fx 2 - DS  "); 	break;
	default: 	strcpy(mainmenu.menuFx2.menuTitle,	"Set fx 2 - NONE"); 	break;
	}

	MenuRedrawScreen();
}

#include "menu.h"

void MenuSetup() {
	LCD_Clear(ColourConverterDec(Black));
	mainmenu.backgroundcolour 	= Black;
	mainmenu.foregroundcolour 	= Green;
	mainmenu.menuCurrent		= &mainmenu.menuMain;

	MenuClearStringMemory(&mainmenu.menuMain);
	MenuClearStringMemory(&mainmenu.menuSettings);
	MenuClearStringMemory(&mainmenu.menuBackcolour);
	MenuClearStringMemory(&mainmenu.menuTextcolour);

	// Main screen //
	mainmenu.menuMain.currentOption							= 0;
	mainmenu.menuMain.nrOfOptions							= 0;
	mainmenu.menuMain.showCursor							= 0;
	mainmenu.menuMain.handler								= Menu_MainHandler;		// Function
	mainmenu.menuMain.hasParent								= 0;
	mainmenu.menuMain.parent								= 0;
	strcpy(mainmenu.menuMain.menuTitle						, TITLE_MAINSCREEN);
	strcpy(mainmenu.menuMain.menuOptions [0]				, "-");
	

	// Settings Menu //
	mainmenu.menuSettings.currentOption						= 0;
	mainmenu.menuSettings.nrOfOptions						= 5;
	mainmenu.menuSettings.showCursor						= 1;
	mainmenu.menuSettings.handler							= Menu_SettingsHandler;	// Function
	mainmenu.menuSettings.hasParent							= 1;
	mainmenu.menuSettings.parent							= Menu_Main;
	strcpy(mainmenu.menuSettings.menuTitle					, TITLE_SETTINGSMENU);
	strcpy(mainmenu.menuSettings.menuOptions [0]			, "Back");
	strcpy(mainmenu.menuSettings.menuOptions [1]			, "Set back colour");
	strcpy(mainmenu.menuSettings.menuOptions [2]			, "Set text colour");
	strcpy(mainmenu.menuSettings.menuOptions [3]			, "Set FX");
	strcpy(mainmenu.menuSettings.menuOptions [4]			, "Banana");

	// Background colour //
	mainmenu.menuBackcolour.currentOption					= 0;
	mainmenu.menuBackcolour.nrOfOptions						= 11;
	mainmenu.menuBackcolour.showCursor						= 1;
	mainmenu.menuBackcolour.handler							= Menu_BackcolourHandler;
	mainmenu.menuBackcolour.parent							= Menu_Settings;
	mainmenu.menuBackcolour.hasParent						= 1;
	strcpy(mainmenu.menuBackcolour.menuTitle				, TITLE_BACKCOLOURMENU);
	strcpy(mainmenu.menuBackcolour.menuOptions	[0]			, "Back");
	strcpy(mainmenu.menuBackcolour.menuOptions	[1]			, "White");
	strcpy(mainmenu.menuBackcolour.menuOptions	[2]			, "Black");
	strcpy(mainmenu.menuBackcolour.menuOptions	[3]			, "Red");
	strcpy(mainmenu.menuBackcolour.menuOptions	[4]			, "Green");
	strcpy(mainmenu.menuBackcolour.menuOptions	[5]			, "Blue");
	strcpy(mainmenu.menuBackcolour.menuOptions	[6]			, "Yellow");
	strcpy(mainmenu.menuBackcolour.menuOptions	[7]			, "Cyan");
	strcpy(mainmenu.menuBackcolour.menuOptions	[8]			, "Magenta");
	strcpy(mainmenu.menuBackcolour.menuOptions	[9]			, "Grey");
	strcpy(mainmenu.menuBackcolour.menuOptions	[10]		, "Blue - 2");

	// Foreground colour //
	mainmenu.menuTextcolour.currentOption					= 0;
	mainmenu.menuTextcolour.nrOfOptions						= 11;
	mainmenu.menuTextcolour.showCursor						= 1;
	mainmenu.menuTextcolour.handler							= Menu_TextcolourHandler;
	mainmenu.menuTextcolour.parent							= Menu_Settings;
	mainmenu.menuTextcolour.hasParent						= 1;
	strcpy(mainmenu.menuTextcolour.menuTitle	  			, TITLE_TEXTCOLOURMENU);
	strcpy(mainmenu.menuTextcolour.menuOptions [0]			, "Back");
	strcpy(mainmenu.menuTextcolour.menuOptions [1]			, "White");
	strcpy(mainmenu.menuTextcolour.menuOptions [2]			, "Black");
	strcpy(mainmenu.menuTextcolour.menuOptions [3]			, "Red");
	strcpy(mainmenu.menuTextcolour.menuOptions [4]			, "Green");
	strcpy(mainmenu.menuTextcolour.menuOptions [5]			, "Blue");
	strcpy(mainmenu.menuTextcolour.menuOptions [6]			, "Yellow");
	strcpy(mainmenu.menuTextcolour.menuOptions [7]			, "Cyan");
	strcpy(mainmenu.menuTextcolour.menuOptions [8]			, "Magenta");
	strcpy(mainmenu.menuTextcolour.menuOptions [9]			, "Grey");
	strcpy(mainmenu.menuTextcolour.menuOptions [10]			, "Blue - 2");

	// Start mainscreen
	Menu_Main();
}

void MenuRedrawScreen () {
	LCD_Clear(ColourConverterDec(mainmenu.backgroundcolour));
	LCD_SetBackColor(ColourConverterDec(mainmenu.backgroundcolour));
	LCD_SetTextColor(ColourConverterDec(mainmenu.foregroundcolour));

	// Title
	LCD_StringLine(210, 30, mainmenu.menuCurrent->menuTitle);

	// Line
	LCD_DrawFullRect(198,10,5,300);

	// Options
	uint8_t optionCounter 	= 0;
	uint8_t optionOffset 	= OPTIONSPERMENU * (mainmenu.menuCurrent->currentOption / OPTIONSPERMENU);
	for (optionCounter = optionOffset; optionCounter < (optionOffset + OPTIONSPERMENU); optionCounter ++) {
		if (optionCounter < MAXOPTIONS && optionCounter < mainmenu.menuCurrent->nrOfOptions) {
			if (mainmenu.menuCurrent->menuOptions[optionCounter][0] != '\0') {
				LCD_StringLine(160 - ((optionCounter - optionOffset) * 30), 30, mainmenu.menuCurrent->menuOptions[optionCounter]);
			}
		}
	}

	// Draw currently selected
	MenuDrawCurrentlySelected();
}

void MenuDrawCurrentlySelected () {
	if (mainmenu.menuCurrent->showCursor) {
		LCD_SetTextColor(255,0,0);
		LCD_DrawFullRect(10, 3, 176, 19);
		LCD_SetTextColor(0,255,0);
		LCD_PutChar(160 - ((mainmenu.menuCurrent->currentOption % 6) * 30), 5, CURRENTLYSELECTEDCHAR);
	}
}

void MenuClearStringMemory (Menu_Typedef* menu) {
	uint8_t count 		= 0;
	uint8_t charcount	= 0;
	for (count = 0; count < MAXOPTIONS; count ++) {
		for (charcount = 0; charcount < MAXSTRINGLENGTH; charcount ++) {
			menu->menuOptions[count][charcount] = '\0';
		}
	}
}

void MenuUpdateSelectedItem() {
	uint8_t oldValue 		= mainmenu.menuCurrent->currentOption;
	uint8_t nrOfOptions		= mainmenu.menuCurrent->nrOfOptions;
	int8_t newValue 		= oldValue;
	int8_t rotaryValue		= MenuRotaryRead(1);

	if (rotaryValue == 0) {
		return;									// RETURN //
	}

	newValue += rotaryValue;
	if (newValue < 0) {
		newValue += nrOfOptions;
	}
	newValue %= nrOfOptions;

	mainmenu.menuCurrent->currentOption = newValue;

	if (newValue / OPTIONSPERMENU == oldValue / OPTIONSPERMENU) {
		MenuDrawCurrentlySelected();
	} else {
		MenuRedrawScreen();
	}

	return;
}

uint8_t MenuOKpressed(uint8_t reset) {
	uint8_t returnValue = 0;
	if (buttonz.buttonOK) {							// BUTTONZ //
		returnValue = 1;

		if (reset)
			buttonz.buttonOK = 0;
	}

	return returnValue;
}

uint8_t MenuBackpressed(uint8_t reset) {
	uint8_t returnValue = 0;
	if (buttonz.buttonBack) {						// BUTTONZ //
		returnValue = 1;

		if (reset)
			buttonz.buttonBack = 0;
	}

	return returnValue;
}

int8_t MenuRotaryRead(uint8_t reset) {
	int8_t returnValue = 0;
	returnValue = buttonz.rotaryValue;

	if (reset)
		buttonz.rotaryValue = 0;

	return returnValue;
}

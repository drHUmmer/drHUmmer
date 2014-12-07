#include "menu.h"

void MenuSetup() {
	LCD_Clear(ColourConverterDec(Black));
	// Set default values
	mainmenu.backgroundcolour 	= Black;
	mainmenu.foregroundcolour 	= Green;
	mainmenu.menuCurrent		= &mainmenu.menuMain;

	// Clear menu options
	MenuClearStringMemory(&mainmenu.menuMain);
	MenuClearStringMemory(&mainmenu.menuSettings);
	MenuClearStringMemory(&mainmenu.menuBackcolour);
	MenuClearStringMemory(&mainmenu.menuTextcolour);

	// Main screen //
	mainmenu.menuMain.currentOption							= 0;
	mainmenu.menuMain.nrOfOptions							= 0;
	mainmenu.menuMain.handler								= Menu_MainHandler;
	strcpy(mainmenu.menuMain.menuTitle						, TITLE_MAINSCREEN);
	

	// Settings Menu //
	mainmenu.menuSettings.currentOption						= 1;
	mainmenu.menuSettings.nrOfOptions						= 3;
	mainmenu.menuSettings.handler							= Menu_SettingsHandler;
	mainmenu.menuSettings.parent							= Menu_Main;
	strcpy(mainmenu.menuSettings.menuTitle					, TITLE_SETTINGSMENU);
	strcpy(mainmenu.menuSettings.menuOptions [0]			, BACKSTRING);
	strcpy(mainmenu.menuSettings.menuOptions [1]			, "Set FX");
	strcpy(mainmenu.menuSettings.menuOptions [2]			, "Set colours");

	// Colours //
	mainmenu.menuColours.currentOption						= 1;
	mainmenu.menuColours.nrOfOptions						= 4;
	mainmenu.menuColours.handler							= Menu_ColourHandler;
	mainmenu.menuColours.parent								= Menu_Settings;
	strcpy(mainmenu.menuColours.menuTitle					, TITLE_COLOURMENU);
	strcpy(mainmenu.menuColours.menuOptions	[0]				, BACKSTRING);
	strcpy(mainmenu.menuColours.menuOptions	[1]				, "Invert");
	strcpy(mainmenu.menuColours.menuOptions	[2]				, "Set back colour");
	strcpy(mainmenu.menuColours.menuOptions	[3]				, "Set text colour");

	// Background colour //
	mainmenu.menuBackcolour.currentOption					= 1;
	mainmenu.menuBackcolour.nrOfOptions						= 11;
	mainmenu.menuBackcolour.handler							= Menu_BackcolourHandler;
	mainmenu.menuBackcolour.parent							= Menu_Colours;
	strcpy(mainmenu.menuBackcolour.menuTitle				, TITLE_BACKCOLOURMENU);
	strcpy(mainmenu.menuBackcolour.menuOptions	[0]			, BACKSTRING);
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
	mainmenu.menuTextcolour.currentOption					= 1;
	mainmenu.menuTextcolour.nrOfOptions						= 11;
	mainmenu.menuTextcolour.handler							= Menu_TextcolourHandler;
	mainmenu.menuTextcolour.parent							= Menu_Colours;
	strcpy(mainmenu.menuTextcolour.menuTitle	  			, TITLE_TEXTCOLOURMENU);
	strcpy(mainmenu.menuTextcolour.menuOptions [0]			, BACKSTRING);
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

////////////////////
// Menu Functions //
////////////////////
void MenuClearStringMemory (Menu_Typedef* menu) {
	uint8_t count 		= 0;
	uint8_t charcount	= 0;

	for (count = 0; count < MAXOPTIONS; count ++) {
		for (charcount = 0; charcount < MAXSTRINGLENGTH; charcount ++) {
			menu->menuOptions[count][charcount] = '\0';
		}
	}
}

uint8_t MenuCompareTitle(char* toCompare) {
	// Return 1 if equals
	// Return 0 if not equal
	return !(!!(strcmp(mainmenu.menuCurrent->menuTitle, toCompare)));
}

uint8_t MenuCompareSelected(char* toCompare) {
	// Return 1 if equals
	// Return 0 if not equal
	uint8_t currentSelectedOption = mainmenu.menuCurrent->currentOption;
	return !(!!(strcmp(mainmenu.menuCurrent->menuOptions[currentSelectedOption], toCompare)));
}

void MenuDrawCurrentlySelected () {
	if (!MenuCompareTitle(TITLE_MAINSCREEN)) {
		LCD_DrawFullRect(10, 3, 176, 19);
		LCD_PutChar(160 - ((mainmenu.menuCurrent->currentOption % OPTIONSPERMENU) * 30), 5, CURRENTLYSELECTEDCHAR);
	}
}

void MenuDrawOptions() {
	LCD_SetTextColor(ColourConverterDec(Yellow));		// DEBUG //
	LCD_DrawFullRect(0,0,200,200);						// Redraw options //
	LCD_SetTextColor(ColourConverterDec(Black));		// DEBUG //

	if (mainmenu.menuCurrent->nrOfOptions) {
		uint8_t optionCounter 	= 0;
		uint8_t optionOffset 	= OPTIONSPERMENU * (mainmenu.menuCurrent->currentOption / OPTIONSPERMENU);

		for (optionCounter = optionOffset; optionCounter < (optionOffset + OPTIONSPERMENU); optionCounter ++) {
			if (optionCounter < MAXOPTIONS && optionCounter < mainmenu.menuCurrent->nrOfOptions) {
				if (mainmenu.menuCurrent->menuOptions[optionCounter][0] != '\0') {
					LCD_StringLine(160 - ((optionCounter - optionOffset) * 30), 30, mainmenu.menuCurrent->menuOptions[optionCounter]);
				}
			}
		}
	}
}

void MenuRedrawScreen () {
	LCD_Clear(ColourConverterDec(mainmenu.backgroundcolour));
	LCD_SetBackColor(ColourConverterDec(mainmenu.backgroundcolour));
	LCD_SetTextColor(ColourConverterDec(mainmenu.foregroundcolour));

	// Title
	LCD_StringLine(210, 30, mainmenu.menuCurrent->menuTitle);

	// Horizontal line, separating menu and title
	LCD_DrawFullRect(198, 10, 5, 300);

	// Draw options
	MenuDrawOptions();

	// Draw cursor
	MenuDrawCurrentlySelected();
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
	if (newValue < 0) {							// If negative
		newValue += nrOfOptions;				// Turn around
	}
	newValue %= nrOfOptions;					// If too high, turn around as well

	mainmenu.menuCurrent->currentOption = newValue;

	if (newValue / OPTIONSPERMENU != oldValue / OPTIONSPERMENU) {	// Only redraw everything when necessary
		MenuDrawOptions();						// Redraw the options
	}

	MenuDrawCurrentlySelected();				// Redraw cursor

	return;
}

////////////////////
// User Interface //
////////////////////
uint8_t MenuBackpressed(uint8_t reset) {
	uint8_t returnValue = 0;
	if (buttonz.buttonBack) {					// BUTTONZ //
		returnValue = 1;

		if (reset)
			buttonz.buttonBack = 0;
	}

	return returnValue;
}

uint8_t MenuOKpressed(uint8_t reset) {
	uint8_t returnValue = 0;
	if (buttonz.buttonOK) {						// BUTTONZ //
		returnValue = 1;

		if (reset)
			buttonz.buttonOK = 0;
	}

	return returnValue;
}

int8_t MenuRotaryRead(uint8_t reset) {
	int8_t returnValue = 0;
	returnValue = buttonz.rotaryValue;

	if (reset)
		buttonz.rotaryValue = 0;				// BUTTONZ //

	return returnValue;
}

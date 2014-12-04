#include "userMenu.h"

void UpdateSelectedItem() {
	// Update current option value (rotate round)
		mainmenu.menuCurrent->currentOption += buttonz.rotaryValue;
		if (mainmenu.menuCurrent->currentOption > mainmenu.menuCurrent->nrOfOptions)
			mainmenu.menuCurrent->currentOption = mainmenu.menuCurrent->nrOfOptions;
		mainmenu.menuCurrent->currentOption %= mainmenu.menuCurrent->nrOfOptions;

		buttonz.rotaryValue = 0;

		Menu_RedrawScreen();
	return;
}

void MenuUpdateHandler () {
	if (buttonz.rotaryValue) {
		UpdateSelectedItem();
		return;																// RETURN //
	}

	if (strcmp(mainmenu.menuCurrent->menuTitle, TITLE_MAINSCREEN) == 0)
		UpdateHandlerMainMenu();

	if (strcmp(mainmenu.menuCurrent->menuTitle, TITLE_SETTINGSMENU) == 0)
		UpdateHandlerSettingsMenu();
}

void UpdateHandlerMainMenu() {
	if (buttonz.buttonOK) {
		buttonz.buttonOK = 0;

		Menu_SettingList(0);
	}
}

void UpdateHandlerSettingsMenu() {
	if (buttonz.buttonBack) {
		buttonz.buttonBack = 0;

		Menu_Main();
	}
}

void MenuSetup() {
	mainmenu.backgroundcolour 	= Black;
	mainmenu.foregroundcolour 	= Green;

	ClearStringMemory(&mainmenu.menuMain);
	ClearStringMemory(&mainmenu.menuSettings);
	ClearStringMemory(&mainmenu.menuSettingsForeground);
	ClearStringMemory(&mainmenu.menuSettingsBackground);

	mainmenu.menuMain.currentOption							= 0;
	mainmenu.menuMain.nrOfOptions							= 0;
	strcpy(mainmenu.menuMain.menuTitle						, TITLE_MAINSCREEN);

	// Main settings //
	mainmenu.menuSettings.currentOption						= 0;
	mainmenu.menuMain.nrOfOptions							= 10;
	strcpy(mainmenu.menuSettings.menuTitle					, TITLE_SETTINGSMENU);
	strcpy(mainmenu.menuSettings.menuOptions [0]			, "Back");
	strcpy(mainmenu.menuSettings.menuOptions [1]			, "Set back colour");
	strcpy(mainmenu.menuSettings.menuOptions [2]			, "Set text colour");
	strcpy(mainmenu.menuSettings.menuOptions [3]			, "Set FX");
	strcpy(mainmenu.menuSettings.menuOptions [4]			, "Banana");

	// Background colour //
	mainmenu.menuSettingsBackground.currentOption			= 0;
	mainmenu.menuSettingsBackground.nrOfOptions				= 11;
	strcpy(mainmenu.menuSettingsBackground.menuTitle		, TITLE_BACKGROUNDMENU);
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[0]	, "Back");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[1]	, "White");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[2]	, "Black");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[3]	, "Red");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[4]	, "Green");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[5]	, "Blue");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[6]	, "Yellow");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[7]	, "Cyan");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[8]	, "Magenta");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[9]	, "Gray");
	strcpy(mainmenu.menuSettingsBackground.menuOptions	[10], "Blue - 2");

	// Foreground colour //
	mainmenu.menuSettingsForeground.currentOption			= 0;
	mainmenu.menuSettingsForeground.nrOfOptions				= 11;
	strcpy(mainmenu.menuSettingsForeground.menuTitle	  	, TITLE_FOREGROUNDMENU);
	strcpy(mainmenu.menuSettingsForeground.menuOptions [0]	, "Back");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [1]	, "White");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [2]	, "Black");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [3]	, "Red");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [4]	, "Green");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [5]	, "Blue");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [6]	, "Yellow");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [7]	, "Cyan");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [8]	, "Magenta");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [9]	, "Gray");
	strcpy(mainmenu.menuSettingsForeground.menuOptions [10]	, "Blue - 2");

	Menu_Main();
}

void Menu_RedrawScreen () {
	LCD_Clear(ColourConverterDec(mainmenu.backgroundcolour));
	LCD_SetBackColor(ColourConverterDec(mainmenu.backgroundcolour));
	LCD_SetTextColor(ColourConverterDec(mainmenu.foregroundcolour));

	// Title
	LCD_StringLine(210, 30, mainmenu.menuCurrent->menuTitle);

	// Line
	LCD_DrawFullRect(198,10,5,300);

	// Options
	uint8_t optionCounter 	= 0;
	uint8_t optionOffset 	= 6 * (mainmenu.menuCurrent->currentOption / 6);
	for (optionCounter = optionOffset; optionCounter < (optionOffset + 6); optionCounter ++) {
		if (optionCounter < MAXOPTIONS && optionCounter < mainmenu.menuCurrent->nrOfOptions) {
			if (mainmenu.menuCurrent->menuOptions[optionCounter][0] != '\0') {
				LCD_StringLine(160 - ((optionCounter - optionOffset) * 30), 30, mainmenu.menuCurrent->menuOptions[optionCounter]);
			}
		}
	}
}

void ClearStringMemory (Menu_Typedef* menu) {
	uint8_t count 		= 0;
	uint8_t charcount	= 0;
	for (count = 0; count < MAXOPTIONS; count ++) {
		for (charcount = 0; charcount < MAXSTRINGLENGTH; charcount ++) {
			menu->menuOptions[count][charcount] = '\0';
		}
	}
}

void Menu_Main() {
	mainmenu.menuCurrent = &mainmenu.menuMain;
	Menu_RedrawScreen();

	LCD_CreateVertProgressbar(5, 5, 150, 25, ColourConverterEnc(50,10,10), Yellow, 33);
}

void Menu_SettingList() {
	mainmenu.menuCurrent = &mainmenu.menuMain;

	Menu_RedrawScreen();
}


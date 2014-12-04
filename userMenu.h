#ifndef USERMENU_H
#define USERMENU_H

//#include <stdio.h>
#include <string.h>
#include "LCDitems.h"
#include "ILI9325.h"
#include "stm32f4xx.h"

#define MAXSTRINGLENGTH			16
#define MAXOPTIONS				12
#define CURRENTLYSELECTEDCHAR	'>'

#define TITLE_MAINSCREEN		"Main"
#define TITLE_SETTINGSMENU		"Settings"
#define TITLE_BACKGROUNDMENU	"Back colour"
#define TITLE_FOREGROUNDMENU	"Text colour"

///////////////////////////////
// Main menu settings struct //
///////////////////////////////
typedef struct {
	char			menuTitle[MAXSTRINGLENGTH];
	char			menuOptions[MAXOPTIONS][MAXSTRINGLENGTH];
	uint8_t			currentOption;
	uint8_t			nrOfOptions;

} Menu_Typedef;

typedef struct {
	uint16_t 		backgroundcolour;
	uint16_t 		foregroundcolour;
	Menu_Typedef*	menuCurrent;
	Menu_Typedef	menuMain;
	Menu_Typedef	menuSettings;
	Menu_Typedef	menuSettingsBackground;
	Menu_Typedef	menuSettingsForeground;

} MenuSettings_TypeDef;

/////////////////////////
// Function prototypes //
/////////////////////////
void MenuSetup();
void UpdateSelectedItem();
void Menu_RedrawScreen ();
void ClearStringMemory (Menu_Typedef* menu);
void Menu_Main();
void Menu_SettingList();

// Update Handlers
void UpdateSelectedItem();
void UpdateHandlerMainMenu();
void UpdateHandlerSettingsMenu();

/////////////////////////
// Structure prototype //
/////////////////////////
MenuSettings_TypeDef mainmenu;


//////////////////////////
// !!!! SIMULATION !!!! //
//////////////////////////
typedef struct {
	uint8_t buttonBack 		: 1;
	uint8_t buttonOK		: 1;
	int8_t  rotaryValue;
} ButtonSim_Typedef;

ButtonSim_Typedef buttonz;

#endif	// USERMENU_H

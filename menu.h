#ifndef MENU_H
#define MENU_H

//////////////
// Includes //
//////////////
#include <string.h>
#include "menuScreens.h"
#include "menuHandlers.h"
#include "LCDitems.h"
#include "ILI9325.h"
#include "stm32f4xx.h"

/////////////////
// Menu titles //
/////////////////
#define TITLE_MAINSCREEN		"Main"
#define TITLE_SETTINGSMENU		"Settings"
#define TITLE_BACKCOLOURMENU	"Back colour"
#define TITLE_TEXTCOLOURMENU	"Text colour"

/////////////////////
// Dispay settings //
/////////////////////
#define BACKSTRING				"Back"
#define MAXSTRINGLENGTH			16
#define MAXOPTIONS				(2 * OPTIONSPERMENU)
#define CURRENTLYSELECTEDCHAR	'>'
#define OPTIONSPERMENU			6



///////////////////////////////
// Main menu settings struct //
///////////////////////////////
typedef struct {
	char			menuTitle[MAXSTRINGLENGTH];				// Menutitle
	char			menuOptions[MAXOPTIONS][MAXSTRINGLENGTH];	// Names of options
	int8_t			currentOption;							// Currently selected option
	uint8_t			nrOfOptions;							// Total number of options
	uint8_t			showCursor					: 1;		// 1 = true, 0 = false
	void			(*handler)(void);						// Handler function pointer
	void			(*parent)(void);
} Menu_Typedef;

typedef struct {
	uint16_t 		backgroundcolour;
	uint16_t 		foregroundcolour;
	Menu_Typedef*	menuCurrent;
	Menu_Typedef	menuMain;
	Menu_Typedef	menuSettings;
	Menu_Typedef	menuBackcolour;
	Menu_Typedef	menuTextcolour;

} MenuSettings_TypeDef;

/////////////////////////
// Function prototypes //
/////////////////////////
void 	MenuClearStringMemory 		(Menu_Typedef* menu);
uint8_t MenuCompareTitle			(char* toCompare);
uint8_t MenuCompareSelected			(char* toCompare);
void 	MenuDrawCurrentlySelected 	(void);
void 	MenuRedrawScreen 			(void);
void 	MenuSetup					(void);
void 	MenuUpdateSelectedItem		(void);

uint8_t MenuBackpressed				(uint8_t reset);
uint8_t MenuOKpressed				(uint8_t reset);
int8_t  MenuRotaryRead				(uint8_t reset);

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

#endif	// MENU_H

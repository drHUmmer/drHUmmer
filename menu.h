#ifndef MENU_H
#define MENU_H

#include "stm32f4xx.h"

typedef struct {
	uint16_t		xPos;
	uint16_t		yPos;
	uint16_t		xSize;
	uint16_t		ySize;
	int8_t			value;
} Progressbar_Typedef;

//////////////
// Includes //
//////////////
#include <string.h>
#include "menuScreens.h"
#include "menuHandlers.h"
#include "ILI9325.h"
#include "LCDitems.h"

/////////////////
// Menu titles //
/////////////////
#define TITLE_INFOSCREEN		"Info"
#define TITLE_MAINSMENU			"Settings"
#define TITLE_COLOURMENU		"Colours"
#define TITLE_BACKCOLOURMENU	"Back colour"
#define TITLE_TEXTCOLOURMENU	"Text colour"
#define TITLE_SETFX				"Set fx"
#define TITLE_SETFX1			"Set fx 1"
#define TITLE_SETFX2			"Set fx 2"
#define TITLE_LEVELBAR			"Set level bar"
#define TITLE_TONEPOSBAR		"Set tone + bar"
#define TITLE_TONENEGBAR		"Set tone - bar"
#define TITLE_SETBPM			"Set BPM"
#define TITLE_SETLPFFREQ		"Set lpf freq"
#define TITLE_SETHPFFREQ		"Set hpf freq"
#define TITLE_SETDSFREQ			"Set ds freq"
#define TITLE_SETBCBITS			"Set bc bits"

/////////////////////
// Dispay settings //
/////////////////////
#define BACKSTRING				"../"
#define MAXSTRINGLENGTH			17
#define MAXOPTIONS				(2 * OPTIONSPERMENU)
#define CURRENTLYSELECTEDCHAR	'>'
#define OPTIONSPERMENU			6

/////////////
// Structs //
/////////////
typedef struct {
	char			menuTitle[MAXSTRINGLENGTH];				// Menutitle
	char			menuOptions[MAXOPTIONS][MAXSTRINGLENGTH];	// Names of options
	uint8_t			showCursor;								// Show cursor
	int8_t			selectedOption;							// Currently selected option
	uint8_t			nrOfOptions;							// Total number of options
	void			(*handler)(void);						// Handler function pointer
	void			(*parent)(void);						// Parent screen
} Menu_Typedef;

typedef struct {
	Menu_Typedef*	current;
	Menu_Typedef	info;
	Menu_Typedef	main;

	// Colours
	Menu_Typedef	colours;
	Menu_Typedef	backcolour;
	Menu_Typedef	textcolour;
	Menu_Typedef	levelBarcolour;
	Menu_Typedef	tonePosBarcolour;
	Menu_Typedef	toneNegBarcolour;

	// FX
	Menu_Typedef	fx;
	Menu_Typedef	fx1;
	Menu_Typedef	fx2;

	// Settings
	Menu_Typedef	bpm;
	Menu_Typedef	fxSettings;
	Menu_Typedef	lpFreq;
	Menu_Typedef	hpFreq;
	Menu_Typedef	dsFreq;
	Menu_Typedef	bcBits;

} Menus_Typedef;

typedef struct {
	uint16_t		background;
	uint16_t		text;
	uint16_t		levelBar;
	uint16_t		tonePosBar;
	uint16_t		toneNegBar;
} Colours_Typedef;

typedef struct {
	Progressbar_Typedef		analogDrum1Level;
	Progressbar_Typedef		analogDrum1Tone;
	Progressbar_Typedef		analogDrum2Level;
	Progressbar_Typedef		analogDrum2Tone;
	Progressbar_Typedef		digitalDrum1Level;
	Progressbar_Typedef		digitalDrum1Tone;
	Progressbar_Typedef		digitalDrum2Level;
	Progressbar_Typedef		digitalDrum2Tone;
	Progressbar_Typedef		digitalDrum3Level;
	Progressbar_Typedef		digitalDrum3Tone;
	Progressbar_Typedef		digitalDrum4Level;
	Progressbar_Typedef		digitalDrum4Tone;
} Progressbars_Typedef;

typedef struct {
	Colours_Typedef			colours;
	Menus_Typedef			menus;
	Progressbars_Typedef	bars;
} MenuSettings_TypeDef;

/////////////////////////
// Function prototypes //
/////////////////////////
void 	MenuClearStringMemory 		(Menu_Typedef* menu);
void 	MenuClearTitle 				(Menu_Typedef* menu);
uint8_t MenuCompareTitle			(char* toCompare);
uint8_t MenuCompareSelected			(char* toCompare);
void 	MenuDrawCurrentlySelected 	(void);
void 	MenuDrawOptions				(uint8_t clearBack);
void 	MenuDrawTitle				(uint8_t clearBack);
void 	MenuRedrawScreen 			(void);
void 	MenuSetup					(void);
void 	MenuUpdateSelectedItem		(void);

// User interface
uint8_t MenuBackpressed				(uint8_t reset);
uint8_t MenuOKpressed				(uint8_t reset);
int8_t  MenuRotaryRead				(uint8_t reset);

/////////////////////////
// Structure prototype //
/////////////////////////
MenuSettings_TypeDef gui;

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

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
#define TITLE_INFOSCREEN			"Info"
#define TITLE_MAINSMENU				"Settings"

// MIDI
#define TITLE_MIDI					"MIDI"
#define TITLE_MIDI_CHANNEL			"MIDI - CH"
#define TITLE_MIDI_MASTER_SLAVE		"MIDI - M/S"
#define TITLE_MIDI_SYNC				"MIDI - Sync"

// SEQ
#define TITLE_SEQ					"SEQ"
#define TITLE_SEQ_BPM				"SEQ - BPM"
#define TITLE_SEQ_PATT_LIVE			"SEQ - Patt/live"

// FILE

// UI
#define TITLE_UI_COLOURS			"UI - Colours"
#define TITLE_UI_COLOURS_BACK		"Colours - back"
#define TITLE_UI_COLOURS_TEXT		"Colours - text"
#define TITLE_UI_COLOURS_LEVEL		"Colours - level"
#define TITLE_UI_COLOURS_TONEPOS	"Colours - tone +"
#define TITLE_UI_COLOURS_TONENEG	"Colours - tone -"
#define TITLE_UI_INFO				"UI - Info"
#define TITLE_UI_INFO_1				"Info - left"
#define TITLE_UI_INFO_2				"Info - right"


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

	// MIDI
	Menu_Typedef	midi;
	Menu_Typedef	midi_channel;
	Menu_Typedef	midi_master_slave;
	Menu_Typedef	midi_sync;

	// SEQ
	Menu_Typedef	seq;
	Menu_Typedef	seq_bpm;
	Menu_Typedef	seq_patt_live_mode;

	// FILE
	Menu_Typedef	file;
	Menu_Typedef	file_sample_select;
	Menu_Typedef	file_save_pattern;
	Menu_Typedef	file_load_pattern;

	// Filter
	Menu_Typedef	filter_bookmark;
	Menu_Typedef	filter_bookmark_1;
	Menu_Typedef	filter_bookmark_2;

	// UI
	Menu_Typedef	ui;
	Menu_Typedef	ui_colours;
	Menu_Typedef	ui_info;
	
	// UI submenus
	Menu_Typedef	ui_backcolour;
	Menu_Typedef	ui_textcolour;
	Menu_Typedef	ui_levelBarcolour;
	Menu_Typedef	ui_tonePosBarcolour;
	Menu_Typedef	ui_toneNegBarcolour;
	Menu_Typedef	ui_info_1;
	Menu_Typedef	ui_info_2;
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
void 	MenuDrawEffect1				(uint8_t redraw);
void 	MenuDrawEffect2				(uint8_t redraw);
void 	MenuDrawInfo1				(uint8_t redraw);
void 	MenuDrawInfo2				(uint8_t redraw);

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

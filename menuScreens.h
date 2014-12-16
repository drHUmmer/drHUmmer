#ifndef MENUSCREENS_H
#define MENUSCREENS_H

#include "menuHandlers.h"
#include "menu.h"
#include "LCDitems.h"
#include "filter.h"
#include "sequencer.h"

#define BARHEIGHT	180

// Function prototypes
void Menu_Info();
void Menu_Main();

// MIDI
void Menu_MIDI					(void);
void Menu_MIDI_Channel			(void);
void Menu_MIDI_Master_Slave		(void);
void Menu_MIDI_Sync				(void);

// SEQ
void Menu_SEQ					(void);
void Menu_SEQ_BPM				(void);
void Menu_SEQ_Patt_Live_Mode	(void);	// IMPLEMENT
void Menu_SEQ_Sync				(void);

// FILE
void Menu_File					(void);
void Menu_File_Sample_Select	(void);
void Menu_File_Save_Pattern		(void);
void Menu_File_Load_Pattern		(void);

// Filter bookmarks
void Menu_Filter_Bookmark		(void);
void Menu_Filter_Bookmark_1		(void);
void Menu_Filter_Bookmark_2		(void);

// UI
void Menu_UI					(void);
void Menu_UI_colours			(void);
void Menu_UI_info				(void);
void Menu_UI_backcolour			(void);
void Menu_UI_textcolour			(void);
void Menu_UI_levelbarcolour		(void);
void Menu_UI_toneposbarcolour	(void);
void Menu_UI_tonenegbarcolour	(void);
void Menu_UI_info_1				(void);
void Menu_UI_info_2				(void);

#endif // MENUSCREENS_H

#ifndef MENUHANDLERS_H
#define MENUHANDLERS_H

#include "menuScreens.h"
#include "menu.h"
#include "LCDitems.h"
#include "timers.h"
#include "DAC.h"

// Main
void Menu_Update_handler();						// X
void Menu_Info_handler(); 						// X
void Menu_Main_handler(); 						// X

// MIDI
void Menu_MIDI_handler					(void); // 
void Menu_MIDI_Channel_handler			(void); // 
void Menu_MIDI_Master_Slave_handler		(void); // 
void Menu_MIDI_Sync_handler				(void); // 

// SEQ
void Menu_SEQ_handler					(void); // 
void Menu_SEQ_BPM_handler				(void); // X
void Menu_SEQ_Patt_Live_Mode_handler	(void); // 

// FILE
void Menu_File_handler					(void); //
void Menu_File_Sample_Select_handler	(void); // 
void Menu_File_Save_Pattern_handler		(void); // 
void Menu_File_Load_Pattern_handler		(void); // 

// Filter bookmarks
void Menu_Filter_Bookmark_handler		(void); // 
void Menu_Filter_Bookmark_1_handler		(void); // 
void Menu_Filter_Bookmark_2_handler		(void); // 

// UI
void Menu_UI_handler					(void); //
void Menu_UI_colours_handler			(void); // X
void Menu_UI_backcolour_handler			(void); // X
void Menu_UI_textcolour_handler			(void); // X
void Menu_UI_levelbarcolour_handler		(void); // X
void Menu_UI_toneposbarcolour_handler	(void); // X
void Menu_UI_tonenegbarcolour_handler	(void); // X
void Menu_UI_info_handler				(void); // 
void Menu_UI_info_1_handler				(void); // 
void Menu_UI_info_2_handler				(void); // 

#endif // MENUHANDLERS_H

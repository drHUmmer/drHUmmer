#ifndef MENUHANDLERS_H
#define MENUHANDLERS_H

#include "menuScreens.h"
#include "menu.h"

// Main
void Menu_UpdateHandler();
void Menu_MainHandler();
void Menu_SettingsHandler();

// Colours
void Menu_ColourHandler();
void Menu_BackcolourHandler();
void Menu_TextcolourHandler();
void Menu_LevelBarHandler();
void Menu_TonePosBarHandler();
void Menu_ToneNegBarHandler();

// FX
void Menu_SetFxHandler();
void Menu_SetFx1Handler();
void Menu_SetFx2Handler();

#endif // MENUHANDLERS_H

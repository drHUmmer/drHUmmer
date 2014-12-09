#ifndef MENUSCREENS_H
#define MENUSCREENS_H

#include "menuHandlers.h"
#include "menu.h"
#include "filter.h"
#include "sequencer.h"

#define BARHEIGHT	180

// Function prototypes
void Menu_Main();
void Menu_Settings();

// Colours
void Menu_Colours();
void Menu_SetBackcolour();
void Menu_SetTextcolour();
void Menu_SetLevelBarcolour();
void Menu_SetTonePosBarcolour();
void Menu_SetToneNegBarcolour();

// FX
void Menu_SetFx();
void Menu_SetFx1();
void Menu_SetFx2();

#endif // MENUSCREENS_H

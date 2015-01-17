#ifndef UIHANDLER
#define UIHANDLER

#include "UI.h"
#include "filter.h"
#include "sequencer.h"

// Menu
uint8_t UIhandler_Menu_Ok 		(uint8_t reset);
uint8_t UIhandler_Menu_Back 	(uint8_t reset);
int8_t 	UIhandler_Menu_Rotary 	(uint8_t reset);

// Fx
void UIhandler_FX_IO			(void);
void UIhandler_FX_ROT			(void);

// Drums
void UIhandler_Drum_Levels		(void);

#endif // UIHANDLER

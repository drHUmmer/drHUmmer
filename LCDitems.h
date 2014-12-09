#ifndef LCDITEMS_H
#define LCDITEMS_H

#include "ILI9325.h"
#include "menu.h"

///////////////////////
// Colour converters //
///////////////////////
#define ColourConverterDec(x) 		(x & Red) >> 8, (x & Green) >> 3 , (x & Blue) << 3
#define ColourConverterEnc(r, g, b) ((r << 8) | (g << 3) | (b >> 3))

/////////////////////////
// Function prototypes //
/////////////////////////
void LCD_Levelbar 	(Progressbar_Typedef* bar, int8_t value);
void LCD_Tonebar	(Progressbar_Typedef* bar, int8_t value);

#endif // LCDITEMS_H

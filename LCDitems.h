#ifndef LCDITEMS_H
#define LCDITEMS_H

#include "ILI9325.h"

#define ColourConverterDec(x) 		(x & Red) >> 8, (x & Green) >> 3 , (x & Blue) << 3
#define ColourConverterEnc(r, g, b) ((r << 8) | (g << 3) | (b >> 3))

void LCD_CreateVertProgressbar(u16 x, u16 y, u16 xSize, u16 ySize, u16 backcolour, u16 progresscolour, u8 value);
void LCD_UpdateVertProgressbar (u16 x, u16 y, u16 xSize, u16 ySize, u16 progresscolour, u16 backcolour, u8 oldValue, u8 newValue);

#endif // LCDITEMS_H

#ifndef LCDITEMS_H
#define LCDITEMS_H

#include "ILI9325.h"

#define ColourConverterDec(x) 		(x & Red) >> 8, (x & Green) >> 3 , (x & Blue) << 3
#define ColourConverterEnc(x, y, z) ((x << 8) | (y << 3) | (z >> 3))

void LCD_CreateVertProgressbar(u16 x, u16 y, u16 xSize, u16 ySize, u16 backcolour, u16 progresscolour, u8 value);

#endif // LCDITEMS_H

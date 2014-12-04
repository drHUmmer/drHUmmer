#include "LCDitems.h"

void LCD_CreateVertProgressbar(u16 x, u16 y, u16 xSize, u16 ySize, u16 backcolour, u16 progresscolour, u8 value) {
	if (value > 100)
		value = 100;

	value = 100 - value;

	u16 progress = (u16)((double)xSize / 100.0 * (double) value);

	// Draw backcolor
	LCD_SetTextColor(ColourConverterDec(backcolour));
	LCD_DrawFullRect(x, y, xSize - progress, ySize);

	// Draw progress
	LCD_SetTextColor(ColourConverterDec(progresscolour));
	LCD_DrawFullRect(x + xSize - progress, y, progress, ySize);
}

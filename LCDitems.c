#include "LCDitems.h"

//void LCD_CreateVertProgressbar(u16 x, u16 y, u16 xSize, u16 ySize, u16 progresscolour, u16 backcolour, u8 value) {
//	if (value > 100)
//		value = 100;
//
//	value = 100 - value;
//
//	u16 progress = (u16)((double)xSize / 100.0 * (double) value);
//
//	// Draw backcolor
//	LCD_SetTextColor(ColourConverterDec(backcolour));
//	LCD_DrawFullRect(x, y, xSize - progress, ySize);
//
//	// Draw progress
//	LCD_SetTextColor(ColourConverterDec(progresscolour));
//	LCD_DrawFullRect(x + xSize - progress, y, progress, ySize);
//}

void LCD_Levelbar (Progressbar_Typedef* bar, int8_t value) {
	if (value == -1) { // Redraw
		uint16_t progress = (uint16_t)((double) bar->xSize / 100.0 * (double) bar->value);
		LCD_SetTextColor(ColourConverterDec(gui.colours.levelBar));
		LCD_DrawFullRect(bar->xPos + bar->xSize - progress, bar->yPos, progress, bar->ySize);
	}

	// Else draw changes
	if (value < 0) {		// If value is negative
		value *= -1;		// Make it positive
		if (value > 100)	// If greater than 100
			value = 100;	// Make it 100
	}

}

void LCD_Tonebar (Progressbar_Typedef* bar, int8_t value){
	if (value == -1) { // Redraw

	}

	// Else draw changes
	if (value < 0) {		// If value is negative
		value *= -1;		// Make it positive
		if (value > 100)	// If greater than 100
			value = 100;	// Make it 100
	}
}

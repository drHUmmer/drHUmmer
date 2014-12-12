#include "LCDitems.h"

static void LCD_TonebarPosChange(Progressbar_Typedef* bar, int8_t newValue) {
	int8_t  	barValue 	= bar->value;
	uint8_t 	deltaValue 	= 0;
	uint16_t 	deltaHeight = 0;
	uint16_t 	startHeight = 0;
	uint16_t	drawColour	= 0x00;

	if (newValue < 0 && barValue <= 0)		// Nothing to do. Invalid range
		return;								// RETURN //

	if (newValue < 0)
		newValue = 0;
	if (barValue < 0)
		barValue = 0;
	if (newValue > 100)
		newValue = 100;
	if (barValue > 100)
		barValue = 100;

	if (newValue > barValue) {
		deltaValue 	= newValue - barValue;
		startHeight = (bar->xSize / 2) + (uint16_t)(((double)bar->xSize / 2.0) / (100.0 / (double)barValue));
		drawColour	= gui.colours.tonePosBar;
	}
	else { // newValue < barValue
		deltaValue 	= barValue - newValue;
		startHeight = (bar->xSize / 2) + (uint16_t)(((double)bar->xSize / 2.0) / (100.0 / (double)newValue));
		drawColour	= gui.colours.background;
	}

	// Calculate bar height
	deltaHeight = bar->xSize / (100 / deltaValue) / 2 + 1;

	// Overdraw protection
	if (startHeight + deltaHeight > bar->xSize)
		startHeight = bar->xSize - deltaHeight;

	// Draw bar
	LCD_SetTextColor(ColourConverterDec(drawColour));
	LCD_DrawFullRect(startHeight, bar->yPos, deltaHeight, bar->ySize);
	LCD_SetTextColor(ColourConverterDec(gui.colours.text));
}

static void LCD_TonebarNegChange(Progressbar_Typedef* bar, int8_t newValue) {
	int8_t  	barValue 	= bar->value;
	uint8_t 	deltaValue 	= 0;
	int16_t 	deltaHeight = 0;
	int16_t 	startHeight = 0;
	uint16_t	drawColour	= 0x00;

	if (newValue > 0 && barValue >= 0)		// Nothing to do. Invalid range
		return;								// RETURN //

	if (barValue > 0)
		barValue = 0;
	if (newValue > 0)
		newValue = 0;
	if (newValue < -100)
		newValue = -100;
	if (barValue < -100)
		barValue = -100;

	if (newValue < barValue) {
		newValue *= -1;
		barValue *= -1;
		deltaValue 	= newValue - barValue;
		startHeight = (bar->xSize / 2) - (uint16_t)(((double)bar->xSize / 2.0) / (100.0 / (double)newValue));
		drawColour	= Cyan;
	}
	else { // newValue < barValue
		newValue *= -1;
		barValue *= -1;
		deltaValue 	= barValue - newValue;
		startHeight = (bar->xSize / 2) - (uint16_t)(((double)bar->xSize / 2.0) / (100.0 / (double)barValue));
		drawColour	= gui.colours.background;
	}

	// Calculate bar height
	deltaHeight = bar->xSize / (100 / deltaValue) / 2 + 1;

	// Draw bar
	LCD_SetTextColor(ColourConverterDec(drawColour));
	LCD_DrawFullRect(startHeight, bar->yPos, deltaHeight, bar->ySize);
	LCD_SetTextColor(ColourConverterDec(gui.colours.text));
}

static void LCD_LevelBarChange (Progressbar_Typedef* bar, int8_t newValue) {
	int8_t  	barValue 	= bar->value;
	uint8_t 	deltaValue 	= 0;
	uint16_t 	deltaHeight = 0;
	uint16_t 	startHeight = 0;
	uint16_t	drawColour	= 0x00;

	if (newValue < 0 && barValue <= 0)		// Nothing to do. Invalid range
		return;								// RETURN //

	if (newValue < 0)
		newValue = 0;
	if (barValue < 0)
		barValue = 0;
	if (newValue > 100)
		newValue = 100;
	if (barValue > 100)
		barValue = 100;

	if (newValue > barValue) {
		deltaValue 	= newValue - barValue;
		startHeight = (uint16_t)(((double)bar->xSize) / (100.0 / (double)barValue));
		drawColour	= gui.colours.levelBar;
	}
	else { // newValue < barValue
		deltaValue 	= barValue - newValue;
		startHeight = (uint16_t)(((double)bar->xSize) / (100.0 / (double)newValue));
		drawColour	= gui.colours.background;
	}

	// Calculate bar height
	deltaHeight = bar->xSize / (100 / deltaValue) + 1;

	// Overdraw protection
	if (startHeight + deltaHeight > bar->xSize)
		deltaHeight = bar->xSize - startHeight;

	// Draw bar
	LCD_SetTextColor(ColourConverterDec(drawColour));
	LCD_DrawFullRect(startHeight, bar->yPos, deltaHeight, bar->ySize);
	LCD_SetTextColor(ColourConverterDec(gui.colours.text));
}

void LCD_Levelbar (Progressbar_Typedef* bar, int8_t value) {
	if (value == BAR_REDRAW) { // Redraw
		uint16_t progress = ((uint16_t)((double) bar->xSize / 100.0 * (double) bar->value));
		LCD_SetTextColor(ColourConverterDec(gui.colours.levelBar));
		LCD_DrawFullRect(bar->xPos, bar->yPos, progress, bar->ySize);
		return;															// RETURN //
	}

	// Same value?? Be lazy, so don't do anything :)
	if (value == bar->value)
		return;															// RETURN //

	// Else draw changes
	LCD_LevelBarChange(bar, value);

	// Update old value
	bar->value = value;
}

void LCD_Tonebar (Progressbar_Typedef* bar, int8_t newValue){
	int8_t barValue = bar->value;

	////////////
	// Redraw //
	////////////
	if (newValue == BAR_REDRAW) { // Redraw
		//////////////////
		// Negative bar //
		//////////////////
		if (barValue < 0) {
			// Set correct colour
			LCD_SetTextColor(ColourConverterDec(gui.colours.toneNegBar));

			// Make value positive
			barValue *= -1;

			// Calculate progress bar
			uint16_t progress = (uint16_t)((double) bar->xSize / 100.0 * (double) barValue);

			// Draw progress bar
			LCD_DrawFullRect(bar->xPos + (bar->xSize / 2) - (progress / 2), bar->yPos, progress / 2, bar->ySize);
		}
		//////////////////
		// Positive bar //
		//////////////////
		else if (barValue > 0) {
			// Set correct colour
			LCD_SetTextColor(ColourConverterDec(gui.colours.tonePosBar));

			// Calculate progress bar
			uint16_t progress = (uint16_t)((double) bar->xSize / 100.0 * (double) barValue);

			// Draw progress bar
			LCD_DrawFullRect(bar->xPos + (bar->xSize / 2), bar->yPos, progress / 2, bar->ySize);
		}

		return;						// RETURN //
	}

	////////////////
	// Same value //
	////////////////
	if (newValue == barValue)
		return;						// RETURN //

	//////////////////
	// Draw changes //
	//////////////////
	LCD_TonebarNegChange(bar, newValue);
	LCD_TonebarPosChange(bar, newValue);

	// Update value
	bar->value = newValue;
}

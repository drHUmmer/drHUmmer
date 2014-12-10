#include "menuHandlers.h"

static void Menu_GotoParent() {
	if (!MenuCompareTitle(TITLE_INFOSCREEN)) {
		gui.menus.current->parent();
	}
}

void Menu_UpdateHandler() {
	if (MenuOKpressed(0)) {
		if (MenuCompareSelected(BACKSTRING)) {
			Menu_GotoParent();
			MenuOKpressed(1);		// Reset OK button
			GPIO_SetBits(GPIOD, GPIO_Pin_14);					// GPIO //
			return;												// RETURN //
		}
	}

	if (MenuBackpressed(1)) {
		Menu_GotoParent();
		GPIO_SetBits(GPIOD, GPIO_Pin_15);						// GPIO //
		return;													// RETURN //
	}

	// Run current menu handler
	gui.menus.current->handler();

	// Always reset the buttons, to prevent weird things to happen
	MenuOKpressed(1);
	MenuBackpressed(1);
}

void Menu_InfoHandler() {
	 if (MenuOKpressed(1)) {
	 	Menu_Main();
	 	return;
	 }

	 uint8_t oldValue 		= sequencer.instrID;
	 int8_t newValue 		= oldValue;
	 int8_t rotaryValue		= MenuRotaryRead(1);

	 if (rotaryValue != 0) {
		 newValue += rotaryValue;
		 if (newValue < 0) {
			 newValue += 6;
		 }
		 newValue %= 6;

	 sequencer.instrID = newValue;
	 if (newValue == 0)
		 LCD_StringLine(212, 270, "0");
	 else
		 LCD_StringInt (212, 200, newValue, 0);

	 }
//	 if (gui.bars.digitalDrum1Level.value != sequencer.instr0.level) {
//		 gui.bars.digitalDrum1Level.value = sequencer.instr0.level;
//		 LCD_Levelbar(&gui.bars.digitalDrum1Level, gui.bars.digitalDrum1Level.value);
//	 }
}

void Menu_MainHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Set colours"))
			Menu_Colours();

		if (MenuCompareSelected("Set fx"))
			Menu_SetFx();

		if (MenuCompareSelected("Set BPM"))
			Menu_SetBPM();

		if (MenuCompareSelected("Set hpf freq"))
			Menu_SethpfFreq();

		if (MenuCompareSelected("Set lpf freq"))
			Menu_SetlpfFreq();

		if (MenuCompareSelected("Set ds freq"))
			Menu_SetDSFreq();

		if (MenuCompareSelected("Set bc bits"))
			Menu_SetBCbits();

	}
}

void Menu_ColourHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("Invert")) {
			uint16_t temp 				= gui.colours.background;
			gui.colours.background 		= gui.colours.text;
			gui.colours.text 			= temp;
			MenuRedrawScreen();
		}

		if (MenuCompareSelected("Back colour"))
			Menu_SetBackcolour();

		if (MenuCompareSelected("Text colour"))
			Menu_SetTextcolour();

		if (MenuCompareSelected("Level colour"))
			Menu_SetLevelBarcolour();

		if (MenuCompareSelected("Tone + colour"))
			Menu_SetTonePosBarcolour();

		if (MenuCompareSelected("Tone - colour"))
			Menu_SetToneNegBarcolour();
	}
}

void Menu_BackcolourHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.background = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.background = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.background = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.background = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.background = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.background = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.background = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.background = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.background = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.background = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_TextcolourHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.text = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.text = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.text = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.text = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.text = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.text = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.text = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.text = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.text = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.text = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_LevelBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.levelBar = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.levelBar = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.levelBar = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.levelBar = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.levelBar = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.levelBar = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.levelBar = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.levelBar = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.levelBar = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.levelBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_TonePosBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.tonePosBar = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.tonePosBar = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.tonePosBar = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.tonePosBar = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.tonePosBar = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.tonePosBar = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.tonePosBar = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.tonePosBar = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.tonePosBar = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.tonePosBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_ToneNegBarHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if(MenuCompareSelected("White")) {
			gui.colours.toneNegBar = White;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Black")) {
			gui.colours.toneNegBar = Black;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Red")) {
			gui.colours.toneNegBar = Red;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Green")) {
			gui.colours.toneNegBar = Green;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue")) {
			gui.colours.toneNegBar = Blue;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Yellow")) {
			gui.colours.toneNegBar = Yellow;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Cyan")) {
			gui.colours.toneNegBar = Cyan;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Magenta")) {
			gui.colours.toneNegBar = Magenta;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Grey")) {
			gui.colours.toneNegBar = Grey;
			MenuRedrawScreen();
		}
		if(MenuCompareSelected("Blue - 2")) {
			gui.colours.toneNegBar = Blue2;
			MenuRedrawScreen();
		}
	}
}

void Menu_SetFxHandler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		uint8_t currentSelectedOption = gui.menus.current->selectedOption;

		if (strstr(gui.menus.current->menuOptions[currentSelectedOption], "Fx 1") != NULL) {
			Menu_SetFx1();
		}
		if (strstr(gui.menus.current->menuOptions[currentSelectedOption], "Fx 2") != NULL) {
			Menu_SetFx2();
		}
	}
}

void Menu_SetFx1Handler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("None"))
			FXsettings.fx1 = NONE;

		if (MenuCompareSelected("Low-pass"))
			FXsettings.fx1 = LPF;

		if (MenuCompareSelected("High-pass"))
			FXsettings.fx1 = HPF;

		if (MenuCompareSelected("Bitcrusher"))
			FXsettings.fx1 = BC;

		if (MenuCompareSelected("Down-sampler"))
			FXsettings.fx1 = DS;

		MenuClearTitle(gui.menus.current);

		switch(FXsettings.fx1) {
		case LPF: 	strcpy(gui.menus.current->menuTitle,	"Set fx 1 - LPF "); 	break;
		case HPF: 	strcpy(gui.menus.current->menuTitle,	"Set fx 1 - HPF "); 	break;
		case BC: 	strcpy(gui.menus.current->menuTitle,	"Set fx 1 - BC  "); 	break;
		case DS: 	strcpy(gui.menus.current->menuTitle, 	"Set fx 1 - DS  "); 	break;
		default: 	strcpy(gui.menus.current->menuTitle,	"Set fx 1 - NONE"); 	break;
		}

		MenuDrawTitle(1);
	}
}

void Menu_SetFx2Handler() {
	MenuUpdateSelectedItem();

	if (MenuOKpressed(1)) {
		if (MenuCompareSelected("None"))
			FXsettings.fx2 = NONE;

		if (MenuCompareSelected("Low-pass"))
			FXsettings.fx2 = LPF;

		if (MenuCompareSelected("High-pass"))
			FXsettings.fx2 = HPF;

		if (MenuCompareSelected("Bitcrusher"))
			FXsettings.fx2 = BC;

		if (MenuCompareSelected("Down-sampler"))
			FXsettings.fx2 = DS;

		MenuClearTitle(gui.menus.current);

		switch(FXsettings.fx2) {
		case LPF: 	strcpy(gui.menus.current->menuTitle, 	"Set fx 2 - LPF "); 	break;
		case HPF: 	strcpy(gui.menus.current->menuTitle,	"Set fx 2 - HPF "); 	break;
		case BC: 	strcpy(gui.menus.current->menuTitle,	"Set fx 2 - BC  "); 	break;
		case DS: 	strcpy(gui.menus.current->menuTitle,	"Set fx 2 - DS  "); 	break;
		default: 	strcpy(gui.menus.current->menuTitle,	"Set fx 2 - NONE"); 	break;
		}

		MenuDrawTitle(1);
	}
}

void Menu_SetBPMHandler() {
	if (MenuOKpressed(1))
		Menu_GotoParent();

	int8_t rotary 	= MenuRotaryRead(1);
	uint16_t BPM	= sequencer.BPM;

	if (rotary) {
		BPM += (rotary * 10);
		if (BPM < 50)
			BPM = 50;

		if (BPM > 400)
			BPM = 400;

		sequencer.BPM = BPM;
		BPMUpdate(BPM);

		LCD_StringInt(120, 50, sequencer.BPM, 1);
	}
}

void Menu_SetLPFfreqHandler() {
	if (MenuOKpressed(1))
		Menu_GotoParent();

	int8_t rotary 		= MenuRotaryRead(1);
	uint16_t lpffreq	= FXsettings.lpfFreq;

	if (rotary) {
		lpffreq += (rotary * 50);
		if (lpffreq < 50)
			lpffreq = 50;

		if (lpffreq > 10000)
			lpffreq = 10000;

		FXsettings.lpfFreq = lpffreq;

		LCD_StringInt(120, 50, lpffreq, 1);
	}
}

void Menu_SetHPFfreqHandler() {
	if (MenuOKpressed(1))
		Menu_GotoParent();

	int8_t rotary 		= MenuRotaryRead(1);
	uint16_t hpffreq	= FXsettings.hpfFreq;

	if (rotary) {
		hpffreq += (rotary * 50);
		if (hpffreq < 50)
			hpffreq = 50;

		if (hpffreq > 10000)
			hpffreq = 10000;

		FXsettings.hpfFreq = hpffreq;

		LCD_StringInt(120, 50, hpffreq, 1);
	}
}

void Menu_SetDSfreqHandler() {
	if (MenuOKpressed(1))
		Menu_GotoParent();

	int8_t rotary 		= MenuRotaryRead(1);
	uint16_t dsfreq		= FXsettings.dsFreq;

	if (rotary) {
		dsfreq += (rotary * 100);
		if (dsfreq < 1)
			dsfreq = 1;

		if (dsfreq > 44100)
			dsfreq = 44100;

		FXsettings.dsFreq = dsfreq;

		LCD_StringInt(120, 50, dsfreq, 1);
	}
}

void Menu_SetBCbitsHandler() {
	if (MenuOKpressed(1))
		Menu_GotoParent();

	int8_t rotary 		= MenuRotaryRead(1);
	uint16_t bcbits	= FXsettings.bcBits;

	if (rotary) {
		bcbits += rotary;
		if (bcbits < 1)
			bcbits = 1;

		if (bcbits > DAC_BITS - 1)
			bcbits = DAC_BITS;

		FXsettings.bcBits = bcbits;

		LCD_StringInt(120, 50, bcbits, 1);
	}
}

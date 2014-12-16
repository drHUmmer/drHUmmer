#ifndef SETTINGS_H
#define SETTINGS_H

#define MIDI_MASTER		1
#define MIDI_SLAVE		0

#define MIDI_SYNC_ON	1
#define MIDI_SYNC_OFF	0

//////////
// MIDI //
//////////
typedef struct {
	uint8_t		channel			: 4; // 0 - 15
	uint8_t		master_slave	: 1; // MIDI_MASTER / MIDI_SLAVE
	uint8_t		sync			: 1; // MIDI_SYNC_ON / MIDI_SYNC_OFF
} MIDI_Typedef;

//////////
// FILE //
//////////
typedef struct {

} FILE_Typedef;

////////////
// FILTER //
////////////
typedef struct {
	uint8_t 	fx1_filter;
	uint16_t	fx1_value;

	uint8_t 	fx2_filter;
	uint16_t	fx2_value;
} FilterBookmark_Typedef;

typedef struct {
	FilterBookmark_Typedef	bookmark1;
	FilterBookmark_Typedef	bookmark2;
} FilterBookmarks_Typedef;

//////////////
// Settings //
//////////////
typedef struct {
	MIDI_Typedef 				midi;
	FilterBookmarks_Typedef		filterbookmarks;
} Settings_Typedef;

// Creation of the setting struct
Settings_Typedef	settings;

#endif // SETTINGS_H

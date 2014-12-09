
#include "SD.h"

FATFS FatFs;		// Fatfs object
FIL fil; 			// File object
uint32_t total;		// Total space
uint32_t free;		// Free space


TCHAR	fnames[_MAX_FILES][13] = {{"\0"},{"\0"}};
uint8_t	nfiles;

FRESULT SDInit(){

	return f_mount(&FatFs, "", 1);
}


FRESULT SDGetNames(const TCHAR* path){

	FILINFO fno;
	DIR		p_dir;
	FRESULT result = FR_OK;
	uint8_t  i,j;

	nfiles = 0;

	result = f_opendir(&p_dir, path);
	if (result) return result;

	for(i=0; i<_MAX_FILES; i++){
		result = f_readdir(&p_dir, &fno);
		if (result || !fno.fname[0]) break; // no more files
		for(j=0; j<13; j++)fnames[i][j] = fno.fname[j];
	}
	nfiles = i;
	return result;
}



uint16_t SDGet16(TCHAR* fname, uint16_t clusterIdx){

	uint8_t buff[2] = {0};
	uint32_t br;
	FRESULT result;
	uint8_t offset = 1;


	uint16_t data;
	result = f_open(&fil, &*(fname),FA_READ);
	if (result == FR_OK) {
		f_lseek(&fil,clusterIdx*2);
		result = f_read(&fil, &buff, 2, &br);
		if (result)
		{
			f_close(&fil);
			return result;
		}
		f_close(&fil);
	}
	data = buff[0];
	data = buff[1];

	data = (buff[0] | (buff[1] << 4));


	return 0;
}

void SDGet512(uint8_t* buf, TCHAR* fname, uint16_t clusterIdx){

	uint8_t buff[512] = {0};
	uint32_t br;
	FRESULT result;
	uint8_t offset = 1;


	uint16_t data;
	result = f_open(&fil, &*(fname),FA_READ);
	if (result == FR_OK) {
		//result = f_read(&fil, &buff, 512, &br);
		f_lseek(&fil,1024);
		result = f_read(&fil, &buff, 512, &br);
		if (result)
		{
			f_close(&fil);
			return result;
		}
		f_close(&fil);
	}
	data = buff[0];
	data = buff[1];
	data = buff[2];
	data = buff[3];
	data = buff[4];

	data = (buff[0] & (buff[1] << 4) & (buff[2] << 8) & (buff[3] << 12));


	return 0;
}

void SDPut16(TCHAR* fname, uint16_t data){


}


/*

	    TCHAR	fnames[_MAX_FILES][13] = {{0},{0}};
	    uint8_t  i;

	    //Initialize delays
	    TM_DELAY_Init();
	    //Initialize LEDs
	    TM_DISCO_LedInit();

	    //Mount drive
	    if (f_mount(&FatFs, "", 1) == FR_OK) {
	        //Mounted OK, turn on RED LED
	        TM_DISCO_LedOn(LED_RED);


	        //read file names
	        result = f_opendir(&p_dir, "/");
	        for(i=0; i<_MAX_FILES; i++){

	        	result = f_readdir(&p_dir, &fno);

	        	if (result || !fno.fname[0]) break; // End of dir

	        	uint8_t j;
	        	for(j=0; j<13; j++)fnames[i][j] = fno.fname[j];


	    	}

	    //result = f_readdir (&p_dir, &fno);




	        //Try to open file
	        if (f_open(&fil, "2ndfile.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
	            //File opened, turn off RED and turn on GREEN led
	            TM_DISCO_LedOn(LED_GREEN);
	            TM_DISCO_LedOff(LED_RED);

	            //If we put more than 0 characters (everything OK)
	            if (f_puts("First string in my file\n", &fil) > 0) {
	                if (TM_FATFS_DriveSize(&total, &free) == FR_OK) {
	                    //Data for drive size are valid
	                }

	                //Turn on both leds
	                TM_DISCO_LedOn(LED_GREEN | LED_RED);
	            }

	            //Close file, don't forget this!
	            f_close(&fil);
	        }

	        //Unmount drive, don't forget this!
	        f_mount(0, "", 1);
	    }
*/

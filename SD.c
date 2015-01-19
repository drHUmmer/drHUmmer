
#include "SD.h"


FATFS FatFs;		// Fatfs object
FIL fil; 			// File object
//uint32_t total;		// Total space
//uint32_t free;		// Free space


TCHAR	fnames[_MAX_FILES][13] = {{"\0"},{"\0"}};
uint8_t	nfiles;

FRESULT SDInit(){

	FRESULT result = f_mount(&FatFs, "", 1);

	//SPI1->CR1 &= ~(0x0038);
	SPI_Cmd(SPI1, DISABLE);

		SPI_InitTypeDef SPI_InitStruct;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

		SPI_StructInit(&SPI_InitStruct);
		SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStruct.SPI_Mode = SPI_Mode_Master;

		SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;

		SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
		SPI_Init(SPI1, &SPI_InitStruct);
		SPI_Cmd(SPI1, ENABLE);

	return result;
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
	uint32_t* br = 0;
	FRESULT result;

	result = f_open(&fil, &*(fname),FA_READ);
	if (result == FR_OK) {
		f_lseek(&fil,(clusterIdx*2));
		result = f_read(&fil, &buff, 2, (UINT*)br);
		if (result)
		{
			f_close(&fil);
			return result;
		}
		f_close(&fil);
	}


	return (buff[0] | (buff[1] << 8));
}

FRESULT SDGet512(uint16_t* buf16, TCHAR* fname, uint32_t clusterIdx){

	uint8_t buf8[(WAV_BUF_SIZE*2)] = {0};
	uint32_t* br = 0;
	uint32_t i;
	FRESULT result;
	//uint8_t offset = 1;
	int16_t data16;

	result = f_open(&fil, &*(fname),FA_READ);
	if (result == FR_OK) {
//		f_lseek(&fil,(clusterIdx*2));
		f_lseek(&fil,clusterIdx);
		result = f_read(&fil, &buf8, (WAV_BUF_SIZE*2), (UINT*)br);
		if (result)
		{
			f_close(&fil);
			return result;
		}
		f_close(&fil);
	}else return result;


	int16_t offset = 32767;	//1024;
	int16_t bitConv = 4;	//32;

	for (i=0; i<(WAV_BUF_SIZE*2); i+=2){
		data16  = (buf8[i] | (buf8[i+1] << 8));
		//data16  += 32767;
		//data16  &= 0xFFF0;

		data16 += offset; // DC comp

		data16  >>= bitConv; //	/= bitConv;		// 16 to 12 bit

		//data16 &= 0x0FFF; // mask

		buf16[i/2] = (uint16_t) data16;
	}

	return FR_OK;
}

uint32_t getFileSize(TCHAR* fname)
{
	uint32_t size;
	f_open(&fil, &*(fname),FA_READ);
	size = f_size(&fil);
	f_close(&fil);

	return size;
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

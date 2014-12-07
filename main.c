#include "main.h"

void task_a(void);
void task_b(void);
void leds(void);

#ifdef USE_OS
OS_STK taskA_stk[128];  /*!< define "taskA" task stack */
OS_STK taskB_stk[128];  /*!< define "taskB" task stack */
OS_STK led_stk [128];  /*!< define "led" task stack */

OS_FlagID a_flag,b_flag;

OS_EventID mbox0;
#endif

#ifndef DEBUG	/* DEBUG not defined; regular operation (define located in main.h) */
int main(void)
{
	PLLInit();
	//SysTick_Init();
	sequencerInit();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
	| GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

//	UIInit();

//	dacInit();
//	adcInit();
	NVICTimer2Init();
	NVICTimer5Init();
	Timer2Init();
	Timer5Init();

	BPMUpdate(sequencer.BPM);

	while(1);
}

#else	/* if debug mode */

int main(void)
{
	PLLInit();
	sequencerInit();
	SPI3_Init();

/*****************
 * 	LED IO init
 * 	PD12 = Green
 * 	PD13 = Orange
 * 	PD14 = Red
 * 	PD15 = Blue
 *****************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
	| GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
/* End LED IO init */

//	UIInit();

//	dacInit();
//	adcInit();
//	NVICTimer2Init();
//	NVICTimer5Init();
//	Timer2Init();
//	Timer5Init();

//	BPMUpdate(sequencer.BPM);

//	RingBufferInit();









//	SysTick_Init();

	//Fatfs object
	    FATFS FatFs;
	    //File object
	    FIL fil;
	    //Free and total space
	    uint32_t total, free;

	    FILINFO fno;
	    DIR		p_dir;
	    FRESULT result = FR_OK;

	    #define _MAX_FILES 20

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

	    while (1) {

	    }
}

void EXTI1_IRQHandler(void)
{

}

#endif	/* end debug mode */


#ifndef USE_OS
/*
void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
*/
#endif

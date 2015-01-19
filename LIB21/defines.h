/**
 *  Defines for your entire project at one place
 * 
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

//Select your own SPI for ILI9341 library
#define ILI9341_SPI         SPI5
#define ILI9341_SPI_PINS    TM_SPI_PinsPack_1

//Use detect pin
#define FATFS_USE_DETECT_PIN            0
//Use writeprotect pin
#define FATFS_USE_WRITEPROTECT_PIN        0

//If you want to overwrite default CD pin, then change this settings
/*
#define FATFS_USE_DETECT_PIN_RCC        RCC_AHB1Periph_GPIOB
#define FATFS_USE_DETECT_PIN_PORT        GPIOB
#define FATFS_USE_DETECT_PIN_PIN        GPIO_Pin_6
*/
//If you want to overwrite default WP pin, then change this settings
/*
#define FATFS_USE_WRITEPROTECT_PIN_RCC        RCC_AHB1Periph_GPIOB
#define FATFS_USE_WRITEPROTECT_PIN_PORT        GPIOB
#define FATFS_USE_WRITEPROTECT_PIN_PIN        GPIO_Pin_7
*/

//Activate SDIO 1-bit mode
#define FATFS_SDIO_4BIT         0

//Activate SDIO 4-bit mode
//#define FATFS_SDIO_4BIT         1

//Use SPI communication with SDCard
#define    FATFS_USE_SDIO                0

//Select your SPI settings
#define FATFS_SPI                SPI1
#define FATFS_SPI_PINSPACK        TM_SPI_PinsPack_1

//Custom CS pin for SPI communication
#define FATFS_CS_RCC        RCC_AHB1Periph_GPIOB
#define FATFS_CS_PORT        GPIOB
#define FATFS_CS_PIN        GPIO_Pin_5

//Use custom get_fattime() function
#define FATFS_CUSTOM_FATTIME                1

//Implement RTC get time here if you need it
/*
DWORD get_fattime (void) {
    return      ((DWORD)(2014 - 1980) << 25)    // Year 2014
            | ((DWORD)7 << 21)                // Month 7
            | ((DWORD)10 << 16)                // Mday 10
            | ((DWORD)16 << 11)                // Hour 16
            | ((DWORD)0 << 5)                // Min 0
            | ((DWORD)0 >> 1);                // Sec 0
}
*/


#endif

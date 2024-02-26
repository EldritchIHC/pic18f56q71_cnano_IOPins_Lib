/*
 * File:   CNANO_BOARD.h
 * Author: Paul
 *
 * Created on February 25, 2024, 4:35 PM
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
//#ifndef XC_HEADER_TEMPLATE_H
//#define	XC_HEADER_TEMPLATE_H


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#include <xc.h>  
#include <stdint.h>
#include <stdbool.h>
/*Defines*/
/*Board LEDs*/
#define  LED0 0 //on port D
#define  LED1 1 //on port D
#define  LED2 4 //on port D
#define  LED3 5 //on port D
#define  LED4 4 //on port B
#define  LED5 5 //on port B
#define  LED6 6 //on port A
#define  LED7 7 //on port A
/*Board Tactile Switches*/
#define SW1 1 //on port A
#define SW2 0 //on port F
#define SW3 7 //on port D
/*SPI Chip Selects*/
#define EEPROM_CS 5 //on port A
#define DAC_CS 6 //on port F
    
/*Structures*/
/*Function prototypes*/
/*Variables*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

//#endif	/* XC_HEADER_TEMPLATE_H */


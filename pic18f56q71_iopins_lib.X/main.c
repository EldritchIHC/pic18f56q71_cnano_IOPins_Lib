/*
 * File:   main.c
 * Author: Paul
 *
 * Created on February 25, 2024, 4:35 PM
 */

// PIC18F56Q71 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator Selection (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_64MHZ// Reset Oscillator Selection (HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1)

// CONFIG2
#pragma config CLKOUTEN = OFF   // Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON      // PRLOCKED One-Way Set Enable bit (PRLOCKED bit can be cleared and set only once)
#pragma config BBEN = OFF       // Boot Block enable bit (Boot block disabled)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config FCMENP = ON      // Fail-Safe Clock Monitor - Primary XTAL Enable bit (Fail-Safe Clock Monitor enabled; timer will flag FSCMP bit and OSFIF interrupt on EXTOSC failure.)
#pragma config FCMENS = ON      // Fail-Safe Clock Monitor - Secondary XTAL Enable bit (Fail-Safe Clock Monitor enabled; timer will flag FSCMP bit and OSFIF interrupt on SOSC failure.)

// CONFIG3
#pragma config MCLRE = EXTMCLR  // MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_16  // Power-up timer selection bits (PWRT set at 16ms)
#pragma config MVECEN = ON      // Multi-vector enable bit (Multi-vector enabled, Vector table used for interrupts)
#pragma config IVT1WAY = ON     // IVTLOCK bit One-way set enable bit (IVTLOCKED bit can be cleared and set only once)
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit (Low-Power BOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG4
#pragma config BORV = VBOR_1P9  // Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 1.9V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD module is disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCKED bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)
#pragma config DEBUG = OFF      // Background Debugger (Background Debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG5
#pragma config WDTCPS = WDTCPS_31// WDT Period selection bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled; SWDTEN is ignored)

// CONFIG6
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG7
#pragma config BBSIZE = BBSIZE_256// Boot Block Size Selection bits (Boot Block size is 256 words)

// CONFIG8
#pragma config SAFSZ = SAFSZ_NONE// SAF Block Size Selection bits (NONE)

// CONFIG9
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not Write protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers not Write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not Write protected)
#pragma config WRTSAF = OFF     // SAF Write protection bit (SAF not Write Protected)
#pragma config WRTAPP = OFF     // Application Block write protection bit (Application Block not write protected)

// CONFIG10
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM code protection disabled)

// CONFIG11
#pragma config CP = OFF         // PFM Code Protection bit (PFM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "IOPINS.h"
#include "CNANO_BOARD.h"

static void IOC0_ISR (void);

bool bState = 0;//Global
bool bLEDPattern = 0;//Global

void main(void) {  
    INTCON0bits.GIE = 1; //Enable global interrupts 
    uint8_t u8Mask1 = 0;//MCU LED
    uint8_t u8Mask2 = 0;//MCU SW and Board LED
    
    uint8_t u8MaskPortA1 = 0;//Board LEDs
    uint8_t u8MaskPortB1 = 0;//Board LEDs
    uint8_t u8MaskPortD1 = 0;//Board LEDs

    uint8_t u8PinList1[] = {7};//on port C
    uint8_t u8PinList2[] = {0, SW1};//on port A
    
    uint8_t u8PinListPortA1[] = {LED6, LED7 };
    uint8_t u8PinListPortB1[] = {LED4, LED5 };
    uint8_t u8PinListPortD1[] = {LED0, LED1, LED2, LED3 };
    uint8_t u8PinListPortA2[] = {SW1};

    
    IOPINS_vMaskGenerator(u8PinList1, 1, &u8Mask1);
    IOPINS_vMaskGenerator(u8PinList2, 2, &u8Mask2);
    
    IOPINS_vMaskGenerator(u8PinListPortA1, 2, &u8MaskPortA1);
    IOPINS_vMaskGenerator(u8PinListPortB1, 2, &u8MaskPortB1);
    IOPINS_vMaskGenerator(u8PinListPortD1, 4, &u8MaskPortD1);
    
    IOPINS_vPortConfig(PRTA, u8Mask2, INPUT, 1, SCHTR);
    //IOPINS_vPortInterruptConfig(PRTA, u8Mask2, NEGEDGE, POLLING_METHOD);//Polling Method
    IOPINS_vPortInterruptConfig(PRTA, u8Mask2, NEGEDGE, ISR_METHOD);//Interrupt Service Routine Method
    IOPINS_vPortConfig(PRTC, u8Mask1, OUTPUT, 0, SCHTR);
    IOPINS_vPortConfig(PRTA, u8MaskPortA1, OUTPUT, 0, SCHTR);
    IOPINS_vPortConfig(PRTB, u8MaskPortB1, OUTPUT, 0, SCHTR);
    IOPINS_vPortConfig(PRTD, u8MaskPortD1, OUTPUT, 0, SCHTR);
    
    uint16_t i = 0;
    while(1)
    {
        /*Polling method*/
        /*
        if(IOPINS_bPinAInterruptRead(u8Mask2))
        {
            if(bState)
                bState = false;
            else
                bState = true;
            
        }
         * 
        if(IOCAFbits.IOCAF1) //Check the interrupt flag
        {
            IOCAFbits.IOCAF1 = 0;// Clear the interrupt flag on RA1

            if(bLEDPattern)
                bLEDPattern = false;
            else
                bLEDPattern = true;
        }
        */
        
        if(bState)
        {
            if(bLEDPattern)
            {
                IOPINS_vPortASet(u8MaskPortA1);
                IOPINS_vPortBSet(u8MaskPortB1);
                IOPINS_vPortDSet(u8MaskPortD1);
                IOPINS_vPortCSet(u8Mask1);
                for( i = 65535; i != 0; i-- );//Delay
                IOPINS_vPortAClear(u8MaskPortA1);
                IOPINS_vPortBClear(u8MaskPortB1);
                IOPINS_vPortDClear(u8MaskPortD1);
                IOPINS_vPortCClear(u8Mask1);
                for( i = 65535; i != 0; i-- );//Delay
            }
            else
            {
                IOPINS_vPortASet(u8MaskPortA1);
                IOPINS_vPortBSet(u8MaskPortB1);
                IOPINS_vPortDClear(u8MaskPortD1);
                IOPINS_vPortCClear(u8Mask1);
                for( i = 65535; i != 0; i-- );//Delay
                for( i = 65535; i != 0; i-- );//Delay
                IOPINS_vPortAClear(u8MaskPortA1);
                IOPINS_vPortBClear(u8MaskPortB1);
                IOPINS_vPortDSet(u8MaskPortD1);
                IOPINS_vPortCSet(u8Mask1);
                for( i = 65535; i != 0; i-- );//Delay
                for( i = 65535; i != 0; i-- );//Delay
            }
        }
    }
    return;
}

void __interrupt(irq(IRQ_IOC),base(8)) IOC0_ISR()
{
    PIR0bits.IOCIF = 0; //Clear interrupt flag    
    if(IOCAFbits.IOCAF0) //Check the interrupt flag
    {
        IOCAFbits.IOCAF0 = 0;// Clear the interrupt flag on RA0
        
        if(bState)
            bState = false;
        else
            bState = true;
    }
    
    if(IOCAFbits.IOCAF1) //Check the interrupt flag
    {
        IOCAFbits.IOCAF1 = 0;// Clear the interrupt flag on RA1
        
        if(bLEDPattern)
            bLEDPattern = false;
        else
            bLEDPattern = true;
    }
}
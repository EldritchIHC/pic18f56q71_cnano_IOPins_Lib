/*
 * File:   IOPINS.c
 * Author: Paul
 *
 * Created on February 25, 2024, 4:55 PM
 */

/* Project Headers */
/* System Headers*/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
/* Own Headers */
#include "IOPINS.h"
/* External Headers */
/* Function Prototypes */
   void IOPINS_vMaskGenerator(uint8_t u8PinList[], uint8_t u8Pins, uint8_t *u8PinMask);
   void IOPINS_vPortConfig(uint8_t u8Port, uint8_t u8PinMask, uint8_t u8Direction, uint8_t bWeakPU, bool bInputLevelSel);
   void IOPINS_vPortInterruptConfig(uint8_t u8Port, uint8_t u8PinMask, bool bEdge, bool bInterruptMethod);
   /*Port A Port functions*/
   void IOPINS_vPortASet(uint8_t u8PinMask);
   void IOPINS_vPortAClear(uint8_t u8PinMask);
   uint8_t IOPINS_u8PortARead();
   bool IOPINS_bPinARead(uint8_t u8PinMask); 
   uint8_t IOPINS_u8PortAInterruptRead();
   bool IOPINS_bPinAInterruptRead(uint8_t u8PinMask); 
   
   /*Port B Port functions*/
   void IOPINS_vPortBSet(uint8_t u8PinMask);
   void IOPINS_vPortBClear(uint8_t u8PinMask);
   uint8_t IOPINS_u8PortBRead();
   bool IOPINS_bPinBRead(uint8_t u8PinMask);
   uint8_t IOPINS_u8PortBInterruptRead();
   bool IOPINS_bPinBInterruptRead(uint8_t u8PinMask); 
   
   /*Port C Port functions*/
   void IOPINS_vPortCSet(uint8_t u8PinMask);
   void IOPINS_vPortCClear(uint8_t u8PinMask);
   uint8_t IOPINS_u8PortCRead();
   bool IOPINS_bPinCRead(uint8_t u8PinMask);
   uint8_t IOPINS_u8PortCInterruptRead();
   bool IOPINS_bPinCInterruptRead(uint8_t u8PinMask); 
   
   /*Port D Port functions*/
   void IOPINS_vPortDSet(uint8_t u8PinMask);
   void IOPINS_vPortDClear(uint8_t u8PinMask);
   uint8_t IOPINS_u8PortDRead();
   bool IOPINS_bPinDRead(uint8_t u8PinMask);
   
   /*Port E Port functions*/
   void IOPINS_vPortESet(uint8_t u8PinMask);
   void IOPINS_vPortEClear(uint8_t u8PinMask);
   uint8_t IOPINS_u8PortERead();
   bool IOPINS_bPinERead(uint8_t u8PinMask);
   /*Port F Port functions*/
   void IOPINS_vPortFSet(uint8_t u8PinMask);
   void IOPINS_vPortFClear(uint8_t u8PinMask);
   uint8_t IOPINS_u8PortFRead();
   bool IOPINS_bPinDFRead(uint8_t u8PinMask);
   
  
   
/* Global Variables */  
void IOPINS_vMaskGenerator(uint8_t u8PinList[], uint8_t u8Pins, uint8_t *u8PinMask)
{
    volatile uint8_t idx;
    volatile uint8_t u8TempMask = 0x00;
    for( idx = 0; idx < u8Pins; idx++)
    {
        u8TempMask |= ( 1 << u8PinList[idx] );
    }
    *u8PinMask = u8TempMask;
}

void IOPINS_vPortConfig(uint8_t u8Port, uint8_t u8PinMask, uint8_t u8Direction, uint8_t bWeakPU, bool bInputLevelSel)
{
    switch(u8Port){
        case PRTA:
            /*Set Port A direction*/
            if(u8Direction == OUTPUT)
                {
                    TRISA = ~u8PinMask;
                    LATA = 0x00;
                }
            else
                {
                    TRISA +=  u8PinMask;
                    /*Set Weak Pull-ups*/
                    if(bWeakPU)
                        WPUA += u8PinMask;
                    else
                        WPUA &= ~u8PinMask;
                    /*Set the input level*/
                    if(bInputLevelSel)
                        INLVLA += u8PinMask;
                    else
                        INLVLA &= ~u8PinMask;   
                }
        break;
        case PRTB:
            /*Set Port B direction*/
            if(u8Direction == OUTPUT)
                {
                    TRISB &= ~u8PinMask;
                    LATB = 0x00;
                }
            else
                {
                    TRISB +=  u8PinMask;
                    /*Set Weak Pull-ups*/
                    if(bWeakPU)
                        WPUB += u8PinMask;
                    else
                        WPUB &= ~u8PinMask;
                    /*Set the input level*/
                    if(bInputLevelSel)
                        INLVLB += u8PinMask;
                    else
                        INLVLB &= ~u8PinMask; 
                }
        break;
        case PRTC:
            /*Set Port C direction*/
            if(u8Direction == OUTPUT)
                {
                    TRISC &= ~u8PinMask;
                    LATC = 0x00;
                }
            else
                {
                    TRISC +=  u8PinMask;
                    /*Set Weak Pull-ups*/
                    if(bWeakPU)
                        WPUC += u8PinMask;
                    else
                        WPUC &= ~u8PinMask;
                    /*Set the input level*/
                    if(bInputLevelSel)
                        INLVLC += u8PinMask;
                    else
                        INLVLC &= ~u8PinMask; 
                }
        break;
        case PRTD:
            /*Set Port D direction*/
            if(u8Direction == OUTPUT)
                {
                    TRISD &= ~u8PinMask;
                    LATD = 0x00;
                }
            else
                {
                    TRISD +=  u8PinMask;
                    /*Set Weak Pull-ups*/
                    if(bWeakPU)
                        WPUD += u8PinMask;
                    else
                        WPUD &= ~u8PinMask;
                    /*Set the input level*/
                    if(bInputLevelSel)
                        INLVLD += u8PinMask;
                    else
                        INLVLD &= ~u8PinMask;  
                }
        break;
        case PRTE:
            /*Set Port E direction*/
            if(u8Direction == OUTPUT)
                {
                    TRISE &= ~u8PinMask;
                    LATE = 0x00;
                }
            else
                {
                    TRISE +=  u8PinMask;
                    /*Set Weak Pull-ups*/
                    if(bWeakPU)
                        WPUE += u8PinMask;
                    else
                        WPUE &= ~u8PinMask;
                    /*Set the input level*/
                    if(bInputLevelSel)
                        INLVLE += u8PinMask;
                    else
                        INLVLE &= ~u8PinMask;   
                }
        break;
        case PRTF:
            /*Set Port F direction*/
            if(u8Direction == OUTPUT)
            {
                TRISF &= ~u8PinMask;
                LATF = 0x00;
            }
            else
                {
                TRISF +=  u8PinMask;
                /*Set Weak Pull-ups*/
                if(bWeakPU)
                    WPUF += u8PinMask;
                else
                    WPUF &= ~u8PinMask;
                /*Set the input level*/
                if(bInputLevelSel)
                    INLVLF += u8PinMask;
                else
                    INLVLF &= ~u8PinMask; 
                }
        break;
    }
}

void IOPINS_vPortInterruptConfig(uint8_t u8Port, uint8_t u8PinMask, bool bEdge, bool bInterruptMethod)
{
    if(bInterruptMethod)PIE0bits.IOCIE = 1; 
    switch(u8Port){
        case PRTA:
            IOCAF = 0x00;
            ANSELA &= ~u8PinMask; 
            if(bEdge)
                {
                    IOCAP |=  u8PinMask;
                    IOCAN &= ~u8PinMask;
                }
            else
                {
                    IOCAP &= ~u8PinMask;
                    IOCAN |=  u8PinMask;
                }
        break;
        
        case PRTB:
            IOCBF = 0x00;
            ANSELB &= ~u8PinMask; 
            if(bEdge)
                {
                    IOCBP |=  u8PinMask;
                    IOCBN &= ~u8PinMask;
                }
            else
                {
                    IOCBP &= ~u8PinMask;
                    IOCBN |=  u8PinMask;
                }

        break;
        
        case PRTC:
            IOCCF = 0x00;
            ANSELC &= ~u8PinMask; 
            if(bEdge)
                {
                    IOCCP |=  u8PinMask;
                    IOCCN &= ~u8PinMask;
                }
            else
                {
                    IOCCP &= ~u8PinMask;
                    IOCCN |=  u8PinMask;
                }

        break;
        
        case PRTD:
                //Doesn't exist
        break;
        
        case PRTE:
                //Doesn't exist
        break;
        
        case PRTF:
                //Doesn't exist
        break;
    } 
}
/*Port A Port functions*/
void IOPINS_vPortASet(uint8_t u8PinMask)
{
    LATA += u8PinMask;
}

void IOPINS_vPortAClear(uint8_t u8PinMask)
{
    LATA &= ~u8PinMask;
}

uint8_t IOPINS_u8PortARead()
{
    return PORTA;
}

bool IOPINS_bPinARead(uint8_t u8PinMask)
{
    if( ( PORTA & u8PinMask ) )
        return true;
    else
        return false;
}

uint8_t IOPINS_u8PortAInterruptRead()
{
    return IOCAF;
}

bool IOPINS_bPinAInterruptRead(uint8_t u8PinMask)
{
    if(  IOCAF & u8PinMask )
    {
        IOCAF = 0x00;
        return true;
    }
    else
        return false;
}

/*Port B Port functions*/
void IOPINS_vPortBSet(uint8_t u8PinMask)
{
    LATB += u8PinMask;
}

void IOPINS_vPortBClear(uint8_t u8PinMask)
{
    LATB &= ~u8PinMask;
}

uint8_t IOPINS_u8PortBRead()
{
    return PORTB;
}

bool IOPINS_bPinBRead(uint8_t u8PinMask)
{
    if( ( PORTB & u8PinMask ) )
        return true;
    else
        return false;
}

uint8_t IOPINS_u8PortBInterruptRead()
{
    return IOCBF;
}

bool IOPINS_bPinBInterruptRead(uint8_t u8PinMask)
{
    if(  IOCBF & u8PinMask )
    {
        IOCBF = 0x00;
        return true;
    }
    else
        return false;
}

/*Port C Port functions*/
void IOPINS_vPortCSet(uint8_t u8PinMask)
{
    LATC += u8PinMask;
}

void IOPINS_vPortCClear(uint8_t u8PinMask)
{
    LATC &= ~u8PinMask;
}

uint8_t IOPINS_u8PortCRead()
{
    return PORTC;
}

bool IOPINS_bPinCRead(uint8_t u8PinMask)
{
    if( ( PORTC & u8PinMask ) )
        return true;
    else
        return false;
}

uint8_t IOPINS_u8PortCInterruptRead()
{
    return IOCCF;
}

bool IOPINS_bPinCInterruptRead(uint8_t u8PinMask)
{
    if(  IOCCF & u8PinMask )
    {
        IOCCF = 0x00;
        return true;
    }
    else
        return false;
}

/*Port D Port functions*/
void IOPINS_vPortDSet(uint8_t u8PinMask)
{
    LATD += u8PinMask;
}

void IOPINS_vPortDClear(uint8_t u8PinMask)
{
    LATD &= ~u8PinMask;
}

uint8_t IOPINS_u8PortDRead()
{
    return PORTD;
}

bool IOPINS_bPinDRead(uint8_t u8PinMask)
{
    if( ( PORTD & u8PinMask ) )
        return true;
    else
        return false;
}

/*Port E Port functions*/
void IOPINS_vPortESet(uint8_t u8PinMask)
{
    LATE += u8PinMask;
}

void IOPINS_vPortEClear(uint8_t u8PinMask)
{
    LATE &= ~u8PinMask;
}

uint8_t IOPINS_u8PortERead()
{
    return PORTE;
}

bool IOPINS_bPinERead(uint8_t u8PinMask)
{
    if( ( PORTE & u8PinMask ) )
        return true;
    else
        return false;
}

/*Port F Port functions*/
void IOPINS_vPortFSet(uint8_t u8PinMask)
{
    LATF += u8PinMask;
}

void IOPINS_vPortFClear(uint8_t u8PinMask)
{
    LATF &= ~u8PinMask;
}

uint8_t IOPINS_u8PortFRead()
{
    return PORTF;
}

bool IOPINS_bPinFRead(uint8_t u8PinMask)
{
    if( ( PORTF & u8PinMask ) )
        return true;
    else
        return false;
}
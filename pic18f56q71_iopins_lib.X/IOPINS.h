/*
 * File:   IOPINS.h
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
#define PRTA 0
#define PRTB 1
#define PRTC 2
#define PRTD 3
#define PRTE 4
#define PRTF 5
    
#define OUTPUT 0
#define INPUT 1
    
#define LVBUF 0
#define SCHTR 1
    
#define NEGEDGE 0
#define POSEDGE 1
#define POLLING_METHOD 0
#define ISR_METHOD 1
/*Structures*/
/*Function prototypes*/
   void IOPINS_vMaskGenerator(uint8_t u8PinList[], uint8_t u8Pins, uint8_t *u8PinMask);
   void IOPINS_vPortConfig(uint8_t u8Port, uint8_t u8PinMask, uint8_t u8Direction, uint8_t bWeakPU, bool bInputLevelSel);
   void IOPINS_vPortInterruptConfig(uint8_t u8Port, uint8_t u8PinMask, bool bEdge , bool bInterruptMethod);
   
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
   
/*Variables*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

//#endif	/* XC_HEADER_TEMPLATE_H */


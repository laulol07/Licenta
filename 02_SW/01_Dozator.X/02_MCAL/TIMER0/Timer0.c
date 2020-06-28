/**
 * \file       Source.c
 * \author     
 * \brief      Short description for this source file
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <pic18f26k83.h>
#include "Timer0.h"
#include "../GPIO/GPIO.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define GPIO_INPUT_COUNT_PIN    (0xA5)
#define MULTIPLEXED_PIN_T0      (0x05)  //this value correspund for timer0 to be multiplexed on external pin (CLOCKSOURCE_INPUT_PIN))
/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/
/**
 * \brief     This function [...];
 * \param     None
 * \return    None 
 */
/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void Timer0_vInit()
{
    T0CKIPPS = MULTIPLEXED_PIN_T0;  //Clock Source for Timer0 is multiplexed on PortA Pin5 (RA5))
    GPIO_vSetPinDirection(GPIO_INPUT_COUNT_PIN, GPIO_INPUT_PIN); //pin RA5 is set as Input Mode
    /*
     * bit 7 EN: TMR0 Enable bit; 0 = 0 = The module is disabled and in the lowest power mode;
     * bit 6-5 Unimplemented / RO
     * bit 4 MD16 = 1: TMR0 Operating as 16-Bit Timer
     * bit 3-0 OUTPS<3:0>: TMR0 Output Postscaler (Divider) Select bits - 0000 = 1:1 Postscaler
     */
    T0CON0 = 0x90;
    /* bit 7-5 CS<2:0>:Timer0 Clock Source Select bits; 000 = PPS: T0CKIPPS
     * bit 4 ASYNC: TMR0 Input Asynchronization Enable bit; 0 = The input to the TMR0 counter is synchronized to FOSC/4
     * bit 3-0 CKPS<3:0>: Prescaler Rate Select bit; 0000 = 1:1
     */
    T0CON1 = 0x10;    
    Timer0_vResetValue();
}

void Timer0_vResetValue()
{
    TMR0L = 0x00;   //Reset LSB value in TIMER0 COUNT REGISTER
    TMR0H = 0x00;   //Reset MSB value in TIMER0 COUNT REGISTER
}

void Timer0_vMain(void)
{
    water_debitmeter.counts = (TMR0H<<8) | TMR0L;
}
/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

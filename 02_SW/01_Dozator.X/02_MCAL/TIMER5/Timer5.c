/**
 * \file       Timer5.c
 * \author     
 * \brief      Source file for Timer5 configured in the counter mode
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <pic18f26k83.h>
#include "Timer5.h"
#include "../GPIO/GPIO.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define PPS_T5_MUX_PIN_BAND           (0x16)
#define PPS_T5_MUX_PIN_VERTICAL       (0x17)
#define INPUT_PIN_ENC_BAND            (0xC6)
#define INPUT_PIN_ENC_VERTICAL        (0xC7)
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
 * \brief     This function reads the Timer5 value counted;
 * \param     None
 * \return    None 
 */
 void Timer5_vReadCountedValue(void);
/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void Timer5_vInit(void)
{
    GPIO_vSetPinDirection(INPUT_PIN_ENC_BAND, GPIO_INPUT_PIN);
    GPIO_vSetPinDirection(INPUT_PIN_ENC_VERTICAL, GPIO_INPUT_PIN);
    T5CON = 0x02; // Presc. 1:1; SYNC: 0; RD16: 1; ON: 0;
    T5GCON = 0x00;  // GE:0;
    T5CLK = 0x00;   // CS: 00000 (T5CKIPPS))
    T5GATE = 0x1F;  // GSS: 11111;   
}

void Timer5_vMain(void)
{
    Timer5_vReadCountedValue();
}

void Timer5_vResetValue(void)
{
    TMR5H = 0x00;   //Reset MSB value in TIMER5 COUNT REGISTER
    TMR5L = 0x00;   //Reset LSB value in TIMER5 COUNT REGISTER
}

void Timer5_vStartCount(uint8_t encoder_no)
{
    if(encoder_no == ENCODER_BAND)
    {
        Timer5_vResetValue();
        T5CKIPPS = PPS_T5_MUX_PIN_BAND;
        MASK_8BIT_SET_BIT(T5CON, 0u);
    }
    else if(encoder_no == ENCODER_VERTICAL)
    {
        Timer5_vResetValue();
        T5CKIPPS = PPS_T5_MUX_PIN_VERTICAL;
        MASK_8BIT_SET_BIT(T5CON, 0u);  
    }
    else
    {
        
    }
}

void Timer5_vReadCountedValue(void)
{
    timer5_counter = (TMR5H<<8) | TMR5L;
}



/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

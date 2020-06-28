/**
 * \file       PWM.c
 * \author     
 * \brief      In this file is configured the PWM5 Module using the Timer2 Module
 *             Frequency range: 500Hz - 40.000Hz
 *             DutyCycle range: 0-100%
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <pic18f26k83.h>
#include "../GPIO/GPIO.h"
#include "PWM.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define MULTIPLEXED_PIN_PWM5    (0x0D)  //RA4 PUMP
#define MULTIPLEXED_PIN_PWM6    (0x0E)  //RC1 BAND
#define MULTIPLEXED_PIN_PWM7    (0x0F)  //RC3 VERTICAL
#define OUTPUT_PWM5             (0xA4)
#define OUTPUT_PWM6             (0xC1)
#define OUTPUT_PWM7             (0xC3)
#define FREQ_CONST              (125000u) //represents Fosc/presc*4
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

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void PWM_vInit()
{
    RA4PPS = MULTIPLEXED_PIN_PWM5;  //PWM5 - multiplexed on PIN RA4
    RC1PPS = MULTIPLEXED_PIN_PWM6; 
    RC3PPS = MULTIPLEXED_PIN_PWM7;  
    GPIO_vSetPinDirection(OUTPUT_PWM5, GPIO_OUTPUT_PIN);   //Pin is set as Output
    GPIO_vSetPinDirection(OUTPUT_PWM6, GPIO_OUTPUT_PIN);   //Pin is set as Output
    GPIO_vSetPinDirection(OUTPUT_PWM7, GPIO_OUTPUT_PIN);   //Pin is set as Output
    MASK_8BIT_SET_BIT(TRISA, MASK_8BIT_GET_LSB_HALF(OUTPUT_PWM5)); //Disable PWM5 trough the setting of TRIS Register
    MASK_8BIT_SET_BIT(TRISC, MASK_8BIT_GET_LSB_HALF(OUTPUT_PWM6)); //Disable PWM6 trough the setting of TRIS Register
    MASK_8BIT_SET_BIT(TRISC, MASK_8BIT_GET_LSB_HALF(OUTPUT_PWM7)); //Disable PWM7 trough the setting of TRIS Register
    
    PWM5CON = RESET_VALUE;  // Clear the PWM5CON Register 
    PWM6CON = RESET_VALUE;  // Clear the PWM6CON Register
    PWM7CON = RESET_VALUE;  // Clear the PWM7CON Register
    CCPTMRS1 = 0x29; // Timer selection bits for PWM module*(PWM5-TIMER2, PWM6,7-TIMER4)
    //START timer config
    MASK_8BIT_CLEAR_BIT(PIR4, 0x02);    //Clear the TIMER2 Interrupt Flag (TMR2IF = 0)
    MASK_8BIT_CLEAR_BIT(PIR8, 0x02);    //Clear the TIMER4 Interrupt Flag (TMR4IF = 0)
    T2CLK = 0x01;   //Sets Clock Source for PWM5: Fosc/4
    T4CLK = 0x01;   //Sets Clock Source for PWM6/7: Fosc/4
    /**
     * bit 7 ON: Timer2 On bit OFF
     * bit 6-4 Timerx-type Clock Prescale Select bits 1:128 
     * bit 3-0 Timerx Output Postscaler Select bits 1:1
    */
    T2CON = 0x70;
    T4CON = 0x70;
    MASK_8BIT_SET_BIT(T2CON, 0x07);  //Enable the Timer2 -> bit 7 ON: Timer2 On bit:ON   
    MASK_8BIT_SET_BIT(T4CON, 0x07);  //Enable the Timer4 -> bit 7 ON: Timer4 On bit:ON  
    //END timer config
    MASK_8BIT_SET_BIT(PWM5CON, 0x07);   //bit 7 EN: PWM Module Enable bit
    MASK_8BIT_SET_BIT(PWM6CON, 0x07);   //bit 7 EN: PWM Module Enable bit
    MASK_8BIT_SET_BIT(PWM7CON, 0x07);   //bit 7 EN: PWM Module Enable bit
    MASK_8BIT_CLEAR_BIT(TRISA, MASK_8BIT_GET_LSB_HALF(OUTPUT_PWM5));   //Enable PWM5 trough clearing of TRIS Register 
    MASK_8BIT_CLEAR_BIT(TRISC, MASK_8BIT_GET_LSB_HALF(OUTPUT_PWM6));   //Enable PWM5 trough clearing of TRIS Register 
    MASK_8BIT_CLEAR_BIT(TRISC, MASK_8BIT_GET_LSB_HALF(OUTPUT_PWM7));   //Enable PWM5 trough clearing of TRIS Register 
}

void PWM_vSetFrequencyAndDuty(uint32_t desired_frequency, uint32_t desired_duty, uint8_t peripheric)
{
    //frequency_scaled = (_XTAL_FREQ/(desired_frequency*512u))-1;
    uint32_t frequency_scaled = ((FREQ_CONST/(desired_frequency))-1u);
    uint32_t dutycycle_scaled = (desired_duty*4u*(frequency_scaled+1u))/100u; 
    if((desired_frequency > 40000u) || (desired_frequency < 500u) || (desired_duty < 0u) || (desired_duty > 100u))
    {
        T4PR = 0u;
        PWM6DC = 0u << 0x06;
        T4PR = 0u;
        PWM7DC = 0u << 0x06;
        T2PR = 0u;
        PWM5DC = 0u << 0x06; //see page 771 datasheet
    }  
    if(peripheric == BAND_SERVO)
    {
        T4PR = frequency_scaled;
        PWM6DC = dutycycle_scaled << 0x06;
    }
    else if(peripheric == VERTICAL_SERVO)
    {
        T4PR = frequency_scaled;
        PWM7DC = dutycycle_scaled << 0x06;
    }
    else if(peripheric == DC_PUMP)
    {
        T2PR = frequency_scaled;
        PWM5DC = dutycycle_scaled << 0x06; //see page 771 datasheet
    }
}
/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

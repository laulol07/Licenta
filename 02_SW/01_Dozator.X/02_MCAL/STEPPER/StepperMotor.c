/**
 * \file       StepperMotor.c
 * \author     
 * \brief      This module handling the stepper and DC motors 
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <pic18f26k83.h>
#include "StepperMotor.h"
#include "../GPIO/GPIO.h"
#include "StepperMotor.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define STEPPER_DUTY_0     (0x00)  //500Hz
#define STEPPER_DUTY_50    (0x7C)  //500Hz
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
 * \brief     This function sets the sense rotation for stepper motor;
 * \param     None
 * \return    None 
 */
void StepperMotor_gvSetDirection(Peripheric_module motorId, Motor_direction direction);

/**
 * \brief     This function sets the speed rotation for stepper motor;
 * \param     None
 * \return    None 
 */
void StepperMotor_gvSetStep(Peripheric_module motorId, uint16_t step_freq, uint8_t dutycycle);
/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void StepperMotor_gvInit(void)
{
   GPIO_vSetPinDirection(DIRECTION_PIN_M1, GPIO_OUTPUT_PIN); 
   GPIO_vSetPinDirection(STEP_PIN_M1, GPIO_OUTPUT_PIN);
   GPIO_vSetPinDirection(DIRECTION_PIN_M2, GPIO_OUTPUT_PIN); 
   GPIO_vSetPinDirection(STEP_PIN_M2, GPIO_OUTPUT_PIN);
   StepperMotor_gvMotorCommand(DC_PUMP, UNKNOWN_DIRECTION, 0u, 0u);
   StepperMotor_gvMotorCommand(BAND_SERVO, UNKNOWN_DIRECTION, 0u, 0u);
   StepperMotor_gvMotorCommand(VERTICAL_SERVO, UNKNOWN_DIRECTION, 0u, 0u);
}

void StepperMotor_gvMotorCommand(Peripheric_module motorId, Motor_direction direction, uint16_t frequency, uint8_t dutycycle)
{
    if(motorId == DC_PUMP)
    {
        StepperMotor_gvSetStep(motorId, frequency, dutycycle);
    }
    else if((motorId == VERTICAL_SERVO) || (motorId == BAND_SERVO))
    {
        StepperMotor_gvSetDirection(motorId, direction);
        StepperMotor_gvSetStep(motorId, frequency, dutycycle);
    }
}



/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/
void StepperMotor_gvSetDirection(Peripheric_module motorId, Motor_direction direction)
{
    if(motorId == BAND_SERVO)
    {
        if (direction == DIRECTION_CW)
        {
            GPIO_vSetPinLevel(DIRECTION_PIN_M1, STD_HIGH);
        }
        else if (direction == DIRECTION_CCW)
        {
            GPIO_vSetPinLevel(DIRECTION_PIN_M1, STD_LOW);
        }
    }
    else if(motorId == VERTICAL_SERVO)
    {
     if (direction == DIRECTION_CW)
        {
            GPIO_vSetPinLevel(DIRECTION_PIN_M2, STD_HIGH);
        }
        else if (direction == DIRECTION_CCW)
        {
            GPIO_vSetPinLevel(DIRECTION_PIN_M2, STD_LOW);
        }   
    }
    else
    {
        
    }
}

void StepperMotor_gvSetStep(Peripheric_module motorId, uint16_t step_freq, uint8_t dutycycle)
{
    if(motorId == BAND_SERVO)
    {
        PWM_vSetFrequencyAndDuty(step_freq, dutycycle, BAND_SERVO);
    }
    else if(motorId == VERTICAL_SERVO)
    {
        PWM_vSetFrequencyAndDuty(step_freq, dutycycle, VERTICAL_SERVO);
    }
    else if(motorId == DC_PUMP)
    {
        PWM_vSetFrequencyAndDuty(step_freq, dutycycle, DC_PUMP);
    }
    else
    {
        
    }   
}
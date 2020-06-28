/*
 * HEAD.H
 *
 *  Created on: Mmm DD, YYYY
 *      Author: Ioan Nicoara
 */

#ifndef HEAD_H_
#define HEAD_H_

/**
 * \file       StepperMotor.h
 * \author     
 * \brief      This module handling the stepper motors
 */


/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "../../03_Common/types.h"
#include "../../02_MCAL/PWM/PWM.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
#define DIRECTION_PIN_M1    (0xC0)
#define DIRECTION_PIN_M2    (0xC2)
#define STEP_PIN_M1         (0xC1)
#define STEP_PIN_M2         (0xC3)
/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
typedef enum
{
    DIRECTION_CW = 0u, /*clockwise direction*/
    DIRECTION_CCW,/*counterclockwise direction*/
    UNKNOWN_DIRECTION,
}Motor_direction;

/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/
/**
 * \brief     This function initialize the stepper motor;
 * \param     None
 * \return    None 
 */
void StepperMotor_gvInit(void);

/**
 * \brief     This is the main function for stepper motor;
 * \param     None
 * \return    None 
 */
void StepperMotor_gvMain(void);

/**
 * \brief     This is used to command the motor;
 * \param     motorId - the motor to be controlled
 * \param     direction - the sense rotation of the motor
 * \param     step_freq - desired frequency
 * \param     dutycycle - desired dutycycle
 * \return    None 
 */
void StepperMotor_gvMotorCommand(Peripheric_module motorId, Motor_direction direction, uint16_t step_freq, uint8_t dutycycle);


#endif /* HEAD_H_ */

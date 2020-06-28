/*
 * HEAD.H
 *
 *  Created on: 08 08, 2019
 *      Author: Ioan Nicoara
 */

#ifndef PWM_H_
#define PWM_H_



/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "../../03_Common/types.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
#define TIMER2_PRESCALER    (128u)
#define TIMER4_PRESCALER    (128u)

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/

struct
{
    uint16_t frequency;
    uint16_t duty;
}PWM_Parameters;


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
 * \brief     This function initializes the PWM5 Module; This function used Timer2 Module as source;
 * \param     None
 * \return    None 
 */
void PWM_vInit(void);

/**
 * \brief     This function sets Frequency and DutyCycle for PWM5;
 * \param     desired_frequency - represents the desired frequency for PWM5
 *            desired_duty - represents the desired Duty Cycle for PWM5
 * \return    None 
 */
void PWM_vSetFrequencyAndDuty(uint32_t desired_frequency, uint32_t desired_duty, uint8_t peripheric);

#endif /* HEAD_H_ */

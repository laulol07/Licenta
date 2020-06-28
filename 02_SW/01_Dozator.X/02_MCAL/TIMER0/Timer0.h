/*
 * HEAD.H
 *
 *  Created on: 08 07, 2019
 *      Author: Ioan Nicoara
 */

#ifndef TIMER0_H_
#define TIMER0_H_

/**
 * \file       Timer0.h
 * \author     
 * \brief      This file contain source file of the Timer0 Module
 */


/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "../../03_Common/types.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
typedef struct counter
{
    uint16_t counts;
}debitmeter;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/
debitmeter water_debitmeter;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/
/**
 * \brief     This function initializes the Timer0 Module;
 * \param     None
 * \return    None 
 */
extern void Timer0_vInit(void);

/**
 * \brief     This function resets the Timer0 value counted;
 * \param     None
 * \return    None 
 */
void Timer0_vResetValue(void);

/**
 * \brief     This function is used for store the pulses counted of the Timer0 timer;
 * \param     None
 * \return    None
 */
extern void Timer0_vMain(void); 


#endif /* HEAD_H_ */

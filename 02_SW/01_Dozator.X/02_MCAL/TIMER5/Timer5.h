/*
 *  Created on: 03 17, 2020
 *      Author: Ioan Nicoara
 */

#ifndef TIMER5_H_
#define TIMER5_H_

/**
 * \file       Timer5.h
 * \author     Ioan Nicoara
 * \brief      Header file for Timer5 configured in counter mode
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
typedef enum
{
    ENCODER_BAND      = 0u,
    ENCODER_VERTICAL  = 1u,  
};
/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/
uint16_t timer5_counter;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/
/**
 * \brief     Init function for Timer5 configured in counter mode;
 * \param     None
 * \return    None 
 */
extern void Timer5_vInit(void);


/**
 * \brief     Main function for Timer5
 * \param     None
 * \return    None 
 */
extern void Timer5_vMain(void);

/**
 * \brief     This function resets the Timer5 value counted;
 * \param     None
 * \return    None 
 */
extern void Timer5_vResetValue(void);

/**
 * \brief     This function start the Timer5 to count;
 * \param     None
 * \return    None 
 */
extern void Timer5_vStartCount(uint8_t encoder_no);

#endif /* HEAD_H_ */

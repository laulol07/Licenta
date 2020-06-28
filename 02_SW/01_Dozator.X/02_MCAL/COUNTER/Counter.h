/*
 * HEAD.H
 *
 *  Created on: Mmm DD, YYYY
 *      Author: Coman Laurentiu
 */

#ifndef CAPTURE_H_
#define CAPTURE_H_

/**
 * \file       Capture.h
 * \author     Coman Laurentiu
 * \brief      Header file for Counter module based on Timer0 and Timer5
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
typedef struct counters
{
    uint16_t encoder_band;
    uint16_t encoder_vertical;
    uint16_t encoder_debit;   
}counted;
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
 * \brief     Init function for counter driver based on Timer0 and Timer5
 * \param     None
 * \return    None 
 */
void Counter_vInit(void);

/**
 * \brief     Main function for counter driver based on Timer0 and Timer5
 * \param     None
 * \return    None 
 */
void Counter_vMain(void);
#endif /* HEAD_H_ */

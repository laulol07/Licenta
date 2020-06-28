/*
 * HEAD.H
 *
 *  Created on: 09 15, 2019
 *      Author: Coman Laurentiu
 */

#ifndef TIMER1_H_
#define TIMER1_H_

/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "../../03_Common/types.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
#define CCP1_Flag   MASK_8BIT_GET_BIT(PIR4,3) //represents the interrupt flag for CCP1
#define CCP2_Flag   MASK_8BIT_GET_BIT(PIR8,3) //represents the interrupt flag for CCP2

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
typedef enum 
{
    SENSOR_1,
    SENSOR_2,
    NO_OF_SENSORS,
};

typedef struct valori
{
    uint16_t sensor_1; //used to detect an object
    uint16_t sensor_2; // used to detect the liquid level of glass
}dataSensor;

typedef struct StatusFlag
{
    bool sensor_1;
    bool sensor_2;
}triggerFlag;


dataSensor distance;
triggerFlag endCapture;
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
 * \brief     This function initializes the Timer1 Module;
 * \param     None
 * \return    None 
 */
void CaptureDistance_vInit(void);



/**
 * \brief     This function is used to update the measured distance 
 * \param     None
 * \return    measured distance 
 */
void CaptureDistance_vMain();

#endif /* HEAD_H_ */

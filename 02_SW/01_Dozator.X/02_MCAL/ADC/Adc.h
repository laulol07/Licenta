/*
 * ADC.H
 *
 *  Created on: 07 03, 2020
 *      Author: Coman Laurentiu
 */

#ifndef ADC_H_
#define ADC_H_

/**
 * \file       Adc.h
 * \author     Ioan Nicoara
 * \brief      Header file of the ADC driver
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
typedef struct ADC_read
{
    uint16_t raw_count_value;
    uint8_t raw_voltage;
    uint8_t filtered_voltage;
    uint8_t adc_debounce;
    uint8_t adc_first_read;
    bool aquisition_complete;
    bool aquisition_running;
    bool aquisition_start;
}ADC_Status;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/
ADC_Status ADC_parameter;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/
/**
 * \brief     This function initializes the Adc Module.
 * \param     None
 * \return    None 
 */
void ADC_vInit(void);

/**
 * \brief     This function interpolate the ADC value with voltage.
 * \param     adc_raw_value
 * \return    voltage - represents the voltage value in V 
 */

uint16_t ADC_VoltageWaterLevel();

#endif /* HEAD_H_ */

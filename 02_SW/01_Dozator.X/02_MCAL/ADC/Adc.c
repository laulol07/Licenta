/**
 * \file       Adc.c
 * \author     
 * \brief      Implementation file of the ADC driver
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <pic18f26k83.h>
#include "../GPIO/GPIO.h"
#include "Adc.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define ADC_PPS_CHANNEL_RB0    (0x08) // RB0 -> 12bit ADC
#define READ_CHANNEL_RB0       (0xB0) // PORT PIN - RB0

#define ADC_VOLTAGE_REFERENCE   (5u)
#define ADC_MAX_RAW_VALUE       (4096u)
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
 * \brief     This function reads the raw value from PortB pin 0;
 * \param     None
 * \return    return_value - represents a value from 0 to 4096 
 */
uint16_t Adc_ReadRawValue_B0();
/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void ADC_vInit(void)
{
    uint8_t idx = 0;
    ADCON0 = 0x15; // CS=1; FM=1; ON=0;
    ADPCH = ADC_PPS_CHANNEL_RB0;
    GPIO_vSetPinDirection(READ_CHANNEL_RB0, GPIO_INPUT_PIN);
    MASK_8BIT_CLEAR_BIT(ANSELB, 0u); // Set RB0 to analog
    MASK_8BIT_SET_BIT(ADCON0, 7u);  // 
    ADC_parameter.aquisition_complete = 0;
    ADC_parameter.aquisition_running = 0;
    ADC_parameter.adc_first_read = 1;
    MASK_8BIT_SET_BIT(ADCON0, 0u); //Start conversion
}

uint16_t ADC_VoltageWaterLevel()
{
    uint8_t idx;
    static uint32_t voltage;
    uint32_t adc_raw_value;
    uint16_t adc_sum;
    
    for(idx=0;idx<10;idx++)
    {
        adc_raw_value = Adc_ReadRawValue_B0();
        adc_sum +=adc_raw_value;
    }
    voltage = adc_sum/10u;
    voltage = (uint32_t)((uint32_t)(voltage*ADC_VOLTAGE_REFERENCE*100u)/ADC_MAX_RAW_VALUE);

    return voltage;
}

/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

uint16_t Adc_ReadRawValue_B0()
{
    static uint16_t return_value;

    if(ADC_parameter.aquisition_running == 0)
    {
        MASK_8BIT_SET_BIT(ADCON0, 0u); //Start conversion
        ADC_parameter.aquisition_running = 1;
        ADC_parameter.aquisition_complete = 0;
    }
    if(ADC_parameter.aquisition_running == 1)
    {
        if(ADCON0bits.GO == 0)
        {
            ADC_parameter.aquisition_running = 0;
            return_value = ADRES;
        }
    } 
    if(ADC_parameter.adc_first_read == 1)
    {
        ADC_parameter.adc_first_read = 0;
        return_value = ADRES;
    }
    
    return return_value;
}











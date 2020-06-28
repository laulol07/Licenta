/**
 * \file       Source.c
 * \author     
 * \brief      This file contain code for Timer1 configured as Capture Mode
 *             This driver is used for Distance Measure with the HC SR-04 Sensor
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <pic18f26k83.h>
#include "CaptureDistance.h"
#include "../GPIO/GPIO.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define SR04_ECHO_PIN_S1       (0xB2)  // RB2 
#define SR04_ECHO_PIN_PPS_S1   (0X0A)  // PPS->CCP for S1
#define SR04_ECHO_PIN_S2       (0xC5)  // RC5 
#define SR04_ECHO_PIN_PPS_S2   (0X15)  // PPS->CCP for S2
#define SR04_TRIGGER_PIN_S1    (0xB1)  // RB1
#define SR04_TRIGGER_PIN_S2    (0xC4)  // RC4
 
/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/
uint8_t currentSensor; // represents the current sensor
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
 * \brief     This function send trigger for the HC SR-04 Sensor;
 * \param     None
 * \return    None 
 */
void SR04_vSendTrigger(uint8_t sensorId);

/**
 * \brief     This function starts the Timer1;
 * \param     None
 * \return    None 
 */
void TIMERx_Start(uint8_t sensorId);

/**
 * \brief     This function stops the Timer1;
 * \param     None
 * \return    None 
 */
void TIMERx_Stop(uint8_t sensorId);

/**
 * \brief     This function clears the CCP1 Interrupt Flag;
 * \param     None
 * \return    None 
 */
void ClearCCPx_IF(uint8_t sensorId);

/**
 * \brief     This function returns distance for the each HC SR-04 Sensor;
 * \param     None
 * \return    distance  
 * pulse width(s) = ((1/Fosc) * CCPR);
 * pulse width(us) = ((1/Fosc)*10^6 * CCPR);
 * distance(cm) = pulse width(us)/58;
 */
uint8_t GetDISTANCEx(uint8_t sensorId);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void CaptureDistance_vInit(void)
{
    GPIO_vSetPinDirection(SR04_TRIGGER_PIN_S1, GPIO_OUTPUT_PIN);
    GPIO_vSetPinDirection(SR04_TRIGGER_PIN_S2, GPIO_OUTPUT_PIN);
    GPIO_vSetPinDirection(SR04_ECHO_PIN_S1, GPIO_INPUT_PIN); //pin RB2 is set as Input Mode
    GPIO_vSetPinDirection(SR04_ECHO_PIN_S2, GPIO_INPUT_PIN); //pin RC5 is set as Input Mode
    CCP1PPS = SR04_ECHO_PIN_PPS_S1;  //set PPS as ->CCP1   
    CCP2PPS = SR04_ECHO_PIN_PPS_S2;
    CCP1CON = 0x85;
    CCP2CON = 0x85;
    CCPTMRS0 = 0x09;
    CCP1CAP = 0x00;
    CCP2CAP = 0x00;
    
    T1CON = 0x02;   /* Prescaler 1:1 | RD16 | Timer Off */
    T1CLK = 0x02;   /* FOSC */
    
    T3CON = 0x02;   /* Prescaler 1:1 | RD16 | Timer Off */
    T3CLK = 0x02;   /* FOSC */
    PIR4 = 0x00;
    PIE4 = 0x08;
    
    PIR8 = 0x00;
    PIE8 = 0x08;
    PIE0 = 0x80;
    IOCCN = 0x20;
    IOCBN = 0x04;
    endCapture.sensor_1 = TRUE;
    endCapture.sensor_2 = TRUE;
}

void SR04_vSendTrigger(uint8_t sensorId)
{
    if(sensorId == SENSOR_1)
    {
        if(endCapture.sensor_1 == TRUE)
        {
            GPIO_vSetPinLevel(SR04_TRIGGER_PIN_S1,STD_HIGH);
            __delay_us(1u);
            GPIO_vSetPinLevel(SR04_TRIGGER_PIN_S1,STD_LOW);
            endCapture.sensor_1 = FALSE;
        } 
    }
    else if(sensorId == SENSOR_2)
    {
        if(endCapture.sensor_2 == TRUE)
        {
            GPIO_vSetPinLevel(SR04_TRIGGER_PIN_S2,STD_HIGH);
            __delay_us(1u);
            GPIO_vSetPinLevel(SR04_TRIGGER_PIN_S2,STD_LOW);
            endCapture.sensor_2 = FALSE;
        } 
    }
    
}

void CaptureDistance_vMain()
{
    uint8_t idxSensor;
    for(idxSensor = 0u; idxSensor < NO_OF_SENSORS; idxSensor++)
    {
        SR04_vSendTrigger(idxSensor);     
    }    
}




/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/
void TIMERx_Start(uint8_t sensorId)
{
    if(sensorId == SENSOR_1)
    {
        TMR1H = 0u;
        TMR1L = 0u;
        MASK_8BIT_SET_BIT(T1CON, 0u);
    }
    else if(sensorId == SENSOR_2)
    {
        TMR3H = 0u;
        TMR3L = 0u;
        MASK_8BIT_SET_BIT(T3CON, 0u);
    }
}

void TIMERx_Stop(uint8_t sensorId)
{
    if(sensorId == SENSOR_1)
    {
        MASK_8BIT_CLEAR_BIT(T1CON, 0u);
    }
    else if(sensorId == SENSOR_2)
    {
        MASK_8BIT_CLEAR_BIT(T3CON, 0u);
    }
    
}

void ClearCCPx_IF(uint8_t sensorId)
{
    if(sensorId == SENSOR_1)
    {
        MASK_8BIT_CLEAR_BIT(PIR4,3u);
    }
    else if (sensorId == SENSOR_2)
    {
        MASK_8BIT_CLEAR_BIT(PIR8,3u);
    }
}

uint8_t GetDISTANCEx(uint8_t sensorId)
{
    uint8_t distance;
    uint32_t ccpr_value;
 
    if(sensorId == SENSOR_1)
    {
        ccpr_value = CCPR1;
        distance = (ccpr_value * 156)/63621;
        endCapture.sensor_1 = TRUE;
    }
    else if (sensorId == SENSOR_2)
    {
        ccpr_value = CCPR2;
        distance = (ccpr_value * 156)/63621;
        endCapture.sensor_2 = TRUE;
    }
    return distance;
}


void __interrupt(irq(7)) CCPx_Interrupt(void)
{
    
    if (CCP1_Flag == 1)
    {
        TIMERx_Start(SENSOR_1);
        ClearCCPx_IF(SENSOR_1);
    }
    if (CCP2_Flag == 1)
    {
        TIMERx_Start(SENSOR_2);
        ClearCCPx_IF(SENSOR_2);
    }
    
    if(IOCBF == 0x04)
    {
        TIMERx_Stop(SENSOR_1);
        distance.sensor_1 = GetDISTANCEx(SENSOR_1);
        IOCBF = 0x00;
    }
    if(IOCCF == 0x20)
    {
        TIMERx_Stop(SENSOR_2);
        distance.sensor_2 = GetDISTANCEx(SENSOR_2);
        IOCCF = 0x00;
    }
    
//    if(IOCCF6 == 1)
//    {
//        uint8_t const chcked = 1;
//        static uint8_t count1;
//        static uint8_t current_state;
//        current_state = GPIO_ui8GetPinLevel(0xC6); //sets PORTB => GPIOB
//        if (current_state == chcked)
//        {
//            count1++;
//            if (count1 > 1)
//            {
//                distance.counter++;
//                count1 = 0u;
//            }
//        }
//        else
//        {
//            count1 = 0u;
//        }
//        //distance.counter++;
//        IOCCF6 = 0;
//    }
    

}




  
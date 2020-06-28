
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/device_config.h"

#include "02_MCAL/GPIO/GPIO.h"
#include "02_MCAL/TIMER0/Timer0.h"
#include "02_MCAL/PWM/PWM.h"
#include "02_MCAL/LCD/LCD.h"
#include "02_MCAL/ENCODER/RotativeEncoder.h"
#include "02_MCAL/GPIO/GPIO.h"
#include "02_MCAL/CAPTURE/CaptureDistance.h"
#include "02_MCAL/STEPPER/StepperMotor.h"
#include "02_MCAL/ENCODER/RotativeEncoder.h"
#include "02_MCAL/UART/UartTypes.h"
#include "02_MCAL/ADC/Adc.h"

/*
                         Main application
 */

//#define __DEBUG
void INTERRUPT_Initialize(void)
{
    INTCON0bits.GIEH = 1; // Enable high priority interrupts
    INTCON0bits.GIEL = 1; // Enable low priority interrupts
    INTCON0bits.IPEN = 0; // Enable interrupt priority
}
 

void main(void)
{
    SYSTEM_Initialize();

    LCD_vInit();
    Timer0_vInit();
    CaptureDistance_vInit();
    StepperMotor_gvInit();
    BtnEnc_vInit();
    PWM_vInit();
    ADC_vInit();
    
    INTERRUPT_Initialize();
    
    
    PIE0 = 0x80;
    IOCCN = 0x20;
    IOCBN = 0x04;
//#ifndef __DEBUG 
//
//    GPIO_vSetPinDirection(0xB7, GPIO_OUTPUT_PIN);
//
//#endif
    
    

    
    uint16_t voltage_raw;
    volatile float voltage_scaled;
    char text[5] = {'s','a','l','u','t'};
    char text1[2] = {'o','n'};
    char text2[2] = {'o','f'};
    encoder_status.enc_state = 268;
    

    while (1)
    {
        LCD_vMainFunction();
        Debitmeter_vMain();
        Encoder_vMain(ENCODER_PIN_CLK, ENCODER_PIN_DT, encoder_status.enc_state);
        Button_vMain(ENCODER_PIN_SW, 100u);
        
        if(encoder_status.btn_state == STD_HIGH)
        {
            LCD_vWriteString(text1, 0, 2);
        }
        else
        {
            LCD_vWriteString(text2, 0, 2);
        }
        
        LCD_vWriteNumber(encoder_status.enc_state, 5, 4);
        
//        voltage_raw = ADC_VoltageWaterLevel();
//        LCD_vWriteNumber(water_debitmeter.counts, 0, 4);
//        LCD_vWriteString(text, 17, 5);
//        
////        // counted_value = Timer0_ui16PulsesCounted;
////
//        StepperMotor_gvMotorCommand(DC_PUMP, UNKNOWN_DIRECTION, 20000, 50u);
//        StepperMotor_gvMotorCommand(BAND_SERVO, DIRECTION_CW, 41000, 50u);
//
//        StepperMotor_gvMotorCommand(BAND_SERVO, DIRECTION_CW, 500, 0);
//
////        StepperMotor_gvMotorCommand(VERTICAL_SERVO, DIRECTION_CW, 500u, 50);
//        
////
////
////            
////
////      
//
//        LCD_vWriteNumber(distance.sensor_1, 6, 5);
//        LCD_vWriteNumber(distance.sensor_2, 24, 5);
//////        
        CaptureDistance_vMain();

        

    }
}


/**
 * Project:
 * \file:      Dio.c
 * \author:    Nicoara Ioan
 * \brief:     Implementation file for the Button and Rotative Encoder driver.
 * \ingroup:
 *
 * Copyright (c) Nicoara Ioan
 */


/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "RotativeEncoder.h"
#include "../GPIO/GPIO.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define CHECKED_STATE	0x00u
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
/*for BtnEnc_uButton*/

uint8_t current_state = 0x00u;
uint16_t count = 0x00u;
uint8_t cnt = 0x00u;
volatile uint8_t state_level = 0x00u;

/*for BtnEnc_uEncoder*/
uint8_t presentState = 0x00u;
uint8_t previousState = 0x00u;

/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

/**
 * \brief      This is init function from Btn_Enc module.
 * \param      -
 * \return     -
 * \pre        -
 * \post       -
 */
void BtnEnc_vInit(void)
{
    GPIO_vSetPinDirection(ENCODER_PIN_SW, GPIO_INPUT_PIN);
    GPIO_vSetPinDirection(ENCODER_PIN_DT, GPIO_INPUT_PIN);
    GPIO_vSetPinDirection(ENCODER_PIN_CLK, GPIO_INPUT_PIN);
}

/**
 * \brief      This is Encoder function from Btn_Enc module.
 * \param      - CLK_pin
 * \param      - DT_pin
 * \param      - SW_pin
 * \return     - cnt - represents output value
 */
void Encoder_vMain(uint8_t CLK_pin, uint8_t DT_pin, uint16_t cnt)
{
    uint8_t clk_state;
    uint8_t dt_state;
    clk_state = GPIO_ui8GetPinLevel(CLK_pin);
    dt_state = GPIO_ui8GetPinLevel(DT_pin);

    presentState = clk_state;
    if (presentState != previousState)
    {
        if (dt_state != presentState)
        {
            encoder_status.enc_state--;
        }
        else if (dt_state == presentState)
        {
            encoder_status.enc_state++;
        }
    }
    previousState = presentState;
}

/**
 * \brief      This is Button/Switch function from Btn_Enc module.
 * \param      - SW_pin - SW pin
 * \param      - delayCnt - debounce time
 * \return     - None
 * \pre        - BtnEnc_vInit(void)
 */
void Button_vMain(uint8_t SW_pin, uint16_t delayCnt)
{
    current_state = GPIO_ui8GetPinLevel(SW_pin); //sets PORTB => GPIOB
    if (current_state == CHECKED_STATE)
    {
        count++;
        if (count > delayCnt)
        {
            encoder_status.btn_state = STD_HIGH;
            count = 0u;
        }
    }
    else
    {
        encoder_status.btn_state = STD_LOW;
        count = 0u;
    }
}
/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/
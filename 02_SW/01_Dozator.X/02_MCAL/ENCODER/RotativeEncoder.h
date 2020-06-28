

/**
 * \file       Btn_Enc.h
 * \author     Coman Laurentiu
 * \brief      This is file header for Button and Rotative Encoder
 */



/*----------- Headerswitch ON (for prevention of nested includes) ------------*/
#ifndef BTN_ENC_H_
#define BTN_ENC_H_
/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "../../03_Common/types.h"

/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
#define ENCODER_PIN_DT      (0xB3)
#define ENCODER_PIN_CLK     (0xB4)
#define ENCODER_PIN_SW      (0xB5)

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
typedef struct encoder_monitor
{
    uint16_t enc_state; // encoder - value to increase or decrease
    bool btn_state;     // button - switch state
    
}enc_status;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/
enc_status encoder_status;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/
void BtnEnc_vInit(void);
void Encoder_vMain(uint8_t CLK_pin, uint8_t DT_pin, uint16_t cnt);
void Button_vMain(uint8_t SW_pin, uint16_t delayCnt);


/*----------------------------- Headerswitch OFF -----------------------------*/
#endif /* BTN_ENC_H_ */
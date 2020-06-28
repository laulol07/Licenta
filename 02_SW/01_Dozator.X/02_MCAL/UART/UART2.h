
#ifndef UART2_H_
#define UART2_H_

/**
 * \file       Head.h
 * \author     Nicoara Ioan
 * \brief      Short description for this header file
 */


/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/

#include "../../03_Common/types.h"
#include "UartTypes.h"
#include "../GPIO/GPIO.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
#define TX2_IS_ENABLE               (MASK_8BIT_GET_BIT(U2CON0,5))   // Transmit Enable bit
#define TX2_INTERRUPT_FLAG          (MASK_8BIT_GET_BIT(PIR7,5))     // UART2 Transmit Interrupt Flag bit   
#define RX2_INTERRUPT_FLAG          (MASK_8BIT_GET_BIT(PIR7,4))     // UART2 Receive Interrupt Flag bit
#define TX2_BUFFER_FULL_STATUS      (MASK_8BIT_GET_BIT(U2FIFO,4))     // UART2 Transmit Buffer Full Status bit: 1 = Transmit buffer is full
                                                                      //                                        0 = Transmit buffer is not full  
#define RX2_BUFFER_FULL_STATUS          (MASK_8BIT_GET_BIT(U2FIFO,0))     // Receive Buffer Full Status bit     1 = Receive buffer is full
                                                                          //                                    0 = Receive buffer is not full
#define TX2_SHIFTREG_EMPTY          (MASK_8BIT_GET_BIT(U2FIFO,5)) 
/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/

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
 * \brief     This function initialize the UART Module;
 * \param     None
 * \return    None 
 */
void UART2_vInit(void);

/**
 * \brief     This function is used for send values on UART Asynchronous Transmitter
 * \param     valSend - represents value wich to be send on TX
 * \return    None 
 */
void UART2_vTransmitter(uint8_t valSend);

/**
 * \brief     This function is used for receive values on UART Asynchronous Receiver
 * \param    
 * \return    returns the value received in the U2RXB register 
 */
uint8_t UART2_uiReception(uint8_t *received_data);

/**
 * \brief     This function automatically calculates Baud Rate and sets the operating mode (NORMAL_SPEED or HIGH_SPEED);
 * \param     GeneratorSpeed - sets the operating mode (NORMAL_SPEED:HIGH_SPEED) 
 *            DesiredBaud - desired BaudRate (110u - 460800u)
 * \return    None 
 */
void UART2_vBaudCalculator( BaudGeneratorSpeed GeneratorSpeed, uint32_t DesiredBaud);

/**
 * \brief     This function selects the UART mode
 * \param     Mode - operating mode (8-bit / 7-bit / 8-bit with odd parity in the 9th bit / 8-bit with even parity in the 9th bit
              8-bit with address indicator in the 9th bit / LIN only slave mode / LIN Master mode)
 * \return    None 
 */
void UART2_vUARTMode(UartMode Mode);

/**
 * \brief     This function selects number of stop bits from UART frame
 * \param     NoStopBits - 1 transmit with receive verify on first / 1.5 transmit with receive verify on first
                           2 transmit with receive verify on both / 2 transmit with receive verify on first only
 * \return    None 
 */
void UART2_vStopBitMode(StopBitMode NoStopBits);

/**
 * \brief     This function selects polarity bits from UART frame
 * \param     Polarity - '1' Output data is inverted => TX output is low in idle state
 *                       '0' Output data is non-inverted => TX output is high in idle state
 * \return    None 
 */
void UART2_vTransmitPolarityControl(TransmitPolarity Polarity);

/**
 * \brief     This function sets HW Hlow Control from UART
 * \param     FlowControl - FLOW_CONTROL_OFF => FlowControl is OFF
 *                          RTS_CTS_HW_LOW_CONTROL => RTS/CTS and TXDE Hardware Flow Control
 * \return    None 
 */
void UART2_vHandshakeFlowControl(HandshakeFlowControl FlowControl);

/**
 * \brief     This function checks if the UART2 receiver ready for reading
 * \param     None
 * \return    Status of UART2 receiver
                TRUE: UART2 receiver is ready for reading
                FALSE: UART2 receiver is not ready for reading
 */
bool UART2_bRX_Ready();

/**
 * \brief     This function checks if the UART2 transmitter is ready to transmit data
 * \param     None
 * \return    Status of UART2 transmitter
                TRUE: UART2 transmitter is ready
                FALSE: UART2 transmitter is not ready
 */
bool UART2_bTX_Ready();
#endif /* HEAD_H_ */

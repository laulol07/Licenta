/**
 * \file       LCD.c
 * \author     Coman Laurentiu
 * \brief      In this file is described functionality of the LCD 16X02
 * \ingroup    GrpName
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "LCD.h"
#include <pic18f26k83.h>
#include "../GPIO/GPIO.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/

/* Represents the number of characters on the entire display */
#define LCD_NUMBER_OF_CHARACTERS    (32u)
#define LCD_CHARS_PER_LINE          (16u)
#define LCD_delay_37us()            __delay_ms(2);
#define LCD_delay_1600us()          __delay_ms(60);
#define LCD_delay_20ms()            __delay_ms(20);
#define LSB_MASK                    (0x01u)
#define NIBBLE_SIZE                 (4u)

#define LCD_D7                      (0xA0)
#define LCD_D6                      (0xA1)
#define LCD_D5                      (0xA2)
#define LCD_D4                      (0xA3)
#define LCD_RS                      (0xA7)
#define LCD_EN                      (0xA6)

/*----------------------------------------------------------------------------*/
/*                              Local data types                              */

/*----------------------------------------------------------------------------*/
typedef enum
{
    instruction = 0u,
    data = 1u,
} LCD_RegisterSelectType;

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

static uint8_t LCD_CharactersOnScreen[' '];
static uint8_t indexCharacter;

/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/
/**
/**
 * \brief     This function is used to send the command to the LCD;
 * \param     type - represents the state of the RS pin (LOW: instruction/HIGH: data);
 * \param     cmd - represents the command to be sent;
 * \return    None
 * \pre       -
 * \post      -
 */
void LCD_vSendCmd(LCD_RegisterSelectType type, uint8_t cmd);

/**
 * \brief     This function is used to send 4 bits at a time to the LCD;
 * \param     cmd - represents the command to be sent;
 * \return    None
 * \pre       -
 * \post      -
 */
void LCD_vSendNibble(uint8_t cmd);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */

/*----------------------------------------------------------------------------*/

void LCD_vInit(void)
{
    GPIO_vSetPinDirection(LCD_D7, GPIO_OUTPUT_PIN);
    GPIO_vSetPinDirection(LCD_D6, GPIO_OUTPUT_PIN);
    GPIO_vSetPinDirection(LCD_D5, GPIO_OUTPUT_PIN);
    GPIO_vSetPinDirection(LCD_D4, GPIO_OUTPUT_PIN);
    GPIO_vSetPinDirection(LCD_RS, GPIO_OUTPUT_PIN);
    GPIO_vSetPinDirection(LCD_EN, GPIO_OUTPUT_PIN);

    uint8_t ucCharIndex;
    indexCharacter = 0u;
    for (ucCharIndex = 0u; ucCharIndex < LCD_NUMBER_OF_CHARACTERS; ucCharIndex++)
    {
        LCD_CharactersOnScreen[ucCharIndex] = ' ';
    }

    /*Set delay for 20ms*/
    __delay_ms(20);
    /*Set DDRAM adress to 00H*/
    LCD_vSendCmd(instruction, 0x03u);
    __delay_ms(5);
    /*Config: 4b mode, 2 rows, 5x8*/
    LCD_vSendCmd(instruction, 0x02u);
    /*Config: 4b mode, 2 rows, 5x8*/
    LCD_vSendCmd(instruction, 0x02u);
    /*Config: display ON, cursor OFF, cursor position OFF*/
    LCD_vSendCmd(instruction, 0x0Cu);
    /*Set cursor move direction and specifies display shift*/
    /*Config: I/D(increment/decrement): HIGH; S(Shift Left/Right): LOW */
    LCD_vSendCmd(instruction, 0x06u);
}



/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */

/*----------------------------------------------------------------------------*/

void LCD_vMainFunction(void)
{
    uint8_t location = 0u;
    static uint8_t flag = 1u;

    if (flag == 1u)
    {
        /*Sets the starting position for the first line*/
        location = indexCharacter | 0x80;
        LCD_vSendCmd(instruction, location);
        flag = 0;
    }
    else if (flag == 2u)
    {
        /*Sets the starting position for the second line*/
        location = (indexCharacter + 0x30) | 0x80;
        LCD_vSendCmd(instruction, location);
        flag = 0u;
    }
    else
    {
        LCD_vSendCmd(data, LCD_CharactersOnScreen[indexCharacter]);
        if (indexCharacter < LCD_NUMBER_OF_CHARACTERS)
        {
            indexCharacter = indexCharacter + 1;
            if (indexCharacter == LCD_NUMBER_OF_CHARACTERS)
            {
                flag = 1u;
                indexCharacter = 0u;
            }
            else if (indexCharacter == LCD_CHARS_PER_LINE)
            {
                flag = 2u;
            }
            else
            {

            }
        }
    }
}

void LCD_vWriteString(uint8_t * StringToBeSent, uint8_t startingPoint, uint8_t length)
{
    uint8_t ucCharIndex;

    if ((LCD_NUMBER_OF_CHARACTERS + 1u) > (startingPoint + length))
    {
        for (ucCharIndex = 0u; ucCharIndex < length; ucCharIndex++)
        {
            LCD_CharactersOnScreen[ucCharIndex + startingPoint] = StringToBeSent[ucCharIndex];
        }
    }
    else
    {

    }
}

void LCD_vSendCmd(LCD_RegisterSelectType type, uint8_t cmd)
{
    if (type == instruction)
    {
        GPIO_vSetPinLevel(LCD_RS, STD_LOW); // RS pin	->PA2
    }
    else if (type == data)
    {
        GPIO_vSetPinLevel(LCD_RS, STD_HIGH); // RS pin	->PA2
    }
    else
    {

    }
    LCD_vSendNibble(cmd >> NIBBLE_SIZE);
    LCD_vSendNibble(cmd & 0x0F);
}

void LCD_vSendNibble(uint8_t cmd)
{
    GPIO_vSetPinLevel(LCD_EN, STD_HIGH); // EN pin	
    /*Sets the pin value for each LSB */
    GPIO_vSetPinLevel(LCD_D4, (cmd & LSB_MASK)); // D4 pin	
    GPIO_vSetPinLevel(LCD_D5, ((cmd >> 1) & LSB_MASK)); // D5 pin	
    GPIO_vSetPinLevel(LCD_D6, ((cmd >> 2) & LSB_MASK)); // D6 pin
    GPIO_vSetPinLevel(LCD_D7, ((cmd >> 3) & LSB_MASK)); // D7 pin	
    GPIO_vSetPinLevel(LCD_EN, STD_LOW); // EN pin
}

void LCD_vWriteNumber(uint16_t NumberToBeSent, uint8_t startingPoint, uint8_t length)
{
    uint16_t temp = 0;
    char NumberAsChar;

    if((NumberToBeSent>0) && (NumberToBeSent<10))
    {
        temp = (NumberToBeSent);
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint , 1);
        LCD_vWriteString(" ", startingPoint+1, 1);
        LCD_vWriteString(" ", startingPoint+2, 1);
        LCD_vWriteString(" ", startingPoint+3, 1);
        LCD_vWriteString(" ", startingPoint+4, 1);
    }
    else if((NumberToBeSent>9)&&(NumberToBeSent<=99))
    {
        temp = (NumberToBeSent / 10) % 10; //zeci
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint , 1);

        temp = (NumberToBeSent) % 10;   //unitati
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint+1, 1);
        LCD_vWriteString(" ", startingPoint+2, 1);
        LCD_vWriteString(" ", startingPoint+3, 1);
        LCD_vWriteString(" ", startingPoint+4, 1);
    }
   
    
    if((NumberToBeSent>99)&&(NumberToBeSent<=999))
    {
            temp = (NumberToBeSent / 100) % 10;    //sute
              NumberAsChar = 0x30 + temp;
              LCD_vWriteString(&NumberAsChar, startingPoint, 1);

	temp = (NumberToBeSent / 10) % 10; //zeci
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 1, 1);

        temp = (NumberToBeSent) % 10;   //unitati
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 2, 1);
        LCD_vWriteString(" ", startingPoint+3, 1);
    }
    else
    {
        
    }
    
        if((NumberToBeSent>999)&&(NumberToBeSent<=9999))
    {
        temp = (NumberToBeSent / 1000) % 10;    //mii
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint , 1);
	
	temp = (NumberToBeSent / 100) % 10;    //sute
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 1, 1);

        temp = (NumberToBeSent / 10) % 10; //zeci
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 2, 1);

        temp = (NumberToBeSent) % 10;   //unitati
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 3, 1);
        LCD_vWriteString(" ", startingPoint+4, 1);
    }
    else
    {
        
    }
    
    
    if(NumberToBeSent > 9999)
    {
        temp = (NumberToBeSent / 10000) % 10;   //zeci de mii
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint, 1);
	
	temp = (NumberToBeSent / 1000) % 10;    //mii
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 1, 1);

        temp = (NumberToBeSent / 100) % 10; //sute
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 2, 1);

        temp = (NumberToBeSent / 10) % 10;  //zeci
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 3, 1);

        temp = (NumberToBeSent) % 10;   //unitati
        NumberAsChar = 0x30 + temp;
        LCD_vWriteString(&NumberAsChar, startingPoint + 4, 1);
    }
    else
    {
        
    }
        



    

}
/*
 * DIO.h
 *
 *  Created on: July 27, 2023
 *      Author: Anwar
 */

#ifndef MCAL_DIO_H_
#define MCAL_DIO_H_

#include "GPIO.h"

unsigned char DIO_ReadChannel(unsigned char ID);
void DIO_WriteChannel(unsigned char ID ,unsigned char Level );

//DIO IDs(PORTA)
#define DIO_DOOR GPIO_PIN_3
#define LED_ID GPIO_PIN_7

//PORT used
#define GPIO_PORT_Used GPIOA

#endif /* MCAL_DIO_H_ */

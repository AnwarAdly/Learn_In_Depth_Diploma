/*
 * DIO.C
 *
 *  Created on: July 27, 2023
 *      Author: Anwar
 */
#include"DIO.h"

unsigned char DIO_ReadChannel(unsigned char ID)
{

	return (MCAL_GPIO_readPin(GPIO_PORT_Used, ID));
}
void DIO_WriteChannel(unsigned char ID ,unsigned char Level )
{
	MCAL_GPIO_writePin(GPIO_PORT_Used, ID, Level);
}

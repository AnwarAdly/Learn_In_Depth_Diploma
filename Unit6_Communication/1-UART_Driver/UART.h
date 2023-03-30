/*
 * UART.h
 *
 *  Created on: Mar 29, 2023
 *      Author: DELL
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f103xx.h"
#include "GPIO.h"
#include "RCC.h"

//Configs structure
typedef struct {
	uint8_t UART_Mode;		// Specifies the TX/RX Mode.
							// This parameter must be set based on @ref UART_Mode_define
	uint32_t BaudRate;		// This member configures the UART communication baud rate
							// This parameter must be set based on @ref UART_BaudRate_define
	uint8_t Payload_Len;	// Specifies the number of data bits transmitted or received in a frame.
							// This parameter must be set based on @ref UART_Payload_Length_define
	uint8_t Parity ;		// Specifies the parity mode.
							// This parameter must be set based on @ref UART_Parity_define
	uint8_t StopBits ;		// Specifies the number of stop bits transmitted
							// This parameter must be set based on @ref UART_StopBits_define
	uint8_t HwFlowCtl ;		// Specifies whether the hardware flow control mode is enabled or disabled
							// This parameter must be set based on @ref UART_HwFlowCtl_define
	uint8_t IRQ_Enable;		// enable or disable UART IRQ TX/RX
							// This parameter must be set based on @ref UART_IRQ_Enable_define
	void(* P_IRQ_CallBack)(void) ;	//Set the C Function() which will be called once the IRQ  Happen

}UART_Config_t;

//Reference Macros
// @ref UART_Mode_define
#define UART_MODE_RX                        (uint32_t)(1<<2) //RE =1
#define UART_MODE_TX                       	(uint32_t)(1<<3) //TE =1
#define UART_MODE_TX_RX                     ((uint32_t)(1<<2 | 1<<3))
// @ref UART_BaudRate_define
#define UART_BaudRate_2400                   2400
#define UART_BaudRate_9600                   9600
#define UART_BaudRate_19200                  19200
#define UART_BaudRate_57600                  57600
#define UART_BaudRate_115200                 115200
#define UART_BaudRate_230400                 230400
#define UART_BaudRate_460800                 460800
#define UART_BaudRate_921600                 921600
#define UART_BaudRate_2250000                2250000
#define UART_BaudRate_4500000                4500000
// @ref UART_Payload_Length_define
#define UART_Payload_Length_8B               (uint32_t)(0)
#define UART_Payload_Length_9B               (uint32_t)(1<<12)
// @ref UART_Parity_define
#define UART_Parity__NONE                    (uint32_t)(0)
#define UART_Parity__EVEN                    ((uint32_t)1<<10)
#define UART_Parity__ODD                     ((uint32_t)(1<<10 | 1<<9))
// @ref UART_StopBits_define
#define UART_StopBits__half                  (uint32_t)(1<<12)
#define UART_StopBits__1                     (uint32_t)(0)
#define UART_StopBits__1_half                (uint32_t)(3<<12)
#define UART_StopBits__2                     (uint32_t)(2<<12)
// @ref UART_HwFlowCtl_define
#define UART_HwFlowCtl_NONE                  (uint32_t)(0)
#define UART_HwFlowCtl_RTS                   ((uint32_t)1<<8)
#define UART_HwFlowCtl_CTS                   ((uint32_t)1<<9)
#define UART_HwFlowCtl_RTS_CTS               ((uint32_t)(1<<8 | 1<<9))
// @ref UART_IRQ_Enable_define
#define UART_IRQ_Enable_NONE                  (uint32_t) (0)
#define UART_IRQ_Enable_TXE                   (uint32_t)(1<<7) //Transmit data register empty
#define UART_IRQ_Enable_TC         			  (uint32_t)(1<<6) //Transmission complete
#define UART_IRQ_Enable_RXNEIE                (uint32_t)(1<<5) //Received data ready to be read & Overrun error detected
#define UART_IRQ_Enable_PE                    (uint32_t)(1<<8) //Parity error

enum Polling_Mechanism{
	enable,
	disable
};

// BaudRate Calculations
//Example : fclk=36000000 , BR=115200
//USARTDIV 		      = fclk / (16 * BR) 										  = 19.53
//USARTDIV_MUL100 	  = (100 *fclk ) / (16 * BR) == (25 *fclk ) / (4* BR)   	  = 1953
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV  )  * 100 						  = 1900
//DIV_Mantissa 		  = Integer Part (USARTDIV  ) 								  = 19
//DIV_Fraction 		  = (( USARTDIV_MUL100  - DIV_Mantissa_MUL100  ) * 16 ) / 100 = 8

#define UARTDIV(_PCLK_ , _BAUD_)			(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define UARTDIV_MUL100(_PCLK_ , _BAUD_)		(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_ , _BAUD_)	(uint32_t) (UARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_ , _BAUD_)			(uint32_t) (UARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_ , _BAUD_)		(uint32_t) (((UARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_ , _BAUD_)	(( Mantissa (_PCLK_, _BAUD_) ) << 4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )

//UART APIs
void MCAL_UART_Init (UART_Typedef *UARTx, UART_Config_t* UART_Config);
void MCAL_UART_DeInit (UART_Typedef *UARTx);
void MCAL_UART_GPIO_Set_Pins (UART_Typedef *UARTx);
void MCAL_UART_SendData	(UART_Typedef *UARTx, uint16_t *pTxBuffer,enum Polling_Mechanism PollingEn );
void MCAL_UART_ReceiveData	(UART_Typedef *UARTx, uint16_t *pRxBuffer ,enum Polling_Mechanism PollingEn );

#endif /* UART_H_ */

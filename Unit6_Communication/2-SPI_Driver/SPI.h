/*
 * SPI.h
 *
 *  Created on: 30 Mar 2023
 *      Author: DELL
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f103xx.h"
#include "GPIO.h"

struct SPI_IRQ_Event{
	uint8_t TXE:1;
	uint8_t RXNE:1;
	uint8_t ERR:1;
	uint8_t Reserved:5;
};

//Configs structure
typedef struct {
	uint16_t Device_Mode;	// Specifies the SPI operating Mode.
							// This parameter must be set based on @ref SPI_Device_Mode
	uint16_t Comm_Mode;		// Specifies the SPI bidirectional state.
							// This parameter must be set based on @ref SPI_Communication_Mode
	uint16_t Frame_Format;	// Specifies the LSB or MSB of data bits transmitted or received in a frame.
							// This parameter must be set based on @ref SPI_frame_format
	uint16_t Data_Size ;	// Specifies the length of data.
							// This parameter must be set based on @ref SPI_Data_Size
	uint16_t Clk_POL ;		// Specifies the Clock Polarity
							// This parameter must be set based on @ref SPI_CLK_Pol
	uint16_t Clk_PHA ;		// Specifies the Clock Phase
							// This parameter must be set based on @ref SPI_CLK_Phase
	uint16_t NSS;			// Specifies whether the SS either by SW or HW
							// This parameter must be set based on @ref SPI_NSS
	uint16_t Prescaler;		// Specifies the divisor of FCLK
							// This parameter must be set based on @ref SPI_Prescaler
	uint16_t IRQ_Enable;	// enable or disable UART IRQ TX/RX
							// This parameter must be set based on @ref SPI_IRQ_Enable_define
	void(* P_IRQ_CallBack)(struct SPI_IRQ_Event irq);	//Set the C Function() which will be called once the IRQ  Happen

}SPI_Config_t;

//Reference Macros
// @ref SPI_Device_Mode
#define SPI_MODE_MASTER    								(1<<2)
#define SPI_MODE_SLAVE       							(0x00000000U)

// @ref SPI_Communication_Mode
#define SPI_COMM_MODE_2LINES 		   				 	(0x00000000U) 		// CR1 :Full duplex
#define SPI_COMM_MODE_2LINES_RXONLY 					(1<<10) 	  		//RXONLY Half duplex
#define SPI_COMM_MODE_1LINES_RXONLY  					(1<<15) 	  		//bidirectional data mode enable
#define SPI_COMM_MODE_1LINES_TXONLY						((1<<15) | (1<<14)) //bidirectional output mode

// @ref SPI_frame_format
#define  SPI_frame_format_LSB_transmitted_first			(1<<7)   //CR1
#define  SPI_frame_format_MSB_transmitted_first			(0x00000000U)

//@ref SPI_Data_Size
#define SPI_Data_Size_8BIT                     		    (0x00000000U)
#define SPI_Data_Size_16BIT                    			(1<<11) 		// CR1:Bit 11 DFF

// @ref SPI_CLKPolarity
#define SPI_CLKPolarity_Low_when_idle               	(0x00000000U)
#define SPI_CLKPolarity_High_when_idle          		(1<<1) //bit1 CPOL

// @ref SPI_CLKPhase
#define SPI_CLKPhase_1stEDGE_first_data_capture      	(0x00000000U)
#define SPI_CLKPhase_2ndEDGE_first_data_capture  		(1<<0) //bit0 CPHA

// CPOL = 0  && CPHA  = 0 	ideal Low  Read  Rising  Write Falling
// CPOL = 0  && CPHA  = 1 	ideal Low  Write Rising  Read  Falling
// CPOL = 1  && CPHA  = 0 	ideal High Read  Falling Write Rising
// CPOL = 1  && CPHA  = 1 	ideal High Read  Rising  Write Falling

//@ref SPI_NSS
//hardware
#define SPI_NSS_Hard_Slave                      		(0x00000000U)
#define SPI_NSS_Hard_Master_SS_output_enable        	(1<<2)    //SPI_CR2 bit2 SSOE
#define SPI_NSS_Hard_Master_SS_output_disable     		~(1<<2)   //SPI_CR2 bit2
#define SPI_NSS_Hard_Master_For_Case_output_disable		0
//NSS is driven by SW (Master or slave)
#define SPI_NSS_Soft_NSSInternalSoft_Reset          	(1<<9)
#define SPI_NSS_Soft_NSSInternalSoft_set            	((1<<9) | (1<<8))

// SSM = 0 , NSS Controlled By H.W  and SSI can not be use
// SMM = 1 , NSS Controlled By S.W  and default NSS = 0 Low or NSS = 1 High

//@ref SPI_BAUDRATEPrescaler
#define SPI_BAUDRATEPrescaler_2              			(0x00000000U)
#define SPI_BAUDRATEPrescaler_4                       	(0b001 << 3)//Bits 5:3
#define SPI_BAUDRATEPrescaler_8            				(0b010 << 3)
#define SPI_BAUDRATEPrescaler_16                    	(0b011 << 3)
#define SPI_BAUDRATEPrescaler_32                  		(0b100 << 3)
#define SPI_BAUDRATEPrescaler_64                 		(0b101 << 3)
#define SPI_BAUDRATEPrescaler_128                  		(0b110 << 3)
#define SPI_BAUDRATEPrescaler_256                   	(0b111 << 3)

//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE                          	(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE                         	(uint32_t)(1<<7) //CR2
#define SPI_IRQ_Enable_RXNEIE                        	(uint32_t)(1<<6)
#define SPI_IRQ_Enable_ERRIE                         	(uint32_t)(1<<5)

// SPI APIs
void MCAL_SPI_Init 			(SPI_Typedef *SPIx, SPI_Config_t* SPI_Config							   );
void MCAL_SPI_DeInit 		(SPI_Typedef *SPIx														   );
void MCAL_SPI_GPIO_Set_Pins (SPI_Typedef *SPIx														   );
void MCAL_SPI_SendData		(SPI_Typedef *SPIx , uint16_t *pTxBuffer ,enum Polling_Mechanism PollingEn );
void MCAL_SPI_ReceiveData	(SPI_Typedef *SPIx , uint16_t *pRxBuffer ,enum Polling_Mechanism PollingEn );
void MCAL_SPI_TX_RX			(SPI_Typedef *SPIx , uint16_t *pTRxBuffer,enum Polling_Mechanism PollingEn );


#endif /* SPI_H_ */

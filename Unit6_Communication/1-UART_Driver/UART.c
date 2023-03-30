/*
 * UART.c
 *
 *  Created on: Mar 29, 2023
 *      Author: DELL
 */

#include "UART.h"

// Generic Macros & Variables
UART_Config_t* gUART_Cfg = NULL;
//APIs Implementation
/**================================================================
 * @Fn			-MCAL_UART_Init
 * @brief 		- Initializes UART (Supported feature ASYNCH. Only)
 * @param [in] 	- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 	- UART_Config: All UART Configuration EXTI_PinConfig_t
 * @retval 		-none
 * Note			-Support for Now Asynch mode & Clock 8 MHZ S
 */
void MCAL_UART_Init (UART_Typedef *UARTx , UART_Config_t* UART_Config){
	gUART_Cfg = UART_Config;
	//Enable Clock for UART
	if (UARTx == UART1)
		RCC_UART1_CLK_EN();
	else if (UARTx == UART2)
		RCC_UART2_CLK_EN();
	else if (UARTx == UART3)
		RCC_UART3_CLK_EN();
	//Enable UART Module
	UARTx->CR[0] |= (1 << 13);
	//UART Mode
	UARTx->CR[0] |= UART_Config->UART_Mode;
	//Payload length
	UARTx->CR[0] |= UART_Config->Payload_Len;
	//Parity
	UARTx->CR[0] |= UART_Config->Parity;
	//StopBits
	UARTx->CR[1] |= UART_Config->StopBits;
	//HW flow control
	UARTx->CR[2] |= UART_Config->HwFlowCtl;
	//BaudRate
	uint32_t pclk , BRR;
	if(UARTx = UART1){
		pclk = MCAL_RCC_GET_PCLK2();
	}
	else{
		pclk = MCAL_RCC_GET_PCLK1();
	}
	BRR = UART_BRR_Register(pclk , UART_Config->BaudRate);
	UARTx->BRR = BRR;
	//IRQ
	if (UART_Config->IRQ_Enable  != UART_IRQ_Enable_NONE){
		UARTx->CR[0] |= (UART_Config->IRQ_Enable) ;
		//	Enable NVIC For USARTx IRQ
		if ( UARTx == UART1 )
			NVIC_IRQ37_UART1_ENABLE ;

		else if ( UARTx == UART2 )
			NVIC_IRQ38_UART2_ENABLE ;

		else if ( UARTx == UART3 )
			NVIC_IRQ39_UART3_ENABLE ;
	}
}

/**================================================================
 * @Fn				-MCAL_UART_DEInit
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 */
void MCAL_UART_DeInit (UART_Typedef *UARTx){
	if ( UARTx == UART1 ){
		RCC_UART1_CLK_RESET();
		NVIC_IRQ37_UART1_DISABLE ;
	}
	else if ( UARTx == UART2 ){
		RCC_UART2_CLK_RESET();
		NVIC_IRQ38_UART2_DISABLE ;
	}
	else if ( UARTx == UART3 ){
		RCC_UART3_CLK_RESET();
		NVIC_IRQ39_UART3_DISABLE ;
	}
}
/**================================================================
 * @Fn				-MCAL_UART_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_Pins (UART_Typedef *UARTx){
	GPIO_pinConfig_t PinCfg;
	if(UARTx == UART1){
		//PA9 TX , PA10 RX , PA11 CTS , PA12 RTS
		PinCfg.GPIO_pinNumber = GPIO_PIN_9;
		PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_init(GPIOA, &PinCfg);
		PinCfg.GPIO_pinNumber = GPIO_PIN_10;
		PinCfg.GPIO_mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_init(GPIOA, &PinCfg);
		if(gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_CTS || gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			PinCfg.GPIO_pinNumber = GPIO_PIN_11;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOA, &PinCfg);
		}
		if(gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS || gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			PinCfg.GPIO_pinNumber = GPIO_PIN_12;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOA, &PinCfg);
		}
	}
	else if ( UARTx == UART2 ){
		//PA2 TX //PA3 RX //PA0 CTS //PA1 RTS
		PinCfg.GPIO_pinNumber = GPIO_PIN_2;
		PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_init(GPIOA, &PinCfg);
		PinCfg.GPIO_pinNumber = GPIO_PIN_3;
		PinCfg.GPIO_mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_init(GPIOA, &PinCfg);
		if (gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_CTS  || gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			PinCfg.GPIO_pinNumber = GPIO_PIN_0;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOA, &PinCfg);
		}
		if (gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS || gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			PinCfg.GPIO_pinNumber = GPIO_PIN_1;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOA, &PinCfg);
		}
	}
	else if ( UARTx == UART3 )
	{
		//PB10 TX //PB11 RX //PB13 CTS //PA14 RTS
		PinCfg.GPIO_pinNumber = GPIO_PIN_10;
		PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_init(GPIOB, &PinCfg);
		PinCfg.GPIO_pinNumber = GPIO_PIN_11;
		PinCfg.GPIO_mode = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_init(GPIOB, &PinCfg);
		if (gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_CTS  || gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			PinCfg.GPIO_pinNumber = GPIO_PIN_13;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOB, &PinCfg);
		}
		if (gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS || gUART_Cfg->HwFlowCtl == UART_HwFlowCtl_RTS_CTS){
			PinCfg.GPIO_pinNumber = GPIO_PIN_14;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOB, &PinCfg);

		}
	}
}
/*********************************************************************
 * @fn      	  - MCAL_UART_SendData
 * @brief         -Send Buffer on UART
 * @param [in] 	  - USARTx: where x can be (1..3 depending on device used)
 * @param[in]     -pTxBuffer Buffer
 * @param[in]     -PollingEn   Enable pooling or disable it
 * @return        -None
 * @Note          - Should initialize UART First
 *		When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
		the value written in the MSB (bit 8 or 9 depending on the data length) has no effect
		because it is replaced by the parity , When receiving with the parity enabled.
 */
void MCAL_UART_SendData	(UART_Typedef *UARTx, uint16_t *pTxBuffer,enum Polling_Mechanism PollingEn ){
	//wait until TXE flag is set in SR
	if (PollingEn == enable)
		while(!((UARTx->SR) & (1<<7)));
	// check if we send at 8 or 9 bit at frame
	if(gUART_Cfg->Payload_Len == UART_Payload_Length_9B){
		UARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}
	else{
		UARTx->DR = (*pTxBuffer & (uint16_t)0xFF);
	}
}
/*********************************************************************
 * @fn      	  - MCAL_UART_ReceiveData
 * @brief         - Receive Buffer on UART
 * @param [in] 	  - USARTx: where x can be (1..3 depending on device used)
 * @param[in]     - pRxBuffer Buffer
 * @param[in]     - PollingEn   Enable polling or disable it
 * @return        - None
 * @Note          - Should initalize UART First
 *		When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
		the value written in the MSB (bit 8 or 9 depending on the data length) has no effect
		because it is replaced by the parity , When receiving with the parity enabled.
 */
void MCAL_UART_ReceiveData	(UART_Typedef *UARTx, uint16_t *pRxBuffer ,enum Polling_Mechanism PollingEn ){
	//wait until RXNE flag is set in SR
	if (PollingEn == enable)
		while(!((UARTx->SR) & (1<<5)));
	// check if we receive 8 or 9 bit at frame
	if(gUART_Cfg->Payload_Len == UART_Payload_Length_9B){
		//check we enable parity or not
		if (gUART_Cfg->Parity == UART_Parity__NONE){
			*((uint16_t*)pRxBuffer) = UARTx->DR;
		}
		else{ // Parity is used so only 8 of 9 bits is data and MSb parity
			*((uint16_t*)pRxBuffer) = (UARTx->DR & (uint8_t)0xFF);
		}
	}
	else{
		if (gUART_Cfg->Parity == UART_Parity__NONE){
			*((uint16_t*)pRxBuffer) = UARTx->DR;
		}
		else{ // Parity is used so only 7 of 8 bits is data and MSb parity
			*((uint16_t*)pRxBuffer) = (UARTx->DR & (uint8_t)0x7F);
		}
	}
}


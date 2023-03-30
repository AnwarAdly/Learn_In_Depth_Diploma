/*
 * SPI.c
 *
 *  Created on: 30 Mar 2023
 *      Author: DELL
 */

#include "SPI.h"

// Generic Macros & Variables
SPI_Config_t* gSPI_Cfg[2] = {NULL , NULL};

#define SPI1_Index		0
#define SPI2_Index		1
#define SPI_TXE			(uint8_t)0x02
#define SPI_RXNE		(uint8_t)0x01

//APIs Implementation
/*=========================================================================
 * @Fn      - MCAL_SPI_INIT
 * @brief   - Initialise SPI according to the specified parameters
 *param[in] - SPIx :where x can be 1,2 depending on device used
 *param[in] - SPI config :all the SPI configuration
 * @retval  - none
 * Note     - Support for SPI Full duplex Master and slave only
 * ========================================================================*/
void MCAL_SPI_Init 			(SPI_Typedef *SPIx, SPI_Config_t* SPI_Config){
	//Virtual Safety Registers
	uint16_t tempreg_CR1 = 0;
	uint16_t tempreg_CR2 = 0;
	//Enable SPI1 or SPI2
	if(SPIx == SPI1){
		gSPI_Cfg[SPI1_Index] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2){
		gSPI_Cfg[SPI2_Index] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}
	//Enable SPI
	tempreg_CR1 |= (1<<6);
	//Configurations
	tempreg_CR1 |= SPI_Config->Device_Mode;
	tempreg_CR1 |= SPI_Config->Comm_Mode;
	tempreg_CR1 |= SPI_Config->Frame_Format;
	tempreg_CR1 |= SPI_Config->Data_Size;
	tempreg_CR1 |= SPI_Config->Clk_POL;
	tempreg_CR1 |= SPI_Config->Clk_PHA;
	tempreg_CR1 |= SPI_Config->Prescaler;
	if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable){
		tempreg_CR2 |= SPI_Config->NSS; // Master by HW
	}
	else if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_disable){
		tempreg_CR2 &= SPI_Config->NSS; // Master changed to slave by Hw
	}
	else{
		tempreg_CR1 |= SPI_Config->NSS;  // By Sw
	}
	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE){
		tempreg_CR2 |= SPI_Config->IRQ_Enable;
		if (SPIx == SPI1){
			NVIC_IRQ35_SPI1_ENABLE;
		}
		else if (SPIx == SPI2){
			NVIC_IRQ36_SPI2_ENABLE;
		}
	}
	SPIx->CR1 = tempreg_CR1;
	SPIx->CR2 = tempreg_CR2;
}
/**================================================================
 * @Fn       - MCAL_SPI_DeINIT
 * @brief    - DeInitialize SPI
 *param[in]  - SPIx :where x can be 1,2 depending on device used
 *param[in]  - SPI config :all the SPI configuration
 * @retval   - none
 * Note      - Reset the model by RCC
 *==================================================================*/
void MCAL_SPI_DeInit(SPI_Typedef *SPIx){
	if (SPIx == SPI1){
		NVIC_IRQ35_SPI1_DISABLE;
		RCC_SPI1_CLK_RESET();
	}
	else if (SPIx == SPI2){
		NVIC_IRQ36_SPI2_DISABLE;
		RCC_SPI2_CLK_RESET();
	}
}
/**==========================================================================================================
 * @Fn      - MCAL_SPI_GPIO_Set_Pins
 * @brief   - Set the Gpio pins (can know the Pins from GPIO Pins table from TRM)
 *param[in] - SPIx :where x can be 1,2,depending on device used
 * @retval  - none
 * Note     - Should enable the corresponding ALT &GPIO in RCC CLOCK AND called after MCAL_SPI_INIT()
 *===========================================================================================================*/
void MCAL_SPI_GPIO_Set_Pins (SPI_Typedef *SPIx){
	GPIO_pinConfig_t PinCfg;
	if(SPIx == SPI1){
		//PA4 : NSS / PA5 : SCK / PA6 : MISO / PA7 : MOSI
		if (gSPI_Cfg[SPI1_Index]->Device_Mode == SPI_MODE_MASTER){
			switch(gSPI_Cfg[SPI1_Index]->NSS){
			case SPI_NSS_Hard_Master_For_Case_output_disable :
				PinCfg.GPIO_pinNumber = GPIO_PIN_4;
				PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_init(GPIOA, &PinCfg);
				break;
			case SPI_NSS_Hard_Master_SS_output_enable :
				PinCfg.GPIO_pinNumber = GPIO_PIN_4;
				PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
				MCAL_GPIO_init(GPIOA, &PinCfg);
				break;
			}
			PinCfg.GPIO_pinNumber = GPIO_PIN_5;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOA, &PinCfg);
			PinCfg.GPIO_pinNumber = GPIO_PIN_6;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOA, &PinCfg);
			PinCfg.GPIO_pinNumber = GPIO_PIN_7;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOA, &PinCfg);
		}
		else{ // Slave (in case of Sw there won't be NSS bit)
			if(gSPI_Cfg[SPI1_Index]->NSS == SPI_NSS_Hard_Slave){
				PinCfg.GPIO_pinNumber = GPIO_PIN_4;
				PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_init(GPIOA, &PinCfg);
			}
			PinCfg.GPIO_pinNumber = GPIO_PIN_5;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOA, &PinCfg);
			PinCfg.GPIO_pinNumber = GPIO_PIN_6;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOA, &PinCfg);
			PinCfg.GPIO_pinNumber = GPIO_PIN_7;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOA, &PinCfg);
		}
	}
	else if (SPIx == SPI2){
		//PB12 : NSS / PB13 : SCK / PB14 : MISO / PB15 : MOSI
		if (gSPI_Cfg[SPI2_Index]->Device_Mode == SPI_MODE_MASTER){
			switch(gSPI_Cfg[SPI2_Index]->NSS){
			case SPI_NSS_Hard_Master_For_Case_output_disable :
				PinCfg.GPIO_pinNumber = GPIO_PIN_12;
				PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_init(GPIOB, &PinCfg);
				break;
			case SPI_NSS_Hard_Master_SS_output_enable :
				PinCfg.GPIO_pinNumber = GPIO_PIN_12;
				PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
				MCAL_GPIO_init(GPIOB, &PinCfg);
				break;
			}
			PinCfg.GPIO_pinNumber = GPIO_PIN_13;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOB, &PinCfg);
			PinCfg.GPIO_pinNumber = GPIO_PIN_14;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOB, &PinCfg);
			PinCfg.GPIO_pinNumber = GPIO_PIN_5;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOB, &PinCfg);
		}
		else{ // Slave (in case of Sw there won't be NSS bit)
			if(gSPI_Cfg[SPI2_Index]->NSS == SPI_NSS_Hard_Slave){
				PinCfg.GPIO_pinNumber = GPIO_PIN_12;
				PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_init(GPIOB, &PinCfg);
			}
			PinCfg.GPIO_pinNumber = GPIO_PIN_13;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOB, &PinCfg);
			PinCfg.GPIO_pinNumber = GPIO_PIN_14;
			PinCfg.GPIO_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_init(GPIOB, &PinCfg);
			PinCfg.GPIO_pinNumber = GPIO_PIN_15;
			PinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_init(GPIOB, &PinCfg);
		}
	}
}
/**============================================================================================
 * @Fn      - MCAL_SPI_SendData
 * @brief   - Send buffer on SPI
 *param[in] - SPIx :where x can be 1,2 depending on device used
 *param[in] - pTxBuffer: the buffer that will be transmitted
 *param[in] - PollingEn enable or disable the polling
 * @retval  - none
 * Note     - Should initialize SPI first
 *          - this sendData function is implemented for Full Duplex SPI only
 *          - But if you want it for all modes should check first on Communication mode
 *===============================================================================================*/
void MCAL_SPI_SendData(SPI_Typedef *SPIx , uint16_t *pTxBuffer ,enum Polling_Mechanism PollingEn){
	if(PollingEn == enable){
		while(!((SPIx->SR) & SPI_TXE)); // Wait till Txbuffer be empty
	}
	SPIx->DR = *pTxBuffer;
}
/**================================================================
 * @Fn      - MCAL_SPI_ReceiveData
 * @brief   - Receive buffer on SPI
 *param[in] - SPIx :where x can be 1,2 depending on device used
 *param[in] - pTxBuffer: the buffer that will be transmitted
 *param[in] - PollingEn enable or disable the polling
 * @retval  - none
 * Note     - none
 *===================================================================*/
void MCAL_SPI_ReceiveData(SPI_Typedef *SPIx , uint16_t *pRxBuffer ,enum Polling_Mechanism PollingEn){
	if(PollingEn == enable){
		while(!((SPIx->SR) & SPI_RXNE)); // Wait till Rxbuffer be not empty
	}
	*pRxBuffer = SPIx->DR;
}
/**================================================================
 * @Fn      - MCAL_SPI_TX_RX
 * @brief   - Receive and transmit buffer on SPI
 *param[in] - SPIx :where x can be 1,2 depending on device used
 *param[in] - pTRxBuffer: the buffer that will be transmitted
 *param[in] - PollingEn enable or disable the polling
 * @retval  - none
 * Note     - none
 *===================================================================*/
void MCAL_SPI_TX_RX(SPI_Typedef * SPIx , uint16_t* pTRxBuffer , enum Polling_Mechanism PollingEn){
	if(PollingEn == enable){
		while(!((SPIx->SR) & SPI_TXE)); // Wait till Txbuffer be empty
	}
	SPIx->DR = *pTRxBuffer;
	if(PollingEn == enable){
		while(!((SPIx->SR) & SPI_RXNE)); // Wait till Rxbuffer be not empty
	}
	*pTRxBuffer = SPIx->DR;
}
// IRQ
void SPI1_IRQHandler(void){
	struct SPI_IRQ_Event irq;
	irq.TXE  = ((SPI1->SR & (1<<1) ) >> 1);
	irq.RXNE = ((SPI1->SR & (1<<0) ) >> 0);
	irq.ERR  = ((SPI1->SR & (1<<4) ) >> 4);
	gSPI_Cfg[SPI1_Index]->P_IRQ_CallBack(irq);
}
void SPI2_IRQHandler(void){
	struct SPI_IRQ_Event irq;
	irq.TXE  = ((SPI2->SR & (1<<1) ) >> 1);
	irq.RXNE = ((SPI2->SR & (1<<0) ) >> 0);
	irq.ERR  = ((SPI2->SR & (1<<4) ) >> 4);
	gSPI_Cfg[SPI2_Index]->P_IRQ_CallBack(irq);
}

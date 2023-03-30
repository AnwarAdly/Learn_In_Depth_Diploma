/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "GPIO.h"
#include "stm32f103xx.h"

int main(void)
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	GPIO_pinConfig_t pinCfg;
	//PA1 input floating
	pinCfg.GPIO_pinNumber = GPIO_PIN_1;
	pinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(GPIOA, &pinCfg);
	//PB1 output pp @10 Mhz
	pinCfg.GPIO_pinNumber = GPIO_PIN_1;
	pinCfg.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinCfg.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(GPIOB, &pinCfg);
	//PA13 input floating
	pinCfg.GPIO_pinNumber = GPIO_PIN_13;
	pinCfg.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(GPIOA, &pinCfg);
	//PB13 output pp @10 Mhz
	pinCfg.GPIO_pinNumber = GPIO_PIN_13;
	pinCfg.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinCfg.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(GPIOB, &pinCfg);
	while(1){
		if(MCAL_GPIO_readPin(GPIOA, GPIO_PIN_1) == 0){
			MCAL_GPIO_togglePin(GPIOB, GPIO_PIN_1);
			while(MCAL_GPIO_readPin(GPIOA, GPIO_PIN_1) == 0);
		}
		if(MCAL_GPIO_readPin(GPIOA, GPIO_PIN_13) == 1){
			MCAL_GPIO_togglePin(GPIOB, GPIO_PIN_13);
		}
	}
}

/*
 * RCC.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Anwar
 */

#ifndef RCC_H_
#define RCC_H_

#include "stm32f103xx.h"
#include "GPIO.h"

#define HSI_RC_CLK (uint32_t)8000000
#define HSE_CLK    (uint32_t)16000000

//RCC APIs
uint32_t MCAL_RCC_GET_SYS_CLK(void);
uint32_t MCAL_RCC_GET_HCL_CLK(void);
uint32_t MCAL_RCC_GET_PCLK1  (void);
uint32_t MCAL_RCC_GET_PCLK2  (void);



#endif /* RCC_H_ */

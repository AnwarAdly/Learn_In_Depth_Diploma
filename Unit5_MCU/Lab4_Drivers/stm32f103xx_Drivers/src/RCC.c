/*
 * RCC.c
 *
 *  Created on: Mar 29, 2023
 *      Author: DELL
 */


#include "RCC.h"

const uint8_t APBPrescaler[8]={0,0,0,0,1,2,3,4};
const uint8_t AHBPrescaler[16]={0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};
uint32_t MCAL_RCC_GET_SYS_CLK(void){
	switch((RCC->CFGR >> 2) & 0b11){
	case 0: return HSI_RC_CLK;	break;
	case 1: return HSE_CLK;		break;
	case 2: return 16000000;	break;
	}
	return HSI_RC_CLK;
}
uint32_t MCAL_RCC_GET_HCL_CLK(void){
	return (MCAL_RCC_GET_SYS_CLK() >> AHBPrescaler[((RCC->CFGR >> 4) & 0b111)]); //The first shift is multiplication
}
uint32_t MCAL_RCC_GET_PCLK1  (void){
	return (MCAL_RCC_GET_HCL_CLK() >> APBPrescaler[((RCC->CFGR >> 8) & 0b111)]); //The first shift is multiplication
}
uint32_t MCAL_RCC_GET_PCLK2  (void){
	return (MCAL_RCC_GET_HCL_CLK() >> APBPrescaler[((RCC->CFGR >> 11) & 0b111)]); //The first shift is multiplication
}

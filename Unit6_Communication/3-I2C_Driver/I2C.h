/*
 * I2C.h
 *
 *  Created on: 3 Apr 2023
 *      Author: Anwar
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f103xx.h"
#include "GPIO.h"
#include "RCC.h"

//-----------------------------
//User type definitions (structures)
//config structure
//-----------------------------

struct S_I2C_Slave_Device_Address{
	uint16_t                       Enable_Dual_ADD ; //1:enable 0:disable
	uint16_t                       Primary_slave_add ;
	uint16_t                       Secondary_slave_add ;
	uint32_t                       I2C_Addressing_Slave_mode;//@ref I2C_Addressing_Slave_
};

typedef enum{
	I2C_EV_STOP ,
	I2C_ERROR_AF ,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ , // The APP layer should send the data (i2c_slaveSendData)   in this state
	I2C_EV_DATA_RCV   // The APP layer should read the data (i2c_slaveReceiveData)in this state
}Slave_State;

typedef struct{
	uint32_t                          I2C_ClockSpeed ;   			 //Specifies the clock frequency
																	 //this parameter must be set to @ref I2C_SCLK_
	uint32_t                          StretchMode ;      			 //Specifies the clock stretching for the slave
																	 //@ref I2C_StretchMode
    uint32_t                          I2C_Mode ;         			 //Specifies the I2C MODE
   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	 //@ref I2C_Mode
    struct S_I2C_Slave_Device_Address I2C_Slave_Address;
    uint32_t                          I2c_ACK_Control ;    			 //Enable or Disable ACK
   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	 //@ref I2C_ACK_
    uint32_t                          General_Call_Address_Detection;//@ref I2C_ENGC
    void (*P_Slave_Event_CallBack)(Slave_State state);   //Callback function for slave interrupt //Master will be with polling mechanism
}I2C_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref I2C_SCLK_
#define I2C_SCLK_SM_50K                      (50000U )
#define I2C_SCLK_SM_100K                     (100000U)
#define I2C_SCLK_FM_200K                     (200000U)//fast mode not supported yet
#define I2C_SCLK_FM_400K                     (400000U)//Standard speed up to 400KHZ

//@ref I2C_StretchMode
#define I2C_StretchMode_Enable                0x00000000U    //CR1
#define I2C_StretchMode_Disable               I2C_CR1_NOSTRETCH

//@ref I2C_Mode
#define I2C_Mode_I2C                          0x00000000U   //CR1
#define I2C_Mode_SMBus                        I2C_CR1_SMBUS //SMBus not supported yet

//@refI2C_Addressing_Slave_
//OAR1.ADDMODE
#define I2C_Addressing_Slave_7Bit             0x00000000U
#define I2C_Addressing_Slave_10Bit            (uint16_t)(1<<15)

//@ref I2C_ACK_
#define I2C_ACK_Enable                        I2C_CR1_ACK
#define I2C_ACK_Disable                       (uint16_t)(0x0000)

//@ref I2C_ENGC
//CR1:BIT6 Enable/Disable general Call with address 00
#define I2C_ENGC_Enable                       I2C_CR1_ENGC
#define I2C_ENGC_Disable                      0x00000000U

typedef enum{
	with_Stop ,
	without_Stop
}Stop_Condition;

typedef enum{
	start ,
	repeated_start
}Repeated_Start;

typedef enum{
	DISABLE =0,
	ENABLE =1
}FunctionalState;

typedef enum{
	RESET ,
	SET
}FlagStatus;

typedef enum{
	I2C_Direction_Transmitter =0 ,
	I2C_Direction_receieve =1
}I2C_Direction;

#define I2C_EVENT_MASTER_BYTE_TRANSMITING          ((uint32_t)0x00070080)/*TRA , BUSY , MSL ,TXE flags*/

typedef enum{
I2C_FLAG_BUSY =0 ,
EV5 , //EV5:  SB=1,  cleared by reading SR1 register followed by writing DR register with Address.
EV6 , //EV6:  ADDR=1,cleared by reading SR1 register followed by reading SR2.
EV8,  //EV8:  TxE=1, shift register not empty, data register empty, cleared by writing DR register
EV8_1,//EV8_1:TxE=1, shift register empty,     data register empty, write Data1 in DR.
EV7 , //RXNE.
MASTER_BYTE_TRANSMITING =((uint32_t)0x00070080)/*TRA , BUSY , MSL ,TXE flags*/
}Status;
//EV9: ADD10=1, cleared by reading SR1 register followed by writing DR register

/*
 * ====================================================================================================
 *                          APIs Supported by "MCAL I2C DRIVER"
 * ====================================================================================================
 */

void MCAL_I2C_INIT(I2C_Typedef * I2Cx , I2C_Config_t* I2C_InitStruct) ;
void MCAL_I2C_DeINIT(I2C_Typedef * I2Cx ) ;
void MCAL_I2C_GPIO_Set_Pins (I2C_Typedef * I2Cx) ;
//Master Polling mechanism
void MCAL_I2C_Master_TX(I2C_Typedef * I2Cx , uint16_t devAddr , uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_Typedef * I2Cx , uint16_t devAddr , uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start);
//Slave interrupt mechanism
void MCAL_I2C_SlaveSendData(I2C_Typedef * I2Cx ,uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_Typedef * I2Cx);
//Generic APIS
void I2C_GenerateSTART(I2C_Typedef * I2Cx , FunctionalState NewState ,Repeated_Start Start);
FlagStatus I2C_GetFlagStatus(I2C_Typedef * I2Cx , Status flag);
void I2C_SendAddress(I2C_Typedef * I2Cx ,uint16_t Address , I2C_Direction Direction);
void I2C_ACKnowlageConfig(I2C_Typedef * I2Cx  ,FunctionalState NewState);
void I2C_GenerateSTOP(I2C_Typedef * I2Cx , FunctionalState NewState);

#endif /* I2C_H_ */

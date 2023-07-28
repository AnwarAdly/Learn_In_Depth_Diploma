################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AUTOSAR_implementation/MCAL/DIO.c 

OBJS += \
./AUTOSAR_implementation/MCAL/DIO.o 

C_DEPS += \
./AUTOSAR_implementation/MCAL/DIO.d 


# Each subdirectory must supply rules for building sources it contributes
AUTOSAR_implementation/MCAL/DIO.o: ../AUTOSAR_implementation/MCAL/DIO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/AUTOSAR_Files" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/MCAL" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/RTE_gen" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AUTOSAR_implementation/MCAL/DIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


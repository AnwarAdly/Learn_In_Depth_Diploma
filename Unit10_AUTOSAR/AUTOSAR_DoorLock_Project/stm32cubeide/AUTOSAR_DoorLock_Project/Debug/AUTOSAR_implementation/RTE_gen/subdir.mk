################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AUTOSAR_implementation/RTE_gen/Rte_DoorLock_indication_SWC.c \
../AUTOSAR_implementation/RTE_gen/Rte_DoorSensorAbstractionSWC.c 

OBJS += \
./AUTOSAR_implementation/RTE_gen/Rte_DoorLock_indication_SWC.o \
./AUTOSAR_implementation/RTE_gen/Rte_DoorSensorAbstractionSWC.o 

C_DEPS += \
./AUTOSAR_implementation/RTE_gen/Rte_DoorLock_indication_SWC.d \
./AUTOSAR_implementation/RTE_gen/Rte_DoorSensorAbstractionSWC.d 


# Each subdirectory must supply rules for building sources it contributes
AUTOSAR_implementation/RTE_gen/Rte_DoorLock_indication_SWC.o: ../AUTOSAR_implementation/RTE_gen/Rte_DoorLock_indication_SWC.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/AUTOSAR_Files" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/MCAL" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/RTE_gen" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AUTOSAR_implementation/RTE_gen/Rte_DoorLock_indication_SWC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
AUTOSAR_implementation/RTE_gen/Rte_DoorSensorAbstractionSWC.o: ../AUTOSAR_implementation/RTE_gen/Rte_DoorSensorAbstractionSWC.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/AUTOSAR_Files" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/MCAL" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/RTE_gen" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AUTOSAR_implementation/RTE_gen/Rte_DoorSensorAbstractionSWC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


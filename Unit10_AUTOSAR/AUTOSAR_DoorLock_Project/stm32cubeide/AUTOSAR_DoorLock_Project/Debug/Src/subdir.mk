################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GPIO.c \
../Src/RCC.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/GPIO.o \
./Src/RCC.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/GPIO.d \
./Src/RCC.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/GPIO.o: ../Src/GPIO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/AUTOSAR_Files" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/MCAL" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/RTE_gen" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/GPIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/RCC.o: ../Src/RCC.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/AUTOSAR_Files" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/MCAL" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/RTE_gen" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/RCC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/AUTOSAR_Files" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/MCAL" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/RTE_gen" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/AUTOSAR_Files" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/MCAL" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/RTE_gen" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/AUTOSAR_Files" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/MCAL" -I"D:/Learn-in-depth/AUTOSAR_DoorLock_Project/stm32cubeide/AUTOSAR_DoorLock_Project/AUTOSAR_implementation/RTE_gen" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


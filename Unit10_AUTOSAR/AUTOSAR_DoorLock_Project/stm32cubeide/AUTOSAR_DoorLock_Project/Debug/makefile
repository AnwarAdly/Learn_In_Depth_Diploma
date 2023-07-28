################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include AUTOSAR_implementation/RTE_gen/subdir.mk
-include AUTOSAR_implementation/MCAL/subdir.mk
-include AUTOSAR_implementation/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
AUTOSAR_DoorLock_Project.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
AUTOSAR_DoorLock_Project.list \

OBJCOPY_BIN += \
AUTOSAR_DoorLock_Project.bin \


# All Target
all: AUTOSAR_DoorLock_Project.elf secondary-outputs

# Tool invocations
AUTOSAR_DoorLock_Project.elf: $(OBJS) $(USER_OBJS) D:\Learn-in-depth\AUTOSAR_DoorLock_Project\stm32cubeide\AUTOSAR_DoorLock_Project\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "AUTOSAR_DoorLock_Project.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Learn-in-depth\AUTOSAR_DoorLock_Project\stm32cubeide\AUTOSAR_DoorLock_Project\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="AUTOSAR_DoorLock_Project.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

AUTOSAR_DoorLock_Project.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "AUTOSAR_DoorLock_Project.list"
	@echo 'Finished building: $@'
	@echo ' '

AUTOSAR_DoorLock_Project.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "AUTOSAR_DoorLock_Project.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

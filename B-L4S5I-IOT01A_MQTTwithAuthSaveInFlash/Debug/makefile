################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/subdir.mk
-include Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/subdir.mk
-include Middlewares/Third_Party/mbedTLS/library/subdir.mk
-include Middlewares/Third_Party/lwip/src/netif/ppp/subdir.mk
-include Middlewares/Third_Party/lwip/src/netif/subdir.mk
-include Middlewares/Third_Party/lwip/src/core/snmp/subdir.mk
-include Middlewares/Third_Party/lwip/src/core/ipv4/subdir.mk
-include Middlewares/Third_Party/lwip/src/core/subdir.mk
-include Middlewares/Third_Party/lwip/src/api/subdir.mk
-include Middlewares/Third_Party/Wifi/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/Components/st25dv/subdir.mk
-include Drivers/BSP/Components/hts221/subdir.mk
-include Drivers/BSP/Components/es_wifi/subdir.mk
-include Drivers/BSP/B-L4S5I-IOT01/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Security/subdir.mk
-include Core/Network/Wifi/subdir.mk
-include Core/Network/Lwip/subdir.mk
-include Core/Network/C2c/subdir.mk
-include Core/Network/subdir.mk
-include Core/Memory/subdir.mk
-include Core/MQTT/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.elf \

MAP_FILES += \
B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.list \


# All Target
all: main-build

# Main-build Target
main-build: B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.elf secondary-outputs

# Tool invocations
B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.elf B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.map: $(OBJS) $(USER_OBJS) C:\Users\shado\Data\Projects\Embedded\STM\ST\ workspaces\workspace_test\B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash\STM32L4S5VITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\shado\Data\Projects\Embedded\STM\ST workspaces\workspace_test\B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash\STM32L4S5VITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.elf B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.list B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tools/Wifi/Src/wifi.c 

OBJS += \
./Tools/Wifi/Src/wifi.o 

C_DEPS += \
./Tools/Wifi/Src/wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Tools/Wifi/Src/%.o Tools/Wifi/Src/%.su: ../Tools/Wifi/Src/%.c Tools/Wifi/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5-IOT01A_MQTTClient/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5-IOT01A_MQTTClient/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5-IOT01A_MQTTClient/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5-IOT01A_MQTTClient/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5-IOT01A_MQTTClient/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5-IOT01A_MQTTClient/Tools/Wifi/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Tools-2f-Wifi-2f-Src

clean-Tools-2f-Wifi-2f-Src:
	-$(RM) ./Tools/Wifi/Src/wifi.d ./Tools/Wifi/Src/wifi.o ./Tools/Wifi/Src/wifi.su

.PHONY: clean-Tools-2f-Wifi-2f-Src


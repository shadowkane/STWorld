################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/MQTTLinux.c 

OBJS += \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/MQTTLinux.o 

C_DEPS += \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/MQTTLinux.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/%.o Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/%.su: ../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/%.c Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_DEBUG -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include/ipv4" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network/Wifi" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTClient-2d-C-2f-src-2f-linux

clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTClient-2d-C-2f-src-2f-linux:
	-$(RM) ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/MQTTLinux.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/MQTTLinux.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src/linux/MQTTLinux.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTClient-2d-C-2f-src-2f-linux

################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/st25dv/st25dv.c \
../Drivers/BSP/Components/st25dv/st25dv_reg.c 

OBJS += \
./Drivers/BSP/Components/st25dv/st25dv.o \
./Drivers/BSP/Components/st25dv/st25dv_reg.o 

C_DEPS += \
./Drivers/BSP/Components/st25dv/st25dv.d \
./Drivers/BSP/Components/st25dv/st25dv_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/st25dv/%.o Drivers/BSP/Components/st25dv/%.su: ../Drivers/BSP/Components/st25dv/%.c Drivers/BSP/Components/st25dv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include/ipv4" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-st25dv

clean-Drivers-2f-BSP-2f-Components-2f-st25dv:
	-$(RM) ./Drivers/BSP/Components/st25dv/st25dv.d ./Drivers/BSP/Components/st25dv/st25dv.o ./Drivers/BSP/Components/st25dv/st25dv.su ./Drivers/BSP/Components/st25dv/st25dv_reg.d ./Drivers/BSP/Components/st25dv/st25dv_reg.o ./Drivers/BSP/Components/st25dv/st25dv_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-st25dv


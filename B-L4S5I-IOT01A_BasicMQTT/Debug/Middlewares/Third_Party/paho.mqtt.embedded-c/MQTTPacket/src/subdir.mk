################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.c \
../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.c 

OBJS += \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.o \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.o 

C_DEPS += \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.d \
./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/%.o Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/%.su: ../Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/%.c Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include/ipv4" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTPacket-2f-src

clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTPacket-2f-src:
	-$(RM) ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTPacket-2f-src


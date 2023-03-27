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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DUSE_MBED_TLS -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/B-L4S5I-IOT01" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/Components/Common" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/Components/es_wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/Components/hts221" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/Components/st25dv" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/Wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/lwip/src/include" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/lwip/src/include/ipv4" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/Network/Wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/Network" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/MQTT" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/mbedTLS/include" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/Security" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/Memory" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTPacket-2f-src

clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTPacket-2f-src:
	-$(RM) ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectClient.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTConnectServer.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTDeserializePublish.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTFormat.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSerializePublish.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeClient.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTSubscribeServer.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeClient.su ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.d ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.o ./Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-paho-2e-mqtt-2e-embedded-2d-c-2f-MQTTPacket-2f-src


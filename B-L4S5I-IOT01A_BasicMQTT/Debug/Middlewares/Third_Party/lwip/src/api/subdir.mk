################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/api/api_lib.c \
../Middlewares/Third_Party/lwip/src/api/api_msg.c \
../Middlewares/Third_Party/lwip/src/api/err.c \
../Middlewares/Third_Party/lwip/src/api/netbuf.c \
../Middlewares/Third_Party/lwip/src/api/netdb.c \
../Middlewares/Third_Party/lwip/src/api/netifapi.c \
../Middlewares/Third_Party/lwip/src/api/sockets.c \
../Middlewares/Third_Party/lwip/src/api/tcpip.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/api/api_lib.o \
./Middlewares/Third_Party/lwip/src/api/api_msg.o \
./Middlewares/Third_Party/lwip/src/api/err.o \
./Middlewares/Third_Party/lwip/src/api/netbuf.o \
./Middlewares/Third_Party/lwip/src/api/netdb.o \
./Middlewares/Third_Party/lwip/src/api/netifapi.o \
./Middlewares/Third_Party/lwip/src/api/sockets.o \
./Middlewares/Third_Party/lwip/src/api/tcpip.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/api/api_lib.d \
./Middlewares/Third_Party/lwip/src/api/api_msg.d \
./Middlewares/Third_Party/lwip/src/api/err.d \
./Middlewares/Third_Party/lwip/src/api/netbuf.d \
./Middlewares/Third_Party/lwip/src/api/netdb.d \
./Middlewares/Third_Party/lwip/src/api/netifapi.d \
./Middlewares/Third_Party/lwip/src/api/sockets.d \
./Middlewares/Third_Party/lwip/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/api/%.o Middlewares/Third_Party/lwip/src/api/%.su: ../Middlewares/Third_Party/lwip/src/api/%.c Middlewares/Third_Party/lwip/src/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include/ipv4" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-api

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-api:
	-$(RM) ./Middlewares/Third_Party/lwip/src/api/api_lib.d ./Middlewares/Third_Party/lwip/src/api/api_lib.o ./Middlewares/Third_Party/lwip/src/api/api_lib.su ./Middlewares/Third_Party/lwip/src/api/api_msg.d ./Middlewares/Third_Party/lwip/src/api/api_msg.o ./Middlewares/Third_Party/lwip/src/api/api_msg.su ./Middlewares/Third_Party/lwip/src/api/err.d ./Middlewares/Third_Party/lwip/src/api/err.o ./Middlewares/Third_Party/lwip/src/api/err.su ./Middlewares/Third_Party/lwip/src/api/netbuf.d ./Middlewares/Third_Party/lwip/src/api/netbuf.o ./Middlewares/Third_Party/lwip/src/api/netbuf.su ./Middlewares/Third_Party/lwip/src/api/netdb.d ./Middlewares/Third_Party/lwip/src/api/netdb.o ./Middlewares/Third_Party/lwip/src/api/netdb.su ./Middlewares/Third_Party/lwip/src/api/netifapi.d ./Middlewares/Third_Party/lwip/src/api/netifapi.o ./Middlewares/Third_Party/lwip/src/api/netifapi.su ./Middlewares/Third_Party/lwip/src/api/sockets.d ./Middlewares/Third_Party/lwip/src/api/sockets.o ./Middlewares/Third_Party/lwip/src/api/sockets.su ./Middlewares/Third_Party/lwip/src/api/tcpip.d ./Middlewares/Third_Party/lwip/src/api/tcpip.o ./Middlewares/Third_Party/lwip/src/api/tcpip.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-api


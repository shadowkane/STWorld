################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/core/ipv4/autoip.c \
../Middlewares/Third_Party/lwip/src/core/ipv4/icmp.c \
../Middlewares/Third_Party/lwip/src/core/ipv4/igmp.c \
../Middlewares/Third_Party/lwip/src/core/ipv4/inet.c \
../Middlewares/Third_Party/lwip/src/core/ipv4/inet_chksum.c \
../Middlewares/Third_Party/lwip/src/core/ipv4/ip.c \
../Middlewares/Third_Party/lwip/src/core/ipv4/ip_addr.c \
../Middlewares/Third_Party/lwip/src/core/ipv4/ip_frag.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/core/ipv4/autoip.o \
./Middlewares/Third_Party/lwip/src/core/ipv4/icmp.o \
./Middlewares/Third_Party/lwip/src/core/ipv4/igmp.o \
./Middlewares/Third_Party/lwip/src/core/ipv4/inet.o \
./Middlewares/Third_Party/lwip/src/core/ipv4/inet_chksum.o \
./Middlewares/Third_Party/lwip/src/core/ipv4/ip.o \
./Middlewares/Third_Party/lwip/src/core/ipv4/ip_addr.o \
./Middlewares/Third_Party/lwip/src/core/ipv4/ip_frag.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/core/ipv4/autoip.d \
./Middlewares/Third_Party/lwip/src/core/ipv4/icmp.d \
./Middlewares/Third_Party/lwip/src/core/ipv4/igmp.d \
./Middlewares/Third_Party/lwip/src/core/ipv4/inet.d \
./Middlewares/Third_Party/lwip/src/core/ipv4/inet_chksum.d \
./Middlewares/Third_Party/lwip/src/core/ipv4/ip.d \
./Middlewares/Third_Party/lwip/src/core/ipv4/ip_addr.d \
./Middlewares/Third_Party/lwip/src/core/ipv4/ip_frag.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/core/ipv4/%.o Middlewares/Third_Party/lwip/src/core/ipv4/%.su: ../Middlewares/Third_Party/lwip/src/core/ipv4/%.c Middlewares/Third_Party/lwip/src/core/ipv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DUSE_MBED_TLS -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/B-L4S5I-IOT01" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/Components/Common" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/Components/es_wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/Components/hts221" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/Components/st25dv" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/Wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/lwip/src/include" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/lwip/src/include/ipv4" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/Network/Wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/Network" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/MQTT" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/mbedTLS/include" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/Security" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/Memory" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-ipv4

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-ipv4:
	-$(RM) ./Middlewares/Third_Party/lwip/src/core/ipv4/autoip.d ./Middlewares/Third_Party/lwip/src/core/ipv4/autoip.o ./Middlewares/Third_Party/lwip/src/core/ipv4/autoip.su ./Middlewares/Third_Party/lwip/src/core/ipv4/icmp.d ./Middlewares/Third_Party/lwip/src/core/ipv4/icmp.o ./Middlewares/Third_Party/lwip/src/core/ipv4/icmp.su ./Middlewares/Third_Party/lwip/src/core/ipv4/igmp.d ./Middlewares/Third_Party/lwip/src/core/ipv4/igmp.o ./Middlewares/Third_Party/lwip/src/core/ipv4/igmp.su ./Middlewares/Third_Party/lwip/src/core/ipv4/inet.d ./Middlewares/Third_Party/lwip/src/core/ipv4/inet.o ./Middlewares/Third_Party/lwip/src/core/ipv4/inet.su ./Middlewares/Third_Party/lwip/src/core/ipv4/inet_chksum.d ./Middlewares/Third_Party/lwip/src/core/ipv4/inet_chksum.o ./Middlewares/Third_Party/lwip/src/core/ipv4/inet_chksum.su ./Middlewares/Third_Party/lwip/src/core/ipv4/ip.d ./Middlewares/Third_Party/lwip/src/core/ipv4/ip.o ./Middlewares/Third_Party/lwip/src/core/ipv4/ip.su ./Middlewares/Third_Party/lwip/src/core/ipv4/ip_addr.d ./Middlewares/Third_Party/lwip/src/core/ipv4/ip_addr.o ./Middlewares/Third_Party/lwip/src/core/ipv4/ip_addr.su ./Middlewares/Third_Party/lwip/src/core/ipv4/ip_frag.d ./Middlewares/Third_Party/lwip/src/core/ipv4/ip_frag.o ./Middlewares/Third_Party/lwip/src/core/ipv4/ip_frag.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-ipv4


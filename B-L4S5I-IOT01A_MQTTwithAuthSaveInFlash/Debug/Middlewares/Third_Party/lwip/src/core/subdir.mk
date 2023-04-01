################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/core/def.c \
../Middlewares/Third_Party/lwip/src/core/dhcp.c \
../Middlewares/Third_Party/lwip/src/core/dns.c \
../Middlewares/Third_Party/lwip/src/core/init.c \
../Middlewares/Third_Party/lwip/src/core/mem.c \
../Middlewares/Third_Party/lwip/src/core/memp.c \
../Middlewares/Third_Party/lwip/src/core/netif.c \
../Middlewares/Third_Party/lwip/src/core/pbuf.c \
../Middlewares/Third_Party/lwip/src/core/raw.c \
../Middlewares/Third_Party/lwip/src/core/stats.c \
../Middlewares/Third_Party/lwip/src/core/sys.c \
../Middlewares/Third_Party/lwip/src/core/tcp.c \
../Middlewares/Third_Party/lwip/src/core/tcp_in.c \
../Middlewares/Third_Party/lwip/src/core/tcp_out.c \
../Middlewares/Third_Party/lwip/src/core/timers.c \
../Middlewares/Third_Party/lwip/src/core/udp.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/core/def.o \
./Middlewares/Third_Party/lwip/src/core/dhcp.o \
./Middlewares/Third_Party/lwip/src/core/dns.o \
./Middlewares/Third_Party/lwip/src/core/init.o \
./Middlewares/Third_Party/lwip/src/core/mem.o \
./Middlewares/Third_Party/lwip/src/core/memp.o \
./Middlewares/Third_Party/lwip/src/core/netif.o \
./Middlewares/Third_Party/lwip/src/core/pbuf.o \
./Middlewares/Third_Party/lwip/src/core/raw.o \
./Middlewares/Third_Party/lwip/src/core/stats.o \
./Middlewares/Third_Party/lwip/src/core/sys.o \
./Middlewares/Third_Party/lwip/src/core/tcp.o \
./Middlewares/Third_Party/lwip/src/core/tcp_in.o \
./Middlewares/Third_Party/lwip/src/core/tcp_out.o \
./Middlewares/Third_Party/lwip/src/core/timers.o \
./Middlewares/Third_Party/lwip/src/core/udp.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/core/def.d \
./Middlewares/Third_Party/lwip/src/core/dhcp.d \
./Middlewares/Third_Party/lwip/src/core/dns.d \
./Middlewares/Third_Party/lwip/src/core/init.d \
./Middlewares/Third_Party/lwip/src/core/mem.d \
./Middlewares/Third_Party/lwip/src/core/memp.d \
./Middlewares/Third_Party/lwip/src/core/netif.d \
./Middlewares/Third_Party/lwip/src/core/pbuf.d \
./Middlewares/Third_Party/lwip/src/core/raw.d \
./Middlewares/Third_Party/lwip/src/core/stats.d \
./Middlewares/Third_Party/lwip/src/core/sys.d \
./Middlewares/Third_Party/lwip/src/core/tcp.d \
./Middlewares/Third_Party/lwip/src/core/tcp_in.d \
./Middlewares/Third_Party/lwip/src/core/tcp_out.d \
./Middlewares/Third_Party/lwip/src/core/timers.d \
./Middlewares/Third_Party/lwip/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/core/%.o Middlewares/Third_Party/lwip/src/core/%.su: ../Middlewares/Third_Party/lwip/src/core/%.c Middlewares/Third_Party/lwip/src/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DUSE_MBED_TLS -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/B-L4S5I-IOT01" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/Components/Common" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/Components/es_wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/Components/hts221" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Drivers/BSP/Components/st25dv" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/Wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/lwip/src/include" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/lwip/src/include/ipv4" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/Network/Wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/Network" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/MQTT" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Middlewares/Third_Party/mbedTLS/include" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/Security" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuthSaveInFlash/Core/Memory" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core:
	-$(RM) ./Middlewares/Third_Party/lwip/src/core/def.d ./Middlewares/Third_Party/lwip/src/core/def.o ./Middlewares/Third_Party/lwip/src/core/def.su ./Middlewares/Third_Party/lwip/src/core/dhcp.d ./Middlewares/Third_Party/lwip/src/core/dhcp.o ./Middlewares/Third_Party/lwip/src/core/dhcp.su ./Middlewares/Third_Party/lwip/src/core/dns.d ./Middlewares/Third_Party/lwip/src/core/dns.o ./Middlewares/Third_Party/lwip/src/core/dns.su ./Middlewares/Third_Party/lwip/src/core/init.d ./Middlewares/Third_Party/lwip/src/core/init.o ./Middlewares/Third_Party/lwip/src/core/init.su ./Middlewares/Third_Party/lwip/src/core/mem.d ./Middlewares/Third_Party/lwip/src/core/mem.o ./Middlewares/Third_Party/lwip/src/core/mem.su ./Middlewares/Third_Party/lwip/src/core/memp.d ./Middlewares/Third_Party/lwip/src/core/memp.o ./Middlewares/Third_Party/lwip/src/core/memp.su ./Middlewares/Third_Party/lwip/src/core/netif.d ./Middlewares/Third_Party/lwip/src/core/netif.o ./Middlewares/Third_Party/lwip/src/core/netif.su ./Middlewares/Third_Party/lwip/src/core/pbuf.d ./Middlewares/Third_Party/lwip/src/core/pbuf.o ./Middlewares/Third_Party/lwip/src/core/pbuf.su ./Middlewares/Third_Party/lwip/src/core/raw.d ./Middlewares/Third_Party/lwip/src/core/raw.o ./Middlewares/Third_Party/lwip/src/core/raw.su ./Middlewares/Third_Party/lwip/src/core/stats.d ./Middlewares/Third_Party/lwip/src/core/stats.o ./Middlewares/Third_Party/lwip/src/core/stats.su ./Middlewares/Third_Party/lwip/src/core/sys.d ./Middlewares/Third_Party/lwip/src/core/sys.o ./Middlewares/Third_Party/lwip/src/core/sys.su ./Middlewares/Third_Party/lwip/src/core/tcp.d ./Middlewares/Third_Party/lwip/src/core/tcp.o ./Middlewares/Third_Party/lwip/src/core/tcp.su ./Middlewares/Third_Party/lwip/src/core/tcp_in.d ./Middlewares/Third_Party/lwip/src/core/tcp_in.o ./Middlewares/Third_Party/lwip/src/core/tcp_in.su ./Middlewares/Third_Party/lwip/src/core/tcp_out.d ./Middlewares/Third_Party/lwip/src/core/tcp_out.o ./Middlewares/Third_Party/lwip/src/core/tcp_out.su ./Middlewares/Third_Party/lwip/src/core/timers.d ./Middlewares/Third_Party/lwip/src/core/timers.o ./Middlewares/Third_Party/lwip/src/core/timers.su ./Middlewares/Third_Party/lwip/src/core/udp.d ./Middlewares/Third_Party/lwip/src/core/udp.o ./Middlewares/Third_Party/lwip/src/core/udp.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core

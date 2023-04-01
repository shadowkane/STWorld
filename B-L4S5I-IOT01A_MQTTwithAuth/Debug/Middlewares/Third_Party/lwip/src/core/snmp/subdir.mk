################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/core/snmp/asn1_dec.c \
../Middlewares/Third_Party/lwip/src/core/snmp/asn1_enc.c \
../Middlewares/Third_Party/lwip/src/core/snmp/mib2.c \
../Middlewares/Third_Party/lwip/src/core/snmp/mib_structs.c \
../Middlewares/Third_Party/lwip/src/core/snmp/msg_in.c \
../Middlewares/Third_Party/lwip/src/core/snmp/msg_out.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/core/snmp/asn1_dec.o \
./Middlewares/Third_Party/lwip/src/core/snmp/asn1_enc.o \
./Middlewares/Third_Party/lwip/src/core/snmp/mib2.o \
./Middlewares/Third_Party/lwip/src/core/snmp/mib_structs.o \
./Middlewares/Third_Party/lwip/src/core/snmp/msg_in.o \
./Middlewares/Third_Party/lwip/src/core/snmp/msg_out.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/core/snmp/asn1_dec.d \
./Middlewares/Third_Party/lwip/src/core/snmp/asn1_enc.d \
./Middlewares/Third_Party/lwip/src/core/snmp/mib2.d \
./Middlewares/Third_Party/lwip/src/core/snmp/mib_structs.d \
./Middlewares/Third_Party/lwip/src/core/snmp/msg_in.d \
./Middlewares/Third_Party/lwip/src/core/snmp/msg_out.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/core/snmp/%.o Middlewares/Third_Party/lwip/src/core/snmp/%.su: ../Middlewares/Third_Party/lwip/src/core/snmp/%.c Middlewares/Third_Party/lwip/src/core/snmp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -DUSE_MBED_TLS -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/B-L4S5I-IOT01" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/Components/Common" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/Components/es_wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/Components/hts221" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Drivers/BSP/Components/st25dv" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/Wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/lwip/src/include" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/lwip/src/include/ipv4" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/Network/Wifi" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/Network" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/MQTT" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Middlewares/Third_Party/mbedTLS/include" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/Security" -I"C:/Users/shado/Data/Projects/Embedded/STM/ST workspaces/workspace_test/B-L4S5I-IOT01A_MQTTwithAuth/Core/Memory" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-snmp

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-snmp:
	-$(RM) ./Middlewares/Third_Party/lwip/src/core/snmp/asn1_dec.d ./Middlewares/Third_Party/lwip/src/core/snmp/asn1_dec.o ./Middlewares/Third_Party/lwip/src/core/snmp/asn1_dec.su ./Middlewares/Third_Party/lwip/src/core/snmp/asn1_enc.d ./Middlewares/Third_Party/lwip/src/core/snmp/asn1_enc.o ./Middlewares/Third_Party/lwip/src/core/snmp/asn1_enc.su ./Middlewares/Third_Party/lwip/src/core/snmp/mib2.d ./Middlewares/Third_Party/lwip/src/core/snmp/mib2.o ./Middlewares/Third_Party/lwip/src/core/snmp/mib2.su ./Middlewares/Third_Party/lwip/src/core/snmp/mib_structs.d ./Middlewares/Third_Party/lwip/src/core/snmp/mib_structs.o ./Middlewares/Third_Party/lwip/src/core/snmp/mib_structs.su ./Middlewares/Third_Party/lwip/src/core/snmp/msg_in.d ./Middlewares/Third_Party/lwip/src/core/snmp/msg_in.o ./Middlewares/Third_Party/lwip/src/core/snmp/msg_in.su ./Middlewares/Third_Party/lwip/src/core/snmp/msg_out.d ./Middlewares/Third_Party/lwip/src/core/snmp/msg_out.o ./Middlewares/Third_Party/lwip/src/core/snmp/msg_out.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-snmp

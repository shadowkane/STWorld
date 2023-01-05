################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/netif/ppp/auth.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/chap.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/chpms.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/fsm.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/ipcp.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/lcp.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/magic.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/md5.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/pap.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/ppp.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/ppp_oe.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/randm.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/vj.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/netif/ppp/auth.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/chap.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/chpms.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/fsm.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/ipcp.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/lcp.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/magic.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/md5.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/pap.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/ppp.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/ppp_oe.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/randm.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/vj.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/netif/ppp/auth.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/chap.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/chpms.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/fsm.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/ipcp.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/lcp.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/magic.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/md5.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/pap.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/ppp.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/ppp_oe.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/randm.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/netif/ppp/%.o Middlewares/Third_Party/lwip/src/netif/ppp/%.su: ../Middlewares/Third_Party/lwip/src/netif/ppp/%.c Middlewares/Third_Party/lwip/src/netif/ppp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include/ipv4" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif-2f-ppp

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif-2f-ppp:
	-$(RM) ./Middlewares/Third_Party/lwip/src/netif/ppp/auth.d ./Middlewares/Third_Party/lwip/src/netif/ppp/auth.o ./Middlewares/Third_Party/lwip/src/netif/ppp/auth.su ./Middlewares/Third_Party/lwip/src/netif/ppp/chap.d ./Middlewares/Third_Party/lwip/src/netif/ppp/chap.o ./Middlewares/Third_Party/lwip/src/netif/ppp/chap.su ./Middlewares/Third_Party/lwip/src/netif/ppp/chpms.d ./Middlewares/Third_Party/lwip/src/netif/ppp/chpms.o ./Middlewares/Third_Party/lwip/src/netif/ppp/chpms.su ./Middlewares/Third_Party/lwip/src/netif/ppp/fsm.d ./Middlewares/Third_Party/lwip/src/netif/ppp/fsm.o ./Middlewares/Third_Party/lwip/src/netif/ppp/fsm.su ./Middlewares/Third_Party/lwip/src/netif/ppp/ipcp.d ./Middlewares/Third_Party/lwip/src/netif/ppp/ipcp.o ./Middlewares/Third_Party/lwip/src/netif/ppp/ipcp.su ./Middlewares/Third_Party/lwip/src/netif/ppp/lcp.d ./Middlewares/Third_Party/lwip/src/netif/ppp/lcp.o ./Middlewares/Third_Party/lwip/src/netif/ppp/lcp.su ./Middlewares/Third_Party/lwip/src/netif/ppp/magic.d ./Middlewares/Third_Party/lwip/src/netif/ppp/magic.o ./Middlewares/Third_Party/lwip/src/netif/ppp/magic.su ./Middlewares/Third_Party/lwip/src/netif/ppp/md5.d ./Middlewares/Third_Party/lwip/src/netif/ppp/md5.o ./Middlewares/Third_Party/lwip/src/netif/ppp/md5.su ./Middlewares/Third_Party/lwip/src/netif/ppp/pap.d ./Middlewares/Third_Party/lwip/src/netif/ppp/pap.o ./Middlewares/Third_Party/lwip/src/netif/ppp/pap.su ./Middlewares/Third_Party/lwip/src/netif/ppp/ppp.d ./Middlewares/Third_Party/lwip/src/netif/ppp/ppp.o ./Middlewares/Third_Party/lwip/src/netif/ppp/ppp.su ./Middlewares/Third_Party/lwip/src/netif/ppp/ppp_oe.d ./Middlewares/Third_Party/lwip/src/netif/ppp/ppp_oe.o ./Middlewares/Third_Party/lwip/src/netif/ppp/ppp_oe.su ./Middlewares/Third_Party/lwip/src/netif/ppp/randm.d ./Middlewares/Third_Party/lwip/src/netif/ppp/randm.o ./Middlewares/Third_Party/lwip/src/netif/ppp/randm.su ./Middlewares/Third_Party/lwip/src/netif/ppp/vj.d ./Middlewares/Third_Party/lwip/src/netif/ppp/vj.o ./Middlewares/Third_Party/lwip/src/netif/ppp/vj.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif-2f-ppp


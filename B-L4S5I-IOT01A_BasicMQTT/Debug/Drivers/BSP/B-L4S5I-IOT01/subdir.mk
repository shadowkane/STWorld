################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01.c \
../Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_hsensor.c \
../Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_tsensor.c 

OBJS += \
./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01.o \
./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_hsensor.o \
./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_tsensor.o 

C_DEPS += \
./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01.d \
./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_hsensor.d \
./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_tsensor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/B-L4S5I-IOT01/%.o Drivers/BSP/B-L4S5I-IOT01/%.su: ../Drivers/BSP/B-L4S5I-IOT01/%.c Drivers/BSP/B-L4S5I-IOT01/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' -DUSE_HAL_DRIVER -DSTM32L4S5xx -DUSE_WIFI -DENABLE_IOT_WARN -DENABLE_IOT_INFO -DENABLE_IOT_ERROR -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/lwip/src/include/ipv4" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTPacket/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Middlewares/Third_Party/paho.mqtt.embedded-c/MQTTClient-C/src" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L4S5I-IOT01A_BasicMQTT/Core/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-B-2d-L4S5I-2d-IOT01

clean-Drivers-2f-BSP-2f-B-2d-L4S5I-2d-IOT01:
	-$(RM) ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01.d ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01.o ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01.su ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_hsensor.d ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_hsensor.o ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_hsensor.su ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_tsensor.d ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_tsensor.o ./Drivers/BSP/B-L4S5I-IOT01/stm32l4s5i_iot01_tsensor.su

.PHONY: clean-Drivers-2f-BSP-2f-B-2d-L4S5I-2d-IOT01


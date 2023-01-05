################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/Network/c2c_net.c \
../Middlewares/Third_Party/Network/lwip_net.c \
../Middlewares/Third_Party/Network/net.c \
../Middlewares/Third_Party/Network/net_tcp_c2c.c \
../Middlewares/Third_Party/Network/net_tcp_lwip.c \
../Middlewares/Third_Party/Network/net_tcp_wifi.c \
../Middlewares/Third_Party/Network/net_tls_mbedtls.c \
../Middlewares/Third_Party/Network/wifi_net.c 

OBJS += \
./Middlewares/Third_Party/Network/c2c_net.o \
./Middlewares/Third_Party/Network/lwip_net.o \
./Middlewares/Third_Party/Network/net.o \
./Middlewares/Third_Party/Network/net_tcp_c2c.o \
./Middlewares/Third_Party/Network/net_tcp_lwip.o \
./Middlewares/Third_Party/Network/net_tcp_wifi.o \
./Middlewares/Third_Party/Network/net_tls_mbedtls.o \
./Middlewares/Third_Party/Network/wifi_net.o 

C_DEPS += \
./Middlewares/Third_Party/Network/c2c_net.d \
./Middlewares/Third_Party/Network/lwip_net.d \
./Middlewares/Third_Party/Network/net.d \
./Middlewares/Third_Party/Network/net_tcp_c2c.d \
./Middlewares/Third_Party/Network/net_tcp_lwip.d \
./Middlewares/Third_Party/Network/net_tcp_wifi.d \
./Middlewares/Third_Party/Network/net_tls_mbedtls.d \
./Middlewares/Third_Party/Network/wifi_net.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/Network/%.o Middlewares/Third_Party/Network/%.su: ../Middlewares/Third_Party/Network/%.c Middlewares/Third_Party/Network/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/lwip/src/include" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/lwip/src/include/ipv4" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-Network

clean-Middlewares-2f-Third_Party-2f-Network:
	-$(RM) ./Middlewares/Third_Party/Network/c2c_net.d ./Middlewares/Third_Party/Network/c2c_net.o ./Middlewares/Third_Party/Network/c2c_net.su ./Middlewares/Third_Party/Network/lwip_net.d ./Middlewares/Third_Party/Network/lwip_net.o ./Middlewares/Third_Party/Network/lwip_net.su ./Middlewares/Third_Party/Network/net.d ./Middlewares/Third_Party/Network/net.o ./Middlewares/Third_Party/Network/net.su ./Middlewares/Third_Party/Network/net_tcp_c2c.d ./Middlewares/Third_Party/Network/net_tcp_c2c.o ./Middlewares/Third_Party/Network/net_tcp_c2c.su ./Middlewares/Third_Party/Network/net_tcp_lwip.d ./Middlewares/Third_Party/Network/net_tcp_lwip.o ./Middlewares/Third_Party/Network/net_tcp_lwip.su ./Middlewares/Third_Party/Network/net_tcp_wifi.d ./Middlewares/Third_Party/Network/net_tcp_wifi.o ./Middlewares/Third_Party/Network/net_tcp_wifi.su ./Middlewares/Third_Party/Network/net_tls_mbedtls.d ./Middlewares/Third_Party/Network/net_tls_mbedtls.o ./Middlewares/Third_Party/Network/net_tls_mbedtls.su ./Middlewares/Third_Party/Network/wifi_net.d ./Middlewares/Third_Party/Network/wifi_net.o ./Middlewares/Third_Party/Network/wifi_net.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-Network


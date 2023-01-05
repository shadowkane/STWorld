################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/core/ipv6/icmp6.c \
../Middlewares/Third_Party/lwip/src/core/ipv6/inet6.c \
../Middlewares/Third_Party/lwip/src/core/ipv6/ip6.c \
../Middlewares/Third_Party/lwip/src/core/ipv6/ip6_addr.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/core/ipv6/icmp6.o \
./Middlewares/Third_Party/lwip/src/core/ipv6/inet6.o \
./Middlewares/Third_Party/lwip/src/core/ipv6/ip6.o \
./Middlewares/Third_Party/lwip/src/core/ipv6/ip6_addr.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/core/ipv6/icmp6.d \
./Middlewares/Third_Party/lwip/src/core/ipv6/inet6.d \
./Middlewares/Third_Party/lwip/src/core/ipv6/ip6.d \
./Middlewares/Third_Party/lwip/src/core/ipv6/ip6_addr.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/core/ipv6/%.o Middlewares/Third_Party/lwip/src/core/ipv6/%.su: ../Middlewares/Third_Party/lwip/src/core/ipv6/%.c Middlewares/Third_Party/lwip/src/core/ipv6/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/lwip/src/include" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/lwip/port/B-L5SI-IOT01A" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/lwip/src/include/ipv4" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-ipv6

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-ipv6:
	-$(RM) ./Middlewares/Third_Party/lwip/src/core/ipv6/icmp6.d ./Middlewares/Third_Party/lwip/src/core/ipv6/icmp6.o ./Middlewares/Third_Party/lwip/src/core/ipv6/icmp6.su ./Middlewares/Third_Party/lwip/src/core/ipv6/inet6.d ./Middlewares/Third_Party/lwip/src/core/ipv6/inet6.o ./Middlewares/Third_Party/lwip/src/core/ipv6/inet6.su ./Middlewares/Third_Party/lwip/src/core/ipv6/ip6.d ./Middlewares/Third_Party/lwip/src/core/ipv6/ip6.o ./Middlewares/Third_Party/lwip/src/core/ipv6/ip6.su ./Middlewares/Third_Party/lwip/src/core/ipv6/ip6_addr.d ./Middlewares/Third_Party/lwip/src/core/ipv6/ip6_addr.o ./Middlewares/Third_Party/lwip/src/core/ipv6/ip6_addr.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core-2f-ipv6


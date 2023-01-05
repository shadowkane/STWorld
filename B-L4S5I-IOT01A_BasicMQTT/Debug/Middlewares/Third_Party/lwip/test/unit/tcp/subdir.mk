################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/test/unit/tcp/tcp_helper.c \
../Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp.c \
../Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp_oos.c 

OBJS += \
./Middlewares/Third_Party/lwip/test/unit/tcp/tcp_helper.o \
./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp.o \
./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp_oos.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/test/unit/tcp/tcp_helper.d \
./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp.d \
./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp_oos.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/test/unit/tcp/%.o Middlewares/Third_Party/lwip/test/unit/tcp/%.su: ../Middlewares/Third_Party/lwip/test/unit/tcp/%.c Middlewares/Third_Party/lwip/test/unit/tcp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-test-2f-unit-2f-tcp

clean-Middlewares-2f-Third_Party-2f-lwip-2f-test-2f-unit-2f-tcp:
	-$(RM) ./Middlewares/Third_Party/lwip/test/unit/tcp/tcp_helper.d ./Middlewares/Third_Party/lwip/test/unit/tcp/tcp_helper.o ./Middlewares/Third_Party/lwip/test/unit/tcp/tcp_helper.su ./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp.d ./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp.o ./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp.su ./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp_oos.d ./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp_oos.o ./Middlewares/Third_Party/lwip/test/unit/tcp/test_tcp_oos.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-test-2f-unit-2f-tcp


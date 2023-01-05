################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/test/unit/etharp/test_etharp.c 

OBJS += \
./Middlewares/Third_Party/lwip/test/unit/etharp/test_etharp.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/test/unit/etharp/test_etharp.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/test/unit/etharp/%.o Middlewares/Third_Party/lwip/test/unit/etharp/%.su: ../Middlewares/Third_Party/lwip/test/unit/etharp/%.c Middlewares/Third_Party/lwip/test/unit/etharp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/Common" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/es_wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/hts221" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Drivers/BSP/Components/st25dv" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/Network" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/Wifi" -I"E:/Projects/Embedded system/STM drivers and examples/ST workspaces/workspace_test/B-L5SI-IOT01A_LwIP/Middlewares/Third_Party/lwip/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-test-2f-unit-2f-etharp

clean-Middlewares-2f-Third_Party-2f-lwip-2f-test-2f-unit-2f-etharp:
	-$(RM) ./Middlewares/Third_Party/lwip/test/unit/etharp/test_etharp.d ./Middlewares/Third_Party/lwip/test/unit/etharp/test_etharp.o ./Middlewares/Third_Party/lwip/test/unit/etharp/test_etharp.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-test-2f-unit-2f-etharp


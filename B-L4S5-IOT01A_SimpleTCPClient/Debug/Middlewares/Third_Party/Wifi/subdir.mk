################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/Wifi/wifi.c 

OBJS += \
./Middlewares/Third_Party/Wifi/wifi.o 

C_DEPS += \
./Middlewares/Third_Party/Wifi/wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/Wifi/%.o Middlewares/Third_Party/Wifi/%.su: ../Middlewares/Third_Party/Wifi/%.c Middlewares/Third_Party/Wifi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/Components/Common" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/Components/es_wifi" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/Components/hts221" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/Components/st25dv" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Middlewares/Third_Party/Wifi" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-Wifi

clean-Middlewares-2f-Third_Party-2f-Wifi:
	-$(RM) ./Middlewares/Third_Party/Wifi/wifi.d ./Middlewares/Third_Party/Wifi/wifi.o ./Middlewares/Third_Party/Wifi/wifi.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-Wifi


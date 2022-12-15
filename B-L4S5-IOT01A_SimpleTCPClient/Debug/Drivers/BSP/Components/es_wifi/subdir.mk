################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/es_wifi/es_wifi.c 

OBJS += \
./Drivers/BSP/Components/es_wifi/es_wifi.o 

C_DEPS += \
./Drivers/BSP/Components/es_wifi/es_wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/es_wifi/%.o Drivers/BSP/Components/es_wifi/%.su: ../Drivers/BSP/Components/es_wifi/%.c Drivers/BSP/Components/es_wifi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/B-L4S5I-IOT01" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/Components/Common" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/Components/es_wifi" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/Components/hts221" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Drivers/BSP/Components/st25dv" -I"E:/Projects/GitHub/STWorld/B-L4S5-IOT01A_SimpleTCPClient/Middlewares/Third_Party/Wifi" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-es_wifi

clean-Drivers-2f-BSP-2f-Components-2f-es_wifi:
	-$(RM) ./Drivers/BSP/Components/es_wifi/es_wifi.d ./Drivers/BSP/Components/es_wifi/es_wifi.o ./Drivers/BSP/Components/es_wifi/es_wifi.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-es_wifi


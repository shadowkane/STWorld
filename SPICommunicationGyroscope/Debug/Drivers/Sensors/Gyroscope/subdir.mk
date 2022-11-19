################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Sensors/Gyroscope/Gyroscope_l3gd20.c 

OBJS += \
./Drivers/Sensors/Gyroscope/Gyroscope_l3gd20.o 

C_DEPS += \
./Drivers/Sensors/Gyroscope/Gyroscope_l3gd20.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Sensors/Gyroscope/%.o Drivers/Sensors/Gyroscope/%.su: ../Drivers/Sensors/Gyroscope/%.c Drivers/Sensors/Gyroscope/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"C:/Users/shado/STM32CubeIDE/workspace_1.10.1/SPICommunicationGyroscope/Drivers/Sensors" -I"C:/Users/shado/STM32CubeIDE/workspace_1.10.1/SPICommunicationGyroscope/Drivers/Sensors/Gyroscope" -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Sensors-2f-Gyroscope

clean-Drivers-2f-Sensors-2f-Gyroscope:
	-$(RM) ./Drivers/Sensors/Gyroscope/Gyroscope_l3gd20.d ./Drivers/Sensors/Gyroscope/Gyroscope_l3gd20.o ./Drivers/Sensors/Gyroscope/Gyroscope_l3gd20.su

.PHONY: clean-Drivers-2f-Sensors-2f-Gyroscope


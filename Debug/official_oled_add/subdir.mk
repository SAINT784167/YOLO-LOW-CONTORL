################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../official_oled_add/oled.c 

OBJS += \
./official_oled_add/oled.o 

C_DEPS += \
./official_oled_add/oled.d 


# Each subdirectory must supply rules for building sources it contributes
official_oled_add/%.o official_oled_add/%.su official_oled_add/%.cyclo: ../official_oled_add/%.c official_oled_add/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../official_oled_add -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-official_oled_add

clean-official_oled_add:
	-$(RM) ./official_oled_add/oled.cyclo ./official_oled_add/oled.d ./official_oled_add/oled.o ./official_oled_add/oled.su

.PHONY: clean-official_oled_add


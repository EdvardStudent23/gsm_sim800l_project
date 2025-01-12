################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/sim800l_lib/src/sim800l.c 

OBJS += \
./Libraries/sim800l_lib/src/sim800l.o 

C_DEPS += \
./Libraries/sim800l_lib/src/sim800l.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/sim800l_lib/src/%.o Libraries/sim800l_lib/src/%.su Libraries/sim800l_lib/src/%.cyclo: ../Libraries/sim800l_lib/src/%.c Libraries/sim800l_lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Libraries/sim800l_lib/inc -I../Libraries/sim800l_lib/config -I../Core/Inc/lcd5110 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-sim800l_lib-2f-src

clean-Libraries-2f-sim800l_lib-2f-src:
	-$(RM) ./Libraries/sim800l_lib/src/sim800l.cyclo ./Libraries/sim800l_lib/src/sim800l.d ./Libraries/sim800l_lib/src/sim800l.o ./Libraries/sim800l_lib/src/sim800l.su

.PHONY: clean-Libraries-2f-sim800l_lib-2f-src


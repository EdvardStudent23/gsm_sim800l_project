################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/lcd5110_lib/src/lcd5110.c \
../Libraries/lcd5110_lib/src/lcd5110_hal.c \
../Libraries/lcd5110_lib/src/lcd5110_ll.c 

OBJS += \
./Libraries/lcd5110_lib/src/lcd5110.o \
./Libraries/lcd5110_lib/src/lcd5110_hal.o \
./Libraries/lcd5110_lib/src/lcd5110_ll.o 

C_DEPS += \
./Libraries/lcd5110_lib/src/lcd5110.d \
./Libraries/lcd5110_lib/src/lcd5110_hal.d \
./Libraries/lcd5110_lib/src/lcd5110_ll.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/lcd5110_lib/src/%.o Libraries/lcd5110_lib/src/%.su Libraries/lcd5110_lib/src/%.cyclo: ../Libraries/lcd5110_lib/src/%.c Libraries/lcd5110_lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Libraries/sim800l_lib/inc -I../Libraries/sim800l_lib/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-lcd5110_lib-2f-src

clean-Libraries-2f-lcd5110_lib-2f-src:
	-$(RM) ./Libraries/lcd5110_lib/src/lcd5110.cyclo ./Libraries/lcd5110_lib/src/lcd5110.d ./Libraries/lcd5110_lib/src/lcd5110.o ./Libraries/lcd5110_lib/src/lcd5110.su ./Libraries/lcd5110_lib/src/lcd5110_hal.cyclo ./Libraries/lcd5110_lib/src/lcd5110_hal.d ./Libraries/lcd5110_lib/src/lcd5110_hal.o ./Libraries/lcd5110_lib/src/lcd5110_hal.su ./Libraries/lcd5110_lib/src/lcd5110_ll.cyclo ./Libraries/lcd5110_lib/src/lcd5110_ll.d ./Libraries/lcd5110_lib/src/lcd5110_ll.o ./Libraries/lcd5110_lib/src/lcd5110_ll.su

.PHONY: clean-Libraries-2f-lcd5110_lib-2f-src


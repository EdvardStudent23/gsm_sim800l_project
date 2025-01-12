################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/lcd5110/lcd5110.c \
../Core/Src/lcd5110/lcd5110_hal.c \
../Core/Src/lcd5110/lcd5110_ll.c 

OBJS += \
./Core/Src/lcd5110/lcd5110.o \
./Core/Src/lcd5110/lcd5110_hal.o \
./Core/Src/lcd5110/lcd5110_ll.o 

C_DEPS += \
./Core/Src/lcd5110/lcd5110.d \
./Core/Src/lcd5110/lcd5110_hal.d \
./Core/Src/lcd5110/lcd5110_ll.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/lcd5110/%.o Core/Src/lcd5110/%.su Core/Src/lcd5110/%.cyclo: ../Core/Src/lcd5110/%.c Core/Src/lcd5110/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Libraries/sim800l_lib/inc -I../Libraries/sim800l_lib/config -I../Core/Inc/lcd5110 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-lcd5110

clean-Core-2f-Src-2f-lcd5110:
	-$(RM) ./Core/Src/lcd5110/lcd5110.cyclo ./Core/Src/lcd5110/lcd5110.d ./Core/Src/lcd5110/lcd5110.o ./Core/Src/lcd5110/lcd5110.su ./Core/Src/lcd5110/lcd5110_hal.cyclo ./Core/Src/lcd5110/lcd5110_hal.d ./Core/Src/lcd5110/lcd5110_hal.o ./Core/Src/lcd5110/lcd5110_hal.su ./Core/Src/lcd5110/lcd5110_ll.cyclo ./Core/Src/lcd5110/lcd5110_ll.d ./Core/Src/lcd5110/lcd5110_ll.o ./Core/Src/lcd5110/lcd5110_ll.su

.PHONY: clean-Core-2f-Src-2f-lcd5110


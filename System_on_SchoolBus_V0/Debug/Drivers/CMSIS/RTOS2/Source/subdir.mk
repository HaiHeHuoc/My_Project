################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/RTOS2/Source/os_systick.c \
../Drivers/CMSIS/RTOS2/Source/os_tick_gtim.c \
../Drivers/CMSIS/RTOS2/Source/os_tick_ptim.c 

OBJS += \
./Drivers/CMSIS/RTOS2/Source/os_systick.o \
./Drivers/CMSIS/RTOS2/Source/os_tick_gtim.o \
./Drivers/CMSIS/RTOS2/Source/os_tick_ptim.o 

C_DEPS += \
./Drivers/CMSIS/RTOS2/Source/os_systick.d \
./Drivers/CMSIS/RTOS2/Source/os_tick_gtim.d \
./Drivers/CMSIS/RTOS2/Source/os_tick_ptim.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/RTOS2/Source/%.o: ../Drivers/CMSIS/RTOS2/Source/%.c Drivers/CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


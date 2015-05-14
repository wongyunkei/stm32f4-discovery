################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/newlib_stubs.c \
../startup/system_stm32f4xx.c 

CPP_SRCS += \
../startup/LibraryHacks.cpp 

S_UPPER_SRCS += \
../startup/startup_stm32f40_41xxx.S 

OBJS += \
./startup/LibraryHacks.o \
./startup/newlib_stubs.o \
./startup/startup_stm32f40_41xxx.o \
./startup/system_stm32f4xx.o 

S_UPPER_DEPS += \
./startup/startup_stm32f40_41xxx.d 

C_DEPS += \
./startup/newlib_stubs.d \
./startup/system_stm32f4xx.d 

CPP_DEPS += \
./startup/LibraryHacks.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DSTM32F40_41xxx=STM32F40_41xxx -DUSE_STDPERIPH_DRIVER=USE_STDPERIPH_DRIVER -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\STM32F4xx_StdPeriph_Driver\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\CMSIS\Include" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DSTM32F40_41xxx=STM32F40_41xxx -DUSE_STDPERIPH_DRIVER=USE_STDPERIPH_DRIVER -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\STM32F4xx_StdPeriph_Driver\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\CMSIS\Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/%.o: ../startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -x assembler-with-cpp -DSTM32F40_41xxx=STM32F40_41xxx -DUSE_STDPERIPH_DRIVER=USE_STDPERIPH_DRIVER -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\STM32F4xx_StdPeriph_Driver\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\CMSIS\Include" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



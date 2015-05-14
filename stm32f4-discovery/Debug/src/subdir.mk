################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Acceleration.cpp \
../src/AdditionalTools.cpp \
../src/Battery.cpp \
../src/Communicating.cpp \
../src/Controlling.cpp \
../src/Delay.cpp \
../src/I2C.cpp \
../src/Kalman.cpp \
../src/Leds.cpp \
../src/MPU6050.cpp \
../src/Main.cpp \
../src/MathAlgorithm.cpp \
../src/MathTools.cpp \
../src/MovingWindowAverageFilter.cpp \
../src/NRF905.cpp \
../src/Omega.cpp \
../src/PWM.cpp \
../src/PhasesMonitoring.cpp \
../src/Pid.cpp \
../src/Quaternion.cpp \
../src/Sonic.cpp \
../src/Spi.cpp \
../src/Task.cpp \
../src/Ticks.cpp \
../src/UKF.cpp \
../src/URG_04LX.cpp \
../src/Usart.cpp 

OBJS += \
./src/Acceleration.o \
./src/AdditionalTools.o \
./src/Battery.o \
./src/Communicating.o \
./src/Controlling.o \
./src/Delay.o \
./src/I2C.o \
./src/Kalman.o \
./src/Leds.o \
./src/MPU6050.o \
./src/Main.o \
./src/MathAlgorithm.o \
./src/MathTools.o \
./src/MovingWindowAverageFilter.o \
./src/NRF905.o \
./src/Omega.o \
./src/PWM.o \
./src/PhasesMonitoring.o \
./src/Pid.o \
./src/Quaternion.o \
./src/Sonic.o \
./src/Spi.o \
./src/Task.o \
./src/Ticks.o \
./src/UKF.o \
./src/URG_04LX.o \
./src/Usart.o 

CPP_DEPS += \
./src/Acceleration.d \
./src/AdditionalTools.d \
./src/Battery.d \
./src/Communicating.d \
./src/Controlling.d \
./src/Delay.d \
./src/I2C.d \
./src/Kalman.d \
./src/Leds.d \
./src/MPU6050.d \
./src/Main.d \
./src/MathAlgorithm.d \
./src/MathTools.d \
./src/MovingWindowAverageFilter.d \
./src/NRF905.d \
./src/Omega.d \
./src/PWM.d \
./src/PhasesMonitoring.d \
./src/Pid.d \
./src/Quaternion.d \
./src/Sonic.d \
./src/Spi.d \
./src/Task.d \
./src/Ticks.d \
./src/UKF.d \
./src/URG_04LX.d \
./src/Usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DSTM32F40_41xxx=STM32F40_41xxx -DUSE_STDPERIPH_DRIVER=USE_STDPERIPH_DRIVER -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\STM32F4xx_StdPeriph_Driver\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\inc" -I"C:\Users\YunKei\Documents\Research\workspace\stm32f4-discovery\CMSIS\Include" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



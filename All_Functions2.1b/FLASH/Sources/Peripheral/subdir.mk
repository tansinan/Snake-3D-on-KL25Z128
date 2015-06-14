################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Peripheral/ADC.c" \
"../Sources/Peripheral/Function.c" \
"../Sources/Peripheral/MMA8451Q.c" \
"../Sources/Peripheral/Music.c" \
"../Sources/Peripheral/OLED.c" \
"../Sources/Peripheral/SMG.c" \
"../Sources/Peripheral/UART.c" \
"../Sources/Peripheral/menu.c" \
"../Sources/Peripheral/sa_mtb.c" \

C_SRCS += \
../Sources/Peripheral/ADC.c \
../Sources/Peripheral/Function.c \
../Sources/Peripheral/MMA8451Q.c \
../Sources/Peripheral/Music.c \
../Sources/Peripheral/OLED.c \
../Sources/Peripheral/SMG.c \
../Sources/Peripheral/UART.c \
../Sources/Peripheral/menu.c \
../Sources/Peripheral/sa_mtb.c \

OBJS += \
./Sources/Peripheral/ADC.o \
./Sources/Peripheral/Function.o \
./Sources/Peripheral/MMA8451Q.o \
./Sources/Peripheral/Music.o \
./Sources/Peripheral/OLED.o \
./Sources/Peripheral/SMG.o \
./Sources/Peripheral/UART.o \
./Sources/Peripheral/menu.o \
./Sources/Peripheral/sa_mtb.o \

C_DEPS += \
./Sources/Peripheral/ADC.d \
./Sources/Peripheral/Function.d \
./Sources/Peripheral/MMA8451Q.d \
./Sources/Peripheral/Music.d \
./Sources/Peripheral/OLED.d \
./Sources/Peripheral/SMG.d \
./Sources/Peripheral/UART.d \
./Sources/Peripheral/menu.d \
./Sources/Peripheral/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/Peripheral/ADC.o" \
"./Sources/Peripheral/Function.o" \
"./Sources/Peripheral/MMA8451Q.o" \
"./Sources/Peripheral/Music.o" \
"./Sources/Peripheral/OLED.o" \
"./Sources/Peripheral/SMG.o" \
"./Sources/Peripheral/UART.o" \
"./Sources/Peripheral/menu.o" \
"./Sources/Peripheral/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/Peripheral/ADC.d" \
"./Sources/Peripheral/Function.d" \
"./Sources/Peripheral/MMA8451Q.d" \
"./Sources/Peripheral/Music.d" \
"./Sources/Peripheral/OLED.d" \
"./Sources/Peripheral/SMG.d" \
"./Sources/Peripheral/UART.d" \
"./Sources/Peripheral/menu.d" \
"./Sources/Peripheral/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/Peripheral/ADC.o \
./Sources/Peripheral/Function.o \
./Sources/Peripheral/MMA8451Q.o \
./Sources/Peripheral/Music.o \
./Sources/Peripheral/OLED.o \
./Sources/Peripheral/SMG.o \
./Sources/Peripheral/UART.o \
./Sources/Peripheral/menu.o \
./Sources/Peripheral/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Peripheral/ADC.o: ../Sources/Peripheral/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Peripheral/Function.o: ../Sources/Peripheral/Function.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/Function.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/Function.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Peripheral/MMA8451Q.o: ../Sources/Peripheral/MMA8451Q.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/MMA8451Q.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/MMA8451Q.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Peripheral/Music.o: ../Sources/Peripheral/Music.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/Music.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/Music.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Peripheral/OLED.o: ../Sources/Peripheral/OLED.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/OLED.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/OLED.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Peripheral/SMG.o: ../Sources/Peripheral/SMG.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/SMG.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/SMG.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Peripheral/UART.o: ../Sources/Peripheral/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/UART.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Peripheral/menu.o: ../Sources/Peripheral/menu.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/menu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/menu.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Peripheral/sa_mtb.o: ../Sources/Peripheral/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Peripheral/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Peripheral/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '



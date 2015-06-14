################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC.c" \
"../Sources/DigitalTube.c" \
"../Sources/Light.c" \
"../Sources/Music.c" \
"../Sources/Timer.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/ADC.c \
../Sources/DigitalTube.c \
../Sources/Light.c \
../Sources/Music.c \
../Sources/Timer.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/ADC.o \
./Sources/DigitalTube.o \
./Sources/Light.o \
./Sources/Music.o \
./Sources/Timer.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/ADC.d \
./Sources/DigitalTube.d \
./Sources/Light.d \
./Sources/Music.d \
./Sources/Timer.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/ADC.o" \
"./Sources/DigitalTube.o" \
"./Sources/Light.o" \
"./Sources/Music.o" \
"./Sources/Timer.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/ADC.d" \
"./Sources/DigitalTube.d" \
"./Sources/Light.d" \
"./Sources/Music.d" \
"./Sources/Timer.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/ADC.o \
./Sources/DigitalTube.o \
./Sources/Light.o \
./Sources/Music.o \
./Sources/Timer.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC.o: ../Sources/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/DigitalTube.o: ../Sources/DigitalTube.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/DigitalTube.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/DigitalTube.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Light.o: ../Sources/Light.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Light.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Light.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Music.o: ../Sources/Music.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Music.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Music.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Timer.o: ../Sources/Timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Timer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Timer.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '



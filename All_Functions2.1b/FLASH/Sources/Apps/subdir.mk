################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Apps/AppFramework.c" \
"../Sources/Apps/AppSensorTest.c" \

C_SRCS += \
../Sources/Apps/AppFramework.c \
../Sources/Apps/AppSensorTest.c \

OBJS += \
./Sources/Apps/AppFramework.o \
./Sources/Apps/AppSensorTest.o \

C_DEPS += \
./Sources/Apps/AppFramework.d \
./Sources/Apps/AppSensorTest.d \

OBJS_QUOTED += \
"./Sources/Apps/AppFramework.o" \
"./Sources/Apps/AppSensorTest.o" \

C_DEPS_QUOTED += \
"./Sources/Apps/AppFramework.d" \
"./Sources/Apps/AppSensorTest.d" \

OBJS_OS_FORMAT += \
./Sources/Apps/AppFramework.o \
./Sources/Apps/AppSensorTest.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Apps/AppFramework.o: ../Sources/Apps/AppFramework.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Apps/AppFramework.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Apps/AppFramework.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Apps/AppSensorTest.o: ../Sources/Apps/AppSensorTest.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Apps/AppSensorTest.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Apps/AppSensorTest.o"
	@echo 'Finished building: $<'
	@echo ' '



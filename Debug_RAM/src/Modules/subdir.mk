################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/Modules/BLUETOOTH.c" \
"../src/Modules/MECANISM.c" \
"../src/Modules/WEIGHT.c" \

C_SRCS += \
../src/Modules/BLUETOOTH.c \
../src/Modules/MECANISM.c \
../src/Modules/WEIGHT.c \

OBJS_OS_FORMAT += \
./src/Modules/BLUETOOTH.o \
./src/Modules/MECANISM.o \
./src/Modules/WEIGHT.o \

C_DEPS_QUOTED += \
"./src/Modules/BLUETOOTH.d" \
"./src/Modules/MECANISM.d" \
"./src/Modules/WEIGHT.d" \

OBJS += \
./src/Modules/BLUETOOTH.o \
./src/Modules/MECANISM.o \
./src/Modules/WEIGHT.o \

OBJS_QUOTED += \
"./src/Modules/BLUETOOTH.o" \
"./src/Modules/MECANISM.o" \
"./src/Modules/WEIGHT.o" \

C_DEPS += \
./src/Modules/BLUETOOTH.d \
./src/Modules/MECANISM.d \
./src/Modules/WEIGHT.d \


# Each subdirectory must supply rules for building sources it contributes
src/Modules/BLUETOOTH.o: ../src/Modules/BLUETOOTH.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Modules/BLUETOOTH.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Modules/BLUETOOTH.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Modules/MECANISM.o: ../src/Modules/MECANISM.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Modules/MECANISM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Modules/MECANISM.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Modules/WEIGHT.o: ../src/Modules/WEIGHT.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Modules/WEIGHT.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Modules/WEIGHT.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '



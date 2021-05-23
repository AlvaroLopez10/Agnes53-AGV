################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/Functions/LINE_TRACKER.c" \
"../src/Functions/MANUAL.c" \
"../src/Functions/SEMIAUTOMATICO.c" \

C_SRCS += \
../src/Functions/LINE_TRACKER.c \
../src/Functions/MANUAL.c \
../src/Functions/SEMIAUTOMATICO.c \

OBJS_OS_FORMAT += \
./src/Functions/LINE_TRACKER.o \
./src/Functions/MANUAL.o \
./src/Functions/SEMIAUTOMATICO.o \

C_DEPS_QUOTED += \
"./src/Functions/LINE_TRACKER.d" \
"./src/Functions/MANUAL.d" \
"./src/Functions/SEMIAUTOMATICO.d" \

OBJS += \
./src/Functions/LINE_TRACKER.o \
./src/Functions/MANUAL.o \
./src/Functions/SEMIAUTOMATICO.o \

OBJS_QUOTED += \
"./src/Functions/LINE_TRACKER.o" \
"./src/Functions/MANUAL.o" \
"./src/Functions/SEMIAUTOMATICO.o" \

C_DEPS += \
./src/Functions/LINE_TRACKER.d \
./src/Functions/MANUAL.d \
./src/Functions/SEMIAUTOMATICO.d \


# Each subdirectory must supply rules for building sources it contributes
src/Functions/LINE_TRACKER.o: ../src/Functions/LINE_TRACKER.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Functions/LINE_TRACKER.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Functions/LINE_TRACKER.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Functions/MANUAL.o: ../src/Functions/MANUAL.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Functions/MANUAL.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Functions/MANUAL.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Functions/SEMIAUTOMATICO.o: ../src/Functions/SEMIAUTOMATICO.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Functions/SEMIAUTOMATICO.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Functions/SEMIAUTOMATICO.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '



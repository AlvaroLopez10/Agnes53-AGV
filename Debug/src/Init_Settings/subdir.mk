################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/Init_Settings/INIT.c" \
"../src/Init_Settings/INIT_ADC0.c" \
"../src/Init_Settings/INIT_FTM.c" \
"../src/Init_Settings/INIT_FTM0.c" \
"../src/Init_Settings/INIT_I2C.c" \
"../src/Init_Settings/INIT_LPIT0.c" \
"../src/Init_Settings/INIT_LPIT1.c" \
"../src/Init_Settings/INIT_PORTE.c" \
"../src/Init_Settings/INIT_UART0.c" \
"../src/Init_Settings/INIT_UART2.c" \

C_SRCS += \
../src/Init_Settings/INIT.c \
../src/Init_Settings/INIT_ADC0.c \
../src/Init_Settings/INIT_FTM.c \
../src/Init_Settings/INIT_FTM0.c \
../src/Init_Settings/INIT_I2C.c \
../src/Init_Settings/INIT_LPIT0.c \
../src/Init_Settings/INIT_LPIT1.c \
../src/Init_Settings/INIT_PORTE.c \
../src/Init_Settings/INIT_UART0.c \
../src/Init_Settings/INIT_UART2.c \

OBJS_OS_FORMAT += \
./src/Init_Settings/INIT.o \
./src/Init_Settings/INIT_ADC0.o \
./src/Init_Settings/INIT_FTM.o \
./src/Init_Settings/INIT_FTM0.o \
./src/Init_Settings/INIT_I2C.o \
./src/Init_Settings/INIT_LPIT0.o \
./src/Init_Settings/INIT_LPIT1.o \
./src/Init_Settings/INIT_PORTE.o \
./src/Init_Settings/INIT_UART0.o \
./src/Init_Settings/INIT_UART2.o \

C_DEPS_QUOTED += \
"./src/Init_Settings/INIT.d" \
"./src/Init_Settings/INIT_ADC0.d" \
"./src/Init_Settings/INIT_FTM.d" \
"./src/Init_Settings/INIT_FTM0.d" \
"./src/Init_Settings/INIT_I2C.d" \
"./src/Init_Settings/INIT_LPIT0.d" \
"./src/Init_Settings/INIT_LPIT1.d" \
"./src/Init_Settings/INIT_PORTE.d" \
"./src/Init_Settings/INIT_UART0.d" \
"./src/Init_Settings/INIT_UART2.d" \

OBJS += \
./src/Init_Settings/INIT.o \
./src/Init_Settings/INIT_ADC0.o \
./src/Init_Settings/INIT_FTM.o \
./src/Init_Settings/INIT_FTM0.o \
./src/Init_Settings/INIT_I2C.o \
./src/Init_Settings/INIT_LPIT0.o \
./src/Init_Settings/INIT_LPIT1.o \
./src/Init_Settings/INIT_PORTE.o \
./src/Init_Settings/INIT_UART0.o \
./src/Init_Settings/INIT_UART2.o \

OBJS_QUOTED += \
"./src/Init_Settings/INIT.o" \
"./src/Init_Settings/INIT_ADC0.o" \
"./src/Init_Settings/INIT_FTM.o" \
"./src/Init_Settings/INIT_FTM0.o" \
"./src/Init_Settings/INIT_I2C.o" \
"./src/Init_Settings/INIT_LPIT0.o" \
"./src/Init_Settings/INIT_LPIT1.o" \
"./src/Init_Settings/INIT_PORTE.o" \
"./src/Init_Settings/INIT_UART0.o" \
"./src/Init_Settings/INIT_UART2.o" \

C_DEPS += \
./src/Init_Settings/INIT.d \
./src/Init_Settings/INIT_ADC0.d \
./src/Init_Settings/INIT_FTM.d \
./src/Init_Settings/INIT_FTM0.d \
./src/Init_Settings/INIT_I2C.d \
./src/Init_Settings/INIT_LPIT0.d \
./src/Init_Settings/INIT_LPIT1.d \
./src/Init_Settings/INIT_PORTE.d \
./src/Init_Settings/INIT_UART0.d \
./src/Init_Settings/INIT_UART2.d \


# Each subdirectory must supply rules for building sources it contributes
src/Init_Settings/INIT.o: ../src/Init_Settings/INIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_ADC0.o: ../src/Init_Settings/INIT_ADC0.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_ADC0.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_ADC0.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_FTM.o: ../src/Init_Settings/INIT_FTM.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_FTM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_FTM.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_FTM0.o: ../src/Init_Settings/INIT_FTM0.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_FTM0.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_FTM0.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_I2C.o: ../src/Init_Settings/INIT_I2C.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_I2C.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_I2C.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_LPIT0.o: ../src/Init_Settings/INIT_LPIT0.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_LPIT0.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_LPIT0.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_LPIT1.o: ../src/Init_Settings/INIT_LPIT1.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_LPIT1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_LPIT1.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_PORTE.o: ../src/Init_Settings/INIT_PORTE.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_PORTE.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_PORTE.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_UART0.o: ../src/Init_Settings/INIT_UART0.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_UART0.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_UART0.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init_Settings/INIT_UART2.o: ../src/Init_Settings/INIT_UART2.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Init_Settings/INIT_UART2.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/Init_Settings/INIT_UART2.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '



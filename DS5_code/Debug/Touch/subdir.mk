################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Touch/button.c \
../Touch/buttonTable.c \
../Touch/touch_api.c 

OBJS += \
./Touch/button.o \
./Touch/buttonTable.o \
./Touch/touch_api.o 

C_DEPS += \
./Touch/button.d \
./Touch/buttonTable.d \
./Touch/touch_api.d 


# Each subdirectory must supply rules for building sources it contributes
Touch/%.o: ../Touch/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc -std=c99 -Dsoc_cv_av -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



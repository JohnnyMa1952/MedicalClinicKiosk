################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Graphics/ColourPallette.c \
../Graphics/Fonts.c \
../Graphics/Graphics.c \
../Graphics/Icons.c \
../Graphics/OutGraphicsCharFont.c 

OBJS += \
./Graphics/ColourPallette.o \
./Graphics/Fonts.o \
./Graphics/Graphics.o \
./Graphics/Icons.o \
./Graphics/OutGraphicsCharFont.o 

C_DEPS += \
./Graphics/ColourPallette.d \
./Graphics/Fonts.d \
./Graphics/Graphics.d \
./Graphics/Icons.d \
./Graphics/OutGraphicsCharFont.d 


# Each subdirectory must supply rules for building sources it contributes
Graphics/%.o: ../Graphics/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc -std=c99 -Dsoc_cv_av -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



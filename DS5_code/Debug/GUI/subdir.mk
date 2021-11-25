################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GUI/CameraScreen.c \
../GUI/DoneScreen.c \
../GUI/PICCNumberScreen.c \
../GUI/PIConfirmScreen.c \
../GUI/PINameScreen.c \
../GUI/PIPhoneNumberScreen.c \
../GUI/ProcessingScreen.c \
../GUI/Screen.c \
../GUI/SuggestionScreen.c \
../GUI/VitalsScreen.c \
../GUI/WelcomeScreen.c 

OBJS += \
./GUI/CameraScreen.o \
./GUI/DoneScreen.o \
./GUI/PICCNumberScreen.o \
./GUI/PIConfirmScreen.o \
./GUI/PINameScreen.o \
./GUI/PIPhoneNumberScreen.o \
./GUI/ProcessingScreen.o \
./GUI/Screen.o \
./GUI/SuggestionScreen.o \
./GUI/VitalsScreen.o \
./GUI/WelcomeScreen.o 

C_DEPS += \
./GUI/CameraScreen.d \
./GUI/DoneScreen.d \
./GUI/PICCNumberScreen.d \
./GUI/PIConfirmScreen.d \
./GUI/PINameScreen.d \
./GUI/PIPhoneNumberScreen.d \
./GUI/ProcessingScreen.d \
./GUI/Screen.d \
./GUI/SuggestionScreen.d \
./GUI/VitalsScreen.d \
./GUI/WelcomeScreen.d 


# Each subdirectory must supply rules for building sources it contributes
GUI/%.o: ../GUI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc -std=c99 -Dsoc_cv_av -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



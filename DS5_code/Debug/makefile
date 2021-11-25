################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include biomed/subdir.mk
-include WIFI/subdir.mk
-include Touch/subdir.mk
-include Point/subdir.mk
-include Linux/subdir.mk
-include Graphics/subdir.mk
-include GUI/subdir.mk
-include GPS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: CPEN391_13

# Tool invocations
CPEN391_13: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc  -o "CPEN391_13" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS) $(C_DEPS) $(EXECUTABLES) CPEN391_13 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

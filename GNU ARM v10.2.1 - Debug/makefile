################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/EFR32BG13P/subdir.mk
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
all: BRD4104A_EFR32BG13_rtcc_alarm_set.axf

# Tool invocations
BRD4104A_EFR32BG13_rtcc_alarm_set.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "BRD4104A_EFR32BG13_rtcc_alarm_set.ld" -Xlinker --gc-sections -Xlinker -Map="BRD4104A_EFR32BG13_rtcc_alarm_set.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o BRD4104A_EFR32BG13_rtcc_alarm_set.axf "./CMSIS/EFR32BG13P/startup_efr32bg13p.o" "./CMSIS/EFR32BG13P/system_efr32bg13p.o" "./Drivers/retargetio.o" "./Drivers/retargetserial.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_rtcc.o" "./emlib/em_system.o" "./emlib/em_usart.o" "./src/main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: BRD4104A_EFR32BG13_rtcc_alarm_set.hex'
	arm-none-eabi-objcopy -O ihex "BRD4104A_EFR32BG13_rtcc_alarm_set.axf" "BRD4104A_EFR32BG13_rtcc_alarm_set.hex"
	@echo ' '

	@echo 'Building bin file: BRD4104A_EFR32BG13_rtcc_alarm_set.bin'
	arm-none-eabi-objcopy -O binary "BRD4104A_EFR32BG13_rtcc_alarm_set.axf" "BRD4104A_EFR32BG13_rtcc_alarm_set.bin"
	@echo ' '

	@echo 'Building s37 file: BRD4104A_EFR32BG13_rtcc_alarm_set.s37'
	arm-none-eabi-objcopy -O srec "BRD4104A_EFR32BG13_rtcc_alarm_set.axf" "BRD4104A_EFR32BG13_rtcc_alarm_set.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "BRD4104A_EFR32BG13_rtcc_alarm_set.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) BRD4104A_EFR32BG13_rtcc_alarm_set.axf
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets

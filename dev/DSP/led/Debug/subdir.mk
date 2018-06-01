################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../led_test.c \
../main.c 

CMD_SRCS += \
../lnkx.cmd 

OBJS += \
./led_test.obj \
./main.obj 

C_DEPS += \
./led_test.pp \
./main.pp 

OBJS__QTD += \
".\led_test.obj" \
".\main.obj" 

C_DEPS__QTD += \
".\led_test.pp" \
".\main.pp" 

C_SRCS_QUOTED += \
"../led_test.c" \
"../main.c" 


# Each subdirectory must supply rules for building sources it contributes
led_test.obj: ../led_test.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="C:/Documents and Settings/Owner/My Documents/workspace/led/../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="led_test.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="C:/Documents and Settings/Owner/My Documents/workspace/led/../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '



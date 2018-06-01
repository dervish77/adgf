################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../aic3204_loop_stereo_in1.c \
../aic3204_test.c \
../aic3204_tone_headphone.c \
../audioBlocks.c \
../audioCore.c \
../audioUtils.c \
../main.c \
../sar.c 

CMD_SRCS += \
../lnkx.cmd 

OBJS += \
./aic3204_loop_stereo_in1.obj \
./aic3204_test.obj \
./aic3204_tone_headphone.obj \
./audioBlocks.obj \
./audioCore.obj \
./audioUtils.obj \
./main.obj \
./sar.obj 

C_DEPS += \
./aic3204_loop_stereo_in1.pp \
./aic3204_test.pp \
./aic3204_tone_headphone.pp \
./audioBlocks.pp \
./audioCore.pp \
./audioUtils.pp \
./main.pp \
./sar.pp 

OBJS__QTD += \
".\aic3204_loop_stereo_in1.obj" \
".\aic3204_test.obj" \
".\aic3204_tone_headphone.obj" \
".\audioBlocks.obj" \
".\audioCore.obj" \
".\audioUtils.obj" \
".\main.obj" \
".\sar.obj" 

C_DEPS__QTD += \
".\aic3204_loop_stereo_in1.pp" \
".\aic3204_test.pp" \
".\aic3204_tone_headphone.pp" \
".\audioBlocks.pp" \
".\audioCore.pp" \
".\audioUtils.pp" \
".\main.pp" \
".\sar.pp" 

C_SRCS_QUOTED += \
"../aic3204_loop_stereo_in1.c" \
"../aic3204_test.c" \
"../aic3204_tone_headphone.c" \
"../audioBlocks.c" \
"../audioCore.c" \
"../audioUtils.c" \
"../main.c" \
"../sar.c" 


# Each subdirectory must supply rules for building sources it contributes
aic3204_loop_stereo_in1.obj: ../aic3204_loop_stereo_in1.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="aic3204_loop_stereo_in1.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

aic3204_test.obj: ../aic3204_test.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="aic3204_test.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

aic3204_tone_headphone.obj: ../aic3204_tone_headphone.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="aic3204_tone_headphone.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

audioBlocks.obj: ../audioBlocks.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="audioBlocks.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

audioCore.obj: ../audioCore.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="audioCore.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

audioUtils.obj: ../audioUtils.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="audioUtils.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

sar.obj: ../sar.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Program Files/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="sar.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '



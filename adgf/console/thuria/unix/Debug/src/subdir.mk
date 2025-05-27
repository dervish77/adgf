################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cmds.c \
../src/debug.c \
../src/game.c \
../src/intro.c \
../src/magic.c \
../src/main.c \
../src/map.c \
../src/object.c \
../src/rank.c \
../src/room.c \
../src/special.c \
../src/verb.c 

OBJS += \
./src/cmds.o \
./src/debug.o \
./src/game.o \
./src/intro.o \
./src/magic.o \
./src/main.o \
./src/map.o \
./src/object.o \
./src/rank.o \
./src/room.o \
./src/special.o \
./src/verb.o 

C_DEPS += \
./src/cmds.d \
./src/debug.d \
./src/game.d \
./src/intro.d \
./src/magic.d \
./src/main.d \
./src/map.d \
./src/object.d \
./src/rank.d \
./src/room.d \
./src/special.d \
./src/verb.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



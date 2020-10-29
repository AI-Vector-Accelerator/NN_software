################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Matrix_IO.c \
../src/NN_algorithms_testbench.c 

OBJS += \
./src/Matrix_IO.o \
./src/NN_algorithms_testbench.o 

C_DEPS += \
./src/Matrix_IO.d \
./src/NN_algorithms_testbench.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



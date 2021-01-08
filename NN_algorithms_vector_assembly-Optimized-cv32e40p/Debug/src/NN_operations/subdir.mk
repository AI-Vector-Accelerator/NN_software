################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/NN_operations/convolution_operations.c \
../src/NN_operations/matrix_operations.c \
../src/NN_operations/pooling_operations.c \
../src/NN_operations/vector_operations.c 

OBJS += \
./src/NN_operations/convolution_operations.o \
./src/NN_operations/matrix_operations.o \
./src/NN_operations/pooling_operations.o \
./src/NN_operations/vector_operations.o 

C_DEPS += \
./src/NN_operations/convolution_operations.d \
./src/NN_operations/matrix_operations.d \
./src/NN_operations/pooling_operations.d \
./src/NN_operations/vector_operations.d 


# Each subdirectory must supply rules for building sources it contributes
src/NN_operations/%.o: ../src/NN_operations/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



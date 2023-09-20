################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/NeuralNetwork.cpp 

CPP_DEPS += \
./src/NeuralNetwork.d 

OBJS += \
./src/NeuralNetwork.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/models/layers" -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/models" -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/utils" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/NeuralNetwork.d ./src/NeuralNetwork.o

.PHONY: clean-src


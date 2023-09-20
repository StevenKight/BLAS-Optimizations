################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/models/NeuralNet.cpp 

CPP_DEPS += \
./src/models/NeuralNet.d 

OBJS += \
./src/models/NeuralNet.o 


# Each subdirectory must supply rules for building sources it contributes
src/models/%.o: ../src/models/%.cpp src/models/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/models/layers" -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/models" -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/utils" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-models

clean-src-2f-models:
	-$(RM) ./src/models/NeuralNet.d ./src/models/NeuralNet.o

.PHONY: clean-src-2f-models


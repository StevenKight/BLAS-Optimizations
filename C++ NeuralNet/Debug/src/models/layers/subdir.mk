################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/models/layers/Layer.cpp 

CPP_DEPS += \
./src/models/layers/Layer.d 

OBJS += \
./src/models/layers/Layer.o 


# Each subdirectory must supply rules for building sources it contributes
src/models/layers/%.o: ../src/models/layers/%.cpp src/models/layers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/models/layers" -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/models" -I"/home/steven/Documents/Personal Work/Neural-Net-Optimizations/C++ NeuralNet/src/utils" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-models-2f-layers

clean-src-2f-models-2f-layers:
	-$(RM) ./src/models/layers/Layer.d ./src/models/layers/Layer.o

.PHONY: clean-src-2f-models-2f-layers


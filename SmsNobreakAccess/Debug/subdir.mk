################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ConsoleTest.cpp \
../SerialAccesser.cpp \
../SmsNobreak.cpp 

OBJS += \
./ConsoleTest.o \
./SerialAccesser.o \
./SmsNobreak.o 

CPP_DEPS += \
./ConsoleTest.d \
./SerialAccesser.d \
./SmsNobreak.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



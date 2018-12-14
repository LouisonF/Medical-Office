################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataBase.cpp \
../Medecin.cpp \
../Patient.cpp \
../Prescription.cpp \
../Rendezvous.cpp \
../medical_office.cpp 

OBJS += \
./DataBase.o \
./Medecin.o \
./Patient.o \
./Prescription.o \
./Rendezvous.o \
./medical_office.o 

CPP_DEPS += \
./DataBase.d \
./Medecin.d \
./Patient.d \
./Prescription.d \
./Rendezvous.d \
./medical_office.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



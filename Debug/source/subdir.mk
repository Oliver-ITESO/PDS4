################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC.c \
../source/Frequency_check.c \
../source/LCD_nokia.c \
../source/LED.c \
../source/NVIC.c \
../source/PIT.c \
../source/SPI.c \
../source/main.c \
../source/semihost_hardfault.c 

OBJS += \
./source/ADC.o \
./source/Frequency_check.o \
./source/LCD_nokia.o \
./source/LED.o \
./source/NVIC.o \
./source/PIT.o \
./source/SPI.o \
./source/main.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/ADC.d \
./source/Frequency_check.d \
./source/LCD_nokia.d \
./source/LED.d \
./source/NVIC.d \
./source/PIT.d \
./source/SPI.d \
./source/main.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\PROJECTS\PDS_P4\Guitar_Strings\drivers" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\utilities" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\component\serial_manager" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\component\uart" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\component\lists" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\CMSIS" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\device" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\board" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\source" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\drivers" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\utilities" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\component\serial_manager" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\component\uart" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\component\lists" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\CMSIS" -I"C:\PROJECTS\PDS_P4\Guitar_Strings\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



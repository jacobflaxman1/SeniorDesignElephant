################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/jacobflaxman/Desktop/senior_design_1/LoRaWAN_End_Node/FATFS/App/app_fatfs.c 

OBJS += \
./Application/User/FATFS/App/app_fatfs.o 

C_DEPS += \
./Application/User/FATFS/App/app_fatfs.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/FATFS/App/app_fatfs.o: /Users/jacobflaxman/Desktop/senior_design_1/LoRaWAN_End_Node/FATFS/App/app_fatfs.c Application/User/FATFS/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../../Core/Inc -I../../LoRaWAN/App -I../../LoRaWAN/Target -I../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../Utilities/trace/adv_trace -I../../Utilities/misc -I../../Utilities/sequencer -I../../Utilities/timer -I../../Utilities/lpm/tiny_lpm -I../../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../Middlewares/Third_Party/LoRaWAN/Crypto -I../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../Middlewares/Third_Party/LoRaWAN/Mac -I../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../Middlewares/Third_Party/SubGHz_Phy -I../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/STM32WLxx_Nucleo -I../../FATFS/Target -I../../FATFS/App -I../../Middlewares/Third_Party/FatFs/src -I"/Users/jacobflaxman/Desktop/senior_design_1/LoRaWAN_End_Node/STM32CubeIDE/Application/User/FATFS/Target" -I"/Users/jacobflaxman/Desktop/senior_design_1/LoRaWAN_End_Node/STM32CubeIDE/Application/User/Core" -I"/Users/jacobflaxman/Desktop/senior_design_1/LoRaWAN_End_Node/STM32CubeIDE/Middlewares/LoRaWAN" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-FATFS-2f-App

clean-Application-2f-User-2f-FATFS-2f-App:
	-$(RM) ./Application/User/FATFS/App/app_fatfs.cyclo ./Application/User/FATFS/App/app_fatfs.d ./Application/User/FATFS/App/app_fatfs.o ./Application/User/FATFS/App/app_fatfs.su

.PHONY: clean-Application-2f-User-2f-FATFS-2f-App


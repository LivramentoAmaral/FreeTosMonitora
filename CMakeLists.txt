# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)



set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(monitoramento_led C CXX ASM)


include($ENV{FREERTOS_KERNEL_PATH}/home/marcos-amaral/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(monitoramento_led monitoramento_led.c )

pico_set_program_name(monitoramento_led "monitoramento_led")
pico_set_program_version(monitoramento_led "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(monitoramento_led 0)
pico_enable_stdio_usb(monitoramento_led 1)

# Add the standard library to the build
target_link_libraries(monitoramento_led
        pico_stdlib
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4)

# Add the standard include files to the build
target_include_directories(monitoramento_led PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(monitoramento_led 
        hardware_i2c
        
        )

pico_add_extra_outputs(monitoramento_led)


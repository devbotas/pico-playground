cmake_minimum_required(VERSION 3.14)

set(FREERTOS_KERNEL_PATH "M:/Code/Forks/pico-FreeRTOS-Kernel")
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/Configs")

set(PICO_SDK_PATH "M:/Code/Forks/pico-sdk")
 
include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(PicoFreeRTOS C CXX ASM)
include(PicoSDKConfig.cmake)

pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_SOURCE_DIR}/Code)

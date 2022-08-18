cmake_minimum_required(VERSION 3.24)

set(PICO_SDK_PATH "M:/Code/Forks/pico-sdk")
 
include(pico_sdk_import.cmake)

project(PicoFreeRTOS C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()



#include(${PICO_SDK_PATH}/pico_sdk_init.cmake)


#include(PicoSDKConfig.cmake)





add_subdirectory(Code)

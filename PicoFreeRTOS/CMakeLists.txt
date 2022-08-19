cmake_minimum_required(VERSION 3.24)

# Importing Pico SDK.
set(PICO_SDK_PATH "M:/Code/Forks/pico-sdk")
include(pico_sdk_import.cmake)

# Creating project.
project(PicoFreeRTOS C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Some VisualGDB stuff that I do not know what it does.
include(PicoSDKConfig.cmake) 
if(DEFINED SYSPROGS_FRAMEWORKS_FILE)
	include(${SYSPROGS_FRAMEWORKS_FILE})
endif()


add_subdirectory(Basic)
add_subdirectory(Code)
add_subdirectory(WiFi)

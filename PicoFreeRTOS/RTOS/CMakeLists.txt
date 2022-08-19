set(FREERTOS_KERNEL_PATH "M:/Code/Forks/pico-FreeRTOS-Kernel")
include(FreeRTOS_Kernel_import.cmake)
message("FreeRTOS is located at: " ${FREERTOS_KERNEL_PATH})


set(TARGET_RTOS "RtosBlink")
add_executable(${TARGET_RTOS} blink.c)
target_include_directories(${TARGET_RTOS} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
)
target_link_libraries(${TARGET_RTOS}
    pico_cyw43_arch_none
    FreeRTOS-Kernel-Heap4
    pico_stdlib
    Profiler
)
pico_add_extra_outputs(${TARGET_RTOS})
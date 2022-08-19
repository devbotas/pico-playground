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


set(TARGET_RTOS "RtosPing")
add_executable(${TARGET_RTOS} ping.c ${PICO_LWIP_CONTRIB_PATH}/apps/ping/ping.c)

target_compile_definitions(${TARGET_RTOS} PRIVATE
    WIFI_SSID=\"${WIFI_SSID}\"
    WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
)

target_include_directories(${TARGET_RTOS} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
    ${PICO_LWIP_CONTRIB_PATH}/apps/ping
)
target_link_libraries(${TARGET_RTOS}
    pico_cyw43_arch_lwip_threadsafe_background
    pico_stdlib
    FreeRTOS-Kernel-Heap4
    Profiler
)
pico_add_extra_outputs(${TARGET_RTOS})
set(FREERTOS_KERNEL_PATH "M:/Code/Forks/pico-FreeRTOS-Kernel")
include(FreeRTOS_Kernel_import.cmake)
message("FreeRTOS is located at: " ${FREERTOS_KERNEL_PATH})

# Include app source code file(s)
add_executable(${PROJECT_NAME}
    main.c
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
            WIFI_SSID=\"${WIFI_SSID}\"
            WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
            NO_SYS=0            # don't want NO_SYS (generally this would be in your lwipopts.h)
            LWIP_SOCKET=1       # we need the socket API (generally this would be in your lwipopts.h)
            PING_USE_SOCKETS=1
            )
# Including all the code files in this subfolder.
target_include_directories(${PROJECT_NAME} PRIVATE  
    ${CMAKE_CURRENT_LIST_DIR} 
)

# Link to built libraries
target_link_libraries(${PROJECT_NAME}
    #pico_cyw43_arch_lwip_threadsafe_background
    pico_cyw43_arch_lwip_sys_freertos
    pico_stdlib
    FreeRTOS-Kernel-Heap4
    Profiler)

# Enable extra build products
pico_add_extra_outputs(${PROJECT_NAME})
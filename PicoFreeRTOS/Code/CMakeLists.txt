# Set project data
set(PROJECT_NAME "FREERTOS_DEMO")
set(VERSION_NUMBER "1.0.0")
set(BUILD_NUMBER "1")

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${PROJECT_NAME}")
add_compile_definitions(APP_VERSION="${VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${BUILD_NUMBER})

# Include app source code file(s)
add_executable(${PROJECT_NAME}
    main.c
)

# Including all the code files in this subfolder.
target_include_directories(${PROJECT_NAME} PRIVATE  ${CMAKE_CURRENT_LIST_DIR})

# Link to built libraries
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    pico_stdlib
    hardware_gpio
    pico_cyw43_arch_none
    #FreeRTOS
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# Enable extra build products
pico_add_extra_outputs(${PROJECT_NAME})
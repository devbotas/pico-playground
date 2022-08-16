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

# Link to built libraries
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    pico_stdlib
    hardware_gpio
    #FreeRTOS
)
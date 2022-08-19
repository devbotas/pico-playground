set(TARGET_WIFI "Blink")
add_executable(${TARGET_WIFI} blink.c)
target_include_directories(${TARGET_WIFI} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
)
target_link_libraries(${TARGET_WIFI}
    pico_cyw43_arch_none
    pico_stdlib
    Profiler
)
pico_add_extra_outputs(${TARGET_WIFI})


set(TARGET_WIFI "Scan")
add_executable(${TARGET_WIFI} scan.c)
target_include_directories(${TARGET_WIFI} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
)
target_link_libraries(${TARGET_WIFI}
    pico_cyw43_arch_lwip_threadsafe_background
    pico_stdlib
    Profiler
)
pico_add_extra_outputs(${TARGET_WIFI})
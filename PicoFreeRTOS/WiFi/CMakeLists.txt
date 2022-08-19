set(TARGET_BLINK "Blink")

add_executable(${TARGET_BLINK} blink.c)

target_include_directories(${TARGET_BLINK} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
)

target_link_libraries(${TARGET_BLINK}
    pico_cyw43_arch_none
    pico_stdlib
    Profiler
)

pico_add_extra_outputs(${TARGET_BLINK})

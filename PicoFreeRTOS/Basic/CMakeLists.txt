message("Building Basic sample!")
set(TARGET_CLICK "Click")

add_executable(${TARGET_CLICK} main.c)

target_include_directories(${TARGET_CLICK} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
)

target_link_libraries(${TARGET_CLICK}
    pico_cyw43_arch_none
    pico_stdlib
    Profiler
)

pico_add_extra_outputs(${TARGET_CLICK})

set(TARGET_PUSH "Push")
add_executable(${TARGET_PUSH} push.c)

target_include_directories(${TARGET_PUSH} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
)

target_link_libraries(${TARGET_PUSH}
    pico_cyw43_arch_none
    pico_stdlib
    Profiler
)

pico_add_extra_outputs(${TARGET_PUSH})
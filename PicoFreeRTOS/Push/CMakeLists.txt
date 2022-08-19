message("Building Basic sample!")
set(TARGET_PUSH "Push")

add_executable(${TARGET_PUSH} main.c)

target_include_directories(${TARGET_PUSH} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
)

target_link_libraries(${TARGET_PUSH}
    pico_cyw43_arch_none
    pico_stdlib
    Profiler
)

pico_add_extra_outputs(${TARGET_PUSH})
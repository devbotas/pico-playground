message("Building Basic sample!")
set(TARGET_CLICK "Click")

add_executable(${TARGET_CLICK} main.c)

target_include_directories(${TARGET_CLICK} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
)

target_link_libraries(${TARGET_CLICK}
    pico_stdlib
)

pico_add_extra_outputs(${TARGET_CLICK})
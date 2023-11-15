cmake_minimum_required(VERSION 3.26)
project(kbrd C)

set(CMAKE_C_STANDARD 17)

add_executable(kbrd
        src/main.c)

target_include_directories(kbrd PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(kbrd ${PROJECT_SOURCE_DIR}/lib/hidapi.lib)
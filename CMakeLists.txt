cmake_minimum_required(VERSION 3.26)
project(kbrd C)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(kbrd
        src/main.c
        src/getInteger.c
        src/ite8291.c
        src/userInterface.c
        include/userInterface.h
        src/handler.c
        include/handler.h)

target_include_directories(kbrd PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(kbrd ${PROJECT_SOURCE_DIR}/lib/hidapi.lib)
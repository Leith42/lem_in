cmake_minimum_required(VERSION 3.9)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

add_executable(lem_in
        src/main.c
        src/parsing.c
        src/room.c
        src/utils.c
        src/checker.c
        src/algo.c
        )

include_directories(lemn_in
        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/libft/include/)

target_link_libraries(lem_in
        ${CMAKE_SOURCE_DIR}/libft/libft.a)
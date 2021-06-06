cmake_minimum_required(VERSION 3.9)


file(GLOB src src/*.c)
project(sudoku)
set(CMAKE_C_STANDARD 11)
add_compile_options(-g -Wall -Wextra -Wshadow -Ofast -mtune=skylake)
add_executable(${PROJECT_NAME} ${src})

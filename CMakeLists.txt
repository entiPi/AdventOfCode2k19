cmake_minimum_required(VERSION 3.10)
project(AdventOfCode2k19)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

enable_testing()

add_subdirectory(src)
add_subdirectory(3rd-party/catch2)

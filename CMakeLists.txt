cmake_minimum_required(VERSION 3.23)
project(IFJ C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)

add_executable(IFJ
        src/hello_world.c)

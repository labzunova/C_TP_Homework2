cmake_minimum_required(VERSION 3.17)
project(Homework_2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

add_library(consistent STATIC consistent/consistent_realization.c consistent/consistent_realization.h )
add_library(parallel SHARED parallel/parallel_realization.h parallel/parallel_realization.c)

target_link_libraries(${APP_NAME} consistent)
target_link_libraries(${APP_NAME} parallel)

add_executable(Homework_2 main.c console_communication.c console_communication.h consistent/consistent_realization.c consistent/consistent_realization.h parallel/parallel_realization.c parallel/parallel_realization.h)
add_subdirectory(Google_tests)
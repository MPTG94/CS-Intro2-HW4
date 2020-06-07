cmake_minimum_required(VERSION 3.15)
project(hw4 C)

set(CMAKE_C_STANDARD 99)

add_executable(hw4q1 hw4q1.c)
target_link_libraries(hw4q1 m)
add_executable(hw4q2 hw4q2.c)
add_executable(hw4q3 hw4q3template.c)

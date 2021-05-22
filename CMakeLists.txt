cmake_minimum_required(VERSION 3.19)
project(progettoSO C)

set(CMAKE_C_STANDARD 11)

add_executable(main src/main.c)
add_executable(p src/p3.c src/p1.c src/p2.c src/p.c)
add_executable(decision_function src/decision_function.c)
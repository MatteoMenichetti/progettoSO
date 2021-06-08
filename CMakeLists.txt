cmake_minimum_required(VERSION 3.19)
project(progettoSO C)

set(CMAKE_C_STANDARD 11)

add_executable(main src/main.c)
add_executable(watchdog src/watchdog.c lib/ipc.h)
add_executable(p lib/ipc.h lib/p.h src/p3.c src/p1.c src/p2.c src/p.c)
add_executable(decision_function lib/ipc.h src/decision_function.c)
add_executable(input_manager src/input_manager.c lib/ipc.h)
add_executable(failure src/failure_manager.c)
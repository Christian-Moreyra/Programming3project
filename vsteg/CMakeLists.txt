cmake_minimum_required(VERSION 3.10)
project(prog C)

set(CMAKE_C_STANDARD 11)

add_executable(vsteg vsteg.c bitmap.c bitmap.h util.h util.c stego.c stego.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(vsteg Threads::Threads)

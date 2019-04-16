cmake_minimum_required(VERSION 3.10)
project(vsteg C)

set(CMAKE_C_STANDARD 11)

add_executable(vsteg vsteg.c isteg.c bitmap.c bitmap.h util.h util.c stego.c stego.h)

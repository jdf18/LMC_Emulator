cmake_minimum_required(VERSION 3.20)
project(LMCEmulator C)

set(CMAKE_C_STANDARD 11)

add_executable(LMCEmulator src/main.c
        src/lmc.c
        src/lmc.h
        src/lmc_reader.c
        src/lmc_reader.h)

cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp u_pipe.h mes_queue.h signals.h check.h helper.h)

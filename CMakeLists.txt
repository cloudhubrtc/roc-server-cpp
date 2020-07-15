cmake_minimum_required(VERSION 3.16)
project(roc_server_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(roc_server_cpp main.cpp roc/Client.cpp roc/Client.h)
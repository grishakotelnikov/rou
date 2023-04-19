cmake_minimum_required(VERSION 3.24)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled2 main.cpp geo.h stat_reader.cpp transport_catalogue.cpp input_reader.h input_reader.cpp)

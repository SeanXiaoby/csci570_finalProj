cmake_minimum_required(VERSION 3.23)
project(csci570_finalProj)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(./src)

add_executable(Test_Class ./src/main.cpp ./src/TestClass.cpp)

cmake_minimum_required(VERSION 3.23)
project(CSCI-570-FinalProject-Sequence-Alignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(./src)

add_executable(Basic-Test src/basic.cpp ./src/CSequenceAligner.cpp ./src/CUtils.cpp)
add_executable(Efficient-Test src/efficient.cpp ./src/CSequenceAligner.cpp ./src/CUtils.cpp)

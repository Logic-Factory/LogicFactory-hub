cmake_minimum_required(VERSION 3.10)

project(netlist)

set(CMAKE_CXX_STANDARD 14)

add_executable(netlist netlist.cpp netlist.h power.cpp feature.cpp main.cpp utility.cpp wire.cpp mapping/mapping.cpp io.cpp)
cmake_minimum_required(VERSION 3.7)
project(indie_server)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES srcs/main.cpp srcs/LinuxSocket.cpp srcs/Router.cpp srcs/Server.cpp)
add_executable(indie_server ${SOURCE_FILES})
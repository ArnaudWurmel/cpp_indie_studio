cmake_minimum_required(VERSION 3.0.2)
project(indie_server)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES srcs/main.cpp srcs/Router.cpp srcs/Server.cpp srcs/GameManager.cpp srcs/GameManager.hh srcs/Room.cpp srcs/Room.hh srcs/Game.cpp srcs/Game.hh srcs/MapParser/MapParser.cpp srcs/MapParser/MapParser.hh srcs/ConfParser.cpp srcs/ConfParser.hh ../srcs/Exception/Exception.cpp ../srcs/Exception/Exception.hh)
add_executable(indie_server ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.0.2)
project(cpp_indie_studio)

set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/")
set(CMAKE_CXX_FLAGS "-std=c++14")


find_package(OGRE REQUIRED)
include_directories (${OGRE_INCLUDE_DIRS})

find_package(OIS REQUIRED)

set(SOURCE_FILES
        srcs/main.cpp srcs/SceneDisplayer/SceneDisplayer.cpp srcs/SceneDisplayer/SceneDisplayer.hh srcs/Bomberman/Bomberman.cpp srcs/Bomberman/Bomberman.hh srcs/Entities/Block.cpp srcs/Entities/Block.hh srcs/Entities/AEntity.hh srcs/Entities/AEntity.cpp srcs/EventListener/EventListener.cpp srcs/EventListener/EventListener.hh srcs/MapParser/MapParser.cpp srcs/MapParser/MapParser.hh srcs/Entities/EntityManager.cpp srcs/Entities/EntityManager.hh srcs/Entities/BreakableBlock.cpp srcs/Entities/BreakableBlock.hh srcs/Player/APlayer.cpp srcs/Player/APlayer.hh srcs/Player/HumanPlayer.cpp srcs/Player/HumanPlayer.hh)
add_executable(cpp_indie_studio ${SOURCE_FILES})

target_link_libraries(cpp_indie_studio ${OGRE_LIBRARY} ${OIS_LIBRARY})
cmake_minimum_required(VERSION 3.7)
project(cpp_indie_studio)

set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/")
include_directories ("/usr/local/share/OGRE/Samples/Common/include/")
#set(CMAKE_CXX_FLAGS "-Wall -W -Werror -ansi -pedantic -g")
set(CMAKE_CXX_STANDARD 14)

find_package(OGRE REQUIRED)
include_directories (${OGRE_INCLUDE_DIRS})

find_package(OIS REQUIRED)

set(SOURCE_FILES main.cpp AppManager.cpp AppManager.hh)
add_executable(cpp_indie_studio ${SOURCE_FILES})

target_link_libraries(cpp_indie_studio ${OGRE_LIBRARY} ${OIS_LIBRARY})
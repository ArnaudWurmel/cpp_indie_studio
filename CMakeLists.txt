
cmake_minimum_required(VERSION 3.0.2)
project(cpp_indie_studio)

set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/")
set(CMAKE_CXX_FLAGS "-std=c++14")
set(INSTALL_PATH ~/.tronberman/)


find_package(OGRE REQUIRED)
include_directories (${OGRE_INCLUDE_DIRS})

find_package(OIS REQUIRED)

set(SOURCE_FILES
        srcs/main.cpp srcs/SceneDisplayer/SceneDisplayer.cpp srcs/SceneDisplayer/SceneDisplayer.hh srcs/Bomberman/Bomberman.cpp srcs/Bomberman/Bomberman.hh srcs/Entities/Block.cpp srcs/Entities/Block.hh srcs/Entities/AEntity.hh srcs/Entities/AEntity.cpp srcs/EventListener/EventListener.cpp srcs/EventListener/EventListener.hh srcs/MapParser/MapParser.cpp srcs/MapParser/MapParser.hh srcs/Entities/EntityManager.cpp srcs/Entities/EntityManager.hh srcs/Entities/BreakableBlock.cpp srcs/Entities/BreakableBlock.hh srcs/Player/APlayer.cpp srcs/Player/APlayer.hh srcs/Player/HumanPlayer.cpp srcs/Player/HumanPlayer.hh srcs/EventListener/AEventRegister.hh srcs/Particle/Particle.cpp srcs/Particle/Particle.hh srcs/Config/Config.cpp srcs/Config/Config.hh srcs/Entities/Bomb.cpp srcs/Entities/Bomb.h srcs/Entities/Explosion.cpp srcs/Entities/Explosion.hh srcs/Entities/ExplosableEntity.cpp srcs/Entities/ExplosableEntity.hh srcs/DataManager/DataManager.cpp srcs/DataManager/DataManager.h srcs/GUI/LoginViewController.cpp srcs/GUI/LoginViewController.hh srcs/GUI/AViewController.hh srcs/GUI/RootViewController.cpp srcs/GUI/RootViewController.hh srcs/GUI/AViewController.cpp srcs/UserManager/User.cpp srcs/UserManager/User.hh srcs/GUI/RoomListViewController.cpp srcs/GUI/RoomListViewController.hh srcs/Models/Room.cpp srcs/Models/Room.hh srcs/GUI/WaitingRoomViewController.cpp srcs/GUI/WaitingRoomViewController.hh srcs/SoundManager/SoundManager.cpp srcs/SoundManager/SoundManager.hh srcs/GUI/GlobalRankingViewController.cpp srcs/GUI/GlobalRankingViewController.hh srcs/Exception/Exception.cpp srcs/Exception/Exception.hh srcs/PowerUp/PowerUp.cpp srcs/PowerUp/PowerUp.hh srcs/PowerUp/SpeedBoost.cpp srcs/PowerUp/SpeedBoost.hh srcs/PowerUp/ExtendBoost.cpp srcs/PowerUp/ExtendBoost.hh srcs/PowerUp/BombUp.cpp srcs/PowerUp/BombUp.hh srcs/GUI/BackgroundController/BackgroundImageController.cpp srcs/GUI/BackgroundController/BackgroundImageController.hh srcs/GUI/BackgroundController/BackgroundMapController.cpp srcs/GUI/BackgroundController/BackgroundMapController.hh)
add_executable(cpp_indie_studio ${SOURCE_FILES})

add_custom_target(installation +
        make && cp runscript.sh /usr/bin/tronberman && rm -rf ${INSTALL_PATH} && mkdir -p ${INSTALL_PATH} && cp cpp_indie_studio ${INSTALL_PATH} && cp -rf resources ${INSTALL_PATH}
)

add_custom_target(uninstall
        sudo rm -rf /usr/bin/runscript.sh ${INSTALL_PATH}
        )

target_link_libraries(cpp_indie_studio sfml-audio MyGUIEngine MyGUI.OgrePlatform pthread ${OGRE_LIBRARY} ${OIS_LIBRARY})

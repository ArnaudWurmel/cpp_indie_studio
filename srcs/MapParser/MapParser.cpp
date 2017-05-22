//
// Created by wurmel on 22/05/17.
//

#include <fstream>
#include <iostream>
#include <Ogre.h>
#include "MapParser.hh"

Indie::MapParser::MapParser(std::string const& mapPath) : _map(0)
{
    _convert.insert(std::make_pair(' ', Indie::MapParser::TileType::EMPTY));
    _convert.insert(std::make_pair('#', Indie::MapParser::TileType::STATIC_BLOCK));
    Ogre::LogManager::getSingletonPtr()->logMessage("*** START MAP PARSING ***");
    this->loadMap(mapPath);
}

std::vector<std::vector<Indie::MapParser::TileType>> const& Indie::MapParser::getMap()
{
    return _map;
}

void    Indie::MapParser::loadMap(std::string const& mapPath)
{
    std::ifstream   file(mapPath);
    std::string     line;

    if (file.is_open())
    {
        while (std::getline(file, line)) {
            std::string::iterator it = line.begin();
            std::vector<TileType>   lineVector;

            while (it != line.end()) {
                if (_convert.find(*it) != _convert.end()) {
                    lineVector.push_back(_convert[*it]);
                }
                else {
                    _map.clear();
                    Ogre::LogManager::getSingletonPtr()->logMessage("/!\\ MAP PARSING FAILED /!\\");
                    return ;
                }
                ++it;
            }
            _map.push_back(lineVector);
        }
        Ogre::LogManager::getSingletonPtr()->logMessage("*** Map parsing ended ***");
    }
    else
        Ogre::LogManager::getSingletonPtr()->logMessage("/!\\ MAP PARSING FAILED /!\\");
}

Indie::MapParser::~MapParser() {}

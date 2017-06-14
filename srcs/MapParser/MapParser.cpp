//
// Created by wurmel on 22/05/17.
//

#include <fstream>
#include <iostream>
#include <Ogre.h>
#include "MapParser.hh"
#include "../DataManager/DataManager.h"
#include "../UserManager/User.hh"

Indie::MapParser&   Indie::MapParser::getMapParser(std::string const& mapPath) {
    static Indie::MapParser *mapParser = NULL;

    if (mapParser == NULL)
        mapParser = new Indie::MapParser(mapPath);
    return (*mapParser);
}

Indie::MapParser::MapParser(std::string const& mapPath) : _map(0)
{
    _convert.insert(std::make_pair(' ', Indie::MapParser::TileType::EMPTY));
    _convert.insert(std::make_pair('#', Indie::MapParser::TileType::STATIC_BLOCK));
    _convert.insert(std::make_pair('0', Indie::MapParser::TileType::DYNAMIC_BLOCK));
    Ogre::LogManager::getSingletonPtr()->logMessage("*** START MAP PARSING ***");
}

std::vector<std::vector<Indie::MapParser::TileType>> const& Indie::MapParser::getMap()
{
    return _map;
}

void    Indie::MapParser::loadMap(std::string const& mapPath)
{
    std::vector<std::string>    map;
    DataManager *dataManager = DataManager::getSingloton("127.0.0.1", 4242);

    std::cout << dataManager->getMap(User::getUser()->getRoomId(), map) << std::endl;
    std::vector<std::string>::iterator  it;

    _map.clear();
    it = map.begin();
    while (it != map.end()) {
        std::cout << (*it) << std::endl;
        std::string::iterator   itString = (*it).begin();
        std::vector<MapParser::TileType>    lineVec;

        while (itString != (*it).end()) {
            if (_convert.find(*itString) != _convert.end()) {
                lineVec.push_back(_convert[*itString]);
            }
            else
                lineVec.push_back(MapParser::TileType::EMPTY);
            ++itString;
        }
        std::cout << lineVec.size() << std::endl;
        _map.push_back(lineVec);
        ++it;
    }

}

Indie::MapParser::~MapParser() {}

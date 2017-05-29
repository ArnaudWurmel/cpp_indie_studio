//
// Created by wurmel on 22/05/17.
//

#include <fstream>
#include <iostream>
#include "MapParser.hh"

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
    _convert.insert(std::make_pair('P', Indie::MapParser::TileType::PLAYER));
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
                    return ;
                }
                ++it;
            }
            _map.push_back(lineVector);
        }
    }
}

Indie::MapParser::~MapParser() {}

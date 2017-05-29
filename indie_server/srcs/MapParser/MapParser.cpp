//
// Created by wurmel on 22/05/17.
//

#include <fstream>
#include <iostream>
#include "MapParser.hh"

Indie::MapParser::MapParser(std::string const& mapPath) : _map(0)
{
    this->loadMap(mapPath);
}

std::vector<std::string> const& Indie::MapParser::getMap()
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
            _map.push_back(line);
        }
    }
}

Indie::MapParser::~MapParser() {}

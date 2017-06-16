//
// Created by erwan on 16/06/17.
//

#include <string>
#include <iostream>
#include <fstream>
#include "Map.h"
#include "../MapParser/MapParser.hh"
#include "../Entities/EntityManager.hh"

Indie::Map::Map() {
    Indie::MapParser&   mapParser = Indie::MapParser::getMapParser("");
    std::vector<std::vector<Indie::MapParser::TileType>> const&   tmp = mapParser.getMap();
    unsigned long   height;
    unsigned long   width;

    height = tmp.size();
    if (height > 0)
        width = tmp[0].size();
    else
        return ;
    initMap(height, width);
    addBlock(Indie::EntityManager::getEntityList());
}

Indie::Map::~Map() {

}

std::vector<std::vector<Indie::Map::map>> Indie::Map::getMap() const {
    return _map;
}

void Indie::Map::showMap() {
    std::vector<std::vector<map>>::iterator     it1;
    std::vector<map>::iterator                  it2;

    std::cout << "\n\n=-=-=-=-=-=-=-=-=-= MAP =-=-=-=-=-=-=-=-=-=\n" << std::endl;
    it1 = _map.begin();
    while (it1 != _map.end())
    {
        it2 = (*it1).begin();
        while (it2 != (*it1).end())
        {
            std::cout << (*it2);
            it2++;
        }
        it1++;
        std::cout << std::endl;
    }
    std::cout << "\n=-=-=-=-=-=-=-=-=-= END =-=-=-=-=-=-=-=-=-=\n" << std::endl;
}

std::pair<int, int> Indie::Map::getPosOfFirst(const std::pair<int, int> & currentPos, Indie::Map::map toFind) {
    std::vector<std::vector<map>>   mapTmp;
    std::vector<std::vector<map>>::iterator itx;
    std::vector<map>::iterator ity;
    std::pair<int, int> res;
    int tmp;
    int x;
    int y;

    mapTmp = _map;
    itx = mapTmp.begin();
    x = 0;
    tmp = mapTmp.size() * mapTmp.size();
    res.first = -1;
    res.second = -1;
    while (itx != mapTmp.end()) {
        ity = (*itx).begin();
        y = 0;
        while (ity != (*itx).end()) {
            if ((*ity) == toFind && tmp >= abs(currentPos.first - x) + abs(currentPos.second - y)) {
                tmp = abs(currentPos.first - x) + abs(currentPos.second - y);
                res.first = x;
                res.second = y;
            }
            ity++;
            y++;
        }
        itx++;
        x++;
    }
    return res;
}

void    Indie::Map::initMap(int height, int width) {
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < height)
    {
        j = 0;
        _map.push_back(std::vector<Indie::Map::map>());
        while (j < width)
        {
            _map[i].push_back(Indie::Map::EMPTY);
            j += 1;
        }
        i += 1;
    }
}

void Indie::Map::addBlock(std::vector<Indie::AEntity*> &blockList) {
    std::vector<Indie::AEntity*>::iterator  it = blockList.begin();

    while (it != blockList.end())
    {
        if ((*it)->hittedByExplosion())
            _map[static_cast<int>(((*it)->getPosition().x + ((_map.size() / 2) * 100)) / 100)][static_cast<int>(((*it)->getPosition().z + ((_map[0].size() / 2) * 100)) / 100)] = DYNAMIC_BLOCK;
        else
            _map[static_cast<int>(((*it)->getPosition().x + ((_map.size() / 2) * 100)) / 100)][static_cast<int>(((*it)->getPosition().z + ((_map[0].size() / 2) * 100)) / 100)] = STATIC_BLOCK;
        it++;
    }
}

//
// Created by ballet_e on 6/7/17.
//

#include <memory>
#include <vector>
#include <stack>
#include <iostream>
#include "AI.hh"
#include "../MapParser/MapParser.hh"
#include "../Entities/EntityManager.hh"

Indie::AI::AI(Ogre::Vector3 const &entityPos, Ogre::SceneManager *sceneManager, std::string const &pId,
              bool mainP) : APlayer(PlayerType::IA, entityPos, sceneManager, "human.mesh", mainP)
{
    setScale(Ogre::Vector3(50.0f, 53.459f, 50.0f));
    mTransformation = Ogre::Vector3(50.0f, 50.0f, 50.0f);
    addParticlesColor("Particles/Pink");
    addParticlesColor("Particles/Grey");
    _pId = pId;
    createMap();
    drawMap();
}

void    Indie::AI::initMap(unsigned long height, unsigned long width) {
    unsigned long i;
    unsigned long j;

    i = 0;
    j = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            _map[i][j] = EMPTY;
            j += 1;
        }
        i += 1;
    }
}

void    Indie::AI::addBlock(std::vector<std::shared_ptr<Indie::AEntity>>& blockList)
{
    std::vector<std::shared_ptr<Indie::AEntity>>::iterator  it = blockList.begin();

    while (it != blockList.end())
    {
        if ((*it)->hittedByExplosion())
            _map[static_cast<int>(((*it)->getPosition().x + 1000) / 100)][static_cast<int>(((*it)->getPosition().z + 1000) / 100)] = DYNAMIC_BLOCK;
        else
            _map[static_cast<int>(((*it)->getPosition().x + 1000) / 100)][static_cast<int>(((*it)->getPosition().z + 1000) / 100)] = STATIC_BLOCK;
        it++;
    }
}

void    Indie::AI::addPlayers(std::vector<std::unique_ptr<Indie::APlayer>>& playerList, std::unique_ptr<Indie::APlayer>& mainPlayer)
{
    std::vector<std::unique_ptr<Indie::APlayer>>::iterator  it = playerList.begin();

    while (it != playerList.end())
    {
        _map[static_cast<int>(((*it)->getPosition().x + 1000) / 100)][static_cast<int>(((*it)->getPosition().z + 1000) / 100)] = ENEMY_PLAYER;
        it++;
    }
    _map[static_cast<int>((mainPlayer->getPosition().x + 1000) / 100)][static_cast<int>((mainPlayer->getPosition().z + 1000) / 100)] = AI_PLAYER;
    _myPos.first = static_cast<unsigned int>((mainPlayer->getPosition().x + 1000) / 100);
    _myPos.second = static_cast<unsigned int>((mainPlayer->getPosition().z + 1000) / 100);
}

void    Indie::AI::createMap()
{
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
    addPlayers(Indie::EntityManager::getPlayerList(), Indie::EntityManager::getMainPlayer());
}

void    Indie::AI::findEnemy() {
    std::vector<std::vector<Indie::AI::map>>::iterator     it;
    std::vector<Indie::AI::map>::iterator  it2;
    unsigned int    x;
    unsigned int    z;

    it = _map.begin();
    x = 0;
    while (it != _map.end())
    {
        it2 = (*it).begin();
        z = 0;
        while (it2 != (*it).end())
        {
            if ((*it2) == ENEMY_PLAYER) {
                _enemyPos.first = x;
                _enemyPos.second = z;
                return ;
            }
            it2++;
            z += 1;
        }
        it++;
        x += 1;
    }
}

void    Indie::AI::findPath() {
    std::stack<std::pair<unsigned int, unsigned int>>   path;
    std::pair<unsigned int, unsigned int>   currentPos;
    std::vector<std::vector<map>>     tmpMap;
    bool    end;

    tmpMap = _map;
    end = false;
    currentPos = _myPos;
    while (!end)
    {
        if (currentPos == _enemyPos)
            end = true;
    }
}

void    Indie::AI::drawMap() {
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
    std::cout << "\n\n=-=-=-=-=-=-=-=-=-= END =-=-=-=-=-=-=-=-=-=\n" << std::endl;
}

Indie::AI::~AI() {}


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
#include "../DataManager/DataManager.h"
#include "../UserManager/User.hh"
#include "../Exception/Exception.hh"

/*
**  Constructeur
*/
Indie::AI::AI(Ogre::Vector3 const &entityPos, Ogre::SceneManager *sceneManager, std::string const &pId,
              bool mainP) : APlayer(PlayerType::IA, entityPos, sceneManager, "human.mesh", mainP)
{
    fncTab.push_back(&Indie::AI::isForward);
    fncTab.push_back(&Indie::AI::isBackward);
    fncTab.push_back(&Indie::AI::isLeft);
    fncTab.push_back(&Indie::AI::isRight);
    posFncTab.push_back(&Indie::AI::addForward);
    posFncTab.push_back(&Indie::AI::addBackward);
    posFncTab.push_back(&Indie::AI::addLeft);
    posFncTab.push_back(&Indie::AI::addRight);
    setScale(Ogre::Vector3(50.0f, 53.459f, 50.0f));
    mTransformation = Ogre::Vector3(50.0f, 50.0f, 50.0f);
    addParticlesColor("Particles/Pink");
    addParticlesColor("Particles/Grey");
    if (!DataManager::getSingloton()->joinRoom(pId, User::getUser()->getRoomId()))
        throw GameException();
    bool    success = false;
    DataManager::getSingloton()->getPlayerStart(pId, success);
    if (!success)
        throw GameException();
    _pId = pId;
    createMap();
}

bool    Indie::AI::updateFromLoop(Ogre::SceneManager *sceneManager) {
    resetMap();
   // addBlock(EntityManager::getEntityList());
    //addPlayers(EntityManager::getPlayerList(), EntityManager::getMainPlayer());
    if (findEnemy()) {
        findPath();
        if (_path.size()) {

        }
    }
    return APlayer::updateFromLoop(sceneManager);
}

/*
**  Les fonctions qui determine l'heuristique
*/

bool    Indie::AI::isForward() {
    if (_myPos.first < _enemyPos.first && _myPos.second <= _enemyPos.second) {
        _heuristic[0] = FORWARD;
        _heuristic[1] = RIGHT;
        _heuristic[2] = LEFT;
        _heuristic[3] = BACKWARD;
        return true;
    } else
        return false;
}

bool    Indie::AI::isBackward() {
    if (_myPos.first > _enemyPos.first && _myPos.second >= _enemyPos.second)
    {
        _heuristic[0] = BACKWARD;
        _heuristic[1] = LEFT;
        _heuristic[2] = RIGHT;
        _heuristic[3] = FORWARD;
        return true;
    } else
        return false;
}

bool    Indie::AI::isLeft() {
    if (_myPos.first <= _enemyPos.first && _myPos.second > _enemyPos.second) {
        _heuristic[0] = LEFT;
        _heuristic[1] = FORWARD;
        _heuristic[2] = BACKWARD;
        _heuristic[3] = RIGHT;
        return true;
    } else
        return false;
}

bool    Indie::AI::isRight() {
    if (_myPos.first >= _enemyPos.first && _myPos.second <= _enemyPos.second) {
        _heuristic[0] = RIGHT;
        _heuristic[1] = BACKWARD;
        _heuristic[2] = FORWARD;
        _heuristic[3] = LEFT;
        return true;
    } else
    return false;
}

/*
**  Les fonctions pour changer la position en fonction de la direction
*/

bool    Indie::AI::addForward(std::pair<unsigned int, unsigned int> &pos, Indie::AI::dir direction) {
    if (direction == FORWARD) {
        pos.first += 1;
        return true;
    } else
        return false;
}

bool    Indie::AI::addBackward(std::pair<unsigned int, unsigned int> &pos, Indie::AI::dir direction) {
    if (direction == BACKWARD) {
        pos.first -= 1;
        return true;
    } else
        return false;
}

bool    Indie::AI::addRight(std::pair<unsigned int, unsigned int> &pos, Indie::AI::dir direction) {
    if (direction == RIGHT) {
        pos.second += 1;
    } else
        return false;
}

bool    Indie::AI::addLeft(std::pair<unsigned int, unsigned int> &pos, Indie::AI::dir direction) {
    if (direction == LEFT) {
        pos.second -= 1;
    } else
        return false;
}

/*
** Fonction d'initialisation de la map. Rempli la map de 0 avec la bonne taille (height * width)
*/

void    Indie::AI::initMap(unsigned long height, unsigned long width) {
    unsigned long i;
    unsigned long j;

    i = 0;
    j = 0;
    while (i < height)
    {
        j = 0;
        _map.push_back(std::vector<Indie::AI::map>());
        while (j < width)
        {
            _map[i].push_back(Indie::AI::EMPTY);
            j += 1;
        }
        i += 1;
    }
}

/*
**  Fonction de reset de la map. Remple la map de 0
*/

void    Indie::AI::resetMap()
{
    unsigned long   height;
    unsigned long   width;
    unsigned long   i;
    unsigned long   j;

    height = _map.size();
    if (width > 0)
        width = _map[0].size();
    else
        return ;
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            _map[i][j] = EMPTY;
            j++;
        }
        i++;
    }
}

/*
**  Fonction d'ajout des blocks sur la map (destructible et fixe)
*/

void    Indie::AI::addBlock(std::vector<std::shared_ptr<Indie::AEntity>>& blockList)
{
    std::vector<std::shared_ptr<Indie::AEntity>>::iterator  it = blockList.begin();

    while (it != blockList.end())
    {
        if ((*it)->hittedByExplosion())
            _map[static_cast<int>(((*it)->getPosition().x + 1000) / 100) - 1][static_cast<int>(((*it)->getPosition().z + 1000) / 100) - 1] = DYNAMIC_BLOCK;
        else
            _map[static_cast<int>(((*it)->getPosition().x + 1000) / 100) - 1][static_cast<int>(((*it)->getPosition().z + 1000) / 100) - 1] = STATIC_BLOCK;
        it++;
    }
}

/*
**  Fonction d'ajout des joueurs sur la map (adversaire et sois-même)
*/

void    Indie::AI::addPlayers(std::vector<std::unique_ptr<Indie::APlayer>>& playerList, std::unique_ptr<Indie::APlayer>& mainPlayer)
{
    std::vector<std::unique_ptr<Indie::APlayer>>::iterator  it = playerList.begin();

    while (it != playerList.end())
    {
        _map[static_cast<int>(((*it)->getPosition().x + 1000) / 100) - 1][static_cast<int>(((*it)->getPosition().z + 1000) / 100) - 1] = ENEMY_PLAYER;
        it++;
    }
    _map[static_cast<int>((mainPlayer->getPosition().x + 1000) / 100) - 1][static_cast<int>((mainPlayer->getPosition().z + 1000) / 100) - 1] = AI_PLAYER;
    _myPos.first = static_cast<unsigned int>((mainPlayer->getPosition().x + 1000) / 100 - 1);
    _myPos.second = static_cast<unsigned int>((mainPlayer->getPosition().z + 1000) / 100 - 1);
}

/*
**  Fonction de création de la map (marche que si la map n'a jamais été créée)
*/

void    Indie::AI::createMap()
{
    Indie::MapParser&   mapParser = Indie::MapParser::getMapParser();
    std::vector<std::vector<Indie::MapParser::TileType>> const&   tmp = mapParser.getMap();
    unsigned long   height;
    unsigned long   width;

    height = tmp.size();
    if (height > 0)
        width = tmp[0].size();
    else
        return ;
    initMap(height, width);
    //addBlock(Indie::EntityManager::getEntityList());
    //addPlayers(Indie::EntityManager::getPlayerList(), Indie::EntityManager::getMainPlayer());
}

/*
**  Trouve le premier ennemi sur la map
*/

bool    Indie::AI::findEnemy() {
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
                return true;
            }
            it2++;
            z += 1;
        }
        it++;
        x += 1;
    }
    return false;
}

/*
**  Utilisation du A* pour trouver le chemin vers l'ennemi
*/

void    Indie::AI::findPath() {
    std::stack<std::pair<unsigned int, unsigned int>>   path;
    std::stack<std::pair<unsigned int, unsigned int>>   node;
    std::pair<unsigned int, unsigned int>   currentPos;
    std::vector<std::vector<map>>     tmpMap;
    bool    end;

    tmpMap = _map;
    end = false;
    //currentPos = _myPos;
    path.push(currentPos);
    if (isANode(currentPos))
        node.push(currentPos);
    tmpMap[currentPos.first][currentPos.second] = ALREADY_PASS;
    findHeuristic();
    while (!end)
    {
        if (findNextPos(currentPos)) {
            path.push(currentPos);
            if (isANode(currentPos))
                node.push(currentPos);
            tmpMap[currentPos.first][currentPos.second] = ALREADY_PASS;
        } else if (node.size() > 0) {
      //      currentPos = node.top();
            node.pop();
        } else
            end = true;
        if (currentPos == _enemyPos)
            end = true;
    }
    while (path.size() > 0)
    {
        //_path.push_back(path.top());
        path.pop();
    }
    std::reverse(_path.begin(), _path.end());
}

/*
**  Fonction determinant le path pour éviter une bomb
*/

void    Indie::AI::escapeBomb() {
    
}

/*
**  Affiche la map en askii (fonction de debug)
*/

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
    std::cout << "\n=-=-=-=-=-=-=-=-=-= END =-=-=-=-=-=-=-=-=-=\n" << std::endl;
}

/*
**  Fonction qui assigne l'heuristique dans la classe
*/

void    Indie::AI::findHeuristic() {
    int i;

    i = 0;
    while (!(this->*fncTab[i])())
        i += 1;
}

/*
**  fonction qui dertermine la prochaine position en fonction de l'heuristique
*/

bool    Indie::AI::findNextPos(std::pair<unsigned int, unsigned int>& currentPos) {
    int i;
    std::pair<unsigned int, unsigned int>   nextPos;
    std::vector<std::vector<map>>::iterator it;
    std::vector<map>::iterator              it2;

    i = 0;
    while (i < 4)
    {
        //nextPos = currentPos;
        addDir(_heuristic[i], nextPos);
        it = _map.begin() + nextPos.first;
        if (it != _map.end())
            it2 = (*it).begin() + nextPos.second;
        if (it2 != (*it).end() && (*it2) != ALREADY_PASS && (*it2) != STATIC_BLOCK) {
          //  currentPos = nextPos;
            return true;
        }
        i++;
    }
    return false;
}

/*
**  Fonction qui change la position en fonction de la direction
*/

void        Indie::AI::addDir(Indie::AI::dir direction, std::pair<unsigned int, unsigned int> &currentPos) {
    int     i;

    i = 0;
    while (i < 4 && !(this->*posFncTab[i])(currentPos, direction))
        i++;
}

/*
**  Fonction qui determine si une pos est une node ou non (un croisement)
*/

bool    Indie::AI::isANode(const std::pair<unsigned int, unsigned int> &pos) {
    std::pair<unsigned int, unsigned int>   nextPos;
    int     nbPass;
    int     i;

    i = 0;
    nbPass = 0;
    while (i < 4)
    {
//        nextPos = pos;
        if ((this->*posFncTab[i])(nextPos, _heuristic[i]))
            nbPass += 1;
        i++;
    }
    return nbPass > 1;
}

/*
**  Destructeur
*/

Indie::AI::~AI() {
    DataManager::getSingloton()->quitRoom(_pId);
}

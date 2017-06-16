//
// Created by ballet_e on 6/7/17.
//

//
// Created by kirrays on 15/06/17.
//

#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include "AI.hh"
#include "../DataManager/DataManager.h"
#include "../UserManager/User.hh"
#include "../Exception/Exception.hh"
#include "../Entities/EntityManager.hh"

/*
** Tableau de pointer sur fonction pour trouver l'heuristique
*/

const std::vector<Indie::AIPlayer::fncPtr> Indie::AIPlayer::fncTab = {
        &Indie::AIPlayer::isForward,
        &Indie::AIPlayer::isBackward,
        &Indie::AIPlayer::isLeft,
        &Indie::AIPlayer::isRight
};

const std::vector<Indie::AIPlayer::posPtr> Indie::AIPlayer::posFncTab = {
        &Indie::AIPlayer::addForward,
        &Indie::AIPlayer::addBackward,
        &Indie::AIPlayer::addLeft,
        &Indie::AIPlayer::addRight
};

const std::vector<Indie::AIPlayer::dirPtr> Indie::AIPlayer::dirTab = {
        &Indie::AIPlayer::onBot,
        &Indie::AIPlayer::onLeft,
        &Indie::AIPlayer::onRight,
        &Indie::AIPlayer::onTop
};

Indie::AIPlayer::AIPlayer(Ogre::Vector3 const &entityPos, Ogre::SceneManager *sceneManager, std::string const &pId,
              bool mainP) : APlayer(PlayerType::IA, entityPos, sceneManager, "human.mesh", mainP)
{
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
}

Indie::AIPlayer::~AIPlayer() {

}

void Indie::AIPlayer::findHeuristic(std::pair<int, int> currentPos, std::pair<int, int> enemyPos) {
    int i;

    i = 0;
    while (!(this->*fncTab[i])(currentPos, enemyPos))
        i += 1;
}

bool Indie::AIPlayer::isForward(std::pair<int, int> currentPos, std::pair<int, int> enemyPos) {
    if (currentPos.first < enemyPos.first && currentPos.second <= enemyPos.second) {
        _heuristic[0] = FORWARD;
        _heuristic[1] = RIGHT;
        _heuristic[2] = LEFT;
        _heuristic[3] = BACKWARD;
        return true;
    } else
        return false;
}

bool    Indie::AIPlayer::isBackward(std::pair<int, int> currentPos, std::pair<int, int> enemyPos) {
    if (currentPos.first > enemyPos.first && currentPos.second >= enemyPos.second)
    {
        _heuristic[0] = BACKWARD;
        _heuristic[1] = LEFT;
        _heuristic[2] = RIGHT;
        _heuristic[3] = FORWARD;
        return true;
    } else
        return false;
}

bool    Indie::AIPlayer::isLeft(std::pair<int, int> currentPos, std::pair<int, int> enemyPos) {
    if (currentPos.first <= enemyPos.first && currentPos.second > enemyPos.second) {
        _heuristic[0] = LEFT;
        _heuristic[1] = FORWARD;
        _heuristic[2] = BACKWARD;
        _heuristic[3] = RIGHT;
        return true;
    } else
        return false;
}

bool    Indie::AIPlayer::isRight(std::pair<int, int> currentPos, std::pair<int, int> enemyPos) {
    if (currentPos.first >= enemyPos.first && currentPos.second <= enemyPos.second) {
        _heuristic[0] = RIGHT;
        _heuristic[1] = BACKWARD;
        _heuristic[2] = FORWARD;
        _heuristic[3] = LEFT;
        return true;
    } else
        return false;
}

bool    Indie::AIPlayer::addForward(std::pair<int, int> &pos, Indie::AIPlayer::dir direction) {
    if (direction == FORWARD) {
        pos.first += 1;
        return true;
    } else
        return false;
}

bool    Indie::AIPlayer::addBackward(std::pair<int, int> &pos, Indie::AIPlayer::dir direction) {
    if (direction == BACKWARD) {
        pos.first -= 1;
        return true;
    } else
        return false;
}

bool    Indie::AIPlayer::addRight(std::pair<int, int> &pos, Indie::AIPlayer::dir direction) {
    if (direction == RIGHT) {
        pos.second += 1;
    } else
        return false;
}

bool    Indie::AIPlayer::addLeft(std::pair<int, int> &pos, Indie::AIPlayer::dir direction) {
    if (direction == LEFT) {
        pos.second -= 1;
    } else
        return false;
}

void    Indie::AIPlayer::addDir(Indie::AIPlayer::dir direction, std::pair<int, int>& currentPos) {
    int     i;

    i = 0;
    while (i < 4 && !(this->*posFncTab[i])(currentPos, direction))
        i++;
}

bool Indie::AIPlayer::isANode(const std::pair<int, int> &pos) {
    std::pair<int, int>   nextPos;
    int     nbPass;
    int     i;

    i = 0;
    nbPass = 0;
    while (i < 4)
    {
        nextPos = pos;
        if ((this->*posFncTab[i])(nextPos, _heuristic[i]))
            nbPass += 1;
        i++;
    }
    return nbPass > 1;
}

bool Indie::AIPlayer::findNextPos(std::pair<int, int> &currentPos, std::vector<std::vector<Indie::Map::map>> map) {
    int i;
    std::pair<int, int>   nextPos;
    std::vector<std::vector<Indie::Map::map>>::iterator it;
    std::vector<Indie::Map::map>::iterator              it2;

    i = 0;
    while (i < 4)
    {
        nextPos = currentPos;
        addDir(_heuristic[i], nextPos);
        it = map.begin() + nextPos.first;
        if (it != map.end())
            it2 = (*it).begin() + nextPos.second;
        if (it2 != (*it).end() && (*it2) != Indie::Map::ALREADY_PASS && (*it2) != Indie::Map::STATIC_BLOCK) {
            currentPos = nextPos;
            return true;
        }
        i++;
    }
    return false;
}

void Indie::AIPlayer::findPath(Indie::Map map) {
    std::stack<std::pair<int, int>>   path;
    std::stack<std::pair<int, int>>   node;
    std::pair<int, int>   currentPos;
    std::pair<int, int>   enemyPos;
    std::vector<std::vector<Indie::Map::map>>     tmpMap;
    bool    end;
    int     i = 0;

    tmpMap = map.getMap();
    end = false;
    currentPos = getMyPos(tmpMap.size(), tmpMap[0].size());
    enemyPos = getClosestEnemy(tmpMap.size(), tmpMap[0].size());
    path.push(currentPos);
    if (isANode(currentPos))
        node.push(currentPos);
    tmpMap[currentPos.first][currentPos.second] = Indie::Map::ALREADY_PASS;
    while (!end)
    {
        findHeuristic(currentPos, enemyPos);
        if (findNextPos(currentPos, tmpMap)) {
            path.push(currentPos);
            if (isANode(currentPos))
                node.push(currentPos);
            std::cout << "currentPos :" << currentPos.first << "|" << currentPos.second << " enemyPos :" << enemyPos.first << "|" << enemyPos.second << std::endl;
            if (currentPos == enemyPos)
                end = true;
            tmpMap[currentPos.first][currentPos.second] = Indie::Map::ALREADY_PASS;
        } else if (node.size() > 0) {
            currentPos = node.top();
            node.pop();
        } else
            end = true;
        ++i;
    }
    while (path.size() > 0)
    {
        _path.push_back(path.top());
        path.pop();
    }
    std::reverse(_path.begin(), _path.end());
}

Indie::AIPlayer::dir Indie::AIPlayer::getDir() {
    Indie::Map  map;
    const dir   tab[5] = {BACKWARD, LEFT, RIGHT, FORWARD, NOTHING};
    std::vector<std::pair<int, int>>::iterator  it;
    std::pair<int, int> currentPos;
    int i;

    findPath(map);
    it = _path.begin();
    while (it != _path.end()) {
        std::cout << (*it).first << "|" << (*it).second << " ";
        it++;
    } std::cout << std::endl;
    currentPos = getMyPos(map.getMap().size(), map.getMap()[0].size());
    if (_path.size() > 1) {
        i = 0;
        while (i < 4 && !(this->*dirTab[i])(currentPos, _path[1])) {
            i += 1;
        }
        return tab[i];
    } else {
        return NOTHING;
    }
}

bool Indie::AIPlayer::onTop(std::pair<int, int> &currentPos, std::pair<int, int> &toGo) {
    std::cout << "TOP" << std::endl;
    return currentPos.first > toGo.first;
}

bool Indie::AIPlayer::onBot(std::pair<int, int> &currentPos, std::pair<int, int> &toGo) {
    std::cout << "BOT :" << currentPos.first << "|" << toGo.second << std::endl;
    return currentPos.first < toGo.first;
}

bool Indie::AIPlayer::onLeft(std::pair<int, int> &currentPos, std::pair<int, int> &toGo) {
    std::cout << "LEFT" << std::endl;
    return currentPos.second < toGo.second;
}

bool Indie::AIPlayer::onRight(std::pair<int, int> &currentPos, std::pair<int, int> &toGo) {
    std::cout << "RIGHT " << std::endl;
    return currentPos.second > toGo.second;
}

std::pair<int, int> Indie::AIPlayer::getMyPos(int height, int width) {
    Ogre::Vector3   pos3D;
    std::pair<int, int> pos;

    pos3D = this->getPosition();
    pos.first = static_cast<int>((this->getPosition().x + ((height / 2) * 100)) / 100);
    pos.second = static_cast<int>((this->getPosition().z + ((width / 2) * 100)) / 100);
    return pos;
}

std::pair<int, int> Indie::AIPlayer::getClosestEnemy(int height, int width) {
    std::vector<Indie::APlayer*>                playerList;
    std::vector<Indie::APlayer*>::iterator      it;
    Indie::APlayer*     mainPlayer;
    std::pair<int, int>     myPos;
    std::pair<int, int>     res;

    myPos = getMyPos(height, width);
    playerList = Indie::EntityManager::getPlayerList();
    it = playerList.begin();
    res.first = height;
    res.second = width;
    while (it != playerList.end()) {
        if (myPos.first != (*it)->getPosition().x && myPos.second != (*it)->getPosition().y && abs(res.first - myPos.first) + abs(res.second - myPos.second) >= abs((*it)->getPosition().x - myPos.first) + abs((*it)->getPosition().y)) {
            res.first = (*it)->getPosition().x;
            res.second = (*it)->getPosition().z;
        }
        it++;
    }
    mainPlayer = Indie::EntityManager::getMainPlayer();
    if (myPos.first != mainPlayer->getPosition().x && myPos.second != mainPlayer->getPosition().y && abs(res.first - myPos.first) + abs(res.second - myPos.second) >= abs(mainPlayer->getPosition().x - myPos.first) + abs(mainPlayer->getPosition().y)) {
        res.first = (*it)->getPosition().x;
        res.second = (*it)->getPosition().z;
    }
    return res;
}

bool Indie::AIPlayer::updateFromLoop(Ogre::SceneManager *sceneManager) {
    dir     direction;

    direction = getDir();
    std::cout << direction << std::endl;
    return (Indie::APlayer::updateFromLoop(sceneManager));
}

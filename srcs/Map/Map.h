//
// Created by erwan on 16/06/17.
//

#ifndef CPP_INDIE_STUDIO_MAP_H
#define CPP_INDIE_STUDIO_MAP_H

#include <vector>
#include "../Entities/AEntity.hh"

namespace   Indie {
    class   Map {
    public:
        enum map
        {
            EMPTY = 0,
            STATIC_BLOCK = 1,
            DYNAMIC_BLOCK = 2,
            ENEMY_PLAYER = 3,
            AI_PLAYER = 4,
            BOMB = 5,
            ALREADY_PASS = 6,
            ERROR = 7
        };

    private:
        std::vector<std::vector<map>>   _map;

    public:
        Map();
        ~Map();

    public:
        std::vector<std::vector<map>>   getMap() const;
        std::pair<int, int>     getPosOfFirst(const std::pair<int, int>&, map);
        void    showMap();

    private:
        void    initMap(int, int);
        void    addBlock(std::vector<Indie::AEntity*>&);
    };
}

#endif //CPP_INDIE_STUDIO_MAP_H

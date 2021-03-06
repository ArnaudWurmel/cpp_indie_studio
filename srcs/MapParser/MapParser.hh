//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAPPARSER_HH
#define CPP_INDIE_STUDIO_MAPPARSER_HH

# include <vector>
# include <map>
# include <utility>
# include <string>

namespace   Indie {
    class MapParser {
    public:
        static MapParser&   getMapParser();
    public:
        enum TileType {
            EMPTY = 0,
            STATIC_BLOCK = 1,
            DYNAMIC_BLOCK,
        };

    public:
        MapParser();
        ~MapParser();

    public:
        std::vector<std::vector<TileType> > const& getMap();

    public:
        void    loadMap();

    private:
        std::vector<std::vector<TileType> > _map;
        std::map<char, TileType>            _convert;
    };
}


#endif //CPP_INDIE_STUDIO_MAPPARSER_HH

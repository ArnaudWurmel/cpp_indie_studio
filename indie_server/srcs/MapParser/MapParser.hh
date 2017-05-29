//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAPPARSER_HH
#define CPP_INDIE_STUDIO_MAPPARSER_HH

# include <vector>
# include <map>
# include <string>
# include <utility>
# include <string>

namespace   Indie {
    class MapParser {
    public:
        MapParser(std::string const&);
        ~MapParser();

    public:
        std::vector<std::string> const& getMap();

    private:
        void    loadMap(std::string const&);

    private:
        std::vector<std::string> _map;
    };
}


#endif //CPP_INDIE_STUDIO_MAPPARSER_HH

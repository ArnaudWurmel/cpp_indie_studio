//
// Created by wurmel_a on 08/06/17.
//

#ifndef CPP_INDIE_STUDIO_ROOM_HH
#define CPP_INDIE_STUDIO_ROOM_HH

namespace Indie {
    class Room {
    public:
        Room(unsigned int, unsigned int);
        ~Room();

    public:
        unsigned int const& getRoomID() const;
        unsigned int const& getNbPlayers() const;

    private:
        unsigned int    _roomId;
        unsigned int    _nbPlayers;
    };

}

#endif //CPP_INDIE_STUDIO_ROOM_HH

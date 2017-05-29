//
// Created by wurmel_a on 29/05/17.
//

#ifndef INDIE_SERVER_GAMEMANAGER_HH
#define INDIE_SERVER_GAMEMANAGER_HH

# include <mutex>
# include <memory>
# include <vector>
# include "Room.hh"

namespace   Indie
{
    class GameManager {
    public:
        GameManager();
        ~GameManager();

    public:
        static GameManager* getSingleton(bool reset = false);

    public:
        unsigned int const& createRoom();
        bool joinRoom(unsigned const&, std::string const&);
        std::vector<std::unique_ptr<Indie::Room> > const&   getRoomList();
        void    exitRoom(std::string const& pName);
        bool    runGame(unsigned int const&);

    public:
        void    lock();
        void    release();

    private:
        std::unique_ptr<std::mutex> _mutexLock;
        std::vector<std::unique_ptr<Indie::Room> >  _roomList;
    };
}

#endif //INDIE_SERVER_GAMEMANAGER_HH
//
// Created by wurmel_a on 07/06/17.
//

#ifndef CPP_INDIE_STUDIO_USER_HH
#define CPP_INDIE_STUDIO_USER_HH

# include <string>

namespace Indie {
    class User {
    public:
        User(std::string const&, std::string const&);
        ~User();

    public:
        std::string const&  getLogName() const;
        int getRoomId() const;

    public:
        void    joinRoomId(int roomId);

    public:
        static User    *getUser(std::string const& logName = "", std::string const& passwd = "", bool reset = false);

    private:
        std::string _logName;
        std::string _passwd;
        int    _roomId;
    };
}

#endif //CPP_INDIE_STUDIO_USER_HH

//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_DATAMANAGER_H
#define CPP_INDIE_STUDIO_DATAMANAGER_H

#include <string>

namespace   Indie {
    class DataManager {
    private:
        const std::string&  _ip;
        int                 _port;

    private:
        DataManager(const std::string&, int);
        ~DataManager();

    public:
        static DataManager  *getSingloton(const std::string&, int, bool reset = false);
        bool                connect(const std::string&, const std::string&);
    };
}

#endif //CPP_INDIE_STUDIO_DATAMANAGER_H

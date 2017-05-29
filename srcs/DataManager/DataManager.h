//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_DATAMANAGER_H
#define CPP_INDIE_STUDIO_DATAMANAGER_H


namespace   Indie {
    class DataManager {
    private:
        DataManager();
        ~DataManager();

    public:
        static DataManager  *getSingloton(bool reset = false);
    };
}

#endif //CPP_INDIE_STUDIO_DATAMANAGER_H

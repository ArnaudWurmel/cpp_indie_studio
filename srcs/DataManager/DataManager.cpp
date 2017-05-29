//
// Created by ballet on 29/05/17.
//

#include <cstring>
#include "DataManager.h"

Indie::DataManager::DataManager() {

}

Indie::DataManager::~DataManager() {

}

Indie::DataManager *Indie::DataManager::getSingloton(bool reset) {
    static Indie::DataManager *data = NULL;

    if (data == NULL)
        data = new Indie::DataManager();
    if (reset)
    {
        delete data;
        data = NULL;
    }
    return data;
}

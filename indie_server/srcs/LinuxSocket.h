//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_LINUXSOCKET_H
# define CPP_INDIE_STUDIO_LINUXSOCKET_H

#include "ISocket.h"

namespace   Indie {
    class   LinuxSocket : public ISocket {
    private:
        int fd;

    public:
        LinuxSocket();
        ~LinuxSocket();
    };
}

#endif //CPP_INDIE_STUDIO_LINUXSOCKET_H

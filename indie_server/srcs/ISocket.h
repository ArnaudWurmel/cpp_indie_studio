//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_ISOCKET_H
# define CPP_INDIE_STUDIO_ISOCKET_H

namespace   Indie {
    class   ISocket {
    public:
        virtual ~ISocket() {};

    public:
        virtual int getFd() = 0;
    };
}

#endif //CPP_INDIE_STUDIO_ISOCKET_H

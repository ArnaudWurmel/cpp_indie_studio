//
// SocketLinux.hh for  in /home/cham/Projets/cpp_indie_studio/srcs/Socket
//
// Made by Thibaud
// Login   <cham@epitech.net>
//
// Started on  Wed May 24 11:17:26 2017 Thibaud
// Last update Wed May 24 17:49:07 2017 Thibaud MARCHAND
//

#ifndef _SOCKETLINUX_HH_
# define _SOCKETLINUX_HH_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "ASocket.hh"

namespace Indie
{
  # define READ_SIZE 1
  class SocketLinux : public ASocket
  {
    private:
      int                 _fd;
      struct protoent     *_pe;
      struct sockaddr_in  _s_in;
      int                 _port;
    public:
      SocketLinux(int port, std::string path);
      ~SocketLinux();
      std::string readfd(int fd);
      int send_msg(int fd, std::string msg);
  };
}

#endif /* !SOCKETLINUX_HH_ */

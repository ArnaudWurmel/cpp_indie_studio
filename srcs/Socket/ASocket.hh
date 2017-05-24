//
// ASocket.hh for  in /home/cham/Projets/cpp_indie_studio/srcs/Socket
//
// Made by Thibaud
// Login   <cham@epitech.net>
//
// Started on  Wed May 24 10:53:56 2017 Thibaud
// Last update Wed May 24 17:47:05 2017 Thibaud MARCHAND
//

#ifndef _ASOCKET_HH_
# define _ASOCKET_HH_

#include <string>

class ASocket
{
public:
  virtual ~ASocket(){}
  virtual std::string readfd(int fd) = 0;
  virtual int send_response(int fd, int code, std::string msg) = 0;
};

#endif /* !ASOCKET_HH_ */

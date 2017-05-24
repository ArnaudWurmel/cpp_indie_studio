//
// SocketLinux.cpp for  in /home/cham/Projets/cpp_indie_studio/srcs/Socket
//
// Made by Thibaud
// Login   <cham@epitech.net>
//
// Started on  Wed May 24 11:17:21 2017 Thibaud
// Last update Wed May 24 17:50:04 2017 Thibaud MARCHAND
//

#include "SocketLinux.hh"

Indie::SocketLinux::SocketLinux(int port, std::string path)
{
  _port = port;
  _pe = getprotobyname("UDP");
  _fd = socket(AF_INET, SOCK_DGRAM, _pe->p_proto);
}

Indie::SocketLinux::~SocketLinux()
{
  close(_fd);
}

std::string get_next_line(int fd)
{
  int		j;
  size_t  pos;
  static int	i = 0;
  static std::string	save = "";
  char		buffer[READ_SIZE + 1];
  std::string		line;
  int		ch_read;

  j = 0;
  while ((pos = save.find("\n", i)) == std::string::npos)
    {
      if ((ch_read = read(fd, buffer, READ_SIZE)) <= 0)
	     return (NULL);
      buffer[ch_read] = '\0';
      save += buffer;
    }
  while (save[i] != '\n' && save[i] != '\0')
    line += save[i++];
  if (save[i] != '\0')
    i++;
  return (line);
}

std::string   Indie::SocketLinux::readfd(int fd)
{
  return (get_next_line(fd));
}

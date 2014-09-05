#ifndef GEMINO_GEMINO_SOCKET_H_
#define GEMINO_GEMINO_SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

namespace Gemino {
    namespace Core {
        class Socket {
            protected:
                int _socket;
                sockaddr_in _socket_info;
            public:
                static const int BACKLOG;
                static const int READ_BUFFER_LENGTH;

                Socket(int socket, sockaddr_in socket_info);
                Socket(int domain, int type, int protocol);
                ~Socket();

                void Bind(unsigned short int port);
                void Bind(unsigned short int port, unsigned long int address);
                void Bind(unsigned short int port, char *address);
                void Bind(unsigned short int port, const char *address);
                void Bind(short int family, unsigned short int port, unsigned long int address);
                void Bind(short int family, unsigned short int port, char *address);
                void Bind(short int family, unsigned short int port, const char *address);

                void Listen();
                void Listen(int backlog);

                Socket* Accept();

                void Close();

                void* Read();
                void* Read(int length);

                void Write(char *message);
                void Write(const char *message);
        };
    }
}

#endif // GEMINO_GEMINO_SOCKET_H_

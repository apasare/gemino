#include "Socket.h"

namespace Gemino {
    namespace Core {
        const int Socket::BACKLOG = 5;
        const int Socket::READ_BUFFER_LENGTH = 256;

        Socket::Socket(int socket, sockaddr_in socket_info) {
            this->_socket = socket;
            this->_socket_info = socket_info;
        }

        Socket::Socket(int domain, int type, int protocol) {
            this->_socket = socket(domain, type, protocol);
            if (this->_socket < 0) {
                perror("Gemino::Socket::Socket()");
                throw errno;
            }
        }

        Socket::~Socket() {
            this->Close();
        }

        void Socket::Bind(unsigned short int port) {
            this->Bind(AF_INET, port, (unsigned long int) INADDR_ANY);
        }

        void Socket::Bind(unsigned short int port, unsigned long int address) {
            this->Bind(AF_INET, port, address);
        }

        void Socket::Bind(unsigned short int port, char *address) {
            this->Bind(AF_INET, port, inet_addr(address));
        }

        void Socket::Bind(unsigned short int port, const char *address) {
            this->Bind(AF_INET, port, inet_addr(address));
        }

        void Socket::Bind(short int family, unsigned short int port, char *address) {
            this->Bind(family, port, inet_addr(address));
        }

        void Socket::Bind(short int family, unsigned short int port, const char *address) {
            this->Bind(family, port, inet_addr(address));
        }

        void Socket::Bind(short int family, unsigned short int port, unsigned long int address) {
            this->_socket_info.sin_family      = family;
            this->_socket_info.sin_port        = htons(port);
            this->_socket_info.sin_addr.s_addr = address;

            int binding = bind(this->_socket, (struct sockaddr *) &this->_socket_info, sizeof(this->_socket_info));
            if (binding < 0) {
                perror("Gemino::Socket::Bind()");
                throw errno;
            }
        }

        void Socket::Listen() {
            this->Listen(Socket::BACKLOG);
        }

        void Socket::Listen(int backlog) {
            int listening = listen(this->_socket, backlog);
            if (listening < 0) {
                perror("Gemino::Socket::Listen()");
                throw errno;
            }
        }

        Socket* Socket::Accept() {
            sockaddr_in socket_info;
            unsigned int socket_info_len = sizeof(socket_info);

            int session = accept(this->_socket, (struct sockaddr *) &socket_info, &socket_info_len);
            if (session < 0) {
                perror("Gemino::Socket::Accept()");
                throw errno;
            }

            Socket *Session = new Socket(session, socket_info);

            return Session;
        }

        void Socket::Close() {
            if (this->_socket >= 0) {
                shutdown(this->_socket, SHUT_WR);
                close(this->_socket);
            }
        }

        void* Socket::Read() {
            return this->Read(READ_BUFFER_LENGTH);
        }

        void* Socket::Read(int length) {
            void *buffer = malloc(length);
            int  readBytes = read(this->_socket, buffer, length);

            if (readBytes == -1) {
                perror("Gemino::Socket::Read()");
                throw errno;
            }

            return buffer;
        }

        void Socket::Write(char *message) {
            int result = write(this->_socket, message, strlen(message));
            if (result < 0) {
                perror("Gemino::Socket::Write()");
                throw errno;
            }
        }

        void Socket::Write(const char *message) {
            this->Write((char*)message);
        }
    }
}

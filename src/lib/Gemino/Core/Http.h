#ifndef GEMINO_GEMINO_HTTP_H_
#define GEMINO_GEMINO_HTTP_H_

#include "Socket.h"

namespace Gemino {
    namespace Core {
        class Http : public Socket {
            public:
                Http();
                Http(unsigned short int port);
                Http(unsigned short int port, char *address);
                Http(unsigned short int port, const char *address);
        };
    }
}

#endif // GEMINO_GEMINO_HTTP_H_

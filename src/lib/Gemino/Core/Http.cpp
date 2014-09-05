#include "Http.h"

namespace Gemino {
    namespace Core {
        Http::Http() : Socket(AF_INET, SOCK_STREAM, 0) {
            this->Bind(8080);
            this->Listen();
        }
    }
}